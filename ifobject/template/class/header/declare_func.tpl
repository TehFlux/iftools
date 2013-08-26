{section declareFunc}
		
		/** {$func.shortDesc}.{if func.longDesc != ""}
		 *
{$func.longDesc|swrap(72,'		 * ')}{/if}{foreach prm in func.param}{first}
		 *{/first}{single}
		 *{/single}
{swrap 75 "		 * "}\\param {$prm.name} {$prm.desc}.{/swrap}{/foreach}{if func.return.value != ""}
		 *
{swrap 75 "		 * "}\\return {$func.return.desc}.{/swrap}{/if}
		 */
{swrap 75 "		"}{$func.spec} {$func.type} {$func.name}({foreach prm in func.param}{$prm.type} {$prm.name}{if prm.default != ""} = {$prm.default}{/if}{first}, {/first}{mid}, {/mid}{/foreach}){if func.const == "true"} const{/if}{if func.throw != ""} throw({if func.throw != "<none>"}{$func.throw}{/if}){/if}{if func.pureVirtual == "true"} = 0{/if};{/swrap}{/section}
