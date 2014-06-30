/* ==========================================================================
 * IFTemplate - Ionflux Template Processor
 * Copyright © 2012 Jörn P. Meier
 * mail@ionflux.org
 * --------------------------------------------------------------------------
 * StringErase.cpp                 String manipulator: erase 
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

#include "iftemplate/StringErase.hpp"
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

StringEraseClassInfo::StringEraseClassInfo()
{
	name = "StringErase";
	desc = "String manipulator: erase";
}

StringEraseClassInfo::~StringEraseClassInfo()
{
}

// public member constants
const std::string StringErase::STRINGMANIP_NAME = "erase";

// run-time type information instance constants
const StringEraseClassInfo StringErase::stringEraseClassInfo;
const Ionflux::ObjectBase::IFClassInfo* StringErase::CLASS_INFO = &StringErase::stringEraseClassInfo;

StringErase::StringErase()
{
	// NOTE: The following line is required for run-time type information.
	theClass = CLASS_INFO;
	// TODO: Nothing ATM. ;-)
}

StringErase::StringErase(const Ionflux::Template::StringManipulator::StringErase& other)
{
	// NOTE: The following line is required for run-time type information.
	theClass = CLASS_INFO;
	*this = other;
}

StringErase::~StringErase()
{
	// TODO: Nothing ATM. ;-)
}

std::string StringErase::process(const std::string& bytes, 
Ionflux::ObjectBase::StringVector* args)
{
	if ((args == 0) || (args->size() == 0))
	    return bytes;
	std::string result = bytes;
	std::string eraseBytes = (*args)[0];
	std::string::size_type currentPos;
	while ((currentPos = result.find(eraseBytes)) != std::string::npos)
	    result.erase(currentPos, eraseBytes.size());
	return result;
}

std::string StringErase::getManipName()
{
	// TODO: Implementation.
	return STRINGMANIP_NAME;
}

Ionflux::Template::StringManipulator::StringErase& 
StringErase::operator=(const 
Ionflux::Template::StringManipulator::StringErase& other)
{
if (this == &other)
    return *this;
	return *this;
}

Ionflux::Template::StringManipulator::StringErase* StringErase::copy() 
const
{
    StringErase* newStringErase = create();
    *newStringErase = *this;
    return newStringErase;
}

Ionflux::Template::StringManipulator::StringErase* 
StringErase::upcast(Ionflux::ObjectBase::IFObject* other)
{
    return dynamic_cast<StringErase*>(other);
}

Ionflux::Template::StringManipulator::StringErase* 
StringErase::create(Ionflux::ObjectBase::IFObject* parentObject)
{
    StringErase* newObject = new StringErase();
    if (newObject == 0)
    {
        return 0;
    }
    if (parentObject != 0)
        parentObject->addLocalRef(newObject);
    return newObject;
}

unsigned int StringErase::getMemSize() const
{
    return sizeof *this;
}

}

}

}

/** \file StringErase.cpp
 * \brief String manipulator: erase implementation.
 */
