#ifndef IONFLUX_TOOLS_TCPMESSAGECLIENT
#define IONFLUX_TOOLS_TCPMESSAGECLIENT
/* ==========================================================================
 * Ionflux Tools
 * Copyright (c) 2004 Joern P. Meier
 * mail@ionflux.org
 * --------------------------------------------------------------------------
 * TCPMessageClient.hpp                   Message based TCP client.
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
#include "ionflux/TCPClient.hpp"
#include "ionflux/MessageHandler.hpp"

namespace Ionflux
{

namespace Tools
{

/** TCPMessageClient.
 * \ingroup network
 *
 * A Message based TCP client. This works like a TCPClient, except that 
 * incoming data is unpacked into a message (if possible). Outgoing data is 
 * wrapped into a message and serialized before being sent over the socket.
 */
class TCPMessageClient
: public TCPClient, public MessageHandler
{
	protected:
		/** Event handler for new connections.
		 *
		 * This is called by the main loop whenever a connection to a peer is
		 * successfully established.
		 *
		 * \note Override this to implement your own connection handling.
		 *
		 * \param peer The peer which caused the event.
		 */
		virtual void onConnect(TCPRemotePeer &peer);
		
		/** Event handler for received data.
		 *
		 * This is called by the main loop whenever data is received from a 
		 * peer. The received bytes will be appended to the receive buffer 
		 * of the remote peer.
		 *
		 * \note Override this to implement your own received data handling. 
		 * Remember that it is your responsibility to empty the receive 
		 * buffer after you are done processing data.
		 *
		 * \param peer The peer which caused the event.
		 */
		virtual void onReceive(TCPRemotePeer &peer);
		
	public:
		/** Constructor.
		 *
		 * Construct new TCPMessageClient object.
		 */
		TCPMessageClient();
		
		/** Constructor.
		 *
		 * Construct new TCPMessageClient object.
		 *
		 * \param initInteractive Whether this client should run interactively 
		 * (i.e. read data from standard input).
		 */
		TCPMessageClient(bool initInteractive);
		
		/** Destructor.
		 *
		 * Destruct TCPMessageClient object.
		 */
		virtual ~TCPMessageClient();
		
		/** Event handler for standard input.
		 *
		 * For interactive clients, this is called by the main loop whenever 
		 * data is available on standard input.
		 *
		 * \param line Data from standard input.
		 */
		virtual void onInput(const std::string &line);
		
		/** Event handler for received messages.
		 *
		 * This is called whenever a valid message is received from a peer. 
		 * The received message will be available from 
		 * TCPRemotePeer::getMessage().
		 *
		 * \note Override this to implement your own message handling. 
		 *
		 * \param peer The peer which caused the event.
		 */
		virtual void onMessage(TCPRemotePeer &peer);
		
		/** Event handler for invalid messages.
		 *
		 * This is called whenever an invalid message is received from a peer.
		 *
		 * \note Override this to implement your own invalid message handling. 
		 *
		 * \param peer The peer which caused the event.
		 */
		virtual void onInvalidMessage(TCPRemotePeer &peer);
		
		/** Broadcast bytes.
		 *
		 * Sends the specified byte string to all connected peers.
		 *
		 * \param bytes The bytes to broadcast.
		 */
		virtual void broadcast(const std::string &bytes);
};

}

}

/** \file TCPMessageClient.hpp
 * \brief Message based TCP Client header.
 */
#endif
