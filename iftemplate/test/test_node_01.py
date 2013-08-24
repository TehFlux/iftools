#!/usr/bin/env python3
# -*- coding: utf-8 -*-
"""Ionflux Template Processor test script."""
import IFObjectBase as ib
import IFTemplate as it

testName = "Node 01"

# memory management
mm = ib.IFObject()

print("Ionflux Template Processor test script: " + testName)

print("  Creating nodes...")

k = 1

n0 = it.Node.create(None, k, "Node 01")
k += 1

n0.setAutoCreate(True)
n0.setIndexMode(it.Node.INDEX_MODE_NODE)

n1 = n0.addChild()
n1.setNodeID(k)
k += 1
n1.setNodeName('Node01_01')
n1.setID('Node01_01')
n1.setData("blupp")

n2 = n0.addChild()
n2.setNodeID(k)
k += 1
n2.setNodeName('Node01_02')
n2.setID('Node01_02')
n2.setDataType(it.Node.DATA_INT)
n2.setData(2)

n3 = n0.addChild()
n3.setNodeID(k)
k += 1
n3.setNodeName('Node01_03')
n3.setID('Node01_03')
n3.setAutoCreate(True)
n3.setIndexMode(it.Node.INDEX_MODE_NODE)

n4 = n3.addChild()
n4.setNodeID(k)
k += 1
n4.setNodeName('Node01_03_01')
n4.setID('Node01_03_01')
n4.setData("miep")

n5 = n3.addChild()
n5.setNodeID(k)
k += 1
n5.setNodeName('Node01_03_02')
n5.setID('Node01_03_02')
n5.setDataType(it.Node.DATA_DOUBLE)
n5.setData(2.4)

nodes = [ n0, n1, n2, n3, n4, n5 ]

for n in nodes:
    print("  Node (id = " + str(n.getNodeID()) + ", name = '"  
        + str(n.getNodeName()) + "', dataType = " + str(n.getDataType()) 
        + "):")
    print(n.toConfig("  ", 0))

searchNode = n4
print("  Finding node '" + searchNode.getNodeName() + "':")
sn0 = n0.findChild(searchNode.getNodeName(), True)
if (sn0 is None):
    print("    Not found!")
else:
    print("    Found (id = " + str(sn0.getNodeID()) + ", name = '"  
        + str(sn0.getNodeName()) + "', dataType = " + str(sn0.getDataType()) 
        + "):")
    print(sn0.toConfig("  ", 0))
    #print(str(sn0.getNumData()))
    #print(sn0.getData(0))

print("All done!")
