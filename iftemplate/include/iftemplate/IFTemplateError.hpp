#ifndef IONFLUX_TEMPLATE_IFTEMPLATEERROR
#define IONFLUX_TEMPLATE_IFTEMPLATEERROR
/* ==========================================================================
 * IFTemplate - Ionflux Template Processor
 * Copyright © 2012 Jörn P. Meier
 * mail@ionflux.org
 * --------------------------------------------------------------------------
 * IFTemplateError.hpp             IFTemplate error (header).
 * =========================================================================
 *
 * This file is part of IFTemplate - Ionflux Template Processor.
 * 
 * IFTemplate - Ionflux Template Processor is free software; you can 
 * redistribute it and/or modify it under the terms of the GNU General 
 * Public License as published by the Free Software Foundation; either 
 * version 2 of the License, or (at your option) any later version.
 * 
 * IFTemplate - Ionflux Template Processor is distributed in the hope that 
 * it will be useful, but WITHOUT ANY WARRANTY; without even the implied 
 * warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See 
 * the GNU General Public License for more details.
 * 
 * You should have received a copy of the GNU General Public License along 
 * with IFTemplate - Ionflux Template Processor; if not, write to the Free 
 * Software Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA 
 * 02111-1307 USA
 * 
 * ========================================================================== */

#include <string>
#include <exception>

namespace Ionflux
{

namespace Template
{

/** IFTemplate error.
 * \ingroup geoutils
 *
 * Exception to be used for errors if no more specific exception class 
 * exists.
 */
class IFTemplateError
: public std::exception
{
	private:
		
	protected:
		/// Reason.
		std::string reason;
		
	public:
		
		/** Constructor.
		 *
		 * Construct new IFTemplateError object.
		 */
		IFTemplateError();
		
		/** Constructor.
		 *
		 * Construct new IFTemplateError object.
		 *
		 * \param other Other object.
		 */
		IFTemplateError(const Ionflux::Template::IFTemplateError& other);
		
		/** Constructor.
		 *
		 * Construct new IFTemplateError object.
		 *
		 * \param initReason Initial reason.
		 */
		IFTemplateError(const std::string& initReason);
		
		/** Destructor.
		 *
		 * Destruct IFTemplateError object.
		 */
		virtual ~IFTemplateError() throw();
		
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
		virtual Ionflux::Template::IFTemplateError& operator=(const 
		Ionflux::Template::IFTemplateError& other);
		
		/** Copy.
		 *
		 * Create a copy of the object.
		 *
		 * \return Newly allocated copy of the object.
		 */
		virtual Ionflux::Template::IFTemplateError* copy() const;
		
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

/** \file IFTemplateError.hpp
 * \brief IFTemplate error (header).
 */
#endif
