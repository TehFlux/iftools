{section deserializeVarStream}{if var.deserialize.impl.stream != ""}
{$var.deserialize.impl.stream|swrap(75,'	')}{else}
	unpack(source, {$var.name});{/if}{/section}
