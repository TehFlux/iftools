{section createOpProxyImpl}

{swrap 75}bool {$class.name}::op{$op.name|uppercase(1)}({foreach prm in op.param}Ionflux::ObjectBase::IFObject* {$prm.name}, {/foreach}Ionflux::ObjectBase::IFObjectVector* target){if op.const == "true"} const{/if}{/swrap}
\{{if op.impl != ""}
{$op.impl|swrap(75,'	')}{else}
	// TODO: Implementation.
	if (target != 0)
		target.clear();
	return true;{/if}
\}{if ( op.const != "true" ) && ( op.constImpl != "" )}

{swrap 75}bool {$class.name}::op{$op.name|uppercase(1)}({foreach prm in op.param}Ionflux::ObjectBase::IFObject* {$prm.name}, {/foreach}Ionflux::ObjectBase::IFObjectVector* target) const{/swrap}
\{
{$op.constImpl|swrap(75,'	')}
\}{/if}{/section}
