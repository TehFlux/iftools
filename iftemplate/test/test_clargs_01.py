#!/usr/bin/env python3
# -*- coding: utf-8 -*-
"""Ionflux Template Processor test script."""
import IFObjectBase as ib
import IFTemplate as it

testName = "CLArgs 01"

# memory management
mm = ib.IFObject()

print("Ionflux Template Processor test script: " + testName)

args0 = [
    [ 'foo', '-a', '-bc', '--foo', 'Miep', 'Blupp=foo', 'Gnap' ]
]

cl0 = it.CLArgs.create()
mm.addLocalRef(cl0)

k = 0
for ca in args0:
    print("  [%02d]\n    Args:  '%s'" % (k + 1, str(ca)))
    
    a0 = ib.StringVector()
    for it in ca:
        a0.push_back(it)
    
    cl0.setArgs(a0)
    
    cl0.printDebugInfo()
    
    k += 1

print("All done!")
