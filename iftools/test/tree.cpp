/* ==========================================================================
 * Ionflux Tools
 * Copyright (c) 2004 Joern P. Meier
 * mail@ionflux.org
 * --------------------------------------------------------------------------
 * tree.cpp                  Data tree test.
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

#include <iostream>
#include <string>
#include "ionflux/Tree.hpp"

using namespace std;
using namespace Ionflux::Tools;

/// Resolve all tree paths in a vector of strings.
void resolveAll(const std::vector<std::string> &treePathExpr, Tree &tree, 
	bool createPath);

int main(int argc, char* argv[])
{
	/* Simple tree test.
	   See configtree.cpp and template.cpp for additional tests. */
	cout << "Tree test (auto-create disabled):" << endl << endl;
	Tree tree;
	Node *root = tree.getRoot();
	root->setName("Root");
	root->setID(0);
	Node *currentNode;
	currentNode = root->addChild();
	currentNode->setID(1);
	currentNode->setName("A");
	currentNode->addData("Miep");
	currentNode->addData("C");
	currentNode = root->addChild();
	currentNode->setID(2);
	currentNode->setName("B");
	currentNode->addData("Blah");
	currentNode->addData("Blupp");
	currentNode = tree.findNode("B");
	Node *currentChild;
	if (currentNode == 0)
	{
		cout << "ERROR: Node 'B' not found." << endl;
		return 0;
	}
	currentChild = currentNode->addChild();
	currentChild->setID(3);
	currentChild->setName("C");
	currentChild->setDataType(Node::NODE_DATA_INT);
	currentChild->addData(42);
	currentChild = currentNode->addChild();
	currentChild->setID(4);
	currentChild->setName("D");
	currentChild->setDataType(Node::NODE_DATA_DOUBLE);
	currentChild->addData(42.42);
	currentChild->addData(12.0);
	tree.printDebugInfo();
	vector<string> treePathExpr;
	treePathExpr.push_back("2");
	treePathExpr.push_back("2[1]");
	treePathExpr.push_back(".A[0]");
	treePathExpr.push_back("B.(.A[1])");
	treePathExpr.push_back(".B.D[1]");
	cout << "Resolving exising nodes:" << endl;
	resolveAll(treePathExpr, tree, false);
	cout << "Resolving non-existent nodes with createPath = true:" << endl;
	treePathExpr.clear();
	treePathExpr.push_back("A.E.F");
	treePathExpr.push_back("foo.bar.baz");
	resolveAll(treePathExpr, tree, true);
	// Auto-create test.
	cout << endl << "Tree test (auto-create enabled):" << endl << endl;
	Tree tree1;
	tree1.getRoot()->setName("Root");
	tree1.getRoot()->setID(tree1.getRoot()->getUID(true));
	tree1.getRoot()->setAutoCreate(true);
	tree1.getRoot()->setUIDMode(Node::UID_MODE_TREE);
	treePathExpr.clear();
	cout << "Resolving non-existent nodes with createPath = false:" << endl;
	treePathExpr.push_back("foo.bar.baz");
	treePathExpr.push_back("foo.miep");
	treePathExpr.push_back("foo.blupp.blah");
	treePathExpr.push_back("baz2.moop");
	treePathExpr.push_back("baz2.muh.A.B");
	treePathExpr.push_back("baz2.muh.C");
	resolveAll(treePathExpr, tree1, false);
	// Subscripting & assignment test.
	Node &root1 = *tree1.getRoot();
	root1["D"][42] = "Hello tree!";
	cout << endl;
	tree1.printDebugInfo();
	return 0;
}

void resolveAll(const std::vector<std::string> &treePathExpr, Tree &tree, 
	bool createPath)
{
	DataEntry data;
	vector<string>::const_iterator i;
	for (i = treePathExpr.begin(); i != treePathExpr.end(); i++)
	{
		data = tree.resolve(*i, createPath);
		if (data.node != 0)
		{
			cout << "    Tree Path '" << *i << "' resolves to '" 
				<< data.node->getData(data.index) << "'" << endl;
		} else
		{
			cout << "    ERROR: Could not resolve tree path '" << *i
				<< "'" << endl;
		}
	}
}

/** \file tree.cpp
 * \brief Data tree test.
 */
