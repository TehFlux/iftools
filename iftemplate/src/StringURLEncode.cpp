/* ==========================================================================
 * IFTemplate - Ionflux Template Processor
 * Copyright © 2012 Jörn P. Meier
 * mail@ionflux.org
 * --------------------------------------------------------------------------
 * StringURLEncode.cpp             String manipulator: urlencode 
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

#include "iftemplate/StringURLEncode.hpp"
#include <iostream>
#include <iomanip>
#include <sstream>
#include <cstdlib>
#include "iftemplate/utils.hpp"

using namespace std;

namespace Ionflux
{

namespace Template
{

namespace StringManipulator
{

StringURLEncodeClassInfo::StringURLEncodeClassInfo()
{
	name = "StringURLEncode";
	desc = "String manipulator: urlencode";
}

StringURLEncodeClassInfo::~StringURLEncodeClassInfo()
{
}

// public member constants
const std::string StringURLEncode::STRINGMANIP_NAME = "urlencode";

// run-time type information instance constants
const StringURLEncodeClassInfo StringURLEncode::stringURLEncodeClassInfo;
const Ionflux::ObjectBase::IFClassInfo* StringURLEncode::CLASS_INFO = &StringURLEncode::stringURLEncodeClassInfo;

StringURLEncode::StringURLEncode()
{
	// NOTE: The following line is required for run-time type information.
	theClass = CLASS_INFO;
	// TODO: Nothing ATM. ;-)
}

StringURLEncode::StringURLEncode(const Ionflux::Template::StringManipulator::StringURLEncode& other)
{
	// NOTE: The following line is required for run-time type information.
	theClass = CLASS_INFO;
	*this = other;
}

StringURLEncode::~StringURLEncode()
{
	// TODO: Nothing ATM. ;-)
}

std::string StringURLEncode::process(const std::string& bytes, 
Ionflux::ObjectBase::StringVector* args)
{
	// TODO: Implementation.
	return urlEncode(bytes);
}

std::string StringURLEncode::getManipName()
{
	// TODO: Implementation.
	return STRINGMANIP_NAME;
}

Ionflux::Template::StringManipulator::StringURLEncode& 
StringURLEncode::operator=(const 
Ionflux::Template::StringManipulator::StringURLEncode& other)
{
if (this == &other)
    return *this;
	return *this;
}

Ionflux::Template::StringManipulator::StringURLEncode* 
StringURLEncode::copy() const
{
    StringURLEncode* newStringURLEncode = create();
    *newStringURLEncode = *this;
    return newStringURLEncode;
}

Ionflux::Template::StringManipulator::StringURLEncode* 
StringURLEncode::upcast(Ionflux::ObjectBase::IFObject* other)
{
    return dynamic_cast<StringURLEncode*>(other);
}

Ionflux::Template::StringManipulator::StringURLEncode* 
StringURLEncode::create(Ionflux::ObjectBase::IFObject* parentObject)
{
    StringURLEncode* newObject = new StringURLEncode();
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

}

/** \file StringURLEncode.cpp
 * \brief String manipulator: urlencode implementation.
 */
