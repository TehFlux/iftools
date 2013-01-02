/* ==========================================================================
 * Ionflux Object Base System
 * Copyright © 2006-2011 Joern P. Meier
 * mail@ionflux.org
 * --------------------------------------------------------------------------
 * IFError.i                       Error (interface).
 * =========================================================================

 * This file is part of Ionflux Object Base System.
 * 
 * Ionflux Object Base System is free software; you can redistribute it 
 * and/or modify it under the terms of the GNU General Public License as 
 * published by the Free Software Foundation; either version 2 of the 
 * License, or (at your option) any later version.
 * 
 * Ionflux Object Base System is distributed in the hope that it will be 
 * useful, but WITHOUT ANY WARRANTY; without even the implied warranty of 
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU 
 * General Public License for more details.
 * 
 * You should have received a copy of the GNU General Public License along 
 * with Ionflux Object Base System; if not, write to the Free Software 
 * Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA 02111-1307 USA
 * 
 * ========================================================================== */
%{
#include "ifobject/IFError.hpp"
%}

namespace Ionflux
{

namespace ObjectBase
{

class IFError
: public std::exception
{
    public:
        
        IFError();
		IFError(const Ionflux::ObjectBase::IFError& other);
        IFError(const std::string& initReason);
        virtual ~IFError() throw();
        virtual std::string getString() const;
        virtual const char* what() const throw();
		virtual Ionflux::ObjectBase::IFError* copy() const;
        virtual void setReason(const std::string& newReason);
        virtual std::string getReason() const;
};

}

}
