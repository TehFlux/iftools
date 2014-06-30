/* ==========================================================================
 * IFTemplate - Ionflux Template Processor
 * Copyright © 2012 Jörn P. Meier
 * mail@ionflux.org
 * --------------------------------------------------------------------------
 * CLArgs.cpp                      Command line argument parser 
 * (implementation).
 * =========================================================================
 * 
 * This file is part of IFTemplate - Ionflux Template Processor.
 * 
 * IFTemplate - Ionflux Template Processor is free software; you can 
 * redistribute it and/or modify it under the terms of the GNU General 
 * Public License as published by the Free Software Foundation; either 
 * version 2 of the License, or (at your option) any later version.
 * 
 * IFTemplate - Ionflux Template Processor is distributed in the hope that 
 * it will be useful, but WITHOUT ANY WARRANTY; without even the implied 
 * warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See 
 * the GNU General Public License for more details.
 * 
 * You should have received a copy of the GNU General Public License along 
 * with IFTemplate - Ionflux Template Processor; if not, write to the Free 
 * Software Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA 
 * 02111-1307 USA
 * 
 * ========================================================================== */

#include "iftemplate/CLArgs.hpp"
#include <iostream>
#include <iomanip>
#include <sstream>
#include <fstream>
#include "ifobject/utils.hpp"
#include "iftemplate/utils.hpp"
#include "iftemplate/IFTemplateError.hpp"

using namespace std;

namespace Ionflux
{

namespace Template
{

CLArgsClassInfo::CLArgsClassInfo()
{
	name = "CLArgs";
	desc = "Command line argument parser";
	baseClassInfo.push_back(Ionflux::ObjectBase::IFObject::CLASS_INFO);
}

CLArgsClassInfo::~CLArgsClassInfo()
{
}

// public member constants
const Ionflux::Template::TokenType CLArgs::TT_OPTION = { TT_ID_USERTYPE + 1, "-", false, 2 };
const Ionflux::Template::TokenType CLArgs::TT_ASSIGN = { TT_ID_USERTYPE + 2, "=", false, 1 };
const Ionflux::Template::CLOption CLArgs::OPTION_NOT_SET = { "", "", false };

// run-time type information instance constants
const CLArgsClassInfo CLArgs::cLArgsClassInfo;
const Ionflux::ObjectBase::IFClassInfo* CLArgs::CLASS_INFO = &CLArgs::cLArgsClassInfo;

CLArgs::CLArgs()
: checkOptions(false)
{
	// NOTE: The following line is required for run-time type information.
	theClass = CLASS_INFO;
	// TODO: Nothing ATM. ;-)
}

CLArgs::CLArgs(const Ionflux::Template::CLArgs& other)
: checkOptions(false)
{
	// NOTE: The following line is required for run-time type information.
	theClass = CLASS_INFO;
	*this = other;
}

CLArgs::CLArgs(int argc, char** argv)
: checkOptions(false)
{
	// NOTE: The following line is required for run-time type information.
	theClass = CLASS_INFO;
	setArgs(argc, argv);
}

CLArgs::~CLArgs()
{
	clearAcceptableOptions();
	clearOptions();
}

bool CLArgs::addOption(Ionflux::Template::CLOption* newOption)
{
	std::ostringstream status;
	if (newOption == 0)
	    throw IFTemplateError("[CLArgs::addOption] "
	        "Attempt to add null option.");
	// Split option if possible.
	if (newOption->splittable && (newOption->option.size() > 1))
	{
	    /* Option is splittable. Create additional options for each 
	       character of the option identifier. */
	    CLOption *splitOption;
	    unsigned int optionSize = newOption->option.size();
	    for (unsigned int i = 0; i < optionSize; i++)
	    {
	        /* <---- DEBUG ----- //
	        status.str("");
	        status << "[CLArgs::addOption] DEBUG: Adding split option: '"
	            << newOption->option[i] << "'.";
	        log.msg(status.str(), log.VL_DEBUG_INSANE);
	        // ----- DEBUG ----> */
	        splitOption = Ionflux::ObjectBase::create<CLOption>(
	            "CLArgs::addOption", "option");
	        splitOption->option.append(1, newOption->option[i]);
	        /* Make sure the last option specified retains its value, or at
	           least the value gets added as a parameter if the last option 
	           does not accept a value. */
	        if (i < (optionSize - 1))
	            splitOption->value = "";
	        else
	            splitOption->value = newOption->value;
	        addOption(splitOption);
	        splitOption = 0;
	    }
	    delete newOption;
	    return false;
	}
	// Add option if option checking is disabled.
	if (!checkOptions)
	{
	    options.push_back(newOption);
	    return true;
	}
	// Option checking enabled. Check whether option is acceptable.
	CLAcceptableOption *acceptableOption = getAcceptableOption(
	    newOption->option);
	if (acceptableOption != 0)
	{
	    // Create new parameter if option does not accept a value.
	    if (!acceptableOption->acceptValue && (newOption->value != ""))
	    {
	        params.push_back(newOption->value);
	        newOption->value = "";
	    }
	    options.push_back(newOption);
	} else
	{
	    // Invalid option.
	    /* <---- DEBUG ----- //
	    status.str("");
	    status << "[CLArgs::addOption] DEBUG: Command line option '" 
	        << newOption->option << "' not recognized.";
	    log.msg(status.str(), log.VL_DEBUG_OPT);
	    // ----- DEBUG ----> */
	    invalidOptions.push_back(newOption->option);
	    // There might still be a parameter which we should extract.
	    if (newOption->value.size() > 0)
	        params.push_back(newOption->value);
	    delete newOption;
	    return false;
	}
	return true;
}

void CLArgs::parse()
{
	if (args.size() == 0)
	    return;
	options.clear();
	params.clear();
	unsigned int currentArg = 0;
	CLOption* currentOption = 0;
	Tokenizer tok;
	tok.addTokenType(TT_OPTION);
	tok.addTokenType(TT_ASSIGN);
	tok.setExtractQuoted(true);
	tok.setTokenTypeAnything();
	Token currentToken;
	string optionMarker;
	bool optionOpen = false;
	bool error = false;
	std::ostringstream status;
	while (currentArg < args.size())
	{
	    tok.setInput(args[currentArg]);
	    currentToken = tok.getNextToken();
	    if (hasType(currentToken, TT_OPTION.typeID))
	    {
	        // Handle option marker.
	        if (currentOption != 0)
	        {
	            // Add open option.
	            addOption(currentOption);
	            currentOption = 0;
	        }
	        optionMarker = currentToken.value;
	        currentToken = tok.getNextToken();
	        currentOption = new CLOption();
	        if (hasType(currentToken, TT_IDENTIFIER.typeID))
	        {
	            if ((optionMarker == "--") || (optionMarker == "-"))
	            {
	                // Extract option identifier.
	                currentOption->option = currentToken.value;
	                currentOption->value = "";
	                if (optionMarker == "--")
	                    currentOption->splittable = false;
	                else
	                    currentOption->splittable = true;
	            } else
	            {
	                status.str("");
	                status << "Invalid option marker: '" << optionMarker 
	                    << "'";
	                if (currentOption != 0)
	                    delete currentOption;
	                throw IFTemplateError(getErrorString(status.str(), 
	                    "parse"));
	            }
	        }
	        currentToken = tok.getNextToken();
	        optionOpen = true;
	    }
	    if (optionOpen 
	        && !hasType(currentToken, TT_NONE.typeID))
	    {
	        // Extract rest of option value.
	        if (currentOption == 0)
	            throw IFTemplateError(getErrorString("Current option "
	                "is null.", "parse"));
	        while ((currentToken.typeID != TT_NONE.typeID)
	            && (currentToken.typeID != TT_INVALID.typeID))
	        {
	            currentOption->value.append(currentToken.value);
	            currentToken = tok.getNextToken();
	        }
	        addOption(currentOption);
	        currentOption = 0;
	        optionOpen = false;
	    } else
	    if (!hasType(currentToken, TT_NONE.typeID))
	    {
	        // Option not open, but further tokens available.
	        if (currentOption != 0)
	            throw IFTemplateError(getErrorString("Option not "
	                "open, but current option not null.", "parse"));
	        error = false;
	        if (hasType(currentToken, TT_IDENTIFIER.typeID))
	        {
	            // Check for assignment style option.
	            currentOption = new CLOption();
	            currentOption->option = currentToken.value;
	            currentOption->value = "";
	            currentOption->splittable = false;
	            currentToken = tok.getNextToken();
	            if (hasType(currentToken, TT_ASSIGN.typeID))
	            {
	                // Append option value.
	                currentToken = tok.getNextToken();
	                while (isNonEmpty(currentToken))
	                {
	                    currentOption->value.append(currentToken.value);
	                    currentToken = tok.getNextToken();
	                }
	                addOption(currentOption);
	                currentOption = 0;
	            } else
	            {
	                // Not an assignment option. Create a parameter.
	                currentOption->option.append(currentToken.value);
	                currentToken = tok.getNextToken();
	                while (isNonEmpty(currentToken))
	                {
	                    currentOption->option.append(currentToken.value);
	                    currentToken = tok.getNextToken();
	                }
	                params.push_back(currentOption->option);
	                delete currentOption;
	                currentOption = 0;
	            }
	        } else
	        {
	            // Not an identifier. Create a parameter.
	            // TODO: Remove code duplicates
	            currentOption = new CLOption();
	            currentOption->option = currentToken.value;
	            currentOption->value = "";
	            currentOption->splittable = false;
	            currentToken = tok.getNextToken();
	            while (isNonEmpty(currentToken))
	            {
	                currentOption->option.append(currentToken.value);
	                currentToken = tok.getNextToken();
	            }
	            params.push_back(currentOption->option);
	            delete currentOption;
	            currentOption = 0;
	        }
	        if (error)
	        {
	            status.str("");
	            status << "Parse error at token '" << currentToken.value 
	                << "'.";
	            if (currentOption != 0)
	                delete currentOption;
	            throw IFTemplateError(getErrorString(status.str(), "parse"));
	        }
	    } else
	    if (currentArg == (args.size() - 1))
	    {
	        // Option open, but no further tokens or arguments available.
	        addOption(currentOption);
	        currentOption = 0;
	        optionOpen = false;
	    }
	    currentArg++;
	}
}

void CLArgs::clearAcceptableOptions()
{
	for (unsigned int i = 0; i < acceptable.size(); i++)
	{
	    if (acceptable[i] != 0)
	        delete acceptable[i];
	    acceptable[i] = 0;
	}
	acceptable.clear();
	checkOptions = false;
}

void CLArgs::clearOptions()
{
	for (unsigned int i = 0; i < options.size(); i++)
	{
	    if (options[i] != 0)
	        delete options[i];
	    options[i] = 0;
	}
	options.clear();
	invalidOptions.clear();
}

void CLArgs::clearParams()
{
	params.clear();
}

void CLArgs::setArgs(int argc, char** argv)
{
	clearOptions();
	for (int i = 1; i < argc; i++)
	    args.push_back(argv[i]);
	parse();
}

void CLArgs::setArgs(const Ionflux::ObjectBase::StringVector& newArgs)
{
	clearOptions();
	for (int i = 1; i < newArgs.size(); i++)
	    args.push_back(newArgs[i]);
	parse();
}

Ionflux::Template::CLOption* CLArgs::getOption(const std::string& 
searchOption)
{
	CLOption *result = 0;
	unsigned int currentOption = 0;
	bool found = false;
	while (!found && (currentOption < options.size()))
	{
	    if (options[currentOption]->option == searchOption)
	        found = true;
	    else
	        currentOption++;
	}
	if (found)
	    result = options[currentOption];
	return result;
}

bool CLArgs::isSet(const std::string& checkOption)
{
	unsigned int currentOption = 0;
	bool found = false;
	while (!found 
	    && (currentOption < options.size()))
	{
	    if (options[currentOption]->option == checkOption)
	        found = true;
	    else
	        currentOption++;
	}
	return found;
}

void CLArgs::getParams(Ionflux::Template::CLParams& target)
{
	target.clear();
	for (unsigned int i = 0; i < params.size(); i++)
	    target.push_back(params[i]);
}

void CLArgs::addAcceptableOption(const std::string& newOption, bool 
newAcceptValue)
{
	checkOptions = true;
	CLAcceptableOption* newAcceptableOption = new CLAcceptableOption();
	newAcceptableOption->option = newOption;
	newAcceptableOption->acceptValue = newAcceptValue;
	acceptable.push_back(newAcceptableOption);
}

Ionflux::Template::CLAcceptableOption* CLArgs::getAcceptableOption(const 
std::string& searchOption)
{
	CLAcceptableOption *result = 0;
	unsigned int currentOption = 0;
	bool found = false;
	while (!found && (currentOption < acceptable.size()))
	{
	    if (acceptable[currentOption]->option == searchOption)
	        found = true;
	    else
	        currentOption++;
	}
	if (found)
	    result = acceptable[currentOption];
	return result;
}

bool CLArgs::isAcceptable(const std::string& checkOption)
{
	if (!checkOptions)
	    return true;
	CLAcceptableOption *result = getAcceptableOption(checkOption);
	if (result == 0)
	    return false;
	return true;
}

bool CLArgs::acceptsValue(const std::string& checkOption)
{
	if (!checkOptions)
	    return true;
	CLAcceptableOption *result = getAcceptableOption(checkOption);
	if (result == 0)
	    return false;
	return result->acceptValue;
}

Ionflux::ObjectBase::StringVector& CLArgs::getInvalidOptions()
{
	// TODO: Implementation.
	return invalidOptions;
}

bool CLArgs::optionsOK()
{
	if (invalidOptions.size() > 0)
	    return false;
	return true;
}

void CLArgs::printDebugInfo()
{
	std::cout << "Number of command line options: " << options.size() << 
	std::endl;
	for (unsigned int i = 0; i < options.size(); i++)
	{
	    std::cout << "Option [" << i << "]: ";
	    if (options[i] == 0)
	        std::cout << "(null)" << std::endl;
	    else
	    {
	        std::cout << std::endl 
	            << "    option = " << options[i]->option << std::endl
	            << "    value  = " << options[i]->value << std::endl;
	    }
	}
	std::cout << "Number of command line parameters: " << params.size() << 
	std::endl;
	for (unsigned int i = 0; i < params.size(); i++)
	{
	    std::cout << "Parameter [" << i << "]: '" << params[i] << "'" << 
	std::endl;
	}
	std::cout << "Check for acceptable command line options: ";
	if (checkOptions)
	    std::cout << "yes";
	else
	    std::cout << "no";
	std::cout << std::endl;
	std::cout << "Number of acceptable command line options: " 
	    << acceptable.size() << std::endl;
	for (unsigned int i = 0; i < acceptable.size(); i++)
	{
	    std::cout << "Option [" << i << "]: ";
	    if (acceptable[i] == 0)
	        std::cout << "(null)" << std::endl;
	    else
	    {
	        std::cout << std::endl 
	            << "    option       = " << acceptable[i]->option << std::endl
	            << "    acceptValue  = " << acceptable[i]->acceptValue << 
	std::endl;
	    }
	}
}

void CLArgs::setCheckOptions(bool newCheckOptions)
{
	checkOptions = newCheckOptions;
}

bool CLArgs::getCheckOptions() const
{
    return checkOptions;
}

Ionflux::Template::CLArgs& CLArgs::operator=(const 
Ionflux::Template::CLArgs& other)
{
if (this == &other)
    return *this;
	return *this;
}

Ionflux::Template::CLArgs* CLArgs::copy() const
{
    CLArgs* newCLArgs = create();
    *newCLArgs = *this;
    return newCLArgs;
}

Ionflux::Template::CLArgs* CLArgs::upcast(Ionflux::ObjectBase::IFObject* 
other)
{
    return dynamic_cast<CLArgs*>(other);
}

Ionflux::Template::CLArgs* CLArgs::create(Ionflux::ObjectBase::IFObject* 
parentObject)
{
    CLArgs* newObject = new CLArgs();
    if (newObject == 0)
    {
        return 0;
    }
    if (parentObject != 0)
        parentObject->addLocalRef(newObject);
    return newObject;
}

unsigned int CLArgs::getMemSize() const
{
    return sizeof *this;
}

}

}

/** \file CLArgs.cpp
 * \brief Command line argument parser implementation.
 */
