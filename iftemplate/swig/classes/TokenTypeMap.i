/* ==========================================================================
 * IFTemplate - Ionflux Template Processor
 * Copyright © 2012 Jörn P. Meier
 * mail@ionflux.org
 * --------------------------------------------------------------------------
 * TokenTypeMap.i                  Token type lookup map (interface).
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
#include "iftemplate/TokenTypeMap.hpp"
%}

namespace Ionflux
{

namespace Template
{

class TokenTypeMapClassInfo
: public Ionflux::ObjectBase::IFClassInfo
{
    public:
        TokenTypeMapClassInfo();
        virtual ~TokenTypeMapClassInfo();
};

class TokenTypeMap
: public Ionflux::ObjectBase::IFObject
{
    public:
		static const unsigned int TYPE_MAP_SIZE;
        
        TokenTypeMap();
		TokenTypeMap(const Ionflux::Template::TokenTypeMap& other);
        virtual ~TokenTypeMap();
        virtual void addTokenType(const Ionflux::Template::TokenType& 
        newTokenType);
        virtual void removeTokenType(const Ionflux::Template::TokenType& 
        removeTokenType);
        virtual Ionflux::Template::TokenType getTokenType(unsigned char 
        testChar) const;
        virtual void addTokenTypeAnything(const 
        Ionflux::Template::TokenType& newTokenType);
        virtual void clear();
        virtual unsigned int getNumTokenTypes() const;
        virtual std::string getString() const;
		virtual Ionflux::Template::TokenTypeMap* copy() const;
		static Ionflux::Template::TokenTypeMap* 
		upcast(Ionflux::ObjectBase::IFObject* other);
		static Ionflux::Template::TokenTypeMap* 
		create(Ionflux::ObjectBase::IFObject* parentObject = 0);
};

}

}
