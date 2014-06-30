#ifndef IONFLUX_TEMPLATE_NODE
#define IONFLUX_TEMPLATE_NODE
/* ==========================================================================
 * IFTemplate - Ionflux Template Processor
 * Copyright © 2012 Jörn P. Meier
 * mail@ionflux.org
 * --------------------------------------------------------------------------
 * Node.hpp                        Tree node (header).
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
#include "ifobject/types.hpp"
#include "iftemplate/types.hpp"
#include "ifobject/IFObject.hpp"

namespace Ionflux
{

namespace Template
{

class NodeDump;

/// Class information for class Node.
class NodeClassInfo
: public Ionflux::ObjectBase::IFClassInfo
{
	public:
		/// Constructor.
		NodeClassInfo();
		/// Destructor.
		virtual ~NodeClassInfo();
};

/** Tree node.
 * \ingroup iftemplate
 *
 * A single data node of a tree. Tree nodes can be used to store data of a 
 * hierarchical, non-cyclical structure, where each child node has exactly 
 * one parent node and loops do not exist. Each node also has a data vector
 * where a large amount of values of identical type may be stored without 
 * the need of additional nodes. The type of a node can be one of BLOB, INT
 * or DOUBLE, and all data will be converted as best as possible to fit the
 * specified node data type. The node object also provides transparent  
 * serialization and unpacking of sub-trees from a data buffer and node  
 * resolution from a fully qualified tree path (see  
 * docs/node-serialization.txt and docs/path-resolution.txt for additional
 * information). Dynamic auto-creation of child nodes is also supported.
 */
class Node
: public Ionflux::ObjectBase::IFObject
{
	private:
		
	protected:
		/// Child nodes.
		Ionflux::Template::NodeVector children;
		/// Data entries.
		Ionflux::ObjectBase::StringVector nodeData;
		/// Node index by name.
		Ionflux::Template::NodeNameMap nameIndex;
		/// Node index by ID.
		Ionflux::Template::NodeVector idIndex;
		/// Numerical ID.
		Ionflux::Template::NodeID nodeID;
		/// Name of the node.
		std::string nodeName;
		/// Data type.
		Ionflux::Template::NodeDataTypeID dataType;
		/// Parent node.
		Ionflux::Template::Node* parent;
		/// Maximum UID that has been assigned by this node.
		Ionflux::Template::NodeID maxUID;
		/// Child node UID assignment mode.
		Ionflux::Template::NodeUIDMode uidMode;
		/// Create requested child nodes and data entries on the fly.
		bool autoCreate;
		/// Child node indexing mode.
		Ionflux::Template::NodeIndexMode indexMode;
		
		/** Validate child node index.
		 *
		 * Check whether the child node index references a valid child node.
		 * 
		 * \note If the child node does not exist, but auto-create mode is set
		 * to \c true, the child node will be created.
		 *
		 * \param childIndex child node index to be validated.
		 *
		 * \return \c true if a child node with specified index exists, \c false 
		 * otherwise..
		 */
		virtual bool validateChildIndex(unsigned int childIndex);
		
		/** Validate child node index.
		 *
		 * Check whether the child node index references a valid child node.
		 * 
		 * \note If the child node does not exist, but auto-create mode is set
		 * to \c true, the child node will be created.
		 *
		 * \param childIndex child node index to be validated.
		 *
		 * \return \c true if a child node with specified index exists, \c false 
		 * otherwise..
		 */
		virtual bool validateChildIndex(unsigned int childIndex) const;
		
		/** Validate data index.
		 *
		 * Check whether the data index references a valid data entry.
		 * 
		 * \note If the data entry does not exist, but auto-create mode is set
		 * to \c true, the data entry will be created.
		 *
		 * \param dataIndex data index to be validated.
		 *
		 * \return \c true if a data entry with specified index exists, \c false 
		 * otherwise..
		 */
		virtual bool validateDataIndex(unsigned int dataIndex);
		
		/** Validate data index.
		 *
		 * Check whether the data index references a valid data entry.
		 *
		 * \param dataIndex data index to be validated.
		 *
		 * \return \c true if a data entry with specified index exists, \c false 
		 * otherwise..
		 */
		virtual bool validateDataIndex(unsigned int dataIndex) const;
		
		/** Add index entry.
		 *
		 * Adds a child node to the name or ID index (or both).
		 * 
		 * \note A child node will be added to an index only if either its 
		 * name is not the empty string or its ID is not ID_NOT_SET and not 
		 * negative. If both keys (name or ID) are set to suitable values, the
		 * node will be added to both indexes. If the indexing mode is 
		 * INDEX_MODE_NONE or \c indexNode is 0, this function will do 
		 * nothing.
		 *
		 * \param indexNode node for which to add an index entry.
		 */
		virtual void addIndexEntry(Ionflux::Template::Node* indexNode);
		
		/** Get index entry.
		 *
		 * Retreives a child node info record by name.
		 * 
		 * \note If a corresponding index entry is not found or the indexing 
		 * mode is INDEX_MODE_NONE or \c indexName is empty, this function 
		 * will return 0.
		 *
		 * \param indexName name to search for.
		 *
		 * \return node with the specified name, or 0 if no matching node is 
		 * found.
		 */
		virtual Ionflux::Template::Node* getIndexEntry(const std::string& 
		indexName) const;
		
		/** Remove index entry.
		 *
		 * Removes a child node info record from the name index.
		 *
		 * \param indexName name to search for.
		 */
		virtual void removeIndexEntry(const std::string& indexName);
		
		/** Get index entry.
		 *
		 * Retreives a child node info record by node ID.
		 * 
		 * \note If a corresponding index entry is not found or the indexing 
		 * mode is INDEX_MODE_NONE or \c indexID is negative, this function 
		 * will return 0.
		 *
		 * \param indexID ID to search for.
		 *
		 * \return node with the specified node ID, or 0 if no matching node is 
		 * found.
		 */
		virtual Ionflux::Template::Node* getIndexEntry(Ionflux::Template::NodeID 
		indexID) const;
		
		/** Remove index entry.
		 *
		 * Removes a child node info record from the ID index.
		 *
		 * \param indexID ID to search for.
		 */
		virtual void removeIndexEntry(Ionflux::Template::NodeID indexID);
		
		/** Remove index entries.
		 *
		 * Removes a child node from all Indexes.
		 *
		 * \param indexNode node to be removed.
		 */
		virtual void removeIndexEntries(Ionflux::Template::Node* indexNode);
		
	public:
		/// Node ID: not set.
		static const Ionflux::Template::NodeID ID_NOT_SET;
		/// Node data type: blob (binary large object, including byte strings).
		static const Ionflux::Template::NodeDataTypeID DATA_BLOB;
		/// Node data type: integer.
		static const Ionflux::Template::NodeDataTypeID DATA_INT;
		/// Node data type: double precision floating point number.
		static const Ionflux::Template::NodeDataTypeID DATA_DOUBLE;
		/// Child node UID assignment mode: Do not assign UID (default).
		static const Ionflux::Template::NodeUIDMode UID_MODE_NONE;
		/// Child node UID assignment mode: Assign ID unique to the parent node.
		static const Ionflux::Template::NodeUIDMode UID_MODE_NODE;
		/// Child node UID assignment mode: Assign ID unique to the tree.
		static const Ionflux::Template::NodeUIDMode UID_MODE_TREE;
		/// Traversal order: inorder.
		static const Ionflux::Template::NodeTraversalMode TRAVERSAL_INORDER;
		/// Traversal order: preorder.
		static const Ionflux::Template::NodeTraversalMode TRAVERSAL_PREORDER;
		/// Traversal order: postorder.
		static const Ionflux::Template::NodeTraversalMode TRAVERSAL_POSTORDER;
		/// Size of serialized node header in bytes.
		static const unsigned int HEADER_SIZE;
		/// Indexing mode: Do not use indexing (default).
		static const Ionflux::Template::NodeIndexMode INDEX_MODE_NONE;
		/// Indexing mode: Per node indexing.
		static const Ionflux::Template::NodeIndexMode INDEX_MODE_NODE;
		/// Indexing mode: Per tree indexing.
		static const Ionflux::Template::NodeIndexMode INDEX_MODE_TREE;
		/// Maximum size of ID index.
		static const unsigned int MAX_ID_INDEX_SIZE;
		/// Class information instance.
		static const NodeClassInfo nodeClassInfo;
		/// Class information.
		static const Ionflux::ObjectBase::IFClassInfo* CLASS_INFO;
		
		/** Constructor.
		 *
		 * Construct new Node object.
		 */
		Node();
		
		/** Constructor.
		 *
		 * Construct new Node object.
		 *
		 * \param other Other object.
		 */
		Node(const Ionflux::Template::Node& other);
		
		/** Constructor.
		 *
		 * Construct new Node object.
		 *
		 * \param initParent parent node.
		 */
		Node(Ionflux::Template::Node* initParent);
		
		/** Constructor.
		 *
		 * Construct new Node object.
		 *
		 * \param initParent parent node.
		 * \param initID node ID.
		 * \param initName node name.
		 * \param initDataType node data type.
		 */
		Node(Ionflux::Template::Node* initParent, Ionflux::Template::NodeID 
		initID, const std::string& initName = "", 
		Ionflux::Template::NodeDataTypeID initDataType = DATA_BLOB);
		
		/** Destructor.
		 *
		 * Destruct Node object.
		 */
		virtual ~Node();
		
		/** Add data entry.
		 *
		 * Adds data to this node.
		 * 
		 * \note This function tries to convert as best as possible if the 
		 * argument type does not match the node data type.
		 *
		 * \param newData Data to be added.
		 *
		 * \return The index of the data on success, -1 otherwise.
		 */
		virtual int addData(const std::string& newData);
		
		/** Add data entry.
		 *
		 * Adds data to this node.
		 * 
		 * \note This function tries to convert as best as possible if the 
		 * argument type does not match the node data type.
		 *
		 * \param newData Data to be added.
		 *
		 * \return The index of the data on success, -1 otherwise.
		 */
		virtual int addData(int newData);
		
		/** Add data entry.
		 *
		 * Adds data to this node.
		 * 
		 * \note This function tries to convert as best as possible if the 
		 * argument type does not match the node data type.
		 *
		 * \param newData Data to be added.
		 *
		 * \return The index of the data on success, -1 otherwise.
		 */
		virtual int addData(double newData);
		
		/** Set data entry.
		 *
		 * Sets value of data entry with specified index.
		 * 
		 * \note This function will always set the data entry to the specified
		 * bytes, regardless of the node data type.
		 *
		 * \param dataIndex Data index.
		 * \param newData New value for data entry.
		 *
		 * \return \c true on success, \c false otherwise.
		 */
		virtual bool setBlob(unsigned int dataIndex, const std::string& newData);
		
		/** Set data entry.
		 *
		 * Sets value of data entry with specified index.
		 * 
		 * \note This function tries to convert as best as possible if the 
		 * argument type does not match the node data type.
		 *
		 * \param dataIndex Data index.
		 * \param newData New value for data entry.
		 *
		 * \return \c true on success, \c false otherwise.
		 */
		virtual bool setData(unsigned int dataIndex, const std::string& newData);
		
		/** Set data entry.
		 *
		 * Sets value of data entry with specified index.
		 * 
		 * \note This function tries to convert as best as possible if the 
		 * argument type does not match the node data type.
		 *
		 * \param dataIndex Data index.
		 * \param newData New value for data entry.
		 *
		 * \return \c true on success, \c false otherwise.
		 */
		virtual bool setData(unsigned int dataIndex, int newData);
		
		/** Set data entry.
		 *
		 * Sets value of data entry with specified index.
		 * 
		 * \note This function tries to convert as best as possible if the 
		 * argument type does not match the node data type.
		 *
		 * \param dataIndex Data index.
		 * \param newData New value for data entry.
		 *
		 * \return \c true on success, \c false otherwise.
		 */
		virtual bool setData(unsigned int dataIndex, unsigned int newData);
		
		/** Set data entry.
		 *
		 * Sets value of data entry with specified index.
		 * 
		 * \note This function tries to convert as best as possible if the 
		 * argument type does not match the node data type.
		 *
		 * \param dataIndex Data index.
		 * \param newData New value for data entry.
		 *
		 * \return \c true on success, \c false otherwise.
		 */
		virtual bool setData(unsigned int dataIndex, double newData);
		
		/** Set data entry.
		 *
		 * Sets value of first data entry.
		 * 
		 * \note This function tries to convert as best as possible if the 
		 * argument type does not match the node data type.
		 *
		 * \param newData New value for data entry.
		 *
		 * \return \c true on success, \c false otherwise.
		 */
		virtual bool setData(const std::string& newData);
		
		/** Set data entry.
		 *
		 * Sets value of first data entry.
		 * 
		 * \note This function tries to convert as best as possible if the 
		 * argument type does not match the node data type.
		 *
		 * \param newData New value for data entry.
		 *
		 * \return \c true on success, \c false otherwise.
		 */
		virtual bool setData(int newData);
		
		/** Set data entry.
		 *
		 * Sets value of first data entry.
		 * 
		 * \note This function tries to convert as best as possible if the 
		 * argument type does not match the node data type.
		 *
		 * \param newData New value for data entry.
		 *
		 * \return \c true on success, \c false otherwise.
		 */
		virtual bool setData(unsigned int newData);
		
		/** Set data entry.
		 *
		 * Sets value of first data entry.
		 * 
		 * \note This function tries to convert as best as possible if the 
		 * argument type does not match the node data type.
		 *
		 * \param newData New value for data entry.
		 *
		 * \return \c true on success, \c false otherwise.
		 */
		virtual bool setData(double newData);
		
		/** Get data entry.
		 *
		 * Get data entry with specified index.
		 * 
		 * \note If used with an INT or DOUBLE node, this returns the string 
		 * representation of the number. If you want the exact binary 
		 * representation, use getBlob() instead.
		 *
		 * \param dataIndex Data index.
		 *
		 * \return Data entry, or an empty string if entry with specified index 
		 * does not exist.
		 */
		virtual std::string getData(unsigned int dataIndex) const;
		
		/** Get data entry.
		 *
		 * Get data entry with specified index.
		 * 
		 * \note If used with an INT or DOUBLE node, this returns the binary 
		 * representation of the number (in network byte order).
		 *
		 * \param dataIndex Data index.
		 *
		 * \return Data entry, or an empty string if entry with specified index 
		 * does not exist.
		 */
		virtual std::string getBlob(unsigned int dataIndex) const;
		
		/** Get data entry.
		 *
		 * Get data entry with specified index.
		 * 
		 * \note If used with a BLOB node, using this may lead to unexpected 
		 * behavior.
		 *
		 * \param dataIndex Data index.
		 *
		 * \return Data entry, or 0 if entry with specified index does not exist.
		 */
		virtual int getInt(unsigned int dataIndex) const;
		
		/** Get data entry.
		 *
		 * Get data entry with specified index.
		 * 
		 * \note If used with a BLOB node, using this may lead to unexpected 
		 * behavior.
		 *
		 * \param dataIndex Data index.
		 *
		 * \return Data entry, or 0 if entry with specified index does not exist.
		 */
		virtual double getDouble(unsigned int dataIndex) const;
		
		/** Remove data entry.
		 *
		 * Remove data entry with specified index.
		 *
		 * \param dataIndex Data index.
		 *
		 * \return \c true on success, \c false otherwise.
		 */
		virtual bool removeData(unsigned int dataIndex);
		
		/** Remove all data entries.
		 *
		 * Remove all data entries from this node. Pass \c true to remove all 
		 * data entries from child nodes recursively.
		 *
		 * \param recursive Whether to remove data entries of child nodes 
		 * recursively.
		 *
		 * \return \c true on success, \c false otherwise.
		 */
		virtual bool clearData(bool recursive);
		
		/** Add a child.
		 *
		 * Creates a new child node and adds it to this node. The node thus 
		 * created is managed by its parent node.
		 * 
		 * \note By default, the new node will have the same data type, the 
		 * same UID assignment mode and the same node auto-create mode as its 
		 * parent.
		 *
		 * \param childID ID of the new child node.
		 * \param childName Name of the new child node.
		 *
		 * \return Pointer to the new child node.
		 */
		virtual Ionflux::Template::Node* addChild(Ionflux::Template::NodeID 
		childID = ID_NOT_SET, const std::string& childName = "");
		
		/** Add a child.
		 *
		 * Adds a new child node to this node.
		 *
		 * \param newChild Child node to be added.
		 */
		virtual void addChild(Ionflux::Template::Node* newChild);
		
		/** Find child node.
		 *
		 * Return a child by numerical ID.
		 *
		 * \param searchID The ID of the child node to be returned.
		 * \param recursive Whether to search recursively through all child 
		 * nodes.
		 * \param level search level.
		 *
		 * \return Pointer to the first child node with the specified ID, or 0 if
		 * no child with the specified ID is found.
		 */
		virtual Ionflux::Template::Node* findChild(int searchID, bool recursive =
		false, unsigned int level = 0);
		
		/** Find child node.
		 *
		 * Return a child by name.
		 *
		 * \param searchName The name of the child node to be returned.
		 * \param recursive Whether to search recursively through all child 
		 * nodes.
		 * \param level search level.
		 *
		 * \return Pointer to the first child node with the specified name, or 0 
		 * if no child with the specified name is found.
		 */
		virtual Ionflux::Template::Node* findChild(const std::string& searchName,
		bool recursive = false, unsigned int level = 0);
		
		/** Find child node.
		 *
		 * Return a child by numerical ID.
		 *
		 * \param searchID The ID of the child node to be returned.
		 * \param recursive Whether to search recursively through all child 
		 * nodes.
		 *
		 * \return Pointer to the first child node with the specified ID, or 0 if
		 * no child with the specified ID is found.
		 */
		virtual Ionflux::Template::Node* findChild(int searchID, bool recursive =
		false) const;
		
		/** Find child node.
		 *
		 * Return a child by name.
		 *
		 * \param searchName The name of the child node to be returned.
		 * \param recursive Whether to search recursively through all child 
		 * nodes.
		 *
		 * \return Pointer to the first child node with the specified name, or 0 
		 * if no child with the specified name is found.
		 */
		virtual Ionflux::Template::Node* findChild(const std::string& searchName,
		bool recursive = false) const;
		
		/** Get child node.
		 *
		 * Get child node with specified index.
		 *
		 * \param childIndex Index of the child node to be returned.
		 *
		 * \return Pointer to the child node with the specified ID, or 0 if no 
		 * child with the specified ID is found.
		 */
		virtual Ionflux::Template::Node* getChild(unsigned int childIndex) const;
		
		/** Remove child node.
		 *
		 * Remove a child node from this node.
		 *
		 * \param childIndex Index of the child node to be removed.
		 *
		 * \return \c true if the specified node has been deleted successfully, 
		 * \c false otherwise.
		 */
		virtual bool removeChild(unsigned int childIndex);
		
		/** Remove child node.
		 *
		 * Remove a child node from this node. Pass \c true to recursively try
		 * to remove the specified node.
		 *
		 * \param targetNode Child node to be removed.
		 * \param recursive Whether to search recursively for the node.
		 *
		 * \return \c true if the specified node has been deleted successfully, 
		 * \c false otherwise.
		 */
		virtual bool removeChild(Ionflux::Template::Node* targetNode, bool 
		recursive = false);
		
		/** Remove all child nodes.
		 *
		 * Remove all child nodes from this node. Pass \c true to recursively 
		 * remove all child nodes.
		 *
		 * \param recursive Whether to remove child nodes recursively.
		 */
		virtual void removeAllChildren(bool recursive = false);
		
		/** Set child node.
		 *
		 * Set a child node to a specified node.
		 *
		 * \param childIndex Index of the child node to be set.
		 * \param newChild Node to be set as child node.
		 *
		 * \return \c true on success, \c false otherwise.
		 */
		virtual bool setChild(unsigned int childIndex, Ionflux::Template::Node* 
		newChild);
		
		/** Get child node index.
		 *
		 * Get the index of a child node.
		 *
		 * \param targetNode Child node.
		 *
		 * \return \c true on success, \c false otherwise.
		 */
		virtual int getChildIndex(Ionflux::Template::Node* targetNode);
		
		/** Print debug information.
		 *
		 * Prints debug information for child nodes belonging to a certain 
		 * tree depth level.
		 *
		 * \param targetLevel The tree depth level for which debugging 
		 * information should be printed.
		 * \param callingLevel The tree depth level of the calling node.
		 * \param parentID The child ID of the calling node.
		 * \param childID The child ID of this node.
		 *
		 * \return Number of nodes of the specified tree depth.
		 */
		virtual unsigned int printDebugInfo(int targetLevel, int callingLevel, 
		int parentID, int childID);
		
		/** Print debug information.
		 *
		 * Prints debug information for child nodes belonging to a certain 
		 * tree depth level, while this node is assumed to be the root node.
		 *
		 * \param targetLevel The tree depth level for which debugging 
		 * information should be printed.
		 *
		 * \return Number of nodes of the specified tree depth.
		 */
		virtual unsigned int printDebugInfo(int targetLevel);
		
		/** Get unique ID.
		 *
		 * Gets a unique ID (UID) for this node. The return value will be 
		 * unique to this node if \c false is passed and unique to the whole 
		 * tree if \c true is passed.
		 *
		 * \param treeUID Whether the UID should be unique to the whole tree.
		 *
		 * \return Unique ID.
		 */
		virtual int getUID(bool treeUID);
		
		/** Traverse sub-tree.
		 *
		 * Traverse the sub-tree starting at this node, in the specified 
		 * order.
		 *
		 * \param target Target to pass nodes to.
		 * \param order Order of traversal.
		 */
		virtual void traverse(Ionflux::Template::NodeDump* target, 
		Ionflux::Template::NodeTraversalMode order);
		
		/** Serialize sub-tree.
		 *
		 * Serialize the sub-tree starting at this node. Any data resulting 
		 * from the serialization will be appended to the target byte string.
		 * 
		 * \note See misc/node-serialization.txt for a description of the 
		 * serialization format.
		 * 
		 * \sa unpack()
		 *
		 * \param target Where to store the serialized sub-tree.
		 */
		virtual void serialize(std::string& target);
		
		/** Unpack sub-tree.
		 *
		 * Unpack the sub-tree starting at this node. This will delete all 
		 * data and remove all children currently in this node. Data 
		 * extraction begins at 'blockStart' and at most 'blockSize' bytes 
		 * will be used for unpacking nodes. If you pass 0 as the block size, 
		 * the block size will be set to the size of the serialized input.
		 * 
		 * \note See misc/node-serialization.txt for a description of the 
		 * serialization format.
		 * 
		 * \sa unpack()
		 *
		 * \param serialized Sub-Tree in serialized form.
		 * \param blockStart Position in the serialized data where the block to 
		 * be unpacked starts.
		 * \param blockSize Size of the block to be unpacked.
		 *
		 * \return \c true if the data is successfully unpacked, \c false 
		 * otherwise.
		 */
		virtual bool unpack(const std::string& serialized, unsigned int 
		blockStart, unsigned int blockSize);
		
		/** Convert node to native data type.
		 *
		 * Converts the node to the data type best suited for representing its
		 * data. This is accomplished by checking the first data entry and 
		 * converting all data entries to the new type.
		 * 
		 * \note This only applies to nodes of type Node::DATA_BLOB. For other
		 * data types, it is assumed that the data type is already optimal to 
		 * represent the data contained in the node.
		 */
		virtual void convertToNativeType();
		
		/** Clear name index.
		 *
		 * Clear the child node by name index.
		 */
		virtual void clearNameIndex();
		
		/** Clear ID index.
		 *
		 * Clear the child node by ID index.
		 */
		virtual void clearIDIndex();
		
		/** Clear all indexes.
		 *
		 * Clear all indexes.
		 */
		virtual void clearIndexes();
		
		/** Copy.
		 *
		 * Copy the node to a specified target node. Child nodes will be 
		 * copied recursively up to the maximum depth specified, or to the 
		 * maximum possible depth if no maximum depth is specified.
		 *
		 * \param target Target for the copy.
		 * \param maxDepth Maximum recursion depth.
		 * \param currentDepth Depth of current node.
		 *
		 * \return target node.
		 */
		virtual Ionflux::Template::Node* copy(Ionflux::Template::Node& target, 
		unsigned int maxDepth = 0, unsigned int currentDepth = 0) const;
		
		/** Find child node.
		 *
		 * Return a child by numerical ID.
		 * 
		 * \note This will always create non-existent nodes, even with 
		 * auto-create turned off. If you do not want this, you should not use
		 * subscripting, but findChild() instead. Also be aware that you 
		 * cannot use subscription operators to access data fields in your 
		 * code, while this is possible if you use subscripting in tree path 
		 * expressions which are parsed at run-time. Use getData() or parsed 
		 * tree paths if you want to access data entries in your source.
		 * 
		 * \sa findChild(), getData()
		 *
		 * \param searchID The ID of the child node to be returned.
		 *
		 * \return First child node with specified ID, or a newly created node 
		 * with that ID.
		 */
		virtual Ionflux::Template::Node& operator[](int searchID);
		
		/** Find child node.
		 *
		 * Return a child by name.
		 * 
		 * \note This will always create non-existent nodes, even with 
		 * auto-create turned off. If you do not want this, you should not use
		 * subscripting, but findChild() instead. Also be aware that you 
		 * cannot use subscription operators to access data fields in your 
		 * code, while this is possible if you use subscripting in tree path 
		 * expressions which are parsed at run-time. Use getData() or parsed 
		 * tree paths if you want to access data entries in your source.
		 * 
		 * \sa findChild(), getData()
		 *
		 * \param searchName The name of the child node to be returned.
		 *
		 * \return First child node with specified name, or a newly created node 
		 * with that ID.
		 */
		virtual Ionflux::Template::Node& operator[](const std::string& 
		searchName);
		
		/** Assign value to data entry.
		 *
		 * Assigns a value to the first data entry.
		 *
		 * \param newData New value for data entry.
		 *
		 * \return New value of the first data entry.
		 */
		virtual std::string operator=(const std::string& newData);
		
		/** Assign value to data entry.
		 *
		 * Assigns a value to the first data entry.
		 *
		 * \param newData New value for data entry.
		 *
		 * \return New value of the first data entry.
		 */
		virtual int operator=(int newData);
		
		/** Assign value to data entry.
		 *
		 * Assigns a value to the first data entry.
		 *
		 * \param newData New value for data entry.
		 *
		 * \return New value of the first data entry.
		 */
		virtual double operator=(double newData);
		
		/** Get data.
		 *
		 * Get data entry at index 0.
		 *
		 * \return Data entry at index 0.
		 */
		virtual std::string getData() const;
		
		/** Get data as blob.
		 *
		 * Get data entry at index 0.
		 *
		 * \return Data entry at index 0.
		 */
		virtual std::string getBlob() const;
		
		/** Get data as integer.
		 *
		 * Get data entry at index 0.
		 *
		 * \return Data entry at index 0.
		 */
		virtual int getInt() const;
		
		/** Get data as double.
		 *
		 * Get data entry at index 0.
		 *
		 * \return Data entry at index 0.
		 */
		virtual double getDouble() const;
		
		/** Get number of data entries.
		 *
		 * Get the number of data entries.
		 *
		 * \return Number of data entries.
		 */
		virtual unsigned int getNumData() const;
		
		/** Get number of children.
		 *
		 * Return the number of children of this node. Pass \c true to 
		 * retrieve the number of children recursively.
		 *
		 * \param recursive Whether to search recursively through all child 
		 * nodes.
		 *
		 * \return Number of child nodes.
		 */
		virtual unsigned int getNumChildren(bool recursive = false) const;
		
		/** Get tree path.
		 *
		 * Get the fully qualified tree path from the root node to this node.
		 * 
		 * \note If a node in the path has a name, that name will be used in 
		 * the tree path expression with the resolution operator. If a node 
		 * has no name, but an ID, the ID will be used in the tree path 
		 * expression using subscripting.
		 *
		 * \return Fully qualified tree path expression.
		 */
		virtual std::string getPath();
		
		/** Clear.
		 *
		 * Clear the node.
		 */
		virtual void clear();
		
		/** Merge nodes.
		 *
		 * Merges data entries and child nodes of the source node into the 
		 * node.
		 * 
		 * \note The name and ID of each source child node will be checked 
		 * against names and IDs child nodes of the source node. If \c replace
		 * is \c false or omitted, child nodes of the target node will not be 
		 * replaced by child nodes of the source node if names or IDs are 
		 * equal.
		 *
		 * \param sourceNode Node which should be merged.
		 * \param replace Whether child nodes in the target node should be 
		 * replaced by child nodes from the source node.
		 * \param maxDepth Maximum recursion depth.
		 * \param currentDepth Depth of current node.
		 *
		 * \return Merged node.
		 */
		virtual Ionflux::Template::Node& merge(Ionflux::Template::Node& 
		sourceNode, bool replace = false, unsigned int maxDepth = 0, unsigned int
		currentDepth = 0);
		
		/** Combine items.
		 *
		 * Combines each data entry of a first level child node (called a 
		 * class of items) with data entries from the other first level child 
		 * nodes (classes). Only nodes in the range \c from up to (and 
		 * including) \c to will be used for combination. The result is stored
		 * in \c target, with each first level node containing a unique 
		 * combination of items as its data entries.
		 *
		 * \param from Start of range.
		 * \param to End of range.
		 * \param target Target node.
		 *
		 * \return \c true on success, \c false otherwise.
		 */
		virtual bool combine(unsigned int from, unsigned int to, 
		Ionflux::Template::Node& target);
		
		/** Get configuration file representation.
		 *
		 * Create a representation of the node (and its children) suitable for
		 * insertion into a config file, using the extended (nested) syntax.
		 * 
		 * \note The configuration file representation is human-readable and 
		 * editable in any text editor. It may consist of multiple lines.
		 *
		 * \param indent Use this string to indent the lines of the string 
		 * representation.
		 * \param level The indentation level.
		 *
		 * \return Configuration file representation of the node.
		 */
		virtual std::string toConfig(const std::string& indent = "  ", unsigned 
		int level = 0);
		
		/** Assignment operator.
		 *
		 * Assign an object.
		 *
		 * \param other Other object.
		 *
		 * \return The object itself.
		 */
		virtual Ionflux::Template::Node& operator=(const Ionflux::Template::Node&
		other);
		
		/** Copy.
		 *
		 * Create a copy of the object.
		 *
		 * \return Newly allocated copy of the object.
		 */
		virtual Ionflux::Template::Node* copy() const;
		
		/** Upcast.
		 *
		 * Cast an IFObject to the most specific type.
		 *
		 * \param other Other object.
		 *
		 * \return The more specific object, or 0 if the cast failed.
		 */
		static Ionflux::Template::Node* upcast(Ionflux::ObjectBase::IFObject* 
		other);
		
		/** Create instance.
		 *
		 * Create a new instance of the class. If the optional parent object 
		 * is specified, a local reference for the new object will be added 
		 * to the parent object.
		 *
		 * \param parentObject Parent object.
		 *
		 * \return Pointer to the new instance.
		 */
		static Ionflux::Template::Node* create(Ionflux::ObjectBase::IFObject* 
		parentObject = 0);
        
		/** Create instance.
		 *
		 * Create a new Node object.
		 *
		 * \param initParent parent node.
		 * \param parentObject Parent object.
		 */
		static Ionflux::Template::Node* create(Ionflux::Template::Node* 
		initParent, Ionflux::ObjectBase::IFObject* parentObject = 0);
        
		/** Create instance.
		 *
		 * Create a new Node object.
		 *
		 * \param initParent parent node.
		 * \param initID node ID.
		 * \param initName node name.
		 * \param initDataType node data type.
		 * \param parentObject Parent object.
		 */
		static Ionflux::Template::Node* create(Ionflux::Template::Node* 
		initParent, Ionflux::Template::NodeID initID, const std::string& initName
		= "", Ionflux::Template::NodeDataTypeID initDataType = DATA_BLOB, 
		Ionflux::ObjectBase::IFObject* parentObject = 0);
		
		/** Get allocated size in memory.
		 *
		 * Get the allocated size in memory for the object.
		 *
		 * \return The more specific object, or 0 if the cast failed.
		 */
		virtual unsigned int getMemSize() const;
		
		/** Get numerical ID.
		 *
		 * \return Current value of numerical ID.
		 */
		virtual Ionflux::Template::NodeID getNodeID() const;
		
		/** Set numerical ID.
		 *
		 * Set new value of numerical ID.
		 *
		 * \param newNodeID New value of numerical ID.
		 */
		virtual void setNodeID(Ionflux::Template::NodeID newNodeID);
		
		/** Get name of the node.
		 *
		 * \return Current value of name of the node.
		 */
		virtual std::string getNodeName() const;
		
		/** Set name of the node.
		 *
		 * Set new value of name of the node.
		 *
		 * \param newNodeName New value of name of the node.
		 */
		virtual void setNodeName(const std::string& newNodeName);
		
		/** Get data type.
		 *
		 * \return Current value of data type.
		 */
		virtual Ionflux::Template::NodeDataTypeID getDataType() const;
		
		/** Set data type.
		 *
		 * Set new value of data type.
		 *
		 * \param newDataType New value of data type.
		 */
		virtual void setDataType(Ionflux::Template::NodeDataTypeID newDataType);
		
		/** Get parent node.
		 *
		 * \return Current value of parent node.
		 */
		virtual Ionflux::Template::Node* getParent() const;
		
		/** Set parent node.
		 *
		 * Set new value of parent node.
		 *
		 * \param newParent New value of parent node.
		 */
		virtual void setParent(Ionflux::Template::Node* newParent);
		
		/** Get maximum UID that has been assigned by this node.
		 *
		 * \return Current value of maximum UID that has been assigned by this 
		 * node.
		 */
		virtual Ionflux::Template::NodeID getMaxUID() const;
		
		/** Set maximum UID that has been assigned by this node.
		 *
		 * Set new value of maximum UID that has been assigned by this node.
		 *
		 * \param newMaxUID New value of maximum UID that has been assigned by 
		 * this node.
		 */
		virtual void setMaxUID(Ionflux::Template::NodeID newMaxUID);
		
		/** Get child node UID assignment mode.
		 *
		 * \return Current value of child node UID assignment mode.
		 */
		virtual Ionflux::Template::NodeUIDMode getUidMode() const;
		
		/** Set child node UID assignment mode.
		 *
		 * Set new value of child node UID assignment mode.
		 *
		 * \param newUidMode New value of child node UID assignment mode.
		 */
		virtual void setUidMode(Ionflux::Template::NodeUIDMode newUidMode);
		
		/** Get create requested child nodes and data entries on the fly.
		 *
		 * \return Current value of create requested child nodes and data entries
		 * on the fly.
		 */
		virtual bool getAutoCreate() const;
		
		/** Set create requested child nodes and data entries on the fly.
		 *
		 * Set new value of create requested child nodes and data entries on the fly.
		 *
		 * \param newAutoCreate New value of create requested child nodes and 
		 * data entries on the fly.
		 */
		virtual void setAutoCreate(bool newAutoCreate);
		
		/** Get child node indexing mode.
		 *
		 * \return Current value of child node indexing mode.
		 */
		virtual Ionflux::Template::NodeIndexMode getIndexMode() const;
		
		/** Set child node indexing mode.
		 *
		 * Set new value of child node indexing mode.
		 *
		 * \param newIndexMode New value of child node indexing mode.
		 */
		virtual void setIndexMode(Ionflux::Template::NodeIndexMode newIndexMode);
};

}

}

/** \file Node.hpp
 * \brief Tree node (header).
 */
#endif
