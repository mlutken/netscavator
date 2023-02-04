#include "DomTreeTextWx.h"

#include <wx/gdicmn.h>
#include <parser/LinearDomSearch.h>
#include <WebBrowserIF.h>
#include <LinearDomIF.h>
#include <DomNodeIF.h>
#include <dom/DOMNode.h>

// BEGIN_EVENT_TABLE(DomTreeTextWx, wxPanel)
// 	EVT_BUTTON(ID_BtnLoadUrl, DomTreeTextWx::onClicked_BtnLoadUrl)
// END_EVENT_TABLE()


/**
 * 
 * @param parent 
 * @param pMozBrowser 
 */
DomTreeTextWx::DomTreeTextWx(wxWindow* parent, boost::shared_ptr<crawl::Crawler> pCrawler )
            : wxPanel(parent, wxID_ANY, wxDefaultPosition, wxDefaultSize)
            , m_pCrawler(pCrawler)
{

	m_connectionPageLoaded = m_pCrawler->webBrowser()->signalsManager()->connectPageLoaded	( boost::bind(&DomTreeTextWx::slotPageLoaded, this, _1 ) );
	
	m_pTxtCtrl = new wxRichTextCtrl( this, wxID_ANY, wxT("Some more text"),wxDefaultPosition, wxSize(500,500), wxTE_MULTILINE|wxNO_BORDER) ;
// 	m_pTxtCtrl = new wxTextCtrl( this, wxID_ANY, wxT("Some more text"),wxDefaultPosition, wxDefaultSize, wxTE_MULTILINE|wxNO_BORDER) ;
	

	wxBoxSizer* pBoxSizer = new wxBoxSizer(wxVERTICAL);
	pBoxSizer->Add(m_pTxtCtrl, 1, wxALIGN_LEFT | wxALIGN_RIGHT | wxALIGN_TOP | wxALIGN_BOTTOM | wxEXPAND);
	SetSizerAndFit(pBoxSizer);

}

#ifdef _WINDOWS
wxColor DomTreeTextWx::getNodeColor ( boost::shared_ptr<DOMNode> pNode ) const
{
	wxColor color;
	switch ( pNode->nodeType() ) {
        case crawl::DomNodeTypes::ELEMENT :
        case crawl::DomNodeIF::NODE_END_TAG:
			color.Set("BLUE");
		 	break;
        case crawl::DomNodeTypes::TEXT :
			color.Set("BLACK");
		 	break;
        case crawl::DomNodeTypes::ATTRIBUTE :
			color.Set("GREEN");
		 	break;
        case crawl::DomNodeTypes::ATTRIBUTE_VALUE :
			color.Set("FOREST GREEN");
		 	break;
        case crawl::DomNodeTypes::COMMENT :
			color.Set("GREY");
		 	break;
        case crawl::DomNodeTypes::DOCUMENT :
			color.Set("BLUE");
		 	break;
		default:
			color.Set("YELLOW");
	}
	return color;		
#else
    wxColor DomTreeTextWx::getNodeColor ( boost::shared_ptr<DOMNode> pNode ) const
    {
        wxColor color;
        switch ( pNode->nodeType() ) {
            case crawl::DomNodeTypes::ELEMENT :
            case crawl::DomNodeTypes::ELEMENT_END_TAG:
                color.Set( wxString("BLUE", wxConvUTF8) );
                break;
            case crawl::DomNodeTypes::TEXT :
                color.Set( wxString("BLACK", wxConvUTF8) );
                break;
            case crawl::DomNodeTypes::ATTRIBUTE :
                color.Set( wxString("GREEN", wxConvUTF8) );
                break;
            case crawl::DomNodeTypes::ATTRIBUTE_VALUE :
                color.Set( wxString("FOREST GREEN", wxConvUTF8) );
                break;
            case crawl::DomNodeTypes::COMMENT :
                color.Set( wxString("GREY", wxConvUTF8) );
                break;
            case crawl::DomNodeTypes::DOCUMENT :
                color.Set( wxString("BLUE", wxConvUTF8 ));
                break;
            default:
                color.Set( wxString("YELLOW", wxConvUTF8) );
        }
        return color;

#endif


}



void DomTreeTextWx::appendNodeText		( 
    boost::shared_ptr<DOMNode> pNode, 						///< DOMNode (pointer) to print.
	crawl::LinearDomSearch::size_type iPos
	)	
{
	return;
	using namespace std;
	bool bTrimBlanksPreset = true;
	std::string sNodeVal = pNode->stringData(bTrimBlanksPreset) ;
// // 	iLineLen += sNodeVal.length();
// 	wxColor color = getNodeColor ( pNode );
	
    printf("%s", sNodeVal.c_str() );
// // 	if ( iPos % 2 == 0 ) color.Set("BLUE");
    if ( pNode->nodeType() == crawl::DomNodeTypes::ELEMENT && pNode->hasChildNodes() ) {
// 		m_pTxtCtrl->AppendText("\n");
	}
// 	m_pTxtCtrl->BeginTextColour(color);

#ifdef _WINDOWS
	m_pTxtCtrl->WriteText("'" + sNodeVal + "' ");
#else
    wxString wsTxt( (std::string("'") + sNodeVal + "' ").c_str(), wxConvUTF8 );
    m_pTxtCtrl->WriteText( wsTxt );
#endif
// 	m_pTxtCtrl->EndTextColour();
	
}



void DomTreeTextWx::slotPageLoaded( crawl::WebBrowserIF& mozBrowser )
{
	using namespace crawl;
	printf("DomTreeTextWx::slotPageLoaded\n");
// 	return;
	m_pTxtCtrl->Clear();
	m_iIndentLvl = 0; 
	LinearDomSearch::size_type iPos = 0;
    LinearDomIF::const_iterator it = m_pCrawler->linearDom()->begin();
	for ( ; it != m_pCrawler->linearDom()->end(); ++it ) {
        appendNodeText( it->node->DOMNodePtr(), ++iPos );
	}
	
	
// 	m_pTxtCtrl->SetValue( m_pMozBrowser->navigation()->currentURI()->spec() );
}
