GECKO_SDK_PATH=d:\work\gecko-sdk-1.7
!IF "$(CFG)" == ""
CFG=MyComponent - Win32 Debug
!MESSAGE No configuration specified. Defaulting to MyComponent - Win32 Debug.
!ENDIF 

!IF "$(CFG)" != "MyComponent - Win32 Release" && "$(CFG)" != "MyComponent - Win32 Debug"
!MESSAGE Invalid configuration "$(CFG)" specified.
!MESSAGE You can specify a configuration when running NMAKE
!MESSAGE by defining the macro CFG on the command line. For example:
!MESSAGE 
!MESSAGE NMAKE /f "MyComponent.mak" CFG="MyComponent - Win32 Debug"
!MESSAGE 
!MESSAGE Possible choices for configuration are:
!MESSAGE 
!MESSAGE "MyComponent - Win32 Release" (based on "Win32 (x86) Dynamic-Link Library")
!MESSAGE "MyComponent - Win32 Debug" (based on "Win32 (x86) Dynamic-Link Library")
!MESSAGE 
!ERROR An invalid configuration is specified.
!ENDIF 

!IF "$(OS)" == "Windows_NT"
NULL=
!ELSE 
NULL=nul
!ENDIF 

!IF  "$(CFG)" == "MyComponent - Win32 Release"

OUTDIR=.\Release
INTDIR=.\Release
# Begin Custom Macros
OutDir=.\Release
# End Custom Macros

ALL : "$(OUTDIR)\MyComponent.dll" "$(OUTDIR)\MyComponent.bsc"


CLEAN :
	-@erase "$(INTDIR)\MyComponent.obj"
	-@erase "$(INTDIR)\MyComponent.sbr"
	-@erase "$(INTDIR)\MyComponentModule.obj"
	-@erase "$(INTDIR)\MyComponentModule.sbr"
	-@erase "$(INTDIR)\vc60.idb"
	-@erase "$(OUTDIR)\MyComponent.bsc"
	-@erase "$(OUTDIR)\MyComponent.dll"
	-@erase "$(OUTDIR)\MyComponent.exp"
	-@erase "$(OUTDIR)\MyComponent.lib"

"$(OUTDIR)" :
    if not exist "$(OUTDIR)/$(NULL)" mkdir "$(OUTDIR)"

CPP=cl.exe
CPP_PROJ=/nologo /MD /W3 /O1 /I "$(GECKO_SDK_PATH)\include" /FI"$(GECKO_SDK_PATH)\include\mozilla-config.h" /D "NDEBUG" /D "WIN32" /D "_WINDOWS" /D "_MBCS" /D "_USRDLL" /D "XPCOM_GLUE" /FR"$(INTDIR)\\" /Fp"$(INTDIR)\MyComponent.pch" /YX /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\" /FD /c 

.c{$(INTDIR)}.obj::
   $(CPP) @<<
   $(CPP_PROJ) $< 
<<

.cpp{$(INTDIR)}.obj::
   $(CPP) @<<
   $(CPP_PROJ) $< 
<<

.cxx{$(INTDIR)}.obj::
   $(CPP) @<<
   $(CPP_PROJ) $< 
<<

.c{$(INTDIR)}.sbr::
   $(CPP) @<<
   $(CPP_PROJ) $< 
<<

.cpp{$(INTDIR)}.sbr::
   $(CPP) @<<
   $(CPP_PROJ) $< 
<<

.cxx{$(INTDIR)}.sbr::
   $(CPP) @<<
   $(CPP_PROJ) $< 
<<

MTL=midl.exe
MTL_PROJ=/nologo /D "NDEBUG" /mktyplib203 /win32 
RSC=rc.exe
BSC32=bscmake.exe
BSC32_FLAGS=/nologo /o"$(OUTDIR)\MyComponent.bsc" 
BSC32_SBRS= \
	"$(INTDIR)\MyComponent.sbr" \
	"$(INTDIR)\MyComponentModule.sbr" 

"$(OUTDIR)\MyComponent.bsc" : "$(OUTDIR)" $(BSC32_SBRS)
    $(BSC32) @<<
  $(BSC32_FLAGS) $(BSC32_SBRS)
<<

LINK32=link.exe
LINK32_FLAGS=kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib nspr4.lib plds4.lib plc4.lib xpcomglue.lib shlwapi.lib /nologo /dll /incremental:no /pdb:"$(OUTDIR)\MyComponent.pdb" /machine:I386 /out:"$(OUTDIR)\MyComponent.dll" /implib:"$(OUTDIR)\MyComponent.lib" /libpath:"$(GECKO_SDK_PATH)\lib"   
LINK32_OBJS= \
	"$(INTDIR)\MyComponent.obj" \
	"$(INTDIR)\MyComponentModule.obj" 

"$(OUTDIR)\MyComponent.dll" : "$(OUTDIR)" $(DEF_FILE) $(LINK32_OBJS)
    $(LINK32) @<<
  $(LINK32_FLAGS) $(LINK32_OBJS)
<<

TargetPath=.\Release\MyComponent.dll
SOURCE="$(InputPath)"

# Begin Custom Macros
OutDir=.\Release
# End Custom Macros

!ELSEIF  "$(CFG)" == "MyComponent - Win32 Debug"

OUTDIR=.\Debug
INTDIR=.\Debug
# Begin Custom Macros
OutDir=.\Debug
# End Custom Macros

ALL : "$(OUTDIR)\MyComponent.dll" "$(OUTDIR)\MyComponent.bsc"


CLEAN :
	-@erase "$(INTDIR)\MyComponent.obj"
	-@erase "$(INTDIR)\MyComponent.sbr"
	-@erase "$(INTDIR)\MyComponentModule.obj"
	-@erase "$(INTDIR)\MyComponentModule.sbr"
	-@erase "$(INTDIR)\vc60.idb"
	-@erase "$(INTDIR)\vc60.pdb"
	-@erase "$(OUTDIR)\MyComponent.bsc"
	-@erase "$(OUTDIR)\MyComponent.dll"
	-@erase "$(OUTDIR)\MyComponent.exp"
	-@erase "$(OUTDIR)\MyComponent.ilk"
	-@erase "$(OUTDIR)\MyComponent.lib"
	-@erase "$(OUTDIR)\MyComponent.pdb"

"$(OUTDIR)" :
    if not exist "$(OUTDIR)/$(NULL)" mkdir "$(OUTDIR)"

CPP=cl.exe
CPP_PROJ=/nologo /MDd /W3 /Gm /ZI /Od /I "$(GECKO_SDK_PATH)\include"  /FI"$(GECKO_SDK_PATH)\include\mozilla-config.h" /D "_DEBUG" /D "WIN32" /D "_WINDOWS" /D "_MBCS" /D "_USRDLL" /D "XPCOM_GLUE" /FR"$(INTDIR)\\" /Fp"$(INTDIR)\MyComponent.pch" /YX /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\" /FD /GZ /c 

.c{$(INTDIR)}.obj::
   $(CPP) @<<
   $(CPP_PROJ) $< 
<<

.cpp{$(INTDIR)}.obj::
   $(CPP) @<<
   $(CPP_PROJ) $< 
<<

.cxx{$(INTDIR)}.obj::
   $(CPP) @<<
   $(CPP_PROJ) $< 
<<

.c{$(INTDIR)}.sbr::
   $(CPP) @<<
   $(CPP_PROJ) $< 
<<

.cpp{$(INTDIR)}.sbr::
   $(CPP) @<<
   $(CPP_PROJ) $< 
<<

.cxx{$(INTDIR)}.sbr::
   $(CPP) @<<
   $(CPP_PROJ) $< 
<<

MTL=midl.exe
MTL_PROJ=/nologo /D "_DEBUG" /mktyplib203 /win32 
RSC=rc.exe
BSC32=bscmake.exe
BSC32_FLAGS=/nologo /o"$(OUTDIR)\MyComponent.bsc" 
BSC32_SBRS= \
	"$(INTDIR)\MyComponent.sbr" \
	"$(INTDIR)\MyComponentModule.sbr" 

"$(OUTDIR)\MyComponent.bsc" : "$(OUTDIR)" $(BSC32_SBRS)
    $(BSC32) @<<
  $(BSC32_FLAGS) $(BSC32_SBRS)
<<

LINK32=link.exe
LINK32_FLAGS=kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib nspr4.lib plds4.lib plc4.lib xpcomglue.lib shlwapi.lib /nologo /dll /incremental:yes /pdb:"$(OUTDIR)\MyComponent.pdb" /debug /machine:I386 /out:"$(OUTDIR)\MyComponent.dll" /implib:"$(OUTDIR)\MyComponent.lib" /pdbtype:sept /libpath:"$(GECKO_SDK_PATH)\lib"  
LINK32_OBJS= \
	"$(INTDIR)\MyComponent.obj" \
	"$(INTDIR)\MyComponentModule.obj" 

"$(OUTDIR)\MyComponent.dll" : "$(OUTDIR)" $(DEF_FILE) $(LINK32_OBJS)
    $(LINK32) @<<
  $(LINK32_FLAGS) $(LINK32_OBJS)
<<

TargetPath=.\Debug\MyComponent.dll
SOURCE="$(InputPath)"

# Begin Custom Macros
OutDir=.\Debug
# End Custom Macros

!ENDIF 

NO_EXTERNAL_DEPS=1

!IF "$(NO_EXTERNAL_DEPS)" != "1"
!IF EXISTS("MyComponent.dep")
!INCLUDE "MyComponent.dep"
!ELSE 
!MESSAGE Warning: cannot find "MyComponent.dep"
!ENDIF 
!ENDIF 


!IF "$(CFG)" == "MyComponent - Win32 Release" || "$(CFG)" == "MyComponent - Win32 Debug"
SOURCE=.\MyComponent.cpp

"$(INTDIR)\MyComponent.obj"	"$(INTDIR)\MyComponent.sbr" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)

SOURCE=.\MyComponentModule.cpp

"$(INTDIR)\MyComponentModule.obj"	"$(INTDIR)\MyComponentModule.sbr" : $(SOURCE) "$(INTDIR)"

!ENDIF 

