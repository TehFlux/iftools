{section createPropertyAccessorDecl}{if prop.bindings.disable != "true"}{if prop.style == "vector"}        
{swrap 75 "        "}virtual unsigned int getNum{if prop.element.plural == ""}{$prop.element.name|uppercase(1)}s{else}{$prop.element.plural|uppercase(1)}{/if}() const;{/swrap}
{swrap 75 "        "}virtual {$prop.element.type} get{$prop.element.name|uppercase(1)}(unsigned int elementIndex = 0) const;{/swrap}
{swrap 75 "		"}virtual int find{$prop.element.name|uppercase(1)}({if prop.element.findType == ""}{$prop.element.type}{else}{$prop.element.findType}{/if} needle, unsigned int occurence = 1) const;{/swrap}{if ( prop.readOnly != "true" ) && ( prop.protectedWrite != "true" )}{if prop.hideImpl != "true"}
{swrap 75 "        "}virtual std::vector<{$prop.element.type}>& get{if prop.element.plural == ""}{$prop.element.name|uppercase(1)}s{else}{$prop.element.plural|uppercase(1)}{/if}();{/swrap}{/if}
{swrap 75 "        "}virtual void add{$prop.element.name|uppercase(1)}({if prop.element.addType == ""}{$prop.element.type}{else}{$prop.element.addType}{/if} addElement);{/swrap}{if prop.extendedAddFuncs == "true"}{ref declareExtendedVectorAddFuncs}{/if}        
{swrap 75 "        "}virtual void remove{$prop.element.name|uppercase(1)}({if prop.element.removeType == ""}{$prop.element.type}{else}{$prop.element.removeType}{/if} removeElement);{/swrap}
{swrap 75 "		"}virtual void remove{$prop.element.name|uppercase(1)}Index(unsigned int removeIndex);{/swrap}{/if}{else}{if prop.style == "map"}
{swrap 75 "        "}virtual unsigned int getNum{if prop.element.plural == ""}{$prop.element.name|uppercase(1)}s{else}{$prop.element.plural|uppercase(1)}{/if}() const;{/swrap}
{swrap 75 "        "}virtual {$prop.element.type} get{$prop.element.name|uppercase(1)}({if prop.key.accessType != ""}{$prop.key.accessType}{else}{$prop.key.type}{/if} elementKey) const;{/swrap}
{if prop.readOnly != "true"}{if prop.hideImpl != "true"}
{swrap 75 "        "}virtual std::map<{$prop.key.type}, {$prop.element.type}>& get{if prop.element.plural == ""}{$prop.element.name|uppercase(1)}s{else}{$prop.element.plural|uppercase(1)}{/if}();{/swrap}{/if}
{swrap 75 "        "}virtual void add{$prop.element.name|uppercase(1)}({if prop.key.accessType != ""}{$prop.key.accessType}{else}{$prop.key.type}{/if} elementKey, {if prop.element.addType == ""}{$prop.element.type}{else}{$prop.element.addType}{/if} addElement);{/swrap}        
{swrap 75 "        "}virtual void remove{$prop.element.name|uppercase(1)}({if prop.key.accessType != ""}{$prop.key.accessType}{else}{$prop.key.type}{/if} elementKey);{/swrap}{/if}{else}{if ( prop.readOnly != "true" ) && ( prop.protectedWrite != "true" )}
{swrap 75 "        "}virtual void set{$prop.name|uppercase(1)}({$prop.setFromType} new{$prop.name|uppercase(1)});{/swrap}{/if}
{swrap 75 "        "}virtual {$prop.type} get{$prop.name|uppercase(1)}() const;{/swrap}{/if}{/if}{/if}{/section}
