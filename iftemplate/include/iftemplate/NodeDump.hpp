#ifndef IONFLUX_TEMPLATE_NODEDUMP
#define IONFLUX_TEMPLATE_NODEDUMP
/* ==========================================================================
 * IFTemplate - Ionflux Template Processor
 * Copyright © 2012 Jörn P. Meier
 * mail@ionflux.org
 * --------------------------------------------------------------------------
 * NodeDump.hpp                    Node dump (header).
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

#include "ifobject/IFObject.hpp"

namespace Ionflux
{

namespace Template
{

class Node;

/// Class information for class NodeDump.
class NodeDumpClassInfo
: public Ionflux::ObjectBase::IFClassInfo
{
	public:
		/// Constructor.
		NodeDumpClassInfo();
		/// Destructor.
		virtual ~NodeDumpClassInfo();
};

/** Node dump.
 * \ingroup iftemplate
 *
 * Abstract base class for anything that can process tree nodes.
 */
class NodeDump
: virtual public Ionflux::ObjectBase::IFObject
{
	private:
		
	protected:
		
	public:
		/// Class information instance.
		static const NodeDumpClassInfo nodeDumpClassInfo;
		/// Class information.
		static const Ionflux::ObjectBase::IFClassInfo* CLASS_INFO;
		
		/** Constructor.
		 *
		 * Construct new NodeDump object.
		 */
		NodeDump();
		
		/** Constructor.
		 *
		 * Construct new NodeDump object.
		 *
		 * \param other Other object.
		 */
		NodeDump(const Ionflux::Template::NodeDump& other);
		
		/** Destructor.
		 *
		 * Destruct NodeDump object.
		 */
		virtual ~NodeDump();
		
		/** Dump node.
		 *
		 * Pass a node to the object for processing.
		 *
		 * \param node node to be processed.
		 */
		virtual void dump(Ionflux::Template::Node* node) = 0;
		
		/** Assignment operator.
		 *
		 * Assign an object.
		 *
		 * \param other Other object.
		 *
		 * \return The object itself.
		 */
		virtual Ionflux::Template::NodeDump& operator=(const 
		Ionflux::Template::NodeDump& other);
		
		/** Upcast.
		 *
		 * Cast an IFObject to the most specific type.
		 *
		 * \param other Other object.
		 *
		 * \return The more specific object, or 0 if the cast failed.
		 */
		static Ionflux::Template::NodeDump* upcast(Ionflux::ObjectBase::IFObject*
		other);
};

}

}

/** \file NodeDump.hpp
 * \brief Node dump (header).
 */
#endif
