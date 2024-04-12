{section createPropertyAccessorImpl}{if prop.style == "vector"}

{swrap 75}unsigned int {$class.name}::getNum{if prop.element.plural == ""}{$prop.element.name|uppercase(1)}s{else}{$prop.element.plural|uppercase(1)}{/if}() const{/swrap}
\{{if enableGuards == 1}
	IFGuard propertyGuard(guardMutex);{/if}{if prop.proxy.target != ""}{if prop.proxy.nullError != ""}
	if ({$prop.proxy.target} == 0)
		throw {$prop.proxy.nullError};{/if}
	return {$prop.proxy.target}->getNum{if prop.element.plural == ""}{$prop.element.name|uppercase(1)}s{else}{$prop.element.plural|uppercase(1)}{/if}();{else}
	return {$prop.name}.size();{/if}
\}

{swrap 75}{$prop.element.type} {$class.name}::get{$prop.element.name|uppercase(1)}(unsigned int elementIndex) const{/swrap}
\{{if enableGuards == 1}
	IFGuard propertyGuard(guardMutex);{/if}{if prop.proxy.target != ""}{if prop.proxy.nullError != ""}
	if ({$prop.proxy.target} == 0)
		throw {$prop.proxy.nullError};{/if}
	return {$prop.proxy.target}->get{$prop.element.name|uppercase(1)}(elementIndex);{else}
	if (elementIndex < {$prop.name}.size())
		return {$prop.name}[elementIndex];
	return {if prop.element.defaultValue != ""}{$prop.element.defaultValue}{else}0{/if};{/if}
\}

{swrap 75}int {$class.name}::find{$prop.element.name|uppercase(1)}({if prop.element.findType == ""}{$prop.element.type}{else}{$prop.element.findType}{/if} needle, unsigned int occurence) const{/swrap}
\{{if enableGuards == 1}
	IFGuard propertyGuard(guardMutex);{/if}{if prop.proxy.target != ""}{if prop.proxy.nullError != ""}
	if ({$prop.proxy.target} == 0)
		throw {$prop.proxy.nullError};{/if}
	return {$prop.proxy.target}->find{$prop.element.name|uppercase(1)}(needle, occurence);{else}
	bool found = false;
	{$prop.element.type} current{$prop.element.name|uppercase(1)} = {if prop.element.defaultValue != ""}{$prop.element.defaultValue}{else}0{/if};
	unsigned int i = 0;
	while (!found 
		&& (i < {$prop.name}.size()))
	\{
		current{$prop.element.name|uppercase(1)} = {$prop.name}[i];
		if (current{$prop.element.name|uppercase(1)} == needle)
		\{
			if (occurence == 1)
				found = true;
			else
				occurence--;
		\} else
			i++;
	\}
	if (found)
		return i;
	return -1;{/if}
\}{if ( prop.readOnly != "true" ) || ( prop.protectedWrite == "true" )}{if prop.hideImpl != "true"}

{swrap 75}std::vector<{$prop.element.type}>& {$class.name}::get{if prop.element.plural == ""}{$prop.element.name|uppercase(1)}s{else}{$prop.element.plural|uppercase(1)}{/if}(){/swrap}
\{{if enableGuards == 1}
	IFGuard propertyGuard(guardMutex);{/if}{if prop.proxy.target != ""}{if prop.proxy.nullError != ""}
	if ({$prop.proxy.target} == 0)
		throw {$prop.proxy.nullError};{/if}
	return {$prop.proxy.target}->get{if prop.element.plural == ""}{$prop.element.name|uppercase(1)}s{else}{$prop.element.plural|uppercase(1)}{/if}();{else}
	return {$prop.name};{/if}
\}{/if}

{swrap 75}void {$class.name}::add{$prop.element.name|uppercase(1)}({if prop.element.addType == ""}{$prop.element.type}{else}{$prop.element.addType}{/if} addElement){/swrap}
\{{if enableGuards == 1}
	IFGuard propertyGuard(guardMutex);{/if}{if prop.proxy.target != ""}{if prop.proxy.nullError != ""}
	if ({$prop.proxy.target} == 0)
		throw {$prop.proxy.nullError};{/if}
	return {$prop.proxy.target}->add{$prop.element.name|uppercase(1)}(addElement);{else}{if prop.check.maxSize != ""}
	if ({$prop.name}.size() >= {$prop.check.maxSize})
		throw {$prop.check.sizeError};{/if}
	{if prop.element.managed == "true"}addLocalRef(addElement);
	{/if}{$prop.name}.push_back(addElement);{/if}
\}{if prop.extendedAddFuncs == "true"}{ref createExtendedVectorAddFuncImpl}{/if}

{swrap 75}void {$class.name}::remove{$prop.element.name|uppercase(1)}({if prop.element.removeType == ""}{$prop.element.type}{else}{$prop.element.removeType}{/if} removeElement){/swrap}
\{{if enableGuards == 1}
	IFGuard propertyGuard(guardMutex);{/if}{if prop.proxy.target != ""}{if prop.proxy.nullError != ""}
	if ({$prop.proxy.target} == 0)
		throw {$prop.proxy.nullError};{/if}
	return {$prop.proxy.target}->remove{$prop.element.name|uppercase(1)}(removeElement);{else}
	bool found = false;
	{$prop.element.type} current{$prop.element.name|uppercase(1)} = {if prop.element.defaultValue != ""}{$prop.element.defaultValue}{else}0{/if};
	unsigned int i = 0;
	while (!found 
		&& (i < {$prop.name}.size()))
	\{
		current{$prop.element.name|uppercase(1)} = {$prop.name}[i];
		if (current{$prop.element.name|uppercase(1)} == removeElement)
			found = true;
		else
			i++;
	\}
	if (found)
	\{
		{$prop.name}.erase({$prop.name}.begin() + i);{if prop.element.managed == "true"}
		if (current{$prop.element.name|uppercase(1)} != {if prop.element.defaultValue != ""}{$prop.element.defaultValue}{else}0{/if})
			removeLocalRef(current{$prop.element.name|uppercase(1)});{/if}
	\}{/if}
\}

{swrap 75}void {$class.name}::remove{$prop.element.name|uppercase(1)}Index(unsigned int removeIndex){/swrap}
\{{if enableGuards == 1}
	IFGuard propertyGuard(guardMutex);{/if}{if prop.proxy.target != ""}{if prop.proxy.nullError != ""}
	if ({$prop.proxy.target} == 0)
		throw {$prop.proxy.nullError};{/if}
	return {$prop.proxy.target}->remove{$prop.element.name|uppercase(1)}Index(removeIndex);{else}
	if (removeIndex > {$prop.name}.size())
		return;{if prop.element.managed == "true"}
	{$prop.element.type} e0 = {$prop.name}[removeIndex];
	{$prop.name}.erase({$prop.name}.begin() + removeIndex);
	if (e0 != {if prop.element.defaultValue != ""}{$prop.element.defaultValue}{else}0{/if})
		removeLocalRef(e0);{else}
	{$prop.name}.erase({$prop.name}.begin() + removeIndex);{/if}{/if}
\}

{swrap 75}void {$class.name}::clear{if prop.element.plural == ""}{$prop.element.name|uppercase(1)}s{else}{$prop.element.plural|uppercase(1)}{/if}(){/swrap}
\{{if enableGuards == 1}
	IFGuard propertyGuard(guardMutex);{/if}{if prop.proxy.target != ""}{if prop.proxy.nullError != ""}
	if ({$prop.proxy.target} == 0)
		throw {$prop.proxy.nullError};{/if}
	return {$prop.proxy.target}->clear{if prop.element.plural == ""}{$prop.element.name|uppercase(1)}s{else}{$prop.element.plural|uppercase(1)}{/if}();{else}
	{if prop.element.managed == "true"}std::vector<{$prop.element.type}>::iterator i;
	for (i = {$prop.name}.begin(); i != {$prop.name}.end(); i++)
		if (*i != {if prop.element.defaultValue != ""}{$prop.element.defaultValue}{else}0{/if})
			removeLocalRef(*i);
	{/if}{$prop.name}.clear();{/if}
\}{/if}{else}{if prop.style == "map"}

{swrap 75}unsigned int {$class.name}::getNum{if prop.element.plural == ""}{$prop.element.name|uppercase(1)}s{else}{$prop.element.plural|uppercase(1)}{/if}() const{/swrap}
\{{if enableGuards == 1}
	IFGuard propertyGuard(guardMutex);{/if}
	return {$prop.name}.size();
\}

{swrap 75}{$prop.element.type} {$class.name}::get{$prop.element.name|uppercase(1)}({if prop.key.accessType != ""}{$prop.key.accessType}{else}{$prop.key.type}{/if} elementKey) const{/swrap}
\{{if enableGuards == 1}
	IFGuard propertyGuard(guardMutex);{/if}{if prop.impl.get != ""}
{swrap 75 "	"}{$prop.impl.get}{/swrap}{else}
	std::map<{$prop.key.type}, {$prop.element.type}>::const_iterator i = {$prop.name}.find(elementKey);
	if (i != {$prop.name}.end())
		return (*i).second;
	return {if prop.element.defaultValue != ""}{$prop.element.defaultValue}{else}0{/if};{/if}
\}{if ( prop.readOnly != "true" ) || ( prop.protectedWrite == "true" )}{if prop.hideImpl != "true"}

{swrap 75}std::map<{$prop.key.type}, {$prop.element.type}>& {$class.name}::get{if prop.element.plural == ""}{$prop.element.name|uppercase(1)}s{else}{$prop.element.plural|uppercase(1)}{/if}(){/swrap}
\{{if enableGuards == 1}
	IFGuard propertyGuard(guardMutex);{/if}
	return {$prop.name};
\}{/if}

{swrap 75}void {$class.name}::add{$prop.element.name|uppercase(1)}({if prop.key.accessType != ""}{$prop.key.accessType}{else}{$prop.key.type}{/if} elementKey, {if prop.element.addType == ""}{$prop.element.type}{else}{$prop.element.addType}{/if} addElement){/swrap}
\{{if enableGuards == 1}
	IFGuard propertyGuard(guardMutex);{/if}{if prop.check.maxSize != ""}
	if ({$prop.name}.size() >= {$prop.check.maxSize})
		throw {$prop.check.sizeError};{/if}
	{$prop.element.type} the{$prop.element.name|uppercase(1)} = get{$prop.element.name|uppercase(1)}(elementKey);
	if (the{$prop.element.name|uppercase(1)} != {if prop.element.defaultValue != ""}{$prop.element.defaultValue}{else}0{/if})
		return;
	{$prop.name}[elementKey] = addElement;{if prop.element.managed == "true"}
	addLocalRef(addElement);{/if}
\}{if prop.extendedAddFuncs == "true"}{ref createExtendedMapAddFuncImpl}{/if}

{swrap 75}void {$class.name}::remove{$prop.element.name|uppercase(1)}({if prop.key.accessType != ""}{$prop.key.accessType}{else}{$prop.key.type}{/if} elementKey){/swrap}
\{{if enableGuards == 1}
	IFGuard propertyGuard(guardMutex);{/if}
	std::map<{$prop.key.type}, {$prop.element.type}>::iterator i = {$prop.name}.find(elementKey);
	if (i != {$prop.name}.end())
	\{
		{if prop.element.managed == "true"}if ((*i).second != {if prop.element.defaultValue != ""}{$prop.element.defaultValue}{else}0{/if})
			removeLocalRef((*i).second);
		{/if}{$prop.name}.erase(i);
	\}
\}

{swrap 75}void {$class.name}::clear{if prop.element.plural == ""}{$prop.element.name|uppercase(1)}s{else}{$prop.element.plural|uppercase(1)}{/if}(){/swrap}
\{{if enableGuards == 1}
	IFGuard propertyGuard(guardMutex);{/if}
	{if prop.element.managed == "true"}std::map<{$prop.key.type}, {$prop.element.type}>::iterator i;
	for (i = {$prop.name}.begin(); i != {$prop.name}.end(); i++)
		if ((*i).second != {if prop.element.defaultValue != ""}{$prop.element.defaultValue}{else}0{/if})
			removeLocalRef((*i).second);
	{/if}{$prop.name}.clear();
\}{/if}{else}{if ( prop.readOnly != "true" ) || ( prop.protectedWrite == "true" )}

{swrap 75}void {$class.name}::set{$prop.name|uppercase(1)}({$prop.setFromType} new{$prop.name|uppercase(1)}){/swrap}
\{{if enableGuards == 1}
	IFGuard propertyGuard(guardMutex);{/if}{if prop.impl.preSet != ""}
{$prop.impl.preSet|swrap(75, "	")}{/if}{if prop.impl.set == ""}{if prop.managed == "true"}
	if ({$prop.name} == new{$prop.name|uppercase(1)})
		return;
	if (new{$prop.name|uppercase(1)} != 0)
		addLocalRef(new{$prop.name|uppercase(1)});
	if ({$prop.name} != 0)
		removeLocalRef({$prop.name});{/if}{if prop.persistent != "true"}
	{$prop.name} = new{$prop.name|uppercase(1)};{else}
	if (persistent != 0)
		{if haveBasePersistent == 0}persistent{else}getPersistent(){/if}->{$prop.name} = new{$prop.name|uppercase(1)};{/if}{else}
{$prop.impl.set|swrap(75, "	")}{/if}{if prop.impl.postSet != ""}
{$prop.impl.postSet|swrap(75, "	")}{/if}
\}{/if}

{swrap 75}{$prop.type} {$class.name}::get{$prop.name|uppercase(1)}() const{/swrap}
\{{if enableGuards == 1}
	IFGuard propertyGuard(guardMutex);{/if}{if prop.impl.preGet != ""}
{$prop.impl.preGet|swrap(75, "	")}{/if}{if prop.impl.get == ""}{if prop.persistent != "true"}
	return {$prop.name};{else}	
	if (persistent != 0)
		return {if haveBasePersistent == 0}persistent{else}getPersistent(){/if}->{$prop.name};
	return {$prop.notSetValue};{/if}{else}
{$prop.impl.get|swrap(75, "	")}{/if}{if prop.impl.postGet != ""}
{$prop.impl.postGet|swrap(75, "	")}{/if}
\}{/if}{/if}{/section}
