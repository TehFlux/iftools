#ifndef IONFLUX_TOOLS_CONFIG
#define IONFLUX_TOOLS_CONFIG
/* ==========================================================================
 * Ionflux Tools
 * Copyright (c) 2004 Joern P. Meier
 * mail@ionflux.org
 * --------------------------------------------------------------------------
 * Config.hpp                    Configuration wrapper (abstract class)
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

namespace Ionflux
{

namespace Tools
{

/** \addtogroup cfgfileio Configuration file I/O
 *
 * Interface to sources of configuration data. (See \ref configdoc for 
 * details.)
 *
 * @{
 */

/** Configuration option.
 *
 * A key/value pair representing a configuration option.
 */
struct ConfigOption
{
	/// The option key.
	std::string key;
	/// The option value.
	std::string value;
};

/** Configuration line.
 *
 * Represents a line of a configuration file.
 */
struct ConfigLine
{
	/** Configuration option.
	 *
	 * If this line is a comment, option.key will be set to 
	 * \c '&lt;comment&gt;' and option.value to the verbatim text of the line 
	 * (excluding line terminators).
	 */
	ConfigOption option;
	/// Line type.
	int type;
	/// Line type: Invalid option.
	static const int CL_INVALID;
	/// Line type: Configuration option.
	static const int CL_OPTION;
	/// Line type: Comment.
	static const int CL_COMMENT;
	/// Line type: Blank.
	static const int CL_BLANK;
	/// Line type: Nested configuration.
	static const int CL_NESTED;
	/// Line type: Root data.
	static const int CL_ROOT_DATA;
};

/** Configuration.
 *
 * Encapsulates configuration data as a set of key/value pairs.
 *
 */
class Config
{
	public:
		/** Constructor.
		 *
		 * Construct new ConfigMap object.
		 */
		Config() { };
		
		/** Destructor.
		 *
		 * Destruct Config object.
		 */
		virtual ~Config() { };
		
		/** Clear all configuration data.
		 *
		 * Effectively erases all configuration data from the 
		 * Config object.
		 */
		virtual void clear() = 0;
		
		/** Read configuration from a file.
		 *
		 * Reads data from a configuration file and stores it in the
		 * configuration table.
		 *
		 * \param configFile Name of the configuration file
		 */
		virtual bool readConfig(const std::string& configFile) = 0;
		
		/** Write configuration to a file.
		 *
		 * Writes configuration data stored in the Config object to 
		 * a file.
		 *
		 * \param configFile Name of the configuration file
		 */
		virtual void writeConfig(const std::string& configFile) = 0;
		
		/** Write configuration to a file.
		 *
		 * Writes configuration data stored in the Config object to 
		 * the same file it was read from.
		 */
		virtual void writeConfig() = 0;
		
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
		virtual std::string get(const std::string& key) = 0;
		
		/** Set a configuration value.
		 *
		 * Sets the configuration option denoted by key to value.
		 *
		 * \param key The key of the configuration option to be set.
		 * \param value The value the option should be set to.
		 */
		virtual void set(const std::string& key, const std::string& value) = 0;
		
};

/// @}

}

}

/** \file Config.hpp
 * \brief Configuration wrapper header.
 */
#endif
