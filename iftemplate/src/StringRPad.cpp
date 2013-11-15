/* ==========================================================================
 * IFTemplate - Ionflux Template Processor
 * Copyright © 2012 Jörn P. Meier
 * mail@ionflux.org
 * --------------------------------------------------------------------------
 * StringRPad.cpp                  String manipulator: rpad 
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

#include "iftemplate/StringRPad.hpp"
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

StringRPadClassInfo::StringRPadClassInfo()
{
	name = "StringRPad";
	desc = "String manipulator: rpad";
}

StringRPadClassInfo::~StringRPadClassInfo()
{
}

// public member constants
const std::string StringRPad::STRINGMANIP_NAME = "rpad";

// run-time type information instance constants
const StringRPadClassInfo StringRPad::stringRPadClassInfo;
const Ionflux::ObjectBase::IFClassInfo* StringRPad::CLASS_INFO = &StringRPad::stringRPadClassInfo;

StringRPad::StringRPad()
{
	// NOTE: The following line is required for run-time type information.
	theClass = CLASS_INFO;
	// TODO: Nothing ATM. ;-)
}

StringRPad::StringRPad(const Ionflux::Template::StringManipulator::StringRPad& other)
{
	// NOTE: The following line is required for run-time type information.
	theClass = CLASS_INFO;
	*this = other;
}

StringRPad::~StringRPad()
{
	// TODO: Nothing ATM. ;-)
}

std::string StringRPad::process(const std::string& bytes, 
Ionflux::ObjectBase::StringVector* args)
{
	if ((args == 0) || (args->size() < 2))
	    return bytes;
	char padChar = (*args)[0][0];
	int fieldWidth = strtol((*args)[1].c_str(), 0, 10);
	int padWidth = fieldWidth - bytes.size();
	string result;
	if (padWidth <= 0)
	    return bytes;
	result.append(bytes);
	result.append(padWidth, padChar);
	return result;
}

std::string StringRPad::getManipName()
{
	// TODO: Implementation.
	return STRINGMANIP_NAME;
}

Ionflux::Template::StringManipulator::StringRPad& 
StringRPad::operator=(const 
Ionflux::Template::StringManipulator::StringRPad& other)
{
if (this == &other)
    return *this;
	return *this;
}

Ionflux::Template::StringManipulator::StringRPad* StringRPad::copy() const
{
    StringRPad* newStringRPad = create();
    *newStringRPad = *this;
    return newStringRPad;
}

Ionflux::Template::StringManipulator::StringRPad* 
StringRPad::upcast(Ionflux::ObjectBase::IFObject* other)
{
    return dynamic_cast<StringRPad*>(other);
}

Ionflux::Template::StringManipulator::StringRPad* 
StringRPad::create(Ionflux::ObjectBase::IFObject* parentObject)
{
    StringRPad* newObject = new StringRPad();
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

/** \file StringRPad.cpp
 * \brief String manipulator: rpad implementation.
 */
