{section createEventHelperFunctionImpl}

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
\}{/section}
