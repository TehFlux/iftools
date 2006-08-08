/* ==========================================================================
 * Ionflux Tools
 * Copyright (c) 2004 Joern P. Meier
 * mail@ionflux.org
 * --------------------------------------------------------------------------
 * utf8encode.cpp                  UTF-8 encoding test.
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
	cout << "Usage: utf8encode [<option> ...] <input>\n"
		"Options:\n"
		"  -h, --help        Print this help.\n"
		"  -v, --version     Print version information.\n"
		"  -S, --separator <sep>\n"
		"                    Use <sep> as list separator.\n"
		"  -f, --file        Read input from file.\n"
		"  --hexin           Treat the input as a hexadecimal string.\n"
		"  --hexout          Output hexadecimal string."
	<< endl;
}

void printVersion()
{
	cout << "utf8encode " << Ionflux::Tools::MODULE_VERSION << " (" 
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
	args.addAcceptableOption("f", false);
	args.addAcceptableOption("file", false);
	args.addAcceptableOption("S", true);
	args.addAcceptableOption("separator", true);
	args.addAcceptableOption("hexin", false);
	args.addAcceptableOption("hexout", false);
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
	string source;
	if (args.isSet("f") || args.isSet("file"))
		source = readFile(params[0]);
	else
		source = params[0];
	string separator = " ";
	CLOption* sepOption = args.getOption("S");
	if (sepOption == 0)
		sepOption = args.getOption("separator");
	if (sepOption != 0)
		separator = sepOption->value;
	unsigned int base = 10;
	if (args.isSet("hexin"))
		base = 16;
	bool hexOut = false;
	if (args.isSet("hexout"))
		hexOut = true;
	vector<unsigned int> input;
	vector<string> rawInput;
	explode(source, separator, rawInput);
	for (unsigned int i = 0; i < rawInput.size(); i++)
		input.push_back(strtol(rawInput[i].c_str(), 0, base));
	string result;
	uintToUtf8(input, result);
	if (!hexOut)
		cout << result << endl;
	else
		cout << makeHex(result) << endl;
	return 0;
}

/** \file utf8encode.cpp
 * \brief UTF-8 encoding test.
 */
