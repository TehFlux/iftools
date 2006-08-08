/* ==========================================================================
 * Ionflux Tools
 * Copyright (c) 2004 Joern P. Meier
 * mail@ionflux.org
 * --------------------------------------------------------------------------
 * ifpasswd.cpp                  Authentication file generator.
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
	cerr << 
"Usage: ifpasswd <option> ... <username>\n"
"Options:\n"
"  -h, --help      Print this help.\n"
"  -v, --version   Print version information."
	<< endl;
}

void printVersion()
{
	cerr << "ifpasswd " << Ionflux::Tools::MODULE_VERSION << " (" 
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
	if (args.isSet("h") || args.isSet("help") || (params.size() < 1))
	{
		printHelp();
		return 0;
	}
	string username = params[0];
	string pass0;
	string pass1;
	getPassword("Enter password: ", pass0);
	if (pass0.size() < 6)
	{
		cerr << "Password too short." << endl;
		return 0;
	}
	getPassword("Confirm password: ", pass1);
	if (pass0 != pass1)
	{
		cerr << "Passwords do not match." << endl;
		return 0;
	}
	cout << username << ":" << makeHex(sha1(pass0)) << endl;
	for (unsigned int i = 0; i < pass0.size(); i++)
		pass0[i] = '\0';
	for (unsigned int i = 0; i < pass1.size(); i++)
		pass1[i] = '\0';
	return 0;
}

/** \file ifpasswd.cpp
 * \brief Authentication file generator.
 */
