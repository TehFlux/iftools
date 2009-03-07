/* ==========================================================================
 * Ionflux Tools
 * Copyright (c) 2004 Joern P. Meier
 * mail@ionflux.org
 * --------------------------------------------------------------------------
 * TCPSocket.cpp                 TCP Socket class
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

#include <cstring>

#include "ionflux/TCPSocket.hpp"

using namespace std;

namespace Ionflux
{

namespace Tools
{

const int TCPSocket::READ_BUFFER_SIZE = 1024;
const int TCPSocket::DEFAULT_LISTEN_QUEUE = 10;

TCPSocket::TCPSocket()
: remoteHostName(""), clientIP(""), port(0), theSocket(0), connected(false), 
  bound(false), listening(false), remoteHostEntry(0), 
  listenQueue(DEFAULT_LISTEN_QUEUE)
{
	// TODO: Nothing ATM. ;-)
}

TCPSocket::TCPSocket(const std::string& initHost, int initPort)
: remoteHostName(initHost), clientIP(""), port(initPort), theSocket(0), 
  connected(false), bound(false), listening(false), remoteHostEntry(0), 
  listenQueue(DEFAULT_LISTEN_QUEUE)
{
	// TODO: Nothing ATM. ;-)
}

TCPSocket::TCPSocket(int initPort)
: remoteHostName(""), clientIP(""), port(initPort), theSocket(0), 
  connected(false), bound(false), listening(false), remoteHostEntry(0), 
  listenQueue(DEFAULT_LISTEN_QUEUE)
{
	// TODO: Nothing ATM. ;-)
}

TCPSocket::~TCPSocket()
{
	close();
}

bool TCPSocket::resolve()
{
	ostringstream status;
	status.str("");
	status << "[TCPSocket::resolve] DEBUG: Resolving host '" 
		<< remoteHostName << "'.";
	log.msg(status.str(), log.VL_DEBUG_OPT);
	remoteHostEntry = ::gethostbyname(remoteHostName.c_str());
	if (remoteHostEntry == 0)
	{
		status.str("");
		status << "[TCPSocket::resolve] ERROR: Could not resolve host '" 
			<< remoteHostName << "'.";
		log.msg(status.str(), log.VL_ERROR);
		return false;
	}
	return true;
}

bool TCPSocket::connect()
{
	close();
	ostringstream status;
	in_addr theAddress;
	if (::inet_aton(remoteHostName.c_str(), &theAddress) == 0)
	{
		// Not a valid IP address, try to resolve as a host name.
		if (remoteHostEntry == 0)
			if (!resolve())
				return false;
		theAddress = 
			*(reinterpret_cast<struct in_addr *>(remoteHostEntry->h_addr));
	}
	theSocket = ::socket(AF_INET, SOCK_STREAM, 0);
	remoteHostAddress.sin_family = AF_INET;
	remoteHostAddress.sin_port = htons(port);
	remoteHostAddress.sin_addr = theAddress;
	memset(&(remoteHostAddress.sin_zero), '\0', 8);
	if (theSocket == 0)
		return false;
	int result = ::connect(theSocket, 
		reinterpret_cast<struct sockaddr *>(&remoteHostAddress), 
		sizeof(struct sockaddr));
	if (result < 0)
	{
		status.str("");
		status << "[TCPSocket::connect] ERROR: Could not connect to host '" 
			<< remoteHostName << "' on port " << port << ".";
		log.msg(status.str(), log.VL_ERROR);
		return false;
	}
	connected = true;
	status.str("");
	status << "[TCPSocket::connect] DEBUG: Connected to host '" 
		<< remoteHostName << "' on port " << port << ".";
	log.msg(status.str(), log.VL_DEBUG_OPT);
	return true;
}

bool TCPSocket::bind()
{
	return bind(INADDR_ANY);
}

bool TCPSocket::bind(unsigned int newAddress)
{
	ostringstream status;
	close();
	theSocket = ::socket(AF_INET, SOCK_STREAM, 0);
	localHostAddress.sin_family = AF_INET;
	localHostAddress.sin_port = htons(port);
	localHostAddress.sin_addr.s_addr = htonl(newAddress);
	int result = ::bind(theSocket,
		reinterpret_cast<sockaddr *>(&localHostAddress),
		sizeof(localHostAddress));
	if (result < 0)
	{
		status.str("");
		status << "[TCPSocket::bind] ERROR: Could not bind to port "
			<< port << ".";
		log.msg(status.str(), log.VL_ERROR);
		return false;
	}
	bound = true;
	status.str("");
	status << "[TCPSocket::bind] DEBUG: Bound to port " << port << ".";
	log.msg(status.str(), log.VL_DEBUG_OPT);
	return true;
}

bool TCPSocket::listen()
{
	if (!bound)
	{
		log.msg("[TCPSocket::listen] ERROR: Socket is not bound.",
			log.VL_ERROR);
		return false;
	}
	if (listening)
	{
		log.msg("[TCPSocket::listen] ERROR: Socket is already listening.",
			log.VL_ERROR);
		return false;
	}
	if (!log.assert(theSocket != 0, "[TCPSocket::listen] Socket is null."))
		return false;
	ostringstream status;
	int result = ::listen(theSocket, listenQueue);
	if (result < 0)
	{
		status.str("");
		status << "[TCPSocket::listen] ERROR: Could not listen on port "
			<< port << ".";
		log.msg(status.str(), log.VL_ERROR);
		return false;
	}
	listening = true;
	status.str("");
	status << "[TCPSocket::listen] DEBUG: Listening on port " << port << ".";
	log.msg(status.str(), log.VL_DEBUG_OPT);
	return true;
}

int TCPSocket::accept(sockaddr_in &newAddr, socklen_t &newAddrSize)
{
	if (!listening)
	{
		log.msg("[TCPSocket::accept] ERROR: Socket is not listening.",
			log.VL_ERROR);
		return -1;
	}
	if (!log.assert(theSocket != 0, "[TCPSocket::accept] Socket is null."))
		return -1;
	newAddrSize = sizeof(newAddr);
	int clientFD = ::accept(theSocket, 
		reinterpret_cast<sockaddr *>(&newAddr),
		&newAddrSize);
	if (clientFD < 0)
	{
		log.msg("[TCPSocket::accept] ERROR: Failed to accept new connection.",
			log.VL_ERROR);
		return -1;
	}
	log.msg("[TCPSocket::accept] DEBUG: Accepted new connection.",
		log.VL_DEBUG_OPT);
	return clientFD;
}

bool TCPSocket::accept(TCPSocket &newClientSocket)
{
	sockaddr_in newAddr;
	socklen_t newAddrSize;
	int clientFD = accept(newAddr, newAddrSize);
	if (clientFD < 0)
		return false;
	newClientSocket.setFD(clientFD);
	newClientSocket.setConnectionState(true);
	newClientSocket.setClientIP(inet_ntoa(newAddr.sin_addr));
	log.msg(string("[TCPSocket::accept] DEBUG: Client IP: ") 
		+ newClientSocket.getClientIP(), log.VL_DEBUG_OPT);
	return true;
}

bool TCPSocket::readBytes(std::string& bytes)
{
	if (!connected)
	{
		log.msg("[TCPSocket::readBytes] ERROR: Socket is not connected.",
			log.VL_ERROR);
		return false;
	}
	if (!log.assert(theSocket != 0, "[TCPSocket::readBytes] Socket is null."))
		return false;
	int bytesRead = 0;
	int bufferSize = READ_BUFFER_SIZE;
	char *readBuffer = new char[bufferSize];
	bytesRead = ::recv(theSocket, readBuffer, bufferSize - 1, 0);
	if (bytesRead <= 0)
	{
		log.msg("[TCPSocket::readBytes] DEBUG: End of file.",
			log.VL_DEBUG_OPT);
		delete[] readBuffer;
		return false;
	}
	bytes = string(readBuffer, bytesRead);
	delete[] readBuffer;
	return true;
}

bool TCPSocket::sendBytes(const std::string& bytes)
{
	if (!connected)
	{
		log.msg("[TCPSocket::sendBytes] ERROR: Socket is not connected.",
			log.VL_ERROR);
		return false;
	}
	if (!log.assert(theSocket != 0, "[TCPSocket::sendBytes] Socket is null."))
		return false;
	int bytesSent = 0;
	int bytesSentTotal = 0;
	int bytesLeft = bytes.size();
	bool result = true;
	while (bytesLeft && result)
	{
		bytesSent = ::send(theSocket, 
			bytes.substr(bytesSentTotal, bytesLeft).c_str(), bytesLeft, 0);
		if (bytesSent < 0)
		{
			log.msg("[TCPSocket::sendBytes] ERROR: Could not write to socket.",
				log.VL_ERROR);
			result = false;
		} else
		{
			bytesLeft -= bytesSent;
			bytesSentTotal += bytesSent;
		}
	}
	return result;
}

void TCPSocket::close()
{
	if ((theSocket != 0) && (connected || bound))
	{
		log.msg("[TCPSocket::close] DEBUG: Closing socket.", log.VL_DEBUG_OPT);
#ifndef HAVE_WINSOCK
		::close(theSocket);
#else
		// Special treatment for win32.
		::closesocket(theSocket);
#endif
		theSocket = 0;
		connected = false;
		bound = false;
		listening = false;
	}
}

void TCPSocket::setRemoteHost(const std::string& newHost)
{
	if (connected)
	{
		log.msg("[TCPSocket::setPort] WARNING: Ignored attempt to change "
			"remote host while connected.", log.VL_WARNING);
	} else
		remoteHostName = newHost;
}

void TCPSocket::setPort(int newPort)
{
	if (connected || bound)
	{
		log.msg("[TCPSocket::setPort] WARNING: Ignored attempt to change "
			"port while connected or bound.", log.VL_WARNING);
	} else
		port = newPort;
}

void TCPSocket::setListenQueue(int newListenQueue)
{
	if (listening)
	{
		log.msg("[TCPSocket::setPort] WARNING: Ignored attempt to change "
			"listen queue while listening.", log.VL_WARNING);
	} else
		listenQueue = newListenQueue;
}

void TCPSocket::setFD(int newFD)
{
	close();
	theSocket = newFD;
}

void TCPSocket::setConnectionState(bool newConnectionState)
{
	connected = newConnectionState;
}

void TCPSocket::setBindingState(bool newBindingState)
{
	bound = newBindingState;
}

void TCPSocket::setListeningState(bool newListeningState)
{
	listening = newListeningState;
}

void TCPSocket::setClientIP(const std::string &newClientIP)
{
	clientIP = newClientIP;
}

string TCPSocket::getRemoteHost()
{
	return remoteHostName;
}

int TCPSocket::getPort()
{
	return port;
}

int TCPSocket::getFD()
{
	return theSocket;
}

int TCPSocket::getListenQueue()
{
	return listenQueue;
}

bool TCPSocket::isConnected()
{
	return connected;
}

bool TCPSocket::isBound()
{
	return bound;
}

bool TCPSocket::isListening()
{
	return listening;
}

std::string TCPSocket::getClientIP()
{
	return clientIP;
}

Reporter &TCPSocket::getLog()
{
	return log;
}

}

}

/** \file TCPSocket.cpp
 * \brief TCP socket wrapper implementation.
 */
