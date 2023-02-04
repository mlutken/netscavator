# File:		makefile.vc
# Author:	Julian Smart
# Created:	2001
# Updated:
# Copyright:	(c) 2001, Julian Smart
#
# "%W% %G%"
#
# Makefile : Builds Plot class library (MS VC++).
# Use FINAL=1 argument to nmake to build final version with no debugging
# info


# Set WXDIR for your system
WXDIR = $(WXWIN)

OBJECTS = $(D)\wxMozillaBrowser.obj $(D)\wxMozillaBrowserChrome.obj $(D)\wxMozillaEvents.obj $(D)\wxMozillaWindow.obj $(D)\helpers.obj $(D)\cstmdlg.obj $(D)\wxMozillaDialogs.obj $(D)\wxMozillaSettings.obj
STLIBS= ..\mozilla\lib\embed_base_s.lib ..\mozilla\lib\profdirserviceprovider_s.lib ..\mozilla\lib\nspr4.lib
!if "$(XPCOM_GLUE)" == "1"

STLIBS=$(STLIBS) ..\mozilla\lib\xpcomglue.lib ..\mozilla\lib\string_s.lib ..\mozilla\lib\string_obsolete_s.lib ..\mozilla\lib\nspr4.lib ..\mozilla\lib\plc4.lib ..\mozilla\lib\plds4.lib
CPPFLAGS=$(CPPFLAGS) /DXPCOM_GLUE=1

!else

STLIBS=$(STLIBS) ..\mozilla\lib\xpcom.lib

!endif
LIBTARGET=$(WXDIR)\lib\wxMozilla$(UNIEXT)$(LIBEXT).lib

!include .\makelib.vc
#/D_DEBUG /DDEBUG /DTRACING 
CPPFLAGS = $(CPPFLAGS) /DXP_WIN=1 /I "./" /I "..\mozilla\include" /D_DLL /D_WINDLL /I "..\mozilla\include\docshell" /I "..\mozilla\include\nspr" /I "..\mozilla\include\xpcom" /I "..\mozilla\include\string" /I "..\mozilla\include\pref" /I "..\mozilla\include\widget" /I "..\mozilla\include\webbrwsr" /I "..\mozilla\include\embed_base" /I "..\mozilla\include\uriloader" /I "..\mozilla\include\gfx" /I "..\mozilla\include\shistory" /I "..\mozilla\include\commandhandler" /I "..\mozilla\include\necko" /I "..\mozilla\include\webbrowserpersist" /I "..\mozilla\include\composer" /I "..\mozilla\include\dom" /I "..\mozilla\include\content" /I "..\mozilla\include\webshell" /I "..\mozilla\include\find" /I "..\mozilla\include\windowwatcher" /I "..\mozilla\include\editor" /I "..\mozilla\include\layout" /I "..\mozilla\include\win" /I "..\mozilla\include\profdirserviceprovider" /I "..\mozilla\include\pref"
