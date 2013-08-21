/* ==========================================================================
 * Ionflux Object Base System
 * Copyright © 2006-2011 Joern P. Meier
 * mail@ionflux.org
 * --------------------------------------------------------------------------
 * IFMMEvent.cpp                   Memory Management Event 
 * (implementation).
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

#include "ifobject/IFMMEvent.hpp"
#include <cmath>
#include <cstdlib>
#include <sstream>
#include <iomanip>
#include <cmath>
#include "ifobject/IFError.hpp"
#include "ifobject/utils.hpp"

using namespace std;

namespace Ionflux
{

namespace ObjectBase
{

IFMMEventClassInfo::IFMMEventClassInfo()
{
	name = "IFMMEvent";
	desc = "Memory Management Event";
}

IFMMEventClassInfo::~IFMMEventClassInfo()
{
}

// public member constants
const Ionflux::ObjectBase::MMEventTypeID IFMMEvent::TYPE_UNDEFINED = 0;
const Ionflux::ObjectBase::MMEventTypeID IFMMEvent::TYPE_CREATE = 1;
const Ionflux::ObjectBase::MMEventTypeID IFMMEvent::TYPE_DELETE = 2;
const Ionflux::ObjectBase::MMEventTypeID IFMMEvent::TYPE_ADD_REF = 3;
const Ionflux::ObjectBase::MMEventTypeID IFMMEvent::TYPE_REMOVE_REF = 4;
const Ionflux::ObjectBase::MMEventTypeID IFMMEvent::TYPE_ADD_LOCAL_REF = 5;
const Ionflux::ObjectBase::MMEventTypeID IFMMEvent::TYPE_REMOVE_LOCAL_REF = 6;

// run-time type information instance constants
const IFMMEventClassInfo IFMMEvent::iFMMEventClassInfo;
const Ionflux::ObjectBase::IFClassInfo* IFMMEvent::CLASS_INFO = &IFMMEvent::iFMMEventClassInfo;

IFMMEvent::IFMMEvent()
: typeID(TYPE_UNDEFINED), object(0), objectRefCount(0), parentObject(0)
{
	// NOTE: The following line is required for run-time type information.
	theClass = CLASS_INFO;
	// TODO: Nothing ATM. ;-)
}

IFMMEvent::IFMMEvent(const Ionflux::ObjectBase::IFMMEvent& other)
: typeID(TYPE_UNDEFINED), object(0), objectRefCount(0), parentObject(0)
{
	// NOTE: The following line is required for run-time type information.
	theClass = CLASS_INFO;
	*this = other;
}

IFMMEvent::IFMMEvent(Ionflux::ObjectBase::MMEventTypeID initTypeID, const 
Ionflux::ObjectBase::IFObject* initObject, unsigned int initObjectRefCount,
const Ionflux::ObjectBase::IFObject* initParentObject)
: typeID(initTypeID), object(0), objectRefCount(initObjectRefCount), 
parentObject(0)
{
	// NOTE: The following line is required for run-time type information.
	theClass = CLASS_INFO;
	setObject(initObject);
	setParentObject(initParentObject);
}

IFMMEvent::~IFMMEvent()
{
	// TODO: Nothing ATM. ;-)
}

bool IFMMEvent::operator==(const Ionflux::ObjectBase::IFMMEvent& other) 
const
{
	// TODO: Implementation.
	return (typeID == other.typeID) && (object == other.object);
}

bool IFMMEvent::operator!=(const Ionflux::ObjectBase::IFMMEvent& other) 
const
{
	// TODO: Implementation.
	return !(*this == other);;
}

std::string IFMMEvent::getValueString() const
{
	ostringstream state;
	state << mmTypeIDGetString(typeID) << ", obj = " 
	    << dynamic_cast<const void*>(object);
	if (object != 0)
	{
	    state << " (" << object->getIDString() << ")";
	}
	if (parentObject != 0)
	{
	    state << ", parent = " << dynamic_cast<const void*>(parentObject) 
	        << " (" << parentObject->getIDString() << ")";
	}
	state << ", refs = " << objectRefCount;
	return state.str();
}

void IFMMEvent::setTypeID(Ionflux::ObjectBase::MMEventTypeID newTypeID)
{
	typeID = newTypeID;
}

Ionflux::ObjectBase::MMEventTypeID IFMMEvent::getTypeID() const
{
	return typeID;
}

void IFMMEvent::setObject(const Ionflux::ObjectBase::IFObject* newObject)
{
	object = newObject;
}

const Ionflux::ObjectBase::IFObject* IFMMEvent::getObject() const
{
	return object;
}

void IFMMEvent::setObjectRefCount(unsigned int newObjectRefCount)
{
	objectRefCount = newObjectRefCount;
}

unsigned int IFMMEvent::getObjectRefCount() const
{
	return objectRefCount;
}

void IFMMEvent::setParentObject(const Ionflux::ObjectBase::IFObject* 
newParentObject)
{
	parentObject = newParentObject;
}

const Ionflux::ObjectBase::IFObject* IFMMEvent::getParentObject() const
{
	return parentObject;
}

Ionflux::ObjectBase::IFMMEvent& IFMMEvent::operator=(const 
Ionflux::ObjectBase::IFMMEvent& other)
{
    if (this == &other)
        return *this;
    typeID = other.typeID;
    setObject(other.object);
    setParentObject(other.parentObject);
	return *this;
}

Ionflux::ObjectBase::IFMMEvent* IFMMEvent::copy() const
{
    IFMMEvent* newIFMMEvent = create();
    *newIFMMEvent = *this;
    return newIFMMEvent;
}

Ionflux::ObjectBase::IFMMEvent* 
IFMMEvent::upcast(Ionflux::ObjectBase::IFObject* other)
{
    return dynamic_cast<IFMMEvent*>(other);
}

Ionflux::ObjectBase::IFMMEvent* 
IFMMEvent::create(Ionflux::ObjectBase::IFObject* parentObject)
{
    IFMMEvent* newObject = new IFMMEvent();
    if (newObject == 0)
    {
        throw IFError("Could not allocate object.");
    }
    if (parentObject != 0)
        parentObject->addLocalRef(newObject);
    return newObject;
}

Ionflux::ObjectBase::IFMMEvent* 
IFMMEvent::create(Ionflux::ObjectBase::MMEventTypeID initTypeID, const 
Ionflux::ObjectBase::IFObject* initObject, unsigned int initObjectRefCount,
const Ionflux::ObjectBase::IFObject* initParentObject, 
Ionflux::ObjectBase::IFObject* parentObject)
{
    IFMMEvent* newObject = new IFMMEvent(initTypeID, initObject, 
    initObjectRefCount, initParentObject);
    if (newObject == 0)
    {
        throw IFError("Could not allocate object.");
    }
    if (parentObject != 0)
        parentObject->addLocalRef(newObject);
    return newObject;
}

}

}

/** \file IFMMEvent.cpp
 * \brief Memory Management Event implementation.
 */
