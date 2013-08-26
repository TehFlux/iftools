{section createParamFuncsImpl}{foreach prm in class.param}

{swrap 75}void {$class.name}::set{$prm.name}(Ionflux::ObjectBase::IFParamID paramID, {$prm.type} paramValue){/swrap}
\{{if prm.impl.set != ""}
    {$prm.impl.set}{/if}{foreach prop in property.protected}{if prop.type == prm.type}
    if (paramID == "{$prop.name}")
    \{
        set{$prop.name|uppercase(1)}(paramValue);
        return;
    \}{/if}{/foreach}{if prm.notExistsError != ""}
    throw {$prm.notExistsError};{/if}
\}

{swrap 75}{$prm.type} {$class.name}::get{$prm.name}(Ionflux::ObjectBase::IFParamID paramID){/swrap}
\{{if prm.impl.get != ""}
    {$prm.impl.get}{/if}{foreach prop in property.protected}{if prop.type == prm.type}
    if (paramID == "{$prop.name}")
        return get{$prop.name|uppercase(1)}();{/if}{/foreach}{if prm.notExistsError != ""}
    throw {$prm.notExistsError};{/if}
\}{/foreach}{/section}
