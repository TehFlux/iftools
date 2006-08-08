#ifndef IONFLUX_TOOLS_MANAGEDOBJECT
#define IONFLUX_TOOLS_MANAGEDOBJECT
/* ==========================================================================
 * Ionflux Tools
 * Copyright (c) 2005 Joern P. Meier
 * mail@ionflux.org
 * --------------------------------------------------------------------------
 * ManagedObject.hpp                 Managed object.
 * ==========================================================================
 * 
 * This file is part of Ionflux Tools.
 * 
 * Ionflux Tools is free software; you can redistribute it and/or modify it
 * under the terms of the GNU General Public License as published by the 
 * Free Software Foundation; either version 2 of the License, or (at your 
 * option) any later version.
 * 
 * Ionflux Tools is distributed in the hope that it will be useful, but 
 * WITHOUT ANY WARRANTY; without even the implied warranty of 
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU 
 * General Public License for more details.
 * 
 * You should have received a copy of the GNU General Public License along 
 * with Ionflux Tools; if not, write to the Free Software Foundation, Inc.,
 * 59 Temple Place, Suite 330, Boston, MA 02111-1307 USA
 * 
 * ========================================================================== */

#include <string>
#include <iostream>
#include "ionflux/Object.hpp"

namespace Ionflux
{

namespace Tools
{

/** \addtogroup memmgmt Memory management
 *
 * Tools for automatic management of memory allocated for objects.
 *
 * @{
 */

/// Class information for class ManagedObject.
class ManagedObjectClassInfo
: public ClassInfo
{
	public:
		/// Constructor.
		ManagedObjectClassInfo();
		/// Destructor.
		virtual ~ManagedObjectClassInfo() { };
};

/** Base class for managed objects.
 * \ingroup general
 *
 * This class provides a base class for objects the allocated memory of 
 * which is managed by another class, called the 'owner' or 'parent' of the
 * object. Making an object managed by another improves the chances that it
 * is properly deleted at the end of its lifetime. This class also provides
 * a reference counting facility that may be used along with or 
 * independently of the memory management flag.
 * 
 * \note Any entity that references an object is also responsible for 
 * removing the references after it has finished using the referenced 
 * object. A managed object will usually not be deleted by its parent 
 * unless its reference count is zero. A parent object must maintain its 
 * own list of managed objects, since the managed object itself does not 
 * keep track of its parents or referencing objects. Generally, it should 
 * be possible to delete an object with a reference count of zero. This 
 * means a parent object should always reference an object on registration 
 * in its list of managed objects. Any managed object should be managed by 
 * only one parent object. If it is not known precisely which parent object
 * should be responsible for destroying a managed object, reference 
 * counting should be used instead.
 */
class ManagedObject
: public Ionflux::Tools::Object
{
	private:
		
	protected:
		/// Memory management flag.
		bool managed;
		/// Reference count.
		unsigned int refCount;
		
	public:
		/// Class information instance.
		static const ManagedObjectClassInfo managedObjectClassInfo;
		/// Class information.
		static const ClassInfo* CLASS_INFO;
		
		/** Constructor.
		 *
		 * Construct new ManagedObject object.
		 */
		ManagedObject();
		
		/** Destructor.
		 *
		 * Destruct ManagedObject object.
		 */
		virtual ~ManagedObject();
		
		/** Set memory management flag.
		 *
		 * This controls whether memory allocated for this object should be 
		 * managed by its parent object.
		 * 
		 * \warning If this function returns \c false, no attempts should be 
		 * made by the caller to manage the object. A return value of \c false
		 * indicates that this object is managed by another parent object (and
		 * thus probably indicates a bug in the calling code). The management 
		 * flag should not be used at all if there are doubts as to which 
		 * parent object should have the sole responsibility for deleting a 
		 * managed object. If the parent object cannot be clearly determined, 
		 * reference counting should be used instead.
		 *
		 * \param newManage Whether memory allocated for this object should be 
		 * managed by ist parent object.
		 *
		 * \return \c true if this object may be managed by the caller, \c false 
		 * otherwise.
		 */
		virtual bool setManaged(bool newManage);
		
		/** Get memory management flag.
		 *
		 * Get the memory management flag of this object.
		 *
		 * \return \c true if this object is managed by its parent, \c false 
		 * otherwise.
		 */
		virtual bool isManaged();
		
		/** Increase reference count.
		 *
		 * Increase the reference count.
		 * 
		 * \warning A managed object may not be properly deleted by its parent
		 * if references are not removed after the referencing entity has 
		 * finished using the object.
		 *
		 * \return Current reference count after the reference operation.
		 */
		virtual unsigned int ref();
		
		/** Decrease reference count.
		 *
		 * Decrease the reference count.
		 *
		 * \return Current reference count after the reference operation.
		 */
		virtual unsigned int unref();
		
		/** Get reference count.
		 *
		 * Get the number of references (reference count).
		 *
		 * \return Current reference count.
		 */
		virtual unsigned int getRefCount();
};

/// @}

}

}

/** \file ManagedObject.hpp
 * \brief Managed object header.
 */
#endif
