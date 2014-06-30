/* ==========================================================================
 * IFTemplate - Ionflux Template Processor
 * Copyright © 2012 Jörn P. Meier
 * mail@ionflux.org
 * --------------------------------------------------------------------------
 * StringSWrap.cpp                 String manipulator: swrap 
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

#include "iftemplate/StringSWrap.hpp"
#include <iostream>
#include <iomanip>
#include <sstream>
#include <cstdlib>
#include "iftemplate/utils.hpp"
#include "iftemplate/Tokenizer.hpp"

using namespace std;

namespace Ionflux
{

namespace Template
{

namespace StringManipulator
{

StringSWrapClassInfo::StringSWrapClassInfo()
{
	name = "StringSWrap";
	desc = "String manipulator: swrap";
}

StringSWrapClassInfo::~StringSWrapClassInfo()
{
}

// public member constants
const std::string StringSWrap::STRINGMANIP_NAME = "swrap";

// run-time type information instance constants
const StringSWrapClassInfo StringSWrap::stringSWrapClassInfo;
const Ionflux::ObjectBase::IFClassInfo* StringSWrap::CLASS_INFO = &StringSWrap::stringSWrapClassInfo;

StringSWrap::StringSWrap()
{
	// NOTE: The following line is required for run-time type information.
	theClass = CLASS_INFO;
	// TODO: Nothing ATM. ;-)
}

StringSWrap::StringSWrap(const Ionflux::Template::StringManipulator::StringSWrap& other)
{
	// NOTE: The following line is required for run-time type information.
	theClass = CLASS_INFO;
	*this = other;
}

StringSWrap::~StringSWrap()
{
	// TODO: Nothing ATM. ;-)
}

std::string StringSWrap::process(const std::string& bytes, 
Ionflux::ObjectBase::StringVector* args)
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
	tok.addTokenType(TT_WHITESPACE);
	tok.addTokenType(TT_LINETERM);
	tok.setTokenTypeAnything();
	tok.setInput(bytes);
	Token currentToken = tok.getNextToken();
	while (isNonEmpty(currentToken))
	{
	    currentWord = currentToken.value;
	    testLine = currentLine + currentWord;
	    if (hasType(currentToken, TT_LINETERM.typeID))
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
	            while (hasType(currentToken, TT_WHITESPACE.typeID))
	                currentToken = tok.getNextToken();
	            currentWord = currentToken.value;
	            if (!hasType(currentToken, TT_NONE.typeID))
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

std::string StringSWrap::getManipName()
{
	// TODO: Implementation.
	return STRINGMANIP_NAME;
}

Ionflux::Template::StringManipulator::StringSWrap& 
StringSWrap::operator=(const 
Ionflux::Template::StringManipulator::StringSWrap& other)
{
if (this == &other)
    return *this;
	return *this;
}

Ionflux::Template::StringManipulator::StringSWrap* StringSWrap::copy() 
const
{
    StringSWrap* newStringSWrap = create();
    *newStringSWrap = *this;
    return newStringSWrap;
}

Ionflux::Template::StringManipulator::StringSWrap* 
StringSWrap::upcast(Ionflux::ObjectBase::IFObject* other)
{
    return dynamic_cast<StringSWrap*>(other);
}

Ionflux::Template::StringManipulator::StringSWrap* 
StringSWrap::create(Ionflux::ObjectBase::IFObject* parentObject)
{
    StringSWrap* newObject = new StringSWrap();
    if (newObject == 0)
    {
        return 0;
    }
    if (parentObject != 0)
        parentObject->addLocalRef(newObject);
    return newObject;
}

unsigned int StringSWrap::getMemSize() const
{
    return sizeof *this;
}

}

}

}

/** \file StringSWrap.cpp
 * \brief String manipulator: swrap implementation.
 */
