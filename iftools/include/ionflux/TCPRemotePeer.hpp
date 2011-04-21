#ifndef IONFLUX_TOOLS_TCPREMOTEPEER
#define IONFLUX_TOOLS_TCPREMOTEPEER
/* ==========================================================================
 * Ionflux Tools
 * Copyright (c) 2004 Joern P. Meier
 * mail@ionflux.org
 * --------------------------------------------------------------------------
 * TCPRemotePeer.hpp                    Remote peer of a TCP connection.
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
#include "ionflux/Auth.hpp"
#include "ionflux/TCPSocket.hpp"
#include "ionflux/Message.hpp"
#include "ionflux/MessageDump.hpp"
#include "ionflux/MessageHandler.hpp"
#include "ionflux/TCPSocketIOHandler.hpp"

namespace Ionflux
{

namespace Tools
{

class MessageHandler;

/** TCPRemotePeer.
 * \ingroup network
 *
 * The remote peer of a TCP connection.
 */
class TCPRemotePeer
: public MessageDump
{
	protected:
		/// Numerical ID of the peer.
		int id;
		/// Socket used to communicate with the remote peer.
		TCPSocket socket;
		/// Receive buffer.
		std::string recvBuf;
		/** Protocol state.
		 *
		 * You can use this to keep track of protocol state in stateful 
		 * protocols.
		 */
		int protocolState;
		/** Peer data.
		 *
		 * You can use this to associate arbitrary data with a remote peer.
		 */
		void *data;
		/// Size of data.
		unsigned int dataSize;
		/** Message.
		 *
		 * This will be used for processing incoming data if you set a 
		 * non-null message handler.
		 */
		Message *message;
		/// Message handler.
		MessageHandler *messageHandler;
		/// Authentication data.
		AuthData auth;
		/** Message data cache.
		 *
		 * Can be used by the application to store message data (or other 
		 * arbitrary data).
		 */
		Node *cache;
		/// Socket I/O handler used for delegating recieve/send operations.
		TCPSocketIOHandler* socketIOHandler;
		
	public:
		/// Peer ID: Not set.
		static const int ID_NOT_SET;
		/// Protocol state: Undefined.
		static const int PROTOCOL_STATE_UNDEFINED;
		
		/** Constructor.
		 *
		 * Construct new TCPRemotePeer object.
		 */
		TCPRemotePeer();
		
		/** Constructor.
		 *
		 * Construct new TCPRemotePeer object.
		 *
		 * \param initID Numerical ID of the peer.
		 */
		TCPRemotePeer(int initID);
		
		/** Destructor.
		 *
		 * Destruct TCPRemotePeer object.
		 */
		virtual ~TCPRemotePeer();
		
		/** Receive data.
		 *
		 * Receives data from the socket. The data will be appended to the 
		 * receive buffer.
		 *
		 * \return \c true on success, \c false otherwise.
		 */
		virtual bool receive();
		
		/** Send data.
		 *
		 * Send data over the socket.
		 *
		 * \param bytes The data to be sent.
		 *
		 * \return \c true on success, \c false otherwise.
		 */
		virtual bool send(const std::string &bytes);
		
		/** Set ID.
		 *
		 * Sets the numerical ID of this peer.
		 *
		 * \param newID Numerical ID of the peer.
		 */
		virtual void setID(int newID);
		
		/** Set protocol state.
		 *
		 * Sets the current protocol state. Use this to set the protocol state 
		 * for implementations of stateful protocols.
		 *
		 * \param newProtocolState The new protocol state.
		 */
		virtual void setProtocolState(int newProtocolState);
		
		/** Set message handler.
		 *
		 * Set the message handler to be used for message handling.
		 *
		 * \note If you set this to a non-null value, the receive buffer will 
		 * be disabled. Instead, all incoming data will be dumped into the 
		 * message object of the remote peer.
		 *
		 * \param newMessageHandler Pointer to a message handler.
		 */
		virtual void setMessageHandler(MessageHandler *newMessageHandler);
		
		/** Set socket I/O handler.
		 *
		 * Set the handler used for socket I/O.
		 *
		 * \note If you set this to a non-null value, all send and receive 
		 * operations will be delegated to the handler.
		 *
		 * \param newSocketIOHandler Pointer to a TCP socket I/O handler.
		 */
		virtual void setSocketIOHandler(TCPSocketIOHandler* 
		    newSocketIOHandler);
		
		/** Set data.
		 * 
		 * Set the data associated with this peer.
		 * 
		 * \param newData Data.
		 * \param newDataSize Size of data.
		 */
		virtual void setData(void* newData = 0, 
		    unsigned int newDataSize = 0);
		
		/** Get ID of the peer.
		 *
		 * \return Numerical ID of the peer.
		 */
		virtual int getID();
		
		/** Get socket.
		 *
		 * Get the socket used to communicate with the remote peer.
		 *
		 * \return Socket used to communicate with the remote peer.
		 */
		virtual TCPSocket &getSocket();
		
		/** Get authentication data.
		 *
		 * Get the authentication data for this peer.
		 *
		 * \return Authentication data used for this peer.
		 */
		virtual AuthData &getAuthData();
		
		/** Get receive buffer.
		 *
		 * \return Receive buffer.
		 */
		virtual std::string &getRecvBuf();
		
		/** Remove bytes from receive buffer.
		 *
		 * Removes the first \c numBytes bytes from the receive buffer.
		 *
		 * \return Number of bytes left in the receive buffer.
		 */
		virtual unsigned int removeRecvBytes(unsigned int numBytes);
		
		/// Clear the receive buffer.
		virtual void clearRecvBuf();
		
		/** Get protocol state.
		 *
		 * \return Current protocol state.
		 */
		virtual int getProtocolState();
		
		/** Get data.
		 *
		 * \return Pointer to data.
		 */
		virtual void *getData();
		
		/** Get size of data.
		 *
		 * \return Size of data.
		 */
		virtual unsigned int getDataSize();
		
		/** Get message.
		 *
		 * \return Pointer to a message object, or 0 if message handling has 
		 * not been initialized.
		 */
		virtual Message *getMessage();
		
		/** Get cache.
		 *
		 * Get a node in which message data (or other arbitrary data) can be 
		 * stored.
		 *
		 * \return Pointer to cache node.
		 */
		virtual Node *getCache();
		
		/** Dump message.
		 *
		 * Pass a message to the object for handling.
		 *
		 * \param msg The message to be dumped.
		 */
		virtual void dump(Message &msg);

};

}

}

/** \file TCPRemotePeer.hpp
 * \brief Remote peer of a TCP connection header.
 */
#endif
