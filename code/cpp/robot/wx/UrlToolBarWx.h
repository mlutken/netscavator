#ifndef _CREATOR_URL_TOOLBAR_WX_H_
#define _CREATOR_URL_TOOLBAR_WX_H_

#include <hacks/wx_h_include_hack.h>
#include <wx/wxprec.h>

#include <SignalsManager.h>

namespace crawl {
    class WebBrowserIF;
}


class UrlToolBarWx : public wxPanel
{
    enum
    {
        ID_TxtUrl = wxID_HIGHEST+1,
        ID_BtnLoadUrl
    };

public:

    UrlToolBarWx(wxWindow* parent, crawl::WebBrowserIF* pMozBrowser );

private:
    void		onClicked_BtnLoadUrl(wxCommandEvent& event);
    void 		slotPageLoaded( crawl::WebBrowserIF& mozBrowser );


private:
	
    SignalsManager::ConnectionT		m_connectionPageLoaded;
    wxTextCtrl* 					m_pTxtUrl;
    wxButton* 						m_pBtnLoadUrl;
    crawl::WebBrowserIF*			m_pMozBrowser;
    DECLARE_EVENT_TABLE()
};




#endif // _CREATOR_URL_TOOLBAR_WX_H_

