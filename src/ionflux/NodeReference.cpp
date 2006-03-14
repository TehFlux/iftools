/* ==========================================================================
 * Ionflux Tools
 * Copyright (c) 2004 Joern P. Meier
 * mail@ionflux.org
 * --------------------------------------------------------------------------
 * NodeReference.cpp                    Tree node reference.
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

#include "ionflux/NodeReference.hpp"

using namespace std;

namespace Ionflux
{

namespace Tools
{

const int NodeReference::REF_INVALID = 0;
const int NodeReference::REF_NAME = 1;
const int NodeReference::REF_ID = 2;
const int NodeReference::REF_PATH = 3;
const int NodeReference::REF_EMPTY = 4;

NodeReference::NodeReference()
: value(""), type(REF_INVALID), subscript(false)
{
	// TODO: Nothing ATM. ;-)
}

NodeReference::NodeReference(const std::string &refExpr)
: value(""), type(REF_INVALID), subscript(false)
{
	setFromRef(refExpr);
}

NodeReference::~NodeReference()
{
	// TODO: Nothing ATM. ;-)
}

void NodeReference::setFromRef(const std::string &refExpr)
{
	setValue(refExpr);
	if (refExpr.size() == 0)
		setType(REF_EMPTY);
	else
	if (isInteger(refExpr))
		setType(REF_ID);
	else
	if (refExpr[0] == TreeResolver::TT_RES_OPERATOR.validChars[0])
		setType(NodeReference::REF_PATH);
	else
		// Allow arbitrary characters to reference a node by name.
		setType(NodeReference::REF_NAME);
}

void NodeReference::setValue(const std::string& newValue)
{
	value = newValue;
}

void NodeReference::setType(int newType)
{
	type = newType;
}

void NodeReference::setSubscript(bool newSubscript)
{
	subscript = newSubscript;
}

std::string NodeReference::getValue() const
{
	return value;
}

int NodeReference::getType() const
{
	return type;
}

bool NodeReference::isSubscript() const
{
	return subscript;
}

void NodeReference::clear()
{
	setValue("");
	setType(REF_INVALID);
	setSubscript(false);
}

void NodeReference::printDebugInfo() const
{
	cout << "[NodeReference] DEBUG Info: " << endl
		<< "    value     = " << getValue() << endl
		<< "    type      = " << getType() << endl
		<< "    subscript = " << isSubscript() << endl;
}

}

}

/** \file NodeReference.cpp
 * \brief Tree node reference implementation.
 */
