#ifndef IONFLUX_TOOLS_MESSAGEDUMP
#define IONFLUX_TOOLS_MESSAGEDUMP
/* ==========================================================================
 * Ionflux Tools
 * Copyright (c) 2004 Joern P. Meier
 * mail@ionflux.org
 * --------------------------------------------------------------------------
 * MessageDump.hpp                 Message dump (abstract class)
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
#include "ionflux/Message.hpp"

namespace Ionflux
{

namespace Tools
{

class Message;

/** Message dump.
 * \ingroup network
 *
 * Abstract base class for anything that can receive network message objects.
 *
 */
class MessageDump
{
	public:
		/** Destructor.
		 *
		 * Destruct MessageDump object.
		 */
		virtual ~MessageDump() { };
		
		/** Dump message.
		 *
		 * Pass a message to the object for handling.
		 *
		 * \param msg The message to be dumped.
		 */
		virtual void dump(Message &msg) = 0;
};

}

}

/** \file MessageDump.hpp
 * \brief Message dump (abstract class) header.
 */
#endif
