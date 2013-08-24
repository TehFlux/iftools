/* ==========================================================================
 * IFTemplate - Ionflux Template Processor
 * Copyright © 2012 Jörn P. Meier
 * mail@ionflux.org
 * --------------------------------------------------------------------------
 * StringMove.cpp                  String manipulator: move 
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

#include "iftemplate/StringMove.hpp"
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

// public member constants
const std::string StringMove::STRINGMANIP_NAME = "move";

StringMove::StringMove()
{
	// TODO: Nothing ATM. ;-)
}

StringMove::StringMove(const Ionflux::Template::StringManipulator::StringMove& other)
{
	*this = other;
}

StringMove::~StringMove()
{
	// TODO: Nothing ATM. ;-)
}

std::string StringMove::process(const std::string& bytes, 
Ionflux::ObjectBase::StringVector* args)
{
	if ((args == 0) || (args->size() < 3))
	    return bytes;
	unsigned int start = strtol((*args)[0].c_str(), 0, 10);
	unsigned int length = strtol((*args)[1].c_str(), 0, 10);
	unsigned int pos;
	if ((*args)[2] == "front")
	    pos = 0;
	else
	if ((*args)[2] == "back")
	    pos = bytes.size();
	else
	    pos = strtol((*args)[2].c_str(), 0, 10);
	if ((start < 0) || ((start + length) > bytes.size()) 
	    || (pos > bytes.size()) || (pos < 0))
	    return bytes;
	std::string result = bytes;
	std::string sub = bytes.substr(start, length);
	if (pos < bytes.size())
	    result.insert(pos, sub);
	else
	    result.append(sub);
	if (pos < start)
	    result.erase(start + length, length);
	else
	    result.erase(start, length);
	return result;
}

std::string StringMove::getManipName()
{
	// TODO: Implementation.
	return STRINGMANIP_NAME;
}

Ionflux::Template::StringManipulator::StringMove& 
StringMove::operator=(const 
Ionflux::Template::StringManipulator::StringMove& other)
{
	return *this;
}

Ionflux::Template::StringManipulator::StringMove* StringMove::copy() const
{
    StringMove* newStringMove = create();
    *newStringMove = *this;
    return newStringMove;
}

Ionflux::Template::StringManipulator::StringMove* 
StringMove::upcast(Ionflux::ObjectBase::IFObject* other)
{
    return dynamic_cast<StringMove*>(other);
}

Ionflux::Template::StringManipulator::StringMove* 
StringMove::create(Ionflux::ObjectBase::IFObject* parentObject)
{
    StringMove* newObject = new StringMove();
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

/** \file StringMove.cpp
 * \brief String manipulator: move implementation.
 */
