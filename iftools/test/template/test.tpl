# ==========================================================================
# ITSP - Ionflux Time Series Processing
# Copyright (c) 2004 Joern P. Meier
# itsp@ionflux.org
# --------------------------------------------------------------------------
# test.tpl             Sample template file.
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
{include test/template/header.tpl}
It contains some variable substitutions, like "{$foo}" and "{$bar.baz[2]}".

Here are {$even} {$more.variables}. Note the different styles that are
possible for specifying variable substitution tags, like \{${$foo[1]}\} and 
\{.{.foo[2]}\} and even \{@{@foo[3]|uppercase|translate('P', 'B')}\}. You can use string manipulators in 
variable substitution tags, for example:

{$example}.

Comments are stripped out, but you can of course still escape the comment
character, like

\# this.

This is a simple foreach example that also demonstrates accessing the 
iteration counter:
{foreach geez in foo}
[{$__i}] Behold the iterations!
+ {$geez}
{/foreach}
Here is (slightly) more complex example demonstrating nested foreach-loops, 
accessing fields of an iterator variable, nested iteration counters, total 
number of iterations and the first/last tags:

Colors:
{foreach color in colors}{first}
First color in list:{/first}{last}
Last color in list:{/last}
Color \#{$__i} of {$__n}: name = {$color.name}, code = {$color.code}
{foreach field in color}    [{$__i[1]} of {$__n[1]}]: {$field}
{/foreach}{/foreach}
This is the result of nested foreach and if-blocks:
{foreach num in number}
{if num > 5}{$num} is greater than 5.{else}{if num == 5}{$num} is equal to 5.{else}{$num} is less than 5.{/if}{/if}{/foreach}

The first/last tags are convenient to output headers and footers only if a 
node has any elements.{foreach li in list}{$listnum = __i[0] + 1}{foreach el in li}{first}

Elements in List {$listnum}: {/first}{single}

Single element in list {$listnum}: {/single}{$el}{notlast}, {/notlast}{/foreach}{/foreach}{foreach el in list3}{first}

Elements in List 3: {/first}{single}

Single element in list 3: {/single}{$el}{first}, {/first}{mid}, {/mid}{empty}

List 3 does not contain any elements.{/foreach}

Note that no header is printed for list 3, since that list is (by default) 
empty. If you add elements to list 3, the header and elements will be 
printed. This example also uses the 'first' and 'mid' tags to ensure the list 
delimiter (',') is only printed between elements. If a list contains but a 
single element, the first/last/mid tags do nothing, but you can use the 
'single' tag to generate additional output. See how this is used in the 
example above to generate a different header for single-element lists, like 
list 2. Also, in this case, no list delimiters are printed.

Now we use in-tag assignment to append the value 'bar' to the value stored 
in the variable 'foo'.
{$foo = foo + "bar"}
The result is:

foo = '{$foo}'
{if cheers != ""}
Have fun!{/if}
