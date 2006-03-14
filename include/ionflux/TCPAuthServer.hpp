#ifndef IONFLUX_TOOLS_TCPAUTHSERVER
#define IONFLUX_TOOLS_TCPAUTHSERVER
/* ==========================================================================
 * Ionflux Tools
 * Copyright (c) 2004 Joern P. Meier
 * mail@ionflux.org
 * --------------------------------------------------------------------------
 * TCPAuthServer.hpp                   Authenticated TCP server.
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
#include "ionflux/tools.hpp"
#include "ionflux/TCPMessageServer.hpp"
#include "ionflux/AuthFile.hpp"

namespace Ionflux
{

namespace Tools
{

/** Authenticated TCP server.
 * \ingroup network
 *
 * A Message based TCP server supporting a simple client authentication 
 * protocol.
 *
 * To define your own protocol on top of an authenticated connection, override 
 * the TCPAuthServer::onAuthMessage() function. The TCPAuthServer will handle 
 * all the rest for you. If you want to define additional protocol states for 
 * your own protocol, the associated values must be of the form 
 * TCPAuthServer::PS_AUTH_OK + n, where n is a positive integer.
 *
 * See <tt>misc/ifta.txt</tt> for a specification of the authentication 
 * protocol.
 */
class TCPAuthServer
: public TCPMessageServer
{
	protected:
		/// Authentication facility.
		Auth* auth;
		/// Authentication file name.
		std::string authFileName;
		/// Current Message ID.
		unsigned int currentMsgID;
		/// Randomizer.
		MTRand *randomizer;
		
		/** Event handler for new connections.
		 *
		 * This is called by the main loop whenever a new client connects.
		 *
		 * \note Override this to implement your own connection handling.
		 *
		 * \param client The client which caused the event.
		 */
		virtual void onConnect(TCPRemotePeer &client);
		
		/** Event handler for authenticated messages.
		 *
		 * This is called whenever a message is received from an authenticated 
		 * peer. The received message will be available from 
		 * TCPRemotePeer::getMessage().
		 *
		 * \note Override this to implement your own authenticated message 
		 * handling. 
		 *
		 * \param peer The peer which caused the event.
		 */
		virtual void onAuthMessage(TCPRemotePeer &peer);
		
		/** Event handler for successful authentication.
		 *
		 * This is called when authentication with a peer has succeeded.
		 *
		 * \note Override this to implement your own authentication success 
		 * handling. 
		 *
		 * \param peer The peer which caused the event.
		 */
		virtual void onAuthOK(TCPRemotePeer &peer);
		
		/** Event handler for failed authentication.
		 *
		 * This is called when authentication with a peer has failed.
		 *
		 * \note Override this to implement your own authentication failure 
		 * handling. 
		 *
		 * \param peer The peer which caused the event.
		 */
		virtual void onAuthFailed(TCPRemotePeer &peer);
		
	public:
		/// Magic word.
		static const std::string MAGIC_WORD;
		/// Protocol version.
		static const unsigned int AUTH_VERSION;
		/// Protocol version (upper boundary).
		static const unsigned int AUTH_VERSION_UPPER;
		/// Protocol version (lower boundary).
		static const unsigned int AUTH_VERSION_LOWER;
		/// Message type ID: HELLO.
		static const int MSGID_HELLO;
		/// Message type ID: WELCOME.
		static const int MSGID_WELCOME;
		/// Message type ID: AUTH.
		static const int MSGID_AUTH;
		/// Message type ID: AUTH_OK.
		static const int MSGID_AUTH_OK;
		/// Message type ID: AUTH_FAILED.
		static const int MSGID_AUTH_FAILED;
		/// Protocol state: Wait for HELLO.
		static const int PS_WAIT_HELLO;
		/// Protocol state: Wait for AUTH.
		static const int PS_WAIT_AUTH;
		/// Protocol state: Authentication succeeded.
		static const int PS_AUTH_OK;
		
		/** Constructor.
		 *
		 * Construct new TCPAuthServer object.
		 */
		TCPAuthServer();
		
		/** Constructor.
		 *
		 * Construct new TCPAuthServer object.
		 *
		 * \param initAuthFileName Authentication file name.
		 */
		TCPAuthServer(const std::string& initAuthFileName);
		
		/** Destructor.
		 *
		 * Destruct TCPAuthServer object.
		 */
		virtual ~TCPAuthServer();
		
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
		
		/** Set authentication facility.
		 *
		 * Set new value of authentication facility.
		 *
		 * \param newAuth New value of authentication facility.
		 */
		virtual void setAuth(Auth* newAuth);
		
		/** Set authentication file name.
		 *
		 * Set new value of authentication file name.
		 *
		 * \param newAuthFileName New value of authentication file name.
		 */
		virtual void setAuthFileName(const std::string& newAuthFileName);
		
		/** Set current Message ID.
		 *
		 * Set new value of current Message ID.
		 *
		 * \param newCurrentMsgID New value of current Message ID.
		 */
		virtual void setCurrentMsgID(unsigned int newCurrentMsgID);
		
		/** Get authentication facility.
		 *
		 * \return Pointer to the authentication facility used by this server.
		 */
		virtual Auth* getAuth();
		
		/** Get authentication file name.
		 *
		 * \return Name of the authentication file, or an empty string if the 
		 * authentication file is not set.
		 */
		virtual std::string getAuthFileName();
		
		/** Get current Message ID.
		 *
		 * \return Current message ID.
		 */
		virtual unsigned int getCurrentMsgID();
};

}

}

/** \file TCPAuthServer.hpp
 * \brief Authenticated TCP server header.
 */
#endif
