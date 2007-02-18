/* ==========================================================================
 * Ionflux Tools
 * Copyright (c) 2004 Joern P. Meier
 * mail@ionflux.org
 * --------------------------------------------------------------------------
 * ifls.cpp                     Template based directory listing tool.
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
#include "ionflux/tools.hpp"
#include "ionflux/File.hpp"
#include "ionflux/CLArgs.hpp"
#include "ionflux/DateTime.hpp"
#include "ionflux/Template.hpp"

using namespace std;
using namespace Ionflux::Tools;

void printHelp()
{
	cout << "Usage: ifls <option> ...\n"
		"Options:\n"
		"  -h, --help        Print this help.\n"
		"  -v, --version     Print version information.\n"
		"  -r, --recursive   Recursively list subdirectories.\n"
		"  -t, --template    Use output template instead of default.\n"
	<< endl;
}

void printVersion()
{
	cout << "ifls " << Ionflux::Tools::MODULE_VERSION << " (" 
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
	args.addAcceptableOption("recursive", false);
	args.addAcceptableOption("t", true);
	args.addAcceptableOption("template", true);
	args.setArgs(argc, argv);
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
	if (args.isSet("h") || args.isSet("help"))
	{
		printHelp();
		return 0;
	}
	bool recursive = false;
	string dirName = ".";
	if (args.isSet("r") || args.isSet("recursive"))
		recursive = true;
	// Initialize template if required.
	CLOption *tplOpt = args.getOption("t");
	string tplFile;
	bool useTemplate = false;
	if (tplOpt == 0)
		tplOpt = args.getOption("template");
	if (tplOpt != 0)
		tplFile = tplOpt->value;
	if (tplFile.size() > 0)
		useTemplate = true;
	Template tpl;
	Node *tplRoot = 0;
	if (useTemplate)
	{
		tpl.readTemplate(tplFile);
		tplRoot = tpl.getRoot();
		if (tplRoot == 0)
		{
			cerr << "ERROR: Template root node is null.";
			return -1;
		}
	}
	// Fetch directory entries.
	vector<string> params;
	args.getParams(params);
	if (params.size() > 0)
		dirName = params[0];
	vector<string> dirEntries;
	// We want full paths. Extraction of file name is done by File.
	readDir(dirName, dirEntries, true, recursive);
	// List directory entries.
	File file;
	DateTime accessTime;
	DateTime modTime;
	DateTime changeTime;
	string pathSep;
	string fileType;
	ostringstream status;
	for (unsigned int i = 0; i < dirEntries.size(); i++)
	{
		file.setFullName(dirEntries[i]);
		accessTime.setTimePosix(file.getAccessTime());
		modTime.setTimePosix(file.getModTime());
		changeTime.setTimePosix(file.getChangeTime());
		if (file.getPath().size() > 0)
			pathSep = DIR_SEPARATOR;
		else
			pathSep = "";
		if (file.isDir())
			fileType = "D";
		else
			fileType = "F";
		if (!useTemplate)
		{
			cout << fileType << "\t" << file.getPath() << "\t" 
				<< file.getName() << "\t" << file.getSize() << "\t" 
				<< accessTime.getTimestamp() << "\t" << modTime.getTimestamp() 
				<< "\t" << changeTime.getTimestamp() << endl;
		} else
		{
			status.str("");
			status << (i + 1);
			(*tplRoot)["num"].setData(status.str());
			status.str("");
			status << file.getSize();
			(*tplRoot)["size"].setData(status.str());
			(*tplRoot)["type"].setData(fileType);
			(*tplRoot)["pathSep"].setData(pathSep);
			(*tplRoot)["path"].setData(file.getPath());
			(*tplRoot)["name"].setData(file.getName());
			(*tplRoot)["fullName"].setData(file.getFullName());
			(*tplRoot)["accessTime"].setData(accessTime.getTimestamp());
			(*tplRoot)["modTime"].setData(modTime.getTimestamp());
			(*tplRoot)["changeTime"].setData(changeTime.getTimestamp());
			cout << tpl.process();
		}
	}
	return 0;
}

/** \file ifls.cpp
 * \brief Template based directory listing tool.
 */
