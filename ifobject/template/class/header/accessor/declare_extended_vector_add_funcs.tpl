{section declareExtendedVectorAddFuncs}
		
		/** Create {$prop.element.name|lowercase(1)}.
		 *
{swrap 75 "		 * "}Create a new {$prop.element.name|lowercase(1)} which is managed by the {$prop.element.name|lowercase(1)} set.{/swrap}
		 *
		 * \\return New {$prop.element.name|lowercase(1)}.
		 */
{swrap 75 "		"}virtual {if prop.element.addType == ""}{$prop.element.type}{else}{$prop.element.addType}{/if} add{$prop.element.name|uppercase(1)}();{/swrap}
		
		/** Add {if prop.element.plural == ""}{$prop.element.name|lowercase(1)}s{else}{$prop.element.plural|lowercase(1)}{/if}.
		 *
{swrap 75 "		 * "}Add {if prop.element.plural == ""}{$prop.element.name|lowercase(1)}s{else}{$prop.element.plural|lowercase(1)}{/if} from a {$prop.element.name|lowercase(1)} vector.{/swrap}
		 *
		 * \\param new{if prop.element.plural == ""}{$prop.element.name|uppercase(1)}s{else}{$prop.element.plural|uppercase(1)}{/if} {if prop.element.plural == ""}{$prop.element.name|lowercase(1)}s{else}{$prop.element.plural|lowercase(1)}{/if}.
		 */
{swrap 75 "		"}virtual void add{if prop.element.plural == ""}{$prop.element.name|uppercase(1)}s{else}{$prop.element.plural|uppercase(1)}{/if}(const std::vector<{$prop.element.type}>& new{if prop.element.plural == ""}{$prop.element.name|uppercase(1)}s{else}{$prop.element.plural|uppercase(1)}{/if});{/swrap}
		
		/** Add {if prop.element.plural == ""}{$prop.element.name|lowercase(1)}s{else}{$prop.element.plural|lowercase(1)}{/if}.
		 *
		 * Add {if prop.element.plural == ""}{$prop.element.name|lowercase(1)}s{else}{$prop.element.plural|lowercase(1)}{/if} from a {$prop.element.name|lowercase(1)} set.
		 *
		 * \\param new{if prop.element.plural == ""}{$prop.element.name|uppercase(1)}s{else}{$prop.element.plural|uppercase(1)}{/if} {if prop.element.plural == ""}{$prop.element.name|lowercase(1)}s{else}{$prop.element.plural|lowercase(1)}{/if}.
		 */
{swrap 75 "		"}virtual void add{if prop.element.plural == ""}{$prop.element.name|uppercase(1)}s{else}{$prop.element.plural|uppercase(1)}{/if}({foreach ns in namespace}{$ns.name}::{/foreach}{$class.name}* new{if prop.element.plural == ""}{$prop.element.name|uppercase(1)}s{else}{$prop.element.plural|uppercase(1)}{/if});{/swrap}{/section}
