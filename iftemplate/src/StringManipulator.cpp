/* ==========================================================================
 * IFTemplate - Ionflux Template Processor
 * Copyright © 2012 Jörn P. Meier
 * mail@ionflux.org
 * --------------------------------------------------------------------------
 * StringManipulator.cpp           String manipulator (implementation).
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

#include "iftemplate/StringManipulator.hpp"
#include <iostream>
#include <iomanip>
#include <sstream>

using namespace std;

namespace Ionflux
{

namespace Template
{

namespace StringManipulator
{

StringManipulatorClassInfo::StringManipulatorClassInfo()
{
	name = "StringManipulator";
	desc = "String manipulator";
	baseClassInfo.push_back(Ionflux::ObjectBase::IFObject::CLASS_INFO);
}

StringManipulatorClassInfo::~StringManipulatorClassInfo()
{
}

// run-time type information instance constants
const StringManipulatorClassInfo StringManipulator::stringManipulatorClassInfo;
const Ionflux::ObjectBase::IFClassInfo* StringManipulator::CLASS_INFO = &StringManipulator::stringManipulatorClassInfo;

StringManipulator::StringManipulator()
{
	// NOTE: The following line is required for run-time type information.
	theClass = CLASS_INFO;
	// TODO: Nothing ATM. ;-)
}

StringManipulator::StringManipulator(const Ionflux::Template::StringManipulator::StringManipulator& other)
{
	// NOTE: The following line is required for run-time type information.
	theClass = CLASS_INFO;
	*this = other;
}

StringManipulator::~StringManipulator()
{
	// TODO: Nothing ATM. ;-)
}

std::string StringManipulator::process(const std::string& bytes, 
Ionflux::ObjectBase::StringVector* args)
{
	// TODO: Implementation.
	return bytes;
}

std::string StringManipulator::operator()(const std::string& bytes, 
Ionflux::ObjectBase::StringVector* args)
{
	// TODO: Implementation.
	return process(bytes, args);
}

std::string StringManipulator::getManipName()
{
	// TODO: Implementation.
	return "<unnamed>";
}

Ionflux::Template::StringManipulator::StringManipulator& 
StringManipulator::operator=(const 
Ionflux::Template::StringManipulator::StringManipulator& other)
{
if (this == &other)
    return *this;
	return *this;
}

Ionflux::Template::StringManipulator::StringManipulator* 
StringManipulator::copy() const
{
    StringManipulator* newStringManipulator = create();
    *newStringManipulator = *this;
    return newStringManipulator;
}

Ionflux::Template::StringManipulator::StringManipulator* 
StringManipulator::upcast(Ionflux::ObjectBase::IFObject* other)
{
    return dynamic_cast<StringManipulator*>(other);
}

Ionflux::Template::StringManipulator::StringManipulator* 
StringManipulator::create(Ionflux::ObjectBase::IFObject* parentObject)
{
    StringManipulator* newObject = new StringManipulator();
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

/** \file StringManipulator.cpp
 * \brief String manipulator implementation.
 */
