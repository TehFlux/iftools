#!/usr/bin/env python3
# -*- coding: utf-8 -*-
"""Ionflux Object Base System test."""
import os, math
import IFObjectBase as ib

print("Ionflux Object Base System test 01.")

cacheSize = 5
maxItems = 8
fetch = [
    'item01', 'item04', 'item04', 'item02', 'item01', 'item04', 'item03'
]
hits = [
    5, 0, 1, 2, 0, 1, 2
]

print ("  Testing IFCache...")

c0 = ib.IFCache()
c0.setMaxSize(cacheSize)
#c0.setPolicy(ib.IFCache.POLICY_KEEP_RECENT)

print ("    Adding items...")
for i in range(0, cacheSize):
    id0 = "item%02d" % (i + 1)
    it0 = ib.IFObject.create()
    it0.setID(id0)
    print(("      #%02d: " % (i + 1)) + str(it0))
    c0.addItem(id0, it0)

print ("    Fetching items from the cache...")
k = 0
for it in fetch:
    it0 = c0.getItem(it)
    print(("      #%02d: " % (k + 1)) + str(it0))
    k += 1

print ("    Cache state:")
print(c0.getDebugInfo())

print ("    Adding more items...")
for i in range(cacheSize, maxItems):
    k = i - cacheSize
    h = 0
    if (k < len(hits)):
        h = hits[k]
    id0 = "item%02d" % (i + 1)
    it0 = ib.IFObject.create()
    it0.setID(id0)
    print(("      #%02d: " % (i + 1)) + str(it0))
    c0.addItem(id0, it0, h)
    print ("    Cache state:")
    print(c0.getDebugInfo())

print("All done!")
