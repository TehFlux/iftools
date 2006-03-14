#ifndef IONFLUX_TOOLS_FDSET
#define IONFLUX_TOOLS_FDSET
/* ==========================================================================
 * Ionflux Tools
 * Copyright (c) 2004 Joern P. Meier
 * mail@ionflux.org
 * --------------------------------------------------------------------------
 * FDSet.hpp                    File descriptor set.
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
#include <iostream>
#include <vector>
#include <sys/select.h>

namespace Ionflux
{

namespace Tools
{

/** File descriptor set.
 * \ingroup iomplex
 *
 * A file descriptor set. This implements the same functionality as select(), 
 * FD_ZERO, FD_SET, FD_ISSET, FD_CLR etc. in a more convenient way. It also 
 * eliminates ugly macros from your application code. ;-)
 */
class FDSet
{
	protected:
		/// Master FD set (read).
		fd_set masterRead;
		/// Master FD set (write).
		fd_set masterWrite;
		/// Master FD set (except).
		fd_set masterExcept;
		/// Active FD set (read).
		fd_set activeRead;
		/// Active FD set (write).
		fd_set activeWrite;
		/// Active FD set (except).
		fd_set activeExcept;
		/// Select timeout.
		timeval *timeout;
		
	public:
		/** Constructor.
		 *
		 * Construct new FDSet object.
		 */
		FDSet();
		
		/** Destructor.
		 *
		 * Destruct FDSet object.
		 */
		virtual ~FDSet();
		
		/** Add file descriptor (read).
		 *
		 * Add a file descriptor to the read set.
		 *
		 * \deprecated You should not use this function, since its name is 
		 * amibiguous. Use addReadFD(), addWriteFD(), addExceptFD() instead. 
		 * This is provided for backward compatibility only.
		 *
		 * \param fd File descriptor.
		 */
		virtual void addFD(int fd);
		
		/** Add file descriptor (read).
		 *
		 * Add a file descriptor to the read set.
		 *
		 * \param fd File descriptor.
		 */
		virtual void addReadFD(int fd);
		
		/** Add file descriptor (write).
		 *
		 * Add a file descriptor to the write set.
		 *
		 * \param fd File descriptor.
		 */
		virtual void addWriteFD(int fd);
		
		/** Add file descriptor (except).
		 *
		 * Add a file descriptor to the except set.
		 *
		 * \param fd File descriptor.
		 */
		virtual void addExceptFD(int fd);
		
		/** Remove file descriptor (read).
		 *
		 * Remove a file descriptor from the read set.
		 *
		 * \deprecated You should not use this function, since its name is 
		 * amibiguous. Use removeReadFD(), removeWriteFD(), removeExceptFD() 
		 * instead. This is provided for backward compatibility only.
		 *
		 * \param fd File descriptor.
		 */
		virtual void removeFD(int fd);
		
		/** Remove file descriptor (read).
		 *
		 * Remove a file descriptor from the read set.
		 *
		 * \param fd File descriptor.
		 */
		virtual void removeReadFD(int fd);
		
		/** Remove file descriptor (write).
		 *
		 * Remove a file descriptor from the write set.
		 *
		 * \param fd File descriptor.
		 */
		virtual void removeWriteFD(int fd);
		
		/** Remove file descriptor (except).
		 *
		 * Remove a file descriptor from the except set.
		 *
		 * \param fd File descriptor.
		 */
		virtual void removeExceptFD(int fd);
		
		/** Check file descriptor status.
		 *
		 * Checks whether a file descriptor has been set during a select() 
		 * operation.
		 *
		 * \note This will check whether the specified file descriptor has 
		 * been set in any of the FD sets (read, write or except). You should 
		 * not normally have to use this. Use isSetRead(), isSetWrite() and 
		 * isSetExcept() instead.
		 *
		 * \param fd File descriptor.
		 *
		 * \return \c true if the file descriptor is set in any of the FD sets, 
		 * \c false otherwise.
		 */
		virtual bool isSet(int fd);
		
		/** Check file descriptor status (read).
		 *
		 * Checks whether a file descriptor has been set during a select() 
		 * operation.
		 *
		 * \param fd File descriptor.
		 *
		 * \return \c true if the file descriptor is set in the read FD set, 
		 * \c false otherwise.
		 */
		virtual bool isSetRead(int fd);
		
		/** Check file descriptor status (write).
		 *
		 * Checks whether a file descriptor has been set during a select() 
		 * operation.
		 *
		 * \param fd File descriptor.
		 *
		 * \return \c true if the file descriptor is set in the write FD set, 
		 * \c false otherwise.
		 */
		virtual bool isSetWrite(int fd);
		
		/** Check file descriptor status (except).
		 *
		 * Checks whether a file descriptor has been set during a select() 
		 * operation.
		 *
		 * \param fd File descriptor.
		 *
		 * \return \c true if the file descriptor is set in the except FD set, 
		 * \c false otherwise.
		 */
		virtual bool isSetExcept(int fd);
		
		/** Select.
		 *
		 * Checks the file descriptors in the set for changed state.
		 *
		 * \return The number of file descriptors that have changed state.
		 */
		virtual int select();
		
		/** Set timeout.
		 *
		 * Sets the timeout of select operations.
		 *
		 * \param secs Seconds.
		 * \param usecs Microseconds.
		 */
		virtual void setTimeout(int secs, int usecs);
		
		/// Clear all file descriptor sets.
		virtual void clear();
		
		/// Clear file descriptor set (read).
		virtual void clearRead();
		
		/// Clear file descriptor set (read).
		virtual void clearWrite();
		
		/// Clear file descriptor set (read).
		virtual void clearExcept();
};

}

}

/** \file FDSet.hpp
 * \brief File descriptor set header.
 */
#endif
