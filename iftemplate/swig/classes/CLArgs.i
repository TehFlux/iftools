/* ==========================================================================
 * IFTemplate - Ionflux Template Processor
 * Copyright © 2012 Jörn P. Meier
 * mail@ionflux.org
 * --------------------------------------------------------------------------
 * CLArgs.i                        Command line argument parser 
 * (interface).
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
#include "iftemplate/CLArgs.hpp"
%}

namespace Ionflux
{

namespace Template
{

class CLArgsClassInfo
: public Ionflux::ObjectBase::IFClassInfo
{
    public:
        CLArgsClassInfo();
        virtual ~CLArgsClassInfo();
};

class CLArgs
: public Ionflux::ObjectBase::IFObject
{
    public:
		static const Ionflux::Template::TokenType TT_OPTION;
		static const Ionflux::Template::TokenType TT_ASSIGN;
		static const Ionflux::Template::CLOption OPTION_NOT_SET;
        
        CLArgs();
		CLArgs(const Ionflux::Template::CLArgs& other);
        CLArgs(int argc, char** argv);
        virtual ~CLArgs();
        virtual void clearAcceptableOptions();
        virtual void clearOptions();
        virtual void clearParams();
        virtual void setArgs(int argc, char** argv);
        virtual void setArgs(const Ionflux::ObjectBase::StringVector& 
        newArgs);
        virtual Ionflux::Template::CLOption* getOption(const std::string& 
        searchOption);
        virtual bool isSet(const std::string& checkOption);
        virtual void getParams(Ionflux::Template::CLParams& target);
        virtual void addAcceptableOption(const std::string& newOption, bool
        newAcceptValue);
        virtual Ionflux::Template::CLAcceptableOption* 
        getAcceptableOption(const std::string& searchOption);
        virtual bool isAcceptable(const std::string& checkOption);
        virtual bool acceptsValue(const std::string& checkOption);
        virtual Ionflux::ObjectBase::StringVector& getInvalidOptions();
        virtual bool optionsOK();
        virtual void printDebugInfo();
		virtual Ionflux::Template::CLArgs* copy() const;
		static Ionflux::Template::CLArgs* upcast(Ionflux::ObjectBase::IFObject* 
		other);
		static Ionflux::Template::CLArgs* create(Ionflux::ObjectBase::IFObject* 
		parentObject = 0);
        virtual void setCheckOptions(bool newCheckOptions);
        virtual bool getCheckOptions() const;
};

}

}
