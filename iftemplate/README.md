# IFTemplate - Ionflux Template Processor
Copyright © 2012-2013 • Jörn Meier <webmaster@ionflux.org>

## README

### What is it?

The Ionflux Template Processor (IFTemplate)) is a template processing library. It also provides a generic Node type that can be used for specifying input data for the template engine.

IFTemplate can be linked into other programs as a dynamic library, or used as a standalone command line template processor.

Using SWIG, bindings for a large variety of programming languages can be created for the C++ library. The package currently supports Python, but it should not be too hard to generate bindings for other languages as well.

### Licensing

The Ionflux Template Processor is free software released under the [GNU General Public 
License version 3](docs/gpl-3.0.md).

**Please note that this program is distributed in the hope that it will be 
useful, but WITHOUT ANY WARRANTY; without even the implied warranty of 
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the GNU General 
Public License for more details.**

### Dependencies

IFTemplate depends on the following packages:

+ Ionflux Object Base System  
  This is provided in the iftools git repository (see below).

The following dependencies are optional:

+ [Python](https://www.python.org/) >= 3.3  
  required for the Python bindings

Make sure you get a recent Git version of Ionflux Object Base System. Older packages will most likely not work.

You can checkout the recent source code from GitHub like this:

`git clone git@github.com:TehFlux/iftools.git`

### Building

Build all of the dependencies before you try to build IFTemplate. There 
are build instructions included with the individual projects.

IFTemplate uses [Scons](http://www.scons.org/) as the build system.

If you want to use custom configuration for the build process (for 
example, Python and library paths), copy `site_scons/local_config.py.default` to `site_scons/local_config.py` and adjust the settings as required.

It is recommended to use a [virtualenv](https://virtualenv.pypa.io/en/latest/) for the Python components of IFTemplate.

You can easily create a virtualenv with e.g. `virtualenv iftools_env` in a directory of your choice and then configure the build process to use this virtualenv for installation in `site_scons/local_config.py`.

Enable the virtualenv using `source <path to virtualenv>/bin/activate`.

When not installing to a system location (which is highly recommended), it is also recommended to set up an environment with all of the required paths for development in `scripts/profile-local.sh`. You can use one of the provided templates to get started.

This environment can then be used with `source scripts/profile-local.sh`.

If everything is set up correctly, you can build the project by running 

`scons`

in the main directory.

Install with

`scons install prefix=<installation base directory>`

where <installation base directory> ist the directory where the Ionflux Object Base System should be installed.

### WARNING
 
 It is not recommended at this point to install the Ionflux Template Processor in a system directory, since this is an alpha version under development. (No harm should be done even if you decide otherwise, but there is no guarantee.)

 **This software is not intended for use in production environments! Ignore this warning at your own peril.**

### Notes

The source files for all of the classes of the Ionflux Template Processor (iftemplate) can be generated from class configuration files using the ifclassgen and iftpl tools, which are part of the distribution. To avoid a circular dependency, iftemplate can be built from the pre-generated source files that are part of the distribution. The build process will 
skip generating the source files if iftpl or ifclassgen are not available.

Care must be taken if libifobject has changed and ifclassgen and iftpl require re-linking. In this case, `scons bootstrap` can be used to rebuild iftemplate without generating the source files.

### Using

This library is intended for developers, so you should be able to derive how it is meant to be used from the source code documentation and the scripts in the 'test' directory. If you have any questions, you can still contact me by mail.

**Enjoy!**