#ifndef IONFLUX_OBJECT_IFOBJECTEVENT
#define IONFLUX_OBJECT_IFOBJECTEVENT
/* ==========================================================================
 * Ionflux Object Base System
 * Copyright © 2006 Joern P. Meier
 * mail@ionflux.org
 * --------------------------------------------------------------------------
 * IFObjectEvent.hpp               Event class for the 'object' event. 
 * (header).
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

#include "ifobject/types.hpp"
#include "ifobject/IFObject.hpp"

namespace Ionflux
{

namespace ObjectBase
{

class IFObject;

/// Class information for class IFObjectEvent.
class IFObjectEventClassInfo
: public Ionflux::ObjectBase::IFClassInfo
{
	public:
		/// Constructor.
		IFObjectEventClassInfo();
		/// Destructor.
		virtual ~IFObjectEventClassInfo() { };
};

/** Object event.
 * \ingroup ifobject
 *
 * Event class for the 'object' event.
 */
class IFObjectEvent
: public Ionflux::ObjectBase::IFObject
{
	private:
		
	protected:
		/// event type.
		Ionflux::ObjectBase::IFEventType type;
		/// event source.
		Ionflux::ObjectBase::IFObject* source;
		/// old ID number.
		Ionflux::ObjectBase::IFIDNum oldIDNum;
		/// new ID number.
		Ionflux::ObjectBase::IFIDNum newIDNum;
		/// old ID.
		Ionflux::ObjectBase::IFObjectID oldID;
		/// new ID.
		Ionflux::ObjectBase::IFObjectID newID;
		
	public:
		/// event type: object changed.
		static const Ionflux::ObjectBase::IFEventType TYPE_OBJECT_CHANGED;
		/// event type: ID number changed.
		static const Ionflux::ObjectBase::IFEventType TYPE_ID_NUM_CHANGED;
		/// event type: ID changed.
		static const Ionflux::ObjectBase::IFEventType TYPE_ID_CHANGED;
		
		/** Constructor.
		 *
		 * Construct new IFObjectEvent object.
		 */
		IFObjectEvent();
		
		/** Destructor.
		 *
		 * Destruct IFObjectEvent object.
		 */
		virtual ~IFObjectEvent();
		
		/** Set event type.
		 *
		 * Set new value of event type.
		 *
		 * \param newType New value of event type.
		 */
		virtual void setType(Ionflux::ObjectBase::IFEventType newType);
		
		/** Get event type.
		 *
		 * \return Current value of event type.
		 */
		virtual Ionflux::ObjectBase::IFEventType getType() const;
		
		/** Set event source.
		 *
		 * Set new value of event source.
		 *
		 * \param newSource New value of event source.
		 */
		virtual void setSource(Ionflux::ObjectBase::IFObject* newSource);
		
		/** Get event source.
		 *
		 * \return Current value of event source.
		 */
		virtual Ionflux::ObjectBase::IFObject* getSource() const;
		
		/** Set old ID number.
		 *
		 * Set new value of old ID number.
		 *
		 * \param newOldIDNum New value of old ID number.
		 */
		virtual void setOldIDNum(Ionflux::ObjectBase::IFIDNum newOldIDNum);
		
		/** Get old ID number.
		 *
		 * \return Current value of old ID number.
		 */
		virtual Ionflux::ObjectBase::IFIDNum getOldIDNum() const;
		
		/** Set new ID number.
		 *
		 * Set new value of new ID number.
		 *
		 * \param newNewIDNum New value of new ID number.
		 */
		virtual void setNewIDNum(Ionflux::ObjectBase::IFIDNum newNewIDNum);
		
		/** Get new ID number.
		 *
		 * \return Current value of new ID number.
		 */
		virtual Ionflux::ObjectBase::IFIDNum getNewIDNum() const;
		
		/** Set old ID.
		 *
		 * Set new value of old ID.
		 *
		 * \param newOldID New value of old ID.
		 */
		virtual void setOldID(const Ionflux::ObjectBase::IFObjectID& newOldID);
		
		/** Get old ID.
		 *
		 * \return Current value of old ID.
		 */
		virtual Ionflux::ObjectBase::IFObjectID getOldID() const;
		
		/** Set new ID.
		 *
		 * Set new value of new ID.
		 *
		 * \param newNewID New value of new ID.
		 */
		virtual void setNewID(const Ionflux::ObjectBase::IFObjectID& newNewID);
		
		/** Get new ID.
		 *
		 * \return Current value of new ID.
		 */
		virtual Ionflux::ObjectBase::IFObjectID getNewID() const;
};

}

}

/** \file IFObjectEvent.hpp
 * \brief Event class for the 'object' event. (header).
 */
#endif
