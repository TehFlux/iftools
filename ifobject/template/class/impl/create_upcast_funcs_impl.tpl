{section createUpcastFuncsImpl}

{swrap 75}{foreach ns in namespace}{$ns.name}::{/foreach}{$class.name}* {$class.name}::upcast(Ionflux::ObjectBase::IFObject* other){/swrap}
\{
    return dynamic_cast<{$class.name}*>(other);
\}{/section}
