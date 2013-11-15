/* ==========================================================================
 * IFTemplate - Ionflux Template Processor
 * Copyright © 2012 Jörn P. Meier
 * mail@ionflux.org
 * --------------------------------------------------------------------------
 * StringFilter.cpp                String filter (implementation).
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

#include "iftemplate/StringFilter.hpp"
#include <iostream>
#include <iomanip>
#include <sstream>
#include "ifobject/utils.hpp"
#include "iftemplate/constants.hpp"
#include "iftemplate/utils.hpp"
#include "iftemplate/IFTemplateError.hpp"
#include "iftemplate/StringFilterFunction.hpp"
#include "iftemplate/StringUppercase.hpp"
#include "iftemplate/StringLowercase.hpp"
#include "iftemplate/StringTrim.hpp"
#include "iftemplate/StringSWrap.hpp"
#include "iftemplate/StringErase.hpp"
#include "iftemplate/StringAppend.hpp"
#include "iftemplate/StringInsert.hpp"
#include "iftemplate/StringNumFormat.hpp"
#include "iftemplate/StringTranslate.hpp"
#include "iftemplate/StringReplace.hpp"
#include "iftemplate/StringSubstr.hpp"
#include "iftemplate/StringRPad.hpp"
#include "iftemplate/StringLPad.hpp"
#include "iftemplate/StringXMLEscape.hpp"
#include "iftemplate/StringURLEncode.hpp"

using namespace std;

namespace Ionflux
{

namespace Template
{

StringFilterClassInfo::StringFilterClassInfo()
{
	name = "StringFilter";
	desc = "String filter";
	baseClassInfo.push_back(Ionflux::ObjectBase::IFObject::CLASS_INFO);
}

StringFilterClassInfo::~StringFilterClassInfo()
{
}

// public member constants
const Ionflux::Template::TokenType StringFilter::TT_FUNC_SEP = { TT_ID_USERTYPE + 1, "|", false, 1 };
const Ionflux::Template::TokenType StringFilter::TT_FUNC_BRACKET_LEFT = { TT_ID_USERTYPE + 2, "(", false, 1 };
const Ionflux::Template::TokenType StringFilter::TT_FUNC_BRACKET_RIGHT = { TT_ID_USERTYPE + 3, ")", false, 1 };
const Ionflux::Template::TokenType StringFilter::TT_FUNC_ARG_SEP = { TT_ID_USERTYPE + 4, ",", false, 1 };

// run-time type information instance constants
const StringFilterClassInfo StringFilter::stringFilterClassInfo;
const Ionflux::ObjectBase::IFClassInfo* StringFilter::CLASS_INFO = &StringFilter::stringFilterClassInfo;

StringFilter::StringFilter()
{
	// NOTE: The following line is required for run-time type information.
	theClass = CLASS_INFO;
	initTokenTypes();
	addDefaultManipulators();
}

StringFilter::StringFilter(const Ionflux::Template::StringFilter& other)
{
	// NOTE: The following line is required for run-time type information.
	theClass = CLASS_INFO;
	*this = other;
}

StringFilter::StringFilter(const std::string& initFilter)
{
	// NOTE: The following line is required for run-time type information.
	theClass = CLASS_INFO;
	initTokenTypes();
	addDefaultManipulators();
	setFilter(initFilter);
}

StringFilter::~StringFilter()
{
	clearFunctions();
	clearManipulators();
	// TODO: Nothing ATM. ;-)
}

void StringFilter::initTokenTypes()
{
	tok.addTokenType(TT_FUNC_SEP);
	tok.addTokenType(TT_FUNC_BRACKET_LEFT);
	tok.addTokenType(TT_FUNC_BRACKET_RIGHT);
	tok.addTokenType(TT_FUNC_ARG_SEP);
	tok.setExtractQuoted(true);
}

void StringFilter::parse()
{
	std::ostringstream status;
	bool error = false;
	string errorReason;
	StringFilterFunction* currentFunc = 0;
	clearFunctions();
	tok.setInput(filter);
	Token currentToken = tok.getNextToken();
	while (isNonEmpty(currentToken)
	    && !error)
	{
	    if (hasType(currentToken, TT_IDENTIFIER.typeID))
	    {
	        // Extract function name.
	        currentFunc = StringFilterFunction::create();
	        currentFunc->setFunc(currentToken.value);
	        currentFunc->setManip(
	            Ionflux::ObjectBase::nullPointerCheck(
	                getManipulatorByName(currentToken.value), 
	                "StringFilter::parse", "String manipulator"));
	        currentToken = tok.getNextToken();
	        if (hasType(currentToken, TT_FUNC_BRACKET_LEFT.typeID))
	        {
	            // Extract arguments.
	            currentToken = tok.getNextToken();
	            // Skip leading whitespace.
	            while (hasType(currentToken, TT_WHITESPACE.typeID))
	                currentToken = tok.getNextToken();
	            while (!error
	                && (hasType(currentToken, TT_IDENTIFIER.typeID)
	                    || hasType(currentToken, TT_QUOTED.typeID)))
	            {
	                currentFunc->addArgument(currentToken.value);
	                currentToken = tok.getNextToken();
	                // Skip trailing whitespace.
	                while (hasType(currentToken, 
	                    TT_WHITESPACE.typeID))
	                    currentToken = tok.getNextToken();
	                if (hasType(currentToken, TT_FUNC_ARG_SEP.typeID))
	                {
	                    // Skip argument separator.
	                    currentToken = tok.getNextToken();
	                    // Skip trailing whitespace.
	                    while (hasType(currentToken, 
	                        TT_WHITESPACE.typeID))
	                        currentToken = tok.getNextToken();
	                } else
	                if (!hasType(currentToken, TT_FUNC_BRACKET_RIGHT.typeID))
	                {
	                    error = true;
	                    errorReason = "Closing function bracket expected.";
	                }
	            }
	            if (hasType(currentToken, TT_FUNC_BRACKET_RIGHT.typeID))
	                // Skip closing bracket.
	                currentToken = tok.getNextToken();
	            else
	            {
	                error = true;
	                errorReason = "Closing function bracket expected.";
	            }
	        }
	        if (hasType(currentToken, TT_NONE.typeID)
	            || hasType(currentToken, TT_FUNC_SEP.typeID))
	        {
	            addFunction(currentFunc);
	            currentFunc = 0;
	        } else
	        {
	            error = true;
	            errorReason = "Function separator expected.";
	        }
	    }
	    if (!error)
	        /* Skip function separator. (If this is the last function, 
	           this doesn't really do anything.) */
	        currentToken = tok.getNextToken();
	}
	if (hasType(currentToken, TT_INVALID.typeID))
	{
	    error = true;
	    errorReason = "Invalid token.";
	}
	if (error)
	{
	    string ws("");
	    int errPos = tok.getCurrentTokenPos();
	    if (errPos > 0)
	        ws.append(errPos, ' ');
	    status.str("");
	    status << "[StringFilter::parse] Parse error at position " 
	        << errPos << ":" << endl << filter << endl << ws << "^" << endl
	        << "(" << errorReason << ")";
	    if (currentFunc != 0)
	        delete currentFunc;
	    clearFunctions();
	    throw IFTemplateError(status.str());
	} else
	if (currentFunc != 0)
	{
	    functions.push_back(currentFunc);
	    currentFunc = 0;
	}
}

Ionflux::Template::StringManipulator::StringManipulator* 
StringFilter::getManipulatorByName(const std::string& manipName)
{
	StringManipulatorNameMap::iterator i = manipByName.find(manipName);
	if (i != manipByName.end())
	    return (*i).second;
	return 0;
}

void StringFilter::addDefaultManipulators()
{
	// TODO: Add default manipulators.
	addManipulator(StringManipulator::StringTrim::create());
	addManipulator(StringManipulator::StringSWrap::create());
	addManipulator(StringManipulator::StringUppercase::create());
	addManipulator(StringManipulator::StringLowercase::create());
	addManipulator(StringManipulator::StringErase::create());
	addManipulator(StringManipulator::StringAppend::create());
	addManipulator(StringManipulator::StringInsert::create());
	addManipulator(StringManipulator::StringNumFormat::create());
	addManipulator(StringManipulator::StringTranslate::create());
	addManipulator(StringManipulator::StringReplace::create());
	addManipulator(StringManipulator::StringSubstr::create());
	addManipulator(StringManipulator::StringRPad::create());
	addManipulator(StringManipulator::StringLPad::create());
	addManipulator(StringManipulator::StringXMLEscape::create());
	addManipulator(StringManipulator::StringURLEncode::create());
	updateIndices();
}

std::string StringFilter::apply(const std::string& bytes)
{
	string result = bytes;
	StringFilterFunctionVector::iterator i;
	StringFilterFunction* currentFunc = 0;
	for (i = functions.begin(); i != functions.end(); i++)
	{
	    currentFunc = *i;
	    StringManipulator::StringManipulator* m0 = currentFunc->getManip();
	    if (m0 != 0)
	        result = m0->process(result, &(currentFunc->getArguments()));
	    else
	    {
	        // <---- DEBUG ----- //
	        std::cout << "[StringFilter::apply] WARNING: "
	            "Skipping manipulator '" + currentFunc->getFunc() 
	            + "' (implementation not available).";
	        // ----- DEBUG ----> */
	    }
	}
	return result;
}

void StringFilter::updateIndices()
{
	manipByName.clear();
	for (StringManipulatorVector::iterator i = manipulators.begin(); 
	    i != manipulators.end(); i++)
	{
	    StringManipulator::StringManipulator* m0 = *i;
	    if (m0 != 0)
	    {
	        std::string mName = m0->getManipName();
	        StringManipulator::StringManipulator* m1 = 
	            getManipulatorByName(mName);
	        if (m1 != 0)
	        {
	            std::ostringstream status;
	            status << "[StringFilter::updateIndices] "
	                "Duplicate index entry for '" << mName << "'.";
	            throw IFTemplateError(status.str());
	        }
	        manipByName[mName] = m0;
	    }
	}
}

void StringFilter::printDebugInfo()
{
	std::cout << "[StringFilter] Functions:" << std::endl;
	StringFilterFunctionVector::const_iterator i;
	StringFilterFunction* currentFunc;
	for (i = functions.begin(); i != functions.end(); i++)
	{
	    currentFunc = *i;
	    std::cout << currentFunc->getFunc() << ":" << std::endl;
	    if (currentFunc->getManip() != 0)
	        std::cout << "    manipulator: (available)" << std::endl;
	    else
	        std::cout << "    manipulator: (not available)" << std::endl;
	    std::cout << "    arguments:" << std::endl;
	    if (currentFunc->getNumArguments() > 0)
	        for (unsigned int k = 0; 
	            k < currentFunc->getNumArguments(); k++)
	            std::cout << "        '" << currentFunc->getArgument(k) 
	                << "'" << std::endl;
	    else
	        std::cout << "        (no arguments)" << std::endl;
	}
}

void StringFilter::setFilter(const std::string& newFilter)
{
	filter = newFilter;
	parse();
}

std::string StringFilter::getFilter() const
{
    return filter;
}

unsigned int StringFilter::getNumFunctions() const
{
    return functions.size();
}

Ionflux::Template::StringFilterFunction* StringFilter::getFunction(unsigned
int elementIndex) const
{
    if (elementIndex < functions.size())
		return functions[elementIndex];
	return 0;
}

int StringFilter::findFunction(Ionflux::Template::StringFilterFunction* 
needle, unsigned int occurence) const
{
    bool found = false;
	Ionflux::Template::StringFilterFunction* currentFunction = 0;
	unsigned int i = 0;
	while (!found 
		&& (i < functions.size()))
	{
		currentFunction = functions[i];
		if (currentFunction == needle)
        {
            if (occurence == 1)
			    found = true;
            else
                occurence--;
		} else
			i++;
	}
	if (found)
        return i;
	return -1;
}

std::vector<Ionflux::Template::StringFilterFunction*>& 
StringFilter::getFunctions()
{
    return functions;
}

void StringFilter::addFunction(Ionflux::Template::StringFilterFunction* 
addElement)
{
	addLocalRef(addElement);
	functions.push_back(addElement);
}

void StringFilter::removeFunction(Ionflux::Template::StringFilterFunction* 
removeElement)
{
    bool found = false;
	Ionflux::Template::StringFilterFunction* currentFunction = 0;
	unsigned int i = 0;
	while (!found 
		&& (i < functions.size()))
	{
		currentFunction = functions[i];
		if (currentFunction == removeElement)
			found = true;
		else
			i++;
	}
	if (found)
	{
		functions.erase(functions.begin() + i);
		if (currentFunction != 0)
			removeLocalRef(currentFunction);
	}
}

void StringFilter::removeFunctionIndex(unsigned int removeIndex)
{
    if (removeIndex > functions.size())
        return;
	Ionflux::Template::StringFilterFunction* e0 = functions[removeIndex];
    functions.erase(functions.begin() + removeIndex);
    if (e0 != 0)
        removeLocalRef(e0);
}

void StringFilter::clearFunctions()
{
    std::vector<Ionflux::Template::StringFilterFunction*>::iterator i;
	for (i = functions.begin(); i != functions.end(); i++)
		if (*i != 0)
			removeLocalRef(*i);
	functions.clear();
}

unsigned int StringFilter::getNumManipulators() const
{
    return manipulators.size();
}

Ionflux::Template::StringManipulator::StringManipulator* 
StringFilter::getManipulator(unsigned int elementIndex) const
{
    if (elementIndex < manipulators.size())
		return manipulators[elementIndex];
	return 0;
}

int 
StringFilter::findManipulator(Ionflux::Template::StringManipulator::StringManipulator*
needle, unsigned int occurence) const
{
    bool found = false;
	Ionflux::Template::StringManipulator::StringManipulator* currentManipulator = 0;
	unsigned int i = 0;
	while (!found 
		&& (i < manipulators.size()))
	{
		currentManipulator = manipulators[i];
		if (currentManipulator == needle)
        {
            if (occurence == 1)
			    found = true;
            else
                occurence--;
		} else
			i++;
	}
	if (found)
        return i;
	return -1;
}

std::vector<Ionflux::Template::StringManipulator::StringManipulator*>& 
StringFilter::getManipulators()
{
    return manipulators;
}

void 
StringFilter::addManipulator(Ionflux::Template::StringManipulator::StringManipulator*
addElement)
{
	addLocalRef(addElement);
	manipulators.push_back(addElement);
}

void 
StringFilter::removeManipulator(Ionflux::Template::StringManipulator::StringManipulator*
removeElement)
{
    bool found = false;
	Ionflux::Template::StringManipulator::StringManipulator* currentManipulator = 0;
	unsigned int i = 0;
	while (!found 
		&& (i < manipulators.size()))
	{
		currentManipulator = manipulators[i];
		if (currentManipulator == removeElement)
			found = true;
		else
			i++;
	}
	if (found)
	{
		manipulators.erase(manipulators.begin() + i);
		if (currentManipulator != 0)
			removeLocalRef(currentManipulator);
	}
}

void StringFilter::removeManipulatorIndex(unsigned int removeIndex)
{
    if (removeIndex > manipulators.size())
        return;
	Ionflux::Template::StringManipulator::StringManipulator* e0 = manipulators[removeIndex];
    manipulators.erase(manipulators.begin() + removeIndex);
    if (e0 != 0)
        removeLocalRef(e0);
}

void StringFilter::clearManipulators()
{
    std::vector<Ionflux::Template::StringManipulator::StringManipulator*>::iterator i;
	for (i = manipulators.begin(); i != manipulators.end(); i++)
		if (*i != 0)
			removeLocalRef(*i);
	manipulators.clear();
}

Ionflux::Template::StringFilter& StringFilter::operator=(const 
Ionflux::Template::StringFilter& other)
{
if (this == &other)
    return *this;
	return *this;
}

Ionflux::Template::StringFilter* StringFilter::copy() const
{
    StringFilter* newStringFilter = create();
    *newStringFilter = *this;
    return newStringFilter;
}

Ionflux::Template::StringFilter* 
StringFilter::upcast(Ionflux::ObjectBase::IFObject* other)
{
    return dynamic_cast<StringFilter*>(other);
}

Ionflux::Template::StringFilter* 
StringFilter::create(Ionflux::ObjectBase::IFObject* parentObject)
{
    StringFilter* newObject = new StringFilter();
    if (newObject == 0)
    {
        throw IFTemplateError("Could not allocate object.");
    }
    if (parentObject != 0)
        parentObject->addLocalRef(newObject);
    return newObject;
}

Ionflux::Template::StringFilter* StringFilter::create(const std::string& 
initFilter, Ionflux::ObjectBase::IFObject* parentObject)
{
    StringFilter* newObject = new StringFilter(initFilter);
    if (newObject == 0)
    {
        throw IFTemplateError("Could not allocate object.");
    }
    if (parentObject != 0)
        parentObject->addLocalRef(newObject);
    return newObject;
}

}

}

/** \file StringFilter.cpp
 * \brief String filter implementation.
 */
