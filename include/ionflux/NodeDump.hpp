#ifndef IONFLUX_TOOLS_NODEDUMP
#define IONFLUX_TOOLS_NODEDUMP
/* ==========================================================================
 * Ionflux Tools
 * Copyright (c) 2004 Joern P. Meier
 * mail@ionflux.org
 * --------------------------------------------------------------------------
 * NodeDump.hpp                 Tree node dump (abstract class)
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

namespace Ionflux
{

namespace Tools
{

class Node;

/** Node dump.
 * \ingroup datahand
 *
 * Abstract base class for anything that can receive tree nodes.
 *
 */
class NodeDump
{
	public:
		/** Destructor.
		 *
		 * Destruct NodeDump object.
		 */
		virtual ~NodeDump() { };
		
		/** Dump node.
		 *
		 * Pass a node to the object for handling.
		 *
		 * \param node The node to be dumped.
		 */
		virtual void dump(Node *node) = 0;
};

}

}

/** \file NodeDump.hpp
 * \brief Node dump (abstract class) header.
 */
#endif
