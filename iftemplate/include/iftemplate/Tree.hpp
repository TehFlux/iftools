#ifndef IONFLUX_TEMPLATE_TREE
#define IONFLUX_TEMPLATE_TREE
/* ==========================================================================
 * IFTemplate - Ionflux Template Processor
 * Copyright © 2012 Jörn P. Meier
 * mail@ionflux.org
 * --------------------------------------------------------------------------
 * Tree.hpp                        Tree (header).
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

#include <string>
#include "iftemplate/types.hpp"
#include "iftemplate/treetypes.hpp"
#include "ifobject/IFObject.hpp"

namespace Ionflux
{

namespace Template
{

class Node;

/// Class information for class Tree.
class TreeClassInfo
: public Ionflux::ObjectBase::IFClassInfo
{
	public:
		/// Constructor.
		TreeClassInfo();
		/// Destructor.
		virtual ~TreeClassInfo();
};

/** Tree.
 * \ingroup iftemplate
 *
 * Tree type data structure. This behaves almost like a Node, but maintains
 * a special node (the root node) as well as providing some convenience 
 * functions for I/O.
 */
class Tree
: virtual public Ionflux::ObjectBase::IFObject
{
	private:
		
	protected:
		/// root node.
		Ionflux::Template::Node* root;
		
	public:
		/// Class information instance.
		static const TreeClassInfo treeClassInfo;
		/// Class information.
		static const Ionflux::ObjectBase::IFClassInfo* CLASS_INFO;
		
		/** Constructor.
		 *
		 * Construct new Tree object.
		 */
		Tree();
		
		/** Constructor.
		 *
		 * Construct new Tree object.
		 *
		 * \param other Other object.
		 */
		Tree(const Ionflux::Template::Tree& other);
		
		/** Constructor.
		 *
		 * Construct new Tree object.
		 *
		 * \param initRoot0 root node.
		 */
		Tree(Ionflux::Template::Node* initRoot0);
		
		/** Destructor.
		 *
		 * Destruct Tree object.
		 */
		virtual ~Tree();
		
		/** Initialize root node.
		 *
		 * Initialize the root node.
		 */
		virtual void initRoot();
		
		/** Clear.
		 *
		 * Clear all nodes from the tree.
		 */
		virtual void clear();
		
		/** Get number of nodes.
		 *
		 * Number of nodes in the tree.
		 *
		 * \return number of nodes in the tree.
		 */
		virtual unsigned int getNumNodes();
		
		/** Find node.
		 *
		 * Searches the tree for a node with the specified ID.
		 *
		 * \param nodeID ID of the node to be returned.
		 *
		 * \return Node, or 0 if node with the specified ID was not found.
		 */
		virtual Ionflux::Template::Node* findNode(int nodeID);
		
		/** Find node.
		 *
		 * Searches the tree for a node with the specified ID.
		 *
		 * \param nodeName name of the node to be returned.
		 *
		 * \return Node, or 0 if node with the specified name was not found.
		 */
		virtual Ionflux::Template::Node* findNode(const std::string& nodeName);
		
		/** Resolve fully qualified tree path.
		 *
		 * Resolve a fully qualified tree path. Pass \c true to \c createPath 
		 * to create a tree path on the fly if it does not already exist.
		 *
		 * \param treePathExpr fully qualified tree path.
		 * \param createPath whether to create the path if it does not already 
		 * exist.
		 * \param nodesOnly whether subscripts should be treated as child node 
		 * references by default.
		 *
		 * \return The data entry referenced by the specified tree path. If the 
		 * specified node is not found (and cannot be auto-created), the 
		 * corresponding field in the data entry will be set to 0..
		 */
		virtual Ionflux::Template::DataEntry resolve(const std::string& 
		treePathExpr, bool createPath = false, bool nodesOnly = false);
		
		/** Evaluate tree expression.
		 *
		 * Evaluates a tree expression using nodes from the tree as variables.
		 * Pass \c true to \c createPath to create tree paths on the fly if it
		 * they do not already exist.
		 *
		 * \param treeExpr tree expression.
		 * \param result where to store the result of the evaluation.
		 * \param createPath whether to create a path if it does not already 
		 * exist.
		 *
		 * \return \c true on success, \c false if there was an error.
		 */
		virtual bool eval(const std::string& treeExpr, Ionflux::Template::Node& 
		result, bool createPath);
		
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
		 * \sa Ionflux::Tools::Node::findChild()
		 *
		 * \param searchID ID of the node to be returned.
		 *
		 * \return First child node with specified ID, or a newly created node 
		 * with that ID.
		 */
		virtual Ionflux::Template::Node& operator[](int searchID);
		
		/** Find child node.
		 *
		 * Return a child of the root node by numerical ID. Returns the first 
		 * child node with the specified name.
		 * 
		 * \note This will always create non-existent nodes, even with 
		 * auto-create turned off. If you do not want this, you should not use
		 * subscripting, but findChild() instead. Also be aware that you 
		 * cannot use subscription operators to access data fields in your 
		 * code, while this is possible if you use subscripting in tree path 
		 * expressions which are parsed at run-time. Use getData() or parsed 
		 * tree paths if you want to access data entries in your source.
		 * 
		 * \sa Ionflux::Tools::Node::findChild()
		 *
		 * \param searchName name of the child node to be returned.
		 *
		 * \return First child node with specified name, or a newly created node 
		 * with that name.
		 */
		virtual Ionflux::Template::Node& operator[](const std::string& 
		searchName);
		
		/** Write tree to file.
		 *
		 * Writes the tree to a binary file.
		 *
		 * \param fileName name of the output file.
		 */
		virtual void writeToFile(const std::string& fileName);
		
		/** Read tree from file.
		 *
		 * Reads tree data from a binary file.
		 *
		 * \param fileName name of the input file.
		 */
		virtual void readFromFile(const std::string& fileName);
		
		/** Print debug information.
		 *
		 * Prints debug information for the tree.
		 */
		virtual void printDebugInfo();
		
		/** Assignment operator.
		 *
		 * Assign an object.
		 *
		 * \param other Other object.
		 *
		 * \return The object itself.
		 */
		virtual Ionflux::Template::Tree& operator=(const Ionflux::Template::Tree&
		other);
		
		/** Copy.
		 *
		 * Create a copy of the object.
		 *
		 * \return Newly allocated copy of the object.
		 */
		virtual Ionflux::Template::Tree* copy() const;
		
		/** Upcast.
		 *
		 * Cast an IFObject to the most specific type.
		 *
		 * \param other Other object.
		 *
		 * \return The more specific object, or 0 if the cast failed.
		 */
		static Ionflux::Template::Tree* upcast(Ionflux::ObjectBase::IFObject* 
		other);
		
		/** Create instance.
		 *
		 * Create a new instance of the class. If the optional parent object 
		 * is specified, a local reference for the new object will be added 
		 * to the parent object.
		 *
		 * \param parentObject Parent object.
		 *
		 * \return Pointer to the new instance.
		 */
		static Ionflux::Template::Tree* create(Ionflux::ObjectBase::IFObject* 
		parentObject = 0);
		
		/** Get root node.
		 *
		 * \return Current value of root node.
		 */
		virtual Ionflux::Template::Node* getRoot() const;
		
		/** Set root node.
		 *
		 * Set new value of root node.
		 *
		 * \param newRoot New value of root node.
		 */
		virtual void setRoot(Ionflux::Template::Node* newRoot);
};

}

}

/** \file Tree.hpp
 * \brief Tree (header).
 */
#endif
