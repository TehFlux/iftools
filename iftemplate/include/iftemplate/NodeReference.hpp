#ifndef IONFLUX_TEMPLATE_NODEREFERENCE
#define IONFLUX_TEMPLATE_NODEREFERENCE
/* ==========================================================================
 * IFTemplate - Ionflux Template Processor
 * Copyright © 2012 Jörn P. Meier
 * mail@ionflux.org
 * --------------------------------------------------------------------------
 * NodeReference.hpp               Node reference (header).
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
#include "ifobject/IFObject.hpp"

namespace Ionflux
{

namespace Template
{

/// Class information for class NodeReference.
class NodeReferenceClassInfo
: public Ionflux::ObjectBase::IFClassInfo
{
	public:
		/// Constructor.
		NodeReferenceClassInfo();
		/// Destructor.
		virtual ~NodeReferenceClassInfo();
};

/** Node reference.
 * \ingroup iftemplate
 *
 * A node reference specifies a tree node, relative to its parent node, in 
 * human readable form. A tree node reference may be generated from a child
 * node ID, a node name, or a fully qualified tree path (i.e. a data 
 * entry).
 */
class NodeReference
: public Ionflux::ObjectBase::IFObject
{
	private:
		
	protected:
		/// Value.
		std::string value;
		/// Type.
		Ionflux::Template::NodeRefTypeID type;
		/// Subscript flag.
		bool subscript;
		
	public:
		/// Reference type: invalid.
		static const Ionflux::Template::NodeRefTypeID TYPE_INVALID;
		/// Reference type: name.
		static const Ionflux::Template::NodeRefTypeID TYPE_NAME;
		/// Reference type: ID.
		static const Ionflux::Template::NodeRefTypeID TYPE_ID;
		/// Reference type: path.
		static const Ionflux::Template::NodeRefTypeID TYPE_PATH;
		/// Reference type: empty.
		static const Ionflux::Template::NodeRefTypeID TYPE_EMPTY;
		/// Class information instance.
		static const NodeReferenceClassInfo nodeReferenceClassInfo;
		/// Class information.
		static const Ionflux::ObjectBase::IFClassInfo* CLASS_INFO;
		
		/** Constructor.
		 *
		 * Construct new NodeReference object.
		 */
		NodeReference();
		
		/** Constructor.
		 *
		 * Construct new NodeReference object.
		 *
		 * \param other Other object.
		 */
		NodeReference(const Ionflux::Template::NodeReference& other);
		
		/** Constructor.
		 *
		 * Construct new NodeReference object.
		 *
		 * \param refExpr reference expression.
		 */
		NodeReference(const std::string& refExpr);
		
		/** Destructor.
		 *
		 * Destruct NodeReference object.
		 */
		virtual ~NodeReference();
		
		/** Clear.
		 *
		 * Clear the reference data.
		 */
		virtual void clear();
		
		/** Initialize from reference.
		 *
		 * Initializes the node reference from a reference expression. This 
		 * may be either a child node ID, a node name, or a fully qualified 
		 * tree path (i.e. data entry).
		 * 
		 * \note This function does not initialize the subscript flag.
		 *
		 * \param refExpr reference expression.
		 */
		virtual void setFromRef(const std::string& refExpr);
		
		/** Get subscript flag.
		 *
		 * Get the subscript flag.
		 *
		 * \return \c true if the reference is a subscript, \c false otherwise.
		 */
		virtual bool isSubscript() const;
		
		/** Get string representation of value.
		 *
		 * Get a string representation of the value of the object.
		 *
		 * \return String representation.
		 */
		virtual std::string getValueString() const;
		
		/** Print debug information.
		 *
		 * Prints debug information for the node reference.
		 */
		virtual void printDebugInfo() const;
		
		/** Assignment operator.
		 *
		 * Assign an object.
		 *
		 * \param other Other object.
		 *
		 * \return The object itself.
		 */
		virtual Ionflux::Template::NodeReference& operator=(const 
		Ionflux::Template::NodeReference& other);
		
		/** Copy.
		 *
		 * Create a copy of the object.
		 *
		 * \return Newly allocated copy of the object.
		 */
		virtual Ionflux::Template::NodeReference* copy() const;
		
		/** Upcast.
		 *
		 * Cast an IFObject to the most specific type.
		 *
		 * \param other Other object.
		 *
		 * \return The more specific object, or 0 if the cast failed.
		 */
		static Ionflux::Template::NodeReference* 
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
		static Ionflux::Template::NodeReference* 
		create(Ionflux::ObjectBase::IFObject* parentObject = 0);
		
		/** Get value.
		 *
		 * \return Current value of value.
		 */
		virtual std::string getValue() const;
		
		/** Set value.
		 *
		 * Set new value of value.
		 *
		 * \param newValue New value of value.
		 */
		virtual void setValue(const std::string& newValue);
		
		/** Get type.
		 *
		 * \return Current value of type.
		 */
		virtual Ionflux::Template::NodeRefTypeID getType() const;
		
		/** Set type.
		 *
		 * Set new value of type.
		 *
		 * \param newType New value of type.
		 */
		virtual void setType(Ionflux::Template::NodeRefTypeID newType);
		
		/** Get subscript flag.
		 *
		 * \return Current value of subscript flag.
		 */
		virtual bool getSubscript() const;
		
		/** Set subscript flag.
		 *
		 * Set new value of subscript flag.
		 *
		 * \param newSubscript New value of subscript flag.
		 */
		virtual void setSubscript(bool newSubscript);
};

}

}

/** \file NodeReference.hpp
 * \brief Node reference (header).
 */
#endif
