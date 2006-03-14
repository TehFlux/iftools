/* ==========================================================================
 * Ionflux Tools
 * Copyright (c) 2004 Joern P. Meier
 * mail@ionflux.org
 * --------------------------------------------------------------------------
 * StringFilter.cpp                    String filter.
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

#include "ionflux/StringFilter.hpp"

using namespace std;

namespace Ionflux
{

namespace Tools
{

const TokenType StringFilter::TT_FUNC_SEP = {
	TokenType::USERTYPE_ID + 1, "|", false, 1};
const TokenType StringFilter::TT_FUNC_BRACKET_LEFT = {
	TokenType::USERTYPE_ID + 2, "(", false, 1};
const TokenType StringFilter::TT_FUNC_BRACKET_RIGHT = {
	TokenType::USERTYPE_ID + 3, ")", false, 1};
const TokenType StringFilter::TT_FUNC_ARG_SEP = {
	TokenType::USERTYPE_ID + 5, ",", false, 1};

StringUppercase StringFilter::STRINGMANIP_UPPERCASE;
StringLowercase StringFilter::STRINGMANIP_LOWERCASE;
StringErase StringFilter::STRINGMANIP_ERASE;
StringReplace StringFilter::STRINGMANIP_REPLACE;
StringTrim StringFilter::STRINGMANIP_TRIM;
StringLTrim StringFilter::STRINGMANIP_LTRIM;
StringRTrim StringFilter::STRINGMANIP_RTRIM;
StringTruncate StringFilter::STRINGMANIP_TRUNCATE;
StringCenter StringFilter::STRINGMANIP_CENTER;
StringMove StringFilter::STRINGMANIP_MOVE;
StringAppend StringFilter::STRINGMANIP_APPEND;
StringInsert StringFilter::STRINGMANIP_INSERT;
StringNumFormat StringFilter::STRINGMANIP_NUMFORMAT;
StringTranslate StringFilter::STRINGMANIP_TRANSLATE;
StringSubstr StringFilter::STRINGMANIP_SUBSTR;
StringLPad StringFilter::STRINGMANIP_LPAD;
StringRPad StringFilter::STRINGMANIP_RPAD;
StringSWrap StringFilter::STRINGMANIP_SWRAP;
StringXMLEscape StringFilter::STRINGMANIP_XMLESCAPE;
StringURLEncode StringFilter::STRINGMANIP_URLENCODE;

StringFilter::StringFilter()
: filter("")
{
	initTokenTypes();
	initManipulators();
}

StringFilter::StringFilter(const std::string& initFilter)
: filter("")
{
	initTokenTypes();
	initManipulators();
	setFilter(initFilter);
}

StringFilter::~StringFilter()
{
	clearFunctions();
	clearManipulators();
}

void StringFilter::clearFunctions()
{
	vector<StringFilterFunction *>::iterator i;
	StringFilterFunction *currentFunc;
	while (functions.size() > 0)
	{
		i = functions.begin();
		currentFunc = *i;
		functions.erase(i);
		delete currentFunc;
	}
}

void StringFilter::clearManipulators()
{
	vector<StringManipulatorEntry>::iterator i;
	StringManipulatorEntry currentEntry;
	while (manipulators.size() > 0)
	{
		i = manipulators.begin();
		currentEntry = *i;
		manipulators.erase(i);
		if (currentEntry.manage)
			delete currentEntry.manip;
	}
	manipIndex.clear();
}

void StringFilter::initManipulators()
{
	addManipulator(&STRINGMANIP_UPPERCASE, false);
	addManipulator(&STRINGMANIP_LOWERCASE, false);
	addManipulator(&STRINGMANIP_ERASE, false);
	addManipulator(&STRINGMANIP_REPLACE, false);
	addManipulator(&STRINGMANIP_TRIM, false);
	addManipulator(&STRINGMANIP_LTRIM, false);
	addManipulator(&STRINGMANIP_RTRIM, false);
	addManipulator(&STRINGMANIP_TRUNCATE, false);
	addManipulator(&STRINGMANIP_CENTER, false);
	addManipulator(&STRINGMANIP_MOVE, false);
	addManipulator(&STRINGMANIP_APPEND, false);
	addManipulator(&STRINGMANIP_INSERT, false);
	addManipulator(&STRINGMANIP_NUMFORMAT, false);
	addManipulator(&STRINGMANIP_TRANSLATE, false);
	addManipulator(&STRINGMANIP_SUBSTR, false);
	addManipulator(&STRINGMANIP_RPAD, false);
	addManipulator(&STRINGMANIP_LPAD, false);
	addManipulator(&STRINGMANIP_SWRAP, false);
	addManipulator(&STRINGMANIP_XMLESCAPE, false);
	addManipulator(&STRINGMANIP_URLENCODE, false);
}

void StringFilter::initTokenTypes()
{
	tok.addTokenType(TT_FUNC_SEP);
	tok.addTokenType(TT_FUNC_BRACKET_LEFT);
	tok.addTokenType(TT_FUNC_BRACKET_RIGHT);
	tok.addTokenType(TT_FUNC_ARG_SEP);
	tok.setExtractQuoted(true);
}

StringManipulator *StringFilter::getManipulator(const std::string& manipName)
{
	return manipIndex[manipName];
}

void StringFilter::parse()
{
	ostringstream status;
	bool error = false;
	string errorReason;
	StringFilterFunction *currentFunc = 0;
	clearFunctions();
	tok.setInput(filter);
	Token currentToken = tok.getNextToken();
	while ((currentToken.typeID != Tokenizer::TT_NONE.typeID)
		&& (currentToken.typeID != Tokenizer::TT_INVALID.typeID)
		&& !error)
	{
		if (currentToken.typeID == Tokenizer::TT_IDENTIFIER.typeID)
		{
			// Extract function name.
			currentFunc = new StringFilterFunction;
			currentFunc->func = currentToken.value;
			currentFunc->manip = getManipulator(currentToken.value);
			currentToken = tok.getNextToken();
			if (currentToken.typeID == TT_FUNC_BRACKET_LEFT.typeID)
			{
				// Extract arguments.
				currentToken = tok.getNextToken();
				// Skip leading whitespace.
				while (currentToken.typeID == Tokenizer::TT_WHITESPACE.typeID)
					currentToken = tok.getNextToken();
				while (!error
					&& ((currentToken.typeID == Tokenizer::TT_IDENTIFIER.typeID)
						|| (currentToken.typeID == Tokenizer::TT_QUOTED.typeID)))
				{
					currentFunc->args.push_back(currentToken.value);
					currentToken = tok.getNextToken();
					// Skip trailing whitespace.
					while (currentToken.typeID 
						== Tokenizer::TT_WHITESPACE.typeID)
						currentToken = tok.getNextToken();
					if (currentToken.typeID == TT_FUNC_ARG_SEP.typeID)
					{
						// Skip argument separator.
						currentToken = tok.getNextToken();
						// Skip trailing whitespace.
						while (currentToken.typeID 
							== Tokenizer::TT_WHITESPACE.typeID)
							currentToken = tok.getNextToken();
					} else
					if (currentToken.typeID != TT_FUNC_BRACKET_RIGHT.typeID)
					{
						error = true;
						errorReason = "Closing function bracket expected.";
					}
				}
				if (currentToken.typeID == TT_FUNC_BRACKET_RIGHT.typeID)
					// Skip closing bracket.
					currentToken = tok.getNextToken();
				else
				{
					error = true;
					errorReason = "Closing function bracket expected.";
				}
			}
			if ((currentToken.typeID == Tokenizer::TT_NONE.typeID)
				|| (currentToken.typeID == TT_FUNC_SEP.typeID))
			{
				functions.push_back(currentFunc);
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
	if (currentToken.typeID == Tokenizer::TT_INVALID.typeID)
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
		status << "[StringFilter::parse] ERROR: Parse error at position " 
			<< errPos << ":" << endl << filter << endl << ws << "^" << endl
			<< "(" << errorReason << ")";
		log.msg(status.str(), log.VL_ERROR);
		if (currentFunc != 0)
			delete currentFunc;
		clearFunctions();
	} else
	if (currentFunc != 0)
	{
		functions.push_back(currentFunc);
		currentFunc = 0;
	}
}

void StringFilter::setFilter(const std::string& newFilter)
{
	filter = newFilter;
	parse();
}

void StringFilter::addManipulator(StringManipulator *newManip, bool manage)
{
	if (newManip == 0)
		return;
	StringManipulatorEntry entry;
	entry.manip = newManip;
	entry.manage = manage;
	manipulators.push_back(entry);
	manipIndex[newManip->getName()] = newManip;
}

std::string StringFilter::apply(const std::string& bytes)
{
	string result = bytes;
	vector<StringFilterFunction *>::const_iterator i;
	StringFilterFunction *currentFunc;
	for (i = functions.begin(); i != functions.end(); i++)
	{
		currentFunc = *i;
		if (currentFunc->manip != 0)
			result = currentFunc->manip->process(result, &(currentFunc->args));
		else
			log.msg(string("[StringFilter::apply] WARNING: Skipping "
				"manipulator '") + currentFunc->func 
				+ "' (implementation not available).", log.VL_WARNING);
	}
	return result;
}

void StringFilter::printDebugInfo()
{
	cout << "[StringFilter] Functions:" << endl;
	vector<StringFilterFunction *>::const_iterator i;
	vector<string>::const_iterator k;
	StringFilterFunction *currentFunc;
	for (i = functions.begin(); i != functions.end(); i++)
	{
		currentFunc = *i;
		cout << currentFunc->func << ":" << endl;
		if (currentFunc->manip != 0)
			cout << "    manipulator: (available)" << endl;
		else
			cout << "    manipulator: (not available)" << endl;
		cout << "    arguments:" << endl;
		if (currentFunc->args.size() > 0)
			for (k = currentFunc->args.begin(); k != currentFunc->args.end(); k++)
				cout << "        '" << *k << "'" << endl;
		else
			cout << "        (no arguments)" << endl;
	}
}

Reporter &StringFilter::getLog()
{
	return log;
}

}

}

/** \file StringFilter.cpp
 * \brief String filter implementation.
 */
