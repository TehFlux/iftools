{section deserializeVar}{if var.deserializeImpl != ""}
{$var.deserializeImpl|swrap(75,'	')}{else}
	offset = unpack(source, {$var.name}, offset);{/if}
	if (offset < 0)
	\{{if enableLogMessage == 1}
		std::ostringstream state;
		state << "Could not deserialize variable '{$var.name}'.";
		log(IFLogMessage(state.str(), VL_ERROR, 
			this, "deserialize"));
        return false;{else}
        std::ostringstream status;
		status << "[{$class.name}::deserialize] "
			"Could not deserialize property '{$prop.name}'.";
        throw {if class.serialize.errorClass != ""}{$class.serialize.errorClass}{else}Ionflux::ObjectBase::IFError{/if}(status.str());{/if}
	\}{/section}
