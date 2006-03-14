/* ==========================================================================
 * Ionflux Tools
 * Copyright (c) 2004 Joern P. Meier
 * mail@ionflux.org
 * --------------------------------------------------------------------------
 * Node.cpp                    Tree data node.
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

#include "ionflux/Node.hpp"

using namespace std;

namespace Ionflux
{

namespace Tools
{

const int Node::NODE_ID_NOT_SET = -1;

const int Node::NODE_DATA_BLOB = 0;
const int Node::NODE_DATA_INT = 1;
const int Node::NODE_DATA_DOUBLE = 2;

const int Node::UID_MODE_NONE = 0;
const int Node::UID_MODE_NODE = 1;
const int Node::UID_MODE_TREE = 2;

const int Node::TRAVERSAL_INORDER = 0;
const int Node::TRAVERSAL_PREORDER = 1;
const int Node::TRAVERSAL_POSTORDER = 2;

const unsigned int Node::NODE_HEADER_SIZE = 53;

const int Node::INDEX_MODE_NONE = 0;
const int Node::INDEX_MODE_NODE = 1;
const int Node::INDEX_MODE_TREE = 2;

const unsigned int Node::MAX_ID_INDEX_SIZE = 268435456L;

Node::Node()
: nodeID(NODE_ID_NOT_SET), nodeName(""), dataType(NODE_DATA_BLOB), parent(0),
  maxUID(-1), uidMode(UID_MODE_NONE), autoCreate(false), 
  indexMode(INDEX_MODE_NONE), managed(false)
{
	log = new Reporter();
}

Node::Node(Node &sourceNode)
: nodeID(NODE_ID_NOT_SET), nodeName(""), dataType(NODE_DATA_BLOB), parent(0),
  maxUID(-1), uidMode(UID_MODE_NONE), autoCreate(false), 
  indexMode(INDEX_MODE_NONE), managed(false)
{
	log = new Reporter();
	*this = sourceNode;
	setName(sourceNode.getName());
	setID(sourceNode.getID());
}

Node::Node(Node *initParent)
: nodeID(NODE_ID_NOT_SET), nodeName(""), dataType(NODE_DATA_BLOB), 
  parent(initParent), maxUID(-1), uidMode(UID_MODE_NONE), autoCreate(false), 
  managed(false)
{
	log = new Reporter();
}

Node::Node(Node *initParent, int initID)
: nodeID(initID), nodeName(""), dataType(NODE_DATA_BLOB), parent(initParent), 
  maxUID(-1), uidMode(UID_MODE_NONE), autoCreate(false), managed(false)
{
	log = new Reporter();
}

Node::Node(Node *initParent, int initID, const std::string &initName)
: nodeID(initID), nodeName(initName), dataType(NODE_DATA_BLOB), 
  parent(initParent), maxUID(-1), uidMode(UID_MODE_NONE), autoCreate(false), 
  managed(false)
{
	log = new Reporter();
}

Node::Node(Node *initParent, int initID, const std::string &initName, 
	int initDataType)
: nodeID(initID), nodeName(initName), dataType(initDataType), 
  parent(initParent), maxUID(-1), uidMode(UID_MODE_NONE), autoCreate(false), 
  managed(false)
{
	log = new Reporter();
}

Node::Node(Node *initParent, int initID, const std::string &initName, 
	int initDataType, bool initManaged)
: nodeID(initID), nodeName(initName), dataType(initDataType), 
  parent(initParent), maxUID(-1), uidMode(UID_MODE_NONE), autoCreate(false), 
  managed(initManaged)
{
	log = new Reporter();
}

Node::~Node()
{
	delete log;
	clearData(false);
	removeAllChildren(false);
}

bool Node::validateChildIndex(unsigned int childIndex)
{
	if ((childIndex >= 0) && (childIndex < children.size()))
		return true;
	else
	if ((childIndex >= 0) && autoCreate)
		while (childIndex != (children.size() - 1))
		{
			/* Add appropriate empty child nodes until there is a valid child 
			   node with the specified index. */
			addChild();
		}
	else
		return false;
	return true;
}

bool Node::validateDataIndex(unsigned int dataIndex)
{
	if ((dataIndex >= 0) && (dataIndex < nodeData.size()))
		return true;
	else
	if ((dataIndex >= 0) && autoCreate)
		while (dataIndex != (nodeData.size() - 1))
		{
			/* Add appropriate empty data entries until there is a valid data 
			   entry with the specified index. */
			switch (dataType)
			{
				case NODE_DATA_BLOB:
					addData("");
					break;
				case NODE_DATA_INT:
					addData(0);
					break;
				case NODE_DATA_DOUBLE:
					addData(0.0);
					break;
				default:
					addData("");
			}
		}
	else
		return false;
	return true;
}

unsigned int Node::refChild(Node *childNode)
{
	if (!log->assert(childNode != 0, 
		"[Node::refChild] Child node pointer is null."))
		return 0;
	childNodeRef[childNode]++;
	return childNodeRef[childNode];
}

unsigned int Node::unrefChild(Node *childNode)
{
	if (!log->assert(childNode != 0, 
		"[Node::unrefChild] Child node pointer is null."))
		return 0;
	childNodeRef[childNode]--;
	if (childNodeRef[childNode] == 0)
	{
		removeIndexEntries(childNode);
		map<Node*, unsigned int>::iterator i = childNodeRef.find(childNode);
		childNodeRef.erase(i);
		if (childNode->isManaged())
			delete childNode;
		return 0;
	}
	return childNodeRef[childNode];
}

unsigned int Node::getRefCount(Node *childNode)
{
	if (!log->assert(childNode != 0, 
		"[Node::unrefChild] Child node pointer is null."))
		return 0;
	return childNodeRef[childNode];
}

void Node::setID(int newID)
{
	int oldID = nodeID;
	nodeID = newID;
	if (parent != 0)
	{
		parent->removeIndexEntry(oldID);
		parent->addIndexEntry(this);
	}
}

void Node::setName(const std::string &newName)
{
	string oldName = nodeName;
	nodeName = newName;
	if (parent != 0)
	{
		parent->removeIndexEntry(oldName);
		parent->addIndexEntry(this);
	}
}

void Node::setParent(Node *newParent)
{
	parent = newParent;
}

void Node::setDataType(int newDataType)
{
	dataType = newDataType;
}

int Node::addData(const std::string &newData)
{
	nodeData.push_back("");
	setData(getNumData() - 1, newData);
	return getNumData() - 1;
}

int Node::addData(int newData)
{
	nodeData.push_back("");
	setData(getNumData() - 1, newData);
	return getNumData() - 1;
}

int Node::addData(double newData)
{
	nodeData.push_back("");
	setData(getNumData() - 1, newData);
	return getNumData() - 1;
}

bool Node::setBlob(unsigned int dataIndex, const std::string &newData)
{
	if (!validateDataIndex(dataIndex))
		return false;
	nodeData[dataIndex] = newData;
	return true;
}

bool Node::setData(unsigned int dataIndex, const std::string &newData)
{
	if (!validateDataIndex(dataIndex))
		return false;
	if (dataType == NODE_DATA_INT)
		return setData(dataIndex, 
			static_cast<int>(strtol(newData.c_str(), 0, 10)));
	if (dataType == NODE_DATA_DOUBLE)
		return setData(dataIndex, strtod(newData.c_str(), 0));
	nodeData[dataIndex] = newData;
	return true;
}

bool Node::setData(unsigned int dataIndex, int newData)
{
	if (dataType == NODE_DATA_DOUBLE)
		return setData(dataIndex, static_cast<double>(newData));
	if (dataType == NODE_DATA_BLOB)
	{
		ostringstream newBlob;
		newBlob << newData;
		return setBlob(dataIndex, newBlob.str());
	}
	return setBlob(dataIndex, packInt(newData));
}

bool Node::setData(unsigned int dataIndex, unsigned int newData)
{
	return setData(dataIndex, static_cast<int>(newData));
}

bool Node::setData(unsigned int dataIndex, double newData)
{
	if (dataType == NODE_DATA_INT)
		return setData(dataIndex, static_cast<int>(newData));
	if (dataType == NODE_DATA_BLOB)
	{
		ostringstream newBlob;
		newBlob << newData;
		return setBlob(dataIndex, newBlob.str());
	}
	return setBlob(dataIndex, packDouble(newData));
}

bool Node::setData(const std::string &newData)
{
	return setData(0, newData);
}

bool Node::setData(int newData)
{
	return setData(0, newData);
}

bool Node::setData(unsigned int newData)
{
	return setData(0, newData);
}

bool Node::setData(double newData)
{
	return setData(0, newData);
}

std::string Node::getData(unsigned int dataIndex)
{
	if (!validateDataIndex(dataIndex))
		return "";
	if (dataType == NODE_DATA_INT)
	{
		ostringstream buf;
		buf << getInt(dataIndex);
		return buf.str();
	} else
	if (dataType == NODE_DATA_DOUBLE)
	{
		ostringstream buf;
		buf << getDouble(dataIndex);
		return buf.str();
	}
	return nodeData[dataIndex];
}

std::string Node::getBlob(unsigned int dataIndex)
{
	if (!validateDataIndex(dataIndex))
		return "";
	return nodeData[dataIndex];
}

int Node::getInt(unsigned int dataIndex)
{
	if (!validateDataIndex(dataIndex))
		return 0;
	if (dataType == NODE_DATA_DOUBLE)
		return static_cast<int>(getDouble(dataIndex));
	return unpackInt(nodeData[dataIndex]);
}

double Node::getDouble(unsigned int dataIndex)
{
	if (!validateDataIndex(dataIndex))
		return 0;
	if (dataType == NODE_DATA_INT)
		return static_cast<double>(getInt(dataIndex));
	return unpackDouble(nodeData[dataIndex]);
}

bool Node::removeData(unsigned int dataIndex)
{
	if (!validateDataIndex(dataIndex))
		return false;
	vector<string>::iterator i = nodeData.begin();
	i += dataIndex;
	nodeData.erase(i);
	return true;
}

void Node::clearData(bool recursive)
{
	if (recursive)
	{
		vector<NodeInfo>::const_iterator i;
		for (i = children.begin(); i != children.end(); i++)
		{
			if ((*i).node != 0)
				(*i).node->clearData(true);
		}
	}
	nodeData.clear();
}

Node *Node::addChild(int childID, const std::string& childName)
{
	NodeInfo newNodeInfo;
	if (childID == NODE_ID_NOT_SET)
	{
		if (uidMode == UID_MODE_NODE)
			childID = getUID(false);
		else
		if (uidMode == UID_MODE_TREE)
			childID = getUID(true);
	}
	newNodeInfo.node = new Node(this, childID, childName, dataType, true);
	newNodeInfo.manage = true;
	newNodeInfo.node->setUIDMode(getUIDMode());
	newNodeInfo.node->setIndexMode(getIndexMode());
	newNodeInfo.node->setAutoCreate(getAutoCreate());
	newNodeInfo.node->getLog().redirect(log);
	children.push_back(newNodeInfo);
	refChild(newNodeInfo.node);
	return newNodeInfo.node;
}

void Node::addChild(Node *newChild, bool newManage)
{
	if (!log->assert(newChild != 0, 
		"[Node::addChild] Child node pointer is null."))
		return;
	NodeInfo newNodeInfo;
	newNodeInfo.node = newChild;
	newNodeInfo.manage = newManage;
	newChild->setParent(this);
	if (newManage)
	{
		newChild->setManaged(true);
		newChild->getLog().redirect(log);
	} else
		log->assert(!newChild->isManaged(), "[Node::addChild] Memory "
			"management flags of function call and child node are "
			"conflicting.");
	children.push_back(newNodeInfo);
	refChild(newNodeInfo.node);
}

Node *Node::findChild(int searchID, bool recursive)
{
	// ----- DISABLED FOR DEBUGGING ----- //
	Node *result = getIndexEntry(searchID);
	if (result != 0)
		return result;
	// ----- DISABLED FOR DEBUGGING ----- */
	/* ----- DEBUG ----- //
	Node *result = 0;
	Node *indexResult = getIndexEntry(searchID);
	// ----- DEBUG ----- */
	// Not in index, do a linear search.
	vector<NodeInfo>::const_iterator i = children.begin();
	while ((result == 0) && (i != children.end()))
	{
		if (((*i).node != 0) && ((*i).node->getID() == searchID))
			result = (*i).node;
		i++;
	}
	if (recursive && (result == 0))
	{
		i = children.begin();
		while ((result == 0) && (i != children.end()))
		{
			if ((*i).node != 0)
				result = (*i).node->findChild(searchID, true);
			i++;
		}
	}
	if ((result == 0) && autoCreate)
	{
		result = addChild();
		result->setID(searchID);
	}
	// Update index. (This will do nothing if indexes are disabled.)
	/* ----- DEBUG ----- //
	if ((indexResult != 0) && (result != indexResult))
	{
		cout << "[Node::findChild] DEBUG: "
			"Invalid pointer to child node in index (indexResult = " 
			<< indexResult << ", result = " << result 
			<< ", searchID = " << searchID << ")." << endl;
		cout.flush();
	}
	// ----- DEBUG ----- */
	if (result != 0)
		addIndexEntry(result);
	return result;
}

Node *Node::findChild(const std::string &searchName, 
	bool recursive)
{
	// ----- DISABLED FOR DEBUGGING ----- //
	Node *result = getIndexEntry(searchName);
	if (result != 0)
		return result;
	// ----- DISABLED FOR DEBUGGING ----- */
	/* ----- DEBUG ----- //
	Node *result = 0;
	Node *indexResult = getIndexEntry(searchName);
	// ----- DEBUG ----- */
	// Not in index, do a linear search.
	vector<NodeInfo>::const_iterator i = children.begin();
	while ((result == 0) && (i != children.end()))
	{
		if (((*i).node != 0) && (*i).node->getName() == searchName)
			result = (*i).node;
		i++;
	}
	if (recursive && (result == 0))
	{
		i = children.begin();
		while ((result == 0) && (i != children.end()))
		{
			if ((*i).node != 0)
				result = (*i).node->findChild(searchName, true);
			i++;
		}
	}
	if ((result == 0) && autoCreate)
	{
		result = addChild();
		result->setName(searchName);
	}
	// Update index. (This will do nothing if indexes are disabled.)
	/* ----- DEBUG ----- //
	if ((indexResult != 0) && (result != indexResult))
	{
		cout << "[Node::findChild] DEBUG: "
			"Invalid pointer to child node in index (indexResult = " 
			<< indexResult << ", result = " << result 
			<< ", searchName = '" << searchName << "')." << endl;
		cout.flush();
	}
	// ----- DEBUG ----- */
	if (result != 0)
		addIndexEntry(result);
	return result;
}

Node *Node::getChild(unsigned int childIndex)
{
	if (!validateChildIndex(childIndex))
		return 0;
	return children[childIndex].node;
}

unsigned int Node::getNumChildren(bool recursive)
{
	unsigned int result = children.size();
	if (recursive)
	{
		vector<NodeInfo>::const_iterator i;
		for (i = children.begin(); i != children.end(); i++)
		{
			if ((*i).node != 0) 
				result += (*i).node->getNumChildren(true);
		}
	}
	return result;
}

bool Node::removeChild(unsigned int childIndex)
{
	if ((childIndex < 0) || (childIndex >= children.size()))
		return false;
	vector<NodeInfo>::iterator i = children.begin();
	i += childIndex;
	if (!log->assert((*i).node != 0, 
		"[Node::removeChild] Child node pointer is null."))
		return false;
	unrefChild((*i).node);
	children.erase(i);
	return true;
}

bool Node::removeChild(Node *targetNode, bool recursive)
{
	if ((targetNode == 0) || (children.size() == 0))
		return false;
	vector<NodeInfo>::iterator i = children.begin();
	bool found = false;
	while ((i != children.end()) && !found)
	{
		if ((*i).node == targetNode)
			found = true;
		else
			i++;
	}
	if (found)
	{
		if (!log->assert((*i).node != 0, 
			"[Node::removeChild] Child node pointer is null."))
			return false;
		unrefChild((*i).node);
		children.erase(i);
	} else
	if (recursive)
	{
		i = children.begin();
		while ((i != children.end()) && !found)
			if ((*i).node != 0)
				found = (*i).node->removeChild(targetNode, true);
	}
	return found;
}

void Node::removeAllChildren(bool recursive)
{
	vector<NodeInfo>::iterator i;
	for (i = children.begin(); i != children.end(); i++)
	{
		if (((*i).node != 0) && recursive)
			(*i).node->removeAllChildren(true);
		if (((*i).node != 0) && (*i).node->isManaged())
		{
			/* Make sure managed child nodes of current child node are 
			   deleted. */
			(*i).node->removeManagedChildren();
			childNodeRef[(*i).node] = 0;
			removeIndexEntries((*i).node);
			delete (*i).node;
		}
	}
	childNodeRef.clear();
	nameIndex.clear();
	idIndex.clear();
	children.clear();
}

bool Node::setChild(unsigned int childIndex, Node *newChild, bool newManage)
{
	if (!log->assert(newChild != 0, 
		"[Node::setChild] Child node pointer is null."))
		return false;
	if (!validateChildIndex(childIndex))
		return 0;
	Node *currentNode = children[childIndex].node;
	if (currentNode != 0)
		unrefChild(currentNode);
	children[childIndex].node = newChild;
	children[childIndex].manage = newManage;
	refChild(newChild);
	if (newManage)
		children[childIndex].node->setManaged(true);
	else
		log->assert(!newChild->isManaged(), "[Node::addChild] "
			"Memory management flags of function call and child node are "
			"conflicting.");
	return true;
}

void Node::removeManagedChildren()
{
	vector<NodeInfo>::iterator i;
	vector<Node *> trash;
	for (i = children.begin(); i != children.end(); i++)
	{
		if (((*i).node != 0) && (*i).node->isManaged())
		{
			/* Make sure managed child nodes of current child node are 
			   deleted. */
			(*i).node->removeManagedChildren();
			trash.push_back((*i).node);
		}
	}
	vector<Node *>::iterator k;
	// Delete managed child nodes of this node.
	for (k = trash.begin(); k != trash.end(); k++)
		removeChild(*k, false);
}

int Node::getChildIndex(Node *targetNode)
{
	unsigned int result = 0;
	bool found = false;
	while ((result < children.size()) && !found)
	{
		if (children[result].node == targetNode)
			found = true;
		else
			result++;
	}
	if (!found)
		return -1;
	return result;
}

unsigned int Node::printDebugInfo(int targetLevel, int callingLevel, 
	int parentID, int childID)
{
	callingLevel++;
	// callingLevel is now actually the tree depth level of this node.
	if (targetLevel == callingLevel)
	{
		cout << "Node " << parentID << ":" << childID << " (level " 
			<< targetLevel << "):" << endl;
		cout << "(this: " << this << ", parent: " << parent << ")" << endl;
		cout << "Name: " << nodeName << endl;
		cout << "ID:   " << nodeID << endl;
		cout << "Data:" << endl;
		if (nodeData.size() == 0)
			cout << "(empty)" << endl;
		string currentData;
		for (unsigned int i = 0; i < nodeData.size(); i++)
		{
			currentData = getBlob(i);
			cout << "[" << i << "]:" << endl 
				<< makeNiceHex(makeHex(currentData), 
					makeReadable(currentData, "."), 16, 8);
		}
		cout << endl;
		return 1;
	}
	int result = 0;
	// If this node didn't belong to target level, try the child nodes.
	for (unsigned int i = 0; i < children.size(); i++)
	{
		if (children[i].node != 0)
			result += children[i].node->printDebugInfo(targetLevel, 
				callingLevel, childID, i);
	}
	return result;
}

unsigned int Node::printDebugInfo(int targetLevel)
{
	return printDebugInfo(targetLevel, -1, 0, 0);
}

int Node::getUID(bool treeUID)
{
	if (!treeUID || (parent == 0))
	{
		maxUID++;
		return maxUID;
	} else
		return parent->getUID(true);
}

void Node::setUIDMode(int newUIDMode)
{
	uidMode = newUIDMode;
}

void Node::setAutoCreate(bool newAutoCreate)
{
	autoCreate = newAutoCreate;
}

void Node::setIndexMode(int newIndexMode)
{
	indexMode = newIndexMode;
}

void Node::traverse(NodeDump *target, int order)
{
	vector<NodeInfo>::const_iterator i;
	switch (order)
	{
		case TRAVERSAL_INORDER:
			if (getNumChildren() == 2)
			{
				Node *leftChild = getChild(0);
				Node *rightChild = getChild(1);
				if (leftChild != 0)
					leftChild->traverse(target, order);
				if (target != 0)
					target->dump(this);
				if (rightChild != 0)
					rightChild->traverse(target, order);
			} else
			{
				log->msg("[Node::traverse] ERROR: Invalid traversal order for "
					"non-binary tree.", log->VL_ERROR);
			}
			break;
		case TRAVERSAL_PREORDER:
			if (target != 0)
				target->dump(this);
			for (i = children.begin(); i != children.end(); i++)
				if ((*i).node != 0)
					(*i).node->traverse(target, order);
			break;
		case TRAVERSAL_POSTORDER:
			for (i = children.begin(); i != children.end(); i++)
				if ((*i).node != 0)
					(*i).node->traverse(target, order);
			if (target != 0)
				target->dump(this);
			break;
		default:
			log->msg("[Node::traverse] ERROR: Invalid traversal order.",
				log->VL_ERROR);
	}
}

void Node::serialize(std::string &target)
{
	ostringstream status;
	string nodeBlock;
	// Reserve 24 bytes for later addition of size and checksum.
	nodeBlock.append(24, '\x00');
	// Append node header.
	nodeBlock.append(packInt(nodeID));
	nodeBlock.append(packInt(dataType));
	nodeBlock.append(packInt(maxUID));
	nodeBlock.append(packInt(uidMode));
	nodeBlock.append(packBool(autoCreate));
	nodeBlock.append(packInt(getNumData()));
	nodeBlock.append(packInt(getNumChildren()));
	// Append node name block.
	nodeBlock.append(packInt(nodeName.size()));
	nodeBlock.append(nodeName);
	// Append data entries.
	for (unsigned int i = 0; i < nodeData.size(); i++)
	{
		nodeBlock.append(packInt(nodeData[i].size()));
		nodeBlock.append(nodeData[i]);
	}
	// Append child node data blocks.
	Node *currentChild;
	for (unsigned int i = 0; i < children.size(); i++)
	{
		currentChild = children[i].node;
		if (currentChild != 0)
			currentChild->serialize(nodeBlock);
		else
			target.append(1, '\x00');
	}
	// Add block size.
	status.str("");
	status << "[Node::serialize] DEBUG: Node block size: " 
		<< nodeBlock.size() << " bytes.";
	log->msg(status.str(), log->VL_DEBUG_INSANE);
	nodeBlock.replace(0, 4, packInt(nodeBlock.size()));
	// Add checksum.
	string checkSum = sha1(nodeBlock);
	nodeBlock.replace(4, 20, checkSum);
	log->msg(string("[Node::serialize] DEBUG: SHA-1 Checksum: ")
		+ makeHex(checkSum), log->VL_DEBUG_INSANE);
	target.append(nodeBlock);
}

bool Node::unpack(const std::string &serialized, unsigned int blockStart, 
	unsigned int blockSize)
{
	if (blockSize == 0)
		blockSize = serialized.size();
	if ((blockStart + blockSize) > serialized.size())
	{
		log->msg("[Node::unpack] ERROR: Block size mismatch: Serialized data "
			"block smaller than specified block size.",
			log->VL_ERROR);
		return false;
	}
	if (blockSize < NODE_HEADER_SIZE)
	{
		log->msg("[Node::unpack] ERROR: Block size mismatch: Specified block "
			"size smaller than size of node header.",
			log->VL_ERROR);
		return false;
	}
	ostringstream status;
	unsigned int currentPos = blockStart;
	// Validate node block size.
	unsigned int nodeBlockSize = unpackInt(serialized.substr(currentPos, 4));
	status.str("");
	status << "[Node::unpack] DEBUG: Node block size: " << nodeBlockSize 
		<< " bytes.";
	log->msg(status.str(), log->VL_DEBUG_INSANE);
	if (blockSize < nodeBlockSize)
	{
		log->msg("[Node::unpack] ERROR: Block size mismatch: Serialized data "
			"block smaller than node block size.",
			log->VL_ERROR);
		return false;
	}
	// Extract node data block.
	string nodeBlock = serialized.substr(currentPos, nodeBlockSize);
	currentPos = 4;
	// Validate checksum.
	string checkSum = nodeBlock.substr(currentPos, 20);
	string emptyCheckSum(20, '\x00');
	log->msg(string("[Node::unpack] DEBUG: Node block SHA-1 extracted "
		"checksum:  ") + makeHex(checkSum), log->VL_DEBUG_INSANE);
	nodeBlock.replace(currentPos, 20, emptyCheckSum);
	string calcCheckSum = sha1(nodeBlock.substr(0, nodeBlockSize));
	log->msg(string("[Node::unpack] DEBUG: Node block SHA-1 calculated "
		"checksum: ") + makeHex(calcCheckSum), log->VL_DEBUG_INSANE);
	if (checkSum != calcCheckSum)
	{
		log->msg("[Node::unpack] ERROR: Checksum mismatch: The node data block "
			"is probably corrupted.", log->VL_ERROR);
		return false;
	}
	log->msg("[Node::unpack] DEBUG: Checksum OK. :-)", log->VL_DEBUG_INSANE);
	currentPos += 20;
	// Extract header fields.
	log->msg("[Node::unpack] DEBUG: Extracting node header data.", 
		log->VL_DEBUG_INSANE);
	clear();
	status.str("");
	status << "[Node::unpack] DEBUG: Extracted header data: ";
	setID(unpackInt(nodeBlock.substr(currentPos, 4)));
	status << "nodeID = " << getID() << ", ";
	currentPos += 4;
	setDataType(unpackInt(nodeBlock.substr(currentPos, 4)));
	status << "dataType = " << getDataType() << ", ";
	currentPos += 4;
	maxUID = unpackInt(nodeBlock.substr(currentPos, 4));
	status << "maxUID = " << maxUID << ", ";
	currentPos += 4;
	setUIDMode(unpackInt(nodeBlock.substr(currentPos, 4)));
	status << "uidMode = " << getUIDMode() << ", ";
	currentPos += 4;
	setAutoCreate(unpackBool(nodeBlock.substr(currentPos, 1)));
	status << "autoCreate = " << getAutoCreate() << ", ";
	currentPos++;
	unsigned int numData = unpackInt(nodeBlock.substr(currentPos, 4));
	status << "numData = " << numData << ", ";
	currentPos += 4;
	unsigned int numChildren = unpackInt(nodeBlock.substr(currentPos, 4));
	status << "numChildren = " << numChildren << ", ";
	currentPos += 4;
	unsigned int nameSize = unpackInt(nodeBlock.substr(currentPos, 4));
	status << "nameSize = " << nameSize << ", ";
	currentPos += 4;
	setName(nodeBlock.substr(currentPos, nameSize));
	status << "nodeName = '" << getName() << "'.";
	currentPos += nameSize;
	log->msg(status.str(), log->VL_DEBUG_INSANE);
	// Extract data.
	if (numData > 0)
		log->msg("[Node::unpack] DEBUG: Extracting data entries.", 
			log->VL_DEBUG_INSANE);
	unsigned int dataSize;
	string dataBytes;
	for (unsigned int i = 0; i < numData; i++)
	{
		dataSize = unpackInt(nodeBlock.substr(currentPos, 4));
		currentPos += 4;
		if (dataSize > 0)
			dataBytes = nodeBlock.substr(currentPos, dataSize);
		else
			dataBytes = "";
		setBlob(i, dataBytes);
		status.str("");
		status << "[Node::unpack] DEBUG: Data entry [" << i 
			<< "]: size = " << dataSize << ", value = " 
			<< makeHex(getData(i));
		log->msg(status.str(), log->VL_DEBUG_INSANE);
		currentPos += dataSize;
	}
	// Extract child nodes.
	if (numChildren > 0)
		log->msg("[Node::unpack] DEBUG: Extracting child nodes.", 
			log->VL_DEBUG_INSANE);
	Node *currentChild;
	unsigned int childBlockSize;
	unsigned int childCount = 0;
	bool unpackOK = true;
	while((childCount < numChildren) && unpackOK)
	{
		childBlockSize = unpackInt(nodeBlock.substr(currentPos, 4));
		status.str("");
		status << "[Node::unpack] DEBUG: Child node [" << childCount 
			<< "]: blockSize = " << childBlockSize;
		log->msg(status.str(), log->VL_DEBUG_INSANE);
		if (childBlockSize == 0)
		{
			log->msg("[Node::unpack] DEBUG: Adding child node (null).", 
				log->VL_DEBUG_INSANE);
			addChild(0, true);
			currentPos += 4;
		} else
		{
			log->msg("[Node::unpack] DEBUG: Unpacking child node.", 
				log->VL_DEBUG_INSANE);
			currentChild = addChild();
			unpackOK = currentChild->unpack(nodeBlock, currentPos, 
				childBlockSize);
			if (unpackOK)
			{
				log->msg("[Node::unpack] DEBUG: Child node unpacked "
					"successfully.", log->VL_DEBUG_INSANE);
			} else
			{
				status.str("");
				status << "[Node::unpack] ERROR: Child node [" << childCount 
					<< "]: Unpacking failed!";
				log->msg(status.str(), log->VL_ERROR);
			}
			currentPos += childBlockSize;
		}
		childCount++;
	}
	log->msg("[Node::unpack] DEBUG: Unpacking finished.", log->VL_DEBUG_INSANE);
	if (!unpackOK)
		log->msg("[Node::unpack] DEBUG: Some child nodes could not be "
			"unpacked.", log->VL_DEBUG_INSANE);
	return unpackOK;
}

void Node::convertToNativeType()
{
	if (dataType != NODE_DATA_BLOB)
		return;
	string data = getBlob();
	if (isInteger(data))
	{
		setDataType(NODE_DATA_INT);
		int intData;
		for (unsigned int i = 0; i < getNumData(); i++)
		{
			data = getBlob(i);
			intData = strtol(data.c_str(), 0, 10);
			setData(i, intData);
		}
	} else
	if (isFloat(data))
	{
		setDataType(Node::NODE_DATA_DOUBLE);
		for (unsigned int i = 0; i < getNumData(); i++)
		{
			data = getBlob(i);
			setData(i, strtod(data.c_str(), 0));
		}
	}
}

void Node::addIndexEntry(Node *indexNode)
{
	if ((indexMode == INDEX_MODE_NONE) || (indexNode == 0))
		return;
	if ((indexMode == INDEX_MODE_TREE) && (parent != 0))
	{
		parent->addIndexEntry(indexNode);
		return;
	}
	string indexName = indexNode->getName();
	int indexID = indexNode->getID();
	if (indexName.size() > 0)
	{
		/* ----- DEBUG ----- //
		cout << "Adding name index entry for name '" << indexName << "'." 
			<< endl;
		// ----- DEBUG ----- */
		nameIndex[indexName] = indexNode;
	}
	if ((indexID != NODE_ID_NOT_SET) && (indexID >= 0) 
		&& (static_cast<unsigned int>(indexID) < MAX_ID_INDEX_SIZE))
	{
		// Resize the index by adding empty elements.
		while (idIndex.size() <= static_cast<unsigned int>(indexID))
			idIndex.push_back(0);
		/* ----- DEBUG ----- //
		cout << "Adding ID index entry for ID " << indexID << "." << endl;
		// ----- DEBUG ----- */
		idIndex[indexID] = indexNode;
	}
}

Node *Node::getIndexEntry(const std::string &indexName)
{
	if ((indexMode == INDEX_MODE_NONE) || (indexName.size() == 0))
		return 0;
	if ((indexMode == INDEX_MODE_TREE) && (parent != 0))
		return parent->getIndexEntry(indexName);
	/* ----- DEBUG ----- //
	cout << "Looking up name index entry for '" << indexName << "'." << endl;
	// ----- DEBUG ----- */
	return nameIndex[indexName];
}

void Node::removeIndexEntry(const std::string &indexName)
{
	if ((indexMode == INDEX_MODE_NONE) || (indexName.size() == 0))
		return;
	if ((indexMode == INDEX_MODE_TREE) && (parent != 0))
	{
		parent->removeIndexEntry(indexName);
		return;
	}
	nameIndex[indexName] = 0;
	map<string, Node*>::iterator i = nameIndex.find(indexName);
	nameIndex.erase(i);
}

Node *Node::getIndexEntry(int indexID)
{
	if ((indexMode == INDEX_MODE_NONE) || (indexID == NODE_ID_NOT_SET)
		|| (indexID < 0))
		return 0;
	if ((indexMode == INDEX_MODE_TREE) && (parent != 0))
		return parent->getIndexEntry(indexID);
	/* ----- DEBUG ----- //
	cout << "Looking up ID index entry for " << indexID << "." << endl;
	// ----- DEBUG ----- */
	if (static_cast<unsigned int>(indexID) < idIndex.size())
		return idIndex[indexID];
	return 0;
}

void Node::removeIndexEntry(int indexID)
{
	if ((indexMode == INDEX_MODE_NONE) || (indexID == NODE_ID_NOT_SET)
		|| (indexID < 0))
		return;
	if ((indexMode == INDEX_MODE_TREE) && (parent != 0))
	{
		parent->removeIndexEntry(indexID);
		return;
	}
	if (static_cast<unsigned int>(indexID) < idIndex.size())
		idIndex[indexID] = 0;
}

void Node::removeIndexEntries(Node *indexNode)
{
	if ((indexMode == INDEX_MODE_NONE) || (indexNode == 0))
		return;
	removeIndexEntry(indexNode->getName());
	removeIndexEntry(indexNode->getID());
}

void Node::clearNameIndex()
{
	nameIndex.clear();
}

void Node::clearIDIndex()
{
	idIndex.clear();
}

void Node::clearIndexes()
{
	clearNameIndex();
	clearIDIndex();
}

Node &Node::operator[](int searchID)
{
	bool lastAutoCreate = getAutoCreate();
	setAutoCreate(true);
	Node *result = findChild(searchID, false);
	setAutoCreate(lastAutoCreate);
	return *result;
}

Node &Node::operator[](const std::string &searchName)
{
	bool lastAutoCreate = getAutoCreate();
	setAutoCreate(true);
	Node *result = findChild(searchName, false);
	setAutoCreate(lastAutoCreate);
	return *result;
}

std::string Node::operator=(const std::string& newData)
{
	setData(0, newData);
	return newData;
}

int Node::operator=(int newData)
{
	setData(0, newData);
	return newData;
}

double Node::operator=(double newData)
{
	setData(0, newData);
	return newData;
}

void Node::copy(Ionflux::Tools::Node& target, unsigned int maxDepth, 
	unsigned int currentDepth)
{
	bool origAutoCreate = getAutoCreate();
	Node *currentChild;
	Node *currentSourceChild;
	// Clear the node.
	target.clearData(false);
	target.removeAllChildren(false);
	target.setDataType(getDataType());
	target.setUIDMode(getUIDMode());
	maxUID = getUID(false);
	// Set auto-create for copying data entries and child nodes.
	target.setAutoCreate(true);
	// Copy data entries.
	for (unsigned int i = 0; i < getNumData(); i++)
		target.setBlob(i, getBlob(i));
	if ((maxDepth > 0)
		&& (currentDepth >= maxDepth))
	{
		target.setAutoCreate(origAutoCreate);
		return;
	}
	// Copy child nodes.
	for (unsigned int i = 0; i < getNumChildren(); i++)
	{
		currentSourceChild = getChild(i);
		if (currentSourceChild != 0)
		{
			currentChild = target.addChild();
			// Name and ID must be set explicitly.
			currentChild->setName(currentSourceChild->getName());
			currentChild->setID(currentSourceChild->getID());
			currentSourceChild->copy(*currentChild, maxDepth, 
				currentDepth + 1);
		}
	}
	target.setAutoCreate(origAutoCreate);
}

Node &Node::operator=(Node &sourceNode)
{
	sourceNode.copy(*this);
	return *this;
}

bool Node::getAutoCreate()
{
	return autoCreate;
}

int Node::getUIDMode()
{
	return uidMode;
}

int Node::getIndexMode()
{
	return indexMode;
}

int Node::getID()
{
	return nodeID;
}

std::string Node::getName()
{
	return nodeName;
}

int Node::getDataType()
{
	return dataType;
}

std::string Node::getData()
{
	return getData(0);
}

std::string Node::getBlob()
{
	return getBlob(0);
}

int Node::getInt()
{
	return getInt(0);
}

double Node::getDouble()
{
	return getDouble(0);
}

unsigned int Node::getNumData()
{
	return nodeData.size();
}

unsigned int Node::getNumChildren()
{
	return getNumChildren(false);
}

Node *Node::getParent()
{
	return parent;
}

std::string Node::getPath()
{
	string result;
	if (parent != 0)
	{
		result = parent->getPath();
		if (nodeName != "")
		{
			/* Append resolution operator only if this node is not a child of
		       the root node. */
			if (result != "")
			   result.append(".");
			result.append(nodeName);
		} else
		if (nodeID != NODE_ID_NOT_SET)
		{
			/* Use subscripting for IDs. (Resolution operator could be used 
			   as well.) */
			ostringstream status;
			status << "[" << nodeID << "]";
			result.append(status.str());
		} else
		{
			log->msg("[Node::getPath] ERROR: Unable to create path for unnamed "
				"node without ID.", log->VL_ERROR);
		}
	}
	return result;
}

void Node::clear()
{
	clearData(false);
	removeAllChildren(false);
}

Node& Node::merge(Node &sourceNode, bool replace, unsigned int maxDepth, 
	unsigned int currentDepth)
{
	bool origAutoCreate = getAutoCreate();
	// Merge data entries.
	setAutoCreate(true);
	unsigned int targetNumData = getNumData();
	unsigned int sourceNumData = sourceNode.getNumData();
	for (unsigned int i = 0; i < sourceNumData; i++)
		setBlob(targetNumData + i, sourceNode.getBlob(i));
	if ((maxDepth > 0)
		&& (currentDepth >= maxDepth))
	{
		setAutoCreate(origAutoCreate);
		return *this;
	}
	// Merge child nodes.
	setAutoCreate(false);
	Node *currentChild = 0;
	Node *currentSourceChild = 0;
	string srcChildName;
	int srcChildID;
	bool merge;
	for (unsigned int i = 0; i < sourceNode.getNumChildren(); i++)
	{
		currentSourceChild = sourceNode.getChild(i);
		if (currentSourceChild != 0)
		{
			merge = true;
			srcChildID = currentSourceChild->getID();
			srcChildName = currentSourceChild->getName();
			if (srcChildID != NODE_ID_NOT_SET)
			{
				// Source child node has an ID.
				currentChild = findChild(srcChildID);
				if (replace && (currentChild != 0))
					// Child node with same ID exists, replace it.
					removeChild(currentChild, false);
				else
				if (currentChild != 0)
					// Child node with same ID exists.
					merge = false;
			}
			if (srcChildName.size() > 0)
			{
				// Source child node is a named node.
				currentChild = findChild(srcChildName);
				if (replace && (currentChild != 0))
					// Child node with same name exists, replace it.
					removeChild(currentChild, false);
				else
				if (currentChild != 0)
					// Child node with same name exists.
					merge = false;
			}
			if (merge)
			{
				// Merge source child node.
				currentChild = addChild();
				currentChild->setName(currentSourceChild->getName());
				currentChild->setID(currentSourceChild->getID());
				currentSourceChild->copy(*currentChild, maxDepth, 
				 	currentDepth + 1);
			}
		}
	}
	setAutoCreate(origAutoCreate);
	return *this;
}

bool Node::combine(unsigned int from, unsigned int to, Node &target)
{
	if (from > to)
		return false;
	target.clear();
	bool origAutoCreate = target.getAutoCreate();
	target.setAutoCreate(true);
	Node *currentClass;
	currentClass = getChild(from);
	if (currentClass == 0)
		return false;
	if (from == to)
	{
		// Nothing to combine, return entries of current class.
		for (unsigned int i = 0; i < currentClass->getNumData(); i++)
			target[i].setData(0, currentClass->getData(i));
	} else
	{
		// Combine recursively.
		Node temp;
		Node *currentSubCmb;
		unsigned int currentCmb = 0;
		string currentItem;
		combine(from + 1, to, temp);
		/* Combine each item of the current class with the combinations of 
		   the other classes. */
		for (unsigned int i = 0; i < currentClass->getNumData(); i++)
		{
			currentItem = currentClass->getData(i);
			for (unsigned int k = 0; k < temp.getNumChildren(); k++)
			{
				currentSubCmb = temp.getChild(k);
				if (currentSubCmb == 0)
					return false;
				target[currentCmb].setData(0, currentItem);
				for (unsigned int l = 0; l < currentSubCmb->getNumData(); l++)
					target[currentCmb].setData(l + 1, 
						currentSubCmb->getData(l));
				currentCmb++;
			}
		}
	}
	target.setAutoCreate(origAutoCreate);
	return true;
}

std::string Node::toConfig(const std::string& indent, unsigned int level)
{
	ostringstream status;
	string levelIndent;
	if (level >= 1)
		for (unsigned int i = 0; i < (level - 1); i++)
			levelIndent.append(indent);
	bool nestedContext = false;
	if ((nodeName == "<root>")
		|| (level == 0))
		nestedContext = false;
	else
	if (nodeName.size() > 0)
	{
		// Named node (but not the root node).
		status << levelIndent;
		if (isIdentifier(nodeName))
			// Simple name (identifier).
			status << nodeName << " = ";
		else
			// Complex name, use subscript.
			status << "[\"" << escape(nodeName, "\"") << "\"] = ";
		nestedContext = true;
	} else
	if (nodeID != NODE_ID_NOT_SET)
	{
		// Unnamed node, use ID.
		status << levelIndent;
		status << "[" << nodeID << "] = ";
		nestedContext = true;
		// NOTE: If this fails, too, this may be a root node (or an error).
	}
	if ((nodeData.size() == 1) 
		&& (children.size() == 0))
	{
		// Single data entry node, use simple syntax.
		if (nestedContext)
			status << escape(getData(0), "{}\n") << "\n";
		else
			/* Rare case of a root node with only one data entry, but 
		       still possible. */
			status << "'" << escape(getData(0), "'{}\n") << "'\n";
		return status.str();
	}
	// Multi-data entry node or parent node, use nested syntax.
	if (nestedContext)
		status << "{\n";
	// Add data entries.
	for (unsigned int i = 0; i < nodeData.size(); i++)
	{
		if (nestedContext)
			status << levelIndent << indent;
		status << "'" << escape(getData(i), "'{}\n") << "'\n";
	}
	// Add child nodes.
	Node *currentChild;
	for (unsigned int i = 0; i < children.size(); i++)
	{
		currentChild = children[i].node;
		status << currentChild->toConfig(indent, level + 1);
	}
	if (nestedContext)
		status << levelIndent << "}\n";
	return status.str();
}

void Node::setManaged(bool newManaged)
{
	managed = newManaged;
}

bool Node::isManaged()
{
	return managed;
}

Reporter &Node::getLog()
{
	return *log;
}

}

}

/** \file Node.cpp
 * \brief Tree data node (implementation).
 */
