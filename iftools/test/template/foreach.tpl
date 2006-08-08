# ==========================================================================
# ITSP - Ionflux Time Series Processing
# Copyright (c) 2004 Joern P. Meier
# itsp@ionflux.org
# --------------------------------------------------------------------------
# foreach.tpl             Sample template file for foreach tests.
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
{foreach list in lists}List '{$list.name}':
  Plain foreach:
    {foreach item in list.items}{$item} {/foreach}
  Foreach with 'first':
    {foreach item in list.items}{$item}{first}*{/first} {/foreach}
  Foreach with 'mid':
    {foreach item in list.items}{$item}{mid}*{/mid} {/foreach}
  Foreach with 'last':
    {foreach item in list.items}{$item}{last}*{/last} {/foreach}
  Foreach with 'single':
    {foreach item in list.items}{$item}{single}*{/single} {/foreach}
  Foreach with 'notfirst':
    {foreach item in list.items}{$item}{notfirst}*{/notfirst} {/foreach}
  Foreach with 'notmid':
    {foreach item in list.items}{$item}{notmid}*{/notmid} {/foreach}
  Foreach with 'notlast':
    {foreach item in list.items}{$item}{notlast}*{/notlast} {/foreach}
  Foreach with 'notsingle':
    {foreach item in list.items}{$item}{notsingle}*{/notsingle} {/foreach}
  Plain foreach with 'empty':
    {foreach item in list.items}{$item} {empty}This list is empty.{/foreach}{notlast}

{/notlast}{/foreach}
