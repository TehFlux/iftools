{section declareCopyFuncs}
		
		/** Assignment operator.
		 *
		 * Assign an object.
		 *
		 * \\param other Other object.
		 *
		 * \\return The object itself.
		 */
{swrap 75 "		"}virtual {foreach ns in namespace}{$ns.name}::{/foreach}{$class.name}& operator=(const {foreach ns in namespace}{$ns.name}::{/foreach}{$class.name}& other);{/swrap}{if abstractClass == 0}
		
		/** Copy.
		 *
		 * Create a copy of the object.
		 *
		 * \\return Newly allocated copy of the object.
		 */
{swrap 75 "		"}virtual {foreach ns in namespace}{$ns.name}::{/foreach}{$class.name}* copy() const;{/swrap}{/if}{/section}
