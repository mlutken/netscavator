
from wxPython.wx import *

from wxPython.mozilla import *
import string

ID_OPEN_NEW_WINDOW = wxNewId()
#----------------------------------------------------------------------
class MozillaBrowser(wxFrame):
    def __init__(self):
        wxFrame.__init__(self,NULL, -1, "Mozilla Browser Demo")
        self.current = "http://www.mozilla.org/"
        self.selLink = ""

        sizer = wxBoxSizer(wxVERTICAL)
        btnSizer = wxBoxSizer(wxHORIZONTAL)
        self.mozilla = wxMozillaBrowser(self, 101, style = wxNO_FULL_REPAINT_ON_RESIZE)
        self.CreateStatusBar()
        self.openBtn = wxButton(self, wxNewId(), "Open", style=wxBU_EXACTFIT)
        EVT_BUTTON(self, self.openBtn.GetId(), self.OnOpenButton)
        btnSizer.Add(self.openBtn, 0, wxEXPAND|wxALL, 2)

        self.backBtn = wxButton(self, wxNewId(), "<--", style=wxBU_EXACTFIT)
        EVT_BUTTON(self, self.backBtn.GetId(), self.OnPrevPageButton)
        btnSizer.Add(self.backBtn, 0, wxEXPAND|wxALL, 2)

        self.nextBtn = wxButton(self, wxNewId(), "-->", style=wxBU_EXACTFIT)
        EVT_BUTTON(self, self.nextBtn.GetId(), self.OnNextPageButton)
        btnSizer.Add(self.nextBtn, 0, wxEXPAND|wxALL, 2)

        self.stopBtn = wxButton(self, wxNewId(), "Stop", style=wxBU_EXACTFIT)
        EVT_BUTTON(self, self.stopBtn.GetId(), self.OnStopButton)
        btnSizer.Add(self.stopBtn, 0, wxEXPAND|wxALL, 2)

        btn = wxButton(self, wxNewId(), "Refresh", style=wxBU_EXACTFIT)
        EVT_BUTTON(self, btn.GetId(), self.OnRefreshPageButton)
        btnSizer.Add(btn, 0, wxEXPAND|wxALL, 2)

        txt = wxStaticText(self, -1, "Location:")
        btnSizer.Add(txt, 0, wxCENTER|wxALL, 2)

        self.location = wxComboBox(self, wxNewId(), "", style=wxCB_DROPDOWN|wxPROCESS_ENTER)
        EVT_COMBOBOX(self, self.location.GetId(), self.OnLocationSelect)
        EVT_KEY_UP(self.location, self.OnLocationKey)
        EVT_CHAR(self.location, self.IgnoreReturn)
        btnSizer.Add(self.location, 1, wxEXPAND|wxALL, 2)
        btnSizer.Add((1, 1), 1, wxEXPAND)

        sizer.Add(btnSizer, 0, wxEXPAND)
        sizer.Add(self.mozilla, 1, wxEXPAND)

        #self.mozilla.LoadURL(self.current)
        #self.location.Append(self.current)

        self.SetSizer(sizer)
        self.SetAutoLayout(true)
        #EVT_SIZE(self, self.OnSize)

        # Hook up the event handlers for the Mozilla window
        EVT_MOZILLA_BEFORE_LOAD(self.mozilla, self.mozilla.GetId(), self.BeforeLoad)
        EVT_MOZILLA_URL_CHANGED(self.mozilla, self.mozilla.GetId(), self.UpdateURL)
        EVT_MOZILLA_STATUS_CHANGED(self.mozilla, self.mozilla.GetId(), self.UpdateStatus)
        EVT_MOZILLA_LOAD_COMPLETE(self.mozilla, self.mozilla.GetId(), self.OnLoadComplete)
        EVT_MOZILLA_STATE_CHANGED(self.mozilla, self.mozilla.GetId(), self.UpdateState)
        EVT_MOZILLA_RIGHT_CLICK(self.mozilla, self.mozilla.GetId(), self.OnRightClick)
        EVT_MENU(self, ID_OPEN_NEW_WINDOW, self.OpenInNewWindow)

    def testing(self, evt):
        wxMessageBox("Called!")

    def BeforeLoad(self, evt):
        if string.find(evt.GetURL(), "microsoft.com/windows/ie") != -1:
            result = wxMessageDialog(self, "Are you sure you want to load the IE homepage? <sniff, sniff>", "Load IE homepage...!?", wxYES_NO).ShowModal()
            if result == wxID_NO:
                self.mozilla.Stop()

    def UpdateURL(self, evt):
        self.location.Append(evt.GetNewURL())
        self.backBtn.Enable(evt.CanGoBack())
        self.nextBtn.Enable(evt.CanGoForward())

    def OpenInNewWindow(self, evt):
        newwindow = MozillaBrowser()
        newwindow.Show()
        newwindow.mozilla.LoadURL(self.selLink)

    def UpdateStatus(self, evt):
        self.SetStatusText(evt.GetStatusText())

    def UpdateState(self, evt):
         if (evt.GetState() & wxMOZILLA_STATE_START) or (evt.GetState() & wxMOZILLA_STATE_TRANSFERRING):
             self.SetStatusText("Loading " + evt.GetURL() + "...")
         elif evt.GetState() & wxMOZILLA_STATE_NEGOTIATING:
             self.SetStatusText("Contacting server...")
         elif evt.GetState() & wxMOZILLA_STATE_REDIRECTING:
             self.SetStatusText("Redirecting from " + evt.GetURL())

    def OnLoadComplete(self, evt):
        self.SetStatusText("")
        self.SetTitle("wxMozilla - " + self.mozilla.GetTitle())

    def OnRightClick(self, evt):
        contextMenu = wxMenu()
        if evt.GetLinks() != "":
            self.selLink = evt.GetLink()
            contextMenu.Append(ID_OPEN_NEW_WINDOW, "Open in New Window")

        self.PopupMenu(contextMenu, evt.GetPosition())

    def OnSize(self, evt):
        self.Layout()
        self.panel.Layout()

    def OnLocationSelect(self, evt):
        url = self.location.GetStringSelection()
        self.mozilla.LoadURL(url)

    def OnLocationKey(self, evt):
        if evt.KeyCode() == WXK_RETURN:
            URL = self.location.GetValue()
            self.location.Append(URL)
            self.mozilla.LoadURL(URL)
        else:
            evt.Skip()


    def IgnoreReturn(self, evt):
        if evt.GetKeyCode() != WXK_RETURN:
            evt.Skip()

    def OnOpenButton(self, event):
        dlg = wxTextEntryDialog(self, "Open Location",
                                "Enter a full URL or local path",
                                self.current, wxOK|wxCANCEL)
        dlg.CentreOnParent()
        if dlg.ShowModal() == wxID_OK:
            self.current = dlg.GetValue()
            self.mozilla.LoadURL(self.current)
        dlg.Destroy()

    def OnPrevPageButton(self, event):
        self.mozilla.GoBack()

    def OnNextPageButton(self, event):
        self.mozilla.GoForward()

    def OnStopButton(self, evt):
        self.mozilla.Stop()

    def OnRefreshPageButton(self, evt):
        self.mozilla.Reload()


overview = """\
<html><body>
<h2>wxMozilla</h2>

The wxMozilla example shows how to use the wxMozillaBrowser to embed Mozilla into
a wxPython application. 
</body></html>
"""

class MyApp(wxApp):
    def OnInit(self):
        self.frame = MozillaBrowser()
        self.frame.Show(True)
        self.SetTopWindow(self.frame)
        return True

app = MyApp(0)
app.MainLoop()


#----------------------------------------------------------------------

