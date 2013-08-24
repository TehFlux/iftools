/* ==========================================================================
 * IFTemplate - Ionflux Template Processor
 * Copyright © 2012 Jörn P. Meier
 * mail@ionflux.org
 * --------------------------------------------------------------------------
 * IFTemplateError.cpp             IFTemplate error (implementation).
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

#include "iftemplate/IFTemplateError.hpp"
#include <iostream>
#include <sstream>
#include <cstdlib>

using namespace std;

namespace Ionflux
{

namespace Template
{

IFTemplateError::IFTemplateError()
{
	// TODO: Nothing ATM. ;-)
}

IFTemplateError::IFTemplateError(const Ionflux::Template::IFTemplateError& other)
{
	*this = other;
}

IFTemplateError::IFTemplateError(const std::string& initReason)
: reason(initReason)
{
	// TODO: Nothing ATM. ;-)
}

IFTemplateError::~IFTemplateError() throw()
{
	// TODO: Nothing ATM. ;-)
}

std::string IFTemplateError::getString() const
{
	ostringstream state;
	state << "IFTemplateError[" << reason << "]";
	return state.str();
}

const char* IFTemplateError::what() const throw()
{
	// TODO: Implementation.
	return reason.c_str();
}

void IFTemplateError::setReason(const std::string& newReason)
{
	reason = newReason;
}

std::string IFTemplateError::getReason() const
{
	return reason;
}

Ionflux::Template::IFTemplateError& IFTemplateError::operator=(const 
Ionflux::Template::IFTemplateError& other)
{
setReason(other.getReason());
	return *this;
}

Ionflux::Template::IFTemplateError* IFTemplateError::copy() const
{
    IFTemplateError* newIFTemplateError = 
        new IFTemplateError();
    *newIFTemplateError = *this;
    return newIFTemplateError;
}

}

}

/** \file IFTemplateError.cpp
 * \brief IFTemplate error implementation.
 */
