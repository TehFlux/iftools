/* ==========================================================================
 * IFTemplate - Ionflux Template Processor
 * Copyright © 2012 Jörn P. Meier
 * mail@ionflux.org
 * --------------------------------------------------------------------------
 * Template.cpp                    Template (implementation).
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

#include "iftemplate/Template.hpp"
#include <iostream>
#include <iomanip>
#include <sstream>
#include "ifobject/utils.hpp"
#include "iftemplate/utils.hpp"
#include "iftemplate/IFTemplateError.hpp"
#include "iftemplate/Node.hpp"
#include "iftemplate/StringFilter.hpp"
#include "iftemplate/StringTrim.hpp"
#include "iftemplate/StringSWrap.hpp"
#include "iftemplate/TemplateRepository.hpp"

using namespace std;

namespace Ionflux
{

namespace Template
{

TemplateClassInfo::TemplateClassInfo()
{
	name = "Template";
	desc = "Template";
}

TemplateClassInfo::~TemplateClassInfo()
{
}

// public member constants
const std::string Template::ITERATION_COUNTER = "__i";
const std::string Template::NUM_ITERATIONS = "__n";
const std::string Template::CONDITION_NODE = "__cond";
const Ionflux::Template::TokenType Template::TT_TEMPLATE_TAG_OPEN = { TT_ID_USERTYPE + 101, "{", false, 1 };
const Ionflux::Template::TokenType Template::TT_TEMPLATE_TAG_CLOSE = { TT_ID_USERTYPE + 102, "}", false, 1 };
const Ionflux::Template::TokenType Template::TT_VAR_MARKER = { TT_ID_USERTYPE + 103, "$@", false, 1 };
const Ionflux::Template::TokenType Template::TT_COMMENT = { TT_ID_USERTYPE + 104, "#", false, 1 };
const Ionflux::Template::TokenType Template::TT_TREEPATH = { TT_ID_USERTYPE + 105, ".[]()", false, 0 };
const Ionflux::Template::TokenType Template::TT_END_TAG_MARKER = { TT_ID_USERTYPE + 106, "/", false, 0 };
const Ionflux::Template::TokenType Template::TT_OPERATOR_NSO = { TT_ID_USERTYPE + 107, "+-*=<>&!~%^", false, 0 };
const std::string Template::TAG_FOREACH = "foreach";
const std::string Template::TAG_FOREACH_ELSE = "empty";
const std::string Template::TAG_FOREACH_IN = "in";
const std::string Template::TAG_IF = "if";
const std::string Template::TAG_IF_ELSE = "else";
const std::string Template::TAG_FIRST = "first";
const std::string Template::TAG_MID = "mid";
const std::string Template::TAG_LAST = "last";
const std::string Template::TAG_SINGLE = "single";
const std::string Template::TAG_NOTFIRST = "notfirst";
const std::string Template::TAG_NOTMID = "notmid";
const std::string Template::TAG_NOTLAST = "notlast";
const std::string Template::TAG_NOTSINGLE = "notsingle";
const std::string Template::TAG_INCLUDE = "include";
const std::string Template::TAG_IMPORT = "import";
const std::string Template::TAG_SWRAP = "swrap";
const std::string Template::TAG_SECTION = "section";
const std::string Template::TAG_REF = "ref";
const std::string Template::SWRAP_DEFAULT_LINE_WIDTH = "78";
const std::string Template::SWRAP_DEFAULT_LINE_TERM = "\n";
const unsigned int Template::DEFAULT_MAX_NESTING_DEPTH = 999;

// run-time type information instance constants
const TemplateClassInfo Template::templateClassInfo;
const Ionflux::ObjectBase::IFClassInfo* Template::CLASS_INFO = &Template::templateClassInfo;

Template::Template()
: templateInput(""), maxNestingDepth(DEFAULT_MAX_NESTING_DEPTH), repository(0)
{
	// NOTE: The following line is required for run-time type information.
	theClass = CLASS_INFO;
	root->setAutoCreate(true);
	root->setIndexMode(Node::INDEX_MODE_NODE);
	initTokenTypes();
}

Template::Template(const Ionflux::Template::Template& other)
: templateInput(""), maxNestingDepth(DEFAULT_MAX_NESTING_DEPTH), repository(0)
{
	// NOTE: The following line is required for run-time type information.
	theClass = CLASS_INFO;
	*this = other;
}

Template::Template(const std::string& templateInput, 
Ionflux::Template::Node* initRoot, Ionflux::Template::TemplateRepository* 
initRepository)
: templateInput(""), maxNestingDepth(DEFAULT_MAX_NESTING_DEPTH), 
repository(0)
{
	// NOTE: The following line is required for run-time type information.
	theClass = CLASS_INFO;
	root->setAutoCreate(true);
	root->setIndexMode(Node::INDEX_MODE_NODE);
	initTokenTypes();
	if (templateInput.size() > 0)
	    setTemplate(templateInput);
	if (initRoot != 0)
	    setRoot(initRoot);
	if (initRepository != 0)
	    setRepository(initRepository);
}

Template::~Template()
{
	clearElements();
}

void Template::clearElements()
{
	for (unsigned int i = 0; i < elements.size(); i++)
	{
	    if (elements[i] != 0)
	    {
	        StringFilter* currentFilter = 0;
	        for (unsigned int k = 0; k < elements[i]->vars.size(); k++)
	        {
	            currentFilter = elements[i]->vars[k].filter;
	            if (currentFilter != 0)
	                removeLocalRef(currentFilter);
	            elements[i]->vars[k].filter = 0;
	        }
	        delete elements[i];
	    }
	    elements[i] = 0;
	}
	elements.clear();
	sections.clear();
}

void Template::initTokenTypes()
{
	tok.addTokenType(TT_TEMPLATE_TAG_OPEN);
	tok.addTokenType(TT_TEMPLATE_TAG_CLOSE);
	tok.addTokenType(TT_VAR_MARKER);
	tok.addTokenType(TT_COMMENT);
	tok.addTokenType(TT_TREEPATH);
	tok.addTokenType(TT_OPERATOR_NSO);
	tok.addTokenType(TT_END_TAG_MARKER);
	tok.addTokenType(StringFilter::TT_FUNC_SEP);
	tok.setExtractEscaped(true);
	tok.setTokenTypeAnything();
	tagTok.addTokenType(TT_VAR_MARKER);
	tagTok.addTokenType(TT_TREEPATH);
	tagTok.addTokenType(TT_OPERATOR_NSO);
	tagTok.addTokenType(TT_END_TAG_MARKER);
	tagTok.addTokenType(StringFilter::TT_FUNC_SEP);
	tagTok.setExtractQuoted(true);
	tagTok.setTokenTypeAnything();
}

bool Template::parse(Ionflux::Template::TemplateElementVector& target)
{
	/* <---- DEBUG ----- //
	std::cerr << "[Template::parse] DEBUG: "
	    "BEGIN" << std::endl;
	// ----- DEBUG ----> */
	std::ostringstream status;
	std::string currentData;
	int nestingLevel = 0;
	bool quoted;
	char quoteChar;
	bool error = false;
	std::string errorReason = "";
	tok.setInput(templateInput);
	Token currentToken = tok.getNextToken();
	unsigned int lineCount = 1;
	target.clear();
	bool startOfLine = true;
	while (isNonEmpty(currentToken) && !error)
	{
	    if (hasType(currentToken, TT_ESCAPED.typeID))
	    {
	        // Handle escaped character.
	        currentData.append(currentToken.value);
	        currentToken = tok.getNextToken();
	        startOfLine = false;
	    } else
	    if (startOfLine && hasType(currentToken, TT_COMMENT.typeID))
	    {
	        /* Handle comments.
	           Skip everything until end of line. */
	        while (isNonEmpty(currentToken) 
	            && !hasType(currentToken, TT_LINETERM.typeID))
	            currentToken = tok.getNextToken();
	        if (hasType(currentToken, TT_LINETERM.typeID) 
	            && hasCharValue(currentToken, '\r'))
	        {
	            /* This is a guess that we are on a system with strange line 
	               terminators, so skip an additional token. */
	            tok.getNextToken();
	        }
	        currentToken = tok.getNextToken();
	        lineCount++;
	        startOfLine = true;
	    } else
	    if (hasType(currentToken, TT_TEMPLATE_TAG_OPEN.typeID))
	    {
	        // Handle template tags.
	        addCharacterData(currentData, target);
	        currentData = "";
	        nestingLevel = 1;
	        quoted = false;
	        tok.setExtractQuoted(true);
	        currentToken = tok.getNextToken();
	        while (isNonEmpty(currentToken) 
	            && (nestingLevel > 0))
	        {
	            /* ----- DEBUG ----- //
	            cout << "[Template::parse] DEBUG: Current token value: "
	                << currentToken.value << endl;
	            // ----- DEBUG ----- */
	            if (hasType(currentToken, TT_QUOTED.typeID))
	            {
	                // Handle quoted string.
	                quoteChar = tok.getQuoteChar();
	                if (quoteChar != 0)
	                    // Preserve quotes.
	                    currentData.append(1, quoteChar);
	                currentData.append(currentToken.value);
	                if (quoteChar != 0)
	                    currentData.append(1, quoteChar);
	            } else
	            if (hasType(currentToken, TT_TEMPLATE_TAG_OPEN.typeID))
	            {
	                // Handle opening template tag marker.
	                if (!quoted)
	                    nestingLevel++;
	                currentData.append(currentToken.value);
	            } else
	            if (hasType(currentToken, TT_TEMPLATE_TAG_CLOSE.typeID))
	            {
	                // Handle closing template tag marker.
	                if (!quoted)
	                    nestingLevel--;
	                if (quoted || (nestingLevel > 0))
	                    currentData.append(currentToken.value);
	                tok.setExtractQuoted(false);
	            } else
	            {
	                // Append anything else.
	                currentData.append(currentToken.value);
	                if (hasType(currentToken, TT_LINETERM.typeID))
	                    lineCount++;
	            }
	            currentToken = tok.getNextToken();
	        }
	        if (nestingLevel == 0)
	        {
	            if (!addTemplateTag(currentData, target))
	            {
	                error = true;
	                errorReason = "Invalid template tag.";
	            }
	            currentData = "";
	        } else
	        {
	            error = true;
	            errorReason = "Unexpected end of template tag data. "
	                "(Mismatched markers?)";
	        }
	        tok.setExtractQuoted(false);
	        startOfLine = false;
	    } else
	    {
	        // Handle character data.
	        if (hasType(currentToken, TT_LINETERM.typeID) 
	            && (currentToken.value.size() > 0) 
	            && !hasCharValue(currentToken, '\r'))
	        {
	            lineCount++;
	            startOfLine = true;
	        } else
	            startOfLine = false;
	        currentData.append(currentToken.value);
	        currentToken = tok.getNextToken();
	    }
	}
	if (hasType(currentToken, TT_INVALID.typeID))
	{
	    errorReason = "Invalid Token.";
	    error = true;
	}
	if (error)
	{
	    status.str("");
	    status << "Parse error in line " << lineCount << " at token '" 
	        << currentToken.value << "'. (" << errorReason << ")";
	    throw IFTemplateError(status.str());
	} else
	{
	    // Add remaining character data as a new element.
	    addCharacterData(currentData, target);
	    currentData = "";
	}
	preprocess(target);
	/* <---- DEBUG ----- //
	std::cerr << "[Template::parse] DEBUG: "
	    "END" << std::endl;
	// ----- DEBUG ----> */
	return false;
}

bool Template::parse()
{
	clearElements();
	return parse(elements);
}

void Template::addCharacterData(const std::string& characterData, 
Ionflux::Template::TemplateElementVector& target)
{
	if (characterData == "")
	    return;
	TemplateElement* currentElement = 
	    Ionflux::ObjectBase::create<TemplateElement>(
	        "Template::addCharacterData", "template element");
	currentElement->type = TemplateElement::TE_CDATA;
	currentElement->params.push_back(characterData);
	target.push_back(currentElement);
}

bool Template::addTemplateTag(const std::string& tagData, 
Ionflux::Template::TemplateElementVector& target)
{
	if (tagData == "")
	    return true;
	tagTok.setInput(tagData);
	bool endTag = false;
	char quoteChar;
	Token currentToken = tagTok.getNextToken();
	// Skip leading whitespace.
	while (hasType(currentToken, TT_WHITESPACE.typeID))
	    currentToken = tagTok.getNextToken();
	// Set end tag flag.
	if (hasType(currentToken, TT_END_TAG_MARKER.typeID))
	{
	    endTag = true;
	    currentToken = tagTok.getNextToken();
	}
	// Determine type of tag and initialize appropriate element.
	if (hasType(currentToken, TT_VAR_MARKER.typeID) 
	    || hasType(currentToken, TT_TREEPATH.typeID))
	{
	    // Variable substitution tag.
	    string currentData = "";
	    currentToken = tagTok.getNextToken();
	    while (hasType(currentToken, TT_IDENTIFIER.typeID)
	        || hasType(currentToken, TT_TREEPATH.typeID)
	        || hasType(currentToken, TT_QUOTED.typeID)
	        || hasType(currentToken, TT_ESCAPED.typeID))
	    {
	        quoteChar = tagTok.getQuoteChar();
	        if (quoteChar != 0)
	            // Preserve quotes.
	            currentData.append(1, quoteChar);
	        currentData.append(currentToken.value);
	        if (quoteChar != 0)
	            currentData.append(1, quoteChar);
	        currentToken = tagTok.getNextToken();
	    }
	    // Skip trailing whitespace.
	    while (hasType(currentToken, TT_WHITESPACE.typeID))
	        currentToken = tagTok.getNextToken();
	    // Extract string filter or assignment expression.
	    string currentFilterExpr = "";
	    string currentAssignExpr = "";
	    if (hasType(currentToken, StringFilter::TT_FUNC_SEP.typeID))
	    {
	        tagTok.setExtractQuoted(false);
	        tagTok.setExtractEscaped(false);
	        currentToken = tagTok.getNextToken();
	        while (isNonEmpty(currentToken))
	        {
	            currentFilterExpr.append(currentToken.value);
	            currentToken = tagTok.getNextToken();
	        }
	        tagTok.setExtractQuoted(true);
	        tagTok.setExtractEscaped(true);
	    } else
	    if (hasType(currentToken, TT_OPERATOR_NSO.typeID)
	        && (currentToken.value == "="))
	    {
	        currentToken = tagTok.getNextToken();
	        /* Everything listed in the following while-condition is a 
	           valid part of a tree expression. */
	        while (hasType(currentToken, TT_IDENTIFIER.typeID)
	            || hasType(currentToken, TT_WHITESPACE.typeID)
	            || hasType(currentToken, StringFilter::TT_FUNC_SEP.typeID)
	            || hasType(currentToken, TT_TREEPATH.typeID)
	            || hasType(currentToken, TT_ESCAPED.typeID)
	            || hasType(currentToken, TT_QUOTED.typeID)
	            || hasType(currentToken, TT_OPERATOR_NSO.typeID)
	            || hasType(currentToken, TT_END_TAG_MARKER.typeID))
	        {
	            quoteChar = tagTok.getQuoteChar();
	            if (quoteChar != 0)
	                // Preserve quotes.
	                currentAssignExpr.append(1, quoteChar);
	            currentAssignExpr.append(currentToken.value);
	            if (quoteChar != 0)
	                currentAssignExpr.append(1, quoteChar);
	            currentToken = tagTok.getNextToken();
	        }
	    }
	    if (!hasType(currentToken, TT_NONE.typeID)
	        || (currentData == ""))
	        return false;
	    // Add template element.
	    TemplateVar currentVar;
	    currentVar.data.node = 0;
	    currentVar.data.index = 0;
	    if (currentFilterExpr != "")
	    {
	        currentVar.filter = Ionflux::ObjectBase::create1<StringFilter>(
	            currentFilterExpr, "Template::addTemplateTag", 
	                "string filter");
	        addLocalRef(currentVar.filter);
	    } else
	        currentVar.filter = 0;
	    TemplateElement* currentElement = 
	        Ionflux::ObjectBase::create<TemplateElement>(
	            "Template::addTemplateTag", "template element");
	    currentElement->type = TemplateElement::TE_VAR;
	    currentElement->params.push_back(tagData);
	    currentElement->params.push_back(currentData);
	    currentElement->params.push_back(currentAssignExpr);
	    currentElement->vars.push_back(currentVar);
	    target.push_back(currentElement);
	} else
	if (hasType(currentToken, TT_IDENTIFIER.typeID))
	{
	    // Control tag.
	    if (currentToken.value == TAG_FOREACH)
	    {
	        // Tag: foreach.
	        currentToken = tagTok.getNextToken();
	        if (!endTag)
	        {
	            /* foreach: Handle opening tag.
	               Skip leading whitespace. */
	            while (hasType(currentToken, TT_WHITESPACE.typeID))
	                currentToken = tagTok.getNextToken();
	            // Extract iterator.
	            string iteratorData;
	            while (hasType(currentToken, TT_IDENTIFIER.typeID)
	                || hasType(currentToken, TT_TREEPATH.typeID)
	                || hasType(currentToken, TT_ESCAPED.typeID)
	                || hasType(currentToken, TT_QUOTED.typeID))
	            {
	                quoteChar = tagTok.getQuoteChar();
	                if (quoteChar != 0)
	                    // Preserve quotes.
	                    iteratorData.append(1, quoteChar);
	                iteratorData.append(currentToken.value);
	                if (quoteChar != 0)
	                    iteratorData.append(1, quoteChar);
	                currentToken = tagTok.getNextToken();
	            }
	            // Skip enclosed whitespace.
	            while (hasType(currentToken, TT_WHITESPACE.typeID))
	                currentToken = tagTok.getNextToken();
	            // Expect 'in' keyword.
	            if (currentToken.value != TAG_FOREACH_IN)
	                return false;
	            currentToken = tagTok.getNextToken();
	            // Skip enclosed whitespace.
	            while (hasType(currentToken, TT_WHITESPACE.typeID))
	                currentToken = tagTok.getNextToken();
	            // Extract source.
	            string sourceData;
	            while (hasType(currentToken, TT_IDENTIFIER.typeID)
	                || hasType(currentToken, TT_TREEPATH.typeID)
	                || hasType(currentToken, TT_ESCAPED.typeID)
	                || hasType(currentToken, TT_QUOTED.typeID))
	            {
	                quoteChar = tagTok.getQuoteChar();
	                if (quoteChar != 0)
	                    // Preserve quotes.
	                    sourceData.append(1, quoteChar);
	                sourceData.append(currentToken.value);
	                if (quoteChar != 0)
	                    sourceData.append(1, quoteChar);
	                currentToken = tagTok.getNextToken();
	            }
	            // Skip trailing whitespace.
	            while (hasType(currentToken, TT_WHITESPACE.typeID))
	                currentToken = tagTok.getNextToken();
	            if (!hasType(currentToken, TT_NONE.typeID)
	                || (iteratorData == "") || (sourceData == ""))
	                return false;
	            // Add template element.
	            TemplateVar iteratorVar;
	            TemplateVar sourceVar;
	            iteratorVar.data.node = 0;
	            iteratorVar.data.index = 0;
	            sourceVar.data.node = 0;
	            sourceVar.data.index = 0;
	            iteratorVar.filter = 0;
	            sourceVar.filter = 0;
	            TemplateElement* currentElement = 
	            	Ionflux::ObjectBase::create<TemplateElement>(
	            		"Template::addTemplateTag", "template element");
	            currentElement->type = TemplateElement::TE_FOREACH;
	            currentElement->params.push_back(tagData);
	            currentElement->params.push_back(iteratorData);
	            currentElement->params.push_back(sourceData);
	            currentElement->vars.push_back(iteratorVar);
	            currentElement->vars.push_back(sourceVar);
	            target.push_back(currentElement);
	        } else
	        {
	            /* foreach: Handle end tag.
	               Skip trailing whitespace. */
	            while (hasType(currentToken, TT_WHITESPACE.typeID))
	                currentToken = tagTok.getNextToken();
	            if (!hasType(currentToken, TT_NONE.typeID))
	                return false;
	            // Add template element.
	            TemplateElement* currentElement = 
	            	Ionflux::ObjectBase::create<TemplateElement>(
	            		"Template::addTemplateTag", "template element");
	            currentElement->type = TemplateElement::TE_FOREACH_END;
	            currentElement->params.push_back(tagData);
	            target.push_back(currentElement);
	        }
	    } else
	    if (currentToken.value == TAG_FOREACH_ELSE)
	    {
	        // Tag: (foreach) else.
	        currentToken = tagTok.getNextToken();
	        if (!endTag)
	        {
	            /* (foreach) else: Handle tag.
	               Skip trailing whitespace. */
	            while (hasType(currentToken, TT_WHITESPACE.typeID))
	                currentToken = tagTok.getNextToken();
	            if (!hasType(currentToken, TT_NONE.typeID))
	                return false;
	            // Add template element.
	            TemplateElement* currentElement = 
	            	Ionflux::ObjectBase::create<TemplateElement>(
	            		"Template::addTemplateTag", "template element");
	            currentElement->type = TemplateElement::TE_FOREACH_ELSE;
	            currentElement->params.push_back(tagData);
	            target.push_back(currentElement);
	        } else
	            // (foreach) else does not have an end tag.
	            return false;
	    } else
	    if (currentToken.value == TAG_IF)
	    {
	        // Tag: if.
	        currentToken = tagTok.getNextToken();
	        if (!endTag)
	        {
	            /* if: Handle opening tag.
	               Skip leading whitespace. */
	            while (hasType(currentToken, TT_WHITESPACE.typeID))
	                currentToken = tagTok.getNextToken();
	            // Extract if-condition.
	            string conditionData;
	            /* Everything listed in the following while-condition is a 
	               valid part of a tree expression. */
	            while (hasType(currentToken, TT_IDENTIFIER.typeID)
	                || hasType(currentToken, TT_WHITESPACE.typeID)
	                || hasType(currentToken, StringFilter::TT_FUNC_SEP.typeID)
	                || hasType(currentToken, TT_TREEPATH.typeID)
	                || hasType(currentToken, TT_ESCAPED.typeID)
	                || hasType(currentToken, TT_QUOTED.typeID)
	                || hasType(currentToken, TT_OPERATOR_NSO.typeID)
	                || hasType(currentToken, TT_END_TAG_MARKER.typeID))
	            {
	                quoteChar = tagTok.getQuoteChar();
	                if (quoteChar != 0)
	                    // Preserve quotes.
	                    conditionData.append(1, quoteChar);
	                conditionData.append(currentToken.value);
	                if (quoteChar != 0)
	                    conditionData.append(1, quoteChar);
	                currentToken = tagTok.getNextToken();
	            }
	            if (!hasType(currentToken, TT_NONE.typeID))
	                return false;
	            // Add template element.
	            TemplateElement* currentElement = 
	            	Ionflux::ObjectBase::create<TemplateElement>(
	            		"Template::addTemplateTag", "template element");
	            currentElement->type = TemplateElement::TE_IF;
	            currentElement->params.push_back(tagData);
	            currentElement->params.push_back(conditionData);
	            target.push_back(currentElement);
	        } else
	        {
	            /* if: Handle end tag.
	               Skip trailing whitespace. */
	            while (hasType(currentToken, TT_WHITESPACE.typeID))
	                currentToken = tagTok.getNextToken();
	            if (!hasType(currentToken, TT_NONE.typeID))
	                return false;
	            // Add template element.
	            TemplateElement* currentElement = 
	            	Ionflux::ObjectBase::create<TemplateElement>(
	            		"Template::addTemplateTag", "template element");
	            currentElement->type = TemplateElement::TE_IF_END;
	            currentElement->params.push_back(tagData);
	            target.push_back(currentElement);
	        }
	    } else
	    if (currentToken.value == TAG_IF_ELSE)
	    {
	        // Tag: (if) else.
	        currentToken = tagTok.getNextToken();
	        if (!endTag)
	        {
	            /* (if) else: Handle tag.
	               Skip trailing whitespace. */
	            while (hasType(currentToken, TT_WHITESPACE.typeID))
	                currentToken = tagTok.getNextToken();
	            if (!hasType(currentToken, TT_NONE.typeID))
	                return false;
	            // Add template element.
	            TemplateElement* currentElement = 
	            	Ionflux::ObjectBase::create<TemplateElement>(
	            		"Template::addTemplateTag", "template element");
	            currentElement->type = TemplateElement::TE_IF_ELSE;
	            currentElement->params.push_back(tagData);
	            target.push_back(currentElement);
	        } else
	            // (if) else does not have an end tag.
	            return false;
	    } else
	    if ((currentToken.value == TAG_FIRST)
	        || (currentToken.value == TAG_MID)
	        || (currentToken.value == TAG_LAST)
	        || (currentToken.value == TAG_SINGLE)
	        || (currentToken.value == TAG_NOTFIRST)
	        || (currentToken.value == TAG_NOTMID)
	        || (currentToken.value == TAG_NOTLAST)
	        || (currentToken.value == TAG_NOTSINGLE))
	    {
	        // Tag: Foreach special blocks.
	        int elementOpenType = TemplateElement::TE_INVALID;
	        int elementCloseType = TemplateElement::TE_INVALID;
	        if (currentToken.value == TAG_FIRST)
	        {
	            elementOpenType = TemplateElement::TE_FIRST;
	            elementCloseType = TemplateElement::TE_FIRST_END;
	        } else
	        if (currentToken.value == TAG_MID)
	        {
	            elementOpenType = TemplateElement::TE_MID;
	            elementCloseType = TemplateElement::TE_MID_END;
	        } else
	        if (currentToken.value == TAG_LAST)
	        {
	            elementOpenType = TemplateElement::TE_LAST;
	            elementCloseType = TemplateElement::TE_LAST_END;
	        } else
	        if (currentToken.value == TAG_SINGLE)
	        {
	            elementOpenType = TemplateElement::TE_SINGLE;
	            elementCloseType = TemplateElement::TE_SINGLE_END;
	        } else
	        if (currentToken.value == TAG_NOTFIRST)
	        {
	            elementOpenType = TemplateElement::TE_NOTFIRST;
	            elementCloseType = TemplateElement::TE_NOTFIRST_END;
	        } else
	        if (currentToken.value == TAG_NOTMID)
	        {
	            elementOpenType = TemplateElement::TE_NOTMID;
	            elementCloseType = TemplateElement::TE_NOTMID_END;
	        } else
	        if (currentToken.value == TAG_NOTLAST)
	        {
	            elementOpenType = TemplateElement::TE_NOTLAST;
	            elementCloseType = TemplateElement::TE_NOTLAST_END;
	        } else
	        if (currentToken.value == TAG_NOTSINGLE)
	        {
	            elementOpenType = TemplateElement::TE_NOTSINGLE;
	            elementCloseType = TemplateElement::TE_NOTSINGLE_END;
	        }
	        currentToken = tagTok.getNextToken();
	        if (!endTag)
	        {
	            /* Foreach special block tag: Handle opening tag.
	               Skip trailing whitespace. */
	            while (hasType(currentToken, TT_WHITESPACE.typeID))
	                currentToken = tagTok.getNextToken();
	            if (!hasType(currentToken, TT_NONE.typeID))
	                return false;
	            TemplateElement* currentElement = 
	            	Ionflux::ObjectBase::create<TemplateElement>(
	            		"Template::addTemplateTag", "template element");
	            currentElement->type = elementOpenType;
	            currentElement->params.push_back(tagData);
	            target.push_back(currentElement);
	        } else
	        {
	            /* Foreach special block tag: Handle end tag.
	               Skip trailing whitespace. */
	            while (hasType(currentToken, TT_WHITESPACE.typeID))
	                currentToken = tagTok.getNextToken();
	            if (!hasType(currentToken, TT_NONE.typeID))
	                return false;
	            // Add template element.
	            TemplateElement* currentElement = 
	            	Ionflux::ObjectBase::create<TemplateElement>(
	            		"Template::addTemplateTag", "template element");
	            currentElement->type = elementCloseType;
	            currentElement->params.push_back(tagData);
	            target.push_back(currentElement);
	        }
	    } else
	    if (currentToken.value == TAG_INCLUDE)
	    {
	        // Tag: include.
	        currentToken = tagTok.getNextToken();
	        if (!endTag)
	        {
	            /* include: Handle tag.
	               Skip leading whitespace. */
	            while (hasType(currentToken, TT_WHITESPACE.typeID))
	                currentToken = tagTok.getNextToken();
	            // Extract filename.
	            string includeFile;
	            while (isNonEmpty(currentToken))
	            {
	                includeFile.append(currentToken.value);
	                currentToken = tagTok.getNextToken();
	            }
	            if (!hasType(currentToken, TT_NONE.typeID))
	                return false;
	            // Remove leading and trailing whitespace.
	            StringManipulator::StringTrim trim;
	            includeFile = trim.process(includeFile, 0);
	            // Add template element.
	            TemplateElement* currentElement = 
	            	Ionflux::ObjectBase::create<TemplateElement>(
	            		"Template::addTemplateTag", "template element");
	            currentElement->type = TemplateElement::TE_INCLUDE;
	            currentElement->params.push_back(tagData);
	            currentElement->params.push_back(includeFile);
	            target.push_back(currentElement);
	        } else
	            // include does not have an end tag.
	            return false;
	    } else
	    if (currentToken.value == TAG_IMPORT)
	    {
	        // Tag: import.
	        currentToken = tagTok.getNextToken();
	        if (!endTag)
	        {
	            /* import: Handle tag.
	               Skip leading whitespace. */
	            while (hasType(currentToken, TT_WHITESPACE.typeID))
	                currentToken = tagTok.getNextToken();
	            // Extract module path.
	            std::string modulePath;
	            while (isNonEmpty(currentToken))
	            {
	                modulePath.append(currentToken.value);
	                currentToken = tagTok.getNextToken();
	            }
	            if (!hasType(currentToken, TT_NONE.typeID))
	                return false;
	            // Remove leading and trailing whitespace.
	            StringManipulator::StringTrim trim;
	            modulePath = trim.process(modulePath, 0);
	            /* <---- DEBUG ----- //
	            std::cerr << "[Template::parse] DEBUG: "
	                "Parsing 'import' tag: modulePath = " << modulePath 
	                << std::endl;
	            // ----- DEBUG ----> */
	            // Add template element.
	            TemplateElement* currentElement = 
	            	Ionflux::ObjectBase::create<TemplateElement>(
	            		"Template::addTemplateTag", "template element");
	            currentElement->type = TemplateElement::TE_IMPORT;
	            currentElement->params.push_back(tagData);
	            currentElement->params.push_back(modulePath);
	            target.push_back(currentElement);
	        } else
	            // import does not have an end tag.
	            return false;
	    } else
	    if (currentToken.value == TAG_SWRAP)
	    {
	        // Tag: swrap.
	        currentToken = tagTok.getNextToken();
	        if (!endTag)
	        {
	            // swrap: Handle opening tag.
	            while (hasType(currentToken, TT_WHITESPACE.typeID))
	                currentToken = tagTok.getNextToken();
	            string lineWidth;
	            string prefix;
	            string lineTerm;
	            // Extract line width.
	            while (hasType(currentToken, TT_IDENTIFIER.typeID)
	                || hasType(currentToken, TT_QUOTED.typeID))
	            {
	                lineWidth.append(currentToken.value);
	                currentToken = tagTok.getNextToken();
	            }
	            while (hasType(currentToken, TT_WHITESPACE.typeID))
	                currentToken = tagTok.getNextToken();
	            // Extract prefix.
	            while (hasType(currentToken, TT_IDENTIFIER.typeID)
	                || hasType(currentToken, TT_QUOTED.typeID))
	            {
	                prefix.append(currentToken.value);
	                currentToken = tagTok.getNextToken();
	            }
	            while (hasType(currentToken, TT_WHITESPACE.typeID))
	                currentToken = tagTok.getNextToken();
	            // Extract line terminator.
	            while (hasType(currentToken, TT_IDENTIFIER.typeID)
	                || hasType(currentToken, TT_QUOTED.typeID))
	            {
	                lineTerm.append(currentToken.value);
	                currentToken = tagTok.getNextToken();
	            }
	            while (hasType(currentToken, TT_WHITESPACE.typeID))
	                currentToken = tagTok.getNextToken();
	            if (!hasType(currentToken, TT_NONE.typeID))
	                return false;
	            // Add template element.
	            TemplateElement* currentElement = 
	            	Ionflux::ObjectBase::create<TemplateElement>(
	            		"Template::addTemplateTag", "template element");
	            currentElement->type = TemplateElement::TE_SWRAP;
	            currentElement->params.push_back(tagData);
	            currentElement->params.push_back(lineWidth);
	            currentElement->params.push_back(prefix);
	            currentElement->params.push_back(lineTerm);
	            target.push_back(currentElement);
	        } else
	        {
	            // swrap: Handle end tag.
	            while (hasType(currentToken, TT_WHITESPACE.typeID))
	                currentToken = tagTok.getNextToken();
	            if (!hasType(currentToken, TT_NONE.typeID))
	                return false;
	            // Add template element.
	            TemplateElement* currentElement = 
	            	Ionflux::ObjectBase::create<TemplateElement>(
	            		"Template::addTemplateTag", "template element");
	            currentElement->type = TemplateElement::TE_SWRAP_END;
	            currentElement->params.push_back(tagData);
	            target.push_back(currentElement);
	        }
	    } else
	    if (currentToken.value == TAG_SECTION)
	    {
	        // Tag: section.
	        currentToken = tagTok.getNextToken();
	        if (!endTag)
	        {
	            // section: Handle opening tag.
	            while (hasType(currentToken, TT_WHITESPACE.typeID))
	                currentToken = tagTok.getNextToken();
	            string sectionName;
	            // Extract section name.
	            while (hasType(currentToken, TT_IDENTIFIER.typeID)
	                || hasType(currentToken, TT_QUOTED.typeID))
	            {
	                sectionName.append(currentToken.value);
	                currentToken = tagTok.getNextToken();
	            }
	            while (hasType(currentToken, TT_WHITESPACE.typeID))
	                currentToken = tagTok.getNextToken();
	            if (!hasType(currentToken, TT_NONE.typeID))
	                return false;
	            // Add template element.
	            TemplateElement* currentElement = 
	            	Ionflux::ObjectBase::create<TemplateElement>(
	            		"Template::addTemplateTag", "template element");
	            currentElement->type = TemplateElement::TE_SECTION;
	            currentElement->params.push_back(sectionName);
	            target.push_back(currentElement);
	        } else
	        {
	            // section: Handle end tag.
	            while (hasType(currentToken, TT_WHITESPACE.typeID))
	                currentToken = tagTok.getNextToken();
	            if (!hasType(currentToken, TT_NONE.typeID))
	                return false;
	            // Add template element.
	            TemplateElement* currentElement = 
	            	Ionflux::ObjectBase::create<TemplateElement>(
	            		"Template::addTemplateTag", "template element");
	            currentElement->type = TemplateElement::TE_SECTION_END;
	            currentElement->params.push_back(tagData);
	            target.push_back(currentElement);
	        }
	    } else
	    if (currentToken.value == TAG_REF)
	    {
	        // Tag: ref.
	        currentToken = tagTok.getNextToken();
	        if (!endTag)
	        {
	            /* ref: Handle tag.
	               Skip leading whitespace. */
	            while (hasType(currentToken, TT_WHITESPACE.typeID))
	                currentToken = tagTok.getNextToken();
	            // Extract reference name.
	            string refName;
	            while (hasType(currentToken, TT_IDENTIFIER.typeID)
	                || hasType(currentToken, TT_QUOTED.typeID))
	            {
	                refName.append(currentToken.value);
	                currentToken = tagTok.getNextToken();
	            }
	            while (hasType(currentToken, TT_WHITESPACE.typeID))
	                currentToken = tagTok.getNextToken();
	            // Extract restore switch.
	            string refRestore;
	            if (hasType(currentToken, TT_IDENTIFIER.typeID))
	            {
	                refRestore = currentToken.value;
	                currentToken = tagTok.getNextToken();
	            }
	            if (!hasType(currentToken, TT_NONE.typeID))
	                return false;
	            // Add template element.
	            TemplateElement* currentElement = 
	            	Ionflux::ObjectBase::create<TemplateElement>(
	            		"Template::addTemplateTag", "template element");
	            currentElement->type = TemplateElement::TE_REF;
	            currentElement->params.push_back(tagData);
	            currentElement->params.push_back(refName);
	            currentElement->params.push_back(refRestore);
	            target.push_back(currentElement);
	        } else
	            // ref does not have an end tag.
	            return false;
	    } else
	        // Unknown tag.
	        return false;
	} else
	    // Invalid token.
	    return false;
	return true;
}

bool Template::preprocess(Ionflux::Template::TemplateElementVector& target)
{
	/* <---- DEBUG ----- //
	std::cerr << "[Template::preprocess] DEBUG: "
	    "BEGIN" << std::endl;
	// ----- DEBUG ----> */
	if (target.size() == 0)
	    return true;
	bool error = false;
	unsigned int i = 0;
	TemplateElementVector result;
	TemplateElementVector trash;
	TemplateElementVector temp;
	TemplateElement* currentElement = 0;
	while (!error && (i < target.size()))
	{
	    currentElement = target[i];
	    if (currentElement != 0)
	    {
	        if (currentElement->type == TemplateElement::TE_INCLUDE)
	        {
	            // include tag
	            if (currentElement->params.size() >= 2)
	            {
	                temp.clear();
	                std::string includeFile = currentElement->params[1];
	                Template* includeTemplate = Template::create(this);
	                if (repository != 0)
	                    includeTemplate->setRepository(repository);
	                includeTemplate->readTemplate(includeFile, temp);
	                for (unsigned int k = 0; k < temp.size(); k++)
	                    result.push_back(temp[k]);
	                removeLocalRef(includeTemplate);
	            }
	            trash.push_back(currentElement);
	        } else
	        if (currentElement->type == TemplateElement::TE_IMPORT)
	        {
	            // import tag
	            if (repository == 0)
	                throw IFTemplateError(getErrorString(
	                    "'import' tag used but no repository "
	                    "has been defined", "preprocess"));
	            if (currentElement->params.size() >= 2)
	            {
	                temp.clear();
	                std::string modulePath = currentElement->params[1];
	                /* <---- DEBUG ----- //
	                std::cerr << "[Template::preprocess] DEBUG: "
	                    "Processing 'import' tag: modulePath = " 
	                    << modulePath << std::endl;
	                // ----- DEBUG ----> */
	                std::string tplData = 
	repository->getTemplateData(modulePath);
	                Template* includeTemplate = Template::create(this);
	                if (repository != 0)
	                    includeTemplate->setRepository(repository);
	                includeTemplate->setTemplate(tplData, temp);
	                for (unsigned int k = 0; k < temp.size(); k++)
	                    result.push_back(temp[k]);
	                removeLocalRef(includeTemplate);
	            }
	            trash.push_back(currentElement);
	        } else
	            result.push_back(currentElement);
	    }
	    i++;
	}
	target.clear();
	// Copy resulting elements back to target vector.
	for (unsigned int k = 0; k < result.size(); k++)
	    target.push_back(result[k]);
	// Delete elements that have been removed during preprocessing.
	for (unsigned int k = 0; k < trash.size(); k++)
	{
	    if (trash[k] != 0)
	        delete trash[k];
	    trash[k] = 0;
	}
	/* <---- DEBUG ----- //
	std::cerr << "[Template::preprocess] DEBUG: "
	    "END" << std::endl;
	// ----- DEBUG ----> */
	return !error;
}

std::string Template::process(unsigned int from, unsigned int to, 
Ionflux::Template::TagNestingLevel depth)
{
	std::ostringstream status;
	if (depth.all > maxNestingDepth)
	{
	    status.str("");
	    status << "[Template::process] Current nesting depth "
	        << depth.all << " exceeds maximum allowed nesting depth " 
	        << maxNestingDepth << ". (Use setMaxNestingDepth() to set "
	        "a higher limit.)";
	    throw IFTemplateError(status.str());
	}
	if ((from > to) || (from < 0) || (to >= elements.size()))
	{
	    status.str("");
	    status << "[Template::process] Invalid template element range ("
	        << from << ", " << to << ").";
	    throw IFTemplateError(status.str());
	}
	string result;
	TemplateElement* currentElement = 0;
	Node* currentNode = 0;
	int currentIndex;
	StringFilter* currentFilter;
	string currentData;
	string currentAssignExpr;
	int currentRef = 0;
	int currentCondition = 0;
	int nestingLevel = 0;
	int iterCount;
	int numIter;
	int iterationsTotal;
	TagNestingLevel newDepth;
	Node* iteratorNode = 0;
	Node* sourceNode = 0;
	Node* iterationCounter = 0;
	Node* numIterations = 0;
	Node* conditionNode = 0;
	TemplateElement* openTag = 0;
	StringManipulator::StringSWrap swrap;
	Ionflux::ObjectBase::StringVector swrapArgs;
	string prefix;
	string lineWidth;
	string lineTerm;
	TemplateSection currentSection;
	TemplateSectionMap::iterator sectionIter;
	Node saveConfig;
	saveConfig.setAutoCreate(true);
	saveConfig.setIndexMode(Node::INDEX_MODE_NODE);
	bool sectionRestore = false;
	for (unsigned int i = from; i <= to; i++)
	{
	    currentElement = elements[i];
	    if (currentElement != 0)
	    {
	        switch (currentElement->type)
	        {
	            case TemplateElement::TE_CDATA:
	                // Character data.
	                if (nestingLevel > 0)
	                    break;
	                if (currentElement->params.size() > 0)
	                    result.append(currentElement->params[0]);
	                break;
	            case TemplateElement::TE_VAR:
	                // Variable substitution.
	                if (nestingLevel > 0)
	                    break;
	                if ((currentElement->vars.size() > 0)
	                    && (currentElement->params.size() > 2))
	                {
	                    /* Resolve node.
	                       This is necessary at this point because node 
	                       references may be invalid if nodes are re-assigned 
	                       during the template processing (applies to iterator
	
                       variables especially). 
	                       TODO: Find a more elegant solution to this issue. 
	*/
	                    currentElement->vars[0].data = resolve(
	                        currentElement->params[1], false);
	                    currentAssignExpr = currentElement->params[2];
	                    currentNode = currentElement->vars[0].data.node;
	                    currentIndex = currentElement->vars[0].data.index;
	                    currentFilter = currentElement->vars[0].filter;
	                    if (currentNode != 0)
	                    {
	                        if (currentAssignExpr.size() == 0)
	                        {
	                            // Variable substitution.
	                            currentData = 
	currentNode->getData(currentIndex);
	                            if (currentFilter != 0)
	                                currentData = 
	                                    currentFilter->apply(currentData);
	                            result.append(currentData);
	                        } else
	                        {
	                            // Assignment.
	                            Node evalResult;
	                            evalResult.setAutoCreate(true);
	                            eval(currentAssignExpr, evalResult, false);
	                            currentNode->setData(currentIndex, 
	                                evalResult.getData());
	                        }
	                    }
	                } else
	                {
	                    throw IFTemplateError("[Template::process] "
	                        "Variable substitution: Missing variable or "
	                        "parameter.");
	                }
	                break;
	            case TemplateElement::TE_FOREACH:
	                // foreach.
	                nestingLevel++;
	                if (nestingLevel == 1)
	                {
	                    currentRef = i;
	                    openTag = elements[currentRef];
	                    openTag->refs.clear();
	                    openTag->refs.push_back(i);
	                }
	                break;
	            case TemplateElement::TE_FOREACH_ELSE:
	                // (foreach) else.
	                if (nestingLevel > 1)
	                    break;
	                openTag = elements[currentRef];
	                if (openTag == 0)
	                {
	                    throw IFTemplateError("[Template::process] "
	                        "foreach: Invalid opening tag.");
	                }
	                if (openTag->type != TemplateElement::TE_FOREACH)
	                    break;
	                openTag->refs.push_back(i);
	                break;
	            case TemplateElement::TE_FOREACH_END:
	                // foreach (end tag).
	                nestingLevel--;
	                if (nestingLevel > 0)
	                    break;
	                openTag = elements[currentRef];
	                if (openTag == 0) 
	                {
	                    throw IFTemplateError("[Template::process] "
	                        "foreach: Invalid opening tag.");
	                }
	                if (openTag->type != TemplateElement::TE_FOREACH)
	                {
	                    throw IFTemplateError("[Template::process] "
	                        "foreach: Mismatched tag.");
	                }
	                if (openTag->vars.size() < 2)
	                {
	                    throw IFTemplateError("[Template::process] "
	                        "foreach: Missing arguments.");
	                }
	                openTag->refs.push_back(i);
	                // Resolve iterator variables (see above).
	                openTag->vars[0].data = resolve(
	                    openTag->params[1], false);
	                openTag->vars[1].data = resolve(
	                    openTag->params[2], false);
	                iteratorNode = openTag->vars[0].data.node;
	                sourceNode = openTag->vars[1].data.node;
	                if ((iteratorNode == 0) || (sourceNode == 0))
	                {
	                    throw IFTemplateError("[Template::process] "
	                        "foreach: Invalid arguments.");
	                }
	                // Data iteration.
	                iterCount = 0;
	                iterationCounter = root->findChild(
	                    ITERATION_COUNTER, false);
	                if (iterationCounter == 0)
	                    throw IFTemplateError("[Template::process] "
	                        "Iteration counter is null.");
	                iterationCounter->setDataType(Node::DATA_INT);
	                numIterations = root->findChild(
	                    NUM_ITERATIONS, false);
	                if (numIterations == 0)
	                    throw IFTemplateError("[Template::process] "
	                        "Number of iterations node  is null.");
	                iterationsTotal = sourceNode->getNumData()
	                        + sourceNode->getNumChildren();
	                numIterations->setDataType(Node::DATA_INT);
	                numIterations->setData(depth.tagForeach, iterationsTotal);
	                newDepth = depth;
	                newDepth.tagForeach += 1;
	                newDepth.all += 1;
	                if ((iterationsTotal == 0)
	                    && (openTag->refs.size() >= 3))
	                {
	                    // No iterations, process (foreach) else block.
	                    /* ----- DEBUG ----- //
	                    cerr << "[Template::process] DEBUG: "
	                        "Processing foreach 'empty' block (openTag has "
	                        << openTag->refs.size() << " refs)." << endl;
	                    // ----- DEBUG ----- */
	                    result.append(process(openTag->refs[1] + 1, 
	                        openTag->refs[2] - 1, newDepth));
	                } else
	                if (iterationsTotal > 0)
	                {
	                    /* ----- DEBUG ----- //
	                    cerr << "[Template::process] DEBUG: "
	                        "Processing foreach main block." << endl;
	                    // ----- DEBUG ----- */
	                    unsigned int blockStart = currentRef + 1;
	                    unsigned int blockEnd = i - 1;
	                    if (openTag->refs.size() >= 3)
	                        blockEnd = openTag->refs[1] - 1;
	                    // Use a temporary node to preserve original data.
	                    /* ----- TESTING ----- //
	                    Node tempNode;
	                    tempNode.setAutoCreate(true);
	                    tempNode.setIndexMode(Node::INDEX_MODE_NODE);
	                    // ----- TESTING ----- */
	                    /* ----- DEBUG ----- //
	                    cerr << "[Template::process] DEBUG: (foreach) "
	                        "Saving source node..." << endl;
	                    // ----- DEBUG ----- */
	                    /* ----- TESTING ----- //
	                    tempNode = *sourceNode;
	                    // ----- TESTING ----- */
	                    /* ----- DEBUG ----- //
	                    cerr << "[Template::process] DEBUG: (foreach) "
	                        "Finished saving source node." << endl;
	                    // ----- DEBUG ----- */
	                    /* ----- DEBUG ----- //
	                    cerr << "[Template::process] DEBUG: (foreach) "
	                        "Source node: " << endl
	                        << tempNode.toConfig("    ") << endl;
	                    // ----- DEBUG ----- */
	                    /* ----- DEBUG ----- //
	                    cerr << "[Template::process] DEBUG: (foreach) "
	                        "Processing iterations." << endl;
	                    // ----- DEBUG ----- */
	                    for (unsigned int k = 0; 
	                        k < sourceNode->getNumData(); k++)
	                    {
	                        iterationCounter->setData(depth.tagForeach, 
	                            iterCount);
	                        iteratorNode->setData(0, sourceNode->getData(k));
	                        result.append(process(blockStart, blockEnd, 
	                            newDepth));
	                        iterCount++;
	                    }
	                    // Child node iteration.
	                    for (unsigned int k = 0; 
	                        k < sourceNode->getNumChildren(); k++)
	                    {
	                        iterationCounter = root->findChild(
	                            ITERATION_COUNTER, false);
	                        iterationCounter->setData(depth.tagForeach, 
	                            iterCount);
	                        // See below.
	                        openTag->vars[0].data = resolve(
	                            openTag->params[1], false);
	                        iteratorNode = openTag->vars[0].data.node;
	                        *iteratorNode = *sourceNode->getChild(k);
	                        result.append(process(blockStart, blockEnd, 
	                            newDepth));
	                        iterCount++;
	                    }
	                    /* ----- DEBUG ----- //
	                    cerr << "[Template::process] DEBUG: (foreach) "
	                        "Restoring source node..." << endl;
	                    // ----- DEBUG ----- */
	                    /* The source node needs to be resolved again before 
	                       it can be restored, since it might have been a 
	                       child node which has been re-allocated during an 
	                       iterator assignment. */
	                    /* ----- TESTING ----- //
	                    openTag->vars[1].data = resolve(
	                        openTag->params[2], false);
	                    sourceNode = openTag->vars[1].data.node;
	                    *sourceNode = tempNode;
	                    // ----- TESTING ----- */
	                    /* ----- DEBUG ----- //
	                    cerr << "[Template::process] DEBUG: (foreach) "
	                        "Finished restoring source node." << endl;
	                    // ----- DEBUG ----- */
	                }
	                break;
	            case TemplateElement::TE_IF:
	                // if.
	                nestingLevel++;
	                if (nestingLevel != 1)
	                    break;
	                currentRef = i;
	                openTag = elements[currentRef];
	                openTag->refs.clear();
	                if (currentElement->params.size() < 2)
	                {
	                    throw IFTemplateError("[Template::process] "
	                        "if: Missing arguments.");
	                }
	                conditionNode = root->findChild(
	                    CONDITION_NODE, false);
	                conditionNode->setDataType(Node::DATA_INT);
	                if (conditionNode == 0)
	                    throw IFTemplateError("[Template::process] "
	                        "Condition node is null.");
	                eval(currentElement->params[1], 
	                    (*conditionNode)[depth.tagIf], false);
	                if (((*conditionNode)[depth.tagIf].getDataType() 
	                        != Node::DATA_INT)
	                    && ((*conditionNode)[depth.tagIf].getDataType() 
	                        != Node::DATA_DOUBLE))
	                {
	                    throw IFTemplateError("[Template::process] "
	                        "if: Condition does not evaluate to numeric "
	                        "value.");
	                }
	                currentCondition = (*conditionNode)[depth.tagIf].getInt();
	                break;
	            case TemplateElement::TE_IF_ELSE:
	                // (if) else.
	                if (nestingLevel > 1)
	                    break;
	                openTag = elements[currentRef];
	                if (openTag == 0)
	                {
	                    throw IFTemplateError("[Template::process] "
	                        "if: Invalid opening tag.");
	                }
	                if (openTag->type != TemplateElement::TE_IF)
	                    break;
	                openTag->refs.push_back(i);
	                newDepth = depth;
	                newDepth.tagIf += 1;
	                newDepth.all += 1;
	                if (currentCondition)
	                    result.append(process(currentRef + 1, i - 1, 
	                        newDepth));
	                currentRef = i;
	                currentCondition = !currentCondition;
	                break;
	            case TemplateElement::TE_IF_END:
	                // if (end tag)
	                nestingLevel--;
	                if (nestingLevel > 0)
	                    break;
	                openTag = elements[currentRef];
	                if (openTag == 0) 
	                {
	                    throw IFTemplateError("[Template::process] "
	                        "if: Invalid tag.");
	                }
	                if ((openTag->type != TemplateElement::TE_IF)
	                    && (openTag->type != TemplateElement::TE_IF_ELSE))
	                {
	                    throw IFTemplateError("[Template::process] "
	                        "if: Mismatched tag.");
	                }
	                openTag->refs.push_back(i);
	                newDepth = depth;
	                newDepth.tagIf += 1;
	                newDepth.all += 1;
	                if (currentCondition)
	                    result.append(process(currentRef + 1, i - 1, 
	                        newDepth));
	                break;
	            case TemplateElement::TE_FIRST:
	                // first.
	                nestingLevel++;
	                if (nestingLevel == 1)
	                    currentRef = i;
	                break;
	            case TemplateElement::TE_FIRST_END:
	                // first (end tag).
	                nestingLevel--;
	                if (nestingLevel > 0)
	                    break;
	                openTag = elements[currentRef];
	                if (openTag == 0) 
	                {
	                    throw IFTemplateError("[Template::process] "
	                        "first: Invalid tag.");
	                }
	                if (openTag->type != TemplateElement::TE_FIRST)
	                {
	                    throw IFTemplateError("[Template::process] "
	                        "first: Mismatched tag.");
	                }
	                iterationCounter = root->findChild(
	                    ITERATION_COUNTER, false);
	                if (iterationCounter == 0)
	                    throw IFTemplateError("[Template::process] "
	                        "Iteration counter is null.");
	                iterationCounter->setDataType(Node::DATA_INT);
	                iterCount = iterationCounter->getInt(depth.tagForeach - 
	1);
	                numIterations = root->findChild(
	                    NUM_ITERATIONS, false);
	                if (numIterations == 0)
	                    throw IFTemplateError("[Template::process] "
	                        "Number of iterations node is null.");
	                numIter = numIterations->getInt(depth.tagForeach - 1);
	                newDepth = depth;
	                newDepth.tagFirst += 1;
	                newDepth.all += 1;
	                if ((iterCount == 0) && (numIter > 1))
	                    result.append(process(currentRef + 1, i - 1, 
	newDepth));
	                break;
	            case TemplateElement::TE_MID:
	                // mid.
	                nestingLevel++;
	                if (nestingLevel == 1)
	                    currentRef = i;
	                break;
	            case TemplateElement::TE_MID_END:
	                // mid (end tag).
	                nestingLevel--;
	                if (nestingLevel > 0)
	                    break;
	                openTag = elements[currentRef];
	                if (openTag == 0) 
	                {
	                    throw IFTemplateError("[Template::process] "
	                        "mid: Invalid tag.");
	                }
	                if (openTag->type != TemplateElement::TE_MID)
	                {
	                    throw IFTemplateError("[Template::process] "
	                        "mid: Mismatched tag.");
	                }
	                iterationCounter = root->findChild(
	                    ITERATION_COUNTER, false);
	                if (iterationCounter == 0)
	                    throw IFTemplateError("[Template::process] "
	                        "Iteration counter is null.");
	                iterationCounter->setDataType(Node::DATA_INT);
	                iterCount = iterationCounter->getInt(depth.tagForeach - 
	1);
	                numIterations = root->findChild(
	                    NUM_ITERATIONS, false);
	                if (numIterations == 0)
	                    throw IFTemplateError("[Template::process] "
	                        "Number of iterations node  is null.");
	                numIter = numIterations->getInt(depth.tagForeach - 1);
	                newDepth = depth;
	                newDepth.tagMid += 1;
	                newDepth.all += 1;
	                if ((iterCount != 0) && (iterCount != (numIter - 1)))
	                    result.append(process(currentRef + 1, i - 1, 
	newDepth));
	                break;
	            case TemplateElement::TE_LAST:
	                // last.
	                nestingLevel++;
	                if (nestingLevel == 1)
	                    currentRef = i;
	                break;
	            case TemplateElement::TE_LAST_END:
	                // last (end tag).
	                nestingLevel--;
	                if (nestingLevel > 0)
	                    break;
	                openTag = elements[currentRef];
	                if (openTag == 0) 
	                {
	                    throw IFTemplateError("[Template::process] "
	                        "last: Invalid tag.");
	                }
	                if (openTag->type != TemplateElement::TE_LAST)
	                {
	                    throw IFTemplateError("[Template::process] "
	                        "last: Mismatched tag.");
	                }
	                iterationCounter = root->findChild(
	                    ITERATION_COUNTER, false);
	                if (iterationCounter == 0)
	                    throw IFTemplateError("[Template::process] "
	                        "Iteration counter is null.");
	                iterationCounter->setDataType(Node::DATA_INT);
	                iterCount = iterationCounter->getInt(depth.tagForeach - 
	1);
	                numIterations = root->findChild(
	                    NUM_ITERATIONS, false);
	                if (numIterations == 0)
	                    throw IFTemplateError("[Template::process] "
	                        "Number of iterations node  is null.");
	                numIter = numIterations->getInt(depth.tagForeach - 1);
	                newDepth = depth;
	                newDepth.tagLast += 1;
	                newDepth.all += 1;
	                if ((iterCount == (numIter - 1)) && (numIter > 1))
	                    result.append(process(currentRef + 1, i - 1, 
	newDepth));
	                break;
	            case TemplateElement::TE_SINGLE:
	                // single.
	                nestingLevel++;
	                if (nestingLevel == 1)
	                    currentRef = i;
	                break;
	            case TemplateElement::TE_SINGLE_END:
	                // single (end tag).
	                nestingLevel--;
	                if (nestingLevel > 0)
	                    break;
	                openTag = elements[currentRef];
	                if (openTag == 0) 
	                {
	                    throw IFTemplateError("[Template::process] "
	                        "single: Invalid tag.");
	                }
	                if (openTag->type != TemplateElement::TE_SINGLE)
	                {
	                    throw IFTemplateError("[Template::process] "
	                        "single: Mismatched tag.");
	                }
	                iterationCounter = root->findChild(
	                    ITERATION_COUNTER, false);
	                if (iterationCounter == 0)
	                    throw IFTemplateError("[Template::process] "
	                        "Iteration counter is null.");
	                iterationCounter->setDataType(Node::DATA_INT);
	                iterCount = iterationCounter->getInt(depth.tagForeach - 
	1);
	                numIterations = root->findChild(
	                    NUM_ITERATIONS, false);
	                if (numIterations == 0)
	                    throw IFTemplateError("[Template::process] "
	                        "Number of iterations node  is null.");
	                numIter = numIterations->getInt(depth.tagForeach - 1);
	                newDepth = depth;
	                newDepth.tagSingle += 1;
	                newDepth.all += 1;
	                if (numIter == 1)
	                    result.append(process(currentRef + 1, i - 1, 
	newDepth));
	                break;
	            case TemplateElement::TE_NOTFIRST:
	                // notfirst.
	                nestingLevel++;
	                if (nestingLevel == 1)
	                    currentRef = i;
	                break;
	            case TemplateElement::TE_NOTFIRST_END:
	                // notfirst (end tag).
	                nestingLevel--;
	                if (nestingLevel > 0)
	                    break;
	                openTag = elements[currentRef];
	                if (openTag == 0) 
	                {
	                    throw IFTemplateError("[Template::process] "
	                        "notfirst: Invalid tag.");
	                }
	                if (openTag->type != TemplateElement::TE_NOTFIRST)
	                {
	                    throw IFTemplateError("[Template::process] "
	                        "notfirst: Mismatched tag.");
	                }
	                iterationCounter = root->findChild(
	                    ITERATION_COUNTER, false);
	                if (iterationCounter == 0)
	                    throw IFTemplateError("[Template::process] "
	                        "Iteration counter is null.");
	                iterationCounter->setDataType(Node::DATA_INT);
	                iterCount = iterationCounter->getInt(depth.tagForeach - 
	1);
	                newDepth = depth;
	                newDepth.tagNotFirst += 1;
	                newDepth.all += 1;
	                if (iterCount != 0)
	                    result.append(process(currentRef + 1, i - 1, 
	newDepth));
	                break;
	            case TemplateElement::TE_NOTMID:
	                // notmid.
	                nestingLevel++;
	                if (nestingLevel == 1)
	                    currentRef = i;
	                break;
	            case TemplateElement::TE_NOTMID_END:
	                // notmid (end tag).
	                nestingLevel--;
	                if (nestingLevel > 0)
	                    break;
	                openTag = elements[currentRef];
	                if (openTag == 0) 
	                {
	                    throw IFTemplateError("[Template::process] "
	                        "notmid: Invalid tag.");
	                }
	                if (openTag->type != TemplateElement::TE_NOTMID)
	                {
	                    throw IFTemplateError("[Template::process] "
	                        "notmid: Mismatched tag.");
	                }
	                iterationCounter = root->findChild(
	                    ITERATION_COUNTER, false);
	                if (iterationCounter == 0)
	                    throw IFTemplateError("[Template::process] "
	                        "Iteration counter is null.");
	                iterationCounter->setDataType(Node::DATA_INT);
	                iterCount = iterationCounter->getInt(depth.tagForeach - 
	1);
	                numIterations = root->findChild(
	                    NUM_ITERATIONS, false);
	                if (numIterations == 0)
	                    throw IFTemplateError("[Template::process] "
	                        "Number of iterations node  is null.");
	                numIter = numIterations->getInt(depth.tagForeach - 1);
	                newDepth = depth;
	                newDepth.tagNotMid += 1;
	                newDepth.all += 1;
	                if ((iterCount == 0) || (iterCount == (numIter - 1)))
	                    result.append(process(currentRef + 1, i - 1, 
	newDepth));
	                break;
	            case TemplateElement::TE_NOTLAST:
	                // notlast.
	                nestingLevel++;
	                if (nestingLevel == 1)
	                    currentRef = i;
	                break;
	            case TemplateElement::TE_NOTLAST_END:
	                // notlast (end tag).
	                nestingLevel--;
	                if (nestingLevel > 0)
	                    break;
	                openTag = elements[currentRef];
	                if (openTag == 0) 
	                {
	                    throw IFTemplateError("[Template::process] "
	                        "notlast: Invalid tag.");
	                }
	                if (openTag->type != TemplateElement::TE_NOTLAST)
	                {
	                    throw IFTemplateError("[Template::process] "
	                        "notlast: Mismatched tag.");
	                }
	                iterationCounter = root->findChild(
	                    ITERATION_COUNTER, false);
	                if (iterationCounter == 0)
	                    throw IFTemplateError("[Template::process] "
	                        "Iteration counter is null.");
	                iterationCounter->setDataType(Node::DATA_INT);
	                iterCount = iterationCounter->getInt(depth.tagForeach - 
	1);
	                numIterations = root->findChild(
	                    NUM_ITERATIONS, false);
	                if (numIterations == 0)
	                    throw IFTemplateError("[Template::process] "
	                        "Number of iterations node  is null.");
	                numIter = numIterations->getInt(depth.tagForeach - 1);
	                newDepth = depth;
	                newDepth.tagNotLast += 1;
	                newDepth.all += 1;
	                if (iterCount != (numIter - 1))
	                    result.append(process(currentRef + 1, i - 1, 
	newDepth));
	                break;
	            case TemplateElement::TE_NOTSINGLE:
	                // notsingle.
	                nestingLevel++;
	                if (nestingLevel == 1)
	                    currentRef = i;
	                break;
	            case TemplateElement::TE_NOTSINGLE_END:
	                // notsingle (end tag).
	                nestingLevel--;
	                if (nestingLevel > 0)
	                    break;
	                openTag = elements[currentRef];
	                if (openTag == 0) 
	                {
	                    throw IFTemplateError("[Template::process] "
	                        "notsingle: Invalid tag.");
	                }
	                if (openTag->type != TemplateElement::TE_NOTSINGLE)
	                {
	                    throw IFTemplateError("[Template::process] "
	                        "notsingle: Mismatched tag.");
	                }
	                iterationCounter = root->findChild(
	                    ITERATION_COUNTER, false);
	                if (iterationCounter == 0)
	                    throw IFTemplateError("[Template::process] "
	                        "Iteration counter is null.");
	                iterationCounter->setDataType(Node::DATA_INT);
	                iterCount = iterationCounter->getInt(depth.tagForeach - 
	1);
	                numIterations = root->findChild(
	                    NUM_ITERATIONS, false);
	                if (numIterations == 0)
	                    throw IFTemplateError("[Template::process] "
	                        "Number of iterations node  is null.");
	                numIter = numIterations->getInt(depth.tagForeach - 1);
	                newDepth = depth;
	                newDepth.tagNotSingle += 1;
	                newDepth.all += 1;
	                if (numIter > 1)
	                    result.append(process(currentRef + 1, i - 1, 
	newDepth));
	                break;
	            case TemplateElement::TE_SWRAP:
	                // swrap.
	                nestingLevel++;
	                if (nestingLevel != 1)
	                    break;
	                currentRef = i;
	                if (currentElement->params.size() < 4)
	                {
	                    throw IFTemplateError("[Template::process] "
	                        "swrap: Missing arguments.");
	                }
	                break;
	            case TemplateElement::TE_SWRAP_END:
	                // swrap (end tag)
	                nestingLevel--;
	                if (nestingLevel > 0)
	                    break;
	                openTag = elements[currentRef];
	                if (openTag == 0) 
	                {
	                    throw IFTemplateError("[Template::process] "
	                        "swrap: Invalid tag.");
	                }
	                if (openTag->type != TemplateElement::TE_SWRAP)
	                {
	                    throw IFTemplateError("[Template::process] "
	                        "swrap: Mismatched tag.");
	                }
	                openTag->refs.push_back(i);
	                newDepth = depth;
	                newDepth.tagSWrap += 1;
	                newDepth.all += 1;
	                swrapArgs.clear();
	                lineWidth = SWRAP_DEFAULT_LINE_WIDTH;
	                prefix = "";
	                lineTerm = SWRAP_DEFAULT_LINE_TERM;
	                if ((openTag->params.size() > 1) 
	                    && (openTag->params[1].size() > 0))
	                    lineWidth = openTag->params[1];
	                if ((openTag->params.size() > 2) 
	                    && (openTag->params[2].size() > 0))
	                    prefix = openTag->params[2];
	                if ((openTag->params.size() > 3) 
	                    && (openTag->params[3].size() > 0))
	                    lineTerm = openTag->params[3];
	                swrapArgs.push_back(lineWidth);
	                swrapArgs.push_back(prefix);
	                swrapArgs.push_back(lineTerm);
	                result.append(swrap.process(
	                    process(currentRef + 1, i - 1, newDepth), 
	                    &swrapArgs));
	                break;
	            case TemplateElement::TE_SECTION:
	                // section.
	                nestingLevel++;
	                if (nestingLevel != 1)
	                    break;
	                currentRef = i;
	                if (currentElement->params.size() < 1)
	                {
	                    throw IFTemplateError("[Template::process] "
	                        "section: Missing arguments.");
	                }
	                break;
	            case TemplateElement::TE_SECTION_END:
	                // section (end tag)
	                nestingLevel--;
	                if (nestingLevel > 0)
	                    break;
	                openTag = elements[currentRef];
	                if (openTag == 0) 
	                {
	                    throw IFTemplateError("[Template::process] "
	                        "section: Invalid tag.");
	                }
	                if (openTag->type != TemplateElement::TE_SECTION)
	                {
	                    throw IFTemplateError("[Template::process] "
	                        "section: Mismatched tag.");
	                }
	                openTag->refs.push_back(i);
	                currentSection.first = currentRef + 1;
	                currentSection.last = i - 1;
	                if ((openTag->params.size() > 0)
	                    && (currentSection.last >= currentSection.first))
	                {
	                    string sectionName = openTag->params[0];
	                    /* ----- DEBUG ----- //
	                    cerr << "[Template::process] Adding section: '"
	                        << sectionName << "' (" << currentSection.first 
	                        << ", " << currentSection.last << ")" << endl;
	                    // ----- DEBUG ----- */
	                    sections[sectionName] = currentSection;
	                }
	                break;
	            case TemplateElement::TE_REF:
	                // ref
	                if (nestingLevel > 0)
	                    break;
	                if (currentElement->params.size() < 2)
	                {
	                    throw IFTemplateError("[Template::process] "
	                        "ref: Missing arguments.");
	                }
	                sectionIter = sections.find(currentElement->params[1]);
	                if (sectionIter == sections.end())
	                {
	                    status.str("");
	                    status << "[Template::process] ref: Section '"
	                        << currentElement->params[1] << "' not defined.";
	                    throw IFTemplateError(status.str());
	                }
	                if ((currentElement->params.size() >= 3)
	                    && (currentElement->params[2] == "restore"))
	                    sectionRestore = true;
	                else
	                    sectionRestore = false;
	                currentSection = (*sectionIter).second;
	                if (sectionRestore)
	                {
	                    /* ----- DEBUG ----- //
	                    cerr << "[Template::process] DEBUG: (ref) "
	                        "Saving environment..." << endl;
	                    // ----- DEBUG ----- */
	                    saveConfig = *root;
	                    /* ----- DEBUG ----- //
	                    cerr << "[Template::process] DEBUG: (ref) "
	                        "Finished saving environment." << endl;
	                    // ----- DEBUG ----- */
	                }
	                newDepth = depth;
	                newDepth.tagRef += 1;
	                newDepth.all += 1;
	                /* ----- DEBUG ----- //
	                cerr << "[Template::process] DEBUG: (ref) "
	                    "Processing section '" << currentElement->params[1] 
	                    << "'." << endl;
	                // ----- DEBUG ----- */
	                result.append(process(currentSection.first, 
	                    currentSection.last, newDepth));
	                if (sectionRestore)
	                {
	                    /* ----- DEBUG ----- //
	                    cerr << "[Template::process] DEBUG: (ref) "
	                        "Restoring environment..." << endl;
	                    // ----- DEBUG ----- */
	                    *root = saveConfig;
	                    /* ----- DEBUG ----- //
	                    cerr << "[Template::process] DEBUG: (ref) "
	                        "Finished restoring environment." << endl;
	                    // ----- DEBUG ----- */
	                }
	                break;
	            default:
	                status.str("");
	                status << "[Template::process] Unknown template "
	                    "element type: " << currentElement->type << ".";
	                throw IFTemplateError(status.str());
	        }
	    }
	}
	return result;
}

void Template::readTemplate(const std::string& templateFileName, 
Ionflux::Template::TemplateElementVector& target)
{
	Ionflux::ObjectBase::readFile(templateFileName, templateInput);
	parse(target);
}

void Template::readTemplate(const std::string& templateFileName)
{
	readTemplate(templateFileName, elements);
}

void Template::setTemplate(const std::string& newTemplate, 
Ionflux::Template::TemplateElementVector& target)
{
	templateInput = newTemplate;
	parse(target);
}

void Template::setTemplate(const std::string& newTemplate)
{
	setTemplate(newTemplate, elements);
}

void Template::setTemplateModule(const std::string& modulePath, 
Ionflux::Template::TemplateElementVector& target)
{
	if (repository == 0)
	{
	    /* <---- DEBUG ----- //
	    std::cerr << "[Template::setTemplateModule] DEBUG: "
	        "Repository not set." << std::endl;
	    // ----- DEBUG ----> */
	    throw IFTemplateError(getErrorString(
	        "Repository not set.", "setTemplateModule"));
	}
	templateInput = repository->getTemplateData(modulePath);
	parse(target);
}

void Template::setTemplateModule(const std::string& modulePath)
{
	setTemplateModule(modulePath, elements);
}

std::string Template::process(const std::string& newTemplate, 
Ionflux::Template::Node* newConfig)
{
	if (newTemplate.size() > 0)
	    setTemplate(newTemplate);
	if ((newConfig != 0) 
	    && (root != 0))
	{
	    *root = *newConfig;
	    root->setAutoCreate(true);
	    root->setIndexMode(Node::INDEX_MODE_NODE);
	}
	TagNestingLevel depth;
	return process(0, elements.size() - 1, depth);
}

std::string Template::processModule(const std::string& modulePath, 
Ionflux::Template::Node* newConfig)
{
	if (modulePath.size() > 0)
	    setTemplateModule(modulePath);
	if ((newConfig != 0) 
	    && (root != 0))
	{
	    *root = *newConfig;
	    root->setAutoCreate(true);
	    root->setIndexMode(Node::INDEX_MODE_NODE);
	}
	TagNestingLevel depth;
	return process(0, elements.size() - 1, depth);
}

void Template::printElementDebugInfo()
{
	Node* currentNode = 0;
	int currentIndex;
	StringFilter* currentFilter = 0;
	std::cout << "Number of elements: " << elements.size() << std::endl;
	for (unsigned int i = 0; i < elements.size(); i++)
	{
	    std::cout << "[" << i << "]:" << std::endl
	        << "    type: " << elements[i]->type << std::endl
	        << "    parameters:" << std::endl;
	    for (unsigned int k = 0; k < elements[i]->params.size(); k++)
	    {
	        std::cout << "        [" << k << "]: '" << elements[i]->params[k] 
	            << "'" << std::endl;
	    }
	    std::cout << "    variables:" << std::endl;
	    if (elements[i]->vars.size() > 0)
	    {
	        for (unsigned int k = 0; k < elements[i]->vars.size(); k++)
	        {
	            /* This assumes that the names of n variables are stored 
	               in the first n parameters, starting from 1. */
	            elements[i]->vars[k].data = resolve(
	                elements[i]->params[k + 1], false);
	            currentNode = elements[i]->vars[k].data.node;
	            currentIndex = elements[i]->vars[k].data.index;
	            currentFilter = elements[i]->vars[k].filter;
	            std::cout << "        [" << k << "]: ";
	            if (currentNode != 0)
	            {
	                std::cout << currentNode->getPath();
	                if (currentIndex != 0)
	                 std::cout << "[" << currentIndex << "]";
	            }
	            else
	                std::cout << "(null)";
	            std::cout << std::endl;
	            std::cout << "            filter: ";
	            if (currentFilter != 0)
	            {
	                std::cout << "yes" << std::endl;
	                currentFilter->printDebugInfo();
	            } else
	                std::cout << "(null)" << std::endl;
	        }
	    } else
	        std::cout << "        (none)" << std::endl;
	    std::cout << "    references:" << std::endl;
	    if (elements[i]->refs.size() > 0)
	    {
	        for (unsigned int k = 0; k < elements[i]->refs.size(); k++)
	        {
	            std::cout << "        [" << k << "]: " << elements[i]->refs[k]
	
                << std::endl;
	        }
	    } else
	        std::cout << "        (none)" << std::endl;
	}
}

void Template::setMaxNestingDepth(unsigned int newMaxNestingDepth)
{
	maxNestingDepth = newMaxNestingDepth;
}

unsigned int Template::getMaxNestingDepth() const
{
	return maxNestingDepth;
}

void Template::setRepository(Ionflux::Template::TemplateRepository* 
newRepository)
{
	if (repository == newRepository)
		return;
    if (newRepository != 0)
        addLocalRef(newRepository);
	if (repository != 0)
		removeLocalRef(repository);
	repository = newRepository;
}

Ionflux::Template::TemplateRepository* Template::getRepository() const
{
	return repository;
}

Ionflux::Template::Template& Template::operator=(const 
Ionflux::Template::Template& other)
{
	return *this;
}

Ionflux::Template::Template* Template::copy() const
{
    Template* newTemplate = create();
    *newTemplate = *this;
    return newTemplate;
}

Ionflux::Template::Template* 
Template::upcast(Ionflux::ObjectBase::IFObject* other)
{
    return dynamic_cast<Template*>(other);
}

Ionflux::Template::Template* 
Template::create(Ionflux::ObjectBase::IFObject* parentObject)
{
    Template* newObject = new Template();
    if (newObject == 0)
    {
        throw IFTemplateError("Could not allocate object.");
    }
    if (parentObject != 0)
        parentObject->addLocalRef(newObject);
    return newObject;
}

Ionflux::Template::Template* Template::create(const std::string& 
templateInput, Ionflux::Template::Node* initRoot, 
Ionflux::Template::TemplateRepository* initRepository, 
Ionflux::ObjectBase::IFObject* parentObject)
{
    Template* newObject = new Template(templateInput, initRoot, 
    initRepository);
    if (newObject == 0)
    {
        throw IFTemplateError("Could not allocate object.");
    }
    if (parentObject != 0)
        parentObject->addLocalRef(newObject);
    return newObject;
}

}

}

/** \file Template.cpp
 * \brief Template implementation.
 */
