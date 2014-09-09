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
		 * \\param addMagicWord add magic word
		 *
		 * \\return \\c true on success, \\c false otherwise.
		 *
		 * \\sa deserialize()
		 */
		virtual bool serialize(std::ostream& target, bool addMagicWord = true) const;
		
		/** Deserialize.
		 *
		 * Deserialize the object from a stream.
		 *
		 * \\param source source stream
		 * \\param offset stream position from where to start deserialization
		 * \\param checkMagicWord add magic word
		 *
		 * \\return offset of remaining data
		 *
		 * \\sa serialize()
		 */
		virtual Ionflux::ObjectBase::DataSize deserialize(std::istream& source, Ionflux::ObjectBase::DataSize offset = Ionflux::ObjectBase::DATA_SIZE_INVALID, bool checkMagicWord = true);
		
		/** Serialize.
		 *
		 * Serialize the object.
		 *
		 * \\param ioCtx I/O context
		 * \\param addMagicWord add magic word
		 *
		 * \\return \\c true on success, \\c false otherwise.
		 *
		 * \\sa deserialize()
		 */
		virtual bool serialize(Ionflux::ObjectBase::IFIOContext& ioCtx, bool addMagicWord = true) const;
		
		/** Deserialize.
		 *
		 * Deserialize the object from a stream.
		 *
		 * \\param ioCtx I/O context
		 * \\param offset stream position from where to start deserialization
		 * \\param checkMagicWord add magic word
		 *
		 * \\return offset of remaining data
		 *
		 * \\sa serialize()
		 */
		virtual Ionflux::ObjectBase::DataSize deserialize(Ionflux::ObjectBase::IFIOContext& ioCtx, Ionflux::ObjectBase::DataSize offset = Ionflux::ObjectBase::DATA_SIZE_INVALID, bool checkMagicWord = true);
		
		/** Get magic syllable (object).
		 *
		 * Get the magic syllable for the object.
		 *
		 * \\return magic syllable
		 */
		virtual Ionflux::ObjectBase::MagicSyllable getMagicSyllable() const;
		
		/** Get magic syllable (base).
		 *
		 * Get the magic syllable for the namespace.
		 *
		 * \\return magic syllable
		 */
		virtual Ionflux::ObjectBase::MagicSyllable getMagicSyllableBase() const;{/section}
