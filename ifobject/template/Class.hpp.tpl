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
{section insertGPLDisclaimer}
 * =========================================================================
{swrap 75 " * "}This file is part of {$project.name}.

{$project.name} is free software; you can redistribute it and/or modify it under the terms of the GNU General Public License as published by the Free Software Foundation; either version 2 of the License, or (at your option) any later version.

{$project.name} is distributed in the hope that it will be useful, but WITHOUT ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU General Public License for more details.

You should have received a copy of the GNU General Public License along with {$project.name}; if not, write to the Free Software Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA 02111-1307 USA{/swrap}{/section}{section createPropertyAccessorDecl}		{if prop.style == "vector"}
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
{swrap 75 "		"}virtual void clear{$prop.element.name|uppercase(1)}s();{/swrap}
{/if}{else}{if prop.style == "map"}
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
{swrap 75 "		"}virtual void clear{$prop.element.name|uppercase(1)}s();{/swrap}
{/if}{else}{if prop.readOnly != "true"}
		/** Set {$prop.desc|lowercase(1)}.
		 *
		 * Set new value of {$prop.desc|lowercase(1)}.
		 *
{swrap 75 "		 * "}\\param new{$prop.name|uppercase(1)} New value of {$prop.desc|lowercase(1)}.{/swrap}
		 */
{swrap 75 "		"}virtual void set{$prop.name|uppercase(1)}({$prop.setFromType} new{$prop.name|uppercase(1)});{/swrap}
		{/if}
		/** Get {$prop.desc|lowercase(1)}.
		 *
{swrap 75 "		 * "}\\return Current value of {$prop.desc|lowercase(1)}.{/swrap}
		 */
{swrap 75 "		"}virtual {$prop.type} get{$prop.name|uppercase(1)}() const;{/swrap}
{/if}{/if}{/section}\#ifndef {$project.includeGuardPrefix}{$class.name|uppercase}
\#define {$project.includeGuardPrefix}{$class.name|uppercase}
/* ==========================================================================
 * {$project.name}
 * Copyright © {$project.copyrightYear} {$project.author}
 * {$project.mail}
 * --------------------------------------------------------------------------
{swrap 75 ' * '}{$class.name|append('.hpp')|rpad(' ', 30)}  {$class.shortDesc} (header).{/swrap}{if project.license == "GPL"}{ref insertGPLDisclaimer}{/if}
 * ========================================================================== */{foreach inc in include.header}{first}
 {/first}{single}
 {/single}
\#include {$inc}{/foreach}{foreach bc in base.ifobject}
\#include "{if bc.include == ""}{$bc.name}.hpp{else}{$bc.include}{/if}"{/foreach}{foreach bc in base.other}
\#include "{if bc.include == ""}{$bc.name}.hpp{else}{$bc.include}{/if}"{/foreach}{foreach un in undef.header}
\#undef {$un}{/foreach}{foreach ns in namespace}

namespace {$ns.name}
\{{/foreach}
# +++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
# ---- Everything below here needs to be validated for use with ifobject ----
# +++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
{$haveSignalForward = 0}{foreach fwd in forward}{first}
{/first}{single}
{/single}
{$fwd}{if fwd == "class IFSignal"}{$haveSignalForward = 1}{/if};{/foreach}{if haveSignalForward == 0}
class IFSignal;{/if}{foreach td in typedef}{first}
{/first}{single}
{/single}
typedef {$td};{/foreach}{foreach sig in signal}
{swrap 75}typedef sigc::signal<{$sig.return.type}{foreach prm in sig.param}, {$prm.type}{/foreach}> {$sig.name};{/swrap}{/foreach}{foreach td in typedefAfterSignals}
typedef {$td};{/foreach}{if class.group.shortDesc != ""}

/** \\addtogroup {$class.group.name} {$class.group.shortDesc}{if class.group.longDesc != ""}
 *
{$class.group.longDesc|swrap(75,' * ')}
 *{/if}
 * @\{
 */{/if}{foreach st in struct}
 
/** {$st.desc}.{if (class.group.shortDesc == "") && (class.group.name != "")}
 * \\ingroup {$class.group.name}{/if}
 */
struct {$st.name}
\{{foreach fi in st.field}
	/// {$fi.desc}.
	{$fi.type} {$fi.name};{/foreach}{foreach cn in st.constant}
	/// {$cn.desc}.
	static const {$cn.type} {$cn.name};{/foreach}{if st.bindings.ruby.createMarkFunction == "true"}
	/// Mark function for the ruby garbage collector.
	static void (*const rubyMark)({$st.name}*);{/if}{if st.refCount.enabled == "true"}
	/// Reference counting information.
	Ionflux::Stuff::ObjectRefInfo* refInfo;{/if}
\};{/foreach}{foreach sig in signal}

/// Signal connections for {$sig.name}.
struct {$sig.name}Connections
\{{foreach ins in sig.instance}
	/// Signal connection: {$ins.desc}
	sigc::connection {$ins.name};{/foreach}
\};{/foreach}{if class.createClassInfo == "true"}

/// Class information for class {$class.name}.
class {$class.name}ClassInfo
: public Ionflux::Stuff::ClassInfo
\{
	public:
		/// Constructor.
		{$class.name}ClassInfo();
		/// Destructor.
		virtual ~{$class.name}ClassInfo() \{ \};
\};{/if}

/** {$class.title}.{if (class.group.shortDesc == "") && (class.group.name != "")}
 * \\ingroup {$class.group.name}{/if}
 *
{$class.longDesc|swrap(75,' * ')}
 */
class {$class.name}{if class.base != ""}
: {$class.base}{/if}{if (class.createClassInfo == "true") ) && ( class.indirectObjectChild != "true" )}{if class.base != ""}, {else}
: {/if}public Ionflux::Stuff::IFObject{/if}
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
	protected:
{foreach var in variable.protected}		/// {$var.desc}.
		{if var.spec != ""}{$var.spec} {/if}{$var.type} {$var.name}{if var.arraySize != ""}[{$var.arraySize}]{/if};
{/foreach}{foreach prop in property.protected}		/// {$prop.desc}.
		{if prop.style == "vector"}std::vector<{$prop.element.type}>{else}{if prop.style == "map"}std::map<{$prop.key.type}, {$prop.element.type}>{else}{$prop.type}{/if}{/if} {$prop.name};
{/foreach}{foreach sig in signal}{foreach ins in sig.instance}		/// Signal: {$ins.desc}.
		{$sig.name} {$ins.name};
		/// Signal wrapper: {$ins.desc}.
		Ionflux::Stuff::Signal* {$ins.name}Wrapper;
{/foreach}{/foreach}{foreach const in constant.protected}		/// {$const.desc}.
		static const {$const.type} {$const.name};
{/foreach}{foreach func in function.protected}		
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
	public:
{foreach var in variable.public}		/// {$var.desc}.
		{if var.spec != ""}{$var.spec} {/if}{$var.type} {$var.name}{if var.arraySize != ""}[{$var.arraySize}]{/if};
{/foreach}{foreach const in constant.public}		/// {$const.desc}.
		static const {$const.type} {$const.name};
{/foreach}{foreach sig in signal}		/// Signal type: {$sig.id}.
		static const SignalType SIGNAL_TYPE_{$sig.id|uppercase};{foreach ins in sig.instance}
		/// Signal name: {$ins.id}.
		static const std::string SIGNAL_NAME_{$ins.id|uppercase};{/foreach}
{/foreach}{if class.createClassInfo == "true"}		/// Class information instance.
		static const {$class.name}ClassInfo {$class.name|lowercase(1)}ClassInfo;
		/// Class information.
		static const Ionflux::Stuff::ClassInfo* CLASS_INFO;
{/if}		
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
		virtual ~{$class.name}();
{foreach func in function.public}		
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
{/foreach}{foreach prop in property.private}{ref createPropertyAccessorDecl}{/foreach}{foreach prop in property.protected}{ref createPropertyAccessorDecl}{/foreach}{foreach sig in signal}{foreach ins in sig.instance}		
		/** Get signal: {$ins.desc}.
		 *
		 * Get the signal for the {$ins.desc} event.
		 *
		 * \\return Signal for the {$ins.desc} event.
		 */
		virtual {$sig.name}& get{$ins.name|uppercase(1)}();
		
		/** Get signal wrapper: {$ins.desc}.
		 *
		 * Get the signal for the {$ins.desc} event.
		 *
		 * \\return Signal for the {$ins.desc} event.
		 */
		virtual Ionflux::Stuff::Signal* get{$ins.name|uppercase(1)}Wrapper();
{/foreach}{/foreach}{if class.bindings.ruby.createMarkFunction == "true"}
		/// Ruby garbage collector mark function.
		virtual void rubyMark() const;
{/if}\};{foreach st in struct}{if st.bindings.ruby.createMarkFunction == "true"}

/// Ruby garbage collector mark function for {$st.name}.
void {$st.name}_rubyMark({$st.name}* targetInstance);{/if}{/foreach}
{foreach func in function.global}
/** {$func.shortDesc}.{if func.longDesc != ""}
 *
{$func.longDesc|swrap(72,' * ')}{/if}{foreach prm in func.param}{first}
 *{/first}{single}
 *{/single}
{swrap 75 " * "}\\param {$prm.name} {$prm.desc}.{/swrap}{/foreach}{if func.return.value != ""}
 *
{swrap 75 " * "}\\return {$func.return.desc}.{/swrap}{/if}
 */
{swrap 75}{$func.type} {$func.name}({foreach prm in func.param}{$prm.type} {$prm.name}{if prm.default != ""} = {$prm.default}{/if}{first}, {/first}{mid}, {/mid}{/foreach}){if func.const == "true"} const{/if}{if func.pureVirtual == "true"} = 0{/if};{/swrap}
{/foreach}{if class.group.shortDesc != ""}
/// @\}
{/if}{foreach ns in namespace}
\}
{/foreach}
/** \\file {$class.name}.hpp
 * \\brief {$class.shortDesc} header.
 */
\#endif
