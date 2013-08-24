/* ==========================================================================
 * IFTemplate - Ionflux Template Processor
 * Copyright © 2012 Jörn P. Meier
 * mail@ionflux.org
 * --------------------------------------------------------------------------
 * File.cpp                        File (implementation).
 * =========================================================================
 * 
 * This file is part of IFTemplate - Ionflux Template Processor.
 * 
 * IFTemplate - Ionflux Template Processor is free software; you can 
 * redistribute it and/or modify it under the terms of the GNU General 
 * Public License as published by the Free Software Foundation; either 
 * version 2 of the License, or (at your option) any later version.
 * 
 * IFTemplate - Ionflux Template Processor is distributed in the hope that 
 * it will be useful, but WITHOUT ANY WARRANTY; without even the implied 
 * warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See 
 * the GNU General Public License for more details.
 * 
 * You should have received a copy of the GNU General Public License along 
 * with IFTemplate - Ionflux Template Processor; if not, write to the Free 
 * Software Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA 
 * 02111-1307 USA
 * 
 * ========================================================================== */

#include "iftemplate/File.hpp"
#include <iostream>
#include <iomanip>
#include <sstream>
#include <fstream>
#include "ifobject/utils.hpp"
#include "iftemplate/utils.hpp"
#include "iftemplate/IFTemplateError.hpp"

using namespace std;

namespace Ionflux
{

namespace Template
{

FileClassInfo::FileClassInfo()
{
	name = "File";
	desc = "File";
	baseClassInfo.push_back(Ionflux::ObjectBase::IFObject::CLASS_INFO);
}

FileClassInfo::~FileClassInfo()
{
}

// run-time type information instance constants
const FileClassInfo File::fileClassInfo;
const Ionflux::ObjectBase::IFClassInfo* File::CLASS_INFO = &File::fileClassInfo;

File::File()
: valid(false)
{
	// NOTE: The following line is required for run-time type information.
	theClass = CLASS_INFO;
	// TODO: Nothing ATM. ;-)
}

File::File(const Ionflux::Template::File& other)
: valid(false)
{
	// NOTE: The following line is required for run-time type information.
	theClass = CLASS_INFO;
	*this = other;
}

File::File(const std::string& initFullName)
: valid(false)
{
	// NOTE: The following line is required for run-time type information.
	theClass = CLASS_INFO;
	setFullName(initFullName);
}

File::~File()
{
	clearFiles();
	// TODO: Nothing ATM. ;-)
}

bool File::updateStatInfo()
{
	fileSize = 0;
	accessTime = 0;
	modTime = 0;
	changeTime = 0;
	statInfo.st_size = 0;
	statInfo.st_atime = 0;
	statInfo.st_mtime = 0;
	statInfo.st_ctime = 0;
	if (fullName.size() == 0)
	    throw IFTemplateError(getErrorString(
	        "File name not set", "updateStatInfo"));
	int result = stat(fullName.c_str(), &statInfo);
	if (result == -1)
	{
	    /* ----- DEBUG ----- //
	    cerr << "[File::updateStatInfo] DEBUG: Stat failed for '" 
	        << fullName << "'." << endl;
	    // ----- DEBUG ----- */
	    valid = false;
	    return false;
	}
	fileSize = statInfo.st_size;
	accessTime = statInfo.st_atime;
	modTime = statInfo.st_mtime;
	changeTime = statInfo.st_ctime;
	valid = true;
	return true;
}

void File::update()
{
	if ((fullName.size() == 0) 
	    && (name.size() == 0) 
	    && (path.size() == 0))
	    return;
	std::string dirSep;
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
	    while ((sepPos > 0) 
	        && (fullName[sepPos] != DIR_SEPARATOR))
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
	// Update base name and extension.
	if (name.size() == 0)
	    throw IFTemplateError(getErrorString(
	        "File name size is zero.", "update"));
	int sepPos = name.size() - 1;
	while ((sepPos >= 0) 
	    && (name[sepPos] != FILE_EXT_SEPARATOR))
	    sepPos--;
	if (sepPos < 0)
	{
	    baseName = name;
	    extension = "";
	} else
	{
	    int baseNameSize = sepPos;
	    int extSize = name.size() - sepPos;
	    if (baseNameSize > 0)
	        baseName = name.substr(0, sepPos);
	    else
	        baseName = "";
	    extension = name.substr(sepPos, extSize);
	}
	updateStatInfo();
}

bool File::isValid() const
{
	// TODO: Implementation.
	return valid;
}

bool File::isDir() const
{
	if (isValid() && S_ISDIR(statInfo.st_mode))
	    return true;
	return false;
}

void File::readDir(bool recursive, unsigned int maxDepth, unsigned int 
depth)
{
	if (!isDir())
	    return;
	if (recursive 
	    && (maxDepth > 0) 
	    && (depth > maxDepth))
	    return;
	Ionflux::ObjectBase::StringVector entries;
	if (!Ionflux::Template::readDir(fullName, entries, true, false))
	{
	    std::ostringstream status;
	    status << "Could not read directory: " << fullName;
	    throw IFTemplateError(getErrorString(status.str(), "readDir"));
	}
	clearFiles();
	for (Ionflux::ObjectBase::StringVector::iterator i = entries.begin(); 
	    i != entries.end(); i++)
	{
	    File* cf0 = addFile();
	    cf0->setFullName(*i);
	    if (recursive && cf0->isDir())
	        cf0->readDir(true, maxDepth, depth + 1);
	}
}

std::string File::getValueString() const
{
	std::ostringstream status;
	if (fullName.size() == 0)
	    status << "<empty>";
	else
	status << "'" << fullName << "'";
	if (isDir())
	    status << "(dir)";
	return status.str();
}

Ionflux::ObjectBase::UInt64 File::getFileSize() const
{
	return fileSize;
}

time_t File::getAccessTime() const
{
	return accessTime;
}

time_t File::getModTime() const
{
	return modTime;
}

time_t File::getChangeTime() const
{
	return changeTime;
}

void File::setName(const std::string& newName)
{
	name = newName;
	fullName = "";
	update();
}

std::string File::getName() const
{
	return name;
}

void File::setPath(const std::string& newPath)
{
	path = newPath;
	fullName = "";
	update();
}

std::string File::getPath() const
{
	return path;
}

void File::setFullName(const std::string& newFullName)
{
	fullName = newFullName;
	name = "";
	path = "";
	update();
}

std::string File::getFullName() const
{
	return fullName;
}

std::string File::getBaseName() const
{
	return baseName;
}

std::string File::getExtension() const
{
	return extension;
}

unsigned int File::getNumFiles() const
{
    return children.size();
}

Ionflux::Template::File* File::getFile(unsigned int elementIndex) const
{
    if (elementIndex < children.size())
		return children[elementIndex];
	return 0;
}

int File::findFile(Ionflux::Template::File* needle, unsigned int occurence)
const
{
    bool found = false;
	Ionflux::Template::File* currentFile = 0;
	unsigned int i = 0;
	while (!found 
		&& (i < children.size()))
	{
		currentFile = children[i];
		if (currentFile == needle)
        {
            if (occurence == 1)
			    found = true;
            else
                occurence--;
		} else
			i++;
	}
	if (found)
        return i;
	return -1;
}

std::vector<Ionflux::Template::File*>& File::getFiles()
{
    return children;
}

void File::addFile(Ionflux::Template::File* addElement)
{
	addLocalRef(addElement);
	children.push_back(addElement);
}

Ionflux::Template::File* File::addFile()
{
	Ionflux::Template::File* o0 = create();;
	addFile(o0);
	return o0;
}

void File::addFiles(std::vector<Ionflux::Template::File*>& newFiles)
{
	for (std::vector<Ionflux::Template::File*>::iterator i = newFiles.begin(); 
	    i != newFiles.end(); i++)
	    addFile(*i);
}

void File::addFiles(Ionflux::Template::File* newFiles)
{
	for (unsigned int i = 0; 
	    i < newFiles->getNumFiles(); i++)
	    addFile(newFiles->getFile(i));
}

void File::removeFile(Ionflux::Template::File* removeElement)
{
    bool found = false;
	Ionflux::Template::File* currentFile = 0;
	unsigned int i = 0;
	while (!found 
		&& (i < children.size()))
	{
		currentFile = children[i];
		if (currentFile == removeElement)
			found = true;
		else
			i++;
	}
	if (found)
	{
		children.erase(children.begin() + i);
		if (currentFile != 0)
			removeLocalRef(currentFile);
	}
}

void File::removeFileIndex(unsigned int removeIndex)
{
    if (removeIndex > children.size())
        return;
	Ionflux::Template::File* e0 = children[removeIndex];
    children.erase(children.begin() + removeIndex);
    if (e0 != 0)
        removeLocalRef(e0);
}

void File::clearFiles()
{
    std::vector<Ionflux::Template::File*>::iterator i;
	for (i = children.begin(); i != children.end(); i++)
		if (*i != 0)
			removeLocalRef(*i);
	children.clear();
}

Ionflux::Template::File& File::operator=(const Ionflux::Template::File& 
other)
{
	return *this;
}

Ionflux::Template::File* File::copy() const
{
    File* newFile = create();
    *newFile = *this;
    return newFile;
}

Ionflux::Template::File* File::upcast(Ionflux::ObjectBase::IFObject* other)
{
    return dynamic_cast<File*>(other);
}

Ionflux::Template::File* File::create(Ionflux::ObjectBase::IFObject* 
parentObject)
{
    File* newObject = new File();
    if (newObject == 0)
    {
        throw IFTemplateError("Could not allocate object.");
    }
    if (parentObject != 0)
        parentObject->addLocalRef(newObject);
    return newObject;
}

Ionflux::Template::File* File::create(const std::string& initFullName, 
Ionflux::ObjectBase::IFObject* parentObject)
{
    File* newObject = new File(initFullName);
    if (newObject == 0)
    {
        throw IFTemplateError("Could not allocate object.");
    }
    if (parentObject != 0)
        parentObject->addLocalRef(newObject);
    return newObject;
}

}

}

/** \file File.cpp
 * \brief File implementation.
 */
