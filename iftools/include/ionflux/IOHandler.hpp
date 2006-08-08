#ifndef IONFLUX_TOOLS_IOHANDLER
#define IONFLUX_TOOLS_IOHANDLER
/* ==========================================================================
 * Ionflux Tools
 * Copyright (c) 2004 Joern P. Meier
 * mail@ionflux.org
 * --------------------------------------------------------------------------
 * IOHandler.hpp                       IO event handler (abstract class).
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
#include <vector>
#include "ionflux/TCPRemotePeer.hpp"

namespace Ionflux
{

namespace Tools
{

/** IO Event.
 * \ingroup iomplex
 *
 * Provides detailed information about an IO event.
 */
struct IOEvent
{
	/// Constructor.
	IOEvent() : data(0), peer(0) { }
	/// File descriptor on which the event occured.
	int fd;
	/// Type of event.
	int type;
	/// Data associated with the event (optional).
	void *data;
	/// TCP remote peer which caused the event (optional).
	TCPRemotePeer *peer;
	/// Event type: read.
	static const int IO_READ;
	/// Event type: write.
	static const int IO_WRITE;
	/// Event type: except.
	static const int IO_EXCEPT;
};

/** IO event handler.
 * \ingroup iomplex
 *
 * A handler for IO events.
 */
class IOHandler
{
	protected:
		
	public:
		
		/** Destructor.
		 *
		 * Destruct IOHandler object.
		 */
		 virtual ~IOHandler() { };
		
		/** Handle IO event.
		 *
		 * Pass an IO event to the object for processing. The IOEvent will 
		 * have its type flags set according to the events that have been 
		 * triggered.
		 *
		 * \param event IO event..
		 */
		virtual void onIO(const IOEvent &event) = 0;
};

}

}

/** \file IOHandler.hpp
 * \brief IO event handler (abstract class) header.
 */
#endif
