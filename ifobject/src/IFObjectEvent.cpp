/* ==========================================================================
 * Ionflux Object Base System
 * Copyright © 2006 Joern P. Meier
 * mail@ionflux.org
 * --------------------------------------------------------------------------
 * IFObjectEvent.cpp               Event class for the 'object' event. 
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

#include "ifobject/IFObjectEvent.hpp"

using namespace std;

namespace Ionflux
{

namespace ObjectBase
{

IFObjectEventClassInfo::IFObjectEventClassInfo()
{
	name = "IFObjectEvent";
	desc = "Event class for the 'object' event.";
	baseClassInfo.push_back(IFObject::CLASS_INFO);
}

IFObjectEventClassInfo::~IFObjectEventClassInfo()
{
}

// public member constants
const Ionflux::ObjectBase::IFEventType IFObjectEvent::TYPE_OBJECT_CHANGED = 0;
const Ionflux::ObjectBase::IFEventType IFObjectEvent::TYPE_OBJECT_ID_NUM_CHANGED = 1;
const Ionflux::ObjectBase::IFEventType IFObjectEvent::TYPE_OBJECT_ID_CHANGED = 2;

// run-time type information instance constants
const IFObjectEventClassInfo IFObjectEvent::iFObjectEventClassInfo;
const Ionflux::ObjectBase::IFClassInfo* IFObjectEvent::CLASS_INFO = &IFObjectEvent::iFObjectEventClassInfo;

IFObjectEvent::IFObjectEvent()
: type(TYPE_OBJECT_CHANGED), source(0), oldIDNum(0), newIDNum(0), oldID(""), newID("")
{
	// NOTE: The following line is required for run-time type information.
	theClass = CLASS_INFO;
	// TODO: Nothing ATM. ;-)
}

IFObjectEvent::~IFObjectEvent()
{
	// TODO: Nothing ATM. ;-)
}

void IFObjectEvent::setType(Ionflux::ObjectBase::IFEventType newType)
{
	type = newType;
}

Ionflux::ObjectBase::IFEventType IFObjectEvent::getType() const
{
	return type;
}

void IFObjectEvent::setSource(Ionflux::ObjectBase::IFObject* newSource)
{
	source = newSource;
}

Ionflux::ObjectBase::IFObject* IFObjectEvent::getSource() const
{
	return source;
}

void IFObjectEvent::setOldIDNum(Ionflux::ObjectBase::IFIDNum newOldIDNum)
{
	oldIDNum = newOldIDNum;
}

Ionflux::ObjectBase::IFIDNum IFObjectEvent::getOldIDNum() const
{
	return oldIDNum;
}

void IFObjectEvent::setNewIDNum(Ionflux::ObjectBase::IFIDNum newNewIDNum)
{
	newIDNum = newNewIDNum;
}

Ionflux::ObjectBase::IFIDNum IFObjectEvent::getNewIDNum() const
{
	return newIDNum;
}

void IFObjectEvent::setOldID(const Ionflux::ObjectBase::IFObjectID& 
newOldID)
{
	oldID = newOldID;
}

Ionflux::ObjectBase::IFObjectID IFObjectEvent::getOldID() const
{
	return oldID;
}

void IFObjectEvent::setNewID(const Ionflux::ObjectBase::IFObjectID& 
newNewID)
{
	newID = newNewID;
}

Ionflux::ObjectBase::IFObjectID IFObjectEvent::getNewID() const
{
	return newID;
}

}

}

/** \file IFObjectEvent.cpp
 * \brief Event class for the 'object' event. implementation.
 */
