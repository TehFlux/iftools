#ifndef IONFLUX_TOOLS_SELECTMULTIPLEXER
#define IONFLUX_TOOLS_SELECTMULTIPLEXER
/* ==========================================================================
 * Ionflux Tools
 * Copyright (c) 2004 Joern P. Meier
 * mail@ionflux.org
 * --------------------------------------------------------------------------
 * SelectMultiplexer.hpp              Select based IO event multiplexer.
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
#include "ionflux/IOMultiplexer.hpp"
#include "ionflux/FDSet.hpp"

namespace Ionflux
{

namespace Tools
{

/** Select based IO event multiplexer.
 * \ingroup iomplex
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
 *
 * \note The SelectMultiplexer uses the select() method as its underlying IO 
 * multiplexing facility.
 */
class SelectMultiplexer
: public IOMultiplexer
{
	protected:
		/// Shutdown flag.
		static sig_atomic_t shutdown;
		/// Console output/logging.
		Ionflux::Tools::Reporter log;
		/// Vector of registered IO events.
		std::vector<IOEventInfo *> events;
		/// Vector of IO events to be removed.
		std::vector<IOEventInfo *> trash;
		/// Vector of IO events to be added.
		std::vector<IOEventInfo *> newEvents;
		/// File descriptor set.
		FDSet fds;
		/// Main loop flag.
		bool running;
		
		/** Clear event.
		 *
		 * Removes an event from the vector of registered events.
		 *
		 * \param eventInfo Event to be removed.
		 */
		virtual void clearEvent(IOEventInfo *eventInfo);
		
		/// Remove events flagged for removal.
		virtual void clearEvents();
		
		/** Add event.
		 *
		 * Add an event to the vector of registered events.
		 *
		 * \param eventInfo Event to be added.
		 */
		virtual void addEvent(IOEventInfo *eventInfo);
		
		/// Add events flagged for registration.
		virtual void addEvents();
		
	public:
		/** Constructor.
		 *
		 * Construct new SelectMultiplexer object.
		 */
		SelectMultiplexer();
		
		/** Destructor.
		 *
		 * Destruct SelectMultiplexer object.
		 */
		virtual ~SelectMultiplexer();
		
		/** Register IO event.
		 *
		 * Register an IO event to be handled by the multiplexer.
		 *
		 * \param handler IO handler to be notified if the event occurs..
		 * \param event IO event..
		 */
		virtual void registerEvent(IOHandler *handler, IOEvent event);
		
		/** Remove IO event.
		 *
		 * Remove an IO event from the set of events handled by the multiplexer.
		 *
		 * \param handler IO handler for which the event has been registered..
		 * \param event IO event..
		 */
		virtual void removeEvent(IOHandler *handler, IOEvent event);
		
		/** Set timeout.
		 *
		 * Sets the timeout of the main loop.
		 *
		 * \param secs Seconds.
		 * \param usecs Microseconds.
		 */
		virtual void setTimeout(int secs, int usecs);
		
		/** Main loop.
		 *
		 * Watch for registered events.
		 */
		virtual void run();
		
		/** Exit main loop.
		 *
		 * Call this function to exit from the main loop.
		 */
		virtual void quit();
		
		/** Get running state.
		 *
		 * \return \c true if the main loop is running, \c false otherwise.
		 */
		virtual bool isRunning();
		
        /** Log events.
         *
         * Output a list of the currently registered events to the logging 
         * facility.
         */
        virtual void logEvents();
        
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
		virtual Reporter &getLog();
};

}

}

/** \file SelectMultiplexer.hpp
 * \brief Select based IO event multiplexer header.
 */
#endif
