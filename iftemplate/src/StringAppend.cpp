/* ==========================================================================
 * IFTemplate - Ionflux Template Processor
 * Copyright © 2012 Jörn P. Meier
 * mail@ionflux.org
 * --------------------------------------------------------------------------
 * StringAppend.cpp                String manipulator: append 
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

#include "iftemplate/StringAppend.hpp"
#include <iostream>
#include <iomanip>
#include <sstream>
#include <cstdlib>

using namespace std;

namespace Ionflux
{

namespace Template
{

namespace StringManipulator
{

StringAppendClassInfo::StringAppendClassInfo()
{
	name = "StringAppend";
	desc = "String manipulator: append";
}

StringAppendClassInfo::~StringAppendClassInfo()
{
}

// public member constants
const std::string StringAppend::STRINGMANIP_NAME = "append";

// run-time type information instance constants
const StringAppendClassInfo StringAppend::stringAppendClassInfo;
const Ionflux::ObjectBase::IFClassInfo* StringAppend::CLASS_INFO = &StringAppend::stringAppendClassInfo;

StringAppend::StringAppend()
{
	// NOTE: The following line is required for run-time type information.
	theClass = CLASS_INFO;
	// TODO: Nothing ATM. ;-)
}

StringAppend::StringAppend(const Ionflux::Template::StringManipulator::StringAppend& other)
{
	// NOTE: The following line is required for run-time type information.
	theClass = CLASS_INFO;
	*this = other;
}

StringAppend::~StringAppend()
{
	// TODO: Nothing ATM. ;-)
}

std::string StringAppend::process(const std::string& bytes, 
Ionflux::ObjectBase::StringVector* args)
{
	if ((args == 0) || (args->size() < 1))
	    return bytes;
	std::string result = bytes;
	result.append((*args)[0]);
	return result;
}

std::string StringAppend::getManipName()
{
	// TODO: Implementation.
	return STRINGMANIP_NAME;
}

Ionflux::Template::StringManipulator::StringAppend& 
StringAppend::operator=(const 
Ionflux::Template::StringManipulator::StringAppend& other)
{
	return *this;
}

Ionflux::Template::StringManipulator::StringAppend* StringAppend::copy() 
const
{
    StringAppend* newStringAppend = create();
    *newStringAppend = *this;
    return newStringAppend;
}

Ionflux::Template::StringManipulator::StringAppend* 
StringAppend::upcast(Ionflux::ObjectBase::IFObject* other)
{
    return dynamic_cast<StringAppend*>(other);
}

Ionflux::Template::StringManipulator::StringAppend* 
StringAppend::create(Ionflux::ObjectBase::IFObject* parentObject)
{
    StringAppend* newObject = new StringAppend();
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

/** \file StringAppend.cpp
 * \brief String manipulator: append implementation.
 */
