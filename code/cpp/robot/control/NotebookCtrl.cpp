#include "NotebookCtrl.h"
#include <wx/aui/aui.h>
#include <base/BasePageCtrl.h>
#include <base/BasePageWxIF.h>

NotebookCtrl::NotebookCtrl(
        CreatorMainFrameWx* pCreatorMainFrameWx
        , wxAuiNotebook* pNotebook )
    : m_pCreatorMainFrameWx	( pCreatorMainFrameWx					)
    , m_pNotebook			( pNotebook		)
    , m_iActivePage			( -1						 			)
    , m_pActivePageWindow	( 0										)
//	, m_iActivePage			( m_pNotebook->GetSelection() 			)
//	, m_pActivePageWindow	( m_pNotebook->GetPage(m_iActivePage)	)
{
    ////printf("NotebookCtrl::CONSTRUCTOR %p\n", m_pActivePageWindow );
    ////printf("NotebookCtrl::CONSTRUCTOR: (oldpage, new page) = (%d, %d)\n", m_iActivePage, m_pNotebook->GetSelection() );
}


int NotebookCtrl::activePageGet () const
{
    return m_pNotebook->GetSelection();
}

wxWindow* NotebookCtrl::pageGet( int iPage ) const
{
    return m_pNotebook->GetPage( iPage );
}

boost::shared_ptr<BasePageCtrl>
NotebookCtrl::basePageCtrlGet	( int iPage ) const
{
    boost::shared_ptr<BasePageCtrl> pPageCtrl;
    wxWindow* pWin = pageGet ( iPage );
    BasePageWxIF* pBasePage = dynamic_cast<BasePageWxIF*>(pWin);
    if ( pBasePage ) {
        pPageCtrl = pBasePage->basePageCtrlGet();
    }
    return pPageCtrl;
}


bool NotebookCtrl::addPage(wxWindow* page, const wxString& caption, bool select, const wxBitmap& bitmap )
{
    bool bRetVal = m_pNotebook->AddPage( page, caption, select, bitmap );
	
    return bRetVal;
}


/**
\example
wxAuiNotebook* pNotebook = (wxAuiNotebook*)evt.GetEventObject();
\endexample
*/
void NotebookCtrl::notebookPageChangeSlot	( wxAuiNotebookEvent& evt )
{
    size_t iNewPage = activePageGet();
    printf("NotebookCtrl::notebookPageChangeSlot: (oldpage, new page) = (%d, %d)\n", m_iActivePage, (int)iNewPage );
	
    // --- Focus de-activate for the "OLD" tab if there is an old tab.
    if ( m_iActivePage >= 0 ) {
        boost::shared_ptr<BasePageCtrl> pOldPageCtrl = basePageCtrlGet( m_iActivePage );
        if ( pOldPageCtrl ) pOldPageCtrl->focusDeactivate();
    }
	
    // --- Focus activate for the NEW tab.
    boost::shared_ptr<BasePageCtrl> pNewPageCtrl = basePageCtrlGet( iNewPage );
    if ( pNewPageCtrl ) pNewPageCtrl->focusActivate();
	
    m_iActivePage = iNewPage;
}


// --------------------------
// --- PRIVATE: Functions ---
// --------------------------

