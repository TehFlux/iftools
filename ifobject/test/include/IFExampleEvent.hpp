#ifndef IONFLUX_EXAMPLE_IFEXAMPLEEVENT
#define IONFLUX_EXAMPLE_IFEXAMPLEEVENT
/* ==========================================================================
 * Ionflux Object Base System
 * Copyright © 2006 Joern P. Meier
 * mail@ionflux.org
 * --------------------------------------------------------------------------
 * IFExampleEvent.hpp              Event class for the 'example' event. 
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

#include "ifobject/IFObject.hpp"

namespace Ionflux
{

namespace Example
{

class IFExampleClass;

/// Class information for class IFExampleEvent.
class IFExampleEventClassInfo
: public Ionflux::ObjectBase::IFClassInfo
{
	public:
		/// Constructor.
		IFExampleEventClassInfo();
		/// Destructor.
		virtual ~IFExampleEventClassInfo();
};

/** Example event.
 * \ingroup ifobject
 *
 * Event class for the 'example' event.
 */
class IFExampleEvent
: public Ionflux::ObjectBase::IFObject
{
	private:
		
	protected:
		/// event type.
		int type;
		/// event source.
		Ionflux::Example::IFExampleClass* source;
		
	public:
		/// event type: first.
		static const int TYPE_FIRST;
		/// event type: second.
		static const int TYPE_SECOND;
		/// Class information instance.
		static const IFExampleEventClassInfo iFExampleEventClassInfo;
		/// Class information.
		static const Ionflux::ObjectBase::IFClassInfo* CLASS_INFO;
		
		/** Constructor.
		 *
		 * Construct new IFExampleEvent object.
		 */
		IFExampleEvent();
		
		/** Destructor.
		 *
		 * Destruct IFExampleEvent object.
		 */
		virtual ~IFExampleEvent();
		
		/** Set event type.
		 *
		 * Set new value of event type.
		 *
		 * \param newType New value of event type.
		 */
		virtual void setType(int newType);
		
		/** Get event type.
		 *
		 * \return Current value of event type.
		 */
		virtual int getType() const;
		
		/** Set event source.
		 *
		 * Set new value of event source.
		 *
		 * \param newSource New value of event source.
		 */
		virtual void setSource(Ionflux::Example::IFExampleClass* newSource);
		
		/** Get event source.
		 *
		 * \return Current value of event source.
		 */
		virtual Ionflux::Example::IFExampleClass* getSource() const;
};

}

}

/** \file IFExampleEvent.hpp
 * \brief Event class for the 'example' event. (header).
 */
#endif
