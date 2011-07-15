# ==========================================================================
# Ionflux Object Base System
# Copyright © 2006-2009 Joern P. Meier
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
{section checkFeatures}{$haveForwards = 0}{foreach fw in forward}{if fw != ""}{$haveForwards = 1}{/if}{/foreach}{$haveTypedefs = 0}{foreach td in typedef}{if td != ""}{$haveTypedefs = 1}{/if}{/foreach}{$haveEvents = 0}{foreach ev in event}{if ev.id != ""}{$haveEvents = 1}{/if}{/foreach}{$haveSignals = 0}{foreach si in signal}{if si.id != ""}{$haveSignals = 1}{/if}{/foreach}{$haveBaseIFObject = 0}{foreach bc in class.base.ifobject}{if bc.name != ""}{$haveBaseIFObject = 1}{/if}{/foreach}{$haveBaseOther = 0}{foreach bc in class.base.other}{if bc.name != ""}{$haveBaseOther = 1}{/if}{/foreach}{$enableClassInfo = 0}{if ( haveBaseIFObject == 1 ) || ( class.name == "IFObject" )}{$enableClassInfo = 1}{/if}{$abstractClass = 0}{foreach func in function.public}{if func.pureVirtual == "true"}{$abstractClass = 1}{/if}{/foreach}{foreach func in function.protected}{if func.pureVirtual == "true"}{$abstractClass = 1}{/if}{/foreach}{$enableMutex = 0}{$enableGuards = 0}{$enableAutoGuards = 0}{$enableLogMessage = 0}{$enableSignal = haveSignals}{$enableSerialize = 0}{$enablePersistence = 0}{$enableCopy = 0}{$enableUpcast = 0}{$enableCreate = 0}{$enableParam = 0}{foreach fe in class.features}{if fe == "mutex"}{$enableMutex = 1}{/if}{if fe == "guards"}{$enableMutex = 1}{$enableGuards = 1}{/if}{if fe == "autoguards"}{$enableMutex = 1}{$enableGuards = 1}{$enableAutoGuards = 1}{/if}{if fe == "logmessage"}{$enableLogMessage = 1}{/if}{if fe == "signal"}{$enableSignal = 1}{/if}{if fe == "serialize"}{$enableSerialize = 1}{/if}{if fe == "classinfo"}{$enableClassInfo = 1}{/if}{if fe == "persistence"}{$enablePersistence = 1}{/if}{if fe == "copy"}{$enableCopy = 1}{/if}{if fe == "upcast"}{$enableUpcast = 1}{/if}{if fe == "create"}{$enableCreate = 1}{/if}{if fe == "param"}{$enableParam = 1}{/if}{/foreach}{$haveOps = 0}{foreach op in operation}{if op.name != ""}{$haveOps = 1}{/if}{/foreach}{$haveBasePersistent = 0}{if enablePersistence == 1}{if class.persistence.backendBase != ""}{$haveBasePersistent = 1}{/if}{if class.persistence.backend == ""}{$class.persistence.backend = class.name + "Backend"}{/if}{/if}{/section}{ref checkFeatures}{section insertGPLDisclaimer}
 * =========================================================================
 *
{swrap 75 " * "}This file is part of {$project.name}.

{$project.name} is free software; you can redistribute it and/or modify it under the terms of the GNU General Public License as published by the Free Software Foundation; either version 2 of the License, or (at your option) any later version.

{$project.name} is distributed in the hope that it will be useful, but WITHOUT ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU General Public License for more details.

You should have received a copy of the GNU General Public License along with {$project.name}; if not, write to the Free Software Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA 02111-1307 USA{/swrap}
 * {/section}{section insertIncludes}{foreach inc in include.header}{first}
{/first}{single}
{/single}
\#include {$inc}{/foreach}{if enablePersistence == 1}
\#include "{$project.persistence.include}"{/if}{foreach bc in class.base.ifobject}
\#include "{if bc.include == ""}ifobject/{$bc.name}.hpp{else}{$bc.include}{/if}"{/foreach}{foreach bc in class.base.other}{if bc.include != "<none>"}
\#include "{if bc.include == ""}{$bc.name}.hpp{else}{$bc.include}{/if}"{/if}{/foreach}{/section}{section insertForwards}{foreach fwd in forward}{first}
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
		IF{$ev.id|uppercase(1)}Event* create{$ev.id|uppercase(1)}Event();{/section}{section declareGlobalFunc}

/** {$func.shortDesc}.{if func.longDesc != ""}
 *
{$func.longDesc|swrap(72,' * ')}{/if}{foreach prm in func.param}{first}
 *{/first}{single}
 *{/single}
{swrap 75 " * "}\\param {$prm.name} {$prm.desc}.{/swrap}{/foreach}{if func.return.value != ""}
 *
{swrap 75 " * "}\\return {$func.return.desc}.{/swrap}{/if}
 */
{swrap 75}{$func.type} {$func.name}({foreach prm in func.param}{$prm.type} {$prm.name}{if prm.default != ""} = {$prm.default}{/if}{first}, {/first}{mid}, {/mid}{/foreach}){if func.const == "true"} const{/if}{if func.pureVirtual == "true"} = 0{/if};{/swrap}{/section}{section declarePropertyClearFunc}
		
		/** Clear {if prop.element.plural == ""}{$prop.element.name|lowercase(1)}s{else}{$prop.element.plural|lowercase(1)}{/if}.
		 *
{swrap 75 "		 * "}Clear all {if prop.element.plural == ""}{$prop.element.name|lowercase(1)}s{else}{$prop.element.plural|lowercase(1)}{/if}.{/swrap}
		 */
{swrap 75 "		"}virtual void clear{if prop.element.plural == ""}{$prop.element.name|uppercase(1)}s{else}{$prop.element.plural|uppercase(1)}{/if}();{/swrap}{/section}{section declareVectorWriteFuncs}{if prop.hideImpl != "true"}
        
		/** Get {$prop.desc|lowercase(1)}.
		 *
{swrap 75 "		 * "}\\return {$prop.desc|lowercase(1)}.{/swrap}
		 */
{swrap 75 "		"}virtual std::vector<{$prop.element.type}>& get{if prop.element.plural == ""}{$prop.element.name|uppercase(1)}s{else}{$prop.element.plural|uppercase(1)}{/if}();{/swrap}{/if}
		
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
		
		/** Remove {$prop.element.name|lowercase(1)}.
		 *
{swrap 75 "		 * "}Remove a {$prop.element.name|lowercase(1)}.{/swrap}
		 *
{swrap 75 "		 * "}\\param removeElement {$prop.element.name|uppercase(1)} to be removed.{/swrap}
		 */
{swrap 75 "		"}virtual void remove{$prop.element.name|uppercase(1)}Index(unsigned int removeIndex);{/swrap}{ref declarePropertyClearFunc}{/section}{section declareMapWriteFuncs}{if prop.hideImpl != "true"}
        
		/** Get {$prop.desc|lowercase(1)}.
		 *
{swrap 75 "		 * "}\\return {$prop.desc|lowercase(1)}.{/swrap}
		 */
{swrap 75 "		"}virtual std::map<{$prop.key.type}, {$prop.element.type}>& get{if prop.element.plural == ""}{$prop.element.name|uppercase(1)}s{else}{$prop.element.plural|uppercase(1)}{/if}();{/swrap}{/if}
		
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
{swrap 75 "		"}virtual void remove{$prop.element.name|uppercase(1)}({if prop.key.accessType != ""}{$prop.key.accessType}{else}{$prop.key.type}{/if} elementKey);{/swrap}{ref declarePropertyClearFunc}{/section}{section declarePropertyWriteFuncs}{if prop.style == "vector"}{ref declareVectorWriteFuncs}{else}{if prop.style == "map"}{ref declareMapWriteFuncs}{else}
		
		/** Set {$prop.desc|lowercase(1)}.
		 *
		 * Set new value of {$prop.desc|lowercase(1)}.
		 *
{swrap 75 "		 * "}\\param new{$prop.name|uppercase(1)} New value of {$prop.desc|lowercase(1)}.{/swrap}
		 */
{swrap 75 "		"}virtual void set{$prop.name|uppercase(1)}({$prop.setFromType} new{$prop.name|uppercase(1)});{/swrap}{/if}{/if}{/section}{section createVectorAccessorDecl}
		
		/** Get number of {if prop.element.plural == ""}{$prop.element.name|lowercase(1)}s{else}{$prop.element.plural|lowercase(1)}{/if}.
		 *
{swrap 75 "		 * "}\\return Number of {if prop.element.plural == ""}{$prop.element.name|lowercase(1)}s{else}{$prop.element.plural|lowercase(1)}{/if}.{/swrap}
		 */
{swrap 75 "		"}virtual unsigned int getNum{if prop.element.plural == ""}{$prop.element.name|uppercase(1)}s{else}{$prop.element.plural|uppercase(1)}{/if}() const;{/swrap}
		
		/** Get {$prop.element.name|lowercase(1)}.
		 *
{swrap 75 "		 * "}Get the {$prop.element.name|lowercase(1)} at the specified index.{/swrap}
		 *
{swrap 75 "		 * "}\\param elementIndex Element index.{/swrap}
		 *
{swrap 75 "		 * "}\\return {$prop.element.name|uppercase(1)} at specified index.{/swrap}
		 */
{swrap 75 "		"}virtual {$prop.element.type} get{$prop.element.name|uppercase(1)}(unsigned int elementIndex = 0) const;{/swrap}
		
		/** Find {$prop.element.name|lowercase(1)}.
		 *
{swrap 75 "		 * "}Find the specified occurence of a {$prop.element.name|lowercase(1)}.{/swrap}
		 *
{swrap 75 "		 * "}\\param needle {$prop.element.name|uppercase(1)} to be found.{/swrap}
{swrap 75 "		 * "}\\param occurence Number of the occurence to be found.{/swrap}
		 *
{swrap 75 "		 * "}\\return Index of the {$prop.element.name|lowercase(1)}, or -1 if the {$prop.element.name|lowercase(1)} cannot be found.{/swrap}
		 */
{swrap 75 "		"}virtual int find{$prop.element.name|uppercase(1)}({if prop.element.findType == ""}{$prop.element.type}{else}{$prop.element.findType}{/if} needle, unsigned int occurence = 1) const;{/swrap}{/section}{section createMapAccessorDecl}
		
		/** Get number of {if prop.element.plural == ""}{$prop.element.name|lowercase(1)}s{else}{$prop.element.plural|lowercase(1)}{/if}.
		 *
{swrap 75 "		 * "}\\return Number of {if prop.element.plural == ""}{$prop.element.name|lowercase(1)}s{else}{$prop.element.plural|lowercase(1)}{/if}.{/swrap}
		 */
{swrap 75 "		"}virtual unsigned int getNum{if prop.element.plural == ""}{$prop.element.name|uppercase(1)}s{else}{$prop.element.plural|uppercase(1)}{/if}() const;{/swrap}
		
		/** Get {$prop.element.name|lowercase(1)}.
		 *
{swrap 75 "		 * "}Get the {$prop.element.name|lowercase(1)} with the specified key.{/swrap}
		 *
{swrap 75 "		 * "}\\param elementKey Element key.{/swrap}
		 *
{swrap 75 "		 * "}\\return {$prop.element.name|uppercase(1)} with specified key.{/swrap}
		 */
{swrap 75 "		"}virtual {$prop.element.type} get{$prop.element.name|uppercase(1)}({if prop.key.accessType != ""}{$prop.key.accessType}{else}{$prop.key.type}{/if} elementKey) const;{/swrap}{/section}{section createPropertyAccessorDecl}{if prop.style == "vector"}{ref createVectorAccessorDecl}{else}{if prop.style == "map"}{ref createMapAccessorDecl}{else}
		
		/** Get {$prop.desc|lowercase(1)}.
		 *
{swrap 75 "		 * "}\\return Current value of {$prop.desc|lowercase(1)}.{/swrap}
		 */
{swrap 75 "		"}virtual {$prop.type} get{$prop.name|uppercase(1)}() const;{/swrap}{/if}{/if}{/section}{section declarePersistentInitFunc}
        
        /** Set from {$prop.name|uppercase(1)}.
		 *
		 * Initialize the object from an existing persistent object with the 
		 * specified {$prop.name|uppercase(1)}.
		 *
		 * \\param init{$prop.name|uppercase(1)} {$prop.name|uppercase(1)}.
		 *
		 * \\return \\c true on success, \\c false otherwise.
		 */
		virtual bool setFrom{$prop.name|uppercase(1)}({$prop.setFromType} init{$prop.name|uppercase(1)});{/section}{section declarePersistenceFuncs}{if haveBasePersistent == 0}
		
		/** Update.
		 *
		 * Update record.
		 */
		virtual void update();
		
		/** Remove.
		 *
		 * Remove record.
		 */
		virtual void remove();
		
		/** Get persistent ID.
		 *
		 * Get the ID of the persistent backend object.
		 */
		virtual int getPersistentID();
		
		/** Set from ID.
		 *
		 * Initialize the object from an existing persistent object with the 
		 * specified ID.
		 *
		 * \\param objectID Object ID.
		 *
		 * \\return \\c true on success, \\c false otherwise.
		 */
		virtual bool setFromID(int objectID);{/if}
		
		/** Get persistent backend object.
		 *
		 * Get the persistent backend object. This should be used by classes 
		 * that use a derived backend object to ensure the class can work with 
		 * the more specific type of the backend object.
		 */
		virtual {$project.persistence.namespace}::{$class.persistence.backend}* getPersistent() const;
		
        /** Get objects.
		 *
		 * Get objects matching the specified expression from the database. 
		 * The returned objects are not referenced and must be managed by the 
		 * caller.
		 *
		 * \\param database Database.
		 * \\param expr Expression.
		 * \\param target Where to store the objects.
		 *
		 * \\return Number of objects.
		 */
		static unsigned int getPersistentObjects(
		    {$project.persistence.namespace}::{$project.persistence.database}* database, 
		    std::vector<{foreach ns in namespace}{$ns.name}::{/foreach}{$class.name}*>& target, 
		    const litesql::Expr& expr = litesql::Expr());{foreach prop in property.protected}{if prop.persistentInit == "true"}{ref declarePersistentInitFunc}{/if}{/foreach}{foreach prop in property.private}{if prop.persistentInit == "true"}{ref declarePersistentInitFunc}{/if}{/foreach}{/section}{section declarePersistentProtectedFuncs}
		
		/** Initialize persistent backend object.
		 *
		 * Initialize the persistent backend object.
		 */
		virtual void initPersistentBackend();
		
		/** Set backend object state.
		 *
		 * Set the state of the persistent backend object to the state of the 
		 * object obtained from the database using the specified litesql 
		 * expression.
		 * 
		 * \param expr Expression.
		 */
		virtual void setPersistentBackendState(const litesql::Expr& expr);{/section}{section declareCopyFuncs}
		
		/** Assignment operator.
		 *
		 * Assign an object.
		 *
		 * \param other Other object.
		 *
		 * \return The object itself.
		 */
{swrap 75 "		"}virtual {foreach ns in namespace}{$ns.name}::{/foreach}{$class.name}& operator=(const {foreach ns in namespace}{$ns.name}::{/foreach}{$class.name}& other);{/swrap}{if abstractClass == 0}
		
		/** Copy.
		 *
		 * Create a copy of the object.
		 *
		 * \return Newly allocated copy of the object.
		 */
{swrap 75 "		"}virtual {foreach ns in namespace}{$ns.name}::{/foreach}{$class.name}* copy() const;{/swrap}{/if}{/section}{section declareUpcastFuncs}
		
		/** Upcast.
		 *
		 * Cast an IFObject to the most specific type.
		 *
		 * \param other Other object.
		 *
		 * \return The more specific object, or 0 if the cast failed.
		 */
{swrap 75 "		"}static {foreach ns in namespace}{$ns.name}::{/foreach}{$class.name}* upcast(Ionflux::ObjectBase::IFObject* other);{/swrap}{/section}{section declareCreateFuncs}
		
		/** Create instance.
		 *
		 * Create a new instance of the class. If the optional parent object 
		 * is specified, a local reference for the new object will be added 
		 * to the parent object.
		 *
		 * \param parentObject Parent object.
		 *
		 * \return Pointer to the new instance.
		 */
{swrap 75 "		"}static {foreach ns in namespace}{$ns.name}::{/foreach}{$class.name}* create(Ionflux::ObjectBase::IFObject* parentObject = 0);{/swrap}{if enablePersistence == 1}
		
		/** Create instance.
		 *
		 * Create a new instance of the class.
		 *
		 * \param initDatabase Database.
		 * \param objectID Object ID.
		 *
		 * \return Pointer to the new instance.
		 */
{swrap 75 "		"}static {foreach ns in namespace}{$ns.name}::{/foreach}{$class.name}* create({$project.persistence.namespace}::{$project.persistence.database}* initDatabase, int objectID = -1);{/swrap}{/if}{/section}{section declareParamFuncs}{foreach prm in class.param}
		
		/** Set parameter.
		 *
		 * Set the parameter with the specified ID.
		 *
		 * \param paramID Parameter ID.
		 * \param paramValue Parameter value.
		 */
{swrap 75 "		"}virtual void set{$prm.name|uppercase(1)}(Ionflux::ObjectBase::IFParamID paramID, {$prm.type} paramValue);{/swrap}
		
		/** Get parameter.
		 *
		 * Get the parameter with the specified ID.
		 *
		 * \param paramID Parameter ID.
		 */
{swrap 75 "		"}virtual {$prm.type} get{$prm.name|uppercase(1)}(Ionflux::ObjectBase::IFParamID paramID);{/swrap}{/foreach}{/section}{section declareFunc}
		
		/** {$func.shortDesc}.{if func.longDesc != ""}
		 *
{$func.longDesc|swrap(72,'		 * ')}{/if}{foreach prm in func.param}{first}
		 *{/first}{single}
		 *{/single}
{swrap 75 "		 * "}\\param {$prm.name} {$prm.desc}.{/swrap}{/foreach}{if func.return.value != ""}
		 *
{swrap 75 "		 * "}\\return {$func.return.desc}.{/swrap}{/if}
		 */
{swrap 75 "		"}{$func.spec} {$func.type} {$func.name}({foreach prm in func.param}{$prm.type} {$prm.name}{if prm.default != ""} = {$prm.default}{/if}{first}, {/first}{mid}, {/mid}{/foreach}){if func.const == "true"} const{/if}{if func.throw != ""} throw({if func.throw != "<none>"}{$func.throw}{/if}){/if}{if func.pureVirtual == "true"} = 0{/if};{/swrap}{/section}\#ifndef {$project.includeGuardPrefix}{$class.name|uppercase}
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
		static const Ionflux::ObjectBase::IFClassInfo* CLASS_INFO;{/if}
		
		/** Constructor.
		 *
		 * Construct new {$class.name} object.
		 */
		{$class.name}();{if enablePersistence == 1}
		
		/** Constructor.
		 *
		 * Construct new {$class.name} object.
		 *
		 * \param initDatabase Database.
		 * \param objectID Object ID.
		 */
		{$class.name}({$project.persistence.namespace}::{$project.persistence.database}* initDatabase, int objectID = -1);
		
		/** Constructor.
		 *
		 * Construct new {$class.name} object.
		 *
		 * \param initDatabase Database.
		 * \param initPersistent Persistent backend object.
		 */
		{$class.name}({$project.persistence.namespace}::{$project.persistence.database}* initDatabase, {$project.persistence.namespace}::{$class.persistence.backend}* initPersistent);{/if}{if enableCopy == 1}
		
		/** Constructor.
		 *
		 * Construct new {$class.name} object.
		 *
		 * \param other Other object.
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
		virtual ~{$class.name}(){if destructor.throw != ""} throw({if destructor.throw != "<none>"}{$destructor.throw}{/if}){/if};{foreach ev in event}{ref createEventHelperFunctionDecl}{/foreach}{foreach func in function.public}{ref declareFunc}{/foreach}{if enableSerialize == 1}
		
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
		virtual int deserialize(const std::string& source, int offset = 0);{/if}{if enablePersistence == 1}{ref declarePersistenceFuncs}{/if}{if enableCopy == 1}{ref declareCopyFuncs}{/if}{if enableUpcast == 1}{ref declareUpcastFuncs}{/if}{if enableCreate == 1}{ref declareCreateFuncs}{/if}{if enableParam == 1}{ref declareParamFuncs}{/if}{foreach prop in property.private}{ref createPropertyAccessorDecl}{/foreach}{foreach prop in property.protected}{ref createPropertyAccessorDecl}{if prop.readOnly != "true"}{ref declarePropertyWriteFuncs}{/if}{/foreach}{if enablePersistence == 1}{if haveBasePersistent == 0}{$prop.style = ""}{$prop.readOnly = "false"}{$prop.name = "database"}{$prop.desc = "Database"}{$prop.type = project.persistence.namespace + "::" + project.persistence.database + "*"}{$prop.setFromType = project.persistence.namespace + "::" + project.persistence.database + "*"}{ref createPropertyAccessorDecl}{ref declarePropertyWriteFuncs}{/if}{/if}{foreach sig in signal}{foreach ins in sig.instance}
		
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
