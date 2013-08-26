{section serializeVar}{if var.serializeImpl != ""}
{$var.serializeImpl|swrap(75,'	')}{else}
	pack({$var.name}, target);{/if}{/section}
