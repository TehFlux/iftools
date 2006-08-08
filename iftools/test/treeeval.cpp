/* ==========================================================================
 * Ionflux Tools
 * Copyright (c) 2004 Joern P. Meier
 * mail@ionflux.org
 * --------------------------------------------------------------------------
 * treeeval.cpp                  Tree expression evaluation test.
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
#include "ionflux/TreeEval.hpp"

using namespace std;
using namespace Ionflux::Tools;

int main(int argc, char* argv[])
{
	string defaultConfigFile = "test/conf/treeeval.conf";
	string configFile;
	if (argc >= 2)
		configFile = argv[1];
	else
		configFile = defaultConfigFile;
	ConfigTree config;
	config.readConfig(configFile);
	// config.printDebugInfo();
	vector<string> test;
	for (unsigned int i = 0; i < config["expr"].getNumData(); i++)
		test.push_back(config["expr"].getData(i));
	Node resultNode;
	for (unsigned int i = 0; i < test.size(); i++)
	{
		cout << "Test #" << (i + 1) << ":" << endl
			<< "  Test string: " << test[i] << endl
			<< "  Result = ";
		config.eval(test[i], resultNode, true);
		cout << resultNode.getData() << endl;
	}
	return 0;
}

/** \file treeeval.cpp
 * \brief Tree expression evaluation test.
 */
