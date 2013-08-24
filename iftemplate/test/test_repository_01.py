#!/usr/bin/env python3
# -*- coding: utf-8 -*-
"""Ionflux Template Processor test script."""
import IFObjectBase as ib
import IFTemplate as it

testName = "TemplateRepository 01"

# memory management
mm = ib.IFObject()

print("Ionflux Template Processor test script: " + testName)

templatePaths = [
    'test/template'
]

templateData = [
    [ 'blah.blupp', '{$blah}' ], 
    [ 'main', """{import miep}
{import blah.blupp}
""" ]
]

testModules = [
    'foo.print_foo', 
    'miep', 
    'bar', 
    'blah.blupp', 
    'main'
]

configData0 = """
foo = {
    'Miep'
    'Blupp'
    'Gnap'
}
bar = 5
blah = Gnaz
"""

config0 = it.ConfigTree.create()
mm.addLocalRef(config0)
config0.parseConfig(configData0)

print("  Configuration data:")
print(config0.getRoot().toConfig("  ", 2))

tr0 = it.TemplateRepository.create()
for cp in templatePaths:
    print("  Adding template path: '%s'" % cp)
    tr0.addTemplatePath(cp)
tr0.update()

for cd in templateData:
    tr0.addTemplateData(cd[0], cd[1])

print("  Repository nodes:")
print(str(tr0.getRoot().toConfig("    ")))

print("  Modules:")
k = 0
for cm in testModules:
    print("  [%02d] %s:" % (k + 1, str(cm)))
    d = tr0.getTemplateData(cm)
    print(str(d))

tpl0 = it.Template.create("", config0.getRoot(), tr0)
mm.addLocalRef(tpl0)
r0 = tpl0.processModule('main')

print("    Result:")
print(str(r0))

print("All done!")
