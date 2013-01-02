#ifndef IONFLUX_OBJECT_IFERROR
#define IONFLUX_OBJECT_IFERROR
/* ==========================================================================
 * Ionflux Object Base System
 * Copyright © 2006-2011 Joern P. Meier
 * mail@ionflux.org
 * --------------------------------------------------------------------------
 * IFError.hpp                     Error (header).
 * =========================================================================
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

#include <string>
#include <exception>

namespace Ionflux
{

namespace ObjectBase
{

/** Error.
 * \ingroup ifobject
 *
 * Exception to be used for errors if no more specific exception class 
 * exists.
 */
class IFError
: public std::exception
{
	private:
		
	protected:
		/// Reason.
		std::string reason;
		
	public:
		
		/** Constructor.
		 *
		 * Construct new IFError object.
		 */
		IFError();
		
		/** Constructor.
		 *
		 * Construct new IFError object.
		 *
		 * \param other Other object.
		 */
		IFError(const Ionflux::ObjectBase::IFError& other);
		
		/** Constructor.
		 *
		 * Construct new IFError object.
		 *
		 * \param initReason Initial reason.
		 */
		IFError(const std::string& initReason);
		
		/** Destructor.
		 *
		 * Destruct IFError object.
		 */
		virtual ~IFError() throw();
		
		/** Get string representation.
		 *
		 * Get a string representation of the object.
		 *
		 * \return String representation.
		 */
		virtual std::string getString() const;
		
		/** Get exception information.
		 *
		 * Get information on what happened.
		 *
		 * \return Exception information.
		 */
		virtual const char* what() const throw();
		
		/** Assignment operator.
		 *
		 * Assign an object.
		 *
		 * \param other Other object.
		 *
		 * \return The object itself.
		 */
		virtual Ionflux::ObjectBase::IFError& operator=(const 
		Ionflux::ObjectBase::IFError& other);
		
		/** Copy.
		 *
		 * Create a copy of the object.
		 *
		 * \return Newly allocated copy of the object.
		 */
		virtual Ionflux::ObjectBase::IFError* copy() const;
		
		/** Get reason.
		 *
		 * \return Current value of reason.
		 */
		virtual std::string getReason() const;
		
		/** Set reason.
		 *
		 * Set new value of reason.
		 *
		 * \param newReason New value of reason.
		 */
		virtual void setReason(const std::string& newReason);
};

}

}

/** \file IFError.hpp
 * \brief Error (header).
 */
#endif
