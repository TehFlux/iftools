/* ==========================================================================
 * Ionflux Tools
 * Copyright (c) 2004 Joern P. Meier
 * mail@ionflux.org
 * --------------------------------------------------------------------------
 * message.cpp                  Network message test.
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
#include <vector>
#include "ionflux/tools.hpp"
#include "ionflux/ConfigTree.hpp"
#include "ionflux/Message.hpp"

using namespace std;
using namespace Ionflux::Tools;

int main(int argc, char* argv[])
{
	string defaultConfigFile = "./test/conf/test.conf";
	string configFile;
	if (argc >= 2)
		configFile = argv[1];
	else
		configFile = defaultConfigFile;
	ConfigTree config;
	config.readConfig(configFile);
	Node &configRoot = *config.getRoot();
	cout << "Data from configuration file:" << endl;
	config.printDebugInfo();
	cout << endl;
	Message msg;
	msg.getLog().setVerbosityLevel(Reporter::VL_DEBUG_OPT);
	msg.setFlags(Message::FLAG_COMPRESS);
	Node &msgRoot = *msg.getRoot();
	msgRoot = configRoot;
	cout << "Message data:" << endl;
	msg.printDebugInfo();
	string serializedMessage;
	msg.serialize(serializedMessage);
	cout << "Serialized message data:" << endl;
	cout << makeNiceHex(makeHex(serializedMessage), 
		makeReadable(serializedMessage, "."), 16, 8);
	msg.clearAll();
	msg.dump(serializedMessage);
	cout << "Message data (after unpacking):" << endl;
	msg.printDebugInfo();
	return 0;
}

/** \file configtree.cpp
 * \brief Configuration tree test.
 */
