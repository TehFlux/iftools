# ==========================================================================
# Ionflux Object Base System
# Copyright © 2006 Joern P. Meier
# mail@ionflux.org
# --------------------------------------------------------------------------
# event.conf.tpl          Configuration template for events.
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

# The contents of this file will be processed to fill in values defined by 
# the class configuration and the generator. The result processed to create 
# the event header and implementation files.

# using directives
using = \{
	'namespace std'
	'namespace Ionflux::ObjectBase'
\}

# class definition
class = \{
	name = IF{$id|uppercase(1)}Event
	shortDesc = {if shortDesc == ""}Event class for the '{$id}' event.{else}{$shortDesc}{/if}
	title = {$id|uppercase(1)} event
	longDesc = {if longDesc == ""}Event class for the '{$id}' event.{else}{$longDesc}{/if}
	group.name = ifobject
	base = \{
		# base classes from the IFObject hierarchy
		ifobject[] = \{
           # class name
		   name = IFObject
		   # include file (optional)
		   # include = 
		\}
	\}
\}

