{section getFromXMLPrivateInner}{foreach ns in namespace}

namespace {$ns.name}
\{{/foreach}

class {$class.name};

namespace XMLUtils
\{

/// Initialize {$class.name} from TiXmlElement.
{swrap 75}void get{$class.name|uppercase(1)}(TiXmlElement* e0, 
    {foreach ns in namespace}{$ns.name}::{/foreach}{$class.name}& target, const std::string& elementName = {foreach ns in namespace}{$ns.name}::{/foreach}{$class.name}::XML_ELEMENT_NAME);{/swrap}

/// Create new {$class.name} from TiXmlElement.
{swrap 75}{foreach ns in namespace}{$ns.name}::{/foreach}{$class.name}* create{$class.name|uppercase(1)}(TiXmlElement* e0, const std::string& elementName = {foreach ns in namespace}{$ns.name}::{/foreach}{$class.name}::XML_ELEMENT_NAME);{/swrap}

\}{foreach ns in namespace}

\}{/foreach}

namespace Ionflux
\{

namespace ObjectBase
\{

namespace XMLUtils
\{

/// Initialize {$class.name} from TiXmlElement.
template<>
{swrap 75}void getObject0<{ref getFQName}>(TiXmlElement* e0, {ref getFQName}& target, const std::string& elementName);{/swrap}{if class.xml.haveChildClasses == 1}

/// Get object vector for polymorphic type {$class.name}.
template<>
void getObjVector<{ref getFQName},
    {ref getFQName}*>(TiXmlElement* e0, 
    std::vector<{ref getFQName}*>& target, 
    const std::string& elementName, 
    const std::string& childElementName);{/if}

\}

\}

\}{/section}
