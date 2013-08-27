{import class.check_features}{import xml.xml_scan_properties}{ref xmlScanProperties}{ref checkFeatures}{import class.insert_gpl_disclaimer}{import xml.impl.project_info}{ref projectInfo}
\#include <cstdlib>
\#include <string>
\#include <sstream>
\#include "{$project.includePrefix}/{$class.name}.hpp"{foreach base in class.base.other}{if base.xml.include != ""}
\#include "{$base.xml.include}_xml_private.hpp"
\#include "{$base.xml.include}_xml.hpp"{/if}{/foreach}
\#include "{$project.includePrefix}/{$class.name}_xml_private.hpp"
\#include "{$project.includePrefix}/{$class.name}_xml.hpp"{foreach ns in namespace}

namespace {$ns.name}
\{{/foreach}

namespace XMLUtils
\{

{swrap 75}void get{$class.name|uppercase(1)}(TiXmlElement* e0, 
    {foreach ns in namespace}{$ns.name}::{/foreach}{$class.name}& target, const std::string& elementName){/swrap}
\{{if function.xml.fromXML.impl == ""}
    Ionflux::ObjectBase::XMLUtils::checkElementNameOrError(e0, 
        elementName, "get{$class.name|uppercase(1)}");{if haveBaseIFObject == 1}
    Ionflux::ObjectBase::XMLUtils::getObject(e0, target);{else}{foreach base in class.base.other}{if ( base.xml.enabled == "true" ) && ( base.xml.getFunc != "" )}
    {$base.xml.getFunc}(e0, target);{/if}{/foreach}{/if}{if haveXMLAttributes == 1}
    // Get attribute data.
    std::string a0;{foreach prop in property.protected}{if prop.xml.attribute.name != ""}
    a0 = Ionflux::ObjectBase::XMLUtils::getAttributeValue(
        e0, "{$prop.xml.attribute.name}"{if prop.xml.attribute.optional == "false"}, false{else}, true{/if});{if prop.valueType == "string"}
    target.set{$prop.name|uppercase(1)}(a0));{/if}{if prop.valueType == "float"}
    target.set{$prop.name|uppercase(1)}(::strtod(a0.c_str(), 0));{/if}{if prop.valueType == "integer"}
    target.set{$prop.name|uppercase(1)}(::strtol(a0.c_str(), 0, 10));{/if}{/if}{/foreach}{/if}{if haveXMLChildElements == 1}
    // TODO: Get child data.{/if}{else}
{swrap 75 "    "}{$function.xml.fromXML.impl}{/swrap}{/if}
\}

{swrap 75}void getObject0(TiXmlElement* e0, 
    {foreach ns in namespace}{$ns.name}::{/foreach}{$class.name}& target, const std::string& elementName){/swrap}
\{
    if (elementName.size() == 0)
        get{$class.name|uppercase(1)}(e0, target);
    else
        get{$class.name|uppercase(1)}(e0, target, elementName);
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

/** \\file {$class.name}_xml.cpp
 * \\brief {$class.shortDesc} XML implementation.
 */

