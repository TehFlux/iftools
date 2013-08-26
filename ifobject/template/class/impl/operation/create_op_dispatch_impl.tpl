{section createOpDispatchImpl}

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
\}{/section}
