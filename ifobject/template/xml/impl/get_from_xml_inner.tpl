{import xml.xml_get_prop_child_element_name}{import class.utils.get_numeric_prop_vector_type}{section getFromXMLInner}{foreach ns in namespace}

namespace {$ns.name}
\{{/foreach}

namespace XMLUtils
\{

{swrap 75}void get{$class.name|uppercase(1)}(TiXmlElement* e0, 
    {foreach ns in namespace}{$ns.name}::{/foreach}{$class.name}& target, const std::string& elementName = {foreach ns in namespace}{$ns.name}::{/foreach}{$class.name}::XML_ELEMENT_NAME){/swrap}
\{{if function.xml.fromXML.impl == ""}
    Ionflux::ObjectBase::XMLUtils::checkElementNameOrError(e0, 
        elementName, "get{$class.name|uppercase(1)}");{if haveBaseIFObject == 1}
    Ionflux::ObjectBase::XMLUtils::getObject(e0, target);{else}{foreach base in class.base.other}{if ( base.xml.enabled == "true" ) && ( base.xml.getFunc != "" )}
    {$base.xml.getFunc}(e0, target, elementName);{/if}{/foreach}{/if}{if haveXMLAttributes == 1}
    // Get attribute data.
    std::string a0;{foreach prop in property.protected}{if prop.xml.attribute.name != ""}
    // Property: {$prop.name} ({$prop.valueType})
    a0 = Ionflux::ObjectBase::XMLUtils::getAttributeValue(
        e0, "{$prop.xml.attribute.name}"{if prop.xml.attribute.optional == "false"}, false{else}, true{/if});{if prop.valueType == "string"}
    target.set{$prop.name|uppercase(1)}(a0));{/if}{if prop.valueType == "float"}
    target.set{$prop.name|uppercase(1)}(::strtod(a0.c_str(), 0));{/if}{if prop.valueType == "integer"}
    target.set{$prop.name|uppercase(1)}(::strtol(a0.c_str(), 0, 10));{/if}{/if}{/foreach}{/if}{if haveXMLChildElements == 1}
    // Get child data.
    TiXmlElement* ce0 = e0->FirstChildElement();
    while (ce0 != 0)
    \{
        std::string en0(ce0->Value());
        std::string pName = 
            Ionflux::ObjectBase::XMLUtils::getAttributeValue(
                ce0, "pname", true);{foreach prop in property.protected}{if prop.xml.child.name != ""}{ref xmlGetPropChildElementName}
        // Property: {$prop.name} ({if prop.style == "vector"}vector[{$prop.element.valueType}]{else}{$prop.valueType}{/if})
        if ((en0 == "{$xmlCEName}") 
            && (pName == "{$prop.xml.child.name}"))
        \{{if prop.valueType == "string"}
            TiXmlElement* ce1 = ce0->FirstChildElement();
            if (ce1 != 0)
            \{
                std::string v0(ce1->Value());
                target.set{$prop.name|uppercase(1)}(v0);
            \}{/if}{if prop.valueType == "float"}
            a0 = Ionflux::ObjectBase::XMLUtils::getAttributeValue(
                ce0, "d", true);
            if (a0.size() > 0)
                target.set{$prop.name|uppercase(1)}(::strtod(a0.c_str(), 0));{/if}{if prop.valueType == "integer"}
            a0 = Ionflux::ObjectBase::XMLUtils::getAttributeValue(
                ce0, "d", true);
            if (a0.size() > 0)
                target.set{$prop.name|uppercase(1)}(::strtol(a0.c_str(), 0, 10));{/if}{if ( prop.valueType == "object" ) && ( prop.xml.getFunc != "" )}
            {$prop.type} co0 = {if prop.xml.createExpr != ""}{$prop.xml.createExpr}{else}
                {$prop.type|replace('*', '')}::create(){/if};
            {$prop.xml.getFunc}(ce0, *co0, "{$xmlCEName}");
            target.set{$prop.name|uppercase(1)}(co0);{/if}{if prop.style == "vector"}{if prop.element.valueType == "object"}
            std::vector<{$prop.element.type}> pv0;
            Ionflux::ObjectBase::XMLUtils::getObjVector<
                    {$prop.element.type|replace('*', '')}, 
                    {$prop.element.type}>(ce0, pv0, 
                "{$xmlCEName}", 
                {$prop.element.type|replace('*', '')}::XML_ELEMENT_NAME);
            target.add{if prop.element.plural != ""}{$prop.element.plural}{else}{$prop.element.name|uppercase(1)}s{/if}(pv0);{/if}{if ( prop.element.valueType == "integer" ) || ( prop.element.valueType == "float" )}{ref getNumericPropVectorType}
            Ionflux::ObjectBase::{$propEVecT} pv0;
            Ionflux::ObjectBase::XMLUtils::get{$propEVecT}(ce0, pv0);
            target.add{if prop.element.plural != ""}{$prop.element.plural}{else}{$prop.element.name|uppercase(1)}s{/if}(pv0);{/if}{/if}
        \}{/if}{/foreach}
        ce0 = ce0->NextSiblingElement();
    }{/if}{else}
{swrap 75 "    "}{$function.xml.fromXML.impl}{/swrap}{/if}
\}

void get{$class.name|uppercase(1)}(const std::string& data, {foreach ns in namespace}{$ns.name}::{/foreach}{$class.name}& target)
\{
    TiXmlDocument d0;
    /* NOTE: Probably a peculiarity of tinyxml, there must be at least one 
             character after the data. Or there could of course also be 
             something wrong with how tinyxml is used here. Anyway, this 
             seems to work. */
    std::string d1(data);
    d1.append(1, ' ');
    if (!d0.Parse(d1.c_str(), 0, TIXML_ENCODING_UTF8))
        throw {$class.xml.exception}("[get{$class.name|uppercase(1)}] "
            "Unable to parse XML data.");
    TiXmlElement* m0 = 
        Ionflux::ObjectBase::XMLUtils::findElementByNameOrError(
            d0.RootElement(), 
            {foreach ns in namespace}{$ns.name}::{/foreach}{$class.name}::XML_ELEMENT_NAME);
    get{$class.name|uppercase(1)}(m0, target);
\}

\}{foreach ns in namespace}

\}{/foreach}

namespace Ionflux
\{

namespace ObjectBase
\{

namespace XMLUtils
\{

template<>
{swrap 75}void getObject0<{foreach ns in namespace}{$ns.name}::{/foreach}{$class.name}>(TiXmlElement* e0, 
    {foreach ns in namespace}{$ns.name}::{/foreach}{$class.name}& target, const std::string& elementName){/swrap}
\{
    // <---- DEBUG ----- //
    std::cerr << "[getObject0] Called for class '{$class.name}'." 
        << std::endl;
    // ----- DEBUG ----> */
    if (elementName.size() == 0)
        {foreach ns in namespace}{$ns.name}::{/foreach}XMLUtils::get{$class.name|uppercase(1)}(e0, target);
    else
        {foreach ns in namespace}{$ns.name}::{/foreach}XMLUtils::get{$class.name|uppercase(1)}(e0, target, elementName);
\}

\}

\}

\}{/section}
