{section createPersistentInitFuncImpl}

{swrap 75}bool {$class.name}::setFrom{$prop.name|uppercase(1)}({$prop.setFromType} init{$prop.name|uppercase(1)}){/swrap}
\{
    setPersistentBackendState({$project.persistence.namespace}::{$class.persistence.backend}::{$prop.name|uppercase(1)} == init{$prop.name|uppercase(1)});
	return true;
\}{/section}
