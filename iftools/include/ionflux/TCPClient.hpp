#ifndef IONFLUX_TOOLS_TCPCLIENT
#define IONFLUX_TOOLS_TCPCLIENT
/* ==========================================================================
 * Ionflux Tools
 * Copyright (c) 2004 Joern P. Meier
 * mail@ionflux.org
 * --------------------------------------------------------------------------
 * TCPClient.hpp                    Generic TCP client.
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
#include <signal.h>
#include "ionflux/Reporter.hpp"
#include "ionflux/TCPRemotePeer.hpp"
#include "ionflux/IOHandler.hpp"
#include "ionflux/SelectMultiplexer.hpp"

namespace Ionflux
{

namespace Tools
{

/** Generic TCP Client.
 * \ingroup network
 *
 * A generic TCP client, supporting an arbitrary number of peers. You can 
 * implement your own protocol by overriding the onConnect(), onReceive() and 
 * onDisconnect() event handlers. The TCP client can either be interactive 
 * (meaning it reads data from standard input) or non-interactive (meaning it 
 * doesn't read anything from standard input).
 */
class TCPClient
: public IOHandler
{
	protected:
		/// Console output/logging.
		Ionflux::Tools::Reporter log;
		/// Interactive flag.
		bool interactive;
		/// Vector of connected peers.
		std::vector<TCPRemotePeer *> peers;
		/// Vector of disconnected peers.
		std::vector<TCPRemotePeer *> trash;
		/// Current peer ID.
		int currentPeerID;
		/// IO multiplexer.
		IOMultiplexer *iomp;
		/// IO multiplexer memory management flag.
		bool manageIomp;
		/// IO event for standard input.
		IOEvent stdinEvent;
		/// IO event for timeout.
		IOEvent* timeoutEvent;
		
		/** Add peer.
		 *
		 * Add a remote peer to the peer vector.
		 *
		 * \param peer Peer to be added.
		 */
		virtual void addPeer(TCPRemotePeer *peer);
		
		/** Remove peer.
		 *
		 * Remove a remote peer from the peer vector.
		 *
		 * \param peer Peer to be removed.
		 */
		virtual void removePeer(TCPRemotePeer *peer);
		
		/** Clean up peers.
		 *
		 * Removes disconnected peers from the peer vector.
		 */
		virtual void cleanupPeers();
		
		/** Handle timeout event.
		 *
		 * Handle a timeout event.
		 */
		virtual void onTimeout();
		
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
		
		/** Event handler for peer disconnection.
		 *
		 * This is called by the main loop whenever a peer disconnects.
		 *
		 * \note Override this to implement your own disconnection handling.
		 * However, do not expect to be able to write to the socket of the 
		 * disconnected peer! The peer reference is provided for 
		 * informational purposes only.
		 *
		 * \param peer The peer which caused the event.
		 */
		virtual void onDisconnect(TCPRemotePeer &peer);
		
		/** Disconnect peer.
		 *
		 * Causes the specified remote peer to be disconnected.
		 *
		 * \param peer The remote peer to be disconnected.
		 */
		virtual void disconnect(TCPRemotePeer *peer);
		
	public:
		/** Constructor.
		 *
		 * Construct new TCPClient object.
		 */
		TCPClient();
		
		/** Constructor.
		 *
		 * Construct new TCPClient object.
		 *
		 * \param initInteractive Whether this client should run interactively 
		 * (i.e. read data from standard input).
		 */
		TCPClient(bool initInteractive);
		
		/** Constructor.
		 *
		 * Construct new TCPClient object.
		 *
		 * \param initInteractive Whether this client should run interactively 
		 * (i.e. read data from standard input).
		 * \param initIomp IO multiplexer.
		 */
		TCPClient(bool initInteractive, IOMultiplexer *initIomp);
		
		/** Destructor.
		 *
		 * Destruct TCPClient object.
		 */
		virtual ~TCPClient();
		
		/** Event handler for standard input.
		 *
		 * For interactive clients, this is called by the main loop whenever 
		 * data is available on standard input.
		 *
		 * \param line Data from standard input.
		 */
		virtual void onInput(const std::string &line);
		
		/** Run client.
		 *
		 * Runs the client main loop.
		 */
		virtual void run();
		
		/** Perform cleanup.
		 *
		 * Shuts the client down and cleans up the resources used by the 
		 * client.
		 */
		virtual void cleanup();
		
		/** Add connection.
		 *
		 * Attempts to establish a connection to the specified host and port. 
		 * On success, the new connection will be maintained by the TCP client.
		 *
		 * \param host Hostname or IP address of the remote host.
		 * \param port Port to connect to.
		 *
		 * \return \c true on success, \c false otherwise.
		 */
		virtual bool addConnection(const std::string &host, int port);
		
		/** Enable timeout.
		 *
		 * Enable or disable timeout events.
         *
         * \param newState New state to be set for timeout events.
		 */
		virtual void enableTimeout(bool newState = true);
		
		/** Broadcast bytes.
		 *
		 * Sends the specified byte string to all connected peers.
		 *
		 * \param bytes The bytes to broadcast.
		 */
		virtual void broadcast(const std::string &bytes);
		
		/** Handle IO event.
		 *
		 * Pass an IO event to the object for processing. The IOEvent will 
		 * have its type flags set according to the events that have been 
		 * triggered.
		 *
		 * \param event IO event..
		 */
		virtual void onIO(const IOEvent &event);
		
		/** Shutdown handler.
		 *
		 * Signal handler for signals that will cause the client to shutdown.
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

/** \file TCPClient.hpp
 * \brief Generic TCP client header.
 */
#endif
