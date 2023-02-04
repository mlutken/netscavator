#ifndef _CREATOR_DOM_TREE_TEXT_WX_H_
#define _CREATOR_DOM_TREE_TEXT_WX_H_

#include <hacks/wx_h_include_hack.h>
#include <wx/wxprec.h>
#include "wx/richtext/richtextctrl.h"

#include <SignalsManager.h>
#include <Crawler.h>


namespace crawl {
    class WebBrowserIF;
}

class DomTreeTextWx : public wxPanel
{
//     enum
//     {
//         ID_TxtUrl = wxID_HIGHEST+1,
//         ID_BtnLoadUrl
//     };

public:

    DomTreeTextWx(wxWindow* parent, boost::shared_ptr<crawl::Crawler> pCrawler );

private:
// 	void		onClicked_BtnLoadUrl(wxCommandEvent& event);
    void 		slotPageLoaded( crawl::WebBrowserIF& mozBrowser );


private:
	// --- PRIVATE: Functions ---	
    wxColor 	getNodeColor    ( boost::shared_ptr<DOMNode> pNode ) const ;
    void 		appendNodeText	( boost::shared_ptr<DOMNode> pNode, crawl::LinearDomSearch::size_type	iPos );
	
	// --- PRIVATE: Data ---	
	
	SignalsManager::ConnectionT			m_connectionPageLoaded;
	wxRichTextCtrl* 					m_pTxtCtrl;
	boost::shared_ptr<crawl::Crawler>	m_pCrawler;
	int									m_iIndentLvl;	
// 	DECLARE_EVENT_TABLE()
};




#endif // _CREATOR_DOM_TREE_TEXT_WX_H_

