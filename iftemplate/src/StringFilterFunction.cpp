/* ==========================================================================
 * IFTemplate - Ionflux Template Processor
 * Copyright © 2012 Jörn P. Meier
 * mail@ionflux.org
 * --------------------------------------------------------------------------
 * StringFilterFunction.cpp        String filter function (implementation).
 * =========================================================================
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

#include "iftemplate/StringFilterFunction.hpp"
#include <iostream>
#include <iomanip>
#include <sstream>
#include "iftemplate/IFTemplateError.hpp"

using namespace std;

namespace Ionflux
{

namespace Template
{

StringFilterFunctionClassInfo::StringFilterFunctionClassInfo()
{
	name = "StringFilterFunction";
	desc = "String filter function";
	baseClassInfo.push_back(Ionflux::ObjectBase::IFObject::CLASS_INFO);
}

StringFilterFunctionClassInfo::~StringFilterFunctionClassInfo()
{
}

// run-time type information instance constants
const StringFilterFunctionClassInfo StringFilterFunction::stringFilterFunctionClassInfo;
const Ionflux::ObjectBase::IFClassInfo* StringFilterFunction::CLASS_INFO = &StringFilterFunction::stringFilterFunctionClassInfo;

StringFilterFunction::StringFilterFunction()
: func(""), manip(0)
{
	// NOTE: The following line is required for run-time type information.
	theClass = CLASS_INFO;
	// TODO: Nothing ATM. ;-)
}

StringFilterFunction::StringFilterFunction(const Ionflux::Template::StringFilterFunction& other)
: func(""), manip(0)
{
	// NOTE: The following line is required for run-time type information.
	theClass = CLASS_INFO;
	*this = other;
}

StringFilterFunction::StringFilterFunction(const std::string& initFunc, 
Ionflux::Template::StringManipulator::StringManipulator* initManip, 
Ionflux::ObjectBase::StringVector* initArgs)
: func(initFunc), manip(0)
{
	// NOTE: The following line is required for run-time type information.
	theClass = CLASS_INFO;
	if (initManip != 0)
	    setManip(initManip);
	if (initArgs != 0)
	    addArguments(*initArgs);
}

StringFilterFunction::~StringFilterFunction()
{
	clearArguments();
	// TODO: Nothing ATM. ;-)
}

void StringFilterFunction::setArgument(unsigned int index, const 
std::string& newArg)
{
	if (index > args.size())
	{
	    std::ostringstream status;
	    status << "[StringFilterFunction::setArgument] "
	        "Index out of range: " << index;
	    throw IFTemplateError(status.str());
	}
	args[index] = newArg;
}

void StringFilterFunction::setFunc(const std::string& newFunc)
{
	func = newFunc;
}

std::string StringFilterFunction::getFunc() const
{
    return func;
}

unsigned int StringFilterFunction::getNumArguments() const
{
    return args.size();
}

std::string StringFilterFunction::getArgument(unsigned int elementIndex) 
const
{
    if (elementIndex < args.size())
		return args[elementIndex];
	return "";
}

int StringFilterFunction::findArgument(const std::string& needle, unsigned 
int occurence) const
{
    bool found = false;
	std::string currentArgument = "";
	unsigned int i = 0;
	while (!found 
		&& (i < args.size()))
	{
		currentArgument = args[i];
		if (currentArgument == needle)
        {
            if (occurence == 1)
			    found = true;
            else
                occurence--;
		} else
			i++;
	}
	if (found)
        return i;
	return -1;
}

std::vector<std::string>& StringFilterFunction::getArguments()
{
    return args;
}

void StringFilterFunction::addArgument(const std::string& addElement)
{
	args.push_back(addElement);
}

const std::string& StringFilterFunction::addArgument()
{
	const std::string& o0 = std::string();
	addArgument(o0);
	return o0;
}

void StringFilterFunction::addArguments(const std::vector<std::string>& 
newArguments)
{
	for (std::vector<std::string>::const_iterator i = newArguments.begin(); 
	    i != newArguments.end(); i++)
	    addArgument(*i);
}

void 
StringFilterFunction::addArguments(Ionflux::Template::StringFilterFunction*
newArguments)
{
	for (unsigned int i = 0; 
	    i < newArguments->getNumArguments(); i++)
	    addArgument(newArguments->getArgument(i));
}

void StringFilterFunction::removeArgument(const std::string& removeElement)
{
    bool found = false;
	std::string currentArgument = "";
	unsigned int i = 0;
	while (!found 
		&& (i < args.size()))
	{
		currentArgument = args[i];
		if (currentArgument == removeElement)
			found = true;
		else
			i++;
	}
	if (found)
	{
		args.erase(args.begin() + i);
	}
}

void StringFilterFunction::removeArgumentIndex(unsigned int removeIndex)
{
    if (removeIndex > args.size())
        return;
    args.erase(args.begin() + removeIndex);
}

void StringFilterFunction::clearArguments()
{
    args.clear();
}

void 
StringFilterFunction::setManip(Ionflux::Template::StringManipulator::StringManipulator*
newManip)
{
	manip = newManip;
}

Ionflux::Template::StringManipulator::StringManipulator* 
StringFilterFunction::getManip() const
{
    return manip;
}

Ionflux::Template::StringFilterFunction& 
StringFilterFunction::operator=(const 
Ionflux::Template::StringFilterFunction& other)
{
if (this == &other)
    return *this;
	return *this;
}

Ionflux::Template::StringFilterFunction* StringFilterFunction::copy() const
{
    StringFilterFunction* newStringFilterFunction = create();
    *newStringFilterFunction = *this;
    return newStringFilterFunction;
}

Ionflux::Template::StringFilterFunction* 
StringFilterFunction::upcast(Ionflux::ObjectBase::IFObject* other)
{
    return dynamic_cast<StringFilterFunction*>(other);
}

Ionflux::Template::StringFilterFunction* 
StringFilterFunction::create(Ionflux::ObjectBase::IFObject* parentObject)
{
    StringFilterFunction* newObject = new StringFilterFunction();
    if (newObject == 0)
    {
        throw IFTemplateError("Could not allocate object.");
    }
    if (parentObject != 0)
        parentObject->addLocalRef(newObject);
    return newObject;
}

Ionflux::Template::StringFilterFunction* StringFilterFunction::create(const
std::string& initFunc, 
Ionflux::Template::StringManipulator::StringManipulator* initManip, 
Ionflux::ObjectBase::StringVector* initArgs, Ionflux::ObjectBase::IFObject*
parentObject)
{
    StringFilterFunction* newObject = new StringFilterFunction(initFunc, 
    initManip, initArgs);
    if (newObject == 0)
    {
        throw IFTemplateError("Could not allocate object.");
    }
    if (parentObject != 0)
        parentObject->addLocalRef(newObject);
    return newObject;
}

}

}

/** \file StringFilterFunction.cpp
 * \brief String filter function implementation.
 */
