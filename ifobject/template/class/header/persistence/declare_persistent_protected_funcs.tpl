{section declarePersistentProtectedFuncs}
		
		/** Initialize persistent backend object.
		 *
		 * Initialize the persistent backend object.
		 */
		virtual void initPersistentBackend();
		
		/** Set backend object state.
		 *
		 * Set the state of the persistent backend object to the state of the 
		 * object obtained from the database using the specified litesql 
		 * expression.
		 * 
		 * \\param expr Expression.
		 */
		virtual void setPersistentBackendState(const litesql::Expr& expr);{/section}
