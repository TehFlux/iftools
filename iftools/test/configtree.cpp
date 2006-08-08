/* ==========================================================================
 * Ionflux Tools
 * Copyright (c) 2004 Joern P. Meier
 * mail@ionflux.org
 * --------------------------------------------------------------------------
 * configtree.cpp                  Configuration tree test.
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
	config.getLog().setVerbosityLevel(Reporter::VL_DEBUG_INSANE);
	config.readConfig(configFile);
	config.printDebugInfo();
	// Add some values.
	/* ----- DEBUG ----- //
	Node &root = *config.getRoot();
	root["baz"]["meep"] = "551";
	root["blah"] = "\"bluah\"";
	config.printDebugInfo();
	// ----- DEBUG ----- */
	config.writeConfig(configFile + ".new");
	// File I/O test.
	/* ----- DEBUG ----- //
	cout << "Writing tree to file." << endl;
	config.writeToFile("test.tree");
	cout << "Reading tree from file." << endl;
	config.readFromFile("test.tree");
	config.printDebugInfo();
	// ----- DEBUG ----- */
	return 0;
}

/** \file configtree.cpp
 * \brief Configuration tree test.
 */
