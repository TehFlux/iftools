/* ==========================================================================
 * Ionflux's Stuff
 * Copyright (c) 2004 Joern P. Meier
 * mail@ionflux.org
 * --------------------------------------------------------------------------
 * filelist.cpp                         Create a list of files.
 * ==========================================================================
 *
 * This file is part of Ionflux's Stuff.
 *
 * Ionflux's Stuff is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by the
 * Free Software Foundation; either version 2 of the License, or (at your
 * option) any later version.
 *
 * Ionflux's Stuff is distributed in the hope that it will be useful, but
 * WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 * General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License along
 * with Ionflux's Stuff; if not, write to the Free Software Foundation,
 * Inc., 59 Temple Place, Suite 330, Boston, MA 02111-1307 USA
 *
 * ========================================================================== */

#include <iostream>
#include <string>
#include <sstream>
#include "ionflux/CLArgs.hpp"
#include "ionflux/tools.hpp"

using namespace std;
using namespace Ionflux::Tools;

void printHelp()
{
	cerr << "Usage: filelist [options] [<path> ...]\n"
		"Options:\n"
		"  -f, --filter <expr>     Regular expression pattern to be used for\n"
		"                          filtering file names.\n"
		"  -r, --recursive         Search for files recursively.\n"
		"  -h, --help              Print this help.\n"
		"  -v, --version           Print version information."
	<< endl;
}

void printVersion()
{
	cerr << "Ionflux file list tool 0.0.1" << endl
		<< "Copyright (c) 2006 Joern P. Meier <mail@ionflux.org>" << endl
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
	args.addAcceptableOption("f", true);
	args.addAcceptableOption("filter", true);
	args.addAcceptableOption("r", false);
	args.addAcceptableOption("recursive", false);
	args.setArgs(argc, argv);
	if (!args.optionsOK())
	{
		for (unsigned int i = 0; i < args.getInvalidOptions().size(); i++)
			cerr << "Option not recognized: '" << args.getInvalidOptions()[i] 
				<< "'" << endl;
	}
	if (args.isSet("v") || args.isSet("version"))
	{
		printVersion();
		return 0;
	}
	CLParams params;
	args.getParams(params);
	unsigned int numPaths = params.size();
	if ((numPaths == 0) || args.isSet("h") || args.isSet("help"))
	{
		printHelp();
		return 0;
	}
	CLOption* filterOpt = args.getOption("f");
	if (filterOpt == 0)
		filterOpt = args.getOption("filter");
	string filterExpr;
	if (filterOpt != 0)
		filterExpr = filterOpt->value;
	bool recursive = (args.isSet("r") || args.isSet("recursive"));
	cerr << "Ionflux file list tool 0.0.1" << endl;
	vector<string> result;
	getFileList(params, result, recursive, filterExpr);
	for (vector<string>::iterator i = result.begin(); i != result.end(); i++)
		cout << *i << endl;
	return 0;
}
