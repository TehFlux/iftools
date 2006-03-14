# ==========================================================================
# Ionflux Tools
# Copyright (c) 2004 Joern P. Meier
# mail@ionflux.org
# --------------------------------------------------------------------------
# Class.cpp.tpl                Class template.
# ==========================================================================
# 
# This file is part of Ionflux Tools.
# 
# Ionflux Tools is free software; you can redistribute it and/or modify it 
# under the terms of the GNU General Public License as published by the Free
# Software Foundation; either version 2 of the License, or (at  your option)
# any later version.
# 
# Ionflux Tools is distributed in the hope that it will be useful, but 
# WITHOUT ANY WARRANTY; without even the implied warranty of MERCHANTABILITY
# or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU General Public License
# for more details.
# 
# You should have received a copy of the GNU General Public License
# along with Ionflux Tools; if not, write to the Free Software Foundation, 
# Inc., 59 Temple Place, Suite 330, Boston, MA 02111-1307 USA
# 
# ==========================================================================
/* ==========================================================================
 * {$project.name}
 * Copyright (c) {$copyrightYear} {$project.author}
 * {$project.mail}
 * --------------------------------------------------------------------------
 * {$class.name|append('.cpp')|rpad(' ', 30)}  {$class.shortDesc}.
 * ==========================================================================
 * 
{include template/class/gpl-disclaimer.tpl} * 
 * ========================================================================== */

\#include "{if class.includeDir != ""}{$class.includeDir}/{/if}{$class.name}.hpp"{foreach inc in include.impl}
\#include {$inc}{/foreach}

{foreach ud in using}using {$ud};
{/foreach}{foreach ns in namespace}
namespace {$ns.name}
\{
{/foreach}{foreach st in struct}{foreach cn in st.constant}{first}
{/first}{single}
{/single}const {$cn.type} {$st.name}::{$cn.name} = {$cn.value};
{/foreach}{/foreach}{if class.createClassInfo == "true"}
{$class.name}ClassInfo::{$class.name}ClassInfo()
\{
	name = "{$class.name}";
	desc = "{$class.shortDesc}";
\}
{/if}{foreach var in variable.private}{if var.spec == "static"}{first}
{/first}{single}
{/single}static {$var.type} {$class.name}::{$var.name} = {$var.value};
{/if}{/foreach}{foreach var in variable.protected}{if var.spec == "static"}{first}
{/first}{single}
{/single}static {$var.type} {$class.name}::{$var.name} = {$var.value};
{/if}{/foreach}{foreach const in constant.private}{first}
{/first}{single}
{/single}const {$const.type} {$class.name}::{$const.name} = {$const.value};
{/foreach}{foreach const in constant.protected}{first}
{/first}{single}
{/single}const {$const.type} {$class.name}::{$const.name} = {$const.value};
{/foreach}{foreach const in constant.public}{first}
{/first}{single}
{/single}const {$const.type} {$class.name}::{$const.name} = {$const.value};
{/foreach}{if class.createClassInfo == "true"}
const {$class.name}ClassInfo {$class.name}::{$class.name|lowercase(1)}ClassInfo;
const ClassInfo* {$class.name}::CLASS_INFO = &{$class.name}::{$class.name|lowercase(1)}ClassInfo;
{/if}
{$class.name}::{$class.name}()
\{
	{if class.createClassInfo == "true"}// NOTE: The following line is required for class information.
	theClasses.push_back(CLASS_INFO);
	{/if}// TODO: Nothing ATM. ;-)
\}
{foreach con in constructor.public}
{swrap 75}{$class.name}::{$class.name}({foreach prm in con.param}{$prm.type} {$prm.name}{first}, {/first}{mid}, {/mid}{/foreach}){/swrap}
\{
	{if class.createClassInfo == "true"}// NOTE: The following line is required for class information.
	theClasses.push_back(CLASS_INFO);
	{/if}// TODO: Implementation.
\}
{/foreach}
{$class.name}::~{$class.name}()
\{
	{foreach prop in property.protected}{if ( prop.style == "vector" ) || ( prop.style == "map" )}clear{$prop.element.name|uppercase(1)}s();
	{else}{if prop.managed == "true"}if ({$prop.name} != 0)
		{$prop.name}->unref();
	{$prop.name} = 0;
	{/if}{/if}{/foreach}// TODO: Nothing ATM. ;-)
\}
{foreach func in function.private}{if func.pureVirtual != "true"}
{swrap 75}{$func.type} {$class.name}::{$func.name}({foreach prm in func.param}{$prm.type} {$prm.name}{first}, {/first}{mid}, {/mid}{/foreach}){if func.const == "true"} const{/if}{/swrap}
\{
{if func.impl == ""}	// TODO: Implementation.{else}{$func.impl|swrap(75,'	')}{/if}
{if func.return.value != ""}	return {$func.return.value};
{/if}\}
{/if}{/foreach}{foreach func in function.protected}{if func.pureVirtual != "true"}
{swrap 75}{$func.type} {$class.name}::{$func.name}({foreach prm in func.param}{$prm.type} {$prm.name}{first}, {/first}{mid}, {/mid}{/foreach}){if func.const == "true"} const{/if}{/swrap}
\{
{if func.impl == ""}	// TODO: Implementation.{else}{$func.impl|swrap(75,'	')}{/if}
{if func.return.value != ""}	return {$func.return.value};
{/if}\}
{/if}{/foreach}{foreach func in function.public}{if func.pureVirtual != "true"}
{swrap 75}{$func.type} {$class.name}::{$func.name}({foreach prm in func.param}{$prm.type} {$prm.name}{first}, {/first}{mid}, {/mid}{/foreach}){if func.const == "true"} const{/if}{/swrap}
\{
{if func.impl == ""}	// TODO: Implementation.{else}{$func.impl|swrap(75,'	')}{/if}
{if func.return.value != ""}	return {$func.return.value};
{/if}\}
{/if}{/foreach}{foreach prop in property.private}{if prop.style == "vector"}
{swrap 75}unsigned int {$class.name}::getNum{$prop.element.name|uppercase(1)}s() const{/swrap}
\{
	return {$prop.name}.size();
\}

{swrap 75}{$prop.element.type} {$class.name}::get{$prop.element.name|uppercase(1)}(unsigned int elementIndex) const{/swrap}
\{
	if (elementIndex < {$prop.name}.size())
		return {$prop.name}[elementIndex];
	return {if prop.element.defaultValue != ""}{$prop.element.defaultValue}{else}0{/if};
\}
{if prop.readOnly != "true"}
{swrap 75}std::vector<{$prop.element.type}>& {$class.name}::get{$prop.name|uppercase(1)}(){/swrap}
\{
	return {$prop.name};
\}

{swrap 75}void {$class.name}::add{$prop.element.name|uppercase(1)}({if prop.element.addType == ""}{$prop.element.type}{else}{$prop.element.addType}{/if} addElement){/swrap}
\{
	{if prop.element.managed == "true"}addElement->ref();
	{/if}{$prop.name}.push_back(addElement);
\}

{swrap 75}void {$class.name}::remove{$prop.element.name|uppercase(1)}({if prop.element.removeType == ""}{$prop.element.type}{else}{$prop.element.removeType}{/if} removeElement){/swrap}
\{
	bool found = false;
	{$prop.element.type} current{$prop.element.name|uppercase(1)} = {if prop.element.defaultValue != ""}{$prop.element.defaultValue}{else}0{/if};
	unsigned int i = 0;
	while (!found 
		&& (i < {$prop.name}.size()))
	\{
		current{$prop.element.name|uppercase(1)} = {$prop.name}[i];
		if (current{$prop.element.name|uppercase(1)} == removeElement)
			found = true;
		else
			i++;
	\}
	if (found)
	\{
		{$prop.name}.erase({$prop.name}.begin() + i);{if prop.element.managed == "true"}
		if (current{$prop.element.name|uppercase(1)} != {if prop.element.defaultValue != ""}{$prop.element.defaultValue}{else}0{/if})
			current{$prop.element.name|uppercase(1)}->unref();{/if}
	\}
\}

{swrap 75}void {$class.name}::clear{$prop.element.name|uppercase(1)}s(){/swrap}
\{
	{if prop.element.managed == "true"}std::vector<{$prop.element.type}>::iterator i;
	for (i = {$prop.name}.begin(); i != {$prop.name}.end(); i++)
		if (*i != {if prop.element.defaultValue != ""}{$prop.element.defaultValue}{else}0{/if})
			(*i)->unref();
	{/if}{$prop.name}.clear();
\}
{/if}{else}{if prop.style == "map"}
{swrap 75}unsigned int {$class.name}::getNum{$prop.element.name|uppercase(1)}s() const{/swrap}
\{
	return {$prop.name}.size();
\}

{swrap 75}{$prop.element.type} {$class.name}::get{$prop.element.name|uppercase(1)}({if prop.key.accessType != ""}{$prop.key.accessType}{else}{$prop.key.type}{/if} elementKey) const{/swrap}
\{
	std::map<{$prop.key.type}, {$prop.element.type}>::const_iterator i = {$prop.name}.find(elementKey);
	if (i != {$prop.name}.end())
		return (*i).second;
	return {if prop.element.defaultValue != ""}{$prop.element.defaultValue}{else}0{/if};
\}
{if prop.readOnly != "true"}
{swrap 75}std::map<{$prop.key.type}, {$prop.element.type}>& {$class.name}::get{$prop.name|uppercase(1)}(){/swrap}
\{
	return {$prop.name};
\}

{swrap 75}void {$class.name}::add{$prop.element.name|uppercase(1)}({if prop.key.accessType != ""}{$prop.key.accessType}{else}{$prop.key.type}{/if} elementKey, {if prop.element.addType == ""}{$prop.element.type}{else}{$prop.element.addType}{/if} addElement){/swrap}
\{
	{$prop.element.type} the{$prop.element.name|uppercase(1)} = get{$prop.element.name|uppercase(1)}(elementKey);
	if (the{$prop.element.name|uppercase(1)} != {if prop.element.defaultValue != ""}{$prop.element.defaultValue}{else}0{/if})
		return;
	{$prop.name}[elementKey] = addElement;{if prop.element.managed == "true"}
	addElement->ref();{/if}
\}

{swrap 75}void {$class.name}::remove{$prop.element.name|uppercase(1)}({if prop.key.accessType != ""}{$prop.key.accessType}{else}{$prop.key.type}{/if} elementKey){/swrap}
\{
	std::map<{$prop.key.type}, {$prop.element.type}>::iterator i = {$prop.name}.find(elementKey);
	if (i != {$prop.name}.end())
	\{
		{if prop.element.managed == "true"}if ((*i).second != {if prop.element.defaultValue != ""}{$prop.element.defaultValue}{else}0{/if})
			(*i).second->unref();
		{/if}{$prop.name}.erase(i);
	\}
\}

{swrap 75}void {$class.name}::clear{$prop.element.name|uppercase(1)}s(){/swrap}
\{
	{if prop.element.managed == "true"}std::map<{$prop.key.type}, {$prop.element.type}>::iterator i;
	for (i = {$prop.name}.begin(); i != {$prop.name}.end(); i++)
		if ((*i).second != {if prop.element.defaultValue != ""}{$prop.element.defaultValue}{else}0{/if})
			(*i).second->unref();
	{/if}{$prop.name}.clear();
\}
{/if}{else}{if prop.readOnly != "true"}
{swrap 75}void {$class.name}::set{$prop.name|uppercase(1)}({$prop.setFromType} new{$prop.name|uppercase(1)}){/swrap}
\{
	{if prop.managed == "true"}if ({$prop.name} == new{$prop.name|uppercase(1)})
		return;
	if ({$prop.name} != 0)
		{$prop.name}->unref();
	{/if}{$prop.name} = new{$prop.name|uppercase(1)};{if prop.managed == "true"}
	if ({$prop.name} != 0)
	\{
		{$prop.name}->ref();{if prop.poolName != ""}
		{$prop.poolName}.addObject({$prop.name});{/if}
	\}{/if}
\}
{/if}
{swrap 75}{$prop.type} {$class.name}::get{$prop.name|uppercase(1)}() const{/swrap}
\{
	return {$prop.name};
\}
{/if}{/if}{/foreach}{foreach prop in property.protected}{if prop.style == "vector"}
{swrap 75}unsigned int {$class.name}::getNum{$prop.element.name|uppercase(1)}s() const{/swrap}
\{
	return {$prop.name}.size();
\}

{swrap 75}{$prop.element.type} {$class.name}::get{$prop.element.name|uppercase(1)}(unsigned int elementIndex) const{/swrap}
\{
	if (elementIndex < {$prop.name}.size())
		return {$prop.name}[elementIndex];
	return {if prop.element.defaultValue != ""}{$prop.element.defaultValue}{else}0{/if};
\}
{if prop.readOnly != "true"}
{swrap 75}std::vector<{$prop.element.type}>& {$class.name}::get{$prop.name|uppercase(1)}(){/swrap}
\{
	return {$prop.name};
\}

{swrap 75}void {$class.name}::add{$prop.element.name|uppercase(1)}({if prop.element.addType == ""}{$prop.element.type}{else}{$prop.element.addType}{/if} addElement){/swrap}
\{
	{if prop.element.managed == "true"}addElement->ref();
	{/if}{$prop.name}.push_back(addElement);
\}

{swrap 75}void {$class.name}::remove{$prop.element.name|uppercase(1)}({if prop.element.removeType == ""}{$prop.element.type}{else}{$prop.element.removeType}{/if} removeElement){/swrap}
\{
	bool found = false;
	{$prop.element.type} current{$prop.element.name|uppercase(1)} = {if prop.element.defaultValue != ""}{$prop.element.defaultValue}{else}0{/if};
	unsigned int i = 0;
	while (!found 
		&& (i < {$prop.name}.size()))
	\{
		current{$prop.element.name|uppercase(1)} = {$prop.name}[i];
		if (current{$prop.element.name|uppercase(1)} == removeElement)
			found = true;
		else
			i++;
	\}
	if (found)
	\{
		{$prop.name}.erase({$prop.name}.begin() + i);{if prop.element.managed == "true"}
		if (current{$prop.element.name|uppercase(1)} != {if prop.element.defaultValue != ""}{$prop.element.defaultValue}{else}0{/if})
			current{$prop.element.name|uppercase(1)}->unref();{/if}
	\}
\}

{swrap 75}void {$class.name}::clear{$prop.element.name|uppercase(1)}s(){/swrap}
\{
	{if prop.element.managed == "true"}std::vector<{$prop.element.type}>::iterator i;
	for (i = {$prop.name}.begin(); i != {$prop.name}.end(); i++)
		if (*i != {if prop.element.defaultValue != ""}{$prop.element.defaultValue}{else}0{/if})
			(*i)->unref();
	{/if}{$prop.name}.clear();
\}
{/if}{else}{if prop.style == "map"}
{swrap 75}unsigned int {$class.name}::getNum{$prop.element.name|uppercase(1)}s() const{/swrap}
\{
	return {$prop.name}.size();
\}

{swrap 75}{$prop.element.type} {$class.name}::get{$prop.element.name|uppercase(1)}({if prop.key.accessType != ""}{$prop.key.accessType}{else}{$prop.key.type}{/if} elementKey) const{/swrap}
\{
	std::map<{$prop.key.type}, {$prop.element.type}>::const_iterator i = {$prop.name}.find(elementKey);
	if (i != {$prop.name}.end())
		return (*i).second;
	return {if prop.element.defaultValue != ""}{$prop.element.defaultValue}{else}0{/if};
\}
{if prop.readOnly != "true"}
{swrap 75}std::map<{$prop.key.type}, {$prop.element.type}>& {$class.name}::get{$prop.name|uppercase(1)}(){/swrap}
\{
	return {$prop.name};
\}

{swrap 75}void {$class.name}::add{$prop.element.name|uppercase(1)}({if prop.key.accessType != ""}{$prop.key.accessType}{else}{$prop.key.type}{/if} elementKey, {if prop.element.addType == ""}{$prop.element.type}{else}{$prop.element.addType}{/if} addElement){/swrap}
\{
	{$prop.element.type} the{$prop.element.name|uppercase(1)} = get{$prop.element.name|uppercase(1)}(elementKey);
	if (the{$prop.element.name|uppercase(1)} != {if prop.element.defaultValue != ""}{$prop.element.defaultValue}{else}0{/if})
		return;
	{$prop.name}[elementKey] = addElement;{if prop.element.managed == "true"}
	addElement->ref();{/if}
\}

{swrap 75}void {$class.name}::remove{$prop.element.name|uppercase(1)}({if prop.key.accessType != ""}{$prop.key.accessType}{else}{$prop.key.type}{/if} elementKey){/swrap}
\{
	std::map<{$prop.key.type}, {$prop.element.type}>::iterator i = {$prop.name}.find(elementKey);
	if (i != {$prop.name}.end())
	\{
		{if prop.element.managed == "true"}if ((*i).second != {if prop.element.defaultValue != ""}{$prop.element.defaultValue}{else}0{/if})
			(*i).second->unref();
		{/if}{$prop.name}.erase(i);
	\}
\}

{swrap 75}void {$class.name}::clear{$prop.element.name|uppercase(1)}s(){/swrap}
\{
	{if prop.element.managed == "true"}std::map<{$prop.key.type}, {$prop.element.type}>::iterator i;
	for (i = {$prop.name}.begin(); i != {$prop.name}.end(); i++)
		if ((*i).second != {if prop.element.defaultValue != ""}{$prop.element.defaultValue}{else}0{/if})
			(*i).second->unref();
	{/if}{$prop.name}.clear();
\}
{/if}{else}{if prop.readOnly != "true"}
{swrap 75}void {$class.name}::set{$prop.name|uppercase(1)}({$prop.setFromType} new{$prop.name|uppercase(1)}){/swrap}
\{
	{if prop.managed == "true"}if ({$prop.name} == new{$prop.name|uppercase(1)})
		return;
	if ({$prop.name} != 0)
		{$prop.name}->unref();
	{/if}{$prop.name} = new{$prop.name|uppercase(1)};{if prop.managed == "true"}
	if ({$prop.name} != 0)
	\{
		{$prop.name}->ref();{if prop.poolName != ""}
		{$prop.poolName}.addObject({$prop.name});{/if}
	\}{/if}
\}
{/if}
{swrap 75}{$prop.type} {$class.name}::get{$prop.name|uppercase(1)}() const{/swrap}
\{
	return {$prop.name};
\}
{/if}{/if}{/foreach}{foreach ns in namespace}
\}
{/foreach}
/** \\file {$class.name}.cpp
 * \\brief {$class.shortDesc} implementation.
 */
