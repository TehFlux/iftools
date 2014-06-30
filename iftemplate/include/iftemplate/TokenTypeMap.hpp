#ifndef IONFLUX_TEMPLATE_TOKENTYPEMAP
#define IONFLUX_TEMPLATE_TOKENTYPEMAP
/* ==========================================================================
 * IFTemplate - Ionflux Template Processor
 * Copyright © 2012 Jörn P. Meier
 * mail@ionflux.org
 * --------------------------------------------------------------------------
 * TokenTypeMap.hpp                Token type lookup map (header).
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

#include "iftemplate/types.hpp"
#include "ifobject/IFObject.hpp"

namespace Ionflux
{

namespace Template
{

/// Class information for class TokenTypeMap.
class TokenTypeMapClassInfo
: public Ionflux::ObjectBase::IFClassInfo
{
	public:
		/// Constructor.
		TokenTypeMapClassInfo();
		/// Destructor.
		virtual ~TokenTypeMapClassInfo();
};

/** Token type lookup map.
 * \ingroup iftemplate
 *
 * A lookup map for mapping bytes to token types.
 */
class TokenTypeMap
: public Ionflux::ObjectBase::IFObject
{
	private:
		
	protected:
		/// Token type lookup map.
		Ionflux::Template::TokenType** typeMap;
		/// Token types.
		Ionflux::Template::TokenTypePtrVector types;
		
	public:
		/// Size of token type lookup map.
		static const unsigned int TYPE_MAP_SIZE;
		/// Class information instance.
		static const TokenTypeMapClassInfo tokenTypeMapClassInfo;
		/// Class information.
		static const Ionflux::ObjectBase::IFClassInfo* CLASS_INFO;
		
		/** Constructor.
		 *
		 * Construct new TokenTypeMap object.
		 */
		TokenTypeMap();
		
		/** Constructor.
		 *
		 * Construct new TokenTypeMap object.
		 *
		 * \param other Other object.
		 */
		TokenTypeMap(const Ionflux::Template::TokenTypeMap& other);
		
		/** Destructor.
		 *
		 * Destruct TokenTypeMap object.
		 */
		virtual ~TokenTypeMap();
		
		/** Add token type.
		 *
		 * Add a token type to the map.
		 *
		 * \param newTokenType Token type to be added.
		 */
		virtual void addTokenType(const Ionflux::Template::TokenType& 
		newTokenType);
		
		/** Remove token type.
		 *
		 * Remove a token type from the map.
		 *
		 * \param removeTokenType Token type to be removed.
		 */
		virtual void removeTokenType(const Ionflux::Template::TokenType& 
		removeTokenType);
		
		/** Get token type.
		 *
		 * Perform a token type lookup for the specified character.
		 *
		 * \param testChar Character to look up.
		 *
		 * \return The token type \c testChar belongs to, or TT_INVALID if \c 
		 * testChar is not part of any valid token..
		 */
		virtual Ionflux::Template::TokenType getTokenType(unsigned char testChar)
		const;
		
		/** Add special token type 'anything'.
		 *
		 * Add special token type 'anything' to the map. The 'anything' token 
		 * type matches any character that is not matched by another token in 
		 * the current setup.
		 * 
		 * \note If you have already added a token type 'anything', calling 
		 * this function again will have no effect. In order to change the 
		 * 'anything' token type, you will either have to remove the one you 
		 * have added previously (by calling removeTokenType()) or clear the 
		 * entire map (by calling clear()).
		 *
		 * \param newTokenType Token type to be added as special type 
		 * 'anything'..
		 */
		virtual void addTokenTypeAnything(const Ionflux::Template::TokenType& 
		newTokenType);
		
		/** Clear map.
		 *
		 * Clears all entries from the token type map.
		 */
		virtual void clear();
		
		/** Get number of token types.
		 *
		 * Get number of token types in the type map.
		 *
		 * \return Number of token types in the type map.
		 */
		virtual unsigned int getNumTokenTypes() const;
		
		/** Get string representation.
		 *
		 * Get a string representation of the object.
		 *
		 * \return String representation.
		 */
		virtual std::string getString() const;
		
		/** Assignment operator.
		 *
		 * Assign an object.
		 *
		 * \param other Other object.
		 *
		 * \return The object itself.
		 */
		virtual Ionflux::Template::TokenTypeMap& operator=(const 
		Ionflux::Template::TokenTypeMap& other);
		
		/** Copy.
		 *
		 * Create a copy of the object.
		 *
		 * \return Newly allocated copy of the object.
		 */
		virtual Ionflux::Template::TokenTypeMap* copy() const;
		
		/** Upcast.
		 *
		 * Cast an IFObject to the most specific type.
		 *
		 * \param other Other object.
		 *
		 * \return The more specific object, or 0 if the cast failed.
		 */
		static Ionflux::Template::TokenTypeMap* 
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
		static Ionflux::Template::TokenTypeMap* 
		create(Ionflux::ObjectBase::IFObject* parentObject = 0);
		
		/** Get allocated size in memory.
		 *
		 * Get the allocated size in memory for the object.
		 *
		 * \return The more specific object, or 0 if the cast failed.
		 */
		virtual unsigned int getMemSize() const;
};

}

}

/** \file TokenTypeMap.hpp
 * \brief Token type lookup map (header).
 */
#endif
