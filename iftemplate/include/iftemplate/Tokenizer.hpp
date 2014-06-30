#ifndef IONFLUX_TEMPLATE_TOKENIZER
#define IONFLUX_TEMPLATE_TOKENIZER
/* ==========================================================================
 * IFTemplate - Ionflux Template Processor
 * Copyright © 2012 Jörn P. Meier
 * mail@ionflux.org
 * --------------------------------------------------------------------------
 * Tokenizer.hpp                   Tokenizer (header).
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

class TokenTypeMap;

/// Class information for class Tokenizer.
class TokenizerClassInfo
: public Ionflux::ObjectBase::IFClassInfo
{
	public:
		/// Constructor.
		TokenizerClassInfo();
		/// Destructor.
		virtual ~TokenizerClassInfo();
};

/** Tokenizer.
 * \ingroup iftemplate
 *
 * A generic tokenizer for parsing byte strings. To set up a tokenizer, 
 * first create a Tokenizer object. This will be set up using the default 
 * token  types TT_WHITESPACE, TT_LINETERM and  TT_IDENTIFIER. You may then
 * add your own custom token types and  optionally set up the TT_ANYTHING 
 * token type (which will match  anything not matched by previously defined
 * token types). To enable  extraction of quoted strings and escaped 
 * characters, call  Tokenizer::setExtractQuoted() with \c true as an 
 * argument.\n To get a token from the token stream, call 
 * Tokenizer::getNextToken(). Make  sure your code handles the TT_NONE and 
 * TT_INVALID  special token types (which cannot be disabled). 
 * Tokenizer::getNextToken()  will always return TT_NONE at the end of the 
 * token stream and  TT_INVALID if an invalid token is encountered.
 */
class Tokenizer
: public Ionflux::ObjectBase::IFObject
{
	private:
		
	protected:
		/// The input string to be parsed.
		std::string theInput;
		/// Current token.
		Ionflux::Template::Token currentToken;
		/// Extract quoted strings flag.
		bool extractQuoted;
		/// Extract escaped characters flag.
		bool extractEscaped;
		/// Current parsing position in the input string.
		unsigned int currentPos;
		/// Position of current token in the input string.
		unsigned int currentTokenPos;
		/// Quote character.
		char currentQuoteChar;
		/// Token type map.
		Ionflux::Template::TokenTypeMap* typeMap;
		
	public:
		/// Token type: Anything (special).
		Ionflux::Template::TokenType TT_ANYTHING;
		/// Class information instance.
		static const TokenizerClassInfo tokenizerClassInfo;
		/// Class information.
		static const Ionflux::ObjectBase::IFClassInfo* CLASS_INFO;
		
		/** Constructor.
		 *
		 * Construct new Tokenizer object.
		 */
		Tokenizer();
		
		/** Constructor.
		 *
		 * Construct new Tokenizer object.
		 *
		 * \param other Other object.
		 */
		Tokenizer(const Ionflux::Template::Tokenizer& other);
		
		/** Constructor.
		 *
		 * Construct new Tokenizer object.
		 *
		 * \param initInput input string to be parsed.
		 */
		Tokenizer(const std::string& initInput);
		
		/** Constructor.
		 *
		 * Construct new Tokenizer object.
		 *
		 * \param initTokenTypes token types to be recognized by the tokenizer.
		 */
		Tokenizer(const Ionflux::Template::TokenTypeVector& initTokenTypes);
		
		/** Constructor.
		 *
		 * Construct new Tokenizer object.
		 *
		 * \param initTokenTypes token types to be recognized by the tokenizer.
		 * \param initInput input string to be parsed.
		 */
		Tokenizer(const Ionflux::Template::TokenTypeVector& initTokenTypes, const
		std::string& initInput);
		
		/** Destructor.
		 *
		 * Destruct Tokenizer object.
		 */
		virtual ~Tokenizer();
		
		/** Clear token types.
		 *
		 * Removes all token types from the set of recognized token types.
		 * 
		 * \note Special token types will still be available to the tokenizer.
		 * You can always restore the default set of token types with 
		 * useDefaultTokenTypes().
		 * 
		 * \sa useDefaultTokenTypes()
		 */
		virtual void clearTokenTypes();
		
		/** Use default token types.
		 *
		 * Initializes the set of recognized token types with the default 
		 * token types.
		 */
		virtual void useDefaultTokenTypes();
		
		/** Set token types.
		 *
		 * Set the set of token types recognized by this tokenizer.
		 * 
		 * \note The special token types are always available, regardless of 
		 * whether they are added or not.
		 *
		 * \param newTokenTypes token types to be recognized by the tokenizer.
		 */
		virtual void setTokenTypes(const Ionflux::Template::TokenTypeVector& 
		newTokenTypes);
		
		/** Add a token type.
		 *
		 * Adds a token type (possibly user defined) to the set of token types
		 * recognized by this tokenizer.
		 *
		 * \param newTokenType token type to be added.
		 */
		virtual void addTokenType(const Ionflux::Template::TokenType& 
		newTokenType);
		
		/** Add token types.
		 *
		 * Adds token types (possibly user defined) to the set of token types 
		 * recognized by the tokenizer.
		 *
		 * \param newTokenTypes token types to be recognized by the tokenizer.
		 */
		virtual void addTokenTypes(const Ionflux::Template::TokenTypeVector& 
		newTokenTypes);
		
		/** Set input.
		 *
		 * Sets the input string to be parsed.
		 *
		 * \param newInput input string to be parsed.
		 */
		virtual void setInput(const std::string& newInput);
		
		/** Get next token.
		 *
		 * Parse the input string and get the next token.
		 *
		 * \param otherMap token type map to be used for extracting the next 
		 * token.
		 *
		 * \return the next token from the current input.
		 */
		virtual Ionflux::Template::Token getNextToken(const 
		Ionflux::Template::TokenTypeMap& otherMap);
		
		/** Get next token.
		 *
		 * Parse the input string and get the next token.
		 *
		 * \return the next token from the current input.
		 */
		virtual Ionflux::Template::Token getNextToken();
		
		/** Get current token.
		 *
		 * Get the current token.
		 *
		 * \return the current token.
		 */
		virtual Ionflux::Template::Token getCurrentToken();
		
		/** Get type of current token.
		 *
		 * Get the type of the current token.
		 *
		 * \return the type of the current token.
		 */
		virtual Ionflux::Template::TokenTypeID getCurrentTokenType();
		
		/** Reset the parser.
		 *
		 * Reset the parser so the input can be parsed again from the 
		 * beginning.
		 */
		virtual void reset();
		
		/** Set special token type TT_ANYTHING.
		 *
		 * This sets up a special token type TT_ANYTHING that will match any 
		 * characters not matched by any of the previously defined token 
		 * types.
		 * 
		 * \note You may call this again to update TT_ANYTHING if you add 
		 * further token types after a call to setTokenTypeAnything().
		 */
		virtual void setTokenTypeAnything();
		
		/** Set quoted string extraction flag.
		 *
		 * Pass \c true to this function to enable extraction of quoted 
		 * strings (and escaped characters), or disable this feature by 
		 * passing \c false.
		 * 
		 * \note If you enable extraction of quoted strings, you should make 
		 * sure that your code handles the TT_QUOTED and TT_ESCAPED special 
		 * token types.
		 *
		 * \param newExtractQuoted Whether to extract quoted strings.
		 */
		virtual void setExtractQuoted(bool newExtractQuoted);
		
		/** Set escaped character extraction flag.
		 *
		 * Pass \c true to this function to enable extraction of escaped 
		 * characters, or disable this feature by passing \c false.
		 * 
		 * \note If you enable extraction of escaped characters, you should 
		 * make sure that your code handles the TT_ESCAPED special token type.
		 * If you have enabled quoted string extraction, escaped character 
		 * extraction will also be enabled by default (and cannot be 
		 * disabled).
		 *
		 * \param newExtractEscaped Whether to extract escaped characters.
		 */
		virtual void setExtractEscaped(bool newExtractEscaped);
		
		/** Get current position.
		 *
		 * Get the current parsing position relative to the first character of
		 * the input string.
		 *
		 * \return current parsing position.
		 */
		virtual unsigned int getCurrentPos();
		
		/** Get position of current token.
		 *
		 * Get the position of the current token relative to the first 
		 * character of the input string.
		 *
		 * \return position of current token.
		 */
		virtual unsigned int getCurrentTokenPos();
		
		/** Get quote character.
		 *
		 * Get the quote character of a quoted string.
		 *
		 * \return Quote character of the current token if this token is a quoted
		 * string, or 0, if the current token is not a quoted string.
		 */
		virtual char getQuoteChar();
		
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
		virtual Ionflux::Template::Tokenizer& operator=(const 
		Ionflux::Template::Tokenizer& other);
		
		/** Copy.
		 *
		 * Create a copy of the object.
		 *
		 * \return Newly allocated copy of the object.
		 */
		virtual Ionflux::Template::Tokenizer* copy() const;
		
		/** Upcast.
		 *
		 * Cast an IFObject to the most specific type.
		 *
		 * \param other Other object.
		 *
		 * \return The more specific object, or 0 if the cast failed.
		 */
		static Ionflux::Template::Tokenizer* 
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
		static Ionflux::Template::Tokenizer* 
		create(Ionflux::ObjectBase::IFObject* parentObject = 0);
		
		/** Get allocated size in memory.
		 *
		 * Get the allocated size in memory for the object.
		 *
		 * \return The more specific object, or 0 if the cast failed.
		 */
		virtual unsigned int getMemSize() const;
		
		/** Get token type map.
		 *
		 * \return Current value of token type map.
		 */
		virtual Ionflux::Template::TokenTypeMap* getTypeMap() const;
		
		/** Set token type map.
		 *
		 * Set new value of token type map.
		 *
		 * \param newTypeMap New value of token type map.
		 */
		virtual void setTypeMap(Ionflux::Template::TokenTypeMap* newTypeMap);
};

}

}

/** \file Tokenizer.hpp
 * \brief Tokenizer (header).
 */
#endif
