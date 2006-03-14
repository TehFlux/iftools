#ifndef IONFLUX_TOOLS_GLIBMULTIPLEXER
#define IONFLUX_TOOLS_GLIBMULTIPLEXER
/* ==========================================================================
 * Ionflux Tools
 * Copyright (c) 2004 Joern P. Meier
 * mail@ionflux.org
 * --------------------------------------------------------------------------
 * GlibMultiplexer.hpp                 Glib based IO event multiplexer.
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
#include <gtkmm/main.h>
#include "ionflux/IOHandler.hpp"
#include "ionflux/Reporter.hpp"
#include "ionflux/IOMultiplexer.hpp"

namespace Ionflux
{

namespace Tools
{

class GlibMultiplexer;

/** IO event information (Glib based).
 * \ingroup iomplex
 *
 * This is like an IOEventInfo, but contains additional fields used by the 
 * GlibMultiplexer implementation, and also a SigC callback for the IO event.
 */
class GlibIOEventInfo
: public sigc::trackable
{
	public:
		/// IO event.
		IOEvent event;
		/// IO handler.
		IOHandler *handler;
		/// IO signal connection.
		sigc::connection signalCon;
#ifdef HAVE_WINSOCK
		/// Socket event object (for win32).
		WSAEVENT socketEvent;
#endif
		/// multiplexer to call back in case of an IO event.
		GlibMultiplexer *target;
		
		// Constructor.
		GlibIOEventInfo() : target(0) { }
		/// IO Handler.
		bool ioHandler(Glib::IOCondition ioCond);
};

/** Glib based IO event multiplexer.
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
 * \note The GlibMultiplexer uses Glib signals as its underlying IO 
 * multiplexing facility.
 */
class GlibMultiplexer
: public sigc::trackable, public IOMultiplexer
{
	protected:
		/// Shutdown flag.
		static sig_atomic_t shutdown;
		/// Console output/logging.
		Ionflux::Tools::Reporter log;
		/// Vector of registered IO events.
		std::vector<GlibIOEventInfo *> events;
		/// Vector of IO events to be removed.
		std::vector<GlibIOEventInfo *> trash;
		/// Vector of IO events to be added.
		std::vector<GlibIOEventInfo *> newEvents;
		/// Main loop flag.
		bool running;
		/// Gtk Main object.
		Gtk::Main* kit;
		/// Argument count.
		int argc;
		/// Argument vector.
		char** argv;
		/// Application main window.
		Gtk::Window* mainWindow;
		
		/** Clear IO event.
		 *
		 * Removes an event from the vector of registered events.
		 *
		 * \param eventInfo Event to be removed.
		 */
		virtual void clearEvent(GlibIOEventInfo* eventInfo);
		
		/** Clear IO events.
		 *
		 * Removes events flagged for removal from  from the vector
		 * of registered events.
		 */
		virtual void clearEvents();
		
		/** Add IO event.
		 *
		 * Adds an event to the vector of registered events.
		 *
		 * \param eventInfo Event to be added.
		 */
		virtual void addEvent(GlibIOEventInfo* eventInfo);
		
		/** Add IO events.
		 *
		 * Adds events flagged for addition to the vector
		 * of registered events.
		 */
		virtual void addEvents();
		
	public:
		/** Constructor.
		 *
		 * Construct new GlibMultiplexer object.
		 */
		GlibMultiplexer();
		
		/** Constructor.
		 *
		 * Construct new GlibMultiplexer object.
		 *
		 * \param initArgc Argument count.
		 * \param initArgv Argument vector.
		 */
		GlibMultiplexer(int initArgc, char** initArgv);
		
		/** Constructor.
		 *
		 * Construct new GlibMultiplexer object.
		 *
		 * \param initArgc Argument count.
		 * \param initArgv Argument vector.
		 * \param initMainWin Application main window.
		 */
		GlibMultiplexer(int initArgc, char** initArgv, 
			Gtk::Window* initMainWin);
		
		/** Destructor.
		 *
		 * Destruct GlibMultiplexer object.
		 */
		virtual ~GlibMultiplexer();
		
		/** Register IO event.
		 *
		 * Register an IO event to be handled by the multiplexer.
		 *
		 * \param handler IO handler to be notified if the event occurs.
		 * \param event IO event.
		 */
		virtual void registerEvent(IOHandler* handler, IOEvent event);
		
		/** Remove IO event.
		 *
		 * Remove an IO event from the set of events handled by the multiplexer.
		 *
		 * \param handler IO handler for which the event has been registered.
		 * \param event IO event.
		 */
		virtual void removeEvent(IOHandler* handler, IOEvent event);
		
		/** Process IO event.
		 *
		 * Processes the event referenced by the specified IO event record.
		 *
		 * \note This is used by GlibIOEventInfo to propagate event signals.
		 * You should not have to use this in any other way.
		 *
		 * \param eventInfo IO event record.
		 * \param ioCond IO condition.
		 *
		 * \return \c true on success, \c false otherwise.
		 */
		virtual bool processEvent(GlibIOEventInfo* eventInfo, 
			Glib::IOCondition ioCond);
		
		/** Main loop.
		 *
		 * Start the main loop to watch for registered events.
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
		
		/** Run handler.
		 *
		 * Event handler for 'run' signals.
		 *
		 * \return \c true on success, \c false otherwise.
		 */
		virtual void runHandler();
		
		/** Quit handler.
		 *
		 * Event handler for 'quit' signals.
		 *
		 * \return \c true on success, \c false otherwise.
		 */
		virtual bool quitHandler();
		
		/** Shutdown handler.
		 *
		 * Signal handler for signals that will cause the main loop to exit.
		 *
		 * \param signum Signal.
		 */
		static void shutdownHandler(int signum);
		
		/** Get Console output/logging facility.
		 *
		 * The console output/logging facility used by this object
		 */
		virtual Reporter& getLog();
		
		/** Set application main window.
		 *
		 * Set new value of application main window.
		 *
		 * \param newMainWindow New value of application main window.
		 */
		virtual void setMainWindow(Gtk::Window* newMainWindow);
		
		/** Get application main window.
		 *
		 * return Current value of application main window.
		 */
		virtual Gtk::Window* getMainWindow();
};

}

}

/** \file GlibMultiplexer.hpp
 * \brief Glib based IO event multiplexer header.
 */
#endif
