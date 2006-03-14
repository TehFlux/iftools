/* ==========================================================================
 * Ionflux Tools
 * Copyright (c) 2004 Joern P. Meier
 * mail@ionflux.org
 * --------------------------------------------------------------------------
 * TokenTypeMap.cpp                Token type lookup map.
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

#include "ionflux/TokenTypeMap.hpp"

using namespace std;

namespace Ionflux
{

namespace Tools
{

const unsigned int TokenTypeMap::TYPE_MAP_SIZE = 256;

TokenTypeMap::TokenTypeMap()
: typeMap(0)
{
	typeMap = new TokenType*[TYPE_MAP_SIZE];
	for (unsigned int i = 0; i < TYPE_MAP_SIZE; i++)
		typeMap[i] = 0;
}

TokenTypeMap::~TokenTypeMap()
{
	clear();
	if (typeMap != 0)
		delete[] typeMap;
	typeMap = 0;
}

void TokenTypeMap::addTokenType(const TokenType& newTokenType)
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
				cerr << "[TokenTypeMap::addTokenType] WARNING: "
					"Possible conflict between token types "
					<< newType->typeID << " and " 
					<< typeMap[currentChar]->typeID << "(char: '" 
					<< currentChar << "')." << endl;
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

void TokenTypeMap::removeTokenType(const TokenType& removeTokenType)
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

TokenType TokenTypeMap::getTokenType(unsigned char testChar) const
{
	if (typeMap[testChar] == 0)
		return Tokenizer::TT_INVALID;
	return *typeMap[testChar];
}

void TokenTypeMap::addTokenTypeAnything(const TokenType& newTokenType)
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
	return types.size();
}

CharTypeMap::CharTypeMap()
{
	typeMap = new TokenType*[TYPE_MAP_SIZE];
	for (unsigned int i = 0; i < TYPE_MAP_SIZE; i++)
		typeMap[i] = 0;
	// Default character types.
	addTokenType(Tokenizer::TT_NUMBER);
	addTokenType(Tokenizer::TT_ALPHA);
	addTokenType(Tokenizer::TT_DEFAULT_SEP);
}

CharTypeMap::~CharTypeMap()
{
	// TODO: Nothing ATM. ;-)
}

}

}

/** \file TokenTypeMap.cpp
 * \brief Token type lookup map implementation.
 */
