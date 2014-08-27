{section projectInfo}\#ifndef {$project.includeGuardPrefix}{$class.name|uppercase}_XML
\#define {$project.includeGuardPrefix}{$class.name|uppercase}_XML
/* ==========================================================================
 * {$project.name}
 * Copyright © {$project.copyrightYear} {$project.author}
 * {$project.mail}
 * --------------------------------------------------------------------------
{swrap 75 ' * '}{$class.name|append('_xml_private.hpp')|rpad(' ', 30)}  {$class.shortDesc} (header).{/swrap}{if project.license == "GPL"}{ref insertGPLDisclaimer}{/if}
 * ========================================================================== */{/section}
