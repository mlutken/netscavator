#include "FindToolBarWx.h"
#include "CreatorMainFrameWx.h"
#include <base/BasePageCtrl.h>
#include <base/BasePageWxIF.h>
#include <wx/CreatorBrowserControlWx.h>
#include <control/NotebookCtrl.h>



BEGIN_EVENT_TABLE(FindToolBarWx, wxPanel)
	EVT_BUTTON(ID_BtnFind, FindToolBarWx::onClicked_BtnFind)
END_EVENT_TABLE()


FindToolBarWx::FindToolBarWx(CreatorMainFrameWx* pCreatorMainFrameWx )
	: wxPanel(reinterpret_cast<wxWindow*>(pCreatorMainFrameWx), wxID_ANY, wxDefaultPosition, wxDefaultSize)
	, m_pCreatorMainFrameWx(pCreatorMainFrameWx)
{


	m_pTxtFind = new wxTextCtrl(this, ID_TxtFind, _(""));
	m_pTxtFind->SetMinSize(wxSize(200, 25));
	m_pBtnFind = new wxButton(this, ID_BtnFind, _("Search"));

	wxBoxSizer* pBoxSizer = new wxBoxSizer(wxHORIZONTAL);
	pBoxSizer->Add(m_pTxtFind);  
	pBoxSizer->Add(m_pBtnFind);  
	SetSizer(pBoxSizer);
	GetSizer()->SetSizeHints(this);
}


void FindToolBarWx::onClicked_BtnFind ( wxCommandEvent& WXUNUSED(event) )
{
#ifdef _WINDOWS
	std::string sSearchFor = m_pTxtFind->GetValue().c_str() ;
#else
    std::string sSearchFor = m_pTxtFind->GetValue().mb_str().data()  ;
#endif
	size_t iPage = m_pCreatorMainFrameWx->notebookCtrl()->activePageGet();
// 	printf("Find(%d): %s\n", iPage, sSearchFor.c_str() );
	boost::shared_ptr<BasePageCtrl> pPageCtrl = m_pCreatorMainFrameWx->notebookCtrl()->basePageCtrlGet( iPage );
	if ( pPageCtrl ) {
		pPageCtrl->searchStringSet( sSearchFor );
		pPageCtrl->findNext();
	}
}


