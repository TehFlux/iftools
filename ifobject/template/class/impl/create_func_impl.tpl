{section createFuncImpl}{if func.pureVirtual != "true"}

{swrap 75}{$func.type} {$class.name}::{$func.name}({foreach prm in func.param}{$prm.type} {$prm.name}{first}, {/first}{mid}, {/mid}{/foreach}){if func.const == "true"} const{/if}{if func.throw != ""} throw({if func.throw != "<none>"}{$func.throw}{/if}){/if}{/swrap}
\{{if ( enableGuards == 1 ) && ( func.spec != "static" )}
	IFGuard functionGuard(guardMutex);{/if}
{if func.impl == ""}	// TODO: Implementation.{else}{$func.impl|swrap(75,'	')}{/if}
{if func.return.value != ""}	return {$func.return.value};
{/if}\}{/if}{/section}
