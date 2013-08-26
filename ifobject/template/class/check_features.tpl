{section checkFeatures}{$haveForwards = 0}{foreach fw in forward}{if fw != ""}{$haveForwards = 1}{/if}{/foreach}{$haveTypedefs = 0}{foreach td in typedef}{if td != ""}{$haveTypedefs = 1}{/if}{/foreach}{$haveEvents = 0}{foreach ev in event}{if ev.id != ""}{$haveEvents = 1}{/if}{/foreach}{$haveSignals = 0}{foreach si in signal}{if si.id != ""}{$haveSignals = 1}{/if}{/foreach}{$haveBaseIFObject = 0}{foreach bc in class.base.ifobject}{if bc.name != ""}{$haveBaseIFObject = 1}{/if}{/foreach}{$haveBaseOther = 0}{foreach bc in class.base.other}{if bc.name != ""}{$haveBaseOther = 1}{/if}{/foreach}{$enableClassInfo = 0}{if ( haveBaseIFObject == 1 ) || ( class.name == "IFObject" )}{$enableClassInfo = 1}{/if}{$abstractClass = 0}{foreach func in function.public}{if func.pureVirtual == "true"}{$abstractClass = 1}{/if}{/foreach}{foreach func in function.protected}{if func.pureVirtual == "true"}{$abstractClass = 1}{/if}{/foreach}{$enableMutex = 0}{$enableGuards = 0}{$enableAutoGuards = 0}{$enableLogMessage = 0}{$enableSignal = haveSignals}{$enableSerialize = 0}{$enablePersistence = 0}{$enableCopy = 0}{$enableUpcast = 0}{$enableCreate = 0}{$enableParam = 0}{$enableQObject = 0}{$enablePropertySet = 0}{$enableClassName = 0}{$enableMemDebug = 0}{$enableExtendedCreate = 0}{foreach fe in class.features}{if fe == "mutex"}{$enableMutex = 1}{/if}{if fe == "guards"}{$enableMutex = 1}{$enableGuards = 1}{/if}{if fe == "autoguards"}{$enableMutex = 1}{$enableGuards = 1}{$enableAutoGuards = 1}{/if}{if fe == "logmessage"}{$enableLogMessage = 1}{/if}{if fe == "signal"}{$enableSignal = 1}{/if}{if fe == "serialize"}{$enableSerialize = 1}{/if}{if fe == "classinfo"}{$enableClassInfo = 1}{/if}{if fe == "persistence"}{$enablePersistence = 1}{/if}{if fe == "copy"}{$enableCopy = 1}{/if}{if fe == "upcast"}{$enableUpcast = 1}{/if}{if fe == "create"}{$enableCreate = 1}{if class.create.extendedCreate == "true"}{$enableExtendedCreate = 1}{/if}{/if}{if fe == "param"}{$enableParam = 1}{/if}{if fe == "qobject"}{$enableQObject = 1}{/if}{if fe == "propertyset"}{$enablePropertySet = 1}{/if}{if fe == "classname"}{$enableClassName = 1}{/if}{if fe == "memdebug"}{$enableMemDebug = 1}{if project.memDebug.autoEnable == "false"}{$class.memDebug.autoEnable = "false"}{/if}{/if}{/foreach}{$haveOps = 0}{foreach op in operation}{if op.name != ""}{$haveOps = 1}{/if}{/foreach}{$haveBasePersistent = 0}{if enablePersistence == 1}{if class.persistence.backendBase != ""}{$haveBasePersistent = 1}{/if}{if class.persistence.backend == ""}{$class.persistence.backend = class.name + "Backend"}{/if}{/if}{/section}
