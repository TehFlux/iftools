/* ==========================================================================
 * Ionflux Tools
 * Copyright (c) 2005 Joern P. Meier
 * mail@ionflux.org
 * --------------------------------------------------------------------------
 * utf8unescape.cpp                  UTF-8 unescaping test.
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
#include "ionflux/tools.hpp"
#include "ionflux/CLArgs.hpp"

using namespace std;
using namespace Ionflux::Tools;

void printHelp()
{
	cout << "Usage: utf8unescape [<option> ...] <input>\n"
		"Options:\n"
		"  -h, --help        Print this help.\n"
		"  -v, --version     Print version information."
	<< endl;
}

void printVersion()
{
	cout << "utf8unescape " << Ionflux::Tools::MODULE_VERSION << " (" 
		<< Ionflux::Tools::MODULE_NAME << " " 
		<< Ionflux::Tools::MODULE_VERSION 
		<< ")" << endl
		<< "Copyright (c) 2005 Joern P. Meier (mail@ionflux.org)" << endl
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
	args.setArgs(argc, argv);
	CLParams params;
	args.getParams(params);
	if (!args.optionsOK())
	{
		for (unsigned int i = 0; i < args.getInvalidOptions().size(); i++)
			cout << "Option not recognized: '" << args.getInvalidOptions()[i] 
				<< "'" << endl;
	}
	if (args.isSet("v") || args.isSet("version"))
	{
		printVersion();
		return 0;
	}
	if ((params.size() < 1) || args.isSet("h") || args.isSet("help"))
	{
		printHelp();
		return 0;
	}
	cout << utf8Unescape(params[0]) << endl;
	return 0;
}

/** \file utf8unescape.cpp
 * \brief UTF-8 unescaping test.
 */
