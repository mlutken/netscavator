#!/usr/bin/env python
import sys, string

from optparse import OptionParser

parser = OptionParser()
parser.add_option('', '--wx-version',
                  dest='wxVersion',
                  default=None,
                  help='set wxPython version to create package for')
parser.add_option('', '--wx-unicode',
                  dest='wxUnicode',
                  default=None,
                  help='set whether to create package for ANSI/UNICODE wxPython')
options, args = parser.parse_args(sys.argv[1:])

if options.wxVersion or options.wxUnicode:
    fullVer = ""
    ver = options.wxVersion
    if ver:
        fullVer = fullVer + ver
    else:
        fullVer = '2.6' # latest stable release
	
    unicode = options.wxUnicode
    if unicode == 'True':
        fullVer = fullVer + "-unicode"
    elif unicode == 'False':
        fullVer = fullVer + "-ansi"

    print "Selecting wxPython version..."
    import wxversion
    wxversion.select(fullVer)
    import wx

    for arg in sys.argv[:]:
        if string.find(arg, "--wx-unicode") == 0 or string.find(arg, "--wx-version") == 0:
            sys.argv.remove(arg)

sys.setup_is_main =  __name__ == "__main__"  # an icky hack!
from wx.build.config import *
if not os.path.exists(PKGDIR):
	os.mkdir(PKGDIR)

if INSTALL_MULTIVERSION:
    EXTRA_PATH = getExtraPath(addOpts=True)
else:
    EXTRA_PATH = None

MOZILLA_ROOT = ""
for arg in sys.argv:
    if arg.find("MOZILLA_ROOT") == 0:
        MOZILLA_ROOT = arg.split("=")[1]
        sys.argv.remove(arg)
        
if MOZILLA_ROOT == "":
    MOZILLA_ROOT = "../../../mozilla/"

if 1:
    msg('Preparing Mozilla...')
    location = './'
    #GENDIR = 'mozilla'
    swig_files = ['mozilla.i', ]
    dirs = ["wx", "wxPython"]
    for mydir in dirs:
        fulldir = location + mydir
        if not os.path.exists(fulldir):
            os.mkdir(mydir)

    #TODO: make this happen on a clean operation only?
    #for now we need it in case we change build options
    import shutil
    if os.path.exists("src"):
        shutil.rmtree("src")

    swig_sources = run_swig(swig_files, location, GENDIR, PKGDIR,
                            USE_SWIG, swig_force, swig_args, swig_deps)

    #just a default value, this should always be overridden by MOZILLA_ROOT
    mozroot = "../../../mozilla/"
    
    if not MOZILLA_ROOT == "":
        mozroot = MOZILLA_ROOT

    if os.name == "posix":
        defines = defines + [('MOZILLA_HOME', '"' + os.path.join(mozroot, "lib") + '"')]

    mozincludes = [mozroot, "../../../src", os.path.join(mozroot, "include")]
    
    for item in glob.glob(os.path.join(mozroot, "include", "*")):
        if os.path.isdir(item):
            mozincludes.append(item)
        
    extralibs = ["xpcom", "nspr4", "plds4", "plc4"]

    if WXPORT.find("gtk") == -1:
        extralibs = extralibs + ["embed_base_s"]

    if os.name == "nt":
        extralibs = extralibs + ["profdirserviceprovider_s"]
        includes.append(WXPY_SRC + "/include")
        if UNICODE:
            includes.append(WXPY_SRC + "/lib/vc_dll/mswuh")
            defines.append(('_UNICODE',1))
        else:
            includes.append(WXPY_SRC + "/lib/vc_dll/mswh")

        libdirs.append(WXPY_SRC + "/lib/vc_dll")

    if debug:
        defines = defines + [('DEBUG', 1),('_DEBUG',1),('TRACING',1)]

    mozsources = []

    if os.name != "posix" or sys.platform == "darwin":
        mozsources = [location + "../../../src/wxMozillaBrowser.cpp", 
                                location + "../../../src/wxMozillaBrowserChrome.cpp",
                                location + "../../../src/wxMozillaEvents.cpp",
                                location + "../../../src/wxMozillaWindow.cpp",
                                location + "../../../src/wxMozillaSettings.cpp",
                                location + "../../../src/wxMozillaDialogs.cpp",
                                location + "../../../src/cstmdlg.cpp",
                                location + "../../../src/helpers.cpp"]
    else:
        #just link to it
        extralibs = extralibs + ["wxmozilla_" + WXPORT + libFlag() + "-" + `VER_MAJOR` + "." + `VER_MINOR`]

    ext = Extension('_mozilla',  mozsources + swig_sources,
                    include_dirs =  mozincludes[:] + includes,
                define_macros = defines,
    
                    library_dirs = [mozroot + "/lib", mozroot + "/gre"] + libdirs,
                    libraries = extralibs + libs,

                extra_compile_args = cflags,
                extra_link_args = lflags,
                    )
    wxpExtensions.append(ext)
    #else:
    #    print "WARNING: Mozilla extension not built - set MOZILLA_ROOT to your mozilla tree's /dist folder and rebuild."

#----------------------------------------------------------------------
# Do the Setup/Build/Install/Whatever
#----------------------------------------------------------------------

if __name__ == "__main__":
    if not PREP_ONLY:
        setup(name             = PKGDIR,
          version          = VERSION,
          description      = DESCRIPTION,
          long_description = LONG_DESCRIPTION,
          author           = AUTHOR,
          author_email     = AUTHOR_EMAIL,
          url              = URL,
          license          = LICENSE,
          packages = ['wx', 'wxPython'],

          extra_path = EXTRA_PATH,
          ext_package = PKGDIR,
          ext_modules = wxpExtensions,

          options = { 'build' : { 'build_base' : BUILD_BASE }},
          )


#----------------------------------------------------------------------
#----------------------------------------------------------------------
