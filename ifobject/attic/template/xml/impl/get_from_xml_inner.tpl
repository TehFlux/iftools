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

\}{/foreach}{/section}
