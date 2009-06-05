#!/bin/sh
# ==========================================================================
# Ionflux Tools
# Copyright (c) 2004-2007 Joern P. Meier
# mail@ionflux.org
# --------------------------------------------------------------------------
# createPyModule.sh              Python module creation script.
# ==========================================================================
# 
# This file is part of Ionflux Tools.
# 
# Ionflux Tools is free software; you can redistribute it and/or modify it 
# under the terms of the GNU General Public License as published by the Free
# Software Foundation; either version 2 of the License, or (at  your option)
# any later version.
# 
# Ionflux Tools is distributed in the hope that it will be useful, but 
# WITHOUT ANY WARRANTY; without even the implied warranty of MERCHANTABILITY
# or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU General Public License
# for more details.
# 
# You should have received a copy of the GNU General Public License
# along with Ionflux Tools; if not, write to the Free Software Foundation, 
# Inc., 59 Temple Place, Suite 330, Boston, MA 02111-1307 USA
# 
# ==========================================================================
echo "Creating wrapper code..."
swig -c++ -python -outdir swig/python swig/iftools.i &&
echo "Building Python module..." &&
g++ -shared -fPIC -o swig/python/_IFTools.so -I/usr/include/python2.6 \
    -Iinclude -Iinclude/ionflux -Iextern/sha1 -Iextern/Mersenne -lpython2.6 -liftools \
    -Llib swig/iftools_wrap.cxx &&
echo "All done."
