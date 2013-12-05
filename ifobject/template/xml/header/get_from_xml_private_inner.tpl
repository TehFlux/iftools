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

\}{/foreach}{/section}
