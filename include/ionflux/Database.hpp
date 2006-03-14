#ifndef IONFLUX_TOOLS_DATABASE
#define IONFLUX_TOOLS_DATABASE
/* ==========================================================================
 * Ionflux Tools
 * Copyright (c) 2004 Joern P. Meier
 * mail@ionflux.org
 * --------------------------------------------------------------------------
 * Database.hpp                   Database (abstract class).
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
#include <vector>
#include <map>
#include "ionflux/Node.hpp"
#include "ionflux/ManagedObject.hpp"

namespace Ionflux
{

namespace Tools
{

/** \addtogroup database Database interface
 *
 * Interface to SQL compatible databases.
 *
 * @{
 */

/// Result row.
typedef std::vector<std::string> DbRow;
/// Result row as a map.
typedef std::map<std::string, std::string> DbRowMap;
/// Set of result rows.
typedef std::vector<DbRow> DbResult;
/// Set of result rows as maps.
typedef std::vector<DbRowMap> DbResultMap;
/// List of tables.
typedef std::vector<std::string> DbTables;
/// List of columns.
typedef std::vector<std::string> DbColumns;

/// Database configuration.
struct DatabaseConfig
{
	/// Server hostname.
	std::string server;
	/// Server port.
	unsigned int port;
	/// Username.
	std::string username;
	/// Password.
	std::string password;
	/// Database name.
	std::string database;
};

/// Database error.
struct DatabaseError
{
	/// Numeric error code.
	unsigned int errNum;
	/// Error message.
	std::string error;
};

/// Class information for class Database.
class DatabaseClassInfo
: public ClassInfo
{
	public:
		/// Constructor.
		DatabaseClassInfo();
		/// Destructor.
		virtual ~DatabaseClassInfo() { };
};

/** Database.
 *
 * Abstract wrapper class for a database connection.
 */
class Database
: public ManagedObject
{
	public:
		/// Node order: First level represents rows.
		static const int NODE_ORDER_ROWS;
		/// Node order: First level represents rows with named field nodes.
		static const int NODE_ORDER_NAMED_FIELDS;
		/// Node order: First level represents columns.
		static const int NODE_ORDER_COLUMNS;
		/// Class information instance.
		static const DatabaseClassInfo databaseClassInfo;
		/// Class information.
		static const ClassInfo* CLASS_INFO;
		
		/** Constructor.
		 *
		 * Construct new Database object.
		 */
		Database();
		
		/** Constructor.
		 *
		 * Construct new Database object.
		 */
		Database(const DatabaseConfig &initConfig);
		
		/** Destructor.
		 *
		 * Destruct Database object.
		 */
		virtual ~Database();
		
		/** Set database configuration.
		 *
		 * Set configuration options for the database.
		 *
		 * \param newConfig Database configuration.
		 */
		virtual void setConfig(const DatabaseConfig &newConfig) = 0;
		
		/** Set database configuration.
		 *
		 * Set configuration options for the database.
		 *
		 * \note This allows to set the database configuration from the 
		 * contents of a configuration node. Each first level node corresponds 
		 * to a field of the DatabaseConfig struct, with its name set to the 
		 * field name and its first data entry set to the field value.
		 *
		 * \param newConfig Database configuration node.
		 */
		virtual void setConfig(Ionflux::Tools::Node &newConfig) = 0;
		
		/** Get database configuration.
		 *
		 * Get the database configuration currently used.
		 *
		 * \return Database configuration.
		 */
		virtual DatabaseConfig getConfig() = 0;
		
		/** Connect to database.
		 *
		 * Establish a database connection.
		 *
		 * \return \c true on success, \c false otherwise.
		 */
		virtual bool connect() = 0;
		
		/// Close database connection.
		virtual void close() = 0;
		
		/** Execute database query.
		 *
		 * Execute a database query.
		 *
		 * \param command Command to execute as a database query.
		 *
		 * \return \c true on success, \c false otherwise.
		 */
		virtual bool query(const std::string &command) = 0;
		
		/** List tables.
		 *
		 * Fetches a list of tables from the current database that match the
		 * specified pattern. Pass an empty string to match all tables.
		 *
		 * \param tables Where to store the list of tables.
		 * \param pattern A pattern to match table names.
		 *
		 * \return \c true on success, \c false otherwise.
		 */
		virtual bool listTables(DbTables &tables, 
			const std::string &pattern = "") = 0;
		
		/** List columns.
		 *
		 * Fetches a list of columns for the specified table.
		 *
		 * \param columns Where to store the list of columns.
		 * \param table Table.
		 *
		 * \return \c true on success, \c false otherwise.
		 */
		virtual bool listColumns(DbColumns &columns, 
			const std::string &table) = 0;
		
		/** Get number of rows.
		 *
		 * Get the number of rows for the specified table.
		 *
		 * \param table Table.
		 *
		 * \return Number of rows for the specified table.
		 */
		virtual unsigned int getNumRows(const std::string &table) = 0;
		
		/** Get number of rows returned.
		 *
		 * Get the number of rows returned by the previous query.
		 *
		 * \return Number of rows in result set.
		 */
		virtual unsigned int getNumRows() = 0;
		
		/** Get number of rows affected.
		 *
		 * Get the number of rows affected by the previous query.
		 *
		 * \return Number of rows affected.
		 */
		virtual unsigned int getNumAffectedRows() = 0;
		
		/** Get a result row.
		 *
		 * Initializes a DbRow to contain the fields of a result row.
		 *
		 * \param row Object to store the row in.
		 *
		 * \return \c true on success, \c false otherwise.
		 */
		virtual bool fetchRow(DbRow &row) = 0;
		
		/** Get a result row as a map.
		 *
		 * Initializes a DbRowMap to contain the fields of a result row.
		 * Use this to get a result row as a map (associative array).
		 *
		 * \param rowMap Object to store the row map in.
		 *
		 * \return \c true on success, \c false otherwise.
		 */
		virtual bool fetchRowMap(DbRowMap &rowMap) = 0;
		
		/** Get a result row as a tree.
		 *
		 * Initializes a tree node to contain the fields of a result row.
		 * Use this to get a result row as a tree.
		 *
		 * \param rowNode Node to store the row in.
		 *
 		 * \return \c true on success, \c false otherwise.
		 */
		virtual bool fetchRowTree(Node &rowNode) = 0;
		
		/** Get a complete result.
		 *
		 * Initializes a DbResult to contain all result rows.
		 *
		 * \param result Object to store the result rows in.
		 *
		 * \return \c true on success, \c false otherwise.
		 */
		virtual bool fetchResult(DbResult &result) = 0;
		
		/** Get a complete result as a map.
		 *
		 * Initializes a DbResultMap to contain all result rows as maps.
		 * Use this to get a complete result as maps.
		 *
		 * \param resultMap Object to store the result row maps in.
		 *
		 * \return \c true on success, \c false otherwise.
		 */
		virtual bool fetchResultMap(DbResultMap &resultMap) = 0;
		
		/** Get a complete result as a tree.
		 *
		 * Initializes a tree node to contain all result rows. Use this to 
		 * get a complete result as a tree. You can specify either 
		 * Database::NODE_ORDER_ROWS, Database::NODE_ORDER_NAMED_FIELDS, or 
		 * Database::NODE_ORDER_COLUMNS as 'nodeOrder'. In row order mode, 
		 * each node on the first level represents a row, and each data entry 
		 * contains field data. The first node contains the field  names as 
		 * data entries. In named field order mode, each node on the first 
		 * level represents a row. Each node on the second level contains 
		 * field data and has its name set to the field name. In column order 
		 * mode, each node on the first level represents a column and has its 
		 * name set to the corresponding field name. Each data entry contains 
		 * field data for a row.
		 *
		 * \param resultNode Node to store the result rows in.
		 * \param nodeOrder Node order.
		 *
		 * \return \c true on success, \c false otherwise.
		 */
		virtual bool fetchResultTree(Node &resultNode, int nodeOrder) = 0;
		
		/** Escape string.
		 *
		 * Escapes a string so it represents a valid SQL string.
		 *
		 * \param source String to be escaped.
		 *
		 * \return Escaped string.
		 */
		virtual std::string sqlEscape(const std::string &source) = 0;
		
		/** Validate existence of table.
		 *
		 * Validate the existence of the table with the specified name. If the 
		 * table does not exist and a create template is specified, try to 
		 * create the table.
		 *
		 * \param tableName Table name.
		 * \param createTemplate Template for the table creation query.
		 * \param createConfig Configuration to be used for table creation.
		 *
		 * \return \c true if the table exists or has been successfully 
		 * created, \c false if the table does not exist and could not be 
		 * created automatically.
		 */
		virtual bool validateTable(const std::string& tableName, 
			const std::string& createTemplate = "", 
			Node* createConfig = 0) = 0;
		
		/** Get error.
		 *
		 * Get the last error.
		 *
		 * \return The last error that occured.
		 */
		virtual DatabaseError getError() = 0;
		
};

/// @}

}

}

/** \file Database.hpp
 * \brief Database (abstract class) header.
 */
#endif
