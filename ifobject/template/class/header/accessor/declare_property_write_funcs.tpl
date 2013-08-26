{section declarePropertyWriteFuncs}{if prop.style == "vector"}{ref declareVectorWriteFuncs}{else}{if prop.style == "map"}{ref declareMapWriteFuncs}{else}
		
		/** Set {$prop.desc|lowercase(1)}.
		 *
		 * Set new value of {$prop.desc|lowercase(1)}.
		 *
{swrap 75 "		 * "}\\param new{$prop.name|uppercase(1)} New value of {$prop.desc|lowercase(1)}.{/swrap}
		 */
{swrap 75 "		"}virtual void set{$prop.name|uppercase(1)}({$prop.setFromType} new{$prop.name|uppercase(1)});{/swrap}{/if}{/if}{/section}
