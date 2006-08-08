/* ==========================================================================
 * Ionflux Tools
 * Copyright (c) 2004 Joern P. Meier
 * mail@ionflux.org
 * --------------------------------------------------------------------------
 * Template.cpp                    Template processor.
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

#include "ionflux/Template.hpp"

using namespace std;

namespace Ionflux
{

namespace Tools
{

const int TemplateElement::TE_INVALID = -1;
const int TemplateElement::TE_CDATA = 0;
const int TemplateElement::TE_VAR = 1;
const int TemplateElement::TE_FOREACH = 2;
const int TemplateElement::TE_FOREACH_ELSE = 3;
const int TemplateElement::TE_FOREACH_END = 4;
const int TemplateElement::TE_IF = 5;
const int TemplateElement::TE_IF_ELSE = 6;
const int TemplateElement::TE_IF_END = 7;
const int TemplateElement::TE_FIRST = 8;
const int TemplateElement::TE_FIRST_END = 9;
const int TemplateElement::TE_MID = 10;
const int TemplateElement::TE_MID_END = 11;
const int TemplateElement::TE_LAST = 12;
const int TemplateElement::TE_LAST_END = 13;
const int TemplateElement::TE_SINGLE = 14;
const int TemplateElement::TE_SINGLE_END = 15;
const int TemplateElement::TE_NOTFIRST = 16;
const int TemplateElement::TE_NOTFIRST_END = 17;
const int TemplateElement::TE_NOTMID = 18;
const int TemplateElement::TE_NOTMID_END = 19;
const int TemplateElement::TE_NOTLAST = 20;
const int TemplateElement::TE_NOTLAST_END = 21;
const int TemplateElement::TE_NOTSINGLE = 22;
const int TemplateElement::TE_NOTSINGLE_END = 23;
const int TemplateElement::TE_INCLUDE = 24;
const int TemplateElement::TE_SWRAP = 25;
const int TemplateElement::TE_SWRAP_END = 26;
const int TemplateElement::TE_SECTION = 27;
const int TemplateElement::TE_SECTION_END = 28;
const int TemplateElement::TE_REF = 29;

TagNestingLevel::TagNestingLevel()
: tagForeach(0), tagIf(0), tagFirst(0), tagMid(0), tagLast(0), tagSingle(0), 
  tagNotFirst(0), tagNotMid(0), tagNotLast(0), tagNotSingle(0), tagSWrap(0), 
  tagSection(0), tagRef(0), all(0)
{
	// TODO: Nothing ATM. ;-)
}

const std::string Template::ITERATION_COUNTER = "__i";
const std::string Template::NUM_ITERATIONS = "__n";
const std::string Template::CONDITION_NODE = "__cond";

const TokenType Template::TT_TEMPLATE_TAG_OPEN = {
	TokenType::USERTYPE_ID + 101, "{", false, 1};
const TokenType Template::TT_TEMPLATE_TAG_CLOSE = {
	TokenType::USERTYPE_ID + 102, "}", false, 1};
const TokenType Template::TT_VAR_MARKER = {
	TokenType::USERTYPE_ID + 103, "$@", false, 1};
const TokenType Template::TT_COMMENT = {
	TokenType::USERTYPE_ID + 104, "#", false, 1};
const TokenType Template::TT_TREEPATH = {
	TokenType::USERTYPE_ID + 105, ".[]()", false, 0};
const TokenType Template::TT_END_TAG_MARKER = {
	TokenType::USERTYPE_ID + 106, "/", false, 0};
const TokenType Template::TT_OPERATOR_NSO = {
	TokenType::USERTYPE_ID + 107, "+-*=<>&!~%^", false, 0};

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
const std::string Template::TAG_SWRAP = "swrap";
const std::string Template::TAG_SECTION = "section";
const std::string Template::TAG_REF = "ref";

const std::string Template::SWRAP_DEFAULT_LINE_WIDTH = "78";
const std::string Template::SWRAP_DEFAULT_LINE_TERM = "\n";
const unsigned int Template::DEFAULT_MAX_NESTING_DEPTH = 999;

Template::Template()
: templateInput(""), maxNestingDepth(DEFAULT_MAX_NESTING_DEPTH)
{
	root.node->setAutoCreate(true);
	root.node->setIndexMode(Node::INDEX_MODE_NODE);
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
			StringFilter *currentFilter;
			for (unsigned int k = 0; k < elements[i]->vars.size(); k++)
			{
				currentFilter = elements[i]->vars[k].filter;
				if (currentFilter != 0)
					delete currentFilter;
				elements[i]->vars[k].filter = 0;
			}
			delete elements[i];
		}
		elements[i] = 0;
	}
	elements.clear();
	sections.clear();
}

bool Template::parse()
{
	clearElements();
	return parse(elements);
}

bool Template::parse(std::vector<TemplateElement *> &target)
{
	ostringstream status;
	string currentData;
	int nestingLevel;
	bool quoted;
	char quoteChar;
	bool error = false;
	string errorReason = "";
	tok.setInput(templateInput);
	Token currentToken = tok.getNextToken();
	unsigned int lineCount = 1;
	target.clear();
	bool startOfLine = true;
	while ((currentToken.typeID != Tokenizer::TT_NONE.typeID) 
		&& (currentToken.typeID != Tokenizer::TT_INVALID.typeID)
		&& !error)
	{
		if (currentToken.typeID == Tokenizer::TT_ESCAPED.typeID)
		{
			// Handle escaped character.
			currentData.append(currentToken.value);
			currentToken = tok.getNextToken();
			startOfLine = false;
		} else
		if (startOfLine &&
			(currentToken.typeID == TT_COMMENT.typeID))
		{
			/* Handle comments.
			   Skip everything until end of line. */
			while ((currentToken.typeID != Tokenizer::TT_NONE.typeID) 
				&& (currentToken.typeID != Tokenizer::TT_INVALID.typeID)
				&& (currentToken.typeID != Tokenizer::TT_LINETERM.typeID))
				currentToken = tok.getNextToken();
			if ((currentToken.typeID == Tokenizer::TT_LINETERM.typeID)
				&& (currentToken.value[0] == '\r'))
			{
				/* This is a guess that we are on a system with strange line 
				   terminators, so skip an additional token. */
				tok.getNextToken();
			}
			currentToken = tok.getNextToken();
			lineCount++;
			startOfLine = true;
		} else
		if (currentToken.typeID == TT_TEMPLATE_TAG_OPEN.typeID)
		{
			// Handle template tags.
			addCharacterData(currentData, target);
			currentData = "";
			nestingLevel = 1;
			quoted = false;
			tok.setExtractQuoted(true);
			currentToken = tok.getNextToken();
			while ((currentToken.typeID != Tokenizer::TT_NONE.typeID) 
				&& (currentToken.typeID != Tokenizer::TT_INVALID.typeID)
				&& (nestingLevel > 0))
			{
				/* ----- DEBUG ----- //
				cout << "[Template::parse] DEBUG: Current token value: "
					<< currentToken.value << endl;
				// ----- DEBUG ----- */
				if (currentToken.typeID == Tokenizer::TT_QUOTED.typeID)
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
				if (currentToken.typeID == TT_TEMPLATE_TAG_OPEN.typeID)
				{
					// Handle opening template tag marker.
					if (!quoted)
						nestingLevel++;
					currentData.append(currentToken.value);
				} else
				if (currentToken.typeID == TT_TEMPLATE_TAG_CLOSE.typeID)
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
					if (currentToken.typeID == Tokenizer::TT_LINETERM.typeID)
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
			if ((currentToken.typeID == Tokenizer::TT_LINETERM.typeID)
				&& (currentToken.value.size() > 0)
				&& (currentToken.value[0] != '\r'))
			{
				lineCount++;
				startOfLine = true;
			} else
				startOfLine = false;
			currentData.append(currentToken.value);
			currentToken = tok.getNextToken();
		}
	}
	if (currentToken.typeID == Tokenizer::TT_INVALID.typeID)
	{
		errorReason = "Invalid Token.";
		error = true;
	}
	if (error)
	{
		status.str("");
		status << "[Template::parse] ERROR: Parse error in line "
			<< lineCount << " at token '" << currentToken.value 
			<< "'. (" << errorReason << ")";
		log.msg(status.str(), log.VL_ERROR);
	} else
	{
		// Add remaining character data as a new element.
		addCharacterData(currentData, target);
		currentData = "";
	}
	preprocess(target);
	return !error;
}

void Template::addCharacterData(const std::string &characterData, 
	std::vector<TemplateElement *> &target)
{
	if (characterData == "")
		return;
	TemplateElement *currentElement = new TemplateElement();
	currentElement->type = TemplateElement::TE_CDATA;
	currentElement->params.push_back(characterData);
	target.push_back(currentElement);
}

bool Template::addTemplateTag(const std::string &tagData, 
	std::vector<TemplateElement *> &target)
{
	if (tagData == "")
		return true;
	tagTok.setInput(tagData);
	bool endTag = false;
	char quoteChar;
	Token currentToken = tagTok.getNextToken();
	// Skip leading whitespace.
	while (currentToken.typeID == Tokenizer::TT_WHITESPACE.typeID)
		currentToken = tagTok.getNextToken();
	// Set end tag flag.
	if (currentToken.typeID == TT_END_TAG_MARKER.typeID)
	{
		endTag = true;
		currentToken = tagTok.getNextToken();
	}
	// Determine type of tag and initialize appropriate element.
	if ((currentToken.typeID == TT_VAR_MARKER.typeID) 
		|| (currentToken.typeID == TT_TREEPATH.typeID))
	{
		// Variable substitution tag.
		string currentData = "";
		currentToken = tagTok.getNextToken();
		while ((currentToken.typeID == Tokenizer::TT_IDENTIFIER.typeID)
			|| (currentToken.typeID == TT_TREEPATH.typeID)
			|| (currentToken.typeID == Tokenizer::TT_QUOTED.typeID)
			|| (currentToken.typeID == Tokenizer::TT_ESCAPED.typeID))
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
		while (currentToken.typeID == Tokenizer::TT_WHITESPACE.typeID)
			currentToken = tagTok.getNextToken();
		// Extract string filter or assignment expression.
		string currentFilterExpr = "";
		string currentAssignExpr = "";
		if (currentToken.typeID == StringFilter::TT_FUNC_SEP.typeID)
		{
			tagTok.setExtractQuoted(false);
			tagTok.setExtractEscaped(false);
			currentToken = tagTok.getNextToken();
			while ((currentToken.typeID != Tokenizer::TT_NONE.typeID)
				&& (currentToken.typeID != Tokenizer::TT_INVALID.typeID))
			{
				currentFilterExpr.append(currentToken.value);
				currentToken = tagTok.getNextToken();
			}
			tagTok.setExtractQuoted(true);
			tagTok.setExtractEscaped(true);
		} else
		if ((currentToken.typeID == TT_OPERATOR_NSO.typeID)
			&& (currentToken.value == "="))
		{
			currentToken = tagTok.getNextToken();
			/* Everything listed in the following while-condition is a 
			   valid part of a tree expression. */
			while ((currentToken.typeID == Tokenizer::TT_IDENTIFIER.typeID)
				|| (currentToken.typeID == Tokenizer::TT_WHITESPACE.typeID)
				|| (currentToken.typeID == StringFilter::TT_FUNC_SEP.typeID)
				|| (currentToken.typeID == TT_TREEPATH.typeID)
				|| (currentToken.typeID == Tokenizer::TT_ESCAPED.typeID)
				|| (currentToken.typeID == Tokenizer::TT_QUOTED.typeID)
				|| (currentToken.typeID == TT_OPERATOR_NSO.typeID)
				|| (currentToken.typeID == TT_END_TAG_MARKER.typeID))
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
		if ((currentToken.typeID != Tokenizer::TT_NONE.typeID)
			|| (currentData == ""))
			return false;
		// Add template element.
		TemplateVar currentVar;
		currentVar.data.node = 0;
		currentVar.data.index = 0;
		if (currentFilterExpr != "")
			currentVar.filter = new StringFilter(currentFilterExpr);
		else
			currentVar.filter = 0;
		TemplateElement *currentElement = new TemplateElement();
		currentElement->type = TemplateElement::TE_VAR;
		currentElement->params.push_back(tagData);
		currentElement->params.push_back(currentData);
		currentElement->params.push_back(currentAssignExpr);
		currentElement->vars.push_back(currentVar);
		target.push_back(currentElement);
	} else
	if (currentToken.typeID == Tokenizer::TT_IDENTIFIER.typeID)
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
				while (currentToken.typeID == Tokenizer::TT_WHITESPACE.typeID)
					currentToken = tagTok.getNextToken();
				// Extract iterator.
				string iteratorData;
				while ((currentToken.typeID == Tokenizer::TT_IDENTIFIER.typeID)
					|| (currentToken.typeID == TT_TREEPATH.typeID)
					|| (currentToken.typeID == Tokenizer::TT_ESCAPED.typeID)
					|| (currentToken.typeID == Tokenizer::TT_QUOTED.typeID))
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
				while (currentToken.typeID == Tokenizer::TT_WHITESPACE.typeID)
					currentToken = tagTok.getNextToken();
				// Expect 'in' keyword.
				if (currentToken.value != TAG_FOREACH_IN)
					return false;
				currentToken = tagTok.getNextToken();
				// Skip enclosed whitespace.
				while (currentToken.typeID == Tokenizer::TT_WHITESPACE.typeID)
					currentToken = tagTok.getNextToken();
				// Extract source.
				string sourceData;
				while ((currentToken.typeID == Tokenizer::TT_IDENTIFIER.typeID)
					|| (currentToken.typeID == TT_TREEPATH.typeID)
					|| (currentToken.typeID == Tokenizer::TT_ESCAPED.typeID)
					|| (currentToken.typeID == Tokenizer::TT_QUOTED.typeID))
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
				while (currentToken.typeID == Tokenizer::TT_WHITESPACE.typeID)
					currentToken = tagTok.getNextToken();
				if ((currentToken.typeID != Tokenizer::TT_NONE.typeID)
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
				TemplateElement *currentElement = new TemplateElement();
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
				while (currentToken.typeID == Tokenizer::TT_WHITESPACE.typeID)
					currentToken = tagTok.getNextToken();
				if (currentToken.typeID != Tokenizer::TT_NONE.typeID)
					return false;
				// Add template element.
				TemplateElement *currentElement = new TemplateElement();
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
				while (currentToken.typeID == Tokenizer::TT_WHITESPACE.typeID)
					currentToken = tagTok.getNextToken();
				if (currentToken.typeID != Tokenizer::TT_NONE.typeID)
					return false;
				// Add template element.
				TemplateElement *currentElement = new TemplateElement();
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
				while (currentToken.typeID == Tokenizer::TT_WHITESPACE.typeID)
					currentToken = tagTok.getNextToken();
				// Extract if-condition.
				string conditionData;
				/* Everything listed in the following while-condition is a 
				   valid part of a tree expression. */
				while ((currentToken.typeID == Tokenizer::TT_IDENTIFIER.typeID)
					|| (currentToken.typeID == Tokenizer::TT_WHITESPACE.typeID)
					|| (currentToken.typeID == StringFilter::TT_FUNC_SEP.typeID)
					|| (currentToken.typeID == TT_TREEPATH.typeID)
					|| (currentToken.typeID == Tokenizer::TT_ESCAPED.typeID)
					|| (currentToken.typeID == Tokenizer::TT_QUOTED.typeID)
					|| (currentToken.typeID == TT_OPERATOR_NSO.typeID)
					|| (currentToken.typeID == TT_END_TAG_MARKER.typeID))
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
				if (currentToken.typeID != Tokenizer::TT_NONE.typeID)
					return false;
				// Add template element.
				TemplateElement *currentElement = new TemplateElement();
				currentElement->type = TemplateElement::TE_IF;
				currentElement->params.push_back(tagData);
				currentElement->params.push_back(conditionData);
				target.push_back(currentElement);
			} else
			{
				/* if: Handle end tag.
				   Skip trailing whitespace. */
				while (currentToken.typeID == Tokenizer::TT_WHITESPACE.typeID)
					currentToken = tagTok.getNextToken();
				if (currentToken.typeID != Tokenizer::TT_NONE.typeID)
					return false;
				// Add template element.
				TemplateElement *currentElement = new TemplateElement();
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
				while (currentToken.typeID == Tokenizer::TT_WHITESPACE.typeID)
					currentToken = tagTok.getNextToken();
				if (currentToken.typeID != Tokenizer::TT_NONE.typeID)
					return false;
				// Add template element.
				TemplateElement *currentElement = new TemplateElement();
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
				while (currentToken.typeID == Tokenizer::TT_WHITESPACE.typeID)
					currentToken = tagTok.getNextToken();
				if (currentToken.typeID != Tokenizer::TT_NONE.typeID)
					return false;
				TemplateElement *currentElement = new TemplateElement();
				currentElement->type = elementOpenType;
				currentElement->params.push_back(tagData);
				target.push_back(currentElement);
			} else
			{
				/* Foreach special block tag: Handle end tag.
				   Skip trailing whitespace. */
				while (currentToken.typeID == Tokenizer::TT_WHITESPACE.typeID)
					currentToken = tagTok.getNextToken();
				if (currentToken.typeID != Tokenizer::TT_NONE.typeID)
					return false;
				// Add template element.
				TemplateElement *currentElement = new TemplateElement();
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
				while (currentToken.typeID == Tokenizer::TT_WHITESPACE.typeID)
					currentToken = tagTok.getNextToken();
				// Extract filename.
				string includeFile;
				while ((currentToken.typeID != Tokenizer::TT_NONE.typeID)
					&& (currentToken.typeID != Tokenizer::TT_INVALID.typeID))
				{
					includeFile.append(currentToken.value);
					currentToken = tagTok.getNextToken();
				}
				if (currentToken.typeID != Tokenizer::TT_NONE.typeID)
					return false;
				// Remove leading and trailing whitespace.
				StringTrim trim;
				includeFile = trim.process(includeFile, 0);
				// Add template element.
				TemplateElement *currentElement = new TemplateElement();
				currentElement->type = TemplateElement::TE_INCLUDE;
				currentElement->params.push_back(tagData);
				currentElement->params.push_back(includeFile);
				target.push_back(currentElement);
			} else
				// include does not have an end tag.
				return false;
		} else
		if (currentToken.value == TAG_SWRAP)
		{
			// Tag: swrap.
			currentToken = tagTok.getNextToken();
			if (!endTag)
			{
				// swrap: Handle opening tag.
				while (currentToken.typeID == Tokenizer::TT_WHITESPACE.typeID)
					currentToken = tagTok.getNextToken();
				string lineWidth;
				string prefix;
				string lineTerm;
				// Extract line width.
				while ((currentToken.typeID == Tokenizer::TT_IDENTIFIER.typeID)
					|| (currentToken.typeID == Tokenizer::TT_QUOTED.typeID))
				{
					lineWidth.append(currentToken.value);
					currentToken = tagTok.getNextToken();
				}
				while (currentToken.typeID == Tokenizer::TT_WHITESPACE.typeID)
					currentToken = tagTok.getNextToken();
				// Extract prefix.
				while ((currentToken.typeID == Tokenizer::TT_IDENTIFIER.typeID)
					|| (currentToken.typeID == Tokenizer::TT_QUOTED.typeID))
				{
					prefix.append(currentToken.value);
					currentToken = tagTok.getNextToken();
				}
				while (currentToken.typeID == Tokenizer::TT_WHITESPACE.typeID)
					currentToken = tagTok.getNextToken();
				// Extract line terminator.
				while ((currentToken.typeID == Tokenizer::TT_IDENTIFIER.typeID)
					|| (currentToken.typeID == Tokenizer::TT_QUOTED.typeID))
				{
					lineTerm.append(currentToken.value);
					currentToken = tagTok.getNextToken();
				}
				while (currentToken.typeID == Tokenizer::TT_WHITESPACE.typeID)
					currentToken = tagTok.getNextToken();
				if (currentToken.typeID != Tokenizer::TT_NONE.typeID)
					return false;
				// Add template element.
				TemplateElement *currentElement = new TemplateElement();
				currentElement->type = TemplateElement::TE_SWRAP;
				currentElement->params.push_back(tagData);
				currentElement->params.push_back(lineWidth);
				currentElement->params.push_back(prefix);
				currentElement->params.push_back(lineTerm);
				target.push_back(currentElement);
			} else
			{
				// swrap: Handle end tag.
				while (currentToken.typeID == Tokenizer::TT_WHITESPACE.typeID)
					currentToken = tagTok.getNextToken();
				if (currentToken.typeID != Tokenizer::TT_NONE.typeID)
					return false;
				// Add template element.
				TemplateElement *currentElement = new TemplateElement();
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
				while (currentToken.typeID == Tokenizer::TT_WHITESPACE.typeID)
					currentToken = tagTok.getNextToken();
				string sectionName;
				// Extract section name.
				while ((currentToken.typeID == Tokenizer::TT_IDENTIFIER.typeID)
					|| (currentToken.typeID == Tokenizer::TT_QUOTED.typeID))
				{
					sectionName.append(currentToken.value);
					currentToken = tagTok.getNextToken();
				}
				while (currentToken.typeID == Tokenizer::TT_WHITESPACE.typeID)
					currentToken = tagTok.getNextToken();
				if (currentToken.typeID != Tokenizer::TT_NONE.typeID)
					return false;
				// Add template element.
				TemplateElement *currentElement = new TemplateElement();
				currentElement->type = TemplateElement::TE_SECTION;
				currentElement->params.push_back(sectionName);
				target.push_back(currentElement);
			} else
			{
				// section: Handle end tag.
				while (currentToken.typeID == Tokenizer::TT_WHITESPACE.typeID)
					currentToken = tagTok.getNextToken();
				if (currentToken.typeID != Tokenizer::TT_NONE.typeID)
					return false;
				// Add template element.
				TemplateElement *currentElement = new TemplateElement();
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
				while (currentToken.typeID == Tokenizer::TT_WHITESPACE.typeID)
					currentToken = tagTok.getNextToken();
				// Extract reference name.
				string refName;
				while ((currentToken.typeID == Tokenizer::TT_IDENTIFIER.typeID)
					|| (currentToken.typeID == Tokenizer::TT_QUOTED.typeID))
				{
					refName.append(currentToken.value);
					currentToken = tagTok.getNextToken();
				}
				while (currentToken.typeID == Tokenizer::TT_WHITESPACE.typeID)
					currentToken = tagTok.getNextToken();
				// Extract restore switch.
				string refRestore;
				if (currentToken.typeID == Tokenizer::TT_IDENTIFIER.typeID)
				{
					refRestore = currentToken.value;
					currentToken = tagTok.getNextToken();
				}
				if (currentToken.typeID != Tokenizer::TT_NONE.typeID)
					return false;
				// Add template element.
				TemplateElement *currentElement = new TemplateElement();
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

bool Template::preprocess(std::vector<TemplateElement *> &target)
{
	if (target.size() == 0)
		return true;
	bool error = false;
	unsigned int i = 0;
	std::vector<TemplateElement *> result;
	std::vector<TemplateElement *> trash;
	std::vector<TemplateElement *> temp;
	TemplateElement *currentElement;
	Template includeTemplate;
	while (!error && (i < target.size()))
	{
		currentElement = target[i];
		if (currentElement != 0)
		{
			switch (currentElement->type)
			{
				case TemplateElement::TE_INCLUDE:
					if (currentElement->params.size() < 2)
						break;
					temp.clear();
					includeTemplate.readTemplate(
						currentElement->params[1], temp);
					for (unsigned int k = 0; k < temp.size(); k++)
						result.push_back(temp[k]);
					trash.push_back(currentElement);
					break;
				default:
					result.push_back(currentElement);
			}
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
	return !error;
}

std::string Template::process(unsigned int from, unsigned int to, 
	TagNestingLevel depth)
{
	ostringstream status;
	if (depth.all > maxNestingDepth)
	{
		status.str("");
		status << "[Template::process] ERROR: Current nesting depth "
			<< depth.all << " exceeds maximum allowed nesting depth " 
			<< maxNestingDepth << ". (Use setMaxNestingDepth() to set "
			"a higher limit.)";
		log.msg(status.str(), log.VL_ERROR);
		return "";
	}
	if ((from > to) || (from < 0) || (to >= elements.size()))
	{
		status.str("");
		status << "[Template::process] ERROR: Invalid template element range ("
			<< from << ", " << to << ").";
		log.msg(status.str(), log.VL_ERROR);
		return "";
	}
	string result;
	TemplateElement *currentElement;
	Node *currentNode;
	int currentIndex;
	StringFilter *currentFilter;
	string currentData;
	string currentAssignExpr;
	int currentRef = 0;
	int currentCondition = 0;
	int nestingLevel = 0;
	int iterCount;
	int numIter;
	int iterationsTotal;
	TagNestingLevel newDepth;
	Node *iteratorNode;
	Node *sourceNode;
	Node *iterationCounter;
	Node *numIterations;
	Node *conditionNode;
	TemplateElement *openTag;
	StringSWrap swrap;
	vector<string> swrapArgs;
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
						   TODO: Find a more elegant solution to this issue. */
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
								currentData = currentNode->getData(currentIndex);
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
						status.str("");
						status << "[Template::process] ERROR: "
							"Variable substitution: Missing variable or "
							"parameter.";
						log.msg(status.str(), log.VL_ERROR);
						break;
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
						status.str("");
						status << "[Template::process] ERROR: "
							"foreach: Invalid opening tag.";
						log.msg(status.str(), log.VL_ERROR);
						break;
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
						status.str("");
						status << "[Template::process] ERROR: foreach: "
							"Invalid opening tag.";
						log.msg(status.str(), log.VL_ERROR);
						break;
					}
					if (openTag->type != TemplateElement::TE_FOREACH)
					{
						status.str("");
						status << "[Template::process] ERROR: foreach: "
							"Mismatched tag.";
						log.msg(status.str(), log.VL_ERROR);
						break;
					}
					if (openTag->vars.size() < 2)
					{
						status.str("");
						status << "[Template::process] ERROR: foreach: Missing "
							"arguments.";
						log.msg(status.str(), log.VL_ERROR);
						break;
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
						status.str("");
						status << "[Template::process] ERROR: foreach: Invalid "
							"arguments.";
						log.msg(status.str(), log.VL_ERROR);
						break;
					}
					// Data iteration.
					iterCount = 0;
					iterationCounter = root.node->findChild(
						ITERATION_COUNTER, false);
					log.assert(iterationCounter != 0, 
						"[Template::process] Iteration counter is null.");
					iterationCounter->setDataType(Node::NODE_DATA_INT);
					numIterations = root.node->findChild(
						NUM_ITERATIONS, false);
					log.assert(numIterations != 0, 
						"[Template::process] Number of iterations node "
						"is null.");
					iterationsTotal = sourceNode->getNumData()
							+ sourceNode->getNumChildren();
					numIterations->setDataType(Node::NODE_DATA_INT);
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
							iterationCounter = root.node->findChild(
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
						status.str("");
						status << "[Template::process] ERROR: if: Missing "
							"arguments.";
						log.msg(status.str(), log.VL_ERROR);
						break;
					}
					conditionNode = root.node->findChild(
						CONDITION_NODE, false);
					conditionNode->setDataType(Node::NODE_DATA_INT);
					log.assert(conditionNode != 0, 
						"[Template::process] Condition node is null.");
					eval(currentElement->params[1], 
						(*conditionNode)[depth.tagIf], false);
					if (((*conditionNode)[depth.tagIf].getDataType() 
							!= Node::NODE_DATA_INT)
						&& ((*conditionNode)[depth.tagIf].getDataType() 
							!= Node::NODE_DATA_DOUBLE))
					{
						status.str("");
						status << "[Template::process] WARNING: "
							"if: Condition does not evaluate to numeric "
							"value.";
						log.msg(status.str(), log.VL_WARNING);
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
						status.str("");
						status << "[Template::process] ERROR: "
							"if: Invalid opening tag.";
						log.msg(status.str(), log.VL_ERROR);
						break;
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
						status.str("");
						status << "[Template::process] ERROR: "
							"if: Invalid tag.";
						log.msg(status.str(), log.VL_ERROR);
						break;
					}
					if ((openTag->type != TemplateElement::TE_IF)
						&& (openTag->type != TemplateElement::TE_IF_ELSE))
					{
						status.str("");
						status << "[Template::process] ERROR: "
							"if: Mismatched tag.";
						log.msg(status.str(), log.VL_ERROR);
						break;
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
						status.str("");
						status << "[Template::process] ERROR: "
							"first: Invalid tag.";
						log.msg(status.str(), log.VL_ERROR);
						break;
					}
					if (openTag->type != TemplateElement::TE_FIRST)
					{
						status.str("");
						status << "[Template::process] ERROR: "
							"first: Mismatched tag.";
						log.msg(status.str(), log.VL_ERROR);
						break;
					}
					iterationCounter = root.node->findChild(
						ITERATION_COUNTER, false);
					log.assert(iterationCounter != 0, 
						"[Template::process] Iteration counter is null.");
					iterationCounter->setDataType(Node::NODE_DATA_INT);
					iterCount = iterationCounter->getInt(depth.tagForeach - 1);
					numIterations = root.node->findChild(
						NUM_ITERATIONS, false);
					log.assert(numIterations != 0, 
						"[Template::process] Number of iterations node "
						"is null.");
					numIter = numIterations->getInt(depth.tagForeach - 1);
					newDepth = depth;
					newDepth.tagFirst += 1;
					newDepth.all += 1;
					if ((iterCount == 0) && (numIter > 1))
						result.append(process(currentRef + 1, i - 1, newDepth));
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
						status.str("");
						status << "[Template::process] ERROR: "
							"mid: Invalid tag.";
						log.msg(status.str(), log.VL_ERROR);
						break;
					}
					if (openTag->type != TemplateElement::TE_MID)
					{
						status.str("");
						status << "[Template::process] ERROR: "
							"mid: Mismatched tag.";
						log.msg(status.str(), log.VL_ERROR);
						break;
					}
					iterationCounter = root.node->findChild(
						ITERATION_COUNTER, false);
					log.assert(iterationCounter != 0, 
						"[Template::process] Iteration counter is null.");
					iterationCounter->setDataType(Node::NODE_DATA_INT);
					iterCount = iterationCounter->getInt(depth.tagForeach - 1);
					numIterations = root.node->findChild(
						NUM_ITERATIONS, false);
					log.assert(numIterations != 0, 
						"[Template::process] Number of iterations node "
						"is null.");
					numIter = numIterations->getInt(depth.tagForeach - 1);
					newDepth = depth;
					newDepth.tagMid += 1;
					newDepth.all += 1;
					if ((iterCount != 0) && (iterCount != (numIter - 1)))
						result.append(process(currentRef + 1, i - 1, newDepth));
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
						status.str("");
						status << "[Template::process] ERROR: "
							"last: Invalid tag.";
						log.msg(status.str(), log.VL_ERROR);
						break;
					}
					if (openTag->type != TemplateElement::TE_LAST)
					{
						status.str("");
						status << "[Template::process] ERROR: "
							"last: Mismatched tag.";
						log.msg(status.str(), log.VL_ERROR);
						break;
					}
					iterationCounter = root.node->findChild(
						ITERATION_COUNTER, false);
					log.assert(iterationCounter != 0, 
						"[Template::process] Iteration counter is null.");
					iterationCounter->setDataType(Node::NODE_DATA_INT);
					iterCount = iterationCounter->getInt(depth.tagForeach - 1);
					numIterations = root.node->findChild(
						NUM_ITERATIONS, false);
					log.assert(numIterations != 0, 
						"[Template::process] Number of iterations node "
						"is null.");
					numIter = numIterations->getInt(depth.tagForeach - 1);
					newDepth = depth;
					newDepth.tagLast += 1;
					newDepth.all += 1;
					if ((iterCount == (numIter - 1)) && (numIter > 1))
						result.append(process(currentRef + 1, i - 1, newDepth));
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
						status.str("");
						status << "[Template::process] ERROR: "
							"single: Invalid tag.";
						log.msg(status.str(), log.VL_ERROR);
						break;
					}
					if (openTag->type != TemplateElement::TE_SINGLE)
					{
						status.str("");
						status << "[Template::process] ERROR: "
							"single: Mismatched tag.";
						log.msg(status.str(), log.VL_ERROR);
						break;
					}
					iterationCounter = root.node->findChild(
						ITERATION_COUNTER, false);
					log.assert(iterationCounter != 0, 
						"[Template::process] Iteration counter is null.");
					iterationCounter->setDataType(Node::NODE_DATA_INT);
					iterCount = iterationCounter->getInt(depth.tagForeach - 1);
					numIterations = root.node->findChild(
						NUM_ITERATIONS, false);
					log.assert(numIterations != 0, 
						"[Template::process] Number of iterations node "
						"is null.");
					numIter = numIterations->getInt(depth.tagForeach - 1);
					newDepth = depth;
					newDepth.tagSingle += 1;
					newDepth.all += 1;
					if (numIter == 1)
						result.append(process(currentRef + 1, i - 1, newDepth));
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
						status.str("");
						status << "[Template::process] ERROR: "
							"notfirst: Invalid tag.";
						log.msg(status.str(), log.VL_ERROR);
						break;
					}
					if (openTag->type != TemplateElement::TE_NOTFIRST)
					{
						status.str("");
						status << "[Template::process] ERROR: "
							"notfirst: Mismatched tag.";
						log.msg(status.str(), log.VL_ERROR);
						break;
					}
					iterationCounter = root.node->findChild(
						ITERATION_COUNTER, false);
					log.assert(iterationCounter != 0, 
						"[Template::process] Iteration counter is null.");
					iterationCounter->setDataType(Node::NODE_DATA_INT);
					iterCount = iterationCounter->getInt(depth.tagForeach - 1);
					newDepth = depth;
					newDepth.tagNotFirst += 1;
					newDepth.all += 1;
					if (iterCount != 0)
						result.append(process(currentRef + 1, i - 1, newDepth));
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
						status.str("");
						status << "[Template::process] ERROR: "
							"notmid: Invalid tag.";
						log.msg(status.str(), log.VL_ERROR);
						break;
					}
					if (openTag->type != TemplateElement::TE_NOTMID)
					{
						status.str("");
						status << "[Template::process] ERROR: "
							"notmid: Mismatched tag.";
						log.msg(status.str(), log.VL_ERROR);
						break;
					}
					iterationCounter = root.node->findChild(
						ITERATION_COUNTER, false);
					log.assert(iterationCounter != 0, 
						"[Template::process] Iteration counter is null.");
					iterationCounter->setDataType(Node::NODE_DATA_INT);
					iterCount = iterationCounter->getInt(depth.tagForeach - 1);
					numIterations = root.node->findChild(
						NUM_ITERATIONS, false);
					log.assert(numIterations != 0, 
						"[Template::process] Number of iterations node "
						"is null.");
					numIter = numIterations->getInt(depth.tagForeach - 1);
					newDepth = depth;
					newDepth.tagNotMid += 1;
					newDepth.all += 1;
					if ((iterCount == 0) || (iterCount == (numIter - 1)))
						result.append(process(currentRef + 1, i - 1, newDepth));
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
						status.str("");
						status << "[Template::process] ERROR: "
							"notlast: Invalid tag.";
						log.msg(status.str(), log.VL_ERROR);
						break;
					}
					if (openTag->type != TemplateElement::TE_NOTLAST)
					{
						status.str("");
						status << "[Template::process] ERROR: "
							"notlast: Mismatched tag.";
						log.msg(status.str(), log.VL_ERROR);
						break;
					}
					iterationCounter = root.node->findChild(
						ITERATION_COUNTER, false);
					log.assert(iterationCounter != 0, 
						"[Template::process] Iteration counter is null.");
					iterationCounter->setDataType(Node::NODE_DATA_INT);
					iterCount = iterationCounter->getInt(depth.tagForeach - 1);
					numIterations = root.node->findChild(
						NUM_ITERATIONS, false);
					log.assert(numIterations != 0, 
						"[Template::process] Number of iterations node "
						"is null.");
					numIter = numIterations->getInt(depth.tagForeach - 1);
					newDepth = depth;
					newDepth.tagNotLast += 1;
					newDepth.all += 1;
					if (iterCount != (numIter - 1))
						result.append(process(currentRef + 1, i - 1, newDepth));
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
						status.str("");
						status << "[Template::process] ERROR: "
							"notsingle: Invalid tag.";
						log.msg(status.str(), log.VL_ERROR);
						break;
					}
					if (openTag->type != TemplateElement::TE_NOTSINGLE)
					{
						status.str("");
						status << "[Template::process] ERROR: "
							"notsingle: Mismatched tag.";
						log.msg(status.str(), log.VL_ERROR);
						break;
					}
					iterationCounter = root.node->findChild(
						ITERATION_COUNTER, false);
					log.assert(iterationCounter != 0, 
						"[Template::process] Iteration counter is null.");
					iterationCounter->setDataType(Node::NODE_DATA_INT);
					iterCount = iterationCounter->getInt(depth.tagForeach - 1);
					numIterations = root.node->findChild(
						NUM_ITERATIONS, false);
					log.assert(numIterations != 0, 
						"[Template::process] Number of iterations node "
						"is null.");
					numIter = numIterations->getInt(depth.tagForeach - 1);
					newDepth = depth;
					newDepth.tagNotSingle += 1;
					newDepth.all += 1;
					if (numIter > 1)
						result.append(process(currentRef + 1, i - 1, newDepth));
					break;
				case TemplateElement::TE_SWRAP:
					// swrap.
					nestingLevel++;
					if (nestingLevel != 1)
						break;
					currentRef = i;
					if (currentElement->params.size() < 4)
					{
						status.str("");
						status << "[Template::process] ERROR: swrap: Missing "
							"arguments.";
						log.msg(status.str(), log.VL_ERROR);
						break;
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
						status.str("");
						status << "[Template::process] ERROR: "
							"swrap: Invalid tag.";
						log.msg(status.str(), log.VL_ERROR);
						break;
					}
					if (openTag->type != TemplateElement::TE_SWRAP)
					{
						status.str("");
						status << "[Template::process] ERROR: "
							"swrap: Mismatched tag.";
						log.msg(status.str(), log.VL_ERROR);
						break;
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
						status.str("");
						status << "[Template::process] ERROR: section: Missing "
							"arguments.";
						log.msg(status.str(), log.VL_ERROR);
						break;
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
						status.str("");
						status << "[Template::process] ERROR: "
							"section: Invalid tag.";
						log.msg(status.str(), log.VL_ERROR);
						break;
					}
					if (openTag->type != TemplateElement::TE_SECTION)
					{
						status.str("");
						status << "[Template::process] ERROR: "
							"section: Mismatched tag.";
						log.msg(status.str(), log.VL_ERROR);
						break;
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
						status.str("");
						status << "[Template::process] ERROR: ref: Missing "
							"arguments.";
						log.msg(status.str(), log.VL_ERROR);
						break;
					}
					sectionIter = sections.find(currentElement->params[1]);
					if (sectionIter == sections.end())
					{
						status.str("");
						status << "[Template::process] ERROR: ref: Section '"
							<< currentElement->params[1] << "' not defined.";
						log.msg(status.str(), log.VL_ERROR);
						break;
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
						saveConfig = *root.node;
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
						*root.node = saveConfig;
						/* ----- DEBUG ----- //
						cerr << "[Template::process] DEBUG: (ref) "
							"Finished restoring environment." << endl;
						// ----- DEBUG ----- */
					}
					break;
				default:
					status.str("");
					status << "[Template::process] WARNING: Unknown template "
						"element type: " << currentElement->type << ".";
					log.msg(status.str(), log.VL_WARNING);
			}
		}
	}
	return result;
}

void Template::readTemplate(const std::string& templateFileName,
	std::vector<TemplateElement *> &target)
{
	templateInput = readFile(templateFileName);
	parse(target);
}

void Template::readTemplate(const std::string& templateFileName)
{
	readTemplate(templateFileName, elements);
}

void Template::setTemplate(const std::string& newTemplate,
	std::vector<TemplateElement *> &target)
{
	templateInput = newTemplate;
	parse(target);
}

void Template::setTemplate(const std::string& newTemplate)
{
	setTemplate(newTemplate, elements);
}

std::string Template::process(const std::string& newTemplate,
	Node* newConfig)
{
	if (newTemplate.size() > 0)
		setTemplate(newTemplate);
	if ((newConfig != 0) && (root.node != 0))
	{
		*root.node = *newConfig;
		root.node->setAutoCreate(true);
		root.node->setIndexMode(Node::INDEX_MODE_NODE);
	}
	TagNestingLevel depth;
	return process(0, elements.size() - 1, depth);
}

void Template::setMaxNestingDepth(unsigned int newMaxNestingDepth)
{
	maxNestingDepth = newMaxNestingDepth;
}

unsigned int Template::getMaxNestingDepth()
{
	return maxNestingDepth;
}

void Template::printElementDebugInfo()
{
	Node *currentNode;
	int currentIndex;
	StringFilter *currentFilter;
	cout << "Number of elements: " << elements.size() << endl;
	for (unsigned int i = 0; i < elements.size(); i++)
	{
		cout << "[" << i << "]:" << endl
			<< "    type: " << elements[i]->type << endl
			<< "    parameters:" << endl;
		for (unsigned int k = 0; k < elements[i]->params.size(); k++)
		{
			cout << "        [" << k << "]: '" << elements[i]->params[k] 
				<< "'" << endl;
		}
		cout << "    variables:" << endl;
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
				cout << "        [" << k << "]: ";
				if (currentNode != 0)
				{
					cout << currentNode->getPath();
					if (currentIndex != 0)
					 cout << "[" << currentIndex << "]";
				}
				else
					cout << "(null)";
				cout << endl;
				cout << "            filter: ";
				if (currentFilter != 0)
				{
					cout << "yes" << endl;
					currentFilter->printDebugInfo();
				} else
					cout << "(null)" << endl;
			}
		} else
			cout << "        (none)" << endl;
		cout << "    references:" << endl;
		if (elements[i]->refs.size() > 0)
		{
			for (unsigned int k = 0; k < elements[i]->refs.size(); k++)
			{
				cout << "        [" << k << "]: " << elements[i]->refs[k] 
					<< endl;
			}
		} else
			cout << "        (none)" << endl;
	}
}

Reporter &Template::getLog()
{
	return log;
}

}

}

/** \file Template.cpp
 * \brief Template processor implementation.
 */
