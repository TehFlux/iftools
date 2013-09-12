{section createExtendedVectorAddFuncImpl}

{swrap 75}{if prop.element.addType == ""}{$prop.element.type}{else}{$prop.element.addType}{/if} {$class.name}::add{$prop.element.name|uppercase(1)}(){/swrap}
\{{if enableGuards == 1}
	IFGuard propertyGuard(guardMutex);{/if}{if prop.proxy.target != ""}{if prop.proxy.nullError != ""}
    if ({$prop.proxy.target} == 0)
        throw {$prop.proxy.nullError};{/if}
    return {$prop.proxy.target}->add{$prop.element.name|uppercase(1)}();{else}{if prop.check.maxSize != ""}
	if ({$prop.name}.size() >= {$prop.check.maxSize})
	    throw {$prop.check.sizeError};{/if}
	{if prop.element.addType == ""}{$prop.element.type}{else}{$prop.element.addType}{/if} o0{if prop.element.createExpr != ""} = {$prop.element.createExpr};{else};
\#error [create] Required option 'createExpr' not set on property element.{/if}
	add{$prop.element.name|uppercase(1)}(o0);
	return o0;{/if}
\}

{swrap 75}void {$class.name}::add{if prop.element.plural == ""}{$prop.element.name|uppercase(1)}s{else}{$prop.element.plural|uppercase(1)}{/if}(const std::vector<{$prop.element.type}>& new{if prop.element.plural == ""}{$prop.element.name|uppercase(1)}s{else}{$prop.element.plural|uppercase(1)}{/if}){/swrap}
\{{if enableGuards == 1}
	IFGuard propertyGuard(guardMutex);{/if}{if prop.proxy.target != ""}{if prop.proxy.nullError != ""}
    if ({$prop.proxy.target} == 0)
        throw {$prop.proxy.nullError};{/if}
    return {$prop.proxy.target}->add{$prop.element.name|uppercase(1)}(new{if prop.element.plural == ""}{$prop.element.name|uppercase(1)}s{else}{$prop.element.plural|uppercase(1)}{/if});{else}
	for (std::vector<{$prop.element.type}>::const_iterator i = new{if prop.element.plural == ""}{$prop.element.name|uppercase(1)}s{else}{$prop.element.plural|uppercase(1)}{/if}.begin(); 
	    i != new{if prop.element.plural == ""}{$prop.element.name|uppercase(1)}s{else}{$prop.element.plural|uppercase(1)}{/if}.end(); i++)
	    add{$prop.element.name|uppercase(1)}(*i);{/if}
\}

{swrap 75}void {$class.name}::add{if prop.element.plural == ""}{$prop.element.name|uppercase(1)}s{else}{$prop.element.plural|uppercase(1)}{/if}({foreach ns in namespace}{$ns.name}::{/foreach}{$class.name}* new{if prop.element.plural == ""}{$prop.element.name|uppercase(1)}s{else}{$prop.element.plural|uppercase(1)}{/if}){/swrap}
\{{if enableGuards == 1}
	IFGuard propertyGuard(guardMutex);{/if}{if prop.proxy.target != ""}{if prop.proxy.nullError != ""}
    if ({$prop.proxy.target} == 0)
        throw {$prop.proxy.nullError};{/if}
    return {$prop.proxy.target}->add{$prop.element.name|uppercase(1)}(new{if prop.element.plural == ""}{$prop.element.name|uppercase(1)}s{else}{$prop.element.plural|uppercase(1)}{/if});{else}
	for (unsigned int i = 0; 
	    i < new{if prop.element.plural == ""}{$prop.element.name|uppercase(1)}s{else}{$prop.element.plural|uppercase(1)}{/if}->getNum{if prop.element.plural == ""}{$prop.element.name|uppercase(1)}s{else}{$prop.element.plural|uppercase(1)}{/if}(); i++)
	    add{$prop.element.name|uppercase(1)}(new{if prop.element.plural == ""}{$prop.element.name|uppercase(1)}s{else}{$prop.element.plural|uppercase(1)}{/if}->get{$prop.element.name|uppercase(1)}(i));{/if}
\}{/section}
