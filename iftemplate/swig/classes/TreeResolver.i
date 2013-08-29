/* ==========================================================================
 * IFTemplate - Ionflux Template Processor
 * Copyright © 2012 Jörn P. Meier
 * mail@ionflux.org
 * --------------------------------------------------------------------------
 * TreeResolver.i                  Node reference (interface).
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
%{
#include "iftemplate/TreeResolver.hpp"
%}

namespace Ionflux
{

namespace Template
{

class Tree;

class TreeResolverClassInfo
: public Ionflux::ObjectBase::IFClassInfo
{
    public:
        TreeResolverClassInfo();
        virtual ~TreeResolverClassInfo();
};

class TreeResolver
: public Ionflux::ObjectBase::IFObject
{
    public:
		static const Ionflux::Template::TokenType TT_RES_OPERATOR;
		static const Ionflux::Template::TokenType TT_SUB_LEFT;
		static const Ionflux::Template::TokenType TT_SUB_RIGHT;
		static const Ionflux::Template::TokenType TT_RES_PAR_LEFT;
		static const Ionflux::Template::TokenType TT_RES_PAR_RIGHT;
        
        TreeResolver();
		TreeResolver(const Ionflux::Template::TreeResolver& other);
        virtual ~TreeResolver();
        static bool parseTreePath(const std::string& treePathExpr, 
        Ionflux::Template::NodeRefVector& nodeRefs);
        static bool createTreePath(Ionflux::Template::Tree* tree, 
        Ionflux::Template::NodeRefVector& nodeRefs, 
        Ionflux::Template::TreePath& treePath, bool createPath, bool 
        nodesOnly = false);
		virtual Ionflux::Template::TreeResolver* copy() const;
		static Ionflux::Template::TreeResolver* 
		upcast(Ionflux::ObjectBase::IFObject* other);
		static Ionflux::Template::TreeResolver* 
		create(Ionflux::ObjectBase::IFObject* parentObject = 0);
};

}

}
