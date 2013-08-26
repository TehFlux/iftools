{section declarePropertySetFuncs}{if class.propertySet.enablePropertyUpdateHandlers == "true"}{if function.updatePropertyHandler.impl != ""}
        
        /** Update property handler.
         *
         * This is called after a property has been updated.
         *
         * \\param p property
         */
{swrap 75 "		"}virtual void onUpdateProperty(const Ionflux::ObjectBase::IFProperty& p);{/swrap}{/if}{if function.updatePropertiesHandler.impl != ""}
        
        /** Update property handler.
         *
         * This is called after a set of properties has been updated.
         *
         * \\param p property set
         */
{swrap 75 "		"}virtual void onUpdateProperties(const Ionflux::ObjectBase::IFPropertySet& p);{/swrap}{/if}{/if}
        
        /** Update property.
         *
         * Update a property of the object.
         *
         * \\param p property
         * \\param ignoreOwnSet ignore the properties added to this set
         */
{swrap 75 "		"}virtual void updateProperty(const Ionflux::ObjectBase::IFProperty& p, bool ignoreOwnSet = false);{/swrap}
        
        /** Update properties.
         *
         * Update the properties of the object using values from the specified 
         * property set.
         *
         * \\param ps property set
         */
{swrap 75 "		"}virtual void updateProperties(const Ionflux::ObjectBase::IFPropertySet& ps);{/swrap}
        
        /** Get property.
         *
         * Get a property from the object.
         *
         * \\param p property
         * \\param ignoreOwnSet ignore the properties added to this set
         */
{swrap 75 "		"}virtual void getProperty(Ionflux::ObjectBase::IFProperty& p, bool ignoreOwnSet = false);{/swrap}
        
       /** Get properties.
         *
         * Add properties from the object the specified property set.
         *
         * \\param ps property set
         */
{swrap 75 "		"}virtual void getProperties(Ionflux::ObjectBase::IFPropertySet& ps);{/swrap}{/section}
