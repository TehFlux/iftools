{section serializeVar}{if var.serialize.impl.string != ""}
{$var.serialize.impl.string|swrap(75,'	')}{else}
	pack({$var.name}, target);{/if}{/section}
