/* ==========================================================================
 * Ionflux Object Base System
 * Copyright © 2006 Joern P. Meier
 * mail@ionflux.org
 * --------------------------------------------------------------------------
 * IFClassInfo.cpp                 Class information (implementation).
 * =========================================================================
 * 
 * This file is part of Ionflux Object Base System.
 * 
 * Ionflux Object Base System is free software; you can redistribute it 
 * and/or modify it under the terms of the GNU General Public License as 
 * published by the Free Software Foundation; either version 2 of the 
 * License, or (at your option) any later version.
 * 
 * Ionflux Object Base System is distributed in the hope that it will be 
 * useful, but WITHOUT ANY WARRANTY; without even the implied warranty of 
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU 
 * General Public License for more details.
 * 
 * You should have received a copy of the GNU General Public License along 
 * with Ionflux Object Base System; if not, write to the Free Software 
 * Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA 02111-1307 USA
 * 
 * ========================================================================== */

#include "ifobject/IFClassInfo.hpp"

namespace Ionflux
{

namespace ObjectBase
{

IFClassInfo::IFClassInfo()
: name("<undefined>"), desc("<undefined>")
{
	// TODO: Nothing ATM. ;-)
}

IFClassInfo::~IFClassInfo()
{
	// TODO: Nothing ATM. ;-)
}
int IFClassInfo::getNumBaseClasses() const
{
	// TODO: Implementation.
	return baseClassInfo.size();
}

Ionflux::ObjectBase::IFClassInfo* IFClassInfo::getBaseClassInfo(unsigned 
int index) const
{
	IFClassInfo* result = 0;
	if (index < baseClassInfo.size())
		return baseClassInfo[index];
	return result;
}

bool IFClassInfo::isDerivedFrom(const Ionflux::ObjectBase::IFClassInfo* 
searchClass, bool recursive) const
{
	bool result = false;
	IFClassInfoVector::const_iterator i = baseClassInfo.begin();
	IFClassInfo* currentClassInfo = 0;
	while (!result
		&& (i != baseClassInfo.end()))
	{
		currentClassInfo = *i;
		if (currentClassInfo != 0)
		{
			if (currentClassInfo == searchClass)
				result = true;
			else
			if (recursive)
				result = currentClassInfo->isDerivedFrom(searchClass, true);
		}
		i++;
	}
	return result;
}

bool IFClassInfo::isBaseOf(const Ionflux::ObjectBase::IFClassInfo* 
checkClass, bool recursive) const
{
	if (checkClass == 0)
		return false;
	return checkClass->isDerivedFrom(this, recursive);
}


std::string IFClassInfo::getName() const
{
	return name;
}

std::string IFClassInfo::getDesc() const
{
	return desc;
}
}

}

/** \file IFClassInfo.cpp
 * \brief Class information implementation.
 */
