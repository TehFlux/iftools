#ifndef IONFLUX_TOOLS_NODE
#define IONFLUX_TOOLS_NODE
/* ==========================================================================
 * Ionflux Tools
 * Copyright (c) 2004 Joern P. Meier
 * mail@ionflux.org
 * --------------------------------------------------------------------------
 * Node.hpp                    Tree data node.
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
#include <map>
#include "ionflux/tools.hpp"
#include "ionflux/Reporter.hpp"
#include "ionflux/NodeDump.hpp"

namespace Ionflux
{

namespace Tools
{

class Node;
class NodeDump;
class Reporter;

/** \addtogroup datahand Data handling
 *
 * Tools for handling and processing large amounts of arbitrary data.
 *
 * @{
 */

/** Node information.
 *
 * Holds information about a child node.
 *
 * \deprecated Functionality of NodeInfo is now provided directly by Node. 
 * This struct is provided for backward compatibility only and may be removed 
 * in future versions.
 */
struct NodeInfo
{
	/// Pointer to a node.
	Node *node;
	/// Allocated memory management flag.
	bool manage;
	
	// Constructor.
	NodeInfo() : node(0), manage(false) { }
};

/** Tree node.
 *
 * A single data node of a tree. Tree nodes can be used to store data of a 
 * hierarchical, non-cyclical structure, where each child node has exactly 
 * one parent node and loops do not exist. Each node also has a data vector 
 * where a large amount of values of identical type may be stored without the 
 * need of additional nodes. The type of a node can be one of BLOB, INT or 
 * DOUBLE, and all data will be converted as best as possible to fit the 
 * specified node data type. The node object also provides transparent 
 * serialization and unpacking of sub-trees from a data buffer and node 
 * resolution from a fully qualified tree path (see 
 * misc/node-serialization.txt and misc/path-resolution.txt for additional 
 * information). Dynamic auto-creation of child nodes is also supported.
 */
class Node
{
	protected:
		/// Console output/logging.
		Ionflux::Tools::Reporter *log;
		/// Numerical ID of this node.
		int nodeID;
		/// Name of this node.
		std::string nodeName;
		/// Vector of pointers to children.
		std::vector<NodeInfo> children;
		/// Data vector.
		std::vector<std::string> nodeData;
		/// Node data type.
		int dataType;
		/// Parent node.
		Node *parent;
		/// Maximum UID assigned by this node.
		int maxUID;
		/// Child node UID assignment mode.
		int uidMode;
		/** Auto-creation mode.
		 *
		 * Whether to create requested child nodes and data entries on the 
		 * fly if they do not already exist.
		 */
		bool autoCreate;
		/// Indexing mode.
		int indexMode;
		/// Index map.
		std::map<std::string, Node*> nameIndex;
		/// Index vector (TODO: Maybe reimplement this as a hash map).
		std::vector<Node*> idIndex;
		/** Memory management mode.
		 *
		 * If set to \c true, this indicates that memory allocated for this 
		 * node is managed by its parent node.
		 */
		bool managed;
		/// Child node reference counter.
		std::map<Node*, unsigned int> childNodeRef;
		
		/** Validate child node index.
		 *
		 * Returns \c true if the child node index references a valid child 
		 * node.
		 *
		 * \note If the child node does not exist, but auto-create mode is set 
		 * to \c true, the child node will be created.
		 *
		 * \param childIndex The child node index to be validated.
		 *
		 * \return \c true if a child node with specified index exists, \c false 
		 * otherwise.
		 */
		virtual bool validateChildIndex(unsigned int childIndex);
		
		/** Validate data index.
		 *
		 * Returns \c true if a data index references a valid data entry.
		 *
		 * \note If the data entry does not exist, but auto-create mode is set 
		 * to \c true, the data entry will be created.
		 *
		 * \param dataIndex The data index to be validated.
		 *
		 * \return \c true if a data entry with specified index exists, \c false 
		 * otherwise.
		 */
		virtual bool validateDataIndex(unsigned int dataIndex);
		
		/** Increase child node reference count.
		 *
		 * Increases the reference count for a child node by one.
		 *
		 * \param childNode Pointer to a child node.
		 *
		 * \return Reference count for \c childNode (after increment).
		 */
		virtual unsigned int refChild(Node *childNode);
		
		/** Decrease child node reference count.
		 *
		 * Decreases the reference count for a child node by one.
		 *
		 * \note If the reference count of a child node drops to zero, it 
		 * will be removed from all indexes and, if managed by its parent 
		 * node, deleted.
		 *
		 * \param childNode Pointer to a child node.
		 *
		 * \return Reference count for \c childNode (after decrement).
		 */
		virtual unsigned int unrefChild(Node *childNode);
		
		/** Get child node reference count.
		 *
		 * Gets the reference count for a child node.
		 *
		 * \param childNode Pointer to a child node.
		 *
		 * \return Reference count for \c childNode.
		 */
		virtual unsigned int getRefCount(Node *childNode);
		
		/** Add index entry.
		 *
		 * Adds a child node to the name or ID index (or both).
		 *
		 * \note A child node will be added to an index only if either its 
		 * name is not the empty string or its ID is not NODE_ID_NOT_SET and 
		 * not negative. If both keys (name or ID) are set to suitable values, 
		 * the node will be added to both indexes. If the indexing mode is 
		 * INDEX_MODE_NONE or \c indexNode is null, this function will do 
		 * nothing.
		 *
		 * \param indexNode Node for which an index entry should be added.
		 */
		virtual void addIndexEntry(Node *indexNode);
		
		/** Get index entry.
		 *
		 * Retreives a child node info record by name.
		 *
		 * \note If a corresponding index entry is not found or the 
		 * indexing mode is INDEX_MODE_NONE or \c indexID is negative, this 
		 * function will return null.
		 *
		 * \param indexName Name to search for.
		 *
		 * \return Pointer to a node with the specified name, or null if no 
		 * suitable node is found.
		 */
		virtual Node *getIndexEntry(const std::string &indexName);
		
		/** Remove index entry.
		 *
		 * Removes a child node info record from the name index.
		 *
		 * \param indexName Name to search for.
		 */
		virtual void removeIndexEntry(const std::string &indexName);
		
		/** Get index entry.
		 *
		 * Retreives a child node info record by ID.
		 *
		 * \note If a corresponding node info entry is not found or the 
		 * indexing mode is INDEX_MODE_NONE or \c indexID is negative, this 
		 * function will return null.
		 *
		 * \param indexID ID to search for.
		 *
		 * \return Pointer to a node with the specified name, or null if no 
		 * suitable node is found.
		 */
		virtual Node *getIndexEntry(int indexID);
		
		/** Remove index entry.
		 *
		 * Removes a child node info record from the ID index.
		 *
		 * \param indexID ID to search for.
		 */
		virtual void removeIndexEntry(int indexID);
		
		/** Remove index entries.
		 *
		 * Removes a child node from all Indexes.
		 */
		virtual void removeIndexEntries(Node *indexNode);
		
	public:
		/// Node ID: Not set.
		static const int NODE_ID_NOT_SET;
		/// Node data type: Blob (Binary large object, including byte strings).
		static const int NODE_DATA_BLOB;
		/// Node data type: Integer.
		static const int NODE_DATA_INT;
		/// Node data type: Double.
		static const int NODE_DATA_DOUBLE;
		/// Child node UID assignment mode: Do not assign UID (default).
		static const int UID_MODE_NONE;
		/// Child node UID assignment mode: Assign ID unique to this node.
		static const int UID_MODE_NODE;
		/// Child node UID assignment mode: Assign ID unique to the tree.
		static const int UID_MODE_TREE;
		/// Traversal order: Inorder.
		static const int TRAVERSAL_INORDER;
		/// Traversal order: Preorder.
		static const int TRAVERSAL_PREORDER;
		/// Traversal order: Postorder.
		static const int TRAVERSAL_POSTORDER;
		/// Size of serialized node header in bytes.
		static const unsigned int NODE_HEADER_SIZE;
		/// Indexing mode: Do not use indexing (default).
		static const int INDEX_MODE_NONE;
		/// Indexing mode: Per node indexing.
		static const int INDEX_MODE_NODE;
		/// Indexing mode: Per tree indexing.
		static const int INDEX_MODE_TREE;
		/// Maximum size of ID index.
		static const unsigned int MAX_ID_INDEX_SIZE;
		
		/** Constructor.
		 *
		 * Construct new Node object.
		 */
		Node();
		
		/** Constructor.
		 *
		 * Construct new Node object.
		 *
		 * \param sourceNode Node which to copy.
		 */
		Node(Node &sourceNode);
		
		/** Constructor.
		 *
		 * Construct new Node object.
		 *
		 * \param initParent Pointer to parent node of this node.
		 */
		Node(Node *initParent);
		
		/** Constructor.
		 *
		 * Construct new Node object.
		 *
		 * \param initParent Pointer to parent node of this node.
		 * \param initID Numerical ID of this node.
		 */
		Node(Node *initParent, int initID);
		
		/** Constructor.
		 *
		 * Construct new Node object.
		 *
		 * \param initParent Pointer to parent node of this node.
		 * \param initID Numerical ID of this node.
		 * \param initName Name of this node.
		 */
		Node(Node *initParent, int initID, const std::string &initName);
		
		/** Constructor.
		 *
		 * Construct new Node object.
		 *
		 * \param initParent Pointer to parent node of this node.
		 * \param initID Numerical ID of this node.
		 * \param initName Name of this node.
		 * \param initDataType Data type of this node.
		 */
		Node(Node *initParent, int initID, const std::string &initName, 
			int initDataType);
		
		/** Constructor.
		 *
		 * Construct new Node object.
		 *
		 * \param initParent Pointer to parent node of this node.
		 * \param initID Numerical ID of this node.
		 * \param initName Name of this node.
		 * \param initDataType Data type of this node.
		 * \param initManaged Whether memory allocated for this node should be 
		 * managed by its parent node.
		 */
		Node(Node *initParent, int initID, const std::string &initName, 
			int initDataType, bool initManaged);
		
		/** Destructor.
		 *
		 * Destruct Node object.
		 */
		virtual ~Node();
		
		/** Set ID.
		 *
		 * Sets the numerical ID of this node.
		 *
		 * \param newID Numerical ID of this node.
		 */
		virtual void setID(int newID);
		
		/** Set Name.
		 *
		 * Sets the name of this node.
		 *
		 * \param newName Name of this node.
		 */
		virtual void setName(const std::string &newName);
		
		/** Set parent Node.
		 *
		 * Sets the parent node of this node.
		 *
		 * \param newParent Pointer to parent node.
		 */
		virtual void setParent(Node *newParent);
		
		/** Set data type.
		 *
		 * Sets the data type of this node. Valid values are set by one of the 
		 * Node::NODE_DATA_* constants.
		 *
		 * \param newDataType Data type to be used for this node.
		 */
		virtual void setDataType(int newDataType);
		
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
		virtual int addData(const std::string &newData);
		
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
		 * \note This function will always set the data entry to the 
		 * specified bytes, regardless of the node data type.
		 *
		 * \param dataIndex Data index.
		 * \param newData New value for data entry.
		 *
		 * \return \c true on success, \c false otherwise.
		 */
		virtual bool setBlob(unsigned int dataIndex, 
			const std::string &newData);
		
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
		virtual bool setData(unsigned int dataIndex, 
			const std::string &newData);
		
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
		 * Sets value of first data entry with specified index.
		 *
		 * \note This function tries to convert as best as possible if the 
		 * argument type does not match the node data type.
		 *
		 * \param newData New value for data entry.
		 *
		 * \return \c true on success, \c false otherwise.
		 */
		virtual bool setData(const std::string &newData);
		
		/** Set data entry.
		 *
		 * Sets value of first data entry with specified index.
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
		 * Sets value of first data entry with specified index.
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
		 * Sets value of first data entry with specified index.
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
		 * \return Data entry, or an empty string if entry with specified 
		 * index does not exist.
		 */
		virtual std::string getData(unsigned int dataIndex);
		
		/** Get data entry.
		 *
		 * Get data entry with specified index.
		 *
		 * \note If used with an INT or DOUBLE node, this returns the binary 
		 * representation of the number (in network byte order).
		 *
		 * \param dataIndex Data index.
		 *
		 * \return Data entry, or an empty string if entry with specified 
		 * index does not exist.
		 */
		virtual std::string getBlob(unsigned int dataIndex);
		
		/** Get data entry.
		 *
		 * Get data entry with specified index.
		 *
		 * \note If used with a BLOB node, using this may lead to unexpected 
		 * behavior.
		 *
		 * \param dataIndex Data index.
		 *
		 * \return Data entry, or 0 if entry with specified index does not 
		 * exist.
		 */
		virtual int getInt(unsigned int dataIndex);
		
		/** Get data entry.
		 *
		 * Get data entry with specified index.
		 *
		 * \note If used with a BLOB node, using this may lead to unexpected 
		 * behavior.
		 *
		 * \param dataIndex Data index.
		 *
		 * \return Data entry, or 0 if entry with specified index does not 
		 * exist.
		 */
		virtual double getDouble(unsigned int dataIndex);
		
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
		 */
		virtual void clearData(bool recursive);
		
		/** Add a child.
		 *
		 * Creates a new child node and adds it to this node. The node thus 
		 * created is managed by its parent node.
		 *
		 * \param childID ID of the new child node.
		 * \param childName Name of the new child node.
		 *
		 * \note By default, the new node will have the same data type, the 
		 * same UID assignment mode and the same node auto-create mode as its 
		 * parent.
		 *
		 * \return Pointer to the new child node.
		 */
		virtual Node *addChild(int childID = NODE_ID_NOT_SET, 
			const std::string& childName = "");
		
		/** Add a child.
		 *
		 * Adds a new child node to this node.
		 *
		 * \param newChild Pointer to child node.
		 * \param newManage Whether memory allocated for the child node should
		 * be managed by this node.
		 */
		virtual void addChild(Node *newChild, bool newManage);
		
		/** Find child node.
		 *
		 * Return a child by numerical ID.
		 *
		 * \param searchID The ID of the child node to be returned.
		 * \param recursive Whether to search recursively through all child 
		 * nodes.
		 *
		 * \return Pointer of the first child node with the specified ID, or 
		 * 0 if no child with the specified ID is found.
		 */
		virtual Node *findChild(int searchID, bool recursive = false);
		
		/** Find child node.
		 *
		 * Return a child by name.
		 *
		 * \param searchName The name of the child node to be returned.
		 * \param recursive Whether to search recursively through all child 
		 * nodes.
		 *
		 * \return Pointer of the first child node with the specified name, or 
		 * 0 if no child with the specified name is found.
		 */
		virtual Node *findChild(const std::string &searchName, 
			bool recursive = false);
		
		/** Get child node.
		 *
		 * Get child node with specified index.
		 *
		 * \param childIndex Index of the child node to be returned.
		 *
		 * \return Pointer to the child node with the specified index, or 0 
		 * if no child node with the specified index exists.
		 */
		virtual Node *getChild(unsigned int childIndex);
		
		/** Get number of children.
		 *
		 * Return the number of children of this node. Pass \c true to 
		 * retrieve the number of children recursively.
		 *
		 * \note If called for a root node, this may be used to retrieve the 
		 * number of nodes in a tree.
		 *
		 * \param recursive Whether to get the number of children recursively.
		 *
		 * \return Number of child nodes.
		 */
		virtual unsigned int getNumChildren(bool recursive);
		
		/** Remove child node.
		 *
		 * Remove a child node from this node.
		 *
		 * \note If the child node to be removed is managed by this node and 
		 * its (parent node internal) reference count drops to zero, it will 
		 * also be deleted.
		 *
		 * \param childIndex Index of the child node to be deleted.
		 *
		 * \return  \c true if the specified node has been deleted 
		 * successfully, \c false otherwise.
		 */
		virtual bool removeChild(unsigned int childIndex);
		
		/** Remove child node.
		 *
		 * Remove a child node from this node. Pass \c true to recursively try
		 * to remove the specified node.
		 *
		 * \note If the child node to be removed is managed by this node and 
		 * its (parent node internal) reference count drops to zero, it will 
		 * also be deleted.
		 *
		 * \param targetNode Pointer to the node to be deleted.
		 * \param recursive Whether to remove the node recursively.
		 *
		 * \return  \c true if the specified node has been deleted 
		 * successfully, \c false otherwise.
		 */
		virtual bool removeChild(Node *targetNode, bool recursive);
		
		/** Remove all child nodes.
		 *
		 * Remove all child nodes from this node. Pass \c true to recursively 
		 * remove all child nodes.
		 *
		 * \note If a child node to be removed is managed by its parent node, 
		 * it will also be deleted. Also, child nodes of managed nodes will 
		 * always be removed recursively, whether you pass \c true or not. This 
		 * is necessary to ensure that all managed nodes are deleted if their 
		 * parent node is deleted.
		 *
		 * \param recursive Whether to remove child nodes recursively.
		 */
		virtual void removeAllChildren(bool recursive);
		
		/** Set child node.
		 *
		 * Set a child node to a specified node.
		 *
		 * \param childIndex Index of the child node to be set.
		 * \param newChild Node to be set as child node.
		 * \param newManage Whether memory allocated for the child node should
		 * be managed by this node.
		 *
		 * \return \c true on success, \c false otherwise.
		 */
		virtual bool setChild(unsigned int childIndex, Node *newChild, 
			bool newManage);
		
		/** Remove managed children.
		 *
		 * Removes all managed child nodes that are descendants of this node 
		 * recursively.
		 */
		virtual void removeManagedChildren();
		
		/** Get child node index.
		 *
		 * Get the index of a child node.
		 *
		 * \param targetNode Child node.
		 *
		 * \return Index of the specified child node, or -1 if the specified 
		 * node is not a child node of this node.
		 */
		virtual int getChildIndex(Node *targetNode);
		
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
		
		/** Set child node UID assignment mode.
		 *
		 * Set the child node UID assignment mode. Use this to automatically 
		 * assign IDs to child nodes created by addChild(). Valid values are 
		 * set by one of the Node::UID_MODE_* constants.
		 *
		 * \param newUIDMode Child node UID assignment mode.
		 */
		virtual void setUIDMode(int newUIDMode);
		
		/** Set auto-create mode.
		 *
		 * If set to \c true, any operation that tries to access a non-existent 
		 * child node or data entry will automatically create that child node 
		 * or data entry. If set to \c false, such operations will (usually) 
		 * return 0.
		 *
		 * \param newAutoCreate Auto-create mode.
		 */
		virtual void setAutoCreate(bool newAutoCreate);
		
		/** Set child node indexing mode.
		 *
		 * Set the child node indexing mode. Use this to automatically create 
		 * and maintain an index of child nodes, which may result in faster 
		 * access times but will consume more memory. Valid values are 
		 * set by one of the Node::INDEX_MODE_* constants.
		 *
		 * \param newIndexMode Child node indexing mode.
		 */
		virtual void setIndexMode(int newIndexMode);
		
		/** Traverse sub-tree.
		 *
		 * Traverse the sub-tree starting at this node, in the specified order.
		 *
		 * \param target Target to pass nodes to.
		 * \param order Order of traversal.
		 */
		virtual void traverse(NodeDump *target, int order);
		
		/** Serialize sub-tree.
		 *
		 * Serialize the sub-tree starting at this node. Any data resulting 
		 * from the serialization will be appended to the target byte string.
		 *
		 * \note See misc/node-serialization.txt for a description of the 
		 * serialization format.
		 *
		 * \param target Where to store the serialized sub-tree.
		 *
		 * \sa unpack()
		 */
		virtual void serialize(std::string &target);
		
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
		 * \param serialized Sub-Tree in serialized form.
		 * \param blockStart Position in the serialized data where the block 
		 * to be unpacked starts.
		 * \param blockSize Size of the block to be unpacked.
		 *
		 * \sa serialize()
		 *
		 * \return \c true if the data is successfully unpacked, \c false 
		 * otherwise.
		 */
		virtual bool unpack(const std::string &serialized, 
			unsigned int blockStart, unsigned int blockSize);
		
		/** Convert node to native data type.
		 *
		 * Converts the node to the data type best suited for representing 
		 * its data. This is accomplished by checking the first data entry 
		 * and converting all data entries to the new type.
		 *
		 * \note This only applies to nodes of type Node::NODE_DATA_BLOB. 
		 * For other data types, it is assumed that the data type is already 
		 * optimal to represent the data contained in the node.
		 */
		virtual void convertToNativeType();
		
		/// Clear name index.
		virtual void clearNameIndex();
		
		/// Clear ID index.
		virtual void clearIDIndex();
		
		/// Clear all indexes.
		virtual void clearIndexes();
		
		/** Copy node.
		 *
		 * Copy the node to a specified target node. Child nodes will be 
		 * copied recursively up to the maximum depth specified, or 
		 * to the maximum possible depth if no maximum depth is specified.
		 *
		 * \param target Target for the copy.
		 * \param maxDepth Maximum recursion depth.
		 * \param currentDepth Depth of current node.
		 */
		virtual void copy(Ionflux::Tools::Node& target, 
			unsigned int maxDepth = 0, unsigned int currentDepth = 0);
		
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
		 * \param searchID The ID of the child node to be returned.
		 *
		 * \return First child node with specified ID, or a newly created node 
		 * with that ID.
		 *
		 * \sa findChild(), getData()
		 */
		virtual Node &operator[](int searchID);
		
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
		 * \param searchName The name of the child node to be returned.
		 *
		 * \return First child node with specified name, or a newly created 
		 * node with that name.
		 *
		 * \sa findChild(), getData()
		 */
		virtual Node &operator[](const std::string &searchName);
		
		/** Assign value to data entry.
		 *
		 * Assigns a value to the first data entry.
		 *
		 * \param newData New value for data entry.
		 */
		virtual std::string operator=(const std::string& newData);
		
		/** Assign value to data entry.
		 *
		 * Assigns a value to the first data entry.
		 *
		 * \param newData New value for data entry.
		 */
		virtual int operator=(int newData);
		
		/** Assign value to data entry.
		 *
		 * Assigns a value to the first data entry.
		 *
		 * \param newData New value for data entry.
		 */
		virtual double operator=(double newData);
		
		/** Copy assignment.
		 *
		 * Copies a node (and all its child nodes). The target node will 
		 * retain its name, ID and parent, but all previous data and child 
		 * nodes will be replaced by the data entries and child nodes of the 
		 * node which is copied.
		 *
		 * \param sourceNode Node which should be copied.
		 */
		virtual Node &operator=(Node &sourceNode);
		
		/** Get auto-create mode.
		 *
		 * \return \c true if auto-create mode is enabled, \c false otherwise.
		 */
		virtual bool getAutoCreate();
		 
		/** Get child node UID assignment mode.
		 *
		 * \return UID assignment mode.
		 */
		virtual int getUIDMode();
		
		/** Get child node indexing mode.
		 *
		 * \return Indexing mode.
		 */
		virtual int getIndexMode();
		
		/** Get node ID.
		 *
		 * \return Node ID.
		 */
		virtual int getID();
		
		/** Get node name.
		 *
		 * \return Node name.
		 */
		virtual std::string getName();
		
		/** Get data type.
		 *
		 * \return Node data type.
		 */
		virtual int getDataType();
		
		/** Get data.
		 *
		 * \return Data entry (at index 0).
		 */
		virtual std::string getData();
		
		/** Get data as blob.
		 *
		 * \return Data entry (at index 0).
		 */
		virtual std::string getBlob();
		
		/** Get data as integer.
		 *
		 * \return Data entry (at index 0).
		 */
		virtual int getInt();
		
		/** Get data as double.
		 *
		 * \return Data entry (at index 0).
		 */
		virtual double getDouble();
		
		/** Get number of data entries.
		 *
		 * \return Number of data entries.
		 */
		virtual unsigned int getNumData();
		
		/** Get number of children.
		 *
		 * \return Number of child nodes.
		 */
		virtual unsigned int getNumChildren();
		
		/** Get parent node.
		 *
		 * \return Pointer to parent node, or 0 if this is a root node.
		 */
		virtual Node *getParent();
		
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
		
		/// Clear the node.
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
		 */
		virtual Node& merge(Node &sourceNode, bool replace = false, 
			unsigned int maxDepth = 0, unsigned int currentDepth = 0);
		
		/** Combine items.
		 *
		 * Combines each data entry of a first level child node (called a 
		 * class of items) with data entries from the other first level child
		 * nodes (classes). Only nodes in the range \c from up to (and 
		 * including) \c to will be used for combination. The result is 
		 * stored in \c target, with each first level node containing a 
		 * unique combination of items as its data entries.
		 *
		 * \return \c true on success, \c false otherwise.
		 */
		bool combine(unsigned int from, unsigned int to, Node &target);
		
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
		std::string toConfig(const std::string& indent = "", 
			unsigned int level = 0);
		
		/** Set memory management flag.
		 *
		 * This controls whether memory allocated for this node should be 
		 * managed by its parent node.
		 *
		 * \note This is used internally by the implementation and should not, 
		 * under normal circumstances, be explicitly called from the 
		 * application level.
		 *
		 * \warning Do not call this function explicitly! If you need control 
		 * over the memory management mode, use addChild() with appropriate 
		 * arguments instead. Calling this function explicitly may result in 
		 * unexpected behavior, or worse.
		 *
		 * \sa addChild()
		 */
		void setManaged(bool newManaged);
		
		/** Get memory management flag.
		 *
		 * Get the current memory management mode of this node.
		 *
		 * \return \c true if memory allocated for this node is managed by its 
		 * parent node, \c false otherwise.
		 */
		bool isManaged();
		
		/** Get Console output/logging facility.
		 *
		 * \return The console output/logging facility used by this object.
		 */
		virtual Reporter &getLog();
};

/// @}

}

}

/** \file Node.hpp
 * \brief Tree data node.
 */
#endif
