/* ==========================================================================
 * Ionflux Tools
 * Copyright (c) 2005 Joern P. Meier
 * mail@ionflux.org
 * --------------------------------------------------------------------------
 * File.cpp                        File.
 * ==========================================================================
 * 
 * This file is part of Ionflux Tools.
 * 
 * Ionflux Tools is free software; you can redistribute it and/or modify it
 * under the terms of the GNU General Public License as published by the 
 * Free Software Foundation; either version 2 of the License, or (at your 
 * option) any later version.
 * 
 * Ionflux Tools is distributed in the hope that it will be useful, but 
 * WITHOUT ANY WARRANTY; without even the implied warranty of 
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU 
 * General Public License for more details.
 * 
 * You should have received a copy of the GNU General Public License along 
 * with Ionflux Tools; if not, write to the Free Software Foundation, Inc.,
 * 59 Temple Place, Suite 330, Boston, MA 02111-1307 USA
 * 
 * ========================================================================== */

#include "ionflux/File.hpp"

using namespace std;

namespace Ionflux
{

namespace Tools
{

File::File()
: validity(false)
{
	// TODO: Nothing ATM. ;-)
}

File::File(const std::string& initFullName)
{
	setFullName(initFullName);
}

File::~File()
{
	// TODO: Nothing ATM. ;-)
}

bool File::updateStatInfo()
{
	size = 0;
	accessTime = 0;
	modTime = 0;
	changeTime = 0;
	statInfo.st_size = 0;
	statInfo.st_atime = 0;
	statInfo.st_mtime = 0;
	statInfo.st_ctime = 0;
	if (fullName.size() == 0)
	{
		cerr << "[File::updateStatInfo] ERROR: File name not set." << endl;
		return false;
	}
	int result = stat(fullName.c_str(), &statInfo);
	if (result == -1)
	{
		/* ----- DEBUG ----- //
		cerr << "[File::updateStatInfo] DEBUG: Stat failed for '" 
			<< fullName << "'." << endl;
		// ----- DEBUG ----- */
		validity = false;
		return false;
	}
	size = statInfo.st_size;
	accessTime = statInfo.st_atime;
	modTime = statInfo.st_mtime;
	changeTime = statInfo.st_ctime;
	validity = true;
	return true;
}

void File::refresh()
{
	if ((fullName.size() == 0) && (name.size() == 0) && (path.size() == 0))
		return;
	string dirSep;
	if (fullName.size() == 0)
	{
		// Set full name from name and path.
		if (path.size() == 0)
		{
			fullName = name;
			path = ".";
		} else
		{
			if (path[path.size() - 1] != DIR_SEPARATOR)
				dirSep = DIR_SEPARATOR;
			else
			{
				path = path.substr(0, path.size() - 1);
				dirSep = "";
			}
			fullName = path + dirSep + name;
		}
	} else
	{
		// Set name and path from full name.
		unsigned int sepPos = fullName.size() - 1;
		while ((sepPos > 0) && (fullName[sepPos] != DIR_SEPARATOR))
			sepPos--;
		if (sepPos == 0)
		{
			name = fullName;
			path = ".";
		} else
		{
			int nameSize = fullName.size() - sepPos - 1;
			int pathSize = sepPos;
			if (nameSize > 0)
				name = fullName.substr(sepPos + 1, nameSize);
			else
				name = "";
			path = fullName.substr(0, pathSize);
		}
	}
	updateStatInfo();
}

bool File::isValid()
{
	return validity;
}

bool File::isDir()
{
	if (isValid() && S_ISDIR(statInfo.st_mode))
		return true;
	return false;
}

unsigned int File::getSize()
{
	return size;
}

time_t File::getAccessTime()
{
	return accessTime;
}

time_t File::getModTime()
{
	return modTime;
}

time_t File::getChangeTime()
{
	return changeTime;
}

void File::setName(const std::string& newName)
{
	name = newName;
	fullName = "";
	refresh();
}

void File::setPath(const std::string& newPath)
{
	path = newPath;
	fullName = "";
	refresh();
}

void File::setFullName(const std::string& newFullName)
{
	fullName = newFullName;
	name = "";
	path = "";
	refresh();
}

std::string File::getName() const
{
	return name;
}

std::string File::getPath() const
{
	return path;
}

std::string File::getFullName() const
{
	return fullName;
}

}

}

/** \file File.cpp
 * \brief File implementation.
 */
