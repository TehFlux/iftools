{section createQtSlotImpl}{if sl.pureVirtual != "true"}

{swrap 75}{$sl.type} {$class.name}::{$sl.name}({foreach prm in sl.param}{$prm.type} {$prm.name}{first}, {/first}{mid}, {/mid}{/foreach}){if sl.const == "true"} const{/if}{if sl.throw != ""} throw({if sl.throw != "<none>"}{$sl.throw}{/if}){/if}{/swrap}
\{{if ( enableGuards == 1 ) && ( sl.spec != "static" )}
	IFGuard functionGuard(guardMutex);{/if}
{if sl.impl == ""}	// TODO: Implementation.{else}{$sl.impl|swrap(75,'	')}{/if}
{if sl.return.value != ""}	return {$sl.return.value};
{/if}\}{/if}{/section}
