{section createCreateFuncsImpl}

{swrap 75}{foreach ns in namespace}{$ns.name}::{/foreach}{$class.name}* {$class.name}::create(Ionflux::ObjectBase::IFObject* parentObject){/swrap}
\{
    {$class.name}* newObject = new {$class.name}();
    if (newObject == 0)
    \{{if class.create.allocationError != ""}
        throw {$class.create.allocationError};{else}
        return 0;{/if}
    \}
    if (parentObject != 0)
        parentObject->addLocalRef(newObject);
    return newObject;
\}{if enablePersistence == 1}

{swrap 75}{foreach ns in namespace}{$ns.name}::{/foreach}{$class.name}* {$class.name}::create({$project.persistence.namespace}::{$project.persistence.database}* initDatabase, int objectID){/swrap}
\{
    {$class.name}* newObject = new {$class.name}(initDatabase, objectID);
    if (newObject == 0)
    \{{if class.create.allocationError != ""}
        throw {$class.create.allocationError};{else}
        return 0;{/if}
    \}
    return newObject;
\}

{/if}{if enableExtendedCreate == 1}{ref createExtendedCreateFuncsImpl}{/if}{/section}
