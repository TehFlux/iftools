#ifndef IONFLUX_TOOLS_AUTH
#define IONFLUX_TOOLS_AUTH
/* ==========================================================================
 * Ionflux Tools
 * Copyright (c) 2004 Joern P. Meier
 * mail@ionflux.org
 * --------------------------------------------------------------------------
 * Auth.hpp                    Simple user authentication (abstract class).
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
#include "ionflux/Reporter.hpp"

namespace Ionflux
{

namespace Tools
{

/** \addtogroup auth Authentication
 *
 * A simple user authentication interface.
 *
 * @{
 */

/** Authentication data record.
 *
 * A set of data used to authenticate a particular user.
 */
struct AuthData
{
	/// Username.
	std::string username;
	/// Password.
	std::string password;
	/// Session secret.
	std::string sessionSecret;
};

/** Auth.
 *
 * A simple user authentication interface.
 */
class Auth
{
	protected:
		
	public:
		/** Constructor.
		 *
		 * Construct new Auth object.
		 */
		 Auth() { };
		
		/** Destructor.
		 *
		 * Destruct Auth object.
		 */
		virtual ~Auth() { };
		 
		/** Authenticate user.
		 *
		 * Authenticate a username/password pair. 
		 *
		 * \param username Username.
		 * \param password Password.
		 *
		 * \return \c true if the username and password are valid, \c false 
		 * otherwise.
		 */
		virtual bool auth(const std::string &username, 
		 	const std::string &password) = 0;
		
		/** Get secret.
		 *
		 * Get the secret associated with a username. If the username is not 
		 * valid, the secret will be set to an empty string.
		 *
		 * \param username Username.
		 * \param secret Where to store the secret.
		 */
		virtual void getSecret(const std::string &username, 
			std::string &secret) = 0;
		
		/** Get Console output/logging facility.
		 *
		 * \return The console output/logging facility used by this object.
		 */
		virtual Reporter &getLog() = 0;
};

/// @}

}

}

/** \file Auth.hpp
 * \brief Simple user authentication (abstract class) header.
 */
#endif
