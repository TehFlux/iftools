#!/bin/sh
# ==========================================================================
# Ionflux Object Base System
# Copyright © 2006 Joern P. Meier
# mail@ionflux.org
# --------------------------------------------------------------------------
# getSVNStatus.sh              Subversion status script.
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
mv svnstatus.mod.txt svnstatus.mod.txt~ 2>/dev/null
mv svnstatus.unknown.txt svnstatus.unknown.txt~ 2>/dev/null
svn status >svnstatus.txt &&
echo "------------------------------------------------------------------------" >svnstatus.mod.txt &&
grep "[AMD] " svnstatus.txt >>svnstatus.mod.txt
grep "\? " svnstatus.txt >svnstatus.unknown.txt
