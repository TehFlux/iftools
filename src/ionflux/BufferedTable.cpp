/* ==========================================================================
 * Ionflux Tools
 * Copyright (c) 2005 Joern P. Meier
 * mail@ionflux.org
 * --------------------------------------------------------------------------
 * BufferedTable.cpp               Buffered database table.
 * ==========================================================================
 * 
 * This file is part of Ionflux Tools.
 * 
 * Ionflux Tools is free software; you can redistribute it and/or modify it
 * under the terms of the GNU General Public License as published by the 
 * Free Software Foundation; either version 2 of the License, or (at your 
 * option) any later version.
 * 
 * Ionflux Tools is distributed in the hope that it will be useful, but 
 * WITHOUT ANY WARRANTY; without even the implied warranty of 
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU 
 * General Public License for more details.
 * 
 * You should have received a copy of the GNU General Public License along 
 * with Ionflux Tools; if not, write to the Free Software Foundation, Inc.,
 * 59 Temple Place, Suite 330, Boston, MA 02111-1307 USA
 * 
 * ========================================================================== */

#include "ionflux/BufferedTable.hpp"

using namespace std;

namespace Ionflux
{

namespace Tools
{

const unsigned int BufferedTable::DEFAULT_BLOCK_SIZE = 50;

BufferedTable::BufferedTable()
: database(0), prevBlock(0), currentBlock(0), nextBlock(0), 
  currentOffset(0), blockSize(DEFAULT_BLOCK_SIZE), origin(""), table(""), 
  keyField(""), currentIndex(0)
{
	// TODO: Nothing ATM. ;-)
}

BufferedTable::BufferedTable(unsigned int initBlockSize)
: database(0), prevBlock(0), currentBlock(0), nextBlock(0), currentOffset(0), 
  blockSize(initBlockSize), origin(""), table(""), keyField(""), 
  currentIndex(0)
{
	// TODO: Nothing ATM. ;-)
}

BufferedTable::BufferedTable(Ionflux::Tools::Database* initDatabase)
: database(0), prevBlock(0), currentBlock(0), nextBlock(0), currentOffset(0), 
  blockSize(DEFAULT_BLOCK_SIZE), origin(""), table(""), keyField(""), 
  currentIndex(0)
{
	setDatabase(initDatabase);
}

BufferedTable::BufferedTable(Ionflux::Tools::Database* initDatabase, 
	unsigned int initBlockSize)
: database(0), prevBlock(0), currentBlock(0), nextBlock(0), currentOffset(0), 
  blockSize(initBlockSize), origin(""), table(""), keyField(""), 
  currentIndex(0)
{
	setDatabase(initDatabase);
}

BufferedTable::BufferedTable(Ionflux::Tools::Database* initDatabase, 
	unsigned int initBlockSize, const std::string& initTable, 
	const std::string& initKeyField, 
	const std::vector<std::string>& initFields)
: database(0), prevBlock(0), currentBlock(0), nextBlock(0), currentOffset(0), 
  blockSize(initBlockSize), origin(""), table(initTable), 
  keyField(initKeyField), currentIndex(0)
{
	setDatabase(initDatabase);
	setFields(initFields);
}

BufferedTable::BufferedTable(Ionflux::Tools::Database* initDatabase, 
	unsigned int initBlockSize, const std::string& initTable, 
	const std::string& initKeyField, 
	const std::vector<std::string>& initFields, const std::string& initOrigin)
: database(0), prevBlock(0), currentBlock(0), nextBlock(0), 
  currentOffset(0), blockSize(initBlockSize), origin(initOrigin), 
  table(initTable), keyField(initKeyField), currentIndex(0)
{
	setDatabase(initDatabase);
	setFields(initFields);
}

BufferedTable::~BufferedTable()
{
	clear();
	if (database != 0)
		database->unref();
}

void BufferedTable::cycleForward()
{
	// ----- DEBUG ----- //
	log.msg("[BufferedTable::cycleForward] DEBUG: "
		"Cycle buffer forward.", log.VL_DEBUG_INSANE);
	// ----- DEBUG ----- */
	if (prevBlock != 0)
		delete prevBlock;
	prevBlock = currentBlock;
	currentBlock = nextBlock;
	nextBlock = 0;
	currentOffset += blockSize;
}

void BufferedTable::cycleBackward()
{
	// ----- DEBUG ----- //
	log.msg("[BufferedTable::cycleBackward] DEBUG: "
		"Cycle buffer backward.", log.VL_DEBUG_INSANE);
	// ----- DEBUG ----- */
	if (nextBlock != 0)
		delete nextBlock;
	nextBlock = currentBlock;
	currentBlock = prevBlock;
	prevBlock = 0;
	currentOffset -= blockSize;
}

void BufferedTable::updateIndices()
{
	if (!log.assert(database != 0, "[BufferedTable::updateIndices] "
		"Database pointer is null."))
		return;
	// ----- DEBUG ----- //
	log.msg("[BufferedTable::updateIndices] DEBUG: "
		"Updating indices.", log.VL_DEBUG_INSANE);
	// ----- DEBUG ----- */
	ostringstream status;
	keyIndex.clear();
	offsetIndex.clear();
	// Create query.
	ostringstream query;
	query << "SELECT " << keyField << " FROM " << table << " ORDER BY " 
		<< keyField;
	bool result = database->query(query.str());
	if (!result)
	{
		DatabaseError dbError = database->getError();
		status.str("");
		status << "[BufferedTable::updateIndices] ERROR: "
			"Database query failed (" << dbError.errNum << ": " 
			<< dbError.error << ").";
		log.msg(status.str(), log.VL_ERROR);
		return;
	}
	DbResult data;
	result = database->fetchResult(data);
	if (!result)
	{
		status.str("");
		status << "[BufferedTable::updateIndices] ERROR: "
			"Could not fetch database query result.";
		log.msg(status.str(), log.VL_ERROR);
		return;
	}
	unsigned int numRecs = data.size();
	DbRow row;
	string currentKey;
	for (unsigned int i = 0; i < numRecs; i++)
	{
		row = data[i];
		if (row.size() > 0)
		{
			/* ----- DEBUG ----- //
			status.str("");
			status << "[BufferedTable::updateIndices] DEBUG: "
				"Adding index entry for "
				<< i <<  ":'" << currentKey << "'.";
			log.msg(status.str(), log.VL_DEBUG_INSANE);
			// ----- DEBUG ----- */
			currentKey = row[0];
			keyIndex.push_back(currentKey);
			offsetIndex[currentKey] = i;
		}
	}
}

void BufferedTable::initBlock(Ionflux::Tools::Node* target, 
	const std::string& fromKey, bool invert)
{
	if (!log.assert(database != 0, "[BufferedTable::initBlock] "
		"Database pointer is null."))
		return;
	if (!log.assert(target != 0, "[BufferedTable::initBlock] "
		"Target block pointer is null."))
		return;
	ostringstream status;
	// ----- DEBUG ----- //
	status.str("");
	string whichBlock;
	if (target == prevBlock)
		whichBlock = "PREVIOUS";
	else
	if (target == currentBlock)
		whichBlock = "CURRENT";
	else
	if (target == nextBlock)
		whichBlock = "NEXT";
	else
		whichBlock = "UNKNOWN";
	status << "[BufferedTable::initBlock] DEBUG: Initializing block ("
		<< whichBlock <<  ") from '" << fromKey << "', invert = ";
	if (invert)
		status << "YES.";
	else
		status << "NO.";
	log.msg(status.str(), log.VL_DEBUG_INSANE);
	// ----- DEBUG ----- */
	// Create query.
	ostringstream query;
	query << "SELECT " << keyField;
	unsigned int numFields = fields.size();
	if (numFields > 0)
		 query << ",";
	for (unsigned int i = 0; i < numFields; i++)
	{
		query << fields[i];
		if (i < (numFields - 1))
			query << ",";
	}
	query << " FROM " << table << " WHERE " << keyField;
	if (!invert)
		query << ">=";
	else
		query << "<=";
	query << "'" << database->sqlEscape(fromKey) << "' ORDER BY " << keyField;
	if (invert)
		query << " DESC";
	query << " LIMIT 0," << blockSize;
	// Execute query.
	bool result = database->query(query.str());
	if (!result)
	{
		DatabaseError dbError = database->getError();
		status.str("");
		status << "[BufferedTable::initBlock] ERROR: "
			"Database query failed (" << dbError.errNum << ": " 
			<< dbError.error << ").";
		log.msg(status.str(), log.VL_ERROR);
		return;
	}
	Node data;
	data.setAutoCreate(true);
	data.setIndexMode(Node::INDEX_MODE_NODE);
	result = database->fetchResultTree(data, Database::NODE_ORDER_ROWS);
	if (!result)
	{
		log.msg("[BufferedTable::initBlock] ERROR: "
			"Could not fetch result tree.", log.VL_ERROR);
		return;
	}
	// Copy data records.
	unsigned int numRecs = data.getNumChildren() - 1;
	// ----- DEBUG ----- //
	status.str("");
	status << "[BufferedTable::initBlock] DEBUG: "
		<< numRecs <<  " records in block.";
	log.msg(status.str(), log.VL_DEBUG_INSANE);
	// ----- DEBUG ----- */
	if (invert && (numRecs < blockSize))
		// Add missing records at start of block.
		for (unsigned int i = 0; i < (blockSize - numRecs); i++)
			target->addChild();
	Node *sourceChild = 0;
	Node *targetChild = 0;
	for (unsigned int i = 1; i < (numRecs + 1); i++)
	{
		if (!invert)
			sourceChild = data.getChild(i);
		else
			sourceChild = data.getChild(numRecs + 1 - i);
		if (!log.assert(target != 0, "[BufferedTable::initBlock] "
			"Source child node pointer is null."))
			return;
		targetChild = target->addChild();
		if (!log.assert(target != 0, "[BufferedTable::initBlock] "
			"Target child node pointer is null."))
			return;
		*targetChild = *sourceChild;
	}
}

int BufferedTable::getTableOffset(const std::string& key)
{
	ostringstream status;
	if (keyIndex.size() == 0)
		updateIndices();
	unsigned int offset = offsetIndex[key];
	// ----- DEBUG ----- //
	status.str("");
	status << "[BufferedTable::getTableOffset] DEBUG: Table offset for key '"
		<< key <<  "' = " << offset << ".";
	log.msg(status.str(), log.VL_DEBUG_INSANE);
	// ----- DEBUG ----- */
	return offset;
}

int BufferedTable::getBlockStartOffset(const std::string& key)
{
	ostringstream status;
	int keyOffset = getTableOffset(key);
	int blockStartOffset = -(keyOffset % blockSize);
	// ----- DEBUG ----- //
	status.str("");
	status << "[BufferedTable::getBlockStartOffset] DEBUG: "
		"Block start offset for key '" << key <<  "' = " 
		<< blockStartOffset << ".";
	log.msg(status.str(), log.VL_DEBUG_INSANE);
	// ----- DEBUG ----- */
	return blockStartOffset;
}

void BufferedTable::setConfig(Ionflux::Tools::Node& newConfig)
{
	/* ----- DEBUG ----- //
	ostringstream status;
	status.str("");
	status << "[BufferedTable::setConfig] DEBUG: "
		"Initializing configuration.";
	log.msg(status.str(), log.VL_DEBUG_INSANE);
	// ----- DEBUG ----- */
	config = newConfig;
	// This allows configuring a database on a per-table basis.
	Node &dbNode = config["database"];
	if (dbNode["type"].getData() == "MySQL")
	{
		Database *newDb = new MySQLDatabase();
		newDb->setConfig(dbNode);
		setDatabase(newDb);
	}
	setBlockSize(strtol(config["blockSize"].getData().c_str(), 0, 10));
	setCreateTemplate(config["createTemplate"].getData());
	setCreateTemplateFile(config["createTemplateFile"].getData());
	setKeyField(config["keyField"].getData());
	Node &fieldNode = config["fields"];
	for (unsigned int i = 0; i < fieldNode.getNumData(); i++)
		fields.push_back(fieldNode.getData(i));
	setTable(config["table"].getData());
	setOrigin(config["origin"].getData());
	setCurrentRecord(config["currentRecord"].getData());
}

void BufferedTable::setDatabase(Ionflux::Tools::Database* newDatabase)
{
	if ((newDatabase == database) || (newDatabase == 0))
		return;
	if (database != 0)
	{
		database->unref();
		pool.cleanup();
	}
	newDatabase->ref();
	pool.addObject(newDatabase);
	database = newDatabase;
}

Ionflux::Tools::Database* BufferedTable::getDatabase()
{
	if (database != 0)
		database->ref();
	return database;
}

bool BufferedTable::validateTable()
{
	if (table.size() == 0)
	{
		log.msg("[BufferedTable::validateTable] WARNING: "
			"Attempt to validate table, but table is not set.",
			log.VL_WARNING);
		return false;
	}
	if (!log.assert(database != 0, "[BufferedTable::validateTable] "
		"Database pointer is null."))
		return false;
	ostringstream status;
	DbTables tables;
	database->listTables(tables, table);
	bool found = false;
	unsigned int i = 0;
	while (!found && (i < tables.size()))
	{
		if (tables[i] == table)
			found = true;
		else
			i++;
	}
	if (found || (createTemplate.size() == 0))
	{
		// ----- DEBUG ----- //
		status.str("");
		if (!found)
		{
			status << "[BufferedTable::validateTable] DEBUG: Table '"
				<< table << "' does not exist and has NOT been created "
				"(create template not set).";
		} else
		{
			status << "[BufferedTable::validateTable] DEBUG: Table '"
				<< table << "' exists.";
		}
		log.msg(status.str(), log.VL_DEBUG_INSANE);
		// ----- DEBUG ----- */
		return found;
	}
	Template createTpl;
	createTpl.setTemplate(createTemplate);
	Node* createTplRoot = createTpl.getRoot();
	if (!log.assert(createTplRoot != 0, "[BufferedTable::validateTable] "
		"Create query template root node is null."))
		return false;
	*createTplRoot = config;
	string query = createTpl.process();
	// ----- DEBUG ----- //
	status.str("");
	status << "[BufferedTable::validateTable] DEBUG: Creating table '"
		<< table << "':" << endl << query;
	log.msg(status.str(), log.VL_DEBUG_INSANE);
	// ----- DEBUG ----- */
	bool result = database->query(query);
	if (!result)
	{
		DatabaseError dbError = database->getError();
		status.str("");
		status << "[BufferedTable::validateTable] ERROR: "
			"Database query failed (" << dbError.errNum << ": " 
			<< dbError.error << ").";
		log.msg(status.str(), log.VL_ERROR);
		return false;
	}
	return true;
}

Ionflux::Tools::Node* BufferedTable::getRecord(int recIndex)
{
	setCurrentIndex(recIndex);
	return getCurrentRecord();
}

Ionflux::Tools::Node* BufferedTable::operator[](int recIndex)
{
	return getRecord(recIndex);
}

Ionflux::Tools::Node* BufferedTable::getCurrentRecord()
{
	ostringstream status;
	Node *result = 0;
	string key;
	/* Handle records which are not possibly in any of the allocated buffer
	   blocks. */
	if ((currentIndex < (currentOffset - static_cast<int>(blockSize)))
		|| (currentIndex >= (currentOffset + 2 * static_cast<int>(blockSize))))
	{
		/* Re-initialize the buffer. After this, the current record 
		   will be in the current block. */
		// ----- DEBUG ----- //
		status.str("");
		status << "[BufferedTable::getCurrentRecord] DEBUG: Current record ("
			<< currentIndex <<  ") not in allocated buffers.";
		log.msg(status.str(), log.VL_DEBUG_INSANE);
		// ----- DEBUG ----- */
		clearBlocks();
		currentBlock = new Node();
		currentBlock->setAutoCreate(true);
		currentBlock->setIndexMode(Node::INDEX_MODE_NODE);
		key = getKey(currentIndex);
		if (key.size() == 0)
		{
			status.str("");
			status << "[BufferedTable::getCurrentRecord] WARNING: "
				<< "Record with index " << currentIndex 
				<< " does not exist.";
			log.msg(status.str(), log.VL_WARNING);
			return 0;
		}
		int blockStartOffset = getBlockStartOffset(key);
		if (blockStartOffset == 0)
		{
			// Current record is the first record of a block.
			// ----- DEBUG ----- //
			log.msg("[BufferedTable::getCurrentRecord] DEBUG: "
				"Current record is first in data block.", log.VL_DEBUG_INSANE);
			// ----- DEBUG ----- */
			initBlock(currentBlock, key);
			currentOffset = currentIndex;
		} else
		{
			// Determine the first record of the block.
			// ----- DEBUG ----- //
			status.str("");
			status << "[BufferedTable::getCurrentRecord] DEBUG: "
				"Block start offset = "	<< blockStartOffset <<  ".";
			log.msg(status.str(), log.VL_DEBUG_INSANE);
			// ----- DEBUG ----- */
			string blockStartKey = getKey(key, blockStartOffset);
			if (!log.assert(blockStartKey.size() > 0, 
				"[BufferedTable::getCurrentRecord] "
				"First key of block does not exist."))
				return 0;
			initBlock(currentBlock, blockStartKey);
			currentOffset = currentIndex + blockStartOffset;
		}
	} else
	/* Cycle blocks if current record is in the previous or next block. 
	   After this, the current record will be in the current block. */
	if ((currentIndex >= (currentOffset - static_cast<int>(blockSize))) 
		&& (currentIndex < currentOffset))
		cycleBackward();
	else
	if ((currentIndex >= (currentOffset + static_cast<int>(blockSize))) 
		&& (currentIndex < (currentOffset + 2 * static_cast<int>(blockSize))))
		cycleForward();
	// Handle records which are in the current block.
	if ((currentIndex >= currentOffset) 
		&& (currentIndex < (currentOffset + static_cast<int>(blockSize))))
	{
		if (currentBlock == 0)
		{
			// ----- DEBUG ----- //
			log.msg("[BufferedTable::getCurrentRecord] DEBUG: "
				"Initializing current block.", log.VL_DEBUG_INSANE);
			// ----- DEBUG ----- */
			key = getKey(currentOffset);
			bool invert = false;
			if (key.size() == 0)
			{
				/* First record of the block does not exist, try to start 
				   initialization with the last record. */
				// ----- DEBUG ----- //
				log.msg("[BufferedTable::getCurrentRecord] DEBUG: "
					"First record of block does not exist, trying inverse "
					"initialization.", log.VL_DEBUG_INSANE);
				// ----- DEBUG ----- */
				key = getKey(currentOffset + blockSize - 1);
				if (key.size() == 0)
				{
					status.str("");
					status << "[BufferedTable::getCurrentRecord] WARNING: "
						<< "First record of block does not exist (offset = "
						<< currentOffset << ").";
					log.msg(status.str(), log.VL_WARNING);
					return 0;
				} else
					invert = true;
			}
			currentBlock = new Node();
			currentBlock->setAutoCreate(true);
			currentBlock->setIndexMode(Node::INDEX_MODE_NODE);
			initBlock(currentBlock, key, invert);
		}
		int childIndex = currentIndex - currentOffset;
		if ((childIndex >= 0) 
			&& (static_cast<unsigned int>(childIndex) 
				< currentBlock->getNumChildren()))
			result = currentBlock->getChild(childIndex);
	}
	return result;
}

Ionflux::Tools::Node* BufferedTable::getNextRecord()
{
	currentIndex++;
	return getCurrentRecord();
}

Ionflux::Tools::Node* BufferedTable::getPrevRecord()
{
	currentIndex--;
	return getCurrentRecord();
}

std::string BufferedTable::getKey(const std::string& key, int recOffset)
{
	if (!log.assert(database != 0, "[BufferedTable::getKey] "
		"Database pointer is null."))
		return 0;
	ostringstream status;
	// ----- DEBUG ----- //
	status.str("");
	status << "[BufferedTable::getKey] DEBUG: Fetching key from '"
		<< key <<  "', offset = " << recOffset << ".";
	log.msg(status.str(), log.VL_DEBUG_INSANE);
	// ----- DEBUG ----- */
	ostringstream query;
	int numRecs = getNumRecs();
	int keyOffset = getTableOffset(key);
	if (((recOffset < 0) && (-recOffset > keyOffset))
		|| ((recOffset > 0) && ((recOffset + keyOffset + 1) > numRecs)))
	{
		// Record does not exist.
		// ----- DEBUG ----- //
		log.msg("[BufferedTable::getKey] DEBUG: Record does not exist.", 
			log.VL_DEBUG_INSANE);
		// ----- DEBUG ----- */
		return "";
	} else
	{
		// Get key from database.
		// ----- DEBUG ----- //
		log.msg("[BufferedTable::getKey] DEBUG: Fetching key from database.", 
			log.VL_DEBUG_INSANE);
		// ----- DEBUG ----- */
		if (recOffset < 0)
			query << "SELECT " << keyField << " FROM " << table 
				<< " WHERE " << keyField << "<='" 
				<< database->sqlEscape(key) << "' ORDER BY " << keyField
				<< " DESC LIMIT " << -recOffset << ",1";
		else
			query << "SELECT " << keyField << " FROM " << table 
				<< " WHERE " << keyField << ">='" 
				<< database->sqlEscape(key) << "' ORDER BY " << keyField
				<< " LIMIT " << recOffset << ",1";
		bool result = database->query(query.str());
		if (!result)
		{
			DatabaseError dbError = database->getError();
			status << "[BufferedTable::getKey] ERROR: "
				"Database query failed (" << dbError.errNum << ": " 
				<< dbError.error << ").";
			log.msg(status.str(), log.VL_ERROR);
			return "";
		}
		DbRow row;
		result = database->fetchRow(row);
		if (!result || (row.size() < 1))
		{
			log.msg("[BufferedTable::getKey] ERROR: "
				"Could not fetch result row.", log.VL_ERROR);
			return "";
		}
		return row[0];
	}
	return "";
}

std::string BufferedTable::getKey(int recIndex)
{
	ostringstream status;
	// Return origin for index zero (this is the easy part).
	if (recIndex == 0)
		return origin;
	if (!log.assert(database != 0, "[BufferedTable::getKey] "
		"Database pointer is null."))
		return "";
	// Fetch key from non-empty buffer blocks (if possible).
	Node *sourceRec = 0;
	if ((currentBlock != 0) && (recIndex >= currentOffset) 
		&& (recIndex < (currentOffset + static_cast<int>(blockSize))))
	{
		// Record is in current block.
		/* ----- DEBUG ----- //
		status.str("");
		status << "[BufferedTable::getKey] DEBUG: Record ("
			<< recIndex << ") is in CURRENT block.";
		log.msg(status.str(), log.VL_DEBUG_INSANE);
		// ----- DEBUG ----- */
		sourceRec = currentBlock->getChild(recIndex - currentOffset);
	} else
	if ((prevBlock != 0) 
		&& (recIndex >= (currentOffset - static_cast<int>(blockSize))) 
		&& (recIndex < currentOffset))
	{
		// Record is in previous block.
		/* ----- DEBUG ----- //
		status.str("");
		status << "[BufferedTable::getKey] DEBUG: Record ("
			<< recIndex << ") is in PREVIOUS block.";
		log.msg(status.str(), log.VL_DEBUG_INSANE);
		// ----- DEBUG ----- */
		sourceRec = prevBlock->getChild(recIndex - currentOffset);
	} else
	if ((nextBlock != 0) 
		&& (recIndex >= (currentOffset + static_cast<int>(blockSize))) 
		&& (recIndex < (currentOffset + 2 * static_cast<int>(blockSize))))
	{
		// Record is in next block.
		/* ----- DEBUG ----- //
		status.str("");
		status << "[BufferedTable::getKey] DEBUG: Record ("
			<< recIndex << ") is in NEXT block.";
		log.msg(status.str(), log.VL_DEBUG_INSANE);
		// ----- DEBUG ----- */
		sourceRec = nextBlock->getChild(recIndex - currentOffset);
	}
	if (sourceRec != 0)
		return sourceRec->getData(0);
	// Fetch key from database (if possible).
	return getKey(origin, recIndex);
}

std::string BufferedTable::fetchKey(unsigned int offset)
{
	unsigned int numRecs = getNumRecs();
	if (offset >= numRecs)
		return "";
	if (!log.assert(database != 0, "[BufferedTable::fetchKey] "
		"Database pointer is null."))
		return "";
	ostringstream status;
	ostringstream query;
	query << "SELECT " << keyField << " FROM " << table << " ORDER BY " 
		<< keyField << " LIMIT " << offset << ",1";
	bool result = database->query(query.str());
	if (!result)
	{
		DatabaseError dbError = database->getError();
		status << "[BufferedTable::fetchKey] ERROR: "
			"Database query failed (" << dbError.errNum << ": " 
			<< dbError.error << ").";
		log.msg(status.str(), log.VL_ERROR);
		return "";
	}
	DbRow row;
	result = database->fetchRow(row);
	if (!result || (row.size() < 1))
	{
		log.msg("[BufferedTable::fetchKey] ERROR: "
			"Could not fetch result row.", log.VL_ERROR);
		return 0;
	}
	return row[0];
}

unsigned int BufferedTable::getNumRecs()
{
	if (!log.assert(database != 0, "[BufferedTable::getNumRecs] "
		"Database pointer is null."))
		return 0;
	ostringstream status;
	ostringstream query;
	query << "SELECT COUNT(*) FROM " << table;
	bool result = database->query(query.str());
	if (!result)
	{
		DatabaseError dbError = database->getError();
		status << "[BufferedTable::getNumRecs] ERROR: "
			"Database query failed (" << dbError.errNum << ": " 
			<< dbError.error << ").";
		log.msg(status.str(), log.VL_ERROR);
		return 0;
	}
	DbRow row;
	result = database->fetchRow(row);
	if (!result || (row.size() < 1))
	{
		log.msg("[BufferedTable::getNumRecs] ERROR: "
			"Could not fetch result row.", log.VL_ERROR);
		return 0;
	}
	return strtol(row[0].c_str(), 0, 10);
}

unsigned int BufferedTable::getFieldIndex(const std::string& fieldName)
{
	ostringstream status;
	// ----- DEBUG ----- //
	status.str("");
	status << "[BufferedTable::getFieldIndex] DEBUG: "
		"Searching field index for '" << fieldName << "'.";
	log.msg(status.str(), log.VL_DEBUG_INSANE);
	// ----- DEBUG ----- */
	bool found = false;
	if (fieldName == keyField)
	{
		// ----- DEBUG ----- //
		status.str("");
		status << "[BufferedTable::getFieldIndex] DEBUG: "
			"Field '" << fieldName << "' is key field (index = 0).";
		log.msg(status.str(), log.VL_DEBUG_INSANE);
		// ----- DEBUG ----- */
		return 0;
	}
	unsigned int i = 0;
	while (!found && (i < fields.size()))
	{
		if (fields[i] == fieldName)
			found = true;
		else
			i++;
	}
	if (found)
	{
		// ----- DEBUG ----- //
		status.str("");
		status << "[BufferedTable::getFieldIndex] DEBUG: "
			"Field '" << fieldName << "' found (index = " << (i + 1) << ").";
		log.msg(status.str(), log.VL_DEBUG_INSANE);
		// ----- DEBUG ----- */
		return i + 1;
	}
	status.str("");
	status << "[BufferedTable::getFieldIndex] WARNING: "
		"Field '" << fieldName << "' not found.";
	log.msg(status.str(), log.VL_WARNING);
	return 0;
}

void BufferedTable::refresh()
{
	// This may seem pretty brutal, but does the job just fine. ;-)
	clearBlocks();
	updateIndices();
}

void BufferedTable::clearBlocks()
{
	if (prevBlock != 0)
		delete prevBlock;
	prevBlock = 0;
	if (currentBlock != 0)
		delete currentBlock;
	currentBlock = 0;
	if (nextBlock != 0)
		delete nextBlock;
	nextBlock = 0;
}

void BufferedTable::clear()
{
	clearBlocks();
	keyIndex.clear();
	offsetIndex.clear();
	currentOffset = 0;
	currentIndex = 0;
}

Ionflux::Tools::Reporter& BufferedTable::getLog()
{
	return log;
}

void BufferedTable::setCurrentRecord(const std::string& newKey)
{
	ostringstream status;
	if (newKey.size() == 0)
	{
		status.str("");
		status << "[BufferedTable::setCurrentRecord] WARNING: "
			" Attempt to set current record by empty key.";
		log.msg(status.str(), log.VL_WARNING);
		return;
	}
	// ----- DEBUG ----- //
	status.str("");
	status << "[BufferedTable::setCurrentRecord] DEBUG: "
		"Setting current record by key '" << newKey << "'.";
	log.msg(status.str(), log.VL_DEBUG_INSANE);
	// ----- DEBUG ----- */
	int newKeyOffset = getTableOffset(newKey);
	int originOffset = getTableOffset(origin);
	setCurrentIndex(newKeyOffset - originOffset);
}

void BufferedTable::setBlockSize(unsigned int newBlockSize)
{
	clear();
	if (newBlockSize > 0)
		blockSize = newBlockSize;
	else
		blockSize = DEFAULT_BLOCK_SIZE;
}

void BufferedTable::setOrigin(const std::string& newOrigin)
{
	if (newOrigin.size() == 0)
		setOrigin(0);
	if (isNumber(newOrigin))
		setOrigin(strtol(newOrigin.c_str(), 0, 10));
	else
	{
		clear();
		origin = newOrigin;
	}
}

void BufferedTable::setOrigin(unsigned int offset)
{
	clear();
	origin = fetchKey(offset);
}

void BufferedTable::setTable(const std::string& newTable)
{
	clear();
	table = newTable;
	validateTable();
	// updateIndices();
}

void BufferedTable::setKeyField(const std::string& newKeyField)
{
	clear();
	keyField = newKeyField;
}

void BufferedTable::setFields(const std::vector<std::string>& newFields)
{
	clear();
	fields = newFields;
}

void BufferedTable::setCurrentIndex(int newCurrentIndex)
{
	currentIndex = newCurrentIndex;
}

void BufferedTable::setCreateTemplate(const std::string& newCreateTemplate)
{
	createTemplate = newCreateTemplate;
}

void BufferedTable::setCreateTemplateFile(
	const std::string& newCreateTemplateFile)
{
	createTemplateFile = newCreateTemplateFile;
	if (createTemplateFile.size() != 0)
		createTemplate = readFile(createTemplateFile);
}


unsigned int BufferedTable::getBlockSize() const
{
	return blockSize;
}

std::string BufferedTable::getOrigin() const
{
	return origin;
}

std::string BufferedTable::getTable() const
{
	return table;
}

std::string BufferedTable::getKeyField() const
{
	return keyField;
}

std::vector<std::string> BufferedTable::getFields() const
{
	return fields;
}

int BufferedTable::getCurrentIndex() const
{
	return currentIndex;
}

std::string BufferedTable::getCreateTemplate() const
{
	return createTemplate;
}

std::string BufferedTable::getCreateTemplateFile() const
{
	return createTemplateFile;
}

}

}

/** \file BufferedTable.cpp
 * \brief Buffered database table implementation.
 */
