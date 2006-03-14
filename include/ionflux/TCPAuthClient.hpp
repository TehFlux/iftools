#ifndef IONFLUX_TOOLS_TCPAUTHCLIENT
#define IONFLUX_TOOLS_TCPAUTHCLIENT
/* ==========================================================================
 * Ionflux Tools
 * Copyright (c) 2004 Joern P. Meier
 * mail@ionflux.org
 * --------------------------------------------------------------------------
 * TCPAuthClient.hpp                   Authenticated TCP client.
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
#include "ionflux/TCPMessageClient.hpp"

namespace Ionflux
{

namespace Tools
{

/** Authenticated TCP client.
 * \ingroup network
 *
 * A Message based TCP client supporting a simple authentication 
 * protocol.
 *
 * See misc/ifta.txt for a specification of the authentication protocol.
 */
class TCPAuthClient
: public TCPMessageClient
{
	protected:
		/// Username.
		std::string username;
		/// Password.
		std::string password;
		/// Current Message ID.
		unsigned int currentMsgID;
		
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
		using TCPClient::addConnection;
		
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
		/// Protocol state: Wait for WELCOME.
		static const int PS_WAIT_WELCOME;
		/// Protocol state: Wait for AUTH result.
		static const int PS_WAIT_AUTH_RESULT;
		/// Protocol state: Authentication succeeded.
		static const int PS_AUTH_OK;
		
		/** Constructor.
		 *
		 * Construct new TCPAuthClient object.
		 */
		TCPAuthClient();
		
		/** Constructor.
		 *
		 * Construct new TCPAuthClient object.
		 *
		 * \param initInteractive Whether this client should run interactively 
		 * (i.e. read data from standard input).
		 */
		TCPAuthClient(bool initInteractive);
		
		/** Constructor.
		 *
		 * Construct new TCPAuthClient object.
		 *
		 * \param initUsername Username.
		 * \param initPassword Password.
		 * \param initInteractive Whether this client should run interactively 
		 * (i.e. read data from standard input).
		 */
		TCPAuthClient(const std::string &initUsername, 
			const std::string &initPassword, bool initInteractive);
		
		/** Destructor.
		 *
		 * Destruct TCPAuthClient object.
		 */
		virtual ~TCPAuthClient();
		
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
		
		/** Add connection.
		 *
		 * Attempts to establish a connection to the specified host and port. 
		 * On success, the new connection will be maintained by the TCP client.
		 *
		 * \param host Hostname or IP address of the remote host.
		 * \param port Port to connect to.
		 * \param connUser Username to use for the connection.
		 * \param connPass Password to use for the connection.
		 *
		 * \return \c true on success, \c false otherwise.
		 */
		virtual bool addConnection(const std::string &host, int port, 
			const std::string &connUser, const std::string &connPass);
		
		/** Set username.
		 *
		 * Set new value of username.
		 *
		 * \param newUsername New value of username.
		 */
		virtual void setUsername(const std::string& newUsername);
		
		/** Set password.
		 *
		 * Set new value of password.
		 *
		 * \param newPassword New value of password.
		 */
		virtual void setPassword(const std::string& newPassword);
		
		/** Set current Message ID.
		 *
		 * Set new value of current Message ID.
		 *
		 * \param newCurrentMsgID New value of current Message ID.
		 */
		virtual void setCurrentMsgID(unsigned int newCurrentMsgID);
		
		/** Get username.
		 *
		 * \return Username.
		 */
		virtual std::string getUsername();
		
		/** Get password.
		 *
		 * \param target Buffer in which to store the password.
		 */
		virtual void getPassword(std::string &target);
		
		/** Get current Message ID.
		 *
		 * \return Current message ID.
		 */
		virtual unsigned int getCurrentMsgID();
};

}

}

/** \file TCPAuthClient.hpp
 * \brief Authenticated TCP client header.
 */
#endif
