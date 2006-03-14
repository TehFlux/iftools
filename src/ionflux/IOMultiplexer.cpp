/* ==========================================================================
 * Ionflux Tools
 * Copyright (c) 2004 Joern P. Meier
 * mail@ionflux.org
 * --------------------------------------------------------------------------
 * IOMultiplexer.cpp               IO event multiplexer (abstract class).
 * ==========================================================================
 * 
 * This file is part of Ionflux Tools.
 * 
 * Ionflux Tools is free software; you can redistribute it and/or modify it 
 * under the terms of the GNU General Public License as published by the Free
 * Software Foundation; either version 2 of the License, or (at  your option)
 * any later version.
 * 
 * Ionflux Tools is distributed in the hope that it will be useful, but 
 * WITHOUT ANY WARRANTY; without even the implied warranty of MERCHANTABILITY
 * or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU General Public License
 * for more details.
 * 
 * You should have received a copy of the GNU General Public License
 * along with Ionflux Tools; if not, write to the Free Software Foundation, 
 * Inc., 59 Temple Place, Suite 330, Boston, MA 02111-1307 USA
 * 
 * ========================================================================== */

#include "ionflux/IOMultiplexer.hpp"

using namespace std;

namespace Ionflux
{

namespace Tools
{

const int IOMultiplexer::IOM_TYPE_UNDEFINED = 0;
const int IOMultiplexer::IOM_TYPE_SELECT = 1;
const int IOMultiplexer::IOM_TYPE_GLIB = 2;

IOMultiplexer::IOMultiplexer()
: type(IOM_TYPE_UNDEFINED)
{
	// TODO: Nothing ATM. ;-)
}

void IOMultiplexer::shutdownHandler(int signum)
{
	// TODO: Nothing ATM. ;-)
}

int IOMultiplexer::getType()
{
	return type;
}

}

}

/** \file IOMultiplexer.cpp
 * \brief IO event multiplexer (abstract class) implementation.
 */
