/* ==========================================================================
 * Ionflux Tools
 * Copyright (c) 2004 Joern P. Meier
 * mail@ionflux.org
 * --------------------------------------------------------------------------
 * StringManipulator.cpp              String manipulators.
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

#include <cstdlib>

#include "ionflux/StringManipulator.hpp"

using namespace std;

namespace Ionflux
{

namespace Tools
{

const string StringUppercase::STRINGMANIP_NAME = "uppercase";

std::string StringUppercase::process(const std::string& bytes, 
	std::vector<std::string>* args)
{
	ostringstream result;
	unsigned int numChars;
	if ((args != 0) && (args->size() >= 1))
		numChars = strtol((*args)[0].c_str(), 0, 10);
	else
		numChars = bytes.size();
	char currentChar;
	for (unsigned int i = 0; i < bytes.size(); i++)
	{
		if (i < numChars)
			currentChar = static_cast<char>(toupper(bytes[i]));
		else
			currentChar = bytes[i];
		result << currentChar;
	}
	return result.str();
}

std::string StringUppercase::getName()
{
	return STRINGMANIP_NAME;
}

const string StringLowercase::STRINGMANIP_NAME = "lowercase";

std::string StringLowercase::process(const std::string& bytes, 
	std::vector<std::string>* args)
{
	ostringstream result;
	unsigned int numChars;
	if ((args != 0) && (args->size() >= 1))
		numChars = strtol((*args)[0].c_str(), 0, 10);
	else
		numChars = bytes.size();
	char currentChar;
	for (unsigned int i = 0; i < bytes.size(); i++)
	{
		if (i < numChars)
			currentChar = static_cast<char>(tolower(bytes[i]));
		else
			currentChar = bytes[i];
		result << currentChar;
	}
	return result.str();
}

std::string StringLowercase::getName()
{
	return STRINGMANIP_NAME;
}

const string StringErase::STRINGMANIP_NAME = "erase";

std::string StringErase::process(const std::string& bytes, 
	std::vector<std::string>* args)
{
	if ((args == 0) || (args->size() == 0))
		return bytes;
	string result = bytes;
	string eraseBytes = (*args)[0];
	string::size_type currentPos;
	while ((currentPos = result.find(eraseBytes)) != string::npos)
		result.erase(currentPos, eraseBytes.size());
	return result;
}

std::string StringErase::getName()
{
	return STRINGMANIP_NAME;
}

const string StringReplace::STRINGMANIP_NAME = "replace";

std::string StringReplace::process(const std::string& bytes, 
	std::vector<std::string>* args)
{
	if ((args == 0) || (args->size() < 2))
		return bytes;
	string result = bytes;
	string replaceBytes = (*args)[0];
	string replaceWith = (*args)[1];
	string::size_type currentPos;
	while ((currentPos = result.find(replaceBytes)) != string::npos)
		result.replace(currentPos, replaceBytes.size(), replaceWith);
	return result;
}

std::string StringReplace::getName()
{
	return STRINGMANIP_NAME;
}

const string StringTrim::STRINGMANIP_NAME = "trim";

std::string StringTrim::process(const std::string& bytes, 
	std::vector<std::string>* args)
{
	return trim(bytes);
}

std::string StringTrim::getName()
{
	return STRINGMANIP_NAME;
}

const string StringLTrim::STRINGMANIP_NAME = "ltrim";

std::string StringLTrim::process(const std::string& bytes, 
	std::vector<std::string>* args)
{
	return trim(bytes, true, false);
}

std::string StringLTrim::getName()
{
	return STRINGMANIP_NAME;
}

const string StringRTrim::STRINGMANIP_NAME = "rtrim";

std::string StringRTrim::process(const std::string& bytes, 
	std::vector<std::string>* args)
{
	return trim(bytes, false, true);
}

std::string StringRTrim::getName()
{
	return STRINGMANIP_NAME;
}

const string StringTruncate::STRINGMANIP_NAME = "truncate";

std::string StringTruncate::process(const std::string& bytes, 
	std::vector<std::string>* args)
{
	if ((args == 0) || (args->size() < 1))
		return bytes;
	unsigned int length = strtol((*args)[0].c_str(), 0, 10);
	if (bytes.size() <= length)
		return bytes;
	string dots = "";
	if (args->size() >= 2)
		dots = (*args)[1];
	if (length > 0)
		return bytes.substr(0, length - dots.size()) + dots;
	return "";
}

std::string StringTruncate::getName()
{
	return STRINGMANIP_NAME;
}

const string StringCenter::STRINGMANIP_NAME = "center";

std::string StringCenter::process(const std::string& bytes, 
	std::vector<std::string>* args)
{
	if ((args == 0) || (args->size() < 1))
		return bytes;
	unsigned int width = strtol((*args)[0].c_str(), 0, 10);
	string result = "";
	string buffer = "";
	string padding = "";
	string centerpadding = " ";
	if (args->size() >= 2)
		padding = (*args)[1];
	if (args->size() >= 3)
		centerpadding = (*args)[2];
	buffer = padding + bytes + padding;
	if (result.size() < width)
	{
		unsigned int padwidth = width - result.size();
		unsigned int padleft = padwidth / 2;
		unsigned int padright = padwidth - padleft;
		char padchar;
		if  (centerpadding.size() > 0)
			padchar = centerpadding[0];
		else
			padchar = ' ';
		result.append(padleft, padchar);
		result.append(buffer);
		result.append(padright, padchar);
	}
	return result;
}

std::string StringCenter::getName()
{
	return STRINGMANIP_NAME;
}

const string StringMove::STRINGMANIP_NAME = "move";

std::string StringMove::process(const std::string& bytes, 
	std::vector<std::string>* args)
{
	if ((args == 0) || (args->size() < 3))
		return bytes;
	unsigned int start = strtol((*args)[0].c_str(), 0, 10);
	unsigned int length = strtol((*args)[1].c_str(), 0, 10);
	unsigned int pos;
	if ((*args)[2] == "front")
		pos = 0;
	else
	if ((*args)[2] == "back")
		pos = bytes.size();
	else
		pos = strtol((*args)[2].c_str(), 0, 10);
	if ((start < 0) || ((start + length) > bytes.size()) 
		|| (pos > bytes.size()) || (pos < 0))
		return bytes;
	string result = bytes;
	string sub = bytes.substr(start, length);
	if (pos < bytes.size())
		result.insert(pos, sub);
	else
		result.append(sub);
	if (pos < start)
		result.erase(start + length, length);
	else
		result.erase(start, length);
	return result;
}

std::string StringMove::getName()
{
	return STRINGMANIP_NAME;
}

const string StringAppend::STRINGMANIP_NAME = "append";

std::string StringAppend::process(const std::string& bytes, 
	std::vector<std::string>* args)
{
	if ((args == 0) || (args->size() < 1))
		return bytes;
	string result = bytes;
	result.append((*args)[0]);
	return result;
}

std::string StringAppend::getName()
{
	return STRINGMANIP_NAME;
}

const string StringInsert::STRINGMANIP_NAME = "insert";

std::string StringInsert::process(const std::string& bytes, 
	std::vector<std::string>* args)
{
	if ((args == 0) || (args->size() < 2))
		return bytes;
	unsigned int pos;
	if ((*args)[1] == "front")
		pos = 0;
	else
	if ((*args)[1] == "back")
		pos = bytes.size();
	else
		pos = strtol((*args)[1].c_str(), 0, 10);
	if ((pos > bytes.size()) || (pos < 0))
		return bytes;
	string result = bytes;
	if (pos < bytes.size())
		result.insert(pos, (*args)[0]);
	else
		result.append((*args)[0]);
	return result;
}

std::string StringInsert::getName()
{
	return STRINGMANIP_NAME;
}

const string StringNumFormat::STRINGMANIP_NAME = "numformat";

std::string StringNumFormat::process(const std::string& bytes, 
	std::vector<std::string>* args)
{
	if ((args == 0) || (args->size() < 3))
		return bytes;
	string integers = "";
	string decimals = "";
	string result = "";
	unsigned int numDecimals = strtol((*args)[0].c_str(), 0, 10);
	string dsep = (*args)[1];
	string tsep = (*args)[2];
	unsigned int pos = 0;
	// Find first digit.
	while ((pos < bytes.size()) && !isdigit(bytes[pos]))
		pos++;
	// Extract integer part.
	while ((pos < bytes.size()) && isdigit(bytes[pos]))
	{
		integers.append(1, bytes[pos]);
		pos++;
	}
	// Extract decimal part.
	if ((pos < bytes.size()) && (bytes[pos] == '.'))
	{
		pos++;
		while ((pos < bytes.size()) && isdigit(bytes[pos]))
		{
			decimals.append(1, bytes[pos]);
			pos++;
		}
	}
	if (decimals.size() < numDecimals)
		decimals.append(numDecimals - decimals.size(), '0');
	// Add integer part with thousands separators to result.
	int numIndex;
	for (int i = (integers.size() - 1); i >= 0; i--)
	{
		numIndex = integers.size() - 1 - i;
		if ((numIndex != 0) && ((numIndex % 3) == 0))
			result.insert(0, tsep);
		result.insert(0, 1, integers[i]);
	}
	if (numDecimals > 0)
	{
		result.append(dsep);
		result.append(decimals.substr(0, numDecimals));
	}
	return result;
}

std::string StringNumFormat::getName()
{
	return STRINGMANIP_NAME;
}

const string StringTranslate::STRINGMANIP_NAME = "translate";

std::string StringTranslate::process(const std::string& bytes, 
	std::vector<std::string>* args)
{
	if ((args == 0) || (args->size() < 2))
		return bytes;
	string source = (*args)[0];
	string target = (*args)[1];
	int numChars;
	source.size() > target.size() 
		? (numChars = target.size())
		: (numChars = source.size());
	string result = "";
	bool match;
	int pos;
	for (unsigned int i = 0; i < bytes.size(); i++)
	{
		match = false;
		pos = 0;
		while (!match && (pos < numChars))
		{
			if (bytes[i] == source[pos])
				match = true;
			else
				pos++;
		}
		if (match)
			result.append(1, target[pos]);
		else
			result.append(1, bytes[i]);
	}
	return result;
}

std::string StringTranslate::getName()
{
	return STRINGMANIP_NAME;
}

const string StringSubstr::STRINGMANIP_NAME = "substr";

std::string StringSubstr::process(const std::string& bytes, 
	std::vector<std::string>* args)
{
	if ((args == 0) || (args->size() < 2))
		return bytes;
	int startIndex = strtol((*args)[0].c_str(), 0, 10);
	int numChars = strtol((*args)[1].c_str(), 0, 10);
	if (startIndex < 0)
		startIndex = 0;
	if (static_cast<unsigned int>(startIndex + numChars) > bytes.size())
		numChars = bytes.size() - startIndex;
	if (numChars <= 0)
		return "";
	return bytes.substr(startIndex, numChars);
}

std::string StringSubstr::getName()
{
	return STRINGMANIP_NAME;
}

const string StringLPad::STRINGMANIP_NAME = "lpad";

std::string StringLPad::process(const std::string& bytes, 
	std::vector<std::string>* args)
{
	if ((args == 0) || (args->size() < 2))
		return bytes;
	char padChar = (*args)[0][0];
	int fieldWidth = strtol((*args)[1].c_str(), 0, 10);
	int padWidth = fieldWidth - bytes.size();
	string result;
	if (padWidth <= 0)
		return bytes;
	result.append(padWidth, padChar);
	result.append(bytes);
	return result;
}

std::string StringLPad::getName()
{
	return STRINGMANIP_NAME;
}

const string StringRPad::STRINGMANIP_NAME = "rpad";

std::string StringRPad::process(const std::string& bytes, 
	std::vector<std::string>* args)
{
	if ((args == 0) || (args->size() < 2))
		return bytes;
	char padChar = (*args)[0][0];
	int fieldWidth = strtol((*args)[1].c_str(), 0, 10);
	int padWidth = fieldWidth - bytes.size();
	string result;
	if (padWidth <= 0)
		return bytes;
	result.append(bytes);
	result.append(padWidth, padChar);
	return result;
}

std::string StringRPad::getName()
{
	return STRINGMANIP_NAME;
}

const string StringSWrap::STRINGMANIP_NAME = "swrap";

std::string StringSWrap::process(const std::string& bytes, 
	std::vector<std::string>* args)
{
	if ((args == 0) || (args->size() < 1))
		return bytes;
	unsigned int lineWidth = strtol((*args)[0].c_str(), 0, 10);
	if (lineWidth <= 0)
		return bytes;
	string prefix;
	if (args->size() >= 2)
		prefix = (*args)[1];
	string lineTerm("\n");
	if (args->size() >= 3)
		lineTerm = (*args)[2];
	string result;
	string currentLine = prefix;
	string testLine;
	string currentWord;
	Tokenizer tok;
	tok.clearTokenTypes();
	tok.addTokenType(Tokenizer::TT_WHITESPACE);
	tok.addTokenType(Tokenizer::TT_LINETERM);
	tok.setTokenTypeAnything();
	tok.setInput(bytes);
	Token currentToken = tok.getNextToken();
	while ((currentToken.typeID != Tokenizer::TT_NONE.typeID)
		&& (currentToken.typeID != Tokenizer::TT_INVALID.typeID))
	{
		currentWord = currentToken.value;
		testLine = currentLine + currentWord;
		if (currentToken.typeID == Tokenizer::TT_LINETERM.typeID)
		{
			// Handle line terminator.
			currentLine.append(currentWord);
			if ((currentWord.size() > 0) && (currentWord[0] != '\r'))
			{
				// Line terminated in the input string, start a new one.
				result.append(currentLine);
				currentLine = prefix;
			}
		} else
		{
			// Handle other tokens.
			if (testLine.size() > lineWidth)
			{
				// Current word does not fit on current line.
				if (currentLine.size() == prefix.size())
				{
					/* Current word is too long to fit on one line, but since 
					   this is a soft wrap, we have to add it anyway. */
					currentLine.append(currentWord);
					currentToken = tok.getNextToken();
				}
				result.append(currentLine);
				// Remove whitespace after current word.
				while (currentToken.typeID == Tokenizer::TT_WHITESPACE.typeID)
					currentToken = tok.getNextToken();
				currentWord = currentToken.value;
				if (currentToken.typeID != Tokenizer::TT_NONE.typeID)
				{
					/* If there are more tokens available, add line 
					   terminator and set current word on next line. */
					result.append(lineTerm);
					currentLine = prefix + currentWord;
				} else
					// No more tokens.
					currentLine = "";
			} else
			{
				// Current word fits on current line.
				currentLine.append(currentWord);
			}
		}
		currentToken = tok.getNextToken();
	}
	if (currentLine.size() > prefix.size())
		result.append(currentLine);
	return result;
}

std::string StringSWrap::getName()
{
	return STRINGMANIP_NAME;
}

const string StringXMLEscape::STRINGMANIP_NAME = "xmlescape";

std::string StringXMLEscape::process(const std::string& bytes, 
	std::vector<std::string>* args)
{
	return xmlEscape(bytes);
}

std::string StringXMLEscape::getName()
{
	return STRINGMANIP_NAME;
}

const string StringURLEncode::STRINGMANIP_NAME = "urlencode";

std::string StringURLEncode::process(const std::string& bytes, 
	std::vector<std::string>* args)
{
	return urlEncode(bytes);
}

std::string StringURLEncode::getName()
{
	return STRINGMANIP_NAME;
}

}

}

/** \file StringManipulator.cpp
 * \brief String manipulators implementation.
 */
