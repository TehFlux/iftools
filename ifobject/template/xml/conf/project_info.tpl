{import xml.conf.insert_gpl_disclaimer}{section projectInfo}\# ==========================================================================
\# {$project.name}
\# Copyright © {$project.copyrightYear} {$project.author}
\# {$project.mail}
\# --------------------------------------------------------------------------
{swrap 75 '# '}{$class.name|append('XMLFactory.conf')|rpad(' ', 30)}  {$class.name} XML factory (configuration).{/swrap}{if project.license == "GPL"}{ref insertGPLDisclaimer}{/if}
\# =========================================================================={/section}
