{section declareUpcastFuncs}
		
		/** Upcast.
		 *
		 * Cast an IFObject to the most specific type.
		 *
		 * \\param other Other object.
		 *
		 * \\return The more specific object, or 0 if the cast failed.
		 */
{swrap 75 "		"}static {foreach ns in namespace}{$ns.name}::{/foreach}{$class.name}* upcast(Ionflux::ObjectBase::IFObject* other);{/swrap}{/section}
