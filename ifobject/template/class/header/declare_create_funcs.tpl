{section declareCreateFuncs}
		
		/** Create instance.
		 *
		 * Create a new instance of the class. If the optional parent object 
		 * is specified, a local reference for the new object will be added 
		 * to the parent object.
		 *
		 * \\param parentObject Parent object.
		 *
		 * \\return Pointer to the new instance.
		 */
{swrap 75 "		"}static {foreach ns in namespace}{$ns.name}::{/foreach}{$class.name}* create(Ionflux::ObjectBase::IFObject* parentObject = 0);{/swrap}{if enablePersistence == 1}
		
		/** Create instance.
		 *
		 * Create a new instance of the class.
		 *
		 * \\param initDatabase Database.
		 * \\param objectID Object ID.
		 *
		 * \\return Pointer to the new instance.
		 */
{swrap 75 "		"}static {foreach ns in namespace}{$ns.name}::{/foreach}{$class.name}* create({$project.persistence.namespace}::{$project.persistence.database}* initDatabase, int objectID = -1);{/swrap}{/if}{if enableExtendedCreate == 1}{ref declareExtendedCreateFuncs}{/if}{/section}
