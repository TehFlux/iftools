/* ==========================================================================
 * IFTemplate - Ionflux Template Processor
 * Copyright © 2012 Jörn P. Meier
 * mail@ionflux.org
 * --------------------------------------------------------------------------
 * StringAppend.i                  String manipulator: append (interface).
 * =========================================================================

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
#include "iftemplate/StringAppend.hpp"
%}

namespace Ionflux
{

namespace Template
{

namespace StringManipulator
{

class StringAppendClassInfo
: public Ionflux::ObjectBase::IFClassInfo
{
    public:
        StringAppendClassInfo();
        virtual ~StringAppendClassInfo();
};

class StringAppend
: virtual public Ionflux::Template::StringManipulator::StringManipulator
{
    public:
		static const std::string STRINGMANIP_NAME;
        
        StringAppend();
		StringAppend(const Ionflux::Template::StringManipulator::StringAppend& other);
        virtual ~StringAppend();
        virtual std::string process(const std::string& bytes, 
        Ionflux::ObjectBase::StringVector* args = 0);
        virtual std::string getManipName();
		virtual Ionflux::Template::StringManipulator::StringAppend* copy() const;
		static Ionflux::Template::StringManipulator::StringAppend* 
		upcast(Ionflux::ObjectBase::IFObject* other);
		static Ionflux::Template::StringManipulator::StringAppend* 
		create(Ionflux::ObjectBase::IFObject* parentObject = 0);
};

}

}

}
