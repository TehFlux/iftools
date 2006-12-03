/* ==========================================================================
 * Ionflux Object Base System
 * Copyright © 2006 Joern P. Meier
 * mail@ionflux.org
 * --------------------------------------------------------------------------
 * IFExampleSignalProxy.cpp        Proxy for the 'example' signal 
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

#include "test/include/IFExampleSignalProxy.hpp"
#include "ifobject/IFLogMessage.hpp"
#include <sstream>

namespace Ionflux
{

namespace Example
{

IFExampleSignalProxyClassInfo::IFExampleSignalProxyClassInfo()
{
	name = "IFExampleSignalProxy";
	desc = "Proxy for the 'example' signal";
	baseClassInfo.push_back(IFObject::CLASS_INFO);
}

IFExampleSignalProxyClassInfo::~IFExampleSignalProxyClassInfo()
{
}

// run-time type information instance constants
const IFExampleSignalProxyClassInfo IFExampleSignalProxy::iFExampleSignalProxyClassInfo;
const Ionflux::ObjectBase::IFClassInfo* IFExampleSignalProxy::CLASS_INFO = &IFExampleSignalProxy::iFExampleSignalProxyClassInfo;

IFExampleSignalProxy::IFExampleSignalProxy()
{
	// NOTE: The following line is required for run-time type information.
	theClass = CLASS_INFO;
	// TODO: Nothing ATM. ;-)
}

IFExampleSignalProxy::~IFExampleSignalProxy()
{
	// TODO: Nothing ATM. ;-)
}

void IFExampleSignalProxy::onIFExampleSignal(const 
Ionflux::Example::IFExampleEvent& param0)
{
	// TODO: Implementation.
}

bool IFExampleSignalProxy::connect(Ionflux::ObjectBase::IFSignal* target, 
int action)
{
	if (target == 0)
		return false;
	IFExampleSignal* targetSignal = 0;
	if (target->getType() == IFExampleClass::SIGNAL_TYPE_EXAMPLE)
	{
		targetSignal = reinterpret_cast<IFExampleSignal*>(target->getSignal());
		signalConnection.disconnect();
		signalConnection = targetSignal->connect(sigc::mem_fun(*this, 
			&IFExampleSignalProxy::onIFExampleSignal));
		return true;
	}
	return false;
}

void IFExampleSignalProxy::disconnect()
{
	signalConnection.disconnect();
}

Ionflux::ObjectBase::IFObject* 
IFExampleSignalProxy::create(Ionflux::ObjectBase::IFObject* parentObject)
{
	IFExampleSignalProxy* newObject = new IFExampleSignalProxy();
	if (newObject == 0)
	{
		std::cerr << IFLogMessage("Could not allocate object instance.", 
			IFLogMessage::VL_ERROR, 0, "IFObject::create") << std::endl;
		return 0;
	}
	if (parentObject != 0)
		parentObject->addLocalRef(newObject);
	return newObject;
}

Ionflux::ObjectBase::IFObject* IFExampleSignalProxy::copy() const
{
	IFExampleSignalProxy* newSignal = new IFExampleSignalProxy();
	*newSignal = *this;
	return newSignal;
}

IFExampleSignalProxy& IFExampleSignalProxy::operator=(const 
IFExampleSignalProxy& otherSignalProxy)
{
	// TODO: Implementation.
	return *this;
}

Ionflux::ObjectBase::IFObject& IFExampleSignalProxy::operator=(const 
Ionflux::ObjectBase::IFObject& otherObject)
{
	const IFExampleSignalProxy* otherSignalProxy = dynamic_cast<const 
	IFExampleSignalProxy*>(&otherObject);
	if (otherSignalProxy != 0)
		*this = *otherSignalProxy;
	else
		std::cerr << "[IFSignal::operator=] ERROR: "
			"Unable to assign object '" << otherObject.getClassName() 
			<< "'." << std::endl;
	return *this;
}

std::string IFExampleSignalProxy::getString() const
{
	std::ostringstream state;
	state << IFObject::getString();
	return state.str();
}

}

}

/** \file IFExampleSignalProxy.cpp
 * \brief Proxy for the 'example' signal implementation.
 */
