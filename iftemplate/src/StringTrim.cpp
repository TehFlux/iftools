/* ==========================================================================
 * IFTemplate - Ionflux Template Processor
 * Copyright © 2012 Jörn P. Meier
 * mail@ionflux.org
 * --------------------------------------------------------------------------
 * StringTrim.cpp                  String manipulator: trim 
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

#include "iftemplate/StringTrim.hpp"
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

StringTrimClassInfo::StringTrimClassInfo()
{
	name = "StringTrim";
	desc = "String manipulator: trim";
}

StringTrimClassInfo::~StringTrimClassInfo()
{
}

// public member constants
const std::string StringTrim::STRINGMANIP_NAME = "trim";

// run-time type information instance constants
const StringTrimClassInfo StringTrim::stringTrimClassInfo;
const Ionflux::ObjectBase::IFClassInfo* StringTrim::CLASS_INFO = &StringTrim::stringTrimClassInfo;

StringTrim::StringTrim()
{
	// NOTE: The following line is required for run-time type information.
	theClass = CLASS_INFO;
	// TODO: Nothing ATM. ;-)
}

StringTrim::StringTrim(const Ionflux::Template::StringManipulator::StringTrim& other)
{
	// NOTE: The following line is required for run-time type information.
	theClass = CLASS_INFO;
	*this = other;
}

StringTrim::~StringTrim()
{
	// TODO: Nothing ATM. ;-)
}

std::string StringTrim::process(const std::string& bytes, 
Ionflux::ObjectBase::StringVector* args)
{
	// TODO: Implementation.
	return Ionflux::ObjectBase::trim(bytes, true, true);
}

std::string StringTrim::getManipName()
{
	// TODO: Implementation.
	return STRINGMANIP_NAME;
}

Ionflux::Template::StringManipulator::StringTrim& 
StringTrim::operator=(const 
Ionflux::Template::StringManipulator::StringTrim& other)
{
if (this == &other)
    return *this;
	return *this;
}

Ionflux::Template::StringManipulator::StringTrim* StringTrim::copy() const
{
    StringTrim* newStringTrim = create();
    *newStringTrim = *this;
    return newStringTrim;
}

Ionflux::Template::StringManipulator::StringTrim* 
StringTrim::upcast(Ionflux::ObjectBase::IFObject* other)
{
    return dynamic_cast<StringTrim*>(other);
}

Ionflux::Template::StringManipulator::StringTrim* 
StringTrim::create(Ionflux::ObjectBase::IFObject* parentObject)
{
    StringTrim* newObject = new StringTrim();
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

/** \file StringTrim.cpp
 * \brief String manipulator: trim implementation.
 */
