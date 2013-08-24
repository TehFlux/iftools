#ifndef IONFLUX_TEMPLATE_TREETYPES
#define IONFLUX_TEMPLATE_TREETYPES
/* ==========================================================================
 * IFTemplate - Ionflux Template Processor
 * Copyright © 2012-2013 Jörn P. Meier
 * mail@ionflux.org
 * --------------------------------------------------------------------------
 * treetypes.hpp                     Types used by Tree (header).
 * =========================================================================
 *
 * This file is part of IFTemplate - Ionflux Template Processor.
 * 
 * IFTemplate - Ionflux Template Processor is free software; you can 
 * redistribute it and/or modify it under the terms of the GNU General 
 * Public License as published by the Free Software Foundation; either 
 * version 2 of the License, or (at your option) any later version.
 * 
 * IFTemplate - Ionflux Template Processor is distributed in the hope that it 
 * will be useful, but WITHOUT ANY WARRANTY; without even the implied 
 * warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See 
 * the GNU General Public License for more details.
 * 
 * You should have received a copy of the GNU General Public License along 
 * with IFTemplate - Ionflux Template Processor; if not, write to the Free 
 * Software Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA 
 * 02111-1307 USA
 * 
 * ========================================================================== */
#include <stack>
#include "iftemplate/NodeReference.hpp"
#include "iftemplate/types.hpp"

namespace Ionflux
{

namespace Template
{

class Node;
class Tree;

/// Vector of node references.
typedef std::vector<Ionflux::Template::NodeReference> NodeRefVector;

/// Data Entry.
struct DataEntry
{
	/// parent node.
	Ionflux::Template::Node* node;
	/// index.
	unsigned int index;
	/// Whether this data entry has been specified by a subscript.
	bool subscript;
};

/** Tree path.
 *
 * Represents a full tree path referencing a data entry in the tree.
 */
struct TreePath
{
	/// The tree this path belongs to.
	Ionflux::Template::Tree* tree;
	/// Vector of nodes, in order of top-to-bottom traversal.
	Ionflux::Template::NodeVector nodes;
	/// Data subscript (of the last node).
	int subscript;
	/// Whether the data subscript has been specified explicitly.
	bool explicitSubscript;
};

/** Tree expression element.
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
	Ionflux::Template::DataEntry data;
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

/// Vector of tree expression elements.
typedef std::vector<Ionflux::Template::TreeExprElement> TreeExprElementVector;
/// Stack of tree expression elements.
typedef std::stack<Ionflux::Template::TreeExprElement> TreeExprElementStack;

}

}

/** \file treetypes.hpp
 * \brief Types used by Tree (header).
 */
#endif
