/* ==========================================================================
 * IFTemplate - Ionflux Template Processor
 * Copyright © 2012 Jörn P. Meier
 * mail@ionflux.org
 * --------------------------------------------------------------------------
 * TreeEval.i                      Tree expression evaluator (interface).
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
#include "iftemplate/TreeEval.hpp"
%}

namespace Ionflux
{

namespace Template
{

class Tree;
class Node;

class TreeEvalClassInfo
: public Ionflux::ObjectBase::IFClassInfo
{
    public:
        TreeEvalClassInfo();
        virtual ~TreeEvalClassInfo();
};

class TreeEval
: public Ionflux::ObjectBase::IFObject
{
    public:
		static const Ionflux::Template::TokenType TT_OPERATOR;
		static const Ionflux::Template::TokenType TT_TREEPATH_NP;
		static const Ionflux::Template::TokenType TT_PAR_LEFT;
		static const Ionflux::Template::TokenType TT_PAR_RIGHT;
        
        TreeEval();
		TreeEval(const Ionflux::Template::TreeEval& other);
        virtual ~TreeEval();
        static bool parseTreeExpr(const std::string& treeExpr, 
        Ionflux::Template::TreeExprElementVector& elements);
        static bool eval(Ionflux::Template::Tree* tree, 
        Ionflux::Template::TreeExprElementVector& elements, 
        Ionflux::Template::Node& result, bool createPath);
		virtual Ionflux::Template::TreeEval* copy() const;
		static Ionflux::Template::TreeEval* upcast(Ionflux::ObjectBase::IFObject*
		other);
		static Ionflux::Template::TreeEval* create(Ionflux::ObjectBase::IFObject*
		parentObject = 0);
};

}

}
