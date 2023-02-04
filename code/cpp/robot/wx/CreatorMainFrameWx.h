#ifndef _CREATOR_MAIN_FRAME_WX_H_
#define _CREATOR_MAIN_FRAME_WX_H_

#include <hacks/wx_h_include_hack.h>
#include <wx/wxprec.h>

#include <wx/aui/aui.h>
#include <wx/wxhtml.h>

#include <wx/CreatorBrowserControlWx.h>
#include <wx/DomTreeTextWx.h>

#include <SignalsManager.h>
#include <ScriptMiner.h>
#include <MozBrowserWx.h>

class FindToolBarWx;
class UrlToolBarWx;
class DomTreeTextCtrl;
class BrowserWindowCtrl;
class NotebookCtrl;

namespace crawl {
    class DataWriterXml;
}


// EVT_AUINOTEBOOK_PAGE_CLOSED, wxEVT_COMMAND_NOTEBOOK_PAGE_CHANGED

class CreatorMainFrameWx : public wxFrame
{
    enum
    {
        ID_CreateTree = wxID_HIGHEST+1,
        ID_CreateText,
        ID_CreateHTML,
        ID_CreateNotebook,
        ID_TextContent,
        ID_HTMLContent,
        ID_NotebookContent,
        ID_CreatePerspective,
        ID_CopyPerspectiveCode,
        ID_NotebookTabFixedWidth,
        ID_NotebookAlignTop,
        ID_NotebookAlignBottom,
        ID_FirstPerspective = ID_CreatePerspective+1000
    };

public:
    CreatorMainFrameWx(
            const SignalsManager::VoidVoidSignalT::slot_type&  onMiningDoneSlot,
            wxWindow* parent,
            wxWindowID id,
            const wxString& title,
            const wxPoint& pos = wxDefaultPosition,
            const wxSize& size = wxDefaultSize,
            long style = wxDEFAULT_FRAME_STYLE | wxSUNKEN_BORDER);

    ~CreatorMainFrameWx();

    wxAuiDockArt* 	GetDockArt();
    void 			DoUpdate();
    void            endMining ();

    boost::shared_ptr<ScriptMiner>          miner				() const	{ return m_pMiner;              }
    boost::shared_ptr<crawl::WebBrowserIF>	mozDomTreeText		() const	{ return m_pMozDomTreeTextWx; 	}
    boost::shared_ptr<DomTreeTextCtrl>		domTreeTextCtrl		() const	{ return m_pDomTreeTextCtrl;	}
    boost::shared_ptr<BrowserWindowCtrl>	browserWindowCtrl	() const	{ return m_pBrowserWindowCtrl;	}
    boost::shared_ptr<NotebookCtrl>			notebookCtrl		() const	{ return m_pNotebookCtrl;		}
    CreatorBrowserControlWx* 				browserWindow		() const	{ return m_pBrowserWindow;		}
    CreatorBrowserControlWx* 				domTreeTextWindow	() const	{ return m_pDomTreeTextWindow;	}
    UrlToolBarWx* 							urlToolBar			() const 	{ return m_pUrlToolBar;			}
    FindToolBarWx* 							findToolBar			() const	{ return m_pFindToolBar;		}
    wxAuiNotebook*							notebook			() const	{ return m_pNotebook;			}

private:
    wxTextCtrl* 		CreateTextCtrl(const wxString& text = wxEmptyString);
    wxPoint 			GetStartPosition();
    wxHtmlWindow* 		CreateHTMLCtrl(wxWindow* parent = NULL);
    wxAuiNotebook* 		CreateNotebook();

    wxString 			GetIntroText();

private:

    void OnEraseBackground(wxEraseEvent& evt);
    void OnSize(wxSizeEvent& evt);

    void OnCreateHTML(wxCommandEvent& evt);
    void OnCreateNotebook(wxCommandEvent& evt);
    void OnCreateText(wxCommandEvent& evt);
    
    void OnCreatePerspective(wxCommandEvent& evt);
    void OnCopyPerspectiveCode(wxCommandEvent& evt);
    void OnRestorePerspective(wxCommandEvent& evt);
    
    void OnAllowNotebookDnD(wxAuiNotebookEvent& evt);
    void OnNotebookPageClose(wxAuiNotebookEvent& evt);
    void OnNotebookPageChange(wxAuiNotebookEvent& evt);
    
    void OnExit(wxCommandEvent& evt);
    void OnAbout(wxCommandEvent& evt);
    void OnTabAlignment(wxCommandEvent &evt);

    void OnNotebookFlag(wxCommandEvent& evt);
    void OnUpdateUI(wxUpdateUIEvent& evt);

    void OnPaneClose(wxAuiManagerEvent& evt);

    void 		slotPageLoaded  ( crawl::WebBrowserIF& mozBrowser );
    //void		slotContextMenu ( boost::uint32_t iContextFlags, boost::shared_ptr<crawl::DomEventIF> pDOMEvent, boost::shared_ptr<DOMNode> pDOMNode );


private:
    SignalsManager::VoidVoidSignalT::slot_type  m_onMiningDoneSlot;
    SignalsManager::ConnectionT				m_connectionOnMiningDone;
    SignalsManager::ConnectionT				m_connectionPageLoaded;
    SignalsManager::ConnectionT				m_connectionContextMenu;
    boost::shared_ptr<crawl::DataWriterXml> m_pXmlOut;
    boost::shared_ptr<ScriptMiner>          m_pMiner;
    wxAuiManager 							m_mgr;
    wxArrayString 							m_perspectives;
    wxMenu* 								m_perspectives_menu;
    long 									m_notebook_style;
    long 									m_notebook_theme;
    boost::shared_ptr<MozBrowserWx>			m_pMozBrowser;
    boost::shared_ptr<MozBrowserWx>			m_pMozDomTreeTextWx;
    CreatorBrowserControlWx* 				m_pBrowserWindow;
    CreatorBrowserControlWx* 				m_pDomTreeTextWindow;
    wxAuiNotebook*							m_pNotebook;
    UrlToolBarWx* 							m_pUrlToolBar;
    FindToolBarWx* 							m_pFindToolBar;
    DomTreeTextWx* 							m_pDomWindowText;
    wxTextCtrl*								m_pLinearDomWindowText;
    boost::shared_ptr<DomTreeTextCtrl>		m_pDomTreeTextCtrl;
    boost::shared_ptr<BrowserWindowCtrl>	m_pBrowserWindowCtrl;
    boost::shared_ptr<NotebookCtrl>			m_pNotebookCtrl;
	
// 	wxRichTextCtrl*					m_pLinearDomWindowText;
// 	wxHtmlWindow*					m_pLinearDomWindowHtml;
	
    DECLARE_EVENT_TABLE()
};



#endif // _CREATOR_MAIN_FRAME_WX_H_

