{section createCopyFuncsImpl}

{swrap 75}{foreach ns in namespace}{$ns.name}::{/foreach}{$class.name}& {$class.name}::operator=(const {foreach ns in namespace}{$ns.name}::{/foreach}{$class.name}& other){/swrap}
\{{if enablePersistence == 1}
    database = other.database;
	if (database != 0)
	\{
	    if (persistent != other.persistent)
	    \{
	        if (persistent != 0)
	            delete persistent;
            persistent = new {$project.persistence.namespace}::{$class.persistence.backend}(*(other.getPersistent()));
            if (persistent == 0)
                throw {if class.persistence.errorClass != ""}{$class.persistence.errorClass}{else}PersistenceError{/if}("Could not allocate backend object!");
	    \}
    \} else
    \{
        if (other.persistent != 0)
		    throw {if class.persistence.errorClass != ""}{$class.persistence.errorClass}{else}PersistenceError{/if}("Database not set, "
		        "but backend object not null!");
    \}{/if}{if function.copy.impl != ""}
{swrap 75 "    "}{$function.copy.impl}{/swrap}{else}
if (this == &other)
    return *this;{foreach prop in property.protected}{if ( prop.copy == "true" ) && ( prop.persistent != "true" )}
set{$prop.name|uppercase(1)}(other.get{$prop.name|uppercase(1)}());{/if}{/foreach}{/if}
    return *this;
\}{if abstractClass == 0}

{swrap 75}{foreach ns in namespace}{$ns.name}::{/foreach}{$class.name}* {$class.name}::copy() const{/swrap}
\{{if enableCreate == 1}
    {$class.name}* new{$class.name|uppercase(1)} = create();{else}
    {$class.name}* new{$class.name|uppercase(1)} = 
        new {$class.name}();{if class.copy.allocationError != ""}
    if (new{$class.name|uppercase(1)} == 0)
        throw {$class.copy.allocationError};{/if}{/if}
    *new{$class.name|uppercase(1)} = *this;
    return new{$class.name|uppercase(1)};
\}{/if}{/section}
