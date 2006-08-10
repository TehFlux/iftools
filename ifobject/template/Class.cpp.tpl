# ==========================================================================
# Ionflux Object Base System
# Copyright © 2006 Joern P. Meier
# mail@ionflux.org
# --------------------------------------------------------------------------
# Class.cpp.tpl              class template (implementation)
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

You should have received a copy of the GNU General Public License along with {$project.name}; if not, write to the Free Software Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA 02111-1307 USA{/swrap}{/section}{section createPropertyAccessorImpl}{if prop.style == "vector"}
{swrap 75}unsigned int {$class.name}::getNum{$prop.element.name|uppercase(1)}s() const{/swrap}
\{
{if prop.guardMutex != ""}	Guard propertyGuard({$prop.guardMutex});
{/if}	return {$prop.name}.size();
\}

{swrap 75}{$prop.element.type} {$class.name}::get{$prop.element.name|uppercase(1)}(unsigned int elementIndex) const{/swrap}
\{
{if prop.guardMutex != ""}	Guard propertyGuard({$prop.guardMutex});
{/if}	if (elementIndex < {$prop.name}.size())
		return {$prop.name}[elementIndex];
	return {if prop.element.defaultValue != ""}{$prop.element.defaultValue}{else}0{/if};
\}
{if prop.readOnly != "true"}
{swrap 75}std::vector<{$prop.element.type}>& {$class.name}::get{$prop.name|uppercase(1)}(){/swrap}
\{
{if prop.guardMutex != ""}	Guard propertyGuard({$prop.guardMutex});
{/if}	return {$prop.name};
\}

{swrap 75}void {$class.name}::add{$prop.element.name|uppercase(1)}({if prop.element.addType == ""}{$prop.element.type}{else}{$prop.element.addType}{/if} addElement){/swrap}
\{
{if prop.guardMutex != ""}	Guard propertyGuard({$prop.guardMutex});
{/if}	{if prop.element.managed == "true"}addElement->ref();
	{/if}{$prop.name}.push_back(addElement);
\}

{swrap 75}void {$class.name}::remove{$prop.element.name|uppercase(1)}({if prop.element.removeType == ""}{$prop.element.type}{else}{$prop.element.removeType}{/if} removeElement){/swrap}
\{
{if prop.guardMutex != ""}	Guard propertyGuard({$prop.guardMutex});
{/if}	bool found = false;
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
			current{$prop.element.name|uppercase(1)}->unref();{/if}
	\}
\}

{swrap 75}void {$class.name}::clear{$prop.element.name|uppercase(1)}s(){/swrap}
\{
{if prop.guardMutex != ""}	Guard propertyGuard({$prop.guardMutex});
{/if}	{if prop.element.managed == "true"}std::vector<{$prop.element.type}>::iterator i;
	for (i = {$prop.name}.begin(); i != {$prop.name}.end(); i++)
		if (*i != {if prop.element.defaultValue != ""}{$prop.element.defaultValue}{else}0{/if})
			(*i)->unref();
	{/if}{$prop.name}.clear();
\}
{/if}{else}{if prop.style == "map"}
{swrap 75}unsigned int {$class.name}::getNum{$prop.element.name|uppercase(1)}s() const{/swrap}
\{
{if prop.guardMutex != ""}	Guard propertyGuard({$prop.guardMutex});
{/if}	return {$prop.name}.size();
\}

{swrap 75}{$prop.element.type} {$class.name}::get{$prop.element.name|uppercase(1)}({if prop.key.accessType != ""}{$prop.key.accessType}{else}{$prop.key.type}{/if} elementKey) const{/swrap}
\{
{if prop.guardMutex != ""}	Guard propertyGuard({$prop.guardMutex});
{/if}	std::map<{$prop.key.type}, {$prop.element.type}>::const_iterator i = {$prop.name}.find(elementKey);
	if (i != {$prop.name}.end())
		return (*i).second;
	return {if prop.element.defaultValue != ""}{$prop.element.defaultValue}{else}0{/if};
\}
{if prop.readOnly != "true"}
{swrap 75}std::map<{$prop.key.type}, {$prop.element.type}>& {$class.name}::get{$prop.name|uppercase(1)}(){/swrap}
\{
{if prop.guardMutex != ""}	Guard propertyGuard({$prop.guardMutex});
{/if}	return {$prop.name};
\}

{swrap 75}void {$class.name}::add{$prop.element.name|uppercase(1)}({if prop.key.accessType != ""}{$prop.key.accessType}{else}{$prop.key.type}{/if} elementKey, {if prop.element.addType == ""}{$prop.element.type}{else}{$prop.element.addType}{/if} addElement){/swrap}
\{
{if prop.guardMutex != ""}	Guard propertyGuard({$prop.guardMutex});
{/if}	{$prop.element.type} the{$prop.element.name|uppercase(1)} = get{$prop.element.name|uppercase(1)}(elementKey);
	if (the{$prop.element.name|uppercase(1)} != {if prop.element.defaultValue != ""}{$prop.element.defaultValue}{else}0{/if})
		return;
	{$prop.name}[elementKey] = addElement;{if prop.element.managed == "true"}
	addElement->ref();{/if}
\}

{swrap 75}void {$class.name}::remove{$prop.element.name|uppercase(1)}({if prop.key.accessType != ""}{$prop.key.accessType}{else}{$prop.key.type}{/if} elementKey){/swrap}
\{
{if prop.guardMutex != ""}	Guard propertyGuard({$prop.guardMutex});
{/if}	std::map<{$prop.key.type}, {$prop.element.type}>::iterator i = {$prop.name}.find(elementKey);
	if (i != {$prop.name}.end())
	\{
		{if prop.element.managed == "true"}if ((*i).second != {if prop.element.defaultValue != ""}{$prop.element.defaultValue}{else}0{/if})
			(*i).second->unref();
		{/if}{$prop.name}.erase(i);
	\}
\}

{swrap 75}void {$class.name}::clear{$prop.element.name|uppercase(1)}s(){/swrap}
\{
{if prop.guardMutex != ""}	Guard propertyGuard({$prop.guardMutex});
{/if}	{if prop.element.managed == "true"}std::map<{$prop.key.type}, {$prop.element.type}>::iterator i;
	for (i = {$prop.name}.begin(); i != {$prop.name}.end(); i++)
		if ((*i).second != {if prop.element.defaultValue != ""}{$prop.element.defaultValue}{else}0{/if})
			(*i).second->unref();
	{/if}{$prop.name}.clear();
\}
{/if}{else}{if prop.readOnly != "true"}
{swrap 75}void {$class.name}::set{$prop.name|uppercase(1)}({$prop.setFromType} new{$prop.name|uppercase(1)}){/swrap}
\{
{if prop.guardMutex != ""}	Guard propertyGuard({$prop.guardMutex});
{/if}{if prop.impl.set == ""}	{if prop.managed == "true"}if ({$prop.name} == new{$prop.name|uppercase(1)})
		return;
	if ({$prop.name} != 0)
		{$prop.name}->unref();
	{/if}{$prop.name} = new{$prop.name|uppercase(1)};{if prop.managed == "true"}
	if ({$prop.name} != 0)
	\{
		{$prop.name}->ref();{if prop.poolName != ""}
		{$prop.poolName}.addObject({$prop.name});{/if}
	\}{/if}{else}{$prop.impl.set|swrap(75, "	")}{/if}
\}
{/if}
{swrap 75}{$prop.type} {$class.name}::get{$prop.name|uppercase(1)}() const{/swrap}
\{
{if prop.guardMutex != ""}	Guard propertyGuard({$prop.guardMutex});
{/if}{if prop.impl.get == ""}	return {$prop.name};{else}{$prop.impl.get|swrap(75, "	")}{/if}
\}
{/if}{/if}{/section}{section createFuncImpl}{if func.pureVirtual != "true"}
{swrap 75}{$func.type} {$class.name}::{$func.name}({foreach prm in func.param}{$prm.type} {$prm.name}{first}, {/first}{mid}, {/mid}{/foreach}){if func.const == "true"} const{/if}{/swrap}
\{
{if func.guardMutex != ""}	Guard functionGuard({$func.guardMutex});
{/if}{if func.impl == ""}	// TODO: Implementation.{else}{$func.impl|swrap(75,'	')}{/if}
{if func.return.value != ""}	return {$func.return.value};
{/if}\}
{/if}{/section}/* ==========================================================================
 * {$project.name}
 * Copyright © {$project.copyrightYear} {$project.author}
 * {$project.mail}
 * --------------------------------------------------------------------------
{swrap 75 ' * '}{$class.name|append('.cpp')|rpad(' ', 30)}  {$class.shortDesc} (implementation).{/swrap}{if project.license == "GPL"}{ref insertGPLDisclaimer}{/if}
 * ========================================================================== */
# +++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
# ---- Everything below here needs to be validated for use with ifobject ----
# +++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
\#include "{if class.includeDir != ""}{$class.includeDir}/{/if}{$class.name}.hpp"{$haveLogMessageInclude = 0}{$haveSignalInclude = 0}{foreach inc in include.impl}
\#include {$inc}{if inc == '"stuff/LogMessage.hpp"'}{$haveLogMessageInclude = 1}{/if}{if inc == '"stuff/Signal.hpp"'}{$haveSignalInclude = 1}{/if}{/foreach}{foreach un in undef.impl}
\#undef {$un}{/foreach}{if haveLogMessageInclude == 0}
\#include "stuff/LogMessage.hpp"{/if}{if haveSignalInclude == 0}
\#include "stuff/Signal.hpp"{/if}

{foreach ud in using}using {$ud};
{/foreach}{foreach ns in namespace}
namespace {$ns.name}
\{
{/foreach}{foreach st in struct}{foreach cn in st.constant}{first}
{/first}{single}
{/single}const {$cn.type} {$st.name}::{$cn.name} = {$cn.value};
{/foreach}{/foreach}{if st.bindings.ruby.createMarkFunction == "true"}
void (*const {$st.name}::rubyMark)({$st.name}*) = {$st.name}_rubyMark;
{/if}{if class.createClassInfo == "true"}
{$class.name}ClassInfo::{$class.name}ClassInfo()
\{
	name = "{$class.name}";
	desc = "{$class.shortDesc}";
\}
{/if}{foreach var in variable.private}{if var.spec == "static"}{first}
{/first}{single}
{/single}{$var.type} {$class.name}::{$var.name} = {$var.value};
{/if}{/foreach}{foreach var in variable.protected}{if var.spec == "static"}{first}
{/first}{single}
{/single}{$var.type} {$class.name}::{$var.name} = {$var.value};
{/if}{/foreach}{foreach const in constant.private}{first}
{/first}{single}
{/single}const {$const.type} {$class.name}::{$const.name} = {$const.value};
{/foreach}{foreach const in constant.protected}{first}
{/first}{single}
{/single}const {$const.type} {$class.name}::{$const.name} = {$const.value};
{/foreach}{foreach const in constant.public}{first}
{/first}{single}
{/single}const {$const.type} {$class.name}::{$const.name} = {$const.value};
{/foreach}{foreach sig in signal}{first}
{/first}{single}
{/single}const SignalType {$class.name}::SIGNAL_TYPE_{$sig.id|uppercase} = 
	"{$sig.return.type},{foreach prm in sig.param}{$prm.type}{notlast}, {/notlast}{/foreach}";{$signalInstanceID = 0}{foreach ins in sig.instance}
const std::string {$class.name}::SIGNAL_NAME_{$ins.id|uppercase} = "{$ins.id|lowercase}";{/foreach}
{/foreach}{if class.createClassInfo == "true"}
const {$class.name}ClassInfo {$class.name}::{$class.name|lowercase(1)}ClassInfo;
const ClassInfo* {$class.name}::CLASS_INFO = &{$class.name}::{$class.name|lowercase(1)}ClassInfo;
{/if}
{$class.name}::{$class.name}(){$haveInitializer = 0}{foreach init in constructor.default.initializer}{$haveInitializer = 1}{first}
: {/first}{single}
: {/single}{$init.name}({$init.value}){notlast}, {/notlast}{/foreach}{foreach sig in signal}{foreach ins in sig.instance}{first}{if haveInitializer == 0}
: {$haveInitializer = 1}{else}, {/if}{/first}{single}{if haveInitializer == 0}
: {$haveInitializer = 1}{else}, {/if}{/single}{$ins.name}Wrapper(0){notlast}, {/notlast}{/foreach}{/foreach}
\{
	{if class.createClassInfo == "true"}// NOTE: The following line is required for class information.
	theClasses.push_back(CLASS_INFO);{/if}{if constructor.default.impl == ""}
	// TODO: Nothing ATM. ;-){else}
{$constructor.default.impl|swrap(75,'	')}{/if}
\}
{foreach con in constructor.public}
{swrap 75}{$class.name}::{$class.name}({foreach prm in con.param}{$prm.type} {$prm.name}{first}, {/first}{mid}, {/mid}{/foreach}){foreach init in con.initializer}{first}
: {/first}{single}
: {/single}{$init.name}({$init.value}){notlast}, {/notlast}{/foreach}{/swrap}
\{
	{if class.createClassInfo == "true"}// NOTE: The following line is required for class information.
	theClasses.push_back(CLASS_INFO);{/if}{if con.impl == ""}
	// TODO: Nothing ATM. ;-){else}
{$con.impl|swrap(75,'	')}{/if}
\}
{/foreach}
{$class.name}::~{$class.name}()
\{
{foreach prop in property.protected}{if ( prop.style == "vector" ) || ( prop.style == "map" )}	clear{$prop.element.name|uppercase(1)}s();
	{else}{if prop.managed == "true"}	if ({$prop.name} != 0)
		{$prop.name}->unref();
	{$prop.name} = 0;
	{/if}{/if}{/foreach}{if destructor.impl == ""}	// TODO: Nothing ATM. ;-){else}{$destructor.impl|swrap(75,'	')}{/if}
\}
{foreach func in function.private}{ref createFuncImpl}{/foreach}{foreach func in function.protected}{ref createFuncImpl}{/foreach}{foreach func in function.public}{ref createFuncImpl}{/foreach}{foreach prop in property.private}{ref createPropertyAccessorImpl}{/foreach}{foreach prop in property.protected}{ref createPropertyAccessorImpl}{/foreach}{foreach sig in signal}{foreach ins in sig.instance}
{$sig.name}& {$class.name}::get{$ins.name|uppercase(1)}()
\{
	return {$ins.name};
\}

Ionflux::Stuff::Signal* {$class.name}::get{$ins.name|uppercase(1)}Wrapper()
\{
	if ({$ins.name}Wrapper == 0)
	\{
		{$ins.name}Wrapper = new Ionflux::Stuff::Signal(
			&{$ins.name}, SIGNAL_TYPE_{$sig.id|uppercase}, 
			SIGNAL_NAME_{$ins.id|uppercase});
		assert({$ins.name}Wrapper != 0, 
			LogMessage("Could not allocate signal wrapper.", 
				LogMessage::VL_ASSERTION, this, 
				"get{$ins.name|uppercase(1)}Wrapper"));
		addLocalRef({$ins.name}Wrapper);
	\}
	return {$ins.name}Wrapper;
\}
{/foreach}{/foreach}{if class.bindings.ruby.createMarkFunction == "true"}
void {$class.name}::rubyMark() const
\{{section markVar}{if var.type == "VALUE"}
	rb_gc_mark({$var.name});{else}{if var.bindings.ruby.mark == "true"}
	if ({$var.name} != 0){if var.bindings.ruby.markMethod == "struct"}
		{$var.name}->rubyMark({$var.name});{else}
		{$var.name}->rubyMark();{/if}{/if}{/if}{/section}{section markProp}{if prop.type == "VALUE"}
	rb_gc_mark({$prop.name});{else}{if prop.bindings.ruby.mark == "true"}
	if ({$prop.name} != 0){if prop.bindings.ruby.markMethod == "struct"}
		{$prop.name}->rubyMark({$prop.name});{else}
		{$prop.name}->rubyMark();{/if}{/if}{/if}{/section}{foreach var in variable.private}{ref markVar}{/foreach}{foreach var in variable.protected}{ref markVar}{/foreach}{foreach var in variable.public}{ref markVar}{/foreach}{foreach prop in property.private}{ref markProp}{/foreach}{foreach prop in property.protected}{ref markProp}{/foreach}{foreach sig in signal}{foreach ins in sig.instance}
	if ({$ins.name}Wrapper != 0)
		{$ins.name}Wrapper->rubyMark();{/foreach}{/foreach}
\}
{/if}{foreach st in struct}{if st.bindings.ruby.createMarkFunction == "true"}
void {$st.name}_rubyMark({$st.name}* targetInstance)
\{
	if (targetInstance == 0)\
		return;{foreach fi in st.field}{if fi.type == "VALUE"}
	rb_gc_mark(targetInstance->{$fi.name});{else}{if fi.bindings.ruby.mark == "true"}
	if (targetInstance->{$fi.name} != 0){if fi.bindings.ruby.markMethod == "struct"}
		targetInstance->{$fi.name}->rubyMark(targetInstance->{$fi.name});{else}
		targetInstance->{$fi.name}->rubyMark();{/if}{/if}{/if}{/foreach}
\}
{/if}{/foreach}{foreach func in function.global}
{swrap 75}{$func.type} {$func.name}({foreach prm in func.param}{$prm.type} {$prm.name}{first}, {/first}{mid}, {/mid}{/foreach}){if func.const == "true"} const{/if}{/swrap}
\{
{if func.impl == ""}	// TODO: Implementation.{else}{$func.impl|swrap(75,'	')}{/if}
{if func.return.value != ""}	return {$func.return.value};
{/if}\}
{/foreach}{foreach ns in namespace}
\}
{/foreach}{if class.loadableModule.enabled == "true"}
extern "C" \{
	Ionflux::Stuff::Object* create{$class.name}(
		Ionflux::Stuff::ModuleLoader* loader = 0)
	\{
		{if class.loadableModule.createImpl != ""}{$class.loadableModule.createImpl}{else}return new {foreach ns in namespace}{$ns.name}::{/foreach}{$class.name};{/if}
	\}
	
	void destroy{$class.name}(Ionflux::Stuff::Object* target,
		Ionflux::Stuff::ModuleLoader* loader = 0)
	\{
		{if class.loadableModule.destroyImpl != ""}{$class.loadableModule.destroyImpl}{else}{foreach ns in namespace}{$ns.name}::{/foreach}{$class.name}* theTarget =
			dynamic_cast<{foreach ns in namespace}{$ns.name}::{/foreach}{$class.name}*>(target);
		if (theTarget != 0)
			delete theTarget;{/if}
	\}
	
	Ionflux::Stuff::ModuleAccess moduleAccess{$class.name} = \{
		0, "",
		create{$class.name},
		destroy{$class.name}
	\};
\}
{/if}
/** \\file {$class.name}.cpp
 * \\brief {$class.shortDesc} implementation.
 */
