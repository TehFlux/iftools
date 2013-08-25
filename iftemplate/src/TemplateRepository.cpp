/* ==========================================================================
 * IFTemplate - Ionflux Template Processor
 * Copyright © 2012 Jörn P. Meier
 * mail@ionflux.org
 * --------------------------------------------------------------------------
 * TemplateRepository.cpp          Template repository (implementation).
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

#include "iftemplate/TemplateRepository.hpp"
#include <iostream>
#include <iomanip>
#include <sstream>
#include "ifobject/utils.hpp"
#include "ifobject/objectutils.hpp"
#include "iftemplate/Node.hpp"
#include "iftemplate/File.hpp"
#include "iftemplate/IFTemplateError.hpp"
#include "iftemplate/utils.hpp"

using namespace std;

namespace Ionflux
{

namespace Template
{

TemplateRepositoryClassInfo::TemplateRepositoryClassInfo()
{
	name = "TemplateRepository";
	desc = "Template repository";
}

TemplateRepositoryClassInfo::~TemplateRepositoryClassInfo()
{
}

// public member constants
const Ionflux::Template::RepositoryEntryTypeID TemplateRepository::ENTRY_TYPE_FILE = 0;
const Ionflux::Template::RepositoryEntryTypeID TemplateRepository::ENTRY_TYPE_DATA = 1;

// run-time type information instance constants
const TemplateRepositoryClassInfo TemplateRepository::templateRepositoryClassInfo;
const Ionflux::ObjectBase::IFClassInfo* TemplateRepository::CLASS_INFO = &TemplateRepository::templateRepositoryClassInfo;

TemplateRepository::TemplateRepository()
{
	// NOTE: The following line is required for run-time type information.
	theClass = CLASS_INFO;
	root->setIndexMode(Node::INDEX_MODE_NODE);
}

TemplateRepository::TemplateRepository(const Ionflux::Template::TemplateRepository& other)
{
	// NOTE: The following line is required for run-time type information.
	theClass = CLASS_INFO;
	*this = other;
}

TemplateRepository::~TemplateRepository()
{
	clearTemplatePaths();
	// TODO: Nothing ATM. ;-)
}

void TemplateRepository::addTemplatePaths(const 
Ionflux::ObjectBase::StringVector& newPaths)
{
	for (Ionflux::ObjectBase::StringVector::const_iterator i = 
	    newPaths.begin(); i != newPaths.end(); i++)
	    templatePaths.push_back(*i);
}

void TemplateRepository::addTemplatePaths(const std::string& newPaths, 
const std::string& separator)
{
	Ionflux::ObjectBase::StringVector parts;
	Ionflux::ObjectBase::explode(newPaths, separator, parts);
	addTemplatePaths(parts);
}

void TemplateRepository::addModule(const std::string& modulePath, 
Ionflux::Template::RepositoryEntryTypeID typeID, const std::string& data)
{
	Ionflux::Template::DataEntry d = resolve(modulePath, true);
	if (d.node == 0)
	{
	    std::ostringstream status;
	    status << "Could not resolve module path: '" << modulePath << "'";
	    throw IFTemplateError(getErrorString(status.str(), "addModule"));
	}
	d.node->setAutoCreate(true);
	Node* tn = d.node->findChild("type");
	Ionflux::ObjectBase::nullPointerCheck(tn, this, "addModule", 
	    "Type node");
	tn->setDataType(Node::DATA_INT);
	tn->setData(typeID);
	Node* dn = d.node->findChild("data");
	Ionflux::ObjectBase::nullPointerCheck(dn, this, "addModule", 
	    "Data node");
	dn->setDataType(Node::DATA_BLOB);
	dn->setData(data);
}

void TemplateRepository::scanFile(Ionflux::Template::File& file, const 
std::string& modulePrefix, bool addRootModule)
{
	if (file.isDir())
	{
	    std::string moduleName = file.getName();
	    if (Ionflux::ObjectBase::isIdentifier(moduleName))
	    {
	        // Scan template directory.
	        std::string mp;
	        if (addRootModule)
	            mp = getModulePath(modulePrefix, moduleName);
	        else
	            mp = modulePrefix;
	        /* <---- DEBUG ----- //
	        std::cerr << "[TemplateRepository::scanFile] DEBUG: "
	            "Processing directory: '" << file.getFullName() 
	            << "' (modulePath = " << mp << ")." << std::endl;
	        // ----- DEBUG ----> */
	        file.readDir(false);
	        unsigned int numFiles = file.getNumFiles();
	        for (unsigned int i = 0; i < numFiles; i++)
	        {
	            File* cf = file.getFile(i);
	            scanFile(*cf, mp, true);
	        }
	    }
	} else
	{
	    if (file.getExtension() == TEMPLATE_FILE_EXT)
	    {
	        std::string moduleName = file.getBaseName();
	        if (Ionflux::ObjectBase::isIdentifier(moduleName))
	        {
	            // Add template file.
	            std::string mp = getModulePath(modulePrefix, moduleName);
	            /* <---- DEBUG ----- //
	            std::cerr << "[TemplateRepository::scanFile] DEBUG: "
	                "Processing file: '" << file.getFullName() 
	                << "' (modulePath = " << mp << ")." << std::endl;
	            // ----- DEBUG ----> */
	            addModule(mp, ENTRY_TYPE_FILE, file.getFullName());
	        }
	    }
	}
}

void TemplateRepository::scanPath(const std::string& dirPath)
{
	File cd(dirPath);
	std::ostringstream status;
	if (!cd.isDir())
	{
	    status << "Invalid template directory path: '" << dirPath << "'";
	    throw IFTemplateError(getErrorString(status.str(), "scanDirectory"));
	}
	scanFile(cd);
}

void TemplateRepository::update()
{
	for (Ionflux::ObjectBase::StringVector::const_iterator i = 
	    templatePaths.begin(); i != templatePaths.end(); i++)
	{
	    /* <---- DEBUG ----- //
	    std::cerr << "[TemplateRepository::update] DEBUG: "
	        "Adding template path: '" << (*i) << "'." << std::endl;
	    // ----- DEBUG ----> */
	    scanPath(*i);
	}
}

void TemplateRepository::addTemplateData(const std::string& modulePath, 
const std::string& templateData)
{
	addModule(modulePath, ENTRY_TYPE_DATA, templateData);
}

std::string TemplateRepository::getTemplateData(const std::string& 
modulePath, bool removeTrailingNewLine)
{
	Ionflux::Template::DataEntry d = resolve(modulePath);
	if (d.node == 0)
	{
	    std::ostringstream status;
	    status << "Could not resolve module path: '" << modulePath << "'";
	    throw IFTemplateError(getErrorString(status.str(), 
	        "getTemplateData"));
	}
	Node* tn = d.node->findChild("type");
	Ionflux::ObjectBase::nullPointerCheck(tn, this, "getTemplateData", 
	    "Type node");
	RepositoryEntryTypeID et = tn->getInt();
	Node* dn = d.node->findChild("data");
	Ionflux::ObjectBase::nullPointerCheck(dn, this, "getTemplateData", 
	    "Data node");
	std::string ed = dn->getData();
	if (et == ENTRY_TYPE_DATA)
	    return ed;
	std::string result;
	Ionflux::ObjectBase::readFile(ed, result);
	if (removeTrailingNewLine 
	    && (result.size() > 0) 
	    && (result[result.size() - 1] == '\n'))
	    return result.substr(0, result.size() - 1);
	return result;
}

std::string TemplateRepository::getModulePath(const std::string& 
modulePrefix, const std::string& moduleName)
{
	if (modulePrefix.size() == 0)
	    return moduleName;
	std::ostringstream mp;
	mp << modulePrefix << TEMPLATE_MODULE_SEP << moduleName;
	return mp.str();
}

unsigned int TemplateRepository::getNumTemplatePaths() const
{
    return templatePaths.size();
}

std::string TemplateRepository::getTemplatePath(unsigned int elementIndex) 
const
{
    if (elementIndex < templatePaths.size())
		return templatePaths[elementIndex];
	return "";
}

int TemplateRepository::findTemplatePath(const std::string& needle, 
unsigned int occurence) const
{
    bool found = false;
	std::string currentTemplatePath = "";
	unsigned int i = 0;
	while (!found 
		&& (i < templatePaths.size()))
	{
		currentTemplatePath = templatePaths[i];
		if (currentTemplatePath == needle)
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

std::vector<std::string>& TemplateRepository::getTemplatePaths()
{
    return templatePaths;
}

void TemplateRepository::addTemplatePath(const std::string& addElement)
{
	templatePaths.push_back(addElement);
}

void TemplateRepository::removeTemplatePath(std::string removeElement)
{
    bool found = false;
	std::string currentTemplatePath = "";
	unsigned int i = 0;
	while (!found 
		&& (i < templatePaths.size()))
	{
		currentTemplatePath = templatePaths[i];
		if (currentTemplatePath == removeElement)
			found = true;
		else
			i++;
	}
	if (found)
	{
		templatePaths.erase(templatePaths.begin() + i);
	}
}

void TemplateRepository::removeTemplatePathIndex(unsigned int removeIndex)
{
    if (removeIndex > templatePaths.size())
        return;
    templatePaths.erase(templatePaths.begin() + removeIndex);
}

void TemplateRepository::clearTemplatePaths()
{
    templatePaths.clear();
}

Ionflux::Template::TemplateRepository& TemplateRepository::operator=(const 
Ionflux::Template::TemplateRepository& other)
{
    if (this == &other)
        return *this;
    if (root == 0)
        initRoot();
    *root = *other.root;
    templatePaths = other.templatePaths;
    update();
	return *this;
}

Ionflux::Template::TemplateRepository* TemplateRepository::copy() const
{
    TemplateRepository* newTemplateRepository = create();
    *newTemplateRepository = *this;
    return newTemplateRepository;
}

Ionflux::Template::TemplateRepository* 
TemplateRepository::upcast(Ionflux::ObjectBase::IFObject* other)
{
    return dynamic_cast<TemplateRepository*>(other);
}

Ionflux::Template::TemplateRepository* 
TemplateRepository::create(Ionflux::ObjectBase::IFObject* parentObject)
{
    TemplateRepository* newObject = new TemplateRepository();
    if (newObject == 0)
    {
        return 0;
    }
    if (parentObject != 0)
        parentObject->addLocalRef(newObject);
    return newObject;
}

}

}

/** \file TemplateRepository.cpp
 * \brief Template repository implementation.
 */
