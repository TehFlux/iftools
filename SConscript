# ==========================================================================
# Ionflux Tools
# Copyright (c) 2004 Joern P. Meier
# mail@ionflux.org
# --------------------------------------------------------------------------
# SConscript                  SCons build script
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

import os

Help("""
Type 'scons' to build the default targets.
Type 'scons install' to install to default location.
Type 'scons <target>' to build a specific target.

Targets:
  (default)                    Library and tools.
  all                          Library, tools and tests.
  test                         Library and tests.
  install                      Install library and tools.

Options:
  prefix=<target directory>    Installation prefix.
                               (default: /usr/local)
  platform=<platform>          Platform which to build for (valid values 
                               currently are linux, freebsd and win32).
							   (default: linux)
  debug=<yes|no>               Whether to use debug compiler flags. 
                               (default: yes)
  gtools=<yes|no>              Whether to build the Glib tools (default: yes).
""")

platform = ARGUMENTS.get('platform', 'linux')
prefix = ARGUMENTS.get('prefix', '/usr/local')
debug =  ARGUMENTS.get('debug', 'yes')
gtools = ARGUMENTS.get('gtools', 'yes')

if (debug == 'yes'):
    debugFlags = ['-g']
else:
    debugFlags = []

BuildDir('build', 'src')
BuildDir('build/ionflux', 'src/ionflux')
BuildDir('test/build', 'test')

toolsSources = ['extern/sha1/sha1.cpp',
	 'build/ionflux/tools.cpp',
	 'build/ionflux/ClassInfo.cpp',
	 'build/ionflux/Object.cpp',
	 'build/ionflux/Reporter.cpp',
	 'build/ionflux/RegExp.cpp',
	 'build/ionflux/Database.cpp',
	 'build/ionflux/MySQLDatabase.cpp',
	 'build/ionflux/TokenTypeMap.cpp',
	 'build/ionflux/Tokenizer.cpp',
	 'build/ionflux/Utf8TokenTypeMap.cpp',
	 'build/ionflux/Utf8Tokenizer.cpp',
	 'build/ionflux/StringFilter.cpp',
	 'build/ionflux/StringManipulator.cpp',
	 'build/ionflux/DateTime.cpp',
	 'build/ionflux/TimeZone.cpp',
	 'build/ionflux/Node.cpp',
	 'build/ionflux/Tree.cpp',
	 'build/ionflux/NodeReference.cpp',
	 'build/ionflux/TreeResolver.cpp',
	 'build/ionflux/TreeEval.cpp',
	 'build/ionflux/Config.cpp',
	 'build/ionflux/ConfigMap.cpp',
	 'build/ionflux/ConfigTree.cpp',
	 'build/ionflux/Template.cpp',
	 'build/ionflux/CLArgs.cpp',
	 'build/ionflux/TCPSocket.cpp',
	 'build/ionflux/TCPRemotePeer.cpp',
	 'build/ionflux/TCPClient.cpp',
	 'build/ionflux/TCPServer.cpp',
	 'build/ionflux/TCPMessageClient.cpp',
	 'build/ionflux/TCPMessageServer.cpp',
	 'build/ionflux/TCPAuthClient.cpp',
	 'build/ionflux/TCPAuthServer.cpp',
	 'build/ionflux/FDSet.cpp',
	 'build/ionflux/AuthFile.cpp',
	 'build/ionflux/Message.cpp',
	 'build/ionflux/IOHandler.cpp',
	 'build/ionflux/IOMultiplexer.cpp',
	 'build/ionflux/SelectMultiplexer.cpp',
	 'build/ionflux/ManagedObject.cpp',
	 'build/ionflux/ObjectPool.cpp',
	 'build/ionflux/BufferedTable.cpp',
	 'build/ionflux/File.cpp',
	 'build/ionflux/EMailAddress.cpp',
	 'build/ionflux/color.cpp',
	 'build/ionflux/Vector3.cpp',
	 'build/ionflux/Matrix3.cpp',
	 'build/ionflux/Canvas.cpp']

toolsHeaders = ['extern/sha1/sha1.h',
    'extern/Mersenne/MersenneTwister.h',
    'include/ionflux/ClassInfo.hpp',
    'include/ionflux/Object.hpp',
    'include/ionflux/AuthFile.hpp',
    'include/ionflux/Auth.hpp',
    'include/ionflux/ByteDump.hpp',
    'include/ionflux/CLArgs.hpp',
    'include/ionflux/Config.hpp',
    'include/ionflux/ConfigMap.hpp',
    'include/ionflux/ConfigTree.hpp',
    'include/ionflux/Database.hpp',
    'include/ionflux/DateTime.hpp',
    'include/ionflux/FDSet.hpp',
    'include/ionflux/IOHandler.hpp',
    'include/ionflux/IOMultiplexer.hpp',
    'include/ionflux/MessageDump.hpp',
    'include/ionflux/Message.hpp',
    'include/ionflux/MessageHandler.hpp',
    'include/ionflux/MySQLDatabase.hpp',
    'include/ionflux/NodeDump.hpp',
    'include/ionflux/Node.hpp',
    'include/ionflux/NodeReference.hpp',
    'include/ionflux/RegExp.hpp',
    'include/ionflux/Reporter.hpp',
    'include/ionflux/SelectMultiplexer.hpp',
    'include/ionflux/StringFilter.hpp',
    'include/ionflux/StringManipulator.hpp',
    'include/ionflux/TCPAuthClient.hpp',
    'include/ionflux/TCPAuthServer.hpp',
    'include/ionflux/TCPClient.hpp',
    'include/ionflux/TCPMessageClient.hpp',
    'include/ionflux/TCPMessageServer.hpp',
    'include/ionflux/TCPRemotePeer.hpp',
    'include/ionflux/TCPServer.hpp',
    'include/ionflux/TCPSocket.hpp',
    'include/ionflux/Template.hpp',
    'include/ionflux/TimeZone.hpp',
    'include/ionflux/Tokenizer.hpp',
    'include/ionflux/TokenTypeMap.hpp',
    'include/ionflux/Utf8TokenTypeMap.hpp',
    'include/ionflux/Utf8Tokenizer.hpp',
    'include/ionflux/tools.hpp',
    'include/ionflux/Tree.hpp',
    'include/ionflux/TreeResolver.hpp',
	'include/ionflux/TreeEval.hpp',
	'include/ionflux/ManagedObject.hpp',
	'include/ionflux/ObjectPool.hpp',
	'include/ionflux/BufferedTable.hpp',
	'include/ionflux/File.hpp',
	'include/ionflux/EMailAddress.hpp',
	'include/ionflux/color.hpp',
	'include/ionflux/Vector3.hpp',
	'include/ionflux/Matrix3.hpp',
	'include/ionflux/Canvas.hpp']

gtoolsSources = ['build/ionflux/GlibMultiplexer.cpp',
    'build/ionflux/CairoContext.cpp',
	'build/ionflux/CairoMatrix.cpp',
	'build/ionflux/CairoPattern.cpp',
	'build/ionflux/CairoSolidPattern.cpp',
	'build/ionflux/CairoSurfacePattern.cpp',
	'build/ionflux/CairoGradient.cpp',
	'build/ionflux/CairoLinearGradient.cpp',
	'build/ionflux/CairoRadialGradient.cpp',
	'build/ionflux/CairoSurface.cpp',
	'build/ionflux/CairoImageSurface.cpp',
	'build/ionflux/CairoPathData.cpp',
	'build/ionflux/CairoPathIterator.cpp',
	'build/ionflux/CairoPath.cpp',
	'build/ionflux/CairoCanvas.cpp',
	'build/ionflux/GtkCairoArea.cpp']

gtoolsHeaders = ['include/ionflux/GlibMultiplexer.hpp',
    'include/ionflux/CairoContext.hpp',
	'include/ionflux/CairoMatrix.hpp',
	'include/ionflux/CairoPattern.hpp',
	'include/ionflux/CairoSolidPattern.hpp',
	'include/ionflux/CairoSurfacePattern.hpp',
	'include/ionflux/CairoGradient.hpp',
	'include/ionflux/CairoLinearGradient.hpp',
	'include/ionflux/CairoRadialGradient.hpp',
	'include/ionflux/CairoSurface.hpp',
	'include/ionflux/CairoImageSurface.hpp',
	'include/ionflux/CairoPathData.hpp',
	'include/ionflux/CairoPathIterator.hpp',
	'include/ionflux/CairoPath.hpp',
	'include/ionflux/CairoCanvas.hpp',
	'include/ionflux/GtkCairoArea.hpp']

if (platform == 'linux'):
	# Build flags for Linux systems
	cxx = 'g++'
	ccflags = []
	cpppath = ['include',
	           'extern/sha1',
			   'extern/Mersenne']
	libs = []
	libpath = ['/usr/local/lib/mysql']
	libsock = []
	libmysql = ['mysqlclient']
	libssl = ['ssl']
	libwinmm = []
	libpthread = ['pthread']
	libext = ".so"
elif (platform == 'freebsd'):
	# Build flags for FreeBSD systems
	cxx = 'g++34'
	ccflags = ['-pthread', '-DHAVE_INTTYPES']
	cpppath = ['include',
	           'extern/sha1',
			   'extern/Mersenne',
			   '/usr/local/include']
	libs = []
	libpath = ['/usr/local/lib/mysql']
	libsock = []
	libmysql = ['mysqlclient']
	libssl = ['ssl']
	libwinmm = []
	libpthread = ['c_r']
	libext = ".so"
elif (platform == 'win32'):
	# Build flags for Windows systems 
	cxx = 'g++'
	ccflags = ['-DHAVE_WINSOCK', 
               '-DHAVE_WIN32_SLEEP',
			   '-DNO_LOCALTIME_R',
			   '-DNO_FORK']
	cpppath = ['include',
	           'extern/sha1',
			   'extern/Mersenne',
	           'C:/Dev-Cpp/include',
	           'C:/Dev-Cpp/include/c++',
			   'C:/Dev-Cpp/include/c++/mingw32',
			   'C:/Dev-Cpp/include/c++/backward',
			   'C:/Dev-Cpp/include']
	libs = []
	libpath = ['C:/Dev-Cpp/lib']
	libsock = ['wsock32']
	libmysql = ['mySQL']
	libssl = ['ssl32', 'eay32']
	libwinmm = ['winmm']
	libpthread = ['pthreadGC']
	libext = ".dll"

if (gtools == "yes"):
	gtkmmccflags = Split(os.popen('pkg-config --cflags gtkmm-2.4').read())
	gtkmmlibs = Split(os.popen('pkg-config --libs-only-l gtkmm-2.4').read())
	gtkmmlibpath = Split(os.popen('pkg-config --libs-only-L gtkmm-2.4').read())
	cairoccflags = Split(os.popen('pkg-config --cflags cairo').read())
	cairolibs = Split(os.popen('pkg-config --libs-only-l cairo').read())
	cairolibpath = Split(os.popen('pkg-config --libs-only-L cairo').read())
else:
    gtkmmccflags = []
    gtkmmlibs = []
    gtkmmlibpath = []
    cairoccflags = []
    cairolibs = []
    cairolibpath = []

mainccflags = ['-Wall',
    '-Wno-deprecated',
    '-pedantic',
    '-O3'] + debugFlags + ccflags

toolsenv = Environment(
    CXX = cxx,
    CCFLAGS = mainccflags)

toolsLib = toolsenv.SharedLibrary('lib/libiftools',
    toolsSources,
	CPPPATH = cpppath,
	LIBS = ['bz2', 'pcre'] + libmysql + libsock,
	LIBPATH = ['lib'] + libpath)

gtoolsLib = toolsenv.SharedLibrary('lib/libifgtools',
    gtoolsSources,
    CCFLAGS = mainccflags + gtkmmccflags + cairoccflags,
	CPPPATH = cpppath,
	LIBS = ['iftools'] + gtkmmlibs + cairolibs,
	LIBPATH = ['lib'] + libpath + gtkmmlibpath + cairolibpath)

buildToolsLib = ['lib/libiftools' + libext]
buildGToolsLib = ['lib/libifgtools' + libext]

if (gtools == "no"):
    buildLibs = buildToolsLib
else:
    buildLibs = buildToolsLib + buildGToolsLib

iftplBin = toolsenv.Program('bin/iftpl',
	['build/iftpl.cpp'],
	CPPPATH = cpppath,
	LIBS = ['iftools'] + libs,
	LIBPATH = ['lib'] + libpath)
ifpasswdBin = toolsenv.Program('bin/ifpasswd',
	['build/ifpasswd.cpp'],
	CPPPATH = cpppath,
	LIBS = ['iftools'] + libs,
	LIBPATH = ['lib'] + libpath)
ifdateBin = toolsenv.Program('bin/ifdate',
	['build/ifdate.cpp'],
	CPPPATH = cpppath,
	LIBS = ['iftools'] + libs,
	LIBPATH = ['lib'] + libpath)
iflsBin = toolsenv.Program('bin/ifls',
	['build/ifls.cpp'],
	CPPPATH = cpppath,
	LIBS = ['iftools'] + libs,
	LIBPATH = ['lib'] + libpath)

buildBin = ['bin/iftpl',
    'bin/ifpasswd',
	'bin/ifdate',
	'bin/ifls']

tokenizerTest = toolsenv.Program('test/bin/tokenizer',
	['test/build/tokenizer.cpp'],
	CPPPATH = cpppath,
	LIBS = ['iftools'] + libs,
	LIBPATH = ['lib'] + libpath)
stringfilterTest = toolsenv.Program('test/bin/stringfilter',
	['test/build/stringfilter.cpp'],
	CPPPATH = cpppath,
	LIBS = ['iftools'] + libs,
	LIBPATH = ['lib'] + libpath)
datetimeTest = toolsenv.Program('test/bin/datetime',
	['test/build/datetime.cpp'],
	CPPPATH = cpppath,
	LIBS = ['iftools'] + libs,
	LIBPATH = ['lib'] + libpath)
treeTest = toolsenv.Program('test/bin/tree',
	['test/build/tree.cpp'],
	CPPPATH = cpppath,
	LIBS = ['iftools'] + libs,
	LIBPATH = ['lib'] + libpath)
treeresolverTest = toolsenv.Program('test/bin/treeresolver',
	['test/build/treeresolver.cpp'],
	CPPPATH = cpppath,
	LIBS = ['iftools'] + libs,
	LIBPATH = ['lib'] + libpath)
configtreeTest = toolsenv.Program('test/bin/configtree',
	['test/build/configtree.cpp'],
	CPPPATH = cpppath,
	LIBS = ['iftools'] + libs,
	LIBPATH = ['lib'] + libpath)
templateTest = toolsenv.Program('test/bin/template',
	['test/build/template.cpp'],
	CPPPATH = cpppath,
	LIBS = ['iftools'] + libs,
	LIBPATH = ['lib'] + libpath)
bz2compressTest = toolsenv.Program('test/bin/bz2compress',
	['test/build/bz2compress.cpp'],
	CPPPATH = cpppath,
	LIBS = ['iftools'] + libs,
	LIBPATH = ['lib'] + libpath)
packTest = toolsenv.Program('test/bin/pack',
	['test/build/pack.cpp'],
	CPPPATH = cpppath,
	LIBS = ['iftools'] + libs,
	LIBPATH = ['lib'] + libpath)
clargsTest = toolsenv.Program('test/bin/clargs',
	['test/build/clargs.cpp'],
	CPPPATH = cpppath,
	LIBS = ['iftools'] + libs,
	LIBPATH = ['lib'] + libpath)
tcpserverTest = toolsenv.Program('test/bin/tcpserver',
	['test/build/tcpserver.cpp'],
	CPPPATH = cpppath,
	LIBS = ['iftools'] + libs,
	LIBPATH = ['lib'] + libpath)
echoserverTest = toolsenv.Program('test/bin/echoserver',
	['test/build/echoserver.cpp'],
	CPPPATH = cpppath,
	LIBS = ['iftools'] + libs,
	LIBPATH = ['lib'] + libpath)
parsehexTest = toolsenv.Program('test/bin/parsehex',
	['test/build/parsehex.cpp'],
	CPPPATH = cpppath,
	LIBS = ['iftools'] + libs,
	LIBPATH = ['lib'] + libpath)
authfileTest = toolsenv.Program('test/bin/authfile',
	['test/build/authfile.cpp'],
	CPPPATH = cpppath,
	LIBS = ['iftools'] + libs,
	LIBPATH = ['lib'] + libpath)
tcpclientTest = toolsenv.Program('test/bin/tcpclient',
	['test/build/tcpclient.cpp'],
	CPPPATH = cpppath,
	LIBS = ['iftools'] + libs,
	LIBPATH = ['lib'] + libpath)
messageTest = toolsenv.Program('test/bin/message',
	['test/build/message.cpp'],
	CPPPATH = cpppath,
	LIBS = ['iftools'] + libs,
	LIBPATH = ['lib'] + libpath)
msgclientTest = toolsenv.Program('test/bin/msgclient',
	['test/build/msgclient.cpp'],
	CPPPATH = cpppath,
	LIBS = ['iftools'] + libs,
	LIBPATH = ['lib'] + libpath)
msgserverTest = toolsenv.Program('test/bin/msgserver',
	['test/build/msgserver.cpp'],
	CPPPATH = cpppath,
	LIBS = ['iftools'] + libs,
	LIBPATH = ['lib'] + libpath)
authclientTest = toolsenv.Program('test/bin/authclient',
	['test/build/authclient.cpp'],
	CPPPATH = cpppath,
	LIBS = ['iftools'] + libs,
	LIBPATH = ['lib'] + libpath)
authserverTest = toolsenv.Program('test/bin/authserver',
	['test/build/authserver.cpp'],
	CPPPATH = cpppath,
	LIBS = ['iftools'] + libs,
	LIBPATH = ['lib'] + libpath)
readdirTest = toolsenv.Program('test/bin/readdir',
	['test/build/readdir.cpp'],
	CPPPATH = cpppath,
	LIBS = ['iftools'] + libs,
	LIBPATH = ['lib'] + libpath)
explodeqTest = toolsenv.Program('test/bin/explodeq',
	['test/build/explodeq.cpp'],
	CPPPATH = cpppath,
	LIBS = ['iftools'] + libs,
	LIBPATH = ['lib'] + libpath)
numcheckTest = toolsenv.Program('test/bin/numcheck',
	['test/build/numcheck.cpp'],
	CPPPATH = cpppath,
	LIBS = ['iftools'] + libs,
	LIBPATH = ['lib'] + libpath)
treeexprTest = toolsenv.Program('test/bin/treeexpr',
	['test/build/treeexpr.cpp'],
	CPPPATH = cpppath,
	LIBS = ['iftools'] + libs,
	LIBPATH = ['lib'] + libpath)
treeevalTest = toolsenv.Program('test/bin/treeeval',
	['test/build/treeeval.cpp'],
	CPPPATH = cpppath,
	LIBS = ['iftools'] + libs,
	LIBPATH = ['lib'] + libpath)
gtcpclientTest = toolsenv.Program('test/bin/gtcpclient',
	['test/build/gtcpclient.cpp'],
    CCFLAGS = mainccflags + gtkmmccflags,
	CPPPATH = cpppath,
	LIBS = ['iftools', 'ifgtools'] + gtkmmlibs,
	LIBPATH = ['lib'] + libpath + gtkmmlibpath)
combineTest = toolsenv.Program('test/bin/combine',
	['test/build/combine.cpp'],
	CPPPATH = cpppath,
	LIBS = ['iftools'] + libs,
	LIBPATH = ['lib'] + libpath)
nodeindexTest = toolsenv.Program('test/bin/nodeindex',
	['test/build/nodeindex.cpp'],
	CPPPATH = cpppath,
	LIBS = ['iftools'] + libs,
	LIBPATH = ['lib'] + libpath)
mergeTest = toolsenv.Program('test/bin/merge',
	['test/build/merge.cpp'],
	CPPPATH = cpppath,
	LIBS = ['iftools'] + libs,
	LIBPATH = ['lib'] + libpath)
toconfigTest = toolsenv.Program('test/bin/toconfig',
	['test/build/toconfig.cpp'],
	CPPPATH = cpppath,
	LIBS = ['iftools'] + libs,
	LIBPATH = ['lib'] + libpath)
urlencodeTest = toolsenv.Program('test/bin/urlencode',
	['test/build/urlencode.cpp'],
	CPPPATH = cpppath,
	LIBS = ['iftools'] + libs,
	LIBPATH = ['lib'] + libpath)
urldecodeTest = toolsenv.Program('test/bin/urldecode',
	['test/build/urldecode.cpp'],
	CPPPATH = cpppath,
	LIBS = ['iftools'] + libs,
	LIBPATH = ['lib'] + libpath)
utf8decodeTest = toolsenv.Program('test/bin/utf8decode',
	['test/build/utf8decode.cpp'],
	CPPPATH = cpppath,
	LIBS = ['iftools'] + libs,
	LIBPATH = ['lib'] + libpath)
utf8encodeTest = toolsenv.Program('test/bin/utf8encode',
	['test/build/utf8encode.cpp'],
	CPPPATH = cpppath,
	LIBS = ['iftools'] + libs,
	LIBPATH = ['lib'] + libpath)
utf8trimTest = toolsenv.Program('test/bin/utf8trim',
	['test/build/utf8trim.cpp'],
	CPPPATH = cpppath,
	LIBS = ['iftools'] + libs,
	LIBPATH = ['lib'] + libpath)
emailaddressTest = toolsenv.Program('test/bin/emailaddress',
	['test/build/emailaddress.cpp'],
	CPPPATH = cpppath,
	LIBS = ['iftools'] + libs,
	LIBPATH = ['lib'] + libpath)
databaseTest = toolsenv.Program('test/bin/database',
	['test/build/database.cpp'],
	CPPPATH = cpppath,
	LIBS = ['iftools'] + libs,
	LIBPATH = ['lib'] + libpath)
colorTest = toolsenv.Program('test/bin/color',
	['test/build/color.cpp'],
	CPPPATH = cpppath,
	LIBS = ['iftools'] + libs,
	LIBPATH = ['lib'] + libpath)
vector3Test = toolsenv.Program('test/bin/vector3',
	['test/build/vector3.cpp'],
	CPPPATH = cpppath,
	LIBS = ['iftools'] + libs,
	LIBPATH = ['lib'] + libpath)
matrix3Test = toolsenv.Program('test/bin/matrix3',
	['test/build/matrix3.cpp'],
	CPPPATH = cpppath,
	LIBS = ['iftools'] + libs,
	LIBPATH = ['lib'] + libpath)
validatepathTest = toolsenv.Program('test/bin/validatepath',
	['test/build/validatepath.cpp'],
	CPPPATH = cpppath,
	LIBS = ['iftools'] + libs,
	LIBPATH = ['lib'] + libpath)
cairoTest = toolsenv.Program('test/bin/cairo',
	['test/build/cairo.cpp'],
	CCFLAGS = mainccflags + gtkmmccflags + cairoccflags,
	CPPPATH = cpppath,
	LIBS = ['iftools', 'ifgtools'] + libs + gtkmmlibs + cairolibs,
	LIBPATH = ['lib'] + libpath + gtkmmlibpath + cairolibpath)
cairopathTest = toolsenv.Program('test/bin/cairopath',
	['test/build/cairopath.cpp'],
	CCFLAGS = mainccflags + gtkmmccflags + cairoccflags,
	CPPPATH = cpppath,
	LIBS = ['iftools', 'ifgtools'] + libs + gtkmmlibs + cairolibs,
	LIBPATH = ['lib'] + libpath + gtkmmlibpath + cairolibpath)
utf8tokenizerTest = toolsenv.Program('test/bin/utf8tokenizer',
	['test/build/utf8tokenizer.cpp'],
	CPPPATH = cpppath,
	LIBS = ['iftools'] + libs,
	LIBPATH = ['lib'] + libpath)
utf8escapeTest = toolsenv.Program('test/bin/utf8escape',
	['test/build/utf8escape.cpp'],
	CPPPATH = cpppath,
	LIBS = ['iftools'] + libs,
	LIBPATH = ['lib'] + libpath)
utf8unescapeTest = toolsenv.Program('test/bin/utf8unescape',
	['test/build/utf8unescape.cpp'],
	CPPPATH = cpppath,
	LIBS = ['iftools'] + libs,
	LIBPATH = ['lib'] + libpath)
filelistTest = toolsenv.Program('test/bin/filelist',
	['test/build/filelist.cpp'],
	CPPPATH = cpppath,
	LIBS = ['iftools'] + libs,
	LIBPATH = ['lib'] + libpath)

buildTest = ['test/bin/tokenizer',
     'test/bin/stringfilter',
     'test/bin/datetime',
     'test/bin/tree',
     'test/bin/treeresolver',
     'test/bin/configtree',
     'test/bin/template',
     'test/bin/bz2compress',
     'test/bin/pack',
     'test/bin/clargs',
     'test/bin/tcpserver',
     'test/bin/echoserver',
     'test/bin/parsehex',
     'test/bin/authfile',
     'test/bin/tcpclient',
     'test/bin/message',
     'test/bin/msgclient',
     'test/bin/msgserver',
     'test/bin/authclient',
     'test/bin/authserver',
	 'test/bin/readdir',
	 'test/bin/explodeq',
	 'test/bin/numcheck',
	 'test/bin/treeexpr',
	 'test/bin/treeeval',
	 'test/bin/combine',
	 'test/bin/nodeindex',
	 'test/bin/merge',
	 'test/bin/toconfig',
	 'test/bin/urlencode',
	 'test/bin/urldecode',
	 'test/bin/utf8decode',
	 'test/bin/utf8encode',
	 'test/bin/utf8trim',
	 'test/bin/utf8escape',
	 'test/bin/utf8unescape',
	 'test/bin/utf8tokenizer',
	 'test/bin/emailaddress',
	 'test/bin/database',
	 'test/bin/color',
	 'test/bin/vector3',
	 'test/bin/matrix3',
	 'test/bin/validatepath',
	 'test/bin/filelist']

if (gtools == "no"):
    targetLibs = [toolsLib]
else:
    targetLibs = [toolsLib, gtoolsLib]
    buildTest += ['test/bin/gtcpclient',
		'test/bin/cairo',
		'test/bin/cairopath']

if (gtools == "no"):
    allHeaders = [toolsHeaders]
else:
    allHeaders = [toolsHeaders, gtoolsHeaders]

toolsenv.Install(prefix + '/include/ionflux', allHeaders)
toolsenv.Install(prefix + '/lib', targetLibs)
toolsenv.Install(prefix + '/bin', 
    [ifpasswdBin,
	 iftplBin,
	 ifdateBin,
	 iflsBin])

installHeader = toolsenv.Alias('install-header',
    prefix + '/include/ionflux')
installLib = toolsenv.Alias('install-lib',
    prefix + '/lib')
installBin = toolsenv.Alias('install-bin',
    prefix + '/bin')

toolsenv.Alias('test',
	buildLibs + buildTest)

toolsenv.Alias('all',
    buildLibs + buildBin + buildTest)

toolsenv.Alias('install',
    [installHeader,
	 installLib,
	 installBin])

Default(targetLibs, iftplBin, ifpasswdBin, ifdateBin, iflsBin)
