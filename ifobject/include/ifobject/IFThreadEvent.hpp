#ifndef IONFLUX_OBJECT_IFTHREADEVENT
#define IONFLUX_OBJECT_IFTHREADEVENT
/* ==========================================================================
 * Ionflux Object Base System
 * Copyright © 2006 Joern P. Meier
 * mail@ionflux.org
 * --------------------------------------------------------------------------
 * IFThreadEvent.hpp               Event class for the 'thread' event. 
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

class IFThread;

/// Class information for class IFThreadEvent.
class IFThreadEventClassInfo
: public Ionflux::ObjectBase::IFClassInfo
{
	public:
		/// Constructor.
		IFThreadEventClassInfo();
		/// Destructor.
		virtual ~IFThreadEventClassInfo() { };
};

/** Thread event.
 * \ingroup ifobject
 *
 * Event class for the 'thread' event.
 */
class IFThreadEvent
: public Ionflux::ObjectBase::IFObject
{
	private:
		
	protected:
		/// event type.
		Ionflux::ObjectBase::IFEventType type;
		/// event source.
		Ionflux::ObjectBase::IFThread* source;
		
	public:
		/// event type: undefined.
		static const Ionflux::ObjectBase::IFEventType TYPE_UNDEFINED;
		/// event type: start.
		static const Ionflux::ObjectBase::IFEventType TYPE_START;
		/// event type: run.
		static const Ionflux::ObjectBase::IFEventType TYPE_RUN;
		/// event type: stop.
		static const Ionflux::ObjectBase::IFEventType TYPE_STOP;
		/// Class information instance.
		static const IFThreadEventClassInfo iFThreadEventClassInfo;
		/// Class information.
		static const Ionflux::ObjectBase::IFClassInfo* CLASS_INFO;
		
		/** Constructor.
		 *
		 * Construct new IFThreadEvent object.
		 */
		IFThreadEvent();
		
		/** Destructor.
		 *
		 * Destruct IFThreadEvent object.
		 */
		virtual ~IFThreadEvent();
		
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
		virtual void setSource(Ionflux::ObjectBase::IFThread* newSource);
		
		/** Get event source.
		 *
		 * \return Current value of event source.
		 */
		virtual Ionflux::ObjectBase::IFThread* getSource() const;
};

}

}

/** \file IFThreadEvent.hpp
 * \brief Event class for the 'thread' event. (header).
 */
#endif
