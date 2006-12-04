#ifndef IONFLUX_OBJECT_IFTHREAD
#define IONFLUX_OBJECT_IFTHREAD
/* ==========================================================================
 * Ionflux Object Base System
 * Copyright © 2006 Joern P. Meier
 * mail@ionflux.org
 * --------------------------------------------------------------------------
 * IFThread.hpp                    Thread (header).
 * =========================================================================
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

#include <pthread.h>
#include "ifobject/IFObject.hpp"

// forward declarations for types from the Ionflux Object Base System
namespace Ionflux
{

namespace ObjectBase
{

class IFSignal;

}

}

namespace Ionflux
{

namespace ObjectBase
{

// events used by IFThread
class IFThreadEvent;

typedef void* (*IFThreadFunction)(void*);
typedef sigc::signal<bool, const Ionflux::ObjectBase::IFThreadEvent&> 
IFThreadSignal;

/// Signal connections for IFThreadSignal.
struct IFThreadSignalConnections
{
	/// Signal connection: thread start signal
	sigc::connection signalStartConnection;
	/// Signal connection: thread run signal
	sigc::connection signalRunConnection;
	/// Signal connection: thread stop signal
	sigc::connection signalStopConnection;
};

/// Class information for class IFThread.
class IFThreadClassInfo
: public Ionflux::ObjectBase::IFClassInfo
{
	public:
		/// Constructor.
		IFThreadClassInfo();
		/// Destructor.
		virtual ~IFThreadClassInfo();
};

/** Thread.
 * \ingroup ifobject
 *
 * A thread of program execution.
 */
class IFThread
: public Ionflux::ObjectBase::IFObject
{
	private:
		
	protected:
		/// Thread.
		pthread_t thread;
		/// Thread attributes.
		pthread_attr_t threadAttributes;
		/// Shutdown flag.
		IFAtomic shutdownFlag;
		/// Run flag.
		bool runFlag;
		/// Initialization flag.
		bool initFlag;
		/// The function which is executed within the thread.
		Ionflux::ObjectBase::IFThreadFunction threadFunction;
		/// Context to be associated with the thread.
		Ionflux::ObjectBase::IFObject* context;
		/// Signal: thread start signal.
		IFThreadSignal signalStart;
		/// Signal wrapper: thread start signal.
		Ionflux::ObjectBase::IFSignal* signalStartWrapper;
		/// Signal: thread run signal.
		IFThreadSignal signalRun;
		/// Signal wrapper: thread run signal.
		Ionflux::ObjectBase::IFSignal* signalRunWrapper;
		/// Signal: thread stop signal.
		IFThreadSignal signalStop;
		/// Signal wrapper: thread stop signal.
		Ionflux::ObjectBase::IFSignal* signalStopWrapper;
		
	public:
		/// Shutdown state: disabled.
		static const IFAtomic SHUTDOWN_DISABLED;
		/// Shutdown state: enabled.
		static const IFAtomic SHUTDOWN_ENABLED;
		/// Signal type: thread.
		static const Ionflux::ObjectBase::IFSignalType SIGNAL_TYPE_THREAD;
		/// Signal name: start.
		static const std::string SIGNAL_NAME_START;
		/// Signal name: run.
		static const std::string SIGNAL_NAME_RUN;
		/// Signal name: stop.
		static const std::string SIGNAL_NAME_STOP;
		/// Class information instance.
		static const IFThreadClassInfo iFThreadClassInfo;
		/// Class information.
		static const Ionflux::ObjectBase::IFClassInfo* CLASS_INFO;
		
		/** Constructor.
		 *
		 * Construct new IFThread object.
		 */
		IFThread();
		
		/** Destructor.
		 *
		 * Destruct IFThread object.
		 */
		virtual ~IFThread();
		
		/** Create event: thread.
		 * 
		 * Create and initialize a 'thread' event.
		 * 
		 * \return New event, or 0 if an error occured.
		 */
		IFThreadEvent* createThreadEvent();
		
		/** Start.
		 *
		 * Start the thread and execute the thread function within the thread.
		 * 
		 * \sa startImpl
		 *
		 * \return \c true on success, \c false otherwise.
		 */
		virtual bool start();
		
		/** Run.
		 *
		 * The function doing stuff in this thread. This will invoke the 
		 * handlers for the run signal and return the object returned by one 
		 * of the handlers.
		 * 
		 * \note To change the default behavior when the thread is run, you 
		 * can either override the run() function, or change the thread 
		 * function using setThreadFunction().
		 *
		 * \return Object returned by one of the handlers for the run signal.
		 */
		virtual void* run();
		
		/** Join.
		 *
		 * Join the thread with another thread.
		 *
		 * \return Return value of the thread function.
		 */
		virtual void* join();
		
		/** Stop.
		 *
		 * Stop the thread. Whether this actually does something depends on 
		 * the implementation of the run() function. By default, calling 
		 * stop() will set the shutdown flag to SHUTDOWN_ENABLED and emit the 
		 * stop signal.
		 */
		virtual void stop();
		
		/** Check whether the thread is running.
		 *
		 * Check whether the thread is running
		 *
		 * \return \c true if the thread is running, \c false otherwise.
		 */
		virtual bool isRunning() const;
		
		/** Start implementation.
		 *
		 * This function is the default thread function used by start(). Its 
		 * purpose is to invoke the run() function on the specified thread. 
		 * The actual implementation of the start() function can be changed by
		 * specifying a different thread function.
		 * 
		 * \sa start
		 *
		 * \param threadArgs Thread arguments.
		 *
		 * \return Return value of the thread function.
		 */
		static void* startImpl(void* threadArgs);
		
		/** Create instance.
		 *
		 * Create a new instance of the class. If the optional parent object 
		 * is specified, a local reference for the new object will be added to
		 * the parent object.
		 *
		 * \param parentObject Parent object.
		 *
		 * \return Pointer to the new instance, or 0 if an error occurs.
		 */
		static Ionflux::ObjectBase::IFObject* 
		create(Ionflux::ObjectBase::IFObject* parentObject = 0);
		
		/** Copy.
		 *
		 * Create a copy of the object.
		 *
		 * \return Copy of the object.
		 */
		virtual Ionflux::ObjectBase::IFObject* copy() const;
		
		/** Assignment operator.
		 *
		 * Assignment operator.
		 *
		 * \param otherThread Thread.
		 *
		 * \return The object itself.
		 */
		virtual Ionflux::ObjectBase::IFThread& operator=(const 
		Ionflux::ObjectBase::IFThread& otherThread);
		
		/** Assignment operator.
		 *
		 * Assignment operator.
		 *
		 * \param otherObject Object.
		 *
		 * \return The object itself.
		 */
		virtual Ionflux::ObjectBase::IFObject& operator=(const 
		Ionflux::ObjectBase::IFObject& otherObject);
		
		/** Get string representation.
		 *
		 * Get a string representation of the object
		 *
		 * \return String representation of the object.
		 */
		virtual std::string getString() const;
		
		/** Sleep.
		 *
		 * Do nothing for the specified amount of time
		 *
		 * \param sleepSecs Time in seconds.
		 */
		static void sleep(unsigned int sleepSecs);
		
		/** Sleep (nanosec resolution).
		 *
		 * Do nothing for the specified amount of time.
		 *
		 * \param sleepSecs Time in seconds.
		 * \param sleepNanoSecs Time in nanoseconds.
		 */
		static void nanoSleep(unsigned int sleepSecs, unsigned int 
		sleepNanoSecs);
		
		/** Set the function which is executed within the thread.
		 *
		 * Set new value of the function which is executed within the thread.
		 *
		 * \param newThreadFunction New value of the function which is executed 
		 * within the thread.
		 */
		virtual void setThreadFunction(Ionflux::ObjectBase::IFThreadFunction 
		newThreadFunction);
		
		/** Get the function which is executed within the thread.
		 *
		 * \return Current value of the function which is executed within the 
		 * thread.
		 */
		virtual Ionflux::ObjectBase::IFThreadFunction getThreadFunction() const;
		
		/** Set context to be associated with the thread.
		 *
		 * Set new value of context to be associated with the thread.
		 *
		 * \param newContext New value of context to be associated with the 
		 * thread.
		 */
		virtual void setContext(Ionflux::ObjectBase::IFObject* newContext);
		
		/** Get context to be associated with the thread.
		 *
		 * \return Current value of context to be associated with the thread.
		 */
		virtual Ionflux::ObjectBase::IFObject* getContext() const;
		
		/** Get signal: thread start signal.
		 *
		 * Get the signal for the thread start signal event.
		 *
		 * \return Signal for the thread start signal event.
		 */
		virtual IFThreadSignal& getSignalStart();
		
		/** Get signal wrapper: thread start signal.
		 *
		 * Get the signal for the thread start signal event.
		 *
		 * \return Signal for the thread start signal event.
		 */
		virtual Ionflux::ObjectBase::IFSignal* getSignalStartWrapper();
		
		/** Get signal: thread run signal.
		 *
		 * Get the signal for the thread run signal event.
		 *
		 * \return Signal for the thread run signal event.
		 */
		virtual IFThreadSignal& getSignalRun();
		
		/** Get signal wrapper: thread run signal.
		 *
		 * Get the signal for the thread run signal event.
		 *
		 * \return Signal for the thread run signal event.
		 */
		virtual Ionflux::ObjectBase::IFSignal* getSignalRunWrapper();
		
		/** Get signal: thread stop signal.
		 *
		 * Get the signal for the thread stop signal event.
		 *
		 * \return Signal for the thread stop signal event.
		 */
		virtual IFThreadSignal& getSignalStop();
		
		/** Get signal wrapper: thread stop signal.
		 *
		 * Get the signal for the thread stop signal event.
		 *
		 * \return Signal for the thread stop signal event.
		 */
		virtual Ionflux::ObjectBase::IFSignal* getSignalStopWrapper();
};

}

}

/** \file IFThread.hpp
 * \brief Thread (header).
 */
#endif
