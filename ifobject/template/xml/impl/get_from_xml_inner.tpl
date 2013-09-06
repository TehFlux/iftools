{import xml.xml_get_prop_child_element_name}{import class.utils.get_numeric_prop_vector_type}{section getFromXMLInner}{foreach ns in namespace}

namespace {$ns.name}
\{{/foreach}

namespace XMLUtils
\{

{swrap 75}{foreach ns in namespace}{$ns.name}::{/foreach}{$class.name}* create{$class.name|uppercase(1)}(TiXmlElement* e0, const std::string& elementName){/swrap}
\{{if function.xml.create.impl == ""}
    std::string en0(e0->Value());
    {$class.name}* o0 = 0;
    if (en0 == elementName)
    \{{if class.isAbstract != 1}
        // default ({$class.name})
        o0 = {$class.name}::create();
        get{$class.name|uppercase(1)}(e0, *o0, en0);{else}
        throw Ionflux::ObjectBase::IFError(
            "[create{$class.name|uppercase(1)}] "
            "Cannot create instance of abstract class.");{/if}
    \}{foreach cc in class.xml.childClass} else
    if (en0 == {$cc.name}::XML_ELEMENT_NAME)
    \{
        // {$cc.name}
        {$cc.name}* o1 = {$cc.name}::create();
        {$cc.getFunc}(e0, *o1, en0);
        o0 = o1;
    \}{/foreach} else
    \{
        std::ostringstream status;
        status << "[create{$class.name|uppercase(1)}] "
            << "Unexpected child element name: '" << en0 << "'";
        throw Ionflux::ObjectBase::IFError(status.str());
    \}
    return o0;{else}
{swrap 75 "    "}{$function.xml.create.impl}{/swrap}{/if}
\}

{swrap 75}void get{$class.name|uppercase(1)}(TiXmlElement* e0, 
    {foreach ns in namespace}{$ns.name}::{/foreach}{$class.name}& target, const std::string& elementName){/swrap}
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
        if ({if prop.valueType == "object"}pName == "{$prop.xml.child.name}"{else}(pName == "{$prop.xml.child.name}") 
            && (en0 == "{$xmlCEName}"){/if})
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
                target.set{$prop.name|uppercase(1)}(::strtol(a0.c_str(), 0, 10));{/if}{if prop.valueType == "object"}{if prop.xml.createFunc != ""}
            {$prop.type} co0 = 
                {$prop.xml.createFunc}(ce0, en0);
            target.set{$prop.name|uppercase(1)}(co0);{else}
\#error [xmlio] Required option 'xml.createFunc' missing on property '{$class.name}::{$prop.name}'.{/if}{/if}{if prop.style == "vector"}{if prop.element.valueType == "object"}
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
    /* <---- DEBUG ----- //
    std::cerr << "[getObject0] Called for class '{$class.name}'." 
        << std::endl;
    // ----- DEBUG ----> */
    if (elementName.size() == 0)
        {foreach ns in namespace}{$ns.name}::{/foreach}XMLUtils::get{$class.name|uppercase(1)}(e0, target);
    else
        {foreach ns in namespace}{$ns.name}::{/foreach}XMLUtils::get{$class.name|uppercase(1)}(e0, target, elementName);
\}{if class.xml.haveChildClasses == 1}

template<>
void getObjVector<{ref getFQName},
    {ref getFQName}*>(TiXmlElement* e0, 
    std::vector<{ref getFQName}*>& target, 
    const std::string& elementName, 
    const std::string& childElementName)
\{
    checkElementNameOrError(e0, elementName, 
        "getObjVector<{$class.name}>");
    TiXmlElement* ce0 = e0->FirstChildElement();
    while (ce0 != 0)
    \{
        // Iterate over vector entries.
        std::string en0(ce0->Value());
        if (en0 == childElementName)
        \{{if class.isAbstract != 1}
            // default ({$class.name})
            {ref getFQName}* co0 = 
                {ref getFQName}::create();
            getObject0(ce0, *co0, en0);
            target.push_back(co0);{else}
            throw Ionflux::ObjectBase::IFError(
                "[getObjVector<{$class.name}>] "
                "Cannot create instance of abstract class.");{/if}
        \}{foreach cc in class.xml.childClass} else
        if (en0 == 
            {$cc.name}::XML_ELEMENT_NAME)
        \{
            // {$cc.name}
            {$cc.name}* co0 = 
                {$cc.name}::create();
            getObject0(ce0, *co0, en0);
            target.push_back(co0);
        \}{/foreach} else
        \{
            std::ostringstream status;
            status << "[getObjVector<{$class.name}>] "
                << "Unexpected child element name: '" << en0 << "'";
            throw Ionflux::ObjectBase::IFError(status.str());
        \}
        ce0 = ce0->NextSiblingElement();
    \}
\}

template<>
void getObjMap<{ref getFQName},
    {ref getFQName}*>(TiXmlElement* e0, 
    std::map<std::string, {ref getFQName}*>& target, 
    const std::string& elementName, 
    const std::string& childElementName)
\{
    checkElementNameOrError(e0, elementName, "getObjMap<{$class.name}>");
    TiXmlElement* ee0 = e0->FirstChildElement();
    while (ee0 != 0)
    \{
        // Iterate over map entries.
        std::string en0(ee0->Value());
        if (en0 == "entry")
        \{
            std::string k = getAttributeValue(ee0, "key", false);
            TiXmlElement* ce0 = ee0->FirstChildElement();
            if (ce0 == 0)
            \{
                std::ostringstream status;
                status << "[getObjMap<{$class.name}>] "
                    << "Missing value for key: '" << k << "'";
                throw Ionflux::ObjectBase::IFError(status.str());
            \}
            std::string en1(ce0->Value());
            {ref getFQName}* co0 = 0;
            // Add an object of the appropriate class. 
            if (en1 == childElementName)
            \{{if class.isAbstract != 1}
                // default ({$class.name})
                co0 = {ref getFQName}::create();
                getObject0(ce0, *co0, childElementName);{else}
                throw Ionflux::ObjectBase::IFError(
                    "[getObjVector<{$class.name}>] "
                    "Cannot create instance of abstract class.");{/if}
            \}{foreach cc in class.xml.childClass} else
            if (en1 == 
                {$cc.name}::XML_ELEMENT_NAME)
            \{
                // {$cc.name}
                {$cc.name}* co1 = 
                    {$cc.name}::create();
                getObject0(ce0, *co0, childElementName);
                co0 = co1;
            \}{/foreach} else
            \{
                std::ostringstream status;
                status << "[getObjMap<{$class.name}>] "
                    << "Unexpected child element name: '" << en1 << "'";
                throw Ionflux::ObjectBase::IFError(status.str());
            \}
            typename std::map<std::string, 
                {ref getFQName}*>::iterator j = target.find(k);
            if (j != target.end())
            \{
                std::ostringstream status;
                status << "[getObjMap<{$class.name}>] Duplicate key: '" 
                    << k << "'";
                throw Ionflux::ObjectBase::IFError(status.str());
            \}
            target[k] = co0;
        \}
        ee0 = ee0->NextSiblingElement();
    \}
\}{/if}

\}

\}

\}{/section}
