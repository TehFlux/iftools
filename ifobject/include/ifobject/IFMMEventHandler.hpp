#ifndef IONFLUX_OBJECT_IFMMEVENTHANDLER
#define IONFLUX_OBJECT_IFMMEVENTHANDLER
/* ==========================================================================
 * Ionflux Object Base System
 * Copyright © 2006-2011 Joern P. Meier
 * mail@ionflux.org
 * --------------------------------------------------------------------------
 * IFMMEventHandler.hpp            Memory management event handler 
 * (header).
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

class IFMMEvent;

/// Class information for class IFMMEventHandler.
class IFMMEventHandlerClassInfo
: public Ionflux::ObjectBase::IFClassInfo
{
	public:
		/// Constructor.
		IFMMEventHandlerClassInfo();
		/// Destructor.
		virtual ~IFMMEventHandlerClassInfo();
};

/** Memory management event handler.
 * \ingroup ifobject
 *
 * A handler for memory management events.
 */
class IFMMEventHandler
: public IFObject
{
	private:
		
	protected:
		/// Global event handler instance.
		static Ionflux::ObjectBase::IFMMEventHandler* instance;
		/// redirection target.
		Ionflux::ObjectBase::IFMMEventHandler* target;
		/// log file name.
		std::string logFileName;
		/// silent flag.
		bool silentFlag;
		
	public:
		/// Class information instance.
		static const IFMMEventHandlerClassInfo iFMMEventHandlerClassInfo;
		/// Class information.
		static const Ionflux::ObjectBase::IFClassInfo* CLASS_INFO;
		
		/** Constructor.
		 *
		 * Construct new IFMMEventHandler object.
		 */
		IFMMEventHandler();
		
		/** Constructor.
		 *
		 * Construct new IFMMEventHandler object.
		 *
		 * \param other Other object.
		 */
		IFMMEventHandler(const Ionflux::ObjectBase::IFMMEventHandler& other);
		
		/** Constructor.
		 *
		 * Construct new IFMMEventHandler object.
		 *
		 * \param initTarget target.
		 * \param initLogFileName log file name.
		 * \param initSilentFlag silent flag.
		 */
		IFMMEventHandler(Ionflux::ObjectBase::IFMMEventHandler* initTarget, const
		std::string& initLogFileName = "", bool initSilentFlag = true);
		
		/** Destructor.
		 *
		 * Destruct IFMMEventHandler object.
		 */
		virtual ~IFMMEventHandler();
		
		/** Handle memory management event.
		 *
		 * Handle memory management event.
		 *
		 * \param event event.
		 */
		virtual void handleMMEvent(const Ionflux::ObjectBase::IFMMEvent& event) 
		const;
		
		/** Get string representation of value.
		 *
		 * Get a string representation of the value of the object.
		 *
		 * \return String representation.
		 */
		virtual std::string getValueString() const;
		
		/** Get global event handler instance.
		 *
		 * Get the global event handler instance.
		 * 
		 * \sa cleanup()
		 *
		 * \return Global context instance.
		 */
		static Ionflux::ObjectBase::IFMMEventHandler* getInstance();
		
		/** Cleanup global event handler instance.
		 *
		 * Clean up the global event handler instance. This should be called 
		 * to clean up the global vent handler instance that can be obtained 
		 * by getInstance() before exiting the application.
		 * 
		 * \sa getInstance()
		 */
		static void cleanup();
		
		/** Assignment operator.
		 *
		 * Assign an object.
		 *
		 * \param other Other object.
		 *
		 * \return The object itself.
		 */
		virtual Ionflux::ObjectBase::IFMMEventHandler& operator=(const 
		Ionflux::ObjectBase::IFMMEventHandler& other);
		
		/** Copy.
		 *
		 * Create a copy of the object.
		 *
		 * \return Newly allocated copy of the object.
		 */
		virtual Ionflux::ObjectBase::IFMMEventHandler* copy() const;
		
		/** Upcast.
		 *
		 * Cast an IFObject to the most specific type.
		 *
		 * \param other Other object.
		 *
		 * \return The more specific object, or 0 if the cast failed.
		 */
		static Ionflux::ObjectBase::IFMMEventHandler* 
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
		static Ionflux::ObjectBase::IFMMEventHandler* 
		create(Ionflux::ObjectBase::IFObject* parentObject = 0);
        
		/** Create instance.
		 *
		 * Create a new IFMMEventHandler object.
		 *
		 * \param initTarget target.
		 * \param initLogFileName log file name.
		 * \param initSilentFlag silent flag.
		 * \param parentObject Parent object.
		 */
		static Ionflux::ObjectBase::IFMMEventHandler* 
		create(Ionflux::ObjectBase::IFMMEventHandler* initTarget, const 
		std::string& initLogFileName = "", bool initSilentFlag = true, 
		Ionflux::ObjectBase::IFObject* parentObject = 0);
		
		/** Get redirection target.
		 *
		 * \return Current value of redirection target.
		 */
		virtual Ionflux::ObjectBase::IFMMEventHandler* getTarget() const;
		
		/** Set redirection target.
		 *
		 * Set new value of redirection target.
		 *
		 * \param newTarget New value of redirection target.
		 */
		virtual void setTarget(Ionflux::ObjectBase::IFMMEventHandler* newTarget);
		
		/** Get log file name.
		 *
		 * \return Current value of log file name.
		 */
		virtual std::string getLogFileName() const;
		
		/** Set log file name.
		 *
		 * Set new value of log file name.
		 *
		 * \param newLogFileName New value of log file name.
		 */
		virtual void setLogFileName(const std::string& newLogFileName);
		
		/** Get silent flag.
		 *
		 * \return Current value of silent flag.
		 */
		virtual bool getSilentFlag() const;
		
		/** Set silent flag.
		 *
		 * Set new value of silent flag.
		 *
		 * \param newSilentFlag New value of silent flag.
		 */
		virtual void setSilentFlag(bool newSilentFlag);
};

}

}

/** \file IFMMEventHandler.hpp
 * \brief Memory management event handler (header).
 */
#endif
