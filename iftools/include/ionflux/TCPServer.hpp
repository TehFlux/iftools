#ifndef IONFLUX_TOOLS_TCPSERVER
#define IONFLUX_TOOLS_TCPSERVER
/* ==========================================================================
 * Ionflux Tools
 * Copyright (c) 2004 Joern P. Meier
 * mail@ionflux.org
 * --------------------------------------------------------------------------
 * TCPServer.hpp                    Generic TCP server.
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
#include "ionflux/tools.hpp"
#include "ionflux/Reporter.hpp"
#include "ionflux/TCPSocket.hpp"
#include "ionflux/TCPRemotePeer.hpp"
#include "ionflux/IOHandler.hpp"
#include "ionflux/SelectMultiplexer.hpp"

namespace Ionflux
{

namespace Tools
{

/** TCPServer.
 * \ingroup network
 *
 * A generic TCP server. You can implement your own protocol by deriving a 
 * class from TCPServer and overriding the onConnect(), onReject(), 
 * onReceive() and onDisconnect() event handlers.
 */
class TCPServer
: public IOHandler
{
	protected:
		/// Console output/logging.
		Ionflux::Tools::Reporter log;
		/// Server socket.
		TCPSocket serverSocket;
		/// Vector of connected clients.
		std::vector<TCPRemotePeer *> clients;
		/// Vector of disconnected clients.
		std::vector<TCPRemotePeer *> trash;
		/// Maximum number of clients.
		unsigned int maxClients;
		/// Current client ID.
		int currentClientID;
		/// IO multiplexer.
		IOMultiplexer *iomp;
		/// IO multiplexer memory management flag.
		bool manageIomp;
		/// IO event for timeout.
		IOEvent* timeoutEvent;
		/// IO event for the server socket.
		IOEvent serverSocketEvent;
        /// Bind address.
        std::string address;
		
		/** Create remote peer.
		 *
		 * Create a remote peer. Derived classes can override this to use 
         * custom TCPRemotePeer subclasses.
		 *
		 * \param clientID Client ID.
		 */
        virtual Ionflux::Tools::TCPRemotePeer* createRemotePeer(int clientID);
        
		/** Add client.
		 *
		 * Add a remote client to the client vector.
		 *
		 * \param client Client to be added.
		 */
		virtual void addClient(TCPRemotePeer *client);
		
		/** Remove client.
		 *
		 * Remove a remote client from the client vector.
		 *
		 * \param client Client to be removed.
		 */
		virtual void removeClient(TCPRemotePeer *client);
		
		/** Clean up clients.
		 *
		 * Removes disconnected clients from the peer vector.
		 */
		virtual void cleanupClients();
		
		/** Handle timeout event.
		 *
		 * Handle a timeout event.
		 */
		virtual void onTimeout();
		
		/** Event handler for new connections.
		 *
		 * This is called by the main loop whenever a new client connects.
		 *
		 * \note Override this to implement your own connection handling.
		 *
		 * \param client The client which caused the event.
		 */
		virtual void onConnect(TCPRemotePeer &client);
		
		/** Event handler for rejected connections.
		 *
		 * This is called by the main loop whenever a new client connection 
		 * is rejected.
		 *
		 * \note Override this to implement your own rejection handling. The 
		 * socket is probably writable while the call lasts, but may be closed 
		 * as soon as onReject returns.
		 *
		 * \param client The client which caused the event.
		 * \param reason The reason why the connection has been rejected.
		 */
		virtual void onReject(TCPRemotePeer &client, int reason);
		
		/** Event handler for received data.
		 *
		 * This is called by the main loop whenever data is received from a 
		 * client. The received bytes will be appended to the receive buffer 
		 * of the remote client.
		 *
		 * \note Override this to implement your own received data handling. 
		 * Remember that it is your responsibility to empty the receive 
		 * buffer after you are done processing data.
		 *
		 * \param client The client which caused the event.
		 */
		virtual void onReceive(TCPRemotePeer &client);
		
		/** Event handler for client disconnection.
		 *
		 * This is called by the main loop whenever a client disconnects.
		 *
		 * \note Override this to implement your own disconnection handling.
		 * However, do not expect to be able to write to the socket of the 
		 * disconnected client! The client reference is provided for 
		 * informational purposes only.
		 *
		 * \param client The client which caused the event.
		 */
		virtual void onDisconnect(TCPRemotePeer &client);
		
		/** Disconnect peer.
		 *
		 * Causes the specified remote peer to be disconnected.
		 *
		 * \param peer The remote peer to be disconnected.
		 */
		virtual void disconnect(TCPRemotePeer *peer);
		
	public:
		/// Default maximum number of clients.
		static const int DEFAULT_MAX_CLIENTS;
		/// Connection rejected: Maximum number of clients connected.
		static const int REJECTED_REASON_MAX_CLIENTS;
		
		/** Constructor.
		 *
		 * Construct new TCPServer object.
		 */
		TCPServer();
		
		/** Constructor.
		 *
		 * Construct new TCPServer object.
		 *
		 * \param initIomp IO multiplexer.
		 */
		TCPServer(IOMultiplexer *initIomp);
		
		/** Destructor.
		 *
		 * Destruct TCPServer object.
		 */
		virtual ~TCPServer();
		
		/** Initialize server.
		 *
		 * Prepare the server for operation.
		 *
		 * \return \c true on success, \c false otherwise.
		 */
		virtual bool init();
		
		/** Run server.
		 *
		 * Runs the server main loop. You must call init before starting the 
		 * main loop.
		 *
		 * \sa init()
		 */
		virtual void run();
		
		/** Perform cleanup.
		 *
		 * Shuts the server down and cleans up the resources used by the 
		 * server.
		 */
		virtual void cleanup();
		
		/** Enable timeout.
		 *
		 * Enable or disable timeout events.
         *
         * \param newState New state to be set for timeout events.
		 */
		virtual void enableTimeout(bool newState = true);
		
		/** Broadcast bytes.
		 *
		 * Sends the specified byte string to all connected clients.
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
		
		/** Set maximum number of clients.
		 *
		 * Sets the maximum number of clients that may be connected to this 
		 * server at the same time.
		 *
		 * \note Set this to 0 to allow as many clients as possible. You can 
		 * also set this to DEFAULT_MAX_CLIENTS to use the default value.
		 *
		 * \param newMaxClients Maximum number of clients.
		 */
		virtual void setMaxClients(unsigned int newMaxClients);
		
		/** Set listening address.
		 *
		 * Sets the address (decimal dot notation) on which this server will 
         * listen for incoming connections. If the address is set to an empty 
         * string, the server will listen on any address.
		 *
		 * \param newAddress Address.
		 */
        virtual void setAddress(const std::string& newAddress);
		        
		/** Set port.
		 *
		 * Sets the port on which this server will listen for incoming 
		 * connections.
		 *
		 * \param newPort Port number.
		 */
		virtual void setPort(int newPort);
		
		/** Get maximum number of clients.
		 *
		 * \return Maximum number of clients.
		 */
		virtual unsigned int getMaxClients();
		
		/** Get listening port.
		 *
		 * \return Listening port.
		 */
		virtual int getPort();
		
		/** Get listening address.
		 *
		 * \return Listening address.
		 */
        virtual std::string getAddress();
		
		/** Shutdown handler.
		 *
		 * Signal handler for signals that will cause the server to shutdown.
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

/** \file TCPServer.hpp
 * \brief Generic TCP server header.
 */
#endif
