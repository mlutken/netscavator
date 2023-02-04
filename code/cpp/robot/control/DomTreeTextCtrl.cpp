#include "DomTreeTextCtrl.h"


#include <wx/clipbrd.h>
#include <boost/algorithm/string.hpp>
#include <cpaf_string_utils.hpp>
#include <parser/LinearDomSearch.h>
#include <LinearDomIF.h>
#include <BoxObjectIF.h>
#include <WebBrowserIF.h>
#include <DomKeyEventIF.h>

#include <wx/CreatorMainFrameWx.h>

DomTreeTextCtrl::DomTreeTextCtrl( CreatorMainFrameWx* pCreatorMainFrameWx )
	: m_pCreatorMainFrameWx	( pCreatorMainFrameWx					)
	, m_pCrawler			( pCreatorMainFrameWx->miner()		)
	, m_pMozDomTreeText		( pCreatorMainFrameWx->mozDomTreeText() )	
	, m_iPosActive			( 0 									)
{
	m_connectionKeyDown 	= m_pMozDomTreeText->signalsManager()->connectKeyDown( boost::bind(&DomTreeTextCtrl::slotKeyDown, this, _1, _2 ) );
	m_connectionKeyPress 	= m_pMozDomTreeText->signalsManager()->connectKeyPress( boost::bind(&DomTreeTextCtrl::slotKeyPress, this, _1, _2 ) );
}






void DomTreeTextCtrl::textHtmlGet( std::string& sTextHtml )
{
	using namespace crawl;
	sTextHtml.clear();

	appendHtmlHeader( sTextHtml );	
	
	m_iIndentLvl = 0; 
	
	LinearDomSearch::size_type iPos = 0;
    LinearDomIF::const_iterator it = m_pCrawler->linearDom()->begin();
	for ( ; it != m_pCrawler->linearDom()->end(); ++it ) {
        appendNodeText( sTextHtml, it->node, ++iPos );
	}
	appendHtmlFooter( sTextHtml );	
}


void DomTreeTextCtrl::searchStringSet ( std::string sSearchFor )
{
    m_pMozDomTreeText->searchStringSet(sSearchFor);
}

bool DomTreeTextCtrl::findNext 	()
{
    m_pMozDomTreeText->findEntireWord(true);
    m_pMozDomTreeText->findMatchCase(true);
    return m_pMozDomTreeText->findNext();
}

void DomTreeTextCtrl::focusActivate ()
{
    m_pMozDomTreeText->focusActivate();
}

void DomTreeTextCtrl::focusDeactivate	()
{
    m_pMozDomTreeText->focusDeactivate();
}



boost::shared_ptr<crawl::DomNodeIF>	DomTreeTextCtrl::containerNodeFromIndex 	( size_type iPos ) const
{
    boost::shared_ptr<crawl::DomNodeIF> pNode = m_pMozDomTreeText->getElementById( cpaf::to_string(iPos) );
    return pNode;
}


void DomTreeTextCtrl::activePositionSet ( size_type iPos )
{
    boost::shared_ptr<crawl::DomNodeIF> pNode = containerNodeFromIndex (m_iPosActive);
    // Remove old active style
    if ( m_iPosActive != 0 && pNode ) {
        pNode->classRemove("ClassActive");
    }

    // Set active style on the new node
    m_iPosActive = iPos;
    pNode = containerNodeFromIndex (m_iPosActive);
    if ( m_iPosActive != 0 && pNode ) {
        pNode->classAdd("ClassActive");
        scrollWindowToPos( m_iPosActive, -4 );
    }
}

void DomTreeTextCtrl::scrollWindowToPos ( size_type iPos, boost::int32_t iOffsetLines )
{
    boost::shared_ptr<crawl::DomNodeIF> pNode = containerNodeFromIndex(iPos);

    boost::shared_ptr<crawl::BoxObjectIF> pBox = pNode->getBoxObject ();
    if ( pBox ) {
        m_pMozDomTreeText->scrollTo( 0, pBox->y() );
        m_pMozDomTreeText->scrollByLines( iOffsetLines );
////        printf("ML: Elem window pos (x,y): ( %d, %d )\n", pBox->x(), pBox->y() );
////        printf("ML: Elem screen pos (x,y): ( %d, %d )\n", pBox->screenX(), pBox->screenY() );
    }
}



// --------------------------
// --- PRIVATE: Functions ---
// --------------------------

std::string DomTreeTextCtrl::getNodeStyle ( boost::shared_ptr<crawl::DomNodeIF> pNode ) const
{
	std::string sClass;
	switch ( pNode->nodeType() ) {
        case crawl::DomNodeTypes::ELEMENT :
        case crawl::DomNodeTypes::ELEMENT_END_TAG:
        case crawl::DomNodeTypes::DOCUMENT :
			sClass = "ClassELEMENT";
		 	break;
        case crawl::DomNodeTypes::TEXT :
			sClass = "ClassTEXT";
		 	break;
        case crawl::DomNodeTypes::ATTRIBUTE :
			sClass = "ClassATTRIBUTE";
		 	break;
        case crawl::DomNodeTypes::ATTRIBUTE_VALUE :
			sClass = "ClassATTRIBUTE_VALUE";
		 	break;
        case crawl::DomNodeTypes::COMMENT :
			sClass = "ClassCOMMENT";
		 	break;
		default:
			sClass = "ClassDEFAULT";
	}
	return sClass;		
}


// http://www.crotchet.co.uk/advsearch.html?id=RKF9XESP

void DomTreeTextCtrl::appendNodeText		( 
	std::string& sTextHtml,
    boost::shared_ptr<crawl::DomNodeIF> pNode, 						///< Node (pointer) to print.
	crawl::LinearDomSearch::size_type iPos
	)	
{
	using namespace std;
////	bool bTrimBlanksPreset = true;
////	std::string sNodeVal = pNode->stringData(bTrimBlanksPreset) ;
    std::string sNodeVal = pNode->stringDataUTF8();
    boost::algorithm::replace_all( sNodeVal, "<", "&lt;");
	boost::algorithm::replace_all( sNodeVal, ">", "&gt;");
	boost::algorithm::replace_all( sNodeVal, std::string("\302\240"), std::string("&amp;nbsp;") );
	std::string sClass = getNodeStyle( pNode ) ;
	
	bool bInsertBreak = false;
	
    if ( pNode->nodeType() == crawl::DomNodeTypes::ELEMENT && pNode->hasChildNodes() )
	{
		if ( sNodeVal != "A" && sNodeVal != "B" ) {
			bInsertBreak = true;
		}
	}
		
    if ( pNode->nodeType() == crawl::DomNodeTypes::ELEMENT_END_TAG ) {
		if ( sNodeVal != "/A" && sNodeVal != "/B" ) {
			bInsertBreak = true;
		}
	}
		
// 	bInsertBreak = false;	
	if ( bInsertBreak)
	{
		sTextHtml += "<br />\n";
	}
	sTextHtml += "<span id='" + cpaf::to_string(iPos) + "' class='" + sClass + "' >" + sNodeVal + ", </span>" ;	
// 	if ( pNode->nodeType() == DOMNode::TEXT ) {
// 		sTextHtml += "<span id='" + cpaf::to_string(iPos) + "' class='" + sClass + "' >'" + sNodeVal + "', </span>" ;	
// 	}
// 	else {
// 		sTextHtml += "<span id='" + cpaf::to_string(iPos) + "' class='" + sClass + "' >" + sNodeVal + ", </span>" ;	
// 	}
}



void DomTreeTextCtrl::appendHtmlHeader	( std::string& sTextHtml )
{
 	sTextHtml += "<html xmlns='http://www.w3.org/1999/xhtml'>\n";
 	sTextHtml += "<head>\n\t<meta http-equiv='content-type' content='text/html; charset=utf-8'/>\n";
 	sTextHtml += "<style type='text/css'>\n.different-text-color { color: Cyan; }\n</style>";
 	sTextHtml += "<style type='text/css'>\n.ClassActive { background-color: PowderBlue; }\n</style>";
 	sTextHtml += "<style type='text/css'>\n.ClassELEMENT { color: DarkBlue; }\n</style>";
 	sTextHtml += "<style type='text/css'>\n.ClassATTRIBUTE { color: DarkGreen ; }\n</style>";
 	sTextHtml += "<style type='text/css'>\n.ClassATTRIBUTE_VALUE { color: LimeGreen; }\n</style>";
 	sTextHtml += "<style type='text/css'>\n.ClassCOMMENT { color: Magenta; }\n</style>";
 	sTextHtml += "<style type='text/css'>\n.ClassDEFAULT { color: Darkorange; }\n</style>";
 	sTextHtml += "</head>\n<body>\n";
}

void DomTreeTextCtrl::appendHtmlFooter	( std::string& sTextHtml )
{
	sTextHtml += "\n</body>\n</html>\n"; 
}


void DomTreeTextCtrl::slotKeyDown(  crawl::WebBrowserIF& mozBrowser, boost::shared_ptr<crawl::DomKeyEventIF> pDOMKeyEvent )
{
	using namespace crawl;
// // 	printf("DomTreeTextCtrl::slotKeyDown: keyCode: '%d', charCode: '%d',  CTRL: %d\n", pDOMKeyEvent->keyCode(), pDOMKeyEvent->charCode(), pDOMKeyEvent->ctrlKey() );
}

void DomTreeTextCtrl::slotKeyPress(  crawl::WebBrowserIF& mozBrowser, boost::shared_ptr<crawl::DomKeyEventIF> pDOMKeyEvent )
{
	using namespace crawl;
// // 	printf("DomTreeTextCtrl::slotKeyPress: keyCode: '%d', charCode: '%d',  CTRL: %d\n", pDOMKeyEvent->keyCode(), pDOMKeyEvent->charCode(), pDOMKeyEvent->ctrlKey() );
	
	boost::uint32_t  chCode = pDOMKeyEvent->charCode(); 
	if ( (chCode == 67 || chCode == 99 ) ){
		if (wxTheClipboard->Open())
		{
			std::string sSelection = boost::algorithm::erase_all_copy( m_pMozDomTreeText->selectionGet(), "\n");
#ifdef _WINDOWS
			m_pCreatorMainFrameWx->GetStatusBar()->SetStatusText(_("COPY: ") + sSelection );
            wxTheClipboard->SetData( new wxTextDataObject( sSelection ) );
#else
            wxString wsTxt( _("COPY: ") );

            wsTxt += wxString( sSelection.c_str(), wxConvUTF8 );
            m_pCreatorMainFrameWx->GetStatusBar()->SetStatusText( wsTxt );
            wxTheClipboard->SetData( new wxTextDataObject( wxString( sSelection.c_str(), wxConvUTF8 ) ) );
#endif
			wxTheClipboard->Close();
		}
	}
}

