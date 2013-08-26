{section persistentDatabaseAccessorImpl}

void {$class.name}::setDatabase({$project.persistence.namespace}::{$project.persistence.database}* newDatabase)
\{
    if (database == newDatabase)
        return;
	database = newDatabase;
	initPersistentBackend();
\}

{$project.persistence.namespace}::{$project.persistence.database}* {$class.name}::getDatabase() const
\{
	return database;
\}{/section}{section createPersistenceFuncsImpl}{if haveBasePersistent == 0}

void {$class.name}::update()
\{
	if (persistent != 0)
		persistent->update();
\}

void {$class.name}::remove()
\{
	if (persistent != 0)
		persistent->del();
\}

int {$class.name}::getPersistentID()
\{
	if (persistent != 0)
		return persistent->id;
    return -1;
\}

bool {$class.name}::setFromID(int objectID)
\{
    setPersistentBackendState({$project.persistence.namespace}::{$class.persistence.backend}::Id == objectID);
	return true;
\}{/if}

{swrap 75}{$project.persistence.namespace}::{$class.persistence.backend}* {$class.name}::getPersistent() const{/swrap}
\{{if haveBasePersistent == 0}
    return persistent;{else}
    {$project.persistence.namespace}::{$class.persistence.backend}* result = dynamic_cast<{$project.persistence.namespace}::{$class.persistence.backend}*>(persistent);
    if (result == 0)
        throw {if class.persistence.errorClass != ""}{$class.persistence.errorClass}{else}PersistenceError{/if}("Backend object has wrong type!");
    return result;{/if}
\}

unsigned int {foreach ns in namespace}{$ns.name}::{/foreach}{$class.name}::getPersistentObjects(
    {$project.persistence.namespace}::{$project.persistence.database}* database, 
    std::vector<{foreach ns in namespace}{$ns.name}::{/foreach}{$class.name}*>& target, 
    const litesql::Expr& expr)
\{
	if (database == 0)
	    throw {if class.persistence.errorClass != ""}{$class.persistence.errorClass}{else}PersistenceError{/if}("Database not set!");
    litesql::DataSource<{$project.persistence.namespace}::{$class.persistence.backend}> result = litesql::select<{$project.persistence.namespace}::{$class.persistence.backend}>(
        *database, expr);
    if (result.count() == 0)
        return 0;
    std::vector<{$project.persistence.namespace}::{$class.persistence.backend}> rv0 = result.all();
    for (std::vector<{$project.persistence.namespace}::{$class.persistence.backend}>::iterator i = 
        rv0.begin(); i != rv0.end(); i++)
    \{
        {$project.persistence.namespace}::{$class.persistence.backend}* pb0 = 
            new {$project.persistence.namespace}::{$class.persistence.backend}(*i);
        if (pb0 == 0)
	        throw {if class.persistence.errorClass != ""}{$class.persistence.errorClass}{else}PersistenceError{/if}("[{$class.name}::getPersistentObjects] "
	            "Could not allocate property backend object!");
        {$class.name}* p0 = new {$class.name}(database, pb0);
	    if (p0 == 0)
	    \{
	        delete pb0;
	        throw {if class.persistence.errorClass != ""}{$class.persistence.errorClass}{else}PersistenceError{/if}("[{$class.name}::getPersistentObjects] "
	            "Could not allocate object!");
	    \}
        target.push_back(p0);
    \}
    return result.count();
\}{foreach prop in property.protected}{if prop.persistentInit == "true"}{ref createPersistentInitFuncImpl}{/if}{/foreach}{foreach prop in property.private}{if prop.persistentInit == "true"}{ref createPersistentInitFuncImpl}{/if}{/foreach}{/section}
