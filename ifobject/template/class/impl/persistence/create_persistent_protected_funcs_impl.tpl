{section createPersistentProtectedFuncsImpl}
		
{swrap 75}void {$class.name}::initPersistentBackend(){/swrap}
\{
    if (persistent != 0)
    \{
        delete persistent;
        persistent = 0;
    \}
	if (database != 0)
	\{
		persistent = new {$project.persistence.namespace}::{$class.persistence.backend}(*database);
		if (persistent == 0)
		    throw {if class.persistence.errorClass != ""}{$class.persistence.errorClass}{else}PersistenceError{/if}("[{$class.name}::initPersistentBackend] "
	            "Could not allocate backend object!");
    \}{if class.persistence.backendInit != ""}
{swrap 75 "    "}{$class.persistence.backendInit}{/swrap}{/if}
\}

void {$class.name}::setPersistentBackendState(const litesql::Expr& expr)
\{
	if (database == 0)
	    throw {if class.persistence.errorClass != ""}{$class.persistence.errorClass}{else}PersistenceError{/if}("Database not set!");
	if (persistent == 0)
		throw {if class.persistence.errorClass != ""}{$class.persistence.errorClass}{else}PersistenceError{/if}("Backend object not set!");
	try \{
		*getPersistent() = litesql::select<{$project.persistence.namespace}::{$class.persistence.backend}>(*database, expr).one();
	\} catch (litesql::NotFound)
	\{
	    std::ostringstream status;
	    status << "[{$class.name}::setPersistentBackendState] "
	        << "Object not found! (expr = '" << expr.asString() << "')";
		throw {if class.persistence.errorClass != ""}{$class.persistence.errorClass}{else}PersistenceError{/if}(status.str());
    \}
\}{/section}
