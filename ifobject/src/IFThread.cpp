/* ==========================================================================
 * Ionflux Object Base System
 * Copyright © 2006 Joern P. Meier
 * mail@ionflux.org
 * --------------------------------------------------------------------------
 * IFThread.cpp                    Thread (implementation).
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

#include "ifobject/IFThread.hpp"
#include "ifobject/IFLogMessage.hpp"
#include "ifobject/IFSignal.hpp"
#include "ifobject/IFThreadEvent.hpp"
#include <unistd.h>
#include <sstream>

using namespace std;
using namespace Ionflux::ObjectBase;

namespace Ionflux
{

namespace ObjectBase
{

IFThreadClassInfo::IFThreadClassInfo()
{
	name = "IFThread";
	desc = "Thread";
	baseClassInfo.push_back(IFObject::CLASS_INFO);
}

IFThreadClassInfo::~IFThreadClassInfo()
{
}

// public member constants
const IFAtomic IFThread::SHUTDOWN_DISABLED = 0;
const IFAtomic IFThread::SHUTDOWN_ENABLED = 1;

// signal type and instance name constants
const Ionflux::ObjectBase::IFSignalType IFThread::SIGNAL_TYPE_THREAD = 
	"bool,const Ionflux::ObjectBase::IFThreadEvent&";
const std::string IFThread::SIGNAL_NAME_START = "start";
const std::string IFThread::SIGNAL_NAME_RUN = "run";
const std::string IFThread::SIGNAL_NAME_STOP = "stop";

// run-time type information instance constants
const IFThreadClassInfo IFThread::iFThreadClassInfo;
const Ionflux::ObjectBase::IFClassInfo* IFThread::CLASS_INFO = &IFThread::iFThreadClassInfo;

IFThread::IFThread()
: shutdownFlag(Ionflux::ObjectBase::IFThread::SHUTDOWN_DISABLED), runFlag(false), initFlag(false), threadFunction(startImpl), context(0), signalStartWrapper(0), signalRunWrapper(0), signalStopWrapper(0)
{
	// NOTE: The following line is required for run-time type information.
	theClass = CLASS_INFO;
	pthread_attr_init(&threadAttributes);
	pthread_attr_setdetachstate(&threadAttributes, PTHREAD_CREATE_JOINABLE);
}

IFThread::~IFThread()
{
	pthread_attr_destroy(&threadAttributes);
}

IFThreadEvent* IFThread::createThreadEvent()
{
	IFThreadEvent* event = new IFThreadEvent();
	if (event == 0)
	{
		log(IFLogMessage("Could not allocate event.", 
			IFLogMessage::VL_ASSERTION, this, "createThreadEvent"));
		return 0;
	}
	addLocalRef(event);
	return event;
}

bool IFThread::start()
{
	int result = pthread_create(&thread, &threadAttributes, 
		threadFunction, reinterpret_cast<void*>(this));
	if (result != 0)
	{
		ostringstream state;
		state << "Could not create thread (error code: " << result << ").";
		log(IFLogMessage(state.str(), IFLogMessage::VL_ERROR, 
			this, "start"));
		return false;
	}
	runFlag = true;
	initFlag = true;
	IFThreadEvent* event = createThreadEvent();
	event->setType(IFThreadEvent::TYPE_START);
	event->setSource(this);
	signalStart.emit(*event);
	removeLocalRef(event);
	return true;
}

void* IFThread::run()
{
	if (!initFlag)
	{
		log(IFLogMessage("Thread has not been initialized.", 
			IFLogMessage::VL_ERROR, this, "run"));
		return 0;
	}
	shutdownFlag = SHUTDOWN_DISABLED;
	IFThreadEvent* event = createThreadEvent();
	event->setType(IFThreadEvent::TYPE_RUN);
	event->setSource(this);
	void* result = reinterpret_cast<void*>(signalRun.emit(*event));
	runFlag = false;
	removeLocalRef(event);
	return result;;
}

void* IFThread::join()
{
	void* result = 0;
	if (initFlag)
		pthread_join(thread, &result);
	else
		log(IFLogMessage("Thread has not been initialized.", 
			IFLogMessage::VL_ERROR, this, "join"));
	return result;
}

void IFThread::stop()
{
	shutdownFlag = SHUTDOWN_ENABLED;
	IFThreadEvent* event = createThreadEvent();
	event->setType(IFThreadEvent::TYPE_STOP);
	event->setSource(this);
	signalStop.emit(*event);
	removeLocalRef(event);
}

bool IFThread::isRunning() const
{
	// TODO: Implementation.
	return runFlag;
}

void* IFThread::startImpl(void* threadArgs)
{
	IFThread* theThread = reinterpret_cast<IFThread*>(threadArgs);
	return theThread->run();
}

Ionflux::ObjectBase::IFObject* 
IFThread::create(Ionflux::ObjectBase::IFObject* parentObject)
{
	IFThread* newObject = new IFThread();
	if (newObject == 0)
	{
		cerr << IFLogMessage("Could not allocate object instance.", 
			IFLogMessage::VL_ERROR, 0, "IFThread::create") << endl;
		return 0;
	}
	if (parentObject != 0)
		parentObject->addLocalRef(newObject);
	return newObject;
}

Ionflux::ObjectBase::IFObject* IFThread::copy() const
{
	IFThread* newThread = new Ionflux::ObjectBase::IFThread();
	*newThread = *this;
	return newThread;
}

Ionflux::ObjectBase::IFThread& IFThread::operator=(const 
Ionflux::ObjectBase::IFThread& otherThread)
{
	// TODO: Implementation.
	return *this;
}

Ionflux::ObjectBase::IFObject& IFThread::operator=(const 
Ionflux::ObjectBase::IFObject& otherObject)
{
	const IFThread* otherThread = dynamic_cast<const IFThread*>(&otherObject);
	if (otherThread != 0)
		*this = *otherThread;
	else
		cerr << "[IFThread::operator=] ERROR: "
			"Unable to assign object '" << otherObject.getClassName() 
			<< "'." << endl;
	return *this;
}

std::string IFThread::getString() const
{
	// TODO: Implementation.
	return IFObject::getString();
}

void IFThread::sleep(unsigned int sleepSecs)
{
	::sleep(sleepSecs);
}

void IFThread::nanoSleep(unsigned int sleepSecs, unsigned int 
sleepNanoSecs)
{
	timespec sleepTime;
	timespec remainingTime;
	sleepTime.tv_sec = sleepSecs;
	sleepTime.tv_nsec = sleepNanoSecs;
	remainingTime.tv_sec = 0;
	remainingTime.tv_nsec = 0;
	while ((sleepTime.tv_sec != 0)
		|| (sleepTime.tv_nsec != 0))
	{
		::nanosleep(&sleepTime, &remainingTime);
		sleepTime = remainingTime;
	}
}

void IFThread::setThreadFunction(Ionflux::ObjectBase::IFThreadFunction 
newThreadFunction)
{
	threadFunction = newThreadFunction;
}

Ionflux::ObjectBase::IFThreadFunction IFThread::getThreadFunction() const
{
	return threadFunction;
}

void IFThread::setContext(Ionflux::ObjectBase::IFObject* newContext)
{
	context = newContext;
}

Ionflux::ObjectBase::IFObject* IFThread::getContext() const
{
	return context;
}

IFThreadSignal& IFThread::getSignalStart()
{
	return signalStart;
}

Ionflux::ObjectBase::IFSignal* IFThread::getSignalStartWrapper()
{
	if (signalStartWrapper == 0)
	{
		signalStartWrapper = new Ionflux::ObjectBase::IFSignal(
			&signalStart, SIGNAL_TYPE_THREAD, 
			SIGNAL_NAME_START);
		if (signalStartWrapper == 0)
			log(IFLogMessage("Could not allocate signal wrapper.", 
				IFLogMessage::VL_ASSERTION, this, 
				"getSignalStartWrapper"));
		addLocalRef(signalStartWrapper);
	}
	return signalStartWrapper;
}

IFThreadSignal& IFThread::getSignalRun()
{
	return signalRun;
}

Ionflux::ObjectBase::IFSignal* IFThread::getSignalRunWrapper()
{
	if (signalRunWrapper == 0)
	{
		signalRunWrapper = new Ionflux::ObjectBase::IFSignal(
			&signalRun, SIGNAL_TYPE_THREAD, 
			SIGNAL_NAME_RUN);
		if (signalRunWrapper == 0)
			log(IFLogMessage("Could not allocate signal wrapper.", 
				IFLogMessage::VL_ASSERTION, this, 
				"getSignalRunWrapper"));
		addLocalRef(signalRunWrapper);
	}
	return signalRunWrapper;
}

IFThreadSignal& IFThread::getSignalStop()
{
	return signalStop;
}

Ionflux::ObjectBase::IFSignal* IFThread::getSignalStopWrapper()
{
	if (signalStopWrapper == 0)
	{
		signalStopWrapper = new Ionflux::ObjectBase::IFSignal(
			&signalStop, SIGNAL_TYPE_THREAD, 
			SIGNAL_NAME_STOP);
		if (signalStopWrapper == 0)
			log(IFLogMessage("Could not allocate signal wrapper.", 
				IFLogMessage::VL_ASSERTION, this, 
				"getSignalStopWrapper"));
		addLocalRef(signalStopWrapper);
	}
	return signalStopWrapper;
}

}

}

/** \file IFThread.cpp
 * \brief Thread implementation.
 */
