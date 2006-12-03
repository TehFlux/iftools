# ==========================================================================
# Ionflux Object Base System
# Copyright © 2006 Joern P. Meier
# mail@ionflux.org
# --------------------------------------------------------------------------
# Class.hpp.tpl              class template (header)
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
{section checkFeatures}{$haveForwards = 0}{foreach fw in forward}{if fw != ""}{$haveForwards = 1}{/if}{/foreach}{$haveTypedefs = 0}{foreach td in typedef}{if td != ""}{$haveTypedefs = 1}{/if}{/foreach}{$haveEvents = 0}{foreach ev in event}{if ev.id != ""}{$haveEvents = 1}{/if}{/foreach}{$haveSignals = 0}{foreach si in signal}{if si.id != ""}{$haveSignals = 1}{/if}{/foreach}{$haveBaseIFObject = 0}{foreach bc in class.base.ifobject}{if bc.name != ""}{$haveBaseIFObject = 1}{/if}{/foreach}{$haveBaseOther = 0}{foreach bc in class.base.other}{if bc.name != ""}{$haveBaseOther = 1}{/if}{/foreach}{$enableClassInfo = 0}{if ( haveBaseIFObject == 1 ) || ( class.name == "IFObject" )}{$enableClassInfo = 1}{/if}{$enableMutex = 0}{$enableGuards = 0}{$enableAutoGuards = 0}{$enableLogMessage = 0}{$enableSignal = haveSignals}{$enableSerialize = 0}{foreach fe in class.features}{if fe == "mutex"}{$enableMutex = 1}{/if}{if fe == "guards"}{$enableMutex = 1}{$enableGuards = 1}{/if}{if fe == "autoguards"}{$enableMutex = 1}{$enableGuards = 1}{$enableAutoGuards = 1}{/if}{if fe == "logmessage"}{$enableLogMessage = 1}{/if}{if fe == "signal"}{$enableSignal = 1}{/if}{if fe == "serialize"}{$enableSerialize = 1}{/if}{/foreach}{$haveOps = 0}{foreach op in operation}{if op.name != ""}{$haveOps = 1}{/if}{/foreach}{/section}{ref checkFeatures}{section insertGPLDisclaimer}
 * =========================================================================
{swrap 75 " * "}This file is part of {$project.name}.

{$project.name} is free software; you can redistribute it and/or modify it under the terms of the GNU General Public License as published by the Free Software Foundation; either version 2 of the License, or (at your option) any later version.

{$project.name} is distributed in the hope that it will be useful, but WITHOUT ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU General Public License for more details.

You should have received a copy of the GNU General Public License along with {$project.name}; if not, write to the Free Software Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA 02111-1307 USA{/swrap}
 * {/section}{section insertIncludes}{foreach inc in include.header}{first}
{/first}{single}
{/single}
\#include {$inc}{/foreach}{foreach bc in base.ifobject}
\#include "{if bc.include == ""}ifobject/{$bc.name}.hpp{else}{$bc.include}{/if}"{/foreach}{foreach bc in base.other}
\#include "{if bc.include == ""}{$bc.name}.hpp{else}{$bc.include}{/if}"{/foreach}{/section}{section insertForwards}{foreach fwd in forward}{first}
{/first}{single}
{/single}
{$fwd};{/foreach}{foreach ev in event}{first}{if haveForwards == 0}
{/if}
// events used by {$class.name}{/first}{single}{if haveForwards == 0}
{/if}
// events used by {$class.name}{/single}
class IF{$ev.id|uppercase(1)}Event;{/foreach}{/section}{section insertIFObjectForwards}{if haveSignals == 1}

// forward declarations for types from the Ionflux Object Base System
namespace Ionflux
\{

namespace ObjectBase
\{

class IFSignal;

\}

\}{/if}{/section}{section insertTypedefs}{foreach td in typedef}{first}
{/first}{single}
{/single}
typedef {$td};{/foreach}{foreach si in signal}{first}{if haveTypedefs == 0}
{/if}{/first}{single}{if haveTypedefs == 0}
{/if}{/single}
{swrap 75}typedef sigc::signal<{$si.return.type}{foreach prm in si.param}, {$prm.type}{/foreach}> IF{$si.id|uppercase(1)}Signal;{/swrap}{/foreach}{foreach td in typedefAfterSignals}{first}{if ( haveTypedefs == 0 ) && ( haveSignals == 0)}
{/if}{/first}{single}{if ( haveTypedefs == 0 ) && ( haveSignals == 0)}
{/if}{/single}
typedef {$td};{/foreach}{/section}{section createStructDecl}{foreach st in struct}
 
/** {$st.desc}.{if (class.group.shortDesc == "") && (class.group.name != "")}
 * \\ingroup {$class.group.name}{/if}
 */
struct {$st.name}
\{{foreach fi in st.field}
	/// {$fi.desc}.
	{$fi.type} {$fi.name};{/foreach}{foreach cn in st.constant}
	/// {$cn.desc}.
	static const {$cn.type} {$cn.name};{/foreach}{if st.refCount.enabled == "true"}
	/// Reference counting information.
	Ionflux::ObjectBase::IFObjectRefInfo* refInfo;{/if}
\};{/foreach}{/section}{section createEventHelperFunctionDecl}
		
		/** Create event: {$ev.id}.
		 * 
		 * Create and initialize a '{$ev.id}' event.
		 * 
		 * \\return New event, or 0 if an error occured.
		 */
		IF{$ev.id|uppercase(1)}Event* create{$ev.id|uppercase(1)}Event();{/section}{section createPropertyAccessorDecl}{if prop.style == "vector"}
		
		/** Get number of {$prop.element.name|lowercase(1)}s.
		 *
{swrap 75 "		 * "}\\return Number of {$prop.element.name|lowercase(1)}s.{/swrap}
		 */
{swrap 75 "		"}virtual unsigned int getNum{$prop.element.name|uppercase(1)}s() const;{/swrap}
		
		/** Get {$prop.element.name|lowercase(1)}.
		 *
{swrap 75 "		 * "}Get the {$prop.element.name|lowercase(1)} at the specified index.{/swrap}
		 *
{swrap 75 "		 * "}\\param elementIndex Element index.{/swrap}
		 *
{swrap 75 "		 * "}\\return {$prop.element.name|uppercase(1)} at specified index.{/swrap}
		 */
{swrap 75 "		"}virtual {$prop.element.type} get{$prop.element.name|uppercase(1)}(unsigned int elementIndex = 0) const;{/swrap}
{if prop.readOnly != "true"}		
		/** Get {$prop.desc|lowercase(1)}.
		 *
{swrap 75 "		 * "}\\return {$prop.desc|lowercase(1)}.{/swrap}
		 */
{swrap 75 "		"}virtual std::vector<{$prop.element.type}>& get{$prop.name|uppercase(1)}();{/swrap}
		
		/** Add {$prop.element.name|lowercase(1)}.
		 *
{swrap 75 "		 * "}Add a {$prop.element.name|lowercase(1)}.{/swrap}
		 *
{swrap 75 "		 * "}\\param addElement {$prop.element.name|uppercase(1)} to be added.{/swrap}
		 */
{swrap 75 "		"}virtual void add{$prop.element.name|uppercase(1)}({if prop.element.addType == ""}{$prop.element.type}{else}{$prop.element.addType}{/if} addElement);{/swrap}
		
		/** Remove {$prop.element.name|lowercase(1)}.
		 *
{swrap 75 "		 * "}Remove a {$prop.element.name|lowercase(1)}.{/swrap}
		 *
{swrap 75 "		 * "}\\param removeElement {$prop.element.name|uppercase(1)} to be removed.{/swrap}
		 */
{swrap 75 "		"}virtual void remove{$prop.element.name|uppercase(1)}({if prop.element.removeType == ""}{$prop.element.type}{else}{$prop.element.removeType}{/if} removeElement);{/swrap}
		
		/** Clear {$prop.element.name|lowercase(1)}s.
		 *
{swrap 75 "		 * "}Clear all {$prop.element.name|lowercase(1)}s.{/swrap}
		 */
{swrap 75 "		"}virtual void clear{$prop.element.name|uppercase(1)}s();{/swrap}{/if}{else}{if prop.style == "map"}
		
		/** Get number of {$prop.element.name|lowercase(1)}s.
		 *
{swrap 75 "		 * "}\\return Number of {$prop.element.name|lowercase(1)}s.{/swrap}
		 */
{swrap 75 "		"}virtual unsigned int getNum{$prop.element.name|uppercase(1)}s() const;{/swrap}
		
		/** Get {$prop.element.name|lowercase(1)}.
		 *
{swrap 75 "		 * "}Get the {$prop.element.name|lowercase(1)} with the specified key.{/swrap}
		 *
{swrap 75 "		 * "}\\param elementKey Element key.{/swrap}
		 *
{swrap 75 "		 * "}\\return {$prop.element.name|uppercase(1)} with specified key.{/swrap}
		 */
{swrap 75 "		"}virtual {$prop.element.type} get{$prop.element.name|uppercase(1)}({if prop.key.accessType != ""}{$prop.key.accessType}{else}{$prop.key.type}{/if} elementKey) const;{/swrap}
{if prop.readOnly != "true"}		
		/** Get {$prop.desc|lowercase(1)}.
		 *
{swrap 75 "		 * "}\\return {$prop.desc|lowercase(1)}.{/swrap}
		 */
{swrap 75 "		"}virtual std::map<{$prop.key.type}, {$prop.element.type}>& get{$prop.name|uppercase(1)}();{/swrap}
		
		/** Add {$prop.element.name|lowercase(1)}.
		 *
{swrap 75 "		 * "}Add a {$prop.element.name|lowercase(1)}.{/swrap}
		 *
		 * \\param elementKey Element key.
{swrap 75 "		 * "}\\param addElement {$prop.element.name|uppercase(1)} to be added.{/swrap}
		 */
{swrap 75 "		"}virtual void add{$prop.element.name|uppercase(1)}({if prop.key.accessType != ""}{$prop.key.accessType}{else}{$prop.key.type}{/if} elementKey, {if prop.element.addType == ""}{$prop.element.type}{else}{$prop.element.addType}{/if} addElement);{/swrap}
		
		/** Remove {$prop.element.name|lowercase(1)}.
		 *
{swrap 75 "		 * "}Remove the {$prop.element.name|lowercase(1)} with the specified key.{/swrap}
		 *
		 * \\param elementKey Element key.
		 */
{swrap 75 "		"}virtual void remove{$prop.element.name|uppercase(1)}({if prop.key.accessType != ""}{$prop.key.accessType}{else}{$prop.key.type}{/if} elementKey);{/swrap}
		
		/** Clear {$prop.element.name|lowercase(1)}s.
		 *
{swrap 75 "		 * "}Clear all {$prop.element.name|lowercase(1)}s.{/swrap}
		 */
{swrap 75 "		"}virtual void clear{$prop.element.name|uppercase(1)}s();{/swrap}{/if}{else}{if prop.readOnly != "true"}
		
		/** Set {$prop.desc|lowercase(1)}.
		 *
		 * Set new value of {$prop.desc|lowercase(1)}.
		 *
{swrap 75 "		 * "}\\param new{$prop.name|uppercase(1)} New value of {$prop.desc|lowercase(1)}.{/swrap}
		 */
{swrap 75 "		"}virtual void set{$prop.name|uppercase(1)}({$prop.setFromType} new{$prop.name|uppercase(1)});{/swrap}{/if}
		
		/** Get {$prop.desc|lowercase(1)}.
		 *
{swrap 75 "		 * "}\\return Current value of {$prop.desc|lowercase(1)}.{/swrap}
		 */
{swrap 75 "		"}virtual {$prop.type} get{$prop.name|uppercase(1)}() const;{/swrap}{/if}{/if}{/section}\#ifndef {$project.includeGuardPrefix}{$class.name|uppercase}
\#define {$project.includeGuardPrefix}{$class.name|uppercase}
/* ==========================================================================
 * {$project.name}
 * Copyright © {$project.copyrightYear} {$project.author}
 * {$project.mail}
 * --------------------------------------------------------------------------
{swrap 75 ' * '}{$class.name|append('.hpp')|rpad(' ', 30)}  {$class.shortDesc} (header).{/swrap}{if project.license == "GPL"}{ref insertGPLDisclaimer}{/if}
 * ========================================================================== */{ref insertIncludes}{foreach un in undef.header}
\#undef {$un}{/foreach}{ref insertIFObjectForwards}{foreach ns in namespace}

namespace {$ns.name}
\{{/foreach}{ref insertForwards}{ref insertTypedefs}{if class.group.shortDesc != ""}

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
class {$class.name}{if ( haveBaseIFObject == 1 ) || ( haveBaseOther == 1 )}
: {swrap 75}{foreach bc in class.base.ifobject}{if bc.inheritanceType == ""}public{else}{$bc.inheritanceType}{/if} Ionflux::ObjectBase::{$bc.name}{notlast}, {/notlast}{/foreach}{foreach bc in class.base.other}{first}{if haveBaseIFObject == 1}, {/if}{/first}{single}{if haveBaseIFObject == 1}, {/if}{/single}{if bc.inheritanceType == ""}public{else}{$bc.inheritanceType}{/if} {$bc.name}{notlast}, {/notlast}{/foreach}{/swrap}{/if}
\{
	private:
{foreach var in variable.private}		/// {$var.desc}.
		{if var.spec != ""}{$var.spec} {/if}{$var.type} {$var.name}{if var.arraySize != ""}[{$var.arraySize}]{/if};
{/foreach}{foreach prop in property.private}		/// {$prop.desc}.
		{if prop.style == "vector"}std::vector<{$prop.element.type}>{else}{if prop.style == "map"}std::map<{$prop.key.type}, {$prop.element.type}>{else}{$prop.type}{/if}{/if} {$prop.name};
{/foreach}{foreach const in constant.private}		/// {$const.desc}.
		static const {$const.type} {$const.name};
{/foreach}{foreach func in function.private}		
		/** {$func.shortDesc}.{if func.longDesc != ""}
		 *
{$func.longDesc|swrap(72,'		 * ')}{/if}{foreach prm in func.param}{first}
		 *{/first}{single}
		 *{/single}
{swrap 75 "		 * "}\\param {$prm.name} {$prm.desc}.{/swrap}{/foreach}{if func.return.value != ""}
		 *
{swrap 75 "		 * "}\\return {$func.return.desc}.{/swrap}{/if}
		 */
{swrap 75 "		"}{$func.spec} {$func.type} {$func.name}({foreach prm in func.param}{$prm.type} {$prm.name}{if prm.default != ""} = {$prm.default}{/if}{first}, {/first}{mid}, {/mid}{/foreach}){if func.const == "true"} const{/if}{if func.pureVirtual == "true"} = 0{/if};{/swrap}
{/foreach}		
	protected:{foreach var in variable.protected}
		/// {$var.desc}.
		{if var.spec != ""}{$var.spec} {/if}{$var.type} {$var.name}{if var.arraySize != ""}[{$var.arraySize}]{/if};{/foreach}{foreach prop in property.protected}
		/// {$prop.desc}.
		{if prop.style == "vector"}std::vector<{$prop.element.type}>{else}{if prop.style == "map"}std::map<{$prop.key.type}, {$prop.element.type}>{else}{$prop.type}{/if}{/if} {$prop.name};{/foreach}{foreach sig in signal}{foreach ins in sig.instance}
		/// Signal: {$ins.desc}.
		IF{$si.id|uppercase(1)}Signal signal{$ins.name|uppercase(1)};
		/// Signal wrapper: {$ins.desc}.
		Ionflux::ObjectBase::IFSignal* signal{$ins.name|uppercase(1)}Wrapper;{/foreach}{/foreach}{foreach const in constant.protected}
		/// {$const.desc}.
		static const {$const.type} {$const.name};{/foreach}{foreach func in function.protected}
		
		/** {$func.shortDesc}.{if func.longDesc != ""}
		 *
{$func.longDesc|swrap(72,'		 * ')}{/if}{foreach prm in func.param}{first}
		 *{/first}{single}
		 *{/single}
{swrap 75 "		 * "}\\param {$prm.name} {$prm.desc}.{/swrap}{/foreach}{if func.return.value != ""}
		 *
{swrap 75 "		 * "}\\return {$func.return.desc}.{/swrap}{/if}
		 */
{swrap 75 "		"}{$func.spec} {$func.type} {$func.name}({foreach prm in func.param}{$prm.type} {$prm.name}{if prm.default != ""} = {$prm.default}{/if}{first}, {/first}{mid}, {/mid}{/foreach}){if func.const == "true"} const{/if}{if func.pureVirtual == "true"} = 0{/if};{/swrap}{/foreach}{foreach op in operation}
		
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
			Ionflux::ObjectBase::IFObjectVector* target = 0) const;{/if}
		
	public:{foreach var in variable.public}
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
		static const Ionflux::ObjectBase::IFClassInfo* CLASS_INFO;{/if}
		
		/** Constructor.
		 *
		 * Construct new {$class.name} object.
		 */
		{$class.name}();
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
		virtual ~{$class.name}();{foreach ev in event}{ref createEventHelperFunctionDecl}{/foreach}{foreach func in function.public}
		
		/** {$func.shortDesc}.{if func.longDesc != ""}
		 *
{$func.longDesc|swrap(72,'		 * ')}{/if}{foreach prm in func.param}{first}
		 *{/first}{single}
		 *{/single}
{swrap 75 "		 * "}\\param {$prm.name} {$prm.desc}.{/swrap}{/foreach}{if func.return.value != ""}
		 *
{swrap 75 "		 * "}\\return {$func.return.desc}.{/swrap}{/if}
		 */
{swrap 75 "		"}{$func.spec} {$func.type} {$func.name}({foreach prm in func.param}{$prm.type} {$prm.name}{if prm.default != ""} = {$prm.default}{/if}{first}, {/first}{mid}, {/mid}{/foreach}){if func.const == "true"} const{/if}{if func.pureVirtual == "true"} = 0{/if};{/swrap}{/foreach}{if enableSerialize == 1}
		
		/** Serialize.
		 *
		 * Serialize the object. This creates a string which contains data 
		 * from which the internal state of the object (as supported 
		 * by serialization) can be restored using deserialize().
		 *
		 * \\param target where to store the result
		 *
		 * \\return \\c true on success, \\c false otherwise.
		 *
		 * \\sa deserialize()
		 */
		virtual bool serialize(std::string& target) const;
		
		/** Deserialize.
		 *
		 * Initialize the object from a serialized representation of its 
		 * internal state. The serialized representation can be obtained 
		 * using serialize().
		 *
		 * \\param source serialized data buffer
		 * \\param offset position where to start deserialization
		 *
		 * \\return offset of remaining data, or -1 if an error occured.
		 *
		 * \\sa serialize()
		 */
		virtual int deserialize(const std::string& source, int offset = 0);{/if}{foreach prop in property.private}{ref createPropertyAccessorDecl}{/foreach}{foreach prop in property.protected}{ref createPropertyAccessorDecl}{/foreach}{foreach sig in signal}{foreach ins in sig.instance}
		
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
		virtual Ionflux::ObjectBase::IFSignal* getSignal{$ins.name|uppercase(1)}Wrapper();{/foreach}{/foreach}
\};{foreach func in function.global}

/** {$func.shortDesc}.{if func.longDesc != ""}
 *
{$func.longDesc|swrap(72,' * ')}{/if}{foreach prm in func.param}{first}
 *{/first}{single}
 *{/single}
{swrap 75 " * "}\\param {$prm.name} {$prm.desc}.{/swrap}{/foreach}{if func.return.value != ""}
 *
{swrap 75 " * "}\\return {$func.return.desc}.{/swrap}{/if}
 */
{swrap 75}{$func.type} {$func.name}({foreach prm in func.param}{$prm.type} {$prm.name}{if prm.default != ""} = {$prm.default}{/if}{first}, {/first}{mid}, {/mid}{/foreach}){if func.const == "true"} const{/if}{if func.pureVirtual == "true"} = 0{/if};{/swrap}{/foreach}{if class.group.shortDesc != ""}

/// @\}
{/if}{foreach ns in namespace}

\}{/foreach}

/** \\file {$class.name}.hpp
 * \\brief {$class.shortDesc} (header).
 */
\#endif
