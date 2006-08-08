#ifndef IONFLUX_TOOLS_TREERESOLVER
#define IONFLUX_TOOLS_TREERESOLVER
/* ==========================================================================
 * Ionflux Tools
 * Copyright (c) 2004 Joern P. Meier
 * mail@ionflux.org
 * --------------------------------------------------------------------------
 * TreeResolver.hpp                    Tree path resolution.
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
#include <vector>
#include "ionflux/Tree.hpp"
#include "ionflux/Tokenizer.hpp"
#include "ionflux/NodeReference.hpp"

namespace Ionflux
{

namespace Tools
{

struct DataEntry;
struct TreePath;
class Tree;
class NodeReference;

/** Tree resolver.
 * \ingroup datahand
 *
 * Resolves a fully qualified tree path. (See 
 * <tt>misc/path-resolution.txt</tt>, \ref tpldoc and \ref configdoc for 
 * additional information.)
 */
class TreeResolver
{
	protected:
		
	public:
		/// Token type: Resolution operator.
		static const TokenType TT_RES_OPERATOR;
		/// Token type: Subscript left.
		static const TokenType TT_SUB_LEFT;
		/// Token type: Subscript right.
		static const TokenType TT_SUB_RIGHT;
		/// Token type: Reference parenthesis (left).
		static const TokenType TT_RES_PAR_LEFT;
		/// Token type: Reference parenthesis (right).
		static const TokenType TT_RES_PAR_RIGHT;
		
		/** Constructor.
		 *
		 * Construct new TreeResolver object.
		 */
		TreeResolver();
		
		/** Destructor.
		 *
		 * Destruct TreeResolver object.
		 */
		virtual ~TreeResolver();
		
		/** Parse a tree path.
		 *
		 * Parses a tree path into node references.
		 *
		 * \param treePathExpr Tree path expression.
		 * \param nodeRefs Vector in which to store node references.
		 *
		 * \return \c true on success, \c false if there was an error.
		 */
		static bool parseTreePath(const std::string &treePathExpr, 
			std::vector<NodeReference> &nodeRefs);
		
		/** Create tree path.
		 *
		 * Creates a tree path from a tree and a set of node references. 
		 * Pass \c true to \c createPath to create a tree path on the fly if 
		 * it does not already exist.
		 *
		 * \param tree Tree for which the path should be created.
		 * \param nodeRefs Node references from which to create a tree path.
		 * \param treePath Where to store the resulting tree path.
		 * \param createPath Whether to create the path if it does not already 
		 * exist.
		 * \param nodesOnly Whether subscripts should be treated as child 
		 * node references by default.
		 *
		 * \return \c true on success, \c false if there was an error.
		 */
		static bool createTreePath(Tree *tree, 
			std::vector<NodeReference> &nodeRefs, TreePath &treePath, 
			bool createPath, bool nodesOnly = false);
		
};

}

}

/** \file TreeResolver.hpp
 * \brief Tree path resolution header.
 */
#endif
