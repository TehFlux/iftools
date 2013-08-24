#ifndef IONFLUX_TEMPLATE_CONFIGTREE
#define IONFLUX_TEMPLATE_CONFIGTREE
/* ==========================================================================
 * IFTemplate - Ionflux Template Processor
 * Copyright © 2012 Jörn P. Meier
 * mail@ionflux.org
 * --------------------------------------------------------------------------
 * ConfigTree.hpp                  Configuration tree (header).
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
#include "iftemplate/constants.hpp"
#include "iftemplate/configtypes.hpp"
#include "iftemplate/Tokenizer.hpp"
#include "iftemplate/Tree.hpp"
#include "iftemplate/Config.hpp"
#include "iftemplate/NodeDump.hpp"

namespace Ionflux
{

namespace Template
{

/// Class information for class ConfigTree.
class ConfigTreeClassInfo
: public Ionflux::ObjectBase::IFClassInfo
{
	public:
		/// Constructor.
		ConfigTreeClassInfo();
		/// Destructor.
		virtual ~ConfigTreeClassInfo();
};

/** Configuration tree.
 * \ingroup iftemplate
 *
 * A tree containing configuration data.
 */
class ConfigTree
: virtual public Ionflux::Template::Tree, virtual public 
Ionflux::Template::Config, virtual public Ionflux::Template::NodeDump
{
	private:
		
	protected:
		/// configuration source file.
		std::string inputFile;
		/// tokenizer.
		Ionflux::Template::Tokenizer tok;
		/// entries.
		Ionflux::Template::ConfigTreeEntryVector entries;
		
		/** Find configuration line.
		 *
		 * Searches for the first line in the configuration file that defines 
		 * the specified node. Returns -1 if the node is not found.
		 *
		 * \param searchNode node to search for.
		 *
		 * \return Line number where the specified node is first defined, or -1, 
		 * if the node is not found.
		 */
		virtual int findFirstLine(Ionflux::Template::Node* searchNode);
		
		/** Find configuration line.
		 *
		 * Searches for the last line in the configuration file that defines 
		 * the specified node. Returns -1 if the node is not found.
		 *
		 * \param searchNode node to search for.
		 *
		 * \return Line number where the specified node is last defined, or -1, 
		 * if the node is not found.
		 */
		virtual int findLastLine(Ionflux::Template::Node* searchNode);
		
		/** Get auto-insert position.
		 *
		 * Fetch the correct line for auto-insertion of values.
		 *
		 * \return Line number where new values should be auto-inserted.
		 */
		virtual int getAutoInsertPos();
		
	public:
		/// Token type: comment.
		static const Ionflux::Template::TokenType TT_COMMENT;
		/// Token type: assignment operator.
		static const Ionflux::Template::TokenType TT_ASSIGN;
		/// Token type: multi-line option marker.
		static const Ionflux::Template::TokenType TT_MULTILINE;
		/// Token type: tree path elements.
		static const Ionflux::Template::TokenType TT_TREEPATH;
		/// Token type: nested configuration (open).
		static const Ionflux::Template::TokenType TT_NESTED_OPEN;
		/// Token type: nested configuration (close).
		static const Ionflux::Template::TokenType TT_NESTED_CLOSE;
		/// Token type: verbatim configuration value (open).
		static const Ionflux::Template::TokenType TT_VERBATIM_OPEN;
		/// Token type: verbatim configuration value (close).
		static const Ionflux::Template::TokenType TT_VERBATIM_CLOSE;
		/// Auto-insertion marker.
		static const std::string AUTO_INSERT_MARKER;
		/// Special characters in configuration values.
		static const std::string SPECIAL_VALUE_CHARS;
		/// Class information instance.
		static const ConfigTreeClassInfo configTreeClassInfo;
		/// Class information.
		static const Ionflux::ObjectBase::IFClassInfo* CLASS_INFO;
		
		/** Constructor.
		 *
		 * Construct new ConfigTree object.
		 */
		ConfigTree();
		
		/** Constructor.
		 *
		 * Construct new ConfigTree object.
		 *
		 * \param other Other object.
		 */
		ConfigTree(const Ionflux::Template::ConfigTree& other);
		
		/** Destructor.
		 *
		 * Destruct ConfigTree object.
		 */
		virtual ~ConfigTree();
		
		/** Clear.
		 *
		 * Clear the configuration data.
		 */
		virtual void clear();
		
		/** Parse configuration data.
		 *
		 * Parse configuration data, with syntax as specified for ConfigTree.
		 *
		 * \param configData configuration data.
		 * \param lineOffset line offset.
		 */
		virtual void parseConfig(const std::string& configData, unsigned int 
		lineOffset = 0);
		
		/** Read configuration from a file.
		 *
		 * Read data from a configuration file and store it in the 
		 * configuration object.
		 *
		 * \param configFile name of configuration file.
		 *
		 * \return \c true on success, \c false otherwise.
		 */
		virtual bool readConfig(const std::string& configFile);
		
		/** Write configuration to a file.
		 *
		 * Writes configuration data stored in the Config object to a file.
		 *
		 * \param configFile name of configuration file.
		 */
		virtual void writeConfig(const std::string& configFile);
		
		/** Write configuration to a file.
		 *
		 * Writes configuration data stored in the Config object to the same 
		 * file it was read from.
		 */
		virtual void writeConfig();
		
		/** Get configuration value.
		 *
		 * Fetches the value of a configuration option from the configuration 
		 * object.
		 *
		 * \param key key identifying the configuration value.
		 *
		 * \return Value of the specified configuration option, or an empty 
		 * string if the option is not set for that key.
		 */
		virtual std::string get(const std::string& key);
		
		/** Set configuration value.
		 *
		 * Sets the configuration option denoted by key to value.
		 *
		 * \param key key of the configuration option to be set.
		 * \param value value the option should be set to.
		 */
		virtual void set(const std::string& key, const std::string& value);
		
		/** Dump node.
		 *
		 * Pass a node to the object for processing.
		 *
		 * \param node node to be processed.
		 */
		virtual void dump(Ionflux::Template::Node* node);
		
		/** Escape configuration value.
		 *
		 * Escapes special characters in a configuration value, making the 
		 * value suitable for a configuration file.
		 *
		 * \param value configuration value.
		 *
		 * \return escaped configuration value.
		 */
		static std::string escapeValue(const std::string& value);
		
		/** Assignment operator.
		 *
		 * Assign an object.
		 *
		 * \param other Other object.
		 *
		 * \return The object itself.
		 */
		virtual Ionflux::Template::ConfigTree& operator=(const 
		Ionflux::Template::ConfigTree& other);
		
		/** Copy.
		 *
		 * Create a copy of the object.
		 *
		 * \return Newly allocated copy of the object.
		 */
		virtual Ionflux::Template::ConfigTree* copy() const;
		
		/** Upcast.
		 *
		 * Cast an IFObject to the most specific type.
		 *
		 * \param other Other object.
		 *
		 * \return The more specific object, or 0 if the cast failed.
		 */
		static Ionflux::Template::ConfigTree* 
		upcast(Ionflux::ObjectBase::IFObject* other);
		
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
		static Ionflux::Template::ConfigTree* 
		create(Ionflux::ObjectBase::IFObject* parentObject = 0);
};

}

}

/** \file ConfigTree.hpp
 * \brief Configuration tree (header).
 */
#endif
