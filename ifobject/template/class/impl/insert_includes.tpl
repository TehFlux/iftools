{section insertIncludeBlocks}{foreach block in includeBlock}{if ( block.pos == includeBlockPos ) && ( block.file == includeBlockFile )}{if block.type == "list"}{foreach inc in block.list}
\#include {$inc}{/foreach}{else}{if block.type == "verbatim"}
{$block.value}{/if}{/if}{/if}{/foreach}{/section}{section insertIncludes}
{$includeBlockPos = "pre"}{$includeBlockFile = "impl"}{ref insertIncludeBlocks}
\#include "{if class.overrideProjectPrefix != "true"}{if project.includePrefix != ""}{$project.includePrefix}/{/if}{/if}{if class.includePrefix != ""}{$class.includePrefix}/{/if}{$class.name}.hpp"{if enableMutex == 1}
\#include "ifobject/IFMutex.hpp"{/if}{if enableGuards == 1}
\#include "ifobject/IFGuard.hpp"{/if}{if enableLogMessage == 1}
\#include "ifobject/IFLogMessage.hpp"{/if}{if enableSignal == 1}
\#include "ifobject/IFSignal.hpp"{/if}{foreach ev in event}
\#include "{if project.includePrefix != ""}{$project.includePrefix}/{/if}{if class.includePrefix != ""}{$class.includePrefix}/{/if}IF{$ev.id|uppercase(1)}Event.hpp"{/foreach}{foreach inc in include.impl}
\#include {$inc}{/foreach}{if enablePropertySet == 1}
\#include "ifobject/IFPropertySet.hpp"
\#include "ifobject/IFProperty.hpp"
\#include "ifobject/IFValue.hpp"{/if}{if enableMemDebug == 1}
\#include "ifobject/IFMMEvent.hpp"{/if}{if ( enableSerialize == 1) || ( enableXMLIO == 1)}
\#include "ifobject/utils.hpp"{/if}{if enableXMLIO == 1}
\#include "ifobject/xmlutils.hpp"{/if}{if enableSerialize == 1}
\#include "ifobject/serialize.hpp"

using Ionflux::ObjectBase::pack;
using Ionflux::ObjectBase::packObj;
using Ionflux::ObjectBase::unpack;
using Ionflux::ObjectBase::unpackObj;{/if}{$includeBlockPos = ""}{ref insertIncludeBlocks}{/section}
