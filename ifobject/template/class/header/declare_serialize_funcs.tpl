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
		 * \\return offset of remaining data, or DATA_SIZE_INVALID if an error occured.
		 *
		 * \\sa serialize()
		 */
		virtual Ionflux::ObjectBase::DataSize deserialize(const std::string& source, Ionflux::ObjectBase::DataSize offset = 0);
		
		/** Serialize.
		 *
		 * Serialize the object to a stream.
		 *
		 * \\param target target stream
		 *
		 * \\return \\c true on success, \\c false otherwise.
		 *
		 * \\sa deserialize()
		 */
		virtual bool serialize(std::ostream& target) const;
		
		/** Deserialize.
		 *
		 * Deserialize the object from a stream.
		 *
		 * \\param source source stream
		 * \\param offset stream position from where to start deserialization
		 *
		 * \\return offset of remaining data
		 *
		 * \\sa serialize()
		 */
		virtual Ionflux::ObjectBase::DataSize deserialize(std::istream& source, Ionflux::ObjectBase::DataSize offset = Ionflux::ObjectBase::DATA_SIZE_INVALID);{/section}
