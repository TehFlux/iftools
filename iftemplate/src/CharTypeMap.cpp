/* ==========================================================================
 * IFTemplate - Ionflux Template Processor
 * Copyright © 2012 Jörn P. Meier
 * mail@ionflux.org
 * --------------------------------------------------------------------------
 * CharTypeMap.cpp                 Character type lookup map 
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

#include "iftemplate/CharTypeMap.hpp"
#include <iostream>
#include <sstream>
#include <cstdlib>
#include "ifobject/utils.hpp"
#include "iftemplate/constants.hpp"

using namespace std;

namespace Ionflux
{

namespace Template
{

CharTypeMapClassInfo::CharTypeMapClassInfo()
{
	name = "CharTypeMap";
	desc = "Character type lookup map";
}

CharTypeMapClassInfo::~CharTypeMapClassInfo()
{
}

// run-time type information instance constants
const CharTypeMapClassInfo CharTypeMap::charTypeMapClassInfo;
const Ionflux::ObjectBase::IFClassInfo* CharTypeMap::CLASS_INFO = &CharTypeMap::charTypeMapClassInfo;

CharTypeMap::CharTypeMap()
{
	// NOTE: The following line is required for run-time type information.
	theClass = CLASS_INFO;
	addTokenType(TT_NUMBER);
	addTokenType(TT_ALPHA);
	addTokenType(TT_DEFAULT_SEP);
}

CharTypeMap::CharTypeMap(const Ionflux::Template::CharTypeMap& other)
{
	// NOTE: The following line is required for run-time type information.
	theClass = CLASS_INFO;
	*this = other;
}

CharTypeMap::~CharTypeMap()
{
	// TODO: Nothing ATM. ;-)
}

Ionflux::Template::CharTypeMap& CharTypeMap::operator=(const 
Ionflux::Template::CharTypeMap& other)
{
if (this == &other)
    return *this;
	return *this;
}

Ionflux::Template::CharTypeMap* CharTypeMap::copy() const
{
    CharTypeMap* newCharTypeMap = create();
    *newCharTypeMap = *this;
    return newCharTypeMap;
}

Ionflux::Template::CharTypeMap* 
CharTypeMap::upcast(Ionflux::ObjectBase::IFObject* other)
{
    return dynamic_cast<CharTypeMap*>(other);
}

Ionflux::Template::CharTypeMap* 
CharTypeMap::create(Ionflux::ObjectBase::IFObject* parentObject)
{
    CharTypeMap* newObject = new CharTypeMap();
    if (newObject == 0)
    {
        return 0;
    }
    if (parentObject != 0)
        parentObject->addLocalRef(newObject);
    return newObject;
}

}

}

/** \file CharTypeMap.cpp
 * \brief Character type lookup map implementation.
 */
