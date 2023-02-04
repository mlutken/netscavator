#include <iostream>
#include <locale>
#include <boost/format.hpp>
#include <dom/ScriptContext.h>
#include "scriptcrawl.h"

//// DECLARE_APP(ScriptCrawlApp)


// --- Debug stuff : BEGIN ---
#include "nsISupports.h"
#include "nsColor.h"
#include "nsCoord.h"
#include "nsCOMPtr.h"
#include "nsIPresShell.h"
#include <nsIDocument.h>
#include <nsGUIEvent.h>
#include <nsIViewManager.h>
#include <nsIDOMEventTarget.h>
#include <nsIDOMMouseEvent.h>
#include <nsComponentManagerUtils.h>
#include <nsIDOMDocumentEvent.h>
// --- Debug stuff : END ---

//#include <nsCOMPtr.h>
//#include <nsIDocument.h>
//#include <nsIPresShell.h>






void initMining()
{
	std::cout << boost::format("initMining\n") ;
	using namespace std;
	

	
//	cout << "toupper('a'): " << use_facet< ctype<char> >( locale() ).toupper('a') << endl;
//	cout << "toupper('æ'): " << use_facet< ctype<char> >( locale() ).toupper('æ') << endl;
//	cout << "toupper('ø'): " << use_facet< ctype<char> >( locale() ).toupper('ø') << endl;
//	cout << "toupper('å'): " << use_facet< ctype<char> >( locale() ).toupper('å') << endl;
//	cout << "toupper('ü'): " << use_facet< ctype<char> >( locale() ).toupper('ü') << endl;
//	std::locale loc ( "da_DK.utf8" );
//	std::locale loc ( "en_DK" );
//	cout << "toupper('a'): " << use_facet< ctype<char> >( loc ).toupper('a') << endl;
//	cout << "toupper('æ'): " << use_facet< ctype<char> >( loc ).toupper('æ') << endl;
//	cout << "toupper('ø'): " << use_facet< ctype<char> >( loc ).toupper('ø') << endl;
//	cout << "toupper('å'): " << use_facet< ctype<char> >( loc ).toupper('å') << endl;
//	cout << "toupper('ü'): " << use_facet< ctype<char> >( loc ).toupper('ü') << endl;
//	cout << "æøåÆØÅ: " << endl;
	
}


void addMiner( const std::string& sMinerName )
{
	std::cout << boost::format("addMiner(%1%)\n") % sMinerName;
	G_ScriptGlobals::Instance().m_miners[sMinerName] = boost::shared_ptr<ScriptMiner>();
}

void runMiners( )
{
//	std::cout << "runMiners() 1 " << std::endl;
	
//	wxString s ("aasd");
	
	char*  szArgv[2] = { "", "" }; 
	int iArgc = 1;
	wxEntry( iArgc, &szArgv[0] );
}

// ----------------------
// --- Misc functions --- 
// ----------------------
void useLocale( 
	const std::string& sLocale )
{
	std::locale loc ( sLocale.c_str() );
	G_ScriptGlobals::Instance().m_pCurrentMiner->stringSearch().locale( loc );	
	std::locale::global ( loc ); // TODO: Should we set the global or not ?
}
 
// ---------------------
// --- DOM functions --- 
// ---------------------
void tester( int iNum )
{
	printf( "TTTTTTTT: iNum: %x\n", iNum );
	
	
}




// ------------------------------------------
// --- String operators/compare functions ---
// ------------------------------------------


// --------------------------------------------
// --- Implementation: Javascript functions ---
// --------------------------------------------
bool javaScriptExecuteRetVal( 
	const std::string& sScript, 
	std::string& sScriptReturnValue )
{
	boost::shared_ptr<ScriptContext> 	pSC;
	boost::shared_ptr<MozBrowser>		pMozBrowser;
	
	pMozBrowser = G_ScriptGlobals::Instance().m_pCurrentMiner->mozBrowser();	
	pSC			= pMozBrowser->webBrowser()->contentDOMWindow()->getScriptContext();
	
	return pSC->evaluateString(sScript, sScriptReturnValue );
}

bool javaScriptExecute( 
	const std::string& sScript )
{
	std::string sIgnoreRetval;
	return javaScriptExecuteRetVal( sScript, sIgnoreRetval );
}

// -----------------------
// --- Debug functions ---
// -----------------------



static void tester( boost::shared_ptr<DOMNode> pNode )
{
	using namespace crawl;
	nsresult rv;
	printf("QQ: tester\n");
	if ( !pNode ) { printf("NULL node!\n"); return; }
	nsCOMPtr<nsIDOMDocument> pIDOMDoc;
	pNode->ifMoz()->GetOwnerDocument( getter_AddRefs( pIDOMDoc ) );
	
	if ( !pIDOMDoc ) return ;
	printf ( "sdsdsdsd 1111 \n");		
	nsCOMPtr<nsIDocument> pDoc = do_QueryInterface( pIDOMDoc );
	if ( !pDoc ) return ;
	printf ( "sdsdsdsd 2222 \n");		
	nsEmbedString sEmbed = pDoc->GetDocumentTitle();
	printf ( "A: '%s'\n", toStdStringUTF8(sEmbed).c_str() );
	
	nsIPresShell* pShell = pDoc->GetPrimaryShell();
	if ( !pShell ) return ;
	printf ( "sdsdsdsd 3333 \n");		

	nsIViewManager* pViewMan = pShell->GetViewManager();
	if ( !pViewMan ) return ;
	printf ( "sdsdsdsd 4444 \n");		
	
//	nsCOMPtr<nsIView> pView ;
//	pViewMan->GetRootView ( getter_AddRefs(pView) );
	nsIView* pView = 0;
	pViewMan->GetRootView ( pView );
	if ( !pView ) return ;
	printf ( "sdsdsdsd 5555 \n");		
	
	nsCOMPtr<nsIDOMEventTarget> pEventTgt = do_QueryInterface( pNode->ifMoz() );
	if ( !pEventTgt ) return ;
	printf ( "sdsdsdsd 6666 \n");		
	
	boost::shared_ptr<DOMDocument>	pDOMDoc	= pNode->ownerDocument();
	
	nsCOMPtr<nsIDOMNode>		pINode 			= pNode->ifMoz();
	
	nsCOMPtr<nsIDOMDocument>	pIDOMDocument;
	pINode->GetOwnerDocument( getter_AddRefs( pIDOMDocument ) );
	
	nsCOMPtr<nsIDOMDocumentEvent> pDOMDocEvent ( do_QueryInterface( pIDOMDocument ) );
	nsCOMPtr<nsIDOMEvent> pEvent;
	rv =	pDOMDocEvent->CreateEvent(NS_LITERAL_STRING("mouseevent"), getter_AddRefs( pEvent ) );
	nsCOMPtr<nsIDOMMouseEvent> pMouseEvent ( do_QueryInterface( pEvent ) );

/*	PRBool bRetval ;
	pMouseEvent->InitMouseEvent(NS_LITERAL_STRING("mouseover"), PR_TRUE, PR_FALSE, nsnull, 1, 0, 0, 0, 0, PR_FALSE, PR_FALSE, PR_FALSE, PR_FALSE, 0, 0 );
	pEventTgt->DispatchEvent( pMouseEvent, &bRetval );
	pMouseEvent->InitMouseEvent(NS_LITERAL_STRING("click"), PR_TRUE, PR_FALSE, nsnull, 1, 0, 0, 0, 0, PR_FALSE, PR_FALSE, PR_FALSE, PR_FALSE, 0, 0 );
	pEventTgt->DispatchEvent( pMouseEvent, &bRetval );
	pMouseEvent->InitMouseEvent(NS_LITERAL_STRING("mouseout"), PR_TRUE, PR_FALSE, nsnull, 1, 0, 0, 0, 0, PR_FALSE, PR_FALSE, PR_FALSE, PR_FALSE, 0, 0 );
	pEventTgt->DispatchEvent( pMouseEvent, &bRetval );
	printf ( "sdsdsdsd AAAA: %d \n", bRetval);		*/
	
	eventClick( pNode );
	return;
	
	boost::shared_ptr<DOMMouseEvent>	pMouseEv = createMouseEvent( pNode );
//	pMouseEv->initMouseEvent( "mouseover", true, false, 1, 0, 0, 0, 0, false, false, false, false, 0 );
	pMouseEv->initMouseEvent( "mouseover", false, 0 );
	dispatchEvent(pNode,pMouseEv);
	pMouseEv->initMouseEvent( "click", false, 0 );
	dispatchEvent(pNode,pMouseEv);
	pMouseEv->initMouseEvent( "mouseout", false, 0 );
	dispatchEvent(pNode,pMouseEv);
}
// nsContentUtils::DispatchTrustedEvent
// nsEventDispatcher::CreateEvent
// static const char* const sEventNames[]


bool	domFindNextTest(  
	int iCount, 											///< [in] Stop at match number iCount (ONLY positive numbers, i.e forward search ).
	const std::string& sSearchFor, 							///< [in] String to search for
	bool (*op)(const std::string&, const std::string&), 	///< [in] Compare operation to use
	int iNodeTypes )										///< [in] Restrict to node types. Default is all node types.
{
	printf( "TTTTTTTT: domFindNextTest\n" );
	bool bFound = G_ScriptGlobals::Instance().m_pCurrentMiner->linearDomSearch()->next( sSearchFor, op, iCount, iNodeTypes );
	if ( bFound ) 	G_ScriptGlobals::Instance().m_pCurrentMiner->domNodeToCurrentValue();
	else			G_ScriptGlobals::Instance().m_pCurrentMiner->stringSearch().setValue ( "" )	;	
	
	
	tester ( G_ScriptGlobals::Instance().m_pCurrentMiner->linearDomSearch()->curElemPtr() );
	
	return bFound;
}




//	nsIWidget* qwidget;
//	qwidget =  view->GetWidget();
//	nsevent.widget = qwidget;


// // 				if (context) {
// // 					printf ( "sdsdsdsd 4444 \n");							
// // 				}
// // 			}
	
	
/*	nsMouseEvent nsevent(PR_TRUE, NS_MOUSE_BUTTON_DOWN, nsnull);
	nsevent.eventStructType = NS_MOUSE_EVENT;
	nsevent.message = NS_MOUSE_BUTTON_DOWN;
	nsevent.point.x = x ;
	nsevent.point.y = y ;
	nsevent.clickCount = 1; */

// // 	rv = 0;
// // 	nsCOMPtr<nsIDOMMouseEvent> pIMouseEvent ( do_CreateInstance ( NS_IDOMMOUSEEVENT_IID_STR, &rv ) );
// // 	printf ( "rv: %d \n", rv);		
// // 	if ( !pIMouseEvent ) return ;
// // 	printf ( "sdsdsdsd AAAA \n");		
