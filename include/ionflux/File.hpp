#ifndef IONFLUX_TOOLS_FILE
#define IONFLUX_TOOLS_FILE
/* ==========================================================================
 * Ionflux Tools
 * Copyright (c) 2005 Joern P. Meier
 * mail@ionflux.org
 * --------------------------------------------------------------------------
 * File.hpp                          File.
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
#include <iostream>
#include <sstream>
#include <vector>
#include <sys/stat.h>
#include "ionflux/tools.hpp"
#include "ionflux/DateTime.hpp"
#include "ionflux/ObjectPool.hpp"

namespace Ionflux
{

namespace Tools
{

/** File.
 * \ingroup general
 *
 * A wrapper for various file properties and operations.
 */
class File
: public Ionflux::Tools::ManagedObject
{
	private:
		
	protected:
		/// Information returned by stat.
		struct stat statInfo;
		/// File size.
		unsigned int size;
		/// Time of last access.
		time_t accessTime;
		/// Time of last modification.
		time_t modTime;
		/// Time of last status change.
		time_t changeTime;
		/// Validity flag.
		bool validity;
		/// File name.
		std::string name;
		/// File path.
		std::string path;
		/// Full name of file (including path).
		std::string fullName;
		
		/** Update stat information.
		 *
		 * Updates the file information obtained from \c stat.
		 *
		 * \return \c true on success, \c false otherwise.
		 */
		virtual bool updateStatInfo();
		
	public:
		/** Constructor.
		 *
		 * Construct new File object.
		 */
		File();
		
		/** Constructor.
		 *
		 * Construct new File object.
		 *
		 * \param initFullName Full name of file (including path).
		 */
		File(const std::string& initFullName);
		
		/** Destructor.
		 *
		 * Destruct File object.
		 */
		virtual ~File();
		
		/** Refresh file.
		 *
		 * Refresh file status information.
		 */
		virtual void refresh();
		
		/** Check validity.
		 *
		 * Check the validity of the file.
		 *
		 * \return \c true if the file is valid, \c false otherwise.
		 */
		virtual bool isValid();
		
		/** Get directory status.
		 *
		 * Get the directory status flag for the file.
		 *
		 * \return \c true if the file is a directory, \c false otherwise.
		 */
		virtual bool isDir();
		
		/** Get file size.
		 *
		 * Get the total size of the file.
		 *
		 * \return File size.
		 */
		virtual unsigned int getSize();
		
		/** Get access time.
		 *
		 * Get the time of last access.
		 *
		 * \return Time of last access.
		 */
		virtual time_t getAccessTime();
		
		/** Get modification time.
		 *
		 * Get the time of last modification.
		 *
		 * \return Time of last modification.
		 */
		virtual time_t getModTime();
		
		/** Get change time.
		 *
		 * Get the time of last status change.
		 *
		 * \return Time of last status change.
		 */
		virtual time_t getChangeTime();
		
		/** Set file name.
		 *
		 * Set new value of file name.
		 *
		 * \param newName New value of file name.
		 */
		virtual void setName(const std::string& newName);
		
		/** Set file path.
		 *
		 * Set new value of file path.
		 *
		 * \param newPath New value of file path.
		 */
		virtual void setPath(const std::string& newPath);
		
		/** Set full name of file (including path).
		 *
		 * Set new value of full name of file (including path).
		 *
		 * \param newFullName New value of full name of file (including path).
		 */
		virtual void setFullName(const std::string& newFullName);
		
		/** Get file name.
		 *
		 * \return Current value of file name.
		 */
		virtual std::string getName() const;
		
		/** Get file path.
		 *
		 * \return Current value of file path.
		 */
		virtual std::string getPath() const;
		
		/** Get full name of file (including path).
		 *
		 * \return Current value of full name of file (including path).
		 */
		virtual std::string getFullName() const;
};

}

}

/** \file File.hpp
 * \brief File header.
 */
#endif
