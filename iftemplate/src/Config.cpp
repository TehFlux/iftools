/* ==========================================================================
 * IFTemplate - Ionflux Template Processor
 * Copyright © 2012 Jörn P. Meier
 * mail@ionflux.org
 * --------------------------------------------------------------------------
 * Config.cpp                      Configuration (implementation).
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

#include "iftemplate/Config.hpp"
#include <iostream>
#include <iomanip>
#include <sstream>

using namespace std;

namespace Ionflux
{

namespace Template
{

ConfigClassInfo::ConfigClassInfo()
{
	name = "Config";
	desc = "Configuration";
	baseClassInfo.push_back(Ionflux::ObjectBase::IFObject::CLASS_INFO);
}

ConfigClassInfo::~ConfigClassInfo()
{
}

// run-time type information instance constants
const ConfigClassInfo Config::configClassInfo;
const Ionflux::ObjectBase::IFClassInfo* Config::CLASS_INFO = &Config::configClassInfo;

Config::Config()
{
	// NOTE: The following line is required for run-time type information.
	theClass = CLASS_INFO;
	// TODO: Nothing ATM. ;-)
}

Config::Config(const Ionflux::Template::Config& other)
{
	// NOTE: The following line is required for run-time type information.
	theClass = CLASS_INFO;
	*this = other;
}

Config::~Config()
{
	// TODO: Nothing ATM. ;-)
}

void Config::clear()
{
	// TODO: Implementation.
}

bool Config::readConfig(const std::string& configFile)
{
	// TODO: Implementation.
	return false;
}

void Config::writeConfig(const std::string& configFile)
{
	// TODO: Implementation.
}

void Config::writeConfig()
{
	// TODO: Implementation.
}

std::string Config::get(const std::string& key)
{
	// TODO: Implementation.
	return "";
}

void Config::set(const std::string& key, const std::string& value)
{
	// TODO: Implementation.
}

Ionflux::Template::Config& Config::operator=(const 
Ionflux::Template::Config& other)
{
if (this == &other)
    return *this;
	return *this;
}

Ionflux::Template::Config* Config::copy() const
{
    Config* newConfig = create();
    *newConfig = *this;
    return newConfig;
}

Ionflux::Template::Config* Config::upcast(Ionflux::ObjectBase::IFObject* 
other)
{
    return dynamic_cast<Config*>(other);
}

Ionflux::Template::Config* Config::create(Ionflux::ObjectBase::IFObject* 
parentObject)
{
    Config* newObject = new Config();
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

/** \file Config.cpp
 * \brief Configuration implementation.
 */
