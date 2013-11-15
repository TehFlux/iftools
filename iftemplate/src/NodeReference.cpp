/* ==========================================================================
 * IFTemplate - Ionflux Template Processor
 * Copyright © 2012 Jörn P. Meier
 * mail@ionflux.org
 * --------------------------------------------------------------------------
 * NodeReference.cpp               Node reference (implementation).
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

#include "iftemplate/NodeReference.hpp"
#include <iostream>
#include <iomanip>
#include <sstream>
#include "ifobject/utils.hpp"
#include "iftemplate/utils.hpp"
#include "iftemplate/TreeResolver.hpp"

using namespace std;

namespace Ionflux
{

namespace Template
{

NodeReferenceClassInfo::NodeReferenceClassInfo()
{
	name = "NodeReference";
	desc = "Node reference";
	baseClassInfo.push_back(Ionflux::ObjectBase::IFObject::CLASS_INFO);
}

NodeReferenceClassInfo::~NodeReferenceClassInfo()
{
}

// public member constants
const Ionflux::Template::NodeRefTypeID NodeReference::TYPE_INVALID = 0;
const Ionflux::Template::NodeRefTypeID NodeReference::TYPE_NAME = 1;
const Ionflux::Template::NodeRefTypeID NodeReference::TYPE_ID = 2;
const Ionflux::Template::NodeRefTypeID NodeReference::TYPE_PATH = 3;
const Ionflux::Template::NodeRefTypeID NodeReference::TYPE_EMPTY = 4;

// run-time type information instance constants
const NodeReferenceClassInfo NodeReference::nodeReferenceClassInfo;
const Ionflux::ObjectBase::IFClassInfo* NodeReference::CLASS_INFO = &NodeReference::nodeReferenceClassInfo;

NodeReference::NodeReference()
: value(""), type(TYPE_INVALID), subscript(false)
{
	// NOTE: The following line is required for run-time type information.
	theClass = CLASS_INFO;
	// TODO: Nothing ATM. ;-)
}

NodeReference::NodeReference(const Ionflux::Template::NodeReference& other)
: value(""), type(TYPE_INVALID), subscript(false)
{
	// NOTE: The following line is required for run-time type information.
	theClass = CLASS_INFO;
	*this = other;
}

NodeReference::NodeReference(const std::string& refExpr)
: value(""), type(TYPE_INVALID), subscript(false)
{
	// NOTE: The following line is required for run-time type information.
	theClass = CLASS_INFO;
	setFromRef(refExpr);
}

NodeReference::~NodeReference()
{
	// TODO: Nothing ATM. ;-)
}

void NodeReference::clear()
{
	setValue("");
	setType(TYPE_INVALID);
	setSubscript(false);
}

void NodeReference::setFromRef(const std::string& refExpr)
{
	setValue(refExpr);
	if (refExpr.size() == 0)
	    setType(TYPE_EMPTY);
	else
	if (Ionflux::ObjectBase::isInteger(refExpr))
	    setType(TYPE_ID);
	else
	if (refExpr[0] == TreeResolver::TT_RES_OPERATOR.validChars[0])
	    setType(TYPE_PATH);
	else
	    // Allow arbitrary characters to reference a node by name.
	    setType(TYPE_NAME);
}

bool NodeReference::isSubscript() const
{
	// TODO: Implementation.
	return subscript;
}

std::string NodeReference::getValueString() const
{
	std::ostringstream status;
	if (value.size() == 0)
	    status << "<empty>";
	else
	status << "'" << value << "', " << nodeRefTypeToString(type) << ", " 
	    << subscript;
	return status.str();
}

void NodeReference::printDebugInfo() const
{
	std::cout << "[NodeReference] DEBUG Info: " << std::endl
	    << "    value     = " << getValue() << std::endl
	    << "    type      = " << getType() << std::endl
	    << "    subscript = " << isSubscript() << std::endl;
}

void NodeReference::setValue(const std::string& newValue)
{
	value = newValue;
}

std::string NodeReference::getValue() const
{
    return value;
}

void NodeReference::setType(Ionflux::Template::NodeRefTypeID newType)
{
	type = newType;
}

Ionflux::Template::NodeRefTypeID NodeReference::getType() const
{
    return type;
}

void NodeReference::setSubscript(bool newSubscript)
{
	subscript = newSubscript;
}

bool NodeReference::getSubscript() const
{
    return subscript;
}

Ionflux::Template::NodeReference& NodeReference::operator=(const 
Ionflux::Template::NodeReference& other)
{
    if (this == &other)
        return *this;
    value = other.value;
    type = other.type;
    subscript = other.subscript;
	return *this;
}

Ionflux::Template::NodeReference* NodeReference::copy() const
{
    NodeReference* newNodeReference = create();
    *newNodeReference = *this;
    return newNodeReference;
}

Ionflux::Template::NodeReference* 
NodeReference::upcast(Ionflux::ObjectBase::IFObject* other)
{
    return dynamic_cast<NodeReference*>(other);
}

Ionflux::Template::NodeReference* 
NodeReference::create(Ionflux::ObjectBase::IFObject* parentObject)
{
    NodeReference* newObject = new NodeReference();
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

/** \file NodeReference.cpp
 * \brief Node reference implementation.
 */
