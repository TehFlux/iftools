{section deserializePropStream}
	// {$prop.name}{if prop.deserialize.impl.stream != ""}
{$prop.deserialize.impl.stream|swrap(75,'	')}{else}{if ( prop.persistent == "true" ) || ( prop.proxy == "true" )}
    {$prop.type} t0;
    unpack(source, t0);
    set{$prop.name|uppercase(1)}(t0);{else}{if prop.valueType == "object"}
    {$prop.type} t{$prop.name|uppercase(1)} = {$prop.name};
    unpackObj(source, t{$prop.name|uppercase(1)});
    if (t{$prop.name|uppercase(1)} != {$prop.name})
        set{$prop.name|uppercase(1)}(t{$prop.name|uppercase(1)});{else}
    unpack(source, {$prop.name});{/if}{/if}{/if}{/section}
