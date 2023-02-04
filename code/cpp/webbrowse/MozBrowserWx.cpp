//#if WEBBROWSE_ENABLE_WX
#include <stdio.h>
#include <wx/event.h>
#include <boost/thread/thread.hpp>

#include <nsIPrefService.h>
#include <nsIPrefBranch.h>
#include <nsIRequest.h>
#include <nsNetError.h>
#include <nsServiceManagerUtils.h>
#include <nsISelection.h>

#include <webbrwsr/DefaultWxBrowserFrame.h>
#include <webbrwsr/WebBrowserFind.h>
#include <nsIInterfaceRequestor.h>
#include <nsIInterfaceRequestorUtils.h>
#include <nsIWebBrowserFocus.h>
#include <dom/ScriptContext.h>
#include <utils/webbrowse_embedding_utils.h>
#include <mozwebbrowser/DomDocumentLinear.h>
#include <mozwebbrowser/MozDomNode.h>
#include "MozBrowserWx.h"
#include "SignalsManagerWx.h"


// ------------------
// --- MozWxTimer ---
// ------------------

class MozWxTimer : public wxTimer
{
public:
	enum EMozWxTimer { eTimerContinuous, eTimerOneShot, eTimerInit };
	explicit MozWxTimer ( MozBrowserWx*	pOwner, EMozWxTimer eType ) 
	 : 	wxTimer(),
		m_pOwner(pOwner),
		m_eType(eType)	
	{
//// 		printf("MozWxTimer::CONSTRUCTOR ( pOwner )n", this );
	}
	
	virtual void Notify()
	{
// 		printf("MozWxTimer::Notify( %d)\n", (int)m_eType );
		switch ( m_eType ) {
			case eTimerContinuous: 
				m_pOwner->signalsManager()->signalContinuousTimer();
				break;
			case eTimerOneShot: 
				m_pOwner->signalsManager()->signalOneShotTimer();
				break;
			case eTimerInit : 
 				printf("MozWxTimer::eTimerInit\n");
				m_pOwner->refresh();
				break;
			default:
				printf("Unknown timer\n");
		}
	}
	
private:
	MozBrowserWx*	m_pOwner;
	EMozWxTimer		m_eType;	
};





// --------------------
// --- MozBrowserWx ---
// --------------------




MozBrowserWx::MozBrowserWx ()	:	
    crawl::WebBrowserIF (),
	m_iKeepAxtiveX(0),
	m_iKeepAxtiveY(0)
{
    m_pSignalsManagerWx =  boost::shared_ptr<SignalsManagerWx>( new SignalsManagerWx() );
    m_pWebBrowser       = createWebBrowser();
    m_pChrome           = new DefaultChromeEmbed( this, m_pWebBrowser->ifMoz(), m_pSignalsManagerWx );


    ////printf("MozBrowserWx::CONSTRUCTOR ()this: %p\n", this );
	m_pGuiWx = new DefaultWxBrowserFrame ( _T ( "Sleipner Crawler Robot" ), webBrowser()->ifMoz(), this );
    ::initNativeWindow ( webBrowser()->ifMoz(), m_pChrome, m_pGuiWx, 0, 0, 1024, 800 );
	initCommonDefaults(); // Important to call this after initNativeWindow
	
	
	m_pContinuousTimer 	= new MozWxTimer(this, MozWxTimer::eTimerContinuous);
	m_pOneShotTimer		= new MozWxTimer(this, MozWxTimer::eTimerOneShot);
	m_pInitTimer		= new MozWxTimer(this, MozWxTimer::eTimerInit);
	m_pInitTimer->Start(1000, wxTIMER_ONE_SHOT) ; // wxTIMER_ONE_SHOT, wxTIMER_CONTINUOUS
}


MozBrowserWx::MozBrowserWx ( 
	wxWindow* pGuiWx 
)	:	
    crawl::WebBrowserIF(),
	m_pGuiWx( pGuiWx ),
	m_iKeepAxtiveX(0),
	m_iKeepAxtiveY(0)
{
    m_pSignalsManagerWx =  boost::shared_ptr<SignalsManagerWx>( new SignalsManagerWx() );
    m_pWebBrowser       = createWebBrowser();

    m_pChrome           = new DefaultChromeEmbed( this, m_pWebBrowser->ifMoz(), m_pSignalsManagerWx );

    ////printf("MozBrowserWx::CONSTRUCTOR (pGuiWx) this: %p\n", this );
    ::initNativeWindow ( webBrowser()->ifMoz(), m_pChrome, m_pGuiWx, 0, 0, 1024, 800 );
	initCommonDefaults(); // Important to call this after initNativeWindow
	m_pContinuousTimer 	= new MozWxTimer(this, MozWxTimer::eTimerContinuous);
	m_pOneShotTimer		= new MozWxTimer(this, MozWxTimer::eTimerOneShot);
	m_pInitTimer		= new MozWxTimer(this, MozWxTimer::eTimerInit);
	m_pInitTimer->Start(1000, wxTIMER_ONE_SHOT) ; // wxTIMER_ONE_SHOT, wxTIMER_CONTINUOUS
}


MozBrowserWx::~MozBrowserWx ( )
{
    ////printf("MozBrowserWx::DESTRUCTOR this: %p\n", this );
    // Disconnect and delete listeners
    m_pSignalsManagerWx->addDOMKeyListener(0, false);
    m_pSignalsManagerWx->addDOMMouseListener(0, false);
    m_pSignalsManagerWx->addDOMUIListener(0, false);
    m_pSignalsManagerWx->addURIContentListener(0, false);
    m_pSignalsManagerWx->addWebProgressListener(0, false);

    delete m_pContinuousTimer;
	delete m_pOneShotTimer;
}


///// Get signals manager pointer.
//boost::shared_ptr<SignalsManager>
//MozBrowserWx::signalsManager()	const
//{
//    return m_pSignalsManagerWx;
//}


/// Get focus.
nsCOMPtr<nsIWebBrowserFocus>
MozBrowserWx::webBrowserFocus()	const
{
    return m_pIWebBrowserFocus;
}

boost::shared_ptr<DOMWindow> MozBrowserWx::getContentDOMWindow() const
{
    return m_pWebBrowser->contentDOMWindow();
}


nsCOMPtr<nsIDOMWindow> MozBrowserWx::getIContentDOMWindow() const
{

    nsIWebBrowser* mWebBrowser =  webBrowser()->ifMoz();
    nsCOMPtr<nsIDOMWindow> contentWin;
    mWebBrowser->GetContentDOMWindow(getter_AddRefs(contentWin));
    return contentWin;
}


/// Get find interface.
boost::shared_ptr<WebBrowserFind>
MozBrowserWx::webBrowserFind()	const
{
    nsCOMPtr<nsIWebBrowser> pIBrowser = webBrowser()->ifMoz();
    nsCOMPtr<nsIInterfaceRequestor> pIIFReq = do_QueryInterface( pIBrowser );

// // 	if ( pIIFReq && pIIFReq.get() ) {
// // 		printf("pIIFReq ok\n");
// // 	}
// // 	else {
// // 		printf("pIIFReq NOT ok\n");
// // 	}
    nsIID iid = NS_GET_IID(nsIWebBrowserFind);
    nsCOMPtr<nsIWebBrowserFind> pIFind = do_GetInterface(pIIFReq);

    if ( pIFind ) {
// 		printf("pIFind ok\n");
    }
    else {
        printf("pIFind NOT ok\n");
    }
    boost::shared_ptr<WebBrowserFind> pFind = boost::shared_ptr<WebBrowserFind>( new WebBrowserFind(pIFind) );

    if ( pFind && pFind->ifMoz() ) {
// 		printf("pFind ok\n");
    }
    else {
        printf("pFind NOT ok\n");
    }

    return pFind;

}



// -------------------------------
// --- PRIVATE: Init functions ---
// -------------------------------
/** Call this from derived class as }last} thing before returning from constructor(s). */
void MozBrowserWx::do_initDerived()
{
    initEventListneners();

    m_pSignalsManagerWx->init(this, m_pWebBrowser);
    m_pNavigation = doQueryInterface<WebNavigation>(m_pWebBrowser);
    m_pSignalsManagerWx->addDOMKeyListener(0);
    m_pSignalsManagerWx->addDOMMouseListener(0);
    m_pSignalsManagerWx->addDOMUIListener(0);
    m_pSignalsManagerWx->addURIContentListener(0);
    m_pSignalsManagerWx->addWebProgressListener(0);
    m_pSignalsManagerWx->addHttpActivityObserver(0);

    m_pIWebBrowserFocus = do_QueryInterface (webBrowser()->ifMoz() );
    if ( m_pIWebBrowserFocus ) {
        m_pIWebBrowserFocus->Activate();
    }
}

// --------------------------------
// --- PRIVATE: Get interfaces functions ---
// --------------------------------
boost::shared_ptr<crawl::LinearDomIF>  MozBrowserWx::do_createLinearDom  ()
{
    using namespace crawl;
    boost::shared_ptr<crawl::WebBrowserIF> pBrowser;

    pBrowser = shared_from_this();
    boost::shared_ptr<DomDocumentLinear> pDomDocumentLinear = boost::shared_ptr<DomDocumentLinear>( new DomDocumentLinear(pBrowser, getContentDOMWindow()->document()) )	;

    pDomDocumentLinear->clearNodes();
    createLinearDomFromNode( pBrowser, pDomDocumentLinear, getContentDOMWindow()->document(), true, true );
//    createLinearDomFromNode( pDomDocumentLinear, getContentDOMWindow()->document(), true, true );

    return pDomDocumentLinear;
}


boost::shared_ptr<SignalsManager> MozBrowserWx::do_signalsManager   ()	const
{
    return m_pSignalsManagerWx;
}


// ------------------------------
// --- PRIVATE: Url functions ---
// ------------------------------
std::string MozBrowserWx::do_currentUriGet () const
{
    return m_pNavigation->currentURIAsString();
}

bool MozBrowserWx::do_loadUri ( const std::string& sUri)
{
    return m_pNavigation->loadURI( sUri, WebNavigation::LOAD_FLAGS_NONE );
}

//        virtual std::string     do_currentLoadingUrl() const = 0;
bool MozBrowserWx::do_goBack() const
{
    bool bRetval = m_pNavigation->canGoBack();
    m_pNavigation->goBack();
    return bRetval;
}

bool MozBrowserWx::do_cancelUriLoadRequest  ( void* requestID, const std::string& /*sUri*/ )
{
    if ( requestID ) {
        nsIRequest* aRequest = (nsIRequest*)requestID;
        aRequest->Cancel(NS_BINDING_ABORTED);
        return true;
    }
    return false;
}

// ------------------------------
// --- PRIVATE: Dom functions ---
// ------------------------------
boost::shared_ptr<crawl::DomNodeIF>    MozBrowserWx::do_getElementById ( const std::string& sID ) const
{
    boost::shared_ptr<crawl::DomNodeIF> pNode;
    boost::shared_ptr<DOMElement> pElem = getContentDOMWindow()->document()->getElementById( sID );
    boost::shared_ptr<crawl::WebBrowserIF> pBrowser;
    pBrowser = boost::const_pointer_cast<crawl::WebBrowserIF>(shared_from_this());
    if ( pElem && pBrowser ) {
        pNode = crawl::mkMozDomNode( pElem, pBrowser );
    }
    return pNode;
}

// ----------------------------------------------
// --- PRIVATE: Pagestatus/Progress functions ---
// ----------------------------------------------


// -------------------------------------
// --- PRIVATE: Javascript functions ---
// -------------------------------------
bool MozBrowserWx::do_javaScriptExecuteRetVal     (
        const std::string& sScript
        , std::string& sScriptReturnValue )
{
    boost::shared_ptr<ScriptContext> 	pSC;
    pSC			= getContentDOMWindow()->getScriptContext();
    return pSC->evaluateString(sScript, sScriptReturnValue );
}


// -------------------------------
// --- Configuration functions ---
// -------------------------------
void MozBrowserWx::do_loadImages ( bool bLoadImages )
{
    int iVal = bLoadImages ? 1 : 2;
    nsresult rv;
    nsCOMPtr<nsIPrefService> 	pPrefService 	= do_GetService(NS_PREFSERVICE_CONTRACTID);
    nsCOMPtr<nsIPrefBranch>		pPrefBranch	 	= do_QueryInterface( pPrefService );

    if ( pPrefBranch ) {
        rv = pPrefBranch->SetIntPref( "permissions.default.image", iVal );
    }
//	if (NS_FAILED(rv)) 	std::cout<< "ERROR: Crawler::loadImages" << std::endl;

}


void MozBrowserWx::do_loadStyleSheets ( bool bLoadStyleSheets )
{
    printf( "WARNING: MozBrowserWx::do_loadStyleSheets needs to be implemented\n" );
}



void MozBrowserWx::do_refresh ()
{
    m_pGuiWx->Refresh( true );

    // Fake paint event
    wxPaintEvent event( m_pGuiWx->GetId() );
    event.SetEventObject( m_pGuiWx );
    // Send it
    m_pGuiWx->GetEventHandler()->ProcessEvent( event );
}

void MozBrowserWx::do_show ()
{
    m_pGuiWx->Show( true );
}

void MozBrowserWx::do_hide ()
{
    m_pGuiWx->Show( false );
}

void MozBrowserWx::do_sizeGet ( int& x, int& y ) const
{
    m_pGuiWx->GetSize(&x, &y);
}

void MozBrowserWx::do_sizeSet( int x, int y 	)
{
    m_pGuiWx->SetSize(x, y);
}

void MozBrowserWx::do_close ( bool bForce )
{
    m_pGuiWx->Close(bForce);
}


void MozBrowserWx::do_focusActivate ()
{
    webBrowserFocus()->Activate();
}

void MozBrowserWx::do_focusDeactivate ()
{
    webBrowserFocus()->Deactivate();
}

void MozBrowserWx::do_sendKeepActive ()
{
    //m_pGuiWx->SendSizeEvent();
    //wxWindow* pWin = m_pGuiWx->GetGrandParent() ;
    int x, y;
    m_pGuiWx->GetSize(&x, &y);

    m_pGuiWx->SetSize(x+1, y);
    boost::this_thread::sleep(boost::posix_time::milliseconds(1));
//	PR_Sleep(100);
    m_pGuiWx->SetSize(x, y);
    m_pGuiWx->GetSize(&x, &y);
}

void MozBrowserWx::do_scrollTo ( boost::int32_t xScroll, boost::int32_t yScroll )
{
    getContentDOMWindow()->scrollTo( xScroll, yScroll );
}

void MozBrowserWx::do_scrollByLines ( boost::int32_t iNumLines )
{
    getContentDOMWindow()->scrollByLines( iNumLines );
}

// -------------------------------
// --- PRIVATE: Edit functions ---
// -------------------------------
std::string	MozBrowserWx::do_selectionGet () const
{
    nsCOMPtr<nsISelection> pISelection;
    //    webBrowser()->contentDOMWindow()->ifMoz()->GetSelection( getter_AddRefs( pISelection) );
    getContentDOMWindow()->ifMoz()->GetSelection( getter_AddRefs( pISelection) );
    PRUnichar* szSelection;
    pISelection->ToString( &szSelection);
    nsEmbedString sSelection(szSelection);
    std::string sSel = toStdStringUTF8( sSelection );
    return sSel;
}


void MozBrowserWx::do_searchStringSet ( const std::string& sSearchFor )
{
    webBrowserFind()->searchString( sSearchFor );
}

bool MozBrowserWx::do_findNext 	()
{
    return webBrowserFind()->findNext();
}

void MozBrowserWx::do_findEntireWord   ( bool val )
{
    webBrowserFind()->entireWord(val);
}


void MozBrowserWx::do_findMatchCase    ( bool val )
{
    webBrowserFind()->matchCase(val);
}

// --------------------------------
// --- PRIVATE: Timer functions ---
// --------------------------------
void MozBrowserWx::do_continuousTimerStart ( int iMilisecs )
{
    m_pContinuousTimer->Start(iMilisecs, wxTIMER_CONTINUOUS) ;
}

void MozBrowserWx::do_oneShotTimerStart	( int iMilisecs )
{
    m_pOneShotTimer->Start(iMilisecs, wxTIMER_ONE_SHOT) ;
}

void MozBrowserWx::do_continuousTimerStop ()
{
    m_pOneShotTimer->Stop();
}

void MozBrowserWx::do_oneShotTimerStop ()
{
    m_pContinuousTimer->Stop();
}


// -------------------------------
// --- PRIVATE: Misc functions ---
// -------------------------------
std::string	MozBrowserWx::do_typeNameGet		() const
{
    return "MozBrowserWx";
}

wxWindow* MozBrowserWx::do_guiWx            () const
{
    return m_pGuiWx;
}



// ---------------------------------------
// --- PRVATE: Mozilla event functions ---
// ---------------------------------------
void MozBrowserWx::initEventListneners()
{
    // --- Get Event Target ---
    nsCOMPtr<nsPIDOMWindow> pPIDOMWindow;
    getPIDOMWindow( getter_AddRefs(pPIDOMWindow), m_pWebBrowser->ifMoz() );
    if ( !pPIDOMWindow ) { printf("Error: Failed to get PIDOMWindow\n");	return;	}
    m_pIDOMEventTarget = do_QueryInterface( pPIDOMWindow->GetChromeEventHandler() );

}







//#endif //#if WEBBROWSE_ENABLE_WX


