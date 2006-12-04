/* ==========================================================================
 * Ionflux Object Base System
 * Copyright © 2006 Joern P. Meier
 * mail@ionflux.org
 * --------------------------------------------------------------------------
 * IFThreadSignalProxy.cpp         Proxy for the 'thread' signal 
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

#include "ifobject/IFThreadSignalProxy.hpp"
#include "ifobject/IFLogMessage.hpp"
#include <sstream>

using namespace std;
using namespace Ionflux::ObjectBase;

namespace Ionflux
{

namespace ObjectBase
{

IFThreadSignalProxyClassInfo::IFThreadSignalProxyClassInfo()
{
	name = "IFThreadSignalProxy";
	desc = "Proxy for the 'thread' signal";
	baseClassInfo.push_back(IFObject::CLASS_INFO);
}

IFThreadSignalProxyClassInfo::~IFThreadSignalProxyClassInfo()
{
}

// run-time type information instance constants
const IFThreadSignalProxyClassInfo IFThreadSignalProxy::iFThreadSignalProxyClassInfo;
const Ionflux::ObjectBase::IFClassInfo* IFThreadSignalProxy::CLASS_INFO = &IFThreadSignalProxy::iFThreadSignalProxyClassInfo;

IFThreadSignalProxy::IFThreadSignalProxy()
{
	// NOTE: The following line is required for run-time type information.
	theClass = CLASS_INFO;
	// TODO: Nothing ATM. ;-)
}

IFThreadSignalProxy::~IFThreadSignalProxy()
{
	// TODO: Nothing ATM. ;-)
}

bool IFThreadSignalProxy::onIFThreadSignal(const 
Ionflux::ObjectBase::IFThreadEvent& param0)
{
	// TODO: Implementation.
	return true;
}

bool IFThreadSignalProxy::connect(Ionflux::ObjectBase::IFSignal* target, 
int action)
{
	if (target == 0)
		return false;
	IFThreadSignal* targetSignal = 0;
	if (target->getType() == IFThread::SIGNAL_TYPE_THREAD)
	{
		targetSignal = reinterpret_cast<IFThreadSignal*>(target->getSignal());
		signalConnection.disconnect();
		signalConnection = targetSignal->connect(sigc::mem_fun(*this, 
			&IFThreadSignalProxy::onIFThreadSignal));
		return true;
	}
	return false;
}

void IFThreadSignalProxy::disconnect()
{
	signalConnection.disconnect();
}

Ionflux::ObjectBase::IFObject* 
IFThreadSignalProxy::create(Ionflux::ObjectBase::IFObject* parentObject)
{
	IFThreadSignalProxy* newObject = new IFThreadSignalProxy();
	if (newObject == 0)
	{
		std::cerr << IFLogMessage("Could not allocate object instance.", 
			VL_ERROR, 0, "IFObject::create") << std::endl;
		return 0;
	}
	if (parentObject != 0)
		parentObject->addLocalRef(newObject);
	return newObject;
}

Ionflux::ObjectBase::IFObject* IFThreadSignalProxy::copy() const
{
	IFThreadSignalProxy* newSignal = new IFThreadSignalProxy();
	*newSignal = *this;
	return newSignal;
}

IFThreadSignalProxy& IFThreadSignalProxy::operator=(const 
IFThreadSignalProxy& otherSignalProxy)
{
	// TODO: Implementation.
	return *this;
}

Ionflux::ObjectBase::IFObject& IFThreadSignalProxy::operator=(const 
Ionflux::ObjectBase::IFObject& otherObject)
{
	const IFThreadSignalProxy* otherSignalProxy = dynamic_cast<const 
	IFThreadSignalProxy*>(&otherObject);
	if (otherSignalProxy != 0)
		*this = *otherSignalProxy;
	else
		std::cerr << "[IFSignal::operator=] ERROR: "
			"Unable to assign object '" << otherObject.getClassName() 
			<< "'." << std::endl;
	return *this;
}

std::string IFThreadSignalProxy::getString() const
{
	std::ostringstream state;
	state << IFObject::getString();
	return state.str();
}

}

}

/** \file IFThreadSignalProxy.cpp
 * \brief Proxy for the 'thread' signal implementation.
 */
