/* ==========================================================================
 * IFTemplate - Ionflux Template Processor
 * Copyright © 2012-2013 Jörn P. Meier
 * mail@ionflux.org
 * --------------------------------------------------------------------------
 * iftpl.cpp                  Template processor.
 * ==========================================================================
 * 
 * This file is part of IFTemplate - Ionflux Template Processor.
 * 
 * IFTemplate - Ionflux Template Processor is free software; you can 
 * redistribute it and/or modify it under the terms of the GNU General 
 * Public License as published by the Free Software Foundation; either 
 * version 2 of the License, or (at your option) any later version.
 * 
 * IFTemplate - Ionflux Template Processor is distributed in the hope that 
 * it will be useful, but WITHOUT ANY WARRANTY; without even the implied 
 * warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See 
 * the GNU General Public License for more details.
 * 
 * You should have received a copy of the GNU General Public License along 
 * with IFTemplate - Ionflux Template Processor; if not, write to the Free 
 * Software Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA 
 * 02111-1307 USA
 * 
 * ========================================================================== */

#include <iostream>
#include <string>
#include "iftemplate/Template.hpp"
#include "iftemplate/TemplateRepository.hpp"
#include "iftemplate/ConfigTree.hpp"
#include "iftemplate/CLArgs.hpp"
#include "iftemplate/Node.hpp"
#include "iftemplate/DateTime.hpp"
#include "ifobject/IFMMEventHandler.hpp"

using namespace std;
using namespace Ionflux::Template;

// Application version number.
const std::string APP_VERSION = "1.0.0";

void printHelp()
{
    std::cerr << 
"Usage: iftpl <option> ... <template file/module> <config file> "
    "[<config file> ...]\n"
"Options:\n"
"  -h, --help                 Print this help.\n"
"  -v, --version              Print version information.\n"
"  -r, --replace              Replace configuration while merging.\n"
"  -I, --include <path list>  Set template include path(s)."
	<< std::endl;
}

void printVersion()
{
	std::cerr << "iftpl " << APP_VERSION << std::endl
		<< "Copyright (c) 2013 Joern P. Meier (mail@ionflux.org)" << std::endl
		<< "This is free software; see the source for copying conditions. " 
		   "There is NO" << std::endl
		<< "warranty; not even for MERCHANTABILITY or FITNESS FOR A "
		<< "PARTICULAR PURPOSE." << std::endl;
}

int main(int argc, char* argv[])
{
    /* <---- DEBUG ----- //
    Ionflux::ObjectBase::IFMMEventHandler* mm =
        Ionflux::ObjectBase::IFMMEventHandler::getInstance();
    mm->setSilentFlag(false);
    // ----- DEBUG ----> */
	CLArgs args;
	args.addAcceptableOption("h", false);
	args.addAcceptableOption("help", false);
	args.addAcceptableOption("v", false);
	args.addAcceptableOption("version", false);
	args.addAcceptableOption("r", false);
	args.addAcceptableOption("replace", false);
	args.addAcceptableOption("I", true);
	args.addAcceptableOption("include", true);
	args.setArgs(argc, argv);
	if (!args.optionsOK())
	{
		for (unsigned int i = 0; i < args.getInvalidOptions().size(); i++)
			cerr << "Option not recognized: '" << args.getInvalidOptions()[i] 
				<< "'" << endl;
	}
	CLOption* includeOpt = args.getOption("I");
	if (includeOpt == 0)
	    includeOpt = args.getOption("include");
	std::string includePath;
	if (includeOpt != 0)
	    includePath = includeOpt->value;
	CLParams params;
	args.getParams(params);
	if (args.isSet("v") || args.isSet("version"))
	{
		printVersion();
		return 0;
	}
	if (args.isSet("h") || args.isSet("help") || (params.size() < 2))
	{
		printHelp();
		return 0;
	}
	bool replace = (args.isSet("r") || args.isSet("replace"));
	string templateFile = params[0];
	string configFile = params[1];
	Template tpl;
	TemplateRepository* tr = 0;
	if (includePath.size() > 0)
	{
	    tr = TemplateRepository::create();
	    tr->addTemplatePaths(includePath);
	    tr->update();
	    tpl.setRepository(tr);
	}
	ConfigTree config;
	Node& root = *tpl.getRoot();
	config.readConfig(configFile);
	root = *config.getRoot();
	root["__config_file"] = configFile;
	root["__template_file"] = templateFile;
	DateTime now;
	root["__datetime"] = now.getTimestamp();
	root["__rfc_datetime"] = now.getRFCTimestamp();
	if (params.size() > 2)
		// Merge additional configuration files.
		for (unsigned int i = 2; i < params.size(); i++)
		{
			string mergeFile = params[i];
			ConfigTree mergeConfig;
			mergeConfig.readConfig(mergeFile);
			root.merge(*mergeConfig.getRoot(), replace);
		}
    if (tr == 0)
        tpl.readTemplate(templateFile);
    else
        tpl.setTemplateModule(templateFile);
	string result = tpl.process();
	cout << result;
	return 0;
}

/** \file iftpl.cpp
 * \brief Template processor.
 */
