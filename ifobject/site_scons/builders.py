#!/usr/bin/python
# -*- coding: utf-8 -*-
# ==========================================================================
# Ionflux Object Base System
# Copyright © 2006-2013 Joern P. Meier
# mail@ionflux.org
# --------------------------------------------------------------------------
# builders.py                  SCons builders.
# ==========================================================================
# 
# This file is part of Ionflux Object Base System.
# 
# Ionflux Object Base System is free software; you can redistribute it 
# and/or modify it under the terms of the GNU General Public License as 
# published by the Free Software Foundation; either version 2 of the 
# License, or (at  your option) any later version.
# 
# Ionflux Object Base System is distributed in the hope that it will be 
# useful, but WITHOUT ANY WARRANTY; without even the implied warranty of 
# MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU 
# General Public License for more details.
# 
# You should have received a copy of the GNU General Public License
# along with Ionflux Object Base System; if not, write to the Free 
# Software Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA 
# 02111-1307 USA
# 
# ==========================================================================
import os, shlex, shutil, subprocess, re, string
import local_config as lc

def buildSource(source, target, env):
    """Builder function to build source files from class configuration."""
    classNames = []
    for it in source:
        cn, ext = os.path.splitext(os.path.basename(it.path))
        if (ext == '.conf'):
            classNames += [cn]
    for cn in classNames:
        c0 = ("ifclassgen0 -t " + lc.ifobjectTemplatePath 
            + " -c conf/class -m conf/main.conf -i include/" 
            + lc.baseName + " -s src " + cn)
        #c0 = ("ifclassgen -t " + lc.ifobjectTemplatePath 
        #    + "/attic/class -c conf/class -m conf/main.conf -i include/" 
        #    + lc.baseName + " -s src " + cn)
        print(c0)
        sp0 = subprocess.call(shlex.split(c0))

def buildClassInterface(source, target, env):
    """Builder function to build SWIG interface files from class 
       configuration."""
    classNames = []
    for it in source:
        cn, ext = os.path.splitext(os.path.basename(it.path))
        if (ext == '.conf'):
            classNames += [cn]
    for cn in classNames:
        c0 = ("iftpl0 -I " + lc.ifobjectTemplatePath 
            + " swig.interface conf/class/" + cn + ".conf conf/main.conf")
        #c0 = ("iftpl " + lc.ifobjectTemplatePath 
        #    + "/attic/interface.i.tpl conf/class/" + cn #
        #    + ".conf conf/main.conf")
        print(c0)
        f0 = open("swig/classes/" + cn + ".i", 'w')
        sp0 = subprocess.call(shlex.split(c0), stdout = f0)
        f0.close()

def buildInterface(source, target, env):
    """Builder function to build a SWIG interface declaration."""
    classNames = []
    if (isinstance(lc.swigInterfaceTemplateFile, str)):
        templateFile = lc.swigInterfaceTemplateFile
    for it in source:
        cn, ext = os.path.splitext(os.path.basename(it.path))
        if (ext == '.i'):
            classNames += [cn]
        elif (ext == '.tpl'):
            templateFile = it.path
    tplData = {}
    p0 = re.compile("/\\*.*?\\*/", re.DOTALL)
    for cn in classNames:
        tplData[cn] = p0.sub('', open('swig/classes/' + cn + '.i').read())
    tplStr = open(templateFile).read()
    tpl = string.Template(tplStr)
    for it in target:
        f0 = open(it.path, 'w')
        f0.write(tpl.substitute(tplData))
        f0.close()

def buildClassXMLFactory(source, target, env):
    """Builder function to build an XML object factory configuration file 
       from class configuration."""
    classNames = []
    for it in source:
        cn, ext = os.path.splitext(os.path.basename(it.path))
        if (ext == '.conf'):
            classNames += [cn]
    for cn in classNames:
        c0 = ("iftpl0 -I " + lc.ifobjectTemplatePath 
            + " xml.conf.xml_object_factory conf/class/" + cn 
            + ".conf conf/main.conf")
        print(c0)
        f0 = open("conf/class/xmlio/" + cn + "XMLFactory.conf", 'w')
        sp0 = subprocess.call(shlex.split(c0), stdout = f0)
        f0.close()

