/* ==========================================================================
 * IFTemplate - Ionflux Template Processor
 * Copyright © 2012 Jörn P. Meier
 * mail@ionflux.org
 * --------------------------------------------------------------------------
 * StringReplace.cpp               String manipulator: (implementation).
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

#include "iftemplate/StringReplace.hpp"
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

StringReplaceClassInfo::StringReplaceClassInfo()
{
	name = "StringReplace";
	desc = "String manipulator:";
}

StringReplaceClassInfo::~StringReplaceClassInfo()
{
}

// public member constants
const std::string StringReplace::STRINGMANIP_NAME = "replace";

// run-time type information instance constants
const StringReplaceClassInfo StringReplace::stringReplaceClassInfo;
const Ionflux::ObjectBase::IFClassInfo* StringReplace::CLASS_INFO = &StringReplace::stringReplaceClassInfo;

StringReplace::StringReplace()
{
	// NOTE: The following line is required for run-time type information.
	theClass = CLASS_INFO;
	// TODO: Nothing ATM. ;-)
}

StringReplace::StringReplace(const Ionflux::Template::StringManipulator::StringReplace& other)
{
	// NOTE: The following line is required for run-time type information.
	theClass = CLASS_INFO;
	*this = other;
}

StringReplace::~StringReplace()
{
	// TODO: Nothing ATM. ;-)
}

std::string StringReplace::process(const std::string& bytes, 
Ionflux::ObjectBase::StringVector* args)
{
	if ((args == 0) || (args->size() < 2))
	    return bytes;
	std::string result = bytes;
	std::string replaceBytes = (*args)[0];
	std::string replaceWith = (*args)[1];
	std::string::size_type currentPos;
	while ((currentPos = result.find(replaceBytes)) != std::string::npos)
	    result.replace(currentPos, replaceBytes.size(), replaceWith);
	return result;
}

std::string StringReplace::getManipName()
{
	// TODO: Implementation.
	return STRINGMANIP_NAME;
}

Ionflux::Template::StringManipulator::StringReplace& 
StringReplace::operator=(const 
Ionflux::Template::StringManipulator::StringReplace& other)
{
if (this == &other)
    return *this;
	return *this;
}

Ionflux::Template::StringManipulator::StringReplace* StringReplace::copy() 
const
{
    StringReplace* newStringReplace = create();
    *newStringReplace = *this;
    return newStringReplace;
}

Ionflux::Template::StringManipulator::StringReplace* 
StringReplace::upcast(Ionflux::ObjectBase::IFObject* other)
{
    return dynamic_cast<StringReplace*>(other);
}

Ionflux::Template::StringManipulator::StringReplace* 
StringReplace::create(Ionflux::ObjectBase::IFObject* parentObject)
{
    StringReplace* newObject = new StringReplace();
    if (newObject == 0)
    {
        return 0;
    }
    if (parentObject != 0)
        parentObject->addLocalRef(newObject);
    return newObject;
}

unsigned int StringReplace::getMemSize() const
{
    return sizeof *this;
}

}

}

}

/** \file StringReplace.cpp
 * \brief String manipulator: implementation.
 */
