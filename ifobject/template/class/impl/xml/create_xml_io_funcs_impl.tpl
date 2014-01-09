{import class.impl.xml.get_xml_property_attribute_value}{import class.impl.xml.get_xml_property_child_element}{import xml.xml_scan_properties}{ref xmlScanProperties}{import xml.xml_scan_base_classes}{ref xmlScanBaseClasses}{section createXMLIOFuncsImpl}

{swrap 75}std::string {$class.name}::getXMLElementName() const{/swrap}
\{
	return XML_ELEMENT_NAME;
\}

{swrap 75}std::string {$class.name}::getXMLAttributeData() const{/swrap}
\{{if enableGuards == 1}
	Ionflux::ObjectBase::IFGuard functionGuard(guardMutex);{/if}{if function.xml.attributeData.impl == ""}
	std::ostringstream d0;{$xaFirst = 1}{if haveBaseIFObject == 1}
	d0 << Ionflux::ObjectBase::IFObject::getXMLAttributeData();{$xaFirst = 0}{/if}{foreach base in class.base.other}{if base.xml.enabled == "true"}{if xaFirst == 0}
	if (d0.str().size() > 0)
	    d0 << " ";{/if}
	d0 << {$base.name}::getXMLAttributeData();{$xaFirst = 0}{/if}{/foreach}{foreach prop in property.protected}{if prop.xml.attribute.name != ""}{if xaFirst == 0}
	if (d0.str().size() > 0)
	    d0 << " ";{/if}
	d0 << {ref getXMLPropertyAttributeValue};{$xaFirst = 0}{/if}{/foreach}
	return d0.str();{else}
{swrap 75 "    "}{$function.xml.attributeData.impl}{/swrap}{/if}
\}

{swrap 75}void {$class.name}::getXMLChildData(std::string& target, unsigned int indentLevel) const{/swrap}
\{{if enableGuards == 1}
	Ionflux::ObjectBase::IFGuard functionGuard(guardMutex);{/if}{if function.xml.childData.impl == ""}
	std::ostringstream d0;{if haveXMLBase == 1}
	std::string bc0;{/if}{$xcFirst = 1}{if haveBaseIFObject == 1}
	Ionflux::ObjectBase::IFObject::getXMLChildData(bc0, indentLevel);
	d0 << bc0;{$xcFirst = 0}{/if}{foreach base in class.base.other}{if base.xml.enabled == "true"}
	{$base.name}::getXMLChildData(bc0, indentLevel);
	d0 << {if xcFirst == 0}"\\n" << {/if}bc0;{$xcFirst = 0}{/if}{/foreach}{if haveXMLChildElements == 1}
	std::string iws0 = Ionflux::ObjectBase::getIndent(indentLevel);
	bool haveBCData = false;{if haveXMLBase == 1}
	if (d0.str().size() > 0)
	    haveBCData = true;{/if}
	bool xcFirst = true;{foreach prop in property.protected}{if prop.xml.child.name != ""}{if prop.valueType != "object"}
	if (!xcFirst || haveBCData)
	    d0 << "\\n";{/if}{ref getXMLPropertyChildElement}{/if}{/foreach}{/if}
	target = d0.str();{else}
{swrap 75 "    "}{$function.xml.childData.impl}{/swrap}{/if}
\}

{swrap 75}void {$class.name}::loadFromXMLFile(const std::string& fileName){/swrap}
\{{if enableGuards == 1}
	Ionflux::ObjectBase::IFGuard functionGuard(guardMutex);{/if}{if function.xml.loadFromFile.impl == ""}
	Ionflux::ObjectBase::XMLUtils::loadFromXMLFile(
	    fileName, *this, getXMLElementName());{else}
{swrap 75 "    "}{$function.xml.loadFromFile.impl}{/swrap}{/if}
\}

{swrap 75}Ionflux::ObjectBase::XMLUtils::IFXMLObjectFactory* {$class.name}::getXMLObjectFactory(){/swrap}
\{
	static {foreach ns in namespace}{$ns.name}::{/foreach}XMLUtils::{$class.name}XMLFactory* fac0 = 0;
    if (fac0 == 0)
    \{
        fac0 = {foreach ns in namespace}{$ns.name}::{/foreach}XMLUtils::{$class.name}XMLFactory::create();
        fac0->addRef();{$bFacDeclared = 0}{if haveBaseIFObject == 1}
        Ionflux::ObjectBase::XMLUtils::IFXMLObjectFactory* bFac = 
            IFObject::getXMLObjectFactory();
        bFac->addFactory(fac0);{$bFacDeclared = 1}{/if}{foreach base in class.base.other}{if ( base.xml.enabled == "true" )}{if bFacDeclared == 0}
        Ionflux::ObjectBase::XMLUtils::IFXMLObjectFactory* bFac = 0;{$bFacDeclared = 1}{/if}
        bFac = {$base.name}::getXMLObjectFactory();
        bFac->addFactory(fac0);{/if}{/foreach}
    \}
    return fac0;
\}{/section}
