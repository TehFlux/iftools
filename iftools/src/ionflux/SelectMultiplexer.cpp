/* ==========================================================================
 * Ionflux Tools
 * Copyright (c) 2004 Joern P. Meier
 * mail@ionflux.org
 * --------------------------------------------------------------------------
 * SelectMultiplexer.cpp            Select based IO event multiplexer.
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

#include "ionflux/SelectMultiplexer.hpp"

using namespace std;

namespace Ionflux
{

namespace Tools
{

sig_atomic_t SelectMultiplexer::shutdown = 0;

SelectMultiplexer::SelectMultiplexer()
: running(false)
{
	type = IOM_TYPE_SELECT;
}

SelectMultiplexer::~SelectMultiplexer()
{
	for (unsigned int i = 0; i < events.size(); i++)
	{
		if (events[i] != 0)
			delete events[i];
		events[i] = 0;
	}
}

void SelectMultiplexer::clearEvent(IOEventInfo *eventInfo)
{
	if (eventInfo == 0)
	{
		log.msg("[SelectMultiplexer::clearEvent] WARNING: Ignoring attempt to "
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
		status << "[SelectMultiplexer::clearEvent] DEBUG: Event removed from "
			"event vector. (" << events.size() << " events registered)";
		log.msg(status.str(), log.VL_DEBUG_INSANE);
		delete eventInfo;
		eventInfo = 0;
	} else
	{
		status.str("");
		status << "[SelectMultiplexer::clearEvent] WARNING: Event "
			"does not exist.";
		log.msg(status.str(), log.VL_WARNING);
	}
}

void SelectMultiplexer::clearEvents()
{
	if (trash.size() > 0)
		log.msg("[SelectMultiplexer::clearEvents] DEBUG: Removing unregistered "
			"events from event vector.", log.VL_DEBUG_INSANE);
	else
		return;
	for (unsigned int i = 0; i < trash.size(); i++)
		clearEvent(trash[i]);
	trash.clear();
}

void SelectMultiplexer::addEvent(IOEventInfo *eventInfo)
{
	events.push_back(eventInfo);
	ostringstream status;
	status << "[SelectMultiplexer::addEvent] DEBUG: Event added to "
		"event vector. (" << events.size() << " events registered)";
	log.msg(status.str(), log.VL_DEBUG_INSANE);
}

void SelectMultiplexer::addEvents()
{
	if (newEvents.size() > 0)
		log.msg("[SelectMultiplexer::addEvents] DEBUG: Adding newly registered "
			"events to event vector.", log.VL_DEBUG_INSANE);
	else
		return;
	for (unsigned int i = 0; i < newEvents.size(); i++)
		addEvent(newEvents[i]);
	newEvents.clear();
}

void SelectMultiplexer::registerEvent(IOHandler *handler, IOEvent event)
{
	if (handler == 0)
	{
		log.msg("[SelectMultiplexer::registerEvent] WARNING: Ignoring attempt "
			"to add null event handler.", log.VL_WARNING);
		return;
	}
	ostringstream status;
	status.str("");
	status << "[SelectMultiplexer::registerEvent] DEBUG: Processing event: "
		"fd = " << event.fd << ", handler = " << handler;
	log.msg(status.str(), log.VL_DEBUG_INSANE);
    // Set a flag if this is a timeout event.
    bool timeoutEvent = false;
    if ((event.type & IOEvent::IO_TIMEOUT) != 0)
        timeoutEvent = true;
	/* Check whether an event is already defined for his handler and FD.
       If the event is a timeout event, the FD does not have to match. */
	bool found = false;
	unsigned int i = 0;
	IOEventInfo *currentInfo;
	while (!found && (i < events.size()))
	{
		currentInfo = events[i];
		if ((currentInfo->handler == handler) 
			&& ((currentInfo->event.fd == event.fd) || timeoutEvent))
			found = true;
		else
			i++;
	}
	if (!found)
	{
		/* If no event for specified handler and FD is defined, create a new 
		   one with specified properties. */
		currentInfo = new IOEventInfo();
		currentInfo->event = event;
		currentInfo->handler = handler;
	}
	// Update file descriptor set and registered event types.
	if ((event.type & IOEvent::IO_READ) != 0)
	{
		status.str("");
		status << "[SelectMultiplexer::registerEvent] DEBUG: Registering FD "
			<< event.fd << " for IO_READ.";
		log.msg(status.str(), log.VL_DEBUG_INSANE);
		currentInfo->event.type |= IOEvent::IO_READ;
		fds.addReadFD(event.fd);
	}
	if ((event.type & IOEvent::IO_WRITE) != 0)
	{
		status.str("");
		status << "[SelectMultiplexer::registerEvent] DEBUG: Registering FD "
			<< event.fd << " for IO_WRITE.";
		log.msg(status.str(), log.VL_DEBUG_INSANE);
		currentInfo->event.type |= IOEvent::IO_WRITE;
		fds.addWriteFD(event.fd);
	}
	if ((event.type & IOEvent::IO_EXCEPT) != 0)
	{
		status.str("");
		status << "[SelectMultiplexer::registerEvent] DEBUG: Registering FD "
			<< event.fd << " for IO_EXCEPT.";
		log.msg(status.str(), log.VL_DEBUG_INSANE);
		currentInfo->event.type |= IOEvent::IO_EXCEPT;
		fds.addExceptFD(event.fd);
	}
	if (timeoutEvent)
	{
		status.str("");
		status << "[SelectMultiplexer::registerEvent] DEBUG: "
            "Registering IO_TIMEOUT event.";
		log.msg(status.str(), log.VL_DEBUG_INSANE);
		currentInfo->event.type |= IOEvent::IO_TIMEOUT;
	}
	if (!found)
	{
		if (running)
			newEvents.push_back(currentInfo);
		else
			addEvent(currentInfo);
	}
}

void SelectMultiplexer::removeEvent(IOHandler *handler, IOEvent event)
{
	if (handler == 0)
	{
		log.msg("[SelectMultiplexer::removeEvent] WARNING: Ignoring attempt "
			"to remove null event handler.", log.VL_WARNING);
		return;
	}
	ostringstream status;
	status.str("");
	status << "[SelectMultiplexer::removeEvent] DEBUG: Processing event: "
		"fd = " << event.fd << ", handler = " << handler;
	log.msg(status.str(), log.VL_DEBUG_INSANE);
    // Set a flag if this is a timeout event.
    bool timeoutEvent = false;
    if ((event.type & IOEvent::IO_TIMEOUT) != 0)
        timeoutEvent = true;
	IOEventInfo *currentInfo;
	bool found = false;
	unsigned int i = 0;
	while (!found && (i < events.size()))
	{
		currentInfo = events[i];
		if ((currentInfo->handler == handler) 
			&& ((currentInfo->event.fd == event.fd) || timeoutEvent))
			found = true;
		else
			i++;
	}
	if (found)
	{
		if ((event.type & IOEvent::IO_READ) != 0)
		{
			status.str("");
			status << "[SelectMultiplexer::removeEvent] DEBUG: Removing FD "
				<< event.fd << " for IO_READ.";
			log.msg(status.str(), log.VL_DEBUG_INSANE);
			fds.removeReadFD(event.fd);
		}
		if ((event.type & IOEvent::IO_WRITE) != 0)
		{
			status.str("");
			status << "[SelectMultiplexer::removeEvent] DEBUG: Removing FD "
				<< event.fd << " for IO_WRITE.";
			log.msg(status.str(), log.VL_DEBUG_INSANE);
			fds.removeWriteFD(event.fd);
		}
		if ((event.type & IOEvent::IO_EXCEPT) != 0)
		{
			status.str("");
			status << "[SelectMultiplexer::removeEvent] DEBUG: Removing FD "
				<< event.fd << " for IO_EXCEPT.";
			log.msg(status.str(), log.VL_DEBUG_INSANE);
			fds.removeExceptFD(event.fd);
		}
		if (timeoutEvent)
		{
			status.str("");
			status << "[SelectMultiplexer::removeEvent] DEBUG: "
                "Removing IO_TIMEOUT event.";
			log.msg(status.str(), log.VL_DEBUG_INSANE);
		}
		currentInfo->event.type &= (~event.type);
		// Remove event only if all event types are cleared.
		if (currentInfo->event.type == 0)
		{
			if (running)
				trash.push_back(currentInfo);
			else
				clearEvent(currentInfo);
		}
	} else
	{
		status.str("");
		status << "[SelectMultiplexer::removeEvent] WARNING: Event "
			"does not exist (fd = " << event.fd << ").";
		log.msg(status.str(), log.VL_WARNING);
	}
}

void SelectMultiplexer::setTimeout(int secs, int usecs)
{
    fds.setTimeout(secs, usecs);
}

void SelectMultiplexer::run()
{
	running = true;
	int result;
	IOEventInfo *currentEvent;
	IOEvent reportEvent;
	ostringstream status;
	while (shutdown == 0)
	{
		result = fds.select();
		if (result > 0)
		{
			// Handle pending events.
			for (unsigned int i = 0; i < events.size(); i++)
			{
				currentEvent = events[i];
				if (!log.assert(currentEvent != 0, "[SelectMultiplexer::run] "
					"Current event is null."))
					return;
				reportEvent = currentEvent->event;
				reportEvent.type = 0;
				if (((currentEvent->event.type & IOEvent::IO_READ) != 0)
					&& (fds.isSetRead(reportEvent.fd)))
				{
					status.str("");
					status << "[SelectMultiplexer::run] DEBUG: Event on FD "
						<< reportEvent.fd << ": IO_READ.";
					log.msg(status.str(), log.VL_DEBUG_INSANE);
					reportEvent.type |= IOEvent::IO_READ;
				}
				if (((currentEvent->event.type & IOEvent::IO_WRITE) != 0)
					&& (fds.isSetWrite(reportEvent.fd)))
				{
					status.str("");
					status << "[SelectMultiplexer::run] DEBUG: Event on FD "
						<< reportEvent.fd << ": IO_WRITE.";
					log.msg(status.str(), log.VL_DEBUG_INSANE);
					reportEvent.type |= IOEvent::IO_WRITE;
				}
				if (((currentEvent->event.type & IOEvent::IO_EXCEPT) != 0)
					&& (fds.isSetExcept(reportEvent.fd)))
				{
					status.str("");
					status << "[SelectMultiplexer::run] DEBUG: Event on FD "
						<< reportEvent.fd << ": IO_EXCEPT.";
					log.msg(status.str(), log.VL_DEBUG_INSANE);
					reportEvent.type |= IOEvent::IO_EXCEPT;
				}
				if ((reportEvent.type != 0) && (currentEvent->handler != 0))
				{
					// Notify handler.
					currentEvent->handler->onIO(reportEvent);
				}
			}
			// Update event vector.
			log.msg("[SelectMultiplexer::run] DEBUG: Updating event vector.", 
				log.VL_DEBUG_INSANE);
			clearEvents();
			addEvents();
		} else
        {
            // Handle timeout event.
            bool haveHandler = false;
			for (unsigned int i = 0; i < events.size(); i++)
			{
				currentEvent = events[i];
				if (!log.assert(currentEvent != 0, "[SelectMultiplexer::run] "
					"Current event is null."))
					return;
				if ((currentEvent->event.type & IOEvent::IO_TIMEOUT) != 0)
				{
                    reportEvent = currentEvent->event;
                    if (currentEvent->handler != 0)
                    {
                        // Notify handler.
                        haveHandler = true;
                        currentEvent->handler->onIO(reportEvent);
                    }
				}
            }
            if (haveHandler)
            {
                // Update event vector.
                log.msg("[SelectMultiplexer::run] DEBUG: "
                    "Updating event vector.", log.VL_DEBUG_INSANE);
                clearEvents();
                addEvents();
            }
        }
	}
	log.msg("[SelectMultiplexer::run] DEBUG: Exiting from main loop.", 
		log.VL_DEBUG_INSANE);
	running = false;
}

bool SelectMultiplexer::isRunning()
{
	return running;
}

void SelectMultiplexer::logEvents()
{
    std::ostringstream status;
    status << "Registered events: ";
    if (events.size() == 0)
        status << "<none>";
    else
    {
        for (std::vector<IOEventInfo*>::iterator i = events.begin(); 
            i != events.end(); i++)
        {
            IOEventInfo* e0 = *i;
            if (e0 != 0)
                status << "\n  " << e0->event << " (" << e0->handler << ")";
            else
                status << "\n  <null>";
        }
    }
    log.msg(status.str(), log.VL_DEBUG);
}

void SelectMultiplexer::quit()
{
	shutdown = 1;
}

void SelectMultiplexer::shutdownHandler(int signum)
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
	cout << "[SelectMultiplexer::shutdownHandler] Received signal " << signalName 
		+ ". Please wait while shutdown is in progress." << endl;
}

Reporter &SelectMultiplexer::getLog()
{
	return log;
}

}

}

/** \file SelectMultiplexer.cpp
 * \brief Select based IO event multiplexer implementation.
 */
