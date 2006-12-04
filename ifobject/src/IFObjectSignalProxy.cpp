/* ==========================================================================
 * Ionflux Object Base System
 * Copyright © 2006 Joern P. Meier
 * mail@ionflux.org
 * --------------------------------------------------------------------------
 * IFObjectSignalProxy.cpp         Proxy for the 'object' signal 
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

#include "ifobject/IFObjectSignalProxy.hpp"
#include "ifobject/IFLogMessage.hpp"
#include <sstream>

using namespace std;
using namespace Ionflux::ObjectBase;

namespace Ionflux
{

namespace ObjectBase
{

IFObjectSignalProxyClassInfo::IFObjectSignalProxyClassInfo()
{
	name = "IFObjectSignalProxy";
	desc = "Proxy for the 'object' signal";
	baseClassInfo.push_back(IFObject::CLASS_INFO);
}

IFObjectSignalProxyClassInfo::~IFObjectSignalProxyClassInfo()
{
}

// run-time type information instance constants
const IFObjectSignalProxyClassInfo IFObjectSignalProxy::iFObjectSignalProxyClassInfo;
const Ionflux::ObjectBase::IFClassInfo* IFObjectSignalProxy::CLASS_INFO = &IFObjectSignalProxy::iFObjectSignalProxyClassInfo;

IFObjectSignalProxy::IFObjectSignalProxy()
{
	// NOTE: The following line is required for run-time type information.
	theClass = CLASS_INFO;
	// TODO: Nothing ATM. ;-)
}

IFObjectSignalProxy::~IFObjectSignalProxy()
{
	// TODO: Nothing ATM. ;-)
}

bool IFObjectSignalProxy::onIFObjectSignal(const 
Ionflux::ObjectBase::IFObjectEvent& param0)
{
	// TODO: Implementation.
	return true;
}

bool IFObjectSignalProxy::connect(Ionflux::ObjectBase::IFSignal* target, 
int action)
{
	if (target == 0)
		return false;
	IFObjectSignal* targetSignal = 0;
	if (target->getType() == IFObject::SIGNAL_TYPE_OBJECT)
	{
		targetSignal = reinterpret_cast<IFObjectSignal*>(target->getSignal());
		signalConnection.disconnect();
		signalConnection = targetSignal->connect(sigc::mem_fun(*this, 
			&IFObjectSignalProxy::onIFObjectSignal));
		return true;
	}
	return false;
}

void IFObjectSignalProxy::disconnect()
{
	signalConnection.disconnect();
}

Ionflux::ObjectBase::IFObject* 
IFObjectSignalProxy::create(Ionflux::ObjectBase::IFObject* parentObject)
{
	IFObjectSignalProxy* newObject = new IFObjectSignalProxy();
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

Ionflux::ObjectBase::IFObject* IFObjectSignalProxy::copy() const
{
	IFObjectSignalProxy* newSignal = new IFObjectSignalProxy();
	*newSignal = *this;
	return newSignal;
}

IFObjectSignalProxy& IFObjectSignalProxy::operator=(const 
IFObjectSignalProxy& otherSignalProxy)
{
	// TODO: Implementation.
	return *this;
}

Ionflux::ObjectBase::IFObject& IFObjectSignalProxy::operator=(const 
Ionflux::ObjectBase::IFObject& otherObject)
{
	const IFObjectSignalProxy* otherSignalProxy = dynamic_cast<const 
	IFObjectSignalProxy*>(&otherObject);
	if (otherSignalProxy != 0)
		*this = *otherSignalProxy;
	else
		std::cerr << "[IFSignal::operator=] ERROR: "
			"Unable to assign object '" << otherObject.getClassName() 
			<< "'." << std::endl;
	return *this;
}

std::string IFObjectSignalProxy::getString() const
{
	std::ostringstream state;
	state << IFObject::getString();
	return state.str();
}

}

}

/** \file IFObjectSignalProxy.cpp
 * \brief Proxy for the 'object' signal implementation.
 */
