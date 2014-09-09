{section insertForwards}{foreach fwd in forward}{first}
{/first}{single}
{/single}
{$fwd};{/foreach}{foreach ev in event}{first}{if haveForwards == 0}
{/if}
// events used by {$class.name}{/first}{single}{if haveForwards == 0}
{/if}
// events used by {$class.name}{/single}
class IF{$ev.id|uppercase(1)}Event;{/foreach}{/section}{section insertIFObjectForwards}{if ( haveSignals == 1 ) || ( enableSerialize == 1 )}

// forward declarations for types from the Ionflux Object Base System
namespace Ionflux
\{

namespace ObjectBase
\{
{if haveSignals == 1}
class IFSignal;{/if}{if enableSerialize == 1}
class IFIOContext;{/if}

\}

\}{/if}{/section}
