#!/bin/bash
# ==========================================================================
# Ionflux Object Base System
# Copyright © 2006-2008 Joern P. Meier
# mail@ionflux.org
# --------------------------------------------------------------------------
# createPyModule.sh              Python module creation script.
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

# You will have to set these to the correct paths yourself 
# Sorry for the inconvenience!
IFOBJECT_PREFIX=/home/ionflux/svn/iftools/trunk/ifobject
PYTHON_INCLUDE_PATH=/usr/include/python2.6

# You can usually leave those as they are if the prefix is correct.
IFOBJECT_INCLUDE_PATH=$IFOBJECT_PREFIX/include
IFOBJECT_LIB_PATH=$IFOBJECT_PREFIX/lib

if [[ ! -d $PYTHON_INCLUDE_PATH ]]; then
    echo "Python include path '$PYTHON_INCLUDE_PATH' does not exist. " \
        "Please set it to the correct path in createPyModule.sh."
fi
if [[ ! -d $IFOBJECT_INCLUDE_PATH ]]; then
    echo "IFObject include path '$IFOBJECT_INCLUDE_PATH' does not exist. " \
        "Please set it to the correct path in createPyModule.sh."
fi
if [[ ! -d $IFOBJECT_LIB_PATH ]]; then
    echo "IFObject library path '$IFOBJECT_LIB_PATH' does not exist. " \
        "Please set it to the correct path in createPyModule.sh."
fi

echo "Creating wrapper code..."
swig -c++ -python -outdir swig/python swig/ifobject.i &&
echo "Building Python module..." &&
g++ -shared -fPIC -o swig/python/_IFObjectBase.so -I$PYTHON_INCLUDE_PATH \
    -I$IFOBJECT_INCLUDE_PATH -L$IFOBJECT_LIB_PATH  \
    $(pkg-config --cflags --libs sigc++-2.0) -lifobject \
    swig/ifobject_wrap.cxx &&
echo "All done."
