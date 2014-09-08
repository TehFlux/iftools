{section serializeVarStream}{if var.serialize.impl.stream != ""}
{$var.serialize.impl.stream|swrap(75,'	')}{else}
	pack({$var.name}, target);{/if}{/section}
