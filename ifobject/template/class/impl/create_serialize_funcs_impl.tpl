{import class.impl.serialize.serialize_prop}{import class.impl.serialize.serialize_var}{import class.impl.serialize.deserialize_prop}{import class.impl.serialize.deserialize_var}{import class.impl.serialize.serialize_prop_stream}{import class.impl.serialize.serialize_var_stream}{import class.impl.serialize.deserialize_prop_stream}{import class.impl.serialize.deserialize_var_stream}{section createSerializeFuncsImpl}

bool {$class.name}::serialize(std::string& target) const
\{{if enableGuards == 1}
	Ionflux::ObjectBase::IFGuard functionGuard(guardMutex);{/if}{if function.serialize.string.impl == ""}{if haveBaseIFObject == 1}{foreach bc in class.base.ifobject}
	if (!{$bc.name}::serialize(target))
		return false;{/foreach}{/if}{foreach bc in class.base.other}{if bc.serialize == "true"}
	if (!{$bc.name}::serialize(target))
		return false;{/if}{/foreach}{foreach prop in property.private}{if prop.serialize == "true"}{ref serializeProp}{/if}{/foreach}{foreach prop in property.protected}{if prop.serialize == "true"}{ref serializeProp}{/if}{/foreach}{foreach var in variable.private}{if var.serialize == "true"}{ref serializeVar}{/if}{/foreach}{foreach var in variable.protected}{if var.serialize == "true"}{ref serializeVar}{/if}{/foreach}{foreach var in variable.public}{if var.serialize == "true"}{ref serializeVar}{/if}{/foreach}{else}
{swrap 75 "    "}{$function.serialize.string.impl}{/swrap}{/if}
	return true;
\}

Ionflux::ObjectBase::DataSize {$class.name}::deserialize(const std::string& source, Ionflux::ObjectBase::DataSize offset)
\{{if enableGuards == 1}
	Ionflux::ObjectBase::IFGuard functionGuard(guardMutex);{/if}{if function.deserialize.string.impl == ""}{if haveBaseIFObject == 1}{foreach bc in class.base.ifobject}
	offset = {$bc.name}::deserialize(source, offset);
	if (offset < 0)
		return -1;{/foreach}{/if}{foreach bc in class.base.other}{if bc.serialize == "true"}
	offset = {$bc.name}::deserialize(source, offset);
	if (offset < 0)
		return false;{/if}{/foreach}{foreach prop in property.private}{if prop.serialize == "true"}{ref deserializeProp}{/if}{/foreach}{foreach prop in property.protected}{if prop.serialize == "true"}{ref deserializeProp}{/if}{/foreach}{foreach var in variable.private}{if var.serialize == "true"}{ref deserializeVar}{/if}{/foreach}{foreach var in variable.protected}{if var.serialize == "true"}{ref deserializeVar}{/if}{/foreach}{foreach var in variable.public}{if var.serialize == "true"}{ref deserializeVar}{/if}{/foreach}{else}
{swrap 75 "    "}{$function.deserialize.string.impl}{/swrap}{/if}
	return offset;
\}

bool {$class.name}::serialize(std::ostream& target, bool addMagicWord) const
\{{if enableGuards == 1}
	Ionflux::ObjectBase::IFGuard functionGuard(guardMutex);{/if}{if function.deserialize.stream.impl == ""}
	if (addMagicWord)
        Ionflux::ObjectBase::pack(getMagicSyllableBase(), 
            getMagicSyllable(), target);{if haveBaseIFObject == 1}{foreach bc in class.base.ifobject}
	if (!{$bc.name}::serialize(target, false))
		return false;{/foreach}{/if}{foreach bc in class.base.other}{if bc.serialize == "true"}
	if (!{$bc.name}::serialize(target, false))
		return false;{/if}{/foreach}{foreach prop in property.private}{if prop.serialize == "true"}{ref serializePropStream}{/if}{/foreach}{foreach prop in property.protected}{if prop.serialize == "true"}{ref serializePropStream}{/if}{/foreach}{foreach var in variable.private}{if var.serialize == "true"}{ref serializeVar}{/if}{/foreach}{foreach var in variable.protected}{if var.serialize == "true"}{ref serializeVarStream}{/if}{/foreach}{foreach var in variable.public}{if var.serialize == "true"}{ref serializeVarStream}{/if}{/foreach}{else}
{swrap 75 "    "}{$function.serialize.stream.impl}{/swrap}{/if}
	return true;
\}

Ionflux::ObjectBase::DataSize {$class.name}::deserialize(std::istream& source, Ionflux::ObjectBase::DataSize offset, bool checkMagicWord)
\{{if enableGuards == 1}
	Ionflux::ObjectBase::IFGuard functionGuard(guardMutex);{/if}
    if (offset != Ionflux::ObjectBase::DATA_SIZE_INVALID)
    \{
        source.seekg(offset);
        if (!source.good())
        \{
            std::ostringstream status;
            status << "Invalid stream offset: " << offset;
            throw {if class.serialize.errorClass != ""}{$class.serialize.errorClass}{else}Ionflux::ObjectBase::IFError{/if}(getErrorString(status.str(), "deserialize"));
        \}
    \}{if function.deserialize.stream.impl == ""}
    if (checkMagicWord)
        Ionflux::ObjectBase::unpackAndCheckMagicWord(source, 
            getMagicSyllableBase(), getMagicSyllable(), 
            Ionflux::ObjectBase::DATA_SIZE_INVALID, 
            this, "deserialize");{if haveBaseIFObject == 1}{foreach bc in class.base.ifobject}
	{$bc.name}::deserialize(source, 
	    Ionflux::ObjectBase::DATA_SIZE_INVALID, false);{/foreach}{/if}{foreach bc in class.base.other}{if bc.serialize == "true"}
	{$bc.name}::deserialize(source, 
	    Ionflux::ObjectBase::DATA_SIZE_INVALID, false);{/if}{/foreach}{foreach prop in property.private}{if prop.serialize == "true"}{ref deserializePropStream}{/if}{/foreach}{foreach prop in property.protected}{if prop.serialize == "true"}{ref deserializePropStream}{/if}{/foreach}{foreach var in variable.private}{if var.serialize == "true"}{ref deserializeVar}{/if}{/foreach}{foreach var in variable.protected}{if var.serialize == "true"}{ref deserializeVarStream}{/if}{/foreach}{foreach var in variable.public}{if var.serialize == "true"}{ref deserializeVarStream}{/if}{/foreach}{else}
{swrap 75 "    "}{$function.deserialize.stream.impl}{/swrap}{/if}
	return source.tellg();
\}

bool {$class.name}::serialize(Ionflux::ObjectBase::IFIOContext& ioCtx, bool addMagicWord) const
\{{if enableGuards == 1}
	Ionflux::ObjectBase::IFGuard functionGuard(guardMutex);{/if}{if function.deserialize.ioContext.impl == ""}
	std::ostream* os0 = Ionflux::ObjectBase::nullPointerCheck(
	    ioCtx.getOutputStream(), this, "serialize", "Output stream");
    return serialize(*os0, addMagicWord);{else}
{swrap 75 "    "}{$function.serialize.ioContext.impl}{/swrap}{/if}
\}

Ionflux::ObjectBase::DataSize {$class.name}::deserialize(Ionflux::ObjectBase::IFIOContext& ioCtx, Ionflux::ObjectBase::DataSize offset, bool checkMagicWord)
\{{if enableGuards == 1}
	Ionflux::ObjectBase::IFGuard functionGuard(guardMutex);{/if}{if function.deserialize.ioContext.impl == ""}
	std::istream* is0 = Ionflux::ObjectBase::nullPointerCheck(
	    ioCtx.getInputStream(), this, "deserialize", "Input stream");
    return deserialize(*is0, offset, checkMagicWord);{else}
{swrap 75 "    "}{$function.deserialize.ioContext.impl}{/swrap}{/if}
\}

Ionflux::ObjectBase::MagicSyllable {$class.name}::getMagicSyllable() const
\{
    return MAGIC_SYLLABLE_OBJECT;
\}

Ionflux::ObjectBase::MagicSyllable {$class.name}::getMagicSyllableBase() const
\{
    return MAGIC_SYLLABLE_BASE;
\}{/section}
