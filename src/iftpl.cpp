/* ==========================================================================
 * Ionflux Tools
 * Copyright (c) 2004 Joern P. Meier
 * mail@ionflux.org
 * --------------------------------------------------------------------------
 * iftpl.cpp                  Template processor.
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
#include "ionflux/CLArgs.hpp"
#include "ionflux/Template.hpp"
#include "ionflux/ConfigTree.hpp"
#include "ionflux/DateTime.hpp"

using namespace std;
using namespace Ionflux::Tools;

void printHelp()
{
	cerr << 
"Usage: iftpl <option> ... <template file> <config file> [<config file> ...]\n"
"Options:\n"
"  -h, --help      Print this help.\n"
"  -v, --version   Print version information.\n"
"  -r, --replace   Replace configuration while merging."
	<< endl;
}

void printVersion()
{
	cerr << "iftpl " << Ionflux::Tools::MODULE_VERSION << " (" 
		<< Ionflux::Tools::MODULE_NAME << " " 
		<< Ionflux::Tools::MODULE_VERSION 
		<< ")" << endl
		<< "Copyright (c) 2004 Joern P. Meier (mail@ionflux.org)" << endl
		<< "This is free software; see the source for copying conditions. " 
		   "There is NO" << endl
		<< "warranty; not even for MERCHANTABILITY or FITNESS FOR A "
		<< "PARTICULAR PURPOSE." << endl;
}

int main(int argc, char* argv[])
{
	CLArgs args;
	args.addAcceptableOption("h", false);
	args.addAcceptableOption("help", false);
	args.addAcceptableOption("v", false);
	args.addAcceptableOption("version", false);
	args.addAcceptableOption("r", false);
	args.addAcceptableOption("replace", false);
	args.setArgs(argc, argv);
	if (!args.optionsOK())
	{
		for (unsigned int i = 0; i < args.getInvalidOptions().size(); i++)
			cerr << "Option not recognized: '" << args.getInvalidOptions()[i] 
				<< "'" << endl;
	}
	CLParams params;
	args.getParams(params);
	if (args.isSet("v") || args.isSet("version"))
	{
		printVersion();
		return 0;
	}
	if (args.isSet("h") || args.isSet("help") || (params.size() < 2))
	{
		printHelp();
		return 0;
	}
	bool replace = (args.isSet("r") || args.isSet("replace"));
	string templateFile = params[0];
	string configFile = params[1];
	Template tpl;
	ConfigTree config;
	Node &root = *tpl.getRoot();
	config.readConfig(configFile);
	root = *config.getRoot();
	root["__config_file"] = configFile;
	root["__template_file"] = templateFile;
	DateTime now;
	root["__datetime"] = now.getTimestamp();
	root["__rfc_datetime"] = now.getRFCTimestamp();
	if (params.size() > 2)
		// Merge additional configuration files.
		for (unsigned int i = 2; i < params.size(); i++)
		{
			string mergeFile = params[i];
			ConfigTree mergeConfig;
			mergeConfig.readConfig(mergeFile);
			root.merge(*mergeConfig.getRoot(), replace);
		}
	tpl.readTemplate(templateFile);
	string result = tpl.process();
	cout << result;
	return 0;
}

/** \file iftpl.cpp
 * \brief Template processor.
 */
