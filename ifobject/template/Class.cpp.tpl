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
{$haveBaseIFObject = 0}{foreach bc in class.base.ifobject}{if bc.name != ""}{$haveBaseIFObject = 1}{/if}{/foreach}{$haveBaseOther = 0}{foreach bc in class.base.other}{if bc.name != ""}{$haveBaseOther = 1}{/if}{/foreach}{section insertGPLDisclaimer}
 * =========================================================================
{swrap 75 " * "}This file is part of {$project.name}.

{$project.name} is free software; you can redistribute it and/or modify it under the terms of the GNU General Public License as published by the Free Software Foundation; either version 2 of the License, or (at your option) any later version.

{$project.name} is distributed in the hope that it will be useful, but WITHOUT ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU General Public License for more details.

You should have received a copy of the GNU General Public License along with {$project.name}; if not, write to the Free Software Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA 02111-1307 USA{/swrap}{/section}{section insertIncludes}

\#include "{if class.includeDir != ""}{$class.includeDir}/{/if}{$class.name}.hpp"{foreach ev in event}
\#include "{if class.includeDir != ""}{$class.includeDir}/{/if}IF{$ev.id|uppercase(1)}Event.hpp"{/foreach}{foreach inc in include.impl}
\#include {$inc}{/foreach}{/section}{section createEventHelperFunctionImpl}
		
IF{$ev.id|uppercase(1)}Event* create{$ev.id|uppercase(1)}Event()
\{
	IF{$ev.id|uppercase(1)}Event* event = new IF{$ev.id|uppercase(1)}Event();
	if (event == 0)
		log(LogMessage("Could not allocate event.", 
			LogMessage::VL_ASSERTION, this, "create{$ev.id|uppercase(1)}Event"));
	addLocalRef(event);
	return event;
\}{/section}{section createPropertyAccessorImpl}{if prop.style == "vector"}

{swrap 75}unsigned int {$class.name}::getNum{$prop.element.name|uppercase(1)}s() const{/swrap}
\{{if haveBaseIFObject == 1}
	IFGuard propertyGuard(guardMutex);{/if}
	return {$prop.name}.size();
\}

{swrap 75}{$prop.element.type} {$class.name}::get{$prop.element.name|uppercase(1)}(unsigned int elementIndex) const{/swrap}
\{{if haveBaseIFObject == 1}
	IFGuard propertyGuard(guardMutex);{/if}
	if (elementIndex < {$prop.name}.size())
		return {$prop.name}[elementIndex];
	return {if prop.element.defaultValue != ""}{$prop.element.defaultValue}{else}0{/if};
\}
{if prop.readOnly != "true"}
{swrap 75}std::vector<{$prop.element.type}>& {$class.name}::get{$prop.name|uppercase(1)}(){/swrap}
\{{if haveBaseIFObject == 1}
	IFGuard propertyGuard(guardMutex);{/if}
	return {$prop.name};
\}

{swrap 75}void {$class.name}::add{$prop.element.name|uppercase(1)}({if prop.element.addType == ""}{$prop.element.type}{else}{$prop.element.addType}{/if} addElement){/swrap}
\{{if haveBaseIFObject == 1}
	IFGuard propertyGuard(guardMutex);{/if}
	{if prop.element.managed == "true"}addElement->ref();
	{/if}{$prop.name}.push_back(addElement);
\}

{swrap 75}void {$class.name}::remove{$prop.element.name|uppercase(1)}({if prop.element.removeType == ""}{$prop.element.type}{else}{$prop.element.removeType}{/if} removeElement){/swrap}
\{{if haveBaseIFObject == 1}
	IFGuard propertyGuard(guardMutex);{/if}
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
			current{$prop.element.name|uppercase(1)}->unref();{/if}
	\}
\}

{swrap 75}void {$class.name}::clear{$prop.element.name|uppercase(1)}s(){/swrap}
\{{if haveBaseIFObject == 1}
	IFGuard propertyGuard(guardMutex);{/if}
	{if prop.element.managed == "true"}std::vector<{$prop.element.type}>::iterator i;
	for (i = {$prop.name}.begin(); i != {$prop.name}.end(); i++)
		if (*i != {if prop.element.defaultValue != ""}{$prop.element.defaultValue}{else}0{/if})
			(*i)->unref();
	{/if}{$prop.name}.clear();
\}{/if}{else}{if prop.style == "map"}

{swrap 75}unsigned int {$class.name}::getNum{$prop.element.name|uppercase(1)}s() const{/swrap}
\{{if haveBaseIFObject == 1}
	IFGuard propertyGuard(guardMutex);{/if}
	return {$prop.name}.size();
\}

{swrap 75}{$prop.element.type} {$class.name}::get{$prop.element.name|uppercase(1)}({if prop.key.accessType != ""}{$prop.key.accessType}{else}{$prop.key.type}{/if} elementKey) const{/swrap}
\{{if haveBaseIFObject == 1}
	IFGuard propertyGuard(guardMutex);{/if}
	std::map<{$prop.key.type}, {$prop.element.type}>::const_iterator i = {$prop.name}.find(elementKey);
	if (i != {$prop.name}.end())
		return (*i).second;
	return {if prop.element.defaultValue != ""}{$prop.element.defaultValue}{else}0{/if};
\}
{if prop.readOnly != "true"}
{swrap 75}std::map<{$prop.key.type}, {$prop.element.type}>& {$class.name}::get{$prop.name|uppercase(1)}(){/swrap}
\{{if haveBaseIFObject == 1}
	IFGuard propertyGuard(guardMutex);{/if}
	return {$prop.name};
\}

{swrap 75}void {$class.name}::add{$prop.element.name|uppercase(1)}({if prop.key.accessType != ""}{$prop.key.accessType}{else}{$prop.key.type}{/if} elementKey, {if prop.element.addType == ""}{$prop.element.type}{else}{$prop.element.addType}{/if} addElement){/swrap}
\{{if haveBaseIFObject == 1}
	IFGuard propertyGuard(guardMutex);{/if}
	{$prop.element.type} the{$prop.element.name|uppercase(1)} = get{$prop.element.name|uppercase(1)}(elementKey);
	if (the{$prop.element.name|uppercase(1)} != {if prop.element.defaultValue != ""}{$prop.element.defaultValue}{else}0{/if})
		return;
	{$prop.name}[elementKey] = addElement;{if prop.element.managed == "true"}
	addElement->ref();{/if}
\}

{swrap 75}void {$class.name}::remove{$prop.element.name|uppercase(1)}({if prop.key.accessType != ""}{$prop.key.accessType}{else}{$prop.key.type}{/if} elementKey){/swrap}
\{{if haveBaseIFObject == 1}
	IFGuard propertyGuard(guardMutex);{/if}
	std::map<{$prop.key.type}, {$prop.element.type}>::iterator i = {$prop.name}.find(elementKey);
	if (i != {$prop.name}.end())
	\{
		{if prop.element.managed == "true"}if ((*i).second != {if prop.element.defaultValue != ""}{$prop.element.defaultValue}{else}0{/if})
			(*i).second->unref();
		{/if}{$prop.name}.erase(i);
	\}
\}

{swrap 75}void {$class.name}::clear{$prop.element.name|uppercase(1)}s(){/swrap}
\{{if haveBaseIFObject == 1}
	IFGuard propertyGuard(guardMutex);{/if}
	{if prop.element.managed == "true"}std::map<{$prop.key.type}, {$prop.element.type}>::iterator i;
	for (i = {$prop.name}.begin(); i != {$prop.name}.end(); i++)
		if ((*i).second != {if prop.element.defaultValue != ""}{$prop.element.defaultValue}{else}0{/if})
			(*i).second->unref();
	{/if}{$prop.name}.clear();
\}{/if}{else}{if prop.readOnly != "true"}

{swrap 75}void {$class.name}::set{$prop.name|uppercase(1)}({$prop.setFromType} new{$prop.name|uppercase(1)}){/swrap}
\{{if haveBaseIFObject == 1}
	IFGuard propertyGuard(guardMutex);{/if}
{if prop.impl.set == ""}	{if prop.managed == "true"}if ({$prop.name} == new{$prop.name|uppercase(1)})
		return;
	if ({$prop.name} != 0)
		{$prop.name}->unref();
	{/if}{$prop.name} = new{$prop.name|uppercase(1)};{if prop.managed == "true"}
	if ({$prop.name} != 0)
	\{
		{$prop.name}->ref();{if prop.poolName != ""}
		{$prop.poolName}.addObject({$prop.name});{/if}
	\}{/if}{else}{$prop.impl.set|swrap(75, "	")}{/if}
\}{/if}

{swrap 75}{$prop.type} {$class.name}::get{$prop.name|uppercase(1)}() const{/swrap}
\{{if haveBaseIFObject == 1}
	IFGuard propertyGuard(guardMutex);{/if}
{if prop.impl.get == ""}	return {$prop.name};{else}{$prop.impl.get|swrap(75, "	")}{/if}
\}{/if}{/if}{/section}{section createFuncImpl}{if func.pureVirtual != "true"}
{swrap 75}{$func.type} {$class.name}::{$func.name}({foreach prm in func.param}{$prm.type} {$prm.name}{first}, {/first}{mid}, {/mid}{/foreach}){if func.const == "true"} const{/if}{/swrap}
\{{if haveBaseIFObject == 1}
	IFGuard functionGuard(guardMutex);{/if}
{if func.impl == ""}	// TODO: Implementation.{else}{$func.impl|swrap(75,'	')}{/if}
{if func.return.value != ""}	return {$func.return.value};
{/if}\}
{/if}{/section}/* ==========================================================================
 * {$project.name}
 * Copyright © {$project.copyrightYear} {$project.author}
 * {$project.mail}
 * --------------------------------------------------------------------------
{swrap 75 ' * '}{$class.name|append('.cpp')|rpad(' ', 30)}  {$class.shortDesc} (implementation).{/swrap}{if project.license == "GPL"}{ref insertGPLDisclaimer}{/if}
 * ========================================================================== */{ref insertIncludes}{foreach un in undef.impl}
\#undef {$un}{/foreach}{foreach ud in using}{first}
{/first}{single}
{/single}
using {$ud};{/foreach}{foreach ns in namespace}

namespace {$ns.name}
\{{/foreach}{foreach st in struct}{first}

// structure constants{/first}{single}

// structure constants{/single}{foreach cn in st.constant}
const {$cn.type} {$st.name}::{$cn.name} = {$cn.value};{/foreach}{/foreach}{if haveBaseIFObject == 1}

{$class.name|uppercase(1)}ClassInfo::{$class.name|uppercase(1)}ClassInfo()
\{
	name = "{$class.name}";
	desc = "{$class.shortDesc}";{foreach bc in class.base.ifobject}
	baseClassInfo.push_back({$bc.name}::CLASS_INFO);{/foreach}
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
const SignalType {$class.name}::SIGNAL_TYPE_{$sig.id|uppercase} = 
	"{$sig.return.type},{foreach prm in sig.param}{$prm.type}{notlast}, {/notlast}{/foreach}";{$signalInstanceID = 0}{foreach ins in sig.instance}
const std::string {$class.name}::SIGNAL_NAME_{$ins.id|uppercase} = "{$ins.id|lowercase}";{/foreach}{/foreach}{if haveBaseIFObject == 1}

// run-time type information instance constants
const {$class.name}ClassInfo {$class.name}::{$class.name|lowercase(1)}ClassInfo;
const ClassInfo* {$class.name}::CLASS_INFO = &{$class.name}::{$class.name|lowercase(1)}ClassInfo;{/if}

{$class.name}::{$class.name}(){$haveInitializer = 0}{foreach init in constructor.default.initializer}{$haveInitializer = 1}{first}
: {/first}{single}
: {/single}{$init.name}({$init.value}){notlast}, {/notlast}{/foreach}{foreach sig in signal}{foreach ins in sig.instance}{first}{if haveInitializer == 0}
: {$haveInitializer = 1}{else}, {/if}{/first}{single}{if haveInitializer == 0}
: {$haveInitializer = 1}{else}, {/if}{/single}{$ins.name}Wrapper(0){notlast}, {/notlast}{/foreach}{/foreach}
\{{if haveBaseIFObject == 1}
	// NOTE: The following line is required for run-time type information.
	theClass = CLASS_INFO;{/if}{if constructor.default.impl == ""}
	// TODO: Nothing ATM. ;-){else}
{$constructor.default.impl|swrap(75,'	')}{/if}
\}
{foreach con in constructor.public}
{swrap 75}{$class.name}::{$class.name}({foreach prm in con.param}{$prm.type} {$prm.name}{first}, {/first}{mid}, {/mid}{/foreach}){foreach init in con.initializer}{first}
: {/first}{single}
: {/single}{$init.name}({$init.value}){notlast}, {/notlast}{/foreach}{/swrap}
\{{if haveBaseIFObject == 1}
	// NOTE: The following line is required for run-time type information.
	theClass = CLASS_INFO;{/if}{if con.impl == ""}
	// TODO: Nothing ATM. ;-){else}
{$con.impl|swrap(75,'	')}{/if}
\}
{/foreach}
{$class.name}::~{$class.name}()
\{{foreach prop in property.protected}{if ( prop.style == "vector" ) || ( prop.style == "map" )}
	clear{$prop.element.name|uppercase(1)}s();
	{else}{if prop.managed == "true"}	if ({$prop.name} != 0)
		{$prop.name}->unref();
	{$prop.name} = 0;{/if}{/if}{/foreach}{if destructor.impl == ""}
	// TODO: Nothing ATM. ;-){else}{$destructor.impl|swrap(75,'	')}{/if}
\}{foreach func in function.private}{ref createFuncImpl}{/foreach}{foreach func in function.protected}{ref createFuncImpl}{/foreach}{foreach ev in event}{ref createEventHelperFunctionImpl}{/foreach}{foreach func in function.public}{ref createFuncImpl}{/foreach}{foreach prop in property.private}{ref createPropertyAccessorImpl}{/foreach}{foreach prop in property.protected}{ref createPropertyAccessorImpl}{/foreach}{foreach sig in signal}{foreach ins in sig.instance}
IF{$sig.id|uppercase(1)}Signal& {$class.name}::getSignal{$ins.name|uppercase(1)}()
\{
	return signal{$ins.name|uppercase(1)};
\}

Ionflux::Stuff::IFSignal* {$class.name}::getSignal{$ins.name|uppercase(1)}Wrapper()
\{
	if (signal{$ins.name|uppercase(1)}Wrapper == 0)
	\{
		signal{$ins.name|uppercase(1)}Wrapper = new Ionflux::Stuff::IFSignal(
			&signal{$ins.name|uppercase(1)}, SIGNAL_TYPE_{$sig.id|uppercase}, 
			SIGNAL_NAME_{$ins.id|uppercase});
		if (signal{$ins.name|uppercase(1)}Wrapper == 0) 
			log(IFLogMessage("Could not allocate signal wrapper.", 
				IFLogMessage::VL_ASSERTION, this, 
				"getSignal{$ins.name|uppercase(1)}Wrapper"));
		addLocalRef(signal{$ins.name|uppercase(1)}Wrapper);
	\}
	return signal{$ins.name|uppercase(1)}Wrapper;
\}
{/foreach}{/foreach}{foreach func in function.global}
{swrap 75}{$func.type} {$func.name}({foreach prm in func.param}{$prm.type} {$prm.name}{first}, {/first}{mid}, {/mid}{/foreach}){if func.const == "true"} const{/if}{/swrap}
\{
{if func.impl == ""}	// TODO: Implementation.{else}{$func.impl|swrap(75,'	')}{/if}
{if func.return.value != ""}	return {$func.return.value};
{/if}\}
{/foreach}{foreach ns in namespace}
\}
{/foreach}
/** \\file {$class.name}.cpp
 * \\brief {$class.shortDesc} implementation.
 */
