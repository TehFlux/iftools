/* ==========================================================================
 * IFTemplate - Ionflux Template Processor
 * Copyright © 2012 Jörn P. Meier
 * mail@ionflux.org
 * --------------------------------------------------------------------------
 * StringInsert.cpp                String manipulator: insert 
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

#include "iftemplate/StringInsert.hpp"
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

StringInsertClassInfo::StringInsertClassInfo()
{
	name = "StringInsert";
	desc = "String manipulator: insert";
}

StringInsertClassInfo::~StringInsertClassInfo()
{
}

// public member constants
const std::string StringInsert::STRINGMANIP_NAME = "insert";

// run-time type information instance constants
const StringInsertClassInfo StringInsert::stringInsertClassInfo;
const Ionflux::ObjectBase::IFClassInfo* StringInsert::CLASS_INFO = &StringInsert::stringInsertClassInfo;

StringInsert::StringInsert()
{
	// NOTE: The following line is required for run-time type information.
	theClass = CLASS_INFO;
	// TODO: Nothing ATM. ;-)
}

StringInsert::StringInsert(const Ionflux::Template::StringManipulator::StringInsert& other)
{
	// NOTE: The following line is required for run-time type information.
	theClass = CLASS_INFO;
	*this = other;
}

StringInsert::~StringInsert()
{
	// TODO: Nothing ATM. ;-)
}

std::string StringInsert::process(const std::string& bytes, 
Ionflux::ObjectBase::StringVector* args)
{
	if ((args == 0) || (args->size() < 2))
	    return bytes;
	unsigned int pos;
	if ((*args)[1] == "front")
	    pos = 0;
	else
	if ((*args)[1] == "back")
	    pos = bytes.size();
	else
	    pos = strtol((*args)[1].c_str(), 0, 10);
	if ((pos > bytes.size()) || (pos < 0))
	    return bytes;
	string result = bytes;
	if (pos < bytes.size())
	    result.insert(pos, (*args)[0]);
	else
	    result.append((*args)[0]);
	return result;
}

std::string StringInsert::getManipName()
{
	// TODO: Implementation.
	return STRINGMANIP_NAME;
}

Ionflux::Template::StringManipulator::StringInsert& 
StringInsert::operator=(const 
Ionflux::Template::StringManipulator::StringInsert& other)
{
if (this == &other)
    return *this;
	return *this;
}

Ionflux::Template::StringManipulator::StringInsert* StringInsert::copy() 
const
{
    StringInsert* newStringInsert = create();
    *newStringInsert = *this;
    return newStringInsert;
}

Ionflux::Template::StringManipulator::StringInsert* 
StringInsert::upcast(Ionflux::ObjectBase::IFObject* other)
{
    return dynamic_cast<StringInsert*>(other);
}

Ionflux::Template::StringManipulator::StringInsert* 
StringInsert::create(Ionflux::ObjectBase::IFObject* parentObject)
{
    StringInsert* newObject = new StringInsert();
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

/** \file StringInsert.cpp
 * \brief String manipulator: insert implementation.
 */
