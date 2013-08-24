/* ==========================================================================
 * IFTemplate - Ionflux Template Processor
 * Copyright © 2012 Jörn P. Meier
 * mail@ionflux.org
 * --------------------------------------------------------------------------
 * StringRTrim.i                   String manipulator: rtrim (interface).
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
#include "iftemplate/StringRTrim.hpp"
%}

namespace Ionflux
{

namespace Template
{

namespace StringManipulator
{

class StringRTrimClassInfo
: public Ionflux::ObjectBase::IFClassInfo
{
    public:
        StringRTrimClassInfo();
        virtual ~StringRTrimClassInfo();
};

class StringRTrim
: virtual public Ionflux::Template::StringManipulator::StringManipulator
{
    public:
		static const std::string STRINGMANIP_NAME;
        
        StringRTrim();
		StringRTrim(const Ionflux::Template::StringManipulator::StringRTrim& other);
        virtual ~StringRTrim();
        virtual std::string process(const std::string& bytes, 
        Ionflux::ObjectBase::StringVector* args = 0);
        virtual std::string getManipName();
		virtual Ionflux::Template::StringManipulator::StringRTrim* copy() const;
		static Ionflux::Template::StringManipulator::StringRTrim* 
		upcast(Ionflux::ObjectBase::IFObject* other);
		static Ionflux::Template::StringManipulator::StringRTrim* 
		create(Ionflux::ObjectBase::IFObject* parentObject = 0);
};

}

}

}
