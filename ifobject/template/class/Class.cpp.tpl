# ==========================================================================
# Ionflux Object Base System
# Copyright © 2006-2009 Joern P. Meier
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
{section checkFeatures}{$haveForwards = 0}{foreach fw in forward}{if fw != ""}{$haveForwards = 1}{/if}{/foreach}{$haveTypedefs = 0}{foreach td in typedef}{if td != ""}{$haveTypedefs = 1}{/if}{/foreach}{$haveEvents = 0}{foreach ev in event}{if ev.id != ""}{$haveEvents = 1}{/if}{/foreach}{$haveSignals = 0}{foreach si in signal}{if si.id != ""}{$haveSignals = 1}{/if}{/foreach}{$haveBaseIFObject = 0}{foreach bc in class.base.ifobject}{if bc.name != ""}{$haveBaseIFObject = 1}{/if}{/foreach}{$haveBaseOther = 0}{foreach bc in class.base.other}{if bc.name != ""}{$haveBaseOther = 1}{/if}{/foreach}{$enableClassInfo = 0}{if ( haveBaseIFObject == 1 ) || ( class.name == "IFObject" )}{$enableClassInfo = 1}{/if}{$abstractClass = 0}{foreach func in function.public}{if func.pureVirtual == "true"}{$abstractClass = 1}{/if}{/foreach}{foreach func in function.protected}{if func.pureVirtual == "true"}{$abstractClass = 1}{/if}{/foreach}{$enableMutex = 0}{$enableGuards = 0}{$enableAutoGuards = 0}{$enableLogMessage = 0}{$enableSignal = haveSignals}{$enableSerialize = 0}{$enablePersistence = 0}{$enableCopy = 0}{$enableUpcast = 0}{$enableCreate = 0}{$enableParam = 0}{foreach fe in class.features}{if fe == "mutex"}{$enableMutex = 1}{/if}{if fe == "guards"}{$enableMutex = 1}{$enableGuards = 1}{/if}{if fe == "autoguards"}{$enableMutex = 1}{$enableGuards = 1}{$enableAutoGuards = 1}{/if}{if fe == "logmessage"}{$enableLogMessage = 1}{/if}{if fe == "signal"}{$enableSignal = 1}{/if}{if fe == "serialize"}{$enableSerialize = 1}{/if}{if fe == "classinfo"}{$enableClassInfo = 1}{/if}{if fe == "persistence"}{$enablePersistence = 1}{/if}{if fe == "copy"}{$enableCopy = 1}{/if}{if fe == "upcast"}{$enableUpcast = 1}{/if}{if fe == "create"}{$enableCreate = 1}{/if}{if fe == "param"}{$enableParam = 1}{/if}{/foreach}{$haveOps = 0}{foreach op in operation}{if op.name != ""}{$haveOps = 1}{/if}{/foreach}{$haveBasePersistent = 0}{if enablePersistence == 1}{if class.persistence.backendBase != ""}{$haveBasePersistent = 1}{/if}{if class.persistence.backend == ""}{$class.persistence.backend = class.name + "Backend"}{/if}{/if}{/section}{ref checkFeatures}{section insertGPLDisclaimer}
 * =========================================================================
{swrap 75 " * "}
This file is part of {$project.name}.

{$project.name} is free software; you can redistribute it and/or modify it under the terms of the GNU General Public License as published by the Free Software Foundation; either version 2 of the License, or (at your option) any later version.

{$project.name} is distributed in the hope that it will be useful, but WITHOUT ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU General Public License for more details.

You should have received a copy of the GNU General Public License along with {$project.name}; if not, write to the Free Software Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA 02111-1307 USA{/swrap}
 * {/section}{section insertIncludes}

\#include "{if class.overrideProjectPrefix != "true"}{if project.includePrefix != ""}{$project.includePrefix}/{/if}{/if}{if class.includePrefix != ""}{$class.includePrefix}/{/if}{$class.name}.hpp"{if enableMutex == 1}
\#include "ifobject/IFMutex.hpp"{/if}{if enableGuards == 1}
\#include "ifobject/IFGuard.hpp"{/if}{if enableLogMessage == 1}
\#include "ifobject/IFLogMessage.hpp"{/if}{if enableSignal == 1}
\#include "ifobject/IFSignal.hpp"{/if}{foreach ev in event}
\#include "{if project.includePrefix != ""}{$project.includePrefix}/{/if}{if class.includePrefix != ""}{$class.includePrefix}/{/if}IF{$ev.id|uppercase(1)}Event.hpp"{/foreach}{foreach inc in include.impl}
\#include {$inc}{/foreach}{/section}{section createEventHelperFunctionImpl}

IF{$ev.id|uppercase(1)}Event* {$class.name}::create{$ev.id|uppercase(1)}Event()
\{{if enableGuards == 1}
	IFGuard functionGuard(guardMutex);{/if}
	IF{$ev.id|uppercase(1)}Event* event = new IF{$ev.id|uppercase(1)}Event();
	if (event == 0)
	\{{if enableLogMessage == 1}
		log(IFLogMessage("Could not allocate event.", 
			VL_ASSERTION, this, "create{$ev.id|uppercase(1)}Event"));{else}
		std::cerr << "[{$class.name}::create{$ev.id|uppercase(1)}Event] ERROR: " 
			"Could not allocate event." << std::endl;{/if}
		return 0;
	\}
	addLocalRef(event);
	return event;
\}{/section}{section createPropertyAccessorImpl}{if prop.style == "vector"}

{swrap 75}unsigned int {$class.name}::getNum{if prop.element.plural == ""}{$prop.element.name|uppercase(1)}s{else}{$prop.element.plural|uppercase(1)}{/if}() const{/swrap}
\{{if enableGuards == 1}
	IFGuard propertyGuard(guardMutex);{/if}{if prop.proxy.target != ""}{if prop.proxy.nullError != ""}
    if ({$prop.proxy.target} == 0)
        throw {$prop.proxy.nullError};{/if}
    return {$prop.proxy.target}->getNum{if prop.element.plural == ""}{$prop.element.name|uppercase(1)}s{else}{$prop.element.plural|uppercase(1)}{/if}();{else}
    return {$prop.name}.size();{/if}
\}

{swrap 75}{$prop.element.type} {$class.name}::get{$prop.element.name|uppercase(1)}(unsigned int elementIndex) const{/swrap}
\{{if enableGuards == 1}
	IFGuard propertyGuard(guardMutex);{/if}{if prop.proxy.target != ""}{if prop.proxy.nullError != ""}
    if ({$prop.proxy.target} == 0)
        throw {$prop.proxy.nullError};{/if}
    return {$prop.proxy.target}->get{$prop.element.name|uppercase(1)}(elementIndex);{else}
    if (elementIndex < {$prop.name}.size())
		return {$prop.name}[elementIndex];
	return {if prop.element.defaultValue != ""}{$prop.element.defaultValue}{else}0{/if};{/if}
\}

{swrap 75}int {$class.name}::find{$prop.element.name|uppercase(1)}({if prop.element.findType == ""}{$prop.element.type}{else}{$prop.element.findType}{/if} needle, unsigned int occurence) const{/swrap}
\{{if enableGuards == 1}
	IFGuard propertyGuard(guardMutex);{/if}{if prop.proxy.target != ""}{if prop.proxy.nullError != ""}
    if ({$prop.proxy.target} == 0)
        throw {$prop.proxy.nullError};{/if}
    return {$prop.proxy.target}->find{$prop.element.name|uppercase(1)}(needle, occurence);{else}
    bool found = false;
	{$prop.element.type} current{$prop.element.name|uppercase(1)} = {if prop.element.defaultValue != ""}{$prop.element.defaultValue}{else}0{/if};
	unsigned int i = 0;
	while (!found 
		&& (i < {$prop.name}.size()))
	\{
		current{$prop.element.name|uppercase(1)} = {$prop.name}[i];
		if (current{$prop.element.name|uppercase(1)} == needle)
        \{
            if (occurence == 1)
			    found = true;
            else
                occurence--;
		\} else
			i++;
	\}
	if (found)
        return i;
	return -1;{/if}
\}{if ( prop.readOnly != "true" ) || ( prop.protectedWrite == "true" )}{if prop.hideImpl != "true"}

{swrap 75}std::vector<{$prop.element.type}>& {$class.name}::get{if prop.element.plural == ""}{$prop.element.name|uppercase(1)}s{else}{$prop.element.plural|uppercase(1)}{/if}(){/swrap}
\{{if enableGuards == 1}
	IFGuard propertyGuard(guardMutex);{/if}{if prop.proxy.target != ""}{if prop.proxy.nullError != ""}
    if ({$prop.proxy.target} == 0)
        throw {$prop.proxy.nullError};{/if}
    return {$prop.proxy.target}->get{if prop.element.plural == ""}{$prop.element.name|uppercase(1)}s{else}{$prop.element.plural|uppercase(1)}{/if}();{else}
    return {$prop.name};{/if}
\}{/if}

{swrap 75}void {$class.name}::add{$prop.element.name|uppercase(1)}({if prop.element.addType == ""}{$prop.element.type}{else}{$prop.element.addType}{/if} addElement){/swrap}
\{{if enableGuards == 1}
	IFGuard propertyGuard(guardMutex);{/if}{if prop.proxy.target != ""}{if prop.proxy.nullError != ""}
    if ({$prop.proxy.target} == 0)
        throw {$prop.proxy.nullError};{/if}
    return {$prop.proxy.target}->add{$prop.element.name|uppercase(1)}(addElement);{else}{if prop.check.maxSize != ""}
	if ({$prop.name}.size() >= {$prop.check.maxSize})
	    throw {$prop.check.sizeError};{/if}
	{if prop.element.managed == "true"}addLocalRef(addElement);
	{/if}{$prop.name}.push_back(addElement);{/if}
\}

{swrap 75}void {$class.name}::remove{$prop.element.name|uppercase(1)}({if prop.element.removeType == ""}{$prop.element.type}{else}{$prop.element.removeType}{/if} removeElement){/swrap}
\{{if enableGuards == 1}
	IFGuard propertyGuard(guardMutex);{/if}{if prop.proxy.target != ""}{if prop.proxy.nullError != ""}
    if ({$prop.proxy.target} == 0)
        throw {$prop.proxy.nullError};{/if}
    return {$prop.proxy.target}->remove{$prop.element.name|uppercase(1)}(removeElement);{else}
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
			removeLocalRef(current{$prop.element.name|uppercase(1)});{/if}
	\}{/if}
\}

{swrap 75}void {$class.name}::remove{$prop.element.name|uppercase(1)}Index(unsigned int removeIndex){/swrap}
\{{if enableGuards == 1}
	IFGuard propertyGuard(guardMutex);{/if}{if prop.proxy.target != ""}{if prop.proxy.nullError != ""}
    if ({$prop.proxy.target} == 0)
        throw {$prop.proxy.nullError};{/if}
    return {$prop.proxy.target}->remove{$prop.element.name|uppercase(1)}Index(removeIndex);{else}
    if (removeIndex > {$prop.name}.size())
        return;{if prop.element.managed == "true"}
	{$prop.element.type} e0 = {$prop.name}[removeIndex];
    {$prop.name}.erase({$prop.name}.begin() + removeIndex);
    if (e0 != {if prop.element.defaultValue != ""}{$prop.element.defaultValue}{else}0{/if})
        removeLocalRef(e0);{else}
    {$prop.name}.erase({$prop.name}.begin() + removeIndex);{/if}{/if}
\}

{swrap 75}void {$class.name}::clear{if prop.element.plural == ""}{$prop.element.name|uppercase(1)}s{else}{$prop.element.plural|uppercase(1)}{/if}(){/swrap}
\{{if enableGuards == 1}
	IFGuard propertyGuard(guardMutex);{/if}{if prop.proxy.target != ""}{if prop.proxy.nullError != ""}
    if ({$prop.proxy.target} == 0)
        throw {$prop.proxy.nullError};{/if}
    return {$prop.proxy.target}->clear{if prop.element.plural == ""}{$prop.element.name|uppercase(1)}s{else}{$prop.element.plural|uppercase(1)}{/if}();{else}
    {if prop.element.managed == "true"}std::vector<{$prop.element.type}>::iterator i;
	for (i = {$prop.name}.begin(); i != {$prop.name}.end(); i++)
		if (*i != {if prop.element.defaultValue != ""}{$prop.element.defaultValue}{else}0{/if})
			removeLocalRef(*i);
	{/if}{$prop.name}.clear();{/if}
\}{/if}{else}{if prop.style == "map"}

{swrap 75}unsigned int {$class.name}::getNum{if prop.element.plural == ""}{$prop.element.name|uppercase(1)}s{else}{$prop.element.plural|uppercase(1)}{/if}() const{/swrap}
\{{if enableGuards == 1}
	IFGuard propertyGuard(guardMutex);{/if}
	return {$prop.name}.size();
\}

{swrap 75}{$prop.element.type} {$class.name}::get{$prop.element.name|uppercase(1)}({if prop.key.accessType != ""}{$prop.key.accessType}{else}{$prop.key.type}{/if} elementKey) const{/swrap}
\{{if enableGuards == 1}
	IFGuard propertyGuard(guardMutex);{/if}
	std::map<{$prop.key.type}, {$prop.element.type}>::const_iterator i = {$prop.name}.find(elementKey);
	if (i != {$prop.name}.end())
		return (*i).second;
	return {if prop.element.defaultValue != ""}{$prop.element.defaultValue}{else}0{/if};
\}{if ( prop.readOnly != "true" ) || ( prop.protectedWrite == "true" )}{if prop.hideImpl != "true"}

{swrap 75}std::map<{$prop.key.type}, {$prop.element.type}>& {$class.name}::get{if prop.element.plural == ""}{$prop.element.name|uppercase(1)}s{else}{$prop.element.plural|uppercase(1)}{/if}(){/swrap}
\{{if enableGuards == 1}
	IFGuard propertyGuard(guardMutex);{/if}
	return {$prop.name};
\}{/if}

{swrap 75}void {$class.name}::add{$prop.element.name|uppercase(1)}({if prop.key.accessType != ""}{$prop.key.accessType}{else}{$prop.key.type}{/if} elementKey, {if prop.element.addType == ""}{$prop.element.type}{else}{$prop.element.addType}{/if} addElement){/swrap}
\{{if enableGuards == 1}
	IFGuard propertyGuard(guardMutex);{/if}{if prop.check.maxSize != ""}
	if ({$prop.name}.size() >= {$prop.check.maxSize})
	    throw {$prop.check.sizeError};{/if}
	{$prop.element.type} the{$prop.element.name|uppercase(1)} = get{$prop.element.name|uppercase(1)}(elementKey);
	if (the{$prop.element.name|uppercase(1)} != {if prop.element.defaultValue != ""}{$prop.element.defaultValue}{else}0{/if})
		return;
	{$prop.name}[elementKey] = addElement;{if prop.element.managed == "true"}
	addLocalRef(addElement);{/if}
\}

{swrap 75}void {$class.name}::remove{$prop.element.name|uppercase(1)}({if prop.key.accessType != ""}{$prop.key.accessType}{else}{$prop.key.type}{/if} elementKey){/swrap}
\{{if enableGuards == 1}
	IFGuard propertyGuard(guardMutex);{/if}
	std::map<{$prop.key.type}, {$prop.element.type}>::iterator i = {$prop.name}.find(elementKey);
	if (i != {$prop.name}.end())
	\{
		{if prop.element.managed == "true"}if ((*i).second != {if prop.element.defaultValue != ""}{$prop.element.defaultValue}{else}0{/if})
			removeLocalRef((*i).second);
		{/if}{$prop.name}.erase(i);
	\}
\}

{swrap 75}void {$class.name}::clear{if prop.element.plural == ""}{$prop.element.name|uppercase(1)}s{else}{$prop.element.plural|uppercase(1)}{/if}(){/swrap}
\{{if enableGuards == 1}
	IFGuard propertyGuard(guardMutex);{/if}
	{if prop.element.managed == "true"}std::map<{$prop.key.type}, {$prop.element.type}>::iterator i;
	for (i = {$prop.name}.begin(); i != {$prop.name}.end(); i++)
		if ((*i).second != {if prop.element.defaultValue != ""}{$prop.element.defaultValue}{else}0{/if})
			removeLocalRef((*i).second);
	{/if}{$prop.name}.clear();
\}{/if}{else}{if ( prop.readOnly != "true" ) || ( prop.protectedWrite == "true" )}

{swrap 75}void {$class.name}::set{$prop.name|uppercase(1)}({$prop.setFromType} new{$prop.name|uppercase(1)}){/swrap}
\{{if enableGuards == 1}
	IFGuard propertyGuard(guardMutex);{/if}{if prop.impl.set == ""}{if prop.managed == "true"}
	if ({$prop.name} == new{$prop.name|uppercase(1)})
		return;
    if (new{$prop.name|uppercase(1)} != 0)
        addLocalRef(new{$prop.name|uppercase(1)});
	if ({$prop.name} != 0)
		removeLocalRef({$prop.name});{/if}{if prop.persistent != "true"}
	{$prop.name} = new{$prop.name|uppercase(1)};{else}
	if (persistent != 0)
		{if haveBasePersistent == 0}persistent{else}getPersistent(){/if}->{$prop.name} = new{$prop.name|uppercase(1)};{/if}{else}
{$prop.impl.set|swrap(75, "	")}{/if}
\}{/if}

{swrap 75}{$prop.type} {$class.name}::get{$prop.name|uppercase(1)}() const{/swrap}
\{{if enableGuards == 1}
	IFGuard propertyGuard(guardMutex);{/if}
{if prop.impl.get == ""}{if prop.persistent != "true"}	return {$prop.name};{else}	if (persistent != 0)
		return {if haveBasePersistent == 0}persistent{else}getPersistent(){/if}->{$prop.name};
	return {$prop.notSetValue};{/if}{else}{$prop.impl.get|swrap(75, "	")}{/if}
\}{/if}{/if}{/section}{section createFuncImpl}{if func.pureVirtual != "true"}

{swrap 75}{$func.type} {$class.name}::{$func.name}({foreach prm in func.param}{$prm.type} {$prm.name}{first}, {/first}{mid}, {/mid}{/foreach}){if func.const == "true"} const{/if}{if func.throw != ""} throw({if func.throw != "<none>"}{$func.throw}{/if}){/if}{/swrap}
\{{if ( enableGuards == 1 ) && ( func.spec != "static" )}
	IFGuard functionGuard(guardMutex);{/if}
{if func.impl == ""}	// TODO: Implementation.{else}{$func.impl|swrap(75,'	')}{/if}
{if func.return.value != ""}	return {$func.return.value};
{/if}\}{/if}{/section}{section createOpProxyImpl}

{swrap 75}bool {$class.name}::op{$op.name|uppercase(1)}({foreach prm in op.param}Ionflux::ObjectBase::IFObject* {$prm.name}, {/foreach}Ionflux::ObjectBase::IFObjectVector* target){if op.const == "true"} const{/if}{/swrap}
\{{if op.impl != ""}
{$op.impl|swrap(75,'	')}{else}
	// TODO: Implementation.
	if (target != 0)
		target.clear();
	return true;{/if}
\}{if ( op.const != "true" ) && ( op.constImpl != "" )}

{swrap 75}bool {$class.name}::op{$op.name|uppercase(1)}({foreach prm in op.param}Ionflux::ObjectBase::IFObject* {$prm.name}, {/foreach}Ionflux::ObjectBase::IFObjectVector* target) const{/swrap}
\{
{$op.constImpl|swrap(75,'	')}
\}{/if}{/section}{section createOpDispatchImpl}

bool {$class.name}::opDispatch(const Ionflux::ObjectBase::IFOpName& opName, 
	const Ionflux::ObjectBase::IFObjectVector* params, 
	Ionflux::ObjectBase::IFObjectVector* target)
\{
	const IFOpInfo* opInfo = theClass->getOpInfo(opName);
	if (opInfo == 0)
	\{{if haveBaseIFObject == 1}
		// Try one of the base classes.{foreach bc in class.base.ifobject}{if bc.inheritOps == "true"}
		if ({$bc.name}::opDispatch(opName, params, target))
			return true;{/if}{/foreach}{/if}{if enableLogMessage == 1}
		ostringstream state;
		state << "Operation not supported: '" << opName << "'.";
		log(IFLogMessage(state.str(), VL_ERROR, 
			this, "opDispatch"));{else}
		std::cerr << "[{$class.name}::opDispatch] ERROR: "
			"Operation not supported: '" << opName << "'.";{/if}
		return false;
	\}
	// Check parameters.
	IFObjectVector checkedParams;
	unsigned int numParams = opInfo->paramInfo.size();
	unsigned int i = 0;
	bool paramsOK = true;
	while ((i < numParams)
		&& paramsOK)
	\{
		const IFOpParamInfo* paramInfo = &(opInfo->paramInfo[i]);
		if ((params != 0) 
			&& (i < params->size()))
		\{
			/* Parameter is defined.
			   Check parameter type. */
			if ((paramInfo->type == 0)
				|| (paramInfo->type == (*params)[i]->getClass())
				|| ((*params)[i]->getClass()->isDerivedFrom(paramInfo->type)))
				checkedParams.push_back((*params)[i]);
			else
			\{{if enableLogMessage == 1}
				ostringstream state;
				state << "Parameter " << i << " for operation '"
					<< opName << "' is of wrong type (type is " 
					<< (*params)[i]->getClassName() << ", expected " 
					<< paramInfo->type->getName() << ").";
				log(IFLogMessage(state.str(), VL_ERROR, 
					this, "opDispatch"));{else}
				std::cerr << "[{$class.name}::opDispatch] ERROR: "
					"Parameter " << i << " for operation '"
					<< opName << "' is of wrong type (type is " 
					<< (*params)[i]->getClassName() << ", expected " 
					<< paramInfo->type->getName() << ").";{/if}
				return false;
			\}
		\} else
		\{
			// Parameter is missing.
			if (!paramInfo->optional)
			\{{if enableLogMessage == 1}
				ostringstream state;
				state << "Required parameter " << i << " for operation '"
					<< opName << "' is missing.";
				log(IFLogMessage(state.str(), VL_ERROR, 
					this, "opDispatch"));{else}
				std::cerr << "[{$class.name}::opDispatch] ERROR: "
					"Required parameter " << i << " for operation '"
					<< opName << "' is missing.";{/if}
				return false;
			\}
			checkedParams.push_back(paramInfo->defaultValue);
		\}
		i++;
	\}
	// Call the appropriate operation proxy.{foreach op in operation}
	if (opName == "{$op.name}")
		return op{$op.name|uppercase(1)}({$paramCount = 0}{foreach prm in op.param}
			checkedParams[{$paramCount}], {$paramCount = paramCount + 1}{/foreach}
			target);{/foreach}{if enableLogMessage == 1}
	ostringstream state;
	state << "Failed to dispatch operation '"
		<< opName << "' for some unknown reason (this should not happen).";
	log(IFLogMessage(state.str(), VL_ERROR, 
		this, "opDispatch"));{else}
	std::cerr << "[{$class.name}::opDispatch] ERROR: "
		"Failed to dispatch operation '" << opName 
		<< "' for some unknown reason (this should not happen).";{/if}
	return false;
\}

bool {$class.name}::opDispatch(const Ionflux::ObjectBase::IFOpName& opName, 
	const Ionflux::ObjectBase::IFObjectVector* params, 
	Ionflux::ObjectBase::IFObjectVector* target) const
\{
	const IFOpInfo* opInfo = theClass->getOpInfo(opName);
	if (opInfo == 0)
	\{{if haveBaseIFObject == 1}
		// Try one of the base classes.{foreach bc in class.base.ifobject}{if bc.inheritOps == "true"}
		if ({$bc.name}::opDispatch(opName, params, target))
			return true;{/if}{/foreach}{/if}{if enableLogMessage == 1}
		ostringstream state;
		state << "Operation not supported: '" << opName << "'.";
		log(IFLogMessage(state.str(), VL_ERROR, 
			this, "opDispatch"));{else}
		std::cerr << "[{$class.name}::opDispatch] ERROR: "
			"Operation not supported: '" << opName << "'.";{/if}
		return false;
	\}
	// Check parameters.
	IFObjectVector checkedParams;
	unsigned int numParams = opInfo->paramInfo.size();
	unsigned int i = 0;
	bool paramsOK = true;
	while ((i < numParams)
		&& paramsOK)
	\{
		const IFOpParamInfo* paramInfo = &(opInfo->paramInfo[i]);
		if ((params != 0) 
			&& (i < params->size()))
		\{
			/* Parameter is defined.
			   Check parameter type. */
			if ((paramInfo->type == 0)
				|| (paramInfo->type == (*params)[i]->getClass())
				|| ((*params)[i]->getClass()->isDerivedFrom(paramInfo->type)))
				checkedParams.push_back((*params)[i]);
			else
			\{{if enableLogMessage == 1}
				ostringstream state;
				state << "Parameter " << i << " for operation '"
					<< opName << "' is of wrong type (type is " 
					<< (*params)[i]->getClassName() << ", expected " 
					<< paramInfo->type->getName() << ").";
				log(IFLogMessage(state.str(), VL_ERROR, 
					this, "opDispatch"));{else}
				std::cerr << "[{$class.name}::opDispatch] ERROR: "
					"Parameter " << i << " for operation '"
					<< opName << "' is of wrong type (type is " 
					<< (*params)[i]->getClassName() << ", expected " 
					<< paramInfo->type->getName() << ").";{/if}
				return false;
			\}
		\} else
		\{
			// Parameter is missing.
			if (!paramInfo->optional)
			\{{if enableLogMessage == 1}
				ostringstream state;
				state << "Required parameter " << i << " for operation '"
					<< opName << "' is missing.";
				log(IFLogMessage(state.str(), VL_ERROR, 
					this, "opDispatch"));{else}
				std::cerr << "[{$class.name}::opDispatch] ERROR: "
					"Required parameter " << i << " for operation '"
					<< opName << "' is missing.";{/if}
				return false;
			\}
			checkedParams.push_back(paramInfo->defaultValue);
		\}
		i++;
	\}
	// Call the appropriate operation proxy.{foreach op in operation}{if ( op.const == "true" ) || ( op.constImpl != "" )}
	if (opName == "{$op.name}")
		return op{$op.name|uppercase(1)}({$paramCount = 0}{foreach prm in op.param}
			checkedParams[{$paramCount}], {$paramCount = paramCount + 1}{/foreach}
			target);{/if}{/foreach}{if enableLogMessage == 1}
	ostringstream state;
	state << "Failed to dispatch operation '"
		<< opName << "' (this is probably because there is no const "
		"implementation available for the operation, but the object on "
		"which the operation has been called is const).";
	log(IFLogMessage(state.str(), VL_ERROR, 
		this, "opDispatch"));{else}
	std::cerr << "[{$class.name}::opDispatch] ERROR: "
		"Failed to dispatch operation '"
		<< opName << "' (this is probably because there is no const "
		"implementation available for the operation, but the object on "
		"which the operation has been called is const).";{/if}
	return false;
\}{/section}{section serializeProp}{if prop.serializeImpl != ""}
{$prop.serializeImpl|swrap(75,'	')}{else}{if ( prop.persistent == "true" ) || ( prop.proxy == "true" )}
    pack(get{$prop.name|uppercase(0)}(), target);{else}
	pack({$prop.name}, target);{/if}{/if}{/section}{section serializeVar}{if var.serializeImpl != ""}
{$var.serializeImpl|swrap(75,'	')}{else}
	pack({$var.name}, target);{/if}{/section}{section deserializeProp}{if prop.deserializeImpl != ""}
{$prop.deserializeImpl|swrap(75,'	')}{else}{if ( prop.persistent == "true" ) || ( prop.proxy == "true" )}
    {$prop.type} t0;
    offset = unpack(source, t0, offset);
    set{$prop.name|uppercase(0)}(t0);{else}
	offset = unpack(source, {$prop.name}, offset);{/if}{/if}
	if (offset < 0)
	\{{if enableLogMessage == 1}
		ostringstream state;
		state << "Could not deserialize property '{$prop.name}'.";
		log(IFLogMessage(state.str(), VL_ERROR, 
			this, "deserialize"));{else}
		std::cerr << "[{$class.name}::deserialize] ERROR: "
			"Could not deserialize property '{$prop.name}'.";{/if}
		return false;
	\}{/section}{section deserializeVar}{if var.deserializeImpl != ""}
{$var.deserializeImpl|swrap(75,'	')}{else}
	offset = unpack(source, {$var.name}, offset);{/if}
	if (offset < 0)
	\{{if enableLogMessage == 1}
		ostringstream state;
		state << "Could not deserialize variable '{$var.name}'.";
		log(IFLogMessage(state.str(), VL_ERROR, 
			this, "deserialize"));{else}
		std::cerr << "[{$class.name}::deserialize] ERROR: "
			"Could not deserialize variable '{$var.name}'.";{/if}
		return false;
	\}{/section}{section defineGlobalFunc}

{swrap 75}{$func.type} {$func.name}({foreach prm in func.param}{$prm.type} {$prm.name}{first}, {/first}{mid}, {/mid}{/foreach}){if func.const == "true"} const{/if}{/swrap}
\{
{if func.impl == ""}	// TODO: Implementation.{else}{$func.impl|swrap(75,'	')}{/if}
{if func.return.value != ""}	return {$func.return.value};
{/if}\}{/section}{section createPersistentInitFuncImpl}

{swrap 75}bool {$class.name}::setFrom{$prop.name|uppercase(1)}({$prop.setFromType} init{$prop.name|uppercase(1)}){/swrap}
\{
    setPersistentBackendState({$project.persistence.namespace}::{$class.persistence.backend}::{$prop.name|uppercase(1)} == init{$prop.name|uppercase(1)});
	return true;
\}{/section}{section persistentDatabaseAccessorImpl}

void {$class.name}::setDatabase({$project.persistence.namespace}::{$project.persistence.database}* newDatabase)
\{
    if (database == newDatabase)
        return;
	database = newDatabase;
	initPersistentBackend();
\}

{$project.persistence.namespace}::{$project.persistence.database}* {$class.name}::getDatabase() const
\{
	return database;
\}{/section}{section createPersistenceFuncsImpl}{if haveBasePersistent == 0}

void {$class.name}::update()
\{
	if (persistent != 0)
		persistent->update();
\}

void {$class.name}::remove()
\{
	if (persistent != 0)
		persistent->del();
\}

int {$class.name}::getPersistentID()
\{
	if (persistent != 0)
		return persistent->id;
    return -1;
\}

bool {$class.name}::setFromID(int objectID)
\{
    setPersistentBackendState({$project.persistence.namespace}::{$class.persistence.backend}::Id == objectID);
	return true;
\}{/if}

{swrap 75}{$project.persistence.namespace}::{$class.persistence.backend}* {$class.name}::getPersistent() const{/swrap}
\{{if haveBasePersistent == 0}
    return persistent;{else}
    {$project.persistence.namespace}::{$class.persistence.backend}* result = dynamic_cast<{$project.persistence.namespace}::{$class.persistence.backend}*>(persistent);
    if (result == 0)
        throw {if class.persistence.errorClass != ""}{$class.persistence.errorClass}{else}PersistenceError{/if}("Backend object has wrong type!");
    return result;{/if}
\}

unsigned int {foreach ns in namespace}{$ns.name}::{/foreach}{$class.name}::getPersistentObjects(
    {$project.persistence.namespace}::{$project.persistence.database}* database, 
    std::vector<{foreach ns in namespace}{$ns.name}::{/foreach}{$class.name}*>& target, 
    const litesql::Expr& expr)
\{
	if (database == 0)
	    throw {if class.persistence.errorClass != ""}{$class.persistence.errorClass}{else}PersistenceError{/if}("Database not set!");
    litesql::DataSource<{$project.persistence.namespace}::{$class.persistence.backend}> result = litesql::select<{$project.persistence.namespace}::{$class.persistence.backend}>(
        *database, expr);
    if (result.count() == 0)
        return 0;
    std::vector<{$project.persistence.namespace}::{$class.persistence.backend}> rv0 = result.all();
    for (std::vector<{$project.persistence.namespace}::{$class.persistence.backend}>::iterator i = 
        rv0.begin(); i != rv0.end(); i++)
    \{
        {$project.persistence.namespace}::{$class.persistence.backend}* pb0 = 
            new {$project.persistence.namespace}::{$class.persistence.backend}(*i);
        if (pb0 == 0)
	        throw {if class.persistence.errorClass != ""}{$class.persistence.errorClass}{else}PersistenceError{/if}("[{$class.name}::getPersistentObjects] "
	            "Could not allocate property backend object!");
        {$class.name}* p0 = new {$class.name}(database, pb0);
	    if (p0 == 0)
	    \{
	        delete pb0;
	        throw {if class.persistence.errorClass != ""}{$class.persistence.errorClass}{else}PersistenceError{/if}("[{$class.name}::getPersistentObjects] "
	            "Could not allocate object!");
	    \}
        target.push_back(p0);
    \}
    return result.count();
\}{foreach prop in property.protected}{if prop.persistentInit == "true"}{ref createPersistentInitFuncImpl}{/if}{/foreach}{foreach prop in property.private}{if prop.persistentInit == "true"}{ref createPersistentInitFuncImpl}{/if}{/foreach}{/section}{section createPersistentProtectedFuncsImpl}
		
{swrap 75}void {$class.name}::initPersistentBackend(){/swrap}
\{
    if (persistent != 0)
    \{
        delete persistent;
        persistent = 0;
    \}
	if (database != 0)
	\{
		persistent = new {$project.persistence.namespace}::{$class.persistence.backend}(*database);
		if (persistent == 0)
		    throw {if class.persistence.errorClass != ""}{$class.persistence.errorClass}{else}PersistenceError{/if}("[{$class.name}::initPersistentBackend] "
	            "Could not allocate backend object!");
    \}{if class.persistence.backendInit != ""}
{swrap 75 "    "}{$class.persistence.backendInit}{/swrap}{/if}
\}

void {$class.name}::setPersistentBackendState(const litesql::Expr& expr)
\{
	if (database == 0)
	    throw {if class.persistence.errorClass != ""}{$class.persistence.errorClass}{else}PersistenceError{/if}("Database not set!");
	if (persistent == 0)
		throw {if class.persistence.errorClass != ""}{$class.persistence.errorClass}{else}PersistenceError{/if}("Backend object not set!");
	try \{
		*getPersistent() = litesql::select<{$project.persistence.namespace}::{$class.persistence.backend}>(*database, expr).one();
	\} catch (litesql::NotFound)
	\{
	    std::ostringstream status;
	    status << "[{$class.name}::setPersistentBackendState] "
	        << "Object not found! (expr = '" << expr.asString() << "')";
		throw {if class.persistence.errorClass != ""}{$class.persistence.errorClass}{else}PersistenceError{/if}(status.str());
    \}
\}{/section}{section createCopyFuncsImpl}

{swrap 75}{foreach ns in namespace}{$ns.name}::{/foreach}{$class.name}& {$class.name}::operator=(const {foreach ns in namespace}{$ns.name}::{/foreach}{$class.name}& other){/swrap}
\{{if enablePersistence == 1}
    database = other.database;
	if (database != 0)
	\{
	    if (persistent != other.persistent)
	    \{
	        if (persistent != 0)
	            delete persistent;
            persistent = new {$project.persistence.namespace}::{$class.persistence.backend}(*(other.getPersistent()));
            if (persistent == 0)
                throw {if class.persistence.errorClass != ""}{$class.persistence.errorClass}{else}PersistenceError{/if}("Could not allocate backend object!");
	    \}
    \} else
    \{
        if (other.persistent != 0)
		    throw {if class.persistence.errorClass != ""}{$class.persistence.errorClass}{else}PersistenceError{/if}("Database not set, "
		        "but backend object not null!");
    \}{/if}{if function.copy.impl != ""}
{swrap 75 "    "}{$function.copy.impl}{/swrap}{else}{foreach prop in property.protected}{if ( prop.copy == "true" ) && ( prop.persistent != "true" )}
set{$prop.name|uppercase(1)}(other.get{$prop.name|uppercase(1)}());{/if}{/foreach}{/if}
	return *this;
\}{if abstractClass == 0}

{swrap 75}{foreach ns in namespace}{$ns.name}::{/foreach}{$class.name}* {$class.name}::copy() const{/swrap}
\{{if enableCreate == 1}
    {$class.name}* new{$class.name|uppercase(1)} = create();{else}
    {$class.name}* new{$class.name|uppercase(1)} = 
        new {$class.name}();{if class.copy.allocationError != ""}
    if (new{$class.name|uppercase(1)} == 0)
        throw {$class.copy.allocationError};{/if}{/if}
    *new{$class.name|uppercase(1)} = *this;
    return new{$class.name|uppercase(1)};
\}{/if}{/section}{section createUpcastFuncsImpl}

{swrap 75}{foreach ns in namespace}{$ns.name}::{/foreach}{$class.name}* {$class.name}::upcast(Ionflux::ObjectBase::IFObject* other){/swrap}
\{
    return dynamic_cast<{$class.name}*>(other);
\}{/section}{section createCreateFuncsImpl}

{swrap 75}{foreach ns in namespace}{$ns.name}::{/foreach}{$class.name}* {$class.name}::create(Ionflux::ObjectBase::IFObject* parentObject){/swrap}
\{
    {$class.name}* newObject = new {$class.name}();
    if (newObject == 0)
    \{{if class.create.allocationError != ""}
        throw {$class.create.allocationError};{else}
        return 0;{/if}
    \}
    if (parentObject != 0)
        parentObject->addLocalRef(newObject);
    return newObject;
\}{if enablePersistence == 1}

{swrap 75}{foreach ns in namespace}{$ns.name}::{/foreach}{$class.name}* {$class.name}::create({$project.persistence.namespace}::{$project.persistence.database}* initDatabase, int objectID){/swrap}
\{
    {$class.name}* newObject = new {$class.name}(initDatabase, objectID);
    if (newObject == 0)
    \{{if class.create.allocationError != ""}
        throw {$class.create.allocationError};{else}
        return 0;{/if}
    \}
    return newObject;
\}

{/if}{/section}{section createParamFuncsImpl}{foreach prm in class.param}

{swrap 75}void {$class.name}::set{$prm.name}(Ionflux::ObjectBase::IFParamID paramID, {$prm.type} paramValue){/swrap}
\{{if prm.impl.set != ""}
    {$prm.impl.set}{/if}{foreach prop in property.protected}{if prop.type == prm.type}
    if (paramID == "{$prop.name}")
    \{
        set{$prop.name|uppercase(1)}(paramValue);
        return;
    \}{/if}{/foreach}{if prm.notExistsError != ""}
    throw {$prm.notExistsError};{/if}
\}

{swrap 75}{$prm.type} {$class.name}::get{$prm.name}(Ionflux::ObjectBase::IFParamID paramID){/swrap}
\{{if prm.impl.get != ""}
    {$prm.impl.get}{/if}{foreach prop in property.protected}{if prop.type == prm.type}
    if (paramID == "{$prop.name}")
        return get{$prop.name|uppercase(1)}();{/if}{/foreach}{if prm.notExistsError != ""}
    throw {$prm.notExistsError};{/if}
\}{/foreach}{/section}/* ==========================================================================
 * {$project.name}
 * Copyright © {$project.copyrightYear} {$project.author}
 * {$project.mail}
 * --------------------------------------------------------------------------
{swrap 75 ' * '}{$class.name|append('.cpp')|rpad(' ', 30)}  {$class.shortDesc} (implementation).{/swrap}{if project.license == "GPL"}{ref insertGPLDisclaimer}{/if}
 * ========================================================================== */{ref insertIncludes}{foreach un in undef.impl}
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
	baseClassInfo.push_back({$bc.name}::CLASS_INFO);{/foreach}{foreach bc in class.base.other}{if bc.hasClassInfo == "true"}
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
const Ionflux::ObjectBase::IFClassInfo* {$class.name}::CLASS_INFO = &{$class.name}::{$class.name|lowercase(1)}ClassInfo;{/if}

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
	setGuardEnabled(true);{/if}{if constructor.default.impl == ""}
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
	setGuardEnabled(true);{/if}
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
	setGuardEnabled(true);{/if}
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
	setGuardEnabled(true);{/if}{if constructor.copy.impl == ""}
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
	setGuardEnabled(true);{/if}{if con.impl == ""}
	// TODO: Nothing ATM. ;-){else}
{$con.impl|swrap(75,'	')}{/if}
\}{/foreach}

{$class.name}::~{$class.name}(){if destructor.throw != ""} throw({if destructor.throw != "<none>"}{$destructor.throw}{/if}){/if}
\{{foreach prop in property.protected}{if ( prop.style == "vector" ) || ( prop.style == "map" )}{if prop.proxy != "true"}
	clear{if prop.element.plural == ""}{$prop.element.name|uppercase(1)}s{else}{$prop.element.plural|uppercase(1)}{/if}();{/if}{/if}{/foreach}{if destructor.impl == ""}{if enablePersistence == 1}
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
		return false;{/foreach}{/if}{foreach bc in class.base.other}{if bc.serialize == "true"}
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
\}{/foreach}{/foreach}{foreach func in function.global}{ref defineGlobalFunc}{/foreach}{foreach ns in namespace}

\}{/foreach}{if insert.impl.postNamespace != ""}

{$insert.impl.postNamespace}{/if}{foreach func in function.externC}{first}

extern "C"
\{{/first}{ref defineGlobalFunc}{last}

\}{/last}{/foreach}

/** \\file {$class.name}.cpp
 * \\brief {$class.shortDesc} implementation.
 */
