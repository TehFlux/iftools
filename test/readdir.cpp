/* ==========================================================================
 * Ionflux Tools
 * Copyright (c) 2004 Joern P. Meier
 * mail@ionflux.org
 * --------------------------------------------------------------------------
 * readdir.cpp                  Directory functions test.
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

using namespace std;
using namespace Ionflux::Tools;

int main(int argc, char* argv[])
{
	CLArgs args;
	args.addAcceptableOption("r", false);
	args.addAcceptableOption("p", false);
	args.setArgs(argc, argv);
	bool prependDirName = false;
	bool recursive = false;
	string dirName = ".";
	if (args.isSet("r"))
		recursive = true;
	if (args.isSet("p"))
		prependDirName = true;
	vector<string> params;
	args.getParams(params);
	if (params.size() > 0)
		dirName = params[0];
	vector<string> dirEntries;
	readDir(dirName, dirEntries, prependDirName, recursive);
	File file;
	DateTime accessTime;
	DateTime modTime;
	DateTime changeTime;
	string dirSep;
	for (unsigned int i = 0; i < dirEntries.size(); i++)
	{
		file.setFullName(dirEntries[i]);
		accessTime.setTime(file.getAccessTime());
		modTime.setTime(file.getModTime());
		changeTime.setTime(file.getChangeTime());
		if (file.getPath().size() > 0)
			dirSep = DIR_SEPARATOR;
		else
			dirSep = "";
		cout << file.getPath() << "\t" << file.getName() << "\t" 
			<< file.getSize() << "\t" << accessTime.getTimestamp() << "\t" 
			<< modTime.getTimestamp() << "\t" << changeTime.getTimestamp() 
			<< endl;
	}
	return 0;
}

/** \file readdir.cpp
 * \brief Directory functions test.
 */
