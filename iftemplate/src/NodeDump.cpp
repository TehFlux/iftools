/* ==========================================================================
 * IFTemplate - Ionflux Template Processor
 * Copyright © 2012 Jörn P. Meier
 * mail@ionflux.org
 * --------------------------------------------------------------------------
 * NodeDump.cpp                    Node dump (implementation).
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

#include "iftemplate/NodeDump.hpp"
#include <iostream>
#include <iomanip>
#include <sstream>

using namespace std;

namespace Ionflux
{

namespace Template
{

NodeDumpClassInfo::NodeDumpClassInfo()
{
	name = "NodeDump";
	desc = "Node dump";
	baseClassInfo.push_back(Ionflux::ObjectBase::IFObject::CLASS_INFO);
}

NodeDumpClassInfo::~NodeDumpClassInfo()
{
}

// run-time type information instance constants
const NodeDumpClassInfo NodeDump::nodeDumpClassInfo;
const Ionflux::ObjectBase::IFClassInfo* NodeDump::CLASS_INFO = &NodeDump::nodeDumpClassInfo;

NodeDump::NodeDump()
{
	// NOTE: The following line is required for run-time type information.
	theClass = CLASS_INFO;
	// TODO: Nothing ATM. ;-)
}

NodeDump::NodeDump(const Ionflux::Template::NodeDump& other)
{
	// NOTE: The following line is required for run-time type information.
	theClass = CLASS_INFO;
	*this = other;
}

NodeDump::~NodeDump()
{
	// TODO: Nothing ATM. ;-)
}

Ionflux::Template::NodeDump& NodeDump::operator=(const 
Ionflux::Template::NodeDump& other)
{
	return *this;
}

Ionflux::Template::NodeDump* 
NodeDump::upcast(Ionflux::ObjectBase::IFObject* other)
{
    return dynamic_cast<NodeDump*>(other);
}

}

}

/** \file NodeDump.cpp
 * \brief Node dump implementation.
 */
