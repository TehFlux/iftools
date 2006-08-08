/* ==========================================================================
 * Ionflux Tools
 * Copyright (c) 2004 Joern P. Meier
 * mail@ionflux.org
 * --------------------------------------------------------------------------
 * TCPMessageServer.cpp            Message based TCP server.
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

#include "ionflux/TCPMessageServer.hpp"

using namespace std;

namespace Ionflux
{

namespace Tools
{

TCPMessageServer::TCPMessageServer()
{
	// TODO: Nothing ATM. ;-)
}

TCPMessageServer::~TCPMessageServer()
{
	// TODO: Nothing ATM. ;-)
}

void TCPMessageServer::onConnect(TCPRemotePeer &client)
{
	client.setMessageHandler(this);
	Message *message = client.getMessage();
	if (message != 0)
		message->getLog().redirect(&log);
}

void TCPMessageServer::onReceive(TCPRemotePeer &client)
{
	client.clearRecvBuf();
}

void TCPMessageServer::onMessage(TCPRemotePeer &peer)
{
	ostringstream status;
	Message *message = peer.getMessage();
	if (message == 0)
	{
		status << "[TCPAuthServer::onMessage] ERROR: Message of peer " 
			<< peer.getID() << " is null.";
		log.msg(status.str(), log.VL_ERROR);
		disconnect(&peer);
		return;
	}
	status << "[TCPAuthServer::onAuthMessage] DEBUG: From peer " 
		<< peer.getID() << ":";
	log.msg(status.str(), log.VL_DEBUG_OPT);
	if (log.getVerbosityLevel() >= log.VL_DEBUG_OPT)
		message->printDebugInfo();
}

void TCPMessageServer::onInvalidMessage(TCPRemotePeer &peer)
{
	ostringstream status;
	status << "[TCPMessageServer::onInvalidMessage] DEBUG: "
		"Invalid message from peer " << peer.getID() 
		<< ", disconnecting.";
	log.msg(status.str(), log.VL_DEBUG_OPT);
	disconnect(&peer);
}

void TCPMessageServer::broadcast(const std::string &bytes)
{
	TCPRemotePeer *currentPeer;
	Message msg;
	msg.getLog().redirect(&log);
	msg.setFlags(Message::FLAG_COMPRESS);
	msg["data"] = bytes;
	string serialized;
	msg.serialize(serialized);
	for (unsigned int i = 0; i < clients.size(); i++)
	{
		currentPeer = clients[i];
		if (currentPeer != 0)
			currentPeer->send(serialized);
	}
}

}

}

/** \file TCPMessageServer.cpp
 * \brief Message based TCP server implementation.
 */
