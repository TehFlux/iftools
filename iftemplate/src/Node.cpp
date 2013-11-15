/* ==========================================================================
 * IFTemplate - Ionflux Template Processor
 * Copyright © 2012 Jörn P. Meier
 * mail@ionflux.org
 * --------------------------------------------------------------------------
 * Node.cpp                        Tree node (implementation).
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

#include "iftemplate/Node.hpp"
#include <iostream>
#include <iomanip>
#include <sstream>
#include <cstdlib>
#include "ifobject/serialize.hpp"
#include "ifobject/utils.hpp"
#include "iftemplate/utils.hpp"
#include "iftemplate/NodeDump.hpp"
#include "iftemplate/IFTemplateError.hpp"

using namespace std;

namespace Ionflux
{

namespace Template
{

NodeClassInfo::NodeClassInfo()
{
	name = "Node";
	desc = "Tree node";
	baseClassInfo.push_back(Ionflux::ObjectBase::IFObject::CLASS_INFO);
}

NodeClassInfo::~NodeClassInfo()
{
}

// public member constants
const Ionflux::Template::NodeID Node::ID_NOT_SET = -1;
const Ionflux::Template::NodeDataTypeID Node::DATA_BLOB = 0;
const Ionflux::Template::NodeDataTypeID Node::DATA_INT = 1;
const Ionflux::Template::NodeDataTypeID Node::DATA_DOUBLE = 2;
const Ionflux::Template::NodeUIDMode Node::UID_MODE_NONE = 0;
const Ionflux::Template::NodeUIDMode Node::UID_MODE_NODE = 1;
const Ionflux::Template::NodeUIDMode Node::UID_MODE_TREE = 2;
const Ionflux::Template::NodeTraversalMode Node::TRAVERSAL_INORDER = 0;
const Ionflux::Template::NodeTraversalMode Node::TRAVERSAL_PREORDER = 1;
const Ionflux::Template::NodeTraversalMode Node::TRAVERSAL_POSTORDER = 2;
const unsigned int Node::HEADER_SIZE = 53;
const Ionflux::Template::NodeIndexMode Node::INDEX_MODE_NONE = 0;
const Ionflux::Template::NodeIndexMode Node::INDEX_MODE_NODE = 1;
const Ionflux::Template::NodeIndexMode Node::INDEX_MODE_TREE = 2;
const unsigned int Node::MAX_ID_INDEX_SIZE = 268435456L;

// run-time type information instance constants
const NodeClassInfo Node::nodeClassInfo;
const Ionflux::ObjectBase::IFClassInfo* Node::CLASS_INFO = &Node::nodeClassInfo;

Node::Node()
: nodeID(ID_NOT_SET), nodeName(""), dataType(DATA_BLOB), parent(0), maxUID(-1), uidMode(UID_MODE_NONE), autoCreate(false), indexMode(INDEX_MODE_NONE)
{
	// NOTE: The following line is required for run-time type information.
	theClass = CLASS_INFO;
	// TODO: Nothing ATM. ;-)
}

Node::Node(const Ionflux::Template::Node& other)
: nodeID(ID_NOT_SET), nodeName(""), dataType(DATA_BLOB), parent(0), maxUID(-1), uidMode(UID_MODE_NONE), autoCreate(false), indexMode(INDEX_MODE_NONE)
{
	// NOTE: The following line is required for run-time type information.
	theClass = CLASS_INFO;
	*this = other;
	setNodeName(other.nodeName);
	setNodeID(other.nodeID);
}

Node::Node(Ionflux::Template::Node* initParent)
: nodeID(ID_NOT_SET), nodeName(""), dataType(DATA_BLOB), 
parent(initParent), maxUID(-1), uidMode(UID_MODE_NONE), autoCreate(false), 
indexMode(INDEX_MODE_NONE)
{
	// NOTE: The following line is required for run-time type information.
	theClass = CLASS_INFO;
	// NOTE: This constructor should not be used anymore.
	std::cerr << "[Node::Node] WARNING: "
	    "Using deprecated constructor to set parent node." << std::endl;
}

Node::Node(Ionflux::Template::Node* initParent, Ionflux::Template::NodeID 
initID, const std::string& initName, Ionflux::Template::NodeDataTypeID 
initDataType)
: nodeID(initID), nodeName(initName), dataType(initDataType), 
parent(initParent), maxUID(-1), uidMode(UID_MODE_NONE), autoCreate(false), 
indexMode(INDEX_MODE_NONE)
{
	// NOTE: The following line is required for run-time type information.
	theClass = CLASS_INFO;
	// TODO: Nothing ATM. ;-)
}

Node::~Node()
{
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

bool Node::validateChildIndex(unsigned int childIndex) const
{
	if ((childIndex >= 0) && (childIndex < children.size()))
	    return true;
	return false;
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
	            case DATA_BLOB:
	                addData("");
	                break;
	            case DATA_INT:
	                addData(0);
	                break;
	            case DATA_DOUBLE:
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

bool Node::validateDataIndex(unsigned int dataIndex) const
{
	if ((dataIndex >= 0) && (dataIndex < nodeData.size()))
	    return true;
	return false;
}

void Node::addIndexEntry(Ionflux::Template::Node* indexNode)
{
	if ((indexMode == INDEX_MODE_NONE) || (indexNode == 0))
	    return;
	if ((indexMode == INDEX_MODE_TREE) && (parent != 0))
	{
	    parent->addIndexEntry(indexNode);
	    return;
	}
	string indexName = indexNode->getNodeName();
	int indexID = indexNode->getNodeID();
	if (indexName.size() > 0)
	{
	    /* ----- DEBUG ----- //
	    cout << "Adding name index entry for name '" << indexName << "'." 
	        << endl;
	    // ----- DEBUG ----- */
	    nameIndex[indexName] = indexNode;
	}
	if ((indexID != ID_NOT_SET) && (indexID >= 0) 
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

Ionflux::Template::Node* Node::getIndexEntry(const std::string& indexName) 
const
{
	if ((indexMode == INDEX_MODE_NONE) || (indexName.size() == 0))
	    return 0;
	if ((indexMode == INDEX_MODE_TREE) && (parent != 0))
	    return parent->getIndexEntry(indexName);
	NodeNameMap::const_iterator i = nameIndex.find(indexName);
	if (i == nameIndex.end())
	    return 0;
	return (*i).second;
}

void Node::removeIndexEntry(const std::string& indexName)
{
	if ((indexMode == INDEX_MODE_NONE) || (indexName.size() == 0))
	    return;
	if ((indexMode == INDEX_MODE_TREE) && (parent != 0))
	{
	    parent->removeIndexEntry(indexName);
	    return;
	}
	nameIndex[indexName] = 0;
	NodeNameMap::iterator i = nameIndex.find(indexName);
	if (i != nameIndex.end())
	    nameIndex.erase(i);
}

Ionflux::Template::Node* Node::getIndexEntry(Ionflux::Template::NodeID 
indexID) const
{
	if ((indexMode == INDEX_MODE_NONE) || (indexID == ID_NOT_SET)
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

void Node::removeIndexEntry(Ionflux::Template::NodeID indexID)
{
	if ((indexMode == INDEX_MODE_NONE) || (indexID == ID_NOT_SET)
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

void Node::removeIndexEntries(Ionflux::Template::Node* indexNode)
{
	if ((indexMode == INDEX_MODE_NONE) || (indexNode == 0))
	        return;
	    removeIndexEntry(indexNode->getNodeName());
	    removeIndexEntry(indexNode->getNodeID());
}

int Node::addData(const std::string& newData)
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

bool Node::setBlob(unsigned int dataIndex, const std::string& newData)
{
	if (!validateDataIndex(dataIndex))
	    return false;
	nodeData[dataIndex] = newData;
	return true;
}

bool Node::setData(unsigned int dataIndex, const std::string& newData)
{
	if (!validateDataIndex(dataIndex))
	    return false;
	if (dataType == DATA_INT)
	    return setData(dataIndex, 
	        static_cast<int>(strtol(newData.c_str(), 0, 10)));
	if (dataType == DATA_DOUBLE)
	    return setData(dataIndex, strtod(newData.c_str(), 0));
	nodeData[dataIndex] = newData;
	return true;
}

bool Node::setData(unsigned int dataIndex, int newData)
{
	if (dataType == DATA_DOUBLE)
	    return setData(dataIndex, static_cast<double>(newData));
	if (dataType == DATA_BLOB)
	{
	    ostringstream newBlob;
	    newBlob << newData;
	    return setBlob(dataIndex, newBlob.str());
	}
	std::string packed;
	Ionflux::ObjectBase::pack(newData, packed);
	return setBlob(dataIndex, packed);;
}

bool Node::setData(unsigned int dataIndex, unsigned int newData)
{
	// TODO: Implementation.
	return setData(dataIndex, static_cast<int>(newData));
}

bool Node::setData(unsigned int dataIndex, double newData)
{
	if (dataType == DATA_INT)
	    return setData(dataIndex, static_cast<int>(newData));
	if (dataType == DATA_BLOB)
	{
	    ostringstream newBlob;
	    newBlob << newData;
	    return setBlob(dataIndex, newBlob.str());
	}
	std::string packed;
	Ionflux::ObjectBase::pack(newData, packed);
	return setBlob(dataIndex, packed);
}

bool Node::setData(const std::string& newData)
{
	// TODO: Implementation.
	return setData(0, newData);
}

bool Node::setData(int newData)
{
	// TODO: Implementation.
	return setData(0, newData);
}

bool Node::setData(unsigned int newData)
{
	// TODO: Implementation.
	return setData(0, newData);
}

bool Node::setData(double newData)
{
	// TODO: Implementation.
	return setData(0, newData);
}

std::string Node::getData(unsigned int dataIndex) const
{
	if (!validateDataIndex(dataIndex))
	    return "";
	if (dataType == DATA_INT)
	{
	    ostringstream buf;
	    buf << getInt(dataIndex);
	    return buf.str();
	} else
	if (dataType == DATA_DOUBLE)
	{
	    ostringstream buf;
	    buf << getDouble(dataIndex);
	    return buf.str();
	}
	return nodeData[dataIndex];
}

std::string Node::getBlob(unsigned int dataIndex) const
{
	if (!validateDataIndex(dataIndex))
	    return "";
	return nodeData[dataIndex];
}

int Node::getInt(unsigned int dataIndex) const
{
	if (!validateDataIndex(dataIndex))
	    return 0;
	if (dataType == DATA_DOUBLE)
	    return static_cast<int>(getDouble(dataIndex));
	int result = 0;
	Ionflux::ObjectBase::unpack(nodeData[dataIndex], result);
	return result;
}

double Node::getDouble(unsigned int dataIndex) const
{
	if (!validateDataIndex(dataIndex))
	    return 0;
	if (dataType == DATA_INT)
	    return static_cast<double>(getInt(dataIndex));
	double result = 0;
	Ionflux::ObjectBase::unpack(nodeData[dataIndex], result);
	return result;
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

bool Node::clearData(bool recursive)
{
	if (recursive)
	{
	    for (NodeVector::const_iterator i = children.begin(); 
	        i != children.end(); i++)
	    {
	        if ((*i) != 0)
	            (*i)->clearData(true);
	    }
	}
	nodeData.clear();
	return true;
}

Ionflux::Template::Node* Node::addChild(Ionflux::Template::NodeID childID, 
const std::string& childName)
{
	if (childID == ID_NOT_SET)
	{
	    if (uidMode == UID_MODE_NODE)
	        childID = getUID(false);
	    else
	    if (uidMode == UID_MODE_TREE)
	        childID = getUID(true);
	}
	Node* nc = new Node(this, childID, childName, dataType);
	if (nc == 0)
	    throw IFTemplateError("[Node::addChild] "
	        "Could not allocate node.");
	nc->setUidMode(uidMode);
	nc->setIndexMode(indexMode);
	nc->setAutoCreate(autoCreate);
	addLocalRef(nc);
	children.push_back(nc);
	nc->setParent(this);
	return nc;
}

void Node::addChild(Ionflux::Template::Node* newChild)
{
	if (newChild == 0)
	    throw IFTemplateError("[Node::addChild] "
	        "Attempt to add null child.");
	addLocalRef(newChild);
	children.push_back(newChild);
	newChild->setParent(this);
}

Ionflux::Template::Node* Node::findChild(int searchID, bool recursive, 
unsigned int level)
{
	Node* result = getIndexEntry(searchID);
	if (result != 0)
	    return result;
	// Not in index, do a linear search.
	NodeVector::const_iterator i = children.begin();
	while ((result == 0) 
	    && (i != children.end()))
	{
	    if (((*i) != 0) 
	        && ((*i)->getNodeID() == searchID))
	        result = *i;
	    i++;
	}
	if (recursive 
	    && (result == 0))
	{
	    i = children.begin();
	    while ((result == 0) 
	        && (i != children.end()))
	    {
	        if ((*i) != 0)
	            result = (*i)->findChild(searchID, true, level + 1);
	        i++;
	    }
	}
	if (level == 0)
	{
	    // Query has been initiated at this node.
	    if ((result == 0) 
	        && autoCreate)
	    {
	        result = addChild();
	        result->setNodeID(searchID);
	    }
	    // Update index. (This will do nothing if indexes are disabled.)
	    if (result != 0)
	        addIndexEntry(result);
	}
	return result;
}

Ionflux::Template::Node* Node::findChild(const std::string& searchName, 
bool recursive, unsigned int level)
{
	Node* result = getIndexEntry(searchName);
	if (result != 0)
	    return result;
	// Not in index, do a linear search.
	/* <---- DEBUG ----- //
	std::cout << "[Node::findChild{" << nodeName << "}] "
	    "DEBUG: Node not found in index, doing linear search." << std::endl;
	// ----- DEBUG ----> */
	NodeVector::const_iterator i = children.begin();
	while ((result == 0) 
	    && (i != children.end()))
	{
	    if (((*i) != 0) && (*i)->getNodeName() == searchName)
	        result = *i;
	    i++;
	}
	if (recursive 
	    && (result == 0))
	{
	    i = children.begin();
	    while ((result == 0) && (i != children.end()))
	    {
	        if ((*i) != 0)
	            result = (*i)->findChild(searchName, true, level + 1);
	        i++;
	    }
	}
	if (level == 0)
	{
	    // Query has been initiated at this node.
	    if ((result == 0)
	        && autoCreate)
	    {
	        /* <---- DEBUG ----- //
	        std::cout << "[Node::findChild{" << nodeName << "}] DEBUG: "
	            "Node not found! Auto-creating a new node." << std::endl;
	        // ----- DEBUG ----> */
	        result = addChild();
	        result->setNodeName(searchName);
	    }
	    // Update index. (This will do nothing if indexes are disabled.)
	    if (result != 0)
	        /* <---- DEBUG ----- //
	        std::cout << "[Node::findChild{" << nodeName << "}] DEBUG: "
	            "Adding node to index." << std::endl;
	        // ----- DEBUG ----> */
	        addIndexEntry(result);
	}
	return result;
}

Ionflux::Template::Node* Node::findChild(int searchID, bool recursive) 
const
{
	Node *result = getIndexEntry(searchID);
	if (result != 0)
	    return result;
	// Not in index, do a linear search.
	NodeVector::const_iterator i = children.begin();
	while ((result == 0) 
	    && (i != children.end()))
	{
	    if (((*i) != 0) 
	        && ((*i)->getNodeID() == searchID))
	        result = *i;
	    i++;
	}
	if (recursive && (result == 0))
	{
	    i = children.begin();
	    while ((result == 0) 
	        && (i != children.end()))
	    {
	        if ((*i) != 0)
	            result = (*i)->findChild(searchID, true);
	        i++;
	    }
	}
	return result;
}

Ionflux::Template::Node* Node::findChild(const std::string& searchName, 
bool recursive) const
{
	Node *result = getIndexEntry(searchName);
	if (result != 0)
	    return result;
	// Not in index, do a linear search.
	NodeVector::const_iterator i = children.begin();
	while ((result == 0) 
	    && (i != children.end()))
	{
	    if (((*i) != 0) && (*i)->getNodeName() == searchName)
	        result = *i;
	    i++;
	}
	if (recursive && (result == 0))
	{
	    i = children.begin();
	    while ((result == 0) && (i != children.end()))
	    {
	        if ((*i) != 0)
	            result = (*i)->findChild(searchName, true);
	        i++;
	    }
	}
	return result;
}

Ionflux::Template::Node* Node::getChild(unsigned int childIndex) const
{
	if (!validateChildIndex(childIndex))
	    return 0;
	return children[childIndex];
}

bool Node::removeChild(unsigned int childIndex)
{
	if ((childIndex < 0) || (childIndex >= children.size()))
	    return false;
	NodeVector::iterator i = children.begin();
	i += childIndex;
	if ((*i) == 0)
	    throw IFTemplateError("[Node::removeChild] "
	        "Child node pointer is null.");
	removeLocalRef(*i);
	children.erase(i);
	return true;
}

bool Node::removeChild(Ionflux::Template::Node* targetNode, bool recursive)
{
	if ((targetNode == 0) || (children.size() == 0))
	    return false;
	NodeVector::iterator i = children.begin();
	bool found = false;
	while ((i != children.end()) 
	    && !found)
	{
	    if ((*i) == targetNode)
	        found = true;
	    else
	        i++;
	}
	if (found)
	{
	    if ((*i) == 0)
	        throw IFTemplateError("[Node::removeChild] "
	            "Child node pointer is null.");
	    removeLocalRef(*i);
	    children.erase(i);
	} else
	if (recursive)
	{
	    i = children.begin();
	    while ((i != children.end()) 
	        && !found)
	        if ((*i) != 0)
	            found = (*i)->removeChild(targetNode, true);
	}
	return found;
}

void Node::removeAllChildren(bool recursive)
{
	/* <---- DEBUG ----- //
	std::cerr << "[" << getIDString() << "::removeAllChildren] DEBUG: "
	    << "Removing all children." << std::endl;
	// ----- DEBUG ----> */
	NodeVector::iterator i;
	for (i = children.begin(); i != children.end(); i++)
	{
	    if ((*i) != 0)
	    {
	        if (recursive)
	            (*i)->removeAllChildren(true);
	        removeIndexEntries(*i);
	        removeLocalRef(*i);
	    } else
	        throw IFTemplateError("[Node::removeAllChildren] "
	            "Child node pointer is null.");
	}
	nameIndex.clear();
	idIndex.clear();
	children.clear();
}

bool Node::setChild(unsigned int childIndex, Ionflux::Template::Node* 
newChild)
{
	if (newChild == 0)
	    throw IFTemplateError("[Node::setChild] "
	        "Attempt to set null child.");
	if (!validateChildIndex(childIndex))
	    return 0;
	addLocalRef(newChild);
	Node* currentNode = children[childIndex];
	if (currentNode != 0)
	    removeLocalRef(currentNode);
	children[childIndex] = newChild;
	return true;
}

int Node::getChildIndex(Ionflux::Template::Node* targetNode)
{
	if (targetNode == 0)
	    throw IFTemplateError("[Node::setChild] "
	        "Target node is null.");
	unsigned int result = 0;
	bool found = false;
	while ((result < children.size()) 
	    && !found)
	{
	    if (children[result] == targetNode)
	        found = true;
	    else
	        result++;
	}
	if (!found)
	    return -1;
	return result;
}

unsigned int Node::printDebugInfo(int targetLevel, int callingLevel, int 
parentID, int childID)
{
	callingLevel++;
	// callingLevel is now actually the tree depth level of this node.
	if (targetLevel == callingLevel)
	{
	    std::cout << "Node " << parentID << ":" << childID << " (level " 
	        << targetLevel << "):" << std::endl;
	    std::cout << "(this: " << this << ", parent: " << parent << ")" 
	        << std::endl;
	    std::cout << "Name: " << nodeName << std::endl;
	    std::cout << "ID:   " << nodeID << std::endl;
	    std::cout << "Data:" << std::endl;
	    if (nodeData.size() == 0)
	        std::cout << "(empty)" << std::endl;
	    string currentData;
	    for (unsigned int i = 0; i < nodeData.size(); i++)
	    {
	        currentData = getBlob(i);
	        std::cout << "[" << i << "]:" << std::endl 
	            << Ionflux::ObjectBase::makeNiceHex(
	                Ionflux::ObjectBase::makeHex(currentData), 
	                Ionflux::ObjectBase::makeReadable(currentData, "."), 
	                16, 8);
	    }
	    std::cout << std::endl;
	    return 1;
	}
	int result = 0;
	// If this node didn't belong to target level, try the child nodes.
	for (unsigned int i = 0; i < children.size(); i++)
	{
	    if (children[i] != 0)
	        result += children[i]->printDebugInfo(targetLevel, 
	            callingLevel, childID, i);
	}
	return result;
}

unsigned int Node::printDebugInfo(int targetLevel)
{
	// TODO: Implementation.
	return printDebugInfo(targetLevel, -1, 0, 0);;
}

int Node::getUID(bool treeUID)
{
	if (!treeUID || (parent == 0))
	{
	    maxUID++;
	    return maxUID;
	}
	return parent->getUID(true);
}

void Node::traverse(Ionflux::Template::NodeDump* target, 
Ionflux::Template::NodeTraversalMode order)
{
	NodeVector::const_iterator i;
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
	            throw IFTemplateError("[Node::traverse] "
	                "Invalid traversal order for non-binary tree.");
	        break;
	    case TRAVERSAL_PREORDER:
	        if (target != 0)
	            target->dump(this);
	        for (i = children.begin(); i != children.end(); i++)
	            if ((*i) != 0)
	                (*i)->traverse(target, order);
	        break;
	    case TRAVERSAL_POSTORDER:
	        for (i = children.begin(); i != children.end(); i++)
	            if ((*i) != 0)
	                (*i)->traverse(target, order);
	        if (target != 0)
	            target->dump(this);
	        break;
	    default:
	        throw IFTemplateError("[Node::traverse] "
	            "Invalid traversal order.");
	}
}

void Node::serialize(std::string& target)
{
	ostringstream status;
	string nodeBlock;
	// Reserve 24 bytes for later addition of size and checksum.
	nodeBlock.append(24, '\x00');
	// Append node header.
	Ionflux::ObjectBase::pack(static_cast<int32_t>(nodeID), nodeBlock);
	Ionflux::ObjectBase::pack(static_cast<int32_t>(dataType), nodeBlock);
	Ionflux::ObjectBase::pack(static_cast<int32_t>(maxUID), nodeBlock);
	Ionflux::ObjectBase::pack(static_cast<int32_t>(uidMode), nodeBlock);
	Ionflux::ObjectBase::pack(static_cast<uint8_t>(autoCreate), nodeBlock);
	Ionflux::ObjectBase::pack(static_cast<uint32_t>(getNumData()), 
	    nodeBlock);
	Ionflux::ObjectBase::pack(static_cast<uint32_t>(getNumChildren()), 
	    nodeBlock);
	// Append node name block.
	Ionflux::ObjectBase::pack(static_cast<uint32_t>(nodeName.size()), 
	    nodeBlock);
	nodeBlock.append(nodeName);
	// Append data entries.
	for (unsigned int i = 0; i < nodeData.size(); i++)
	{
	    Ionflux::ObjectBase::pack(static_cast<uint32_t>(nodeData[i].size()), 
	        nodeBlock);
	    nodeBlock.append(nodeData[i]);
	}
	// Append child node data blocks.
	Node *currentChild;
	for (unsigned int i = 0; i < children.size(); i++)
	{
	    currentChild = children[i];
	    if (currentChild != 0)
	        currentChild->serialize(nodeBlock);
	    else
	        target.append(1, '\x00');
	}
	// Add block size.
	/* <---- DEBUG ----- //
	status.str("");
	status << "[Node::serialize] DEBUG: "
	    "Node block size: " << nodeBlock.size() << " bytes.";
	std::cout << status.str() << std::endl;
	// ----- DEBUG ----> */
	std::string packed;
	Ionflux::ObjectBase::pack(static_cast<uint32_t>(nodeBlock.size()), 
	    packed);
	nodeBlock.replace(0, 4, packed);
	// Add checksum.
	std::string checkSum = Ionflux::ObjectBase::sha1(nodeBlock);
	nodeBlock.replace(4, 20, checkSum);
	/* <---- DEBUG ----- //
	status.str("");
	status << "[Node::serialize] DEBUG: "
	    "SHA-1 Checksum: " << Ionflux::ObjectBase::makeHex(checkSum);
	std::cout << status.str() << std::endl;
	// ----- DEBUG ----> */
	target.append(nodeBlock);
}

bool Node::unpack(const std::string& serialized, unsigned int blockStart, 
unsigned int blockSize)
{
	if (blockSize == 0)
	    blockSize = serialized.size();
	if ((blockStart + blockSize) > serialized.size())
	{
	    throw IFTemplateError("[Node::unpack] "
	        "Block size mismatch: Serialized data "
	        "block smaller than specified block size.");
	    return false;
	}
	if (blockSize < HEADER_SIZE)
	{
	    throw IFTemplateError("[Node::unpack] "
	        "Block size mismatch: Specified block "
	        "size smaller than size of node header.");
	    return false;
	}
	std::ostringstream status;
	unsigned int currentPos = blockStart;
	// Validate node block size.
	unsigned int nodeBlockSize = unpackInt(serialized.substr(currentPos, 4));
	/* <---- DEBUG ----- //
	std:cerr << "[Node::unpack] DEBUG: Node block size: " << nodeBlockSize 
	    << " bytes." << std::endl;
	// ----- DEBUG ----> */
	if (blockSize < nodeBlockSize)
	{
	    throw IFTemplateError("[Node::unpack] "
	        "Block size mismatch: Serialized data "
	        "block smaller than node block size.");
	}
	// Extract node data block.
	string nodeBlock = serialized.substr(currentPos, nodeBlockSize);
	currentPos = 4;
	// Validate checksum.
	string checkSum = nodeBlock.substr(currentPos, 20);
	string emptyCheckSum(20, '\x00');
	/* <---- DEBUG ----- //
	std::cerr << "[Node::unpack] DEBUG: Node block SHA-1 extracted "
	    "checksum:  " << Ionflux::ObjectBase::makeHex(checkSum) 
	    << std::endl;
	// ----- DEBUG ----> */
	nodeBlock.replace(currentPos, 20, emptyCheckSum);
	string calcCheckSum = Ionflux::ObjectBase::sha1(
	    nodeBlock.substr(0, nodeBlockSize));
	/* <---- DEBUG ----- //
	std::cerr << "[Node::unpack] DEBUG: Node block SHA-1 calculated "
	    "checksum: " + Ionflux::ObjectBase::makeHex(calcCheckSum) 
	    << std::endl;
	// ----- DEBUG ----> */
	if (checkSum != calcCheckSum)
	{
	    throw IFTemplateError("[Node::unpack] "
	        "Checksum mismatch: The node data block "
	        "is probably corrupted.");
	    return false;
	}
	/* <---- DEBUG ----- //
	std::cerr << "[Node::unpack] DEBUG: Checksum OK. :-)" << std::endl;
	// ----- DEBUG ----> */
	currentPos += 20;
	// Extract header fields.
	/* <---- DEBUG ----- //
	log->msg("[Node::unpack] DEBUG: Extracting node header data.", 
	    log->VL_DEBUG_INSANE);
	// ----- DEBUG ----> */
	clear();
	/* <---- DEBUG ----- //
	status.str("");
	status << "[Node::unpack] DEBUG: Extracted header data: ";
	// ----- DEBUG ----> */
	setNodeID(unpackInt(nodeBlock.substr(currentPos, 4)));
	/* <---- DEBUG ----- //
	status << "nodeID = " << getID() << ", ";
	// ----- DEBUG ----> */
	currentPos += 4;
	setDataType(unpackInt(nodeBlock.substr(currentPos, 4)));
	/* <---- DEBUG ----- //
	status << "dataType = " << getDataType() << ", ";
	// ----- DEBUG ----> */
	currentPos += 4;
	maxUID = unpackInt(nodeBlock.substr(currentPos, 4));
	/* <---- DEBUG ----- //
	status << "maxUID = " << maxUID << ", ";
	// ----- DEBUG ----> */
	currentPos += 4;
	setUidMode(unpackInt(nodeBlock.substr(currentPos, 4)));
	/* <---- DEBUG ----- //
	status << "uidMode = " << getUIDMode() << ", ";
	// ----- DEBUG ----> */
	currentPos += 4;
	setAutoCreate(unpackBool(nodeBlock.substr(currentPos, 1)));
	/* <---- DEBUG ----- //
	status << "autoCreate = " << getAutoCreate() << ", ";
	// ----- DEBUG ----> */
	currentPos++;
	unsigned int numData = unpackInt(nodeBlock.substr(currentPos, 4));
	/* <---- DEBUG ----- //
	status << "numData = " << numData << ", ";
	// ----- DEBUG ----> */
	currentPos += 4;
	unsigned int numChildren = unpackInt(nodeBlock.substr(currentPos, 4));
	/* <---- DEBUG ----- //
	status << "numChildren = " << numChildren << ", ";
	// ----- DEBUG ----> */
	currentPos += 4;
	unsigned int nameSize = unpackInt(nodeBlock.substr(currentPos, 4));
	/* <---- DEBUG ----- //
	status << "nameSize = " << nameSize << ", ";
	// ----- DEBUG ----> */
	currentPos += 4;
	setNodeName(nodeBlock.substr(currentPos, nameSize));
	/* <---- DEBUG ----- //
	status << "nodeName = '" << getName() << "'.";
	// ----- DEBUG ----> */
	currentPos += nameSize;
	/* <---- DEBUG ----- //
	log->msg(status.str(), log->VL_DEBUG_INSANE);
	if (numData > 0)
	    log->msg("[Node::unpack] DEBUG: Extracting data entries.", 
	        log->VL_DEBUG_INSANE);
	// ----- DEBUG ----> */
	// Extract data.
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
	    /* <---- DEBUG ----- //
	    status.str("");
	    status << "[Node::unpack] DEBUG: Data entry [" << i 
	        << "]: size = " << dataSize << ", value = " 
	        << makeHex(getData(i));
	    log->msg(status.str(), log->VL_DEBUG_INSANE);
	    // ----- DEBUG ----> */
	    currentPos += dataSize;
	}
	// Extract child nodes.
	/* <---- DEBUG ----- //
	if (numChildren > 0)
	    log->msg("[Node::unpack] DEBUG: Extracting child nodes.", 
	        log->VL_DEBUG_INSANE);
	// ----- DEBUG ----> */
	Node *currentChild;
	unsigned int childBlockSize;
	unsigned int childCount = 0;
	bool unpackOK = true;
	while((childCount < numChildren) && unpackOK)
	{
	    childBlockSize = unpackInt(nodeBlock.substr(currentPos, 4));
	    /* <---- DEBUG ----- //
	    status.str("");
	    status << "[Node::unpack] DEBUG: Child node [" << childCount 
	        << "]: blockSize = " << childBlockSize;
	    log->msg(status.str(), log->VL_DEBUG_INSANE);
	    // ----- DEBUG ----> */
	    if (childBlockSize == 0)
	    {
	        /* <---- DEBUG ----- //
	        log->msg("[Node::unpack] DEBUG: Adding child node (null).", 
	            log->VL_DEBUG_INSANE);
	        // ----- DEBUG ----> */
	        addChild(Node::create());
	        currentPos += 4;
	    } else
	    {
	        /* <---- DEBUG ----- //
	        log->msg("[Node::unpack] DEBUG: Unpacking child node.", 
	            log->VL_DEBUG_INSANE);
	        // ----- DEBUG ----> */
	        currentChild = addChild();
	        unpackOK = currentChild->unpack(nodeBlock, currentPos, 
	            childBlockSize);
	        if (unpackOK)
	        {
	            /* <---- DEBUG ----- //
	            log->msg("[Node::unpack] DEBUG: Child node unpacked "
	                "successfully.", log->VL_DEBUG_INSANE);
	            // ----- DEBUG ----> */
	        } else
	        {
	            status.str("");
	            status << "[Node::unpack] Child node [" << childCount 
	                << "]: Unpacking failed!";
	            throw IFTemplateError(status.str());
	        }
	        currentPos += childBlockSize;
	    }
	    childCount++;
	}
	/* <---- DEBUG ----- //
	log->msg("[Node::unpack] DEBUG: Unpacking finished.", 
	log->VL_DEBUG_INSANE);
	if (!unpackOK)
	    log->msg("[Node::unpack] DEBUG: Some child nodes could not be "
	        "unpacked.", log->VL_DEBUG_INSANE);
	// ----- DEBUG ----> */
	return unpackOK;
}

void Node::convertToNativeType()
{
	if (dataType != DATA_BLOB)
	        return;
	    string data = getBlob();
	    if (Ionflux::ObjectBase::isInteger(data))
	    {
	        setDataType(DATA_INT);
	        int intData;
	        for (unsigned int i = 0; i < getNumData(); i++)
	        {
	            data = getBlob(i);
	            intData = strtol(data.c_str(), 0, 10);
	            setData(i, intData);
	        }
	    } else
	    if (Ionflux::ObjectBase::isFloat(data))
	    {
	        setDataType(DATA_DOUBLE);
	        for (unsigned int i = 0; i < getNumData(); i++)
	        {
	            data = getBlob(i);
	            setData(i, strtod(data.c_str(), 0));
	        }
	    }
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

Ionflux::Template::Node* Node::copy(Ionflux::Template::Node& target, 
unsigned int maxDepth, unsigned int currentDepth) const
{
	if (&target == this)
	    return &target;
	bool origAutoCreate = getAutoCreate();
	Node* currentChild = 0;
	Node* currentSourceChild = 0;
	// Clear the node.
	target.clearData(false);
	target.removeAllChildren(false);
	target.setDataType(getDataType());
	target.setUidMode(getUidMode());
	// NOTE: Why is maxUID reset here?
	//maxUID = getUID(false);
	// Set auto-create for copying data entries and child nodes.
	target.setAutoCreate(true);
	// Copy data entries.
	for (unsigned int i = 0; i < getNumData(); i++)
	    target.setBlob(i, getBlob(i));
	if ((maxDepth > 0)
	    && (currentDepth >= maxDepth))
	{
	    target.setAutoCreate(origAutoCreate);
	    return &target;
	}
	// Copy child nodes.
	for (unsigned int i = 0; i < getNumChildren(); i++)
	{
	    currentSourceChild = getChild(i);
	    if (currentSourceChild != 0)
	    {
	        currentChild = target.addChild();
	        /* <---- DEBUG ----- //
	        std::cerr << "[Node::copy] DEBUG: "
	            "Created node " << currentChild << std::endl;
	        // ----- DEBUG ----> */
	        // Name and ID must be set explicitly.
	        currentChild->setNodeName(currentSourceChild->getNodeName());
	        currentChild->setNodeID(currentSourceChild->getNodeID());
	        currentSourceChild->copy(*currentChild, maxDepth, 
	            currentDepth + 1);
	    }
	}
	target.setAutoCreate(origAutoCreate);
	return &target;
}

Ionflux::Template::Node& Node::operator[](int searchID)
{
	bool lastAutoCreate = getAutoCreate();
	setAutoCreate(true);
	Node *result = findChild(searchID, false);
	setAutoCreate(lastAutoCreate);
	return *result;
}

Ionflux::Template::Node& Node::operator[](const std::string& searchName)
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

std::string Node::getData() const
{
	// TODO: Implementation.
	return getData(0);
}

std::string Node::getBlob() const
{
	// TODO: Implementation.
	return getBlob(0);
}

int Node::getInt() const
{
	// TODO: Implementation.
	return getInt(0);
}

double Node::getDouble() const
{
	// TODO: Implementation.
	return getDouble(0);
}

unsigned int Node::getNumData() const
{
	// TODO: Implementation.
	return nodeData.size();
}

unsigned int Node::getNumChildren(bool recursive) const
{
	unsigned int result = children.size();
	if (recursive)
	{
	    NodeVector::const_iterator i;
	    for (i = children.begin(); i != children.end(); i++)
	    {
	        if ((*i) != 0) 
	            result += (*i)->getNumChildren(true);
	    }
	}
	return result;
}

std::string Node::getPath()
{
	std::string result;
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
	    if (nodeID != ID_NOT_SET)
	    {
	        /* Use subscripting for IDs. (Resolution operator could be used 
	           as well.) */
	        ostringstream status;
	        status << "[" << nodeID << "]";
	        result.append(status.str());
	    } else
	    {
	        throw IFTemplateError("[Node::getPath] "
	            "Unable to create path for unnamed "
	            "node without ID.");
	    }
	}
	return result;
}

void Node::clear()
{
	clearData(false);
	removeAllChildren(false);
}

Ionflux::Template::Node& Node::merge(Ionflux::Template::Node& sourceNode, 
bool replace, unsigned int maxDepth, unsigned int currentDepth)
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
	        srcChildID = currentSourceChild->getNodeID();
	        srcChildName = currentSourceChild->getNodeName();
	        if (srcChildID != ID_NOT_SET)
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
	            currentChild->setNodeName(currentSourceChild->getNodeName());
	            currentChild->setNodeID(currentSourceChild->getNodeID());
	            currentSourceChild->copy(*currentChild, maxDepth, 
	                currentDepth + 1);
	        }
	    }
	}
	setAutoCreate(origAutoCreate);
	return *this;
}

bool Node::combine(unsigned int from, unsigned int to, 
Ionflux::Template::Node& target)
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
	std::ostringstream status;
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
	    if (Ionflux::ObjectBase::isIdentifier(nodeName))
	        // Simple name (identifier).
	        status << nodeName << " = ";
	    else
	        // Complex name, use subscript.
	        status << "[\"" << Ionflux::ObjectBase::escape(nodeName, "\"") 
	            << "\"] = ";
	    nestedContext = true;
	} else
	if (nodeID != ID_NOT_SET)
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
	        status << Ionflux::ObjectBase::escape(getData(0), "{}\n") << "\n";
	    else
	        /* Rare case of a root node with only one data entry, but 
	           still possible. */
	       status << "'" << Ionflux::ObjectBase::escape(getData(0), "'{}\n") 
	           << "'\n";
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
	    status << "'" << Ionflux::ObjectBase::escape(getData(i), "'{}\n") 
	        << "'\n";
	}
	// Add child nodes.
	Node *currentChild;
	for (unsigned int i = 0; i < children.size(); i++)
	{
	    currentChild = children[i];
	    status << currentChild->toConfig(indent, level + 1);
	}
	if (nestedContext)
	    status << levelIndent << "}\n";
	return status.str();
}

void Node::setNodeID(Ionflux::Template::NodeID newNodeID)
{
	int oldID = nodeID;
	nodeID = newNodeID;
	if (parent != 0)
	{
	    parent->removeIndexEntry(oldID);
	    parent->addIndexEntry(this);
	}
}

Ionflux::Template::NodeID Node::getNodeID() const
{
    return nodeID;
}

void Node::setNodeName(const std::string& newNodeName)
{
	string oldName = nodeName;
	nodeName = newNodeName;
	if (parent != 0)
	{
	    parent->removeIndexEntry(oldName);
	    parent->addIndexEntry(this);
	}
}

std::string Node::getNodeName() const
{
    return nodeName;
}

void Node::setDataType(Ionflux::Template::NodeDataTypeID newDataType)
{
	dataType = newDataType;
}

Ionflux::Template::NodeDataTypeID Node::getDataType() const
{
    return dataType;
}

void Node::setParent(Ionflux::Template::Node* newParent)
{
	parent = newParent;
}

Ionflux::Template::Node* Node::getParent() const
{
    return parent;
}

void Node::setMaxUID(Ionflux::Template::NodeID newMaxUID)
{
	maxUID = newMaxUID;
}

Ionflux::Template::NodeID Node::getMaxUID() const
{
    return maxUID;
}

void Node::setUidMode(Ionflux::Template::NodeUIDMode newUidMode)
{
	uidMode = newUidMode;
}

Ionflux::Template::NodeUIDMode Node::getUidMode() const
{
    return uidMode;
}

void Node::setAutoCreate(bool newAutoCreate)
{
	autoCreate = newAutoCreate;
}

bool Node::getAutoCreate() const
{
    return autoCreate;
}

void Node::setIndexMode(Ionflux::Template::NodeIndexMode newIndexMode)
{
	indexMode = newIndexMode;
}

Ionflux::Template::NodeIndexMode Node::getIndexMode() const
{
    return indexMode;
}

Ionflux::Template::Node& Node::operator=(const Ionflux::Template::Node& 
other)
{
    other.copy(*this);
	return *this;
}

Ionflux::Template::Node* Node::copy() const
{
    Node* newNode = create();
    *newNode = *this;
    return newNode;
}

Ionflux::Template::Node* Node::upcast(Ionflux::ObjectBase::IFObject* other)
{
    return dynamic_cast<Node*>(other);
}

Ionflux::Template::Node* Node::create(Ionflux::ObjectBase::IFObject* 
parentObject)
{
    Node* newObject = new Node();
    if (newObject == 0)
    {
        throw IFTemplateError("Could not allocate object.");
    }
    if (parentObject != 0)
        parentObject->addLocalRef(newObject);
    return newObject;
}

Ionflux::Template::Node* Node::create(Ionflux::Template::Node* initParent, 
Ionflux::ObjectBase::IFObject* parentObject)
{
    Node* newObject = new Node(initParent);
    if (newObject == 0)
    {
        throw IFTemplateError("Could not allocate object.");
    }
    if (parentObject != 0)
        parentObject->addLocalRef(newObject);
    return newObject;
}

Ionflux::Template::Node* Node::create(Ionflux::Template::Node* initParent, 
Ionflux::Template::NodeID initID, const std::string& initName, 
Ionflux::Template::NodeDataTypeID initDataType, 
Ionflux::ObjectBase::IFObject* parentObject)
{
    Node* newObject = new Node(initParent, initID, initName, initDataType);
    if (newObject == 0)
    {
        throw IFTemplateError("Could not allocate object.");
    }
    if (parentObject != 0)
        parentObject->addLocalRef(newObject);
    return newObject;
}

}

}

/** \file Node.cpp
 * \brief Tree node implementation.
 */
