from wxPython.wx import *
import string

from wxPython.mozilla import *

ID_NEW = wxNewId()
ID_OPEN = wxNewId()
ID_SAVE = wxNewId()
ID_QUIT = wxNewId()

ID_UNDO = wxNewId()
ID_REDO = wxNewId()
ID_REMOVE_LINK = wxNewId()

class MozillaEditor(wxFrame):
    def __init__(self):
        wxFrame.__init__(self,NULL, -1, "Mozilla Editor Demo")
        self.current = "about:blank"

        print "Initializing wxMozillaEditor..."
        self.menu = wxMenuBar()
        self.filemenu = wxMenu()
        self.filemenu.Append(ID_NEW, "New")
        self.filemenu.Append(ID_OPEN, "Open")
        self.filemenu.Append(ID_SAVE, "Save")
        #self.filemenu.Append(ID_QUIT, "Exit")
        self.editmenu = wxMenu()
        self.editmenu.Append(ID_UNDO, "Undo")
        self.editmenu.Append(ID_REDO, "Redo")
        self.editmenu.AppendSeparator()
        self.editmenu.Append(ID_REMOVE_LINK, "Remove Link")
        self.menu.Append(self.filemenu, "File")
        self.menu.Append(self.editmenu, "Edit")
        self.SetMenuBar(self.menu)
        sizer = wxBoxSizer(wxVERTICAL)
        btnSizer = wxBoxSizer(wxHORIZONTAL)

        self.mozilla = wxMozillaBrowser(self, -1, style = wxNO_FULL_REPAINT_ON_RESIZE)

        self.fonts = ["Helvetica, Arial, sans-serif", "Times New Roman, Times, serif", "Courier New, Courier, monospace"]
        self.fontlist = wxComboBox(self, wxNewId(), self.fonts[0], choices=self.fonts,style=wxCB_DROPDOWN|wxPROCESS_ENTER)
        self.mozilla.EditCommand("cmd_fontFace", self.fonts[0])
        btnSizer.Add(self.fontlist, 0, wxEXPAND|wxALL, 2)

        #btn = wxButton(self, wxNewId(), "Open", style=wxBU_EXACTFIT)
        #EVT_BUTTON(self, btn.GetId(), self.OnOpenButton)
        #btnSizer.Add(btn, 0, wxEXPAND|wxALL, 2)

        btn = wxButton(self, wxNewId(), "B", style=wxBU_EXACTFIT)
        EVT_BUTTON(self, btn.GetId(), self.OnBoldButton)
        btnSizer.Add(btn, 0, wxEXPAND|wxALL, 2)

        btn = wxButton(self, wxNewId(), "I", style=wxBU_EXACTFIT)
        EVT_BUTTON(self, btn.GetId(), self.OnItalicButton)
        btnSizer.Add(btn, 0, wxEXPAND|wxALL, 2)

        btn = wxButton(self, wxNewId(), "U", style=wxBU_EXACTFIT)
        EVT_BUTTON(self, btn.GetId(), self.OnUnderlineButton)
        btnSizer.Add(btn, 0, wxEXPAND|wxALL, 2)

        btn = wxButton(self, wxNewId(), "L", style=wxBU_EXACTFIT)
        EVT_BUTTON(self, btn.GetId(), self.OnLeftAlignButton)
        btnSizer.Add(btn, 0, wxEXPAND|wxALL, 2)

        btn = wxButton(self, wxNewId(), "C", style=wxBU_EXACTFIT)
        EVT_BUTTON(self, btn.GetId(), self.OnCenterAlignButton)
        btnSizer.Add(btn, 0, wxEXPAND|wxALL, 2)

        btn = wxButton(self, wxNewId(), "R", style=wxBU_EXACTFIT)
        EVT_BUTTON(self, btn.GetId(), self.OnRightAlignButton)
        btnSizer.Add(btn, 0, wxEXPAND|wxALL, 2)

        btn = wxButton(self, wxNewId(), "A", style=wxBU_EXACTFIT)
        EVT_BUTTON(self, btn.GetId(), self.OnFontIncreaseButton)
        btnSizer.Add(btn, 0, wxEXPAND|wxALL, 2)

        btn = wxButton(self, wxNewId(), "a", style=wxBU_EXACTFIT)
        EVT_BUTTON(self, btn.GetId(), self.OnFontDecreaseButton)
        btnSizer.Add(btn, 0, wxEXPAND|wxALL, 2)

        btn = wxButton(self, wxNewId(), "Color", style=wxBU_EXACTFIT)
        EVT_BUTTON(self, btn.GetId(), self.OnFontColorButton)
        btnSizer.Add(btn, 0, wxEXPAND|wxALL, 2)

        btn = wxButton(self, wxNewId(), "<-", style=wxBU_EXACTFIT)
        EVT_BUTTON(self, btn.GetId(), self.OnOutdentButton)
        btnSizer.Add(btn, 0, wxEXPAND|wxALL, 2)

        btn = wxButton(self, wxNewId(), "->", style=wxBU_EXACTFIT)
        EVT_BUTTON(self, btn.GetId(), self.OnIndentButton)
        btnSizer.Add(btn, 0, wxEXPAND|wxALL, 2)

        btn = wxButton(self, wxNewId(), "Link", style=wxBU_EXACTFIT)
        EVT_BUTTON(self, btn.GetId(), self.OnLinkButton)
        btnSizer.Add(btn, 0, wxEXPAND|wxALL, 2)

        btn = wxButton(self, wxNewId(), "Image", style=wxBU_EXACTFIT)
        EVT_BUTTON(self, btn.GetId(), self.OnImageButton)
        btnSizer.Add(btn, 0, wxEXPAND|wxALL, 2)

        btn = wxButton(self, wxNewId(), "HR", style=wxBU_EXACTFIT)
        EVT_BUTTON(self, btn.GetId(), self.OnHRButton)
        btnSizer.Add(btn, 0, wxEXPAND|wxALL, 2)

        #txt = wxStaticText(self, -1, "Location:")
        #btnSizer.Add(txt, 0, wxCENTER|wxALL, 2)

        #self.location = wxComboBox(self, wxNewId(), "", style=wxCB_DROPDOWN|wxPROCESS_ENTER)
        EVT_COMBOBOX(self, self.fontlist.GetId(), self.OnFontSelect)
        #EVT_KEY_UP(self.location, self.OnLocationKey)
        #EVT_CHAR(self.location, self.IgnoreReturn)
        EVT_MENU(self, ID_NEW, self.OnNew)
        EVT_MENU(self, ID_OPEN, self.OnOpen)
        EVT_MENU(self, ID_SAVE, self.OnSave)
        #EVT_MENU(self, ID_QUIT, self.OnQuit)
        EVT_MENU(self, ID_UNDO, self.OnUndo)
        EVT_MENU(self, ID_REDO, self.OnRedo)
        EVT_MENU(self, ID_REMOVE_LINK, self.OnRemoveLink)
        #btnSizer.Add(self.location, 1, wxEXPAND|wxALL, 2)


        sizer.Add(btnSizer, 0, wxEXPAND)
        sizer.Add(self.mozilla, 1, wxEXPAND)

        self.mozilla.MakeEditable()
        self.mozilla.LoadURL(self.current)
        #self.location.Append(self.current)

        self.SetSizer(sizer)
        self.SetAutoLayout(true)
        EVT_SIZE(self, self.OnSize)

    def ShutdownDemo(self):
        # put the frame title back
        if self:
            self.SetTitle(self.titleBase)

    def OnSize(self, evt):
        self.Layout()

    def OnRemoveLink(self, evt):
        self.mozilla.EditCommand("cmd_removeLinks")

    def OnBoldButton(self, evt):
        self.mozilla.EditCommand("cmd_bold")

    def OnItalicButton(self, evt):
        self.mozilla.EditCommand("cmd_italic")

    def OnUnderlineButton(self, evt):
        self.mozilla.EditCommand("cmd_underline")

    def OnLeftAlignButton(self, evt):
        self.mozilla.EditCommand("cmd_align", "left")

    def OnCenterAlignButton(self, evt):
        self.mozilla.EditCommand("cmd_align", "center")

    def OnRightAlignButton(self, evt):
        self.mozilla.EditCommand("cmd_align", "right")

    def OnOutdentButton(self, evt):
        self.mozilla.EditCommand("cmd_outdent")

    def OnIndentButton(self, evt):
        self.mozilla.EditCommand("cmd_indent")

    def OnUndo(self, evt):
        self.mozilla.EditCommand("cmd_undo")

    def OnFontSelect(self, evt):
        self.mozilla.EditCommand("cmd_fontFace", self.fontlist.GetStringSelection())

    def OnRedo(self, evt):
        self.mozilla.EditCommand("cmd_redo")

    def OnLinkButton(self, evt):    
        dialog = wxTextEntryDialog(self, "Please enter a URL.")
        if dialog.ShowModal() == wxID_OK:
            self.mozilla.EditCommand("cmd_insertLinkNoUI", dialog.GetValue())

    def OnImageButton(self, evt):
        imageFormats = "Image files|*.gif;*.jpg;*.png;*.jpeg;*.bmp"
        dialog = wxFileDialog(self, "Select an image", "","", imageFormats, wxOPEN)
        if dialog.ShowModal() == wxID_OK:
            self.mozilla.EditCommand("cmd_insertImageNoUI", "file://" + dialog.GetPath())

    def OnHRButton(self, evt):    
        self.mozilla.EditCommand("cmd_insertHR")

    def OnFontIncreaseButton(self, evt):    
        self.mozilla.EditCommand("cmd_increaseFont")

    def OnFontDecreaseButton(self, evt):    
        self.mozilla.EditCommand("cmd_decreaseFont")

    def OnFontColorButton(self, evt):
        dlg = wxColourDialog(self)
        dlg.GetColourData().SetChooseFull(true)
        if dlg.ShowModal() == wxID_OK:
            data = dlg.GetColourData().GetColour().Get() #RGB tuple
            red = string.replace(str(hex(data[0])), "0x", "")
            if len(red) == 1:
                red = "0" + red
            green = string.replace(str(hex(data[1])), "0x", "")
            if len(green) == 1:
                green = "0" + green
            blue = string.replace(str(hex(data[2])), "0x", "")
            if len(blue) == 1:
                blue = "0" + blue
            value = "#" + red + green + blue
            print value
            self.mozilla.EditCommand("cmd_fontColor", value)
        dlg.Destroy()

    def OnLocationSelect(self, evt):
        #url = self.location.GetStringSelection()
        self.log.write('OnLocationSelect: %s\n' % url)
        self.mozilla.LoadURL(url)

    def OnLocationKey(self, evt):
        if evt.KeyCode() == WXK_RETURN:
            #URL = self.location.GetValue()
            #self.location.Append(URL)
            self.mozilla.LoadURL(URL)
        else:
            evt.Skip()


    def IgnoreReturn(self, evt):
        if evt.GetKeyCode() != WXK_RETURN:
            evt.Skip()

    def OnNew(self, event):
        self.mozilla.LoadURL("about:blank")

    def OnOpen(self, event):
        dlg = wxFileDialog(self, "Select a file", "", "", "HTML Files (*.html)|*.html", wxOPEN)
        dlg.CentreOnParent()
        if dlg.ShowModal() == wxID_OK:
            self.current = dlg.GetPath()
            self.mozilla.LoadURL(self.current)
        dlg.Destroy()

    def OnSave(self, event):
        dlg = wxFileDialog(self, "Save to disk", "", "", "HTML Files (*.html)|*.html", wxSAVE)
        dlg.CentreOnParent()
        if dlg.ShowModal() == wxID_OK:
            self.current = dlg.GetPath()
            self.mozilla.SavePage(self.current)
        dlg.Destroy()

#----------------------------------------------------------------------
# for the demo framework...

#def runTest(frame, nb, log):
#    if wxPlatform == '__WXMSW__':
#        win = TestPanel(nb, log, frame) #TestPanel(nb, log, frame)
#        return win
#    else:
#        dlg = wxMessageDialog(frame, 'This demo only works on MSW.',
#                          'Sorry', wxOK | wxICON_INFORMATION)
#        dlg.ShowModal()
#        dlg.Destroy()



overview = """\
<html><body>
<h2>wxMozillaEditor</h2>

The wxMozillaEditor example shows how the wxMozillaBrowser can be used as an HTML Editor.
<p>Once you call MakeEditable(), you can use the DoCommand interface to send editing commands to wxMozilla. 
The example uses many of the commands available, but not all.

<p>If you want to learn the other commands, you will need to refer
to Mozilla's Editor Embedding Guide. Here is a link:

<p><a href="http://lxr.mozilla.org/seamonkey/source/editor/docs/Editor_Embedding_Guide.html">http://lxr.mozilla.org/seamonkey/source/editor/docs/Editor_Embedding_Guide.html</a>
</body></html>
"""

class MyApp(wxApp):
    def OnInit(self):
        self.frame = MozillaEditor()
        self.frame.Show(True)
        self.SetTopWindow(self.frame)
        return True

app = MyApp(0)
app.MainLoop()

