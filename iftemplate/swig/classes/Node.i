/* ==========================================================================
 * IFTemplate - Ionflux Template Processor
 * Copyright © 2012 Jörn P. Meier
 * mail@ionflux.org
 * --------------------------------------------------------------------------
 * Node.i                          Tree node (interface).
 * =========================================================================

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
%{
#include "iftemplate/Node.hpp"
%}

namespace Ionflux
{

namespace Template
{

class NodeDump;

class NodeClassInfo
: public Ionflux::ObjectBase::IFClassInfo
{
    public:
        NodeClassInfo();
        virtual ~NodeClassInfo();
};

class Node
: public Ionflux::ObjectBase::IFObject
{
    public:
		static const Ionflux::Template::NodeID ID_NOT_SET;
		static const Ionflux::Template::NodeDataTypeID DATA_BLOB;
		static const Ionflux::Template::NodeDataTypeID DATA_INT;
		static const Ionflux::Template::NodeDataTypeID DATA_DOUBLE;
		static const Ionflux::Template::NodeUIDMode UID_MODE_NONE;
		static const Ionflux::Template::NodeUIDMode UID_MODE_NODE;
		static const Ionflux::Template::NodeUIDMode UID_MODE_TREE;
		static const Ionflux::Template::NodeTraversalMode TRAVERSAL_INORDER;
		static const Ionflux::Template::NodeTraversalMode TRAVERSAL_PREORDER;
		static const Ionflux::Template::NodeTraversalMode TRAVERSAL_POSTORDER;
		static const unsigned int HEADER_SIZE;
		static const Ionflux::Template::NodeIndexMode INDEX_MODE_NONE;
		static const Ionflux::Template::NodeIndexMode INDEX_MODE_NODE;
		static const Ionflux::Template::NodeIndexMode INDEX_MODE_TREE;
		static const unsigned int MAX_ID_INDEX_SIZE;
        
        Node();
		Node(const Ionflux::Template::Node& other);
        Node(Ionflux::Template::Node* initParent);
        Node(Ionflux::Template::Node* initParent, Ionflux::Template::NodeID
        initID, const std::string& initName = "", 
        Ionflux::Template::NodeDataTypeID initDataType = DATA_BLOB);
        virtual ~Node();
        virtual int addData(const std::string& newData);
        virtual int addData(int newData);
        virtual int addData(double newData);
        virtual bool setBlob(unsigned int dataIndex, const std::string& 
        newData);
        virtual bool setData(unsigned int dataIndex, const std::string& 
        newData);
        virtual bool setData(unsigned int dataIndex, int newData);
        virtual bool setData(unsigned int dataIndex, unsigned int newData);
        virtual bool setData(unsigned int dataIndex, double newData);
        virtual bool setData(const std::string& newData);
        virtual bool setData(int newData);
        virtual bool setData(unsigned int newData);
        virtual bool setData(double newData);
        virtual std::string getData(unsigned int dataIndex) const;
        virtual std::string getBlob(unsigned int dataIndex) const;
        virtual int getInt(unsigned int dataIndex) const;
        virtual double getDouble(unsigned int dataIndex) const;
        virtual bool removeData(unsigned int dataIndex);
        virtual bool clearData(bool recursive);
        virtual Ionflux::Template::Node* addChild(Ionflux::Template::NodeID
        childID = ID_NOT_SET, const std::string& childName = "");
        virtual void addChild(Ionflux::Template::Node* newChild);
        virtual Ionflux::Template::Node* findChild(int searchID, bool 
        recursive = false, unsigned int level = 0);
        virtual Ionflux::Template::Node* findChild(const std::string& 
        searchName, bool recursive = false, unsigned int level = 0);
        virtual Ionflux::Template::Node* findChild(int searchID, bool 
        recursive = false) const;
        virtual Ionflux::Template::Node* findChild(const std::string& 
        searchName, bool recursive = false) const;
        virtual Ionflux::Template::Node* getChild(unsigned int childIndex) 
        const;
        virtual bool removeChild(unsigned int childIndex);
        virtual bool removeChild(Ionflux::Template::Node* targetNode, bool 
        recursive = false);
        virtual void removeAllChildren(bool recursive = false);
        virtual bool setChild(unsigned int childIndex, 
        Ionflux::Template::Node* newChild);
        virtual int getChildIndex(Ionflux::Template::Node* targetNode);
        virtual unsigned int printDebugInfo(int targetLevel, int 
        callingLevel, int parentID, int childID);
        virtual unsigned int printDebugInfo(int targetLevel);
        virtual int getUID(bool treeUID);
        virtual void traverse(Ionflux::Template::NodeDump* target, 
        Ionflux::Template::NodeTraversalMode order);
        virtual void serialize(std::string& target);
        virtual bool unpack(const std::string& serialized, unsigned int 
        blockStart, unsigned int blockSize);
        virtual void convertToNativeType();
        virtual void clearNameIndex();
        virtual void clearIDIndex();
        virtual void clearIndexes();
        virtual Ionflux::Template::Node* copy(Ionflux::Template::Node& 
        target, unsigned int maxDepth = 0, unsigned int currentDepth = 0) 
        const;
        virtual std::string getData() const;
        virtual std::string getBlob() const;
        virtual int getInt() const;
        virtual double getDouble() const;
        virtual unsigned int getNumData() const;
        virtual unsigned int getNumChildren(bool recursive = false) const;
        virtual std::string getPath();
        virtual void clear();
        virtual Ionflux::Template::Node& merge(Ionflux::Template::Node& 
        sourceNode, bool replace = false, unsigned int maxDepth = 0, 
        unsigned int currentDepth = 0);
        virtual bool combine(unsigned int from, unsigned int to, 
        Ionflux::Template::Node& target);
        virtual std::string toConfig(const std::string& indent = "  ", 
        unsigned int level = 0);
		virtual Ionflux::Template::Node* copy() const;
		static Ionflux::Template::Node* upcast(Ionflux::ObjectBase::IFObject* 
		other);
		static Ionflux::Template::Node* create(Ionflux::ObjectBase::IFObject* 
		parentObject = 0);
		static Ionflux::Template::Node* create(Ionflux::Template::Node* 
		initParent, Ionflux::ObjectBase::IFObject* parentObject = 0);
		static Ionflux::Template::Node* create(Ionflux::Template::Node* 
		initParent, Ionflux::Template::NodeID initID, const std::string& initName
		= "", Ionflux::Template::NodeDataTypeID initDataType = DATA_BLOB, 
		Ionflux::ObjectBase::IFObject* parentObject = 0);
        virtual void setNodeID(Ionflux::Template::NodeID newNodeID);
        virtual Ionflux::Template::NodeID getNodeID() const;
        virtual void setNodeName(const std::string& newNodeName);
        virtual std::string getNodeName() const;
        virtual void setDataType(Ionflux::Template::NodeDataTypeID 
        newDataType);
        virtual Ionflux::Template::NodeDataTypeID getDataType() const;
        virtual void setParent(Ionflux::Template::Node* newParent);
        virtual Ionflux::Template::Node* getParent() const;
        virtual void setMaxUID(Ionflux::Template::NodeID newMaxUID);
        virtual Ionflux::Template::NodeID getMaxUID() const;
        virtual void setUidMode(Ionflux::Template::NodeUIDMode newUidMode);
        virtual Ionflux::Template::NodeUIDMode getUidMode() const;
        virtual void setAutoCreate(bool newAutoCreate);
        virtual bool getAutoCreate() const;
        virtual void setIndexMode(Ionflux::Template::NodeIndexMode 
        newIndexMode);
        virtual Ionflux::Template::NodeIndexMode getIndexMode() const;
};

}

}
