{section declareParamFuncs}{foreach prm in class.param}
		
		/** Set parameter.
		 *
		 * Set the parameter with the specified ID.
		 *
		 * \\param paramID Parameter ID.
		 * \\param paramValue Parameter value.
		 */
{swrap 75 "		"}virtual void set{$prm.name|uppercase(1)}(Ionflux::ObjectBase::IFParamID paramID, {$prm.type} paramValue);{/swrap}
		
		/** Get parameter.
		 *
		 * Get the parameter with the specified ID.
		 *
		 * \\param paramID Parameter ID.
		 */
{swrap 75 "		"}virtual {$prm.type} get{$prm.name|uppercase(1)}(Ionflux::ObjectBase::IFParamID paramID);{/swrap}{/foreach}{/section}
