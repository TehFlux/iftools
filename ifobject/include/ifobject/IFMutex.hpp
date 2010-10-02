#ifndef IONFLUX_OBJECT_IFMUTEX
#define IONFLUX_OBJECT_IFMUTEX
/* ==========================================================================
 * Ionflux Object Base System
 * Copyright © 2006 Joern P. Meier
 * mail@ionflux.org
 * --------------------------------------------------------------------------
 * IFMutex.hpp                     Mutex (header).
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

#include <pthread.h>
#include "ifobject/IFObject.hpp"

namespace Ionflux
{

namespace ObjectBase
{

/// Class information for class IFMutex.
class IFMutexClassInfo
: public Ionflux::ObjectBase::IFClassInfo
{
	public:
		/// Constructor.
		IFMutexClassInfo();
		/// Destructor.
		virtual ~IFMutexClassInfo();
};

/** Mutex.
 * \ingroup ifobject
 *
 * A mutual exclusion for use with threads.
 */
class IFMutex
: public Ionflux::ObjectBase::IFObject
{
	private:
		
	protected:
		/// Mutex.
		pthread_mutex_t mutex;
		/// Attributes.
		pthread_mutexattr_t attributes;
		/// Type.
		Ionflux::ObjectBase::IFMutexType type;
		
	public:
		/// Mutex type: default.
		static const Ionflux::ObjectBase::IFMutexType TYPE_DEFAULT;
		/// Mutex type: normal.
		static const Ionflux::ObjectBase::IFMutexType TYPE_NORMAL;
		/// Mutex type: errorcheck.
		static const Ionflux::ObjectBase::IFMutexType TYPE_ERRORCHECK;
		/// Mutex type: recursive.
		static const Ionflux::ObjectBase::IFMutexType TYPE_RECURSIVE;
		/// Class information instance.
		static const IFMutexClassInfo iFMutexClassInfo;
		/// Class information.
		static const Ionflux::ObjectBase::IFClassInfo* CLASS_INFO;
		
		/** Constructor.
		 *
		 * Construct new IFMutex object.
		 */
		IFMutex();
		
		/** Constructor.
		 *
		 * Construct new IFMutex object.
		 *
		 * \param initType Initial type.
		 */
		IFMutex(Ionflux::ObjectBase::IFMutexType initType);
		
		/** Destructor.
		 *
		 * Destruct IFMutex object.
		 */
		virtual ~IFMutex();
		
		/** Lock.
		 *
		 * Lock the mutex. This function blocks until the mutex can be locked.
		 *
		 * \return \c true on success, \c false otherwise.
		 */
		virtual bool lock();
		
		/** Try lock.
		 *
		 * Try to lock the mutex. This function returns immediately if the 
		 * mutex cannot be locked.
		 *
		 * \return \c true on success, \c false otherwise.
		 */
		virtual bool tryLock();
		
		/** Unlock.
		 *
		 * Unlock the mutex.
		 *
		 * \return \c true on success, \c false otherwise.
		 */
		virtual bool unlock();
		
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
		 * \param otherMutex Mutex.
		 *
		 * \return The object itself.
		 */
		virtual Ionflux::ObjectBase::IFMutex& operator=(const 
		Ionflux::ObjectBase::IFMutex& otherMutex);
		
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
		
		/** Get type.
		 *
		 * \return Current value of type.
		 */
		virtual Ionflux::ObjectBase::IFMutexType getType() const;
};

}

}

/** \file IFMutex.hpp
 * \brief Mutex (header).
 */
#endif
