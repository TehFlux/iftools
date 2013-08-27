{import xml.xml_get_prop_child_element_name}{section getXMLPropertyChildElement}{ref xmlGetPropChildElementName}{if prop.valueType == "object"}
	d0 << {$prop.name}->getXML0(indentLevel, "pname=\\"{$prop.xml.child.name}\\"");{/if}{if prop.valueType == "string"}
	d0 << iws0 << "<{$xmlCEName} pname=\\"{$prop.xml.child.name}\\">" 
	    << Ionflux::ObjectBase::XMLUtils::xmlEscape({$prop.name}) 
	    << "</{$xmlCEName}>";{/if}{if ( prop.valueType == "float") || ( prop.valueType == "integer" )}
	d0 << iws0 << "<{$xmlCEName} pname=\\"{$prop.xml.child.name}\\" d=\\"" << {$prop.name} << "\\" />";{/if}{if prop.valueType == "bool"}
    d0 << iws0 << "<{$xmlCEName} pname=\\"{$prop.xml.child.name}\\" d=\\"" << static_cast<int>({$prop.name}) << "\\" />";{/if}{if prop.style == "vector"}{if prop.element.valueType == "object"}
    d0 << Ionflux::ObjectBase::XMLUtils::getXML0({$prop.name}, "{$xmlCEName}", "", 
        indentLevel, "pname=\\"{$prop.xml.child.name}\\"");{/if}{if ( prop.element.valueType == "float" ) || ( prop.element.valueType == "integer" )}
    d0 << Ionflux::ObjectBase::XMLUtils::getXML0({$prop.name}, "", 
        indentLevel, "pname=\\"{$prop.xml.child.name}\\"");{/if}{/if}{/section}
