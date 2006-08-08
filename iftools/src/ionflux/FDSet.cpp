/* ==========================================================================
 * Ionflux Tools
 * Copyright (c) 2004 Joern P. Meier
 * mail@ionflux.org
 * --------------------------------------------------------------------------
 * FDSet.cpp                    File descriptor set.
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

#include "ionflux/FDSet.hpp"

using namespace std;

namespace Ionflux
{

namespace Tools
{

FDSet::FDSet()
: timeout(0)
{
	clear();
}

FDSet::~FDSet()
{
	if (timeout != 0)
		delete timeout;
	timeout = 0;
}

void FDSet::addFD(int fd)
{
	addReadFD(fd);
}

void FDSet::addReadFD(int fd)
{
	FD_SET(fd, &masterRead);
}

void FDSet::addWriteFD(int fd)
{
	FD_SET(fd, &masterWrite);
}

void FDSet::addExceptFD(int fd)
{
	FD_SET(fd, &masterExcept);
}

void FDSet::removeFD(int fd)
{
	removeReadFD(fd);
}

void FDSet::removeReadFD(int fd)
{
	FD_CLR(fd, &masterRead);
}

void FDSet::removeWriteFD(int fd)
{
	FD_CLR(fd, &masterWrite);
}

void FDSet::removeExceptFD(int fd)
{
	FD_CLR(fd, &masterExcept);
}

bool FDSet::isSet(int fd)
{
	return isSetRead(fd) || isSetWrite(fd) || isSetExcept(fd);
}

bool FDSet::isSetRead(int fd)
{
	return FD_ISSET(fd, &activeRead);
}

bool FDSet::isSetWrite(int fd)
{
	return FD_ISSET(fd, &activeWrite);
}

bool FDSet::isSetExcept(int fd)
{
	return FD_ISSET(fd, &activeExcept);
}

int FDSet::select()
{
	activeRead = masterRead;
	activeWrite = masterWrite;
	activeExcept = masterExcept;
	return ::select(FD_SETSIZE, &activeRead, &activeWrite, &activeExcept, 
		timeout);
}

void FDSet::setTimeout(int secs, int usecs)
{
	if ((secs != 0) || (usecs != 0))
	{
		if (timeout == 0)
			timeout = new timeval();
		timeout->tv_sec = secs;
		timeout->tv_usec = usecs;
	} else
	if (timeout != 0)
	{
		delete timeout;
		timeout = 0;
	}
}

void FDSet::clear()
{
	clearRead();
	clearWrite();
	clearExcept();
}

void FDSet::clearRead()
{
	FD_ZERO(&masterRead);
	FD_ZERO(&activeRead);
}

void FDSet::clearWrite()
{
	FD_ZERO(&masterWrite);
	FD_ZERO(&activeWrite);
}

void FDSet::clearExcept()
{
	FD_ZERO(&masterExcept);
	FD_ZERO(&activeExcept);
}

}

}

/** \file FDSet.cpp
 * \brief File descriptor set implementation.
 */
