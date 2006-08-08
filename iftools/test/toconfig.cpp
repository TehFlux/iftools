/* ==========================================================================
 * Ionflux Tools
 * Copyright (c) 2004 Joern P. Meier
 * mail@ionflux.org
 * --------------------------------------------------------------------------
 * toconfig.cpp                      Node to config test.
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
#include "ionflux/ConfigTree.hpp"

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
	// config.getLog().setVerbosityLevel(Reporter::VL_DEBUG_INSANE);
	config.readConfig(configFile);
	// config.printDebugInfo();
	Node* configRoot = config.getRoot();
	if (configRoot == 0)
	{
		cerr << "ERROR: Configuration root node is null." << endl;
		return 1;
	}
	/* ----- DEBUG ----- //
	Node test1;
	test1.setAutoCreate(true);
	test1["uid"].setDataType(Node::NODE_DATA_INT);
	test1["uid"].setData(42);
	Node* test2 = configRoot->addChild(42, "Foo");
	*test2 = test1;
	cout << "test1:" << endl 
		<< test1.toConfig("    ") << "----" << endl;
	// ----- DEBUG ----- */
	cout << configRoot->toConfig("    ");
	return 0;
}

/** \file toconfig.cpp
 * \brief Node to config test.
 */
