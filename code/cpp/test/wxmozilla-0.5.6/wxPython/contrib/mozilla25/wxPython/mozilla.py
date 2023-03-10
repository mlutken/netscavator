## This file reverse renames symbols in the wx package to give
## them their wx prefix again, for backwards compatibility.
##
## Generated by BuildRenamers in config.py

# This silly stuff here is so the wxPython.wx module doesn't conflict
# with the wx package.  We need to import modules from the wx package
# here, then we'll put the wxPython.wx entry back in sys.modules.
import sys
_wx = None
if sys.modules.has_key('wxPython.wx'):
    _wx = sys.modules['wxPython.wx']
    del sys.modules['wxPython.wx']

import wx.mozilla

sys.modules['wxPython.wx'] = _wx
del sys, _wx


# Now assign all the reverse-renamed names:
wxMOZ_MAJOR_VERSION = wx.mozilla.MOZ_MAJOR_VERSION
wxMOZ_MINOR_VERSION = wx.mozilla.MOZ_MINOR_VERSION
wxMOZ_RELEASE_NUMBER = wx.mozilla.MOZ_RELEASE_NUMBER
wxMozillaBrowser = wx.mozilla.MozillaBrowser
wxMozillaBrowserPtr = wx.mozilla.MozillaBrowserPtr
wxMozillaWindow = wx.mozilla.MozillaWindow
wxMozillaWindowPtr = wx.mozilla.MozillaWindowPtr
wxMozillaSettings = wx.mozilla.MozillaSettings
wxMozillaSettingsPtr = wx.mozilla.MozillaSettingsPtr
wxMozillaSettings_SetProfilePath = wx.mozilla.MozillaSettings_SetProfilePath
wxMozillaSettings_GetProfilePath = wx.mozilla.MozillaSettings_GetProfilePath
wxMozillaSettings_SetMozillaPath = wx.mozilla.MozillaSettings_SetMozillaPath
wxMozillaSettings_GetMozillaPath = wx.mozilla.MozillaSettings_GetMozillaPath
wxMozillaSettings_SetBoolPref = wx.mozilla.MozillaSettings_SetBoolPref
wxMozillaSettings_GetBoolPref = wx.mozilla.MozillaSettings_GetBoolPref
wxMozillaSettings_SetStrPref = wx.mozilla.MozillaSettings_SetStrPref
wxMozillaSettings_GetStrPref = wx.mozilla.MozillaSettings_GetStrPref
wxMozillaSettings_SetIntPref = wx.mozilla.MozillaSettings_SetIntPref
wxMozillaSettings_GetIntPref = wx.mozilla.MozillaSettings_GetIntPref
wxMozillaSettings_SavePrefs = wx.mozilla.MozillaSettings_SavePrefs
wxMOZILLA_STATE_START = wx.mozilla.MOZILLA_STATE_START
wxMOZILLA_STATE_NEGOTIATING = wx.mozilla.MOZILLA_STATE_NEGOTIATING
wxMOZILLA_STATE_REDIRECTING = wx.mozilla.MOZILLA_STATE_REDIRECTING
wxMOZILLA_STATE_TRANSFERRING = wx.mozilla.MOZILLA_STATE_TRANSFERRING
wxMOZILLA_STATE_STOP = wx.mozilla.MOZILLA_STATE_STOP
wxMOZILLA_STATE_IS_REQUEST = wx.mozilla.MOZILLA_STATE_IS_REQUEST
wxMOZILLA_STATE_IS_DOCUMENT = wx.mozilla.MOZILLA_STATE_IS_DOCUMENT
wxMOZILLA_STATE_IS_NETWORK = wx.mozilla.MOZILLA_STATE_IS_NETWORK
wxMOZILLA_STATE_IS_WINDOW = wx.mozilla.MOZILLA_STATE_IS_WINDOW
wxMOZILLA_IS_INSECURE = wx.mozilla.MOZILLA_IS_INSECURE
wxMOZILLA_IS_BROKEN = wx.mozilla.MOZILLA_IS_BROKEN
wxMOZILLA_IS_SECURE = wx.mozilla.MOZILLA_IS_SECURE
wxMOZILLA_SECURE_HIGH = wx.mozilla.MOZILLA_SECURE_HIGH
wxMOZILLA_SECURE_MED = wx.mozilla.MOZILLA_SECURE_MED
wxMOZILLA_SECURE_LOW = wx.mozilla.MOZILLA_SECURE_LOW
wxMOZILLA_CONTEXT_DOCUMENT = wx.mozilla.MOZILLA_CONTEXT_DOCUMENT
wxMOZILLA_CONTEXT_LINK = wx.mozilla.MOZILLA_CONTEXT_LINK
wxMOZILLA_CONTEXT_TEXT = wx.mozilla.MOZILLA_CONTEXT_TEXT
wxMOZILLA_CONTEXT_BACKGROUND_IMAGE = wx.mozilla.MOZILLA_CONTEXT_BACKGROUND_IMAGE
wxMOZILLA_CONTEXT_IMAGE = wx.mozilla.MOZILLA_CONTEXT_IMAGE
wxMozillaBeforeLoadEvent = wx.mozilla.MozillaBeforeLoadEvent
wxMozillaBeforeLoadEventPtr = wx.mozilla.MozillaBeforeLoadEventPtr
wxMozillaLinkChangedEvent = wx.mozilla.MozillaLinkChangedEvent
wxMozillaLinkChangedEventPtr = wx.mozilla.MozillaLinkChangedEventPtr
wxMozillaStateChangedEvent = wx.mozilla.MozillaStateChangedEvent
wxMozillaStateChangedEventPtr = wx.mozilla.MozillaStateChangedEventPtr
wxMozillaSecurityChangedEvent = wx.mozilla.MozillaSecurityChangedEvent
wxMozillaSecurityChangedEventPtr = wx.mozilla.MozillaSecurityChangedEventPtr
wxMozillaLoadCompleteEvent = wx.mozilla.MozillaLoadCompleteEvent
wxMozillaLoadCompleteEventPtr = wx.mozilla.MozillaLoadCompleteEventPtr
wxMozillaStatusChangedEvent = wx.mozilla.MozillaStatusChangedEvent
wxMozillaStatusChangedEventPtr = wx.mozilla.MozillaStatusChangedEventPtr
wxMozillaTitleChangedEvent = wx.mozilla.MozillaTitleChangedEvent
wxMozillaTitleChangedEventPtr = wx.mozilla.MozillaTitleChangedEventPtr
wxMozillaProgressEvent = wx.mozilla.MozillaProgressEvent
wxMozillaProgressEventPtr = wx.mozilla.MozillaProgressEventPtr
wxMozillaRightClickEvent = wx.mozilla.MozillaRightClickEvent
wxMozillaRightClickEventPtr = wx.mozilla.MozillaRightClickEventPtr
wxEVT_MOZILLA_BEFORE_LOAD = wx.mozilla.wxEVT_MOZILLA_BEFORE_LOAD
wxEVT_MOZILLA_URL_CHANGED = wx.mozilla.wxEVT_MOZILLA_URL_CHANGED
wxEVT_MOZILLA_STATE_CHANGED = wx.mozilla.wxEVT_MOZILLA_STATE_CHANGED
wxEVT_MOZILLA_SECURITY_CHANGED = wx.mozilla.wxEVT_MOZILLA_SECURITY_CHANGED
wxEVT_MOZILLA_STATUS_CHANGED = wx.mozilla.wxEVT_MOZILLA_STATUS_CHANGED
wxEVT_MOZILLA_TITLE_CHANGED = wx.mozilla.wxEVT_MOZILLA_TITLE_CHANGED
wxEVT_MOZILLA_LOAD_COMPLETE = wx.mozilla.wxEVT_MOZILLA_LOAD_COMPLETE
wxEVT_MOZILLA_PROGRESS = wx.mozilla.wxEVT_MOZILLA_PROGRESS
wxEVT_MOZILLA_RIGHT_CLICK = wx.mozilla.wxEVT_MOZILLA_RIGHT_CLICK
__version__ = (wxMOZ_MAJOR_VERSION, wxMOZ_MINOR_VERSION, wxMOZ_RELEASE_NUMBER)


d = globals()
for k, v in wx.mozilla.__dict__.iteritems():
    if k.startswith('EVT'):
        d[k] = v
del d, k, v



