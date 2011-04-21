/* ==========================================================================
 * Ionflux Tools
 * Copyright (c) 2004 Joern P. Meier
 * mail@ionflux.org
 * --------------------------------------------------------------------------
 * TCPRemotePeer.cpp                    Remote peer of a TCP connection.
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

#include "ionflux/TCPRemotePeer.hpp"

using namespace std;

namespace Ionflux
{

namespace Tools
{

const int TCPRemotePeer::ID_NOT_SET = -1;
const int TCPRemotePeer::PROTOCOL_STATE_UNDEFINED = -1;

TCPRemotePeer::TCPRemotePeer()
: id(ID_NOT_SET), recvBuf(""), protocolState(PROTOCOL_STATE_UNDEFINED), 
  data(0), dataSize(0), message(0), messageHandler(0), cache(0), 
  socketIOHandler(0)
{
	// TODO: Nothing ATM. ;-)
}

TCPRemotePeer::TCPRemotePeer(int initID)
: id(initID), recvBuf(""), protocolState(PROTOCOL_STATE_UNDEFINED), 
  data(0), dataSize(0), message(0), messageHandler(0), cache(0), 
  socketIOHandler(0)
{
	// TODO: Nothing ATM. ;-)
}

TCPRemotePeer::~TCPRemotePeer()
{
	if (message != 0)
		delete message;
	message = 0;
	if (cache != 0)
		delete cache;
	cache = 0;
	for (unsigned int i = 0; i < auth.password.size(); i++)
		auth.password[i] = '\0';
	for (unsigned int i = 0; i < auth.sessionSecret.size(); i++)
		auth.sessionSecret[i] = '\0';
}

bool TCPRemotePeer::receive()
{
	string bytes;
	bool result;
	if (socketIOHandler == 0)
	    result = socket.readBytes(bytes);
	else
	    result = socketIOHandler->readBytes(socket, bytes);
	if (result)
	{
		if ((message == 0) || (messageHandler == 0))
			recvBuf.append(bytes);
		else
		{
			if (!message->append(bytes))
				messageHandler->onInvalidMessage(*this);
		}
	}
	return result;
}

bool TCPRemotePeer::send(const std::string &bytes)
{
	bool result;
	if (socketIOHandler == 0)
	    result = socket.sendBytes(bytes);
	else
	    result = socketIOHandler->sendBytes(socket, bytes);
	return result;
}

void TCPRemotePeer::setID(int newID)
{
	id = newID;
}

void TCPRemotePeer::setProtocolState(int newProtocolState)
{
	protocolState = newProtocolState;
}

void TCPRemotePeer::setMessageHandler(MessageHandler *newMessageHandler)
{
	messageHandler = newMessageHandler;
	if ((messageHandler != 0) && (message == 0))
	{
		message = new Message();
		message->setTarget(this);
	}
}

void TCPRemotePeer::setSocketIOHandler(TCPSocketIOHandler* 
    newSocketIOHandler)
{
    socketIOHandler = newSocketIOHandler;
}

void TCPRemotePeer::setData(void* newData, unsigned int newDataSize)
{
    data = newData;
    dataSize = newDataSize;
}

int TCPRemotePeer::getID()
{
	return id;
}

TCPSocket &TCPRemotePeer::getSocket()
{
	return socket;
}

AuthData &TCPRemotePeer::getAuthData()
{
	return auth;
}

std::string &TCPRemotePeer::getRecvBuf()
{
	return recvBuf;
}

unsigned int TCPRemotePeer::removeRecvBytes(unsigned int numBytes)
{
	if (numBytes >= recvBuf.size())
	{
		recvBuf = "";
		return 0;
	}
	recvBuf = recvBuf.substr(numBytes, recvBuf.size() - numBytes);
	return recvBuf.size();
}

void TCPRemotePeer::clearRecvBuf()
{
	recvBuf = "";
}

int TCPRemotePeer::getProtocolState()
{
	return protocolState;
}

void *TCPRemotePeer::getData()
{
	return data;
}

unsigned int TCPRemotePeer::getDataSize()
{
	return dataSize;
}

Message *TCPRemotePeer::getMessage()
{
	return message;
}

Node *TCPRemotePeer::getCache()
{
	if (cache == 0)
	{
		// Allocate cache node on demand.
		cache = new Node;
		cache->setAutoCreate(true);
		cache->setIndexMode(Node::INDEX_MODE_NODE);
	}
	return cache;
}

void TCPRemotePeer::dump(Message &msg)
{
	if ((messageHandler != 0) && (message != 0))
		messageHandler->onMessage(*this);
	return;
}

}

}

/** \file TCPRemotePeer.cpp
 * \brief Remote peer of a TCP connection implementation.
 */
