#!/usr/bin/env python3
# -*- coding: utf-8 -*-
"""Ionflux Template Processor test script."""
import IFObjectBase as ib
import IFTemplate as it

testName = "Template 01"

# memory management
mm = ib.IFObject()

print("Ionflux Template Processor test script: " + testName)

configData0 = """
a = 5
b = {
    'Miep'
    'Blupp'
    'Gnap'
}
"""

templates0 = [
    """{section showA}      a: {$a = a + 6}{$a}{/section}{foreach x in b}      {$x}
{/foreach}{ref showA}"""
]

config0 = it.ConfigTree.create()
mm.addLocalRef(config0)
config0.parseConfig(configData0)

print("  Data:")
print(config0.getRoot().toConfig("  ", 2))

k = 0
for cd in templates0:
    print("  [%02d]\n    Template:" % (k + 1))
    print(str(cd))
    
    tpl = it.Template.create()
    mm.addLocalRef(tpl)
    tpl.setTemplate(cd)
    tpl.setID("Blah")
    #rn0 = tpl.getRoot()
    #rn0.setID("TemplateRoot01")
    tpl.setRoot(config0.getRoot())
    
    r0 = tpl.process()
    
    print("    Result:")
    print(str(r0))
    
    mm.removeLocalRef(tpl)
    k += 1

mm.removeLocalRef(config0)

print("All done!")
