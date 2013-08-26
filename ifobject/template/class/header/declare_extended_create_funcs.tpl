{section declareExtendedCreateFuncs}{foreach con in constructor.public}
        
		/** Create instance.
		 *
		 * Create a new {$class.name} object.{foreach prm in con.param}{first}
		 *{/first}{single}
		 *{/single}
{swrap 75 "		 * "}\\param {$prm.name} {$prm.desc}.{/swrap}{/foreach}
		 * \\param parentObject Parent object.
		 */
{swrap 75 "		"}static {foreach ns in namespace}{$ns.name}::{/foreach}{$class.name}* create({foreach prm in con.param}{$prm.type} {$prm.name}{if prm.default != ""} = {$prm.default}{/if}{first}, {/first}{mid}, {/mid}{/foreach}, Ionflux::ObjectBase::IFObject* parentObject = 0);{/swrap}{/foreach}{/section}
