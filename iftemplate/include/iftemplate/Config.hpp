#ifndef IONFLUX_TEMPLATE_CONFIG
#define IONFLUX_TEMPLATE_CONFIG
/* ==========================================================================
 * IFTemplate - Ionflux Template Processor
 * Copyright © 2012 Jörn P. Meier
 * mail@ionflux.org
 * --------------------------------------------------------------------------
 * Config.hpp                      Configuration (header).
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
#include "ifobject/IFObject.hpp"

namespace Ionflux
{

namespace Template
{

/// Class information for class Config.
class ConfigClassInfo
: public Ionflux::ObjectBase::IFClassInfo
{
	public:
		/// Constructor.
		ConfigClassInfo();
		/// Destructor.
		virtual ~ConfigClassInfo();
};

/** Configuration.
 * \ingroup iftemplate
 *
 * Encapsulates configuration data as a set of key/value pairs.
 */
class Config
: virtual public Ionflux::ObjectBase::IFObject
{
	private:
		
	protected:
		
	public:
		/// Class information instance.
		static const ConfigClassInfo configClassInfo;
		/// Class information.
		static const Ionflux::ObjectBase::IFClassInfo* CLASS_INFO;
		
		/** Constructor.
		 *
		 * Construct new Config object.
		 */
		Config();
		
		/** Constructor.
		 *
		 * Construct new Config object.
		 *
		 * \param other Other object.
		 */
		Config(const Ionflux::Template::Config& other);
		
		/** Destructor.
		 *
		 * Destruct Config object.
		 */
		virtual ~Config();
		
		/** Clear.
		 *
		 * Clear the configuration data.
		 */
		virtual void clear();
		
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
		
		/** Assignment operator.
		 *
		 * Assign an object.
		 *
		 * \param other Other object.
		 *
		 * \return The object itself.
		 */
		virtual Ionflux::Template::Config& operator=(const 
		Ionflux::Template::Config& other);
		
		/** Copy.
		 *
		 * Create a copy of the object.
		 *
		 * \return Newly allocated copy of the object.
		 */
		virtual Ionflux::Template::Config* copy() const;
		
		/** Upcast.
		 *
		 * Cast an IFObject to the most specific type.
		 *
		 * \param other Other object.
		 *
		 * \return The more specific object, or 0 if the cast failed.
		 */
		static Ionflux::Template::Config* upcast(Ionflux::ObjectBase::IFObject* 
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
		static Ionflux::Template::Config* create(Ionflux::ObjectBase::IFObject* 
		parentObject = 0);
};

}

}

/** \file Config.hpp
 * \brief Configuration (header).
 */
#endif
