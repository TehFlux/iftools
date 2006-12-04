/* ==========================================================================
 * Ionflux Object Base System
 * Copyright © 2006 Joern P. Meier
 * mail@ionflux.org
 * --------------------------------------------------------------------------
 * IFExampleEvent.cpp              Event class for the 'example' event. 
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

#include "test/include/IFExampleEvent.hpp"
#include "test/include/IFExampleClass.hpp"

using namespace std;
using namespace Ionflux::ObjectBase;

namespace Ionflux
{

namespace Example
{

IFExampleEventClassInfo::IFExampleEventClassInfo()
{
	name = "IFExampleEvent";
	desc = "Event class for the 'example' event.";
	baseClassInfo.push_back(IFObject::CLASS_INFO);
}

IFExampleEventClassInfo::~IFExampleEventClassInfo()
{
}

// public member constants
const int IFExampleEvent::TYPE_FIRST = 0;
const int IFExampleEvent::TYPE_SECOND = 1;

// run-time type information instance constants
const IFExampleEventClassInfo IFExampleEvent::iFExampleEventClassInfo;
const Ionflux::ObjectBase::IFClassInfo* IFExampleEvent::CLASS_INFO = &IFExampleEvent::iFExampleEventClassInfo;

IFExampleEvent::IFExampleEvent()
: type(TYPE_FIRST), source(0)
{
	// NOTE: The following line is required for run-time type information.
	theClass = CLASS_INFO;
	// TODO: Nothing ATM. ;-)
}

IFExampleEvent::~IFExampleEvent()
{
	// TODO: Nothing ATM. ;-)
}

void IFExampleEvent::setType(int newType)
{
	type = newType;
}

int IFExampleEvent::getType() const
{
	return type;
}

void IFExampleEvent::setSource(Ionflux::Example::IFExampleClass* newSource)
{
	source = newSource;
}

Ionflux::Example::IFExampleClass* IFExampleEvent::getSource() const
{
	return source;
}

}

}

/** \file IFExampleEvent.cpp
 * \brief Event class for the 'example' event. implementation.
 */
