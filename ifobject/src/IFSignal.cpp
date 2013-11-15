/* ==========================================================================
 * Ionflux Object Base System
 * Copyright © 2006-2011 Joern P. Meier
 * mail@ionflux.org
 * --------------------------------------------------------------------------
 * IFSignal.cpp                    Signal (implementation).
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

#include "ifobject/IFSignal.hpp"
#include "ifobject/IFLogMessage.hpp"
#include <sstream>

using namespace std;
using namespace Ionflux::ObjectBase;

namespace Ionflux
{

namespace ObjectBase
{

IFSignalClassInfo::IFSignalClassInfo()
{
	name = "IFSignal";
	desc = "Signal";
	baseClassInfo.push_back(Ionflux::ObjectBase::IFObject::CLASS_INFO);
}

IFSignalClassInfo::~IFSignalClassInfo()
{
}

// run-time type information instance constants
const IFSignalClassInfo IFSignal::iFSignalClassInfo;
const Ionflux::ObjectBase::IFClassInfo* IFSignal::CLASS_INFO = &IFSignal::iFSignalClassInfo;

IFSignal::IFSignal()
: signal(0)
{
	// NOTE: The following line is required for run-time type information.
	theClass = CLASS_INFO;
	// TODO: Nothing ATM. ;-)
}

IFSignal::IFSignal(Ionflux::ObjectBase::IFSignalBase initSignal, 
Ionflux::ObjectBase::IFSignalType initType, std::string initName)
: signal(initSignal), type(initType), name(initName)
{
	// NOTE: The following line is required for run-time type information.
	theClass = CLASS_INFO;
	// TODO: Nothing ATM. ;-)
}

IFSignal::~IFSignal()
{
	// TODO: Nothing ATM. ;-)
}

Ionflux::ObjectBase::IFObject* 
IFSignal::create(Ionflux::ObjectBase::IFObject* parentObject)
{
	IFSignal* newObject = new IFSignal();
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

Ionflux::ObjectBase::IFObject* IFSignal::copy() const
{
	IFSignal* newSignal = new IFSignal();
	*newSignal = *this;
	return newSignal;
}

Ionflux::ObjectBase::IFSignal& IFSignal::operator=(const 
Ionflux::ObjectBase::IFSignal& otherSignal)
{
	// TODO: Implementation.
	return *this;
}

Ionflux::ObjectBase::IFObject& IFSignal::operator=(const 
Ionflux::ObjectBase::IFObject& otherObject)
{
	const IFSignal* otherSignal = dynamic_cast<const IFSignal*>(&otherObject);
	if (otherSignal != 0)
		*this = *otherSignal;
	else
		std::cerr << "[IFSignal::operator=] ERROR: "
			"Unable to assign object '" << otherObject.getClassName() 
			<< "'." << std::endl;
	return *this;
}

std::string IFSignal::getString() const
{
	ostringstream state;
	state << IFObject::getString() << ":{" << type << ";" << name << "}";
	return state.str();
}

Ionflux::ObjectBase::IFSignalBase IFSignal::getSignal() const
{
    return signal;
}

Ionflux::ObjectBase::IFSignalType IFSignal::getType() const
{
    return type;
}

std::string IFSignal::getName() const
{
    return name;
}

}

}

/** \file IFSignal.cpp
 * \brief Signal implementation.
 */
