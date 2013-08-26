{section declarePersistentInitFunc}
        
        /** Set from {$prop.name|uppercase(1)}.
		 *
		 * Initialize the object from an existing persistent object with the 
		 * specified {$prop.name|uppercase(1)}.
		 *
		 * \\param init{$prop.name|uppercase(1)} {$prop.name|uppercase(1)}.
		 *
		 * \\return \\c true on success, \\c false otherwise.
		 */
		virtual bool setFrom{$prop.name|uppercase(1)}({$prop.setFromType} init{$prop.name|uppercase(1)});{/section}
