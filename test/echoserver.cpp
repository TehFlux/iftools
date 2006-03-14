/* ==========================================================================
 * Ionflux Tools
 * Copyright (c) 2004 Joern P. Meier
 * mail@ionflux.org
 * --------------------------------------------------------------------------
 * echoserver.cpp                  Echo server.
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

#include <iostream>
#include <string>
#include <cstdlib>
#include <signal.h>
#include "ionflux/CLArgs.hpp"
#include "ionflux/TCPServer.hpp"

using namespace std;
using namespace Ionflux::Tools;

/** Echo server.
 *
 * Sends back any data it receives from a client.
 */
class EchoServer
: public TCPServer
{
	public:
		/// Constructor.
		EchoServer() { }
		
		/// Destructor.
		virtual ~EchoServer() { }
		
		/// Receive event handler.
		virtual void onReceive(TCPRemotePeer &client)
		{
			ostringstream status;
			status << "[TCPServer::onConnect] DEBUG: From client " 
				<< client.getID() << ":" << endl 
				<< makeNiceHex(makeHex(client.getRecvBuf()), 
					makeReadable(client.getRecvBuf(), "."), 16, 8);
			log.msg(status.str(), log.VL_DEBUG_OPT);
			client.send(client.getRecvBuf());
			client.clearRecvBuf();
		}
		
		/// Connection rejected event handler.
		virtual void onReject(TCPRemotePeer &client, int reason)
		{
			if (reason == REJECTED_REASON_MAX_CLIENTS)
				client.send("Sorry, too many connections. "
					"Try again later.\r\n");
			else
				client.send("Your connection has been rejected for an "
					"unknown reason.\r\n");
		}
};

int main(int argc, char* argv[])
{
	CLArgs args(argc, argv);
	CLOption *option = args.getOption("p");
	if (option == 0)
	{
		cout << "Usage: echoserver -p <port> [-m <maxClients>]" << endl;
		return 0;
	}
	int port = strtol(option->value.c_str(), 0, 10);
	int maxClients = 0;
	option = args.getOption("m");
	if (option != 0)
		maxClients = strtol(option->value.c_str(), 0, 10);
	EchoServer server;
	signal(SIGINT, EchoServer::shutdownHandler);
	signal(SIGTERM, EchoServer::shutdownHandler);
	server.getLog().setVerbosityLevel(Reporter::VL_DEBUG_OPT);
	server.setPort(port);
	server.setMaxClients(maxClients);
	server.init();
	server.run();
	return 0;
}

/** \file echoserver.cpp
 * \brief Echo server.
 */
