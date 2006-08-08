#ifndef IONFLUX_TOOLS_REGEXP
#define IONFLUX_TOOLS_REGEXP
/* ==========================================================================
 * Ionflux Tools
 * Copyright (c) 2004 Joern P. Meier
 * mail@ionflux.org
 * --------------------------------------------------------------------------
 * RegExp.hpp                 Regular expression pattern matching
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

#include <math.h>
#include <pcre.h>
#include <string>
#include <iostream>
#include <vector>
#include <map>
#include "ionflux/tools.hpp"
#include "ionflux/Tree.hpp"

namespace Ionflux
{

namespace Tools
{

/** \addtogroup regexp Regular expressions
 *
 * Tools for Perl compatible regular expression pattern matching.
 *
 * @{
 */

/// Set of matched subpatterns.
typedef std::vector<std::string> ReMatch;
/// Set of several sets of matched subpatterns.
typedef std::vector<ReMatch> ReMatchSet;

/** Regular expression matching.
 *
 * Wrapper class for the Perl compatible regular expression API (PCRE).
 */
class RegExp
{
	protected:
		/// PCRE object.
		pcre *regExp;
		/// The pattern.
		std::string pattern;
		/// Maximum number of subpatterns that can be matched.
		unsigned int maxSubpatterns;
		/// PCRE options (see PCRE API specification).
		int pcreOptions;
		
	public:
		/** Constructor.
		 *
		 * Construct new RegExp object.
		 */
		RegExp();
		
		/** Constructor.
		 *
		 * Construct new RegExp object.
		 *
		 * \param initPattern The initial pattern.
		 */
		RegExp(const std::string& initPattern);
		
		/** Constructor.
		 *
		 * Construct new RegExp object.
		 *
		 * \param initPattern The initial pattern.
		 * \param initOptions PCRE options.
		 *
		 * \sa setOptions()
		 */
		RegExp(const std::string& initPattern, int initOptions);
		
		/** Destructor.
		 *
		 * Destruct RegExp object.
		 */
		virtual ~RegExp();
		
		/** Set the pattern.
		 *
		 * Sets the pattern used for matching to the specified string.
		 *
		 * \param newPattern The new pattern.
		 */
		virtual void setPattern(const std::string& newPattern);
		
		/** Get the pattern.
		 *
		 * Get the current pattern.
		 *
		 * \return The current pattern.
		 */
		virtual std::string getPattern();
		
		/** Set PCRE options.
		 *
		 * Sets PCRE options used for matching to the specified string.
		 *
		 * As of PCRE 4.5, valid options are:
		 *
		 * \c PCRE_ANCHORED         Force pattern anchoring\n
		 * \c PCRE_CASELESS         Do caseless matching\n
		 * \c PCRE_DOLLAR_ENDONLY   $ not to match newline at end\n
		 * \c PCRE_DOTALL           . matches anything including NL\n
		 * \c PCRE_EXTENDED         Ignore whitespace and # comments\n
		 * \c PCRE_EXTRA            PCRE extra features (not much use currently)\n
		 * \c PCRE_MULTILINE        ^ and $ match newlines within data\n
		 * \c PCRE_NO_AUTO_CAPTURE  Disable numbered capturing parentheses
         *                          (named ones available)\n
		 * \c PCRE_UNGREEDY         Invert greediness of quantifiers\n
		 * \c PCRE_UTF8             Run in UTF-8 mode\n
		 * \c PCRE_NO_UTF8_CHECK    Do not check the pattern for UTF-8 validity
		 *                          (only relevant if PCRE_UTF8 is set)
		 *
		 * \param newOptions PCRE options.
		 */
		virtual void setOptions(int newOptions);
		
		/** Get PCRE options.
		 *
		 * Get the current PCRE options.
		 *
		 * \return Current PCRE options.
		 */
		virtual int getOptions();
		
		/** Set maximum number of subpatterns.
		 *
		 * Sets the maximum number of subpatterns that will be returned by a
		 * matching operation.
		 *
		 * \param newMaxSubpatterns Maximum number of subpatterns to return.
		 */
		virtual void setMaxSubpatterns(unsigned int newMaxSubpatterns);
		
		/** Get maximum number of subpatterns.
		 *
		 * Get the maximum number of subpatterns that will be returned by
		 * a matching operation.
		 *
		 * \return Maximum number of subpatterns.
		 */
		virtual unsigned int getMaxSubpatterns();
		
		/** Match pattern in a string.
		 *
		 * Match pattern to a string. Returns true if a match is found, false 
		 * otherwise. If the \c subPatterns argument is not null, it will be 
		 * used to store matched subpatterns. The maximum number of 
		 * subpatterns that will be stored can be retrieved with 
		 * getMaxSubpatterns() and set with setMaxSubpatterns().
		 *
		 * \param haystack String in which to search for patterns.
		 * \param subPatterns Where to store subpatterns.
		 *
		 * \sa matchAll(), getMaxSubpatterns() setMaxSubpatterns()
		 *
		 * \return \c true if the pattern matches the \c haystack, \c false 
		 * otherwise.
		 */
		virtual bool match(const std::string& haystack, 
			ReMatch* subPatterns = 0);
		
		/** Match all patterns in a string.
		 *
		 * Like match(), except that all occurences of the pattern in 
		 * \c haystack are matched. Returns the number of matches. If the 
		 * \c subPatterns argument is not null, it will be used to store 
		 * matched subpatterns.
		 *
		 * \param haystack String in which to search for patterns.
		 * \param subPatterns Where to store subpatterns.
		 *
		 * \sa match()
		 *
		 * \return Number of occurences of the pattern that have been matched.
		 */
		virtual unsigned int matchAll(const std::string& haystack, 
			ReMatchSet* subPatterns);
		
		/** Match pattern in a string.
		 *
		 * Convenience function to match pattern \c needle to string 
		 * \c haystack without any previous pattern initialization.
		 *
		 * \param needle Pattern to search for.
		 * \param haystack String in which to search for patterns.
		 * \param subPatterns Where to store subpatterns.
		 *
		 * \return \c true if the pattern matches the \c haystack, \c false 
		 * otherwise.
		 */
		virtual bool match(const std::string& needle, 
			const std::string& haystack, ReMatch* subPatterns);
		
		/** Match pattern in a string.
		 *
		 * Convenience function to match all occurences of pattern \c needle 
		 * in string \c haystack without any previous pattern initialization.
		 *
		 * \param needle Pattern to search for.
		 * \param haystack String in which to search for patterns.
		 * \param subPatterns Where to store subpatterns.
		 *
		 * \sa match()
		 *
		 * \return Number of occurences of the pattern that have been matched.
		 */
		virtual unsigned int matchAll(const std::string& needle, 
			const std::string& haystack, ReMatchSet* subPatterns);
		
		/** Replace pattern in a string.
		 *
		 * Replaces pattern in string \c haystack with \c replacement.
		 *
		 * \param haystack String in which to replace patterns.
		 * \param replacement Replacement string.
		 */
		virtual void replace(std::string& haystack, 
			const std::string& replacement);
		
		/** Replace subpatterns in a string.
		 *
		 * Replaces subpatterns in string \c haystack with strings from 
		 * vector \c replacement.
		 *
		 * \param haystack String in which to replace patterns.
		 * \param replacement Replacement strings.
		 */
		virtual void replaceSubpatterns(std::string& haystack, 
			const std::vector<std::string>& replacement);
		
		/** Replace all patterns in a string.
		 *
		 * Like replace(), except that all occurences of the pattern are 
		 * replaced.
		 *
		 * \param haystack String in which to replace patterns.
		 * \param replacement Replacement string.
		 *
		 * \sa replace()
		 */
		virtual void replaceAll(std::string& haystack, 
			const std::string& replacement);
		
		/** Replace all subpatterns in a string.
		 *
		 * Like replaceSubpatterns(), except that all occurences of the 
		 * subpatterns are replaced.
		 *
		 * \param haystack String in which to replace patterns.
		 * \param replacement Replacement strings.
		 *
		 * \sa replaceSubPatterns()
		 */
		virtual void replaceAllSubpatterns(std::string& haystack, 
			const std::vector<std::string>& replacement);
		
		/** Replace pattern in a string.
		 *
		 * Convenience function to replace pattern \c needle in string 
		 * \c haystack with \c replacement without any previous pattern 
		 * initialization.
		 *
		 * \param needle Pattern which to replace.
		 * \param haystack String in which to replace patterns.
		 * \param replacement Replacement string.
		 */
		virtual void replace(const std::string& needle, std::string& haystack, 
			const std::string& replacement);
		
		/** Replace subpatterns in a string.
		 *
		 * Convenience function to replace subpatterns of \c needle in string 
		 * \c haystack with strings from \c replacement without any previous 
		 * pattern initialization.
		 *
		 * \param needle Pattern which to replace.
		 * \param haystack String in which to replace patterns.
		 * \param replacement Replacement strings.
		 */
		virtual void replaceSubpatterns(const std::string& needle, 
			std::string& haystack, const std::vector<std::string>& replacement);
		
		/** Replace all patterns in a string.
		 *
		 * Convenience function to replace all occurences of pattern \c needle 
		 * in string \c haystack with \c replacement without any previous 
		 * pattern initialization.
		 *
		 * \param needle Pattern which to replace.
		 * \param haystack String in which to replace patterns.
		 * \param replacement Replacement string.
		 *
		 * \sa replace()
		 */
		virtual void replaceAll(const std::string& needle, 
			std::string& haystack, const std::string& replacement);
		
		/** Replace all subpatterns in a string.
		 *
		 * Convenience function to replace all occurences of subpatterns of 
		 * \c needle in string \c haystack with strings from \c replacement 
		 * without any previous pattern initialization.
		 *
		 * \param needle Pattern which to replace.
		 * \param haystack String in which to replace patterns.
		 * \param replacement Replacement strings.
		 *
		 * \sa replaceSubPatterns()
		 */
		virtual void replaceAllSubpatterns(const std::string& needle, 
			std::string& haystack, const std::vector<std::string>& replacement);
		
		/** Create a map of matched subpatterns.
		 *
		 * Generates a map of matched subpatterns by taking keys from the 
		 * \c fields parameter and the matched subpatterns as values.
		 * The \c fields parameter is a string consisting of field names, 
		 * separated by the string 'separator'. If there are more subpatterns 
		 * than field names, missing field names will be generated 
		 * automatically by appending a number to the 'undefinedPrefix'.
		 *
		 * \note The complete match will not be added to the map.
		 *
		 * \param match Subpatterns for which a map should be created.
		 * \param fields Field names tu use as keys.
		 * \param separator Field name separator.
		 * \param undefinedPrefix Prefix for undefined fields.
		 * \param record Map to store the results in.
		 */
		static void createMatchMap(const ReMatch& match, 
			const std::string& fields, const std::string& separator, 
			const std::string& undefinedPrefix, 
			std::map<std::string, std::string>& record);
		
		/** Create a map of matched subpatterns.
		 *
		 * Generates a map of matched subpatterns by taking keys from the 
		 * \c fields parameter and the matched subpatterns as values.
		 * The \c fields parameter is a vector containing the of field names.
		 * If there are more subpatterns than field names, missing field names 
		 * will be generated automatically by appending a number to the 
		 * 'undefinedPrefix'.
		 *
		 * \note The complete match will not be added to the map.
		 *
		 * \param match Subpatterns for which a map should be created.
		 * \param fields Vector of field names tu use as keys.
		 * \param undefinedPrefix Prefix for undefined fields.
		 * \param record Map to store the results in.
		 */
		static void createMatchMap(const ReMatch& match, 
			const std::vector<std::string>& fields, 
			const std::string& undefinedPrefix, 
			std::map<std::string, std::string>& record);
		
		/** Create a tree of matched subpatterns.
		 *
		 * Generates a tree of matched subpatterns by taking keys from the 
		 * \c fields parameter and the matched subpatterns as values.
		 * The \c fields parameter is a string consisting of field names, 
		 * separated by the string \c separator. If there are more subpatterns 
		 * than field names, missing field names will be generated 
		 * automatically by appending a number to the \c undefinedPrefix.
		 *
		 * \note The complete match will not be added to the tree.
		 *
		 * \param match Subpatterns for which a map should be created.
		 * \param fields Field names tu use as keys.
		 * \param separator Field name separator.
		 * \param undefinedPrefix Prefix for undefined fields.
		 * \param record Node to store the results in.
		 */
		static void createMatchTree(const ReMatch& match, 
			const std::string& fields, const std::string& separator, 
			const std::string& undefinedPrefix, Node& record);
		
		/** Create a tree of matched subpatterns.
		 *
		 * Generates a tree of matched subpatterns by taking keys from the 
		 * \c fields parameter and the matched subpatterns as values.
		 * The \c fields parameter is a vector containing the of field names.
		 * If there are more subpatterns than field names, missing field names 
		 * will be generated automatically by appending a number to the 
		 * \c undefinedPrefix.
		 *
		 * \note The complete match will not be added to the tree.
		 *
		 * \param match Subpatterns for which a map should be created.
		 * \param fields Vector of field names tu use as keys.
		 * \param undefinedPrefix Prefix for undefined fields.
		 * \param record Node to store the results in.
		 */
		static void createMatchTree(const ReMatch& match, 
			const std::vector<std::string>& fields, 
			const std::string& undefinedPrefix, Node& record);
		
};

/// @}

}

}

/** \file RegExp.hpp
 * \brief Regular expression pattern matching header.
 */
#endif
