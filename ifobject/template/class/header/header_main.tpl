# ==========================================================================
# Ionflux Object Base System
# Copyright © 2006-2013 Joern P. Meier
# mail@ionflux.org
# --------------------------------------------------------------------------
# header_main.tpl              Main header template.
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
{import class.check_features}{ref checkFeatures}{import class.utils.get_fq_name}{import class.header.insert_includes}{import class.header.insert_forwards}{import class.header.insert_typedefs}{import class.header.create_struct_decl}{import class.header.create_event_helper_function_decl}{import class.header.declare_global_func}{import class.header.declare_class_name_funcs}{import class.header.property.declare_property_set_funcs}{import class.header.property.declare_property_clear_func}{import class.header.accessor.declare_extended_vector_add_funcs}{import class.header.accessor.declare_vector_write_funcs}{import class.header.accessor.declare_extended_map_add_funcs}{import class.header.accessor.declare_map_write_funcs}{import class.header.accessor.declare_property_write_funcs}{import class.header.accessor.declare_vector_read_funcs}{import class.header.accessor.declare_map_read_funcs}{import class.header.accessor.declare_property_read_funcs}{import class.header.persistence.declare_persistent_init_func}{import class.header.persistence.declare_persistence_funcs}{import class.header.persistence.declare_persistent_protected_funcs}{import class.header.declare_serialize_funcs}{import class.header.declare_copy_funcs}{import class.header.declare_upcast_funcs}{import class.header.declare_mem_funcs}{import class.header.declare_extended_create_funcs}{import class.header.declare_create_funcs}{import class.header.declare_param_funcs}{import class.header.declare_func}{import class.header.qt.declare_qt_signal}{import class.header.qt.declare_qt_slot}{import class.header.xml.declare_xml_io_funcs}{import class.header.project_info}{ref projectInfo}
{ref insertIncludes}{if class.linkagePrefix != ""}

\#ifndef {$class.linkagePrefix}
\#define {$class.linkagePrefix}
\#endif{else}{if project.linkagePrefix != ""}

\#ifndef {$project.linkagePrefix}
\#define {$project.linkagePrefix}
\#endif{/if}{/if}{foreach un in undef.header}
\#undef {$un}{/foreach}{if enablePropertySet == 1}

namespace Ionflux
\{

namespace ObjectBase
\{
    // Forward declarations for the PropertySet feature.
    class IFProperty;
    class IFPropertySet;
\}

\}{/if}{ref insertIFObjectForwards}{foreach ns in namespace}

namespace {$ns.name}
\{{/foreach}{ref insertForwards}{if enableXMLIO == 1}

namespace XMLUtils
\{

class {$class.name}XMLFactory;

\}{/if}{ref insertTypedefs}{if class.group.shortDesc != ""}

/** \\addtogroup {$class.group.name} {$class.group.shortDesc}{if class.group.longDesc != ""}
 *
{$class.group.longDesc|swrap(75,' * ')}
 *{/if}
 * @\{
 */{/if}{ref createStructDecl}{foreach sig in signal}

/// Signal connections for IF{$sig.id|uppercase(1)}Signal.
struct IF{$sig.id|uppercase(1)}SignalConnections
\{{foreach ins in sig.instance}
	/// Signal connection: {$ins.desc}
	sigc::connection signal{$ins.name|uppercase(1)}Connection;{/foreach}
\};{/foreach}{if enableClassInfo == 1}

/// Class information for class {$class.name}.
class {$class.name}ClassInfo
: public Ionflux::ObjectBase::IFClassInfo
\{{if haveOps == 1}
	protected:{foreach op in operation}
		// Operation info: {$op.name}.
		static Ionflux::ObjectBase::IFOpInfo OP_INFO_{$op.name|uppercase};{/foreach}
		{/if}
	public:
		/// Constructor.
		{$class.name}ClassInfo();
		/// Destructor.
		virtual ~{$class.name}ClassInfo();
\};{/if}

/** {$class.title}.{if (class.group.shortDesc == "") && (class.group.name != "")}
 * \\ingroup {$class.group.name}{/if}
 *
{$class.longDesc|swrap(75,' * ')}
 */
class {if class.linkagePrefix != ""}{$class.linkagePrefix} {else}{if project.linkagePrefix != ""}{$project.linkagePrefix} {/if}{/if}{$class.name}{if ( haveBaseIFObject == 1 ) || ( haveBaseOther == 1 )}
: {swrap 75}{foreach bc in class.base.ifobject}{if bc.inheritanceType == ""}public{else}{$bc.inheritanceType}{/if} Ionflux::ObjectBase::{$bc.name}{notlast}, {/notlast}{/foreach}{foreach bc in class.base.other}{first}{if haveBaseIFObject == 1}, {/if}{/first}{single}{if haveBaseIFObject == 1}, {/if}{/single}{if bc.inheritanceType == ""}public{else}{$bc.inheritanceType}{/if} {$bc.name}{notlast}, {/notlast}{/foreach}{/swrap}{/if}
\{{if enableQObject == 1}
    Q_OBJECT
    {/if}
	private:
{foreach var in variable.private}		/// {$var.desc}.
		{if var.spec != ""}{$var.spec} {/if}{$var.type} {$var.name}{if var.arraySize != ""}[{$var.arraySize}]{/if};
{/foreach}{foreach prop in property.private}{if ( prop.proxy != "true" ) && ( prop.persistent != "true" )}		/// {$prop.desc}.
		{if prop.style == "vector"}std::vector<{$prop.element.type}>{else}{if prop.style == "map"}std::map<{$prop.key.type}, {$prop.element.type}>{else}{$prop.type}{/if}{/if} {$prop.name};
{/if}{/foreach}{foreach const in constant.private}		/// {$const.desc}.
		static const {$const.type} {$const.name};
{/foreach}{foreach func in function.private}{ref declareFunc}{/foreach}		
	protected:{if enablePersistence == 1}{if haveBasePersistent == 0}
		/// Persistence: database.
		{$project.persistence.namespace}::{$project.persistence.database}* database;
		/// Persistence: backend object.
		{$project.persistence.namespace}::{$class.persistence.backend}* persistent;{/if}{/if}{foreach var in variable.protected}
		/// {$var.desc}.
		{if var.spec != ""}{$var.spec} {/if}{$var.type} {$var.name}{if var.arraySize != ""}[{$var.arraySize}]{/if};{/foreach}{foreach prop in property.protected}{if ( prop.proxy != "true" ) && ( prop.persistent != "true" )}
		/// {$prop.desc}.
		{if prop.style == "vector"}std::vector<{$prop.element.type}>{else}{if prop.style == "map"}std::map<{$prop.key.type}, {$prop.element.type}>{else}{$prop.type}{/if}{/if} {$prop.name};{/if}{/foreach}{foreach sig in signal}{foreach ins in sig.instance}
		/// Signal: {$ins.desc}.
		IF{$si.id|uppercase(1)}Signal signal{$ins.name|uppercase(1)};
		/// Signal wrapper: {$ins.desc}.
		Ionflux::ObjectBase::IFSignal* signal{$ins.name|uppercase(1)}Wrapper;{/foreach}{/foreach}{foreach const in constant.protected}
		/// {$const.desc}.
		static const {$const.type} {$const.name};{/foreach}{foreach func in function.protected}{ref declareFunc}{/foreach}{foreach op in operation}
		
		/** Operation proxy: {$op.name}.
		 *
		 * Proxy for the '{$op.name}' operation.
		 *{foreach prm in op.param}
{swrap 75 "		 * "}\\param {$prm.name} {$prm.desc}.{/swrap}{/foreach}
		 * \\param target Where to store the result.
		 */
{swrap 75 "		"}bool op{$op.name|uppercase(1)}({foreach prm in op.param}Ionflux::ObjectBase::IFObject* {$prm.name}, {/foreach}Ionflux::ObjectBase::IFObjectVector* target = 0){if op.const != ""} const{/if};{/swrap}{if ( op.const != "true" ) && ( op.constImpl != "" )}

		/** Operation proxy: {$op.name}.
		 *
		 * Proxy for the '{$op.name}' operation.
		 *{foreach prm in op.param}
{swrap 75 "		 * "}\\param {$prm.name} {$prm.desc}.{/swrap}{/foreach}
		 * \\param target Where to store the result.
		 */
{swrap 75 "		"}bool op{$op.name|uppercase(1)}({foreach prm in op.param}Ionflux::ObjectBase::IFObject* {$prm.name}, {/foreach}Ionflux::ObjectBase::IFObjectVector* target = 0) const;{/swrap}{/if}{/foreach}{if haveOps == 1}
		
		/** Operation dispatch.
		 *
		 * Default function used for dispatching operations.
		 *
		 * \\param opName Operation name.
		 * \\param params Parameters.
		 * \\param target Where to store the result.
		 */
		bool opDispatch(const Ionflux::ObjectBase::IFOpName& opName, 
			const Ionflux::ObjectBase::IFObjectVector* params = 0, 
			Ionflux::ObjectBase::IFObjectVector* target = 0);
		
		/** Operation dispatch.
		 *
		 * Default function used for dispatching operations.
		 *
		 * \\param opName Operation name.
		 * \\param params Parameters.
		 * \\param target Where to store the result.
		 */
		bool opDispatch(const Ionflux::ObjectBase::IFOpName& opName, 
			const Ionflux::ObjectBase::IFObjectVector* params = 0, 
			Ionflux::ObjectBase::IFObjectVector* target = 0) const;{/if}{if enablePersistence == 1}{ref declarePersistentProtectedFuncs}{/if}{foreach prop in property.protected}{if prop.protectedWrite == "true"}{ref declarePropertyWriteFuncs}{/if}{/foreach}
		
	public:{foreach fr in class.friendClasses}{first}
	    // Friend classes.{/first}{single}
	    // Friend classes.{/single}
	    friend class {$fr};{last}
	    {/last}{single}
	    {/single}{/foreach}{foreach var in variable.public}
		/// {$var.desc}.
		{if var.spec != ""}{$var.spec} {/if}{$var.type} {$var.name}{if var.arraySize != ""}[{$var.arraySize}]{/if};{/foreach}{foreach const in constant.public}
		/// {$const.desc}.
		static const {$const.type} {$const.name};{/foreach}{foreach sig in signal}
		/// Signal type: {$sig.id}.
		static const Ionflux::ObjectBase::IFSignalType SIGNAL_TYPE_{$sig.id|uppercase};{foreach ins in sig.instance}
		/// Signal name: {$ins.id}.
		static const std::string SIGNAL_NAME_{$ins.id|uppercase};{/foreach}{/foreach}{if enableClassInfo == 1}
		/// Class information instance.
		static const {$class.name}ClassInfo {$class.name|lowercase(1)}ClassInfo;
		/// Class information.
		static const Ionflux::ObjectBase::IFClassInfo* CLASS_INFO;{/if}{if enableXMLIO == 1}
		/// XML element name.
		static const std::string XML_ELEMENT_NAME;{/if}{if enableSerialize == 1}
		/// Magic syllable (object{if class.serialize.magicSyllable.desc != ""}, {$class.serialize.magicSyllable.desc}{/if}).
		static const Ionflux::ObjectBase::MagicSyllable MAGIC_SYLLABLE_OBJECT;{/if}
		
		/** Constructor.
		 *
		 * Construct new {$class.name} object.
		 */
		{$class.name}();{if enablePersistence == 1}
		
		/** Constructor.
		 *
		 * Construct new {$class.name} object.
		 *
		 * \\param initDatabase Database.
		 * \\param objectID Object ID.
		 */
		{$class.name}({$project.persistence.namespace}::{$project.persistence.database}* initDatabase, int objectID = -1);
		
		/** Constructor.
		 *
		 * Construct new {$class.name} object.
		 *
		 * \\param initDatabase Database.
		 * \\param initPersistent Persistent backend object.
		 */
		{$class.name}({$project.persistence.namespace}::{$project.persistence.database}* initDatabase, {$project.persistence.namespace}::{$class.persistence.backend}* initPersistent);{/if}{if enableCopy == 1}
		
		/** Constructor.
		 *
		 * Construct new {$class.name} object.
		 *
		 * \\param other Other object.
		 */
		{$class.name}(const {foreach ns in namespace}{$ns.name}::{/foreach}{$class.name}& other);{/if}
		{foreach con in constructor.public}
		/** Constructor.
		 *
		 * Construct new {$class.name} object.{foreach prm in con.param}{first}
		 *{/first}{single}
		 *{/single}
{swrap 75 "		 * "}\\param {$prm.name} {$prm.desc}.{/swrap}{/foreach}
		 */
{swrap 75 "		"}{$class.name}({foreach prm in con.param}{$prm.type} {$prm.name}{if prm.default != ""} = {$prm.default}{/if}{first}, {/first}{mid}, {/mid}{/foreach});{/swrap}
		{/foreach}
		/** Destructor.
		 *
		 * Destruct {$class.name} object.
		 */
		virtual ~{$class.name}(){if destructor.throw != ""} throw({if destructor.throw != "<none>"}{$destructor.throw}{/if}){/if};{foreach ev in event}{ref createEventHelperFunctionDecl}{/foreach}{foreach func in function.public}{ref declareFunc}{/foreach}{if enableSerialize == 1}{ref declareSerializeFuncs}{/if}{if enablePersistence == 1}{ref declarePersistenceFuncs}{/if}{if enableCopy == 1}{ref declareCopyFuncs}{/if}{if enableUpcast == 1}{ref declareUpcastFuncs}{/if}{if enableCreate == 1}{ref declareCreateFuncs}{/if}{if ( haveBaseIFObject == 1 ) || ( enableClassInfo == 1)}{ref declareMemFuncs}{/if}{if enableParam == 1}{ref declareParamFuncs}{/if}{if enablePropertySet == 1}{ref declarePropertySetFuncs}{/if}{if enableXMLIO == 1}{ref declareXMLIOFuncs}{/if}{foreach prop in property.private}{ref declarePropertyReadFuncs}{/foreach}{foreach prop in property.protected}{ref declarePropertyReadFuncs}{if ( prop.readOnly != "true" ) && ( prop.protectedWrite != "true" )}{ref declarePropertyWriteFuncs}{/if}{/foreach}{if enablePersistence == 1}{if haveBasePersistent == 0}{$prop.style = ""}{$prop.readOnly = "false"}{$prop.name = "database"}{$prop.desc = "Database"}{$prop.type = project.persistence.namespace + "::" + project.persistence.database + "*"}{$prop.setFromType = project.persistence.namespace + "::" + project.persistence.database + "*"}{ref declarePropertyReadFuncs}{ref declarePropertyWriteFuncs}{/if}{/if}{foreach sig in signal}{foreach ins in sig.instance}
		
		/** Get signal: {$ins.desc}.
		 *
		 * Get the signal for the {$ins.desc} event.
		 *
		 * \\return Signal for the {$ins.desc} event.
		 */
		virtual IF{$sig.id|uppercase(1)}Signal& getSignal{$ins.name|uppercase(1)}();
		
		/** Get signal wrapper: {$ins.desc}.
		 *
		 * Get the signal for the {$ins.desc} event.
		 *
		 * \\return Signal for the {$ins.desc} event.
		 */
		virtual Ionflux::ObjectBase::IFSignal* getSignal{$ins.name|uppercase(1)}Wrapper();{/foreach}{/foreach}{if enableClassName == 1}{ref declareClassNameFuncs}{/if}{if enableQObject == 1}
    
    signals:{foreach si in qt.signals}{ref declareQtSignal}{/foreach}
    
    public slots:{foreach sl in qt.slots.public}{ref declareQtSlot}{/foreach}
    
    protected slots:{foreach sl in qt.slots.protected}{ref declareQtSlot}{/foreach}
{/if}
\};{foreach func in function.global}{ref declareGlobalFunc}{/foreach}{if class.group.shortDesc != ""}

/// @\}
{/if}{foreach ns in namespace}

\}{/foreach}{foreach func in function.externC}{first}

extern "C"
\{{/first}{ref declareGlobalFunc}{last}

\}{/last}{/foreach}

/** \\file {$class.name}.hpp
 * \\brief {$class.shortDesc} (header).
 */
\#endif

