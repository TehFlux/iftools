/* ==========================================================================
 * Ionflux Tools
 * Copyright (c) 2004 Joern P. Meier
 * mail@ionflux.org
 * --------------------------------------------------------------------------
 * authclient.cpp                  Authenticated TCP client test.
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
#include "ionflux/tools.hpp"
#include "ionflux/CLArgs.hpp"
#include "ionflux/TCPAuthClient.hpp"

using namespace std;
using namespace Ionflux::Tools;

int main(int argc, char* argv[])
{
	CLArgs args(argc, argv);
	CLOption *hostOpt = args.getOption("h");
	CLOption *portOpt = args.getOption("p");
	CLOption *userOpt = args.getOption("u");
	if ((hostOpt == 0) || (portOpt == 0) || (userOpt == 0))
	{
		cout << "Usage: authclient -u <username> -h <host> -p <port>" << endl;
		return 0;
	}
	string host = hostOpt->value;
	string username = userOpt->value;
	int port = strtol(portOpt->value.c_str(), 0, 10);
	string password;
	getPassword("Enter password: ", password);
	TCPAuthClient client(username, sha1(password), true);
	for (unsigned int i = 0; i < password.size(); i++)
		password[i] = '\0';
	signal(SIGINT, TCPAuthClient::shutdownHandler);
	signal(SIGTERM, TCPAuthClient::shutdownHandler);
	client.getLog().setVerbosityLevel(Reporter::VL_DEBUG_OPT);
	client.addConnection(host, port);
	client.run();
	return 0;
}

/** \file msgclient.cpp
 * \brief Message based TCP client test.
 */
