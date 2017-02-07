/* ==========================================================================
 * IFTemplate - Ionflux Template Processor
 * Copyright © 2012 Jörn P. Meier
 * mail@ionflux.org
 * --------------------------------------------------------------------------
 * Config.i                        Configuration (interface).
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
%{
#include "iftemplate/Config.hpp"
%}

namespace Ionflux
{

namespace Template
{

class ConfigClassInfo
: public Ionflux::ObjectBase::IFClassInfo
{
    public:
        ConfigClassInfo();
        virtual ~ConfigClassInfo();
};

class Config
: virtual public Ionflux::ObjectBase::IFObject
{
    public:
        
        Config();
		Config(const Ionflux::Template::Config& other);
        virtual ~Config();
        virtual void clear();
        virtual bool readConfig(const std::string& configFile);
        virtual void writeConfig(const std::string& configFile);
        virtual void writeConfig();
        virtual std::string get(const std::string& key);
        virtual void set(const std::string& key, const std::string& value);
		virtual Ionflux::Template::Config* copy() const;
		static Ionflux::Template::Config* upcast(Ionflux::ObjectBase::IFObject* 
		other);
		static Ionflux::Template::Config* create(Ionflux::ObjectBase::IFObject* 
		parentObject = 0);
		virtual unsigned int getMemSize() const;
};

}

}
