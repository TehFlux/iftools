{section createClassNameFuncsImpl}

{swrap 75}std::string {$class.name}::getClassName() const{/swrap}
\{{if enableGuards == 1}
    IFGuard functionGuard(guardMutex);{/if}
    return "{$class.name}";
\}{/section}
