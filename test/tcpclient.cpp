/* ==========================================================================
 * Ionflux Tools
 * Copyright (c) 2004 Joern P. Meier
 * mail@ionflux.org
 * --------------------------------------------------------------------------
 * tcpclient.cpp                  Generic TCP client test.
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
#include "ionflux/TCPClient.hpp"

using namespace std;
using namespace Ionflux::Tools;

int main(int argc, char* argv[])
{
	CLArgs args(argc, argv);
	CLOption *hostOpt = args.getOption("h");
	CLOption *portOpt = args.getOption("p");
	if ((hostOpt == 0) && (portOpt == 0))
	{
		cout << "Usage: tcpclient -h <host> -p <port>" << endl;
		return 0;
	}
	string host = hostOpt->value;
	int port = strtol(portOpt->value.c_str(), 0, 10);
	TCPClient client(true);
	signal(SIGINT, TCPClient::shutdownHandler);
	signal(SIGTERM, TCPClient::shutdownHandler);
	client.getLog().setVerbosityLevel(Reporter::VL_DEBUG_OPT);
	client.addConnection(host, port);
	client.run();
	return 0;
}

/** \file tcpclient.cpp
 * \brief Generic TCP client test.
 */
