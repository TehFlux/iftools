#ifndef IONFLUX_TEMPLATE_TEMPLATE
#define IONFLUX_TEMPLATE_TEMPLATE
/* ==========================================================================
 * IFTemplate - Ionflux Template Processor
 * Copyright © 2012 Jörn P. Meier
 * mail@ionflux.org
 * --------------------------------------------------------------------------
 * Template.hpp                    Template (header).
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

#include <string>
#include "iftemplate/types.hpp"
#include "iftemplate/templatetypes.hpp"
#include "iftemplate/Tokenizer.hpp"
#include "iftemplate/Tree.hpp"

namespace Ionflux
{

namespace Template
{

class TemplateRepository;

/// Class information for class Template.
class TemplateClassInfo
: public Ionflux::ObjectBase::IFClassInfo
{
	public:
		/// Constructor.
		TemplateClassInfo();
		/// Destructor.
		virtual ~TemplateClassInfo();
};

/** Template.
 * \ingroup iftemplate
 *
 * A template is used to create a representation of data dynamically from a
 * template string.
 */
class Template
: public Ionflux::Template::Tree
{
	private:
		
	protected:
		/// template input.
		std::string templateInput;
		/// template tokenizer.
		Ionflux::Template::Tokenizer tok;
		/// tag tokenizer.
		Ionflux::Template::Tokenizer tagTok;
		/// template elements.
		Ionflux::Template::TemplateElementVector elements;
		/// template sections.
		Ionflux::Template::TemplateSectionMap sections;
		/// maximum nesting depth.
		unsigned int maxNestingDepth;
		/// template respository.
		Ionflux::Template::TemplateRepository* repository;
		
		/** Clear elements.
		 *
		 * Clear the elements from the template.
		 */
		virtual void clearElements();
		
		/** Initialize token types.
		 *
		 * Initialize the token types.
		 */
		virtual void initTokenTypes();
		
		/** Parse template input.
		 *
		 * Parse the template input into a target vector of template elements.
		 * 
		 * \note Any memory allocated for template elements by this function 
		 * must be managed by the caller.
		 *
		 * \param target where to store the resulting template elements.
		 *
		 * \return \c true on success, \c false otherwise.
		 */
		virtual bool parse(Ionflux::Template::TemplateElementVector& target);
		
		/** Parse template input.
		 *
		 * Parse the template input into a target vector of template elements.
		 *
		 * \return \c true on success, \c false otherwise.
		 */
		virtual bool parse();
		
		/** Add character data.
		 *
		 * Creates a new template element for the specified character data. No
		 * element will be added if the character data is empty.
		 *
		 * \param characterData where to store new template elements.
		 * \param target where to store the new template elements.
		 */
		virtual void addCharacterData(const std::string& characterData, 
		Ionflux::Template::TemplateElementVector& target);
		
		/** Add template tag.
		 *
		 * Creates a new template element for the specified template tag data.
		 * No element will be added if the tag data is empty.
		 *
		 * \param tagData template tag data.
		 * \param target where to store the new template elements.
		 *
		 * \return \c true if the tag data is valid and a template element has 
		 * been added, \c false otherwise..
		 */
		virtual bool addTemplateTag(const std::string& tagData, 
		Ionflux::Template::TemplateElementVector& target);
		
		/** Preprocess template elements.
		 *
		 * Preprocesses template elements.
		 *
		 * \param target template elements to be preprocessed.
		 *
		 * \return \c true on success, \c false otherwise.
		 */
		virtual bool preprocess(Ionflux::Template::TemplateElementVector& 
		target);
		
		/** Process template.
		 *
		 * Generate a data representation from the specified template element 
		 * range.
		 *
		 * \param from first template element of the range.
		 * \param to last template element of the range.
		 * \param depth nesting levels.
		 *
		 * \return data representation.
		 */
		virtual std::string process(unsigned int from, unsigned int to, 
		Ionflux::Template::TagNestingLevel depth);
		
	public:
		/// Iteration counter node name.
		static const std::string ITERATION_COUNTER;
		/// Number of iterations node name.
		static const std::string NUM_ITERATIONS;
		/// Condition node name.
		static const std::string CONDITION_NODE;
		/// Token type: template tag (open).
		static const Ionflux::Template::TokenType TT_TEMPLATE_TAG_OPEN;
		/// Token type: template tag (close).
		static const Ionflux::Template::TokenType TT_TEMPLATE_TAG_CLOSE;
		/// Token type: variable marker.
		static const Ionflux::Template::TokenType TT_VAR_MARKER;
		/// Token type: comment.
		static const Ionflux::Template::TokenType TT_COMMENT;
		/// Token type: tree path.
		static const Ionflux::Template::TokenType TT_TREEPATH;
		/// Token type: template tag end marker.
		static const Ionflux::Template::TokenType TT_END_TAG_MARKER;
		/// Token type: operators.
		static const Ionflux::Template::TokenType TT_OPERATOR_NSO;
		/// Template tag name: foreach.
		static const std::string TAG_FOREACH;
		/// Template tag name: foreach else.
		static const std::string TAG_FOREACH_ELSE;
		/// Template tag name: foreach in.
		static const std::string TAG_FOREACH_IN;
		/// Template tag name: if.
		static const std::string TAG_IF;
		/// Template tag name: else.
		static const std::string TAG_IF_ELSE;
		/// Template tag name: first.
		static const std::string TAG_FIRST;
		/// Template tag name: mid.
		static const std::string TAG_MID;
		/// Template tag name: last.
		static const std::string TAG_LAST;
		/// Template tag name: single.
		static const std::string TAG_SINGLE;
		/// Template tag name: notfirst.
		static const std::string TAG_NOTFIRST;
		/// Template tag name: notmid.
		static const std::string TAG_NOTMID;
		/// Template tag name: notlast.
		static const std::string TAG_NOTLAST;
		/// Template tag name: notsingle.
		static const std::string TAG_NOTSINGLE;
		/// Template tag name: include.
		static const std::string TAG_INCLUDE;
		/// Template tag name: import.
		static const std::string TAG_IMPORT;
		/// Template tag name: swrap.
		static const std::string TAG_SWRAP;
		/// Template tag name: section.
		static const std::string TAG_SECTION;
		/// Template tag name: ref.
		static const std::string TAG_REF;
		/// Swrap default line width.
		static const std::string SWRAP_DEFAULT_LINE_WIDTH;
		/// Swrap default line terminator.
		static const std::string SWRAP_DEFAULT_LINE_TERM;
		/// Default maximum nesting depth.
		static const unsigned int DEFAULT_MAX_NESTING_DEPTH;
		/// Class information instance.
		static const TemplateClassInfo templateClassInfo;
		/// Class information.
		static const Ionflux::ObjectBase::IFClassInfo* CLASS_INFO;
		
		/** Constructor.
		 *
		 * Construct new Template object.
		 */
		Template();
		
		/** Constructor.
		 *
		 * Construct new Template object.
		 *
		 * \param other Other object.
		 */
		Template(const Ionflux::Template::Template& other);
		
		/** Constructor.
		 *
		 * Construct new Template object.
		 *
		 * \param templateInput template input.
		 * \param initRoot root node.
		 * \param initRepository template repository.
		 */
		Template(const std::string& templateInput, Ionflux::Template::Node* 
		initRoot = 0, Ionflux::Template::TemplateRepository* initRepository = 0);
		
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
		Ionflux::Template::TemplateElementVector& target);
		
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
		Ionflux::Template::TemplateElementVector& target);
		
		/** Set template.
		 *
		 * Sets the template to the specified byte string.
		 *
		 * \param newTemplate Template.
		 */
		virtual void setTemplate(const std::string& newTemplate);
		
		/** Set template module.
		 *
		 * Sets the template to the data of the specified template module.
		 *
		 * \param modulePath Module path.
		 * \param target Where to store new template elements.
		 */
		virtual void setTemplateModule(const std::string& modulePath, 
		Ionflux::Template::TemplateElementVector& target);
		
		/** Set template module.
		 *
		 * Sets the template to the data of the specified template module.
		 *
		 * \param modulePath Module path.
		 */
		virtual void setTemplateModule(const std::string& modulePath);
		
		/** Process template.
		 *
		 * Generate a data representation from the template.
		 *
		 * \param newTemplate Template.
		 * \param newConfig Configuration.
		 *
		 * \return data representation.
		 */
		virtual std::string process(const std::string& newTemplate = "", 
		Ionflux::Template::Node* newConfig = 0);
		
		/** Process template module.
		 *
		 * Generate a data representation from the template module.
		 *
		 * \param modulePath Module path.
		 * \param newConfig Configuration.
		 *
		 * \return data representation.
		 */
		virtual std::string processModule(const std::string& modulePath, 
		Ionflux::Template::Node* newConfig = 0);
		
		/** Print debug information.
		 *
		 * Print debug information.
		 */
		virtual void printElementDebugInfo();
		
		/** Assignment operator.
		 *
		 * Assign an object.
		 *
		 * \param other Other object.
		 *
		 * \return The object itself.
		 */
		virtual Ionflux::Template::Template& operator=(const 
		Ionflux::Template::Template& other);
		
		/** Copy.
		 *
		 * Create a copy of the object.
		 *
		 * \return Newly allocated copy of the object.
		 */
		virtual Ionflux::Template::Template* copy() const;
		
		/** Upcast.
		 *
		 * Cast an IFObject to the most specific type.
		 *
		 * \param other Other object.
		 *
		 * \return The more specific object, or 0 if the cast failed.
		 */
		static Ionflux::Template::Template* upcast(Ionflux::ObjectBase::IFObject*
		other);
		
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
		static Ionflux::Template::Template* create(Ionflux::ObjectBase::IFObject*
		parentObject = 0);
        
		/** Create instance.
		 *
		 * Create a new Template object.
		 *
		 * \param templateInput template input.
		 * \param initRoot root node.
		 * \param initRepository template repository.
		 * \param parentObject Parent object.
		 */
		static Ionflux::Template::Template* create(const std::string& 
		templateInput, Ionflux::Template::Node* initRoot = 0, 
		Ionflux::Template::TemplateRepository* initRepository = 0, 
		Ionflux::ObjectBase::IFObject* parentObject = 0);
		
		/** Get maximum nesting depth.
		 *
		 * \return Current value of maximum nesting depth.
		 */
		virtual unsigned int getMaxNestingDepth() const;
		
		/** Set maximum nesting depth.
		 *
		 * Set new value of maximum nesting depth.
		 *
		 * \param newMaxNestingDepth New value of maximum nesting depth.
		 */
		virtual void setMaxNestingDepth(unsigned int newMaxNestingDepth);
		
		/** Get template respository.
		 *
		 * \return Current value of template respository.
		 */
		virtual Ionflux::Template::TemplateRepository* getRepository() const;
		
		/** Set template respository.
		 *
		 * Set new value of template respository.
		 *
		 * \param newRepository New value of template respository.
		 */
		virtual void setRepository(Ionflux::Template::TemplateRepository* 
		newRepository);
};

}

}

/** \file Template.hpp
 * \brief Template (header).
 */
#endif
