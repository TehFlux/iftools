{section createExtendedMapAddFuncImpl}

{swrap 75}{if prop.element.addType == ""}{$prop.element.type}{else}{$prop.element.addType}{/if} {$class.name}::add{$prop.element.name|uppercase(1)}({if prop.key.accessType != ""}{$prop.key.accessType}{else}{$prop.key.type}{/if} elementKey){/swrap}
\{{if enableGuards == 1}
	IFGuard propertyGuard(guardMutex);{/if}{if prop.proxy.target != ""}{if prop.proxy.nullError != ""}
    if ({$prop.proxy.target} == 0)
        throw {$prop.proxy.nullError};{/if}
    return {$prop.proxy.target}->add{$prop.element.name|uppercase(1)}(elementKey);{else}{if prop.check.maxSize != ""}
	if ({$prop.name}.size() >= {$prop.check.maxSize})
	    throw {$prop.check.sizeError};{/if}
	{if prop.element.addType == ""}{$prop.element.type}{else}{$prop.element.addType}{/if} o0 = {$prop.element.createExpr};
	add{$prop.element.name|uppercase(1)}(elementKey, o0);
	return o0;{/if}
\}

{swrap 75}void {$class.name}::add{if prop.element.plural == ""}{$prop.element.name|uppercase(1)}s{else}{$prop.element.plural|uppercase(1)}{/if}(std::vector<{$prop.element.type}>& new{if prop.element.plural == ""}{$prop.element.name|uppercase(1)}s{else}{$prop.element.plural|uppercase(1)}{/if}){/swrap}
\{{if enableGuards == 1}
	IFGuard propertyGuard(guardMutex);{/if}{if prop.proxy.target != ""}{if prop.proxy.nullError != ""}
    if ({$prop.proxy.target} == 0)
        throw {$prop.proxy.nullError};{/if}
    return {$prop.proxy.target}->add{$prop.element.name|uppercase(1)}(new{if prop.element.plural == ""}{$prop.element.name|uppercase(1)}s{else}{$prop.element.plural|uppercase(1)}{/if});{else}
	for (std::map<{$prop.key.type}, {$prop.element.type}>::iterator i = new{if prop.element.plural == ""}{$prop.element.name|uppercase(1)}s{else}{$prop.element.plural|uppercase(1)}{/if}.begin(); 
	    i != new{if prop.element.plural == ""}{$prop.element.name|uppercase(1)}s{else}{$prop.element.plural|uppercase(1)}{/if}.end(); i++)
	    add{$prop.element.name|uppercase(1)}((*i).first, (*i).second);{/if}
\}

{swrap 75}void {$class.name}::add{if prop.element.plural == ""}{$prop.element.name|uppercase(1)}s{else}{$prop.element.plural|uppercase(1)}{/if}({foreach ns in namespace}{$ns.name}::{/foreach}{$class.name}* new{if prop.element.plural == ""}{$prop.element.name|uppercase(1)}s{else}{$prop.element.plural|uppercase(1)}{/if}){/swrap}
\{{if enableGuards == 1}
	IFGuard propertyGuard(guardMutex);{/if}{if prop.proxy.target != ""}{if prop.proxy.nullError != ""}
    if ({$prop.proxy.target} == 0)
        throw {$prop.proxy.nullError};{/if}
    return {$prop.proxy.target}->add{$prop.element.name|uppercase(1)}(new{if prop.element.plural == ""}{$prop.element.name|uppercase(1)}s{else}{$prop.element.plural|uppercase(1)}{/if});{else}
	for (std::map<{$prop.key.type}, {$prop.element.type}>::iterator i = new{if prop.element.plural == ""}{$prop.element.name|uppercase(1)}s{else}{$prop.element.plural|uppercase(1)}{/if}.{$prop.name}.begin(); 
	    i != new{if prop.element.plural == ""}{$prop.element.name|uppercase(1)}s{else}{$prop.element.plural|uppercase(1)}{/if}.{$prop.name}.end(); i++)
	    add{$prop.element.name|uppercase(1)}((*i).first, (*i).second);{/if}
\}{/section}
