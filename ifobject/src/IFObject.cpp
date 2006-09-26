/* ==========================================================================
 * Ionflux Object Base System
 * Copyright © 2006 Joern P. Meier
 * mail@ionflux.org
 * --------------------------------------------------------------------------
 * IFObject.cpp                    Object (implementation).
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

#include "ifobject/IFObject.hpp"
#include "ifobject/IFMutex.hpp"
#include "ifobject/IFGuard.hpp"
#include "ifobject/IFLogMessage.hpp"
#include "ifobject/IFSignal.hpp"
#include "ifobject/IFObjectEvent.hpp"
#include <sstream>

using namespace std;
using namespace Ionflux::ObjectBase;

namespace Ionflux
{

namespace ObjectBase
{

// structure constants

IFObjectClassInfo::IFObjectClassInfo()
{
	name = "IFObject";
	desc = "Object";
}

// public member constants
const IFIDNum IFObject::ID_NUM_UNDEFINED = -1;

// signal type and instance name constants
const Ionflux::ObjectBase::IFSignalType IFObject::SIGNAL_TYPE_OBJECT = 
	"bool,const Ionflux::ObjectBase::IFObjectEvent&";
const std::string IFObject::SIGNAL_NAME_OBJECT_CHANGED = "object_changed";
const std::string IFObject::SIGNAL_NAME_OBJECT_ID_NUM_CHANGED = "object_id_num_changed";
const std::string IFObject::SIGNAL_NAME_OBJECT_ID_CHANGED = "object_id_changed";

// run-time type information instance constants
const IFObjectClassInfo IFObject::iFObjectClassInfo;
const Ionflux::ObjectBase::IFClassInfo* IFObject::CLASS_INFO = &IFObject::iFObjectClassInfo;

IFObject::IFObject()
: idNum(ID_NUM_UNDEFINED), refData(0), guardMutex(0), logTarget(0), signalObjectChangedWrapper(0), signalObjectIDNumChangedWrapper(0), signalObjectIDChangedWrapper(0)
{
	// NOTE: The following line is required for run-time type information.
	theClass = CLASS_INFO;
	/* NOTE: Creating IFObjects here will cause an infinite loop. 
	         (Don't do it.) */
	refData = new IFRefCountData();
	if (refData == 0)
	{
		std::cerr << "[IFObject::IFObject] ERROR: "
			"Could not allocate reference count data structure "
			"(this is bad, exiting)." << std::endl;
		exit(-1);
	}
	refData->refCount = 0;
}

IFObject::~IFObject()
{
	removeAllLocalRefs();
	delete refData;
	refData = 0;
}

IFObjectEvent* IFObject::createObjectEvent()
{
	IFGuard functionGuard(guardMutex);
	IFObjectEvent* event = new IFObjectEvent();
	if (event == 0)
	{
		log(IFLogMessage("Could not allocate event.", 
			IFLogMessage::VL_ASSERTION, this, "createObjectEvent"));
		return 0;
	}
	addLocalRef(event);
	return event;
}

const Ionflux::ObjectBase::IFClassInfo* IFObject::getClass() const
{
	IFGuard functionGuard(guardMutex);
	// TODO: Implementation.
	return theClass;
}

std::string IFObject::getClassName() const
{
	IFGuard functionGuard(guardMutex);
	const IFClassInfo* theClassInfo = getClass();
	if (theClassInfo != 0)
		return theClassInfo->getName();
	return "";
}

std::string IFObject::getClassDesc() const
{
	IFGuard functionGuard(guardMutex);
	const IFClassInfo* theClassInfo = getClass();
	if (theClassInfo != 0)
		return theClassInfo->getDesc();
	return "";
}

void IFObject::setID(const Ionflux::ObjectBase::IFObjectID& newID)
{
	IFGuard functionGuard(guardMutex);
	IFObjectEvent* event = createObjectEvent();
	event->setType(IFObjectEvent::TYPE_OBJECT_ID_CHANGED);
	event->setOldID(id);
	event->setNewID(newID);
	id = newID;
	signalObjectIDChanged.emit(*event);
	removeLocalRef(event);
}

Ionflux::ObjectBase::IFObjectID IFObject::getID() const
{
	IFGuard functionGuard(guardMutex);
	// TODO: Implementation.
	return id;
}

void IFObject::setIDNum(Ionflux::ObjectBase::IFIDNum newIDNum)
{
	IFGuard functionGuard(guardMutex);
	IFObjectEvent* event = createObjectEvent();
	event->setType(IFObjectEvent::TYPE_OBJECT_ID_NUM_CHANGED);
	event->setOldIDNum(idNum);
	event->setNewIDNum(newIDNum);
	idNum = newIDNum;
	signalObjectIDNumChanged.emit(*event);
	removeLocalRef(event);
}

Ionflux::ObjectBase::IFIDNum IFObject::getIDNum() const
{
	IFGuard functionGuard(guardMutex);
	// TODO: Implementation.
	return idNum;
}

std::string IFObject::getString() const
{
	IFGuard functionGuard(guardMutex);
	ostringstream state;
	state << getClassName();
	if (id.size() > 0)
		state << "{" << id << "}";
	return state.str();
}

 IFObject::operator std::string() const
{
	IFGuard functionGuard(guardMutex);
	// TODO: Implementation.
	return getString();
}

Ionflux::ObjectBase::IFObject* IFObject::copy() const
{
	IFGuard functionGuard(guardMutex);
	log(IFLogMessage("Copy operation not implemented.", 
		IFLogMessage::VL_ERROR, this, "copy"));
	return 0;
}

Ionflux::ObjectBase::IFObject* 
IFObject::create(Ionflux::ObjectBase::IFObject* parentObject)
{
	IFObject* newObject = new IFObject();
	if (newObject == 0)
	{
		cerr << IFLogMessage("Could not allocate object instance.", 
			IFLogMessage::VL_ERROR, 0, "IFObject::create") << endl;
		return 0;
	}
	if (parentObject != 0)
		parentObject->addLocalRef(newObject);
	return newObject;
}

Ionflux::ObjectBase::IFObject& IFObject::operator=(const 
Ionflux::ObjectBase::IFObject& otherObject)
{
	IFGuard functionGuard(guardMutex);
	log(IFLogMessage("Assignment operator not implemented.", 
		IFLogMessage::VL_ERROR, this, "operator="));
	return *this;
}

void IFObject::log(const Ionflux::ObjectBase::IFObject& logObject)
{
	IFGuard functionGuard(guardMutex);
	if (logTarget == 0)
		cout << logObject << endl;
	else
		logTarget->log(logObject);
}

void IFObject::log()
{
	IFGuard functionGuard(guardMutex);
	log(*this);
}

void IFObject::log(const Ionflux::ObjectBase::IFObject& logObject) const
{
	IFGuard functionGuard(guardMutex);
	if (logTarget == 0)
		cout << logObject << endl;
	else
		logTarget->log(logObject);
}

void IFObject::log() const
{
	IFGuard functionGuard(guardMutex);
	log(*this);
}

bool IFObject::assert(bool assertion, const Ionflux::ObjectBase::IFObject& 
logObject)
{
	IFGuard functionGuard(guardMutex);
	if (!assertion)
		log(logObject);
	return assertion;
}

bool IFObject::assert(bool assertion, const Ionflux::ObjectBase::IFObject& 
logObject) const
{
	IFGuard functionGuard(guardMutex);
	if (!assertion)
		log(logObject);
	return assertion;
}

bool IFObject::addRef() const
{
	IFGuard functionGuard(guardMutex);
	if (refData->refCount < UINT_MAX)
		refData->refCount++;
	else
	{
		log(IFLogMessage("Reference count overflow.", 
			IFLogMessage::VL_ERROR, this, "addRef"));
		return false;
	}
	return true;
}

bool IFObject::removeRef() const
{
	IFGuard functionGuard(guardMutex);
	if (refData->refCount > 0)
		refData->refCount--;
	else
	{
		log(IFLogMessage("Attempt to remove reference for object "
			"with zero references.", IFLogMessage::VL_ERROR, this, "removeRef"));
		return false;
	}
	return true;
}

unsigned int IFObject::getNumRefs() const
{
	IFGuard functionGuard(guardMutex);
	// TODO: Implementation.
	return refData->refCount;
}

bool IFObject::addLocalRef(Ionflux::ObjectBase::IFObject* refTarget) const
{
	IFGuard functionGuard(guardMutex);
	if (refTarget == 0)
	{
		log(IFLogMessage("Attempt to add reference to null object.", 
			IFLogMessage::VL_ERROR, this, "addLocalRef"));
		return false;
	}
	IFObjectRefMap::iterator i = refData->refMap.find(refTarget);
	IFObjectRefInfo* refInfo = 0;
	if ((i != refData->refMap.end())
		&& ((*i).second != 0))
		refInfo = (*i).second;
	else
	{
		refInfo = new IFObjectRefInfo();
		if (refInfo == 0)
		{
			log(IFLogMessage("Could not allocate "
				"object reference info.", IFLogMessage::VL_ASSERTION, this, 
				"addLocalRef"));
			return false;
		}
		refInfo->refCount = 0;
		refData->refMap[refTarget] = refInfo;
	}
	if (!refTarget->addRef())
	{
		ostringstream state;
		state << "Could not add reference to object '" 
			<< refTarget->getString() << "'.";
		log(IFLogMessage(state.str(), 
			IFLogMessage::VL_ERROR, this, "addLocalRef"));
		return false;
	}
	if (refInfo->refCount < UINT_MAX)
		refInfo->refCount++;
	else
	{
		log(IFLogMessage("Local reference count overflow.", 
			IFLogMessage::VL_ERROR, this, "addLocalRef"));
		refTarget->removeRef();
		return false;
	}
	/* ----- DEBUG ----- //
	ostringstream state;
	state << "Added local reference to object '" 
		<< refTarget->getString() << "'.";
	log(IFLogMessage(state.str(), 
		IFLogMessage::VL_DEBUG_INSANE, this, "addLocalRef"));
	// ----- DEBUG ----- */
	return true;
}

bool IFObject::removeLocalRef(Ionflux::ObjectBase::IFObject* refTarget) 
const
{
	IFGuard functionGuard(guardMutex);
	if (refTarget == 0)
	{
		log(IFLogMessage("Attempt to remove reference to null object.", 
			IFLogMessage::VL_ERROR, this, "removeLocalRef"));
		return false;
	}
	IFObjectRefMap::iterator i = refData->refMap.find(refTarget);
	IFObjectRefInfo* refInfo = 0;
	if ((i != refData->refMap.end())
		&& ((*i).second != 0))
		refInfo = (*i).second;
	if ((refInfo == 0)
		|| (refInfo->refCount == 0))
	{
		ostringstream state;
		state << "Could not remove local reference to object '" 
			<< refTarget->getString() << "': No local references found.";
		log(IFLogMessage(state.str(), 
			IFLogMessage::VL_ERROR, this, "removeLocalRef"));
		return false;
	}
	if (refInfo->refCount > 0)
		refInfo->refCount--;
	else
	{
		log(IFLogMessage("Attempt to remove local reference for object "
			"with zero local references.", IFLogMessage::VL_ERROR, this, 
			"removeLocalRef"));
		return false;
	}
	if (refInfo->refCount == 0)
	{
		refData->refMap[refTarget] = 0;
		delete refInfo;
		refInfo = 0;
		refData->refMap.erase(i);
		/* ----- DEBUG ----- //
		ostringstream state;
		state << "Removed local reference info for object '" 
			<< refTarget->getString() << "'.";
		log(IFLogMessage(state.str(), 
			IFLogMessage::VL_DEBUG_INSANE, this, "removeLocalRef"));
		// ----- DEBUG ----- */
	}
	if (!refTarget->removeRef())
	{
		ostringstream state;
		state << "Could not remove reference to object '" 
			<< refTarget->getString() << "'.";
		log(IFLogMessage(state.str(), 
			IFLogMessage::VL_ERROR, this, "removeLocalRef"));
		return false;
	}
	if (refTarget->getNumRefs() == 0)
	{
		/* ----- DEBUG ----- //
		ostringstream state;
		state << "Deleting object '" << refTarget->getString() 
			<< "' since there are no more references.";
		log(IFLogMessage(state.str(), 
			IFLogMessage::VL_DEBUG_INSANE, this, "removeLocalRef"));
		// ----- DEBUG ----- */
		delete refTarget;
		refTarget = 0;
	}
	/* ----- DEBUG ----- //
	if (refTarget != 0)
	{
		ostringstream state;
		state << "Removed local reference to object '" 
			<< refTarget->getString() << "'.";
		log(IFLogMessage(state.str(), 
			IFLogMessage::VL_DEBUG_INSANE, this, "removeLocalRef"));
	}
	// ----- DEBUG ----- */
	return true;
}

bool IFObject::removeAllLocalRefs() const
{
	IFGuard functionGuard(guardMutex);
	IFObjectRefInfo* refInfo = 0;
	IFObjectRefMap::iterator i;
	IFObject* refTarget = 0;
	bool result = true;
	for (i = refData->refMap.begin(); i != refData->refMap.end(); i++)
	{
		refTarget = (*i).first;
		refInfo = (*i).second;
		if ((refInfo != 0)
			&& (refTarget != 0))
		{
			while (refInfo->refCount > 0)
			{
				if (!refTarget->removeRef())
				{
					ostringstream state;
					state << "Could not remove reference to object '" 
						<< refTarget->getString() << "'.";
					log(IFLogMessage(state.str(), 
						IFLogMessage::VL_ERROR, this, "removeAllLocalRefs"));
					result = false;
				}
				refInfo->refCount--;
				if (refTarget->getNumRefs() == 0)
				{
					/* ----- DEBUG ----- //
					ostringstream state;
					state << "Deleting object '" << refTarget->getString() 
						<< "' since there are no more references.";
					log(IFLogMessage(state.str(), 
						IFLogMessage::VL_DEBUG_INSANE, this, 
							"removeAllLocalRefs"));
					// ----- DEBUG ----- */
					delete refTarget;
					refTarget = 0;
				}
				/* ----- DEBUG ----- //
				if (refTarget != 0)
				{
					ostringstream state;
					state << "Removed local reference to object '" 
						<< refTarget->getString() << "'.";
					log(IFLogMessage(state.str(), 
						IFLogMessage::VL_DEBUG_INSANE, this, 
							"removeAllLocalRefs"));
				}
				// ----- DEBUG ----- */
			}
			refData->refMap[refTarget] = 0;
			delete refInfo;
			refInfo = 0;
		}
	}
	refData->refMap.clear();
	return result;
}

void IFObject::setGuardEnabled(bool newGuardState)
{
	IFGuard functionGuard(guardMutex);
	if (newGuardState)
	{
		if (guardMutex != 0)
			return;
		guardMutex = new Ionflux::ObjectBase::IFMutex(IFMutex::TYPE_RECURSIVE);
		if (guardMutex == 0)
			log(IFLogMessage("Could not allocate guard mutex.", 
				IFLogMessage::VL_ASSERTION, this, "setGuardEnabled"));
		addLocalRef(guardMutex);
	} else
	{
		if (guardMutex != 0)
		{
			removeLocalRef(guardMutex);
			guardMutex = 0;
		}
	}
}

bool IFObject::getGuardEnabled()
{
	IFGuard functionGuard(guardMutex);
	if (guardMutex != 0)
		return true;
	return false;
}

bool IFObject::lock() const
{
	IFGuard functionGuard(guardMutex);
	if (guardMutex != 0)
		return guardMutex->lock();
	return true;
}

bool IFObject::tryLock() const
{
	IFGuard functionGuard(guardMutex);
	if (guardMutex != 0)
		return guardMutex->tryLock();
	return true;
}

bool IFObject::unlock() const
{
	IFGuard functionGuard(guardMutex);
	if (guardMutex != 0)
		return guardMutex->unlock();
	return true;
}

void IFObject::setLogTarget(Ionflux::ObjectBase::IFObject* newLogTarget)
{
	IFGuard propertyGuard(guardMutex);
	if (logTarget == newLogTarget)
		return;
	if (logTarget != 0)
		removeLocalRef(logTarget);
	logTarget = newLogTarget;
	if (logTarget != 0)
		addLocalRef(logTarget);
}

Ionflux::ObjectBase::IFObject* IFObject::getLogTarget() const
{
	IFGuard propertyGuard(guardMutex);
	return logTarget;
}

IFObjectSignal& IFObject::getSignalObjectChanged()
{
	return signalObjectChanged;
}

Ionflux::ObjectBase::IFSignal* IFObject::getSignalObjectChangedWrapper()
{
	if (signalObjectChangedWrapper == 0)
	{
		signalObjectChangedWrapper = new Ionflux::ObjectBase::IFSignal(
			&signalObjectChanged, SIGNAL_TYPE_OBJECT, 
			SIGNAL_NAME_OBJECT_CHANGED);
		if (signalObjectChangedWrapper == 0)
			log(IFLogMessage("Could not allocate signal wrapper.", 
				IFLogMessage::VL_ASSERTION, this, 
				"getSignalObjectChangedWrapper"));
		addLocalRef(signalObjectChangedWrapper);
	}
	return signalObjectChangedWrapper;
}

IFObjectSignal& IFObject::getSignalObjectIDNumChanged()
{
	return signalObjectIDNumChanged;
}

Ionflux::ObjectBase::IFSignal* IFObject::getSignalObjectIDNumChangedWrapper()
{
	if (signalObjectIDNumChangedWrapper == 0)
	{
		signalObjectIDNumChangedWrapper = new Ionflux::ObjectBase::IFSignal(
			&signalObjectIDNumChanged, SIGNAL_TYPE_OBJECT, 
			SIGNAL_NAME_OBJECT_ID_NUM_CHANGED);
		if (signalObjectIDNumChangedWrapper == 0)
			log(IFLogMessage("Could not allocate signal wrapper.", 
				IFLogMessage::VL_ASSERTION, this, 
				"getSignalObjectIDNumChangedWrapper"));
		addLocalRef(signalObjectIDNumChangedWrapper);
	}
	return signalObjectIDNumChangedWrapper;
}

IFObjectSignal& IFObject::getSignalObjectIDChanged()
{
	return signalObjectIDChanged;
}

Ionflux::ObjectBase::IFSignal* IFObject::getSignalObjectIDChangedWrapper()
{
	if (signalObjectIDChangedWrapper == 0)
	{
		signalObjectIDChangedWrapper = new Ionflux::ObjectBase::IFSignal(
			&signalObjectIDChanged, SIGNAL_TYPE_OBJECT, 
			SIGNAL_NAME_OBJECT_ID_CHANGED);
		if (signalObjectIDChangedWrapper == 0)
			log(IFLogMessage("Could not allocate signal wrapper.", 
				IFLogMessage::VL_ASSERTION, this, 
				"getSignalObjectIDChangedWrapper"));
		addLocalRef(signalObjectIDChangedWrapper);
	}
	return signalObjectIDChangedWrapper;
}

std::ostream& operator<<(std::ostream& outputStream, const 
Ionflux::ObjectBase::IFObject& source)
{
	// TODO: Implementation.
	return outputStream << source.getString();
}

}

}

/** \file IFObject.cpp
 * \brief Object implementation.
 */
