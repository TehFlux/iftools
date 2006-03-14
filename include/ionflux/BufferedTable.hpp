#ifndef IONFLUX_TOOLS_BUFFEREDTABLE
#define IONFLUX_TOOLS_BUFFEREDTABLE
/* ==========================================================================
 * Ionflux Tools
 * Copyright (c) 2005 Joern P. Meier
 * mail@ionflux.org
 * --------------------------------------------------------------------------
 * BufferedTable.hpp                 Buffered database table.
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

#include <string>
#include <iostream>
#include <sstream>
#include <vector>
#include "ionflux/Reporter.hpp"
#include "ionflux/MySQLDatabase.hpp"
#include "ionflux/Node.hpp"
#include "ionflux/Template.hpp"
#include "ionflux/ObjectPool.hpp"

namespace Ionflux
{

namespace Tools
{

/** Buffered database table.
 * \ingroup database
 *
 * A buffered table providing access to records which are stored in a 
 * database table. The table buffer allows for the efficient sequential 
 * retrieval of records from the database, where the order of records is 
 * defined by a specified key field. This is achieved by fetching a block 
 * (or page) of records on each database query. Records from the blocks 
 * loaded into memory may then be accessed sequentially. A new block is 
 * fetched from the database automatically whenever the current index 
 * pointer goes out of the scope of a block.
 * 
 * \note The buffered table also allows random access, however, this does 
 * not have any advantages in efficiency unless the random accesses occur 
 * within order of the block size.
 */
class BufferedTable
: public Ionflux::Tools::ManagedObject
{
	private:
		
	protected:
		/// Console output/logging.
		Ionflux::Tools::Reporter log;
		/// Object allocation pool.
		Ionflux::Tools::ObjectPool pool;
		/// Source database.
		Ionflux::Tools::Database* database;
		/// Previous block.
		Ionflux::Tools::Node* prevBlock;
		/// Current block.
		Ionflux::Tools::Node* currentBlock;
		/// Next block.
		Ionflux::Tools::Node* nextBlock;
		/// Index of the first record of the current block.
		int currentOffset;
		/// Key/offset index.
		std::map<std::string, unsigned int> offsetIndex;
		/// Offset/key index.
		std::vector<std::string> keyIndex;
		/// Buffer block size.
		unsigned int blockSize;
		/// Key of the record with index pointer zero.
		std::string origin;
		/// Source database table name.
		std::string table;
		/// Name of the key field of the source database table.
		std::string keyField;
		/// Names of fields to be included in each record.
		std::vector<std::string> fields;
		/// Index of current record.
		int currentIndex;
		/// Create template.
		std::string createTemplate;
		/// Create template file name.
		std::string createTemplateFile;
		/// Buffered table configuration node.
		Ionflux::Tools::Node config;
		
		/** Cycle buffers (forward).
		 *
		 * Cycle the buffer blocks forward.
		 * 
		 * \note This effectively discards the previous block, sets the 
		 * previous block to the current block, the current block to the next 
		 * block end empties the next block.
		 */
		virtual void cycleForward();
		
		/** Cycle buffers (backward).
		 *
		 * Cycle the buffer blocks backward.
		 * 
		 * \note This effectively discards the next block, sets the next block
		 * to the current block, the current block to the previous block end 
		 * empties the previous block.
		 */
		virtual void cycleBackward();
		
		/** Update indices.
		 *
		 * Update the key/offset and offset/key indices.
		 */
		virtual void updateIndices();
		
		/** Initialize buffer block.
		 *
		 * Initialize a block of the buffer with records starting from the 
		 * specified key value.
		 * 
		 * \note Pass \c true to \c invert to initialize a block with records 
		 * starting from the last record (instead of the first) counting 
		 * records backwards and result records being aligned to the end of 
		 * the block (instead of the start of the block).
		 *
		 * \param target Where to store the resulting records.
		 * \param fromKey Key of the first (or last, if \c invert is \c true) 
		 * record of the block.
		 * \param invert Whether initialization order should be inverted.
		 */
		virtual void initBlock(Ionflux::Tools::Node* target, 
			const std::string& fromKey, bool invert = false);
		
		/** Get block start offset.
		 *
		 * Get the offset of the start of the data block which contains the 
		 * specified key, relative to the specified key.
		 * 
		 * \note A data block is a block of data in the source database table 
		 * of buffer block size, with the first block aligned to the start of 
		 * the table. The data block that contains a certain key may be 
		 * different from the buffer block that contains that same key. Data 
		 * and buffer blocks can contain the same data only if the buffer 
		 * block boundaries are aligned to the data block boundaries.
		 *
		 * \param key Key.
		 *
		 * \return Block start offset.
		 */
		virtual int getBlockStartOffset(const std::string& key);
		
	public:
		/// Default buffering block size.
		static const unsigned int DEFAULT_BLOCK_SIZE;
		
		/** Constructor.
		 *
		 * Construct new BufferedTable object.
		 */
		BufferedTable();
		
		/** Constructor.
		 *
		 * Construct new BufferedTable object.
		 *
		 * \param initBlockSize Buffering block size.
		 */
		BufferedTable(unsigned int initBlockSize);
		
		/** Constructor.
		 *
		 * Construct new BufferedTable object.
		 *
		 * \param initDatabase Source database.
		 */
		BufferedTable(Ionflux::Tools::Database* initDatabase);
		
		/** Constructor.
		 *
		 * Construct new BufferedTable object.
		 *
		 * \param initDatabase Source database.
		 * \param initBlockSize Buffering block size.
		 */
		BufferedTable(Ionflux::Tools::Database* initDatabase, unsigned int 
		initBlockSize);
		
		/** Constructor.
		 *
		 * Construct new BufferedTable object.
		 *
		 * \param initDatabase Source database.
		 * \param initBlockSize Buffering block size.
		 * \param initTable Source database table name.
		 * \param initKeyField Name of the key field of the source database 
		 * table.
		 * \param initFields Names of fields to be included in each record.
		 */
		BufferedTable(Ionflux::Tools::Database* initDatabase, unsigned int 
		initBlockSize, const std::string& initTable, const std::string& 
		initKeyField, const std::vector<std::string>& initFields);
		
		/** Constructor.
		 *
		 * Construct new BufferedTable object.
		 *
		 * \param initDatabase Source database.
		 * \param initBlockSize Buffering block size.
		 * \param initTable Source database table name.
		 * \param initKeyField Name of the key field of the source database 
		 * table.
		 * \param initFields Names of fields to be included in each record.
		 * \param initOrigin Key of the record with index pointer zero.
		 */
		BufferedTable(Ionflux::Tools::Database* initDatabase, unsigned int 
		initBlockSize, const std::string& initTable, const std::string& 
		initKeyField, const std::vector<std::string>& initFields, const 
		std::string& initOrigin);
		
		/** Destructor.
		 *
		 * Destruct BufferedTable object.
		 */
		virtual ~BufferedTable();
		
		/** Set configuration.
		 *
		 * Initialize the configuration of the buffered table from a 
		 * configuration data node.
		 *
		 * \param newConfig Configuration node.
		 */
		virtual void setConfig(Ionflux::Tools::Node& newConfig);
		
		/** Set source database.
		 *
		 * Set the source database that will be used for fetching record 
		 * blocks.
		 *
		 * \param newDatabase Source database.
		 */
		virtual void setDatabase(Ionflux::Tools::Database* newDatabase);
		
		/** Get source database.
		 *
		 * Get the source database that will be used for fetching record 
		 * blocks.
		 *
		 * \return Source database. (The returned object will be referenced).
		 */
		virtual Ionflux::Tools::Database* getDatabase();
		
		/** Validate database table.
		 *
		 * Validate the existence of the database table. If the table does not
		 * exist and a template is set, the table will be created 
		 * automatically.
		 *
		 * \return \c true on success, \c false otherwise.
		 */
		virtual bool validateTable();
		
		/** Get record.
		 *
		 * Get the record with the specified index.
		 *
		 * \param recIndex Record index.
		 *
		 * \return Record with specified index, or null if the record does not 
		 * exist.
		 */
		virtual Ionflux::Tools::Node* getRecord(int recIndex);
		
		/** Get record.
		 *
		 * Get the record with the specified index.
		 *
		 * \param recIndex Record index.
		 *
		 * \return Record with specified index, or null if the record does not 
		 * exist.
		 */
		virtual Ionflux::Tools::Node* operator[](int recIndex);
		
		/** Get current record.
		 *
		 * Get the current record.
		 *
		 * \return Current record, or null if the record does not exist.
		 */
		virtual Ionflux::Tools::Node* getCurrentRecord();
		
		/** Get next record.
		 *
		 * Get the next record.
		 * 
		 * \note This also makes the next record the current record.
		 *
		 * \return Next record, or null if the record does not exist.
		 */
		virtual Ionflux::Tools::Node* getNextRecord();
		
		/** Get previous record.
		 *
		 * Get the previous record.
		 * 
		 * \note This also makes the previous record the current record.
		 *
		 * \return Previous record, or null if the record does not exist.
		 */
		virtual Ionflux::Tools::Node* getPrevRecord();
		
		/** Get key table offset.
		 *
		 * Get the database table offset (position relative to the start of 
		 * the table) of a key.
		 *
		 * \param key Key.
		 *
		 * \return Table offset.
		 */
		virtual int getTableOffset(const std::string& key);
		
		/** Get key.
		 *
		 * Get the key of the record with the specified offset relative to the
		 * record with the specified key.
		 * 
		 * \sa fetchKey
		 *
		 * \param key Key.
		 * \param recOffset Offset of target record.
		 *
		 * \return Key of record with specified offset relative to specified key,
		 * or an empty string if the record does not exist.
		 */
		virtual std::string getKey(const std::string& key, int recOffset);
		
		/** Get key by index.
		 *
		 * Get the key of the record with the specified index relative to the 
		 * origin.
		 * 
		 * \sa fetchKey
		 *
		 * \param recIndex Record index.
		 *
		 * \return Key of record with specified index, or an empty string if the 
		 * record does not exist.
		 */
		virtual std::string getKey(int recIndex);
		
		/** Get key from database table.
		 *
		 * Get the key of the record with the specified offset from the start 
		 * of the database table.
		 * 
		 * \sa getKey
		 *
		 * \param offset Record offset.
		 *
		 * \return Key of record with specified offset, or an empty string if 
		 * record does not exist..
		 */
		virtual std::string fetchKey(unsigned int offset);
		
		/** Get number of records.
		 *
		 * Get the number of records in the source database table.
		 *
		 * \return Number of records.
		 */
		virtual unsigned int getNumRecs();
		
		/** Get field index.
		 *
		 * Get the index of the specified field.
		 *
		 * \param fieldName Field name.
		 *
		 * \return Field index.
		 */
		virtual unsigned int getFieldIndex(const std::string& fieldName);
		
		/** Refresh buffer.
		 *
		 * Refresh the buffer to reflect changes in the database table.
		 * 
		 * \note This function should always be called after records have been
		 * inserted, changed or deleted in the database table. Failing to do 
		 * this may result in inaccurate buffers or even errors.
		 */
		virtual void refresh();
		
		/** Clear buffer blocks.
		 *
		 * Clear all records from the buffer blocks.
		 * 
		 * \note While this function will clear all data from the buffer, it 
		 * will not touch any of the other internal state (unlike clear()).
		 * 
		 * \sa clear
		 */
		virtual void clearBlocks();
		
		/** Clear buffer.
		 *
		 * Clear all records from the buffer.
		 */
		virtual void clear();
		
		/** Get Console output/logging facility.
		 *
		 * The console output/logging facility used by this object.
		 *
		 * \return Console output/logging facility.
		 */
		virtual Ionflux::Tools::Reporter& getLog();
		
		/** Set key of the record with index pointer zero.
		 *
		 * Set the key of the record with index pointer zero by its offset in 
		 * the database table.
		 *
		 * \param offset Database table offset.
		 */
		virtual void setOrigin(unsigned int offset);
		
		/** Set current record.
		 *
		 * Set the current record by key.
		 *
		 * \sa setCurrentIndex
		 *
		 * \param newKey Key of record to be set as current record.
		 */
		virtual void setCurrentRecord(const std::string& newKey);
		
		/** Set buffer block size.
		 *
		 * Set new value of buffer block size.
		 *
		 * \param newBlockSize New value of buffer block size.
		 */
		virtual void setBlockSize(unsigned int newBlockSize);
		
		/** Set key of the record with index pointer zero.
		 *
		 * Set new value of key of the record with index pointer zero.
		 *
		 * \param newOrigin New value of key of the record with index pointer 
		 * zero.
		 */
		virtual void setOrigin(const std::string& newOrigin);
		
		/** Set source database table name.
		 *
		 * Set new value of source database table name.
		 *
		 * \param newTable New value of source database table name.
		 */
		virtual void setTable(const std::string& newTable);
		
		/** Set name of the key field of the source database table.
		 *
		 * Set new value of name of the key field of the source database table.
		 *
		 * \param newKeyField New value of name of the key field of the source 
		 * database table.
		 */
		virtual void setKeyField(const std::string& newKeyField);
		
		/** Set names of fields to be included in each record.
		 *
		 * Set new value of names of fields to be included in each record.
		 *
		 * \param newFields New value of names of fields to be included in each 
		 * record.
		 */
		virtual void setFields(const std::vector<std::string>& newFields);
		
		/** Set index of current record.
		 *
		 * Set new value of index of current record.
		 *
		 * \param newCurrentIndex New value of index of current record.
		 */
		virtual void setCurrentIndex(int newCurrentIndex);
		
		/** Set create template.
		 *
		 * Set new value of create template.
		 *
		 * \param newCreateTemplate New value of create template.
		 */
		virtual void setCreateTemplate(const std::string& newCreateTemplate);
		
		/** Set create template file name.
		 *
		 * Set new value of create template file name.
		 *
		 * \param newCreateTemplateFile New value of create template file name.
		 */
		virtual void setCreateTemplateFile(const std::string& 
		newCreateTemplateFile);
		
		/** Get buffer block size.
		 *
		 * \return Current value of buffer block size.
		 */
		virtual unsigned int getBlockSize() const;
		
		/** Get key of the record with index pointer zero.
		 *
		 * \return Current value of key of the record with index pointer zero.
		 */
		virtual std::string getOrigin() const;
		
		/** Get source database table name.
		 *
		 * \return Current value of source database table name.
		 */
		virtual std::string getTable() const;
		
		/** Get name of the key field of the source database table.
		 *
		 * \return Current value of name of the key field of the source database 
		 * table.
		 */
		virtual std::string getKeyField() const;
		
		/** Get names of fields to be included in each record.
		 *
		 * \return Current value of names of fields to be included in each 
		 * record.
		 */
		virtual std::vector<std::string> getFields() const;
		
		/** Get index of current record.
		 *
		 * \return Current value of index of current record.
		 */
		virtual int getCurrentIndex() const;
		
		/** Get create template.
		 *
		 * \return Current value of create template.
		 */
		virtual std::string getCreateTemplate() const;
		
		/** Get create template file name.
		 *
		 * \return Current value of create template file name.
		 */
		virtual std::string getCreateTemplateFile() const;
		
};

}

}

/** \file BufferedTable.hpp
 * \brief Buffered database table header.
 */
#endif
