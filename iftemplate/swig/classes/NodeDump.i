/* ==========================================================================
 * IFTemplate - Ionflux Template Processor
 * Copyright © 2012 Jörn P. Meier
 * mail@ionflux.org
 * --------------------------------------------------------------------------
 * NodeDump.i                      Node dump (interface).
 * =========================================================================

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
%{
#include "iftemplate/NodeDump.hpp"
%}

namespace Ionflux
{

namespace Template
{

class Node;

class NodeDumpClassInfo
: public Ionflux::ObjectBase::IFClassInfo
{
    public:
        NodeDumpClassInfo();
        virtual ~NodeDumpClassInfo();
};

class NodeDump
: virtual public Ionflux::ObjectBase::IFObject
{
    public:
        
        NodeDump();
		NodeDump(const Ionflux::Template::NodeDump& other);
        virtual ~NodeDump();
        virtual void dump(Ionflux::Template::Node* node) = 0;
		static Ionflux::Template::NodeDump* upcast(Ionflux::ObjectBase::IFObject*
		other);
};

}

}
