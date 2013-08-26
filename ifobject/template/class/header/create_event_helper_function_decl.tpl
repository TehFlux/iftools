{section createEventHelperFunctionDecl}
		
		/** Create event: {$ev.id}.
		 * 
		 * Create and initialize a '{$ev.id}' event.
		 * 
		 * \\return New event, or 0 if an error occured.
		 */
		IF{$ev.id|uppercase(1)}Event* create{$ev.id|uppercase(1)}Event();{/section}
