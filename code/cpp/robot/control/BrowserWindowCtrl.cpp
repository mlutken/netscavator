#include "BrowserWindowCtrl.h"

#include <wx/clipbrd.h>
#include <cpaf_string_utils.hpp>
#include <parser/LinearDomSearch.h>
#include <WebBrowserIF.h>
#include <ScriptingClassIF.h>

#include <wx/CreatorMainFrameWx.h>
#include <control/DomTreeTextCtrl.h>
#include <php_embedding/php_embedding_utils.h>
#include <scriptcrawl_private_php.h>
#include <Configuration.h>
#include <Globals.h>



BrowserWindowCtrl::BrowserWindowCtrl( CreatorMainFrameWx* pCreatorMainFrameWx )
	: m_pCreatorMainFrameWx	( pCreatorMainFrameWx					)
    , m_pMiner			( pCreatorMainFrameWx->miner()		)
	, m_pMozDomTreeText		( pCreatorMainFrameWx->mozDomTreeText() )	
{
    m_connectionContextMenu = m_pMiner->webBrowser()->signalsManager()->connectContextMenu ( boost::bind(&BrowserWindowCtrl::slotContextMenu, this, _1, _2, _3 ) );
    m_connectionKeyPress 	= m_pMiner->webBrowser()->signalsManager()->connectKeyPress( boost::bind(&BrowserWindowCtrl::slotKeyPress, this, _1, _2 ) );
}

void BrowserWindowCtrl::searchStringSet ( std::string sSearchFor )
{
    m_pMiner->webBrowser()->searchStringSet(sSearchFor);
}

bool BrowserWindowCtrl::findNext 	()
{
    return m_pMiner->webBrowser()->findNext();
}

void BrowserWindowCtrl::focusActivate ()
{
    m_pMiner->webBrowser()->focusActivate();
}

void BrowserWindowCtrl::focusDeactivate	()
{
    m_pMiner->webBrowser()->focusDeactivate();
}



void BrowserWindowCtrl::slotContextMenu(
        boost::uint32_t iContextFlags
        , boost::shared_ptr<crawl::DomEventIF>	pDOMEvent
        , boost::shared_ptr<crawl::DomNodeIF> pDomNode )
{
	using crawl::LinearDomSearch;
//    boost::shared_ptr<DOMNode> pDOMNode = pDomNode->DOMNodePtr();
//    printf("ML: BrowserWindowCtrl::slotContextMenu iContextFlags: %X nodeName: '%s',  nodePtr: '%p', stringData: '%s'\n",
//        iContextFlags, pDomNode->nodeName().c_str(), pDomNode->nativeNodePtr(), pDomNode->stringDataUTF8().c_str() );

    boost::shared_ptr<crawl::LinearDomSearch> pSearch = m_pMiner->linearDomSearch();
    LinearDomSearch::size_type iPos = pSearch->findFromRawPointer( pDomNode, true );
	if ( iPos != 0 ) {
//	 	std::string sDbg = pSearch->debugGetCurrentNode( 5, 5, false );
//        printf("ML: foundpos: %s\n", sDbg.c_str());
        m_pCreatorMainFrameWx->domTreeTextCtrl()->activePositionSet(iPos);
	}
	else {
	 	m_pCreatorMainFrameWx->domTreeTextCtrl()->activePositionSet(0);
	}
}


void BrowserWindowCtrl::slotKeyDown(  crawl::WebBrowserIF& mozBrowser, boost::shared_ptr<crawl::DomKeyEventIF> pDOMKeyEvent )
{
	using namespace crawl;
}

// ./crawler/_test/simple_test.php

void BrowserWindowCtrl::slotKeyPress(  crawl::WebBrowserIF& mozBrowser, boost::shared_ptr<crawl::DomKeyEventIF> pDOMKeyEvent )
{
    //printf("BrowserWindowCtrl::slotKeyPress: %d\n", pDOMKeyEvent->charCode());
    if ( crawl::DomKeyEventIF::DOM_VK_BACK_SPACE == pDOMKeyEvent->keyCode() ) {
        mozBrowser.goBack();
        ////mozBrowser.navigation()->goBack();
	}
    if ( 82 == pDOMKeyEvent->charCode() || 114 == pDOMKeyEvent->charCode() ) {
        //testPhpNoMiner();
        boost::shared_ptr<crawl::Configuration> c= crawl::g()->configuration();

//        startupPhp(c->valueStrGet("php-ini-path").c_str());
//        executePhpString("require_once 'webminer.php';");
        setMinerPointerRaw(m_pMiner.get());
//        executePhpFile(c->valueStrGet("script-path").c_str());
////        executePhpFile("./crawler/_test/simple_test.php");
//        executePhpString("addMiner('MyMiner');");
////    executePhpString(s.c_str());


        boost::shared_ptr<crawl::ScriptingClassIF> pSC = createPhpScriptingClass();
        m_pMiner->assignScriptingClass(pSC);
        pSC->callScriptFunction_Void("domTest");
       // pSC->callScriptFunction_Void("nonExistingPhpFun");

        //executePhpString("domTest();");


//        shutdownPhp();
    }

    // currentMinerSetPointer("1234");

// 	using namespace crawl;
// 	boost::uint32_t  chCode = pDOMKeyEvent->charCode();
// 	if ( (chCode == 67 || chCode == 99 ) ){
// 		if (wxTheClipboard->Open())
// 		{
// 			std::string sSelection = m_pMozDomTree->selectionGet();
// 			m_pCreatorMainFrameWx->GetStatusBar()->SetStatusText(_("COPY: ") + sSelection );
// 			wxTheClipboard->SetData( new wxTextDataObject( sSelection ) );
// 			wxTheClipboard->Close();
// 		}
// 	}
}

