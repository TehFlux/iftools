/* ==========================================================================
 * Ionflux Object Base System
 * Copyright © 2006 Joern P. Meier
 * mail@ionflux.org
 * --------------------------------------------------------------------------
 * log.cpp                 Logging.
 * ==========================================================================
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

#include "ifobject/log.hpp"
#include "ifobject/IFLogMessage.hpp"
#include <iostream>

namespace Ionflux
{

namespace ObjectBase
{

const IFObject* IF_DEFAULT_LOG_TARGET = 0;

void setDefaultLogTarget(const Ionflux::ObjectBase::IFObject* logTarget)
{
	IF_DEFAULT_LOG_TARGET = logTarget;
}

const Ionflux::ObjectBase::IFObject* getDefaultLogTarget()
{
	return IF_DEFAULT_LOG_TARGET;
}

void log(const std::string& message, IFVerbosityLevel level, 
	const std::string& source, const Ionflux::ObjectBase::IFObject* logTarget)
{
	IFLogMessage msg(message, level, 0, source);
	if (logTarget == 0)
	{
		if (IF_DEFAULT_LOG_TARGET == 0)
		{
			if (level <= VL_WARNING_OPT)
				std::cerr << msg << std::endl;
			else
				std::cout << msg << std::endl;
		} else
			IF_DEFAULT_LOG_TARGET->log(msg);
	} else
		logTarget->log(msg);
}

}

}

/** \file log.cpp
 * \brief Logging.
 */
