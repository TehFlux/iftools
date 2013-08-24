#ifndef IONFLUX_TEMPLATE_TEMPLATE_TYPES
#define IONFLUX_TEMPLATE_TEMPLATE_TYPES
/* ==========================================================================
 * IFTemplate - Ionflux Template Processor
 * Copyright © 2012-2013 Jörn P. Meier
 * mail@ionflux.org
 * --------------------------------------------------------------------------
 * templatetypes.hpp                  Types used by Template (header).
 * =========================================================================
 *
 * This file is part of IFTemplate - Ionflux Template Processor.
 * 
 * IFTemplate - Ionflux Template Processor is free software; you can 
 * redistribute it and/or modify it under the terms of the GNU General 
 * Public License as published by the Free Software Foundation; either 
 * version 2 of the License, or (at your option) any later version.
 * 
 * IFTemplate - Ionflux Template Processor is distributed in the hope that it 
 * will be useful, but WITHOUT ANY WARRANTY; without even the implied 
 * warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See 
 * the GNU General Public License for more details.
 * 
 * You should have received a copy of the GNU General Public License along 
 * with IFTemplate - Ionflux Template Processor; if not, write to the Free 
 * Software Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA 
 * 02111-1307 USA
 * 
 * ========================================================================== */
#include <vector>
#include <map>
#include "ifobject/types.hpp"
#include "iftemplate/types.hpp"
#include "iftemplate/treetypes.hpp"

namespace Ionflux
{

namespace Template
{

class StringFilter;

/** Template variable.
 *
 * A template variable, consisting of a data entry and (optionally) a string 
 * filter.
 */
struct TemplateVar
{
	/// Data entry.
	Ionflux::Template::DataEntry data;
	/// String filter.
	Ionflux::Template::StringFilter* filter;
};

/// Vector of template variables.
typedef std::vector<Ionflux::Template::TemplateVar> TemplateVarVector;

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
	Ionflux::ObjectBase::StringVector params;
	/// Element variables.
	Ionflux::Template::TemplateVarVector vars;
	/// Element references.
	Ionflux::ObjectBase::IntVector refs;
	
	/// Element type: Invalid.
	static const int TE_INVALID = -1;
	/// Element type: Character data.
	static const int TE_CDATA = 0;
	/// Element type: Variable.
	static const int TE_VAR = 1;
	/// Element type: foreach block.
	static const int TE_FOREACH = 2;
	/// Element type: (foreach) else block.
	static const int TE_FOREACH_ELSE = 3;
	/// Element type: foreach block (end tag).
	static const int TE_FOREACH_END = 4;
	/// Element type: if block.
	static const int TE_IF = 5;
	/// Element type: (if) else block.
	static const int TE_IF_ELSE = 6;
	/// Element type: if block (end tag).
	static const int TE_IF_END = 7;
	/// Element type: first block.
	static const int TE_FIRST = 8;
	/// Element type: first block (end tag).
	static const int TE_FIRST_END = 9;
	/// Element type: mid block.
	static const int TE_MID = 10;
	/// Element type: mid block (end tag).
	static const int TE_MID_END = 11;
	/// Element type: last block.
	static const int TE_LAST = 12;
	/// Element type: last block (end tag).
	static const int TE_LAST_END = 13;
	/// Element type: single block.
	static const int TE_SINGLE = 14;
	/// Element type: single block (end tag).
	static const int TE_SINGLE_END = 15;
	/// Element type: notlast block.
	static const int TE_NOTLAST = 16;
	/// Element type: notlast block (end tag).
	static const int TE_NOTLAST_END = 17;
	/// Element type: notfirst block.
	static const int TE_NOTFIRST = 18;
	/// Element type: notfirst block (end tag).
	static const int TE_NOTFIRST_END = 19;
	/// Element type: notmid block.
	static const int TE_NOTMID = 20;
	/// Element type: notmid block (end tag).
	static const int TE_NOTMID_END = 21;
	/// Element type: notsingle block.
	static const int TE_NOTSINGLE = 22;
	/// Element type: notsingle block (end tag).
	static const int TE_NOTSINGLE_END = 23;
	/// Element type: include.
	static const int TE_INCLUDE = 24;
	/// Element type: swrap.
	static const int TE_SWRAP = 25;
	/// Element type: swrap (end tag).
	static const int TE_SWRAP_END = 26;
	/// Element type: section.
	static const int TE_SECTION = 27;
	/// Element type: section (end tag).
	static const int TE_SECTION_END = 28;
	/// Element type: ref.
	static const int TE_REF = 29;
	/// Element type: import.
	static const int TE_IMPORT = 30;
};

/// Vector of template variables.
typedef std::vector<Ionflux::Template::TemplateElement*> 
    TemplateElementVector;

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

//// Template section.
struct TemplateSection
{
	/// First template element of the section.
	unsigned int first;
	/// Last template element of the section.
	unsigned int last;
};

/// Map from section names to template sections.
typedef std::map<std::string, Ionflux::Template::TemplateSection> 
    TemplateSectionMap;

/// Repository entry type ID.
typedef int RepositoryEntryTypeID;

}

}

/** \file templatetypes.hpp
 * \brief Types used by Template (header).
 */
#endif
