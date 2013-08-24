#!/usr/bin/env python3
# -*- coding: utf-8 -*-
"""Ionflux Template Processor test script."""
import IFObjectBase as ib
import IFTemplate as it

testName = "Tokenizer 01"

# memory management
mm = ib.IFObject()

print("Ionflux Template Processor test script: " + testName)

input0 = "some (test   data (blah #2351 ##blupp))"

print("  Setting up token types...")

tt0 = it.createTokenType(1, "#", False, 0)
tt1 = it.createTokenType(2, "(", False, 1)
tt2 = it.createTokenType(3, ")", False, 1)

tokenTypes = [
    it.TT_WHITESPACE, 
    it.TT_ALPHA, 
    it.TT_NUMBER, 
    tt0, tt1, tt2 
]

print("  Setting up tokenizer...")

tok = it.Tokenizer.create()
mm.addLocalRef(tok)
tok.clearTokenTypes()
for tt in tokenTypes:
    tok.addTokenType(tt)
tok.setInput(input0)

print("  Tokenizing: '%s'" % input0)

ct = tok.getNextToken()
k = 0
while (it.isNonEmpty(ct)):
    print(("    [%03d]" % k) + " '" + ct.value + ("' (%d)" % ct.typeID))
    ct = tok.getNextToken()
    k += 1

print("All done!")
