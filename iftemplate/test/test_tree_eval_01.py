#!/usr/bin/env python3
# -*- coding: utf-8 -*-
"""Ionflux Template Processor test script."""
import IFObjectBase as ib
import IFTemplate as it

testName = "TreeEval 01"

# memory management
mm = ib.IFObject()

print("Ionflux Template Processor test script: " + testName)

configData0 = """
a = 5
b = 7
foo = Hello
bar = {
  gnap = Miep
  gnaz = Blubb
}
"""

expressions0 = [
    "a + b", 
    "foo + ' ' + bar.gnap", 
    "a + '_' + bar.gnaz"
]

config0 = it.ConfigTree.create()
mm.addLocalRef(config0)
config0.parseConfig(configData0)

print("  Data:")
print(config0.getRoot().toConfig("  ", 2))

k = 0
for ce in expressions0:
    print("  [%02d]\n    Expression:  '%s'" % (k + 1, str(ce)))
    
    elements0 = it.TreeExprElementVector()
    it.TreeEval.parseTreeExpr(ce, elements0)
    
    result0 = it.Node.create()
    result0.setAutoCreate(True)
    result0.setIndexMode(it.Node.INDEX_MODE_NODE)
    result0.setDataType(it.Node.DATA_INT)
    
    mm.addLocalRef(result0)
    
    if (not (it.TreeEval.eval(config0, elements0, result0, True))):
        print("    ERROR: Could not evaluate tree expression!")
    else:
        print("    Result:      " + str(result0.toConfig()))
    
    mm.removeLocalRef(result0)
    k += 1

print("All done!")
