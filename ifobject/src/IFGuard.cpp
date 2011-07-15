/* ==========================================================================
 * Ionflux Object Base System
 * Copyright © 2006-2011 Joern P. Meier
 * mail@ionflux.org
 * --------------------------------------------------------------------------
 * IFGuard.cpp                     Guard (implementation).
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

#include "ifobject/IFGuard.hpp"
#include "ifobject/IFMutex.hpp"
#include "ifobject/IFLogMessage.hpp"

using namespace std;
using namespace Ionflux::ObjectBase;

namespace Ionflux
{

namespace ObjectBase
{

IFGuardClassInfo::IFGuardClassInfo()
{
	name = "IFGuard";
	desc = "Guard";
	baseClassInfo.push_back(IFObject::CLASS_INFO);
}

IFGuardClassInfo::~IFGuardClassInfo()
{
}

// run-time type information instance constants
const IFGuardClassInfo IFGuard::iFGuardClassInfo;
const Ionflux::ObjectBase::IFClassInfo* IFGuard::CLASS_INFO = &IFGuard::iFGuardClassInfo;

IFGuard::IFGuard()
: mutex(0)
{
	// NOTE: The following line is required for run-time type information.
	theClass = CLASS_INFO;
	// TODO: Nothing ATM. ;-)
}

IFGuard::IFGuard(Ionflux::ObjectBase::IFMutex* initMutex)
: mutex(0)
{
	// NOTE: The following line is required for run-time type information.
	theClass = CLASS_INFO;
	setMutex(initMutex);
}

IFGuard::~IFGuard()
{
	setMutex(0);
}

Ionflux::ObjectBase::IFObject* 
IFGuard::create(Ionflux::ObjectBase::IFObject* parentObject)
{
	IFGuard* newObject = new IFGuard();
	if (newObject == 0)
	{
		cerr << IFLogMessage("Could not allocate object instance.", 
			VL_ERROR, 0, "IFObject::create") << endl;
		return 0;
	}
	if (parentObject != 0)
		parentObject->addLocalRef(newObject);
	return newObject;
}

Ionflux::ObjectBase::IFObject* IFGuard::copy() const
{
	IFGuard* newGuard = new IFGuard();
	*newGuard = *this;
	return newGuard;
}

Ionflux::ObjectBase::IFGuard& IFGuard::operator=(const 
Ionflux::ObjectBase::IFGuard& otherGuard)
{
	setMutex(otherGuard.getMutex());
	return *this;
}

Ionflux::ObjectBase::IFObject& IFGuard::operator=(const 
Ionflux::ObjectBase::IFObject& otherObject)
{
	const IFGuard* otherGuard = dynamic_cast<const IFGuard*>(&otherObject);
	if (otherGuard != 0)
		*this = *otherGuard;
	else
		cerr << "[IFGuard::operator=] ERROR: "
			"Unable to assign object '" << otherObject.getClassName() 
			<< "'." << endl;
	return *this;
}

void IFGuard::setMutex(Ionflux::ObjectBase::IFMutex* newMutex)
{
	if (newMutex == mutex)
		return;
	if (mutex != 0)
	{
		mutex->unlock();
		removeLocalRef(mutex);
	}
	mutex = newMutex;
	if (mutex != 0)
	{
		addLocalRef(mutex);
		mutex->lock();
	}
}

Ionflux::ObjectBase::IFMutex* IFGuard::getMutex() const
{
	return mutex;
}

}

}

/** \file IFGuard.cpp
 * \brief Guard implementation.
 */
