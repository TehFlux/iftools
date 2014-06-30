/* ==========================================================================
 * IFTemplate - Ionflux Template Processor
 * Copyright © 2012 Jörn P. Meier
 * mail@ionflux.org
 * --------------------------------------------------------------------------
 * TreeResolver.cpp                Node reference (implementation).
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

#include "iftemplate/TreeResolver.hpp"
#include <iostream>
#include <iomanip>
#include <sstream>
#include <vector>
#include <cstdlib>
#include "ifobject/utils.hpp"
#include "iftemplate/constants.hpp"
#include "iftemplate/Tree.hpp"
#include "iftemplate/Node.hpp"
#include "iftemplate/NodeReference.hpp"
#include "iftemplate/Tokenizer.hpp"
#include "iftemplate/IFTemplateError.hpp"

using namespace std;

namespace Ionflux
{

namespace Template
{

TreeResolverClassInfo::TreeResolverClassInfo()
{
	name = "TreeResolver";
	desc = "Node reference";
	baseClassInfo.push_back(Ionflux::ObjectBase::IFObject::CLASS_INFO);
}

TreeResolverClassInfo::~TreeResolverClassInfo()
{
}

// public member constants
const Ionflux::Template::TokenType TreeResolver::TT_RES_OPERATOR = { TT_ID_USERTYPE + 1, ".", false, 1 };
const Ionflux::Template::TokenType TreeResolver::TT_SUB_LEFT = { TT_ID_USERTYPE + 2, "[", false, 1 };
const Ionflux::Template::TokenType TreeResolver::TT_SUB_RIGHT = { TT_ID_USERTYPE + 3, "]", false, 1 };
const Ionflux::Template::TokenType TreeResolver::TT_RES_PAR_LEFT = { TT_ID_USERTYPE + 4, "(", false, 1 };
const Ionflux::Template::TokenType TreeResolver::TT_RES_PAR_RIGHT = { TT_ID_USERTYPE + 5, ")", false, 1 };

// run-time type information instance constants
const TreeResolverClassInfo TreeResolver::treeResolverClassInfo;
const Ionflux::ObjectBase::IFClassInfo* TreeResolver::CLASS_INFO = &TreeResolver::treeResolverClassInfo;

TreeResolver::TreeResolver()
{
	// NOTE: The following line is required for run-time type information.
	theClass = CLASS_INFO;
	// TODO: Nothing ATM. ;-)
}

TreeResolver::TreeResolver(const Ionflux::Template::TreeResolver& other)
{
	// NOTE: The following line is required for run-time type information.
	theClass = CLASS_INFO;
	*this = other;
}

TreeResolver::~TreeResolver()
{
	// TODO: Nothing ATM. ;-)
}

bool TreeResolver::parseTreePath(const std::string& treePathExpr, 
Ionflux::Template::NodeRefVector& nodeRefs)
{
	nodeRefs.clear();
	if (treePathExpr.size() == 0)
	    return true;
	/* Prepend resolution operator if not present, unless the path 
	   starts with a subscript. */
	string inputExpr;
	if ((treePathExpr[0] != TreeResolver::TT_RES_OPERATOR.validChars[0])
	    && (treePathExpr[0] != TreeResolver::TT_SUB_LEFT.validChars[0]))
	    inputExpr = ".";
	inputExpr.append(treePathExpr);
	Tokenizer tok(inputExpr);
	tok.addTokenType(TT_RES_OPERATOR);
	tok.addTokenType(TT_SUB_LEFT);
	tok.addTokenType(TT_SUB_RIGHT);
	tok.addTokenType(TT_RES_PAR_LEFT);
	tok.addTokenType(TT_RES_PAR_RIGHT);
	tok.setExtractQuoted(true);
	int nestingLevel;
	bool error = false;
	string errorReason;
	NodeReference currentRef;
	string currentValue;
	string quoteChar;
	Token currentToken = tok.getNextToken();
	while ((currentToken.typeID != TT_NONE.typeID)
	    && (currentToken.typeID != TT_INVALID.typeID)
	    && !error)
	{
	    if (currentToken.typeID == TT_RES_OPERATOR.typeID)
	    {
	        // We have a node reference. Examine next token.
	        currentToken = tok.getNextToken();
	        if ((currentToken.typeID == TT_IDENTIFIER.typeID)
	            || (currentToken.typeID == TT_QUOTED.typeID)
	            || (currentToken.typeID == TT_ESCAPED.typeID))
	        {
	            // Plain node reference.
	            currentRef.setFromRef(currentToken.value);
	            currentRef.setSubscript(false);
	            nodeRefs.push_back(currentRef);
	        } else
	        if (currentToken.typeID == TT_RES_PAR_LEFT.typeID)
	        {
	            // Node reference enclosed in parentheses.
	            currentValue = "";
	            nestingLevel = 1;
	            while (nestingLevel > 0)
	            {
	                currentToken = tok.getNextToken();
	                // Handle nested parentheses.
	                if (currentToken.typeID == TT_RES_PAR_LEFT.typeID)
	                    nestingLevel++;
	                else
	                if (currentToken.typeID == TT_RES_PAR_RIGHT.typeID)
	                    nestingLevel--;
	                /* Append everything but invalid or empty tokens or the
	                   closing quote. */
	                if ((currentToken.typeID != TT_NONE.typeID)
	                    && (currentToken.typeID != TT_INVALID.typeID)
	                    && (nestingLevel != 0))
	                    currentValue.append(currentToken.value);
	                else
	                if (nestingLevel != 0)
	                {
	                    errorReason = "Invalid Token in node reference.";
	                    error = true;
	                }
	            }
	            currentRef.setFromRef(currentValue);
	            currentRef.setSubscript(false);
	            nodeRefs.push_back(currentRef);
	        }
	    } else
	    if (currentToken.typeID == TT_SUB_LEFT.typeID)
	    {
	        // We have a subscript.
	        currentValue = "";
	        nestingLevel = 1;
	        while ((nestingLevel > 0) && !error)
	        {
	            currentToken = tok.getNextToken();
	            // Handle nested quotes.
	            if (currentToken.typeID == TT_SUB_LEFT.typeID)
	                nestingLevel++;
	            else
	            if (currentToken.typeID == TT_SUB_RIGHT.typeID)
	                nestingLevel--;
	            /* Append everything but invalid or empty tokens or the
	               closing quote. */
	            if ((currentToken.typeID != TT_NONE.typeID)
	                && (currentToken.typeID != TT_INVALID.typeID)
	                && (nestingLevel != 0))
	                currentValue.append(currentToken.value);
	            else
	            if (nestingLevel != 0)
	            {
	                errorReason = "Invalid Token in subscript.";
	                error = true;
	            }
	        }
	        currentRef.setFromRef(currentValue);
	        currentRef.setSubscript(true);
	        nodeRefs.push_back(currentRef);
	    } else
	    {
	        errorReason = "Resolution operator or subscript expected.";
	        error = true;
	    }
	    if (!error)
	        currentToken = tok.getNextToken();
	}
	if (currentToken.typeID == TT_INVALID.typeID)
	{
	    errorReason = "Invalid Token.";
	    error = true;
	}
	if (error)
	{
	    string ws("");
	    int errPos = tok.getCurrentTokenPos();
	    if (errPos > 0)
	        ws.append(errPos, ' ');
	    std::ostringstream status;
	    status << "[TreeResolver::parseTreePath] Parse error at position " 
	        << errPos << ":" << endl << treePathExpr << endl << ws << "^" 
	        << endl << "(" << errorReason << ")" << status;
	    throw IFTemplateError(status.str());
	}
	return !error;
}

bool TreeResolver::createTreePath(Ionflux::Template::Tree* tree, 
Ionflux::Template::NodeRefVector& nodeRefs, Ionflux::Template::TreePath& 
treePath, bool createPath, bool nodesOnly)
{
	Ionflux::ObjectBase::nullPointerCheck(tree, 
	    "TreeResolver::createTreePath", "Tree");
	treePath.tree = tree;
	treePath.nodes.clear();
	treePath.subscript = 0;
	treePath.explicitSubscript = false;
	Node* currentNode = tree->getRoot();
	Node* currentChild = 0;
	treePath.nodes.push_back(currentNode);
	NodeReference currentRef;
	int currentID;
	DataEntry currentEntry;
	bool error = false;
	ostringstream status;
	string errorReason;
	unsigned int i = 0;
	int currentRefType = NodeReference::TYPE_INVALID;
	while ((i < nodeRefs.size()) && !error)
	{
	    currentRef = nodeRefs[i];
	    currentRefType = currentRef.getType();
	    currentChild = 0;
	    if (currentNode == 0)
	        throw IFTemplateError("[TreeResolver::createTreePath] "
	            "Current node is null.");
	    if (currentRefType == NodeReference::TYPE_NAME)
	    {
	        // Reference by name.
	        /* ----- DEBUG ----- //
	        cout << "[TreeResolver::createTreePath] DEBUG: "
	            "Current reference value: " << currentRef.getValue() 
	            << endl;
	        // ----- DEBUG ----- */
	        currentChild = currentNode->findChild(
	            currentRef.getValue(), false);
	        if (currentChild != 0)
	        {
	            treePath.nodes.push_back(currentChild);
	            currentNode = currentChild;
	        } else
	        if (createPath)
	        {
	            currentChild = currentNode->addChild();
	            currentChild->setNodeName(currentRef.getValue());
	            treePath.nodes.push_back(currentChild);
	            currentNode = currentChild;
	        } else
	        {
	            status.str("");
	            status << "Could not resolve node name '" 
	                << currentRef.getValue() << "' in node '" 
	                << currentNode->getNodeName() << "'.";
	            errorReason = status.str();
	            error = true;
	        }
	    } else
	    if (currentRefType == NodeReference::TYPE_ID)
	    {
	        // Reference by ID.
	        currentID = strtol(currentRef.getValue().c_str(), 0, 10);
	        /* ----- DEBUG ----- //
	        cout << "[TreeResolver::createTreePath] DEBUG: "
	            "Current reference value: " << currentID << endl;
	        // ----- DEBUG ----- */
	        if ((i == (nodeRefs.size() - 1)) 
	            && (currentRef.isSubscript())
	            && !nodesOnly)
	        {
	            /* This is the last reference in the set, and it has been
	               generated from a subscript, so it actually is a data 
	               index. */
	            treePath.subscript = currentID;
	            treePath.explicitSubscript = true;
	        } else
	        {
	            // This is a node reference.
	            currentChild = currentNode->findChild(currentID, false);
	            if (currentChild != 0)
	            {
	                treePath.nodes.push_back(currentChild);
	                currentNode = currentChild;
	            } else
	            if (createPath)
	            {
	                currentChild = currentNode->addChild();
	                currentChild->setNodeID(currentID);
	                treePath.nodes.push_back(currentChild);
	                currentNode = currentChild;
	            } else
	            {
	                status.str("");
	                status << "Could not resolve node ID " 
	                    << currentRef.getValue() << " in node '" 
	                    << currentNode->getNodeName() << "'.";
	                errorReason = status.str();
	                error = true;
	            }
	        }
	    } else
	    if (currentRefType == NodeReference::TYPE_PATH)
	    {
	        // Reference by data entry.
	        /* ----- DEBUG ----- //
	        cout << "[TreeResolver::createTreePath] DEBUG: "
	            "Current reference value: " << currentRef.getValue() 
	            << endl;
	        // ----- DEBUG ----- */
	        currentEntry = tree->resolve(currentRef.getValue(), false);
	        if (currentEntry.node != 0)
	        {
	            /* Set current reference to result of resolution. */
	            nodeRefs[i].setFromRef(
	                currentEntry.node->getData(currentEntry.index));
	            /* We want to stay put on this reference until it is 
	               either resolved to a name or an ID or there is an 
	               error. */
	            i--;
	        } else
	        {
	            status.str("");
	            status << "Could not resolve tree path '" 
	                << currentRef.getValue() << "'.";
	            errorReason = status.str();
	            error = true;
	        }
	    } else
	    if (currentRefType == NodeReference::TYPE_EMPTY)
	    {
	        // Empty reference.
	        if ((i == (nodeRefs.size() - 1)) 
	            && (currentRef.isSubscript())
	            && !nodesOnly)
	        {
	            /* This is the last reference in the set, and it has been
	               generated from a subscript, so it actually is a data 
	               index. Set subscript value to point to the next data 
	               entry. */
	            treePath.subscript = currentNode->getNumData();
	            treePath.explicitSubscript = true;
	        } else
	        {
	            /* This is a node reference.
	               Set the current ID to the index of the next child node. 
	               TODO: There is a little guesswork involved in this method, 
	               since we cannot be sure that this node ID is not already 
	               in use. If it is, no new node will be added, instead the 
	               existing one will be used. */
	            currentID = currentNode->getNumChildren();
	            currentChild = currentNode->findChild(currentID, false);
	            if (currentChild != 0)
	            {
	                treePath.nodes.push_back(currentChild);
	                currentNode = currentChild;
	            } else
	            if (createPath)
	            {
	                currentChild = currentNode->addChild();
	                currentChild->setNodeID(currentID);
	                treePath.nodes.push_back(currentChild);
	                currentNode = currentChild;
	            } else
	            {
	                status.str("");
	                status << "Could not resolve node ID " 
	                    << currentRef.getValue() << " in node '" 
	                    << currentNode->getNodeName() << "'.";
	                errorReason = status.str();
	                error = true;
	            }
	        }
	    } else
	    if (currentRefType == NodeReference::TYPE_INVALID)
	    {
	        status.str("");
	        status << "Invalid node reference (" << i << ").";
	        errorReason = status.str();
	        error = true;
	    } else
	    {
	            errorReason = "Undefined reference type.";
	            error = true;
	    }
	    i++;
	}
	if (error)
	{
	    std::ostringstream status;
	    status << "[TreeResolver::createTreePath] " << errorReason;
	    throw IFTemplateError(status.str());
	}
	return !error;
}

Ionflux::Template::TreeResolver& TreeResolver::operator=(const 
Ionflux::Template::TreeResolver& other)
{
if (this == &other)
    return *this;
	return *this;
}

Ionflux::Template::TreeResolver* TreeResolver::copy() const
{
    TreeResolver* newTreeResolver = create();
    *newTreeResolver = *this;
    return newTreeResolver;
}

Ionflux::Template::TreeResolver* 
TreeResolver::upcast(Ionflux::ObjectBase::IFObject* other)
{
    return dynamic_cast<TreeResolver*>(other);
}

Ionflux::Template::TreeResolver* 
TreeResolver::create(Ionflux::ObjectBase::IFObject* parentObject)
{
    TreeResolver* newObject = new TreeResolver();
    if (newObject == 0)
    {
        return 0;
    }
    if (parentObject != 0)
        parentObject->addLocalRef(newObject);
    return newObject;
}

unsigned int TreeResolver::getMemSize() const
{
    return sizeof *this;
}

}

}

/** \file TreeResolver.cpp
 * \brief Node reference implementation.
 */
