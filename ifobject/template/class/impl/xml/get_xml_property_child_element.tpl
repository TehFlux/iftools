{section getXMLPropertyChildElement}{if prop.xml.child.elementName != ""}{$pe = prop.xml.child.elementName}{else}{if prop.style == "vector"}{$pe = "vec"}{else}{if prop.style == "map"}{$pe = "map"}{else}{$pe = "prop"}{/if}{/if}{/if}{if prop.valueType == "object"}
	d0 << {$prop.name}->getXML0(indentLevel, "pname=\\"{$prop.xml.child.name}\\"");{/if}{if prop.valueType == "string"}
	d0 << iws0 << "<{$pe} pname=\\"{$prop.xml.child.name}\\">" 
	    << Ionflux::ObjectBase::XMLUtils::xmlEscape({$prop.name}) 
	    << "</{$pe}>";{/if}{if ( prop.valueType == "float") || ( prop.valueType == "integer" )}
	d0 << iws0 << "<{$pe} pname=\\"{$prop.xml.child.name}\\">" << {$prop.name} << "</{$pe}>";{/if}{if prop.valueType == "bool"}
    d0 << iws0 << "<{$pe} pname=\\"{$prop.xml.child.name}\\">" << static_cast<int>({$prop.name}) << "</{$pe}>";{/if}{if prop.style == "vector"}{if prop.element.valueType == "object"}
    d0 << Ionflux::ObjectBase::XMLUtils::getXML0({$prop.name}, "{$pe}", "", 
        indentLevel, "pname=\\"{$prop.xml.child.name}\\"");{/if}{if ( prop.element.valueType == "float" ) || ( prop.element.valueType == "integer" )}
    d0 << Ionflux::ObjectBase::XMLUtils::getXML0({$prop.name}, "", 
        indentLevel, "pname=\\"{$prop.xml.child.name}\\"");{/if}{/if}{/section}
