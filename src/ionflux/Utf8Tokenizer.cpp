/* ==========================================================================
 * Ionflux Tools
 * Copyright (c) 2005 Joern P. Meier
 * mail@ionflux.org
 * --------------------------------------------------------------------------
 * Utf8Tokenizer.cpp               Tokenizer with UTF-8 support.
 * ==========================================================================
 * 
 * This file is part of Ionflux Tools.
 * 
 * Ionflux Tools is free software; you can redistribute it and/or modify it
 * under the terms of the GNU General Public License as published by the 
 * Free Software Foundation; either version 2 of the License, or (at your 
 * option) any later version.
 * 
 * Ionflux Tools is distributed in the hope that it will be useful, but 
 * WITHOUT ANY WARRANTY; without even the implied warranty of 
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU 
 * General Public License for more details.
 * 
 * You should have received a copy of the GNU General Public License along 
 * with Ionflux Tools; if not, write to the Free Software Foundation, Inc.,
 * 59 Temple Place, Suite 330, Boston, MA 02111-1307 USA
 * 
 * ========================================================================== */

#include "ionflux/Utf8Tokenizer.hpp"
#include "ionflux/tools.hpp"

using namespace std;
using namespace Ionflux::Tools;

namespace Ionflux
{

namespace Tools
{

Utf8TokenizerClassInfo::Utf8TokenizerClassInfo()
{
	name = "Utf8Tokenizer";
	desc = "Tokenizer with UTF-8 support";
}

const Utf8TokenType Utf8Tokenizer::TT_INVALID = {
	Utf8TokenType::INVALID_ID, "", 0};
const Utf8TokenType Utf8Tokenizer::TT_NONE = {
	Utf8TokenType::EMPTY_ID, "", 0};
const Utf8TokenType Utf8Tokenizer::TT_DEFAULT = {1, "", 0};
const Utf8TokenType Utf8Tokenizer::TT_QUOTED = {2, "", 0};
const Utf8TokenType Utf8Tokenizer::TT_ESCAPED = {3, "", 0};
const Utf8TokenType Utf8Tokenizer::TT_LINEAR_WHITESPACE = {4, " \t", 0};
const Utf8TokenType Utf8Tokenizer::TT_LINETERM = {5, "\n\r", 1};
const Utf8TokenType Utf8Tokenizer::TT_IDENTIFIER = {6, 
		"abcdefghijklmnopqrstuvwxyz"
		"ABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789_", 0};
const Utf8TokenType Utf8Tokenizer::TT_NUMBER = {7, "0123456789", 0};
const Utf8TokenType Utf8Tokenizer::TT_ALPHA = {8, 
		"abcdefghijklmnopqrstuvwxyz"
		"ABCDEFGHIJKLMNOPQRSTUVWXYZ", 0};
const Utf8TokenType Utf8Tokenizer::TT_DEFAULT_SEP = {9, "_-.", 0};
const Utf8TokenType Utf8Tokenizer::TT_LATIN = {10, 
		"abcdefghijklmnopqrstuvwxyz"
		"ABCDEFGHIJKLMNOPQRSTUVWXYZ"
		"ÀÁÂÃÄÅÆÇÈÉÊËÌÍÎÏÐÑÒÓÔÕÖØÙÚÛÜÝÞßàáâãäåæçèéêëìíî"
		"ïðñòóôõöøùúûüýþÿĀāĂăĄąĆćĈĉĊċČčĎďĐđĒēĔĕĖėĘęĚěĜ"
		"ĞğĠġĢģĤĥĦħĨĩĪīĬĭĮįİıĲĳĴĵĶķĸĹĺĻļĽľĿŀŁłŃńŅņŇňŉŊŋŌ"
		"ōŎŏŐőŒœŔŕŖŗŘřŚśŜŝŞşŠšŢţŤťŦŧŨũŪūŬŭŮůŰűŲųŴŵŶŷŸŹźŻżŽžſ", 0};
const Utf8Token Utf8Tokenizer::TOK_INVALID = {
	Utf8TokenType::INVALID_ID, ""};
const Utf8Token Utf8Tokenizer::TOK_NONE = {
	Utf8TokenType::EMPTY_ID, ""};
const std::string Utf8Tokenizer::QUOTE_CHARS = "'\"";
const unsigned int Utf8Tokenizer::ESCAPE_CHAR = '\\';

const Utf8TokenizerClassInfo Utf8Tokenizer::utf8TokenizerClassInfo;
const ClassInfo* Utf8Tokenizer::CLASS_INFO = 
	&Utf8Tokenizer::utf8TokenizerClassInfo;

Utf8Tokenizer::Utf8Tokenizer()
: currentPos(0), currentTokenPos(0), currentQuoteChar(0), typeMap(0), 
  extractQuoted(false), extractEscaped(false)
{
	// NOTE: The following line is required for class information.
	theClasses.push_back(CLASS_INFO);
	typeMap = new Utf8TokenTypeMap();
	utf8ToUInt(QUOTE_CHARS, quoteChars);
	useDefaultTokenTypes();
	currentToken = TOK_INVALID;
}

Utf8Tokenizer::Utf8Tokenizer(const std::string& initInput)
: currentPos(0), currentTokenPos(0), currentQuoteChar(0), typeMap(0), 
  extractQuoted(false), extractEscaped(false)
{
	// NOTE: The following line is required for class information.
	theClasses.push_back(CLASS_INFO);
	typeMap = new Utf8TokenTypeMap();
	utf8ToUInt(QUOTE_CHARS, quoteChars);
	useDefaultTokenTypes();
	setInput(initInput);
	currentToken = TOK_INVALID;
}

Utf8Tokenizer::Utf8Tokenizer(const std::vector<Utf8TokenType>& initTokenTypes, 
const std::string& initInput)
: currentPos(0), currentTokenPos(0), currentQuoteChar(0), typeMap(0), 
  extractQuoted(false), extractEscaped(false)
{
	// NOTE: The following line is required for class information.
	theClasses.push_back(CLASS_INFO);
	typeMap = new Utf8TokenTypeMap();
	utf8ToUInt(QUOTE_CHARS, quoteChars);
	setTokenTypes(initTokenTypes);
	if (initInput.size() > 0)
		setInput(initInput);
	currentToken = TOK_INVALID;
}

Utf8Tokenizer::~Utf8Tokenizer()
{
	if (typeMap != 0)
		delete typeMap;
	typeMap = 0;
}

void Utf8Tokenizer::reset()
{
	currentPos = 0;
	currentTokenPos = 0;
	currentQuoteChar = 0;
	currentToken = TOK_INVALID;
}

void Utf8Tokenizer::clearTokenTypes()
{
	typeMap->clear();
}

void Utf8Tokenizer::useDefaultTokenTypes()
{
	typeMap->clear();
	typeMap->addTokenType(TT_LINEAR_WHITESPACE);
	typeMap->addTokenType(TT_IDENTIFIER);
	typeMap->addTokenType(TT_LINETERM);
}

void Utf8Tokenizer::addDefaultTokenType()
{
	typeMap->setDefaultTokenType(TT_DEFAULT);
}

void Utf8Tokenizer::setTokenTypes(const std::vector<Utf8TokenType>& 
newTokenTypes)
{
	typeMap->clear();
	addTokenTypes(newTokenTypes);
}

void Utf8Tokenizer::addTokenTypes(const std::vector<Utf8TokenType>& 
newTokenTypes)
{
	for (vector<Utf8TokenType>::const_iterator i = newTokenTypes.begin();
		i != newTokenTypes.end(); i++)
		typeMap->addTokenType(*i);
}

void Utf8Tokenizer::addTokenType(const Utf8TokenType& newTokenType)
{
	typeMap->addTokenType(newTokenType);
}

void Utf8Tokenizer::setInput(const std::string& newInput)
{
	theInput.clear();
	reset();
	utf8ToUInt(newInput, theInput);
}

void Utf8Tokenizer::setInput(const std::vector<unsigned int>& newInput)
{
	theInput.clear();
	reset();
	for (vector<unsigned int>::const_iterator i = newInput.begin();
		i != newInput.end(); i++)
		theInput.push_back(*i);
}

Utf8Token Utf8Tokenizer::getNextToken(Utf8TokenTypeMap* otherTypeMap)
{
	if (otherTypeMap == 0)
		otherTypeMap = typeMap;
	if ((currentPos >= theInput.size()) 
		|| (otherTypeMap->getNumTokenTypes() == 0))
		return TOK_NONE;
	unsigned int maxChars;
	unsigned int tokenChars;
	currentToken = TOK_INVALID;
	Utf8TokenType currentTokenType = TT_INVALID;
	unsigned int quoteChar = 0;
	currentQuoteChar = 0;
	if (extractEscaped 
		&& (theInput[currentPos] == ESCAPE_CHAR))
	{
		// Extract escaped characters.
		currentPos++;
		if (currentPos < theInput.size())
			// Append quoted character.
			currentToken.value.append(uintToUtf8(theInput[currentPos]));
		currentToken.typeID = TT_ESCAPED.typeID;
		currentPos++;
		return currentToken;
	}
	if (extractQuoted)
	{
		// Extract quoted strings.
		while((currentPos < theInput.size())
			&& ((theInput[currentPos] == ESCAPE_CHAR)
				|| utf8IsOneOf(theInput[currentPos], quoteChars)
				|| (quoteChar != 0)))
		{
			if (theInput[currentPos] == ESCAPE_CHAR)
			{
				currentPos++;
				if (currentPos < theInput.size())
				{
					/* Append quoted character.
					   TODO: Expansion of quoted characters should be 
					   C++-compatible. This should be implemented more 
					   elegantly as well. */
					if (theInput[currentPos] == 'n')
						currentToken.value.append(1, '\n');
					else
					if (theInput[currentPos] == 't')
						currentToken.value.append(1, '\t');
					else
					if (theInput[currentPos] == 'v')
						currentToken.value.append(1, '\v');
					else
					if (theInput[currentPos] == 'b')
						currentToken.value.append(1, '\b');
					else
					if (theInput[currentPos] == 'r')
						currentToken.value.append(1, '\r');
					else
					if (theInput[currentPos] == 'f')
						currentToken.value.append(1, '\f');
					else
					if (theInput[currentPos] == 'a')
						currentToken.value.append(1, '\a');
					else
						currentToken.value.append(
							uintToUtf8(theInput[currentPos]));
				}
				if (quoteChar == 0)
				{
					// Escaped character outside of quoted string.
					currentToken.typeID = TT_ESCAPED.typeID;
					currentPos++;
					return currentToken;
				}
			} else
			if (utf8IsOneOf(theInput[currentPos], quoteChars))
			{
				if (quoteChar == 0)
				{
					// Open quoted string.
					quoteChar = theInput[currentPos];
					currentQuoteChar = quoteChar;
				} else
				if (theInput[currentPos] == quoteChar)
				{
					// Close quoted string.
					quoteChar = 0;
					currentToken.typeID = TT_QUOTED.typeID;
					currentPos++;
					return currentToken;
				} else
					// Append mismatched quote.
					currentToken.value.append(
						uintToUtf8(theInput[currentPos]));
			} else
			{
				// Append anything else.
				currentToken.value.append(uintToUtf8(theInput[currentPos]));
			}
			currentPos++;
		}
		if (quoteChar != 0)
		{
			// Closing quote missing.
			currentQuoteChar = 0;
			return TOK_INVALID;
		}
	}
	// Extract other tokens.
	if (currentPos >= theInput.size())
		return TOK_NONE;
	currentTokenType = otherTypeMap->getTokenType(theInput[currentPos]);
	if (currentTokenType.typeID != TT_INVALID.typeID)
	{
		currentTokenPos = currentPos;
		currentToken.typeID = currentTokenType.typeID;
		if (currentTokenType.maxChars > 0)
			maxChars = currentTokenType.maxChars;
		else
			maxChars = theInput.size();
		tokenChars = 0;
		// Append all valid characters for the current token.
		while((currentPos < theInput.size()) 
			&& (otherTypeMap->getTokenType(theInput[currentPos]).typeID 
				== currentTokenType.typeID)
			&& (tokenChars < maxChars)
			&& (!extractQuoted 
				|| !utf8IsOneOf(theInput[currentPos], quoteChars))
			&& (!extractEscaped
				|| (theInput[currentPos] != ESCAPE_CHAR)))
		{
			currentToken.value.append(uintToUtf8(theInput[currentPos]));
			currentPos++;
			tokenChars++;
		}
	}
	return currentToken;
}

Utf8Token Utf8Tokenizer::getCurrentToken()
{
	return currentToken;
}

int Utf8Tokenizer::getCurrentTokenType()
{
	return currentToken.typeID;
}

unsigned int Utf8Tokenizer::getCurrentPos()
{
	return currentPos;
}

unsigned int Utf8Tokenizer::getCurrentTokenPos()
{
	return currentTokenPos;
}

unsigned int Utf8Tokenizer::getQuoteChar()
{
	return currentQuoteChar;
}

bool Utf8Tokenizer::isValid(const Utf8Token& checkToken)
{
	return ((checkToken.typeID != TT_INVALID.typeID)
		&& (checkToken.typeID != TT_NONE.typeID));
}

void Utf8Tokenizer::setExtractQuoted(bool newExtractQuoted)
{
	extractQuoted = newExtractQuoted;
}

bool Utf8Tokenizer::getExtractQuoted() const
{
	return extractQuoted;
}

void Utf8Tokenizer::setExtractEscaped(bool newExtractEscaped)
{
	extractEscaped = newExtractEscaped;
}

bool Utf8Tokenizer::getExtractEscaped() const
{
	return extractEscaped;
}

}

}

/** \file Utf8Tokenizer.cpp
 * \brief Tokenizer with UTF-8 support implementation.
 */
