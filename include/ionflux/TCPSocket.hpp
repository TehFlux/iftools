#ifndef IONFLUX_TOOLS_TCPSOCKET
#define IONFLUX_TOOLS_TCPSOCKET
/* ==========================================================================
 * Ionflux Tools
 * Copyright (c) 2004 Joern P. Meier
 * mail@ionflux.org
 * --------------------------------------------------------------------------
 * TCPSocket.hpp                 TCP Socket class
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
#include <sstream>
#ifndef HAVE_WINSOCK
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <netdb.h>
#else
#include <winsock.h>
#include <unistd.h>
typedef int socklen_t;
#endif
#include "ionflux/Reporter.hpp"

namespace Ionflux
{

namespace Tools
{

/** \addtogroup network Network interface
 *
 * Interface to networking facilities.
 *
 * @{
 */

/** TCP socket.
 *
 * Wrapper class for a TCP socket.
 */
class TCPSocket
{
	protected:
		/// Console output/logging.
		Ionflux::Tools::Reporter log;
		/// Remote hostname.
		std::string remoteHostName;
		/** Client IP address.
		 *
		 * This is used by accept() to store the IP address of a connected 
		 * client.
		 */
		std::string clientIP;
		/// Remote port number.
		int port;
		/// Socket file descriptor.
		int theSocket;
		/// Connection state.
		bool connected;
		/// Binding state.
		bool bound;
		/// Listening state.
		bool listening;
		/// Address of the remote socket.
		struct sockaddr_in remoteHostAddress;
		/// Address of the local socket.
		struct sockaddr_in localHostAddress;
		/// Host entry of the remote host
		struct hostent *remoteHostEntry;
		/// Queue size for incoming connections.
		int listenQueue;
		
	public:
		/// Size of read buffer.
		static const int READ_BUFFER_SIZE;
		/// Default queue size for incoming connections.
		static const int DEFAULT_LISTEN_QUEUE;
		
		/** Constructor.
		 *
		 * Construct a new TCPSocket object.
		 */
		TCPSocket();
		
		/** Constructor.
		 *
		 * Construct a new TCPSocket object.
		 *
		 * \param initPort The port this socket object will connect to or 
		 * listen on.
		 */
		TCPSocket(int initPort);
		
		/** Constructor.
		 *
		 * Construct a new TCPSocket object.
		 *
		 * \param initHost The remote host this socket object will connect to.
		 * \param initPort The port this socket object will connect to.
		 */
		TCPSocket(const std::string& initHost, int initPort);
		
		/** Destructor.
		 *
		 * Destruct TCPSocket object.
		 */
		virtual ~TCPSocket();
		
		/** Resolve remote hostname.
		 *
		 * Resolve the remote hostname.
		 *
		 * \return \c true on success, \c false otherwise.
		 */
		virtual bool resolve();
		
		/** Connect.
		 *
		 * Connect to remote host.
		 *
		 * \return \c true on success, \c false otherwise.
		 */
		virtual bool connect();
		
		/** Close connection.
		 *
		 * Closes the connection.
		 */
		virtual void close();
		
		/** Bind socket.
		 *
		 * Bind a socket to a local port on all available local interfaces.
		 *
		 * \return \c true on success, \c false otherwise.
		 */
		virtual bool bind();
		
		/** Bind socket.
		 *
		 * Bind a socket to a local port and interface. Pass INADDR_ANY to 
		 * 'address' to bind to all available local interfaces. Returns \c true 
		 * on success, \c false otherwise.
		 *
		 * \param newAddress Local interface address to bind to.
		 *
		 * \return \c true on success, \c false otherwise.
		 */
		virtual bool bind(unsigned int newAddress);
		
		/** Listen.
		 *
		 * Listen for incoming connections.
		 *
		 * \note You must call bind() prior to listen().
		 *
		 * \return \c true on success, \c false otherwise.
		 */
		virtual bool listen();
		
		/** Accept connection.
		 *
		 * Accepts a new client connection on a listening socket.
		 *
		 * \note You must call listen() prior to accept().
		 *
		 * \param newAddr Where to store the address of the connected peer.
		 * \param newAddrSize Where to store size of the address of the 
		 * connected peer.
		 *
		 * \return File descriptor of the new client socket.
		 */
		virtual int accept(sockaddr_in &newAddr, socklen_t &newAddrSize);
		
		/** Accept connection.
		 *
		 * Accepts a new client connection on a listening socket and 
		 * initializes a TCPSocket object appropriately. Returns \c true on 
		 * success, \c false otherwise.
		 *
		 * \note On success, you can use the new remote client socket for I/O 
		 * like you would use a local client socket.
		 *
		 * \param newClientSocket Where to store the new remote client socket.
		 *
		 * \return \c true on success, \c false otherwise.
		 */
		virtual bool accept(TCPSocket &newClientSocket);
		
		/** Read bytes.
		 *
		 * Read bytes from the socket.
		 *
		 * \param bytes String to store incoming bytes.
		 *
		 * \return \c true on success, \c false otherwise.
		 */
		virtual bool readBytes(std::string& bytes);
		
		/** Send bytes.
		 *
		 * Send bytes over the socket.
		 *
		 * \param bytes Bytes to send over the socket.
		 *
		 * \return \c true on success, \c false otherwise.
		 */
		virtual bool sendBytes(const std::string& bytes);
		
		/** Set remote host.
		 *
		 * Sets the remote host this socket object will connect to. You can 
		 * specify either a host name or an IP address.
		 *
		 * \param newHost Hostname of the remote host.
		 */
		virtual void setRemoteHost(const std::string& newHost);
		
		/** Set port.
		 *
		 * Sets the port this socket object will connect to.
		 *
		 * \param newPort Port number of the remote host.
		 */
		virtual void setPort(int newPort);
		
		/** Set listen queue.
		 *
		 * Sets the size of the queue for incoming connections.
		 *
		 * \note This is only valid for server sockets.
		 *
		 * \param newListenQueue Queue size for incoming connections.
		 */
		virtual void setListenQueue(int newListenQueue);
		
		/** Set file descriptor.
		 *
		 * Sets the file descriptor associated with this socket object.
		 *
		 * \note If the TCPSocket object is initialized and connected when you 
		 * call this function, it will be closed and its internal state reset.
		 *
		 * \param newFD Socket file descriptor.
		 */
		virtual void setFD(int newFD);
		
		/** Set connection state.
		 *
		 * Sets the connection state.
		 *
		 * \note You should not normally use this, since the connection state 
		 * is set automatically. However, if you want to construct a TCPSocket 
		 * object for an existing file descriptor, it might be necessary to 
		 * set the connection state manually.
		 *
		 * \param newConnectionState Connection state.
		 */
		virtual void setConnectionState(bool newConnectionState);
		
		/** Set binding state.
		 *
		 * Sets the binding state.
		 *
		 * \note You should not normally use this, since the binding state 
		 * is set automatically. However, if you want to construct a TCPSocket 
		 * object for an existing file descriptor, it might be necessary to 
		 * set the binding state manually.
		 *
		 * \param newBindingState Binding state.
		 */
		virtual void setBindingState(bool newBindingState);
		
		/** Set listening state.
		 *
		 * Sets the listening state.
		 *
		 * \note You should not normally use this, since the listening state 
		 * is set automatically. However, if you want to construct a TCPSocket 
		 * object for an existing file descriptor, it might be necessary to 
		 * set the listening state manually.
		 *
		 * \param newListeningState Listening state.
		 */
		virtual void setListeningState(bool newListeningState);
		
		/** Set client IP.
		 *
		 * Sets the IP address of the client represented by this TCPSocket 
		 * object.
		 *
		 * \note This is used by accept() to store the IP address of a newly 
		 * connected client. You should not normally set this by hand.
		 *
		 * \param newClientIP Client IP.
		 */
		virtual void setClientIP(const std::string &newClientIP);
		
		/** Get port.
		 *
		 * Get the port number this socket object will connect to.
		 *
		 * \return Port number.
		 */
		virtual int getPort();
		
		/** Get remote host.
		 *
		 * Get the hostname of the remote host this socket object will
		 * connect to.
		 *
		 * \return Hostname.
		 */
		virtual std::string getRemoteHost();
		
		/** Get file descriptor.
		 *
		 * Get the file descriptor associated with this socket object.
		 *
		 * \return Socket file descriptor..
		 */
		virtual int getFD();
		
		/** Connection state.
		 *
		 * Get the connection state.
		 *
		 * \note This is only valid for client sockets.
		 *
		 * \return \c true if this socket object is connected, \c false 
		 * otherwise.
		 */
		virtual bool isConnected();
		
		/** Get listen queue.
		 *
		 * Get the listen queue size for a server socket.
		 *
		 * \return Listen queue size.
		 */
		virtual int getListenQueue();
		
		/** Binding state.
		 *
		 * Get the binding state of the socket.
		 *
		 * \note This is only valid for server sockets.
		 *
		 * \return \c true if this socket object is bound to a local port, 
		 * \c false otherwise.
		 */
		virtual bool isBound();
		
		/** Listening state.
		 *
		 * Get the listening state of the socket.
		 *
		 * \note This is only valid for server sockets.
		 *
		 * \return \c true if this socket object is listening, \c false 
		 * otherwise.
		 */
		virtual bool isListening();
		
		/** Get client IP.
		 *
		 * Get the IP address which the socket is bound to.
		 * 
		 * \note For remote client sockets, the IP address will be set 
		 * automatically by accept(). However, it will not be set 
		 * automatically for a local client socket.
		 *
		 * \return IP address, in numbers-and-dots notation.
		 */
		virtual std::string getClientIP();
		
		/** Get Console output/logging facility.
		 *
		 * \return The console output/logging facility used by this object.
		 */
		virtual Reporter &getLog();
};

/// @}

}

}

/** \file TCPSocket.hpp
 * \brief TCP socket wrapper header.
 */
#endif
