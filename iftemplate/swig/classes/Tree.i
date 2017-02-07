/* ==========================================================================
 * IFTemplate - Ionflux Template Processor
 * Copyright © 2012 Jörn P. Meier
 * mail@ionflux.org
 * --------------------------------------------------------------------------
 * Tree.i                          Tree (interface).
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
#include "iftemplate/Tree.hpp"
%}

namespace Ionflux
{

namespace Template
{

class Node;

class TreeClassInfo
: public Ionflux::ObjectBase::IFClassInfo
{
    public:
        TreeClassInfo();
        virtual ~TreeClassInfo();
};

class Tree
: virtual public Ionflux::ObjectBase::IFObject
{
    public:
        
        Tree();
		Tree(const Ionflux::Template::Tree& other);
        Tree(Ionflux::Template::Node* initRoot0);
        virtual ~Tree();
        virtual void initRoot();
        virtual void clear();
        virtual unsigned int getNumNodes();
        virtual Ionflux::Template::Node* findNode(int nodeID);
        virtual Ionflux::Template::Node* findNode(const std::string& 
        nodeName);
        virtual Ionflux::Template::DataEntry resolve(const std::string& 
        treePathExpr, bool createPath = false, bool nodesOnly = false);
        virtual bool eval(const std::string& treeExpr, 
        Ionflux::Template::Node& result, bool createPath);
        virtual void writeToFile(const std::string& fileName);
        virtual void readFromFile(const std::string& fileName);
        virtual void printDebugInfo();
		virtual Ionflux::Template::Tree* copy() const;
		static Ionflux::Template::Tree* upcast(Ionflux::ObjectBase::IFObject* 
		other);
		static Ionflux::Template::Tree* create(Ionflux::ObjectBase::IFObject* 
		parentObject = 0);
		virtual unsigned int getMemSize() const;
        virtual void setRoot(Ionflux::Template::Node* newRoot);
        virtual Ionflux::Template::Node* getRoot() const;
};

}

}
