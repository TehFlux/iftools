{section getFromXMLInner}{foreach ns in namespace}

namespace {$ns.name}
\{{/foreach}

class {$class.name};

namespace XMLUtils
\{

{swrap 75}void get{$class.name|uppercase(1)}(const std::string& data, {foreach ns in namespace}{$ns.name}::{/foreach}{$class.name}& target);{/swrap}

\}{foreach ns in namespace}

\}{/foreach}{/section}
