#ifndef IONFLUX_TOOLS_CLASSINFO
#define IONFLUX_TOOLS_CLASSINFO
/* ==========================================================================
 * Ionflux Tools
 * Copyright (c) 2004-2005 Joern P. Meier
 * mail@ionflux.org
 * --------------------------------------------------------------------------
 * ClassInfo.hpp                     Class information.
 * ==========================================================================
 * 
 * This file is part of Ionflux Tools.
 * 
 * Ionflux Tools is free software; you can redistribute it and/or modify it
 * under the terms of the GNU General Public License as published by the 
 * Free Software Foundation; either version 2 of the License, or (at your 
 * option) any later version.
 * 
 * Ionflux Tools is distributed in the hope that it will be useful, but 
 * WITHOUT ANY WARRANTY; without even the implied warranty of 
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU 
 * General Public License for more details.
 * 
 * You should have received a copy of the GNU General Public License along 
 * with Ionflux Tools; if not, write to the Free Software Foundation, Inc.,
 * 59 Temple Place, Suite 330, Boston, MA 02111-1307 USA
 * 
 * ========================================================================== */

#include <string>

namespace Ionflux
{

namespace Tools
{

/** Class information.
 * \ingroup general
 *
 * Information describing a class.
 */
class ClassInfo
{
	private:
		
	protected:
		/// Class name.
		std::string name;
		/// Class description.
		std::string desc;
		
	public:
		
		/** Constructor.
		 *
		 * Construct new ClassInfo object.
		 */
		ClassInfo();
		
		/** Destructor.
		 *
		 * Destruct ClassInfo object.
		 */
		virtual ~ClassInfo();
		
		/** Get class name.
		 *
		 * Get the class name.
		 *
		 * \return The class name.
		 */
		virtual std::string getName() const;
		
		/** Get class description.
		 *
		 * Get the class description.
		 *
		 * \return The class description.
		 */
		virtual std::string getDesc() const;
};

}

}

/** \file ClassInfo.hpp
 * \brief Class information header.
 */
#endif
