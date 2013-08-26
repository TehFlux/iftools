{section getXMLPropertyChildElement}{if prop.valueType == "object"}
	d0 << {$prop.name}->getXML0(indentLevel, "pname=\\"{$prop.xml.child.name}\\"");{/if}{if prop.valueType == "string"}
	d0 << iws0 << "<prop pname=\\"{$prop.xml.child.name}\\">" 
	    << Ionflux::ObjectBase::XMLUtils::xmlEscape({$prop.name}) 
	    << "</prop>";{/if}{if ( prop.valueType == "float") || ( prop.valueType == "integer" )}
	d0 << iws0 << "<prop pname=\\"{$prop.xml.child.name}\\">" << {$prop.name} << "</prop>";{/if}{if prop.valueType == "bool"}
    d0 << iws0 << "<prop pname=\\"{$prop.xml.child.name}\\">" << static_cast<int>({$prop.name}) << "</prop>";{/if}{/section}
