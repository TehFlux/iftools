/* ==========================================================================
 * Ionflux Object Base System
 * Copyright © 2006-2011 Joern P. Meier
 * mail@ionflux.org
 * --------------------------------------------------------------------------
 * IFMutex.cpp                     Mutex (implementation).
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

#include "ifobject/IFMutex.hpp"
#include "ifobject/IFLogMessage.hpp"

using namespace std;
using namespace Ionflux::ObjectBase;

namespace Ionflux
{

namespace ObjectBase
{

IFMutexClassInfo::IFMutexClassInfo()
{
	name = "IFMutex";
	desc = "Mutex";
	baseClassInfo.push_back(IFObject::CLASS_INFO);
}

IFMutexClassInfo::~IFMutexClassInfo()
{
}

// public member constants
const Ionflux::ObjectBase::IFMutexType IFMutex::TYPE_DEFAULT = 0;
const Ionflux::ObjectBase::IFMutexType IFMutex::TYPE_NORMAL = 1;
const Ionflux::ObjectBase::IFMutexType IFMutex::TYPE_ERRORCHECK = 2;
const Ionflux::ObjectBase::IFMutexType IFMutex::TYPE_RECURSIVE = 3;

// run-time type information instance constants
const IFMutexClassInfo IFMutex::iFMutexClassInfo;
const Ionflux::ObjectBase::IFClassInfo* IFMutex::CLASS_INFO = &IFMutex::iFMutexClassInfo;

IFMutex::IFMutex()
: type(Ionflux::ObjectBase::IFMutex::TYPE_DEFAULT)
{
	// NOTE: The following line is required for run-time type information.
	theClass = CLASS_INFO;
	pthread_mutexattr_init(&attributes);
	pthread_mutexattr_settype(&attributes, PTHREAD_MUTEX_DEFAULT);
	pthread_mutex_init(&mutex, &attributes);
}

IFMutex::IFMutex(Ionflux::ObjectBase::IFMutexType initType)
: type(initType)
{
	// NOTE: The following line is required for run-time type information.
	theClass = CLASS_INFO;
	pthread_mutexattr_init(&attributes);
	if (initType == TYPE_NORMAL)
		pthread_mutexattr_settype(&attributes, PTHREAD_MUTEX_NORMAL);
	else
	if (initType == TYPE_ERRORCHECK)
		pthread_mutexattr_settype(&attributes, PTHREAD_MUTEX_ERRORCHECK);
	else
	if (initType == TYPE_RECURSIVE)
		pthread_mutexattr_settype(&attributes, PTHREAD_MUTEX_RECURSIVE);
	else
		pthread_mutexattr_settype(&attributes, PTHREAD_MUTEX_DEFAULT);
	pthread_mutex_init(&mutex, &attributes);
}

IFMutex::~IFMutex()
{
	pthread_mutex_destroy(&mutex);
	pthread_mutexattr_destroy(&attributes);
}

bool IFMutex::lock()
{
	if (pthread_mutex_lock(&mutex) == 0)
		return true;
	return false;
}

bool IFMutex::tryLock()
{
	if (pthread_mutex_trylock(&mutex) == 0)
		return true;
	return false;
}

bool IFMutex::unlock()
{
	if (pthread_mutex_unlock(&mutex) == 0)
		return true;
	return false;
}

Ionflux::ObjectBase::IFObject* 
IFMutex::create(Ionflux::ObjectBase::IFObject* parentObject)
{
	IFMutex* newObject = new IFMutex();
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

Ionflux::ObjectBase::IFObject* IFMutex::copy() const
{
	IFMutex* newMutex = new IFMutex();
	*newMutex = *this;
	return newMutex;
}

Ionflux::ObjectBase::IFMutex& IFMutex::operator=(const 
Ionflux::ObjectBase::IFMutex& otherMutex)
{
	// TODO: Implementation.
	return *this;
}

Ionflux::ObjectBase::IFObject& IFMutex::operator=(const 
Ionflux::ObjectBase::IFObject& otherObject)
{
	const IFMutex* otherMutex = dynamic_cast<const IFMutex*>(&otherObject);
	if (otherMutex != 0)
		*this = *otherMutex;
	else
		cerr << "[IFMutex::operator=] ERROR: "
			"Unable to assign object '" << otherObject.getClassName() 
			<< "'." << endl;
	return *this;
}

std::string IFMutex::getString() const
{
	// TODO: Implementation.
	return IFObject::getString();
}

Ionflux::ObjectBase::IFMutexType IFMutex::getType() const
{
	return type;
}

}

}

/** \file IFMutex.cpp
 * \brief Mutex implementation.
 */
