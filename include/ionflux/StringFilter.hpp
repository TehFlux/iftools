#ifndef IONFLUX_TOOLS_STRINGFILTER
#define IONFLUX_TOOLS_STRINGFILTER
/* ==========================================================================
 * Ionflux Tools
 * Copyright (c) 2004 Joern P. Meier
 * mail@ionflux.org
 * --------------------------------------------------------------------------
 * StringFilter.hpp                    String filter.
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
#include <map>
#include "ionflux/Reporter.hpp"
#include "ionflux/Tokenizer.hpp"
#include "ionflux/StringManipulator.hpp"

namespace Ionflux
{

namespace Tools
{

/** \addtogroup strfilt String filters
 *
 * A versatile and powerful string processing facility. (See \ref strfiltdoc 
 * for details.)
 *
 * @{
 */

/// A string filter function.
struct StringFilterFunction
{
	/// Name of the filter function.
	std::string func;
	/// Function arguments.
	std::vector<std::string> args;
	/// String manipulator that implements this filter function.
	StringManipulator *manip;
};

/// Entry for a StringManipulator object.
struct StringManipulatorEntry
{
	/// Pointer to a string manipulator object.
	StringManipulator *manip;
	/// Whether this object is managed by the filter.
	bool manage;
};

/** String filter.
 *
 * A string filter is a set of functions (manipulators) that can be applied to 
 * a string to yield another string. String manipulators may take one or more 
 * arguments, and they can be stacked. An example of a string filter expression 
 * would be:
 *
 * <tt>uppercase|remove(' ')</tt>
 *
 * This filter would first change the string to uppercase and then remove 
 * all spaces.
 *
 * The general format of a string manipulator is:
 *
 * <tt>&lt;function&gt; [ '(' [  (&lt;identifier&gt; | 
 * (&lt;quote char&gt; &lt;argument&gt; &lt;quote char&gt;)) [',' 
 * | &lt;linear whitespace&gt;]+ ]+ ')' ]+</tt>
 *
 * Where <tt>&lt;quote char&gt;</tt> is either ' or ". String arguments should 
 * always be enclosed in quotes and multiple arguments should be separated 
 * by ','.
 */
class StringFilter
{
	protected:
		/// Console output/logging.
		Ionflux::Tools::Reporter log;
		/// The filter expression.
		std::string filter;
		/// The functions in this filter
		std::vector<StringFilterFunction *> functions;
		/// String manipulators available to this filter
		std::vector<StringManipulatorEntry> manipulators;
		/// String manipulator index map.
		std::map<std::string, StringManipulator*> manipIndex;
		/// Tokenizer for parsing filter expressions
		Tokenizer tok;
		/// String manipulator: uppercase.
		static StringUppercase STRINGMANIP_UPPERCASE;
		/// String manipulator: lowercase.
		static StringLowercase STRINGMANIP_LOWERCASE;
		/// String manipulator: erase.
		static StringErase STRINGMANIP_ERASE;
		/// String manipulator: replace.
		static StringReplace STRINGMANIP_REPLACE;
		/// String manipulator: trim.
		static StringTrim STRINGMANIP_TRIM;
		/// String manipulator: ltrim.
		static StringLTrim STRINGMANIP_LTRIM;
		/// String manipulator: rtrim.
		static StringRTrim STRINGMANIP_RTRIM;
		/// String manipulator: truncate.
		static StringTruncate STRINGMANIP_TRUNCATE;
		/// String manipulator: center.
		static StringCenter STRINGMANIP_CENTER;
		/// String manipulator: move.
		static StringMove STRINGMANIP_MOVE;
		/// String manipulator: append.
		static StringAppend STRINGMANIP_APPEND;
		/// String manipulator: insert.
		static StringInsert STRINGMANIP_INSERT;
		/// String manipulator: numformat.
		static StringNumFormat STRINGMANIP_NUMFORMAT;
		/// String manipulator: translate.
		static StringTranslate STRINGMANIP_TRANSLATE;
		/// String manipulator: substr.
		static StringSubstr STRINGMANIP_SUBSTR;
		/// String manipulator: lpad.
		static StringLPad STRINGMANIP_LPAD;
		/// String manipulator: rpad.
		static StringRPad STRINGMANIP_RPAD;
		/// String manipulator: swrap.
		static StringSWrap STRINGMANIP_SWRAP;
		/// String manipulator: xmlescape.
		static StringXMLEscape STRINGMANIP_XMLESCAPE;
		/// String manipulator: urlencode.
		static StringURLEncode STRINGMANIP_URLENCODE;
		
		/** Delete all functions.
		 *
		 * Erase all parsed functions from this filter.
		 */
		virtual void clearFunctions();
		
		/** Delete string manipulators.
		 *
		 * Erase all manipulators from this filter.
		 */
		virtual void clearManipulators();
		
		/** Initialize token types.
		 *
		 * Initialize the token types used for parsing filter expressions.
		 */
		virtual void initTokenTypes();
		
		/** Initialize string manipulators.
		 *
		 * Initialize string manipulators usable by this filter.
		 */
		virtual void initManipulators();
		
		/** Parse filter expression.
		 *
		 * Parse the current filter expression.
		 */
		virtual void parse();
		
		/** Get string manipulator by name.
		 *
		 * Find a string manipulator of the specified name in the vector of 
		 * registered manipulators.
		 *
		 * \param manipName Name of the string manipulator.
		 *
		 * \return The string manipulator of the specified name if available, 
		 * 0 otherwise.
		 */
		virtual StringManipulator *getManipulator(const std::string& manipName);
		
	public:
		/// Token type: Function separator.
		static const TokenType TT_FUNC_SEP;
		/// Token type: Function left bracket.
		static const TokenType TT_FUNC_BRACKET_LEFT;
		/// Token type: Function right bracket.
		static const TokenType TT_FUNC_BRACKET_RIGHT;
		/// Token type: Argument delimiter.
		static const TokenType TT_FUNC_ARG_DELIM;
		/// Token type: Argument separator.
		static const TokenType TT_FUNC_ARG_SEP;
		
		/** Constructor.
		 *
		 * Construct new StringFilter object.
		 */
		StringFilter();
		
		/** Constructor.
		 *
		 * Construct new StringFilter object.
		 *
		 * \param initFilter A string filter expression.
		 */
		StringFilter(const std::string& initFilter);
		
		/** Destructor.
		 *
		 * Destruct StringFilter object.
		 */
		virtual ~StringFilter();
		
		/** Sets filter expression.
		 *
		 * Sets the filter expression for this string filter.
		 *
		 * \param newFilter A string filter expression.
		 */
		virtual void setFilter(const std::string& newFilter);
		
		/** Add a string manipulator.
		 *
		 * Add a string manipulator to the set of manipulators available to
		 * this string filter. Manipulators must be added before they can be
		 * used in a filter expression. They also must be available during the
		 * whole lifetime of the string filter object.\n
		 * NOTE: This is easily accomplished by allocating the string 
		 * manipulator on the free store and passing 'true' as the 'manage' 
		 * parameter. The string filter will then delete the string manipulator 
		 * upon deconstruction.
		 *
		 * \param newManip Pointer to a string manipulator object.
		 * \param manage Whether this manipulator is managed by the filter.
		 */
		virtual void addManipulator(StringManipulator *newManip, bool manage);
		
		/** Apply filter.
		 *
		 * Apply the filter to a string of bytes.
		 *
		 * \param bytes A string to apply this filter to.
		 *
		 * \return The result of applying the string filter to \c bytes.
		 */
		virtual std::string apply(const std::string& bytes);
		
		/// Print debug information.
		virtual void printDebugInfo();
		
		/** Get Console output/logging facility.
		 *
		 * \return The console output/logging facility used by this object.
		 */
		virtual Reporter &getLog();
};

/// @}

}

}

/** \file StringFilter.hpp
 * \brief String filter header.
 */
#endif
