#include <string>
#include "UrlToolBarWx.h"

#include <url/Url.h>
#include <WebBrowserIF.h>


BEGIN_EVENT_TABLE(UrlToolBarWx, wxPanel)
    EVT_BUTTON(ID_BtnLoadUrl, UrlToolBarWx::onClicked_BtnLoadUrl)
END_EVENT_TABLE()


UrlToolBarWx::UrlToolBarWx(wxWindow* parent, crawl::WebBrowserIF* pMozBrowser )
    : wxPanel(parent, wxID_ANY, wxDefaultPosition, wxDefaultSize)
    , m_pMozBrowser(pMozBrowser)
{

    m_connectionPageLoaded = m_pMozBrowser->signalsManager()->connectPageLoaded	( boost::bind(&UrlToolBarWx::slotPageLoaded, this, _1 ) );

    m_pTxtUrl = new wxTextCtrl(this, ID_TxtUrl, _("URL"));
    m_pTxtUrl->SetMinSize(wxSize(300, 25));
    m_pBtnLoadUrl = new wxButton(this, ID_BtnLoadUrl, _("Load"));

    wxBoxSizer* pBoxSizer = new wxBoxSizer(wxHORIZONTAL);
    pBoxSizer->Add(m_pTxtUrl);
    pBoxSizer->Add(m_pBtnLoadUrl);
    SetSizer(pBoxSizer);
    GetSizer()->SetSizeHints(this);
}


void UrlToolBarWx::onClicked_BtnLoadUrl ( wxCommandEvent& WXUNUSED(event) )
{
#ifdef _WINDOWS
    crawl::Url url( m_pTxtUrl->GetValue().c_str() );
#else
    crawl::Url url( m_pTxtUrl->GetValue().mb_str().data() );
#endif
    if ( !url.hasProtocol() ) url.protocolSet("http");
    std::string sUrl = url.parsedString();
    m_pMozBrowser->loadUri(sUrl);
#ifdef _WINDOWS
    m_pTxtUrl->SetValue(sUrl);
#else
    m_pTxtUrl->SetValue( wxString(sUrl.c_str(), wxConvUTF8) );
#endif
}


void UrlToolBarWx::slotPageLoaded( crawl::WebBrowserIF& mozBrowser )
{
////    printf("UrlToolBarWx::slotPageLoaded\n");
#ifdef _WINDOWS
    wxString wsURI( m_pMozBrowser->currentUri().c_str(), wxConvUTF8 );
    m_pTxtUrl->SetValue( wsURI );
#else
    wxString wsURI( m_pMozBrowser->currentUri().c_str(), wxConvUTF8 );
    m_pTxtUrl->SetValue( wsURI );
#endif
}
