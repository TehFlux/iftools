/* ==========================================================================
 * IFTemplate - Ionflux Template Processor
 * Copyright © 2012 Jörn P. Meier
 * mail@ionflux.org
 * --------------------------------------------------------------------------
 * StringRTrim.cpp                 String manipulator: rtrim 
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

#include "iftemplate/StringRTrim.hpp"
#include <iostream>
#include <iomanip>
#include <sstream>
#include <cstdlib>
#include "ifobject/utils.hpp"

using namespace std;

namespace Ionflux
{

namespace Template
{

namespace StringManipulator
{

StringRTrimClassInfo::StringRTrimClassInfo()
{
	name = "StringRTrim";
	desc = "String manipulator: rtrim";
}

StringRTrimClassInfo::~StringRTrimClassInfo()
{
}

// public member constants
const std::string StringRTrim::STRINGMANIP_NAME = "rtrim";

// run-time type information instance constants
const StringRTrimClassInfo StringRTrim::stringRTrimClassInfo;
const Ionflux::ObjectBase::IFClassInfo* StringRTrim::CLASS_INFO = &StringRTrim::stringRTrimClassInfo;

StringRTrim::StringRTrim()
{
	// NOTE: The following line is required for run-time type information.
	theClass = CLASS_INFO;
	// TODO: Nothing ATM. ;-)
}

StringRTrim::StringRTrim(const Ionflux::Template::StringManipulator::StringRTrim& other)
{
	// NOTE: The following line is required for run-time type information.
	theClass = CLASS_INFO;
	*this = other;
}

StringRTrim::~StringRTrim()
{
	// TODO: Nothing ATM. ;-)
}

std::string StringRTrim::process(const std::string& bytes, 
Ionflux::ObjectBase::StringVector* args)
{
	// TODO: Implementation.
	return Ionflux::ObjectBase::trim(bytes, false, true);
}

std::string StringRTrim::getManipName()
{
	// TODO: Implementation.
	return STRINGMANIP_NAME;
}

Ionflux::Template::StringManipulator::StringRTrim& 
StringRTrim::operator=(const 
Ionflux::Template::StringManipulator::StringRTrim& other)
{
if (this == &other)
    return *this;
	return *this;
}

Ionflux::Template::StringManipulator::StringRTrim* StringRTrim::copy() 
const
{
    StringRTrim* newStringRTrim = create();
    *newStringRTrim = *this;
    return newStringRTrim;
}

Ionflux::Template::StringManipulator::StringRTrim* 
StringRTrim::upcast(Ionflux::ObjectBase::IFObject* other)
{
    return dynamic_cast<StringRTrim*>(other);
}

Ionflux::Template::StringManipulator::StringRTrim* 
StringRTrim::create(Ionflux::ObjectBase::IFObject* parentObject)
{
    StringRTrim* newObject = new StringRTrim();
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

/** \file StringRTrim.cpp
 * \brief String manipulator: rtrim implementation.
 */
