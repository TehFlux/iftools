/* ==========================================================================
 * IFTemplate - Ionflux Template Processor
 * Copyright © 2012 Jörn P. Meier
 * mail@ionflux.org
 * --------------------------------------------------------------------------
 * Template.i                      Template (interface).
 * =========================================================================

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
#include "iftemplate/Template.hpp"
%}

namespace Ionflux
{

namespace Template
{

class TemplateRepository;

class TemplateClassInfo
: public Ionflux::ObjectBase::IFClassInfo
{
    public:
        TemplateClassInfo();
        virtual ~TemplateClassInfo();
};

class Template
: public Ionflux::Template::Tree
{
    public:
		static const std::string ITERATION_COUNTER;
		static const std::string NUM_ITERATIONS;
		static const std::string CONDITION_NODE;
		static const Ionflux::Template::TokenType TT_TEMPLATE_TAG_OPEN;
		static const Ionflux::Template::TokenType TT_TEMPLATE_TAG_CLOSE;
		static const Ionflux::Template::TokenType TT_VAR_MARKER;
		static const Ionflux::Template::TokenType TT_COMMENT;
		static const Ionflux::Template::TokenType TT_TREEPATH;
		static const Ionflux::Template::TokenType TT_END_TAG_MARKER;
		static const Ionflux::Template::TokenType TT_OPERATOR_NSO;
		static const std::string TAG_FOREACH;
		static const std::string TAG_FOREACH_ELSE;
		static const std::string TAG_FOREACH_IN;
		static const std::string TAG_IF;
		static const std::string TAG_IF_ELSE;
		static const std::string TAG_FIRST;
		static const std::string TAG_MID;
		static const std::string TAG_LAST;
		static const std::string TAG_SINGLE;
		static const std::string TAG_NOTFIRST;
		static const std::string TAG_NOTMID;
		static const std::string TAG_NOTLAST;
		static const std::string TAG_NOTSINGLE;
		static const std::string TAG_INCLUDE;
		static const std::string TAG_IMPORT;
		static const std::string TAG_SWRAP;
		static const std::string TAG_SECTION;
		static const std::string TAG_REF;
		static const std::string SWRAP_DEFAULT_LINE_WIDTH;
		static const std::string SWRAP_DEFAULT_LINE_TERM;
		static const unsigned int DEFAULT_MAX_NESTING_DEPTH;
        
        Template();
		Template(const Ionflux::Template::Template& other);
        Template(const std::string& templateInput, Ionflux::Template::Node*
        initRoot = 0, Ionflux::Template::TemplateRepository* initRepository
        = 0);
        virtual ~Template();
        virtual void readTemplate(const std::string& templateFileName, 
        Ionflux::Template::TemplateElementVector& target);
        virtual void readTemplate(const std::string& templateFileName);
        virtual void setTemplate(const std::string& newTemplate, 
        Ionflux::Template::TemplateElementVector& target);
        virtual void setTemplate(const std::string& newTemplate);
        virtual void setTemplateModule(const std::string& modulePath, 
        Ionflux::Template::TemplateElementVector& target);
        virtual void setTemplateModule(const std::string& modulePath);
        virtual std::string process(const std::string& newTemplate = "", 
        Ionflux::Template::Node* newConfig = 0);
        virtual std::string processModule(const std::string& modulePath, 
        Ionflux::Template::Node* newConfig = 0);
        virtual void printElementDebugInfo();
		virtual Ionflux::Template::Template* copy() const;
		static Ionflux::Template::Template* upcast(Ionflux::ObjectBase::IFObject*
		other);
		static Ionflux::Template::Template* create(Ionflux::ObjectBase::IFObject*
		parentObject = 0);
		static Ionflux::Template::Template* create(const std::string& 
		templateInput, Ionflux::Template::Node* initRoot = 0, 
		Ionflux::Template::TemplateRepository* initRepository = 0, 
		Ionflux::ObjectBase::IFObject* parentObject = 0);
        virtual void setMaxNestingDepth(unsigned int newMaxNestingDepth);
        virtual unsigned int getMaxNestingDepth() const;
        virtual void setRepository(Ionflux::Template::TemplateRepository* 
        newRepository);
        virtual Ionflux::Template::TemplateRepository* getRepository() 
        const;
};

}

}
