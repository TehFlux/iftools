/* ==========================================================================
 * Ionflux Tools
 * Copyright (c) 2004 Joern P. Meier
 * mail@ionflux.org
 * --------------------------------------------------------------------------
 * GlibMultiplexer.cpp             Glib based IO event multiplexer.
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

#include "ionflux/GlibMultiplexer.hpp"

using namespace std;

namespace Ionflux
{

namespace Tools
{

bool GlibIOEventInfo::ioHandler(Glib::IOCondition ioCond)
{
	if (target != 0)
		return target->processEvent(this, ioCond);
	else
		cerr << "[GlibIOEventInfo::ioHandler] "
			"WARNING: Target is null." << endl;
	return false;
}

sig_atomic_t GlibMultiplexer::shutdown = 0;

GlibMultiplexer::GlibMultiplexer()
: running(false), argc(0), argv(0), mainWindow(0)
{
	type = IOM_TYPE_GLIB;
	kit = new Gtk::Main(argc, argv);
	Gtk::Main::signal_quit().connect(
		sigc::mem_fun(*this, &GlibMultiplexer::quitHandler));
	Gtk::Main::signal_run().connect(
		sigc::mem_fun(*this, &GlibMultiplexer::runHandler));
}

GlibMultiplexer::GlibMultiplexer(int initArgc, char** initArgv)
: running(false), argc(initArgc), argv(initArgv), mainWindow(0)
{
	type = IOM_TYPE_GLIB;
	kit = new Gtk::Main(argc, argv);
	Gtk::Main::signal_quit().connect(
		sigc::mem_fun(*this, &GlibMultiplexer::quitHandler));
	Gtk::Main::signal_run().connect(
		sigc::mem_fun(*this, &GlibMultiplexer::runHandler));
}

GlibMultiplexer::GlibMultiplexer(int initArgc, char** initArgv, 
	Gtk::Window* initMainWin)
: running(false), argc(initArgc), argv(initArgv), mainWindow(initMainWin)
{
	type = IOM_TYPE_GLIB;
	kit = new Gtk::Main(argc, argv);
	Gtk::Main::signal_quit().connect(
		sigc::mem_fun(*this, &GlibMultiplexer::quitHandler));
	Gtk::Main::signal_run().connect(
		sigc::mem_fun(*this, &GlibMultiplexer::runHandler));
}

GlibMultiplexer::~GlibMultiplexer()
{
	for (unsigned int i = 0; i < events.size(); i++)
	{
		if (events[i] != 0)
		{
			events[i]->signalCon.disconnect();
#ifdef HAVE_WINSOCK
			// Special treatment for win32.
			WSAResetEvent(events[i]->socketEvent);
#endif
			delete events[i];
			events[i] = 0;
		}
	}
	delete kit;
}

void GlibMultiplexer::clearEvent(GlibIOEventInfo* eventInfo)
{
	if (eventInfo == 0)
	{
		log.msg("[GlibMultiplexer::clearEvent] WARNING: Ignoring attempt to "
			"remove null event.", log.VL_WARNING);
		return;
	}
	bool found = false;
	unsigned int i = 0;
	ostringstream status;
	while(!found && (i < events.size()))
	{
		if (events[i] == eventInfo)
			found = true;
		else
			i++;
	}
	if (found)
	{
		events.erase(events.begin() + i);
		status << "[GlibMultiplexer::clearEvent] DEBUG: Event removed from "
			"event vector. (" << events.size() << " events registered)";
		log.msg(status.str(), log.VL_DEBUG_INSANE);
		delete eventInfo;
		eventInfo = 0;
	} else
	{
		status.str("");
		status << "[GlibMultiplexer::clearEvent] WARNING: Event "
			"does not exist.";
		log.msg(status.str(), log.VL_WARNING);
	}
}

void GlibMultiplexer::clearEvents()
{
	if (trash.size() > 0)
		log.msg("[GlibMultiplexer::clearEvents] DEBUG: Removing unregistered "
			"events from event vector.", log.VL_DEBUG_INSANE);
	else
		return;
	for (unsigned int i = 0; i < trash.size(); i++)
		clearEvent(trash[i]);
	trash.clear();
}

void GlibMultiplexer::addEvent(GlibIOEventInfo* eventInfo)
{
	events.push_back(eventInfo);
	ostringstream status;
	status << "[GlibMultiplexer::addEvent] DEBUG: Event added to "
		"event vector. (" << events.size() << " events registered)";
	log.msg(status.str(), log.VL_DEBUG_INSANE);
}

void GlibMultiplexer::addEvents()
{
	if (newEvents.size() > 0)
		log.msg("[GlibMultiplexer::addEvents] DEBUG: Adding newly registered "
			"events to event vector.", log.VL_DEBUG_INSANE);
	else
		return;
	for (unsigned int i = 0; i < newEvents.size(); i++)
		addEvent(newEvents[i]);
	newEvents.clear();
}

void GlibMultiplexer::registerEvent(IOHandler* handler, IOEvent event)
{
	if (handler == 0)
	{
		log.msg("[GlibMultiplexer::registerEvent] WARNING: Ignoring attempt "
			"to add null event handler.", log.VL_WARNING);
		return;
	}
	ostringstream status;
	status.str("");
	status << "[GlibMultiplexer::registerEvent] DEBUG: Processing event: "
		"fd = " << event.fd << ", handler = " << handler;
	log.msg(status.str(), log.VL_DEBUG_INSANE);
	// Check whether an event is already defined for his handler and FD.
	bool found = false;
	unsigned int i = 0;
	GlibIOEventInfo *currentInfo;
	while (!found && (i < events.size()))
	{
		currentInfo = events[i];
		if ((currentInfo->handler == handler) 
			&& (currentInfo->event.fd == event.fd))
			found = true;
		else
			i++;
	}
	if (!found)
	{
		/* If no event for specified handler and FD is defined, create a new 
		   one with specified properties. */
		currentInfo = new GlibIOEventInfo();
		currentInfo->event = event;
		currentInfo->handler = handler;
		currentInfo->target = this;
	}
	// Update file descriptor set and registered event types.
	Glib::IOCondition ioCond;
	bool condRead = false;
	bool condWrite = false;
	bool condExcept = false;
	if ((event.type & IOEvent::IO_READ) != 0)
	{
		status.str("");
		status << "[GlibMultiplexer::registerEvent] DEBUG: Registering FD "
			<< event.fd << " for IO_READ.";
		log.msg(status.str(), log.VL_DEBUG_INSANE);
		currentInfo->event.type |= IOEvent::IO_READ;
		ioCond = (Glib::IO_IN | Glib::IO_PRI | Glib::IO_ERR | Glib::IO_HUP);
		condRead = true;
	}
	if ((event.type & IOEvent::IO_WRITE) != 0)
	{
		status.str("");
		status << "[GlibMultiplexer::registerEvent] DEBUG: Registering FD "
			<< event.fd << " for IO_WRITE.";
		log.msg(status.str(), log.VL_DEBUG_INSANE);
		currentInfo->event.type |= IOEvent::IO_WRITE;
		if (condRead)
			ioCond |= Glib::IO_OUT;
		else
			ioCond = Glib::IO_OUT;
		condWrite = true;
	}
	if ((event.type & IOEvent::IO_EXCEPT) != 0)
	{
		status.str("");
		status << "[GlibMultiplexer::registerEvent] DEBUG: Registering FD "
			<< event.fd << " for IO_EXCEPT.";
		log.msg(status.str(), log.VL_DEBUG_INSANE);
		currentInfo->event.type |= IOEvent::IO_EXCEPT;
		/* I don't really know what we should watch for in this case, but 
		   IO_ERR cabn't be all that wrong. */
		if (condRead || condWrite)
			ioCond |= Glib::IO_ERR;
		else
			ioCond = Glib::IO_ERR;
		condExcept = true;
	}
	// Connect IO signal.
	if (condRead || condWrite || condExcept)
	{
		/* TODO: FD needs to be transformed into a HANDLE on win32 in 
		   order for this to work. */
		currentInfo->signalCon = Glib::signal_io().connect(
			sigc::mem_fun(*currentInfo, &GlibIOEventInfo::ioHandler), 
			currentInfo->event.fd, ioCond);
	}
	if (!found)
	{
		if (running)
			newEvents.push_back(currentInfo);
		else
			addEvent(currentInfo);
	}
}

void GlibMultiplexer::removeEvent(IOHandler* handler, IOEvent event)
{
	if (handler == 0)
	{
		log.msg("[GlibMultiplexer::removeEvent] WARNING: Ignoring attempt "
			"to remove null event handler.", log.VL_WARNING);
		return;
	}
	ostringstream status;
	status.str("");
	status << "[GlibMultiplexer::removeEvent] DEBUG: Processing event: "
		"fd = " << event.fd << ", handler = " << handler;
	log.msg(status.str(), log.VL_DEBUG_INSANE);
	GlibIOEventInfo *currentInfo;
	bool found = false;
	unsigned int i = 0;
	while (!found && (i < events.size()))
	{
		currentInfo = events[i];
		if ((currentInfo->handler == handler) 
			&& (currentInfo->event.fd == event.fd))
			found = true;
		else
			i++;
	}
	if (found)
	{
		if ((event.type & IOEvent::IO_READ) != 0)
		{
			status.str("");
			status << "[GlibMultiplexer::removeEvent] DEBUG: Removing FD "
				<< event.fd << " for IO_READ.";
			log.msg(status.str(), log.VL_DEBUG_INSANE);
		}
		if ((event.type & IOEvent::IO_WRITE) != 0)
		{
			status.str("");
			status << "[GlibMultiplexer::removeEvent] DEBUG: Removing FD "
				<< event.fd << " for IO_WRITE.";
			log.msg(status.str(), log.VL_DEBUG_INSANE);
		}
		if ((event.type & IOEvent::IO_EXCEPT) != 0)
		{
			status.str("");
			status << "[GlibMultiplexer::removeEvent] DEBUG: Removing FD "
				<< event.fd << " for IO_EXCEPT.";
			log.msg(status.str(), log.VL_DEBUG_INSANE);
		}
		currentInfo->event.type &= (~event.type);
		// Disconnect IO signal, just in case.
		currentInfo->signalCon.disconnect();
		if (currentInfo->event.type == 0)
		{
			// Remove event only if all event types are cleared.
			if (running)
				trash.push_back(currentInfo);
			else
				clearEvent(currentInfo);
		} else
		{
			// Reconnect signal with whatever event types are left
			Glib::IOCondition ioCond;
			bool condRead = false;
			bool condWrite = false;
			bool condExcept = false;
			if ((currentInfo->event.type & IOEvent::IO_READ) != 0)
			{
				ioCond = (Glib::IO_IN | Glib::IO_PRI | Glib::IO_ERR 
					| Glib::IO_HUP);
				condRead = true;
			}
			if ((currentInfo->event.type & IOEvent::IO_WRITE) != 0)
			{
				if (condRead)
					ioCond |= Glib::IO_OUT;
				else
					ioCond = Glib::IO_OUT;
				condWrite = true;
			}
			if ((currentInfo->event.type & IOEvent::IO_EXCEPT) != 0)
			{
				if (condRead || condWrite)
					ioCond |= Glib::IO_ERR;
				else
					ioCond = Glib::IO_ERR;
				condExcept = true;
			}
			// Connect IO signal.
			if (condRead || condWrite || condExcept)
			{
				/* TODO: FD needs to be transformed into a HANDLE on win32 
				   in order for this to work. */
				currentInfo->signalCon = Glib::signal_io().connect(
					sigc::mem_fun(*currentInfo, &GlibIOEventInfo::ioHandler), 
					currentInfo->event.fd, ioCond);
			}
		}
	} else
	{
		status.str("");
		status << "[GlibMultiplexer::removeEvent] WARNING: Event "
			"does not exist (fd = " << event.fd << ").";
		log.msg(status.str(), log.VL_WARNING);
	}
}

bool GlibMultiplexer::processEvent(GlibIOEventInfo* eventInfo, 
	Glib::IOCondition ioCond)
{
	ostringstream status;
	IOEvent reportEvent = eventInfo->event;
	reportEvent.type = 0;
	if (((eventInfo->event.type & IOEvent::IO_READ) != 0)
		&& (ioCond & (Glib::IO_IN | Glib::IO_PRI | Glib::IO_ERR 
			| Glib::IO_HUP)))
	{
		status.str("");
		status << "[GlibMultiplexer::processEvent] DEBUG: Event on FD "
			<< reportEvent.fd << ": IO_READ.";
		log.msg(status.str(), log.VL_DEBUG_INSANE);
		reportEvent.type |= IOEvent::IO_READ;
	}
	if (((eventInfo->event.type & IOEvent::IO_WRITE) != 0)
		&& (ioCond & Glib::IO_OUT))
	{
		status.str("");
		status << "[GlibMultiplexer::processEvent] DEBUG: Event on FD "
			<< reportEvent.fd << ": IO_WRITE.";
		log.msg(status.str(), log.VL_DEBUG_INSANE);
		reportEvent.type |= IOEvent::IO_WRITE;
	}
	if (((eventInfo->event.type & IOEvent::IO_EXCEPT) != 0)
		&& (ioCond & Glib::IO_ERR))
	{
		status.str("");
		status << "[GlibMultiplexer::processEvent] DEBUG: Event on FD "
			<< reportEvent.fd << ": IO_EXCEPT.";
		log.msg(status.str(), log.VL_DEBUG_INSANE);
		reportEvent.type |= IOEvent::IO_EXCEPT;
	}
	if ((reportEvent.type != 0) && (eventInfo->handler != 0))
	{
		// Notify handler.
		eventInfo->handler->onIO(reportEvent);
	}
	// Update event vector.
	log.msg("[GlibMultiplexer::processEvent] DEBUG: Updating event vector.", 
		log.VL_DEBUG_INSANE);
	/* This might not work, since we are called from a GlibIOEventInfo 
	   that might get deleted during this call. */
	clearEvents();
	addEvents();
	return true;
}

void GlibMultiplexer::run()
{
	if (mainWindow == 0)
		kit->run();
	else
		kit->run(*mainWindow);
}

void GlibMultiplexer::quit()
{
	kit->quit();
}

bool GlibMultiplexer::isRunning()
{
	return running;
}

void GlibMultiplexer::runHandler()
{
	running = true;
}

bool GlibMultiplexer::quitHandler()
{
	running = false;
	return true;
}

void GlibMultiplexer::shutdownHandler(int signum)
{
	if (shutdown == 1)
		return;
	shutdown = 1;
	string signalName;
	if (signum == SIGINT)
		signalName = "SIGINT";
	else
	if (signum == SIGTERM)
		signalName = "SIGTERM";
	else
		signalName = "(unknown)";
	cout << "[GlibMultiplexer::shutdownHandler] Received signal " << signalName 
		+ ". Please wait while shutdown is in progress." << endl;
	Gtk::Main::quit();
}

Reporter& GlibMultiplexer::getLog()
{
	return log;
}

void GlibMultiplexer::setMainWindow(Gtk::Window* newMainWindow)
{
	mainWindow = newMainWindow;
}

Gtk::Window* GlibMultiplexer::getMainWindow()
{
	return mainWindow;
}

}

}

/** \file GlibMultiplexer.cpp
 * \brief Glib based IO event multiplexer implementation.
 */
