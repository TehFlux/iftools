/* ==========================================================================
 * Ionflux Object Base System
 * Copyright © 2006 Joern P. Meier
 * mail@ionflux.org
 * --------------------------------------------------------------------------
 * IFError.cpp                     Error (implementation).
 * =========================================================================
 * 
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

#include "ifobject/IFError.hpp"
#include <iostream>
#include <sstream>
#include <cstdlib>

using namespace std;

namespace Ionflux
{

namespace ObjectBase
{

IFError::IFError()
{
	// TODO: Nothing ATM. ;-)
}

IFError::IFError(const Ionflux::ObjectBase::IFError& other)
{
	*this = other;
}

IFError::IFError(const std::string& initReason)
: reason(initReason)
{
	// TODO: Nothing ATM. ;-)
}

IFError::~IFError() throw()
{
	// TODO: Nothing ATM. ;-)
}

std::string IFError::getString() const
{
	ostringstream state;
	state << "IFError[" << reason << "]";
	return state.str();
}

const char* IFError::what() const throw()
{
	// TODO: Implementation.
	return reason.c_str();
}

void IFError::setReason(const std::string& newReason)
{
	reason = newReason;
}

std::string IFError::getReason() const
{
	return reason;
}

Ionflux::ObjectBase::IFError& IFError::operator=(const 
Ionflux::ObjectBase::IFError& other)
{
	setReason(other.getReason());
	return *this;
}

Ionflux::ObjectBase::IFError* IFError::copy() const
{
    IFError* newIFError = 
        new IFError();
    *newIFError = *this;
    return newIFError;
}

}

}

/** \file IFError.cpp
 * \brief Error implementation.
 */
