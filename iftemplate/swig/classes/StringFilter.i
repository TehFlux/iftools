/* ==========================================================================
 * IFTemplate - Ionflux Template Processor
 * Copyright © 2012 Jörn P. Meier
 * mail@ionflux.org
 * --------------------------------------------------------------------------
 * StringFilter.i                  String filter (interface).
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
#include "iftemplate/StringFilter.hpp"
%}

namespace Ionflux
{

namespace Template
{

class StringFilterFunction;

class StringFilterClassInfo
: public Ionflux::ObjectBase::IFClassInfo
{
    public:
        StringFilterClassInfo();
        virtual ~StringFilterClassInfo();
};

class StringFilter
: virtual public Ionflux::ObjectBase::IFObject
{
    public:
		static const Ionflux::Template::TokenType TT_FUNC_SEP;
		static const Ionflux::Template::TokenType TT_FUNC_BRACKET_LEFT;
		static const Ionflux::Template::TokenType TT_FUNC_BRACKET_RIGHT;
		static const Ionflux::Template::TokenType TT_FUNC_ARG_SEP;
        
        StringFilter();
		StringFilter(const Ionflux::Template::StringFilter& other);
        StringFilter(const std::string& initFilter);
        virtual ~StringFilter();
        virtual void addDefaultManipulators();
        virtual std::string apply(const std::string& bytes);
        virtual void updateIndices();
        virtual void printDebugInfo();
		virtual Ionflux::Template::StringFilter* copy() const;
		static Ionflux::Template::StringFilter* 
		upcast(Ionflux::ObjectBase::IFObject* other);
		static Ionflux::Template::StringFilter* 
		create(Ionflux::ObjectBase::IFObject* parentObject = 0);
		static Ionflux::Template::StringFilter* create(const std::string& 
		initFilter, Ionflux::ObjectBase::IFObject* parentObject = 0);
        virtual void setFilter(const std::string& newFilter);
        virtual std::string getFilter() const;        
        virtual unsigned int getNumFunctions() const;
        virtual Ionflux::Template::StringFilterFunction* 
        getFunction(unsigned int elementIndex = 0) const;
		virtual int findFunction(Ionflux::Template::StringFilterFunction* needle,
		unsigned int occurence = 1) const;
        virtual std::vector<Ionflux::Template::StringFilterFunction*>& 
        getFunctions();
        virtual void addFunction(Ionflux::Template::StringFilterFunction* 
        addElement);        
        virtual void 
        removeFunction(Ionflux::Template::StringFilterFunction* 
        removeElement);
		virtual void removeFunctionIndex(unsigned int removeIndex);
		virtual void clearFunctions();        
        virtual unsigned int getNumManipulators() const;
        virtual Ionflux::Template::StringManipulator::StringManipulator* 
        getManipulator(unsigned int elementIndex = 0) const;
		virtual int 
		findManipulator(Ionflux::Template::StringManipulator::StringManipulator* 
		needle, unsigned int occurence = 1) const;
        virtual 
        std::vector<Ionflux::Template::StringManipulator::StringManipulator*>&
        getManipulators();
        virtual void 
        addManipulator(Ionflux::Template::StringManipulator::StringManipulator*
        addElement);        
        virtual void 
        removeManipulator(Ionflux::Template::StringManipulator::StringManipulator*
        removeElement);
		virtual void removeManipulatorIndex(unsigned int removeIndex);
		virtual void clearManipulators();
};

}

}
