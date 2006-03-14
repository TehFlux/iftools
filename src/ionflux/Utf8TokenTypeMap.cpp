/* ==========================================================================
 * Ionflux Tools
 * Copyright (c) 2005 Joern P. Meier
 * mail@ionflux.org
 * --------------------------------------------------------------------------
 * Utf8TokenTypeMap.cpp            Token type map with UTF-8 support.
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

#include "ionflux/Utf8TokenTypeMap.hpp"
#include "ionflux/tools.hpp"

using namespace std;
using namespace Ionflux::Tools;

namespace Ionflux
{

namespace Tools
{

const int Utf8TokenType::USERTYPE_ID = 100;
const int Utf8TokenType::INVALID_ID = -1;
const int Utf8TokenType::EMPTY_ID = 0;

Utf8TokenTypeMapClassInfo::Utf8TokenTypeMapClassInfo()
{
	name = "Utf8TokenTypeMap";
	desc = "Token type map with UTF-8 support";
}

const Utf8TokenTypeMapClassInfo Utf8TokenTypeMap::utf8TokenTypeMapClassInfo;
const ClassInfo* Utf8TokenTypeMap::CLASS_INFO = 
	&Utf8TokenTypeMap::utf8TokenTypeMapClassInfo;

Utf8TokenTypeMap::Utf8TokenTypeMap()
: defaultTokenType(0)
{
	// NOTE: The following line is required for class information.
	theClasses.push_back(CLASS_INFO);
	// TODO: Nothing ATM. ;-)
}

Utf8TokenTypeMap::~Utf8TokenTypeMap()
{
	clear();
}

void Utf8TokenTypeMap::clear()
{
	vector<Utf8TokenType*>::iterator i;
	for (i = tokenTypes.begin(); i != tokenTypes.end(); i++)
		if (*i != 0)
			delete *i;
	tokenTypes.clear();
	typeMap.clear();
	if (defaultTokenType != 0)
		delete defaultTokenType;
	defaultTokenType = 0;
}

unsigned int Utf8TokenTypeMap::getNumTokenTypes()
{
	return tokenTypes.size();
}

void Utf8TokenTypeMap::addTokenType(const Utf8TokenType& newTokenType)
{
	if (!isValid(newTokenType))
	{
		cerr << "[Utf8TokenTypeMap::addTokenType] ERROR: "
			"Attempt to add invalid token type." << endl;
		return;
	}
	// Check whether a token type with the same ID has already been added.
	bool found = false;
	unsigned int i = 0;
	Utf8TokenType* currentTokenType = 0;
	while (!found
		&& (i < tokenTypes.size()))
	{
		currentTokenType = tokenTypes[i];
		if ((currentTokenType != 0)
			&& (currentTokenType->typeID == newTokenType.typeID))
			found = true;
		else
			i++;
	}
	if (found)
		removeTokenType(newTokenType);
	vector<unsigned int> uniChars;
	if (!utf8ToUInt(newTokenType.validChars, uniChars))
	{
		cerr << "[Utf8TokenTypeMap::addTokenType] ERROR: "
			"Decoding of UTF-8 character string failed." << endl;
		return;
	}
	Utf8TokenType* theTokenType = new Utf8TokenType();
	*theTokenType = newTokenType;
	tokenTypes.push_back(theTokenType);
	// Add new token type to map.
	for (vector<unsigned int>::iterator k = uniChars.begin(); 
		k != uniChars.end(); k++)
	{
		ImplTokenTypeMap::iterator j = typeMap.find(*k);
		if ((j != typeMap.end())
			&& ((*j).second != 0))
		{
			cerr << "[Utf8TokenTypeMap::addTokenType] WARNING: "
				"Conflict between token types " << (*j).second->typeID
				<< " and " << theTokenType->typeID << " at character '"
				<< uintToUtf8(*k) << "' (" << *k << ")." << endl;
		}
		typeMap[*k] = theTokenType;
		/* ----- DEBUG ----- //
		cerr << "[Utf8TokenTypeMap::addTokenType] DEBUG: "
			"Character '" << uintToUtf8(*k) << "' (" << *k << ") "
			"is now mapped to token type "<< theTokenType->typeID << "."
			<< endl;
		// ----- DEBUG ----- */
	}
}

void Utf8TokenTypeMap::removeTokenType(const Utf8TokenType& 
removeTokenType)
{
	// Remove entries with specified type from the map.
	vector<unsigned int> clearChars;
	for (ImplTokenTypeMap::iterator j = typeMap.begin(); 
		j != typeMap.end(); j++)
	{
		if (((*j).second != 0)
			&& ((*j).second->typeID == removeTokenType.typeID))
		{
			clearChars.push_back((*j).first);
			/* ----- DEBUG ----- //
			cerr << "[Utf8TokenTypeMap::removeTokenType] DEBUG: "
				"Character '" << uintToUtf8((*j).first) << "' (" 
				<< (*j).first << ") is mapped to token type "
				<< removeTokenType.typeID 
				<< " and will be removed from the map." << endl;
			// ----- DEBUG ----- */
		}
	}
	for (vector<unsigned int>::iterator k = clearChars.begin(); 
		k != clearChars.end(); k++)
	{
		ImplTokenTypeMap::iterator j = typeMap.find(*k);
		if (j != typeMap.end())
		{
			typeMap.erase(j);
			/* ----- DEBUG ----- //
			cerr << "[Utf8TokenTypeMap::removeTokenType] DEBUG: "
				"Character '" << uintToUtf8((*j).first) << "' (" 
				<< (*j).first << ") has been removed from the map." << endl;
			// ----- DEBUG ----- */
		}
	}
	// Remove token type from token type vector.
	bool found = false;
	unsigned int i = 0;
	Utf8TokenType* currentTokenType = 0;
	while (!found
		&& (i < tokenTypes.size()))
	{
		currentTokenType = tokenTypes[i];
		if ((currentTokenType != 0)
			&& (currentTokenType->typeID == removeTokenType.typeID))
			found = true;
		else
			i++;
	}
	if (found)
	{
		/* ----- DEBUG ----- //
		cerr << "[Utf8TokenTypeMap::removeTokenType] DEBUG: "
			"Removing token type " << currentTokenType->typeID << "." 
			<< endl;
		// ----- DEBUG ----- */
		delete currentTokenType;
		tokenTypes.erase(tokenTypes.begin() + i);
	}
}

void Utf8TokenTypeMap::setDefaultTokenType(const Utf8TokenType& 
newDefaultTokenType)
{
	if (!isValid(newDefaultTokenType))
	{
		cerr << "[Utf8TokenTypeMap::setDefaultTokenType] ERROR: "
			"Attempt to set invalid default token type." << endl;
		return;
	}
	if (defaultTokenType != 0)
		delete defaultTokenType;
	defaultTokenType = new Utf8TokenType();
	*defaultTokenType = newDefaultTokenType;
}

Utf8TokenType Utf8TokenTypeMap::getTokenType(unsigned int testChar)
{
	ImplTokenTypeMap::iterator j = typeMap.find(testChar);
	if ((j != typeMap.end())
		&& ((*j).second != 0))
		return *(*j).second;
	if (defaultTokenType != 0)
		return *defaultTokenType;
	Utf8TokenType result;
	result.typeID = Utf8TokenType::INVALID_ID;
	result.maxChars = 0;
	return result;
}

bool Utf8TokenTypeMap::isValid(const Utf8TokenType& checkTokenType)
{
	return ((checkTokenType.typeID != Utf8TokenType::INVALID_ID)
		&& (checkTokenType.typeID != Utf8TokenType::EMPTY_ID));
}

}

}

/** \file Utf8TokenTypeMap.cpp
 * \brief Token type map with UTF-8 support implementation.
 */
