{section declareQtSlot}
		
		/** {$sl.shortDesc}.{if sl.longDesc != ""}
		 *
{$sl.longDesc|swrap(72,'		 * ')}{/if}{foreach prm in sl.param}{first}
		 *{/first}{single}
		 *{/single}
{swrap 75 "		 * "}\\param {$prm.name} {$prm.desc}.{/swrap}{/foreach}{if sl.return.value != ""}
		 *
{swrap 75 "		 * "}\\return {$sl.return.desc}.{/swrap}{/if}
		 */
{swrap 75 "		"}{$sl.spec} {$sl.type} {$sl.name}({foreach prm in sl.param}{$prm.type} {$prm.name}{if prm.default != ""} = {$prm.default}{/if}{first}, {/first}{mid}, {/mid}{/foreach}){if sl.const == "true"} const{/if}{if sl.throw != ""} throw({if sl.throw != "<none>"}{$sl.throw}{/if}){/if}{if sl.pureVirtual == "true"} = 0{/if};{/swrap}{/section}
