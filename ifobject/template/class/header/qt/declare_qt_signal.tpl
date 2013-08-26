{section declareQtSignal}
		
		/** {$si.shortDesc}.{if si.longDesc != ""}
		 *
{$si.longDesc|swrap(72,'		 * ')}{/if}{foreach prm in si.param}{first}
		 *{/first}{single}
		 *{/single}
{swrap 75 "		 * "}\\param {$prm.name} {$prm.desc}.{/swrap}{/foreach}{if si.return.value != ""}
		 *
{swrap 75 "		 * "}\\return {$si.return.desc}.{/swrap}{/if}
		 */
{swrap 75 "		"}{$si.type} {$si.name}({foreach prm in si.param}{$prm.type} {$prm.name}{if prm.default != ""} = {$prm.default}{/if}{first}, {/first}{mid}, {/mid}{/foreach}){if si.const == "true"} const{/if}{if si.throw != ""} throw({if si.throw != "<none>"}{$si.throw}{/if}){/if}{if si.pureVirtual == "true"} = 0{/if};{/swrap}{/section}
