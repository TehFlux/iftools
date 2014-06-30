{section createSerializeFuncsImpl}

bool {$class.name}::serialize(std::string& target) const
\{{if haveBaseIFObject == 1}{foreach bc in class.base.ifobject}
	if (!{$bc.name}::serialize(target))
		return false;{/foreach}{/if}{foreach bc in class.base.other}{if bc.serialize == "true"}
	if (!{$bc.name}::serialize(target))
		return false;{/if}{/foreach}{foreach prop in property.private}{if prop.serialize == "true"}{ref serializeProp}{/if}{/foreach}{foreach prop in property.protected}{if prop.serialize == "true"}{ref serializeProp}{/if}{/foreach}{foreach var in variable.private}{if var.serialize == "true"}{ref serializeVar}{/if}{/foreach}{foreach var in variable.protected}{if var.serialize == "true"}{ref serializeVar}{/if}{/foreach}{foreach var in variable.public}{if var.serialize == "true"}{ref serializeVar}{/if}{/foreach}
	return true;
\}

int {$class.name}::deserialize(const std::string& source, int offset)
\{{if haveBaseIFObject == 1}{foreach bc in class.base.ifobject}
	offset = {$bc.name}::deserialize(source, offset);
	if (offset < 0)
		return -1;{/foreach}{/if}{foreach bc in class.base.other}{if bc.serialize == "true"}
	offset = {$bc.name}::deserialize(source, offset);
	if (offset < 0)
		return false;{/if}{/foreach}{foreach prop in property.private}{if prop.serialize == "true"}{ref deserializeProp}{/if}{/foreach}{foreach prop in property.protected}{if prop.serialize == "true"}{ref deserializeProp}{/if}{/foreach}{foreach var in variable.private}{if var.serialize == "true"}{ref deserializeVar}{/if}{/foreach}{foreach var in variable.protected}{if var.serialize == "true"}{ref deserializeVar}{/if}{/foreach}{foreach var in variable.public}{if var.serialize == "true"}{ref deserializeVar}{/if}{/foreach}
	return offset;
\}{/section}
