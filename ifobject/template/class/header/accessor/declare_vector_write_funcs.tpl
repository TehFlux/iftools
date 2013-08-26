{section declareVectorWriteFuncs}{if prop.hideImpl != "true"}
        
		/** Get {$prop.desc|lowercase(1)}.
		 *
{swrap 75 "		 * "}\\return {$prop.desc|lowercase(1)}.{/swrap}
		 */
{swrap 75 "		"}virtual std::vector<{$prop.element.type}>& get{if prop.element.plural == ""}{$prop.element.name|uppercase(1)}s{else}{$prop.element.plural|uppercase(1)}{/if}();{/swrap}{/if}
		
		/** Add {$prop.element.name|lowercase(1)}.
		 *
{swrap 75 "		 * "}Add a {$prop.element.name|lowercase(1)}.{/swrap}
		 *
{swrap 75 "		 * "}\\param addElement {$prop.element.name|uppercase(1)} to be added.{/swrap}
		 */
{swrap 75 "		"}virtual void add{$prop.element.name|uppercase(1)}({if prop.element.addType == ""}{$prop.element.type}{else}{$prop.element.addType}{/if} addElement);{/swrap}{if prop.extendedAddFuncs == "true"}{ref declareExtendedVectorAddFuncs}{/if}
		
		/** Remove {$prop.element.name|lowercase(1)}.
		 *
{swrap 75 "		 * "}Remove a {$prop.element.name|lowercase(1)}.{/swrap}
		 *
{swrap 75 "		 * "}\\param removeElement {$prop.element.name|uppercase(1)} to be removed.{/swrap}
		 */
{swrap 75 "		"}virtual void remove{$prop.element.name|uppercase(1)}({if prop.element.removeType == ""}{$prop.element.type}{else}{$prop.element.removeType}{/if} removeElement);{/swrap}
		
		/** Remove {$prop.element.name|lowercase(1)}.
		 *
{swrap 75 "		 * "}Remove a {$prop.element.name|lowercase(1)}.{/swrap}
		 *
{swrap 75 "		 * "}\\param removeIndex {$prop.element.name|uppercase(1)} to be removed.{/swrap}
		 */
{swrap 75 "		"}virtual void remove{$prop.element.name|uppercase(1)}Index(unsigned int removeIndex);{/swrap}{ref declarePropertyClearFunc}{/section}
