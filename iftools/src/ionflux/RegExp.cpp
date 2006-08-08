/* ==========================================================================
 * Ionflux Tools
 * Copyright (c) 2004 Joern P. Meier
 * mail@ionflux.org
 * --------------------------------------------------------------------------
 * RegExp.cpp                Regular expression pattern matching
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

#include "ionflux/RegExp.hpp"

using namespace std;

namespace Ionflux
{

namespace Tools
{

RegExp::RegExp()
: regExp(0), maxSubpatterns(100), pcreOptions(0)
{
	// TODO: Nothing ATM. ;-)
}

RegExp::RegExp(const std::string& initPattern)
: regExp(0), maxSubpatterns(100), pcreOptions(0)
{
	setPattern(initPattern);
}

RegExp::RegExp(const std::string& initPattern, int initOptions)
: regExp(0), maxSubpatterns(100), pcreOptions(initOptions)
{
	setPattern(initPattern);
}

RegExp::~RegExp()
{
	if (regExp != 0)
		pcre_free(regExp);
}

void RegExp::setPattern(const std::string& newPattern)
{
	pattern = newPattern;
	if (pattern != "")
	{
		if (regExp != 0)
			pcre_free(regExp);
		const char *compileError;
		int errorOffset;
		regExp = pcre_compile(pattern.c_str(), pcreOptions, &compileError, 
			&errorOffset, NULL);
		if (!regExp)
		{
			cout << "[RegExp::setPattern] Error: Regular expression error at offset "
				 << errorOffset << ": " << compileError << endl;
			return;
		}
	}
}

string RegExp::getPattern()
{
	return pattern;
}

void RegExp::setOptions(int newOptions)
{
	if (newOptions != pcreOptions)
	{
		pcreOptions = newOptions;
		// Recompile current pattern with new options.
		setPattern(pattern);
	}
}

int RegExp::getOptions()
{
	return pcreOptions;
}

void RegExp::setMaxSubpatterns(unsigned int newMaxSubpatterns)
{
	maxSubpatterns = newMaxSubpatterns;
}

unsigned int RegExp::getMaxSubpatterns()
{
	return maxSubpatterns;
}

bool RegExp::match(const std::string& haystack, ReMatch* subPatterns)
{
	if ((regExp == 0) || (haystack.size() == 0))
		return false;
	int result;
	int subVecSize = (maxSubpatterns + 1) * 3;
	int* subVec = new int[subVecSize];
	result = pcre_exec(regExp, 0, haystack.c_str(), haystack.size(), 
		0, 0, subVec, subVecSize);
	if (result < 0)
	{
		delete[] subVec;
		return false;
	}
	if (subPatterns != 0)
	{
		subPatterns->clear();
		for (int i = 0; i < result; i++)
			subPatterns->push_back(haystack.substr(subVec[2 * i], 
				subVec[(2 * i) + 1] - subVec[2 * i]));
	}
	delete[] subVec;
	return true;
}

unsigned int RegExp::matchAll(const std::string& haystack, 
	ReMatchSet* subPatterns)
{
	if ((regExp == 0) || (haystack.size() == 0))
		return false;
	unsigned int offset = 0;
	int result = 1;
	int matches = 0;
	int subVecSize = (maxSubpatterns + 1) * 3;
	int* subVec = new int[subVecSize];
	if (subPatterns != 0)
		subPatterns->clear();
	while ((offset < haystack.size()) && (result > 0))
	{
		result = pcre_exec(regExp, 0, haystack.c_str(), haystack.size(), 
			offset, 0, subVec, subVecSize);
		if (result > 0)
		{
			if (subPatterns != 0)
			{
				subPatterns->push_back(ReMatch());
				for (int i = 0; i < result; i++)
				{
					subPatterns->back().push_back(haystack.substr(subVec[2 * i], 
						subVec[(2 * i) + 1] - subVec[2 * i]));
				}
			}
			matches++;
			offset = subVec[2 * (result - 1) + 1];
		}
	}
	delete[] subVec;
	return matches;
}

bool RegExp::match(const std::string& needle, const std::string& haystack, 
	ReMatch* subPatterns)
{
	setPattern(needle);
	return match(haystack, subPatterns);
}

unsigned int RegExp::matchAll(const std::string& needle, 
	const std::string& haystack, ReMatchSet* subPatterns)
{
	setPattern(needle);
	return matchAll(haystack, subPatterns);
}

void RegExp::replace(std::string& haystack, const std::string& replacement)
{
	string temp("");
	if ((regExp == 0) || (haystack.size() == 0))
		return;
	int result;
	int subVecSize = (maxSubpatterns + 1) * 3;
	int* subVec = new int[subVecSize];
	result = pcre_exec(regExp, 0, haystack.c_str(), haystack.size(), 
		0, 0, subVec, subVecSize);
	if (result < 0)
	{
		delete[] subVec;
		return;
	}
	if (subVec[0] > 0)
		temp.append(haystack.substr(0, subVec[0]));
	temp.append(replacement);
	if (static_cast<unsigned int>(subVec[1]) < haystack.size())
		temp.append(haystack.substr(subVec[1], haystack.size() - subVec[1]));
	haystack = temp;
	delete[] subVec;
}

void RegExp::replaceSubpatterns(std::string& haystack, 
	const std::vector<std::string>& replacement)
{
	string temp("");
	if ((regExp == 0) || (haystack.size() == 0))
		return;
	int result;
	int subVecSize = (maxSubpatterns + 1) * 3;
	int* subVec = new int[subVecSize];
	result = pcre_exec(regExp, 0, haystack.c_str(), haystack.size(), 
		0, 0, subVec, subVecSize);
	if (result < 0)
	{
		delete[] subVec;
		return;
	}
	int numRepl;
	int replFrom = 0;
	int replTo = 0;
	int k;
	(replacement.size() < static_cast<unsigned int>(result - 1)) 
		? numRepl = replacement.size()
		: numRepl = result - 1;
	for (int i = 0; i < numRepl; i++)
	{
		k = i + 1;
		// Append text preceding the current subpattern.
		replTo = subVec[2 * k];
		if (replTo > replFrom)
			temp.append(haystack.substr(replFrom, replTo - replFrom));
		// Append replacement.
		temp.append(replacement[i]);
		replFrom = subVec[2 * k + 1];
	}
	// Append remaining part of haystack.
	if (static_cast<unsigned int>(replFrom) < haystack.size())
		temp.append(haystack.substr(replFrom, haystack.size() - replFrom));
	haystack = temp;
	delete[] subVec;
}

void RegExp::replaceAll(std::string& haystack, const std::string& replacement)
{
	string temp("");
	if ((regExp == 0) || (haystack.size() == 0))
		return;
	unsigned int offset = 0;
	int result = 1;
	int subVecSize = (maxSubpatterns + 1) * 3;
	int* subVec = new int[subVecSize];
	int replFrom = 0;
	int replTo = 0;
	while ((offset < haystack.size()) && (result > 0))
	{
		result = pcre_exec(regExp, 0, haystack.c_str(), haystack.size(), 
			offset, 0, subVec, subVecSize);
		if (result > 0)
		{
			// Append text preceding the current pattern occurence.
			replTo = subVec[0];
			if (replTo > replFrom)
				temp.append(haystack.substr(replFrom, replTo - replFrom));
			// Append replacement.
			temp.append(replacement);
			replFrom = subVec[1];
			offset = replFrom;
		}
	}
	// Append remaining part of haystack.
	if (static_cast<unsigned int>(replFrom) < haystack.size())
		temp.append(haystack.substr(replFrom, haystack.size() - replFrom));
	haystack = temp;
	delete[] subVec;
}

void RegExp::replaceAllSubpatterns(std::string& haystack, 
	const std::vector<std::string>& replacement)
{
	string temp("");
	if ((regExp == 0) || (haystack.size() == 0))
		return;
	unsigned int offset = 0;
	int result = 1;
	int subVecSize = (maxSubpatterns + 1) * 3;
	int* subVec = new int[subVecSize];
	int numRepl;
	int replFrom = 0;
	int replTo = 0;
	int k;
	while ((offset < haystack.size()) && (result > 0))
	{
		result = pcre_exec(regExp, 0, haystack.c_str(), haystack.size(), 
			offset, 0, subVec, subVecSize);
		(replacement.size() < static_cast<unsigned int>(result - 1)) 
			? numRepl = replacement.size()
			: numRepl = result - 1;
		if (result > 0)
		{
			for (int i = 0; i < numRepl; i++)
			{
				k = i + 1;
				// Append text preceding the current subpattern.
				replTo = subVec[2 * k];
				if (replTo > replFrom)
					temp.append(haystack.substr(replFrom, replTo - replFrom));
				// Append replacement.
				temp.append(replacement[i]);
				replFrom = subVec[2 * k + 1];
			}
			offset = replFrom;
		}
	}
	// Append remaining part of haystack.
	if (static_cast<unsigned int>(replFrom) < haystack.size())
		temp.append(haystack.substr(replFrom, haystack.size() - replFrom));
	haystack = temp;
	delete[] subVec;
}

void RegExp::replace(const std::string& needle, std::string& haystack, 
	const std::string& replacement)
{
	setPattern(needle);
	return replace(haystack, replacement);
}

void RegExp::replaceSubpatterns(const std::string& needle, 
	std::string& haystack, const std::vector<std::string>& replacement)
{
	setPattern(needle);
	return replaceSubpatterns(haystack, replacement);
}

void RegExp::replaceAll(const std::string& needle, std::string& haystack, 
	const std::string& replacement)
{
	setPattern(needle);
	return replaceAll(haystack, replacement);
}

void RegExp::replaceAllSubpatterns(const std::string& needle, 
	std::string& haystack, const std::vector<std::string>& replacement)
{
	setPattern(needle);
	return replaceAllSubpatterns(haystack, replacement);
}

void RegExp::createMatchMap(const ReMatch& match, const std::string& fields, 
	const std::string& separator, const std::string& undefinedPrefix, 
	std::map<std::string, std::string>& record)
{
	vector<string> fieldVec;
	explode(fields, separator, fieldVec);
	createMatchMap(match, fieldVec, undefinedPrefix, record);
}

void RegExp::createMatchMap(const ReMatch& match, 
	const std::vector<std::string>& fields, const std::string& undefinedPrefix, 
	std::map<std::string, std::string>& record)
{
	unsigned int currentField = 0;
	int undefinedFields = 0;
	string key;
	record.clear();
	for (ReMatch::const_iterator i = match.begin(); i != match.end(); i++)
	{
		if (currentField > 0)
		{
			if ((currentField - 1) < fields.size())
			{
				key = fields[currentField - 1];
			} else
			{
				ostringstream completeKey;
				completeKey << undefinedPrefix << undefinedFields;
				key = completeKey.str();
				undefinedFields++;
			}
			record[key] = *i;
		}
		currentField++;
	}
}

void RegExp::createMatchTree(const ReMatch& match, const std::string& fields, 
	const std::string& separator, const std::string& undefinedPrefix, 
	Node& record)
{
	vector<string> fieldVec;
	explode(fields, separator, fieldVec);
	createMatchTree(match, fieldVec, undefinedPrefix, record);
}

void RegExp::createMatchTree(const ReMatch& match, 
	const std::vector<std::string>& fields, const std::string& undefinedPrefix, 
	Node& record)
{
	unsigned int currentField = 0;
	int undefinedFields = 0;
	string key;
	record.clear();
	for (ReMatch::const_iterator i = match.begin(); i != match.end(); i++)
	{
		if (currentField > 0)
		{
			if ((currentField - 1) < fields.size())
			{
				key = fields[currentField - 1];
			} else
			{
				ostringstream completeKey;
				completeKey << undefinedPrefix << undefinedFields;
				key = completeKey.str();
				undefinedFields++;
			}
			record[key] = *i;
		}
		currentField++;
	}
}

}

}

/** \file RegExp.cpp
 * \brief Regular expression pattern matching implementation.
 */
