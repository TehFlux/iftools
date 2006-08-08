/* ==========================================================================
 * Ionflux Tools
 * Copyright (c) 2004 Joern P. Meier
 * mail@ionflux.org
 * --------------------------------------------------------------------------
 * Tokenizer.cpp                    Generic byte string tokenizer.
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

#include "ionflux/Tokenizer.hpp"

using namespace std;

namespace Ionflux
{

namespace Tools
{

const int TokenType::USERTYPE_ID = 100;

const TokenType Tokenizer::TT_INVALID = {-1, "", false, 0};
const TokenType Tokenizer::TT_NONE = {0, "", false, 0};
const TokenType Tokenizer::TT_QUOTED = {2, "", false, 0};
const TokenType Tokenizer::TT_ESCAPED = {3, "", false, 0};
const TokenType Tokenizer::TT_WHITESPACE = {4, " \t", false, 0};
const TokenType Tokenizer::TT_LINETERM = {5, "\n\r", false, 1};
const TokenType Tokenizer::TT_IDENTIFIER = {6, 
	"abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789_", 
	false, 0};
const TokenType Tokenizer::TT_NUMBER = {7, "0123456789", false, 0};
const TokenType Tokenizer::TT_ALPHA = {8, 
	"abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ", 
	false, 0};
const TokenType Tokenizer::TT_DEFAULT_SEP = {7, "_-.", false, 0};

const Token Tokenizer::TOK_INVALID = {Tokenizer::TT_INVALID.typeID, ""};
const Token Tokenizer::TOK_NONE = {Tokenizer::TT_NONE.typeID, ""};

const int Tokenizer::TT_ANYTHING_TYPE_ID = 1;

const std::string Tokenizer::QUOTE_CHARS = "\"'";
const char Tokenizer::ESCAPE_CHAR = '\\';

Tokenizer::Tokenizer()
: theInput(""), currentPos(0), currentTokenPos(0), extractQuoted(false), 
  extractEscaped(false), typeMap(0)
{
	typeMap = new TokenTypeMap;
	useDefaultTokenTypes();
}

Tokenizer::Tokenizer(const std::string& initInput)
: theInput(initInput), currentPos(0), currentTokenPos(0), extractQuoted(false), 
  extractEscaped(false), typeMap(0)
{
	typeMap = new TokenTypeMap;
	useDefaultTokenTypes();
}

Tokenizer::Tokenizer(const std::vector<TokenType>& initTokenTypes)
: theInput(""), currentPos(0), currentTokenPos(0), extractQuoted(false), 
  extractEscaped(false), typeMap(0)
{
	typeMap = new TokenTypeMap;
	setTokenTypes(initTokenTypes);
}

Tokenizer::Tokenizer(const std::vector<TokenType>& initTokenTypes, 
	const std::string& initInput)
: theInput(initInput), currentPos(0), currentTokenPos(0), extractQuoted(false), 
  extractEscaped(false), typeMap(0)
{
	typeMap = new TokenTypeMap;
	setTokenTypes(initTokenTypes);
}

Tokenizer::~Tokenizer()
{
	if (typeMap != 0)
		delete typeMap;
	typeMap = 0;
}

void Tokenizer::clearTokenTypes()
{
	typeMap->clear();
}

void Tokenizer::useDefaultTokenTypes()
{
	typeMap->clear();
	typeMap->addTokenType(TT_WHITESPACE);
	typeMap->addTokenType(TT_LINETERM);
	typeMap->addTokenType(TT_IDENTIFIER);
}

void Tokenizer::setTokenTypes(const std::vector<TokenType>& newTokenTypes)
{
	typeMap->clear();
	addTokenTypes(newTokenTypes);
}

void Tokenizer::addTokenType(const TokenType& newTokenType)
{
	typeMap->addTokenType(newTokenType);
}

void Tokenizer::addTokenTypes(const std::vector<TokenType>& newTokenTypes)
{
	for(std::vector<TokenType>::const_iterator i = newTokenTypes.begin();
		i != newTokenTypes.end(); i++)
			addTokenType(*i);
}

void Tokenizer::setInput(const std::string& newInput)
{
	theInput = newInput;
	reset();
}

Token Tokenizer::nextToken()
{
	return getNextToken();
}

Token Tokenizer::getNextToken(const TokenTypeMap &otherMap)
{
	if ((currentPos >= theInput.size()) || (otherMap.getNumTokenTypes() == 0))
		return TOK_NONE;
	unsigned int maxChars;
	unsigned int tokenChars;
	currentToken = TOK_INVALID;
	TokenType currentTokenType = TT_INVALID;
	char quoteChar = 0;
	currentQuoteChar = 0;
	if (extractEscaped && (theInput[currentPos] == ESCAPE_CHAR))
	{
		// Extract escaped characters.
		currentPos++;
		if (currentPos < theInput.size())
			// Append quoted character.
			currentToken.value.append(1, theInput[currentPos]);
		currentToken.typeID = TT_ESCAPED.typeID;
		currentPos++;
		return currentToken;
	}
	if (extractQuoted)
	{
		// Extract quoted strings.
		while((currentPos < theInput.size())
			&& ((theInput[currentPos] == ESCAPE_CHAR)
				|| isOneOf(theInput[currentPos], QUOTE_CHARS, false)
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
						currentToken.value.append(1, theInput[currentPos]);
				}
				if (quoteChar == 0)
				{
					// Escaped character outside of quoted string.
					currentToken.typeID = TT_ESCAPED.typeID;
					currentPos++;
					return currentToken;
				}
			} else
			if (isOneOf(theInput[currentPos], QUOTE_CHARS, false))
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
					currentToken.value.append(1, theInput[currentPos]);
			} else
			{
				// Append anything else.
				currentToken.value.append(1, theInput[currentPos]);
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
	currentTokenType = otherMap.getTokenType(theInput[currentPos]);
	if (currentTokenType.typeID != TT_INVALID.typeID)
	{
		currentTokenPos = currentPos;
		currentToken.typeID = currentTokenType.typeID;
		if (currentTokenType.maxChars > 0)
			maxChars = currentTokenType.maxChars;
		else
			maxChars = theInput.size();
		tokenChars = 0;
		while((currentPos < theInput.size()) 
			&& (otherMap.getTokenType(theInput[currentPos]).typeID 
				== currentTokenType.typeID)
			&& (tokenChars < maxChars)
			&& (!extractQuoted 
				|| !isOneOf(theInput[currentPos], QUOTE_CHARS, false))
			&& (!extractEscaped
				|| (theInput[currentPos] != ESCAPE_CHAR)))
		{
			currentToken.value.append(1, theInput[currentPos]);
			currentPos++;
			tokenChars++;
		}
	}
	return currentToken;
}

Token Tokenizer::getNextToken()
{
	return getNextToken(*typeMap);
}

Token Tokenizer::getCurrentToken()
{
	return currentToken;
}

int Tokenizer::getCurrentTokenType()
{
	return currentToken.typeID;
}

void Tokenizer::reset()
{
	currentPos = 0;
	currentToken = TOK_NONE;
}

void Tokenizer::setTokenTypeAnything()
{
	TT_ANYTHING.typeID = TT_ANYTHING_TYPE_ID;
	TT_ANYTHING.validChars = "";
	TT_ANYTHING.invert = true;
	TT_ANYTHING.maxChars = 0;
	typeMap->removeTokenType(TT_ANYTHING);
	typeMap->addTokenTypeAnything(TT_ANYTHING);
}

void Tokenizer::setExtractQuoted(bool newExtractQuoted)
{
	extractQuoted = newExtractQuoted;
}

void Tokenizer::setExtractEscaped(bool newExtractEscaped)
{
	extractEscaped = newExtractEscaped;
}

unsigned int Tokenizer::getCurrentPos()
{
	return currentPos;
}

unsigned int Tokenizer::getCurrentTokenPos()
{
	return currentTokenPos;
}

char Tokenizer::getQuoteChar()
{
	return currentQuoteChar;
}

bool Tokenizer::isOneOf(char c, const std::string& testChars, bool invert)
{
	if (invert)
		return !Ionflux::Tools::isOneOf(c, testChars);
	return Ionflux::Tools::isOneOf(c, testChars);
}

bool Tokenizer::isValid(Token& token)
{
	if ((token.typeID != TT_NONE.typeID)
		&& (token.typeID != TT_INVALID.typeID))
		return true;
	return false;
}

}

}

/** \file Tokenizer.cpp
 * \brief Generic byte string tokenizer implementation.
 */
