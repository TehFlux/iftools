{import class.check_features}{ref checkFeatures}{import xml.xml_scan_properties}{ref xmlScanProperties}{import class.insert_gpl_disclaimer}{import xml.impl.project_info}{ref projectInfo}
\#include <cstdlib>
\#include <string>
\#include <sstream>
\#include "{$project.includePrefix}/{$class.name}.hpp"{foreach base in class.base.other}{if ( base.xml.enabled == "true" ) && ( base.xml.include != "" )}
\#include "{$base.xml.include}_xml_private.hpp"
\#include "{$base.xml.include}_xml.hpp"{/if}{/foreach}
\#include "{$project.includePrefix}/{$class.name}_xml_private.hpp"
\#include "{$project.includePrefix}/{$class.name}_xml.hpp"{import xml.impl.get_from_xml_inner}{ref getFromXMLInner}

/** \\file {$class.name}_xml.cpp
 * \\brief {$class.shortDesc} XML implementation.
 */

