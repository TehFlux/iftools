/* ==========================================================================
 * IFTemplate - Ionflux Template Processor
 * Copyright © 2012 Jörn P. Meier
 * mail@ionflux.org
 * --------------------------------------------------------------------------
 * StringLowercase.cpp             String manipulator: lowercase 
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

#include "iftemplate/StringLowercase.hpp"
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

StringLowercaseClassInfo::StringLowercaseClassInfo()
{
	name = "StringLowercase";
	desc = "String manipulator: lowercase";
}

StringLowercaseClassInfo::~StringLowercaseClassInfo()
{
}

// public member constants
const std::string StringLowercase::STRINGMANIP_NAME = "lowercase";

// run-time type information instance constants
const StringLowercaseClassInfo StringLowercase::stringLowercaseClassInfo;
const Ionflux::ObjectBase::IFClassInfo* StringLowercase::CLASS_INFO = &StringLowercase::stringLowercaseClassInfo;

StringLowercase::StringLowercase()
{
	// NOTE: The following line is required for run-time type information.
	theClass = CLASS_INFO;
	// TODO: Nothing ATM. ;-)
}

StringLowercase::StringLowercase(const Ionflux::Template::StringManipulator::StringLowercase& other)
{
	// NOTE: The following line is required for run-time type information.
	theClass = CLASS_INFO;
	*this = other;
}

StringLowercase::~StringLowercase()
{
	// TODO: Nothing ATM. ;-)
}

std::string StringLowercase::process(const std::string& bytes, 
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
	        currentChar = static_cast<char>(tolower(bytes[i]));
	    else
	        currentChar = bytes[i];
	    result << currentChar;
	}
	return result.str();
}

std::string StringLowercase::getManipName()
{
	// TODO: Implementation.
	return STRINGMANIP_NAME;
}

Ionflux::Template::StringManipulator::StringLowercase& 
StringLowercase::operator=(const 
Ionflux::Template::StringManipulator::StringLowercase& other)
{
	return *this;
}

Ionflux::Template::StringManipulator::StringLowercase* 
StringLowercase::copy() const
{
    StringLowercase* newStringLowercase = create();
    *newStringLowercase = *this;
    return newStringLowercase;
}

Ionflux::Template::StringManipulator::StringLowercase* 
StringLowercase::upcast(Ionflux::ObjectBase::IFObject* other)
{
    return dynamic_cast<StringLowercase*>(other);
}

Ionflux::Template::StringManipulator::StringLowercase* 
StringLowercase::create(Ionflux::ObjectBase::IFObject* parentObject)
{
    StringLowercase* newObject = new StringLowercase();
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

/** \file StringLowercase.cpp
 * \brief String manipulator: lowercase implementation.
 */
