/* ==========================================================================
 * IFTemplate - Ionflux Template Processor
 * Copyright © 2012 Jörn P. Meier
 * mail@ionflux.org
 * --------------------------------------------------------------------------
 * StringXMLEscape.cpp             String manipulator: xmlescape 
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

#include "iftemplate/StringXMLEscape.hpp"
#include <iostream>
#include <iomanip>
#include <sstream>
#include <cstdlib>
#include "ifobject/xmlutils.hpp"

using namespace std;

namespace Ionflux
{

namespace Template
{

namespace StringManipulator
{

StringXMLEscapeClassInfo::StringXMLEscapeClassInfo()
{
	name = "StringXMLEscape";
	desc = "String manipulator: xmlescape";
}

StringXMLEscapeClassInfo::~StringXMLEscapeClassInfo()
{
}

// public member constants
const std::string StringXMLEscape::STRINGMANIP_NAME = "xmlescape";

// run-time type information instance constants
const StringXMLEscapeClassInfo StringXMLEscape::stringXMLEscapeClassInfo;
const Ionflux::ObjectBase::IFClassInfo* StringXMLEscape::CLASS_INFO = &StringXMLEscape::stringXMLEscapeClassInfo;

StringXMLEscape::StringXMLEscape()
{
	// NOTE: The following line is required for run-time type information.
	theClass = CLASS_INFO;
	// TODO: Nothing ATM. ;-)
}

StringXMLEscape::StringXMLEscape(const Ionflux::Template::StringManipulator::StringXMLEscape& other)
{
	// NOTE: The following line is required for run-time type information.
	theClass = CLASS_INFO;
	*this = other;
}

StringXMLEscape::~StringXMLEscape()
{
	// TODO: Nothing ATM. ;-)
}

std::string StringXMLEscape::process(const std::string& bytes, 
Ionflux::ObjectBase::StringVector* args)
{
	// TODO: Implementation.
	return Ionflux::ObjectBase::XMLUtils::xmlEscape(bytes);
}

std::string StringXMLEscape::getManipName()
{
	// TODO: Implementation.
	return STRINGMANIP_NAME;
}

Ionflux::Template::StringManipulator::StringXMLEscape& 
StringXMLEscape::operator=(const 
Ionflux::Template::StringManipulator::StringXMLEscape& other)
{
	return *this;
}

Ionflux::Template::StringManipulator::StringXMLEscape* 
StringXMLEscape::copy() const
{
    StringXMLEscape* newStringXMLEscape = create();
    *newStringXMLEscape = *this;
    return newStringXMLEscape;
}

Ionflux::Template::StringManipulator::StringXMLEscape* 
StringXMLEscape::upcast(Ionflux::ObjectBase::IFObject* other)
{
    return dynamic_cast<StringXMLEscape*>(other);
}

Ionflux::Template::StringManipulator::StringXMLEscape* 
StringXMLEscape::create(Ionflux::ObjectBase::IFObject* parentObject)
{
    StringXMLEscape* newObject = new StringXMLEscape();
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

/** \file StringXMLEscape.cpp
 * \brief String manipulator: xmlescape implementation.
 */
