/* ==========================================================================
 * Ionflux Tools
 * Copyright (c) 2004-2005 Joern P. Meier
 * mail@ionflux.org
 * --------------------------------------------------------------------------
 * Object.cpp                      Object.
 * ==========================================================================
 * 
 * This file is part of Ionflux Tools.
 * 
 * Ionflux Tools is free software; you can redistribute it and/or modify it
 * under the terms of the GNU General Public License as published by the 
 * Free Software Foundation; either version 2 of the License, or (at your 
 * option) any later version.
 * 
 * Ionflux Tools is distributed in the hope that it will be useful, but 
 * WITHOUT ANY WARRANTY; without even the implied warranty of 
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU 
 * General Public License for more details.
 * 
 * You should have received a copy of the GNU General Public License along 
 * with Ionflux Tools; if not, write to the Free Software Foundation, Inc.,
 * 59 Temple Place, Suite 330, Boston, MA 02111-1307 USA
 * 
 * ========================================================================== */

#include "ionflux/Object.hpp"

using namespace std;
using namespace Ionflux::Tools;

namespace Ionflux
{

namespace Tools
{

ObjectClassInfo::ObjectClassInfo()
{
	name = "Object";
	desc = "Object";
}

const ObjectClassInfo Object::objectClassInfo;
const ClassInfo* Object::CLASS_INFO = &Object::objectClassInfo;

Object::Object()
{
	// NOTE: The following line is required for class information.
	theClasses.push_back(CLASS_INFO);
}

Object::~Object()
{
	// TODO: Nothing ATM. ;-)
}

const ClassInfo* Object::getClass() const
{
	if (theClasses.size() > 0)
		return theClasses[theClasses.size() - 1];
	return 0;
}

std::string Object::getClassName() const
{
	const ClassInfo* theClassInfo = getClass();
	if (theClassInfo != 0)
		return theClassInfo->getName();
	return "";
}

std::string Object::getClassDesc() const
{
	const ClassInfo* theClassInfo = getClass();
	if (theClassInfo != 0)
		return theClassInfo->getDesc();
	return "";
}

}

}

/** \file Object.cpp
 * \brief Object implementation.
 */
