#ifndef IONFLUX_OBJECT_LOG
#define IONFLUX_OBJECT_LOG
/* ==========================================================================
 * Ionflux Object Base System
 * Copyright © 2006 Joern P. Meier
 * mail@ionflux.org
 * --------------------------------------------------------------------------
 * utf8.hpp                 UTF-8 encoding/decoding.
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

#include "ifobject/types.hpp"

namespace Ionflux
{

namespace ObjectBase
{

/// Verbosity level.
enum IFVerbosityLevel
{
	/// Verbosity level: assertion.
	VL_ASSERTION = -60,
	/// Verbosity level: silent.
	VL_SILENT = -50,
	/// Verbosity level: critical error.
	VL_ERROR_CRITICAL = -40,
	/// Verbosity level: error.
	VL_ERROR = -30,
	/// Verbosity level: warning.
	VL_WARNING = -20,
	/// Verbosity level: optional warning.
	VL_WARNING_OPT = -10,
	/// Verbosity level: info.
	VL_INFO = 0,
	/// Verbosity level: optional info.
	VL_INFO_OPT = 10,
	/// Verbosity level: debug.
	VL_DEBUG = 20,
	/// Verbosity level: optional debug.
	VL_DEBUG_OPT = 30,
	/// Verbosity level: insane debug.
	VL_DEBUG_INSANE = 40,
	/// Verbosity level: all.
	VL_ALL = 50
};

/** Set default log target.
 *
 * Set the default logging target.
 *
 * \param logTarget object to be used for logging
 */
void setDefaultLogTarget(const Ionflux::ObjectBase::IFObject* logTarget);

/** Get default log target.
 *
 * Get the default logging target.
 *
 * \return default logging target
 */
const Ionflux::ObjectBase::IFObject* getDefaultLogTarget();

/** Log message.
 *
 * Log a message. If a log target is specified, the message will be logged 
 * using the log target. Otherwise, if a default log target is set, the 
 * default log target will be used. If no log target is set, the message will 
 * be logged to standard output or to standard error, depending on the 
 * verbosity level.
 * 
 * \param message message text
 * \param level verbosity level
 * \param source source of the message
 * \param logTarget object to be used for logging
 */
void log(const std::string& message, IFVerbosityLevel level = VL_INFO, 
	const std::string& source = "", 
	const Ionflux::ObjectBase::IFObject* logTarget = 0);

}

}

/** \file utf8.hpp
 * \brief UTF-8 encoding/decoding.
 */
#endif
