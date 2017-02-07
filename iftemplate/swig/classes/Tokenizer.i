/* ==========================================================================
 * IFTemplate - Ionflux Template Processor
 * Copyright © 2012 Jörn P. Meier
 * mail@ionflux.org
 * --------------------------------------------------------------------------
 * Tokenizer.i                     Tokenizer (interface).
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
#include "iftemplate/Tokenizer.hpp"
%}

namespace Ionflux
{

namespace Template
{

class TokenTypeMap;

class TokenizerClassInfo
: public Ionflux::ObjectBase::IFClassInfo
{
    public:
        TokenizerClassInfo();
        virtual ~TokenizerClassInfo();
};

class Tokenizer
: public Ionflux::ObjectBase::IFObject
{
    public:
        Ionflux::Template::TokenType TT_ANYTHING;
        
        Tokenizer();
		Tokenizer(const Ionflux::Template::Tokenizer& other);
        Tokenizer(const std::string& initInput);
        Tokenizer(const Ionflux::Template::TokenTypeVector& 
        initTokenTypes);
        Tokenizer(const Ionflux::Template::TokenTypeVector& initTokenTypes,
        const std::string& initInput);
        virtual ~Tokenizer();
        virtual void clearTokenTypes();
        virtual void useDefaultTokenTypes();
        virtual void setTokenTypes(const 
        Ionflux::Template::TokenTypeVector& newTokenTypes);
        virtual void addTokenType(const Ionflux::Template::TokenType& 
        newTokenType);
        virtual void addTokenTypes(const 
        Ionflux::Template::TokenTypeVector& newTokenTypes);
        virtual void setInput(const std::string& newInput);
        virtual Ionflux::Template::Token getNextToken(const 
        Ionflux::Template::TokenTypeMap& otherMap);
        virtual Ionflux::Template::Token getNextToken();
        virtual Ionflux::Template::Token getCurrentToken();
        virtual Ionflux::Template::TokenTypeID getCurrentTokenType();
        virtual void reset();
        virtual void setTokenTypeAnything();
        virtual void setExtractQuoted(bool newExtractQuoted);
        virtual void setExtractEscaped(bool newExtractEscaped);
        virtual unsigned int getCurrentPos();
        virtual unsigned int getCurrentTokenPos();
        virtual char getQuoteChar();
        virtual std::string getString() const;
		virtual Ionflux::Template::Tokenizer* copy() const;
		static Ionflux::Template::Tokenizer* 
		upcast(Ionflux::ObjectBase::IFObject* other);
		static Ionflux::Template::Tokenizer* 
		create(Ionflux::ObjectBase::IFObject* parentObject = 0);
		virtual unsigned int getMemSize() const;
        virtual void setTypeMap(Ionflux::Template::TokenTypeMap* 
        newTypeMap);
        virtual Ionflux::Template::TokenTypeMap* getTypeMap() const;
};

}

}
