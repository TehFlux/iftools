/* ==========================================================================
 * IFTemplate - Ionflux Template Processor
 * Copyright © 2012 Jörn P. Meier
 * mail@ionflux.org
 * --------------------------------------------------------------------------
 * StringTruncate.cpp              String manipulator: truncate 
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

#include "iftemplate/StringTruncate.hpp"
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

StringTruncateClassInfo::StringTruncateClassInfo()
{
	name = "StringTruncate";
	desc = "String manipulator: truncate";
}

StringTruncateClassInfo::~StringTruncateClassInfo()
{
}

// public member constants
const std::string StringTruncate::STRINGMANIP_NAME = "truncate";

// run-time type information instance constants
const StringTruncateClassInfo StringTruncate::stringTruncateClassInfo;
const Ionflux::ObjectBase::IFClassInfo* StringTruncate::CLASS_INFO = &StringTruncate::stringTruncateClassInfo;

StringTruncate::StringTruncate()
{
	// NOTE: The following line is required for run-time type information.
	theClass = CLASS_INFO;
	// TODO: Nothing ATM. ;-)
}

StringTruncate::StringTruncate(const Ionflux::Template::StringManipulator::StringTruncate& other)
{
	// NOTE: The following line is required for run-time type information.
	theClass = CLASS_INFO;
	*this = other;
}

StringTruncate::~StringTruncate()
{
	// TODO: Nothing ATM. ;-)
}

std::string StringTruncate::process(const std::string& bytes, 
Ionflux::ObjectBase::StringVector* args)
{
	if ((args == 0) || (args->size() < 1))
	    return bytes;
	unsigned int length = strtol((*args)[0].c_str(), 0, 10);
	if (bytes.size() <= length)
	    return bytes;
	std::string dots = "";
	if (args->size() >= 2)
	    dots = (*args)[1];
	if (length > 0)
	    return bytes.substr(0, length - dots.size()) + dots;
	return "";
}

std::string StringTruncate::getManipName()
{
	// TODO: Implementation.
	return STRINGMANIP_NAME;
}

Ionflux::Template::StringManipulator::StringTruncate& 
StringTruncate::operator=(const 
Ionflux::Template::StringManipulator::StringTruncate& other)
{
	return *this;
}

Ionflux::Template::StringManipulator::StringTruncate* 
StringTruncate::copy() const
{
    StringTruncate* newStringTruncate = create();
    *newStringTruncate = *this;
    return newStringTruncate;
}

Ionflux::Template::StringManipulator::StringTruncate* 
StringTruncate::upcast(Ionflux::ObjectBase::IFObject* other)
{
    return dynamic_cast<StringTruncate*>(other);
}

Ionflux::Template::StringManipulator::StringTruncate* 
StringTruncate::create(Ionflux::ObjectBase::IFObject* parentObject)
{
    StringTruncate* newObject = new StringTruncate();
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

/** \file StringTruncate.cpp
 * \brief String manipulator: truncate implementation.
 */
