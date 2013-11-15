/* ==========================================================================
 * IFTemplate - Ionflux Template Processor
 * Copyright © 2012 Jörn P. Meier
 * mail@ionflux.org
 * --------------------------------------------------------------------------
 * Tree.cpp                        Tree (implementation).
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

#include "iftemplate/Tree.hpp"
#include <iostream>
#include <iomanip>
#include <sstream>
#include <vector>
#include "ifobject/utils.hpp"
#include "iftemplate/constants.hpp"
#include "iftemplate/utils.hpp"
#include "iftemplate/Node.hpp"
#include "iftemplate/TreeResolver.hpp"
#include "iftemplate/TreeEval.hpp"
#include "iftemplate/IFTemplateError.hpp"

using namespace std;

namespace Ionflux
{

namespace Template
{

TreeClassInfo::TreeClassInfo()
{
	name = "Tree";
	desc = "Tree";
	baseClassInfo.push_back(Ionflux::ObjectBase::IFObject::CLASS_INFO);
}

TreeClassInfo::~TreeClassInfo()
{
}

// run-time type information instance constants
const TreeClassInfo Tree::treeClassInfo;
const Ionflux::ObjectBase::IFClassInfo* Tree::CLASS_INFO = &Tree::treeClassInfo;

Tree::Tree()
: root(0)
{
	// NOTE: The following line is required for run-time type information.
	theClass = CLASS_INFO;
	initRoot();
}

Tree::Tree(const Ionflux::Template::Tree& other)
: root(0)
{
	// NOTE: The following line is required for run-time type information.
	theClass = CLASS_INFO;
	*this = other;
}

Tree::Tree(Ionflux::Template::Node* initRoot0)
: root(0)
{
	// NOTE: The following line is required for run-time type information.
	theClass = CLASS_INFO;
	if (initRoot0 != 0)
	    setRoot(initRoot0);
	else
	    initRoot();
}

Tree::~Tree()
{
	// TODO: Nothing ATM. ;-)
}

void Tree::initRoot()
{
	Node* root0 = Node::create();
	/* <---- DEBUG ----- //
	root0->setID("root");
	// ----- DEBUG ----- */
	root0->setNodeName("<root>");
	root0->setNodeID(root0->getUID(true));
	root0->setDataType(Node::DATA_BLOB);
	root0->setUidMode(Node::UID_MODE_NONE);
	root0->setLogTarget(this);
	/* <---- DEBUG ----- //
	std::cerr << "[Tree::initRoot] DEBUG: Created root node " << root0 
	    << std::endl;
	// ----- DEBUG ----- */
	setRoot(root0);
}

void Tree::clear()
{
	if (root != 0)
	    root->clear();
}

unsigned int Tree::getNumNodes()
{
	if (root == 0)
	    return 0;
	return root->getNumChildren() + 1;
}

Ionflux::Template::Node* Tree::findNode(int nodeID)
{
	if (root == 0)
	    return 0;
	return root->findChild(nodeID, true);
}

Ionflux::Template::Node* Tree::findNode(const std::string& nodeName)
{
	if (root == 0)
	    return 0;
	return root->findChild(nodeName, true);
}

Ionflux::Template::DataEntry Tree::resolve(const std::string& treePathExpr,
bool createPath, bool nodesOnly)
{
	DataEntry result;
	result.node = 0;
	result.index = 0;
	result.subscript = false;
	vector<NodeReference> nodeRefs;
	TreePath treePath;
	if (!TreeResolver::parseTreePath(treePathExpr, nodeRefs))
	    return result;
	if (!TreeResolver::createTreePath(this, nodeRefs, treePath, createPath, 
	    nodesOnly))
	    return result;
	result.node = treePath.nodes[treePath.nodes.size() - 1];
	result.index = treePath.subscript;
	result.subscript = treePath.explicitSubscript;
	return result;
}

bool Tree::eval(const std::string& treeExpr, Ionflux::Template::Node& 
result, bool createPath)
{
	TreeExprElementVector elements;
	if (TreeEval::parseTreeExpr(treeExpr, elements))
	    return TreeEval::eval(this, elements, result, createPath);
	return false;
}

Ionflux::Template::Node& Tree::operator[](int searchID)
{
	if (root == 0)
	    initRoot();
	return (*root)[searchID];
}

Ionflux::Template::Node& Tree::operator[](const std::string& searchName)
{
	if (root == 0)
	    initRoot();
	return (*root)[searchName];
}

void Tree::writeToFile(const std::string& fileName)
{
	if (root == 0)
	    throw IFTemplateError("[Tree::writeToFile] "
	        "Cannot write to file: Root node is null.");
	string serializedTree;
	root->serialize(serializedTree);
	Ionflux::ObjectBase::writeFile(fileName, serializedTree, 'w');
}

void Tree::readFromFile(const std::string& fileName)
{
	if (root == 0)
	    initRoot();
	string fileInput;
	Ionflux::ObjectBase::readFile(fileName, fileInput);
	if (fileInput.size() == 0)
	    throw IFTemplateError("[Tree::readFromFile] "
	        "File contains no data.");
	root->unpack(fileInput, 0, 0);
}

void Tree::printDebugInfo()
{
	if (root == 0)
	{
	    cout << "This tree is empty." << endl;
	    return;
	}
	int currentLevel = 0;
	while(root->printDebugInfo(currentLevel))
	    currentLevel++;
}

void Tree::setRoot(Ionflux::Template::Node* newRoot)
{
	if (root == newRoot)
		return;
    if (newRoot != 0)
        addLocalRef(newRoot);
	if (root != 0)
		removeLocalRef(root);
	root = newRoot;
}

Ionflux::Template::Node* Tree::getRoot() const
{
    return root;
}

Ionflux::Template::Tree& Tree::operator=(const Ionflux::Template::Tree& 
other)
{
    if (this == &other)
        return *this;
    if (other.root != 0)
        setRoot(other.root->copy());
    else
        initRoot();
	return *this;
}

Ionflux::Template::Tree* Tree::copy() const
{
    Tree* newTree = create();
    *newTree = *this;
    return newTree;
}

Ionflux::Template::Tree* Tree::upcast(Ionflux::ObjectBase::IFObject* other)
{
    return dynamic_cast<Tree*>(other);
}

Ionflux::Template::Tree* Tree::create(Ionflux::ObjectBase::IFObject* 
parentObject)
{
    Tree* newObject = new Tree();
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

/** \file Tree.cpp
 * \brief Tree implementation.
 */
