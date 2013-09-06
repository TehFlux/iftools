{import xml.xml_get_prop_child_element_name}{section getXMLPropertyChildElement}{ref xmlGetPropChildElementName}{if prop.xml.child.generatorFunc.name != ""}
    d0 << {$prop.xml.child.generatorFunc.name}(
        {$prop.name}, indentLevel, "pname=\\"{$prop.xml.child.name}\\""{if prop.xml.child.generatorFunc.args != ""}, {$prop.xml.child.generatorFunc.args}{/if});
    xcFirst = false;{else}{if prop.valueType == "object"}
    if ({$prop.name} != 0)
    \{
        if (!xcFirst || haveBCData)
            d0 << "\\n";
	    d0 << {$prop.name}->getXML0(indentLevel, "pname=\\"{$prop.xml.child.name}\\"");
	    xcFirst = false;
    \}{/if}{if prop.valueType == "string"}
	d0 << iws0 << "<{$xmlCEName} pname=\\"{$prop.xml.child.name}\\">" 
	    << Ionflux::ObjectBase::XMLUtils::xmlEscape({$prop.name}) 
	    << "</{$xmlCEName}>";
    xcFirst = false;{/if}{if ( prop.valueType == "float") || ( prop.valueType == "integer" )}
	d0 << iws0 << "<{$xmlCEName} pname=\\"{$prop.xml.child.name}\\" d=\\"" << {$prop.name} << "\\" />";
	xcFirst = false;{/if}{if prop.valueType == "bool"}
    d0 << iws0 << "<{$xmlCEName} pname=\\"{$prop.xml.child.name}\\" d=\\"" << static_cast<int>({$prop.name}) << "\\" />";
    xcFirst = false;{/if}{if prop.style == "vector"}{if prop.element.valueType == "object"}
    d0 << Ionflux::ObjectBase::XMLUtils::getXML0({$prop.name}, "{$xmlCEName}", "", 
        indentLevel, "pname=\\"{$prop.xml.child.name}\\"");
    xcFirst = false;{/if}{if ( prop.element.valueType == "float" ) || ( prop.element.valueType == "integer" )}
    d0 << Ionflux::ObjectBase::XMLUtils::getXML0({$prop.name}, "", 
        indentLevel, "pname=\\"{$prop.xml.child.name}\\"");
    xcFirst = false;{/if}{/if}{if prop.style == "map"}{if prop.key.type = "std::string"}{if prop.element.valueType == "object"}
    d0 << Ionflux::ObjectBase::XMLUtils::getXML0({$prop.name}, "{$xmlCEName}", 
        "", indentLevel, "pname=\\"{$prop.xml.child.name}\\"");
    xcFirst = false;{/if}{/if}{/if}{/if}{/section}
