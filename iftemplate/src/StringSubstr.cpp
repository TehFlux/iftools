/* ==========================================================================
 * IFTemplate - Ionflux Template Processor
 * Copyright © 2012 Jörn P. Meier
 * mail@ionflux.org
 * --------------------------------------------------------------------------
 * StringSubstr.cpp                String manipulator: substr 
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

#include "iftemplate/StringSubstr.hpp"
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

StringSubstrClassInfo::StringSubstrClassInfo()
{
	name = "StringSubstr";
	desc = "String manipulator: substr";
}

StringSubstrClassInfo::~StringSubstrClassInfo()
{
}

// public member constants
const std::string StringSubstr::STRINGMANIP_NAME = "substr";

// run-time type information instance constants
const StringSubstrClassInfo StringSubstr::stringSubstrClassInfo;
const Ionflux::ObjectBase::IFClassInfo* StringSubstr::CLASS_INFO = &StringSubstr::stringSubstrClassInfo;

StringSubstr::StringSubstr()
{
	// NOTE: The following line is required for run-time type information.
	theClass = CLASS_INFO;
	// TODO: Nothing ATM. ;-)
}

StringSubstr::StringSubstr(const Ionflux::Template::StringManipulator::StringSubstr& other)
{
	// NOTE: The following line is required for run-time type information.
	theClass = CLASS_INFO;
	*this = other;
}

StringSubstr::~StringSubstr()
{
	// TODO: Nothing ATM. ;-)
}

std::string StringSubstr::process(const std::string& bytes, 
Ionflux::ObjectBase::StringVector* args)
{
	if ((args == 0) || (args->size() < 2))
	    return bytes;
	int startIndex = strtol((*args)[0].c_str(), 0, 10);
	int numChars = strtol((*args)[1].c_str(), 0, 10);
	if (startIndex < 0)
	    startIndex = 0;
	if (static_cast<unsigned int>(startIndex + numChars) > bytes.size())
	    numChars = bytes.size() - startIndex;
	if (numChars <= 0)
	    return "";
	return bytes.substr(startIndex, numChars);
}

std::string StringSubstr::getManipName()
{
	// TODO: Implementation.
	return STRINGMANIP_NAME;
}

Ionflux::Template::StringManipulator::StringSubstr& 
StringSubstr::operator=(const 
Ionflux::Template::StringManipulator::StringSubstr& other)
{
if (this == &other)
    return *this;
	return *this;
}

Ionflux::Template::StringManipulator::StringSubstr* StringSubstr::copy() 
const
{
    StringSubstr* newStringSubstr = create();
    *newStringSubstr = *this;
    return newStringSubstr;
}

Ionflux::Template::StringManipulator::StringSubstr* 
StringSubstr::upcast(Ionflux::ObjectBase::IFObject* other)
{
    return dynamic_cast<StringSubstr*>(other);
}

Ionflux::Template::StringManipulator::StringSubstr* 
StringSubstr::create(Ionflux::ObjectBase::IFObject* parentObject)
{
    StringSubstr* newObject = new StringSubstr();
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

/** \file StringSubstr.cpp
 * \brief String manipulator: substr implementation.
 */
