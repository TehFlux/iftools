{section declareSerializeFuncs}
		
		/** Serialize.
		 *
		 * Serialize the object. This creates a string which contains data 
		 * from which the internal state of the object (as supported 
		 * by serialization) can be restored using deserialize().
		 *
		 * \\param target where to store the result
		 *
		 * \\return \\c true on success, \\c false otherwise.
		 *
		 * \\sa deserialize()
		 */
		virtual bool serialize(std::string& target) const;
		
		/** Deserialize.
		 *
		 * Initialize the object from a serialized representation of its 
		 * internal state. The serialized representation can be obtained 
		 * using serialize().
		 *
		 * \\param source serialized data buffer
		 * \\param offset position where to start deserialization
		 *
		 * \\return offset of remaining data, or -1 if an error occured.
		 *
		 * \\sa serialize()
		 */
		virtual int deserialize(const std::string& source, int offset = 0);{/section}
