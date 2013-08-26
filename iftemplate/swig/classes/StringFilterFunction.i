/* ==========================================================================
 * IFTemplate - Ionflux Template Processor
 * Copyright © 2012 Jörn P. Meier
 * mail@ionflux.org
 * --------------------------------------------------------------------------
 * StringFilterFunction.i          String filter function (interface).
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
#include "iftemplate/StringFilterFunction.hpp"
%}

namespace Ionflux
{

namespace Template
{

class StringFilterFunctionClassInfo
: public Ionflux::ObjectBase::IFClassInfo
{
    public:
        StringFilterFunctionClassInfo();
        virtual ~StringFilterFunctionClassInfo();
};

class StringFilterFunction
: virtual public Ionflux::ObjectBase::IFObject
{
    public:
        
        StringFilterFunction();
		StringFilterFunction(const Ionflux::Template::StringFilterFunction& other);
        StringFilterFunction(const std::string& initFunc, 
        Ionflux::Template::StringManipulator::StringManipulator* initManip 
        = 0, Ionflux::ObjectBase::StringVector* initArgs = 0);
        virtual ~StringFilterFunction();
        virtual void setArgument(unsigned int index, const std::string& 
        newArg);
		virtual Ionflux::Template::StringFilterFunction* copy() const;
		static Ionflux::Template::StringFilterFunction* 
		upcast(Ionflux::ObjectBase::IFObject* other);
		static Ionflux::Template::StringFilterFunction* 
		create(Ionflux::ObjectBase::IFObject* parentObject = 0);
		static Ionflux::Template::StringFilterFunction* create(const std::string&
		initFunc, Ionflux::Template::StringManipulator::StringManipulator* 
		initManip = 0, Ionflux::ObjectBase::StringVector* initArgs = 0, 
		Ionflux::ObjectBase::IFObject* parentObject = 0);
        virtual void setFunc(const std::string& newFunc);
        virtual std::string getFunc() const;        
        virtual unsigned int getNumArguments() const;
        virtual std::string getArgument(unsigned int elementIndex = 0) 
        const;
		virtual int findArgument(const std::string& needle, unsigned int 
		occurence = 1) const;
        virtual std::vector<std::string>& getArguments();
        virtual void addArgument(const std::string& addElement);
		virtual const std::string& addArgument();
		virtual void addArguments(std::vector<std::string>& newArguments);
		virtual void addArguments(Ionflux::Template::StringFilterFunction* 
		newArguments);        
        virtual void removeArgument(const std::string& removeElement);
		virtual void removeArgumentIndex(unsigned int removeIndex);
		virtual void clearArguments();
        virtual void 
        setManip(Ionflux::Template::StringManipulator::StringManipulator* 
        newManip);
        virtual Ionflux::Template::StringManipulator::StringManipulator* 
        getManip() const;
};

}

}
