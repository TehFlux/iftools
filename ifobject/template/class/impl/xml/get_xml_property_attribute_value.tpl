{section getXMLPropertyAttributeValue}"{$prop.xml.attribute.name}=\\"" << {if prop.valueType == "string"}
    Ionflux::ObjectBase::XMLUtils::xmlEscape({$prop.name}){/if}{if ( prop.valueType == "float" ) || ( prop.valueType == "integer" )}{$prop.name}{/if}{if prop.valueType == "bool"}static_cast<int>({$prop.name}){/if} << "\\""{/section}
