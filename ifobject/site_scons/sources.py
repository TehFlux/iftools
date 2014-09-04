#!/usr/bin/python
# -*- coding: utf-8 -*-
"""Sources.

This file contains lists of source files used by the build system."""

# Ionflux Object Base library
ifobjectLibHeaders = [
    'include/sha1.hpp',
    'include/libb64.hpp',
	'include/ifobject/types.hpp',
	'include/ifobject/constants.hpp',
	'include/ifobject/log.hpp',
	'include/ifobject/utf8.hpp',
	'include/ifobject/serialize.hpp',
	'include/ifobject/utils.hpp',
	'include/ifobject/xmlutils.hpp',
	'include/ifobject/objectutils.hpp',
	'include/ifobject/xmlutils_private.hpp',
	'include/ifobject/cachehelpers.hpp',
	'include/ifobject/ifobjectbase.hpp',
	'include/ifobject/IFClassInfo.hpp',
	'include/ifobject/IFObject.hpp',
	'include/ifobject/IFObjectEvent.hpp',
	'include/ifobject/IFObjectSignalProxy.hpp',
	'include/ifobject/IFMutex.hpp',
	'include/ifobject/IFGuard.hpp',
	'include/ifobject/IFSignal.hpp',
	'include/ifobject/IFLogMessage.hpp', 
	'include/ifobject/IFThread.hpp', 
	'include/ifobject/IFThreadEvent.hpp', 
	'include/ifobject/IFObjectSignalProxy.hpp', 
    'include/ifobject/IFCache.hpp', 
    'include/ifobject/IFError.hpp', 
    'include/ifobject/IFMMEvent.hpp', 
    'include/ifobject/IFMMEventHandler.hpp',
    'include/ifobject/IFXMLObjectFactory.hpp', 
    'include/ifobject/IFIOContext.hpp'
]

ifobjectLibSources = [
    'build/sha1.cpp',
    'build/libb64.cpp',
	'build/log.cpp',
	'build/utf8.cpp',
	'build/serialize.cpp',
	'build/utils.cpp',
	'build/xmlutils.cpp',
	'build/IFClassInfo.cpp',
	'build/IFObject.cpp',
	'build/IFObjectEvent.cpp',
	'build/IFObjectSignalProxy.cpp',
	'build/IFMutex.cpp',
	'build/IFGuard.cpp',
	'build/IFSignal.cpp',
	'build/IFLogMessage.cpp',
	'build/IFThread.cpp',
	'build/IFThreadEvent.cpp',
	'build/IFThreadSignalProxy.cpp', 
	'build/IFCache.cpp', 
	'build/IFError.cpp', 
	'build/IFMMEvent.cpp', 
	'build/IFMMEventHandler.cpp', 
	'build/IFXMLObjectFactory.cpp', 
	'build/IFIOContext.cpp'
]

ifobjectLibClasses = [
    'IFClassInfo', 
    'IFExampleClass', 
    'IFGuard', 
    'IFLogMessage', 
    'IFMutex', 
    'IFObject', 
    'IFSignal', 
    'IFThread', 
    'IFCache', 
    'IFError', 
    'IFMMEvent', 
    'IFMMEventHandler', 
    'IFXMLObjectFactory', 
    'IFIOContext'
]

