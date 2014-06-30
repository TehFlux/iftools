/* ==========================================================================
 * IFTemplate - Ionflux Template Processor
 * Copyright © 2012 Jörn P. Meier
 * mail@ionflux.org
 * --------------------------------------------------------------------------
 * StringLPad.cpp                  String manipulator: lpad 
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

#include "iftemplate/StringLPad.hpp"
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

StringLPadClassInfo::StringLPadClassInfo()
{
	name = "StringLPad";
	desc = "String manipulator: lpad";
}

StringLPadClassInfo::~StringLPadClassInfo()
{
}

// public member constants
const std::string StringLPad::STRINGMANIP_NAME = "lpad";

// run-time type information instance constants
const StringLPadClassInfo StringLPad::stringLPadClassInfo;
const Ionflux::ObjectBase::IFClassInfo* StringLPad::CLASS_INFO = &StringLPad::stringLPadClassInfo;

StringLPad::StringLPad()
{
	// NOTE: The following line is required for run-time type information.
	theClass = CLASS_INFO;
	// TODO: Nothing ATM. ;-)
}

StringLPad::StringLPad(const Ionflux::Template::StringManipulator::StringLPad& other)
{
	// NOTE: The following line is required for run-time type information.
	theClass = CLASS_INFO;
	*this = other;
}

StringLPad::~StringLPad()
{
	// TODO: Nothing ATM. ;-)
}

std::string StringLPad::process(const std::string& bytes, 
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
	result.append(padWidth, padChar);
	result.append(bytes);
	return result;
}

std::string StringLPad::getManipName()
{
	// TODO: Implementation.
	return STRINGMANIP_NAME;
}

Ionflux::Template::StringManipulator::StringLPad& 
StringLPad::operator=(const 
Ionflux::Template::StringManipulator::StringLPad& other)
{
if (this == &other)
    return *this;
	return *this;
}

Ionflux::Template::StringManipulator::StringLPad* StringLPad::copy() const
{
    StringLPad* newStringLPad = create();
    *newStringLPad = *this;
    return newStringLPad;
}

Ionflux::Template::StringManipulator::StringLPad* 
StringLPad::upcast(Ionflux::ObjectBase::IFObject* other)
{
    return dynamic_cast<StringLPad*>(other);
}

Ionflux::Template::StringManipulator::StringLPad* 
StringLPad::create(Ionflux::ObjectBase::IFObject* parentObject)
{
    StringLPad* newObject = new StringLPad();
    if (newObject == 0)
    {
        return 0;
    }
    if (parentObject != 0)
        parentObject->addLocalRef(newObject);
    return newObject;
}

unsigned int StringLPad::getMemSize() const
{
    return sizeof *this;
}

}

}

}

/** \file StringLPad.cpp
 * \brief String manipulator: lpad implementation.
 */
