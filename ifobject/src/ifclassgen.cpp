/* ==========================================================================
 * Ionflux Object Base System
 * Copyright © 2006 Joern P. Meier
 * mail@ionflux.org
 * --------------------------------------------------------------------------
 * ifclassgen.cpp                         Class generator.
 * ==========================================================================
 *
 * This file is part of Ionflux's Stuff.
 *
 * Ionflux's Stuff is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by the
 * Free Software Foundation; either version 2 of the License, or (at your
 * option) any later version.
 *
 * Ionflux's Stuff is distributed in the hope that it will be useful, but
 * WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 * General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License along
 * with Ionflux's Stuff; if not, write to the Free Software Foundation,
 * Inc., 59 Temple Place, Suite 330, Boston, MA 02111-1307 USA
 *
 * ========================================================================== */

#include <iostream>
#include <string>
#include <sstream>
#include <fstream>
#include <iomanip>
#include "ionflux/CLArgs.hpp"
#include "ionflux/ConfigTree.hpp"
#include "ionflux/Template.hpp"
#include "ionflux/File.hpp"
#include "ionflux/DateTime.hpp"

using namespace std;
using namespace Ionflux::Tools;

void printHelp()
{
	cerr << "Usage: ifclassgen [options] <class name>\n"
		"Options:\n"
		"  -t, --templatedir <dir>   Class template directory\n"
		"                            (default: template/class).\n"
		"  -c, --configdir <dir>     Class configuration directory\n"
		"                            (default: conf/class).\n"
		"  -m  --merge <list>        Whitespace separated list of\n"
		"                            configuration files to be merged.\n"
		"                            files to be merged.\n"
		"  -i --includedir           Output directory for header files\n"
		"                            (default: include).\n"
		"  -s --srcdir               Output directory for implementation\n"
		"                            files (default: src).\n"
		"  -e --genevents            Generate event classes.\n"
		"  --eventtemplate <file>    Event configuration template file\n"
		"                            (default: template/event.conf.tpl)"
		"  -h, --help                Print this help.\n"
		"  -v, --version             Print version information."
	<< endl;
}

void printVersion()
{
	cerr << "Ionflux Object Base System class generator 0.0.1" << endl
		<< "Copyright (c) 2006 Joern P. Meier <mail@ionflux.org>" << endl
		<< "This is free software; see the source for copying conditions. " 
		   "There is NO" << endl
		<< "warranty; not even for MERCHANTABILITY or FITNESS FOR A "
		<< "PARTICULAR PURPOSE." << endl;
}

int main(int argc, char* argv[])
{
	CLArgs args;
	args.addAcceptableOption("h", false);
	args.addAcceptableOption("help", false);
	args.addAcceptableOption("v", false);
	args.addAcceptableOption("version", false);
	args.addAcceptableOption("t", true);
	args.addAcceptableOption("templatedir", true);
	args.addAcceptableOption("c", true);
	args.addAcceptableOption("configdir", true);
	args.addAcceptableOption("i", true);
	args.addAcceptableOption("includedir", true);
	args.addAcceptableOption("s", true);
	args.addAcceptableOption("srcdir", true);
	args.addAcceptableOption("m", true);
	args.addAcceptableOption("merge", true);
	args.addAcceptableOption("e", false);
	args.addAcceptableOption("genevents", false);
	args.addAcceptableOption("eventtemplate", true);
	args.setArgs(argc, argv);
	if (!args.optionsOK())
	{
		for (unsigned int i = 0; i < args.getInvalidOptions().size(); i++)
			cerr << "Option not recognized: '" << args.getInvalidOptions()[i] 
				<< "'" << endl;
	}
	if (args.isSet("v") || args.isSet("version"))
	{
		printVersion();
		return 0;
	}
	CLParams params;
	args.getParams(params);
	unsigned int numInput = params.size();
	if ((numInput == 0) || args.isSet("h") || args.isSet("help"))
	{
		printHelp();
		return 0;
	}
	string className = params[0];
	if (!isIdentifier(className))
	{
		cerr << "ERROR: Invalid characters in class name." << endl;
		return -1;
	}
	CLOption* tplOpt = args.getOption("t");
	if (tplOpt == 0)
		tplOpt = args.getOption("templatedir");
	string tplDir;
	if (tplOpt != 0)
		tplDir = tplOpt->value;
	else
		tplDir = "template/class";
	CLOption* confOpt = args.getOption("c");
	if (confOpt == 0)
		confOpt = args.getOption("confdir");
	string confDir;
	if (confOpt != 0)
		confDir = confOpt->value;
	else
		confDir = "conf/class";
	CLOption* includeOpt = args.getOption("i");
	if (includeOpt == 0)
		includeOpt = args.getOption("includedir");
	string includeDir;
	if (includeOpt != 0)
		includeDir = includeOpt->value;
	else
		includeDir = "include";
	CLOption* srcOpt = args.getOption("s");
	if (srcOpt == 0)
		srcOpt = args.getOption("srcdir");
	string srcDir;
	if (srcOpt != 0)
		srcDir = srcOpt->value;
	else
		srcDir = "src";
	CLOption* mergeOpt = args.getOption("m");
	if (mergeOpt == 0)
		mergeOpt = args.getOption("merge");
	string mergeList;
	if (mergeOpt != 0)
		mergeList = mergeOpt->value;
	std::vector<string> mergeFiles;
	explodeQuoted(mergeList, mergeFiles);
	bool generateEvents = false;
	if (args.isSet("e") || args.isSet("genevents"))
		generateEvents = true;
	CLOption* eventTplOpt = args.getOption("eventtemplate");
	string eventTplFile;
	if (eventTplOpt != 0)
		eventTplFile = eventTplOpt->value;
	else
		eventTplFile = "template/event.conf.tpl";
	cerr << "Ionflux Object Base system class generator 0.0.1" << endl;
	ConfigTree config;
	File currentFile;
	ostringstream status;
	status << appendDirSeparator(confDir) << className << ".conf";
	string classConfigFile = status.str();
	currentFile.setFullName(classConfigFile);
	if (!currentFile.isValid())
	{
		cerr << "ERROR: Class configuration file '" << classConfigFile 
			<< "' not found." << endl;
		return -1;
	}
	config.readConfig(classConfigFile);
	Node& configRoot = *config.getRoot();
	// Merge configuration files.
	ConfigTree currentConfig;
	Node mergeConf;
	mergeConf.setAutoCreate(true);
	mergeConf.setIndexMode(Node::INDEX_MODE_NODE);
	std::vector<string>::iterator l = mergeFiles.begin();
	unsigned int mergeCount = 0;
	if (l != mergeFiles.end())
	{
		cerr << "Merging configuration files..." << endl;
		while (l != mergeFiles.end())
		{
			currentFile.setFullName(*l);
			if (currentFile.isValid())
			{
				cerr << "  Merging file '" << *l << "'... ";
				currentConfig.readConfig(*l);
				mergeConf.merge(*(currentConfig.getRoot()));
				cerr << "done." << endl;
			} else
				cerr << "  ERROR: File '" << *l << " not found." << endl;
			l++;
			mergeCount++;
		}
		if (mergeCount != 1)
			cerr << "Done (" << mergeCount << " configuration files merged)." 
				<< endl;
		else
			cerr << "Done (" << mergeCount << " configuration file merged)." 
				<< endl;
	}
	if (mergeCount > 0)
		configRoot.merge(mergeConf);
	// Set special variables.
	DateTime now;
	config["___datetime"].setData(now.getTimestamp());
	config["___rfc_datetime"].setData(now.getRFCTimestamp());
	// Prepare templates.
	status.str("");
	status << appendDirSeparator(tplDir) << "Class.hpp.tpl";
	string classHeaderTplFile = status.str();
	currentFile.setFullName(classHeaderTplFile);
	if (!currentFile.isValid())
	{
		cerr << "ERROR: Class header template file '" << classHeaderTplFile 
			<< "' not found." << endl;
		return -1;
	}
	string headerTpl = readFile(classHeaderTplFile);
	status.str("");
	status << appendDirSeparator(tplDir) << "Class.cpp.tpl";
	string classImplTplFile = status.str();
	currentFile.setFullName(classImplTplFile);
	if (!currentFile.isValid())
	{
		cerr << "ERROR: Class implementation template file '" 
			<< classImplTplFile << "' not found." << endl;
		return -1;
	}
	string implTpl = readFile(classImplTplFile);
	// Generate output.
	Template tpl;
	string header = tpl.process(headerTpl, &configRoot);
	currentFile.setFullName(includeDir);
	if (!currentFile.isDir())
	{
		cerr << "ERROR: Header output path '" << includeDir 
			<< "' is not a directory." << endl;
		return -1;
	}
	status.str("");
	status << appendDirSeparator(includeDir) << className << ".hpp";
	cerr << "Writing header file to '" << status.str() << "'... ";
	writeFile(status.str(), header, 'w');
	cerr << "done." << endl;
	/* ----- DEBUG ----- //
	cerr << "DEBUG: header:" << endl;
	cerr << header << endl;
	// ----- DEBUG ----- */
	string impl = tpl.process(implTpl, &configRoot);
	currentFile.setFullName(srcDir);
	if (!currentFile.isDir())
	{
		cerr << "ERROR: Implementation output path '" << srcDir 
			<< "' is not a directory." << endl;
		return -1;
	}
	status.str("");
	status << appendDirSeparator(srcDir) << className << ".cpp";
	cerr << "Writing implementation file to '" << status.str() << "'... ";
	writeFile(status.str(), impl, 'w');
	cerr << "done." << endl;
	/* ----- DEBUG ----- //
	cerr << "DEBUG: implementation:" << endl;
	cerr << impl << endl;
	// ----- DEBUG ----- */
	// Generate event classes.
	if (generateEvents)
	{
		currentFile.setFullName(eventTplFile);
		if (!currentFile.isValid())
		{
			cerr << "ERROR: Event configuration template file '" 
				<< eventTplFile << "' not found." << endl;
			return -1;
		}
		string eventConfTpl = readFile(eventTplFile);
		Node& eventNode = configRoot["event"];
		Node* currentEvent = 0;
		unsigned int numEvents = eventNode.getNumChildren();
		cerr << "Generating event classes... " << endl;
		for (unsigned int i = 0; i < numEvents; i++)
		{
			currentEvent = eventNode.getChild(i);
			if (currentEvent != 0)
			{
				Node eventConfNode;
				eventConfNode.setAutoCreate(true);
				eventConfNode.setIndexMode(Node::INDEX_MODE_NODE);
				eventConfNode["___datetime"].setData(now.getTimestamp());
				eventConfNode["___rfc_datetime"].setData(now.getRFCTimestamp());
				eventConfNode.merge(mergeConf);
				eventConfNode.merge(*currentEvent);
				/* Create additional configuration using the global 
				   configuration and the event configuration. */
				string eventConf = tpl.process(eventConfTpl, &eventConfNode);
				ConfigTree processedEventConf;
				processedEventConf.parseConfig(eventConf);
				eventConfNode.merge(*processedEventConf.getRoot());
				string eventClassName = eventConfNode["class"]["name"]
					.getData();
				if (eventClassName.size() == 0)
				{
					cerr << "ERROR: Event class name not found "
						"(it should be available in the configuration as "
						"class.name)." << endl;
					return -1;
				}
				if (!isIdentifier(eventClassName))
				{
					cerr << "ERROR: Invalid characters in event class name." 
						<< endl;
					return -1;
				}
				cerr << "  Creating event class '" << eventClassName << "'..." 
					<< endl;
				string eventHeader = tpl.process(headerTpl, &eventConfNode);
				status.str("");
				status << appendDirSeparator(includeDir) << eventClassName 
					<< ".hpp";
				cerr << "    Writing header file to '" << status.str() 
					<< "'... ";
				writeFile(status.str(), eventHeader, 'w');
				cerr << "done." << endl;
				string eventImpl = tpl.process(implTpl, &eventConfNode);
				status.str("");
				status << appendDirSeparator(srcDir) << eventClassName 
					<< ".cpp";
				cerr << "    Writing implementation file to '" << status.str() 
					<< "'... ";
				writeFile(status.str(), eventImpl, 'w');
				cerr << "done." << endl;
				cerr << "  Done." << endl;
			}
		}
		cerr << "Done." << endl;
	}
	return 0;
}
