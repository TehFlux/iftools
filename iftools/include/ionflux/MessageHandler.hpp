#ifndef IONFLUX_TOOLS_MESSAGEHANDLER
#define IONFLUX_TOOLS_MESSAGEHANDLER
/* ==========================================================================
 * Ionflux Tools
 * Copyright (c) 2004 Joern P. Meier
 * mail@ionflux.org
 * --------------------------------------------------------------------------
 * MessageHandler.hpp                 Message event handler (abstract class)
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
#include "ionflux/TCPRemotePeer.hpp"

namespace Ionflux
{

namespace Tools
{

class TCPRemotePeer;

/** Message event handler.
 * \ingroup network
 *
 * Abstract base class for handling message events. A message event is invoked 
 * whenever a TCPRemotePeer has received and unpacked a valid network message.
 */
class MessageHandler
{
	public:
		/** Destructor.
		 *
		 * Destruct MessageDump object.
		 */
		virtual ~MessageHandler() { };
		
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
		virtual void onMessage(TCPRemotePeer &peer) = 0;
		
		/** Event handler for invalid messages.
		 *
		 * This is called whenever an invalid message is received from a peer.
		 *
		 * \note Override this to implement your own invalid message handling. 
		 *
		 * \param peer The peer which caused the event.
		 */
		virtual void onInvalidMessage(TCPRemotePeer &peer) = 0;
};

}

}

/** \file MessageHandler.hpp
 * \brief Message handler (abstract class) header.
 */
#endif
