{section declareMapReadFuncs}
		
		/** Get number of {if prop.element.plural == ""}{$prop.element.name|lowercase(1)}s{else}{$prop.element.plural|lowercase(1)}{/if}.
		 *
{swrap 75 "		 * "}\\return Number of {if prop.element.plural == ""}{$prop.element.name|lowercase(1)}s{else}{$prop.element.plural|lowercase(1)}{/if}.{/swrap}
		 */
{swrap 75 "		"}virtual unsigned int getNum{if prop.element.plural == ""}{$prop.element.name|uppercase(1)}s{else}{$prop.element.plural|uppercase(1)}{/if}() const;{/swrap}
		
		/** Get {$prop.element.name|lowercase(1)}.
		 *
{swrap 75 "		 * "}Get the {$prop.element.name|lowercase(1)} with the specified key.{/swrap}
		 *
{swrap 75 "		 * "}\\param elementKey Element key.{/swrap}
		 *
{swrap 75 "		 * "}\\return {$prop.element.name|uppercase(1)} with specified key.{/swrap}
		 */
{swrap 75 "		"}virtual {$prop.element.type} get{$prop.element.name|uppercase(1)}({if prop.key.accessType != ""}{$prop.key.accessType}{else}{$prop.key.type}{/if} elementKey) const;{/swrap}{/section}
