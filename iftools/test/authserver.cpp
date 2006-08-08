/* ==========================================================================
 * Ionflux Tools
 * Copyright (c) 2004 Joern P. Meier
 * mail@ionflux.org
 * --------------------------------------------------------------------------
 * authserver.cpp                  Authenticated TCP server test.
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
#include "ionflux/TCPAuthServer.hpp"

using namespace std;
using namespace Ionflux::Tools;

int main(int argc, char* argv[])
{
	CLArgs args(argc, argv);
	CLOption *option;
	CLOption *optionPort = args.getOption("p");
	CLOption *optionAuth = args.getOption("a");
	if ((optionPort == 0) || (optionAuth == 0))
	{
		cerr << "Usage: authserver -p <port> -a <authfile> [-m <maxClients>]" 
			<< endl;
		return 0;
	}
	int port = strtol(optionPort->value.c_str(), 0, 10);
	int maxClients = 0;
	option = args.getOption("m");
	if (option != 0)
		maxClients = strtol(option->value.c_str(), 0, 10);
	TCPAuthServer server(optionAuth->value);
	signal(SIGINT, TCPAuthServer::shutdownHandler);
	signal(SIGTERM, TCPAuthServer::shutdownHandler);
	server.getLog().setVerbosityLevel(Reporter::VL_DEBUG_OPT);
	server.setPort(port);
	server.setMaxClients(maxClients);
	server.init();
	server.run();
	return 0;
}

/** \file authserver.cpp
 * \brief Authenticated TCP server test.
 */
