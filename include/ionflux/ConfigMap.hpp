#ifndef IONFLUX_TOOLS_CONFIG_MAP
#define IONFLUX_TOOLS_CONFIG_MAP
/* ==========================================================================
 * Ionflux Tools
 * Copyright (c) 2004 Joern P. Meier
 * mail@ionflux.org
 * --------------------------------------------------------------------------
 * ConfigMap.hpp                    Configuration map.
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

#include <pcre.h>
#include <string>
#include <iostream>
#include <fstream>
#include <map>
#include <vector>
#include "ionflux/Config.hpp"

namespace Ionflux
{

namespace Tools
{

/** Configuration map.
 * \ingroup cfgfileio
 *
 * Encapsulates configuration data as a set of key/value pairs.
 */
class ConfigMap
: public Config
{
	protected:
		/// Vector to store the input as read from a config file.
		std::vector<std::string> configInput;
		/// Configuration source file.
		std::string inputFile;
		/// Configuration map where key/value pairs are stored.
		std::map<std::string, std::string> config;
		/// Vector to store option keys that were added at runtime.
		std::vector<std::string> newKeys;
		/// Configuration line regexp pattern.
		pcre *configRE;
		/// Comment line regexp pattern.
		pcre *commentRE;
		
		/** Initialize configuration object.
		 *
		 * Sets up the internals, such as patterns that should be 
		 * compiled in advance.
		 */
		virtual void init();
		
		/** Parse a line of configuration.
		 *
		 * Parses a line containing a key/value pair or a comment. 
		 * Key/Value pairs are added to the configuration map, 
		 * comments are simply ignored.
		 *
		 * \param configLine Line of configuration data
		 */
		virtual ConfigOption parseConfigLine(const std::string& configLine);
		
		/** Update configuration input data.
		 *
		 * Changes the configuration input data so that it represents the
		 * actual current settings of the Config object. This may be used 
		 * to update a configuration file.
		 */
		virtual void updateInputData();
		
	public:
		/// Pattern used to match configuration key/value pairs
		static const std::string CONFIG_PATTERN; 
		/// Pattern used to match comments
		static const std::string COMMENT_PATTERN;
		
		/** Constructor.
		 *
		 * Construct new ConfigMap object.
		 */
		ConfigMap();
		
		/** Destructor.
		 *
		 * Destruct ConfigMap object.
		 */
		virtual ~ConfigMap();
		
		/** Clear all configuration data.
		 *
		 * Effectively erases all configuration data from the 
		 * ConfigMap object.
		 */
		virtual void clear();
		
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
		 * Writes configuration data stored in the ConfigMap object to 
		 * a file.
		 *
		 * \param configFile Name of the configuration file
		 */
		virtual void writeConfig(const std::string& configFile);
		
		/** Write configuration to a file.
		 *
		 * Writes configuration data stored in the ConfigMap object to 
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
		
};

}

}

/** \file ConfigMap.hpp
 * \brief Configuration map header.
 */
#endif
