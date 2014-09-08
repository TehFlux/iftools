{import class.impl.serialize.serialize_prop}{import class.impl.serialize.serialize_var}{import class.impl.serialize.deserialize_prop}{import class.impl.serialize.deserialize_var}{import class.impl.serialize.serialize_prop_stream}{import class.impl.serialize.serialize_var_stream}{import class.impl.serialize.deserialize_prop_stream}{import class.impl.serialize.deserialize_var_stream}{section createSerializeFuncsImpl}

bool {$class.name}::serialize(std::string& target) const
\{{if haveBaseIFObject == 1}{foreach bc in class.base.ifobject}
	if (!{$bc.name}::serialize(target))
		return false;{/foreach}{/if}{foreach bc in class.base.other}{if bc.serialize == "true"}
	if (!{$bc.name}::serialize(target))
		return false;{/if}{/foreach}{foreach prop in property.private}{if prop.serialize == "true"}{ref serializeProp}{/if}{/foreach}{foreach prop in property.protected}{if prop.serialize == "true"}{ref serializeProp}{/if}{/foreach}{foreach var in variable.private}{if var.serialize == "true"}{ref serializeVar}{/if}{/foreach}{foreach var in variable.protected}{if var.serialize == "true"}{ref serializeVar}{/if}{/foreach}{foreach var in variable.public}{if var.serialize == "true"}{ref serializeVar}{/if}{/foreach}
	return true;
\}

Ionflux::ObjectBase::DataSize {$class.name}::deserialize(const std::string& source, Ionflux::ObjectBase::DataSize offset)
\{{if haveBaseIFObject == 1}{foreach bc in class.base.ifobject}
	offset = {$bc.name}::deserialize(source, offset);
	if (offset < 0)
		return -1;{/foreach}{/if}{foreach bc in class.base.other}{if bc.serialize == "true"}
	offset = {$bc.name}::deserialize(source, offset);
	if (offset < 0)
		return false;{/if}{/foreach}{foreach prop in property.private}{if prop.serialize == "true"}{ref deserializeProp}{/if}{/foreach}{foreach prop in property.protected}{if prop.serialize == "true"}{ref deserializeProp}{/if}{/foreach}{foreach var in variable.private}{if var.serialize == "true"}{ref deserializeVar}{/if}{/foreach}{foreach var in variable.protected}{if var.serialize == "true"}{ref deserializeVar}{/if}{/foreach}{foreach var in variable.public}{if var.serialize == "true"}{ref deserializeVar}{/if}{/foreach}
	return offset;
\}

bool {$class.name}::serialize(std::ostream& target) const
\{{if haveBaseIFObject == 1}{foreach bc in class.base.ifobject}
	if (!{$bc.name}::serialize(target))
		return false;{/foreach}{/if}{foreach bc in class.base.other}{if bc.serialize == "true"}
	if (!{$bc.name}::serialize(target))
		return false;{/if}{/foreach}{foreach prop in property.private}{if prop.serialize == "true"}{ref serializePropStream}{/if}{/foreach}{foreach prop in property.protected}{if prop.serialize == "true"}{ref serializePropStream}{/if}{/foreach}{foreach var in variable.private}{if var.serialize == "true"}{ref serializeVar}{/if}{/foreach}{foreach var in variable.protected}{if var.serialize == "true"}{ref serializeVarStream}{/if}{/foreach}{foreach var in variable.public}{if var.serialize == "true"}{ref serializeVarStream}{/if}{/foreach}
	return true;
\}

Ionflux::ObjectBase::DataSize {$class.name}::deserialize(std::istream& source, Ionflux::ObjectBase::DataSize offset)
\{
    if (offset != DATA_SIZE_INVALID)
    \{
        source.seekg(offset);
        if (!source.good())
        \{
            std::ostringstream status;
            status << "Invalid stream offset: " << offset;
            throw {if class.serialize.errorClass != ""}{$class.serialize.errorClass}{else}Ionflux::ObjectBase::IFError{/if}(getErrorString(status.str(), "deserialize"));
        \}
    \}{if haveBaseIFObject == 1}{foreach bc in class.base.ifobject}
	{$bc.name}::deserialize(source);{/foreach}{/if}{foreach bc in class.base.other}{if bc.serialize == "true"}
	{$bc.name}::deserialize(source);{/if}{/foreach}{foreach prop in property.private}{if prop.serialize == "true"}{ref deserializePropStream}{/if}{/foreach}{foreach prop in property.protected}{if prop.serialize == "true"}{ref deserializePropStream}{/if}{/foreach}{foreach var in variable.private}{if var.serialize == "true"}{ref deserializeVar}{/if}{/foreach}{foreach var in variable.protected}{if var.serialize == "true"}{ref deserializeVarStream}{/if}{/foreach}{foreach var in variable.public}{if var.serialize == "true"}{ref deserializeVarStream}{/if}{/foreach}
	return offset;
\}{/section}
