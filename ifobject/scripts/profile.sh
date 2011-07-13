#!/bin/bash
IFOBJECT_PYTHONPATH=/home/flux/svn/iftools/trunk/ifobject/swig/python
IFOBJECT_BIN_PATH=/home/flux/svn/iftools/trunk/ifobject/bin
IFOBJECT_LIB_PATH=/home/flux/svn/iftools/trunk/ifobject/lib
PATH=$PATH:$IFOBJECT_BIN_PATH
LD_LIBRARY_PATH=$LD_LIBRARY_PATH:$IFOBJECT_LIB_PATH
PYTHONPATH=$PYTHONPATH:$IFOBJECT_PYTHONPATH:./python
export PATH LD_LIBRARY_PATH PYTHONPATH
