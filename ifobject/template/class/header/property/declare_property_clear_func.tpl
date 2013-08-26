{section declarePropertyClearFunc}
		
		/** Clear {if prop.element.plural == ""}{$prop.element.name|lowercase(1)}s{else}{$prop.element.plural|lowercase(1)}{/if}.
		 *
{swrap 75 "		 * "}Clear all {if prop.element.plural == ""}{$prop.element.name|lowercase(1)}s{else}{$prop.element.plural|lowercase(1)}{/if}.{/swrap}
		 */
{swrap 75 "		"}virtual void clear{if prop.element.plural == ""}{$prop.element.name|uppercase(1)}s{else}{$prop.element.plural|uppercase(1)}{/if}();{/swrap}{/section}
