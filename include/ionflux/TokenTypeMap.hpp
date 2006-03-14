#ifndef IONFLUX_TOOLS_TOKENTYPEMAP
#define IONFLUX_TOOLS_TOKENTYPEMAP
/* ==========================================================================
 * Ionflux Tools
 * Copyright (c) 2004 Joern P. Meier
 * mail@ionflux.org
 * --------------------------------------------------------------------------
 * TokenTypeMap.hpp                    Token type lookup map.
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
#include <iostream>
#include <sstream>
#include <vector>
#include "ionflux/Tokenizer.hpp"

namespace Ionflux
{

namespace Tools
{

struct TokenType;

/** Token type lookup map.
 * \ingroup tokenizer
 *
 * A lookup map for mapping bytes to token types.
 */
class TokenTypeMap
{
	protected:
		/// Token type lookup map.
		TokenType** typeMap;
		/// Token types.
		std::vector<TokenType *> types;
		
	public:
		/// Size of token type lookup map.
		static const unsigned int TYPE_MAP_SIZE;
		
		/** Constructor.
		 *
		 * Construct new TokenTypeMap object.
		 */
		TokenTypeMap();
		
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
		virtual void addTokenType(const TokenType& newTokenType);
		
		/** Remove token type.
		 *
		 * Remove a token type from the map.
		 *
		 * \param removeTokenType Token type to be removed.
		 */
		virtual void removeTokenType(const TokenType& removeTokenType);
		
		/** Get token type.
		 *
		 * Perform a token type lookup for the specified character.
		 *
		 * \param testChar Character to look up.
		 *
		 * \return The token type \c testChar belongs to, or 
		 * Tokenizer::TT_INVALID if \c testChar is not part of any valid 
		 * token.
		 */
		virtual TokenType getTokenType(unsigned char testChar) const;
		
		/** Add special token type 'anything'.
		 *
		 * Add special token type 'anything' to the map. The 'anything' token 
		 * type matches any character that is not matched by another token 
		 * in the current setup.
		 *
		 * \note If you have already added a token type 'anything', calling 
		 * this function again will have no effect. In order to change the 
		 * 'anything' token type, you will either have to remove the one you 
		 * have added previously (by calling removeTokenType()) or clear the 
		 * entire map (by calling clear()).
		 *
		 * \param newTokenType Token type to be added as special type 
		 * 'anything'.
		 */
		virtual void addTokenTypeAnything(const TokenType& newTokenType);
		
		/** Clear map.
		 *
		 * Clears all entries from the token type map.
		 */
		virtual void clear();
		
		/** Get number of token types.
		 *
		 * \return Number of token types in the type map.
		 */
		virtual unsigned int getNumTokenTypes() const;
};

/** Character type lookup map.
 * \ingroup tokenizer
 *
 * A lookup map for mapping bytes to character types.
 */
class CharTypeMap
: public TokenTypeMap
{
	protected:
		
	public:
		/** Constructor.
		 *
		 * Construct new TokenTypeMap object.
		 */
		CharTypeMap();
		
		/** Destructor.
		 *
		 * Destruct TokenTypeMap object.
		 */
		virtual ~CharTypeMap();
};

}

}

/** \file TokenTypeMap.hpp
 * \brief Token type lookup map header.
 */
#endif
