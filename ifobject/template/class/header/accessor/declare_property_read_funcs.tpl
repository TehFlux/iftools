{section declarePropertyReadFuncs}{if prop.style == "vector"}{ref declareVectorReadFuncs}{else}{if prop.style == "map"}{ref declareMapReadFuncs}{else}
		
		/** Get {$prop.desc|lowercase(1)}.
		 *
{swrap 75 "		 * "}\\return Current value of {$prop.desc|lowercase(1)}.{/swrap}
		 */
{swrap 75 "		"}virtual {$prop.type} get{$prop.name|uppercase(1)}() const;{/swrap}{/if}{/if}{/section}
