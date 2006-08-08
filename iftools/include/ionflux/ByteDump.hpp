#ifndef IONFLUX_TOOLS_BYTEDUMP
#define IONFLUX_TOOLS_BYTEDUMP
/* ==========================================================================
 * Ionflux Tools
 * Copyright (c) 2004 Joern P. Meier
 * mail@ionflux.org
 * --------------------------------------------------------------------------
 * ByteDump.hpp                 Byte dump (abstract class)
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

#include <string>

namespace Ionflux
{

namespace Tools
{

/** Byte dump.
 * \ingroup general
 *
 * Abstract base class for anything that can receive bytes.
 */
class ByteDump
{
	public:
		/** Destructor.
		 *
		 * Destruct ByteDump object.
		 */
		virtual ~ByteDump() { };
		
		/** Dump bytes.
		 *
		 * Pass a string of bytes to the object for handling.
		 *
		 * \param bytes The bytes to be dumped.
		 */
		virtual void dump(const std::string &bytes) = 0;
};

}

}

/** \file ByteDump.hpp
 * \brief Byte dump (abstract class) header.
 */
#endif
