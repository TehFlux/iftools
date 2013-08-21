#ifndef IONFLUX_OBJECT_IFMMEVENT
#define IONFLUX_OBJECT_IFMMEVENT
/* ==========================================================================
 * Ionflux Object Base System
 * Copyright © 2006-2011 Joern P. Meier
 * mail@ionflux.org
 * --------------------------------------------------------------------------
 * IFMMEvent.hpp                   Memory Management Event (header).
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

#include "ifobject/types.hpp"
#include "ifobject/constants.hpp"
#include "IFObject.hpp"

namespace Ionflux
{

namespace ObjectBase
{

/// Class information for class IFMMEvent.
class IFMMEventClassInfo
: public Ionflux::ObjectBase::IFClassInfo
{
	public:
		/// Constructor.
		IFMMEventClassInfo();
		/// Destructor.
		virtual ~IFMMEventClassInfo();
};

/** Memory Management Event.
 * \ingroup ifobject
 *
 * A memory management event.
 */
class IFMMEvent
: public IFObject
{
	private:
		
	protected:
		/// type ID.
		Ionflux::ObjectBase::MMEventTypeID typeID;
		/// object.
		const Ionflux::ObjectBase::IFObject* object;
		/// object reference count.
		unsigned int objectRefCount;
		/// parent object.
		const Ionflux::ObjectBase::IFObject* parentObject;
		
	public:
		/// Event type ID: undefined.
		static const Ionflux::ObjectBase::MMEventTypeID TYPE_UNDEFINED;
		/// Event type ID: create.
		static const Ionflux::ObjectBase::MMEventTypeID TYPE_CREATE;
		/// Event type ID: delete.
		static const Ionflux::ObjectBase::MMEventTypeID TYPE_DELETE;
		/// Event type ID: add reference.
		static const Ionflux::ObjectBase::MMEventTypeID TYPE_ADD_REF;
		/// Event type ID: remove reference.
		static const Ionflux::ObjectBase::MMEventTypeID TYPE_REMOVE_REF;
		/// Event type ID: add local reference.
		static const Ionflux::ObjectBase::MMEventTypeID TYPE_ADD_LOCAL_REF;
		/// Event type ID: remove local reference.
		static const Ionflux::ObjectBase::MMEventTypeID TYPE_REMOVE_LOCAL_REF;
		/// Class information instance.
		static const IFMMEventClassInfo iFMMEventClassInfo;
		/// Class information.
		static const Ionflux::ObjectBase::IFClassInfo* CLASS_INFO;
		
		/** Constructor.
		 *
		 * Construct new IFMMEvent object.
		 */
		IFMMEvent();
		
		/** Constructor.
		 *
		 * Construct new IFMMEvent object.
		 *
		 * \param other Other object.
		 */
		IFMMEvent(const Ionflux::ObjectBase::IFMMEvent& other);
		
		/** Constructor.
		 *
		 * Construct new IFMMEvent object.
		 *
		 * \param initTypeID type ID.
		 * \param initObject object.
		 * \param initObjectRefCount object reference count.
		 * \param initParentObject parent object.
		 */
		IFMMEvent(Ionflux::ObjectBase::MMEventTypeID initTypeID, const 
		Ionflux::ObjectBase::IFObject* initObject, unsigned int 
		initObjectRefCount = 0, const Ionflux::ObjectBase::IFObject* 
		initParentObject = 0);
		
		/** Destructor.
		 *
		 * Destruct IFMMEvent object.
		 */
		virtual ~IFMMEvent();
		
		/** Comparison operator: equality.
		 *
		 * Compare equality.
		 *
		 * \param other value.
		 *
		 * \return Result of the comparison.
		 */
		virtual bool operator==(const Ionflux::ObjectBase::IFMMEvent& other) 
		const;
		
		/** Comparison operator: inequality.
		 *
		 * Compare inequality.
		 *
		 * \param other value.
		 *
		 * \return Result of the comparison.
		 */
		virtual bool operator!=(const Ionflux::ObjectBase::IFMMEvent& other) 
		const;
		
		/** Get string representation of value.
		 *
		 * Get a string representation of the value of the object.
		 *
		 * \return String representation.
		 */
		virtual std::string getValueString() const;
		
		/** Assignment operator.
		 *
		 * Assign an object.
		 *
		 * \param other Other object.
		 *
		 * \return The object itself.
		 */
		virtual Ionflux::ObjectBase::IFMMEvent& operator=(const 
		Ionflux::ObjectBase::IFMMEvent& other);
		
		/** Copy.
		 *
		 * Create a copy of the object.
		 *
		 * \return Newly allocated copy of the object.
		 */
		virtual Ionflux::ObjectBase::IFMMEvent* copy() const;
		
		/** Upcast.
		 *
		 * Cast an IFObject to the most specific type.
		 *
		 * \param other Other object.
		 *
		 * \return The more specific object, or 0 if the cast failed.
		 */
		static Ionflux::ObjectBase::IFMMEvent* 
		upcast(Ionflux::ObjectBase::IFObject* other);
		
		/** Create instance.
		 *
		 * Create a new instance of the class. If the optional parent object 
		 * is specified, a local reference for the new object will be added 
		 * to the parent object.
		 *
		 * \param parentObject Parent object.
		 *
		 * \return Pointer to the new instance.
		 */
		static Ionflux::ObjectBase::IFMMEvent* 
		create(Ionflux::ObjectBase::IFObject* parentObject = 0);
        
		/** Create instance.
		 *
		 * Create a new IFMMEvent object.
		 *
		 * \param initTypeID type ID.
		 * \param initObject object.
		 * \param initObjectRefCount object reference count.
		 * \param initParentObject parent object.
		 * \param parentObject Parent object.
		 */
		static Ionflux::ObjectBase::IFMMEvent* 
		create(Ionflux::ObjectBase::MMEventTypeID initTypeID, const 
		Ionflux::ObjectBase::IFObject* initObject, unsigned int 
		initObjectRefCount = 0, const Ionflux::ObjectBase::IFObject* 
		initParentObject = 0, Ionflux::ObjectBase::IFObject* parentObject = 0);
		
		/** Get type ID.
		 *
		 * \return Current value of type ID.
		 */
		virtual Ionflux::ObjectBase::MMEventTypeID getTypeID() const;
		
		/** Set type ID.
		 *
		 * Set new value of type ID.
		 *
		 * \param newTypeID New value of type ID.
		 */
		virtual void setTypeID(Ionflux::ObjectBase::MMEventTypeID newTypeID);
		
		/** Get object.
		 *
		 * \return Current value of object.
		 */
		virtual const Ionflux::ObjectBase::IFObject* getObject() const;
		
		/** Set object.
		 *
		 * Set new value of object.
		 *
		 * \param newObject New value of object.
		 */
		virtual void setObject(const Ionflux::ObjectBase::IFObject* newObject);
		
		/** Get object reference count.
		 *
		 * \return Current value of object reference count.
		 */
		virtual unsigned int getObjectRefCount() const;
		
		/** Set object reference count.
		 *
		 * Set new value of object reference count.
		 *
		 * \param newObjectRefCount New value of object reference count.
		 */
		virtual void setObjectRefCount(unsigned int newObjectRefCount);
		
		/** Get parent object.
		 *
		 * \return Current value of parent object.
		 */
		virtual const Ionflux::ObjectBase::IFObject* getParentObject() const;
		
		/** Set parent object.
		 *
		 * Set new value of parent object.
		 *
		 * \param newParentObject New value of parent object.
		 */
		virtual void setParentObject(const Ionflux::ObjectBase::IFObject* 
		newParentObject);
};

}

}

/** \file IFMMEvent.hpp
 * \brief Memory Management Event (header).
 */
#endif
