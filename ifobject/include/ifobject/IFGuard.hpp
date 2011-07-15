#ifndef IONFLUX_OBJECT_IFGUARD
#define IONFLUX_OBJECT_IFGUARD
/* ==========================================================================
 * Ionflux Object Base System
 * Copyright © 2006-2011 Joern P. Meier
 * mail@ionflux.org
 * --------------------------------------------------------------------------
 * IFGuard.hpp                     Guard (header).
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

namespace Ionflux
{

namespace ObjectBase
{

/// Class information for class IFGuard.
class IFGuardClassInfo
: public Ionflux::ObjectBase::IFClassInfo
{
	public:
		/// Constructor.
		IFGuardClassInfo();
		/// Destructor.
		virtual ~IFGuardClassInfo();
};

/** Guard.
 * \ingroup ifobject
 *
 * A guard object which will lock a mutex on construction and release it on
 * destruction. Locking and unlocking is also possible using the accessors.
 */
class IFGuard
: public Ionflux::ObjectBase::IFObject
{
	private:
		
	protected:
		/// Mutex.
		Ionflux::ObjectBase::IFMutex* mutex;
		
	public:
		/// Class information instance.
		static const IFGuardClassInfo iFGuardClassInfo;
		/// Class information.
		static const Ionflux::ObjectBase::IFClassInfo* CLASS_INFO;
		
		/** Constructor.
		 *
		 * Construct new IFGuard object.
		 */
		IFGuard();
		
		/** Constructor.
		 *
		 * Construct new IFGuard object.
		 *
		 * \param initMutex Initial mutex.
		 */
		IFGuard(Ionflux::ObjectBase::IFMutex* initMutex);
		
		/** Destructor.
		 *
		 * Destruct IFGuard object.
		 */
		virtual ~IFGuard();
		
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
		 * \param otherGuard Guard.
		 *
		 * \return The object itself.
		 */
		virtual Ionflux::ObjectBase::IFGuard& operator=(const 
		Ionflux::ObjectBase::IFGuard& otherGuard);
		
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
		
		/** Get mutex.
		 *
		 * \return Current value of mutex.
		 */
		virtual Ionflux::ObjectBase::IFMutex* getMutex() const;
		
		/** Set mutex.
		 *
		 * Set new value of mutex.
		 *
		 * \param newMutex New value of mutex.
		 */
		virtual void setMutex(Ionflux::ObjectBase::IFMutex* newMutex);
};

}

}

/** \file IFGuard.hpp
 * \brief Guard (header).
 */
#endif
