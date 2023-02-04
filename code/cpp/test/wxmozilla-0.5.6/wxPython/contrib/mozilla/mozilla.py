# This file was created automatically by SWIG.
import mozillac

from misc import *

from misc2 import *

from windows import *

from gdi import *

from fonts import *

from clip_dnd import *

from events import *

from streams import *

from utils import *

from mdi import *

from frames import *

from stattool import *

from controls import *

from controls2 import *

from windows2 import *

from cmndlgs import *

from windows3 import *

from image import *

from printfw import *

from sizers import *

from filesys import *
import wx

def EVT_MOZILLA_BEFORE_LOAD(win, id, func):
    win.Connect(id, -1, wxEVT_MOZILLA_BEFORE_LOAD, func)

def EVT_MOZILLA_URL_CHANGED(win, id, func):
    win.Connect(id, -1, wxEVT_MOZILLA_URL_CHANGED, func)

def EVT_MOZILLA_STATE_CHANGED(win, id, func):
    win.Connect(id, -1, wxEVT_MOZILLA_STATE_CHANGED, func)

def EVT_MOZILLA_SECURITY_CHANGED(win, id, func):
    win.Connect(id, -1, wxEVT_MOZILLA_SECURITY_CHANGED, func)

def EVT_MOZILLA_STATUS_CHANGED(win, id, func):
    win.Connect(id, -1, wxEVT_MOZILLA_STATUS_CHANGED, func)

def EVT_MOZILLA_TITLE_CHANGED(win, id, func):
    win.Connect(id, -1, wxEVT_MOZILLA_TITLE_CHANGED, func)

def EVT_MOZILLA_LOAD_COMPLETE(win, id, func):
    win.Connect(id, -1, wxEVT_MOZILLA_LOAD_COMPLETE, func)

def EVT_MOZILLA_PROGRESS(win, id, func):
    win.Connect(id, -1, wxEVT_MOZILLA_PROGRESS, func)

def EVT_MOZILLA_RIGHT_CLICK(win, id, func):
    win.Connect(id, -1, wxEVT_MOZILLA_RIGHT_CLICK, func)

class wxMozillaBrowserPtr(wxWindowPtr):
    def __init__(self,this):
        self.this = this
        self.thisown = 0
    def Create(self, *_args, **_kwargs):
        val = mozillac.wxMozillaBrowser_Create(self, *_args, **_kwargs)
        return val
    def LoadURL(self, *_args, **_kwargs):
        val = mozillac.wxMozillaBrowser_LoadURL(self, *_args, **_kwargs)
        return val
    def GetURL(self, *_args, **_kwargs):
        val = mozillac.wxMozillaBrowser_GetURL(self, *_args, **_kwargs)
        return val
    def SavePage(self, *_args, **_kwargs):
        val = mozillac.wxMozillaBrowser_SavePage(self, *_args, **_kwargs)
        return val
    def IsBusy(self, *_args, **_kwargs):
        val = mozillac.wxMozillaBrowser_IsBusy(self, *_args, **_kwargs)
        return val
    def GoBack(self, *_args, **_kwargs):
        val = mozillac.wxMozillaBrowser_GoBack(self, *_args, **_kwargs)
        return val
    def CanGoBack(self, *_args, **_kwargs):
        val = mozillac.wxMozillaBrowser_CanGoBack(self, *_args, **_kwargs)
        return val
    def GoForward(self, *_args, **_kwargs):
        val = mozillac.wxMozillaBrowser_GoForward(self, *_args, **_kwargs)
        return val
    def CanGoForward(self, *_args, **_kwargs):
        val = mozillac.wxMozillaBrowser_CanGoForward(self, *_args, **_kwargs)
        return val
    def Stop(self, *_args, **_kwargs):
        val = mozillac.wxMozillaBrowser_Stop(self, *_args, **_kwargs)
        return val
    def Reload(self, *_args, **_kwargs):
        val = mozillac.wxMozillaBrowser_Reload(self, *_args, **_kwargs)
        return val
    def Find(self, *_args, **_kwargs):
        val = mozillac.wxMozillaBrowser_Find(self, *_args, **_kwargs)
        return val
    def FindNext(self, *_args, **_kwargs):
        val = mozillac.wxMozillaBrowser_FindNext(self, *_args, **_kwargs)
        return val
    def GetStatus(self, *_args, **_kwargs):
        val = mozillac.wxMozillaBrowser_GetStatus(self, *_args, **_kwargs)
        return val
    def GetSelection(self, *_args, **_kwargs):
        val = mozillac.wxMozillaBrowser_GetSelection(self, *_args, **_kwargs)
        return val
    def Copy(self, *_args, **_kwargs):
        val = mozillac.wxMozillaBrowser_Copy(self, *_args, **_kwargs)
        return val
    def SelectAll(self, *_args, **_kwargs):
        val = mozillac.wxMozillaBrowser_SelectAll(self, *_args, **_kwargs)
        return val
    def SelectNone(self, *_args, **_kwargs):
        val = mozillac.wxMozillaBrowser_SelectNone(self, *_args, **_kwargs)
        return val
    def MakeEditable(self, *_args, **_kwargs):
        val = mozillac.wxMozillaBrowser_MakeEditable(self, *_args, **_kwargs)
        return val
    def InsertHTML(self, *_args, **_kwargs):
        val = mozillac.wxMozillaBrowser_InsertHTML(self, *_args, **_kwargs)
        return val
    def IsEditable(self, *_args, **_kwargs):
        val = mozillac.wxMozillaBrowser_IsEditable(self, *_args, **_kwargs)
        return val
    def EditCommand(self, *_args, **_kwargs):
        val = mozillac.wxMozillaBrowser_EditCommand(self, *_args, **_kwargs)
        return val
    def GetCommandState(self, *_args, **_kwargs):
        val = mozillac.wxMozillaBrowser_GetCommandState(self, *_args, **_kwargs)
        return val
    def GetStateAttribute(self, *_args, **_kwargs):
        val = mozillac.wxMozillaBrowser_GetStateAttribute(self, *_args, **_kwargs)
        return val
    def IsElementInSelection(self, *_args, **_kwargs):
        val = mozillac.wxMozillaBrowser_IsElementInSelection(self, *_args, **_kwargs)
        return val
    def SelectElement(self, *_args, **_kwargs):
        val = mozillac.wxMozillaBrowser_SelectElement(self, *_args, **_kwargs)
        return val
    def GetElementAttribute(self, *_args, **_kwargs):
        val = mozillac.wxMozillaBrowser_GetElementAttribute(self, *_args, **_kwargs)
        return val
    def SetElementAttribute(self, *_args, **_kwargs):
        val = mozillac.wxMozillaBrowser_SetElementAttribute(self, *_args, **_kwargs)
        return val
    def SetPage(self, *_args, **_kwargs):
        val = mozillac.wxMozillaBrowser_SetPage(self, *_args, **_kwargs)
        return val
    def GetPage(self, *_args, **_kwargs):
        val = mozillac.wxMozillaBrowser_GetPage(self, *_args, **_kwargs)
        return val
    def SetZoom(self, *_args, **_kwargs):
        val = mozillac.wxMozillaBrowser_SetZoom(self, *_args, **_kwargs)
        return val
    def __repr__(self):
        return "<%s.%s instance; proxy of C++ wxMozillaBrowser instance at %s>" % (self.__class__.__module__, self.__class__.__name__, self.this)
class wxMozillaBrowser(wxMozillaBrowserPtr):
    def __init__(self,*_args,**_kwargs):
        self.this = mozillac.new_wxMozillaBrowser(*_args,**_kwargs)
        self.thisown = 1




class wxMozillaWindowPtr(wxFramePtr):
    def __init__(self,this):
        self.this = this
        self.thisown = 0
    def __setattr__(self,name,value):
        if name == "Mozilla" :
            mozillac.wxMozillaWindow_Mozilla_set(self,value.this)
            return
        self.__dict__[name] = value
    def __getattr__(self,name):
        if name == "Mozilla" : 
            return wxMozillaBrowserPtr(mozillac.wxMozillaWindow_Mozilla_get(self))
        raise AttributeError,name
    def __repr__(self):
        return "<%s.%s instance; proxy of C++ wxMozillaWindow instance at %s>" % (self.__class__.__module__, self.__class__.__name__, self.this)
class wxMozillaWindow(wxMozillaWindowPtr):
    def __init__(self,*_args,**_kwargs):
        self.this = mozillac.new_wxMozillaWindow(*_args,**_kwargs)
        self.thisown = 1




class wxMozillaSettingsPtr :
    def __init__(self,this):
        self.this = this
        self.thisown = 0
    def __repr__(self):
        return "<%s.%s instance; proxy of C++ wxMozillaSettings instance at %s>" % (self.__class__.__module__, self.__class__.__name__, self.this)
class wxMozillaSettings(wxMozillaSettingsPtr):
    def __init__(self,this):
        self.this = this




class wxMozillaBeforeLoadEventPtr(wxCommandEventPtr):
    def __init__(self,this):
        self.this = this
        self.thisown = 0
    def GetURL(self, *_args, **_kwargs):
        val = mozillac.wxMozillaBeforeLoadEvent_GetURL(self, *_args, **_kwargs)
        return val
    def SetURL(self, *_args, **_kwargs):
        val = mozillac.wxMozillaBeforeLoadEvent_SetURL(self, *_args, **_kwargs)
        return val
    def Cancel(self, *_args, **_kwargs):
        val = mozillac.wxMozillaBeforeLoadEvent_Cancel(self, *_args, **_kwargs)
        return val
    def IsCancelled(self, *_args, **_kwargs):
        val = mozillac.wxMozillaBeforeLoadEvent_IsCancelled(self, *_args, **_kwargs)
        return val
    def __repr__(self):
        return "<%s.%s instance; proxy of C++ wxMozillaBeforeLoadEvent instance at %s>" % (self.__class__.__module__, self.__class__.__name__, self.this)
class wxMozillaBeforeLoadEvent(wxMozillaBeforeLoadEventPtr):
    def __init__(self,*_args,**_kwargs):
        self.this = mozillac.new_wxMozillaBeforeLoadEvent(*_args,**_kwargs)
        self.thisown = 1




class wxMozillaLinkChangedEventPtr(wxCommandEventPtr):
    def __init__(self,this):
        self.this = this
        self.thisown = 0
    def GetNewURL(self, *_args, **_kwargs):
        val = mozillac.wxMozillaLinkChangedEvent_GetNewURL(self, *_args, **_kwargs)
        return val
    def CanGoBack(self, *_args, **_kwargs):
        val = mozillac.wxMozillaLinkChangedEvent_CanGoBack(self, *_args, **_kwargs)
        return val
    def CanGoForward(self, *_args, **_kwargs):
        val = mozillac.wxMozillaLinkChangedEvent_CanGoForward(self, *_args, **_kwargs)
        return val
    def SetNewURL(self, *_args, **_kwargs):
        val = mozillac.wxMozillaLinkChangedEvent_SetNewURL(self, *_args, **_kwargs)
        return val
    def SetCanGoBack(self, *_args, **_kwargs):
        val = mozillac.wxMozillaLinkChangedEvent_SetCanGoBack(self, *_args, **_kwargs)
        return val
    def SetCanGoForward(self, *_args, **_kwargs):
        val = mozillac.wxMozillaLinkChangedEvent_SetCanGoForward(self, *_args, **_kwargs)
        return val
    def __repr__(self):
        return "<%s.%s instance; proxy of C++ wxMozillaLinkChangedEvent instance at %s>" % (self.__class__.__module__, self.__class__.__name__, self.this)
class wxMozillaLinkChangedEvent(wxMozillaLinkChangedEventPtr):
    def __init__(self,*_args,**_kwargs):
        self.this = mozillac.new_wxMozillaLinkChangedEvent(*_args,**_kwargs)
        self.thisown = 1




class wxMozillaStateChangedEventPtr(wxCommandEventPtr):
    def __init__(self,this):
        self.this = this
        self.thisown = 0
    def GetState(self, *_args, **_kwargs):
        val = mozillac.wxMozillaStateChangedEvent_GetState(self, *_args, **_kwargs)
        return val
    def SetState(self, *_args, **_kwargs):
        val = mozillac.wxMozillaStateChangedEvent_SetState(self, *_args, **_kwargs)
        return val
    def GetURL(self, *_args, **_kwargs):
        val = mozillac.wxMozillaStateChangedEvent_GetURL(self, *_args, **_kwargs)
        return val
    def SetURL(self, *_args, **_kwargs):
        val = mozillac.wxMozillaStateChangedEvent_SetURL(self, *_args, **_kwargs)
        return val
    def __repr__(self):
        return "<%s.%s instance; proxy of C++ wxMozillaStateChangedEvent instance at %s>" % (self.__class__.__module__, self.__class__.__name__, self.this)
class wxMozillaStateChangedEvent(wxMozillaStateChangedEventPtr):
    def __init__(self,*_args,**_kwargs):
        self.this = mozillac.new_wxMozillaStateChangedEvent(*_args,**_kwargs)
        self.thisown = 1




class wxMozillaSecurityChangedEventPtr(wxCommandEventPtr):
    def __init__(self,this):
        self.this = this
        self.thisown = 0
    def GetSecurity(self, *_args, **_kwargs):
        val = mozillac.wxMozillaSecurityChangedEvent_GetSecurity(self, *_args, **_kwargs)
        return val
    def SetSecurity(self, *_args, **_kwargs):
        val = mozillac.wxMozillaSecurityChangedEvent_SetSecurity(self, *_args, **_kwargs)
        return val
    def __repr__(self):
        return "<%s.%s instance; proxy of C++ wxMozillaSecurityChangedEvent instance at %s>" % (self.__class__.__module__, self.__class__.__name__, self.this)
class wxMozillaSecurityChangedEvent(wxMozillaSecurityChangedEventPtr):
    def __init__(self,*_args,**_kwargs):
        self.this = mozillac.new_wxMozillaSecurityChangedEvent(*_args,**_kwargs)
        self.thisown = 1




class wxMozillaLoadCompleteEventPtr(wxCommandEventPtr):
    def __init__(self,this):
        self.this = this
        self.thisown = 0
    def __repr__(self):
        return "<%s.%s instance; proxy of C++ wxMozillaLoadCompleteEvent instance at %s>" % (self.__class__.__module__, self.__class__.__name__, self.this)
class wxMozillaLoadCompleteEvent(wxMozillaLoadCompleteEventPtr):
    def __init__(self,*_args,**_kwargs):
        self.this = mozillac.new_wxMozillaLoadCompleteEvent(*_args,**_kwargs)
        self.thisown = 1




class wxMozillaStatusChangedEventPtr(wxCommandEventPtr):
    def __init__(self,this):
        self.this = this
        self.thisown = 0
    def GetStatusText(self, *_args, **_kwargs):
        val = mozillac.wxMozillaStatusChangedEvent_GetStatusText(self, *_args, **_kwargs)
        return val
    def IsBusy(self, *_args, **_kwargs):
        val = mozillac.wxMozillaStatusChangedEvent_IsBusy(self, *_args, **_kwargs)
        return val
    def SetStatusText(self, *_args, **_kwargs):
        val = mozillac.wxMozillaStatusChangedEvent_SetStatusText(self, *_args, **_kwargs)
        return val
    def SetBusy(self, *_args, **_kwargs):
        val = mozillac.wxMozillaStatusChangedEvent_SetBusy(self, *_args, **_kwargs)
        return val
    def __repr__(self):
        return "<%s.%s instance; proxy of C++ wxMozillaStatusChangedEvent instance at %s>" % (self.__class__.__module__, self.__class__.__name__, self.this)
class wxMozillaStatusChangedEvent(wxMozillaStatusChangedEventPtr):
    def __init__(self,*_args,**_kwargs):
        self.this = mozillac.new_wxMozillaStatusChangedEvent(*_args,**_kwargs)
        self.thisown = 1




class wxMozillaTitleChangedEventPtr(wxCommandEventPtr):
    def __init__(self,this):
        self.this = this
        self.thisown = 0
    def GetTitle(self, *_args, **_kwargs):
        val = mozillac.wxMozillaTitleChangedEvent_GetTitle(self, *_args, **_kwargs)
        return val
    def SetTitle(self, *_args, **_kwargs):
        val = mozillac.wxMozillaTitleChangedEvent_SetTitle(self, *_args, **_kwargs)
        return val
    def __repr__(self):
        return "<%s.%s instance; proxy of C++ wxMozillaTitleChangedEvent instance at %s>" % (self.__class__.__module__, self.__class__.__name__, self.this)
class wxMozillaTitleChangedEvent(wxMozillaTitleChangedEventPtr):
    def __init__(self,*_args,**_kwargs):
        self.this = mozillac.new_wxMozillaTitleChangedEvent(*_args,**_kwargs)
        self.thisown = 1




class wxMozillaProgressEventPtr(wxCommandEventPtr):
    def __init__(self,this):
        self.this = this
        self.thisown = 0
    def GetSelfCurrentProgress(self, *_args, **_kwargs):
        val = mozillac.wxMozillaProgressEvent_GetSelfCurrentProgress(self, *_args, **_kwargs)
        return val
    def SetSelfCurrentProgress(self, *_args, **_kwargs):
        val = mozillac.wxMozillaProgressEvent_SetSelfCurrentProgress(self, *_args, **_kwargs)
        return val
    def GetSelfMaxProgress(self, *_args, **_kwargs):
        val = mozillac.wxMozillaProgressEvent_GetSelfMaxProgress(self, *_args, **_kwargs)
        return val
    def SetSelfMaxProgress(self, *_args, **_kwargs):
        val = mozillac.wxMozillaProgressEvent_SetSelfMaxProgress(self, *_args, **_kwargs)
        return val
    def GetTotalCurrentProgress(self, *_args, **_kwargs):
        val = mozillac.wxMozillaProgressEvent_GetTotalCurrentProgress(self, *_args, **_kwargs)
        return val
    def SetTotalCurrentProgress(self, *_args, **_kwargs):
        val = mozillac.wxMozillaProgressEvent_SetTotalCurrentProgress(self, *_args, **_kwargs)
        return val
    def GetTotalMaxProgress(self, *_args, **_kwargs):
        val = mozillac.wxMozillaProgressEvent_GetTotalMaxProgress(self, *_args, **_kwargs)
        return val
    def SetTotalMaxProgress(self, *_args, **_kwargs):
        val = mozillac.wxMozillaProgressEvent_SetTotalMaxProgress(self, *_args, **_kwargs)
        return val
    def __repr__(self):
        return "<%s.%s instance; proxy of C++ wxMozillaProgressEvent instance at %s>" % (self.__class__.__module__, self.__class__.__name__, self.this)
class wxMozillaProgressEvent(wxMozillaProgressEventPtr):
    def __init__(self,*_args,**_kwargs):
        self.this = mozillac.new_wxMozillaProgressEvent(*_args,**_kwargs)
        self.thisown = 1




class wxMozillaRightClickEventPtr(wxMouseEventPtr):
    def __init__(self,this):
        self.this = this
        self.thisown = 0
    def IsBusy(self, *_args, **_kwargs):
        val = mozillac.wxMozillaRightClickEvent_IsBusy(self, *_args, **_kwargs)
        return val
    def SetBusy(self, *_args, **_kwargs):
        val = mozillac.wxMozillaRightClickEvent_SetBusy(self, *_args, **_kwargs)
        return val
    def GetBackgroundImageSrc(self, *_args, **_kwargs):
        val = mozillac.wxMozillaRightClickEvent_GetBackgroundImageSrc(self, *_args, **_kwargs)
        return val
    def SetBackgroundImageSrc(self, *_args, **_kwargs):
        val = mozillac.wxMozillaRightClickEvent_SetBackgroundImageSrc(self, *_args, **_kwargs)
        return val
    def GetText(self, *_args, **_kwargs):
        val = mozillac.wxMozillaRightClickEvent_GetText(self, *_args, **_kwargs)
        return val
    def SetText(self, *_args, **_kwargs):
        val = mozillac.wxMozillaRightClickEvent_SetText(self, *_args, **_kwargs)
        return val
    def GetImageSrc(self, *_args, **_kwargs):
        val = mozillac.wxMozillaRightClickEvent_GetImageSrc(self, *_args, **_kwargs)
        return val
    def SetImageSrc(self, *_args, **_kwargs):
        val = mozillac.wxMozillaRightClickEvent_SetImageSrc(self, *_args, **_kwargs)
        return val
    def GetLink(self, *_args, **_kwargs):
        val = mozillac.wxMozillaRightClickEvent_GetLink(self, *_args, **_kwargs)
        return val
    def SetLink(self, *_args, **_kwargs):
        val = mozillac.wxMozillaRightClickEvent_SetLink(self, *_args, **_kwargs)
        return val
    def GetContext(self, *_args, **_kwargs):
        val = mozillac.wxMozillaRightClickEvent_GetContext(self, *_args, **_kwargs)
        return val
    def SetContext(self, *_args, **_kwargs):
        val = mozillac.wxMozillaRightClickEvent_SetContext(self, *_args, **_kwargs)
        return val
    def __setattr__(self,name,value):
        if name == "m_x" :
            mozillac.wxMozillaRightClickEvent_m_x_set(self,value)
            return
        if name == "m_y" :
            mozillac.wxMozillaRightClickEvent_m_y_set(self,value)
            return
        if name == "m_leftDown" :
            mozillac.wxMozillaRightClickEvent_m_leftDown_set(self,value)
            return
        if name == "m_middleDown" :
            mozillac.wxMozillaRightClickEvent_m_middleDown_set(self,value)
            return
        if name == "m_rightDown" :
            mozillac.wxMozillaRightClickEvent_m_rightDown_set(self,value)
            return
        if name == "m_controlDown" :
            mozillac.wxMozillaRightClickEvent_m_controlDown_set(self,value)
            return
        if name == "m_shiftDown" :
            mozillac.wxMozillaRightClickEvent_m_shiftDown_set(self,value)
            return
        if name == "m_altDown" :
            mozillac.wxMozillaRightClickEvent_m_altDown_set(self,value)
            return
        if name == "m_metaDown" :
            mozillac.wxMozillaRightClickEvent_m_metaDown_set(self,value)
            return
        if name == "m_wheelRotation" :
            mozillac.wxMozillaRightClickEvent_m_wheelRotation_set(self,value)
            return
        if name == "m_wheelDelta" :
            mozillac.wxMozillaRightClickEvent_m_wheelDelta_set(self,value)
            return
        if name == "m_linesPerAction" :
            mozillac.wxMozillaRightClickEvent_m_linesPerAction_set(self,value)
            return
        self.__dict__[name] = value
    def __getattr__(self,name):
        if name == "m_x" : 
            return mozillac.wxMozillaRightClickEvent_m_x_get(self)
        if name == "m_y" : 
            return mozillac.wxMozillaRightClickEvent_m_y_get(self)
        if name == "m_leftDown" : 
            return mozillac.wxMozillaRightClickEvent_m_leftDown_get(self)
        if name == "m_middleDown" : 
            return mozillac.wxMozillaRightClickEvent_m_middleDown_get(self)
        if name == "m_rightDown" : 
            return mozillac.wxMozillaRightClickEvent_m_rightDown_get(self)
        if name == "m_controlDown" : 
            return mozillac.wxMozillaRightClickEvent_m_controlDown_get(self)
        if name == "m_shiftDown" : 
            return mozillac.wxMozillaRightClickEvent_m_shiftDown_get(self)
        if name == "m_altDown" : 
            return mozillac.wxMozillaRightClickEvent_m_altDown_get(self)
        if name == "m_metaDown" : 
            return mozillac.wxMozillaRightClickEvent_m_metaDown_get(self)
        if name == "m_wheelRotation" : 
            return mozillac.wxMozillaRightClickEvent_m_wheelRotation_get(self)
        if name == "m_wheelDelta" : 
            return mozillac.wxMozillaRightClickEvent_m_wheelDelta_get(self)
        if name == "m_linesPerAction" : 
            return mozillac.wxMozillaRightClickEvent_m_linesPerAction_get(self)
        raise AttributeError,name
    def __repr__(self):
        return "<%s.%s instance; proxy of C++ wxMozillaRightClickEvent instance at %s>" % (self.__class__.__module__, self.__class__.__name__, self.this)
class wxMozillaRightClickEvent(wxMozillaRightClickEventPtr):
    def __init__(self,*_args,**_kwargs):
        self.this = mozillac.new_wxMozillaRightClickEvent(*_args,**_kwargs)
        self.thisown = 1





#-------------- FUNCTION WRAPPERS ------------------

wxMozillaSettings_SetProfilePath = mozillac.wxMozillaSettings_SetProfilePath

wxMozillaSettings_GetProfilePath = mozillac.wxMozillaSettings_GetProfilePath

wxMozillaSettings_SetMozillaPath = mozillac.wxMozillaSettings_SetMozillaPath

wxMozillaSettings_GetMozillaPath = mozillac.wxMozillaSettings_GetMozillaPath

wxMozillaSettings_SetBoolPref = mozillac.wxMozillaSettings_SetBoolPref

wxMozillaSettings_GetBoolPref = mozillac.wxMozillaSettings_GetBoolPref

wxMozillaSettings_SetStrPref = mozillac.wxMozillaSettings_SetStrPref

wxMozillaSettings_GetStrPref = mozillac.wxMozillaSettings_GetStrPref

wxMozillaSettings_SetIntPref = mozillac.wxMozillaSettings_SetIntPref

wxMozillaSettings_GetIntPref = mozillac.wxMozillaSettings_GetIntPref

wxMozillaSettings_SavePrefs = mozillac.wxMozillaSettings_SavePrefs



#-------------- VARIABLE WRAPPERS ------------------

wxMOZ_MAJOR_VERSION = mozillac.wxMOZ_MAJOR_VERSION
wxMOZ_MINOR_VERSION = mozillac.wxMOZ_MINOR_VERSION
wxMOZ_RELEASE_NUMBER = mozillac.wxMOZ_RELEASE_NUMBER
wxMOZILLA_STATE_START = mozillac.wxMOZILLA_STATE_START
wxMOZILLA_STATE_NEGOTIATING = mozillac.wxMOZILLA_STATE_NEGOTIATING
wxMOZILLA_STATE_REDIRECTING = mozillac.wxMOZILLA_STATE_REDIRECTING
wxMOZILLA_STATE_TRANSFERRING = mozillac.wxMOZILLA_STATE_TRANSFERRING
wxMOZILLA_STATE_STOP = mozillac.wxMOZILLA_STATE_STOP
wxMOZILLA_STATE_IS_REQUEST = mozillac.wxMOZILLA_STATE_IS_REQUEST
wxMOZILLA_STATE_IS_DOCUMENT = mozillac.wxMOZILLA_STATE_IS_DOCUMENT
wxMOZILLA_STATE_IS_NETWORK = mozillac.wxMOZILLA_STATE_IS_NETWORK
wxMOZILLA_STATE_IS_WINDOW = mozillac.wxMOZILLA_STATE_IS_WINDOW
wxMOZILLA_IS_INSECURE = mozillac.wxMOZILLA_IS_INSECURE
wxMOZILLA_IS_BROKEN = mozillac.wxMOZILLA_IS_BROKEN
wxMOZILLA_IS_SECURE = mozillac.wxMOZILLA_IS_SECURE
wxMOZILLA_SECURE_HIGH = mozillac.wxMOZILLA_SECURE_HIGH
wxMOZILLA_SECURE_MED = mozillac.wxMOZILLA_SECURE_MED
wxMOZILLA_SECURE_LOW = mozillac.wxMOZILLA_SECURE_LOW
wxMOZILLA_CONTEXT_DOCUMENT = mozillac.wxMOZILLA_CONTEXT_DOCUMENT
wxMOZILLA_CONTEXT_LINK = mozillac.wxMOZILLA_CONTEXT_LINK
wxMOZILLA_CONTEXT_TEXT = mozillac.wxMOZILLA_CONTEXT_TEXT
wxMOZILLA_CONTEXT_BACKGROUND_IMAGE = mozillac.wxMOZILLA_CONTEXT_BACKGROUND_IMAGE
wxMOZILLA_CONTEXT_IMAGE = mozillac.wxMOZILLA_CONTEXT_IMAGE
wxEVT_MOZILLA_BEFORE_LOAD = mozillac.wxEVT_MOZILLA_BEFORE_LOAD
wxEVT_MOZILLA_URL_CHANGED = mozillac.wxEVT_MOZILLA_URL_CHANGED
wxEVT_MOZILLA_STATE_CHANGED = mozillac.wxEVT_MOZILLA_STATE_CHANGED
wxEVT_MOZILLA_SECURITY_CHANGED = mozillac.wxEVT_MOZILLA_SECURITY_CHANGED
wxEVT_MOZILLA_STATUS_CHANGED = mozillac.wxEVT_MOZILLA_STATUS_CHANGED
wxEVT_MOZILLA_TITLE_CHANGED = mozillac.wxEVT_MOZILLA_TITLE_CHANGED
wxEVT_MOZILLA_LOAD_COMPLETE = mozillac.wxEVT_MOZILLA_LOAD_COMPLETE
wxEVT_MOZILLA_PROGRESS = mozillac.wxEVT_MOZILLA_PROGRESS
wxEVT_MOZILLA_RIGHT_CLICK = mozillac.wxEVT_MOZILLA_RIGHT_CLICK


#-------------- USER INCLUDE -----------------------

wx.wxMozillaBeforeLoadEventPtr = wxMozillaBeforeLoadEventPtr
wx.wxMozillaLinkChangedEventPtr = wxMozillaLinkChangedEventPtr
wx.wxMozillaStateChangedEventPtr = wxMozillaStateChangedEventPtr
wx.wxMozillaSecurityChangedEventPtr = wxMozillaSecurityChangedEventPtr
wx.wxMozillaStatusChangedEventPtr = wxMozillaStatusChangedEventPtr
wx.wxMozillaTitleChangedEventPtr = wxMozillaTitleChangedEventPtr
wx.wxMozillaLoadCompleteEventPtr = wxMozillaLoadCompleteEventPtr
wx.wxMozillaProgressEventPtr = wxMozillaProgressEventPtr
wx.wxMozillaRightClickEventPtr = wxMozillaRightClickEventPtr

__version__ = (wxMOZ_MAJOR_VERSION, wxMOZ_MINOR_VERSION, wxMOZ_RELEASE_NUMBER)
