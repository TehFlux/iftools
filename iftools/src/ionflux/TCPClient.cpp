/* ==========================================================================
 * Ionflux Tools
 * Copyright (c) 2004 Joern P. Meier
 * mail@ionflux.org
 * --------------------------------------------------------------------------
 * TCPClient.cpp                    Generic TCP client.
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

#include <algorithm>
#include "ionflux/TCPClient.hpp"

using namespace std;

namespace Ionflux
{

namespace Tools
{

TCPClient::TCPClient()
: interactive(true), currentPeerID(0), iomp(0), manageIomp(true), 
timeoutEvent(0)
{
	iomp = new SelectMultiplexer();
	iomp->getLog().redirect(&log);
	stdinEvent.fd = STDIN_FILENO;
	stdinEvent.type = IOEvent::IO_READ;
}

TCPClient::TCPClient(bool initInteractive)
: interactive(initInteractive), currentPeerID(0), iomp(0), manageIomp(true), 
timeoutEvent(0)
{
	iomp = new SelectMultiplexer();
	iomp->getLog().redirect(&log);
	stdinEvent.fd = STDIN_FILENO;
	stdinEvent.type = IOEvent::IO_READ;
}

TCPClient::TCPClient(bool initInteractive, IOMultiplexer *initIomp)
: interactive(initInteractive), currentPeerID(0), iomp(initIomp), 
  manageIomp(false)
{
	if (iomp == 0)
	{
		iomp = new SelectMultiplexer();
		manageIomp = true;
	}
	iomp->getLog().redirect(&log);
	stdinEvent.fd = STDIN_FILENO;
	stdinEvent.type = IOEvent::IO_READ;
}

TCPClient::~TCPClient()
{
	cleanup();
	if (manageIomp && (iomp != 0))
		delete iomp;
	iomp = 0;
	/* NOTE: Is this a good idea? The timeout event should have been 
	         removed by cleanup(). */
	if (timeoutEvent != 0)
	    delete timeoutEvent;
	timeoutEvent = 0;
}

TCPRemotePeer* TCPClient::createPeer(int peerID)
{
    return createPeer(peerID);
}

void TCPClient::destroyPeer(TCPRemotePeer *peer)
{
    delete peer;
}

void TCPClient::addPeer(TCPRemotePeer *peer)
{
	if (peer == 0)
	{
		log.msg("[TCPClient::addPeer] WARNING: Ignoring attempt to add "
			"null peer.", log.VL_WARNING);
		return;
	}
	ostringstream status;
	peers.push_back(peer);
	peer->getSocket().getLog().redirect(&log);
	status << "[TCPClient::addPeer] DEBUG: Peer " 
		<< peer->getID() << " added to peer vector. (" << peers.size()
		<< " peers connected)";
	log.msg(status.str(), log.VL_DEBUG_OPT);
}

void TCPClient::removePeer(TCPRemotePeer *peer)
{
	if (peer == 0)
	{
		log.msg("[TCPClient::removePeer] WARNING: Ignoring attempt to "
			"remove null peer.", log.VL_WARNING);
		return;
	}
	bool found = false;
	unsigned int i = 0;
	ostringstream status;
	while(!found && (i < peers.size()))
	{
		if (peers[i] == peer)
			found = true;
		else
			i++;
	}
	if (found)
	{
		peers.erase(peers.begin() + i);
		status << "[TCPClient::removePeer] DEBUG: Peer " 
			<< peer->getID() << " removed from peer vector. (" 
			<< peers.size() << " peers connected)";
		log.msg(status.str(), log.VL_DEBUG_OPT);
		destroyPeer(peer);
		peer = 0;
	} else
	{
		status.str("");
		status << "[TCPClient::removePeer] WARNING: Peer "
			<< peer->getID() << " does not exist.";
		log.msg(status.str(), log.VL_WARNING);
	}
}

void TCPClient::cleanupPeers()
{
	if (trash.size() > 0)
		log.msg("[TCPClient::cleanupPeers] DEBUG: Removing disconnected "
			"peers.", log.VL_DEBUG_OPT);
	else
		return;
	for (unsigned int i = 0; i < trash.size(); i++)
		removePeer(trash[i]);
	trash.clear();
}

void TCPClient::onConnect(TCPRemotePeer &peer)
{
	ostringstream status;
	status << "[TCPClient::onConnect] DEBUG: Peer " << peer.getID() 
		<< " connected.";
	log.msg(status.str(), log.VL_DEBUG_OPT);
}

void TCPClient::onReceive(TCPRemotePeer &peer)
{
	ostringstream status;
	status << "[TCPClient::onReceive] DEBUG: From peer " << peer.getID() 
		<< ":" << endl << makeNiceHex(makeHex(peer.getRecvBuf()), 
			makeReadable(peer.getRecvBuf(), "."), 16, 8) << endl;
	log.msg(status.str(), log.VL_DEBUG_OPT);
	peer.clearRecvBuf();
}

void TCPClient::onDisconnect(TCPRemotePeer &peer)
{
	ostringstream status;
	status << "[TCPClient::onDisconnect] DEBUG: Peer " << peer.getID() 
		<< " disconnected.";
	log.msg(status.str(), log.VL_DEBUG_OPT);
}

void TCPClient::onInput(const std::string &line)
{
	ostringstream status;
	status << "[TCPClient::onInput] DEBUG: From standard input: '" 
		<< line << "'" << endl;
	if ((line == "quit") || (line == "exit"))
		iomp->quit();
	else
		broadcast(line + "\r\n");
	log.msg(status.str(), log.VL_DEBUG_OPT);
}

void TCPClient::run()
{
	if (!log.assert(iomp != 0, "[TCPClient::run] IO multiplexer is null."))
		return;
	if (interactive)
		iomp->registerEvent(this, stdinEvent);
	iomp->run();
}

void TCPClient::cleanup()
{
	log.msg("[TCPClient::cleanup] DEBUG: Client cleanup.", log.VL_DEBUG);
	if (!log.assert(iomp != 0, "[TCPClient::cleanup] IO multiplexer is null."))
		return;
	enableTimeout(false);
	if (interactive)
		iomp->removeEvent(this, stdinEvent);
	log.msg("[TCPClient::cleanup] DEBUG: Cleaning up peer vector.", 
		log.VL_DEBUG_OPT);
	TCPRemotePeer *currentPeer;
	IOEvent currentEvent;
	for (unsigned int i = 0; i < peers.size(); i++)
	{
		currentPeer = peers[i];
		if (log.assert(currentPeer != 0, 
			"[TCPClient::cleanup] Peer is null."))
		{
			if (currentPeer->getSocket().isConnected())
			{
				currentEvent.fd = currentPeer->getSocket().getFD();
				currentEvent.peer = currentPeer;
				currentEvent.type = IOEvent::IO_READ;
				iomp->removeEvent(this, currentEvent);
				onDisconnect(*currentPeer);
				currentPeer->getSocket().close();
			}
			destroyPeer(peers[i]);
			peers[i] = 0;
		}
	}
	peers.clear();
	currentPeerID = 0;
	log.msg("[TCPClient::cleanup] DEBUG: Client cleanup complete.", 
		log.VL_DEBUG);
}

bool TCPClient::addConnection(const std::string &host, int port)
{
	if (!log.assert(iomp != 0, "[TCPClient::addConnection] "
		"IO multiplexer is null."))
		return false;
	TCPRemotePeer *newPeer = new TCPRemotePeer(currentPeerID);
	TCPSocket &socket = newPeer->getSocket();
	socket.setRemoteHost(host);
	socket.setPort(port);
	if (!socket.connect())
	{
		destroyPeer(newPeer);
		return false;
	}
	IOEvent newEvent;
	newEvent.fd = newPeer->getSocket().getFD();
	newEvent.peer = newPeer;
	newEvent.type = IOEvent::IO_READ;
	iomp->registerEvent(this, newEvent);
	addPeer(newPeer);
	onConnect(*newPeer);
	return true;
}

void TCPClient::enableTimeout(bool newState)
{
    if (!newState)
    {
        if (timeoutEvent == 0)
            // Timeout event not registered.
            return;
        iomp->removeEvent(this, *timeoutEvent);
        delete timeoutEvent;
        timeoutEvent = 0;
        return;
    }
    // Register new timeout event.
    timeoutEvent = new IOEvent();
    timeoutEvent->fd = 0;
    timeoutEvent->peer = 0;
    timeoutEvent->type = IOEvent::IO_TIMEOUT;
    iomp->registerEvent(this, *timeoutEvent);
}

void TCPClient::onTimeout()
{
    // Do nothing.
}

void TCPClient::onIO(const IOEvent &event)
{
	if (!log.assert(iomp != 0, "[TCPClient::onIO] IO multiplexer is null."))
		return;
    if ((event.type & IOEvent::IO_TIMEOUT) != 0)
    {
        onTimeout();
        return;
    }
	ostringstream status;
	TCPRemotePeer *currentPeer = 0;
	// Check for data on standard input.
	if (interactive && (event.fd == STDIN_FILENO))
	{
		string line;
		getline(cin, line);
		onInput(line);
	} else
	{
		// Check for incoming data.
		currentPeer = event.peer;
	    std::vector<TCPRemotePeer*>::iterator i = find(peers.begin(), 
	        peers.end(), currentPeer);
	    if (i == peers.end())
	    {
            status.str("");
            status << "[TCPClient::onIO] WARNING: Peer does not exist!";
            log.msg(status.str(), log.VL_WARNING);
	    } else
		if (currentPeer != 0)
		{
			if ((event.type & IOEvent::IO_READ) != 0)
			{
				if (!currentPeer->receive())
				{
					status.str("");
					status << "[TCPClient::onIO] DEBUG: Peer "
						<< currentPeer->getID() << " disconnected (fd = " 
						<< currentPeer->getSocket().getFD() << ").";
					log.msg(status.str(), log.VL_DEBUG_OPT);
					disconnect(currentPeer);
				} else
					onReceive(*currentPeer);
			} else
			{
				status.str("");
				status << "[TCPClient::onIO] ERROR: Received unrequested "
					"IO event for peer " << currentPeer->getID() << ".";
				log.msg(status.str(), log.VL_ERROR);
			}
			cleanupPeers();
		} else
		{
			status.str("");
			status << "[TCPClient::onIO] FATAL ERROR: Peer "
				<< currentPeer->getID() << " is null.";
			log.msg(status.str(), log.VL_ERROR_CRIT);
			iomp->quit();
		}
	}
}

void TCPClient::disconnect(TCPRemotePeer *peer)
{
	if (!log.assert(iomp != 0, "[TCPClient::disconnect] "
		"IO multiplexer is null."))
		return;
    /* <---- DEBUG ----- //
    std::ostringstream status;
    status << "[TCPClient::disconnect] DEBUG: peer = " << peer;
    log.msg(status.str(), log.VL_DEBUG_OPT);
    // ----- DEBUG ----> */
	if (peer == 0)
	{
		log.msg("[TCPClient::disconnect] WARNING: Ignoring attempt to "
			"disconnect null peer.", log.VL_WARNING);
		return;
	}
	IOEvent currentEvent;
	currentEvent.fd = peer->getSocket().getFD();
	currentEvent.peer = peer;
	currentEvent.type = IOEvent::IO_READ;
	iomp->removeEvent(this, currentEvent);
	onDisconnect(*peer);
	peer->getSocket().close();
	if (iomp->isRunning())
		trash.push_back(peer);
	else
		removePeer(peer);
}

void TCPClient::broadcast(const std::string &bytes)
{
	TCPRemotePeer *currentPeer;
	for (unsigned int i = 0; i < peers.size(); i++)
	{
		currentPeer = peers[i];
		if (currentPeer != 0)
			currentPeer->send(bytes);
	}
}

void TCPClient::shutdownHandler(int signum)
{
	SelectMultiplexer::shutdownHandler(signum);
}

Reporter &TCPClient::getLog()
{
	return log;
}

}

}

/** \file TCPClient.cpp
 * \brief Generic TCP client implementation.
 */
