# 
# ***** BEGIN LICENSE BLOCK *****
# Version: MPL 1.1/GPL 2.0/LGPL 2.1
#
# The contents of this file are subject to the Mozilla Public License Version
# 1.1 (the "License"); you may not use this file except in compliance with
# the License. You may obtain a copy of the License at
# http://www.mozilla.org/MPL/
#
# Software distributed under the License is distributed on an "AS IS" basis,
# WITHOUT WARRANTY OF ANY KIND, either express or implied. See the License
# for the specific language governing rights and limitations under the
# License.
#
# The Original Code is the Mozilla browser.
#
# The Initial Developer of the Original Code is
# Christopher Blizzard.
# Portions created by the Initial Developer are Copyright (C) 1999
# the Initial Developer. All Rights Reserved.
#
# Contributor(s):
#   Christopher Blizzard <blizzard@mozilla.org>
#
# Alternatively, the contents of this file may be used under the terms of
# either the GNU General Public License Version 2 or later (the "GPL"), or
# the GNU Lesser General Public License Version 2.1 or later (the "LGPL"),
# in which case the provisions of the GPL or the LGPL are applicable instead
# of those above. If you wish to allow use of your version of this file only
# under the terms of either the GPL or the LGPL, and not to allow others to
# use your version of this file under the terms of the MPL, indicate your
# decision by deleting the provisions above and replace them with the notice
# and other provisions required by the GPL or the LGPL. If you do not delete
# the provisions above, a recipient may use your version of this file under
# the terms of any one of the MPL, the GPL or the LGPL.
#
# ***** END LICENSE BLOCK *****

DEPTH		= ../../../..
topsrcdir	= ../../../..
srcdir		= .
VPATH		= .

include $(DEPTH)/config/autoconf.mk

MODULE		= gtkembedmoz
LIBRARY_NAME	= gtkembedmoz
LIBXUL_LIBRARY	= 1
FORCE_STATIC_LIB = 1
DEFINES += -DIMPL_XREAPI

REQUIRES	= xpcom \
		  content \
		  string \
		  docshell \
		  necko \
		  widget \
		  dom \
		  gfx \
		  layout \
		  uriloader \
		  webbrwsr \
		  shistory \
		  embed_base \
		  windowwatcher \
		  profdirserviceprovider \
		  xulapp \
		  $(NULL)

ifdef ACCESSIBILITY
REQUIRES        += accessibility
endif

CPPSRCS		= \
		gtkmozembed2.cpp \
		EmbedPrivate.cpp \
		EmbedWindow.cpp \
		EmbedProgress.cpp \
		EmbedContentListener.cpp \
		EmbedEventListener.cpp \
		EmbedWindowCreator.cpp \
		$(NULL)

ifdef MOZ_ENABLE_GTK2
CSRCS           = \
		gtkmozembedmarshal.c
CPPSRCS         += \
		EmbedPrompter.cpp \
		GtkPromptService.cpp
endif

LOCAL_INCLUDES += \
		  -I. \
		  $(NULL)

include $(topsrcdir)/config/config.mk

EXPORTS		= \
		gtkmozembed.h \
		gtkmozembed_glue.cpp \
		gtkmozembed_internal.h

include $(topsrcdir)/config/rules.mk

ifeq ($(OS_ARCH), SunOS)
ifndef GNU_CC
# When using Sun's WorkShop compiler, including
# /wherever/workshop-5.0/SC5.0/include/CC/std/time.h
# causes most of these compiles to fail with:
# line 29: Error: Multiple declaration for std::tm.
# So, this gets around the problem.
DEFINES         += -D_TIME_H=1
endif
endif

CXXFLAGS        += $(MOZ_GTK_CFLAGS) $(MOZ_GTK2_CFLAGS)
CFLAGS          += $(MOZ_GTK_CFLAGS) $(MOZ_GTK2_CFLAGS)
DEFINES         += -D_IMPL_GTKMOZEMBED

MARSHAL_FILE = gtkmozembedmarshal
MARSHAL_PREFIX = gtkmozembed

$(MARSHAL_FILE).h: $(MARSHAL_FILE).list
	glib-genmarshal --prefix=$(MARSHAL_PREFIX) $(srcdir)/$(MARSHAL_FILE).list --skip-source --header > $@

$(MARSHAL_FILE).c: $(MARSHAL_FILE).list $(MARSHAL_FILE).h
	glib-genmarshal --prefix=$(MARSHAL_PREFIX) $(srcdir)/$(MARSHAL_FILE).list --skip-source --body > $@

GARBAGE += $(MARSHAL_FILE).h $(MARSHAL_FILE).c

