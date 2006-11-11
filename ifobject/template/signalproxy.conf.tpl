# ==========================================================================
# Ionflux Object Base System
# Copyright © 2006 Joern P. Meier
# mail@ionflux.org
# --------------------------------------------------------------------------
# signalproxy.conf.tpl          Configuration template for signal proxies.
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

# The contents of this file will be processed to fill in values defined by 
# the class configuration and the generator. The result processed to create 
# the signal proxy header and implementation files.

# include files
include= \{
	header = \{
		'"{if project.includePrefix != ""}{$project.includePrefix}/{/if}{if parentClass.includePrefix != ""}{$parentClass.includePrefix}/{/if}{$parentClass.name}.hpp"'
		'"ifobject/IFSignal.hpp"'{foreach inc in proxy.include.header}
		'{$inc}'{/foreach}
	\}
	impl = \{
		'<sstream>'{foreach inc in proxy.include.impl}
		'{$inc}'{/foreach}
	\}
\}

# class definition
class = \{
	name = IF{$id|uppercase(1)}SignalProxy
	title = Proxy for the '{$id}' signal
	shortDesc = Proxy for the '{$id}' signal
	longDesc = Proxy for the '{$id}' signal. This can be used to connect an object to a signal without knowing anything about the implementation of the signal mechanism.
	group.name = ifobject
	base = \{
		# base classes from the IFObject hierarchy
		ifobject[] = \{
           # class name
		   name = IFObject
		   # include file (optional)
		   # include = 
		\}
	\}
	features = \{
		'logmessage'
	\}
\}

# Member variables.
variable.protected[] = \{
	type = sigc::connection
	name = signalConnection
	desc = Signal connection
\}

# Signals.

# Public static constants.

# Protected static constants.

# Protected member functions.

# Public member functions.
function.public[] = \{
	spec = virtual
	type = {$return.type}
	name = onIF{$id|uppercase(1)}Signal
	shortDesc = Handler for the '{$id}' signal
	longDesc = Handle the '{$id}' signal. Override this method in a derived class to implement custom behavior.{$paramNum = 0}{foreach prm in param}
	param[] = \{
		type = {$prm.type}
		name = param{$paramNum}
		desc = signal parameter #{$paramNum}
	\}{$paramNum = paramNum + 1}{/foreach}
	impl = {$proxy.impl}{if return.type != "void"}
	return = \{
		desc = {if proxy.return.desc != ""}{$proxy.return.desc}{else}signal handler result{/if}
		value = {if proxy.return.value != ""}{$proxy.return.value}{else}{if return.type == "bool"}true{else}0{/if}{/if}
	\}{/if}
\}
function.public[] = \{
	spec = virtual
	type = bool
	name = connect
	shortDesc = Connect signal
	longDesc = Connect a signal to the specified action.
	param[] = \{
		type = Ionflux::ObjectBase::IFSignal*
		name = target
		desc = Target signal
	\}
	param[] = \{
		type = int
		name = action
		desc = Action to which the signal should be connected
	\}
	impl = if (target == 0)\\
	return false;\\
IF{$id|uppercase(1)}Signal* targetSignal = 0;\\
if (target->getType() == {$parentClass.name}::SIGNAL_TYPE_{$id|uppercase})\\
\\\{\\
	targetSignal = reinterpret_cast<IF{$id|uppercase(1)}Signal*>(target->getSignal());\\
	signalConnection.disconnect();\\
	signalConnection = targetSignal->connect(sigc::mem_fun(*this, \\
		&IF{$id|uppercase(1)}SignalProxy::onIF{$id|uppercase(1)}Signal));\\
	return true;\\
\\\}
	return = \{
		value = false
		desc = \\c true on success, \\c false otherwise
	\}
\}
function.public[] = \{
	spec = virtual
	type = void
	name = disconnect
	shortDesc = Disconnect signal
	longDesc = Disconnect the signal.
	impl = signalConnection.disconnect();
\}
function.public[] = \{
	spec = static
	type = Ionflux::ObjectBase::IFObject*
	name = create
	shortDesc = Create instance
	longDesc = Create a new instance of the class. If the optional parent object is specified, a local reference for the new object will be added to the parent object.
	param[] = \{
		type = Ionflux::ObjectBase::IFObject*
		name = parentObject
		desc = Parent object
		default = 0
	\}
	impl = IF{$id|uppercase(1)}SignalProxy* newObject = new IF{$id|uppercase(1)}SignalProxy();\\
if (newObject == 0)\\
\\\{\\
	std::cerr << IFLogMessage("Could not allocate object instance.", \\
		IFLogMessage::VL_ERROR, 0, "IFObject::create") << std::endl;\\
	return 0;\\
\\\}\\
if (parentObject != 0)\\
	parentObject->addLocalRef(newObject);
	return = \{
		value = newObject
		desc = Pointer to the new instance, or 0 if an error occurs
	\}
\}
function.public[] = \{
	spec = virtual
	type = Ionflux::ObjectBase::IFObject*
	name = copy
	const = true
	shortDesc = Copy
	longDesc = Create a copy of the object.
	impl = IF{$id|uppercase(1)}SignalProxy* newSignal = new IF{$id|uppercase(1)}SignalProxy();\\
*newSignal = *this;
	return = \{
		value = newSignal
		desc = Copy of the object
	\}
\}
function.public[] = \{
	spec = virtual
	type = IF{$id|uppercase(1)}SignalProxy&
	name = operator=
	shortDesc = Assignment operator
	longDesc = Assignment operator.
	param[] = \{
		type = const IF{$id|uppercase(1)}SignalProxy&
		name = otherSignalProxy
		desc = 
	\}
	impl = 
	return = \{
		value = *this
		desc = The object itself
	\}
\}
function.public[] = \{
	spec = virtual
	type = Ionflux::ObjectBase::IFObject&
	name = operator=
	shortDesc = Assignment operator
	longDesc = Assignment operator.
	param[] = \{
		type = const Ionflux::ObjectBase::IFObject&
		name = otherObject
		desc = IFObject
	\}
	impl = const IF{$id|uppercase(1)}SignalProxy* otherSignalProxy = dynamic_cast<const IF{$id|uppercase(1)}SignalProxy*>(&otherObject);\\
if (otherSignalProxy != 0)\\
	*this = *otherSignalProxy;\\
else\\
	std::cerr << "[IFSignal::operator=] ERROR: "\\
		"Unable to assign object '" << otherObject.getClassName() \\
		<< "'." << std::endl;
	return = \{
		value = *this
		desc = The object itself
	\}
\}
function.public[] = \{
	spec = virtual
	type = std::string
	name = getString
	const = true
	shortDesc = Get string representation
	longDesc = Get a string representation of the object
	impl = std::ostringstream state;\\
state << IFObject::getString();
	return = \{
		value = state.str()
		desc = String representation of the object
	\}
\}
