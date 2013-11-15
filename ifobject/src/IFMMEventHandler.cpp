/* ==========================================================================
 * Ionflux Object Base System
 * Copyright © 2006-2011 Joern P. Meier
 * mail@ionflux.org
 * --------------------------------------------------------------------------
 * IFMMEventHandler.cpp            Memory management event handler 
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

#include "ifobject/IFMMEventHandler.hpp"
#include <cmath>
#include <cstdlib>
#include <sstream>
#include <iomanip>
#include <cmath>
#include "ifobject/IFError.hpp"
#include "ifobject/utils.hpp"
#include "ifobject/IFMMEvent.hpp"

using namespace std;

namespace Ionflux
{

namespace ObjectBase
{

IFMMEventHandlerClassInfo::IFMMEventHandlerClassInfo()
{
	name = "IFMMEventHandler";
	desc = "Memory management event handler";
}

IFMMEventHandlerClassInfo::~IFMMEventHandlerClassInfo()
{
}

// static protected member variables
Ionflux::ObjectBase::IFMMEventHandler* IFMMEventHandler::instance = 0;

// run-time type information instance constants
const IFMMEventHandlerClassInfo IFMMEventHandler::iFMMEventHandlerClassInfo;
const Ionflux::ObjectBase::IFClassInfo* IFMMEventHandler::CLASS_INFO = &IFMMEventHandler::iFMMEventHandlerClassInfo;

IFMMEventHandler::IFMMEventHandler()
: target(0), logFileName(""), silentFlag(true)
{
	// NOTE: The following line is required for run-time type information.
	theClass = CLASS_INFO;
	// TODO: Nothing ATM. ;-)
}

IFMMEventHandler::IFMMEventHandler(const Ionflux::ObjectBase::IFMMEventHandler& other)
: target(0), logFileName(""), silentFlag(true)
{
	// NOTE: The following line is required for run-time type information.
	theClass = CLASS_INFO;
	*this = other;
}

IFMMEventHandler::IFMMEventHandler(Ionflux::ObjectBase::IFMMEventHandler* 
initTarget, const std::string& initLogFileName, bool initSilentFlag)
: target(0), logFileName(initLogFileName), silentFlag(initSilentFlag)
{
	// NOTE: The following line is required for run-time type information.
	theClass = CLASS_INFO;
	if (initTarget != 0)
	    setTarget(initTarget);
}

IFMMEventHandler::~IFMMEventHandler()
{
	// TODO: Nothing ATM. ;-)
}

void IFMMEventHandler::handleMMEvent(const Ionflux::ObjectBase::IFMMEvent& 
event) const
{
	if (target != 0)
	{
	    target->handleMMEvent(event);
	    return;
	}
	if (logFileName.size() > 0)
	{
	    std::ostringstream s0;
	    s0 << "[" << getTimestamp() << "] " << event.getValueString() 
	        << "\n";
	    writeFile(logFileName, s0.str(), 'a');
	    return;
	}
	if (!silentFlag)
	    std::cerr << event << std::endl;
}

std::string IFMMEventHandler::getValueString() const
{
	ostringstream state;
	if (target != 0)
	{
	    state << "target = " << dynamic_cast<const void*>(target) 
	        << " (" << target->getIDString() << ")";
	}
	return state.str();
}

Ionflux::ObjectBase::IFMMEventHandler* IFMMEventHandler::getInstance()
{
	if (instance != 0)
	    return instance;
	instance = Ionflux::ObjectBase::create<IFMMEventHandler>(
	    "IFMMEventHandler::getInstance", "event handler");
	instance->addRef();
	return instance;
}

void IFMMEventHandler::cleanup()
{
	if (instance == 0)
	    return;
	if (instance->getNumRefs() == 0)
	    throw IFError("[IFMMEventHandler::cleanup] "
	        "Event handler has already been cleaned up.");
	instance->removeRef();
	if (instance->getNumRefs() == 0)
	{
	    delete instance;
	    instance = 0;
	} else
	    throw IFError("[MMEventHandler::cleanup] "
	        "Event handler still referenced on cleanup.");
}

void IFMMEventHandler::setTarget(Ionflux::ObjectBase::IFMMEventHandler* 
newTarget)
{
	if (target == newTarget)
		return;
    if (newTarget != 0)
        addLocalRef(newTarget);
	if (target != 0)
		removeLocalRef(target);
	target = newTarget;
}

Ionflux::ObjectBase::IFMMEventHandler* IFMMEventHandler::getTarget() const
{
    return target;
}

void IFMMEventHandler::setLogFileName(const std::string& newLogFileName)
{
	logFileName = newLogFileName;
}

std::string IFMMEventHandler::getLogFileName() const
{
    return logFileName;
}

void IFMMEventHandler::setSilentFlag(bool newSilentFlag)
{
	silentFlag = newSilentFlag;
}

bool IFMMEventHandler::getSilentFlag() const
{
    return silentFlag;
}

Ionflux::ObjectBase::IFMMEventHandler& IFMMEventHandler::operator=(const 
Ionflux::ObjectBase::IFMMEventHandler& other)
{
    if (this == &other)
        return *this;
    setTarget(other.target);
	return *this;
}

Ionflux::ObjectBase::IFMMEventHandler* IFMMEventHandler::copy() const
{
    IFMMEventHandler* newIFMMEventHandler = create();
    *newIFMMEventHandler = *this;
    return newIFMMEventHandler;
}

Ionflux::ObjectBase::IFMMEventHandler* 
IFMMEventHandler::upcast(Ionflux::ObjectBase::IFObject* other)
{
    return dynamic_cast<IFMMEventHandler*>(other);
}

Ionflux::ObjectBase::IFMMEventHandler* 
IFMMEventHandler::create(Ionflux::ObjectBase::IFObject* parentObject)
{
    IFMMEventHandler* newObject = new IFMMEventHandler();
    if (newObject == 0)
    {
        throw IFError("Could not allocate object.");
    }
    if (parentObject != 0)
        parentObject->addLocalRef(newObject);
    return newObject;
}

Ionflux::ObjectBase::IFMMEventHandler* 
IFMMEventHandler::create(Ionflux::ObjectBase::IFMMEventHandler* initTarget,
const std::string& initLogFileName, bool initSilentFlag, 
Ionflux::ObjectBase::IFObject* parentObject)
{
    IFMMEventHandler* newObject = new IFMMEventHandler(initTarget, 
    initLogFileName, initSilentFlag);
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

/** \file IFMMEventHandler.cpp
 * \brief Memory management event handler implementation.
 */
