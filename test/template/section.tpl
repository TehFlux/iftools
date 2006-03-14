# ==========================================================================
# ITSP - Ionflux Time Series Processing
# Copyright (c) 2006 Joern P. Meier
# itsp@ionflux.org
# --------------------------------------------------------------------------
# section.tpl             Sample template file.
# ==========================================================================
# 
# This file is part of ITSP.
# 
# ITSP is free software; you can redistribute it and/or modify it under the 
# terms of the GNU General Public License as published by the Free Software 
# Foundation; either version 2 of the License, or (at  your option) any 
# later version.
# 
# ITSP is distributed in the hope that it will be useful, but WITHOUT ANY 
# WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS 
# FOR A PARTICULAR PURPOSE.  See the GNU General Public License for more 
# details.
# 
# You should have received a copy of the GNU General Public License
# along with ITSP; if not, write to the Free Software Foundation, Inc., 59 
# Temple Place, Suite 330, Boston, MA 02111-1307 USA
# 
# ==========================================================================
{$level = 0}{$indent = ""}{section test}If you can read this, the section 'test' has been referenced from the template.{/section}{section recursiveSectionA}{$indent = indent + "  "}{$level = level + 1}{foreach a in a.child}
{$indent}• {$a.name} ({$level}){ref recursiveSectionA restore}{/foreach}{/section}{section recursiveSectionB}{$indent = indent + "  "}{$level = level + 1}{foreach a in a.child}
{$indent}• {$a.name} ({$level}){ref recursiveSectionB}{/foreach}{/section}This is a section test.

{ref test}

The following is an example of a section used to implement recursive 
processing. It uses the 'restore' switch to restore the environment after the 
section is processed. This is very useful, as you can see from the automatic 
indentation and level information:

• {$a.name} ({$level}){ref recursiveSectionA restore}

The following example does not use the 'restore' switch. As you can see, this 
causes unexpected indentation and wrong level information, but it might be 
useful in some cases, such as when a section needs to update the global 
environment:

• {$a.name} ({$level}){ref recursiveSectionB}

WARNING: Don't try recursive processing with data entries. It will cause an 
infinite loop, since each node with a single data element is considered a list 
with one element which should be iterated over. Child node iterations should 
work fine.
