#ifndef IONFLUX_TOOLS_NODEREFERENCE
#define IONFLUX_TOOLS_NODEREFERENCE
/* ==========================================================================
 * Ionflux Tools
 * Copyright (c) 2004 Joern P. Meier
 * mail@ionflux.org
 * --------------------------------------------------------------------------
 * NodeReference.hpp                    Tree node reference.
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
#include "ionflux/tools.hpp"
#include "ionflux/TreeResolver.hpp"

namespace Ionflux
{

namespace Tools
{

/** Tree node reference.
 * \ingroup datahand
 *
 * A tree node reference specifies a tree node, relative to its parent node, 
 * in human readable form. A tree node reference may be generated from a child 
 * node ID, a node name, or a fully qualified tree path (i.e. a data entry).
 */
class NodeReference
{
	protected:
		/// Value of the reference (either name or ID of the node).
		std::string value;
		/// Reference type.
		int type;
		/// Whether this reference has been generated from a subscript.
		bool subscript;
		
	public:
		/// Reference type: Invalid.
		static const int REF_INVALID;
		/// Reference type: Node name.
		static const int REF_NAME;
		/// Reference type: Node ID.
		static const int REF_ID;
		/// Reference type: Tree path.
		static const int REF_PATH;
		/// Reference type: Empty.
		static const int REF_EMPTY;
		
		/** Constructor.
		 *
		 * Construct new NodeReference object.
		 */
		NodeReference();
		
		/** Constructor.
		 *
		 * Creates a node reference from a reference expression. This may be 
		 * either a child node ID, a node name, or a fully qualified tree path 
		 * (i.e. data entry).
		 *
		 * \param refExpr Reference expression.
		 */
		NodeReference(const std::string &refExpr);
		
		/** Destructor.
		 *
		 * Destruct NodeReference object.
		 */
		virtual ~NodeReference();
		
		/** Initialize from reference.
		 *
		 * Initializes the node reference from a reference expression. This 
		 * may be either a child node ID, a node name, or a fully qualified 
		 * tree path (i.e. data entry).
		 *
		 * Note: This function does not initialize the subscript flag.
		 *
		 * \param refExpr Reference expression.
		 */
		virtual void setFromRef(const std::string &refExpr);
		
		/** Set value.
		 *
		 * Sets the reference value.
		 *
		 * \param newValue Reference value.
		 */
		virtual void setValue(const std::string& newValue);
		
		/** Set type.
		 *
		 * Sets the reference type.
		 *
		 * \param newType Reference type.
		 */
		virtual void setType(int newType);
		
		/** Set subscript flag.
		 *
		 * Sets the subscript flag. This should be set to \c true if this 
		 * reference has been generated from a subscript.
		 *
		 * \param newSubscript Subscript flag.
		 */
		virtual void setSubscript(bool newSubscript);
		
		/** Get value.
		 *
		 * \return Value (name or ID) of the reference.
		 */
		virtual std::string getValue() const;
		
		/** Get type.
		 *
		 * \return Reference type.
		 */
		virtual int getType() const;
		
		/** Get subscript flag.
		 *
		 * \return \c true if the reference is a subscript, \c false otherwise.
		 */
		virtual bool isSubscript() const;
		
		/// Make this an empty (invalid) node reference.
		virtual void clear();
		
		/// Print debug information.
		virtual void printDebugInfo() const;
};

}

}

/** \file NodeReference.hpp
 * \brief Tree node reference header.
 */
#endif
