/* ==========================================================================
 * IFTemplate - Ionflux Template Processor
 * Copyright © 2012 Jörn P. Meier
 * mail@ionflux.org
 * --------------------------------------------------------------------------
 * TokenTypeMap.cpp                Token type lookup map (implementation).
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

#include "iftemplate/TokenTypeMap.hpp"
#include <iostream>
#include <sstream>
#include <cstdlib>
#include "ifobject/utils.hpp"
#include "iftemplate/constants.hpp"

using namespace std;
using Ionflux::ObjectBase::isOneOf;

namespace Ionflux
{

namespace Template
{

TokenTypeMapClassInfo::TokenTypeMapClassInfo()
{
	name = "TokenTypeMap";
	desc = "Token type lookup map";
	baseClassInfo.push_back(Ionflux::ObjectBase::IFObject::CLASS_INFO);
}

TokenTypeMapClassInfo::~TokenTypeMapClassInfo()
{
}

// public member constants
const unsigned int TokenTypeMap::TYPE_MAP_SIZE = 256;

// run-time type information instance constants
const TokenTypeMapClassInfo TokenTypeMap::tokenTypeMapClassInfo;
const Ionflux::ObjectBase::IFClassInfo* TokenTypeMap::CLASS_INFO = &TokenTypeMap::tokenTypeMapClassInfo;

TokenTypeMap::TokenTypeMap()
: typeMap(0)
{
	// NOTE: The following line is required for run-time type information.
	theClass = CLASS_INFO;
	typeMap = new TokenType*[TYPE_MAP_SIZE];
	for (unsigned int i = 0; i < TYPE_MAP_SIZE; i++)
	    typeMap[i] = 0;
}

TokenTypeMap::TokenTypeMap(const Ionflux::Template::TokenTypeMap& other)
: typeMap(0)
{
	// NOTE: The following line is required for run-time type information.
	theClass = CLASS_INFO;
	*this = other;
}

TokenTypeMap::~TokenTypeMap()
{
	clear();
	if (typeMap != 0)
	    delete[] typeMap;
	typeMap = 0;
}

void TokenTypeMap::addTokenType(const Ionflux::Template::TokenType& 
newTokenType)
{
	TokenType *newType = new TokenType;
	*newType = newTokenType;
	types.push_back(newType);
	unsigned char currentChar;
	if (!newType->invert)
	{
	    // Add normal token to map.
	    for (unsigned int i = 0; i < newType->validChars.size(); i++)
	    {
	        currentChar = newType->validChars[i];
	        if (typeMap[currentChar] != 0)
	        {
	            // <---- DEBUG ----- //
	            cerr << "[TokenTypeMap::addTokenType] WARNING: "
	                "Possible conflict between token types "
	                << newType->typeID << " and " 
	                << typeMap[currentChar]->typeID << " (char: '" 
	                << currentChar << "')." << endl;
	            // ----- DEBUG ----> */
	        }
	        typeMap[currentChar] = newType;
	    }
	} else
	{
	    // Add inverted token to map.
	    for (unsigned int i = 0; i < TYPE_MAP_SIZE; i++)
	    {
	        currentChar = static_cast<unsigned char>(i);
	        if ((typeMap[i] == 0)
	            && !isOneOf(currentChar, newType->validChars))
	            typeMap[i] = newType;
	    }
	}
}

void TokenTypeMap::removeTokenType(const Ionflux::Template::TokenType& 
removeTokenType)
{
	TokenType *trashType = 0;
	unsigned int trashIndex = 0;
	while ((trashType == 0) && (trashIndex < types.size()))
	{
	    if ((types[trashIndex] != 0) 
	        && (types[trashIndex]->typeID == removeTokenType.typeID))
	    {
	        trashType = types[trashIndex];
	    } else
	        trashIndex++;
	}
	if (trashType == 0)
	    return;
	unsigned char currentChar;
	if (!(*trashType).invert)
	{
	    // Remove normal token type from map.
	    for (unsigned int i = 0; i < trashType->validChars.size(); i++)
	    {
	        currentChar = trashType->validChars[i];
	        typeMap[currentChar] = 0;
	    }
	} else
	{
	    // Remove inverted token type from map.
	    for (unsigned int i = 0; i < TYPE_MAP_SIZE; i++)
	        if (typeMap[i] == trashType)
	            typeMap[i] = 0;
	}
	delete types[trashIndex];
	types[trashIndex] = 0;
	types.erase(types.begin() + trashIndex);
}

Ionflux::Template::TokenType TokenTypeMap::getTokenType(unsigned char 
testChar) const
{
	if (typeMap[testChar] == 0)
	    return TT_INVALID;
	return *typeMap[testChar];
}

void TokenTypeMap::addTokenTypeAnything(const Ionflux::Template::TokenType&
newTokenType)
{
	TokenType *newType = new TokenType;
	*newType = newTokenType;
	/* Set 'invert' to 'true' to make sure the token type can be properly 
	   removed. */
	newType->invert = true;
	types.push_back(newType);
	for (unsigned int i = 0; i < TYPE_MAP_SIZE; i++)
	    if (typeMap[i] == 0)
	        typeMap[i] = newType;
}

void TokenTypeMap::clear()
{
	if (typeMap != 0)
	    for (unsigned int i = 0; i < TYPE_MAP_SIZE; i++)
	        typeMap[i] = 0;
	for (unsigned int i = 0; i < types.size(); i++)
	{
	    if (types[i] != 0)
	        delete types[i];
	    types[i] = 0;
	}
	types.clear();
}

unsigned int TokenTypeMap::getNumTokenTypes() const
{
	// TODO: Implementation.
	return types.size();
}

std::string TokenTypeMap::getString() const
{
	ostringstream state;
	state << "TokenTypeMap";
	return state.str();
}

Ionflux::Template::TokenTypeMap& TokenTypeMap::operator=(const 
Ionflux::Template::TokenTypeMap& other)
{
if (this == &other)
    return *this;
	return *this;
}

Ionflux::Template::TokenTypeMap* TokenTypeMap::copy() const
{
    TokenTypeMap* newTokenTypeMap = create();
    *newTokenTypeMap = *this;
    return newTokenTypeMap;
}

Ionflux::Template::TokenTypeMap* 
TokenTypeMap::upcast(Ionflux::ObjectBase::IFObject* other)
{
    return dynamic_cast<TokenTypeMap*>(other);
}

Ionflux::Template::TokenTypeMap* 
TokenTypeMap::create(Ionflux::ObjectBase::IFObject* parentObject)
{
    TokenTypeMap* newObject = new TokenTypeMap();
    if (newObject == 0)
    {
        return 0;
    }
    if (parentObject != 0)
        parentObject->addLocalRef(newObject);
    return newObject;
}

unsigned int TokenTypeMap::getMemSize() const
{
    return sizeof *this;
}

}

}

/** \file TokenTypeMap.cpp
 * \brief Token type lookup map implementation.
 */
