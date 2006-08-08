/* ==========================================================================
 * Ionflux Tools
 * Copyright (c) 2004 Joern P. Meier
 * mail@ionflux.org
 * --------------------------------------------------------------------------
 * merge.cpp                  Node merge test.
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
	string defaultConfigFile1 = "./test/conf/merge1.conf";
	string defaultConfigFile2 = "./test/conf/merge2.conf";
	string configFile1;
	string configFile2;
	bool replace = false;
	if (argc >= 2)
		replace = toBool(argv[1]);
	if (argc >= 4)
	{
		configFile1 = argv[2];
		configFile2 = argv[3];
	} else
	{
		configFile1 = defaultConfigFile1;
		configFile2 = defaultConfigFile2;
	}
	ConfigTree config1;
	cout << "Configuration file 1:" << endl;
	config1.getLog().setVerbosityLevel(Reporter::VL_DEBUG_OPT);
	config1.readConfig(configFile1);
	config1.printDebugInfo();
	ConfigTree config2;
	cout << "Configuration file 2:" << endl;
	config2.getLog().setVerbosityLevel(Reporter::VL_DEBUG_OPT);
	config2.readConfig(configFile2);
	config2.printDebugInfo();
	ConfigTree config;
	config.getLog().setVerbosityLevel(Reporter::VL_DEBUG_OPT);
	Node *cfgRoot1 = config1.getRoot();
	Node *cfgRoot2 = config2.getRoot();
	Node *cfgRoot = config.getRoot();
	cout << "Merging configuration." << endl;
	*cfgRoot = *cfgRoot1;
	cfgRoot->merge(*cfgRoot2, replace);
	config.printDebugInfo();
	cout << "Writing merged configuration to file." << endl;
	config.writeConfig("merged.conf");
	return 0;
}

/** \file merge.cpp
 * \brief Node merge test.
 */
