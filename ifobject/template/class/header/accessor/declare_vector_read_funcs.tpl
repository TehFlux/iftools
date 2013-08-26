{section declareVectorReadFuncs}
		
		/** Get number of {if prop.element.plural == ""}{$prop.element.name|lowercase(1)}s{else}{$prop.element.plural|lowercase(1)}{/if}.
		 *
{swrap 75 "		 * "}\\return Number of {if prop.element.plural == ""}{$prop.element.name|lowercase(1)}s{else}{$prop.element.plural|lowercase(1)}{/if}.{/swrap}
		 */
{swrap 75 "		"}virtual unsigned int getNum{if prop.element.plural == ""}{$prop.element.name|uppercase(1)}s{else}{$prop.element.plural|uppercase(1)}{/if}() const;{/swrap}
		
		/** Get {$prop.element.name|lowercase(1)}.
		 *
{swrap 75 "		 * "}Get the {$prop.element.name|lowercase(1)} at the specified index.{/swrap}
		 *
{swrap 75 "		 * "}\\param elementIndex Element index.{/swrap}
		 *
{swrap 75 "		 * "}\\return {$prop.element.name|uppercase(1)} at specified index.{/swrap}
		 */
{swrap 75 "		"}virtual {$prop.element.type} get{$prop.element.name|uppercase(1)}(unsigned int elementIndex = 0) const;{/swrap}
		
		/** Find {$prop.element.name|lowercase(1)}.
		 *
{swrap 75 "		 * "}Find the specified occurence of a {$prop.element.name|lowercase(1)}.{/swrap}
		 *
{swrap 75 "		 * "}\\param needle {$prop.element.name|uppercase(1)} to be found.{/swrap}
{swrap 75 "		 * "}\\param occurence Number of the occurence to be found.{/swrap}
		 *
{swrap 75 "		 * "}\\return Index of the {$prop.element.name|lowercase(1)}, or -1 if the {$prop.element.name|lowercase(1)} cannot be found.{/swrap}
		 */
{swrap 75 "		"}virtual int find{$prop.element.name|uppercase(1)}({if prop.element.findType == ""}{$prop.element.type}{else}{$prop.element.findType}{/if} needle, unsigned int occurence = 1) const;{/swrap}{/section}
