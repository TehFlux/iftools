/* ==========================================================================
 * IFTemplate - Ionflux Template Processor
 * Copyright © 2012 Jörn P. Meier
 * mail@ionflux.org
 * --------------------------------------------------------------------------
 * StringUppercase.cpp             String manipulator: uppercase 
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

#include "iftemplate/StringUppercase.hpp"
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

StringUppercaseClassInfo::StringUppercaseClassInfo()
{
	name = "StringUppercase";
	desc = "String manipulator: uppercase";
}

StringUppercaseClassInfo::~StringUppercaseClassInfo()
{
}

// public member constants
const std::string StringUppercase::STRINGMANIP_NAME = "uppercase";

// run-time type information instance constants
const StringUppercaseClassInfo StringUppercase::stringUppercaseClassInfo;
const Ionflux::ObjectBase::IFClassInfo* StringUppercase::CLASS_INFO = &StringUppercase::stringUppercaseClassInfo;

StringUppercase::StringUppercase()
{
	// NOTE: The following line is required for run-time type information.
	theClass = CLASS_INFO;
	// TODO: Nothing ATM. ;-)
}

StringUppercase::StringUppercase(const Ionflux::Template::StringManipulator::StringUppercase& other)
{
	// NOTE: The following line is required for run-time type information.
	theClass = CLASS_INFO;
	*this = other;
}

StringUppercase::~StringUppercase()
{
	// TODO: Nothing ATM. ;-)
}

std::string StringUppercase::process(const std::string& bytes, 
Ionflux::ObjectBase::StringVector* args)
{
	std::ostringstream result;
	unsigned int numChars;
	if ((args != 0) && (args->size() >= 1))
	    numChars = strtol((*args)[0].c_str(), 0, 10);
	else
	    numChars = bytes.size();
	char currentChar;
	for (unsigned int i = 0; i < bytes.size(); i++)
	{
	    if (i < numChars)
	        currentChar = static_cast<char>(toupper(bytes[i]));
	    else
	        currentChar = bytes[i];
	    result << currentChar;
	}
	return result.str();
}

std::string StringUppercase::getManipName()
{
	// TODO: Implementation.
	return STRINGMANIP_NAME;
}

Ionflux::Template::StringManipulator::StringUppercase& 
StringUppercase::operator=(const 
Ionflux::Template::StringManipulator::StringUppercase& other)
{
if (this == &other)
    return *this;
	return *this;
}

Ionflux::Template::StringManipulator::StringUppercase* 
StringUppercase::copy() const
{
    StringUppercase* newStringUppercase = create();
    *newStringUppercase = *this;
    return newStringUppercase;
}

Ionflux::Template::StringManipulator::StringUppercase* 
StringUppercase::upcast(Ionflux::ObjectBase::IFObject* other)
{
    return dynamic_cast<StringUppercase*>(other);
}

Ionflux::Template::StringManipulator::StringUppercase* 
StringUppercase::create(Ionflux::ObjectBase::IFObject* parentObject)
{
    StringUppercase* newObject = new StringUppercase();
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

/** \file StringUppercase.cpp
 * \brief String manipulator: uppercase implementation.
 */
