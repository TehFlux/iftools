/* ==========================================================================
 * Ionflux Object Base System
 * Copyright © 2006 Joern P. Meier
 * mail@ionflux.org
 * --------------------------------------------------------------------------
 * IFThreadEvent.cpp               Event class for the 'thread' event. 
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

#include "ifobject/IFThreadEvent.hpp"

using namespace std;

namespace Ionflux
{

namespace ObjectBase
{

IFThreadEventClassInfo::IFThreadEventClassInfo()
{
	name = "IFThreadEvent";
	desc = "Event class for the 'thread' event.";
	baseClassInfo.push_back(IFObject::CLASS_INFO);
}

// public member constants
const Ionflux::ObjectBase::IFEventType IFThreadEvent::TYPE_UNDEFINED = 0;
const Ionflux::ObjectBase::IFEventType IFThreadEvent::TYPE_START = 1;
const Ionflux::ObjectBase::IFEventType IFThreadEvent::TYPE_RUN = 2;
const Ionflux::ObjectBase::IFEventType IFThreadEvent::TYPE_STOP = 3;

// run-time type information instance constants
const IFThreadEventClassInfo IFThreadEvent::iFThreadEventClassInfo;
const Ionflux::ObjectBase::IFClassInfo* IFThreadEvent::CLASS_INFO = &IFThreadEvent::iFThreadEventClassInfo;

IFThreadEvent::IFThreadEvent()
: type(TYPE_UNDEFINED), source(0)
{
	// NOTE: The following line is required for run-time type information.
	theClass = CLASS_INFO;
	// TODO: Nothing ATM. ;-)
}

IFThreadEvent::~IFThreadEvent()
{
	// TODO: Nothing ATM. ;-)
}

void IFThreadEvent::setType(Ionflux::ObjectBase::IFEventType newType)
{
	type = newType;
}

Ionflux::ObjectBase::IFEventType IFThreadEvent::getType() const
{
	return type;
}

void IFThreadEvent::setSource(Ionflux::ObjectBase::IFThread* newSource)
{
	source = newSource;
}

Ionflux::ObjectBase::IFThread* IFThreadEvent::getSource() const
{
	return source;
}

}

}

/** \file IFThreadEvent.cpp
 * \brief Event class for the 'thread' event. implementation.
 */
