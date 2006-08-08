#ifndef IONFLUX_TOOLS_TREE
#define IONFLUX_TOOLS_TREE
/* ==========================================================================
 * Ionflux Tools
 * Copyright (c) 2004 Joern P. Meier
 * mail@ionflux.org
 * --------------------------------------------------------------------------
 * Tree.hpp                    Data tree.
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

#include <string>
#include <iostream>
#include "ionflux/tools.hpp"
#include "ionflux/Reporter.hpp"
#include "ionflux/Node.hpp"
#include "ionflux/TreeResolver.hpp"
#include "ionflux/TreeEval.hpp"

namespace Ionflux
{

namespace Tools
{

class Node;
struct NodeInfo;
class TreeResolver;
struct TreePath;
class TreeEval;
struct TreeExprElement;
class Tree;

/** Data Entry.
 * \ingroup datahand
 *
 * Complete reference to a node data entry.
 */
struct DataEntry
{
	/// Parent node.
	Node *node;
	/// Data entry index.
	unsigned int index;
	/// Whether this data entry has been specified by a subscript.
	bool subscript;
};

/** Tree path.
 * \ingroup datahand
 *
 * Represents a full tree path referencing a data entry in the tree.
 */
struct TreePath
{
	/// The tree this path belongs to.
	Tree *tree;
	/// Vector of nodes, in order of top-to-bottom traversal.
	std::vector<Node *> nodes;
	/// Data subscript (of the last node).
	int subscript;
	/// Whether the data subscript has been specified explicitly.
	bool explicitSubscript;
};

/** Tree expression element.
 * \ingroup datahand
 *
 * Part of a tree expression, such as a constant, a variable or an operator.
 */
struct TreeExprElement
{
	/// Element type.
	int type;
	/// Element value.
	std::string value;
	/// Data entry.
	DataEntry data;
	/// Force unary operator if ambiguous.
	bool unary;
	/// Element type: Invalid.
	static const int TE_INVALID;
	/// Element type: Constant.
	static const int TE_CONST;
	/// Element type: Variable.
	static const int TE_VAR;
	/// Element type: Operator.
	static const int TE_OP;
};

/** Data tree.
 * \ingroup datahand
 *
 * Tree type data structure. This behaves almost like a Node, but maintains a 
 * special node (the root node) as well as providing some convenience 
 * functions for I/O.
 */
class Tree
{
	protected:
		/// Console output/logging.
		Ionflux::Tools::Reporter log;
		/// Root node.
		NodeInfo root;
		
	public:
		/** Constructor.
		 *
		 * Construct new Tree object.
		 */
		Tree();
		
		/** Constructor.
		 *
		 * Construct new Tree object.
		 *
		 * \param initRoot The root node of this tree.
		 * \param initManage Whether memory allocated for the root node should 
		 * be managed by this tree.
		 */
		Tree(Node *initRoot, bool initManage);
		
		/** Destructor.
		 *
		 * Destruct Tree object.
		 */
		virtual ~Tree();
		
		/** Find node.
		 *
		 * Searches the tree for a node with the specified ID.
		 *
		 * \param nodeID The ID of the node to be returned.
		 *
		 * \return Pointer to node with specified ID if found, 0 otherwise.
		 */
		virtual Node *findNode(int nodeID);
		
		/** Find node.
		 *
		 * Searches the tree for a node with the specified name.
		 *
		 * \param nodeName The name of the node to be returned.
		 *
		 * \return Pointer to node with specified name if found, 0 otherwise.
		 */
		virtual Node *findNode(const std::string &nodeName);
		
		/** Resolve fully qualified tree path.
		 *
		 * Resolve a fully qualified tree path. Pass \c true to \c createPath 
		 * to create a tree path on the fly if it does not already exist.
		 *
		 * \param treePathExpr Fully qualified tree path.
		 * \param createPath Whether to create the path if it does not already 
		 * exist.
		 * \param nodesOnly Whether subscripts should be treated as child 
		 * node references by default.
		 *
		 * \return The data entry referenced by the specified tree path. If 
		 * the specified node is not found (and cannot be auto-created), the 
		 * corresponding field in the data entry will be set to 0.
		 */
		virtual DataEntry resolve(const std::string &treePathExpr, 
			bool createPath, bool nodesOnly = false);
		
		/** Set root node.
		 *
		 * Sets the root node of this tree to specified node.
		 *
		 * \param newRoot The root node of this tree.
		 * \param newManage Whether memory allocated for the root node should 
		 * be managed by this tree.
		 */
		virtual void setRoot(Node *newRoot, bool newManage);
		
		/** Write tree to file.
		 *
		 * Writes the tree to a file.
		 *
		 * \param fileName Name of the output file.
		 */
		virtual void writeToFile(const std::string &fileName);
		
		/** Read tree from file.
		 *
		 * Reads the tree from a file.
		 *
		 * \param fileName Name of the input file.
		 */
		virtual void readFromFile(const std::string &fileName);
		
		/** Evaluate tree expression.
		 *
		 * Evaluates a tree expression using nodes from the tree as variables. 
		 * Pass \c true to \c createPath to create tree paths on the fly if 
		 * it they do not already exist.
		 *
		 * \param treeExpr Tree expression.
		 * \param result Where to store the result of the evaluation.
		 * \param createPath Whether to create a path if it does not already 
		 * exist.
		 *
		 * \return \c true on success, \c false if there was an error.
		 */
		virtual bool eval(const std::string &treeExpr, Node &result, 
			bool createPath);
		
		/** Find child node.
		 *
		 * Return a child of the root node by numerical ID. Returns the first 
		 * child node with the specified ID.
		 *
		 * \note This will always create non-existent nodes, even with 
		 * auto-create turned off. If you do not want this, you should not use 
		 * subscripting, but findChild() instead. Also be aware that you 
		 * cannot use subscription operators to access data fields in your 
		 * code, while this is possible if you use subscripting in tree path 
		 * expressions which are parsed at run-time. Use getData() or parsed 
		 * tree paths if you want to access data entries in your source.
		 *
		 * \param searchID The ID of the child node to be returned.
		 *
		 * \return First child node with specified ID, or a newly created node 
		 * with that ID.
		 *
		 * \sa Ionflux::Tools::Node::findChild()
		 */
		virtual Node &operator[](int searchID);
		
		/** Find child node.
		 *
		 * Return a child of the root node by name. Returns the first child 
		 * node with the specified name.
		 *
		 * \note This will always create non-existent nodes, even with 
		 * auto-create turned off. If you do not want this, you should not use 
		 * subscripting, but findChild() instead. Also be aware that you 
		 * cannot use subscription operators to access data fields in your 
		 * code, while this is possible if you use subscripting in tree path 
		 * expressions which are parsed at run-time. Use getData() or parsed 
		 * tree paths if you want to access data entries in your source.
		 *
		 * \param searchName The name of the child node to be returned.
		 *
		 * \return First child node with specified name, or a newly created 
		 * node with that name.
		 *
		 * \sa Ionflux::Tools::Node::findChild()
		 */
		virtual Node &operator[](const std::string &searchName);
		
		/// Print debug information.
		virtual void printDebugInfo();
		
		/** Get root node.
		 *
		 * \return The root node of the tree.
		 */
		virtual Node *getRoot();
		
		/** Get number of nodes.
		 *
		 * \return Number of nodes in the tree.
		 */
		virtual int getNumNodes();
		
		/// Clear the tree.
		virtual void clear();
		
		/** Get Console output/logging facility.
		 *
		 * \return The console output/logging facility used by this object.
		 */
		virtual Reporter &getLog();
};

}

}

/** \file Tree.hpp
 * \brief Data tree header.
 */
#endif
