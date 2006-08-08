/* ==========================================================================
 * Ionflux Tools
 * Copyright (c) 2004 Joern P. Meier
 * mail@ionflux.org
 * --------------------------------------------------------------------------
 * TCPAuthClient.cpp               Authenticated TCP client.
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

#include "ionflux/TCPAuthClient.hpp"

using namespace std;

namespace Ionflux
{

namespace Tools
{

const std::string TCPAuthClient::MAGIC_WORD = "IFTA";
const unsigned int TCPAuthClient::AUTH_VERSION = 0x000001L;
const unsigned int TCPAuthClient::AUTH_VERSION_UPPER = 0x000001L;
const unsigned int TCPAuthClient::AUTH_VERSION_LOWER = 0x000001L;
const int TCPAuthClient::MSGID_HELLO = 101;
const int TCPAuthClient::MSGID_WELCOME = 201;
const int TCPAuthClient::MSGID_AUTH = 102;
const int TCPAuthClient::MSGID_AUTH_OK = 202;
const int TCPAuthClient::MSGID_AUTH_FAILED = 401;
const int TCPAuthClient::PS_WAIT_WELCOME = 1;
const int TCPAuthClient::PS_WAIT_AUTH_RESULT = 2;
const int TCPAuthClient::PS_AUTH_OK = 3;

TCPAuthClient::TCPAuthClient()
: username(""), password(""), currentMsgID(0)
{
	// TODO: Nothing ATM. ;-)
}

TCPAuthClient::TCPAuthClient(bool initInteractive)
{
	interactive = initInteractive;
}

TCPAuthClient::TCPAuthClient(const std::string &initUsername, 
	const std::string &initPassword, bool initInteractive)
: username(initUsername), password(initPassword), currentMsgID(0)
{
	interactive = initInteractive;
	currentPeerID = 0;
}

TCPAuthClient::~TCPAuthClient()
{
	// TODO: Nothing ATM. ;-)
}

void TCPAuthClient::onConnect(TCPRemotePeer &peer)
{
	ostringstream status;
	peer.setMessageHandler(this);
	if (peer.getAuthData().username.size() == 0)
		peer.getAuthData().username = username;
	if (peer.getAuthData().password.size() == 0)
		peer.getAuthData().password = password;
	Message *message = peer.getMessage();
	if (message == 0)
	{
		status << "[TCPAuthClient::onConnect] ERROR: Message of peer " 
			<< peer.getID() << " is null.";
		log.msg(status.str(), log.VL_ERROR);
		disconnect(&peer);
		return;
	}
	message->getLog().redirect(&log);
	message->setMagicWord(TCPAuthClient::MAGIC_WORD);
	message->setProtocolVersion(TCPAuthClient::AUTH_VERSION);
	message->setAcceptableProtocolVersion(
		TCPAuthClient::AUTH_VERSION_LOWER, 
		TCPAuthClient::AUTH_VERSION_UPPER);
	// Send message: HELLO.
	Message msg;
	string serialized;
	msg.getLog().redirect(&log);
	msg.setFlags(Message::FLAG_COMPRESS);
	msg.setMagicWord(TCPAuthClient::MAGIC_WORD);
	msg.setProtocolVersion(TCPAuthClient::AUTH_VERSION);
	msg.setAcceptableProtocolVersion(
		TCPAuthClient::AUTH_VERSION_LOWER, 
		TCPAuthClient::AUTH_VERSION_UPPER);
	msg.setUID(currentMsgID);
	msg.setType(MSGID_HELLO);
	msg["user"] = peer.getAuthData().username;
	msg.serialize(serialized);
	peer.setProtocolState(PS_WAIT_WELCOME);
	peer.send(serialized);
}

void TCPAuthClient::onMessage(TCPRemotePeer &peer)
{
	ostringstream status;
	Message *message = peer.getMessage();
	if (message == 0)
	{
		status.str("");
		status << "[TCPAuthClient::onMessage] ERROR: Message of peer " 
			<< peer.getID() << " is null.";
		log.msg(status.str(), log.VL_ERROR);
		disconnect(&peer);
		return;
	}
	status.str("");
	status << "[TCPAuthClient::onMessage] DEBUG: From peer " 
		<< peer.getID() << ":";
	log.msg(status.str(), log.VL_DEBUG_INSANE);
	if (log.getVerbosityLevel() >= log.VL_DEBUG_INSANE)
		message->printDebugInfo();
	int currentPS = peer.getProtocolState();
	int currentMsgType = message->getType();
	Message reply;
	string serialized;
	string msgText;
	reply.getLog().redirect(&log);
	reply.setFlags(Message::FLAG_COMPRESS);
	reply.setMagicWord(TCPAuthClient::MAGIC_WORD);
	reply.setProtocolVersion(TCPAuthClient::AUTH_VERSION);
	reply.setAcceptableProtocolVersion(
		TCPAuthClient::AUTH_VERSION_LOWER, 
		TCPAuthClient::AUTH_VERSION_UPPER);
	reply.setUID(currentMsgID);
	if ((currentPS == PS_WAIT_WELCOME) && (currentMsgType == MSGID_WELCOME))
	{
		// Handle message: WELCOME.
		status.str("");
		status << "[TCPAuthClient::onMessage] DEBUG: From peer " 
			<< peer.getID() << ": WELCOME.";
		log.msg(status.str(), log.VL_DEBUG_OPT);
		peer.getAuthData().sessionSecret = 
			(*message)["sessionSecret"].getData();
		reply.setUsername(peer.getAuthData().username);
		reply.setUserSecret(peer.getAuthData().password);
		reply.setSessionSecret(peer.getAuthData().sessionSecret);
		// Send message: AUTH.
		status.str("");
		status << "[TCPAuthClient::onMessage] DEBUG: Sending to peer " 
			<< peer.getID() << ": AUTH.";
		log.msg(status.str(), log.VL_DEBUG_OPT);
		reply.setType(MSGID_AUTH);
		reply.serialize(serialized);
		peer.setProtocolState(PS_WAIT_AUTH_RESULT);
		peer.send(serialized);
		currentMsgID++;
	} else
	if ((currentPS == PS_WAIT_AUTH_RESULT) 
		&& (currentMsgType == MSGID_AUTH_OK))
	{
		// Handle message: AUTH_OK.
		msgText = (*message)["status"].getData();
		status.str("");
		status << "[TCPAuthClient::onMessage] DEBUG: From peer " 
			<< peer.getID() << ": AUTH_OK. (" << msgText << ")";
		log.msg(status.str(), log.VL_DEBUG_OPT);
		peer.setProtocolState(PS_AUTH_OK);
		// Switch peer to authenticated messages.
		message->setUsername(peer.getAuthData().username);
		message->setUserSecret(peer.getAuthData().password);
		message->setSessionSecret(peer.getAuthData().sessionSecret);
		onAuthOK(peer);
		currentMsgID++;
	} else
	if ((currentPS == PS_WAIT_AUTH_RESULT) 
		&& (currentMsgType == MSGID_AUTH_FAILED))
	{
		// Handle message: AUTH_FAILED.
		msgText = (*message)["status"].getData();
		status.str("");
		status << "[TCPAuthClient::onMessage] DEBUG: From peer " 
			<< peer.getID() << ": AUTH_FAILED. (" << msgText << ")";
		log.msg(status.str(), log.VL_DEBUG_OPT);
		onAuthFailed(peer);
		currentMsgID++;
		status.str("");
		status << "[TCPAuthClient::onMessage] DEBUG: Peer " 
			<< peer.getID() << ": Authentication failed, disconnecting.";
		log.msg(status.str(), log.VL_DEBUG_OPT);
		disconnect(&peer);
	} else
	if (currentPS >= PS_AUTH_OK)
	{
		// Handle authenticated messages.
		onAuthMessage(peer);
		currentMsgID++;
	} else
	{
		status << "[TCPAuthServer::onMessage] ERROR: Peer " 
			<< peer.getID() << ": Invalid protocol state, disconnecting. "
			"(protocol state: " << currentPS << ", message type: " 
			<< currentMsgType << ")";
		log.msg(status.str(), log.VL_ERROR);
		disconnect(&peer);
		return;
	}
}

void TCPAuthClient::onInvalidMessage(TCPRemotePeer &peer)
{
	ostringstream status;
	status.str("");
	status << "[TCPAuthClient::onInvalidMessage] DEBUG: "
		"Invalid message from peer " << peer.getID() 
		<< ", disconnecting.";
	log.msg(status.str(), log.VL_DEBUG_OPT);
	disconnect(&peer);
}

void TCPAuthClient::onAuthMessage(TCPRemotePeer &peer)
{
	ostringstream status;
	Message *message = peer.getMessage();
	if (message == 0)
	{
		status << "[TCPAuthClient::onMessage] ERROR: Message of peer " 
			<< peer.getID() << " is null.";
		log.msg(status.str(), log.VL_ERROR);
		disconnect(&peer);
		return;
	}
	status << "[TCPAuthClient::onAuthMessage] DEBUG: From peer " 
		<< peer.getID() << ":";
	log.msg(status.str(), log.VL_DEBUG_OPT);
	if (log.getVerbosityLevel() >= log.VL_DEBUG_OPT)
		message->printDebugInfo();
}

void TCPAuthClient::onAuthOK(TCPRemotePeer &peer)
{
	ostringstream status;
	status << "[TCPAuthClient::onAuthOK] DEBUG: Peer " 
		<< peer.getID() << ": Authentication successful.";
	log.msg(status.str(), log.VL_DEBUG_OPT);
}

void TCPAuthClient::onAuthFailed(TCPRemotePeer &peer)
{
	ostringstream status;
	status << "[TCPAuthClient::onAuthFailed] DEBUG: Peer " 
		<< peer.getID() << ": Authentication failed.";
	log.msg(status.str(), log.VL_DEBUG_OPT);
}

void TCPAuthClient::broadcast(const std::string &bytes)
{
	TCPRemotePeer *currentPeer;
	Message msg;
	msg.getLog().redirect(&log);
	msg.setFlags(Message::FLAG_COMPRESS);
	msg.setMagicWord(TCPAuthClient::MAGIC_WORD);
	msg.setProtocolVersion(TCPAuthClient::AUTH_VERSION);
	msg.setAcceptableProtocolVersion(
		TCPAuthClient::AUTH_VERSION_LOWER, 
		TCPAuthClient::AUTH_VERSION_UPPER);
	msg["data"] = bytes;
	string serialized;
	for (unsigned int i = 0; i < peers.size(); i++)
	{
		currentPeer = peers[i];
		if (currentPeer != 0)
		{
			msg.setUID(currentMsgID);
			msg.setUsername(currentPeer->getAuthData().username);
			msg.setUserSecret(currentPeer->getAuthData().password);
			msg.setSessionSecret(currentPeer->getAuthData().sessionSecret);
			msg.serialize(serialized);
			currentPeer->send(serialized);
		}
		currentMsgID++;
	}
}

bool TCPAuthClient::addConnection(const std::string &host, int port, 
	const std::string &connUser, const std::string &connPass)
{
	if (!log.assert(iomp != 0, "[TCPClient::addConnection] "
		"IO multiplexer is null."))
		return false;
	TCPRemotePeer *newPeer = new TCPRemotePeer(currentPeerID);
	TCPSocket &socket = newPeer->getSocket();
	socket.setRemoteHost(host);
	socket.setPort(port);
	if (!socket.connect())
		return false;
	newPeer->getAuthData().username = connUser;
	newPeer->getAuthData().password = connPass;
	IOEvent newEvent;
	newEvent.fd = newPeer->getSocket().getFD();
	newEvent.peer = newPeer;
	newEvent.type = IOEvent::IO_READ;
	iomp->registerEvent(this, newEvent);
	addPeer(newPeer);
	onConnect(*newPeer);
	return true;
}

void TCPAuthClient::setUsername(const std::string& newUsername)
{
	username = newUsername;
}

void TCPAuthClient::setPassword(const std::string& newPassword)
{
	password = newPassword;
}

void TCPAuthClient::setCurrentMsgID(unsigned int newCurrentMsgID)
{
	currentMsgID = newCurrentMsgID;
}

std::string TCPAuthClient::getUsername()
{
	return username;
}

void TCPAuthClient::getPassword(std::string &target)
{
	target = password;
}

unsigned int TCPAuthClient::getCurrentMsgID()
{
	return currentMsgID;
}

}

}

/** \file TCPAuthClient.cpp
 * \brief Authenticated TCP client implementation.
 */
