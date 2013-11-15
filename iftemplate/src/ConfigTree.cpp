/* ==========================================================================
 * IFTemplate - Ionflux Template Processor
 * Copyright © 2012 Jörn P. Meier
 * mail@ionflux.org
 * --------------------------------------------------------------------------
 * ConfigTree.cpp                  Configuration tree (implementation).
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

#include "iftemplate/ConfigTree.hpp"
#include <iostream>
#include <iomanip>
#include <sstream>
#include <fstream>
#include "ifobject/utils.hpp"
#include "iftemplate/utils.hpp"
#include "iftemplate/Node.hpp"
#include "iftemplate/IFTemplateError.hpp"

using namespace std;

namespace Ionflux
{

namespace Template
{

ConfigTreeClassInfo::ConfigTreeClassInfo()
{
	name = "ConfigTree";
	desc = "Configuration tree";
}

ConfigTreeClassInfo::~ConfigTreeClassInfo()
{
}

// public member constants
const Ionflux::Template::TokenType ConfigTree::TT_COMMENT = { TT_ID_USERTYPE + 1, "#", false, 1 };
const Ionflux::Template::TokenType ConfigTree::TT_ASSIGN = { TT_ID_USERTYPE + 2, "=", false, 1 };
const Ionflux::Template::TokenType ConfigTree::TT_MULTILINE = { TT_ID_USERTYPE + 3, "\\", false, 1 };
const Ionflux::Template::TokenType ConfigTree::TT_TREEPATH = { TT_ID_USERTYPE + 4, ".[]()", false, 0 };
const Ionflux::Template::TokenType ConfigTree::TT_NESTED_OPEN = { TT_ID_USERTYPE + 5, "{", false, 1 };
const Ionflux::Template::TokenType ConfigTree::TT_NESTED_CLOSE = { TT_ID_USERTYPE + 6, "}", false, 1 };
const Ionflux::Template::TokenType ConfigTree::TT_VERBATIM_OPEN = { TT_ID_USERTYPE + 7, "<", false, 3 };
const Ionflux::Template::TokenType ConfigTree::TT_VERBATIM_CLOSE = { TT_ID_USERTYPE + 8, ">", false, 3 };
const std::string ConfigTree::AUTO_INSERT_MARKER = "# ------- Values inserted automatically by the "
    "configuration system --------";
const std::string ConfigTree::SPECIAL_VALUE_CHARS = "{}<>\n";

// run-time type information instance constants
const ConfigTreeClassInfo ConfigTree::configTreeClassInfo;
const Ionflux::ObjectBase::IFClassInfo* ConfigTree::CLASS_INFO = &ConfigTree::configTreeClassInfo;

ConfigTree::ConfigTree()
{
	// NOTE: The following line is required for run-time type information.
	theClass = CLASS_INFO;
	if (root == 0)
	    throw IFTemplateError("[ConfigTree::ConfigTree] Root node is null.");
	root->setAutoCreate(true);
	root->setIndexMode(Node::INDEX_MODE_NODE);
	tok.addTokenType(TT_COMMENT);
	tok.addTokenType(TT_ASSIGN);
	tok.addTokenType(TT_MULTILINE);
	tok.addTokenType(TT_TREEPATH);
	tok.addTokenType(TT_NESTED_OPEN);
	tok.addTokenType(TT_NESTED_CLOSE);
	tok.addTokenType(TT_VERBATIM_OPEN);
	tok.addTokenType(TT_VERBATIM_CLOSE);
	tok.setTokenTypeAnything();
	tok.setExtractQuoted(true);
}

ConfigTree::ConfigTree(const Ionflux::Template::ConfigTree& other)
{
	// NOTE: The following line is required for run-time type information.
	theClass = CLASS_INFO;
	*this = other;
}

ConfigTree::~ConfigTree()
{
	// TODO: Nothing ATM. ;-)
}

int ConfigTree::findFirstLine(Ionflux::Template::Node* searchNode)
{
	if (searchNode == 0)
	    return -1;
	int result = -1;
	unsigned int i = 0;
	bool found = false;
	while (!found && (i < entries.size()))
	{
	    if ((entries[i].line.type == ConfigLine::CL_OPTION)
	        && (entries[i].data.node == searchNode))
	        found = true;
	    else
	        i++;
	}
	if (found)
	    result = i;
	return result;
}

int ConfigTree::findLastLine(Ionflux::Template::Node* searchNode)
{
	if (searchNode == 0)
			return -1;
		int result = -1;
		for (unsigned int i = 0; i < entries.size(); i++)
			if ((entries[i].line.type == ConfigLine::CL_OPTION)
				&& (entries[i].data.node == searchNode))
				result = i;
	return result;
}

int ConfigTree::getAutoInsertPos()
{
	int result = -1;
	for (unsigned int i = 0; i < entries.size(); i++)
	    if ((entries[i].line.type == ConfigLine::CL_COMMENT)
	        && (entries[i].line.option.value == AUTO_INSERT_MARKER))
	        result = i;
	if (result == -1)
	{
	    // Auto-insertion marker missing; add it after a blank line.
	    ConfigTreeEntry newEntry;
	    newEntry.line.type = ConfigLine::CL_BLANK;
	    newEntry.line.option.key = "<blank>";
	    newEntry.line.option.value = "";
	    newEntry.data.node = 0;
	    newEntry.data.index = 0;
	    entries.push_back(newEntry);
	    newEntry.line.type = ConfigLine::CL_COMMENT;
	    newEntry.line.option.key = "<comment>";
	    newEntry.line.option.value = AUTO_INSERT_MARKER;
	    entries.push_back(newEntry);
	    result = entries.size() - 1;
	}
	return result;
}

void ConfigTree::clear()
{
	inputFile = "";
	entries.clear();
	root->removeAllChildren(true);
	root->clearData(false);
}

void ConfigTree::parseConfig(const std::string& configData, unsigned int 
lineOffset)
{
	std::ostringstream status;
	ConfigTreeEntry currentEntry;
	tok.setInput(configData);
	Token currentToken = tok.getNextToken();
	bool error = false;
	bool lineError = false;
	unsigned int lineCount = 1;
	unsigned int nestingLevel = 0;
	unsigned int nestedLines = 0;
	ConfigTree *nestedTree = 0;
	Node *nestedRoot = 0;
	// Node *currentChild = 0;
	while (isNonEmpty(currentToken) && !error)
	{
	    /* ----- DEBUG ----- //
	    status.str("");
	    status << "[ConfigTree::parseConfigLine] DEBUG: Parsing line "
	        << lineCount << ".";
	    log.msg(status.str(), log.VL_DEBUG_INSANE);
	    // ----- DEBUG ----- */
	    // Skip leading whitespace.
	    while (currentToken.typeID == TT_WHITESPACE.typeID)
	        currentToken = tok.getNextToken();
	    // Check token type.
	    if (currentToken.typeID == TT_LINETERM.typeID)
	    {
	        // Blank line.
	        if (currentToken.value[0] == '\r')
	            // File has peculiar line terminators, so we skip a token.
	            currentToken = tok.getNextToken();
	        if ((currentToken.typeID == TT_LINETERM.typeID)
	            && currentToken.value[0] == '\n')
	            currentToken = tok.getNextToken();
	        currentEntry.line.type = ConfigLine::CL_BLANK;
	        currentEntry.line.option.key = "<blank>";
	        currentEntry.line.option.value = "";
	        currentEntry.data.node = 0;
	        currentEntry.data.index = 0;
	        /* <---- DEBUG ----- //
	        status.str("");
	        status << "[ConfigTree::parseConfigLine] DEBUG: (Line " 
	            << lineCount << ") type: CL_BLANK.";
	        log.msg(status.str(), log.VL_DEBUG_INSANE);
	        // ----- DEBUG ----> */
	        lineCount++;
	    } else
	    if (currentToken.typeID == TT_COMMENT.typeID)
	    {
	        // Extract comment.
	        currentEntry.line.type = ConfigLine::CL_COMMENT;
	        currentEntry.line.option.key = "<comment>";
	        currentEntry.line.option.value = "";
	        currentEntry.data.node = 0;
	        currentEntry.data.index = 0;
	        tok.setExtractQuoted(false);
	        while ((currentToken.typeID != TT_NONE.typeID)
	            && (currentToken.typeID != TT_INVALID.typeID)
	            && (currentToken.typeID != TT_LINETERM.typeID))
	        {
	            /* ----- DEBUG ----- //
	            status.str("");
	            status << "[ConfigTree::parseConfigLine] DEBUG: typeID = "
	                << currentToken.typeID 
	                << ", value = '" << currentToken.value << "'";
	            log.msg(status.str(), log.VL_DEBUG_INSANE);
	            // ----- DEBUG ----- */
	            currentEntry.line.option.value.append(currentToken.value);
	            currentToken = tok.getNextToken();
	        }
	        /* ----- DEBUG ----- //
	        status.str("");
	        status << "[ConfigTree::parseConfigLine] DEBUG: comment = "
	            << currentEntry.line.option.value;
	        log.msg(status.str(), log.VL_DEBUG_INSANE);
	        // ----- DEBUG ----- */
	        tok.setExtractQuoted(true);
	        /* <---- DEBUG ----- //
	        status.str("");
	        status << "[ConfigTree::parseConfigLine] DEBUG: (Line " 
	            << lineCount << ") type: CL_COMMENT.";
	        log.msg(status.str(), log.VL_DEBUG_INSANE);
	        // ----- DEBUG ----> */
	    } else
	    if (currentToken.typeID == TT_QUOTED.typeID)
	    {
	        // Extract root data.
	        currentEntry.line.type = ConfigLine::CL_ROOT_DATA;
	        currentEntry.line.option.key = "";
	        currentEntry.line.option.value = "";
	        currentEntry.data.node = 0;
	        currentEntry.data.index = 0;
	        while (currentToken.typeID == TT_QUOTED.typeID)
	        {
	            currentEntry.line.option.value.append(currentToken.value);
	            currentToken = tok.getNextToken();
	            // Ignore inline whitespace.
	            while (currentToken.typeID == TT_WHITESPACE.typeID)
	                currentToken = tok.getNextToken();
	        }
	        /* <---- DEBUG ----- //
	        status.str("");
	        status << "[ConfigTree::parseConfigLine] DEBUG: (Line " 
	            << lineCount << ") type: CL_ROOT_DATA.";
	        log.msg(status.str(), log.VL_DEBUG_INSANE);
	        // ----- DEBUG ----> */
	    } else
	    if ((currentToken.typeID == TT_TREEPATH.typeID)
	        || (currentToken.typeID == TT_IDENTIFIER.typeID)
	        || (currentToken.typeID == TT_ESCAPED.typeID))
	    {
	        // Extract option.
	        currentEntry.line.type = ConfigLine::CL_OPTION;
	        currentEntry.line.option.key = "";
	        currentEntry.line.option.value = "";
	        currentEntry.data.node = 0;
	        currentEntry.data.index = 0;
	        // Extract key.
	        /* <---- DEBUG ----- //
	        log.msg("[ConfigTree::parseConfigLine] DEBUG: Extracting key.", 
	            log.VL_DEBUG_INSANE);
	        // ----- DEBUG ----> */
	        char quoteChar = 0;
	        while ((currentToken.typeID == TT_TREEPATH.typeID)
	            || (currentToken.typeID == TT_IDENTIFIER.typeID)
	            || (currentToken.typeID == TT_QUOTED.typeID)
	            || (currentToken.typeID == TT_ESCAPED.typeID))
	        {
	            quoteChar = tok.getQuoteChar();
	            if (quoteChar != 0)
	                // Preserve quoted strings.
	                currentEntry.line.option.key.append(1, quoteChar);
	            currentEntry.line.option.key.append(currentToken.value);
	            if (quoteChar != 0)
	                currentEntry.line.option.key.append(1, quoteChar);
	            currentToken = tok.getNextToken();
	        }
	        /* ----- DEBUG ----- //
	        status.str("");
	        status << "[ConfigTree::parseConfigLine] DEBUG: key = "
	            << currentEntry.line.option.key;
	        log.msg(status.str(), log.VL_DEBUG_INSANE);
	        // ----- DEBUG ----- */
	        while (currentToken.typeID == TT_WHITESPACE.typeID)
	            currentToken = tok.getNextToken();
	        // If assignment operator is present, extract value.
	        if (currentToken.typeID != TT_ASSIGN.typeID)
	            lineError = true;
	        else 
	        {
	            /* Disable quoted string extraction since we want the 
	               option value verbatim. Enable escaped character extraction 
	               so nesting operators or newlines may be escaped. */
	            tok.setExtractQuoted(false);
	            tok.setExtractEscaped(true);
	            currentToken = tok.getNextToken();
	            while (currentToken.typeID == TT_WHITESPACE.typeID)
	                currentToken = tok.getNextToken();
	            // Extract value.
	            /* <---- DEBUG ----- //
	            log.msg("[ConfigTree::parseConfigLine] DEBUG: Extracting "
	                "value.", log.VL_DEBUG_INSANE);
	            // ----- DEBUG ----> */
	            if (currentToken.typeID == TT_NESTED_OPEN.typeID)
	            {
	                // Extract nested configuration.
	                currentEntry.line.type = ConfigLine::CL_NESTED;
	                nestingLevel = 1;
	                /* Disable escaped character extraction since we need 
	                   everything inside the nesting block verbatim. */
	                //tok.setExtractEscaped(false);
	                currentToken = tok.getNextToken();
	                while (isNonEmpty(currentToken) 
	                    && (nestingLevel > 0))
	                {
	                    if (currentToken.typeID == TT_NESTED_CLOSE.typeID)
	                        nestingLevel--;
	                    else
	                    if (currentToken.typeID == TT_NESTED_OPEN.typeID)
	                        nestingLevel++;
	                    else
	                    if ((currentToken.typeID == TT_LINETERM.typeID) 
	                        && (currentToken.value[0] == '\n'))
	                        nestedLines++;
	                    if (currentToken.typeID == TT_ESCAPED.typeID)
	                        currentEntry.line.option.value.append(
	                            1, ESCAPE_CHAR);
	                    if (nestingLevel != 0)
	                        currentEntry.line.option.value.append(
	                            currentToken.value);
	                    currentToken = tok.getNextToken();
	                }
	                if (nestingLevel != 0)
	                {
	                    error = true;
	                    status.str("");
	                    status << "[ConfigTree::parseConfigLine] "
	                        "Parse error in line " << (lineCount + lineOffset)
	                        << ": Mismatched nesting quotes.";
	                    throw IFTemplateError(status.str());
	                }
	                /* <---- DEBUG ----- //
	                status.str("");
	                status << "[ConfigTree::parseConfigLine] DEBUG: (Line " 
	                    << lineCount << ") type: CL_NESTED.";
	                log.msg(status.str(), log.VL_DEBUG_INSANE);
	                // ----- DEBUG ----> */
	            } else
	            {
	                // Extract option value.
	                /* verbatim state
	                   0 - none
	                   1 - open
	                   2 - closed
	                 */
	                int verbatim = 0;
	                while ((currentToken.typeID != TT_NONE.typeID)
	                    && (currentToken.typeID != TT_INVALID.typeID)
	                    && ((verbatim == 1) 
	                        || (currentToken.typeID 
	                            != TT_LINETERM.typeID))
	                    && (verbatim < 2))
	                {
	                    if (currentToken.typeID == TT_ESCAPED.typeID)
	                    {
	                        if ((currentToken.value.size() > 0)
	                            && (currentToken.value[0] == '\r'))
	                        {
	                            /* We have a peculiar line terminator, so we 
	                               skip a token. */
	                            currentEntry.line.option.value.append(
	                                currentToken.value);
	                            currentToken = tok.getNextToken();
	                        } else
	                        if (((currentToken.value.size() > 0)
	                                && (currentToken.value[0] != '\n')
	                                && (currentToken.value[0] 
	                                    != TT_NESTED_OPEN.validChars[0])
	                                && (currentToken.value[0] 
	                                    != TT_NESTED_CLOSE.validChars[0])
	                                && (currentToken.value[0] 
	                                    != TT_VERBATIM_OPEN.validChars[0])
	                                && (currentToken.value[0] 
	                                    != TT_VERBATIM_CLOSE.validChars[0])
	                                && (currentToken.value[0] 
	                                    != ESCAPE_CHAR))
	                            || (currentToken.value.size() == 0))
	                        {
	                            /* Append the escape character, since it does 
	                               not initiate a valid escape sequence (this 
	                               is somehow inconsistent, but I'll leave it 
	                               for now, since all of this is going to be 
	                               rewritten). */
	                            currentEntry.line.option.value.append(1, 
	                                ESCAPE_CHAR);
	                        }
	                    } else
	                    if ((currentToken.typeID == TT_VERBATIM_OPEN.typeID) 
	                        && (currentToken.value.size() == 3))
	                    {
	                        // Extract verbatim token value.
	                        verbatim = 1;
	                        currentToken = tok.getNextToken();
	                        if (currentToken.typeID == 
	                            TT_LINETERM.typeID)
	                            // Skip the first lineterm.
	                            currentToken = tok.getNextToken();
	                    } else
	                    if (verbatim 
	                        && (currentToken.typeID 
	                            == TT_VERBATIM_CLOSE.typeID) 
	                        && (currentToken.value.size() == 3))
	                    {
	                        // End of verbatim token value.
	                        verbatim = 2;
	                    }
	                    if (verbatim < 2)
	                        currentEntry.line.option.value.append(
	                            currentToken.value);
	                    currentToken = tok.getNextToken();
	                }
	                /* <---- DEBUG ----- //
	                status.str("");
	                status << "[ConfigTree::parseConfigLine] DEBUG: (Line " 
	                    << lineCount << ") type: CL_OPTION.";
	                log.msg(status.str(), log.VL_DEBUG_INSANE);
	                // ----- DEBUG ----> */
	            }
	            // Reset quoting and escaping.
	            tok.setExtractQuoted(true);
	            tok.setExtractEscaped(false);
	        }
	        // Strip leading and trailing whitespace.
	        currentEntry.line.option.value = 
	            Ionflux::ObjectBase::trim(currentEntry.line.option.value, 0);
	        /* ----- DEBUG ----- //
	        status.str("");
	        status << "[ConfigTree::parseConfigLine] DEBUG: value = "
	            << currentEntry.line.option.value;
	        log.msg(status.str(), log.VL_DEBUG_INSANE);
	        // ----- DEBUG ----- */
	    } else
	    {
	        error = true;
	        status.str("");
	        status << "[ConfigTree::parseConfigLine] Parse error in "
	            "line " << (lineCount + lineOffset) << ": Unexpected token '" 
	            << currentToken.value << "'.";
	        throw IFTemplateError(status.str());
	    }
	    if (lineError || (currentToken.typeID == TT_INVALID.typeID))
	    {
	        /* <---- DEBUG ----- //
	        status.str("");
	        status << "[ConfigTree::parseConfigLine] DEBUG: (Line " 
	            << lineCount << ") type: CL_INVALID.";
	        log.msg(status.str(), log.VL_DEBUG_INSANE);
	        // ----- DEBUG ----> */
	    } else
	    if (currentEntry.line.type == ConfigLine::CL_OPTION)
	    {
	        // Resolve and set data entry.
	        currentEntry.data = resolve(currentEntry.line.option.key, false);
	        if (currentEntry.data.node == 0)
	        {
	            status.str("");
	            status << "[ConfigTree::parseConfigLine] "
	                "Could not resolve node '" << 
	currentEntry.line.option.key;
	            throw IFTemplateError(status.str());
	        }
	        currentEntry.data.node->setData(currentEntry.data.index, 
	            currentEntry.line.option.value);
	        entries.push_back(currentEntry);
	    } else
	    if (currentEntry.line.type == ConfigLine::CL_NESTED)
	    {
	        // Resolve nested configuration.
	        currentEntry.data = resolve(currentEntry.line.option.key, 
	            false, true);
	        if (currentEntry.data.node == 0)
	        {
	            status.str("");
	            status << "[ConfigTree::parseConfigLine] "
	                "Could not resolve node '" 
	                << currentEntry.line.option.key;
	            throw IFTemplateError(status.str());
	        }
	        /* <---- TESTING ----- //
	        if (currentEntry.data.subscript)
	        {
	            // ----- DEBUG ----- //
	            cout << "[ConfigTree::parseConfigLine] DEBUG: "
	                "Nested configuration subscript = " 
	                << currentEntry.data.index << endl;
	            // ----- DEBUG ----- //
	            // We need a child node for nested configuration, 
	            // even if the reference contains a subscript.
	            currentChild = currentEntry.data.node->findChild(
	                currentEntry.data.index, false);
	            if (log.assert(currentEntry.data.node != 0, 
	                "[ConfigTree::parseConfigLine] Could not "
	                "resolve nested configuration node!"))
	            {
	                currentEntry.data.node = currentChild;
	                currentEntry.data.index = false;
	            }
	        }
	        // ----- TESTING ----> */
	        nestedTree = ConfigTree::create(this);
	        nestedTree->parseConfig(currentEntry.line.option.value, 
	            lineCount - 1);
	        nestedRoot = nestedTree->getRoot();
	        /* <---- DEBUG ----- //
	        std::cerr << "[ConfigTree::parseConfigLine] DEBUG: "
	            "Created nested tree " << nestedTree << " (root = " 
	            << nestedRoot << ")" << std::endl;
	        // ----- DEBUG ----- */
	        if (nestedRoot == 0)
	            throw IFTemplateError(getErrorString(
	                "Nested tree root node pointer is null.", 
	                    "parseConfigLine"));
	        *currentEntry.data.node = *nestedRoot;
	        entries.push_back(currentEntry);
	        /* <---- DEBUG ----- //
	        std::cerr << "[ConfigTree::parseConfigLine] DEBUG: "
	            "Deleting nested tree " << nestedTree 
	            << std::endl;
	        // ----- DEBUG ----- */
	        removeLocalRef(nestedTree);
	        /* <---- DEBUG ----- //
	        std::cerr << "[ConfigTree::parseConfigLine] DEBUG: "
	            "Deleted nested tree." << std::endl;
	        // ----- DEBUG ----- */
	        lineCount += nestedLines;
	        nestedLines = 0;
	    } else
	    if (currentEntry.line.type == ConfigLine::CL_ROOT_DATA)
	    {
	        // Add root data.
	        root->addData(currentEntry.line.option.value);
	        entries.push_back(currentEntry);
	    } else
	    if ((currentEntry.line.type == ConfigLine::CL_COMMENT)
	        || (currentEntry.line.type == ConfigLine::CL_BLANK))
	    {
	        entries.push_back(currentEntry);
	    } else
	        throw IFTemplateError("[ConfigTree::parseConfigLine] "
	            "Invalid line type.");
	    // Skip line terminator.
	    if (currentToken.typeID == TT_LINETERM.typeID)
	    {
	        if (currentToken.value[0] == '\r')
	            // File has peculiar line terminators, so we skip a token.
	            currentToken = tok.getNextToken();
	        if ((currentToken.typeID == TT_LINETERM.typeID)
	            && (currentToken.value[0] == '\n'))
	            currentToken = tok.getNextToken();
	        lineCount++;
	    }
	}
}

bool ConfigTree::readConfig(const std::string& configFile)
{
	if (configFile == "")
	    throw IFTemplateError("[ConfigTree::readConfig] "
	        "File name is an empty string.");
	std::string inputFileData;
	Ionflux::ObjectBase::readFile(configFile, inputFileData);
	if (inputFileData == "")
	{
	    std::ostringstream status;
	    status << "[ConfigTree::readConfig] "
	        "Could not read from file '" << configFile << "', or file "
	        "does not contain any data!";
	    throw IFTemplateError(status.str());
	}
	clear();
	inputFile = configFile;
	parseConfig(inputFileData);
	return true;
}

void ConfigTree::writeConfig(const std::string& configFile)
{
	std::ostringstream status;
	std::ofstream configFileStream(configFile.c_str());
	if (!configFileStream)
	{
	    status.str("");
	    status << "[ConfigTree::writeConfig] Could write to file '" 
	        << configFile << "'";
	    throw IFTemplateError(status.str());
	}
	// Update the configuration table.
	root->traverse(this, Node::TRAVERSAL_PREORDER);
	/* Write configuration table to file.
	   TODO: Handle nested configuration and root data entries. */
	ConfigTreeEntryVector::const_iterator i;
	for (i = entries.begin(); i != entries.end(); i++)
	{
	    if (((*i).line.type == ConfigLine::CL_COMMENT)
	        || ((*i).line.type == ConfigLine::CL_BLANK))
	    {
	        configFileStream << (*i).line.option.value << endl;
	    } else
	    if ((*i).line.type == ConfigLine::CL_OPTION)
	    {
	        configFileStream << (*i).line.option.key << " = " 
	            << (*i).line.option.value << endl;
	    }
	}
	configFileStream.flush();
}

void ConfigTree::writeConfig()
{
	if (inputFile != "")
	    writeConfig(inputFile);
}

std::string ConfigTree::get(const std::string& key)
{
	std::ostringstream status;
	DataEntry result = resolve(key, false);
	if (result.node == 0)
	{
	    status.str("");
	    status << "[ConfigTree::parseConfigLine] Could not resolve "
	        "node '" << key << "'! (This shouldn't happen!)";
	    throw IFTemplateError(status.str());
	}
	return result.node->getData(result.index);
}

void ConfigTree::set(const std::string& key, const std::string& value)
{
	DataEntry result = resolve(key, false);
	if (result.node == 0)
	{
	    std::ostringstream status;
	    status << "[ConfigTree::parseConfigLine] "
	        "Could not resolve node '" + key + "'!";
	    throw IFTemplateError(status.str());
	}
	result.node->setData(result.index, value);
}

void ConfigTree::dump(Ionflux::Template::Node* node)
{
	if (node == 0)
	    return;
	int first = findFirstLine(node);
	int last = findLastLine(node);
	vector<ConfigTreeEntry>::iterator insertPos;
	if (last != -1)
	{
	    // Node exists in file; remove all entries for this node.
	    entries.erase(entries.begin() + first, entries.begin() + last + 1);
	    insertPos = entries.begin() + first;
	} else
	{
	    /* Node doesn't exist in file; find a suitable position for 
	       insertion of this node (i.e. the last line of the parent node). */
	    Node *currentNode = node->getParent();
	    while ((currentNode != 0) && (last == -1))
	    {
	        last = findLastLine(currentNode);
	        currentNode = currentNode->getParent();
	    }
	    if (last == -1)
	        last = getAutoInsertPos();
	    insertPos = entries.begin() + last + 1;
	}
	int numData = node->getNumData();
	ConfigTreeEntry currentEntry;
	currentEntry.line.type = ConfigLine::CL_OPTION;
	if (numData == 1)
	{
	    // Insert a single data entry.
	    currentEntry.line.option.key = node->getPath();
	    currentEntry.line.option.value = escapeValue(node->getData());
	    currentEntry.data.node = node;
	    currentEntry.data.index = 0;
	    entries.insert(insertPos, currentEntry);
	} else
	{
	    // Insert all data entries.
	    ostringstream currentKey;
	    string currentData;
	    for (int i = numData; i >= 0; i--)
	    {
	        currentData = escapeValue(node->getData(i));
	        if (currentData.size() > 0)
	        {
	            currentKey.str("");
	            currentKey << node->getPath() << "[" << i << "]";
	            currentEntry.line.option.key = currentKey.str();
	            currentEntry.line.option.value = currentData;
	            currentEntry.data.node = node;
	            currentEntry.data.index = i;
	            insertPos = entries.insert(insertPos, currentEntry);
	        }
	    }
	}
}

std::string ConfigTree::escapeValue(const std::string& value)
{
	// TODO: Implementation.
	return Ionflux::ObjectBase::escape(value, SPECIAL_VALUE_CHARS);
}

Ionflux::Template::ConfigTree& ConfigTree::operator=(const 
Ionflux::Template::ConfigTree& other)
{
if (this == &other)
    return *this;
	return *this;
}

Ionflux::Template::ConfigTree* ConfigTree::copy() const
{
    ConfigTree* newConfigTree = create();
    *newConfigTree = *this;
    return newConfigTree;
}

Ionflux::Template::ConfigTree* 
ConfigTree::upcast(Ionflux::ObjectBase::IFObject* other)
{
    return dynamic_cast<ConfigTree*>(other);
}

Ionflux::Template::ConfigTree* 
ConfigTree::create(Ionflux::ObjectBase::IFObject* parentObject)
{
    ConfigTree* newObject = new ConfigTree();
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

/** \file ConfigTree.cpp
 * \brief Configuration tree implementation.
 */
