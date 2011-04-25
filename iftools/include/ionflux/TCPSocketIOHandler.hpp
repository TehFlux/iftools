#ifndef IONFLUX_TOOLS_TCPSOCKETIOHANDLER
#define IONFLUX_TOOLS_TCPSOCKETIOHANDLER
/* ==========================================================================
 * Ionflux Tools
 * Copyright (c) 2004-2011 Joern P. Meier
 * mail@ionflux.org
 * --------------------------------------------------------------------------
 * TCPSocketIOHandler.hpp          TCP socket I/O handler.
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
#include "ionflux/TCPSocket.hpp"

namespace Ionflux
{

namespace Tools
{

/** TCP socket IO handler.
 * \ingroup iomplex
 *
 * A handler for socket I/O. This allows classes which handle TCP socket I/O 
 * to delegate I/O operations on the socket to another class.
 */
class TCPSocketIOHandler
{
	protected:
		
	public:
		
		/** Destructor.
		 *
		 * Destruct IOHandler object.
		 */
		virtual ~TCPSocketIOHandler() { };
		
		/** Read bytes.
		 *
		 * Read bytes from a socket.
		 *
		 * \param socket TCP socket.
		 * \param bytes Where to store the bytes.
		 *
		 * \return \c true on success, \c false otherwise.
		 */
	    virtual bool readBytes(Ionflux::Tools::TCPSocket& socket, 
	        std::string& bytes);
	    
		/** Send bytes.
		 *
		 * Send bytes over a socket.
		 *
		 * \param socket TCP socket.
		 * \param bytes Bytes to be sent.
		 *
		 * \return \c true on success, \c false otherwise.
		 */
	    virtual bool sendBytes(Ionflux::Tools::TCPSocket& socket, 
	        const std::string& bytes);
};

}

}

/** \file TCPSocketIOHandler.hpp
 * \brief TCP socket I/O handler header.
 */
#endif
