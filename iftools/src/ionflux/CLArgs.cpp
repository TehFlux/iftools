/* ==========================================================================
 * Ionflux Tools
 * Copyright (c) 2004 Joern P. Meier
 * mail@ionflux.org
 * --------------------------------------------------------------------------
 * CLArgs.cpp                    Command line argument parser.
 * ==========================================================================
 * 
 * This file is part of Ionflux Tools.
 * 
 * Ionflux Tools is free software; you can redistribute it and/or modify it 
 * under the terms of the GNU General Public License as published by the Free
 * Software Foundation; either version 2 of the License, or (at  your option)
 * any later version.
 * 
 * Ionflux Tools is distributed in the hope that it will be useful, but 
 * WITHOUT ANY WARRANTY; without even the implied warranty of MERCHANTABILITY
 * or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU General Public License
 * for more details.
 * 
 * You should have received a copy of the GNU General Public License
 * along with Ionflux Tools; if not, write to the Free Software Foundation, 
 * Inc., 59 Temple Place, Suite 330, Boston, MA 02111-1307 USA
 * 
 * ========================================================================== */

#include "ionflux/CLArgs.hpp"

using namespace std;

namespace Ionflux
{

namespace Tools
{

const TokenType CLArgs::TT_OPTION = {
	TokenType::USERTYPE_ID + 1, "-", false, 2};
const TokenType CLArgs::TT_ASSIGN = {
	TokenType::USERTYPE_ID + 2, "=", false, 1};

CLArgs::CLArgs()
: checkOptions(false)
{
	// TODO: Nothing ATM. ;-)
}

CLArgs::CLArgs(int argc, char *argv[])
: checkOptions(false)
{
	setArgs(argc, argv);
}

CLArgs::~CLArgs()
{
	clearAcceptableOptions();
	clearOptions();
}

bool CLArgs::addOption(CLOption *newOption)
{
	ostringstream status;
	if (newOption == 0)
	{
		log.msg("[CLArgs::addOption] WARNING: Ignoring attempt to add "
			"null option.", log.VL_WARNING);
		return false;
	}
	// Split option if possible.
	if (newOption->splittable && (newOption->option.size() > 1))
	{
		/* Option is splittable. Create additional options for each 
		   character of the option identifier. */
		CLOption *splitOption;
		unsigned int optionSize = newOption->option.size();
		for (unsigned int i = 0; i < optionSize; i++)
		{
			status.str("");
			status << "[CLArgs::addOption] DEBUG: Adding split option: '"
				<< newOption->option[i] << "'.";
			log.msg(status.str(), log.VL_DEBUG_INSANE);
			splitOption = new CLOption();
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
		status.str("");
		status << "[CLArgs::addOption] DEBUG: Command line option '" 
			<< newOption->option << "' not recognized.";
		log.msg(status.str(), log.VL_DEBUG_OPT);
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
	CLOption *currentOption = 0;
	Tokenizer tok;
	tok.addTokenType(TT_OPTION);
	tok.addTokenType(TT_ASSIGN);
	tok.setExtractQuoted(true);
	tok.setTokenTypeAnything();
	Token currentToken;
	string optionMarker;
	bool optionOpen = false;
	bool error = false;
	while (currentArg < args.size())
	{
		tok.setInput(args[currentArg]);
		currentToken = tok.getNextToken();
		if (currentToken.typeID == TT_OPTION.typeID)
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
			if (currentToken.typeID == Tokenizer::TT_IDENTIFIER.typeID)
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
					log.msg(string("[CLArgs::parse] ERROR: Invalid option "
						"marker: '") + optionMarker + "'", log.VL_ERROR);
					if (currentOption != 0)
						delete currentOption;
					return;
				}
			}
			currentToken = tok.getNextToken();
			optionOpen = true;
		}
		if (optionOpen 
			&& (currentToken.typeID != Tokenizer::TT_NONE.typeID))
		{
			// Extract rest of option value.
			log.assert(currentOption != 0, "[CLArgs::parse] Current option "
				"is null.");
			while ((currentToken.typeID != Tokenizer::TT_NONE.typeID)
				&& (currentToken.typeID != Tokenizer::TT_INVALID.typeID))
			{
				currentOption->value.append(currentToken.value);
				currentToken = tok.getNextToken();
			}
			addOption(currentOption);
			currentOption = 0;
			optionOpen = false;
		} else
		if (currentToken.typeID != Tokenizer::TT_NONE.typeID)
		{
			// Option not open, but further tokens available.
			log.assert(currentOption == 0, "[CLArgs::parse] Option not "
				"open, but current option not null.");
			error = false;
			if (currentToken.typeID == Tokenizer::TT_IDENTIFIER.typeID)
			{
				// Check for assignment style option.
				currentOption = new CLOption();
				currentOption->option = currentToken.value;
				currentOption->value = "";
				currentOption->splittable = false;
				currentToken = tok.getNextToken();
				if (currentToken.typeID == TT_ASSIGN.typeID)
				{
					// Append option value.
					currentToken = tok.getNextToken();
					while ((currentToken.typeID != Tokenizer::TT_NONE.typeID)
						&& (currentToken.typeID != Tokenizer::TT_INVALID.typeID))
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
					while ((currentToken.typeID != Tokenizer::TT_NONE.typeID)
						&& (currentToken.typeID != Tokenizer::TT_INVALID.typeID))
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
				while ((currentToken.typeID != Tokenizer::TT_NONE.typeID)
					&& (currentToken.typeID != Tokenizer::TT_INVALID.typeID))
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
				log.msg(string("[CLArgs::parse] ERROR: Parse error at "
					"token '") + currentToken.value + "'", log.VL_ERROR);
				if (currentOption != 0)
					delete currentOption;
				return;
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

void CLArgs::setArgs(int argc, char *argv[])
{
	clearOptions();
	for (int i = 1; i < argc; i++)
		args.push_back(argv[i]);
	parse();
}

CLOption *CLArgs::getOption(const std::string &searchOption)
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

bool CLArgs::isSet(const std::string &checkOption)
{
	unsigned int currentOption = 0;
	bool found = false;
	while (!found && (currentOption < options.size()))
	{
		if (options[currentOption]->option == checkOption)
			found = true;
		else
			currentOption++;
	}
	return found;
}

void CLArgs::getParams(CLParams &target)
{
	target.clear();
	for (unsigned int i = 0; i < params.size(); i++)
		target.push_back(params[i]);
}

void CLArgs::setCheckOptions(bool newCheckOptions)
{
	checkOptions = newCheckOptions;
}

void CLArgs::addAcceptableOption(const std::string &newOption, 
	bool newAcceptValue)
{
	checkOptions = true;
	CLAcceptableOption *newAcceptableOption = new CLAcceptableOption();
	newAcceptableOption->option = newOption;
	newAcceptableOption->acceptValue = newAcceptValue;
	acceptable.push_back(newAcceptableOption);
}

bool CLArgs::getCheckOptions()
{
	return checkOptions;
}

CLAcceptableOption *CLArgs::getAcceptableOption(
	const std::string &searchOption)
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

bool CLArgs::isAcceptable(const std::string &checkOption)
{
	if (!checkOptions)
		return true;
	CLAcceptableOption *result = getAcceptableOption(checkOption);
	if (result == 0)
		return false;
	return true;
}

bool CLArgs::acceptsValue(const std::string &checkOption)
{
	if (!checkOptions)
		return true;
	CLAcceptableOption *result = getAcceptableOption(checkOption);
	if (result == 0)
		return false;
	return result->acceptValue;
}

std::vector<std::string> &CLArgs::getInvalidOptions()
{
	return invalidOptions;
}

bool CLArgs::optionsOK()
{
	if (invalidOptions.size() > 0)
		return false;
	return true;
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

void CLArgs::printDebugInfo()
{
	cout << "Number of command line options: " << options.size() << endl;
	for (unsigned int i = 0; i < options.size(); i++)
	{
		cout << "Option [" << i << "]: ";
		if (options[i] == 0)
			cout << "(null)" << endl;
		else
		{
			cout << endl 
				<< "    option = " << options[i]->option << endl
				<< "    value  = " << options[i]->value << endl;
		}
	}
	cout << "Number of command line parameters: " << params.size() << endl;
	for (unsigned int i = 0; i < params.size(); i++)
	{
		cout << "Parameter [" << i << "]: '" << params[i] << "'" << endl;
	}
	cout << "Check for acceptable command line options: ";
	if (checkOptions)
		cout << "yes";
	else
		cout << "no";
	cout << endl;
	cout << "Number of acceptable command line options: " 
		<< acceptable.size() << endl;
	for (unsigned int i = 0; i < acceptable.size(); i++)
	{
		cout << "Option [" << i << "]: ";
		if (acceptable[i] == 0)
			cout << "(null)" << endl;
		else
		{
			cout << endl 
				<< "    option       = " << acceptable[i]->option << endl
				<< "    acceptValue  = " << acceptable[i]->acceptValue << endl;
		}
	}
}

Reporter &CLArgs::getLog()
{
	return log;
}

}

}

/** \file CLArgs.cpp
 * \brief Command line argument parser implementation.
 */
