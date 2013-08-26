{section projectInfo}\#ifndef {$project.includeGuardPrefix}{$class.name|uppercase}
\#define {$project.includeGuardPrefix}{$class.name|uppercase}
/* ==========================================================================
 * {$project.name}
 * Copyright © {$project.copyrightYear} {$project.author}
 * {$project.mail}
 * --------------------------------------------------------------------------
{swrap 75 ' * '}{$class.name|append('.hpp')|rpad(' ', 30)}  {$class.shortDesc} (header).{/swrap}{if project.license == "GPL"}{ref insertGPLDisclaimer}{/if}
 * ========================================================================== */{/section}
