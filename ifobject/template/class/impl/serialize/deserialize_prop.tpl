{section deserializeProp}
	// {$prop.name}{if prop.deserializeImpl != ""}
{$prop.deserializeImpl|swrap(75,'	')}{else}{if ( prop.persistent == "true" ) || ( prop.proxy == "true" )}
    {$prop.type} t0;
    offset = unpack(source, t0, offset);
    set{$prop.name|uppercase(1)}(t0);{else}{if prop.valueType == "object"}
    {$prop.type} t{$prop.name|uppercase(1)} = {$prop.name};
    offset = unpackObj(source, t{$prop.name|uppercase(1)}, offset);
    if (t{$prop.name|uppercase(1)} != {$prop.name})
        set{$prop.name|uppercase(1)}(t{$prop.name|uppercase(1)});{else}
    offset = unpack(source, {$prop.name}, offset);{/if}{/if}{/if}
	if (offset < 0)
	\{{if enableLogMessage == 1}
		std::ostringstream state;
		state << "Could not deserialize property '{$prop.name}'.";
		log(IFLogMessage(state.str(), VL_ERROR, 
			this, "deserialize"));
        return -1;{else}
        std::ostringstream status;
		status << "[{$class.name}::deserialize] "
			"Could not deserialize property '{$prop.name}'.";
        throw {if class.serialize.errorClass != ""}{$class.serialize.errorClass}{else}Ionflux::ObjectBase::IFError{/if}(status.str());{/if}
	\}{/section}
