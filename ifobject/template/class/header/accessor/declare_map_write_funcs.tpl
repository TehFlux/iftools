{section declareMapWriteFuncs}{if prop.hideImpl != "true"}
        
		/** Get {$prop.desc|lowercase(1)}.
		 *
{swrap 75 "		 * "}\\return {$prop.desc|lowercase(1)}.{/swrap}
		 */
{swrap 75 "		"}virtual std::map<{$prop.key.type}, {$prop.element.type}>& get{if prop.element.plural == ""}{$prop.element.name|uppercase(1)}s{else}{$prop.element.plural|uppercase(1)}{/if}();{/swrap}{/if}
		
		/** Add {$prop.element.name|lowercase(1)}.
		 *
{swrap 75 "		 * "}Add a {$prop.element.name|lowercase(1)}.{/swrap}
		 *
		 * \\param elementKey Element key.
{swrap 75 "		 * "}\\param addElement {$prop.element.name|uppercase(1)} to be added.{/swrap}
		 */
{swrap 75 "		"}virtual void add{$prop.element.name|uppercase(1)}({if prop.key.accessType != ""}{$prop.key.accessType}{else}{$prop.key.type}{/if} elementKey, {if prop.element.addType == ""}{$prop.element.type}{else}{$prop.element.addType}{/if} addElement);{/swrap}
		
		/** Remove {$prop.element.name|lowercase(1)}.
		 *
{swrap 75 "		 * "}Remove the {$prop.element.name|lowercase(1)} with the specified key.{/swrap}
		 *
		 * \\param elementKey Element key.
		 */
{swrap 75 "		"}virtual void remove{$prop.element.name|uppercase(1)}({if prop.key.accessType != ""}{$prop.key.accessType}{else}{$prop.key.type}{/if} elementKey);{/swrap}{ref declarePropertyClearFunc}{/section}
