# This file was created automatically by SWIG.
# Don't modify this file, modify the SWIG interface instead.

import _mozilla

def _swig_setattr_nondynamic(self,class_type,name,value,static=1):
    if (name == "this"):
        if isinstance(value, class_type):
            self.__dict__[name] = value.this
            if hasattr(value,"thisown"): self.__dict__["thisown"] = value.thisown
            del value.thisown
            return
    method = class_type.__swig_setmethods__.get(name,None)
    if method: return method(self,value)
    if (not static) or hasattr(self,name) or (name == "thisown"):
        self.__dict__[name] = value
    else:
        raise AttributeError("You cannot add attributes to %s" % self)

def _swig_setattr(self,class_type,name,value):
    return _swig_setattr_nondynamic(self,class_type,name,value,0)

def _swig_getattr(self,class_type,name):
    method = class_type.__swig_getmethods__.get(name,None)
    if method: return method(self)
    raise AttributeError,name

import types
try:
    _object = types.ObjectType
    _newclass = 1
except AttributeError:
    class _object : pass
    _newclass = 0
del types


def _swig_setattr_nondynamic_method(set):
    def set_attr(self,name,value):
        if hasattr(self,name) or (name in ("this", "thisown")):
            set(self,name,value)
        else:
            raise AttributeError("You cannot add attributes to %s" % self)
    return set_attr


import _core
import _windows
import _misc
wx = _core 
__docfilter__ = wx.__DocFilter(globals()) 
class MozillaBrowser(_core.Window):
    """Proxy of C++ MozillaBrowser class"""
    def __repr__(self):
        return "<%s.%s; proxy of C++ wxMozillaBrowser instance at %s>" % (self.__class__.__module__, self.__class__.__name__, self.this,)
    def __init__(self, *args, **kwargs):
        """
        __init__(self, Window parent, int id, Point pos=DefaultPosition, Size size=DefaultSize, 
            long style=0, String name=PanelNameStr) -> MozillaBrowser
        """
        newobj = _mozilla.new_MozillaBrowser(*args, **kwargs)
        self.this = newobj.this
        self.thisown = 1
        del newobj.thisown
    def Create(*args, **kwargs):
        """
        Create(self, Window parent, int id, Point pos=DefaultPosition, Size size=DefaultSize, 
            long style=0, String name=PanelNameStr) -> bool
        """
        return _mozilla.MozillaBrowser_Create(*args, **kwargs)

    def LoadURL(*args, **kwargs):
        """LoadURL(self, String location) -> bool"""
        return _mozilla.MozillaBrowser_LoadURL(*args, **kwargs)

    def GetURL(*args, **kwargs):
        """GetURL(self) -> String"""
        return _mozilla.MozillaBrowser_GetURL(*args, **kwargs)

    def SavePage(*args, **kwargs):
        """SavePage(self, String filename, bool saveFiles=True) -> bool"""
        return _mozilla.MozillaBrowser_SavePage(*args, **kwargs)

    def IsBusy(*args, **kwargs):
        """IsBusy(self) -> bool"""
        return _mozilla.MozillaBrowser_IsBusy(*args, **kwargs)

    def GoBack(*args, **kwargs):
        """GoBack(self) -> bool"""
        return _mozilla.MozillaBrowser_GoBack(*args, **kwargs)

    def CanGoBack(*args, **kwargs):
        """CanGoBack(self) -> bool"""
        return _mozilla.MozillaBrowser_CanGoBack(*args, **kwargs)

    def GoForward(*args, **kwargs):
        """GoForward(self) -> bool"""
        return _mozilla.MozillaBrowser_GoForward(*args, **kwargs)

    def CanGoForward(*args, **kwargs):
        """CanGoForward(self) -> bool"""
        return _mozilla.MozillaBrowser_CanGoForward(*args, **kwargs)

    def Stop(*args, **kwargs):
        """Stop(self) -> bool"""
        return _mozilla.MozillaBrowser_Stop(*args, **kwargs)

    def Reload(*args, **kwargs):
        """Reload(self) -> bool"""
        return _mozilla.MozillaBrowser_Reload(*args, **kwargs)

    def Find(*args, **kwargs):
        """
        Find(self, String searchString, bool matchCase=False, bool matchWholeWord=False, 
            bool wrapAround=True, bool searchBackwards=False) -> bool
        """
        return _mozilla.MozillaBrowser_Find(*args, **kwargs)

    def FindNext(*args, **kwargs):
        """FindNext(self) -> bool"""
        return _mozilla.MozillaBrowser_FindNext(*args, **kwargs)

    def GetStatus(*args, **kwargs):
        """GetStatus(self) -> String"""
        return _mozilla.MozillaBrowser_GetStatus(*args, **kwargs)

    def GetSelection(*args, **kwargs):
        """GetSelection(self) -> String"""
        return _mozilla.MozillaBrowser_GetSelection(*args, **kwargs)

    def Copy(*args, **kwargs):
        """Copy(self)"""
        return _mozilla.MozillaBrowser_Copy(*args, **kwargs)

    def SelectAll(*args, **kwargs):
        """SelectAll(self)"""
        return _mozilla.MozillaBrowser_SelectAll(*args, **kwargs)

    def SelectNone(*args, **kwargs):
        """SelectNone(self)"""
        return _mozilla.MozillaBrowser_SelectNone(*args, **kwargs)

    def UpdateBaseURI(*args, **kwargs):
        """UpdateBaseURI(self)"""
        return _mozilla.MozillaBrowser_UpdateBaseURI(*args, **kwargs)

    def MakeEditable(*args, **kwargs):
        """MakeEditable(self, bool enable=True)"""
        return _mozilla.MozillaBrowser_MakeEditable(*args, **kwargs)

    def InsertHTML(*args, **kwargs):
        """InsertHTML(self, String html)"""
        return _mozilla.MozillaBrowser_InsertHTML(*args, **kwargs)

    def IsEditable(*args, **kwargs):
        """IsEditable(self) -> bool"""
        return _mozilla.MozillaBrowser_IsEditable(*args, **kwargs)

    def EditCommand(*args, **kwargs):
        """EditCommand(self, String cmdId, String value=wxEmptyString)"""
        return _mozilla.MozillaBrowser_EditCommand(*args, **kwargs)

    def GetCommandState(*args, **kwargs):
        """GetCommandState(self, String command, String state) -> bool"""
        return _mozilla.MozillaBrowser_GetCommandState(*args, **kwargs)

    def GetStateAttribute(*args, **kwargs):
        """GetStateAttribute(self, String command) -> String"""
        return _mozilla.MozillaBrowser_GetStateAttribute(*args, **kwargs)

    def IsElementInSelection(*args, **kwargs):
        """IsElementInSelection(self, String element) -> bool"""
        return _mozilla.MozillaBrowser_IsElementInSelection(*args, **kwargs)

    def SelectElement(*args, **kwargs):
        """SelectElement(self, String element) -> bool"""
        return _mozilla.MozillaBrowser_SelectElement(*args, **kwargs)

    def GetElementAttribute(*args, **kwargs):
        """GetElementAttribute(self, String tagName, String attrName) -> String"""
        return _mozilla.MozillaBrowser_GetElementAttribute(*args, **kwargs)

    def SetElementAttribute(*args, **kwargs):
        """SetElementAttribute(self, String attrName, String attrValue)"""
        return _mozilla.MozillaBrowser_SetElementAttribute(*args, **kwargs)

    def SetPage(*args, **kwargs):
        """SetPage(self, String data) -> bool"""
        return _mozilla.MozillaBrowser_SetPage(*args, **kwargs)

    def GetPage(*args, **kwargs):
        """GetPage(self) -> String"""
        return _mozilla.MozillaBrowser_GetPage(*args, **kwargs)

    def SetZoom(*args, **kwargs):
        """SetZoom(self, float level) -> bool"""
        return _mozilla.MozillaBrowser_SetZoom(*args, **kwargs)


class MozillaBrowserPtr(MozillaBrowser):
    def __init__(self, this):
        self.this = this
        if not hasattr(self,"thisown"): self.thisown = 0
        self.__class__ = MozillaBrowser
_mozilla.MozillaBrowser_swigregister(MozillaBrowserPtr)
cvar = _mozilla.cvar
MOZ_MAJOR_VERSION = cvar.MOZ_MAJOR_VERSION
MOZ_MINOR_VERSION = cvar.MOZ_MINOR_VERSION
MOZ_RELEASE_NUMBER = cvar.MOZ_RELEASE_NUMBER

class MozillaWindow(_windows.Frame):
    """Proxy of C++ MozillaWindow class"""
    def __repr__(self):
        return "<%s.%s; proxy of C++ wxMozillaWindow instance at %s>" % (self.__class__.__module__, self.__class__.__name__, self.this,)
    def __init__(self, *args, **kwargs):
        """__init__(self, bool showMenu=True, bool showToolbar=True, bool showStatusbar=True) -> MozillaWindow"""
        newobj = _mozilla.new_MozillaWindow(*args, **kwargs)
        self.this = newobj.this
        self.thisown = 1
        del newobj.thisown
    Mozilla = property(_mozilla.MozillaWindow_Mozilla_get, _mozilla.MozillaWindow_Mozilla_set)

class MozillaWindowPtr(MozillaWindow):
    def __init__(self, this):
        self.this = this
        if not hasattr(self,"thisown"): self.thisown = 0
        self.__class__ = MozillaWindow
_mozilla.MozillaWindow_swigregister(MozillaWindowPtr)

class MozillaSettings(object):
    """Proxy of C++ MozillaSettings class"""
    def __init__(self): raise RuntimeError, "No constructor defined"
    def __repr__(self):
        return "<%s.%s; proxy of C++ wxMozillaSettings instance at %s>" % (self.__class__.__module__, self.__class__.__name__, self.this,)
    def SetProfilePath(*args, **kwargs):
        """SetProfilePath(String path) -> bool"""
        return _mozilla.MozillaSettings_SetProfilePath(*args, **kwargs)

    SetProfilePath = staticmethod(SetProfilePath)
    def GetProfilePath(*args, **kwargs):
        """GetProfilePath() -> String"""
        return _mozilla.MozillaSettings_GetProfilePath(*args, **kwargs)

    GetProfilePath = staticmethod(GetProfilePath)
    def SetMozillaPath(*args, **kwargs):
        """SetMozillaPath(String path)"""
        return _mozilla.MozillaSettings_SetMozillaPath(*args, **kwargs)

    SetMozillaPath = staticmethod(SetMozillaPath)
    def GetMozillaPath(*args, **kwargs):
        """GetMozillaPath() -> String"""
        return _mozilla.MozillaSettings_GetMozillaPath(*args, **kwargs)

    GetMozillaPath = staticmethod(GetMozillaPath)
    def SetBoolPref(*args, **kwargs):
        """SetBoolPref(String name, bool value)"""
        return _mozilla.MozillaSettings_SetBoolPref(*args, **kwargs)

    SetBoolPref = staticmethod(SetBoolPref)
    def GetBoolPref(*args, **kwargs):
        """GetBoolPref(String name) -> bool"""
        return _mozilla.MozillaSettings_GetBoolPref(*args, **kwargs)

    GetBoolPref = staticmethod(GetBoolPref)
    def SetStrPref(*args, **kwargs):
        """SetStrPref(String name, String value)"""
        return _mozilla.MozillaSettings_SetStrPref(*args, **kwargs)

    SetStrPref = staticmethod(SetStrPref)
    def GetStrPref(*args, **kwargs):
        """GetStrPref(String name) -> String"""
        return _mozilla.MozillaSettings_GetStrPref(*args, **kwargs)

    GetStrPref = staticmethod(GetStrPref)
    def SetIntPref(*args, **kwargs):
        """SetIntPref(String name, int value)"""
        return _mozilla.MozillaSettings_SetIntPref(*args, **kwargs)

    SetIntPref = staticmethod(SetIntPref)
    def GetIntPref(*args, **kwargs):
        """GetIntPref(String name) -> int"""
        return _mozilla.MozillaSettings_GetIntPref(*args, **kwargs)

    GetIntPref = staticmethod(GetIntPref)
    def SavePrefs(*args, **kwargs):
        """SavePrefs()"""
        return _mozilla.MozillaSettings_SavePrefs(*args, **kwargs)

    SavePrefs = staticmethod(SavePrefs)

class MozillaSettingsPtr(MozillaSettings):
    def __init__(self, this):
        self.this = this
        if not hasattr(self,"thisown"): self.thisown = 0
        self.__class__ = MozillaSettings
_mozilla.MozillaSettings_swigregister(MozillaSettingsPtr)

def MozillaSettings_SetProfilePath(*args, **kwargs):
    """MozillaSettings_SetProfilePath(String path) -> bool"""
    return _mozilla.MozillaSettings_SetProfilePath(*args, **kwargs)

def MozillaSettings_GetProfilePath(*args, **kwargs):
    """MozillaSettings_GetProfilePath() -> String"""
    return _mozilla.MozillaSettings_GetProfilePath(*args, **kwargs)

def MozillaSettings_SetMozillaPath(*args, **kwargs):
    """MozillaSettings_SetMozillaPath(String path)"""
    return _mozilla.MozillaSettings_SetMozillaPath(*args, **kwargs)

def MozillaSettings_GetMozillaPath(*args, **kwargs):
    """MozillaSettings_GetMozillaPath() -> String"""
    return _mozilla.MozillaSettings_GetMozillaPath(*args, **kwargs)

def MozillaSettings_SetBoolPref(*args, **kwargs):
    """MozillaSettings_SetBoolPref(String name, bool value)"""
    return _mozilla.MozillaSettings_SetBoolPref(*args, **kwargs)

def MozillaSettings_GetBoolPref(*args, **kwargs):
    """MozillaSettings_GetBoolPref(String name) -> bool"""
    return _mozilla.MozillaSettings_GetBoolPref(*args, **kwargs)

def MozillaSettings_SetStrPref(*args, **kwargs):
    """MozillaSettings_SetStrPref(String name, String value)"""
    return _mozilla.MozillaSettings_SetStrPref(*args, **kwargs)

def MozillaSettings_GetStrPref(*args, **kwargs):
    """MozillaSettings_GetStrPref(String name) -> String"""
    return _mozilla.MozillaSettings_GetStrPref(*args, **kwargs)

def MozillaSettings_SetIntPref(*args, **kwargs):
    """MozillaSettings_SetIntPref(String name, int value)"""
    return _mozilla.MozillaSettings_SetIntPref(*args, **kwargs)

def MozillaSettings_GetIntPref(*args, **kwargs):
    """MozillaSettings_GetIntPref(String name) -> int"""
    return _mozilla.MozillaSettings_GetIntPref(*args, **kwargs)

def MozillaSettings_SavePrefs(*args, **kwargs):
    """MozillaSettings_SavePrefs()"""
    return _mozilla.MozillaSettings_SavePrefs(*args, **kwargs)

MOZILLA_STATE_START = _mozilla.MOZILLA_STATE_START
MOZILLA_STATE_NEGOTIATING = _mozilla.MOZILLA_STATE_NEGOTIATING
MOZILLA_STATE_REDIRECTING = _mozilla.MOZILLA_STATE_REDIRECTING
MOZILLA_STATE_TRANSFERRING = _mozilla.MOZILLA_STATE_TRANSFERRING
MOZILLA_STATE_STOP = _mozilla.MOZILLA_STATE_STOP
MOZILLA_STATE_IS_REQUEST = _mozilla.MOZILLA_STATE_IS_REQUEST
MOZILLA_STATE_IS_DOCUMENT = _mozilla.MOZILLA_STATE_IS_DOCUMENT
MOZILLA_STATE_IS_NETWORK = _mozilla.MOZILLA_STATE_IS_NETWORK
MOZILLA_STATE_IS_WINDOW = _mozilla.MOZILLA_STATE_IS_WINDOW
MOZILLA_IS_INSECURE = _mozilla.MOZILLA_IS_INSECURE
MOZILLA_IS_BROKEN = _mozilla.MOZILLA_IS_BROKEN
MOZILLA_IS_SECURE = _mozilla.MOZILLA_IS_SECURE
MOZILLA_SECURE_HIGH = _mozilla.MOZILLA_SECURE_HIGH
MOZILLA_SECURE_MED = _mozilla.MOZILLA_SECURE_MED
MOZILLA_SECURE_LOW = _mozilla.MOZILLA_SECURE_LOW
MOZILLA_CONTEXT_DOCUMENT = _mozilla.MOZILLA_CONTEXT_DOCUMENT
MOZILLA_CONTEXT_LINK = _mozilla.MOZILLA_CONTEXT_LINK
MOZILLA_CONTEXT_TEXT = _mozilla.MOZILLA_CONTEXT_TEXT
MOZILLA_CONTEXT_BACKGROUND_IMAGE = _mozilla.MOZILLA_CONTEXT_BACKGROUND_IMAGE
MOZILLA_CONTEXT_IMAGE = _mozilla.MOZILLA_CONTEXT_IMAGE
class MozillaBeforeLoadEvent(_core.CommandEvent):
    """Proxy of C++ MozillaBeforeLoadEvent class"""
    def __repr__(self):
        return "<%s.%s; proxy of C++ wxMozillaBeforeLoadEvent instance at %s>" % (self.__class__.__module__, self.__class__.__name__, self.this,)
    def GetURL(*args, **kwargs):
        """GetURL(self) -> String"""
        return _mozilla.MozillaBeforeLoadEvent_GetURL(*args, **kwargs)

    def SetURL(*args, **kwargs):
        """SetURL(self, String newURL)"""
        return _mozilla.MozillaBeforeLoadEvent_SetURL(*args, **kwargs)

    def Cancel(*args, **kwargs):
        """Cancel(self)"""
        return _mozilla.MozillaBeforeLoadEvent_Cancel(*args, **kwargs)

    def IsCancelled(*args, **kwargs):
        """IsCancelled(self) -> bool"""
        return _mozilla.MozillaBeforeLoadEvent_IsCancelled(*args, **kwargs)

    def __init__(self, *args, **kwargs):
        """__init__(self, Window win=None) -> MozillaBeforeLoadEvent"""
        newobj = _mozilla.new_MozillaBeforeLoadEvent(*args, **kwargs)
        self.this = newobj.this
        self.thisown = 1
        del newobj.thisown

class MozillaBeforeLoadEventPtr(MozillaBeforeLoadEvent):
    def __init__(self, this):
        self.this = this
        if not hasattr(self,"thisown"): self.thisown = 0
        self.__class__ = MozillaBeforeLoadEvent
_mozilla.MozillaBeforeLoadEvent_swigregister(MozillaBeforeLoadEventPtr)

class MozillaLinkChangedEvent(_core.CommandEvent):
    """Proxy of C++ MozillaLinkChangedEvent class"""
    def __repr__(self):
        return "<%s.%s; proxy of C++ wxMozillaLinkChangedEvent instance at %s>" % (self.__class__.__module__, self.__class__.__name__, self.this,)
    def GetNewURL(*args, **kwargs):
        """GetNewURL(self) -> String"""
        return _mozilla.MozillaLinkChangedEvent_GetNewURL(*args, **kwargs)

    def CanGoBack(*args, **kwargs):
        """CanGoBack(self) -> bool"""
        return _mozilla.MozillaLinkChangedEvent_CanGoBack(*args, **kwargs)

    def CanGoForward(*args, **kwargs):
        """CanGoForward(self) -> bool"""
        return _mozilla.MozillaLinkChangedEvent_CanGoForward(*args, **kwargs)

    def SetNewURL(*args, **kwargs):
        """SetNewURL(self, String newurl)"""
        return _mozilla.MozillaLinkChangedEvent_SetNewURL(*args, **kwargs)

    def SetCanGoBack(*args, **kwargs):
        """SetCanGoBack(self, bool goback)"""
        return _mozilla.MozillaLinkChangedEvent_SetCanGoBack(*args, **kwargs)

    def SetCanGoForward(*args, **kwargs):
        """SetCanGoForward(self, bool goforward)"""
        return _mozilla.MozillaLinkChangedEvent_SetCanGoForward(*args, **kwargs)

    def __init__(self, *args, **kwargs):
        """__init__(self, Window win=None) -> MozillaLinkChangedEvent"""
        newobj = _mozilla.new_MozillaLinkChangedEvent(*args, **kwargs)
        self.this = newobj.this
        self.thisown = 1
        del newobj.thisown

class MozillaLinkChangedEventPtr(MozillaLinkChangedEvent):
    def __init__(self, this):
        self.this = this
        if not hasattr(self,"thisown"): self.thisown = 0
        self.__class__ = MozillaLinkChangedEvent
_mozilla.MozillaLinkChangedEvent_swigregister(MozillaLinkChangedEventPtr)

class MozillaStateChangedEvent(_core.CommandEvent):
    """Proxy of C++ MozillaStateChangedEvent class"""
    def __repr__(self):
        return "<%s.%s; proxy of C++ wxMozillaStateChangedEvent instance at %s>" % (self.__class__.__module__, self.__class__.__name__, self.this,)
    def GetState(*args, **kwargs):
        """GetState(self) -> int"""
        return _mozilla.MozillaStateChangedEvent_GetState(*args, **kwargs)

    def SetState(*args, **kwargs):
        """SetState(self, int state)"""
        return _mozilla.MozillaStateChangedEvent_SetState(*args, **kwargs)

    def GetURL(*args, **kwargs):
        """GetURL(self) -> String"""
        return _mozilla.MozillaStateChangedEvent_GetURL(*args, **kwargs)

    def SetURL(*args, **kwargs):
        """SetURL(self, String url)"""
        return _mozilla.MozillaStateChangedEvent_SetURL(*args, **kwargs)

    def __init__(self, *args, **kwargs):
        """__init__(self, Window win=None) -> MozillaStateChangedEvent"""
        newobj = _mozilla.new_MozillaStateChangedEvent(*args, **kwargs)
        self.this = newobj.this
        self.thisown = 1
        del newobj.thisown

class MozillaStateChangedEventPtr(MozillaStateChangedEvent):
    def __init__(self, this):
        self.this = this
        if not hasattr(self,"thisown"): self.thisown = 0
        self.__class__ = MozillaStateChangedEvent
_mozilla.MozillaStateChangedEvent_swigregister(MozillaStateChangedEventPtr)

class MozillaSecurityChangedEvent(_core.CommandEvent):
    """Proxy of C++ MozillaSecurityChangedEvent class"""
    def __repr__(self):
        return "<%s.%s; proxy of C++ wxMozillaSecurityChangedEvent instance at %s>" % (self.__class__.__module__, self.__class__.__name__, self.this,)
    def GetSecurity(*args, **kwargs):
        """GetSecurity(self) -> int"""
        return _mozilla.MozillaSecurityChangedEvent_GetSecurity(*args, **kwargs)

    def SetSecurity(*args, **kwargs):
        """SetSecurity(self, int security)"""
        return _mozilla.MozillaSecurityChangedEvent_SetSecurity(*args, **kwargs)

    def __init__(self, *args, **kwargs):
        """__init__(self, Window win=None) -> MozillaSecurityChangedEvent"""
        newobj = _mozilla.new_MozillaSecurityChangedEvent(*args, **kwargs)
        self.this = newobj.this
        self.thisown = 1
        del newobj.thisown

class MozillaSecurityChangedEventPtr(MozillaSecurityChangedEvent):
    def __init__(self, this):
        self.this = this
        if not hasattr(self,"thisown"): self.thisown = 0
        self.__class__ = MozillaSecurityChangedEvent
_mozilla.MozillaSecurityChangedEvent_swigregister(MozillaSecurityChangedEventPtr)

class MozillaLoadCompleteEvent(_core.CommandEvent):
    """Proxy of C++ MozillaLoadCompleteEvent class"""
    def __repr__(self):
        return "<%s.%s; proxy of C++ wxMozillaLoadCompleteEvent instance at %s>" % (self.__class__.__module__, self.__class__.__name__, self.this,)
    def __init__(self, *args, **kwargs):
        """__init__(self, Window win=None) -> MozillaLoadCompleteEvent"""
        newobj = _mozilla.new_MozillaLoadCompleteEvent(*args, **kwargs)
        self.this = newobj.this
        self.thisown = 1
        del newobj.thisown

class MozillaLoadCompleteEventPtr(MozillaLoadCompleteEvent):
    def __init__(self, this):
        self.this = this
        if not hasattr(self,"thisown"): self.thisown = 0
        self.__class__ = MozillaLoadCompleteEvent
_mozilla.MozillaLoadCompleteEvent_swigregister(MozillaLoadCompleteEventPtr)

class MozillaStatusChangedEvent(_core.CommandEvent):
    """Proxy of C++ MozillaStatusChangedEvent class"""
    def __repr__(self):
        return "<%s.%s; proxy of C++ wxMozillaStatusChangedEvent instance at %s>" % (self.__class__.__module__, self.__class__.__name__, self.this,)
    def GetStatusText(*args, **kwargs):
        """GetStatusText(self) -> String"""
        return _mozilla.MozillaStatusChangedEvent_GetStatusText(*args, **kwargs)

    def IsBusy(*args, **kwargs):
        """IsBusy(self) -> bool"""
        return _mozilla.MozillaStatusChangedEvent_IsBusy(*args, **kwargs)

    def SetStatusText(*args, **kwargs):
        """SetStatusText(self, String status)"""
        return _mozilla.MozillaStatusChangedEvent_SetStatusText(*args, **kwargs)

    def SetBusy(*args, **kwargs):
        """SetBusy(self, bool isbusy)"""
        return _mozilla.MozillaStatusChangedEvent_SetBusy(*args, **kwargs)

    def __init__(self, *args, **kwargs):
        """__init__(self, Window win=None) -> MozillaStatusChangedEvent"""
        newobj = _mozilla.new_MozillaStatusChangedEvent(*args, **kwargs)
        self.this = newobj.this
        self.thisown = 1
        del newobj.thisown

class MozillaStatusChangedEventPtr(MozillaStatusChangedEvent):
    def __init__(self, this):
        self.this = this
        if not hasattr(self,"thisown"): self.thisown = 0
        self.__class__ = MozillaStatusChangedEvent
_mozilla.MozillaStatusChangedEvent_swigregister(MozillaStatusChangedEventPtr)

class MozillaTitleChangedEvent(_core.CommandEvent):
    """Proxy of C++ MozillaTitleChangedEvent class"""
    def __repr__(self):
        return "<%s.%s; proxy of C++ wxMozillaTitleChangedEvent instance at %s>" % (self.__class__.__module__, self.__class__.__name__, self.this,)
    def GetTitle(*args, **kwargs):
        """GetTitle(self) -> String"""
        return _mozilla.MozillaTitleChangedEvent_GetTitle(*args, **kwargs)

    def SetTitle(*args, **kwargs):
        """SetTitle(self, String title)"""
        return _mozilla.MozillaTitleChangedEvent_SetTitle(*args, **kwargs)

    def __init__(self, *args, **kwargs):
        """__init__(self, Window win=None) -> MozillaTitleChangedEvent"""
        newobj = _mozilla.new_MozillaTitleChangedEvent(*args, **kwargs)
        self.this = newobj.this
        self.thisown = 1
        del newobj.thisown

class MozillaTitleChangedEventPtr(MozillaTitleChangedEvent):
    def __init__(self, this):
        self.this = this
        if not hasattr(self,"thisown"): self.thisown = 0
        self.__class__ = MozillaTitleChangedEvent
_mozilla.MozillaTitleChangedEvent_swigregister(MozillaTitleChangedEventPtr)

class MozillaProgressEvent(_core.CommandEvent):
    """Proxy of C++ MozillaProgressEvent class"""
    def __repr__(self):
        return "<%s.%s; proxy of C++ wxMozillaProgressEvent instance at %s>" % (self.__class__.__module__, self.__class__.__name__, self.this,)
    def GetSelfCurrentProgress(*args, **kwargs):
        """GetSelfCurrentProgress(self) -> int"""
        return _mozilla.MozillaProgressEvent_GetSelfCurrentProgress(*args, **kwargs)

    def SetSelfCurrentProgress(*args, **kwargs):
        """SetSelfCurrentProgress(self, int progress)"""
        return _mozilla.MozillaProgressEvent_SetSelfCurrentProgress(*args, **kwargs)

    def GetSelfMaxProgress(*args, **kwargs):
        """GetSelfMaxProgress(self) -> int"""
        return _mozilla.MozillaProgressEvent_GetSelfMaxProgress(*args, **kwargs)

    def SetSelfMaxProgress(*args, **kwargs):
        """SetSelfMaxProgress(self, int progress)"""
        return _mozilla.MozillaProgressEvent_SetSelfMaxProgress(*args, **kwargs)

    def GetTotalCurrentProgress(*args, **kwargs):
        """GetTotalCurrentProgress(self) -> int"""
        return _mozilla.MozillaProgressEvent_GetTotalCurrentProgress(*args, **kwargs)

    def SetTotalCurrentProgress(*args, **kwargs):
        """SetTotalCurrentProgress(self, int progress)"""
        return _mozilla.MozillaProgressEvent_SetTotalCurrentProgress(*args, **kwargs)

    def GetTotalMaxProgress(*args, **kwargs):
        """GetTotalMaxProgress(self) -> int"""
        return _mozilla.MozillaProgressEvent_GetTotalMaxProgress(*args, **kwargs)

    def SetTotalMaxProgress(*args, **kwargs):
        """SetTotalMaxProgress(self, int progress)"""
        return _mozilla.MozillaProgressEvent_SetTotalMaxProgress(*args, **kwargs)

    def __init__(self, *args, **kwargs):
        """__init__(self, Window win=None) -> MozillaProgressEvent"""
        newobj = _mozilla.new_MozillaProgressEvent(*args, **kwargs)
        self.this = newobj.this
        self.thisown = 1
        del newobj.thisown

class MozillaProgressEventPtr(MozillaProgressEvent):
    def __init__(self, this):
        self.this = this
        if not hasattr(self,"thisown"): self.thisown = 0
        self.__class__ = MozillaProgressEvent
_mozilla.MozillaProgressEvent_swigregister(MozillaProgressEventPtr)

class MozillaRightClickEvent(_core.MouseEvent):
    """Proxy of C++ MozillaRightClickEvent class"""
    def __repr__(self):
        return "<%s.%s; proxy of C++ wxMozillaRightClickEvent instance at %s>" % (self.__class__.__module__, self.__class__.__name__, self.this,)
    def IsBusy(*args, **kwargs):
        """IsBusy(self) -> bool"""
        return _mozilla.MozillaRightClickEvent_IsBusy(*args, **kwargs)

    def SetBusy(*args, **kwargs):
        """SetBusy(self, bool isbusy)"""
        return _mozilla.MozillaRightClickEvent_SetBusy(*args, **kwargs)

    def GetBackgroundImageSrc(*args, **kwargs):
        """GetBackgroundImageSrc(self) -> String"""
        return _mozilla.MozillaRightClickEvent_GetBackgroundImageSrc(*args, **kwargs)

    def SetBackgroundImageSrc(*args, **kwargs):
        """SetBackgroundImageSrc(self, String name)"""
        return _mozilla.MozillaRightClickEvent_SetBackgroundImageSrc(*args, **kwargs)

    def GetText(*args, **kwargs):
        """GetText(self) -> String"""
        return _mozilla.MozillaRightClickEvent_GetText(*args, **kwargs)

    def SetText(*args, **kwargs):
        """SetText(self, String text)"""
        return _mozilla.MozillaRightClickEvent_SetText(*args, **kwargs)

    def GetImageSrc(*args, **kwargs):
        """GetImageSrc(self) -> String"""
        return _mozilla.MozillaRightClickEvent_GetImageSrc(*args, **kwargs)

    def SetImageSrc(*args, **kwargs):
        """SetImageSrc(self, String src)"""
        return _mozilla.MozillaRightClickEvent_SetImageSrc(*args, **kwargs)

    def GetLink(*args, **kwargs):
        """GetLink(self) -> String"""
        return _mozilla.MozillaRightClickEvent_GetLink(*args, **kwargs)

    def SetLink(*args, **kwargs):
        """SetLink(self, String link)"""
        return _mozilla.MozillaRightClickEvent_SetLink(*args, **kwargs)

    def GetContext(*args, **kwargs):
        """GetContext(self) -> int"""
        return _mozilla.MozillaRightClickEvent_GetContext(*args, **kwargs)

    def SetContext(*args, **kwargs):
        """SetContext(self, int context)"""
        return _mozilla.MozillaRightClickEvent_SetContext(*args, **kwargs)

    def __init__(self, *args, **kwargs):
        """__init__(self, Window win=None) -> MozillaRightClickEvent"""
        newobj = _mozilla.new_MozillaRightClickEvent(*args, **kwargs)
        self.this = newobj.this
        self.thisown = 1
        del newobj.thisown

class MozillaRightClickEventPtr(MozillaRightClickEvent):
    def __init__(self, this):
        self.this = this
        if not hasattr(self,"thisown"): self.thisown = 0
        self.__class__ = MozillaRightClickEvent
_mozilla.MozillaRightClickEvent_swigregister(MozillaRightClickEventPtr)

wxEVT_MOZILLA_BEFORE_LOAD = _mozilla.wxEVT_MOZILLA_BEFORE_LOAD
wxEVT_MOZILLA_URL_CHANGED = _mozilla.wxEVT_MOZILLA_URL_CHANGED
wxEVT_MOZILLA_STATE_CHANGED = _mozilla.wxEVT_MOZILLA_STATE_CHANGED
wxEVT_MOZILLA_SECURITY_CHANGED = _mozilla.wxEVT_MOZILLA_SECURITY_CHANGED
wxEVT_MOZILLA_STATUS_CHANGED = _mozilla.wxEVT_MOZILLA_STATUS_CHANGED
wxEVT_MOZILLA_TITLE_CHANGED = _mozilla.wxEVT_MOZILLA_TITLE_CHANGED
wxEVT_MOZILLA_LOAD_COMPLETE = _mozilla.wxEVT_MOZILLA_LOAD_COMPLETE
wxEVT_MOZILLA_PROGRESS = _mozilla.wxEVT_MOZILLA_PROGRESS
wxEVT_MOZILLA_RIGHT_CLICK = _mozilla.wxEVT_MOZILLA_RIGHT_CLICK
__version__ = (MOZ_MAJOR_VERSION, MOZ_MINOR_VERSION, MOZ_RELEASE_NUMBER)

EVT_MOZILLA_BEFORE_LOAD = wx.PyEventBinder(wxEVT_MOZILLA_BEFORE_LOAD, 1)
EVT_MOZILLA_URL_CHANGED = wx.PyEventBinder(wxEVT_MOZILLA_URL_CHANGED, 1)
EVT_MOZILLA_STATE_CHANGED = wx.PyEventBinder(wxEVT_MOZILLA_STATE_CHANGED, 1)
EVT_MOZILLA_SECURITY_CHANGED = wx.PyEventBinder(wxEVT_MOZILLA_SECURITY_CHANGED, 1)
EVT_MOZILLA_STATUS_CHANGED = wx.PyEventBinder(wxEVT_MOZILLA_STATUS_CHANGED, 1)
EVT_MOZILLA_TITLE_CHANGED = wx.PyEventBinder(wxEVT_MOZILLA_TITLE_CHANGED, 1)
EVT_MOZILLA_LOAD_COMPLETE = wx.PyEventBinder(wxEVT_MOZILLA_LOAD_COMPLETE, 1)
EVT_MOZILLA_PROGRESS = wx.PyEventBinder(wxEVT_MOZILLA_PROGRESS, 1)
EVT_MOZILLA_RIGHT_CLICK = wx.PyEventBinder(wxEVT_MOZILLA_RIGHT_CLICK, 1)


