{section createPropertySetFuncsImpl}{if class.propertySet.enablePropertyUpdateHandlers == "true"}{if function.updatePropertyHandler.impl != ""}

{swrap 75}void {$class.name}::onUpdateProperty(const Ionflux::ObjectBase::IFProperty& p){/swrap}
\{{if enableGuards == 1}
    IFGuard functionGuard(guardMutex);{/if}
{swrap 75 "    "}{$function.updatePropertyHandler.impl}{/swrap}
\}{/if}{if function.updatePropertiesHandler.impl != ""}

{swrap 75}void {$class.name}::onUpdateProperties(const Ionflux::ObjectBase::IFPropertySet& p){/swrap}
\{{if enableGuards == 1}
    IFGuard functionGuard(guardMutex);{/if}
{swrap 75 "    "}{$function.updatePropertiesHandler.impl}{/swrap}
\}{/if}{/if}

{swrap 75}void {$class.name}::updateProperty(const Ionflux::ObjectBase::IFProperty& p, bool ignoreOwnSet){/swrap}
\{{if enableGuards == 1}
    IFGuard functionGuard(guardMutex);{/if}{foreach prop in property.protected}{if ( prop.readOnly != "true") && ( prop.protectedWrite != "true" )}{if prop.valueType == "bool"}
    // {$prop.name}
    if (p.getName() == "{$prop.name}")
    \{
        Ionflux::ObjectBase::IFValue* v0 = Ionflux::ObjectBase::IFValue::upcast(p.getValue());
        if (v0 != 0)\
        \{\
            set{$prop.name|uppercase(1)}(v0->getBool());{if class.propertySet.enablePropertyUpdateHandlers == "true"}
            onUpdateProperty(p);{/if}
        \}\
        return;
    \}{/if}{if prop.valueType == "integer"}
    // {$prop.name}
    if (p.getName() == "{$prop.name}")
    \{
        Ionflux::ObjectBase::IFValue* v0 = Ionflux::ObjectBase::IFValue::upcast(p.getValue());
        if (v0 != 0)\
        \{\
            set{$prop.name|uppercase(1)}(v0->getInteger());{if class.propertySet.enablePropertyUpdateHandlers == "true"}
            onUpdateProperty(p);{/if}
        \}\
        return;
    \}{/if}{if prop.valueType == "float"}
    // {$prop.name}
    if (p.getName() == "{$prop.name}")
    \{
        Ionflux::ObjectBase::IFValue* v0 = Ionflux::ObjectBase::IFValue::upcast(p.getValue());
        if (v0 != 0)\
        \{\
            set{$prop.name|uppercase(1)}(v0->getFloat());{if class.propertySet.enablePropertyUpdateHandlers == "true"}
            onUpdateProperty(p);{/if}
        \}\
        return;
    \}{/if}{if prop.valueType == "string"}
    // {$prop.name}
    if (p.getName() == "{$prop.name}")
    \{
        Ionflux::ObjectBase::IFValue* v0 = Ionflux::ObjectBase::IFValue::upcast(p.getValue());
        if (v0 != 0)\
        \{\
            set{$prop.name|uppercase(1)}(v0->getStringValue());{if class.propertySet.enablePropertyUpdateHandlers == "true"}
            onUpdateProperty(p);{/if}
        \}\
        return;
    \}{/if}{if prop.valueType == "vec4"}
    // {$prop.name}
    if (p.getName() == "{$prop.name}")
    \{
        Ionflux::ObjectBase::IFValue* v0 = Ionflux::ObjectBase::IFValue::upcast(p.getValue());
        if (v0 != 0)\
        \{\
            set{$prop.name|uppercase(1)}(v0->getV4());{if class.propertySet.enablePropertyUpdateHandlers == "true"}
            onUpdateProperty(p);{/if}
        \}\
        return;
    \}{/if}{if prop.valueType == "color"}
    // {$prop.name}
    if (p.getName() == "{$prop.name}")
    \{
        Ionflux::ObjectBase::IFValue* v0 = Ionflux::ObjectBase::IFValue::upcast(p.getValue());
        if (v0 != 0)\
        \{\
            set{$prop.name|uppercase(1)}(v0->getColor());{if class.propertySet.enablePropertyUpdateHandlers == "true"}
            onUpdateProperty(p);{/if}
        \}\
        return;
    \}{/if}{if prop.valueType == "object"}
    // {$prop.name}
    if (p.getName() == "{$prop.name}")
    \{
        set{$prop.name|uppercase(1)}(
            dynamic_cast<{$prop.type}>(p.getValue()));{if class.propertySet.enablePropertyUpdateHandlers == "true"}
        onUpdateProperty(p);{/if}
        return;
    \}{/if}{if prop.valueType == "propertySet"}
    // property set: {$prop.name}
    if ({$prop.name} != 0)
    \{
        Ionflux::ObjectBase::IFProperty* p0 = {$prop.name}->getProperty(p.getName());
        if ((p0 != 0) && (p0 != &p))
        \{
            p0->setValue(p.getValue());{if class.propertySet.enablePropertyUpdateHandlers == "true"}
            onUpdateProperty(*p0);{/if}
            return;
        \}
    \}{/if}{if prop.valueType == "propertyIndex"}
    // property index: {$prop.name}
    if ({$prop.name} != 0)
    \{
        Ionflux::ObjectBase::IFProperty* p0 = {$prop.name}->getProperty(p.getName());
        if ((p0 != 0) && (p0 != &p))
        \{
            p0->setValue(p.getValue());{if class.propertySet.enablePropertyUpdateHandlers == "true"}
            onUpdateProperty(*p0);{/if}
            return;
        \}
    \}{/if}{/if}{/foreach}{if class.propertySet.isPropertySet == "true"}
    // the class itself is a property set
    if (!ignoreOwnSet)
    \{
        Ionflux::ObjectBase::IFProperty* p0 = getProperty(p.getName());
        if ((p0 != 0) && (p0 != &p))
        \{
            p0->setValue(p.getValue());{if class.propertySet.enablePropertyUpdateHandlers == "true"}
            onUpdateProperty(*p0);{/if}
            return;
        \}
    \}{/if}{if class.propertySet.isPropertyIndex == "true"}
    // the class itself is a property index
    if (!ignoreOwnSet)
    \{
        Ionflux::ObjectBase::IFProperty* p0 = getProperty(p.getName());
        if ((p0 != 0) && (p0 != &p))
        \{
            p0->setValue(p.getValue());{if class.propertySet.enablePropertyUpdateHandlers == "true"}
            onUpdateProperty(*p0);{/if}
            return;
        \}
    \}{/if}{foreach bc in class.base.other}{if bc.propertySetEnabled == "true"}{if bc.ignoreOwnSet == "true"}
    // NOTE: base class will not check its own property set{/if}
    {$bc.name}::updateProperty(p{if bc.ignoreOwnSet == "true"}, true{/if});{/if}{/foreach}
\}

{swrap 75}void {$class.name}::updateProperties(const Ionflux::ObjectBase::IFPropertySet& ps){/swrap}
\{{if enableGuards == 1}
    IFGuard functionGuard(guardMutex);{/if}
    for (unsigned int i = 0; i < ps.getNumProperties(); i++)
    \{
        Ionflux::ObjectBase::IFProperty* p0 = ps.getProperty(i);
        if (p0 != 0)
            updateProperty(*p0);
    \}{if class.propertySet.enablePropertyUpdateHandlers == "true"}
    onUpdateProperties(ps);{/if}
\}

{swrap 75}void {$class.name}::getProperty(Ionflux::ObjectBase::IFProperty& p, bool ignoreOwnSet){/swrap}
\{{if enableGuards == 1}
    IFGuard functionGuard(guardMutex);{/if}{foreach prop in property.protected}{if prop.valueType == "bool"}
    // {$prop.name}
    if (p.getName() == "{$prop.name}")
    \{
        Ionflux::ObjectBase::IFValue* v0 = Ionflux::ObjectBase::IFValue::create();
        v0->setValue(static_cast<bool>(get{$prop.name|uppercase(1)}()));
        p.setValue(v0);
        return;
    \}{/if}{if prop.valueType == "integer"}
    // {$prop.name}
    if (p.getName() == "{$prop.name}")
    \{
        Ionflux::ObjectBase::IFValue* v0 = Ionflux::ObjectBase::IFValue::create();
        v0->setValue(static_cast<Ionflux::ObjectBase::Int64>(get{$prop.name|uppercase(1)}()));
        p.setValue(v0);
        return;
    \}{/if}{if prop.valueType == "float"}
    // {$prop.name}
    if (p.getName() == "{$prop.name}")
    \{
        Ionflux::ObjectBase::IFValue* v0 = Ionflux::ObjectBase::IFValue::create();
        v0->setValue(static_cast<double>(get{$prop.name|uppercase(1)}()));
        p.setValue(v0);
        return;
    \}{/if}{if prop.valueType == "string"}
    // {$prop.name}
    if (p.getName() == "{$prop.name}")
    \{
        Ionflux::ObjectBase::IFValue* v0 = Ionflux::ObjectBase::IFValue::create();
        v0->setValue(get{$prop.name|uppercase(1)}());
        p.setValue(v0);{if prop.typeHint == "file"}
        p.setTypeHint(Ionflux::ObjectBase::IFProperty::TYPE_HINT_FILE);{/if}{if prop.typeHint == "filePath"}
        p.setTypeHint(Ionflux::ObjectBase::IFProperty::TYPE_HINT_FILE_PATH);{/if}{if prop.typeHint == "callable"}
        p.setTypeHint(Ionflux::ObjectBase::IFProperty::TYPE_HINT_CALLABLE);{/if}
        return;
    \}{/if}{if prop.valueType == "vec4"}
    // {$prop.name}
    if (p.getName() == "{$prop.name}")
    \{
        Ionflux::ObjectBase::IFValue* v0 = Ionflux::ObjectBase::IFValue::create();
        v0->setValue(get{$prop.name|uppercase(1)}());
        p.setValue(v0);
        return;
    \}{/if}{if prop.valueType == "color"}
    // {$prop.name}
    if (p.getName() == "{$prop.name}")
    \{
        Ionflux::ObjectBase::IFValue* v0 = Ionflux::ObjectBase::IFValue::create();
        v0->setValue(get{$prop.name|uppercase(1)}());
        p.setValue(v0);
        return;
    \}{/if}{if prop.valueType == "object"}
    // {$prop.name}
    if (p.getName() == "{$prop.name}")
    \{
        p.setValue(get{$prop.name|uppercase(1)}());
        return;
    \}{/if}{if prop.valueType == "propertySet"}
    // property set: {$prop.name}
    if ({$prop.name} != 0)
    \{
        Ionflux::ObjectBase::IFProperty* p0 = {$prop.name}->getProperty(p.getName());
        if (p0 != 0)
        \{
            p.setValue(p0->getValue());
            return;
        \}
    \}{/if}{if prop.valueType == "propertyIndex"}
    // property index: {$prop.name}
    if ({$prop.name} != 0)
    \{
        Ionflux::ObjectBase::IFProperty* p0 = {$prop.name}->getProperty(p.getName());
        if (p0 != 0)
        \{
            p.setValue(p0->getValue());
            return;
        \}
    \}{/if}{/foreach}{if class.propertySet.isPropertySet == "true"}
    // the class itself is a property set
    if (!ignoreOwnSet)
    \{
        Ionflux::ObjectBase::IFProperty* p0 = getProperty(p.getName());
        if (p0 != 0)
        \{
            p.setValue(p0->getValue());
            return;
        \}
    \}{/if}{if class.propertySet.isPropertyIndex == "true"}
    // the class itself is a property index
    if (!ignoreOwnSet)
    \{
        Ionflux::ObjectBase::IFProperty* p0 = getProperty(p.getName());
        if (p0 != 0)
        \{
            p.setValue(p0->getValue());
            return;
        \}
    \}{/if}{foreach bc in class.base.other}{if bc.propertySetEnabled == "true"}{if bc.ignoreOwnSet == "true"}
    // NOTE: base class will not check its own property set{/if}
    {$bc.name}::getProperty(p{if bc.ignoreOwnSet == "true"}, true{/if});{/if}{/foreach}
\}

{swrap 75}void {$class.name}::getProperties(Ionflux::ObjectBase::IFPropertySet& ps){/swrap}
\{{if enableGuards == 1}
    IFGuard functionGuard(guardMutex);{/if}{$tempPropDefined = 0}{foreach bc in class.base.other}{if bc.propertySetEnabled == "true"}
    {$bc.name}::getProperties(ps);{/if}{/foreach}{foreach prop in property.protected}{if ( prop.valueType == "bool" ) || ( prop.valueType == "integer" ) || ( prop.valueType == "float" ) || ( prop.valueType == "string" ) || ( prop.valueType == "vec4" ) || ( prop.valueType == "color" )}
    // {$prop.name}
    {if tempPropDefined == 0}Ionflux::ObjectBase::IFProperty* {$tempPropDefined = 1}{/if}p0 = ps.getProperty("{$prop.name}");
    if (p0 == 0)
    \{
        p0 = ps.addProperty();
        p0->setName("{$prop.name}");
    \}
    getProperty(*p0);{/if}{/foreach}{if class.propertySet.isPropertySet == "true"}
    // the class itself is a property set
    ps.addProperties(this);{/if}
\}{/section}
