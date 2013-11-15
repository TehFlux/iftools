/* ==========================================================================
 * IFTemplate - Ionflux Template Processor
 * Copyright © 2012 Jörn P. Meier
 * mail@ionflux.org
 * --------------------------------------------------------------------------
 * StringLTrim.cpp                 String manipulator: ltrim 
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

#include "iftemplate/StringLTrim.hpp"
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

StringLTrimClassInfo::StringLTrimClassInfo()
{
	name = "StringLTrim";
	desc = "String manipulator: ltrim";
}

StringLTrimClassInfo::~StringLTrimClassInfo()
{
}

// public member constants
const std::string StringLTrim::STRINGMANIP_NAME = "ltrim";

// run-time type information instance constants
const StringLTrimClassInfo StringLTrim::stringLTrimClassInfo;
const Ionflux::ObjectBase::IFClassInfo* StringLTrim::CLASS_INFO = &StringLTrim::stringLTrimClassInfo;

StringLTrim::StringLTrim()
{
	// NOTE: The following line is required for run-time type information.
	theClass = CLASS_INFO;
	// TODO: Nothing ATM. ;-)
}

StringLTrim::StringLTrim(const Ionflux::Template::StringManipulator::StringLTrim& other)
{
	// NOTE: The following line is required for run-time type information.
	theClass = CLASS_INFO;
	*this = other;
}

StringLTrim::~StringLTrim()
{
	// TODO: Nothing ATM. ;-)
}

std::string StringLTrim::process(const std::string& bytes, 
Ionflux::ObjectBase::StringVector* args)
{
	// TODO: Implementation.
	return Ionflux::ObjectBase::trim(bytes, true, false);
}

std::string StringLTrim::getManipName()
{
	// TODO: Implementation.
	return STRINGMANIP_NAME;
}

Ionflux::Template::StringManipulator::StringLTrim& 
StringLTrim::operator=(const 
Ionflux::Template::StringManipulator::StringLTrim& other)
{
if (this == &other)
    return *this;
	return *this;
}

Ionflux::Template::StringManipulator::StringLTrim* StringLTrim::copy() 
const
{
    StringLTrim* newStringLTrim = create();
    *newStringLTrim = *this;
    return newStringLTrim;
}

Ionflux::Template::StringManipulator::StringLTrim* 
StringLTrim::upcast(Ionflux::ObjectBase::IFObject* other)
{
    return dynamic_cast<StringLTrim*>(other);
}

Ionflux::Template::StringManipulator::StringLTrim* 
StringLTrim::create(Ionflux::ObjectBase::IFObject* parentObject)
{
    StringLTrim* newObject = new StringLTrim();
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

/** \file StringLTrim.cpp
 * \brief String manipulator: ltrim implementation.
 */
