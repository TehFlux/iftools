#ifndef IONFLUX_TEMPLATE_TREERESOLVER
#define IONFLUX_TEMPLATE_TREERESOLVER
/* ==========================================================================
 * IFTemplate - Ionflux Template Processor
 * Copyright © 2012 Jörn P. Meier
 * mail@ionflux.org
 * --------------------------------------------------------------------------
 * TreeResolver.hpp                Node reference (header).
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

class Tree;

/// Class information for class TreeResolver.
class TreeResolverClassInfo
: public Ionflux::ObjectBase::IFClassInfo
{
	public:
		/// Constructor.
		TreeResolverClassInfo();
		/// Destructor.
		virtual ~TreeResolverClassInfo();
};

/** Node reference.
 * \ingroup iftemplate
 *
 * A node reference specifies a tree node, relative to its parent node, in 
 * human readable form. A tree node reference may be generated from a child
 * node ID, a node name, or a fully qualified tree path (i.e. a data 
 * entry).
 */
class TreeResolver
: public Ionflux::ObjectBase::IFObject
{
	private:
		
	protected:
		
	public:
		/// Token type: resolution operator.
		static const Ionflux::Template::TokenType TT_RES_OPERATOR;
		/// Token type: resolution operator.
		static const Ionflux::Template::TokenType TT_SUB_LEFT;
		/// Token type: resolution operator.
		static const Ionflux::Template::TokenType TT_SUB_RIGHT;
		/// Token type: resolution operator.
		static const Ionflux::Template::TokenType TT_RES_PAR_LEFT;
		/// Token type: resolution operator.
		static const Ionflux::Template::TokenType TT_RES_PAR_RIGHT;
		/// Class information instance.
		static const TreeResolverClassInfo treeResolverClassInfo;
		/// Class information.
		static const Ionflux::ObjectBase::IFClassInfo* CLASS_INFO;
		
		/** Constructor.
		 *
		 * Construct new TreeResolver object.
		 */
		TreeResolver();
		
		/** Constructor.
		 *
		 * Construct new TreeResolver object.
		 *
		 * \param other Other object.
		 */
		TreeResolver(const Ionflux::Template::TreeResolver& other);
		
		/** Destructor.
		 *
		 * Destruct TreeResolver object.
		 */
		virtual ~TreeResolver();
		
		/** Parse a tree path.
		 *
		 * Parses a tree path into node references.
		 *
		 * \param treePathExpr tree path expression.
		 * \param nodeRefs vector in which to store node references.
		 *
		 * \return \c true on success, \c false if there was an error.
		 */
		static bool parseTreePath(const std::string& treePathExpr, 
		Ionflux::Template::NodeRefVector& nodeRefs);
		
		/** Create tree path.
		 *
		 * Creates a tree path from a tree and a set of node references. Pass 
		 * \c true to \c createPath to create a tree path on the fly if it 
		 * does not already exist.
		 *
		 * \param tree tree for which the path should be created.
		 * \param nodeRefs node references from which to create a tree path.
		 * \param treePath where to store the resulting tree path.
		 * \param createPath whether to create the path if it does not already 
		 * exist.
		 * \param nodesOnly Whether subscripts should be treated as child node 
		 * references by default.
		 *
		 * \return \c true on success, \c false if there was an error.
		 */
		static bool createTreePath(Ionflux::Template::Tree* tree, 
		Ionflux::Template::NodeRefVector& nodeRefs, Ionflux::Template::TreePath& 
		treePath, bool createPath, bool nodesOnly = false);
		
		/** Assignment operator.
		 *
		 * Assign an object.
		 *
		 * \param other Other object.
		 *
		 * \return The object itself.
		 */
		virtual Ionflux::Template::TreeResolver& operator=(const 
		Ionflux::Template::TreeResolver& other);
		
		/** Copy.
		 *
		 * Create a copy of the object.
		 *
		 * \return Newly allocated copy of the object.
		 */
		virtual Ionflux::Template::TreeResolver* copy() const;
		
		/** Upcast.
		 *
		 * Cast an IFObject to the most specific type.
		 *
		 * \param other Other object.
		 *
		 * \return The more specific object, or 0 if the cast failed.
		 */
		static Ionflux::Template::TreeResolver* 
		upcast(Ionflux::ObjectBase::IFObject* other);
		
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
		static Ionflux::Template::TreeResolver* 
		create(Ionflux::ObjectBase::IFObject* parentObject = 0);
};

}

}

/** \file TreeResolver.hpp
 * \brief Node reference (header).
 */
#endif
