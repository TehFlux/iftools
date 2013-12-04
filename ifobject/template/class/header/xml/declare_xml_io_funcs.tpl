{section declareXMLIOFuncs}
        
		/** Get XML element name.
		 *
		 * Get the XML element name for the object.
		 *
		 * \\return XML element name
		 */
{swrap 75 "		"}virtual std::string getXMLElementName() const;{/swrap}
        
		/** Get XML attribute data.
		 *
		 * Get a string containing the XML attributes of the object.
		 *
		 * \\return XML attribute data
		 */
{swrap 75 "		"}virtual std::string getXMLAttributeData() const;{/swrap}
        
        /** Get XML child data.
		 *
		 * Get the XML child data for the object.
		 *
		 * \\param target Where to store the XML data.
		 * \\param indentLevel Indentation level.
		 */
{swrap 75 "		"}virtual void getXMLChildData(std::string& target, unsigned int indentLevel = 0) const;{/swrap}
        
        /** Load from XML file.
		 *
		 * Initialize the object from an XML file.
		 *
		 * \\param fileName file name
		 */
{swrap 75 "		"}virtual void loadFromXMLFile(const std::string& FileName);{/swrap}
        
        /** Get XML object factory
		 *
		 * Get the XML object factory singleton for the class.
		 *
		 * \\param fileName file name
		 */
{swrap 75 "		"}static Ionflux::ObjectBase::XMLUtils::IFXMLObjectFactory* getXMLObjectFactory();{/swrap}{/section}
