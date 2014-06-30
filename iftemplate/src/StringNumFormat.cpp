/* ==========================================================================
 * IFTemplate - Ionflux Template Processor
 * Copyright © 2012 Jörn P. Meier
 * mail@ionflux.org
 * --------------------------------------------------------------------------
 * StringNumFormat.cpp             String manipulator: numformat 
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

#include "iftemplate/StringNumFormat.hpp"
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

StringNumFormatClassInfo::StringNumFormatClassInfo()
{
	name = "StringNumFormat";
	desc = "String manipulator: numformat";
}

StringNumFormatClassInfo::~StringNumFormatClassInfo()
{
}

// public member constants
const std::string StringNumFormat::STRINGMANIP_NAME = "numformat";

// run-time type information instance constants
const StringNumFormatClassInfo StringNumFormat::stringNumFormatClassInfo;
const Ionflux::ObjectBase::IFClassInfo* StringNumFormat::CLASS_INFO = &StringNumFormat::stringNumFormatClassInfo;

StringNumFormat::StringNumFormat()
{
	// NOTE: The following line is required for run-time type information.
	theClass = CLASS_INFO;
	// TODO: Nothing ATM. ;-)
}

StringNumFormat::StringNumFormat(const Ionflux::Template::StringManipulator::StringNumFormat& other)
{
	// NOTE: The following line is required for run-time type information.
	theClass = CLASS_INFO;
	*this = other;
}

StringNumFormat::~StringNumFormat()
{
	// TODO: Nothing ATM. ;-)
}

std::string StringNumFormat::process(const std::string& bytes, 
Ionflux::ObjectBase::StringVector* args)
{
	if ((args == 0) || (args->size() < 3))
	    return bytes;
	std::string integers = "";
	std::string decimals = "";
	std::string result = "";
	unsigned int numDecimals = strtol((*args)[0].c_str(), 0, 10);
	std::string dsep = (*args)[1];
	std::string tsep = (*args)[2];
	unsigned int pos = 0;
	// Find first digit.
	while ((pos < bytes.size()) && !isdigit(bytes[pos]))
	    pos++;
	// Extract integer part.
	while ((pos < bytes.size()) && isdigit(bytes[pos]))
	{
	    integers.append(1, bytes[pos]);
	    pos++;
	}
	// Extract decimal part.
	if ((pos < bytes.size()) && (bytes[pos] == '.'))
	{
	    pos++;
	    while ((pos < bytes.size()) && isdigit(bytes[pos]))
	    {
	        decimals.append(1, bytes[pos]);
	        pos++;
	    }
	}
	if (decimals.size() < numDecimals)
	    decimals.append(numDecimals - decimals.size(), '0');
	// Add integer part with thousands separators to result.
	int numIndex = 0;
	for (int i = (integers.size() - 1); i >= 0; i--)
	{
	    numIndex = integers.size() - 1 - i;
	    if ((numIndex != 0) && ((numIndex % 3) == 0))
	        result.insert(0, tsep);
	    result.insert(0, 1, integers[i]);
	}
	if (numDecimals > 0)
	{
	    result.append(dsep);
	    result.append(decimals.substr(0, numDecimals));
	}
	return result;
}

std::string StringNumFormat::getManipName()
{
	// TODO: Implementation.
	return STRINGMANIP_NAME;
}

Ionflux::Template::StringManipulator::StringNumFormat& 
StringNumFormat::operator=(const 
Ionflux::Template::StringManipulator::StringNumFormat& other)
{
if (this == &other)
    return *this;
	return *this;
}

Ionflux::Template::StringManipulator::StringNumFormat* 
StringNumFormat::copy() const
{
    StringNumFormat* newStringNumFormat = create();
    *newStringNumFormat = *this;
    return newStringNumFormat;
}

Ionflux::Template::StringManipulator::StringNumFormat* 
StringNumFormat::upcast(Ionflux::ObjectBase::IFObject* other)
{
    return dynamic_cast<StringNumFormat*>(other);
}

Ionflux::Template::StringManipulator::StringNumFormat* 
StringNumFormat::create(Ionflux::ObjectBase::IFObject* parentObject)
{
    StringNumFormat* newObject = new StringNumFormat();
    if (newObject == 0)
    {
        return 0;
    }
    if (parentObject != 0)
        parentObject->addLocalRef(newObject);
    return newObject;
}

unsigned int StringNumFormat::getMemSize() const
{
    return sizeof *this;
}

}

}

}

/** \file StringNumFormat.cpp
 * \brief String manipulator: numformat implementation.
 */
