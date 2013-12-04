/* ==========================================================================
 * IFTemplate - Ionflux Template Processor
 * Copyright © 2012 Jörn P. Meier
 * mail@ionflux.org
 * --------------------------------------------------------------------------
 * NodeReference.i                 Node reference (interface).
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
#include "iftemplate/NodeReference.hpp"
%}

namespace Ionflux
{

namespace Template
{

class NodeReferenceClassInfo
: public Ionflux::ObjectBase::IFClassInfo
{
    public:
        NodeReferenceClassInfo();
        virtual ~NodeReferenceClassInfo();
};

class NodeReference
: public Ionflux::ObjectBase::IFObject
{
    public:
		static const Ionflux::Template::NodeRefTypeID TYPE_INVALID;
		static const Ionflux::Template::NodeRefTypeID TYPE_NAME;
		static const Ionflux::Template::NodeRefTypeID TYPE_ID;
		static const Ionflux::Template::NodeRefTypeID TYPE_PATH;
		static const Ionflux::Template::NodeRefTypeID TYPE_EMPTY;
        
        NodeReference();
		NodeReference(const Ionflux::Template::NodeReference& other);
        NodeReference(const std::string& refExpr);
        virtual ~NodeReference();
        virtual void clear();
        virtual void setFromRef(const std::string& refExpr);
        virtual bool isSubscript() const;
        virtual std::string getValueString() const;
        virtual void printDebugInfo() const;
		virtual Ionflux::Template::NodeReference* copy() const;
		static Ionflux::Template::NodeReference* 
		upcast(Ionflux::ObjectBase::IFObject* other);
		static Ionflux::Template::NodeReference* 
		create(Ionflux::ObjectBase::IFObject* parentObject = 0);
        virtual void setValue(const std::string& newValue);
        virtual std::string getValue() const;
        virtual void setType(Ionflux::Template::NodeRefTypeID newType);
        virtual Ionflux::Template::NodeRefTypeID getType() const;
        virtual void setSubscript(bool newSubscript);
        virtual bool getSubscript() const;
};

}

}
