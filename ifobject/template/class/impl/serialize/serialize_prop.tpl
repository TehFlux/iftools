{section serializeProp}{if prop.serialize.impl.string != ""}
{$prop.serialize.impl.string|swrap(75,'	')}{else}{if ( prop.persistent == "true" ) || ( prop.proxy == "true" )}
    pack(get{$prop.name|uppercase(0)}(), target);{else}{if prop.valueType == "object"}
    packObj({$prop.name}, target);{else}
	pack({$prop.name}, target);{/if}{/if}{/if}{/section}
