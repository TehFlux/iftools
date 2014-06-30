/* ==========================================================================
 * IFTemplate - Ionflux Template Processor
 * Copyright © 2012 Jörn P. Meier
 * mail@ionflux.org
 * --------------------------------------------------------------------------
 * Tokenizer.cpp                   Tokenizer (implementation).
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

#include "iftemplate/Tokenizer.hpp"
#include <iostream>
#include <sstream>
#include <cstdlib>
#include "ifobject/utils.hpp"
#include "iftemplate/constants.hpp"
#include "iftemplate/TokenTypeMap.hpp"
#include "iftemplate/IFTemplateError.hpp"

using namespace std;
using Ionflux::ObjectBase::isOneOf;

namespace Ionflux
{

namespace Template
{

TokenizerClassInfo::TokenizerClassInfo()
{
	name = "Tokenizer";
	desc = "Tokenizer";
	baseClassInfo.push_back(Ionflux::ObjectBase::IFObject::CLASS_INFO);
}

TokenizerClassInfo::~TokenizerClassInfo()
{
}

// run-time type information instance constants
const TokenizerClassInfo Tokenizer::tokenizerClassInfo;
const Ionflux::ObjectBase::IFClassInfo* Tokenizer::CLASS_INFO = &Tokenizer::tokenizerClassInfo;

Tokenizer::Tokenizer()
: theInput(""), currentToken(TOK_NONE), extractQuoted(false), extractEscaped(false), currentPos(0), currentTokenPos(0), currentQuoteChar(0), typeMap(0)
{
	// NOTE: The following line is required for run-time type information.
	theClass = CLASS_INFO;
	setTypeMap(TokenTypeMap::create());
	useDefaultTokenTypes();
}

Tokenizer::Tokenizer(const Ionflux::Template::Tokenizer& other)
: theInput(""), currentToken(TOK_NONE), extractQuoted(false), extractEscaped(false), currentPos(0), currentTokenPos(0), currentQuoteChar(0), typeMap(0)
{
	// NOTE: The following line is required for run-time type information.
	theClass = CLASS_INFO;
	*this = other;
}

Tokenizer::Tokenizer(const std::string& initInput)
: theInput(initInput), currentToken(TOK_NONE), extractQuoted(false), 
extractEscaped(false), currentPos(0), currentTokenPos(0), 
currentQuoteChar(0), typeMap(0)
{
	// NOTE: The following line is required for run-time type information.
	theClass = CLASS_INFO;
	setTypeMap(TokenTypeMap::create());
	useDefaultTokenTypes();
}

Tokenizer::Tokenizer(const Ionflux::Template::TokenTypeVector& 
initTokenTypes)
: theInput(""), currentToken(TOK_NONE), extractQuoted(false), 
extractEscaped(false), currentPos(0), currentTokenPos(0), 
currentQuoteChar(0), typeMap(0)
{
	// NOTE: The following line is required for run-time type information.
	theClass = CLASS_INFO;
	setTypeMap(TokenTypeMap::create());
	setTokenTypes(initTokenTypes);
}

Tokenizer::Tokenizer(const Ionflux::Template::TokenTypeVector& 
initTokenTypes, const std::string& initInput)
: theInput(initInput), currentToken(TOK_NONE), extractQuoted(false), 
extractEscaped(false), currentPos(0), currentTokenPos(0), 
currentQuoteChar(0), typeMap(0)
{
	// NOTE: The following line is required for run-time type information.
	theClass = CLASS_INFO;
	setTypeMap(TokenTypeMap::create());
	setTokenTypes(initTokenTypes);
}

Tokenizer::~Tokenizer()
{
	// TODO: Nothing ATM. ;-)
}

void Tokenizer::clearTokenTypes()
{
	if (typeMap == 0)
	    throw IFTemplateError("[Tokenizer::clearTokenTypes] "
	        "Token type map is null.");
	typeMap->clear();
}

void Tokenizer::useDefaultTokenTypes()
{
	if (typeMap == 0)
	    throw IFTemplateError("[Tokenizer::useDefaultTokenTypes] "
	        "Token type map is null.");
	typeMap->clear();
	typeMap->addTokenType(TT_WHITESPACE);
	typeMap->addTokenType(TT_LINETERM);
	typeMap->addTokenType(TT_IDENTIFIER);
}

void Tokenizer::setTokenTypes(const Ionflux::Template::TokenTypeVector& 
newTokenTypes)
{
	typeMap->clear();
	addTokenTypes(newTokenTypes);
}

void Tokenizer::addTokenType(const Ionflux::Template::TokenType& 
newTokenType)
{
	typeMap->addTokenType(newTokenType);
}

void Tokenizer::addTokenTypes(const Ionflux::Template::TokenTypeVector& 
newTokenTypes)
{
	for(TokenTypeVector::const_iterator i = newTokenTypes.begin();
	    i != newTokenTypes.end(); i++)
	        addTokenType(*i);
}

void Tokenizer::setInput(const std::string& newInput)
{
	theInput = newInput;
	reset();
}

Ionflux::Template::Token Tokenizer::getNextToken(const 
Ionflux::Template::TokenTypeMap& otherMap)
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

Ionflux::Template::Token Tokenizer::getNextToken()
{
	// TODO: Implementation.
	return getNextToken(*typeMap);
}

Ionflux::Template::Token Tokenizer::getCurrentToken()
{
	// TODO: Implementation.
	return currentToken;
}

Ionflux::Template::TokenTypeID Tokenizer::getCurrentTokenType()
{
	// TODO: Implementation.
	return currentToken.typeID;
}

void Tokenizer::reset()
{
	currentPos = 0;
	currentTokenPos = 0;
	currentQuoteChar = 0;
	currentToken = TOK_NONE;
}

void Tokenizer::setTokenTypeAnything()
{
	TT_ANYTHING.typeID = TT_ID_ANYTHING;
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
	// TODO: Implementation.
	return currentPos;
}

unsigned int Tokenizer::getCurrentTokenPos()
{
	// TODO: Implementation.
	return currentTokenPos;
}

char Tokenizer::getQuoteChar()
{
	// TODO: Implementation.
	return currentQuoteChar;
}

std::string Tokenizer::getString() const
{
	ostringstream state;
	state << "Tokenizer";
	return state.str();
}

void Tokenizer::setTypeMap(Ionflux::Template::TokenTypeMap* newTypeMap)
{
	if (typeMap == newTypeMap)
		return;
    if (newTypeMap != 0)
        addLocalRef(newTypeMap);
	if (typeMap != 0)
		removeLocalRef(typeMap);
	typeMap = newTypeMap;
}

Ionflux::Template::TokenTypeMap* Tokenizer::getTypeMap() const
{
    return typeMap;
}

Ionflux::Template::Tokenizer& Tokenizer::operator=(const 
Ionflux::Template::Tokenizer& other)
{
    if (this == &other)
        return *this;
    reset();
    setTypeMap(other.typeMap);
    setInput(other.theInput);
    setExtractQuoted(other.extractQuoted);
    setExtractEscaped(other.extractEscaped);
	return *this;
}

Ionflux::Template::Tokenizer* Tokenizer::copy() const
{
    Tokenizer* newTokenizer = create();
    *newTokenizer = *this;
    return newTokenizer;
}

Ionflux::Template::Tokenizer* 
Tokenizer::upcast(Ionflux::ObjectBase::IFObject* other)
{
    return dynamic_cast<Tokenizer*>(other);
}

Ionflux::Template::Tokenizer* 
Tokenizer::create(Ionflux::ObjectBase::IFObject* parentObject)
{
    Tokenizer* newObject = new Tokenizer();
    if (newObject == 0)
    {
        return 0;
    }
    if (parentObject != 0)
        parentObject->addLocalRef(newObject);
    return newObject;
}

unsigned int Tokenizer::getMemSize() const
{
    return sizeof *this;
}

}

}

/** \file Tokenizer.cpp
 * \brief Tokenizer implementation.
 */
