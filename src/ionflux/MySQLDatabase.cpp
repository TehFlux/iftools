/* ==========================================================================
 * Ionflux Tools
 * Copyright (c) 2004 Joern P. Meier
 * mail@ionflux.org
 * --------------------------------------------------------------------------
 * MySQLDatabase.cpp                MySQL Database access
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

#include "ionflux/MySQLDatabase.hpp"
#include "ionflux/Template.hpp"

using namespace std;

namespace Ionflux
{

namespace Tools
{

MySQLDatabaseClassInfo::MySQLDatabaseClassInfo()
{
	name = "MySQLDatabase";
	desc = "MySQL database";
}

const string MySQLDatabase::DEFAULT_SERVER = "localhost";
const unsigned int MySQLDatabase::DEFAULT_PORT = 3306;
const string MySQLDatabase::DEFAULT_USERNAME = "anonymous";
const string MySQLDatabase::DEFAULT_PASSWORD = "";
const string MySQLDatabase::DEFAULT_DATABASE = "test";
const MySQLDatabaseClassInfo MySQLDatabase::mySQLDatabaseClassInfo;
const ClassInfo* MySQLDatabase::CLASS_INFO = 
	&MySQLDatabase::mySQLDatabaseClassInfo;

MySQLDatabase::MySQLDatabase()
: mysql(0), queryResult(0), numRows(0), numFields(0), numAffectedRows(0)
{
	// NOTE: The following line is required for class information.
	theClasses.push_back(CLASS_INFO);
	config.server = DEFAULT_SERVER;
	config.port = DEFAULT_PORT;
	config.username = DEFAULT_USERNAME;
	config.password = DEFAULT_PASSWORD;
	config.database = DEFAULT_DATABASE;
}

MySQLDatabase::MySQLDatabase(const DatabaseConfig &initConfig)
: mysql(0), queryResult(0), numRows(0), numFields(0), numAffectedRows(0)
{
	// NOTE: The following line is required for class information.
	theClasses.push_back(CLASS_INFO);
	setConfig(initConfig);
}

MySQLDatabase::~MySQLDatabase()
{
	close();
}

void MySQLDatabase::setConfig(const DatabaseConfig &newConfig)
{
	config = newConfig;
	if (config.server == "")
		config.server = DEFAULT_SERVER;
	if (config.port == 0)
		config.port = DEFAULT_PORT;
	if (config.username == "")
		config.username = DEFAULT_USERNAME;
	if (config.password == "")
		config.password = DEFAULT_PASSWORD;
	if (config.database == "")
		config.database = DEFAULT_DATABASE;
}

void MySQLDatabase::setConfig(Ionflux::Tools::Node &newConfig)
{
	DatabaseConfig tmpConfig;
	tmpConfig.server = newConfig["server"].getData();
	tmpConfig.port = strtol(newConfig["port"].getData().c_str(), 0, 10);
	tmpConfig.username = newConfig["username"].getData();
	tmpConfig.password = newConfig["password"].getData();
	tmpConfig.database = newConfig["database"].getData();
	setConfig(tmpConfig);
}

DatabaseConfig MySQLDatabase::getConfig()
{
	return config;
}

bool MySQLDatabase::connect()
{
	close();
	mysql = ::mysql_init(0);
	MYSQL *result = ::mysql_real_connect(mysql, config.server.c_str(), 
		config.username.c_str(), config.password.c_str(), 
		config.database.c_str(), config.port, 0, 0);
	if (result == 0)
	{
		lastError.errNum = ::mysql_errno(mysql);
		lastError.error = ::mysql_error(mysql);
		return false;
	}
	return true;
}

void MySQLDatabase::close()
{
	freeResult();
	if (mysql != 0)
		::mysql_close(mysql);
	mysql = 0;
}

void MySQLDatabase::freeResult()
{
	numRows = 0;
	numFields = 0;
	numAffectedRows = 0;
	if (queryResult != 0)
		::mysql_free_result(queryResult);
	queryResult = 0;
}

bool MySQLDatabase::query(const std::string &command)
{
	if (mysql == 0)
		connect();
	freeResult();
	int result = ::mysql_real_query(mysql, command.c_str(), command.size());
	if (result != 0)
	{
		lastError.errNum = ::mysql_errno(mysql);
		lastError.error = ::mysql_error(mysql);
		return false;
	}
	queryResult = ::mysql_store_result(mysql);
	numFields = ::mysql_field_count(mysql);
	if (queryResult == 0)
	{
		if (numFields == 0)
		{
			numAffectedRows = ::mysql_affected_rows(mysql);
		} else
		{
			lastError.errNum = ::mysql_errno(mysql);
			lastError.error = ::mysql_error(mysql);
			return false;
		}
	} else
	{
		numRows = ::mysql_num_rows(queryResult);
	}
	return true;
}

bool MySQLDatabase::listTables(DbTables &tables, const std::string &pattern)
{
	if (mysql == 0)
		connect();
	freeResult();
	const char *patternBuf = 0;
	if (pattern.size() > 0)
		patternBuf = pattern.c_str();
	queryResult = ::mysql_list_tables(mysql, patternBuf);
	numFields = ::mysql_field_count(mysql);
	if (queryResult == 0)
	{
		if (numFields == 0)
		{
			numAffectedRows = ::mysql_affected_rows(mysql);
		} else
		{
			lastError.errNum = ::mysql_errno(mysql);
			lastError.error = ::mysql_error(mysql);
			return false;
		}
	} else
	{
		numRows = ::mysql_num_rows(queryResult);
	}
	tables.clear();
	DbRow currentRow;
	while(fetchRow(currentRow))
	{
		if (currentRow.size() > 0)
			tables.push_back(currentRow[0]);
	}
	return true;
}

bool MySQLDatabase::listColumns(DbColumns &columns, const std::string &table)
{
	if (table.size() == 0)
		return false;
	columns.clear();
	ostringstream theQuery;
	theQuery << "SHOW COLUMNS FROM " << sqlEscape(table);
	if (!query(theQuery.str()))
		return false;
	DbRow row;
	while(fetchRow(row))
		if (row.size() > 0)
			columns.push_back(row[0]);
	return true;
}

unsigned int MySQLDatabase::getNumRows(const std::string &table)
{
	if (table.size() == 0)
		return 0;
	ostringstream theQuery;
	theQuery << "SELECT COUNT(*) FROM " << sqlEscape(table);
	if (!query(theQuery.str()))
		return false;
	DbRow row;
	unsigned int result = 0;
	if (fetchRow(row) && (row.size() > 0))
		result = strtol(row[0].c_str(), 0, 10);
	return result;
}

unsigned int MySQLDatabase::getNumRows()
{
	return numRows;
}

unsigned int MySQLDatabase::getNumAffectedRows()
{
	return numAffectedRows;
}

bool MySQLDatabase::fetchRow(DbRow &row)
{
	if (numRows == 0)
		return false;
	MYSQL_ROW resultRow = ::mysql_fetch_row(queryResult);
	if (resultRow == 0)
	{
		lastError.errNum = ::mysql_errno(mysql);
		lastError.error = ::mysql_error(mysql);
		return false;
	} else
	{
		unsigned long *fieldLengths = ::mysql_fetch_lengths(queryResult);
		row.clear();
		for (unsigned int i = 0; i < numFields; i++)
			row.push_back(string(resultRow[i], fieldLengths[i]));
	}
	return true;
}

bool MySQLDatabase::fetchRowMap(DbRowMap &rowMap)
{
	if (numRows == 0)
		return false;
	DbRow row;
	if (!fetchRow(row))
		return false;
	MYSQL_FIELD *fields = ::mysql_fetch_fields(queryResult);
	rowMap.clear();
	for (unsigned int i = 0; i < numFields; i++)
		rowMap[fields[i].name] = row[i];
	return true;
}

bool MySQLDatabase::fetchRowTree(Node &rowNode)
{
	if (numRows == 0)
		return false;
	DbRow row;
	if (!fetchRow(row))
		return false;
	MYSQL_FIELD *fields = ::mysql_fetch_fields(queryResult);
	rowNode.clear();
	for (unsigned int i = 0; i < numFields; i++)
		rowNode[fields[i].name] = row[i];
	return true;
}

bool MySQLDatabase::fetchResult(DbResult &result)
{
	if (numRows == 0)
		return false;
	::mysql_data_seek(queryResult, 0);
	result.clear();
	DbRow currentRow;
	while (fetchRow(currentRow))
		result.push_back(currentRow);
	return true;
}

bool MySQLDatabase::fetchResultMap(DbResultMap &resultMap)
{
	if (numRows == 0)
		return false;
	::mysql_data_seek(queryResult, 0);
	resultMap.clear();
	DbRowMap currentRowMap;
	while (fetchRowMap(currentRowMap))
		resultMap.push_back(currentRowMap);
	return true;
}

bool MySQLDatabase::fetchResultTree(Node &resultNode, int nodeOrder)
{
	if (numRows == 0)
		return false;
	MYSQL_FIELD *fields = ::mysql_fetch_fields(queryResult);
	::mysql_data_seek(queryResult, 0);
	resultNode.clear();
	bool origAutoCreate = resultNode.getAutoCreate();
	resultNode.setAutoCreate(true);
	resultNode.setIndexMode(Node::INDEX_MODE_NODE);
	DbRow currentRow;
	unsigned int rowCount = 0;
	Node *currentNode = 0;
	Node **columns = 0;
	if (nodeOrder == Database::NODE_ORDER_ROWS)
	{
		// Initialize first row with field names.
		currentNode = resultNode.getChild(0);
		if (currentNode == 0)
			return false;
		currentNode->setID(0);
		for (unsigned int i = 0; i < numFields; i++)
			currentNode->setData(i, fields[i].name);
	} else
	if (nodeOrder == Database::NODE_ORDER_COLUMNS)
	{
		// Set up column node array.
		columns = new Node*[numFields];
		for (unsigned int i = 0; i < numFields; i++)
			columns[i] = resultNode.findChild(fields[i].name, false);
	}
	while (fetchRow(currentRow))
	{
		if (nodeOrder == Database::NODE_ORDER_ROWS)
		{
			currentNode = resultNode.getChild(rowCount + 1);
			if (currentNode == 0)
				return false;
			currentNode->setID(rowCount + 1);
			for (unsigned int i = 0; i < numFields; i++)
				currentNode->setData(i, currentRow[i]);
		} else
		if (nodeOrder == Database::NODE_ORDER_NAMED_FIELDS)
		{
			currentNode = resultNode.getChild(rowCount);
			if (currentNode == 0)
				return false;
			currentNode->setID(rowCount);
			for (unsigned int i = 0; i < numFields; i++)
				(*currentNode)[fields[i].name] = currentRow[i];
		} else
		if (nodeOrder == Database::NODE_ORDER_COLUMNS)
		{
			for (unsigned int i = 0; i < numFields; i++)
				if (columns[i] != 0)
					columns[i]->setData(rowCount, currentRow[i]);
				else
				{
					delete[] columns;
					return false;
				}
		} else
			return false;
		rowCount++;
	}
	resultNode.setAutoCreate(origAutoCreate);
	if (columns != 0)
		delete[] columns;
	return true;
}

std::string MySQLDatabase::sqlEscape(const std::string &source)
{
	if (mysql == 0)
		connect();
	char *buf = new char[source.size() * 2 + 1];
	unsigned int resultSize = mysql_real_escape_string(
		mysql, buf, source.c_str(), source.size());
	string result(buf, resultSize);
	delete[] buf;
	return result;
}

bool MySQLDatabase::validateTable(const std::string& tableName, 
	const std::string& createTemplate, Node* createConfig)
{
	if (tableName.size() == 0)
	{
		/* ----- DEBUG ----- //
		cerr << "[MySQLDatabase::validateTable] DEBUG: "
			"Table name is empty string." << endl;
		// ----- DEBUG ----- */
		return false;
	}
	DbTables tables;
	listTables(tables, tableName);
	bool found = false;
	unsigned int i = 0;
	while (!found && (i < tables.size()))
	{
		if (tables[i] == tableName)
			found = true;
		else
			i++;
	}
	if (found || (createTemplate.size() == 0))
	{
		if (!found)
		{
			/* ----- DEBUG ----- //
			cerr << "[MySQLDatabase::validateTable] DEBUG: Table '"
				<< tableName << "' does not exist and has NOT been created "
				"(create template not set)." << endl;
			// ----- DEBUG ----- */
			return false;
		} else
		{
			/* ----- DEBUG ----- //
			cerr << "[MySQLDatabase::validateTable] DEBUG: Table '"
				<< tableName << "' exists." << endl;
			// ----- DEBUG ----- */
			return true;
		}
	}
	Template createTpl;
	Node tplConfig;
	tplConfig.setAutoCreate(true);
	tplConfig.setIndexMode(Node::INDEX_MODE_NODE);
	if (createConfig != 0)
		tplConfig = *createConfig;
	string theQuery = createTpl.process(createTemplate, &tplConfig);
	/* ----- DEBUG ----- //
	cerr << "[MySQLDatabase::validateTable] DEBUG: Creating table '"
		<< table << "':" << endl << query;
	// ----- DEBUG ----- */
	if (!query(theQuery))
		return false;
	return true;
}

DatabaseError MySQLDatabase::getError()
{
	return lastError;
}

}

}

/** \file MySQLDatabase.cpp
 * \brief MySQL database wrapper implementation.
 */
