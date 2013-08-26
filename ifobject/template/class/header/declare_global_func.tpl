{section declareGlobalFunc}

/** {$func.shortDesc}.{if func.longDesc != ""}
 *
{$func.longDesc|swrap(72,' * ')}{/if}{foreach prm in func.param}{first}
 *{/first}{single}
 *{/single}
{swrap 75 " * "}\\param {$prm.name} {$prm.desc}.{/swrap}{/foreach}{if func.return.value != ""}
 *
{swrap 75 " * "}\\return {$func.return.desc}.{/swrap}{/if}
 */
{swrap 75}{if class.linkagePrefix != ""}{$class.linkagePrefix} {else}{if project.linkagePrefix != ""}{$project.linkagePrefix} {/if}{/if}{$func.type} {$func.name}({foreach prm in func.param}{$prm.type} {$prm.name}{if prm.default != ""} = {$prm.default}{/if}{first}, {/first}{mid}, {/mid}{/foreach}){if func.const == "true"} const{/if}{if func.pureVirtual == "true"} = 0{/if};{/swrap}{/section}
