/* ==========================================================================
 * Ionflux Tools
 * Copyright (c) 2004 Joern P. Meier
 * mail@ionflux.org
 * --------------------------------------------------------------------------
 * Database.cpp                    Database (abstract class).
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

#include "ionflux/Database.hpp"

using namespace std;

namespace Ionflux
{

namespace Tools
{

DatabaseClassInfo::DatabaseClassInfo()
{
	name = "Database";
	desc = "Database";
}

const int Database::NODE_ORDER_ROWS = 0;
const int Database::NODE_ORDER_NAMED_FIELDS = 1;
const int Database::NODE_ORDER_COLUMNS = 2;
const DatabaseClassInfo Database::databaseClassInfo;
const ClassInfo* Database::CLASS_INFO = 
	&Database::databaseClassInfo;

Database::Database()
{
	// NOTE: The following line is required for class information.
	theClasses.push_back(CLASS_INFO);
}

Database::Database(const DatabaseConfig &initConfig)
{
	// TODO: Nothing ATM. ;-)
}

Database::~Database()
{
	// TODO: Nothing ATM. ;-)
}

}

}

/** \file Database.cpp
 * \brief Database (abstract class) implementation.
 */
