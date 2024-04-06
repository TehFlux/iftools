# Ionflux Object Base System
Copyright © 2006-2024 • Jörn Meier <webmaster@ionflux.org>

## README

### What is it?

The Ionflux Object Base System (IFObject) is a small library which provides a framework for developing object oriented software in C++. It is intended to be the foundation of a modular re-implementation of the Ionflux Tools Class Library. New classes based on the framework can be created easily using templates and configuration files.

See [specification](misc/spec.md) for an overview of features which will be provided by the Ionflux Tools Object Base System.

### Licensing

The Ionflux Object Base System is free software released under the [GNU General Public 
License version 3](docs/gpl-3.0.md).

**Please note that this program is distributed in the hope that it will be useful, but WITHOUT ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the GNU General Public License for more details.**

### Dependencies

To build the Ionflux Object Base System, the following dependencies must be installed on your target system:

+ [SCons](http://www.scons.org/)
+ [libsigc++](http://libsigc.sourceforge.net/)
+ pthread
+ [tinyxml](http://www.grinninglizard.com/tinyxml/)  
  A version suitable for use with ifobject, including Scons build scripts for a dynamic library, is included in the IFObject repository.

The following dependencies are optional, but highly recommended:

+ [Python](https://www.python.org/) >= 3.3  
  required for the Python bindings
+ Ionflux Template Processor (IFTemplate)  
  Required to build the source files from the class configuration (see notes). This is provided in the iftools git repository (see below).

Make sure you get a recent Git version of Ionflux Template Processor. Older packages will most likely not work.

You can checkout the recent source code from GitHub like this:

`git clone git@github.com:TehFlux/iftools.git`

### Building

IFObject uses [Scons](http://www.scons.org/) as the build system.

If you want to use custom configuration for the build process (for example, Python and ibrary paths), copy `site_scons/local_config.py.default` to `site_scons/local_config.py` and adjust the settings as required.

It is recommended to use a [virtualenv](https://virtualenv.pypa.io/en/latest/) for the Python components of IFTemplate.

You can easily create a virtualenv with e.g. `virtualenv iftools_env` in a directory of your choice and then configure the build process to use this virtualenv for installation in `site_scons/local_config.py`.

Enable the virtualenv using `source <path to virtualenv>/bin/activate`.

When not installing to a system location (which is highly recommended), it is also ecommended to set up an environment with all of the required paths for development in `scripts/profile-local.sh`. You can use one of the provided templates to get started.

This environment can then be used with `source scripts/profile-local.sh`.

If everything is set up correctly, you can build the project by running 

`scons`

Install with

`scons install prefix=<installation base directory>`

where <installation base directory> ist the directory where the Ionflux Object Base System should be installed.

### WARNING
 
 It is not recommended at this point to install the Ionflux Object Base System in a system directory, since this is an alpha version under development. (No harm should be done even if you decide otherwise, but there is no guarantee.)

 **This software is not intended for use in production environments! Ignore this warning at your own peril.**

### Notes

The source files for all of the classes of the Ionflux Object Base System can be generated from class configuration files using the ifclassgen and iftpl tools which are part of Ionflux Template Processor, which in turn is based on the Ionflux Object Base System (ifobject).

To avoid a circular dependency, ifobject can be built from the pre-generated source files that are part of the distribution. The build process will skip generating the source files if iftpl or ifclassgen are not available.

Care must be taken if libifobject has changed and ifclassgen and iftpl require re-linking. In this case, 'scons bootstrap' can be used to rebuild ifobject without generating the source files.

### Using

This library is intended for developers, so you should be able to derive how it is meant to be used from the source code documentation and the scripts in the `test` directory. If you have any questions, you can still contact me by mail.

**Enjoy!**