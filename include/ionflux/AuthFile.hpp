#ifndef IONFLUX_TOOLS_AUTHFILE
#define IONFLUX_TOOLS_AUTHFILE
/* ==========================================================================
 * Ionflux Tools
 * Copyright (c) 2004 Joern P. Meier
 * mail@ionflux.org
 * --------------------------------------------------------------------------
 * AuthFile.hpp                    File based authentication.
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
#include <sstream>
#include <vector>
#include "ionflux/Auth.hpp"
#include "ionflux/Reporter.hpp"
#include "ionflux/Tokenizer.hpp"

namespace Ionflux
{

namespace Tools
{

/** File based authentication.
 * \ingroup auth
 *
 * Reads authentication data from a file and validates user accounts against 
 * the data stored in the authentication file. Each line of the authentication 
 * file represents a valid username/password pair in the following format:
 *
 * \c &lt;username&gt;:&lt;password hash&gt;
 *
 * Where 'password hash' is the hex-encoded SHA-1 hash of the password.
 */
class AuthFile
: public Auth
{
	protected:
		/// Console output/logging.
		Ionflux::Tools::Reporter log;
		/// Authentication file name.
		std::string authFile;
		/// Authentication data vector.
		std::vector<AuthData> authData;
		
		/** Parse authentication file.
		 *
		 * Extract authentication data records from authentication file.
		 */
		void parse();
		
	public:
		/// Token type: Username/password separator.
		static const TokenType TT_USER_PASS_SEP;
		
		/** Constructor.
		 *
		 * Construct new AuthFile object.
		 */
		AuthFile();
		
		/** Constructor.
		 *
		 * Construct new AuthFile object.
		 *
		 * \param initAuthFile Authentication file name.
		 */
		AuthFile(const std::string &initAuthFile);
		
		/** Destructor.
		 *
		 * Destruct AuthFile object.
		 */
		virtual ~AuthFile();
		
		/** Set authentication file.
		 *
		 * Set the authentication file name.
		 *
		 * \param newAuthFile Authentication file name.
		 */
		virtual void setAuthFile(const std::string &newAuthFile);
		
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
		 	const std::string &password);
		
		/** Get secret.
		 *
		 * Get the secret associated with a username. If the username is not 
		 * valid, the secret will be set to an empty string.
		 *
		 * Note: The returned secret is the SHA-1 hash of the user's password.
		 *
		 * \param username Username.
		 * \param secret Where to store the secret.
		 */
		virtual void getSecret(const std::string &username, 
			std::string &secret);
		
		/** Get Console output/logging facility.
		 *
		 * \return The console output/logging facility used by this object.
		 */
		virtual Reporter &getLog();
		
		/// Print debug information.
		virtual void printDebugInfo();
};

}

}

/** \file AuthFile.hpp
 * \brief File based authentication header.
 */
#endif
