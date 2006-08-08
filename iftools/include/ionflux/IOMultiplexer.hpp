#ifndef IONFLUX_TOOLS_IOMULTIPLEXER
#define IONFLUX_TOOLS_IOMULTIPLEXER
/* ==========================================================================
 * Ionflux Tools
 * Copyright (c) 2004 Joern P. Meier
 * mail@ionflux.org
 * --------------------------------------------------------------------------
 * IOMultiplexer.hpp                   IO event multiplexer (abstract class).
 * ==========================================================================
 * 
 * This file is part of Ionflux Tools.
 * 
 * Ionflux Tools is free software; you can redistribute it and/or modify it 
 * under the terms of the GNU General Public License as published by the Free
 * Software Foundation; either version 2 of the License, or (at  your option)
 * any later version.
 * 
 * Ionflux Tools is distributed in the hope that it will be useful, but 
 * WITHOUT ANY WARRANTY; without even the implied warranty of MERCHANTABILITY
 * or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU General Public License
 * for more details.
 * 
 * You should have received a copy of the GNU General Public License
 * along with Ionflux Tools; if not, write to the Free Software Foundation, 
 * Inc., 59 Temple Place, Suite 330, Boston, MA 02111-1307 USA
 * 
 * ========================================================================== */

#include <string>
#include <iostream>
#include <sstream>
#include <vector>
#include <signal.h>
#include "ionflux/IOHandler.hpp"
#include "ionflux/Reporter.hpp"

namespace Ionflux
{

namespace Tools
{

/** \addtogroup iomplex I/O Multiplexing
 *
 * I/O multiplexing facilities.
 *
 * @{
 */

/// IO event information.
struct IOEventInfo
{
	/// IO event.
	IOEvent event;
	/// IO handler.
	IOHandler *handler;
};

/** IO event multiplexer.
 *
 * A multiplexer for IO events. If a specified event is ready to be processed, 
 * the IO multiplexer notifies the associated IO handler. For example, an 
 * IOHandler may be called if a file descriptor is ready for reading.
 *
 * To register an event, you set a file descriptor and a mask of event types 
 * which the IO handler should be notified of. You then call 
 * IOMultiplexer::registerEvent() with a pointer to an IOHandler and the 
 * event object. To remove (unregister) an event, call 
 * IOMultiplexer::removeEvent() with the same handler and event object.
 */
class IOMultiplexer
{
	protected:
		/// IO multiplexer type ID.
		int type;
		
	public:
		/// IO multiplexer type ID: Undefined.
		static const int IOM_TYPE_UNDEFINED;
		/// IO multiplexer type ID: Select multiplexer.
		static const int IOM_TYPE_SELECT;
		/// IO multiplexer type ID: Glib multiplexer.
		static const int IOM_TYPE_GLIB;
		
		/** Constructor.
		 *
		 * Construct new IOMultiplexer object.
		 */
		IOMultiplexer();
		
		/** Destructor.
		 *
		 * Destruct IOMultiplexer object.
		 */
		virtual ~IOMultiplexer() { };
		
		/** Register IO event.
		 *
		 * Register an IO event to be handled by the multiplexer.
		 *
		 * \param handler IO handler to be notified if the event occurs.
		 * \param event IO event.
		 */
		virtual void registerEvent(IOHandler *handler, IOEvent event) = 0;
		
		/** Remove IO event.
		 *
		 * Remove an IO event from the set of events handled by the multiplexer.
		 *
		 * \param handler IO handler for which the event has been registered.
		 * \param event IO event.
		 */
		virtual void removeEvent(IOHandler *handler, IOEvent event) = 0;
		
		/** Main loop.
		 *
		 * Start the main loop to watch for registered events.
		 */
		virtual void run() = 0;
		
		/** Exit main loop.
		 *
		 * Call this function to exit from the main loop.
		 */
		virtual void quit() = 0;
		
		/** Get running state.
		 *
		 * \return \c true if the main loop is running, \c false otherwise.
		 */
		virtual bool isRunning() = 0;
		
		/** Get type.
		 *
		 * Returns the IO multiplexer type ID.
		 *
		 * \note The type ID may be used by applications to improve behaviour 
		 * based on the type of multiplexer used, but each application should 
		 * be able to handle any IO multiplexer type gracefully, regardless of 
		 * whether its ID is recognized or not.
		 *
		 * \return The type ID of the IO multiplexer.
		 */
		virtual int getType();
		
		/** Shutdown handler.
		 *
		 * Signal handler for signals that will cause the main loop to exit.
		 *
		 * \param signum Signal.
		 */
		static void shutdownHandler(int signum);
		
		/** Get Console output/logging facility.
		 *
		 * \return The console output/logging facility used by this object.
		 */
		virtual Reporter &getLog() = 0;
};

/// @}

}

}

/** \file IOMultiplexer.hpp
 * \brief IO event multiplexer (abstract class) header.
 */
#endif
