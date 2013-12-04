{import xml.xml_get_prop_child_element_name}{import class.utils.get_numeric_prop_vector_type}{section getFromXMLInner}{foreach ns in namespace}

namespace {$ns.name}
\{{/foreach}

namespace XMLUtils
\{

{swrap 75}{foreach ns in namespace}{$ns.name}::{/foreach}{$class.name}* create{$class.name|uppercase(1)}(TiXmlElement* e0, const std::string& elementName){/swrap}
\{
    {ref getFQName}* co0 =
        {$class.name}::upcast(
            {$class.name}::getXMLObjectFactory()->createObject(
                e0, elementName));
    return co0;
\}

{swrap 75}void get{$class.name|uppercase(1)}(TiXmlElement* e0, 
    {foreach ns in namespace}{$ns.name}::{/foreach}{$class.name}& target, const std::string& elementName){/swrap}
\{
    {$class.name}::getXMLObjectFactory()->initObject(e0, 
        target, elementName);
\}

void get{$class.name|uppercase(1)}(const std::string& data, {foreach ns in namespace}{$ns.name}::{/foreach}{$class.name}& target)
\{
    {$class.name}::getXMLObjectFactory()->initObject(data, target);
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
    {$class.name|uppercase(1)}::getXMLObjectFactory()->initObject(
        e0, target, elementName);
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
        {ref getFQName}* co0 =
            {$class.name}::upcast(
                {$class.name}::getXMLObjectFactory()->createObject(
                    ce0, en0));
        target.push_back(co0);
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
            {ref getFQName}* co0 =
                {$class.name}::upcast(
                    {$class.name}::getXMLObjectFactory()->createObject(
                        ce0, en0));
            std::map<std::string, 
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
