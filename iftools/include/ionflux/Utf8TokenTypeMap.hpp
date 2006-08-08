#ifndef IONFLUX_TOOLS_UTF8TOKENTYPEMAP
#define IONFLUX_TOOLS_UTF8TOKENTYPEMAP
/* ==========================================================================
 * Ionflux Tools
 * Copyright (c) 2005 Joern P. Meier
 * mail@ionflux.org
 * --------------------------------------------------------------------------
 * Utf8TokenTypeMap.hpp              Token type map with UTF-8 support.
 * ==========================================================================
 * 
 * This file is part of Ionflux Tools.
 * 
 * Ionflux Tools is free software; you can redistribute it and/or modify it
 * under the terms of the GNU General Public License as published by the 
 * Free Software Foundation; either version 2 of the License, or (at your 
 * option) any later version.
 * 
 * Ionflux Tools is distributed in the hope that it will be useful, but 
 * WITHOUT ANY WARRANTY; without even the implied warranty of 
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU 
 * General Public License for more details.
 * 
 * You should have received a copy of the GNU General Public License along 
 * with Ionflux Tools; if not, write to the Free Software Foundation, Inc.,
 * 59 Temple Place, Suite 330, Boston, MA 02111-1307 USA
 * 
 * ========================================================================== */

#include <string>
#include <vector>
#include <map>
#include "ionflux/ManagedObject.hpp"

namespace Ionflux
{

namespace Tools
{

struct Utf8TokenType;

typedef std::map<unsigned int, Ionflux::Tools::Utf8TokenType*> ImplTokenTypeMap;

/** A token type with UTF-8 support.
 * \ingroup tokenizer
 */
struct Utf8TokenType
{
	/// Numeric token type ID.
	int typeID;
	/// UTF-8 encoded sequence of valid characters.
	std::string validChars;
	/// Maximum number of characters (use 0 for unlimited).
	unsigned int maxChars;
	/// First free token type ID for user types.
	static const int USERTYPE_ID;
	/// Type ID for invalid tokens.
	static const int INVALID_ID;
	/// Type ID for empty tokens.
	static const int EMPTY_ID;
};

/// Class information for class Utf8TokenTypeMap.
class Utf8TokenTypeMapClassInfo
: public Ionflux::Tools::ClassInfo
{
	public:
		/// Constructor.
		Utf8TokenTypeMapClassInfo();
		/// Destructor.
		virtual ~Utf8TokenTypeMapClassInfo() { };
};

/** Token type map with UTF-8 support.
 * \ingroup tokenizer
 *
 * A lookup map for mapping Unicode characters to token types.
 */
class Utf8TokenTypeMap
: public Ionflux::Tools::ManagedObject
{
	private:
		
	protected:
		/// Token types.
		std::vector<Utf8TokenType*> tokenTypes;
		/// The actual token type map.
		ImplTokenTypeMap typeMap;
		/// The default token type.
		Utf8TokenType* defaultTokenType;
		
	public:
		/// Class information instance.
		static const Utf8TokenTypeMapClassInfo utf8TokenTypeMapClassInfo;
		/// Class information.
		static const Ionflux::Tools::ClassInfo* CLASS_INFO;
		
		/** Constructor.
		 *
		 * Construct new Utf8TokenTypeMap object.
		 */
		Utf8TokenTypeMap();
		
		/** Destructor.
		 *
		 * Destruct Utf8TokenTypeMap object.
		 */
		virtual ~Utf8TokenTypeMap();
		
		/** Clear token type map.
		 *
		 * Remove all token types from the map.
		 */
		virtual void clear();
		
		/** Get number of token types.
		 *
		 * Get the number of token types in the map.
		 *
		 * \return Number of token types.
		 */
		virtual unsigned int getNumTokenTypes();
		
		/** Add token type.
		 *
		 * Add a token type to the map
		 *
		 * \param newTokenType Token type to be added.
		 */
		virtual void addTokenType(const Utf8TokenType& newTokenType);
		
		/** Remove token type.
		 *
		 * Remove a token type from the map
		 *
		 * \param removeTokenType Token type to be removed.
		 */
		virtual void removeTokenType(const Utf8TokenType& removeTokenType);
		
		/** Set default token type.
		 *
		 * Set the token type to be returned if a character does not match any
		 * token type in the map.
		 *
		 * \param newDefaultTokenType Default token type.
		 */
		virtual void setDefaultTokenType(const Utf8TokenType& 
		newDefaultTokenType);
		
		/** Get token type.
		 *
		 * Perform a token type lookup for the specified character.
		 *
		 * \param testChar Unicode character.
		 *
		 * \return Token type.
		 */
		virtual Utf8TokenType getTokenType(unsigned int testChar);
		
		/** Validate token type.
		 *
		 * Check whether the specified token type represents a valid token 
		 * (i.e. it is not invalid or empty).
		 *
		 * \param checkTokenType Token type to be checked.
		 *
		 * \return \c true if the specified token type is valid, \c false 
		 * otherwise.
		 */
		static bool isValid(const Utf8TokenType& checkTokenType);
};

}

}

/** \file Utf8TokenTypeMap.hpp
 * \brief Token type map with UTF-8 support header.
 */
#endif
