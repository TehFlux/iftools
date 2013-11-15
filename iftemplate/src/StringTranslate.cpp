/* ==========================================================================
 * IFTemplate - Ionflux Template Processor
 * Copyright © 2012 Jörn P. Meier
 * mail@ionflux.org
 * --------------------------------------------------------------------------
 * StringTranslate.cpp             String manipulator: translate 
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

#include "iftemplate/StringTranslate.hpp"
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

StringTranslateClassInfo::StringTranslateClassInfo()
{
	name = "StringTranslate";
	desc = "String manipulator: translate";
}

StringTranslateClassInfo::~StringTranslateClassInfo()
{
}

// public member constants
const std::string StringTranslate::STRINGMANIP_NAME = "translate";

// run-time type information instance constants
const StringTranslateClassInfo StringTranslate::stringTranslateClassInfo;
const Ionflux::ObjectBase::IFClassInfo* StringTranslate::CLASS_INFO = &StringTranslate::stringTranslateClassInfo;

StringTranslate::StringTranslate()
{
	// NOTE: The following line is required for run-time type information.
	theClass = CLASS_INFO;
	// TODO: Nothing ATM. ;-)
}

StringTranslate::StringTranslate(const Ionflux::Template::StringManipulator::StringTranslate& other)
{
	// NOTE: The following line is required for run-time type information.
	theClass = CLASS_INFO;
	*this = other;
}

StringTranslate::~StringTranslate()
{
	// TODO: Nothing ATM. ;-)
}

std::string StringTranslate::process(const std::string& bytes, 
Ionflux::ObjectBase::StringVector* args)
{
	if ((args == 0) || (args->size() < 2))
	    return bytes;
	std::string source = (*args)[0];
	std::string target = (*args)[1];
	int numChars;
	source.size() > target.size() 
	    ? (numChars = target.size())
	    : (numChars = source.size());
	std::string result = "";
	bool match = false;
	int pos = 0;
	for (unsigned int i = 0; i < bytes.size(); i++)
	{
	    match = false;
	    pos = 0;
	    while (!match 
	        && (pos < numChars))
	    {
	        if (bytes[i] == source[pos])
	            match = true;
	        else
	            pos++;
	    }
	    if (match)
	        result.append(1, target[pos]);
	    else
	        result.append(1, bytes[i]);
	}
	return result;
}

std::string StringTranslate::getManipName()
{
	// TODO: Implementation.
	return STRINGMANIP_NAME;
}

Ionflux::Template::StringManipulator::StringTranslate& 
StringTranslate::operator=(const 
Ionflux::Template::StringManipulator::StringTranslate& other)
{
if (this == &other)
    return *this;
	return *this;
}

Ionflux::Template::StringManipulator::StringTranslate* 
StringTranslate::copy() const
{
    StringTranslate* newStringTranslate = create();
    *newStringTranslate = *this;
    return newStringTranslate;
}

Ionflux::Template::StringManipulator::StringTranslate* 
StringTranslate::upcast(Ionflux::ObjectBase::IFObject* other)
{
    return dynamic_cast<StringTranslate*>(other);
}

Ionflux::Template::StringManipulator::StringTranslate* 
StringTranslate::create(Ionflux::ObjectBase::IFObject* parentObject)
{
    StringTranslate* newObject = new StringTranslate();
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

/** \file StringTranslate.cpp
 * \brief String manipulator: translate implementation.
 */
