/* ==========================================================================
 * Ionflux Tools
 * Copyright (c) 2004 Joern P. Meier
 * mail@ionflux.org
 * --------------------------------------------------------------------------
 * Config.cpp                    Configuration wrapper
 * ==========================================================================
 * 
 * This file is part of Ionflux Tools.
 * 
 * Ionflux Tools is free software; you can redistribute it and/or modify it 
 * under the terms of the GNU General Public License as published by the Free
 * Software Foundation; either version 2 of the License, or (at  your option)
 * any later version.
 * 
 * Ionflux Tools is distributed in the hope that it will be useful, but 
 * WITHOUT ANY WARRANTY; without even the implied warranty of MERCHANTABILITY
 * or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU General Public License
 * for more details.
 * 
 * You should have received a copy of the GNU General Public License
 * along with Ionflux Tools; if not, write to the Free Software Foundation, 
 * Inc., 59 Temple Place, Suite 330, Boston, MA 02111-1307 USA
 * 
 * ========================================================================== */

#include "ionflux/ConfigMap.hpp"

using namespace std;

namespace Ionflux
{

namespace Tools
{

const string ConfigMap::CONFIG_PATTERN = "([a-zA-Z0-9_\\.]+)\\s*=\\s*(.*)";
const string ConfigMap::COMMENT_PATTERN = "^#";

ConfigMap::ConfigMap()
: configRE(0), commentRE(0)
{
	clear();
	init();
}

ConfigMap::~ConfigMap()
{
	pcre_free(configRE);
	pcre_free(commentRE);
}

void ConfigMap::clear()
{
	config.clear();
	configInput.clear();
	newKeys.clear();
	inputFile = "";
}

void ConfigMap::init()
{
	const char *compileError;
	int errorOffset;
	configRE = pcre_compile(CONFIG_PATTERN.c_str(), 0, &compileError, 
		&errorOffset, NULL);
	if (!configRE)
	{
		cout << "[ConfigMap::parseConfigLine] Error: Regular expression error "
			"in CONFIG_PATTERN at offset "
			<< errorOffset << ": " << compileError << endl;
		return;
	}
	commentRE = pcre_compile(COMMENT_PATTERN.c_str(), 0, &compileError, 
		&errorOffset, NULL);
	if (!commentRE)
	{
		cout << "[ConfigMap::parseConfigLine] Error: Regular expression error "
			"in COMMENT_PATTERN at offset "
			<< errorOffset << ": " << compileError << endl;
		return;
	}
}

ConfigOption ConfigMap::parseConfigLine(const std::string& configLine)
{
	ConfigOption option;
	option.key = "";
	option.value = "";
	if ((configRE == 0) || (commentRE == 0))
	{
		cout << "[ConfigMap::parseConfigLine] Error: patterns have not been "
			"initialized."
			<< endl;
		return option;
	}
	int result;
	int subPattern[30];
	result = pcre_exec(commentRE, NULL, configLine.c_str(), 
		configLine.length(), 0, 0, subPattern, 30);
	if (result == PCRE_ERROR_NOMATCH)
	{
		result = pcre_exec(configRE, NULL, configLine.c_str(), 
			configLine.length(), 0, 0, subPattern, 30);
		if (result >= 2)
		{
			option.key = configLine.substr(subPattern[2], 
				subPattern[3] - subPattern[2]);
			option.value = configLine.substr(subPattern[4], 
				subPattern[5] - subPattern[4]);
		}
	}
	return option;
}

void ConfigMap::readConfig(const std::string& configFile)
{
	ifstream configFileStream(configFile.c_str());
	if (!configFileStream)
	{
		cout << "[ConfigMap::readConfig] Error: Could not read from file '" 
			<< configFile << "'" << endl;
		return;
	}
	clear();
	inputFile = configFile;
	ConfigOption option;
	string currentLine;
	int lineLength;
	while (!configFileStream.eof())
	{
		getline(configFileStream, currentLine);
		lineLength = currentLine.size();
		if (lineLength > 1)
		{
			if (currentLine[lineLength - 1] == '\r')
				currentLine = currentLine.substr(0, lineLength - 1);
		} else
		if (currentLine == "\r")
			currentLine = "";
		configInput.push_back(currentLine);
		option = parseConfigLine(currentLine);
		if (option.key != "")
			config[option.key] = option.value;
	}
}

void ConfigMap::writeConfig()
{
	if (inputFile != "")
		writeConfig(inputFile);
}

void ConfigMap::writeConfig(const std::string& configFile)
{
	ofstream configFileStream(configFile.c_str());
	if (!configFileStream)
	{
		cout << "[ConfigMap::writeConfig] Error: Could write to file '" 
			<< configFile << "'" << endl;
		return;
	}
	updateInputData();
	vector<string>::const_iterator i;
	for (i = configInput.begin(); i != configInput.end(); i++)
	{
		configFileStream << *i << "\n";
	}
	configFileStream.flush();
}

void ConfigMap::updateInputData()
{
	vector<string> output;
	vector<string>::const_iterator i;
	ConfigOption option;
	for (i = configInput.begin(); i != configInput.end(); i++)
	{
		option = parseConfigLine(*i);
		if (option.key != "")
		{
			if (config[option.key] != option.value)
			{
				output.push_back(option.key + " = " + config[option.key]);
			} else
			{
				output.push_back(*i);
			}
		} else
		{
			output.push_back(*i);
		}
	}
	configInput.clear();
	for (i = output.begin(); i != output.end(); i++)
		configInput.push_back(*i);
	if (newKeys.size() > 0)
		configInput.push_back(
			"# The following options were added automatically");
	for (i = newKeys.begin(); i != newKeys.end(); i++)
		configInput.push_back(*i + " = " + config[*i]);
	newKeys.clear();
}

string ConfigMap::get(const std::string& key)
{
	return config[key];
}

void ConfigMap::set(const std::string& key, const std::string& value)
{
	if (config[key] == "")
		newKeys.push_back(key);
	config[key] = value;
}

}

}

/** \file ConfigMap.cpp
 * \brief Configuration map implementation.
 */
