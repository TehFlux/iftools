/* ==========================================================================
 * Ionflux Tools
 * Copyright (c) 2004 Joern P. Meier
 * mail@ionflux.org
 * --------------------------------------------------------------------------
 * Tree.cpp                    Data tree.
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

#include "ionflux/Tree.hpp"

using namespace std;

namespace Ionflux
{

namespace Tools
{

Tree::Tree()
{
	root.node = new Node();
	root.manage = true;
	root.node->setName("<root>");
	root.node->setID(root.node->getUID(true));
	root.node->setDataType(Node::NODE_DATA_BLOB);
	root.node->setUIDMode(Node::UID_MODE_NONE);
	root.node->getLog().redirect(&log);
}

Tree::Tree(Node *initRoot, bool initManage)
{
	root.node = initRoot;
	root.manage = initManage;
}

Tree::~Tree()
{
	if ((root.node != 0) && (root.manage))
		delete root.node;
	root.node = 0;
	root.manage = false;
}

Node *Tree::findNode(int nodeID)
{
	if (root.node == 0)
		return 0;
	return root.node->findChild(nodeID, true);
}

Node *Tree::findNode(const std::string &nodeName)
{
	if (root.node == 0)
		return 0;
	return root.node->findChild(nodeName, true);
}

DataEntry Tree::resolve(const std::string &treePathExpr, bool createPath, 
	bool nodesOnly)
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

void Tree::setRoot(Node *newRoot, bool newManage)
{
	if (root.node != 0)
		delete root.node;
	root.node = newRoot;
	root.manage = newManage;
	if (root.node != 0)
		root.node->getLog().redirect(&log);
}

void Tree::writeToFile(const std::string &fileName)
{
	if (root.node == 0)
	{
		log.msg("[Tree::writeToFile] ERROR: Cannot write to file: Root node "
			"is null.", log.VL_ERROR);
		return;
	}
	string serializedTree;
	string compressedTree;
	root.node->serialize(serializedTree);
	if (log.assert(serializedTree.size() > 0, "[Tree::writeToFile] "
			"Serialization returned empty string."))
		bz2Compress(serializedTree, compressedTree);
	writeFile(fileName, compressedTree, 'w');
}

void Tree::readFromFile(const std::string &fileName)
{
	if (root.node == 0)
	{
		root.node = new Node();
		root.manage = true;
		root.node->getLog().redirect(&log);
	}
	string fileInput;
	string decompressedTree;
	string unpackedTree;
	fileInput = readFile(fileName);
	if (fileInput.size() == 0)
	{
		log.msg("[Tree::readFromFile] ERROR: File contains no data.", 
			log.VL_ERROR);
		return;
	}
	bool result = bz2Decompress(fileInput, decompressedTree);
	if (!result)
	{
		log.msg("[Tree::readFromFile] ERROR: Data decompression failed.", 
			log.VL_ERROR);
		return;
	}
	root.node->unpack(decompressedTree, 0, 0);
}

bool Tree::eval(const std::string &treeExpr, Node &result, bool createPath)
{
	vector<TreeExprElement> elements;
	if (TreeEval::parseTreeExpr(treeExpr, elements))
		return TreeEval::eval(this, elements, result, createPath);
	return false;
}

Node &Tree::operator[](int searchID)
{
	if (root.node == 0)
	{
		root.node = new Node();
		root.manage = true;
	}
	return (*root.node)[searchID];
}

Node &Tree::operator[](const std::string &searchName)
{
	if (root.node == 0)
	{
		root.node = new Node();
		root.manage = true;
		root.node->getLog().redirect(&log);
	}
	return (*root.node)[searchName];
}

Node *Tree::getRoot()
{
	return root.node;
}

int Tree::getNumNodes()
{
	if (root.node == 0)
		return 0;
	return root.node->getNumChildren(true) + 1;
}

void Tree::printDebugInfo()
{
	if (root.node == 0)
	{
		cout << "This tree is empty." << endl;
		return;
	}
	int currentLevel = 0;
	while(root.node->printDebugInfo(currentLevel))
		currentLevel++;
}

void Tree::clear()
{
	if (root.node == 0)
		return;
	root.node->clear();
}

Reporter &Tree::getLog()
{
	return log;
}

}

}

/** \file Tree.cpp
 * \brief Data tree implementation.
 */
