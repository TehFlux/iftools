/* ==========================================================================
 * Ionflux Tools
 * Copyright (c) 2004 Joern P. Meier
 * mail@ionflux.org
 * --------------------------------------------------------------------------
 * database.cpp                  Database test.
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
#include "ionflux/CLArgs.hpp"
#include "ionflux/ConfigTree.hpp"
#include "ionflux/MySQLDatabase.hpp"

using namespace std;
using namespace Ionflux::Tools;

int main(int argc, char* argv[])
{
	CLArgs args(argc, argv);
	CLParams params;
	args.getParams(params);
	if (params.size() < 2)
	{
		cerr << "Usage: database <config file> <query>" << endl;
		return 0;
	}
	Database* database = new MySQLDatabase();
	ConfigTree config;
	config.readConfig(params[0]);
	database->setConfig(*config.getRoot());
	if (!database->connect())
	{
		DatabaseError dbError = database->getError();
		cerr << "Error: Could not connect to database: " 
			<< dbError.error << " (" << dbError.errNum << ")." << endl;
		return -1;
	}
	if (!database->query(params[1]))
	{
		DatabaseError dbError = database->getError();
		cerr << "Error: Could not execute database query: " 
			<< dbError.error << " (" << dbError.errNum << ")." << endl;
		return -1;
	}
	Node result;
	database->fetchResultTree(result, Database::NODE_ORDER_NAMED_FIELDS);
	cout << result.toConfig() << endl;
	return 0;
}

/** \file database.cpp
 * \brief Database test.
 */
