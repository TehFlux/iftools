/* ==========================================================================
 * IFTemplate - Ionflux Template Processor
 * Copyright © 2012 Jörn P. Meier
 * mail@ionflux.org
 * --------------------------------------------------------------------------
 * TemplateRepository.i            Template repository (interface).
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
%{
#include "iftemplate/TemplateRepository.hpp"
%}

namespace Ionflux
{

namespace Template
{

class Node;

class TemplateRepositoryClassInfo
: public Ionflux::ObjectBase::IFClassInfo
{
    public:
        TemplateRepositoryClassInfo();
        virtual ~TemplateRepositoryClassInfo();
};

class TemplateRepository
: public Ionflux::Template::Tree
{
    public:
		static const Ionflux::Template::RepositoryEntryTypeID ENTRY_TYPE_FILE;
		static const Ionflux::Template::RepositoryEntryTypeID ENTRY_TYPE_DATA;
        
        TemplateRepository();
		TemplateRepository(const Ionflux::Template::TemplateRepository& other);
        virtual ~TemplateRepository();
        virtual void addTemplatePaths(const 
        Ionflux::ObjectBase::StringVector& newPaths);
        virtual void addTemplatePaths(const std::string& newPaths, const 
        std::string& separator = DEFAULT_TEMPLATE_PATH_SEP);
        virtual void addModule(const std::string& modulePath, 
        Ionflux::Template::RepositoryEntryTypeID typeID, const std::string&
        data);
        virtual void scanFile(Ionflux::Template::File& file, const 
        std::string& modulePrefix = "", bool addRootModule = false);
        virtual void scanPath(const std::string& dirPath);
        virtual void update();
        virtual void addTemplateData(const std::string& modulePath, const 
        std::string& templateData);
        virtual std::string getTemplateData(const std::string& modulePath, 
        bool removeTrailingNewLine = true);
        static std::string getModulePath(const std::string& modulePrefix, 
        const std::string& moduleName);
		virtual Ionflux::Template::TemplateRepository* copy() const;
		static Ionflux::Template::TemplateRepository* 
		upcast(Ionflux::ObjectBase::IFObject* other);
		static Ionflux::Template::TemplateRepository* 
		create(Ionflux::ObjectBase::IFObject* parentObject = 0);        
        virtual unsigned int getNumTemplatePaths() const;
        virtual std::string getTemplatePath(unsigned int elementIndex = 0) 
        const;
		virtual int findTemplatePath(const std::string& needle, unsigned int 
		occurence = 1) const;
        virtual std::vector<std::string>& getTemplatePaths();
        virtual void addTemplatePath(const std::string& addElement);        
        virtual void removeTemplatePath(std::string removeElement);
		virtual void removeTemplatePathIndex(unsigned int removeIndex);
		virtual void clearTemplatePaths();
};

}

}
