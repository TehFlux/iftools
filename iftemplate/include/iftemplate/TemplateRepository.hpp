#ifndef IONFLUX_TEMPLATE_TEMPLATEREPOSITORY
#define IONFLUX_TEMPLATE_TEMPLATEREPOSITORY
/* ==========================================================================
 * IFTemplate - Ionflux Template Processor
 * Copyright © 2012 Jörn P. Meier
 * mail@ionflux.org
 * --------------------------------------------------------------------------
 * TemplateRepository.hpp          Template repository (header).
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

#include "iftemplate/templatetypes.hpp"
#include "iftemplate/constants.hpp"
#include "iftemplate/Tree.hpp"

namespace Ionflux
{

namespace Template
{

class Node;

/// Class information for class TemplateRepository.
class TemplateRepositoryClassInfo
: public Ionflux::ObjectBase::IFClassInfo
{
	public:
		/// Constructor.
		TemplateRepositoryClassInfo();
		/// Destructor.
		virtual ~TemplateRepositoryClassInfo();
};

/** Template repository.
 * \ingroup iftemplate
 *
 * A repository of templates. A template can be requested from the 
 * repository by a qualified name, consisting of a sequence of identifiers 
 * separated by dots. Templates can be fetched either from a set of 
 * template paths or directly added to the repository.
 */
class TemplateRepository
: public Ionflux::Template::Tree
{
	private:
		
	protected:
		/// Template path vector.
		std::vector<std::string> templatePaths;
		
	public:
		/// Entry type: file.
		static const Ionflux::Template::RepositoryEntryTypeID ENTRY_TYPE_FILE;
		/// Entry type: data.
		static const Ionflux::Template::RepositoryEntryTypeID ENTRY_TYPE_DATA;
		/// Class information instance.
		static const TemplateRepositoryClassInfo templateRepositoryClassInfo;
		/// Class information.
		static const Ionflux::ObjectBase::IFClassInfo* CLASS_INFO;
		
		/** Constructor.
		 *
		 * Construct new TemplateRepository object.
		 */
		TemplateRepository();
		
		/** Constructor.
		 *
		 * Construct new TemplateRepository object.
		 *
		 * \param other Other object.
		 */
		TemplateRepository(const Ionflux::Template::TemplateRepository& other);
		
		/** Destructor.
		 *
		 * Destruct TemplateRepository object.
		 */
		virtual ~TemplateRepository();
		
		/** Add template paths.
		 *
		 * Add template paths from a vector of strings.
		 *
		 * \param newPaths template paths.
		 */
		virtual void addTemplatePaths(const Ionflux::ObjectBase::StringVector& 
		newPaths);
		
		/** Add template paths.
		 *
		 * Add template paths from a string.
		 *
		 * \param newPaths template paths.
		 * \param separator template path separator.
		 */
		virtual void addTemplatePaths(const std::string& newPaths, const 
		std::string& separator = DEFAULT_TEMPLATE_PATH_SEP);
		
		/** Add module.
		 *
		 * Add a template module at the specified path.
		 *
		 * \param modulePath module path.
		 * \param typeID entry type ID.
		 * \param data module data.
		 */
		virtual void addModule(const std::string& modulePath, 
		Ionflux::Template::RepositoryEntryTypeID typeID, const std::string& 
		data);
		
		/** Scan file.
		 *
		 * Scan a file for templates and add them to the repository. If the 
		 * file is a template file, it will be added to the repository at the 
		 * appropriate module path. If the file is a directory, its child 
		 * files will be scanned recursively for template files.
		 *
		 * \param file file.
		 * \param modulePrefix module prefix.
		 * \param addRootModule whether to add a module for the root directory.
		 */
		virtual void scanFile(Ionflux::Template::File& file, const std::string& 
		modulePrefix = "", bool addRootModule = false);
		
		/** Scan path.
		 *
		 * Recursively scan a directory path for templates and add them to the
		 * repository.
		 *
		 * \param dirPath directory path.
		 */
		virtual void scanPath(const std::string& dirPath);
		
		/** Update.
		 *
		 * Update the template repository. This scans all template directories
		 * and adds any templates that are found to the repository.
		 */
		virtual void update();
		
		/** Add template data.
		 *
		 * Add template data at the specified module path.
		 *
		 * \param modulePath module path.
		 * \param templateData templateData.
		 */
		virtual void addTemplateData(const std::string& modulePath, const 
		std::string& templateData);
		
		/** getTemplateData.
		 *
		 * Get template data for the specified module path.
		 *
		 * \param modulePath module path.
		 * \param removeTrailingNewLine remove trailing newlines on template file
		 * data.
		 *
		 * \return template data.
		 */
		virtual std::string getTemplateData(const std::string& modulePath, bool 
		removeTrailingNewLine = true);
		
		/** Get module path.
		 *
		 * Get a module path that consists of the path prefix, a module path 
		 * separator and the module name.
		 *
		 * \param modulePrefix module prefix.
		 * \param moduleName module name.
		 *
		 * \return module path.
		 */
		static std::string getModulePath(const std::string& modulePrefix, const 
		std::string& moduleName);
		
		/** Assignment operator.
		 *
		 * Assign an object.
		 *
		 * \param other Other object.
		 *
		 * \return The object itself.
		 */
		virtual Ionflux::Template::TemplateRepository& operator=(const 
		Ionflux::Template::TemplateRepository& other);
		
		/** Copy.
		 *
		 * Create a copy of the object.
		 *
		 * \return Newly allocated copy of the object.
		 */
		virtual Ionflux::Template::TemplateRepository* copy() const;
		
		/** Upcast.
		 *
		 * Cast an IFObject to the most specific type.
		 *
		 * \param other Other object.
		 *
		 * \return The more specific object, or 0 if the cast failed.
		 */
		static Ionflux::Template::TemplateRepository* 
		upcast(Ionflux::ObjectBase::IFObject* other);
		
		/** Create instance.
		 *
		 * Create a new instance of the class. If the optional parent object 
		 * is specified, a local reference for the new object will be added 
		 * to the parent object.
		 *
		 * \param parentObject Parent object.
		 *
		 * \return Pointer to the new instance.
		 */
		static Ionflux::Template::TemplateRepository* 
		create(Ionflux::ObjectBase::IFObject* parentObject = 0);
		
		/** Get allocated size in memory.
		 *
		 * Get the allocated size in memory for the object.
		 *
		 * \return The more specific object, or 0 if the cast failed.
		 */
		virtual unsigned int getMemSize() const;
		
		/** Get number of templatePaths.
		 *
		 * \return Number of templatePaths.
		 */
		virtual unsigned int getNumTemplatePaths() const;
		
		/** Get templatePath.
		 *
		 * Get the templatePath at the specified index.
		 *
		 * \param elementIndex Element index.
		 *
		 * \return TemplatePath at specified index.
		 */
		virtual std::string getTemplatePath(unsigned int elementIndex = 0) const;
		
		/** Find templatePath.
		 *
		 * Find the specified occurence of a templatePath.
		 *
		 * \param needle TemplatePath to be found.
		 * \param occurence Number of the occurence to be found.
		 *
		 * \return Index of the templatePath, or -1 if the templatePath cannot be
		 * found.
		 */
		virtual int findTemplatePath(const std::string& needle, unsigned int 
		occurence = 1) const;
        
		/** Get template path vector.
		 *
		 * \return template path vector.
		 */
		virtual std::vector<std::string>& getTemplatePaths();
		
		/** Add templatePath.
		 *
		 * Add a templatePath.
		 *
		 * \param addElement TemplatePath to be added.
		 */
		virtual void addTemplatePath(const std::string& addElement);
		
		/** Remove templatePath.
		 *
		 * Remove a templatePath.
		 *
		 * \param removeElement TemplatePath to be removed.
		 */
		virtual void removeTemplatePath(std::string removeElement);
		
		/** Remove templatePath.
		 *
		 * Remove a templatePath.
		 *
		 * \param removeIndex TemplatePath to be removed.
		 */
		virtual void removeTemplatePathIndex(unsigned int removeIndex);
		
		/** Clear templatePaths.
		 *
		 * Clear all templatePaths.
		 */
		virtual void clearTemplatePaths();
};

}

}

/** \file TemplateRepository.hpp
 * \brief Template repository (header).
 */
#endif
