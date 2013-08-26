#ifndef IONFLUX_TEMPLATE_FILE
#define IONFLUX_TEMPLATE_FILE
/* ==========================================================================
 * IFTemplate - Ionflux Template Processor
 * Copyright © 2012 Jörn P. Meier
 * mail@ionflux.org
 * --------------------------------------------------------------------------
 * File.hpp                        File (header).
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

#include <string>
#include <sys/stat.h>
#include "iftemplate/constants.hpp"
#include "iftemplate/types.hpp"
#include "ifobject/IFObject.hpp"

namespace Ionflux
{

namespace Template
{

/// Class information for class File.
class FileClassInfo
: public Ionflux::ObjectBase::IFClassInfo
{
	public:
		/// Constructor.
		FileClassInfo();
		/// Destructor.
		virtual ~FileClassInfo();
};

/** File.
 * \ingroup iftemplate
 *
 * A file on a filesystem.
 */
class File
: public Ionflux::ObjectBase::IFObject
{
	private:
		
	protected:
		/// Information returned by stat.
		struct stat statInfo;
		/// Validity flag.
		bool valid;
		/// File size.
		Ionflux::ObjectBase::UInt64 fileSize;
		/// Time of last access.
		time_t accessTime;
		/// Time of last modification.
		time_t modTime;
		/// Time of last change.
		time_t changeTime;
		/// File name.
		std::string name;
		/// File path.
		std::string path;
		/// Full name of file (including path).
		std::string fullName;
		/// Base name.
		std::string baseName;
		/// File name extension.
		std::string extension;
		/// Child file vector.
		std::vector<Ionflux::Template::File*> children;
		
		/** Update stat information.
		 *
		 * Update the file information obtained from \c stat.
		 *
		 * \return \c true on success, \c false otherwise.
		 */
		virtual bool updateStatInfo();
        
		/** Get child file vector.
		 *
		 * \return child file vector.
		 */
		virtual std::vector<Ionflux::Template::File*>& getFiles();
		
		/** Add file.
		 *
		 * Add a file.
		 *
		 * \param addElement File to be added.
		 */
		virtual void addFile(Ionflux::Template::File* addElement);
		
		/** Create file.
		 *
		 * Create a new file which is managed by the file set.
		 *
		 * \return New file.
		 */
		virtual Ionflux::Template::File* addFile();
		
		/** Add files.
		 *
		 * Add files from a file vector.
		 *
		 * \param newFiles files.
		 */
		virtual void addFiles(std::vector<Ionflux::Template::File*>& newFiles);
		
		/** Add files.
		 *
		 * Add files from a file set.
		 *
		 * \param newFiles files.
		 */
		virtual void addFiles(Ionflux::Template::File* newFiles);
		
		/** Remove file.
		 *
		 * Remove a file.
		 *
		 * \param removeElement File to be removed.
		 */
		virtual void removeFile(Ionflux::Template::File* removeElement);
		
		/** Remove file.
		 *
		 * Remove a file.
		 *
		 * \param removeIndex File to be removed.
		 */
		virtual void removeFileIndex(unsigned int removeIndex);
		
		/** Clear files.
		 *
		 * Clear all files.
		 */
		virtual void clearFiles();
		
	public:
		/// Class information instance.
		static const FileClassInfo fileClassInfo;
		/// Class information.
		static const Ionflux::ObjectBase::IFClassInfo* CLASS_INFO;
		
		/** Constructor.
		 *
		 * Construct new File object.
		 */
		File();
		
		/** Constructor.
		 *
		 * Construct new File object.
		 *
		 * \param other Other object.
		 */
		File(const Ionflux::Template::File& other);
		
		/** Constructor.
		 *
		 * Construct new File object.
		 *
		 * \param initFullName Full name of file (including path).
		 */
		File(const std::string& initFullName);
		
		/** Destructor.
		 *
		 * Destruct File object.
		 */
		virtual ~File();
		
		/** Update file information.
		 *
		 * Update the information record for this file.
		 */
		virtual void update();
		
		/** Check validity.
		 *
		 * Check whether the file is valid.
		 *
		 * \return \c true if the file is valid, \c false otherwise.
		 */
		virtual bool isValid() const;
		
		/** Get directory status.
		 *
		 * Check whether the file is a directory.
		 *
		 * \return \c true if the file is a directory, \c false otherwise.
		 */
		virtual bool isDir() const;
		
		/** Read directory.
		 *
		 * If this file is a directory, read the directory contents. This adds
		 * one child file per contained file to the file object. If \c 
		 * recursive is set to \c true, a hierarchy of files is generated. The
		 * \c maxDepth parameter can be used to limit the recursion depth.
		 *
		 * \param recursive read directories recursively.
		 * \param maxDepth maximum recursion depth.
		 * \param depth current depth.
		 */
		virtual void readDir(bool recursive = false, unsigned int maxDepth = 0, 
		unsigned int depth = 0);
		
		/** Get string representation of value.
		 *
		 * Get a string representation of the value of the object.
		 *
		 * \return String representation.
		 */
		virtual std::string getValueString() const;
		
		/** Assignment operator.
		 *
		 * Assign an object.
		 *
		 * \param other Other object.
		 *
		 * \return The object itself.
		 */
		virtual Ionflux::Template::File& operator=(const Ionflux::Template::File&
		other);
		
		/** Copy.
		 *
		 * Create a copy of the object.
		 *
		 * \return Newly allocated copy of the object.
		 */
		virtual Ionflux::Template::File* copy() const;
		
		/** Upcast.
		 *
		 * Cast an IFObject to the most specific type.
		 *
		 * \param other Other object.
		 *
		 * \return The more specific object, or 0 if the cast failed.
		 */
		static Ionflux::Template::File* upcast(Ionflux::ObjectBase::IFObject* 
		other);
		
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
		static Ionflux::Template::File* create(Ionflux::ObjectBase::IFObject* 
		parentObject = 0);
        
		/** Create instance.
		 *
		 * Create a new File object.
		 *
		 * \param initFullName Full name of file (including path).
		 * \param parentObject Parent object.
		 */
		static Ionflux::Template::File* create(const std::string& initFullName, 
		Ionflux::ObjectBase::IFObject* parentObject = 0);
		
		/** Get file size.
		 *
		 * \return Current value of file size.
		 */
		virtual Ionflux::ObjectBase::UInt64 getFileSize() const;
		
		/** Get time of last access.
		 *
		 * \return Current value of time of last access.
		 */
		virtual time_t getAccessTime() const;
		
		/** Get time of last modification.
		 *
		 * \return Current value of time of last modification.
		 */
		virtual time_t getModTime() const;
		
		/** Get time of last change.
		 *
		 * \return Current value of time of last change.
		 */
		virtual time_t getChangeTime() const;
		
		/** Get file name.
		 *
		 * \return Current value of file name.
		 */
		virtual std::string getName() const;
		
		/** Set file name.
		 *
		 * Set new value of file name.
		 *
		 * \param newName New value of file name.
		 */
		virtual void setName(const std::string& newName);
		
		/** Get file path.
		 *
		 * \return Current value of file path.
		 */
		virtual std::string getPath() const;
		
		/** Set file path.
		 *
		 * Set new value of file path.
		 *
		 * \param newPath New value of file path.
		 */
		virtual void setPath(const std::string& newPath);
		
		/** Get full name of file (including path).
		 *
		 * \return Current value of full name of file (including path).
		 */
		virtual std::string getFullName() const;
		
		/** Set full name of file (including path).
		 *
		 * Set new value of full name of file (including path).
		 *
		 * \param newFullName New value of full name of file (including path).
		 */
		virtual void setFullName(const std::string& newFullName);
		
		/** Get base name.
		 *
		 * \return Current value of base name.
		 */
		virtual std::string getBaseName() const;
		
		/** Get file name extension.
		 *
		 * \return Current value of file name extension.
		 */
		virtual std::string getExtension() const;
		
		/** Get number of files.
		 *
		 * \return Number of files.
		 */
		virtual unsigned int getNumFiles() const;
		
		/** Get file.
		 *
		 * Get the file at the specified index.
		 *
		 * \param elementIndex Element index.
		 *
		 * \return File at specified index.
		 */
		virtual Ionflux::Template::File* getFile(unsigned int elementIndex = 0) 
		const;
		
		/** Find file.
		 *
		 * Find the specified occurence of a file.
		 *
		 * \param needle File to be found.
		 * \param occurence Number of the occurence to be found.
		 *
		 * \return Index of the file, or -1 if the file cannot be found.
		 */
		virtual int findFile(Ionflux::Template::File* needle, unsigned int 
		occurence = 1) const;
};

}

}

/** \file File.hpp
 * \brief File (header).
 */
#endif
