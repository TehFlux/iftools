/* ==========================================================================
 * Ionflux Tools
 * Copyright (c) 2004 Joern P. Meier
 * mail@ionflux.org
 * --------------------------------------------------------------------------
 * TCPServer.cpp                    Generic TCP server.
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

#include "ionflux/TCPServer.hpp"

using namespace std;

namespace Ionflux
{

namespace Tools
{

const int TCPServer::DEFAULT_MAX_CLIENTS = 0;
const int TCPServer::REJECTED_REASON_MAX_CLIENTS = 0;
const int TCPServer::REJECTED_REASON_VERIFICATION_FAILED = 1;

TCPServer::TCPServer()
: maxClients(DEFAULT_MAX_CLIENTS), iomp(0), manageIomp(true), timeoutEvent(0)
{
	serverSocket.getLog().redirect(&log);
	iomp = new SelectMultiplexer();
    manageIomp = true;
	iomp->getLog().redirect(&log);
}

TCPServer::TCPServer(IOMultiplexer *initIomp)
: maxClients(DEFAULT_MAX_CLIENTS), iomp(initIomp), manageIomp(false), 
timeoutEvent(0)
{
	serverSocket.getLog().redirect(&log);
	if (iomp == 0)
	{
		iomp = new SelectMultiplexer();
		manageIomp = true;
	}
	iomp->getLog().redirect(&log);
}

TCPServer::~TCPServer()
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

void TCPServer::addClient(TCPRemotePeer *client)
{
	if (client == 0)
	{
		log.msg("[TCPServer::addClient] WARNING: Ignoring attempt to add "
			"null client.", log.VL_WARNING);
		return;
	}
	ostringstream status;
	clients.push_back(client);
	client->getSocket().getLog().redirect(&log);
	status << "[TCPServer::addClient] DEBUG: Client " 
		<< client->getID() << " added to client vector. (" << clients.size()
		<< " clients connected)";
	log.msg(status.str(), log.VL_DEBUG_OPT);
}

void TCPServer::removeClient(TCPRemotePeer *client)
{
	if (client == 0)
	{
		log.msg("[TCPServer::removeClient] WARNING: Ignoring attempt to "
			"remove null client.", log.VL_WARNING);
		return;
	}
	bool found = false;
	unsigned int i = 0;
	ostringstream status;
	while(!found && (i < clients.size()))
	{
		if (clients[i] == client)
			found = true;
		else
			i++;
	}
	if (found)
	{
		clients.erase(clients.begin() + i);
		status << "[TCPServer::removeClient] DEBUG: Client " 
			<< client->getID() << " removed from client vector. (" 
			<< clients.size() << " clients connected)";
		log.msg(status.str(), log.VL_DEBUG_OPT);
		delete client;
		client = 0;
	} else
	{
		status.str("");
		status << "[TCPServer::removeClient] WARNING: Client "
			<< client->getID() << " does not exist.";
		log.msg(status.str(), log.VL_WARNING);
	}
}

void TCPServer::cleanupClients()
{
	if (trash.size() > 0)
		log.msg("[TCPServer::cleanupClients] DEBUG: Removing disconnected "
			"clients.", log.VL_DEBUG_OPT);
	else
		return;
	for (unsigned int i = 0; i < trash.size(); i++)
		removeClient(trash[i]);
	trash.clear();
}

bool TCPServer::init()
{
	if (!log.assert(iomp != 0, "[TCPServer::init] IO multiplexer is null."))
		return false;
	cleanup();
	log.msg("[TCPServer::init] DEBUG: Server startup.", log.VL_DEBUG);
	log.msg("[TCPServer::init] DEBUG: Bind to local interface.", 
		log.VL_DEBUG_OPT);
    bool bindResult = false;
    if (address.size() == 0)
        // Bind to any address.
        bindResult = serverSocket.bind();
    else
    {
        // Bind to specific address.
        in_addr address0;
        if (::inet_pton(AF_INET, address.c_str(), &address0) != 1)
        {
            ostringstream status;
            status << "[TCPServer::init] ERROR: Invalid bind address: " 
                << address;
            log.msg(status.str(), log.VL_ERROR);
            return false;
        }
        bindResult = serverSocket.bind(address0.s_addr);
    }
	if (!bindResult)
	{
		log.msg("[TCPServer::init] ERROR: Bind failed.", log.VL_ERROR);
		return false;
	}
	log.msg("[TCPServer::init] DEBUG: Listen on socket.", log.VL_DEBUG_OPT);
	if (!serverSocket.listen())
	{
		log.msg("[TCPServer::init] ERROR: Listen failed.", log.VL_ERROR);
		return false;
	}
	log.msg("[TCPServer::init] DEBUG: Server startup complete.", 
		log.VL_DEBUG);
	// Register IO event for the server socket.
	serverSocketEvent.fd = serverSocket.getFD();
	serverSocketEvent.type = IOEvent::IO_READ;
	iomp->registerEvent(this, serverSocketEvent);
	return true;
}

void TCPServer::run()
{
	if (!log.assert(iomp != 0, "[TCPServer::run] IO multiplexer is null."))
		return;
	if (!serverSocket.isListening())
	{
		log.msg("[TCPServer::run] ERROR: Server socket not listening.", 
			log.VL_ERROR_CRIT);
		return;
	}
	iomp->run();
}

void TCPServer::cleanup()
{
	log.msg("[TCPServer::cleanup] DEBUG: Server cleanup.", log.VL_DEBUG);
	if (!log.assert(iomp != 0, "[TCPServer::cleanup] IO multiplexer is null."))
		return;
	enableTimeout(false);
	if (serverSocket.isBound())
	{
		log.msg("[TCPServer::cleanup] DEBUG: Taking down server socket.", 
			log.VL_DEBUG_OPT);
		iomp->removeEvent(this, serverSocketEvent);
		serverSocket.close();
	}
	log.msg("[TCPServer::cleanup] DEBUG: Cleaning up client vector.", 
		log.VL_DEBUG_OPT);
	TCPRemotePeer *currentClient;
	IOEvent currentEvent;
	for (unsigned int i = 0; i < clients.size(); i++)
	{
		currentClient = clients[i];
		if (log.assert(currentClient != 0, 
			"[TCPServer::cleanup] Client is null."))
		{
			if (currentClient->getSocket().isConnected())
			{
				currentEvent.fd = currentClient->getSocket().getFD();
				currentEvent.peer = currentClient;
				currentEvent.type = IOEvent::IO_READ;
				iomp->removeEvent(this, currentEvent);
				onDisconnect(*currentClient);
				currentClient->getSocket().close();
			}
			delete clients[i];
			clients[i] = 0;
		}
	}
	clients.clear();
	currentClientID = 0;
	log.msg("[TCPServer::cleanup] DEBUG: Server cleanup complete.", 
		log.VL_DEBUG);
}

void TCPServer::enableTimeout(bool newState)
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

bool TCPServer::verifyConnect(TCPRemotePeer& client)
{
	ostringstream status;
	status << "[TCPServer::verifyConnect] DEBUG: Accepting client " 
	    << client.getID() << " (" << client.getSocket().getClientIP() 
	    << ").";
	log.msg(status.str(), log.VL_DEBUG_OPT);
	return true;
}

void TCPServer::onTimeout()
{
    // Do nothing.
}

void TCPServer::onConnect(TCPRemotePeer &client)
{
	ostringstream status;
	status << "[TCPServer::onConnect] DEBUG: Client " << client.getID() 
		<< " connected.";
	log.msg(status.str(), log.VL_DEBUG_OPT);
}

void TCPServer::onReject(TCPRemotePeer &client, int reason)
{
	ostringstream status;
	status << "[TCPServer::onReject] DEBUG: Connection for client " 
		<< client.getID() << " rejected. (Reason: " << reason << ")";
	log.msg(status.str(), log.VL_DEBUG_OPT);
}

void TCPServer::onReceive(TCPRemotePeer &client)
{
	ostringstream status;
	status << "[TCPServer::onReceive] DEBUG: From client " << client.getID() 
		<< ":" << endl << makeNiceHex(makeHex(client.getRecvBuf()), 
			makeReadable(client.getRecvBuf(), "."), 16, 8);
	log.msg(status.str(), log.VL_DEBUG_OPT);
	client.clearRecvBuf();
}


void TCPServer::onDisconnect(TCPRemotePeer &client)
{
	ostringstream status;
	status << "[TCPServer::onDisconnect] DEBUG: Client " << client.getID() 
		<< " disconnected.";
	log.msg(status.str(), log.VL_DEBUG_OPT);
}

Ionflux::Tools::TCPRemotePeer* TCPServer::createRemotePeer(int clientID)
{
    TCPRemotePeer* newPeer = new TCPRemotePeer(clientID);
    if (newPeer == 0)
    {
        log.msg("[TCPServer::createRemotePeer] ERROR: "
            "Could not allocate remote peer object.", log.VL_ERROR);
    }
    return newPeer;
}

void TCPServer::onIO(const IOEvent &event)
{
	if (!log.assert(iomp != 0, "[TCPServer::onIO] IO multiplexer is null."))
		return;
    if ((event.type & IOEvent::IO_TIMEOUT) != 0)
    {
        onTimeout();
        return;
    }
	ostringstream status;
	int serverFD = serverSocket.getFD();
	TCPRemotePeer *currentClient = 0;
	IOEvent currentEvent;
	// Check for new connections on listening socket.
	if (event.fd == serverFD)
	{
		log.msg("[TCPServer::onIO] DEBUG: Incoming connection.",
			log.VL_DEBUG_OPT);
		currentClient = createRemotePeer(currentClientID);
		if (!serverSocket.accept(currentClient->getSocket()))
		{
			log.msg("[TCPServer::onIO] ERROR: Failed to accept "
				"client connection", log.VL_ERROR);
			delete currentClient;
			currentClient = 0;
		} else
		{
		    bool accepted = true;
		    int reason = 0;
		    std::string msgReason;
		    if ((maxClients > 0) && (clients.size() >= maxClients))
		    {
		        msgReason = "Maximum number of clients connected.";
				reason = REJECTED_REASON_MAX_CLIENTS;
		        accepted = false;
		    } else
            if (!verifyConnect(*currentClient))
            {
                msgReason = "Verification failed.";
				log.msg(status.str(), log.VL_DEBUG_OPT);
		        accepted = false;
            }
			if (accepted)
			{
				currentEvent.fd = currentClient->getSocket().getFD();
				currentEvent.peer = currentClient;
				currentEvent.type = IOEvent::IO_READ;
				iomp->registerEvent(this, currentEvent);
				addClient(currentClient);
				status.str("");
				status << "[TCPServer::onIO] DEBUG: Accepted client "
					"connection for client " << currentClient->getID() 
					<< " from " << currentClient->getSocket().getClientIP() 
					<< " (fd = " << currentClient->getSocket().getFD() << ").";
				log.msg(status.str(), log.VL_DEBUG_OPT);
				currentClientID++;
				onConnect(*currentClient);
			} else
			{
				status.str("");
				status << "[TCPServer::onIO] DEBUG: Rejecting client "
					"connection for client " << currentClient->getID() 
					<< " from " << currentClient->getSocket().getClientIP() 
					<< " (fd = " << currentClient->getSocket().getFD() 
					<< "): " << msgReason;
				log.msg(status.str(), log.VL_DEBUG_OPT);
				onReject(*currentClient, reason);
				currentClient->getSocket().close();
				delete currentClient;
				currentClient = 0;
			}
		}
	} else
	{
		// Check for incoming data.
		currentClient = event.peer;
		if (currentClient != 0)
		{
			if ((event.type & IOEvent::IO_READ) != 0)
			{
				if (!currentClient->receive())
				{
					status.str("");
					status << "[TCPServer::onIO] DEBUG: Client "
						<< currentClient->getID() << " disconnected (fd = " 
						<< currentClient->getSocket().getFD() << ").";
					log.msg(status.str(), log.VL_DEBUG_OPT);
					disconnect(currentClient);
				} else
					onReceive(*currentClient);
			} else
			{
				status.str("");
				status << "[TCPServer::onIO] ERROR: Received unrequested "
					"IO event for client " << currentClient->getID() << ".";
				log.msg(status.str(), log.VL_ERROR);
			}
			cleanupClients();
		} else
		{
			status.str("");
			status << "[TCPServer::onIO] FATAL ERROR: Client "
				<< currentClient->getID() << " is null.";
			log.msg(status.str(), log.VL_ERROR_CRIT);
			iomp->quit();
		}
	}
}

void TCPServer::disconnect(TCPRemotePeer *peer)
{
	if (!log.assert(iomp != 0, "[TCPServer::disconnect] "
		"IO multiplexer is null."))
		return;
	if (peer == 0)
	{
		log.msg("[TCPServer::disconnect] WARNING: Ignoring attempt to "
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
		removeClient(peer);
}

void TCPServer::broadcast(const std::string &bytes)
{
	TCPRemotePeer *currentClient;
	for (unsigned int i = 0; i < clients.size(); i++)
	{
		currentClient = clients[i];
		if (currentClient != 0)
			currentClient->send(bytes);
	}
}

void TCPServer::setMaxClients(unsigned int newMaxClients)
{
	maxClients = newMaxClients;
}

void TCPServer::setPort(int newPort)
{
	serverSocket.setPort(newPort);
}

unsigned int TCPServer::getMaxClients()
{
	return maxClients;
}

std::string TCPServer::getAddress()
{
    return address;
}

void TCPServer::setAddress(const std::string& newAddress)
{
    address = newAddress;
}

int TCPServer::getPort()
{
	return serverSocket.getPort();
}

void TCPServer::shutdownHandler(int signum)
{
	SelectMultiplexer::shutdownHandler(signum);
}

Reporter &TCPServer::getLog()
{
	return log;
}

}

}

/** \file TCPServer.cpp
 * \brief Generic TCP Server implementation.
 */
