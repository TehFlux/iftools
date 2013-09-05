# ==========================================================================
# Ionflux Object Base System
# Copyright © 2006-2013 Joern P. Meier
# mail@ionflux.org
# --------------------------------------------------------------------------
# impl_main.tpl              Main implementation template.
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
{import class.check_features}{import class.utils.get_fq_name}{ref checkFeatures}{import class.insert_gpl_disclaimer}{import class.impl.insert_includes}{import class.impl.create_class_name_funcs_impl}{import class.impl.create_event_helper_function_impl}{import class.impl.property.create_property_set_funcs_impl}{import class.impl.accessor.create_extended_vector_add_func_impl}{import class.impl.accessor.create_extended_map_add_func_impl}{import class.impl.accessor.create_property_accessor_impl}{import class.impl.create_func_impl}{import class.impl.qt.create_qt_slot_impl}{import class.impl.operation.create_op_proxy_impl}{import class.impl.operation.create_op_dispatch_impl}{import class.impl.serialize.serialize_prop}{import class.impl.serialize.serialize_var}{import class.impl.serialize.deserialize_prop}{import class.impl.serialize.deserialize_var}{import class.impl.define_global_func}{import class.impl.persistence.create_persistent_init_func_impl}{import class.impl.persistence.persistent_database_accessor_impl}{import class.impl.persistence.create_persistent_protected_funcs_impl}{import class.impl.create_copy_funcs_impl}{import class.impl.create_upcast_funcs_impl}{import class.impl.create_extended_create_funcs_impl}{import class.impl.create_create_funcs_impl}{import class.impl.create_param_funcs_impl}{import class.impl.xml.create_xml_io_funcs_impl}{import class.impl.project_info}{ref projectInfo}{ref insertIncludes}{foreach un in undef.impl}
\#undef {$un}{/foreach}{foreach ud in using}{first}
{/first}{single}
{/single}
using {$ud};{/foreach}{if insert.impl.preNamespace != ""}

{$insert.impl.preNamespace}{/if}{foreach ns in namespace}

namespace {$ns.name}
\{{/foreach}{foreach st in struct}{first}

// structure constants{/first}{single}

// structure constants{/single}{foreach cn in st.constant}
const {$cn.type} {$st.name}::{$cn.name} = {$cn.value};{/foreach}{/foreach}{if enableClassInfo == 1}{if haveOps == 1}

// operation info records{foreach op in operation}
Ionflux::ObjectBase::IFOpInfo {$class.name|uppercase(1)}ClassInfo::OP_INFO_{$op.name|uppercase};{/foreach}{/if}

{$class.name|uppercase(1)}ClassInfo::{$class.name|uppercase(1)}ClassInfo()
\{
	name = "{$class.name}";
	desc = "{$class.shortDesc}";{foreach bc in class.base.ifobject}
	baseClassInfo.push_back(Ionflux::ObjectBase::{$bc.name}::CLASS_INFO);{/foreach}{foreach bc in class.base.other}{if bc.hasClassInfo == "true"}
	baseClassInfo.push_back({$bc.name}::CLASS_INFO);{/if}{/foreach}{if haveOps == 1}{$haveParams = 0}{$haveResults = 0}{foreach op in operation}{foreach prm in op.param}{first}{$haveParams = 1}{/first}{single}{$haveParams = 1}{/single}{/foreach}{foreach res in op.result}{first}{$haveResults = 1}{/first}{single}{$haveResults = 1}{/single}{/foreach}{/foreach}{if haveParams == 1}
	Ionflux::ObjectBase::IFOpParamInfo currentParam;{/if}{if haveResults == 1}
	Ionflux::ObjectBase::IFOpResultInfo currentResult;{/if}{foreach op in operation}
	OP_INFO_{$op.name|uppercase}.name = "{$op.name}";{foreach prm in op.param}
	currentParam.type = {if prm.type != ""}{$prm.type}::CLASS_INFO{else}0{/if};
	currentParam.name = "{$prm.name}";
	currentParam.desc = "{$prm.desc}";
	currentParam.optional = {if prm.optional != ""}{$prm.optional}{else}false{/if};
	currentParam.defaultValue = {if prm.optional != ""}{$prm.optional}{else}0{/if};
	OP_INFO_{$op.name|uppercase}.paramInfo.push_back(currentParam);{/foreach}{foreach res in op.result}
	currentResult.type = {if res.type != ""}{$res.type}::CLASS_INFO{else}0{/if};
	currentResult.desc = "{$res.desc}";
	OP_INFO_{$op.name|uppercase}.resultInfo.push_back(currentResult);{/foreach}{/foreach}
	opInfo = new IFOpNameInfoMap();{foreach op in operation}
	(*opInfo)[OP_INFO_{$op.name|uppercase}.name] = &OP_INFO_{$op.name|uppercase};{/foreach}{/if}
\}

{$class.name|uppercase(1)}ClassInfo::~{$class.name|uppercase(1)}ClassInfo()
\{{if haveOps == 1}
	delete opInfo;{/if}
\}{/if}{foreach var in variable.private}{if var.spec == "static"}{first}

// static private member variables{/first}{single}

// static private member variables{/single}
{$var.type} {$class.name}::{$var.name} = {$var.value};{/if}{/foreach}{foreach var in variable.protected}{if var.spec == "static"}{first}

// static protected member variables{/first}{single}

// static protected member variables{/single}
{$var.type} {$class.name}::{$var.name} = {$var.value};{/if}{/foreach}{foreach const in constant.private}{first}

// private member constants{/first}{single}

// private member constants{/single}
const {$const.type} {$class.name}::{$const.name} = {$const.value};{/foreach}{foreach const in constant.protected}{first}

// protected member constants{/first}{single}

// protected member constants{/single}
const {$const.type} {$class.name}::{$const.name} = {$const.value};{/foreach}{foreach const in constant.public}{first}

// public member constants{/first}{single}

// public member constants{/single}
const {$const.type} {$class.name}::{$const.name} = {$const.value};{/foreach}{foreach sig in signal}{first}

// signal type and instance name constants{/first}{single}

// signal type and instance name constants{/single}
const Ionflux::ObjectBase::IFSignalType {$class.name}::SIGNAL_TYPE_{$sig.id|uppercase} = 
	"{$sig.return.type},{foreach prm in sig.param}{$prm.type}{notlast}, {/notlast}{/foreach}";{$signalInstanceID = 0}{foreach ins in sig.instance}
const std::string {$class.name}::SIGNAL_NAME_{$ins.id|uppercase} = "{$ins.id|lowercase}";{/foreach}{/foreach}{if enableClassInfo == 1}

// run-time type information instance constants
const {$class.name}ClassInfo {$class.name}::{$class.name|lowercase(1)}ClassInfo;
const Ionflux::ObjectBase::IFClassInfo* {$class.name}::CLASS_INFO = &{$class.name}::{$class.name|lowercase(1)}ClassInfo;{/if}{if enableXMLIO == 1}

const std::string {$class.name}::XML_ELEMENT_NAME = "{if class.xml.elementName != ""}{$class.xml.elementName}{else}{$class.name|lowercase}{/if}";{/if}{if class.hooks.preConstructorDef != ""}

{$class.hooks.preConstructorDef}{/if}

{$class.name}::{$class.name}(){$haveInitializer = 0}{foreach init in constructor.default.initializer}{$haveInitializer = 1}{first}
: {/first}{single}
: {/single}{$init.name}({$init.value}){notlast}, {/notlast}{/foreach}{foreach sig in signal}{foreach ins in sig.instance}{first}{if haveInitializer == 0}
: {$haveInitializer = 1}{else}, {/if}{/first}{single}{if haveInitializer == 0}
: {$haveInitializer = 1}{else}, {/if}{/single}signal{$ins.name|uppercase(1)}Wrapper(0){notlast}, {/notlast}{/foreach}{/foreach}{if ( enablePersistence == 1 ) && ( haveBasePersistent == 0 )}{if haveInitializer == 0}
: {$haveInitializer = 1}{else}, {/if}database(0), persistent(0){/if}
\{{if enableClassInfo == 1}
	// NOTE: The following line is required for run-time type information.
	theClass = CLASS_INFO;{/if}{if enableAutoGuards == 1}
	// NOTE: The following line is required for guards to work.
	setGuardEnabled(true);{/if}{if enableMemDebug == 1}{if class.memDebug.autoEnable == "true"}
    refData->mmDebug = true;{/if}
    if (refData->mmDebug)
        handleMMEvent(Ionflux::ObjectBase::IFMMEvent(
            Ionflux::ObjectBase::IFMMEvent::TYPE_CREATE, this));{/if}{if constructor.default.impl == ""}
	// TODO: Nothing ATM. ;-){else}
{$constructor.default.impl|swrap(75,'	')}{/if}
\}{if enablePersistence == 1}

{$class.name}::{$class.name}({$project.persistence.namespace}::{$project.persistence.database}* initDatabase, int objectID){$haveInitializer = 0}{foreach init in constructor.default.initializer}{$haveInitializer = 1}{first}
: {/first}{single}
: {/single}{$init.name}({$init.value}){notlast}, {/notlast}{/foreach}{foreach sig in signal}{foreach ins in sig.instance}{first}{if haveInitializer == 0}
: {$haveInitializer = 1}{else}, {/if}{/first}{single}{if haveInitializer == 0}
: {$haveInitializer = 1}{else}, {/if}{/single}signal{$ins.name|uppercase(1)}Wrapper(0){notlast}, {/notlast}{/foreach}{/foreach}{if ( enablePersistence == 1 ) && ( haveBasePersistent == 0 )}{if haveInitializer == 0}
: {$haveInitializer = 1}{else}, {/if}database(0), persistent(0){/if}
\{{if enableClassInfo == 1}
	// NOTE: The following line is required for run-time type information.
	theClass = CLASS_INFO;{/if}{if enableAutoGuards == 1}
	// NOTE: The following line is required for guards to work.
	setGuardEnabled(true);{/if}{if enableMemDebug == 1}{if class.memDebug.autoEnable == "true"}
    refData->mmDebug = true;{/if}
    if (refData->mmDebug)
        handleMMEvent(Ionflux::ObjectBase::IFMMEvent(
            Ionflux::ObjectBase::IFMMEvent::TYPE_CREATE, this));{/if}
	setDatabase(initDatabase);
	if (objectID != -1)
		setFromID(objectID);
\}

{$class.name}::{$class.name}({$project.persistence.namespace}::{$project.persistence.database}* initDatabase, {$project.persistence.namespace}::{$class.persistence.backend}* initPersistent){$haveInitializer = 0}{foreach init in constructor.default.initializer}{$haveInitializer = 1}{first}
: {/first}{single}
: {/single}{$init.name}({$init.value}){notlast}, {/notlast}{/foreach}{foreach sig in signal}{foreach ins in sig.instance}{first}{if haveInitializer == 0}
: {$haveInitializer = 1}{else}, {/if}{/first}{single}{if haveInitializer == 0}
: {$haveInitializer = 1}{else}, {/if}{/single}signal{$ins.name|uppercase(1)}Wrapper(0){notlast}, {/notlast}{/foreach}{/foreach}{if ( enablePersistence == 1 ) && ( haveBasePersistent == 0 )}{if haveInitializer == 0}
: {$haveInitializer = 1}{else}, {/if}database(0), persistent(0){/if}
\{{if enableClassInfo == 1}
	// NOTE: The following line is required for run-time type information.
	theClass = CLASS_INFO;{/if}{if enableAutoGuards == 1}
	// NOTE: The following line is required for guards to work.
	setGuardEnabled(true);{/if}{if enableMemDebug == 1}{if class.memDebug.autoEnable == "true"}
	refData->mmDebug = true;{/if}
    if (refData->mmDebug)
        handleMMEvent(Ionflux::ObjectBase::IFMMEvent(
            Ionflux::ObjectBase::IFMMEvent::TYPE_CREATE, this));{/if}
	/* Do not use setDatabase() here since that also initializes the 
	   persistent backend. */
	database = initDatabase;
	persistent = initPersistent;
\}{/if}{if enableCopy == 1}

{$class.name}::{$class.name}(const {foreach ns in namespace}{$ns.name}::{/foreach}{$class.name}& other){$haveInitializer = 0}{foreach init in constructor.default.initializer}{$haveInitializer = 1}{first}
: {/first}{single}
: {/single}{$init.name}({$init.value}){notlast}, {/notlast}{/foreach}{foreach sig in signal}{foreach ins in sig.instance}{first}{if haveInitializer == 0}
: {$haveInitializer = 1}{else}, {/if}{/first}{single}{if haveInitializer == 0}
: {$haveInitializer = 1}{else}, {/if}{/single}signal{$ins.name|uppercase(1)}Wrapper(0){notlast}, {/notlast}{/foreach}{/foreach}{if ( enablePersistence == 1 ) && ( haveBasePersistent == 0 )}{if haveInitializer == 0}
: {$haveInitializer = 1}{else}, {/if}database(0), persistent(0){/if}
\{{if enableClassInfo == 1}
	// NOTE: The following line is required for run-time type information.
	theClass = CLASS_INFO;{/if}{if enableAutoGuards == 1}
	// NOTE: The following line is required for guards to work.
	setGuardEnabled(true);{/if}{if enableMemDebug == 1}{if class.memDebug.autoEnable == "true"}
	refData->mmDebug = true;{/if}
    if (refData->mmDebug)
        handleMMEvent(Ionflux::ObjectBase::IFMMEvent(
            Ionflux::ObjectBase::IFMMEvent::TYPE_CREATE, this));{/if}{if constructor.copy.impl == ""}
	*this = other;{else}
{swrap 75 "	"}{$constructor.copy.impl}{/swrap}{/if}
\}{/if}{foreach con in constructor.public}

{swrap 75}{$class.name}::{$class.name}({foreach prm in con.param}{$prm.type} {$prm.name}{first}, {/first}{mid}, {/mid}{/foreach}){foreach init in con.initializer}{first}
: {/first}{single}
: {/single}{$init.name}({$init.value}){notlast}, {/notlast}{/foreach}{/swrap}
\{{if enableClassInfo == 1}
	// NOTE: The following line is required for run-time type information.
	theClass = CLASS_INFO;{/if}{if enableAutoGuards == 1}
	// NOTE: The following line is required for guards to work.
	setGuardEnabled(true);{/if}{if enableMemDebug == 1}{if class.memDebug.autoEnable == "true"}
	refData->mmDebug = true;{/if}
    if (refData->mmDebug)
        handleMMEvent(Ionflux::ObjectBase::IFMMEvent(
            Ionflux::ObjectBase::IFMMEvent::TYPE_CREATE, this));{/if}{if con.impl == ""}
	// TODO: Nothing ATM. ;-){else}
{$con.impl|swrap(75,'	')}{/if}
\}{/foreach}

{$class.name}::~{$class.name}(){if destructor.throw != ""} throw({if destructor.throw != "<none>"}{$destructor.throw}{/if}){/if}
\{{foreach prop in property.protected}{if ( prop.style == "vector" ) || ( prop.style == "map" )}{if prop.proxy != "true"}
	clear{if prop.element.plural == ""}{$prop.element.name|uppercase(1)}s{else}{$prop.element.plural|uppercase(1)}{/if}();{/if}{/if}{/foreach}{if enableMemDebug == 1}
    if (refData->mmDebug)
        handleMMEvent(Ionflux::ObjectBase::IFMMEvent(
            Ionflux::ObjectBase::IFMMEvent::TYPE_DELETE, this));{/if}{if destructor.impl == ""}{if enablePersistence == 1}
	if (persistent != 0)
		delete persistent;
	persistent = 0;{else}
	// TODO: Nothing ATM. ;-){/if}{else}
{$destructor.impl|swrap(75,'	')}{/if}
\}{foreach func in function.private}{ref createFuncImpl}{/foreach}{foreach func in function.protected}{ref createFuncImpl}{/foreach}{if enablePersistence == 1}{ref createPersistentProtectedFuncsImpl}{/if}{foreach op in operation}{ref createOpProxyImpl}{/foreach}{if haveOps == 1}{ref createOpDispatchImpl}{/if}{foreach ev in event}{ref createEventHelperFunctionImpl}{/foreach}{foreach func in function.public}{ref createFuncImpl}{/foreach}{foreach prop in property.private}{ref createPropertyAccessorImpl}{/foreach}{foreach prop in property.protected}{ref createPropertyAccessorImpl}{/foreach}{if ( enablePersistence == 1 ) && ( haveBasePersistent == 0 )}{ref persistentDatabaseAccessorImpl}{/if}{if enableSerialize == 1}

bool {$class.name}::serialize(std::string& target) const
\{{if haveBaseIFObject == 1}{foreach bc in class.base.ifobject}
	if (!{$bc.name}::serialize(target))
		return false;{/foreach}{/if}{foreach bc in class.base.other}{if bc.serialize == "true"}
	if (!{$bc.name}::serialize(target))
		return false;{/if}{/foreach}{foreach prop in property.private}{if prop.serialize == "true"}{ref serializeProp}{/if}{/foreach}{foreach prop in property.protected}{if prop.serialize == "true"}{ref serializeProp}{/if}{/foreach}{foreach var in variable.private}{if var.serialize == "true"}{ref serializeVar}{/if}{/foreach}{foreach var in variable.protected}{if var.serialize == "true"}{ref serializeVar}{/if}{/foreach}{foreach var in variable.public}{if var.serialize == "true"}{ref serializeVar}{/if}{/foreach}
	return true;
\}

int {$class.name}::deserialize(const std::string& source, int offset)
\{{if haveBaseIFObject == 1}{foreach bc in class.base.ifobject}
	offset = {$bc.name}::deserialize(source, offset);
	if (offset < 0)
		return -1;{/foreach}{/if}{foreach bc in class.base.other}{if bc.serialize == "true"}
	offset = {$bc.name}::deserialize(source, offset);
	if (offset < 0)
		return false;{/if}{/foreach}{foreach prop in property.private}{if prop.serialize == "true"}{ref deserializeProp}{/if}{/foreach}{foreach prop in property.protected}{if prop.serialize == "true"}{ref deserializeProp}{/if}{/foreach}{foreach var in variable.private}{if var.serialize == "true"}{ref deserializeVar}{/if}{/foreach}{foreach var in variable.protected}{if var.serialize == "true"}{ref deserializeVar}{/if}{/foreach}{foreach var in variable.public}{if var.serialize == "true"}{ref deserializeVar}{/if}{/foreach}
	return offset;
\}{/if}{if enablePersistence == 1}{ref createPersistenceFuncsImpl}{/if}{if enableCopy == 1}{ref createCopyFuncsImpl}{/if}{if enableUpcast == 1}{ref createUpcastFuncsImpl}{/if}{if enableCreate == 1}{ref createCreateFuncsImpl}{/if}{if enableParam == 1}{ref createParamFuncsImpl}{/if}{foreach sig in signal}{foreach ins in sig.instance}

IF{$sig.id|uppercase(1)}Signal& {$class.name}::getSignal{$ins.name|uppercase(1)}()
\{
	return signal{$ins.name|uppercase(1)};
\}

Ionflux::ObjectBase::IFSignal* {$class.name}::getSignal{$ins.name|uppercase(1)}Wrapper()
\{
	if (signal{$ins.name|uppercase(1)}Wrapper == 0)
	\{
		signal{$ins.name|uppercase(1)}Wrapper = new Ionflux::ObjectBase::IFSignal(
			&signal{$ins.name|uppercase(1)}, SIGNAL_TYPE_{$sig.id|uppercase}, 
			SIGNAL_NAME_{$ins.id|uppercase});
		if (signal{$ins.name|uppercase(1)}Wrapper == 0){if enableLogMessage == 1}
			log(IFLogMessage("Could not allocate signal wrapper.", 
				VL_ASSERTION, this, 
				"getSignal{$ins.name|uppercase(1)}Wrapper"));{else}
			std::cerr << "[{$class.name}::getSignal{$ins.name|uppercase(1)}Wrapper] ERROR: " 
				"Could not allocate signal wrapper." << std::endl;{/if}
		addLocalRef(signal{$ins.name|uppercase(1)}Wrapper);
	\}
	return signal{$ins.name|uppercase(1)}Wrapper;
\}{/foreach}{/foreach}{if enableClassName == 1}{ref createClassNameFuncsImpl}{/if}{if enableQObject == 1}{foreach sl in qt.slots.public}{ref createQtSlotImpl}{/foreach}{foreach sl in qt.slots.protected}{ref createQtSlotImpl}{/foreach}{/if}{if enablePropertySet == 1}{ref createPropertySetFuncsImpl}{/if}{if enableXMLIO == 1}{ref createXMLIOFuncsImpl}{/if}{foreach func in function.global}{ref defineGlobalFunc}{/foreach}{foreach ns in namespace}

\}{/foreach}{if insert.impl.postNamespace != ""}

{$insert.impl.postNamespace}{/if}{foreach func in function.externC}{first}

extern "C"
\{{/first}{ref defineGlobalFunc}{last}

\}{/last}{/foreach}

/** \\file {$class.name}.cpp
 * \\brief {$class.shortDesc} implementation.
 */

