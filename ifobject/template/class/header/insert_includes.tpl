{section insertIncludeBlocks}{foreach block in includeBlock}{if ( block.pos == includeBlockPos ) && ( block.file == includeBlockFile )}{if block.type == "list"}{foreach inc in block.list}
\#include {$inc}{/foreach}{else}{if block.type == "verbatim"}
{$block.value}{/if}{/if}{/if}{/foreach}{/section}{section insertIncludes}{if project.exportSpecInclude != ""}
\#include "{$project.exportSpecInclude}"{/if}{$includeBlockPos = ""}{$includeBlockFile = "header"}{ref insertIncludeBlocks}{foreach inc in include.header}
\#include {$inc}{/foreach}{if enablePersistence == 1}
\#include "{$project.persistence.include}"{/if}{foreach bc in class.base.ifobject}
\#include "{if bc.include == ""}ifobject/{$bc.name}.hpp{else}{$bc.include}{/if}"{/foreach}{foreach bc in class.base.other}{if bc.include != "<none>"}
\#include "{if bc.include == ""}{$bc.name}.hpp{else}{$bc.include}{/if}"{/if}{/foreach}{$includeBlockPos = "post"}{ref insertIncludeBlocks}{/section}
