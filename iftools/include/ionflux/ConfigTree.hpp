#ifndef IONFLUX_TOOLS_CONFIGTREE
#define IONFLUX_TOOLS_CONFIGTREE
/* ==========================================================================
 * Ionflux Tools
 * Copyright (c) 2004 Joern P. Meier
 * mail@ionflux.org
 * --------------------------------------------------------------------------
 * ConfigTree.hpp                    Configuration tree.
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
#include "ionflux/tools.hpp"
#include "ionflux/Config.hpp"
#include "ionflux/Tree.hpp"
#include "ionflux/NodeDump.hpp"
#include "ionflux/Tokenizer.hpp"
#include "ionflux/StringManipulator.hpp"

namespace Ionflux
{

namespace Tools
{

/** Configuration tree entry.
 * \ingroup cfgfileio
 *
 * Maps a line of a configuration file to a tree data entry (if available).
 *
 * \note If the configuration line represents a comment, the node of the data 
 * entry is set to 0.
 */
struct ConfigTreeEntry
{
	/// Configuration file line.
	ConfigLine line;
	/// Data entry corresponding to the configuration line.
	DataEntry data;
};

/** Configuration tree.
 * \ingroup cfgfileio
 *
 * A tree containing configuration data. (See \ref configdoc for details)
 */
class ConfigTree
: public Tree, public Config, public NodeDump
{
	protected:
		/// Configuration source file.
		std::string inputFile;
		/// Configuration line tokenizer.
		Tokenizer tok;
		/// Vector of configuration tree entries.
		std::vector<ConfigTreeEntry> entries;
		
		/** Find a configuration line.
		 *
		 * Searches for the first line in the configuration file that defines 
		 * the specified node. Returns -1 if the node is not found.
		 *
		 * \param searchNode The node to search for.
		 *
		 * \return Line number where the specified node is first defined, 
		 * or -1, if the node is not found.
		 */
		virtual int findFirstLine(Node *searchNode);
		
		/** Find a configuration line.
		 *
		 * Searches for the last line in the configuration file that defines 
		 * the specified node. Returns -1 if the node is not found.
		 *
		 * \param searchNode The node to search for.
		 *
		 * \return Line number where the specified node is last defined, 
		 * or -1, if the node is not found.
		 */
		virtual int findLastLine(Node *searchNode);
		
		/**Get auto-insert position.
		 *
		 * Fetch the correct line for auto-insertion of values.
		 *
		 * \return Line number where new values should be auto-inserted.
		 */
		virtual int getAutoInsertPos();
		
	public:
		/// Token type: Comment.
		static const TokenType TT_COMMENT;
		/// Token type: Assignment operator.
		static const TokenType TT_ASSIGN;
		/// Token type: Multi-line option marker.
		static const TokenType TT_MULTILINE;
		/// Token type: Tree path elements.
		static const TokenType TT_TREEPATH;
		/// Token type: Nested configuration (open).
		static const TokenType TT_NESTED_OPEN;
		/// Token type: Nested configuration (close).
		static const TokenType TT_NESTED_CLOSE;
		/// Auto-insertion marker.
		static const std::string AUTO_INSERT_MARKER;
		/// Special characters in configuration values.
		static const std::string SPECIAL_VALUE_CHARS;
		
		/** Constructor.
		 *
		 * Construct new ConfigTree object.
		 */
		ConfigTree();
		
		/** Destructor.
		 *
		 * Destruct ConfigTree object.
		 */
		virtual ~ConfigTree();
		
		/** Clear all configuration data.
		 *
		 * Effectively erases all configuration data from the 
		 * ConfigTree object.
		 */
		virtual void clear();
		
		/** Parse configuration data.
		 *
		 * Parses configuration data, with syntax as specified for ConfigTree.
		 *
		 * \param configData Configuration data.
		 */
		virtual void parseConfig(const std::string& configData);
		
		/** Read configuration from a file.
		 *
		 * Reads data from a configuration file and stores it in the
		 * configuration table.
		 *
		 * \param configFile Name of the configuration file
		 */
		virtual void readConfig(const std::string& configFile);
		
		/** Write configuration to a file.
		 *
		 * Writes configuration data stored in the ConfigTree object to 
		 * a file.
		 *
		 * \param configFile Name of the configuration file
		 */
		virtual void writeConfig(const std::string& configFile);
		
		/** Write configuration to a file.
		 *
		 * Writes configuration data stored in the ConfigTree object to 
		 * the same file it was read from.
		 */
		virtual void writeConfig();
		
		/** Get a configuration value.
		 *
		 * Fetches the value of a configuration option from the 
		 * configuration table.
		 *
		 * \param key The key identifying the configuration value.
		 *
		 * \return Value of the specified configuration option, or an empty 
		 * string if the option is not set.
		 */
		virtual std::string get(const std::string& key);
		
		/** Set a configuration value.
		 *
		 * Sets the configuration option denoted by key to value.
		 *
		 * \param key The key of the configuration option to be set.
		 * \param value The value the option should be set to.
		 */
		virtual void set(const std::string& key, const std::string& value);
		
		/** Process a tree node.
		 *
		 * Tree traversal callback, used for updating the configuration file.
		 * The data of the node will be added to or updated in the 
		 * configuration file entry table
		 *
		 * \param node Node to be processed.
		 */
		virtual void dump(Node *node);
		
		/** Escape configuration value.
		 *
		 * Escapes special characters in a configuration value, making the 
		 * value suitable for a configuration file.
		 *
		 * \param value Configuration value.
		 *
		 * \return Escaped configuration value.
		 */
		static std::string escapeValue(const std::string& value);
};

}

}

/** \file ConfigTree.hpp
 * \brief Configuration tree header.
 */
#endif
