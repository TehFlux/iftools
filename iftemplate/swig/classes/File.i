/* ==========================================================================
 * IFTemplate - Ionflux Template Processor
 * Copyright © 2012 Jörn P. Meier
 * mail@ionflux.org
 * --------------------------------------------------------------------------
 * File.i                          File (interface).
 * =========================================================================

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
#include "iftemplate/File.hpp"
%}

namespace Ionflux
{

namespace Template
{

class FileClassInfo
: public Ionflux::ObjectBase::IFClassInfo
{
    public:
        FileClassInfo();
        virtual ~FileClassInfo();
};

class File
: public Ionflux::ObjectBase::IFObject
{
    public:
        
        File();
		File(const Ionflux::Template::File& other);
        File(const std::string& initFullName);
        virtual ~File();
        virtual void update();
        virtual bool isValid() const;
        virtual bool isDir() const;
        virtual void readDir(bool recursive = false, unsigned int maxDepth 
        = 0, unsigned int depth = 0);
        virtual std::string getValueString() const;
		virtual Ionflux::Template::File* copy() const;
		static Ionflux::Template::File* upcast(Ionflux::ObjectBase::IFObject* 
		other);
		static Ionflux::Template::File* create(Ionflux::ObjectBase::IFObject* 
		parentObject = 0);
		static Ionflux::Template::File* create(const std::string& initFullName, 
		Ionflux::ObjectBase::IFObject* parentObject = 0);
        virtual Ionflux::ObjectBase::UInt64 getFileSize() const;
        virtual time_t getAccessTime() const;
        virtual time_t getModTime() const;
        virtual time_t getChangeTime() const;
        virtual void setName(const std::string& newName);
        virtual std::string getName() const;
        virtual void setPath(const std::string& newPath);
        virtual std::string getPath() const;
        virtual void setFullName(const std::string& newFullName);
        virtual std::string getFullName() const;
        virtual std::string getBaseName() const;
        virtual std::string getExtension() const;        
        virtual unsigned int getNumFiles() const;
        virtual Ionflux::Template::File* getFile(unsigned int elementIndex 
        = 0) const;
		virtual int findFile(Ionflux::Template::File* needle, unsigned int 
		occurence = 1) const;
};

}

}
