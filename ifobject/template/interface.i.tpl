# ==========================================================================
# Ionflux Object Base System
# Copyright © 2006-2008 Joern P. Meier
# mail@ionflux.org
# --------------------------------------------------------------------------
# interface.i.tpl              SWIG interface template
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
{section checkFeatures}{$haveForwards = 0}{foreach fw in forward}{if fw != ""}{$haveForwards = 1}{/if}{/foreach}{$haveTypedefs = 0}{foreach td in typedef}{if td != ""}{$haveTypedefs = 1}{/if}{/foreach}{$haveEvents = 0}{foreach ev in event}{if ev.id != ""}{$haveEvents = 1}{/if}{/foreach}{$haveSignals = 0}{foreach si in signal}{if si.id != ""}{$haveSignals = 1}{/if}{/foreach}{$haveBaseIFObject = 0}{foreach bc in class.base.ifobject}{if bc.name != ""}{$haveBaseIFObject = 1}{/if}{/foreach}{$haveBaseOther = 0}{foreach bc in class.base.other}{if bc.name != ""}{$haveBaseOther = 1}{/if}{/foreach}{$enableClassInfo = 0}{if ( haveBaseIFObject == 1 ) || ( class.name == "IFObject" )}{$enableClassInfo = 1}{/if}{$enableMutex = 0}{$enableGuards = 0}{$enableAutoGuards = 0}{$enableLogMessage = 0}{$enableSignal = haveSignals}{$enableSerialize = 0}{foreach fe in class.features}{if fe == "mutex"}{$enableMutex = 1}{/if}{if fe == "guards"}{$enableMutex = 1}{$enableGuards = 1}{/if}{if fe == "autoguards"}{$enableMutex = 1}{$enableGuards = 1}{$enableAutoGuards = 1}{/if}{if fe == "logmessage"}{$enableLogMessage = 1}{/if}{if fe == "signal"}{$enableSignal = 1}{/if}{if fe == "serialize"}{$enableSerialize = 1}{/if}{if fe == "classinfo"}{$enableClassInfo = 1}{/if}{/foreach}{$haveOps = 0}{foreach op in operation}{if op.name != ""}{$haveOps = 1}{/if}{/foreach}{/section}{ref checkFeatures}{section insertGPLDisclaimer}
 * =========================================================================

{swrap 75 " * "}This file is part of {$project.name}.

{$project.name} is free software; you can redistribute it and/or modify it under the terms of the GNU General Public License as published by the Free Software Foundation; either version 2 of the License, or (at your option) any later version.

{$project.name} is distributed in the hope that it will be useful, but WITHOUT ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU General Public License for more details.

You should have received a copy of the GNU General Public License along with {$project.name}; if not, write to the Free Software Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA 02111-1307 USA{/swrap}
 * {/section}{section insertIncludes}
%\{
\#include "{if project.includePrefix != ""}{$project.includePrefix}/{/if}{if class.includePrefix != ""}{$class.includePrefix}/{/if}{$class.name}.hpp"
%\}{/section}{section insertForwards}{foreach fwd in forward}{first}
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
 
struct {$st.name}
\{{foreach fi in st.field}
    {$fi.type} {$fi.name};{/foreach}{foreach cn in st.constant}
    static const {$cn.type} {$cn.name};{/foreach}{if st.refCount.enabled == "true"}
    Ionflux::ObjectBase::IFObjectRefInfo* refInfo;{/if}
\};{/foreach}{/section}{section createEventHelperFunctionDecl}        
        IF{$ev.id|uppercase(1)}Event* create{$ev.id|uppercase(1)}Event();{/section}{section createPropertyAccessorDecl}{if prop.style == "vector"}        
{swrap 75 "        "}virtual unsigned int getNum{$prop.element.name|uppercase(1)}s() const;{/swrap}        
{swrap 75 "        "}virtual {$prop.element.type} get{$prop.element.name|uppercase(1)}(unsigned int elementIndex = 0) const;{/swrap}{if prop.readOnly != "true"}        
{swrap 75 "        "}virtual std::vector<{$prop.element.type}>& get{$prop.name|uppercase(1)}();{/swrap}        
{swrap 75 "        "}virtual void add{$prop.element.name|uppercase(1)}({if prop.element.addType == ""}{$prop.element.type}{else}{$prop.element.addType}{/if} addElement);{/swrap}        
{swrap 75 "        "}virtual void remove{$prop.element.name|uppercase(1)}({if prop.element.removeType == ""}{$prop.element.type}{else}{$prop.element.removeType}{/if} removeElement);{/swrap}        
{swrap 75 "        "}virtual void clear{$prop.element.name|uppercase(1)}s();{/swrap}{/if}{else}{if prop.style == "map"}        
{swrap 75 "        "}virtual unsigned int getNum{$prop.element.name|uppercase(1)}s() const;{/swrap}        
{swrap 75 "        "}virtual {$prop.element.type} get{$prop.element.name|uppercase(1)}({if prop.key.accessType != ""}{$prop.key.accessType}{else}{$prop.key.type}{/if} elementKey) const;{/swrap}
{if prop.readOnly != "true"}        
{swrap 75 "        "}virtual std::map<{$prop.key.type}, {$prop.element.type}>& get{$prop.name|uppercase(1)}();{/swrap}        
{swrap 75 "        "}virtual void add{$prop.element.name|uppercase(1)}({if prop.key.accessType != ""}{$prop.key.accessType}{else}{$prop.key.type}{/if} elementKey, {if prop.element.addType == ""}{$prop.element.type}{else}{$prop.element.addType}{/if} addElement);{/swrap}        
{swrap 75 "        "}virtual void remove{$prop.element.name|uppercase(1)}({if prop.key.accessType != ""}{$prop.key.accessType}{else}{$prop.key.type}{/if} elementKey);{/swrap}        
{swrap 75 "        "}virtual void clear{$prop.element.name|uppercase(1)}s();{/swrap}{/if}{else}{if prop.readOnly != "true"}        
{swrap 75 "        "}virtual void set{$prop.name|uppercase(1)}({$prop.setFromType} new{$prop.name|uppercase(1)});{/swrap}{/if}        
{swrap 75 "        "}virtual {$prop.type} get{$prop.name|uppercase(1)}() const;{/swrap}{/if}{/if}{/section}/* ==========================================================================
 * {$project.name}
 * Copyright © {$project.copyrightYear} {$project.author}
 * {$project.mail}
 * --------------------------------------------------------------------------
{swrap 75 ' * '}{$class.name|append('.i')|rpad(' ', 30)}  {$class.shortDesc} (interface).{/swrap}{if project.license == "GPL"}{ref insertGPLDisclaimer}{/if}
 * ========================================================================== */{ref insertIncludes}{foreach un in undef.header}
\#undef {$un}{/foreach}{ref insertIFObjectForwards}{foreach ns in namespace}

namespace {$ns.name}
\{{/foreach}{ref insertForwards}{ref insertTypedefs}{if class.group.shortDesc != ""}

{/if}{ref createStructDecl}{foreach sig in signal}

struct IF{$sig.id|uppercase(1)}SignalConnections
\{{foreach ins in sig.instance}
    sigc::connection signal{$ins.name|uppercase(1)}Connection;{/foreach}
\};{/foreach}{if enableClassInfo == 1}

class {$class.name}ClassInfo
: public Ionflux::ObjectBase::IFClassInfo
\{
    public:
        {$class.name}ClassInfo();
        virtual ~{$class.name}ClassInfo();
\};{/if}

class {$class.name}{if ( haveBaseIFObject == 1 ) || ( haveBaseOther == 1 )}
: {swrap 75}{foreach bc in class.base.ifobject}{if bc.inheritanceType == ""}public{else}{$bc.inheritanceType}{/if} Ionflux::ObjectBase::{$bc.name}{notlast}, {/notlast}{/foreach}{foreach bc in class.base.other}{first}{if haveBaseIFObject == 1}, {/if}{/first}{single}{if haveBaseIFObject == 1}, {/if}{/single}{if bc.inheritanceType == ""}public{else}{$bc.inheritanceType}{/if} {$bc.name}{notlast}, {/notlast}{/foreach}{/swrap}{/if}
\{
    public:{foreach var in variable.public}{if ( var.disableBindings != "true" )}
        {if var.spec != ""}{$var.spec} {/if}{$var.type} {$var.name}{if var.arraySize != ""}[{$var.arraySize}]{/if};{/if}{/foreach}{foreach const in constant.public}
		static const {$const.type} {$const.name};{/foreach}{foreach sig in signal}
        static const Ionflux::ObjectBase::IFSignalType SIGNAL_TYPE_{$sig.id|uppercase};{foreach ins in sig.instance}
        static const std::string SIGNAL_NAME_{$ins.id|uppercase};{/foreach}{/foreach}
        
        {$class.name}();{foreach con in constructor.public}
{swrap 75 "        "}{$class.name}({foreach prm in con.param}{$prm.type} {$prm.name}{if prm.default != ""} = {$prm.default}{/if}{first}, {/first}{mid}, {/mid}{/foreach});{/swrap}
        {/foreach}virtual ~{$class.name}();{foreach ev in event}{ref createEventHelperFunctionDecl}{/foreach}{foreach func in function.public}{if ( func.name != "operator=" ) && ( func.disableBindings != "true" )}
{swrap 75 "        "}{$func.spec} {$func.type} {$func.name}({foreach prm in func.param}{$prm.type} {$prm.name}{if prm.default != ""} = {$prm.default}{/if}{first}, {/first}{mid}, {/mid}{/foreach}){if func.const == "true"} const{/if}{if func.pureVirtual == "true"} = 0{/if};{/swrap}{/if}{/foreach}{if enableSerialize == 1}
        virtual bool serialize(std::string& target) const;
        virtual int deserialize(const std::string& source, int offset = 0);{/if}{foreach prop in property.private}{ref createPropertyAccessorDecl}{/foreach}{foreach prop in property.protected}{ref createPropertyAccessorDecl}{/foreach}{foreach sig in signal}{foreach ins in sig.instance}
        virtual IF{$sig.id|uppercase(1)}Signal& getSignal{$ins.name|uppercase(1)}();
        virtual Ionflux::ObjectBase::IFSignal* getSignal{$ins.name|uppercase(1)}Wrapper();{/foreach}{/foreach}
\};{foreach func in function.global}

{swrap 75}{$func.type} {$func.name}({foreach prm in func.param}{$prm.type} {$prm.name}{if prm.default != ""} = {$prm.default}{/if}{first}, {/first}{mid}, {/mid}{/foreach}){if func.const == "true"} const{/if}{if func.pureVirtual == "true"} = 0{/if};{/swrap}{/foreach}{foreach ns in namespace}

\}{/foreach}
