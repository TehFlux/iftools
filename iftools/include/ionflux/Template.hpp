#ifndef IONFLUX_TOOLS_TEMPLATE
#define IONFLUX_TOOLS_TEMPLATE
/* ==========================================================================
 * Ionflux Tools
 * Copyright (c) 2004 Joern P. Meier
 * mail@ionflux.org
 * --------------------------------------------------------------------------
 * Template.hpp                    Template processor.
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
#include <fstream>
#include <sstream>
#include <vector>
#include <map>
#include "ionflux/tools.hpp"
#include "ionflux/Reporter.hpp"
#include "ionflux/Tree.hpp"
#include "ionflux/Tokenizer.hpp"
#include "ionflux/StringFilter.hpp"

namespace Ionflux
{

namespace Tools
{

/** \addtogroup template Template processor
 *
 * A generic template processor. (See \ref tpldoc for details.)
 *
 * @{
 */

/** Template variable.
 *
 * A template variable, consisting of a data entry and (optionally) a string 
 * filter.
 */
struct TemplateVar
{
	/// Data entry.
	DataEntry data;
	/// String filter.
	StringFilter *filter;
};

/** Template element.
 *
 * Part of a template, generated from character data and template tags by the 
 * template parser.
 */
struct TemplateElement
{
	/// Element type.
	int type;
	/// Element parameters.
	std::vector<std::string> params;
	/// Element variables.
	std::vector<TemplateVar> vars;
	/// Element references.
	std::vector<int> refs;
	/// Element type: Invalid.
	static const int TE_INVALID;
	/// Element type: Character data.
	static const int TE_CDATA;
	/// Element type: Variable.
	static const int TE_VAR;
	/// Element type: foreach block.
	static const int TE_FOREACH;
	/// Element type: (foreach) else block.
	static const int TE_FOREACH_ELSE;
	/// Element type: foreach block (end tag).
	static const int TE_FOREACH_END;
	/// Element type: if block.
	static const int TE_IF;
	/// Element type: (if) else block.
	static const int TE_IF_ELSE;
	/// Element type: if block (end tag).
	static const int TE_IF_END;
	/// Element type: first block.
	static const int TE_FIRST;
	/// Element type: first block (end tag).
	static const int TE_FIRST_END;
	/// Element type: mid block.
	static const int TE_MID;
	/// Element type: mid block (end tag).
	static const int TE_MID_END;
	/// Element type: last block.
	static const int TE_LAST;
	/// Element type: last block (end tag).
	static const int TE_LAST_END;
	/// Element type: single block.
	static const int TE_SINGLE;
	/// Element type: single block (end tag).
	static const int TE_SINGLE_END;
	/// Element type: notlast block.
	static const int TE_NOTLAST;
	/// Element type: notlast block (end tag).
	static const int TE_NOTLAST_END;
	/// Element type: notfirst block.
	static const int TE_NOTFIRST;
	/// Element type: notfirst block (end tag).
	static const int TE_NOTFIRST_END;
	/// Element type: notmid block.
	static const int TE_NOTMID;
	/// Element type: notmid block (end tag).
	static const int TE_NOTMID_END;
	/// Element type: notsingle block.
	static const int TE_NOTSINGLE;
	/// Element type: notsingle block (end tag).
	static const int TE_NOTSINGLE_END;
	/// Element type: include.
	static const int TE_INCLUDE;
	/// Element type: swrap.
	static const int TE_SWRAP;
	/// Element type: swrap (end tag).
	static const int TE_SWRAP_END;
	/// Element type: section.
	static const int TE_SECTION;
	/// Element type: section (end tag).
	static const int TE_SECTION_END;
	/// Element type: ref.
	static const int TE_REF;
};

/** Template tag nesting level.
 *
 * Keeps track of tag nesting levels in a template.
 */
struct TagNestingLevel
{
	/// Nesting level: foreach tags.
	unsigned int tagForeach;
	/// Nesting level: if tags.
	unsigned int tagIf;
	/// Nesting level: first tags.
	unsigned int tagFirst;
	/// Nesting level: mid tags.
	unsigned int tagMid;
	/// Nesting level: last tags.
	unsigned int tagLast;
	/// Nesting level: single tags.
	unsigned int tagSingle;
	/// Nesting level: notfirst tags.
	unsigned int tagNotFirst;
	/// Nesting level: notmid tags.
	unsigned int tagNotMid;
	/// Nesting level: notlast tags.
	unsigned int tagNotLast;
	/// Nesting level: notsingle tags.
	unsigned int tagNotSingle;
	/// Nesting level: swrap tags.
	unsigned int tagSWrap;
	/// Nesting level: section tags.
	unsigned int tagSection;
	/// Nesting level: ref tags.
	unsigned int tagRef;
	/// Nesting level: all tags.
	unsigned int all;
	
	/// Constructor.
	TagNestingLevel();
};

/** Template section.
 *
 * A template section.
 */
struct TemplateSection
{
	/// First template element of the section.
	unsigned int first;
	/// Last template element of the section.
	unsigned int last;
};

/// Map from section names to template sections.
typedef std::map<std::string, TemplateSection> TemplateSectionMap;

/** Template processor.
 *
 * Create a representation of data dynamically from a template.
 */
class Template
: public Tree
{
	protected:
		/// Console output/logging.
		Ionflux::Tools::Reporter log;
		/// Template input.
		std::string templateInput;
		/// Template tokenizer.
		Tokenizer tok;
		/// Template tag tokenizer.
		Tokenizer tagTok;
		/// Template elements.
		std::vector<TemplateElement *> elements;
		/// Template sections.
		TemplateSectionMap sections;
		/// Maximum nesting depth.
		unsigned int maxNestingDepth;
		
		/// Clear element vector.
		virtual void clearElements();
		
		/** Parse template.
		 *
		 * Parses the template input into a target vector of template 
		 * elements.
		 *
		 * \note Any memory allocated for template elements by this 
		 * function must be managed by the caller.
		 *
		 * \param target Where to store the resulting template elements.
		 *
		 * \return \c true on success, \c false otherwise.
		 */
		virtual bool parse(std::vector<TemplateElement *> &target);
		
		/** Parse template input.
		 *
		 * Parses the template input into template elements.
		 *
		 * \return \c true on success, \c false otherwise.
		 */
		virtual bool parse();
		
		/** Add character data.
		 *
		 * Creates a new template element for the specified character data. No 
		 * element will be added if the character data is empty.
		 *
		 * \param characterData Character data.
		 * \param target Where to store new template elements.
		 */
		virtual void addCharacterData(const std::string &characterData,
			std::vector<TemplateElement *> &target);
		
		/** Add template tag.
		 *
		 * Creates a new template element for the specified template tag data.
		 * No element will be added if the tag data is empty.
		 *
		 * \param tagData Template tag data.
		 * \param target Where to store new template elements.
		 *
		 * \return \c true if the tag data is valid and a template element 
		 * has been added, \c false otherwise.
		 */
		virtual bool addTemplateTag(const std::string &tagData, 
			std::vector<TemplateElement *> &target);
		
		/** Preprocess template elements.
		 *
		 * Preprocesses template elements.
		 *
		 * \param target Template elements to be preprocessed.
		 *
		 * \return \c true on success, \c false otherwise.
		 */
		virtual bool preprocess(std::vector<TemplateElement *> &target);
		
		/** Process template.
		 *
		 * Generate a data representation from the specified template element 
		 * range.
		 *
		 * \param from First template element of the range.
		 * \param to Last template element of the range.
		 * \param depth The nesting levels of this call.
		 *
		 * \return Data representation.
		 */
		virtual std::string process(unsigned int from, unsigned int to, 
			TagNestingLevel depth);
		
	public:
		/** Iteration counter node name.
		 *
		 * This node name is reserved for iteration counting. You can access 
		 * the iteration counters in a template by accessing the node data 
		 * entry &lt;ITERATION_COUNTER&gt;[&lt;nesting level&gt;], starting 
		 * from 0.
		 */
		static const std::string ITERATION_COUNTER;
		/** Number of iterations node name.
		 *
		 * This node name is reserved for storing the number of iterations. 
		 * You can access the number of iterations in a template by accessing 
		 * the node data entry &lt;NUM_ITERATIONS&gt;[&lt;nesting level&gt;], 
		 * starting from 0.
		 */
		static const std::string NUM_ITERATIONS;
		/** Condition node name.
		 *
		 * This node name is reserved for storing conditions.
		 */
		static const std::string CONDITION_NODE;
		/// Token type: Template tag marker (open).
		static const TokenType TT_TEMPLATE_TAG_OPEN;
		/// Token type: Template tag marker (close).
		static const TokenType TT_TEMPLATE_TAG_CLOSE;
		/// Token type: Variable marker.
		static const TokenType TT_VAR_MARKER;
		/// Token type: Comment character.
		static const TokenType TT_COMMENT;
		/// Token type: Tree path element.
		static const TokenType TT_TREEPATH;
		/// Token type: End tag marker.
		static const TokenType TT_END_TAG_MARKER;
		/// Token type: Operator (excluding slash and OR-sign).
		static const TokenType TT_OPERATOR_NSO;
		/// Tag keyword: foreach.
		static const std::string TAG_FOREACH;
		/// Tag keyword: (foreach) else.
		static const std::string TAG_FOREACH_ELSE;
		/// Tag keyword: (foreach) in.
		static const std::string TAG_FOREACH_IN;
		/// Tag keyword: if.
		static const std::string TAG_IF;
		/// Tag keyword: (if) else.
		static const std::string TAG_IF_ELSE;
		/// Tag keyword: first.
		static const std::string TAG_FIRST;
		/// Tag keyword: mid.
		static const std::string TAG_MID;
		/// Tag keyword: last.
		static const std::string TAG_LAST;
		/// Tag keyword: single.
		static const std::string TAG_SINGLE;
		/// Tag keyword: notfirst.
		static const std::string TAG_NOTFIRST;
		/// Tag keyword: notmid.
		static const std::string TAG_NOTMID;
		/// Tag keyword: notlast.
		static const std::string TAG_NOTLAST;
		/// Tag keyword: notsingle.
		static const std::string TAG_NOTSINGLE;
		/// Tag keyword: include.
		static const std::string TAG_INCLUDE;
		/// Tag keyword: swrap.
		static const std::string TAG_SWRAP;
		/// Tag keyword: section.
		static const std::string TAG_SECTION;
		/// Tag keyword: ref.
		static const std::string TAG_REF;
		/// SWrap default line width.
		static const std::string SWRAP_DEFAULT_LINE_WIDTH;
		/// SWrap default line terminator.
		static const std::string SWRAP_DEFAULT_LINE_TERM;
		/// Default maximum nesting depth.
		static const unsigned int DEFAULT_MAX_NESTING_DEPTH;
		
		/** Constructor.
		 *
		 * Construct new Template object.
		 */
		Template();
		
		/** Destructor.
		 *
		 * Destruct Template object.
		 */
		virtual ~Template();
		
		/** Read template file.
		 *
		 * Reads a template from a file.
		 *
		 * \param templateFileName Template file name.
		 * \param target Where to store new template elements.
		 */
		virtual void readTemplate(const std::string& templateFileName, 
			std::vector<TemplateElement *> &target);
		
		/** Read template file.
		 *
		 * Reads a template from a file.
		 *
		 * \param templateFileName Template file name.
		 */
		virtual void readTemplate(const std::string& templateFileName);
		
		/** Set template.
		 *
		 * Sets the template to the specified byte string.
		 *
		 * \param newTemplate Template.
		 * \param target Where to store new template elements.
		 */
		virtual void setTemplate(const std::string& newTemplate, 
			std::vector<TemplateElement *> &target);
		
		/** Set template.
		 *
		 * Sets the template to the specified byte string.
		 *
		 * \param newTemplate Template.
		 */
		virtual void setTemplate(const std::string& newTemplate);
		
		/** Process template.
		 *
		 * Generate a data representation from the template.
		 *
		 * \return Data representation.
		 */
		virtual std::string process(const std::string& newTemplate = "",
			Node* newConfig = 0);
		
		/** Set maximum nesting depth.
		 *
		 * Set the maximum nesting depth for template processing.
		 *
		 * \param newMaxNestingDepth Maximum nesting depth.
		 */
		virtual void setMaxNestingDepth(unsigned int newMaxNestingDepth);
		
		/** Get maximum nesting depth.
		 *
		 * Get the maximum nesting depth for template processing.
		 *
		 * \return Maximum nesting depth.
		 */
		virtual unsigned int getMaxNestingDepth();
		
		/// Print debug information.
		virtual void printElementDebugInfo();
		
		/** Get Console output/logging facility.
		 *
		 * \return The console output/logging facility used by this object.
		 */
		virtual Reporter &getLog();

};

/// @}

}

}

/** \file Template.hpp
 * \brief Template processor header.
 */
#endif
