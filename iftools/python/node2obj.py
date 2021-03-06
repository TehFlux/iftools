#!/usr/bin/python
# -*- coding: utf-8 -*-
"""Convert an Ionflux Tools node hierarchy to a python object hierarchy. Also 
has some tools to do the reverse."""

import hashlib, IFTools

DATA_LIST_KEY = "__data"
"""Dictionary entry to denote list of data entries."""

class N2OError(Exception):
    """Generic exception for Node2Object errors."""
    value = ""
    """Value which is reported with the exception."""
    
    def __init__(self, value = ""):
        self.value = value
    
    def __str__(self):
        return self.value
    
    def __repr__(self):
        return "N2OError(" + repr(self.value) + ")"

def isIdentifier(text):
    """Check whether text is an identifier.
    
    Returns True if text is an identifier, False otherwise."""
    idChars = "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789_"
    for c in text:
        if (not c in idChars):
            return False
    return True

class Node:
    """Ionflux Tools Node.
    
    This object represents an Ionflux Tools node. Child nodes are available in 
    the childNodes attribute, data is available in the data attribute. If a 
    child node has a name which is an identifier, an attribute will be added to 
    the parent node. This attribute will reference either the node itself (if 
    the node has child nodes of its own) or the data entries of that node (if 
    the node is a leaf)."""
    childNodes = []
    """List of child nodes."""
    childNodesByName = {}
    """Dictionary of child nodes, indexed by name."""
    childNodesByID = {}
    """Dictionary of child nodes, indexed by ID."""
    data = []
    """Data vector."""
    name = ""
    """Name."""
    nodeID = 0
    """ID."""
    
    def __init__(self, name = "", nodeID = IFTools.Node.NODE_ID_NOT_SET,
        initData = None, initChildNodes = None, initNode = None):
        self.name = name
        self.nodeId = nodeID
        if (not initData is None):
            self.data = initData
        if (not initChildNodes is None):
            self.childNodes = initChildNodes
            self.updateIndexes()
        if (not initNode is None):
            self.setFromIFToolsNode(initNode)
    
    def updateIndexes(self):
        """Update child node indexes."""
        self.childNodesByName = {}
        self.childNodesByID = {}
        for c in self.childNodes:
            if (len(c.name) > 0):
                self.childNodesByName[c.name] = c
                if (isIdentifier(c.name)
                    and not hasattr(self, c.name)):
                    if (len(c.childNodes) > 0):
                        # Child node is not a leaf.
                        setattr(self, c.name, c)
                    else:
                        # Child node is a leaf.
                        if (len(c.data) == 1):
                            # Only one data entry.
                            setattr(self, c.name, c.data[0])
                        else:
                            # Several data entries.
                            setattr(self, c.name, c.data)
            if (c.nodeID != IFTools.Node.NODE_ID_NOT_SET):
                self.childNodesByID[c.name] = c
    
    def setFromIFToolsNode(self, node):
        """Initialize node hierarchy from Ionflux Tools node."""
        self.name = node.getName()
        self.nodeID = node.getID()
        # <---- DEBUG -----
        #print ("[Node.setFromIFToolsNode] DEBUG: "
        #    "name = '" + self.name + "', id = " + str(self.nodeID))
        # <---- DEBUG ---->
        # Process data entries.
        self.data = []
        dataType = node.getDataType()
        if (dataType == IFTools.Node.NODE_DATA_INT):
            for i in range(0, node.getNumData()):
                self.data += [ node.getInt(i) ]
        elif (dataType == IFTools.Node.NODE_DATA_DOUBLE):
            for i in range(0, node.getNumData()):
                self.data += [ node.getDouble(i) ]
        elif (dataType == IFTools.Node.NODE_DATA_BLOB):
            for i in range(0, node.getNumData()):
                self.data += [ node.getData(i) ]
        # <---- DEBUG -----
        #i = 0
        #for it in self.data:
        #    print ("[Node.setFromIFToolsNode] DEBUG: "
        #        "data[" + str(i) + "] = '" + str(it) + "')")
        # <---- DEBUG ---->
        # Process child nodes.
        self.childNodes = []
        for i in range(0, node.getNumChildren()):
            c = node.getChild(i)
            cn = Node()
            cn.setFromIFToolsNode(c)
            self.childNodes += [ cn ]
        self.updateIndexes()
        return True
    
    def setFromConfigFile(self, fileName):
        """Initialize node hierarchy from Ionflux Tools configuration file."""
        c = IFTools.ConfigTree()
        c.readConfig(fileName)
        r = c.getRoot()
        self.setFromIFToolsNode(r)
    
    def getMD5Hash(self):
        """Get MD5 hash for the node."""
        h = hashlib.md5()
        for it in self.data:
            h.update(str(it))
        for cn in self.childNodes:
            h.update(cn.getMD5Hash())
        return h.hexdigest()
    
    def __str__(self):
        return "Node['" + str(self.name) + "', " + str(self.nodeID) + "]"
    
    def __repr__(self):
        r = "Node(" + repr(self.name) + ", " + repr(self.nodeID) + ", [\n"
        i = 0
        for d in self.data:
            if (i > 0):
                r += ",\n"
            r += repr(d)
            i += 1
        r += "    ], [\n"
        i = 0
        for c in self.childNodes:
            if (i > 0):
                r += ",\n"
            r += repr(c)
            i += 1
        r += "])\n"
        return r
    
    @classmethod
    def getConfig(cls, fileName):
        """Get IFTools configuration tree."""
        c = IFTools.ConfigTree()
        c.readConfig(fileName)
        return c
    
    @classmethod
    def initFromPyObject(cls, node, obj):
        """Initialize IFTools node from Python object.
        
        Initialize an IFTools node hierarchy from a hierarchy of native 
        python objects. This works as follows:
        
        If the object is a dictionary, it is treated as a set of named child 
        nodes. If there is an entry with key DATA_LIST_KEY ("__data" by 
        default) and a list value, this entry is treated as the vector of data 
        entries sof the current node.
        
        If the object is a list, it is treated as a set of unnamed child 
        nodes.
        
        If the object is either one of string, int or float, it is treated as 
        a data entry.
        
        Nodes are processed recursively in this fashion to yield a hierarchy 
        of nodes, with the specified node itself as the root node. Returns 
        the root node."""
        node.setAutoCreate(True)
        node.setIndexMode(IFTools.Node.INDEX_MODE_NODE)
        if (isinstance(obj, dict)):
            # Dictionary of named child nodes and maybe a data entry list.
            for k in obj:
                it = obj[k]
                if ((k == DATA_LIST_KEY)
                    and isinstance(it, list)):
                    # Data entry list.
                    for i in range(0, len(it)):
                        d = it[i]
                        dataType = IFTools.Node.NODE_DATA_BLOB
                        if (isinstance(d, int)):
                            dataType = IFTools.Node.NODE_DATA_INT
                        elif (isinstance(d, float)):
                            dataType = IFTools.Node.NODE_DATA_DOUBLE
                        else:
                            raise N2OError("Unknown data type for item: " 
                                + str(d))
                        if (i == 0):
                            # Set node data type on first item.
                            node.setDataType(dataType)
                        # Set data entry.
                        if (dataType == IFTools.Node.NODE_DATA_BLOB):
                            node.setData(i, d)
                        elif (dataType == IFTools.Node.NODE_DATA_INT):
                            node.setInt(i, d)
                        elif (dataType == IFTools.Node.NODE_DATA_DOUBLE):
                            node.setDouble(i, d)
                else:
                    # Named child node.
                    cn = node.findChild(k)
                    cls.initFromPyObject(cn, it)
        elif (isinstance(obj, list)):
            # List of unnamed child nodes.
            for it in obj:
                cn = node.addChild()
                cls.initFromPyObject(cn, it)
        else:
            # Data entry.
            if (isinstance(obj, str)):
                node.setDataType(IFTools.Node.NODE_DATA_BLOB)
                node.setData(0, obj)
            elif (isinstance(obj, int)):
                node.setDataType(IFTools.Node.NODE_DATA_INT)
                node.setInt(0, obj)
            elif (isinstance(obj, float)):
                node.setDataType(IFTools.Node.NODE_DATA_DOUBLE)
                node.setDouble(0, obj)
            else:
                raise N2OError("Unknown data type for item: " 
                    + str(obj))
        return node

