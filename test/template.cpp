/* ==========================================================================
 * Ionflux Tools
 * Copyright (c) 2004 Joern P. Meier
 * mail@ionflux.org
 * --------------------------------------------------------------------------
 * template.cpp                  Template processor test.
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
#include "ionflux/Template.hpp"
#include "ionflux/ConfigTree.hpp"

using namespace std;
using namespace Ionflux::Tools;

int main(int argc, char* argv[])
{
	string defaultTemplateFile = "./test/template/test.tpl";
	string defaultConfigFile = "./test/conf/template.conf";
	string templateFile;
	string configFile;
	if (argc >= 2)
		templateFile = argv[1];
	else
		templateFile = defaultTemplateFile;
	if (argc >= 3)
		configFile = argv[2];
	else
		configFile = defaultConfigFile;
	Template tpl;
	ConfigTree config;
	tpl.getLog().setVerbosityLevel(Reporter::VL_DEBUG);
	config.getLog().setVerbosityLevel(Reporter::VL_DEBUG);
	Node &root = *tpl.getRoot();
	config.readConfig(configFile);
	// config.printDebugInfo();
	root = *config.getRoot();
	root["configFile"] = configFile;
	root["templateFile"] = templateFile;
	// tpl.printDebugInfo();
	tpl.readTemplate(templateFile);
	// tpl.printElementDebugInfo();
	string result = tpl.process();
	cerr << "----- BEGIN -----" << endl;
	cout << result;
	cerr << "------ END ------" << endl;
	return 0;
}

/** \file template.cpp
 * \brief Template processor test.
 */
