#ifndef IONFLUX_TOOLS_OBJECT
#define IONFLUX_TOOLS_OBJECT
/* ==========================================================================
 * Ionflux Tools
 * Copyright (c) 2004-2005 Joern P. Meier
 * mail@ionflux.org
 * --------------------------------------------------------------------------
 * Object.hpp                        Object.
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
#include <vector>
#include "ionflux/ClassInfo.hpp"

namespace Ionflux
{

namespace Tools
{

/// Class information for class Object.
class ObjectClassInfo
: public ClassInfo
{
	public:
		/// Constructor.
		ObjectClassInfo();
		/// Destructor.
		virtual ~ObjectClassInfo() { };
};

/** Object.
 * \ingroup general
 *
 * A base class for all objects.
 */
class Object
{
	private:
		
	protected:
		/// Class info vector.
		std::vector<const ClassInfo*> theClasses;
		
	public:
		/// Class information instance.
		static const ObjectClassInfo objectClassInfo;
		/// Class information.
		static const ClassInfo* CLASS_INFO;
		
		/** Constructor.
		 *
		 * Construct new Object object.
		 */
		Object();
		
		/** Destructor.
		 *
		 * Destruct Object object.
		 */
		virtual ~Object();
		
		/** Get class information.
		 *
		 * Get the class information.
		 *
		 * \return The class information, or 0 if no class information exists for
		 * this class.
		 */
		virtual const ClassInfo* getClass() const;
		
		/** Get class name.
		 *
		 * Get the class name
		 *
		 * \return The class name.
		 */
		virtual std::string getClassName() const;
		
		/** Get class description.
		 *
		 * Get the class description
		 *
		 * \return The class description.
		 */
		virtual std::string getClassDesc() const;
};

}

}

/** \file Object.hpp
 * \brief Object header.
 */
#endif
