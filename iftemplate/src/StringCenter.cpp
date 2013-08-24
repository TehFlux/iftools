/* ==========================================================================
 * IFTemplate - Ionflux Template Processor
 * Copyright © 2012 Jörn P. Meier
 * mail@ionflux.org
 * --------------------------------------------------------------------------
 * StringCenter.cpp                String manipulator: center 
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

#include "iftemplate/StringCenter.hpp"
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

StringCenterClassInfo::StringCenterClassInfo()
{
	name = "StringCenter";
	desc = "String manipulator: center";
}

StringCenterClassInfo::~StringCenterClassInfo()
{
}

// public member constants
const std::string StringCenter::STRINGMANIP_NAME = "center";

// run-time type information instance constants
const StringCenterClassInfo StringCenter::stringCenterClassInfo;
const Ionflux::ObjectBase::IFClassInfo* StringCenter::CLASS_INFO = &StringCenter::stringCenterClassInfo;

StringCenter::StringCenter()
{
	// NOTE: The following line is required for run-time type information.
	theClass = CLASS_INFO;
	// TODO: Nothing ATM. ;-)
}

StringCenter::StringCenter(const Ionflux::Template::StringManipulator::StringCenter& other)
{
	// NOTE: The following line is required for run-time type information.
	theClass = CLASS_INFO;
	*this = other;
}

StringCenter::~StringCenter()
{
	// TODO: Nothing ATM. ;-)
}

std::string StringCenter::process(const std::string& bytes, 
Ionflux::ObjectBase::StringVector* args)
{
	if ((args == 0) || (args->size() < 1))
	    return bytes;
	unsigned int width = strtol((*args)[0].c_str(), 0, 10);
	std::string result = "";
	std::string buffer = "";
	std::string padding = "";
	std::string centerpadding = " ";
	if (args->size() >= 2)
	    padding = (*args)[1];
	if (args->size() >= 3)
	    centerpadding = (*args)[2];
	buffer = padding + bytes + padding;
	if (result.size() < width)
	{
	    unsigned int padwidth = width - result.size();
	    unsigned int padleft = padwidth / 2;
	    unsigned int padright = padwidth - padleft;
	    char padchar;
	    if  (centerpadding.size() > 0)
	        padchar = centerpadding[0];
	    else
	        padchar = ' ';
	    result.append(padleft, padchar);
	    result.append(buffer);
	    result.append(padright, padchar);
	}
	return result;
}

std::string StringCenter::getManipName()
{
	// TODO: Implementation.
	return STRINGMANIP_NAME;
}

Ionflux::Template::StringManipulator::StringCenter& 
StringCenter::operator=(const 
Ionflux::Template::StringManipulator::StringCenter& other)
{
	return *this;
}

Ionflux::Template::StringManipulator::StringCenter* StringCenter::copy() 
const
{
    StringCenter* newStringCenter = create();
    *newStringCenter = *this;
    return newStringCenter;
}

Ionflux::Template::StringManipulator::StringCenter* 
StringCenter::upcast(Ionflux::ObjectBase::IFObject* other)
{
    return dynamic_cast<StringCenter*>(other);
}

Ionflux::Template::StringManipulator::StringCenter* 
StringCenter::create(Ionflux::ObjectBase::IFObject* parentObject)
{
    StringCenter* newObject = new StringCenter();
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

/** \file StringCenter.cpp
 * \brief String manipulator: center implementation.
 */
