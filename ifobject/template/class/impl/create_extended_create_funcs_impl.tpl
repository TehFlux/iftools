{section createExtendedCreateFuncsImpl}{foreach con in constructor.public}

{swrap 75}{foreach ns in namespace}{$ns.name}::{/foreach}{$class.name}* {$class.name}::create({foreach prm in con.param}{$prm.type} {$prm.name}{first}, {/first}{mid}, {/mid}{/foreach}, Ionflux::ObjectBase::IFObject* parentObject){/swrap}
\{
{swrap 75 "    "}{$class.name}* newObject = new {$class.name}({foreach prm in con.param}{$prm.name}{first}, {/first}{mid}, {/mid}{/foreach});{/swrap}
    if (newObject == 0)
    \{{if class.create.allocationError != ""}
        throw {$class.create.allocationError};{else}
        return 0;{/if}
    \}
    if (parentObject != 0)
        parentObject->addLocalRef(newObject);
    return newObject;
\}{/foreach}{/section}
