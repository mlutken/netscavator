#include "CreatorMainFrameWx.h"

#include "wx/app.h"
#include "wx/grid.h"
#include "wx/treectrl.h"
#include "wx/spinctrl.h"
#include "wx/artprov.h"
#include "wx/clipbrd.h"
#include "wx/image.h"
#include "wx/colordlg.h"
#include "wx/wxhtml.h"
#include "wx/imaglist.h"
#include "wx/dataobj.h"
#include "wx/dcclient.h"
#include "wx/bmpbuttn.h"
#include "wx/menu.h"
#include "wx/toolbar.h"
#include "wx/statusbr.h"
#include "wx/msgdlg.h"
#include "wx/textdlg.h"
#include "wx/textctrl.h"
#include "wx/richtext/richtextctrl.h"
#include "wx/aui/aui.h"

#include <cpaf_special_dirs.h>


#include "images/sample.xpm"


#include <WebBrowserIF.h>
#include <ScriptingClassIF.h>
#include <interfaces_types.h>
#include <Configuration.h>
#include <Globals.h>
#include <parser/DataWriterXml.h>
#include <scriptcrawl_private_php.h>
#include <php_embedding/php_embedding_utils.h>
#include <control/DomTreeTextCtrl.h>
#include <control/BrowserWindowCtrl.h>
#include <control/NotebookCtrl.h>
#include <wx/UrlToolBarWx.h>
#include <wx/FindToolBarWx.h>



BEGIN_EVENT_TABLE(CreatorMainFrameWx, wxFrame)
	EVT_ERASE_BACKGROUND(CreatorMainFrameWx::OnEraseBackground)
	EVT_SIZE(CreatorMainFrameWx::OnSize)
	EVT_MENU(CreatorMainFrameWx::ID_CreateText, CreatorMainFrameWx::OnCreateText)
    
    EVT_MENU(CreatorMainFrameWx::ID_CreatePerspective, CreatorMainFrameWx::OnCreatePerspective)
    EVT_MENU(CreatorMainFrameWx::ID_CopyPerspectiveCode, CreatorMainFrameWx::OnCopyPerspectiveCode)
    
    EVT_MENU(ID_NotebookTabFixedWidth, CreatorMainFrameWx::OnNotebookFlag)
    
    EVT_MENU(ID_NotebookAlignTop,     CreatorMainFrameWx::OnTabAlignment)
    EVT_MENU(ID_NotebookAlignBottom,  CreatorMainFrameWx::OnTabAlignment)
    
    EVT_MENU(wxID_EXIT, CreatorMainFrameWx::OnExit)
    EVT_MENU(wxID_ABOUT, CreatorMainFrameWx::OnAbout)
    EVT_UPDATE_UI(ID_NotebookTabFixedWidth, CreatorMainFrameWx::OnUpdateUI)
    EVT_MENU_RANGE(CreatorMainFrameWx::ID_FirstPerspective, CreatorMainFrameWx::ID_FirstPerspective+1000,
                   CreatorMainFrameWx::OnRestorePerspective)
    EVT_AUI_PANE_CLOSE(CreatorMainFrameWx::OnPaneClose)
    EVT_AUINOTEBOOK_ALLOW_DND(wxID_ANY, CreatorMainFrameWx::OnAllowNotebookDnD)
    EVT_AUINOTEBOOK_PAGE_CLOSE(wxID_ANY, CreatorMainFrameWx::OnNotebookPageClose)
   	EVT_AUINOTEBOOK_PAGE_CHANGED(wxID_ANY, CreatorMainFrameWx::OnNotebookPageChange) 
END_EVENT_TABLE()

using namespace crawl;

CreatorMainFrameWx::CreatorMainFrameWx(
        const SignalsManager::VoidVoidSignalT::slot_type&  onMiningDoneSlot,
        wxWindow* parent,
        wxWindowID id,
        const wxString& title,
        const wxPoint& pos,
        const wxSize& size,
        long style)
            : wxFrame(parent, id, title, pos, size, style)
            , m_onMiningDoneSlot(onMiningDoneSlot)
{
    
    
    // tell wxAuiManager to manage this frame
    m_mgr.SetManagedWindow(this);

    // set frame icon
    SetIcon(wxIcon(sample_xpm));

    // set up default notebook style
    m_notebook_style = wxAUI_NB_DEFAULT_STYLE | wxAUI_NB_TAB_EXTERNAL_MOVE | wxNO_BORDER;
    m_notebook_theme = 0;

    // create menu
    wxMenuBar* mb = new wxMenuBar;

    wxMenu* file_menu = new wxMenu;
    file_menu->Append(wxID_EXIT, _("Exit"));


    wxMenu* options_menu = new wxMenu;
    options_menu->AppendRadioItem(ID_NotebookAlignTop, _("Tab Top Alignment"));
    options_menu->AppendRadioItem(ID_NotebookAlignBottom, _("Tab Bottom Alignment"));
    options_menu->AppendCheckItem(ID_NotebookTabFixedWidth, _("Fixed-width Tabs"));
    options_menu->AppendSeparator();

    m_perspectives_menu = new wxMenu;
    m_perspectives_menu->Append(ID_CreatePerspective, _("Create Perspective"));
    m_perspectives_menu->Append(ID_CopyPerspectiveCode, _("Copy Perspective Data To Clipboard"));
    m_perspectives_menu->AppendSeparator();
    m_perspectives_menu->Append(ID_FirstPerspective+0, _("Default Startup"));
    m_perspectives_menu->Append(ID_FirstPerspective+1, _("All Panes"));

    wxMenu* help_menu = new wxMenu;
    help_menu->Append(wxID_ABOUT, _("About..."));

    mb->Append(file_menu, _("File"));
    mb->Append(m_perspectives_menu, _("Perspectives"));
    mb->Append(options_menu, _("Options"));
    mb->Append(help_menu, _("Help"));

    SetMenuBar(mb);

    CreateStatusBar();
    GetStatusBar()->SetStatusText(_("Ready"));


    // min size for the frame itself isn't completely done.
    // see the end up wxAuiManager::Update() for the test
    // code. For now, just hard code a frame minimum size
    SetMinSize(wxSize(400,300));

    m_mgr.AddPane(CreateNotebook(), wxAuiPaneInfo().Name(wxT("notebook_content")).
                  CenterPane().PaneBorder(false));


    // --- create some toolbars ---

	m_pUrlToolBar = new UrlToolBarWx ( this , m_pMozBrowser.get());
    m_mgr.AddPane( m_pUrlToolBar,
                  wxAuiPaneInfo().Name(wxT("UrlToolBar")).
                  ToolbarPane().Top().Row(2).Position(1).
                  LeftDockable(false).RightDockable(false));

	m_pFindToolBar = new FindToolBarWx ( this );
    m_mgr.AddPane( m_pFindToolBar,
                  wxAuiPaneInfo().Name(wxT("FindToolBar")).
                  ToolbarPane().Top().Row(2).Position(1).
                  LeftDockable(false).RightDockable(false));



//     wxWindow* wnd10 = CreateTextCtrl(wxT("This pane will prompt the user before hiding."));
//     m_mgr.AddPane(wnd10, wxAuiPaneInfo().
//                   Name(wxT("test10")).Caption(wxT("Text Pane with Hide Prompt")).
//                   Bottom().Layer(1).Position(1));



    // make some default perspectives
    wxString perspective_all = m_mgr.SavePerspective();

    m_mgr.GetPane(wxT("test10")).Show().Bottom().Layer(0).Row(0).Position(0);
    m_mgr.GetPane(wxT("notebook_content")).Show();
    wxString perspective_default = m_mgr.SavePerspective();

    m_perspectives.Add(perspective_default);
    m_perspectives.Add(perspective_all);
    
    
    // --- Connect slots ---
	m_connectionPageLoaded 	= m_pMozBrowser->signalsManager()->connectPageLoaded	( boost::bind(&CreatorMainFrameWx::slotPageLoaded, this, _1 ) );
    m_connectionOnMiningDone= m_pMozBrowser->signalsManager()->connectOnMiningDone	( m_onMiningDoneSlot );

    m_mgr.GetArtProvider()->SetMetric(wxAUI_DOCKART_GRADIENT_TYPE, wxAUI_GRADIENT_HORIZONTAL); // wxAUI_GRADIENT_VERTICAL, wxAUI_GRADIENT_HORIZONTAL 
    m_mgr.Update();		// "commit" all changes made to wxAuiManager
}

CreatorMainFrameWx::~CreatorMainFrameWx()
{
    m_mgr.UnInit();
	m_pMozBrowser.reset();
	m_pMozDomTreeTextWx.reset();
}



void CreatorMainFrameWx::slotPageLoaded( crawl::WebBrowserIF& mozBrowser )
{
	using namespace crawl;
	using namespace cpaf::filesystem;
	namespace fs = boost::filesystem;
	
    boost::shared_ptr<crawl::Configuration> c= crawl::g()->configuration();
    if ( crawl::rmCrawlerE == c->runMode() || crawl::rmNormalE == c->runMode()  ) return;

 ////	printf("CreatorMainFrameWx::slotPageLoaded\n");
 	
 	
 	std::string sTextHtml ;
 	m_pDomTreeTextCtrl->textHtmlGet(sTextHtml);
 	
	 	
	 	
	fs::path fileHtmlPath = special_dirs::startup / fs::path("domTree.html");	
	std::string sFileHtml = fileHtmlPath.string();
 	
    //printf( "PATH Html: %s\n", sFileHtml.c_str() );
 	
 	{
 		std::ofstream os(sFileHtml.c_str() );
 		os << sTextHtml; 
 	}
    m_pMozDomTreeTextWx->loadUri( "file://" + sFileHtml );
 	
 	
//  	std::cout << sTextHtml;
// 	std::stringstream sOut;
// 	m_pMiner->linearDom()->print(sOut, false );
// 	m_pLinearDomWindowText->SetValue( sOut.str() );
 	
//  	{
//  		std::ofstream os( "page.html" );
//  		os << sOut.str(); 
//  	}
}

void CreatorMainFrameWx::endMining ()
{
    m_pMiner->endMining(crawl::miningDoneUserExitE);
}



wxAuiDockArt* CreatorMainFrameWx::GetDockArt()
{
    return m_mgr.GetArtProvider();
}

void CreatorMainFrameWx::DoUpdate()
{
    m_mgr.Update();
}

void CreatorMainFrameWx::OnEraseBackground(wxEraseEvent& event)
{
    event.Skip();
}

void CreatorMainFrameWx::OnSize(wxSizeEvent& event)
{
    event.Skip();
}



void CreatorMainFrameWx::OnNotebookFlag(wxCommandEvent& event)
{

    int id = event.GetId();

    if (id == ID_NotebookTabFixedWidth)
    {
        m_notebook_style ^= wxAUI_NB_TAB_FIXED_WIDTH;
    }


    size_t i, count;
    wxAuiPaneInfoArray& all_panes = m_mgr.GetAllPanes();
    for (i = 0, count = all_panes.GetCount(); i < count; ++i)
    {
        wxAuiPaneInfo& pane = all_panes.Item(i);
        if (pane.window->IsKindOf(CLASSINFO(wxAuiNotebook)))
        {
            wxAuiNotebook* nb = (wxAuiNotebook*)pane.window;

            nb->SetWindowStyleFlag(m_notebook_style);
            nb->Refresh();
        }
    }
}


void CreatorMainFrameWx::OnUpdateUI(wxUpdateUIEvent& event)
{
    unsigned int flags = m_mgr.GetFlags();

    switch (event.GetId())
    {
        case ID_NotebookTabFixedWidth:
            event.Check((m_notebook_style & wxAUI_NB_TAB_FIXED_WIDTH) != 0);
            break;
    }
}

void CreatorMainFrameWx::OnPaneClose(wxAuiManagerEvent& evt)
{
    if (evt.pane->name == wxT("test10"))
    {
        int res = wxMessageBox(wxT("Are you sure you want to close/hide this pane?"),
                               wxT("wxAUI"),
                               wxYES_NO,
                               this);
        if (res != wxYES)
            evt.Veto();
    }
}

void CreatorMainFrameWx::OnCreatePerspective(wxCommandEvent& WXUNUSED(event))
{
    wxTextEntryDialog dlg(this, wxT("Enter a name for the new perspective:"),
                          wxT("wxAUI Test"));

    dlg.SetValue(wxString::Format(wxT("Perspective %u"), unsigned(m_perspectives.GetCount() + 1)));
    if (dlg.ShowModal() != wxID_OK)
        return;

    if (m_perspectives.GetCount() == 0)
    {
        m_perspectives_menu->AppendSeparator();
    }

    m_perspectives_menu->Append(ID_FirstPerspective + m_perspectives.GetCount(), dlg.GetValue());
    m_perspectives.Add(m_mgr.SavePerspective());
}

void CreatorMainFrameWx::OnCopyPerspectiveCode(wxCommandEvent& WXUNUSED(evt))
{
    wxString s = m_mgr.SavePerspective();

#if wxUSE_CLIPBOARD
    if (wxTheClipboard->Open())
    {
        wxTheClipboard->SetData(new wxTextDataObject(s));
        wxTheClipboard->Close();
    }
#endif
}

void CreatorMainFrameWx::OnRestorePerspective(wxCommandEvent& evt)
{
    m_mgr.LoadPerspective(m_perspectives.Item(evt.GetId() - ID_FirstPerspective));
}

void CreatorMainFrameWx::OnNotebookPageClose(wxAuiNotebookEvent& evt)
{
    wxAuiNotebook* ctrl = (wxAuiNotebook*)evt.GetEventObject();
    if (ctrl->GetPage(evt.GetSelection())->IsKindOf(CLASSINFO(wxHtmlWindow)))
    {
        int res = wxMessageBox(wxT("Are you sure you want to close/hide this notebook page?"),
                       wxT("wxAUI"),
                       wxYES_NO,
                       this);
        if (res != wxYES)
            evt.Veto();
    }
}

void CreatorMainFrameWx::OnNotebookPageChange(wxAuiNotebookEvent& evt)
{
    if ( m_pNotebookCtrl )	m_pNotebookCtrl->notebookPageChangeSlot( evt );
}


void CreatorMainFrameWx::OnAllowNotebookDnD(wxAuiNotebookEvent& evt)
{
    // for the purpose of this test application, explicitly
    // allow all notebook drag and drop events
    evt.Allow();
}

wxPoint CreatorMainFrameWx::GetStartPosition()
{
    static int x = 0;
    x += 20;
    wxPoint pt = ClientToScreen(wxPoint(0,0));
    return wxPoint(pt.x + x, pt.y + x);
}


void CreatorMainFrameWx::OnCreateNotebook(wxCommandEvent& WXUNUSED(event))
{
    m_mgr.AddPane(CreateNotebook(), wxAuiPaneInfo().
                  Caption(wxT("Notebook")).
                  Float().FloatingPosition(GetStartPosition()).
                  //FloatingSize(300,200).
                  CloseButton(true).MaximizeButton(true));
    m_mgr.Update();
}

void CreatorMainFrameWx::OnCreateText(wxCommandEvent& WXUNUSED(event))
{
    m_mgr.AddPane(CreateTextCtrl(), wxAuiPaneInfo().
                  Caption(wxT("Text Control")).
                  Float().FloatingPosition(GetStartPosition()));
    m_mgr.Update();
}


void CreatorMainFrameWx::OnTabAlignment(wxCommandEvent &evt)
{
   size_t i, count;
    wxAuiPaneInfoArray& all_panes = m_mgr.GetAllPanes();
    for (i = 0, count = all_panes.GetCount(); i < count; ++i)
    {
        wxAuiPaneInfo& pane = all_panes.Item(i);
        if (pane.window->IsKindOf(CLASSINFO(wxAuiNotebook)))
        {
            wxAuiNotebook* nb = (wxAuiNotebook*)pane.window;

            if (evt.GetId() == ID_NotebookAlignTop)
                nb->SetWindowStyleFlag(nb->GetWindowStyleFlag()^wxAUI_NB_BOTTOM|wxAUI_NB_TOP);
           else if (evt.GetId() == ID_NotebookAlignBottom)
               nb->SetWindowStyleFlag(nb->GetWindowStyleFlag()^wxAUI_NB_TOP|wxAUI_NB_BOTTOM);
            nb->Refresh();
        }
    }
}

void CreatorMainFrameWx::OnExit(wxCommandEvent& WXUNUSED(event))
{
    Close(true);
}

void CreatorMainFrameWx::OnAbout(wxCommandEvent& WXUNUSED(event))
{
    wxMessageBox(_("Crawler Robot\nAn advanced Webcrawler\n(c) Copyright 2012, Nitram"), _("About Crawler Robot"), wxOK, this);
}

wxTextCtrl* CreatorMainFrameWx::CreateTextCtrl(const wxString& ctrl_text)
{
    static int n = 0;

    wxString text;
    if (ctrl_text.Length() > 0)
        text = ctrl_text;
    else
        text.Printf(wxT("This is text box %d"), ++n);

    return new wxTextCtrl(this,wxID_ANY, text,
                          wxPoint(0,0), wxSize(150,90),
                          wxNO_BORDER | wxTE_MULTILINE);
}


wxAuiNotebook* CreatorMainFrameWx::CreateNotebook()
{
    // create the notebook off-window to avoid flicker
    wxSize client_size = GetClientSize();

	m_pNotebook = new wxAuiNotebook(this, wxID_ANY,
                                    wxPoint(client_size.x, client_size.y),
                                    wxSize(430,200),
                                    m_notebook_style);

    m_pNotebookCtrl = boost::shared_ptr<NotebookCtrl> ( new NotebookCtrl(this, this->notebook()) ) ;
	wxBitmap page_bmp = wxArtProvider::GetBitmap(wxART_NORMAL_FILE, wxART_OTHER, wxSize(16,16));

    // --- ---
    boost::shared_ptr<crawl::Configuration> c= crawl::g()->configuration();
    boost::shared_ptr<crawl::ScriptingClassIF> pScriptingClass = createPhpScriptingClass();
    std::string sMinerName = "";

    std::string sFunName = "Script_minerName" ;
    if ( pScriptingClass->scriptFunctionExists(sFunName) ) sMinerName = pScriptingClass->callScriptFunction_String ( sFunName, sMinerName ) ;

    sFunName = "currentMiner" ;
    if ( sMinerName == "" ) {
        sMinerName = pScriptingClass->callScriptFunction_String ( sFunName ) ;
    }
    if ( sMinerName == "" ) sMinerName = "Crawler" ;

    std::string sBaseOutputName = sMinerName;

    sFunName = "TEMPLATE_baseOutputName" ;
    if ( pScriptingClass->scriptFunctionExists(sFunName) ) sBaseOutputName = pScriptingClass->callScriptFunction_String ( sFunName, sMinerName ) ;

    sFunName = sMinerName + "_baseOutputName" ;
    if ( pScriptingClass->scriptFunctionExists(sFunName) ) sBaseOutputName = pScriptingClass->callScriptFunction_String ( sFunName ) ;
    printf( "BaseOutputName: %s\n", sBaseOutputName.c_str() );

    std::string sUrlSite = "";
    sFunName = sMinerName + "_urlSite";
    if ( pScriptingClass->scriptFunctionExists(sFunName) ) sUrlSite = pScriptingClass->callScriptFunction_String ( sFunName );
    ////boost::shared_ptr<std::ofstream> pOstream( new std::ofstream( (sBaseOutputName + ".xml").c_str() ) );

	// -------------------------
	// --- m_pBrowserWindow ---
	// -------------------------
	m_pBrowserWindow = new CreatorBrowserControlWx( m_pNotebook );
    m_pMozBrowser = boost::shared_ptr<MozBrowserWx>( new MozBrowserWx(m_pBrowserWindow) );
    m_pMozBrowser->runModeSet( c->runMode() );
	m_pBrowserWindow->initWebBrowser( m_pMozBrowser-> webBrowser()->ifMoz() );
    m_pXmlOut = boost::shared_ptr<crawl::DataWriterXml>( new DataWriterXml(sBaseOutputName) );
    StringSearch::DataWriterVecT writers;
    writers.push_back(m_pXmlOut);

    m_pMiner = boost::shared_ptr<ScriptMiner>(
            new ScriptMiner(m_pMozBrowser,sMinerName, sBaseOutputName, crawl::Url(sUrlSite), writers, pScriptingClass, c )
        );
    setMinerPointerRaw(m_pMiner.get());
////    m_pMiner->assignConfiguration( c );
////    m_pMiner->assignScriptingClass(pScriptingClass);

//    std::string sUrl = c->valueStrGet("url");
//    if ( sUrl == "" ) sUrl = "http://airplaymusic.dk.localhost";
//    m_pMiner->loadURI( sUrl );
    m_pMiner->startMining();
    m_pMiner->show();
    m_pMiner->refresh();

	
	// -----------------------------------
	// --- m_pDomTreeTextWindow (text) ---
	// -----------------------------------
	m_pDomTreeTextWindow = new CreatorBrowserControlWx( m_pNotebook );
	m_pMozDomTreeTextWx = MozBrowserWx::Ptr( new MozBrowserWx(m_pDomTreeTextWindow) );
	m_pDomTreeTextWindow->initWebBrowser( m_pMozDomTreeTextWx-> webBrowser()->ifMoz() );
	m_pMozDomTreeTextWx->show(); 

		
 	m_pBrowserWindowCtrl = boost::shared_ptr<BrowserWindowCtrl>( new BrowserWindowCtrl( this ) );
	m_pDomTreeTextCtrl = boost::shared_ptr<DomTreeTextCtrl>( new DomTreeTextCtrl( this ) );
	
	m_pBrowserWindow->basePageCtrlSet( m_pBrowserWindowCtrl );
	m_pDomTreeTextWindow->basePageCtrlSet( m_pDomTreeTextCtrl );
	
	
	m_pNotebookCtrl->addPage(m_pBrowserWindow, wxT("Browser") , false, page_bmp);
	m_pNotebookCtrl->addPage(m_pDomTreeTextWindow, wxT("DOM tree") , false, page_bmp);
	
// 	m_pLinearDomWindowText = new wxTextCtrl( m_pNotebook, wxID_ANY, wxT("Some text"), wxDefaultPosition, wxDefaultSize, wxTE_MULTILINE|wxNO_BORDER );
// 	m_pNotebook->AddPage( m_pLinearDomWindowText, wxT("Dom window"), false, page_bmp );
	
	
// 	m_pDomWindowText = new DomTreeTextWx( m_pNotebook, m_pMiner ) ;
// 	m_pNotebook->AddPage( m_pDomWindowText, wxT("DomTreeTextWx") , false, page_bmp );

// 	ctrl->AddPage( new wxTextCtrl( m_pNotebook, wxID_ANY, wxT("Some more text"),
// 				wxDefaultPosition, wxDefaultSize, wxTE_MULTILINE|wxNO_BORDER) , wxT("wxTextCtrl 2") );
	
	return m_pNotebook;
}



