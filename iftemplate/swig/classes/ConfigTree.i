/* ==========================================================================
 * IFTemplate - Ionflux Template Processor
 * Copyright © 2012 Jörn P. Meier
 * mail@ionflux.org
 * --------------------------------------------------------------------------
 * ConfigTree.i                    Configuration tree (interface).
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
#include "iftemplate/ConfigTree.hpp"
%}

namespace Ionflux
{

namespace Template
{

class ConfigTreeClassInfo
: public Ionflux::ObjectBase::IFClassInfo
{
    public:
        ConfigTreeClassInfo();
        virtual ~ConfigTreeClassInfo();
};

class ConfigTree
: virtual public Ionflux::Template::Tree, virtual public 
Ionflux::Template::Config, virtual public Ionflux::Template::NodeDump
{
    public:
		static const Ionflux::Template::TokenType TT_COMMENT;
		static const Ionflux::Template::TokenType TT_ASSIGN;
		static const Ionflux::Template::TokenType TT_MULTILINE;
		static const Ionflux::Template::TokenType TT_TREEPATH;
		static const Ionflux::Template::TokenType TT_NESTED_OPEN;
		static const Ionflux::Template::TokenType TT_NESTED_CLOSE;
		static const Ionflux::Template::TokenType TT_VERBATIM_OPEN;
		static const Ionflux::Template::TokenType TT_VERBATIM_CLOSE;
		static const std::string AUTO_INSERT_MARKER;
		static const std::string SPECIAL_VALUE_CHARS;
        
        ConfigTree();
		ConfigTree(const Ionflux::Template::ConfigTree& other);
        virtual ~ConfigTree();
        virtual void clear();
        virtual void parseConfig(const std::string& configData, unsigned 
        int lineOffset = 0);
        virtual bool readConfig(const std::string& configFile);
        virtual void writeConfig(const std::string& configFile);
        virtual void writeConfig();
        virtual std::string get(const std::string& key);
        virtual void set(const std::string& key, const std::string& value);
        virtual void dump(Ionflux::Template::Node* node);
        static std::string escapeValue(const std::string& value);
		virtual Ionflux::Template::ConfigTree* copy() const;
		static Ionflux::Template::ConfigTree* 
		upcast(Ionflux::ObjectBase::IFObject* other);
		static Ionflux::Template::ConfigTree* 
		create(Ionflux::ObjectBase::IFObject* parentObject = 0);
};

}

}
