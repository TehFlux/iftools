{import class.impl.xml.get_xml_property_attribute_value}{section createXMLIOFuncsImpl}

{swrap 75}std::string {$class.name}::getXMLElementName() const{/swrap}
\{
	return XML_ELEMENT_NAME;
\}

{swrap 75}std::string {$class.name}::getXMLAttributeData() const{/swrap}
\{{if enableGuards == 1}
	Ionflux::ObjectBase::IFGuard functionGuard(guardMutex);{/if}{if function.xml.attributeData.impl == ""}
	std::ostringstream d0;{foreach prop in property.protected}{if prop.xml.attribute.name != ""}
	d0 << {notfirst}" " << {/notfirst}{ref getXMLPropertyAttributeValue};{/if}{/foreach}
	return d0.str();{else}
{swrap 75 "    "}{$function.xml.attributeData.impl}{/swrap}{/if}
\}

{swrap 75}void {$class.name}::getXMLChildData(std::string& target, unsigned int indentLevel) const{/swrap}
\{{if enableGuards == 1}
	Ionflux::ObjectBase::IFGuard functionGuard(guardMutex);{/if}{if function.xml.childData.impl == ""}
	// TODO: Implementation.{else}
{swrap 75 "    "}{$function.xml.childData.impl}{/swrap}{/if}
\}{/section}
