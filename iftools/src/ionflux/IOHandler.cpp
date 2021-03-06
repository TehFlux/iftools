/* ==========================================================================
 * Ionflux Tools
 * Copyright (c) 2004 Joern P. Meier
 * mail@ionflux.org
 * --------------------------------------------------------------------------
 * IOHandler.cpp                   IO event handler (abstract class).
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

#include "ionflux/IOHandler.hpp"

using namespace std;

namespace Ionflux
{

namespace Tools
{

const int IOEvent::IO_READ = 1;
const int IOEvent::IO_WRITE = 2;
const int IOEvent::IO_EXCEPT = 4;
const int IOEvent::IO_TIMEOUT = 8;

std::string IOEvent::getString() const
{
    std::ostringstream status;
    status << "IOEvent[" << fd;
    bool first = true;
    if ((type & IO_READ) != 0)
    {
        if (!first)
            status << ", ";
        else
        {
            status << "; ";
            first = false;
        }
        status << "READ";
    }
    if ((type & IO_WRITE) != 0)
    {
        if (!first)
            status << ", ";
        else
        {
            status << "; ";
            first = false;
        }
        status << "WRITE";
    }
    if ((type & IO_EXCEPT) != 0)
    {
        if (!first)
            status << ", ";
        else
        {
            status << "; ";
            first = false;
        }
        status << "EXCEPT";
    }
    if ((type & IO_TIMEOUT) != 0)
    {
        if (!first)
            status << ", ";
        else
        {
            status << "; ";
            first = false;
        }
        status << "TIMEOUT";
    }
    status << "]";
    return status.str();
}

std::ostream& operator<<(std::ostream& outputStream, const 
    Ionflux::Tools::IOEvent& event)
{
    outputStream << event.getString();
    return outputStream;
}

}

}

/** \file IOHandler.cpp
 * \brief IO event handler (abstract class) implementation.
 */
