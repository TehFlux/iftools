# Ionflux Tools
Copyright © 2004-2024 • Jörn Meier <webmaster@ionflux.org>

## README

### HERE BE DRAGONS!

**The Ionflux Tools Class Library contains mostly legacy code that will be integrated into the Ionflux Object Base System or moved to other libraries.**

**It is not recommended to use the Ionflux Tools at this point in time!**

**The build instructions may be outdated and incomplete and will not be updated!**

---

### What is it?

The Ionflux Tools Class Library is a lightweight multi-platform C++ framework. It features a set of useful classes and tools, such as a template engine and a universal hierarchical type.

### Licensing

Ionflux Tools Class Library is free software released under the [GNU General Public 
License version 3](docs/gpl-3.0.md).

**Please note that this program is distributed in the hope that it will be useful, but WITHOUT ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the GNU General Public License for more details.**

### Features

Features include:

+ Generic, serializable tree data structure.
+ Powerful template engine, usable as a library or a separate tool.
+ Logging/console output facility.
+ Command line parsing.
+ Configuration file I/O.
+ Database interface.
+ IO multiplexing.
+ Perl-compatible regular expression pattern matching.
+ String filters.
+ Advanced date and time handling (not restricted to the POSIX epoch, 
  supporting time zone conversions).
+ Generic string tokenizer (supports UTF-8).
+ TCP socket API.
+ Generic TCP client and server, message based client and server, and 
  authenticated client and server.
+ Miscellaneous helpful and easy to use utility functions.

Furthermore, the following tools are provided with the distribution:

+ ifdate A world clock and datetime conversion utility.
+ iftpl An easy-to-use template processor.
+ ifpasswd An SHA-1 based authentication file generator.
+ ifls A template based directory listing utility.

### Dependencies

Ionflux Tools uses the following libraries:

+ PCRE (Perl compatible regular expressions).
+ bzip2
+ mysql
+ Gtkmm (optional)

Ionflux Tools also uses the following external code:

+ Mersenne Twister randomizer class by Richard J. Wagner 
  (rjwagner@writeme.com, 
  http://www-personal.engin.umich.edu/~wagnerr/MersenneTwister.html);  
  based on code by Makoto Matsumoto, Takuji Nishimura, and Shawn Cokus 
  (matumoto@math.keio.ac.jp, Cokus@math.washington.edu, 
  http://www.math.sci.hiroshima-u.ac.jp/~m-mat/eindex.html).

+ FIPS-180-1 compliant SHA-1 implementation by Christophe Devine  
  (http://www.cr0.net:8040/code/crypto/sha1/).

Please refer to the extern directory of the distribution for detailed 
information and license.

### Build

To build, you need the [SCons](https://www.scons.org/) build system and the following libraries:

+ MySQL client
+ libbz2
+ PCRE (Perl Compatible Regular Expressions)
+ Gtkmm (optional)

If you do not want to build the Ionflux Tools Class Library with Gtkmm features, you can specify gtools=no after the build and install commands.

If you want to use custom configuration for the build process (for example, Python and library paths), copy `site_scons/local_config.py.default` to `site_scons/local_config.py` and 
adjust the settings as required.

You can then (on Linux and FreeBSD systems) build everything with:

`scons`

Type

`scons -h`

for a list of build options.

To install, type:

`scons install`

You must be root to install to default locations. If you want to install to a 
different directory (highly recommended), you can specify a prefix with:

`scons install prefix=<target directory>`

### WARNING
 
 It is not recommended at this point to install Ionflux Tools in a system directory, since this is an alpha version under development. (No harm should be done even if you decide otherwise, but there is no guarantee.)

 **This software is not intended for use in production environments! Ignore this warning at your own peril.**

### Using

**The Ionflux Tools Class Library contains mostly legacy code that will be integrated into the Ionflux Object Base System or moved to other libraries.**

**It is not recommended to use the Ionflux Tools at this point in time!**