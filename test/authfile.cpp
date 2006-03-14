/* ==========================================================================
 * Ionflux Tools
 * Copyright (c) 2004 Joern P. Meier
 * mail@ionflux.org
 * --------------------------------------------------------------------------
 * authfile.cpp                  File based authentication test.
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

#include <iostream>
#include <string>
#include "ionflux/tools.hpp"
#include "ionflux/AuthFile.hpp"

using namespace std;
using namespace Ionflux::Tools;

int main(int argc, char* argv[])
{
	if (argc < 2)
	{
		cout << "Usage: authfile <file name>" << endl;
		return 0;
	}
	AuthFile authFile(argv[1]);
	authFile.printDebugInfo();
	string username;
	string password;
	cout << "Enter username: ";
	getline(cin, username);
	getPassword("Enter password: ", password);
	if (authFile.auth(username, password))
	{
		cout << "Your user account is valid." << endl;
	} else
	{
		cout << "Authentication failed." << endl;
	}
	for (unsigned int i = 0; i < password.size(); i++)
		password[i] = '\0';
	return 0;
}

/** \file authfile.cpp
 * \brief File based authentication test.
 */
