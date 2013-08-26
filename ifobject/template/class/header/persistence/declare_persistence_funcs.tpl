{section declarePersistenceFuncs}{if haveBasePersistent == 0}
		
		/** Update.
		 *
		 * Update record.
		 */
		virtual void update();
		
		/** Remove.
		 *
		 * Remove record.
		 */
		virtual void remove();
		
		/** Get persistent ID.
		 *
		 * Get the ID of the persistent backend object.
		 */
		virtual int getPersistentID();
		
		/** Set from ID.
		 *
		 * Initialize the object from an existing persistent object with the 
		 * specified ID.
		 *
		 * \\param objectID Object ID.
		 *
		 * \\return \\c true on success, \\c false otherwise.
		 */
		virtual bool setFromID(int objectID);{/if}
		
		/** Get persistent backend object.
		 *
		 * Get the persistent backend object. This should be used by classes 
		 * that use a derived backend object to ensure the class can work with 
		 * the more specific type of the backend object.
		 */
		virtual {$project.persistence.namespace}::{$class.persistence.backend}* getPersistent() const;
		
        /** Get objects.
		 *
		 * Get objects matching the specified expression from the database. 
		 * The returned objects are not referenced and must be managed by the 
		 * caller.
		 *
		 * \\param database Database.
		 * \\param expr Expression.
		 * \\param target Where to store the objects.
		 *
		 * \\return Number of objects.
		 */
		static unsigned int getPersistentObjects(
		    {$project.persistence.namespace}::{$project.persistence.database}* database, 
		    std::vector<{foreach ns in namespace}{$ns.name}::{/foreach}{$class.name}*>& target, 
		    const litesql::Expr& expr = litesql::Expr());{foreach prop in property.protected}{if prop.persistentInit == "true"}{ref declarePersistentInitFunc}{/if}{/foreach}{foreach prop in property.private}{if prop.persistentInit == "true"}{ref declarePersistentInitFunc}{/if}{/foreach}{/section}
