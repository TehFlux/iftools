/* ==========================================================================
 * Ionflux Tools
 * Copyright (c) 2004 Joern P. Meier
 * mail@ionflux.org
 * --------------------------------------------------------------------------
 * TCPMessageClient.cpp                    Message based TCP Client.
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

#include "ionflux/TCPMessageClient.hpp"

using namespace std;

namespace Ionflux
{

namespace Tools
{

TCPMessageClient::TCPMessageClient()
{
	// TODO: Nothing ATM. ;-)
}

TCPMessageClient::TCPMessageClient(bool initInteractive)
{
	interactive = initInteractive;
	currentPeerID = 0;
}

TCPMessageClient::~TCPMessageClient()
{
	// TODO: Nothing ATM. ;-)
}

void TCPMessageClient::onConnect(TCPRemotePeer &peer)
{
	peer.setMessageHandler(this);
	Message *message = peer.getMessage();
	if (message != 0)
		message->getLog().redirect(&log);
}

void TCPMessageClient::onReceive(TCPRemotePeer &peer)
{
	peer.clearRecvBuf();
}

void TCPMessageClient::onInput(const std::string &line)
{
	broadcast(line);
}

void TCPMessageClient::onMessage(TCPRemotePeer &peer)
{
	ostringstream status;
	Message *message = peer.getMessage();
	if (message != 0)
	{
		status << "[TCPMessageClient::onMessage] DEBUG: From peer " 
			<< peer.getID() << ":";
		log.msg(status.str(), log.VL_DEBUG_OPT);
		message->printDebugInfo();
	}
}

void TCPMessageClient::onInvalidMessage(TCPRemotePeer &peer)
{
	ostringstream status;
	status << "[TCPMessageClient::onInvalidMessage] DEBUG: "
		"Invalid message from peer " << peer.getID() 
		<< ", disconnecting.";
	log.msg(status.str(), log.VL_DEBUG_OPT);
	disconnect(&peer);
}

void TCPMessageClient::broadcast(const std::string &bytes)
{
	TCPRemotePeer *currentPeer;
	Message msg;
	msg.setFlags(Message::FLAG_COMPRESS);
	msg["data"] = bytes;
	string serialized;
	msg.serialize(serialized);
	for (unsigned int i = 0; i < peers.size(); i++)
	{
		currentPeer = peers[i];
		if (currentPeer != 0)
			currentPeer->send(serialized);
	}
}

}

}

/** \file TCPMessageClient.cpp
 * \brief Message based TCP Client implementation.
 */
