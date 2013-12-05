# ==========================================================================
# Ionflux Object Base System
# Copyright © 2006-2013 Joern P. Meier
# mail@ionflux.org
# --------------------------------------------------------------------------
# xml_object_factory.tpl       XML object factory implementation template.
# ==========================================================================
# 
# This file is part of Ionflux Object Base System.
# 
# Ionflux Object Base System is free software; you can redistribute it 
# and/or modify it under the terms of the GNU General Public License as 
# published by the Free Software Foundation; either version 2 of the 
# License, or (at  your option) any later version.
# 
# Ionflux Object Base System is distributed in the hope that it will be 
# useful, but WITHOUT ANY WARRANTY; without even the implied warranty of 
# MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU 
# General Public License for more details.
# 
# You should have received a copy of the GNU General Public License
# along with Ionflux Object Base System; if not, write to the Free 
# Software Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA 
# 02111-1307 USA
# 
# ==========================================================================
{import class.check_features}{import class.utils.get_fq_name}{ref checkFeatures}{import xml.xml_scan_properties}{ref xmlScanProperties}{import xml.xml_scan_child_classes}{ref xmlScanChildClasses}{import xml.xml_get_prop_child_element_name}{import class.utils.get_numeric_prop_vector_type}{import xml.conf.project_info}{ref projectInfo}
\# namespaces{foreach ns in namespace}
namespace[].name = {$ns.name}{/foreach}
namespace[].name = XMLUtils

\# using directives
using = \{
    'namespace std'
\}

\# include files.
include = \{
    header = \{
        '"ifobject/types.hpp"'
        '"ifobject/xmlutils.hpp"'
        '"{if project.includePrefix != ""}{$project.includePrefix}/{/if}xmlutils.hpp"'
        '"{if class.overrideProjectPrefix != "true"}{if project.includePrefix != ""}{$project.includePrefix}/{/if}{/if}{if class.includePrefix != ""}{$class.includePrefix}/{/if}{$class.name}.hpp"'
    \}
    impl = \{
        '"ifobject/objectutils.hpp"'
        '"ifobject/xmlutils_private.hpp"'
        '"ifobject/IFError.hpp"'
        '"{if project.includePrefix != ""}{$project.includePrefix}/{/if}{if project.includeAll != ""}{$project.includeAll}{else}{$project.baseName}{/if}.hpp"'
        '"{if project.includePrefix != ""}{$project.includePrefix}/{/if}xmlutils_private.hpp"'
    \}
\}

\# Undefine macros.

\# Forward declarations.

\# Typedefs.

\# Helper structs.

\# events

\# signals

\# Class definition.
class = \{
    name = {$class.name}XMLFactory
    shortDesc = XML object factory: {$class.name}
    title = XML object factory: {$class.name}
    longDesc = A factory that creates {$class.name} objects from XML data.
    group.name = {$project.baseName}
    includePrefix = xmlio
    base = \{
        \#ifobject[] = \{
        \#    name = IFObject
        \#    inheritanceType = virtual public
        \#\}
        \# other base classes
        other[] = \{
            name = Ionflux::ObjectBase::XMLUtils::IFXMLObjectFactory
            include = ifobject/IFXMLObjectFactory.hpp
            hasClassInfo = true
        \}
    \}
    features = \{
        'copy'
        'upcast'
        'classinfo'
        'create'
    \}
    create = \{
        allocationError = Ionflux::ObjectBase::IFError("Could not allocate object.")
        extendedCreate = true
    \}
\}

\# Public constructors.
constructor.copy.impl = *this = other;
constructor.default = \{
    impl = 
\}

\# Destructor.
destructor.impl = 

\# Member variables.

\# Class properties.

\# Public static constants.

\# Protected static constants.

\# Protected member functions.

\# Public member functions.
function.copy.impl = <<<
if (this == &other)
    return *this;
Ionflux::ObjectBase::XMLUtils::IFXMLObjectFactory::operator=(other);
>>>
function.public[] = \{
    spec = virtual
    type = std::string
    name = getObjectXMLElementName
    const = true
    shortDesc = Get XML element name
    longDesc = Get the XML element name that this factory creates objects for.
    impl = 
    return = \{
        value = {ref getFQName}::XML_ELEMENT_NAME
        desc = XML element name
    \}
\}
function.public[] = \{
    spec = virtual
    type = std::string
    name = getObjectClassName
    const = true
    shortDesc = Get class name
    longDesc = Get the name of the class this factory creates objects for. This should be overridden by derived classes to return the name of the base type.
    impl = <<<
/* NOTE: This should be obtained via a global singleton IFClassInfo 
         instance of the appropriate type. */
>>>
    return = \{
        value = "{$class.name}"
        desc = Class name
    \}
\}
function.public[] = \{
    spec = virtual
    type = void
    name = initObject
    const = true
    disableBindings = true
    shortDesc = Initialize object
    longDesc = Initialize an object from an XML element. This should be overridden by derived classes to initialize an object of the base type.
    param[] = \{
        type = TiXmlElement*
        name = xmlElement
        desc = XML element
    \}
    param[] = \{
        type = Ionflux::ObjectBase::IFObject*
        name = target
        desc = Target object
    \}
    param[] = \{
        type = const std::string&
        name = elementName
        desc = XML element name
        default = ""
    \}
    impl = <<<
Ionflux::ObjectBase::nullPointerCheck(target, this, 
    "initObject", "Target object");
{ref getFQName}* o0 = {$class.name}::upcast(target);
initObject(xmlElement, *o0, elementName);
>>>
\}
function.public[] = \{
	spec = virtual
	type = void
	name = initObject
	const = true
    disableBindings = true
	shortDesc = Initialize object
	longDesc = Initialize an object from XML data.
    param[] = \{
        type = TiXmlElement*
        name = xmlElement
        desc = XML element
    \}
	param[] = \{
	    type = {ref getFQName}&
	    name = target
	    desc = Target object
	\}
    param[] = \{
        type = const std::string&
        name = elementName
        desc = XML element name
        default = ""
    \}
	impl = <<<
Ionflux::ObjectBase::nullPointerCheck(xmlElement, this, 
    "initObject", "XML element");
std::string en1(elementName);
if (en1.size() == 0)
    en1 = getObjectXMLElementName();
TiXmlElement* e0 = xmlElement;{if function.xml.fromXML.impl == ""}
Ionflux::ObjectBase::XMLUtils::checkElementNameOrError(e0, 
    en1, "{$class.name}XMLFactory::initObject");{if haveBaseIFObject == 1}
Ionflux::ObjectBase::XMLUtils::getObject(e0, target);{else}{foreach base in class.base.other}{if base.xml.enabled == "true"}{if base.xml.getFunc != ""}
{$base.xml.getFunc}(e0, target, en1);{else}
{$base.name}::getXMLObjectFactory()->initObject(
    e0, target, en1);{/if}{/if}{/foreach}{/if}{if haveXMLAttributes == 1}
// Get attribute data.
std::string a0;{foreach prop in property.protected}{if prop.xml.attribute.name != ""}
// Property: {$prop.name} ({$prop.valueType})
a0 = Ionflux::ObjectBase::XMLUtils::getAttributeValue(
    e0, "{$prop.xml.attribute.name}"{if prop.xml.attribute.optional == "false"}, false{else}, true{/if});{if prop.valueType == "string"}
target.set{$prop.name|uppercase(1)}(a0));{/if}{if prop.valueType == "float"}
target.set{$prop.name|uppercase(1)}(::strtod(a0.c_str(), 0));{/if}{if prop.valueType == "integer"}
target.set{$prop.name|uppercase(1)}(::strtol(a0.c_str(), 0, 10));{/if}{/if}{/foreach}{/if}{if haveXMLChildElements == 1}
// Get child data.
TiXmlElement* ce0 = e0->FirstChildElement();
while (ce0 != 0)
\{
    std::string en0(ce0->Value());
    std::string pName = 
        Ionflux::ObjectBase::XMLUtils::getAttributeValue(
            ce0, "pname", true);{foreach prop in property.protected}{if prop.xml.child.name != ""}{ref xmlGetPropChildElementName}
    // Property: {$prop.name} ({if prop.style == "vector"}vector[{$prop.element.valueType}]{else}{$prop.valueType}{/if})
    if ({if prop.valueType == "object"}pName == "{$prop.xml.child.name}"{else}(pName == "{$prop.xml.child.name}") 
        && (en0 == "{$xmlCEName}"){/if})
    \{{if prop.valueType == "string"}
        TiXmlElement* ce1 = ce0->FirstChildElement();
        if (ce1 != 0)
        \{
            std::string v0(ce1->Value());
            target.set{$prop.name|uppercase(1)}(v0);
        \}{/if}{if prop.valueType == "float"}
        a0 = Ionflux::ObjectBase::XMLUtils::getAttributeValue(
            ce0, "d", true);
        if (a0.size() > 0)
            target.set{$prop.name|uppercase(1)}(::strtod(a0.c_str(), 0));{/if}{if prop.valueType == "integer"}
        a0 = Ionflux::ObjectBase::XMLUtils::getAttributeValue(
            ce0, "d", true);
        if (a0.size() > 0)
            target.set{$prop.name|uppercase(1)}(::strtol(a0.c_str(), 0, 10));{/if}{if prop.valueType == "object"}{if prop.xml.createFunc != ""}
        {$prop.type} co0 = 
            {$prop.xml.createFunc}(ce0, en0);
        target.set{$prop.name|uppercase(1)}(co0);{else}
\#error [xmlio] Required option 'xml.createFunc' missing on property '{$class.name}::{$prop.name}'.{/if}{/if}{if prop.style == "vector"}{if prop.element.valueType == "object"}
        std::vector<{$prop.element.type}> pv0;
        Ionflux::ObjectBase::XMLUtils::getObjVector<
                {$prop.element.type|replace('*', '')}, 
                {$prop.element.type}>(ce0, pv0, 
            "{$xmlCEName}", 
            {$prop.element.type|replace('*', '')}::getXMLObjectFactory()
                ->getObjectXMLElementName());
        target.add{if prop.element.plural != ""}{$prop.element.plural}{else}{$prop.element.name|uppercase(1)}s{/if}(pv0);{/if}{if ( prop.element.valueType == "integer" ) || ( prop.element.valueType == "float" )}{ref getNumericPropVectorType}
        Ionflux::ObjectBase::{$propEVecT} pv0;
        Ionflux::ObjectBase::XMLUtils::get{$propEVecT}(ce0, pv0);
        target.add{if prop.element.plural != ""}{$prop.element.plural}{else}{$prop.element.name|uppercase(1)}s{/if}(pv0);{/if}{/if}
    \}{/if}{/foreach}
    ce0 = ce0->NextSiblingElement();
}{/if}{else}
{swrap 75}{$function.xml.fromXML.impl}{/swrap}{/if}
>>>
\}
function.public[] = \{
	spec = virtual
	type = void
	name = initObject
	const = true
	shortDesc = Initialize object
	longDesc = Initialize an object from XML data.
	param[] = \{
	    type = const std::string&
	    name = data
	    desc = XML data
	}
	param[] = \{
	    type = {ref getFQName}&
	    name = target
	    desc = Target object
	\}
    param[] = \{
        type = const std::string&
        name = elementName
        desc = XML element name
        default = ""
    \}
	impl = <<<
TiXmlDocument d0;
\/* NOTE: Probably a peculiarity of tinyxml, there must be at least one 
         character after the data. Or there could of course also be 
         something wrong with how tinyxml is used here. Anyway, this 
         seems to work. *\/
std::string d1(data);
d1.append(1, ' ');
if (!d0.Parse(d1.c_str(), 0, TIXML_ENCODING_UTF8))
    throw {$class.xml.exception}(getErrorString( 
        "Unable to parse XML data.", "initObject"));
std::string en1(elementName);
if (en1.size() == 0)
    en1 = getObjectXMLElementName();
TiXmlElement* m0 = 
    Ionflux::ObjectBase::XMLUtils::findElementByNameOrError(
        d0.RootElement(), en1);
initObject(m0, target, en1);
>>>
\}
function.public[] = \{
    spec = virtual
    type = {ref getFQName}*
    name = createObject
    const = true
    shortDesc = Create new object
    longDesc = Create a new object. This should be overridden by derived classes to create a new object of the base type.
    impl = <<<
{if class.isAbstract != 1}{ref getFQName}* o0 = 
    {$class.name}::create();{else}throw {$class.xml.exception}(getErrorString( 
        "Cannot create instance of abstract class.", "createObject"));{/if}
>>>
    return = \{
        value = {if class.isAbstract != 1}o0{else}0{/if}
        desc = New object
    \}
\}
function.public[] = \{
    spec = virtual
    type = {ref getFQName}*
    name = createObject
    const = true
    disableBindings = true
    shortDesc = Create object
    longDesc = Create a new object from an XML element.
    param[] = \{
        type = TiXmlElement*
        name = xmlElement
        desc = XML element
    \}
    param[] = \{
        type = const std::string&
        name = elementName
        desc = XML element name
        default = ""
    \}
    impl = <<<
{$class.name}* result = {$class.name}::upcast(
    Ionflux::ObjectBase::XMLUtils::IFXMLObjectFactory::createObject(
        xmlElement, elementName));
>>>
    return = \{
        value = result
        desc = New object
    \}
\}


