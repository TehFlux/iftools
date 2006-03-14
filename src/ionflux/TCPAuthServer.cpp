/* ==========================================================================
 * Ionflux Tools
 * Copyright (c) 2004 Joern P. Meier
 * mail@ionflux.org
 * --------------------------------------------------------------------------
 * TCPAuthServer.cpp               Authenticated TCP server.
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

#include "ionflux/TCPAuthServer.hpp"

using namespace std;

namespace Ionflux
{

namespace Tools
{

const std::string TCPAuthServer::MAGIC_WORD = "IFTA";
const unsigned int TCPAuthServer::AUTH_VERSION = 0x000001L;
const unsigned int TCPAuthServer::AUTH_VERSION_UPPER = 0x000001L;
const unsigned int TCPAuthServer::AUTH_VERSION_LOWER = 0x000001L;
const int TCPAuthServer::MSGID_HELLO = 101;
const int TCPAuthServer::MSGID_WELCOME = 201;
const int TCPAuthServer::MSGID_AUTH = 102;
const int TCPAuthServer::MSGID_AUTH_OK = 202;
const int TCPAuthServer::MSGID_AUTH_FAILED = 401;
const int TCPAuthServer::PS_WAIT_HELLO = 1;
const int TCPAuthServer::PS_WAIT_AUTH = 2;
const int TCPAuthServer::PS_AUTH_OK = 3;

TCPAuthServer::TCPAuthServer()
: auth(0), authFileName(""), currentMsgID(0), randomizer(0)
{
	randomizer = new MTRand(time(0));
}

TCPAuthServer::TCPAuthServer(const std::string& initAuthFileName)
: auth(0), authFileName(initAuthFileName), currentMsgID(0), randomizer(0)
{
	auth = new AuthFile(authFileName);
	auth->getLog().redirect(&log);
	randomizer = new MTRand(time(0));
}

TCPAuthServer::~TCPAuthServer()
{
	if (auth != 0)
		delete auth;
	if (randomizer !=0)
		delete randomizer;
}

void TCPAuthServer::onConnect(TCPRemotePeer &client)
{
	ostringstream status;
	client.setMessageHandler(this);
	Message *message = client.getMessage();
	if (message == 0)
	{
		status << "[TCPAuthServer::onConnect] ERROR: Message of client " 
			<< client.getID() << " is null.";
		log.msg(status.str(), log.VL_ERROR);
		disconnect(&client);
		return;
	}
	message->getLog().redirect(&log);
	message->setMagicWord(TCPAuthServer::MAGIC_WORD);
	message->setProtocolVersion(TCPAuthServer::AUTH_VERSION);
	message->setAcceptableProtocolVersion(
		TCPAuthServer::AUTH_VERSION_LOWER, 
		TCPAuthServer::AUTH_VERSION_UPPER);
	client.setProtocolState(PS_WAIT_HELLO);
}

void TCPAuthServer::onMessage(TCPRemotePeer &peer)
{
	ostringstream status;
	Message *message = peer.getMessage();
	if (message == 0)
	{
		status.str("");
		status << "[TCPAuthServer::onMessage] ERROR: Message of peer " 
			<< peer.getID() << " is null.";
		log.msg(status.str(), log.VL_ERROR);
		disconnect(&peer);
		return;
	}
	status.str("");
	status << "[TCPAuthServer::onMessage] DEBUG: From peer " 
		<< peer.getID() << ":";
	log.msg(status.str(), log.VL_DEBUG_INSANE);
	if (log.getVerbosityLevel() >= log.VL_DEBUG_INSANE)
		message->printDebugInfo();
	int currentPS = peer.getProtocolState();
	int currentMsgType = message->getType();
	Message reply;
	string serialized;
	reply.getLog().redirect(&log);
	reply.setFlags(Message::FLAG_COMPRESS);
	reply.setMagicWord(TCPAuthServer::MAGIC_WORD);
	reply.setProtocolVersion(TCPAuthServer::AUTH_VERSION);
	reply.setAcceptableProtocolVersion(
		TCPAuthServer::AUTH_VERSION_LOWER, 
		TCPAuthServer::AUTH_VERSION_UPPER);
	reply.setUID(currentMsgID);
	if ((currentPS == PS_WAIT_HELLO) && (currentMsgType == MSGID_HELLO))
	{
		// Handle message: HELLO.
		status.str("");
		status << "[TCPAuthServer::onMessage] DEBUG: From peer " 
			<< peer.getID() << ": HELLO.";
		log.msg(status.str(), log.VL_DEBUG_OPT);
		peer.getAuthData().username = (*message)["user"].getData();
		if ((peer.getAuthData().username.size() == 0) || (auth == 0))
		{
			status.str("");
			status << "[TCPAuthServer::onMessage] DEBUG: Peer " 
				<< peer.getID() << ": Invalid username, disconnecting.";
			log.msg(status.str(), log.VL_DEBUG_OPT);
			onAuthFailed(peer);
			disconnect(&peer);
			return;
		}
		// Initialize user and session secret.
		auth->getSecret(peer.getAuthData().username, 
			peer.getAuthData().password);
		getRandomBytes(peer.getAuthData().sessionSecret, 20, randomizer);
		// Send message: WELCOME.
		status.str("");
		status << "[TCPAuthServer::onMessage] DEBUG: Sending to peer " 
			<< peer.getID() << ": WELCOME.";
		log.msg(status.str(), log.VL_DEBUG_OPT);
		reply.setType(MSGID_WELCOME);
		reply["sessionSecret"] = peer.getAuthData().sessionSecret;
		reply.serialize(serialized);
		peer.setProtocolState(PS_WAIT_AUTH);
		peer.send(serialized);
		// Switch peer to authenticated messages.
		message->setUsername(peer.getAuthData().username);
		message->setUserSecret(peer.getAuthData().password);
		message->setSessionSecret(peer.getAuthData().sessionSecret);
		currentMsgID++;
	} else
	if ((currentPS == PS_WAIT_AUTH) && (currentMsgType == MSGID_AUTH))
	{
		// Handle message: AUTH.
		status.str("");
		status << "[TCPAuthServer::onMessage] DEBUG: From peer " 
			<< peer.getID() << ": AUTH.";
		log.msg(status.str(), log.VL_DEBUG_OPT);
		// Send message: AUTH_OK.
		status.str("");
		status << "[TCPAuthServer::onMessage] DEBUG: Sending to peer " 
			<< peer.getID() << ": AUTH_OK.";
		log.msg(status.str(), log.VL_DEBUG_OPT);
		reply.setType(MSGID_AUTH_OK);
		reply["status"] = "Authentication successful.";
		reply.serialize(serialized);
		peer.setProtocolState(PS_AUTH_OK);
		peer.send(serialized);
		onAuthOK(peer);
		currentMsgID++;
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

void TCPAuthServer::onInvalidMessage(TCPRemotePeer &peer)
{
	ostringstream status;
	if ((peer.getProtocolState() >= PS_WAIT_AUTH) 
		&& (peer.getProtocolState() < PS_AUTH_OK))
	{
		// Send message: AUTH_FAILED.
		status.str("");
		status << "[TCPAuthServer::onInvalidMessage] DEBUG: Sending to peer " 
			<< peer.getID() << ": AUTH_FAILED.";
		log.msg(status.str(), log.VL_DEBUG_OPT);
		Message reply;
		string serialized;
		reply.getLog().redirect(&log);
		reply.setFlags(Message::FLAG_COMPRESS);
		reply.setMagicWord(TCPAuthServer::MAGIC_WORD);
		reply.setProtocolVersion(TCPAuthServer::AUTH_VERSION);
		reply.setAcceptableProtocolVersion(
			TCPAuthServer::AUTH_VERSION_LOWER, 
			TCPAuthServer::AUTH_VERSION_UPPER);
		reply.setUID(currentMsgID);
		reply.setType(MSGID_AUTH_FAILED);
		reply["status"] = "Authentication failed.";
		reply.serialize(serialized);
		peer.send(serialized);
		onAuthFailed(peer);
		currentMsgID++;
		status.str("");
		status << "[TCPAuthServer::onInvalidMessage] DEBUG: Peer " 
			<< peer.getID() << ": Authentication failed, disconnecting.";
		log.msg(status.str(), log.VL_DEBUG_OPT);
		disconnect(&peer);
	} else
	{
		status.str("");
		status << "[TCPAuthServer::onInvalidMessage] DEBUG: "
			"Invalid message from peer " << peer.getID() 
			<< ", disconnecting.";
		log.msg(status.str(), log.VL_DEBUG_OPT);
		disconnect(&peer);
	}
}

void TCPAuthServer::onAuthMessage(TCPRemotePeer &peer)
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

void TCPAuthServer::onAuthOK(TCPRemotePeer &peer)
{
	ostringstream status;
	status << "[TCPAuthServer::onAuthOK] DEBUG: Peer " 
		<< peer.getID() << ": Authentication successful.";
	log.msg(status.str(), log.VL_DEBUG_OPT);
}

void TCPAuthServer::onAuthFailed(TCPRemotePeer &peer)
{
	ostringstream status;
	status << "[TCPAuthServer::onAuthFailed] DEBUG: Peer " 
		<< peer.getID() << ": Authentication failed.";
	log.msg(status.str(), log.VL_DEBUG_OPT);
}

void TCPAuthServer::broadcast(const std::string &bytes)
{
	TCPRemotePeer *currentPeer;
	Message msg;
	msg.getLog().redirect(&log);
	msg.setFlags(Message::FLAG_COMPRESS);
	msg.setMagicWord(TCPAuthServer::MAGIC_WORD);
	msg.setProtocolVersion(TCPAuthServer::AUTH_VERSION);
	msg.setAcceptableProtocolVersion(
		TCPAuthServer::AUTH_VERSION_LOWER, 
		TCPAuthServer::AUTH_VERSION_UPPER);
	msg["data"] = bytes;
	string serialized;
	for (unsigned int i = 0; i < clients.size(); i++)
	{
		currentPeer = clients[i];
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

void TCPAuthServer::setAuth(Auth* newAuth)
{
	auth = newAuth;
}

void TCPAuthServer::setAuthFileName(const std::string& newAuthFileName)
{
	authFileName = newAuthFileName;
	if (auth != 0)
		delete auth;
	if (authFileName.size() == 0)
	{
		auth = 0;
		return;
	}
	auth = new AuthFile(authFileName);
	auth->getLog().redirect(&log);
}

void TCPAuthServer::setCurrentMsgID(unsigned int newCurrentMsgID)
{
        currentMsgID = newCurrentMsgID;
}

Auth* TCPAuthServer::getAuth()
{
	return auth;
}

std::string TCPAuthServer::getAuthFileName()
{
	return authFileName;
}

unsigned int TCPAuthServer::getCurrentMsgID()
{
	return currentMsgID;
}

}

}

/** \file TCPAuthServer.cpp
 * \brief Authenticated TCP server implementation.
 */
