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
{import class.check_features}{import class.utils.get_fq_name}{ref checkFeatures}{import xml.conf.project_info}{ref projectInfo}
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
if (xmlElement == 0)
    throw Ionflux::ObjectBase::IFError(
        getErrorString("XML element is null.", "initObject"));
if (target == 0)
    throw Ionflux::ObjectBase::IFError(
        getErrorString("Target object is null.", "initObject"));
std::string en1(elementName);
if (en1.size() == 0)
    en1 = getObjectXMLElementName();
Ionflux::ObjectBase::XMLUtils::checkElementNameOrError(
    xmlElement, en1, "{$class.name}XMLFactory::initObject");
{foreach ns in namespace}{$ns.name}::{/foreach}XMLUtils::get{$class.name}(xmlElement, 
    *{$class.name}::upcast(target));
>>>
\}
function.public[] = \{
    spec = virtual
    type = {ref getFQName}*
    name = createObject
    shortDesc = Create new object
    longDesc = Create a new object. This should be overridden by derived classes to create a new object of the base type.
    impl = 
    return = \{
        value = {$class.name}::create()
        desc = New object
    \}
\}
function.public[] = \{
    spec = virtual
    type = {ref getFQName}*
    name = createObject
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


