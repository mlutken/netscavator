
#include <stdio.h>
#include <iostream>
#include <sstream>
#include <boost/format.hpp>
#include <boost/thread/thread.hpp>


#include <nsServiceManagerUtils.h>
#include <nsIPrefService.h>

#include "mozbrowser/DefaultContentListener.h"
#include "mozbrowser/DefaultEventListener.h"
#include "mozbrowser/DefaultProgress.h"
#include <mozbrowser/DefaultHttpChannel.h>
#include <mozbrowser/DefaultHttpActivityObserver.h>
#include "utils/webbrowse_embedding_utils.h"

#include "SignalsManagerWx.h"

using namespace std;
namespace b = boost;

// ------------------------------------
// --- Constructor / Init Functions ---
// ------------------------------------
SignalsManagerWx::SignalsManagerWx()
    : SignalsManager()
{

}

SignalsManagerWx::~SignalsManagerWx()
{

}



void SignalsManagerWx::init(
    MozBrowserWx* 					pMozBrowser,
    boost::shared_ptr<WebBrowser> 	pWebBrowser
)
{
    m_pMozBrowser = pMozBrowser;
    m_pWebBrowser = pWebBrowser;

    // --- Get Event Target ---
    nsCOMPtr<nsPIDOMWindow> pPIDOMWindow;
    getPIDOMWindow( getter_AddRefs(pPIDOMWindow), m_pWebBrowser->ifMoz() );
    if ( !pPIDOMWindow ) { printf("Error: Failed to get PIDOMWindow\n");	return;	}
    m_pIDOMEventTarget = do_QueryInterface( pPIDOMWindow->GetChromeEventHandler() );
}







// ------------------------------
// --- Add listener Functions ---
// ------------------------------

void SignalsManagerWx::addContextMenuListener(
	nsCOMPtr<nsIContextMenuListener>	pIContextMenuListener,
	bool bAllowCreateDefault
)
{
//	nsresult rv;
	// Should we disable this listener ?
	if ( !pIContextMenuListener && !bAllowCreateDefault ) {
// 		rv = m_pIDOMEventTarget->RemoveEventListenerByIID(m_pIContextMenuListener, NS_GET_IID(nsIDOMMouseListener));
// 		if (NS_FAILED(rv)) {	NS_WARNING("Failed to remove context menu listener\n");	}
// 		m_pIContextMenuListener = NULL;
// 		return;	
	}

	// Add listener	
// 	m_pIContextMenuListener = pIContextMenuListener;
// 	if ( !m_pIContextMenuListener ) m_pIContextMenuListener = new DefaultContextMenuListener(*m_pMozBrowser);	
// 	rv = m_pIDOMEventTarget->AddEventListenerByIID(m_pIContextMenuListener, NS_GET_IID(nsIContextMenuListener));
// 	if (NS_FAILED(rv)) {	NS_WARNING("Failed to add context menu listener\n");	}
}	


void SignalsManagerWx::addDOMKeyListener(
	nsCOMPtr<nsIDOMKeyListener>	pIDOMKeyListener,
	bool bAllowCreateDefault
)
{
	nsresult rv;
	
	// Should we disable this listener ?
	if ( !pIDOMKeyListener && !bAllowCreateDefault ) {
// // 		printf("\n\nXXXXXXXXXXXXXXXXXXXXXXXX\n\n");
		rv = m_pIDOMEventTarget->RemoveEventListenerByIID(m_pIDOMKeyListener, NS_GET_IID(nsIDOMKeyListener));
		if (NS_FAILED(rv)) {	NS_WARNING("Failed to remove key listener\n");	}
		m_pIDOMKeyListener = NULL;
		return;	
	}

	// Add listener	
	m_pIDOMKeyListener = pIDOMKeyListener;
	if ( !m_pIDOMKeyListener ) 	m_pIDOMKeyListener = new DefaultDOMKeyListener(*m_pMozBrowser);	
	rv = m_pIDOMEventTarget->AddEventListenerByIID(m_pIDOMKeyListener, NS_GET_IID(nsIDOMKeyListener));
	if (NS_FAILED(rv)) {	NS_WARNING("Failed to add key listener\n");	}
}	



void SignalsManagerWx::addDOMMouseListener(
	nsCOMPtr<nsIDOMMouseListener>	pIDOMMouseListener,
	bool bAllowCreateDefault
)
{
	nsresult rv;
	// Should we disable this listener ?
	if ( !pIDOMMouseListener && !bAllowCreateDefault ) {
		rv = m_pIDOMEventTarget->RemoveEventListenerByIID(m_pIDOMMouseListener, NS_GET_IID(nsIDOMMouseListener));
		if (NS_FAILED(rv)) {	NS_WARNING("Failed to remove mouse listener\n");	}
		m_pIDOMMouseListener = NULL;
		return;	
	}

	// Add listener	
	m_pIDOMMouseListener = pIDOMMouseListener;
	if ( !m_pIDOMMouseListener ) m_pIDOMMouseListener = new DefaultDOMMouseListener(*m_pMozBrowser);	
	rv = m_pIDOMEventTarget->AddEventListenerByIID(m_pIDOMMouseListener, NS_GET_IID(nsIDOMMouseListener));
	if (NS_FAILED(rv)) {	NS_WARNING("Failed to add mouse listener\n");	}
}	


void SignalsManagerWx::addDOMUIListener(
	nsCOMPtr<nsIDOMUIListener>	pIDOMUIListener,
	bool bAllowCreateDefault
)
{
	nsresult rv;
	// Should we disable this listener ?
	if ( !pIDOMUIListener && !bAllowCreateDefault ) {
		// TODO: Remove event listener somehow;
		rv = m_pIDOMEventTarget->RemoveEventListenerByIID(m_pIDOMUIListener, NS_GET_IID(nsIDOMUIListener));
		if ( NS_FAILED(rv) ) {	NS_WARNING("Failed to remove mouse listener\n");	}
		m_pIDOMUIListener = NULL;
		return;	
	}

	// Add listener	
	m_pIDOMUIListener = pIDOMUIListener;
	if ( !m_pIDOMUIListener ) m_pIDOMUIListener = new DefaultDOMUIListener(*m_pMozBrowser);	
	rv = m_pIDOMEventTarget->AddEventListenerByIID(m_pIDOMUIListener, NS_GET_IID(nsIDOMUIListener));
	if (NS_FAILED(rv)) {	NS_WARNING("Failed to add mouse listener\n");	}
}	


void SignalsManagerWx::addURIContentListener (
	nsCOMPtr<nsIURIContentListener>		pIURIContentListener, 	
	bool 								bAllowCreateDefault
)
{
//	nsresult rv;
	// Should we disable this listener ?
	if ( !pIURIContentListener && !bAllowCreateDefault ) {
		m_pWebBrowser->ifMoz()->SetParentURIContentListener(NULL);
		m_pIURIContentListener = NULL;
		return;	
	}

	// Add listener	
	m_pIURIContentListener = pIURIContentListener;
	if ( !m_pIURIContentListener ) m_pIURIContentListener = new DefaultURIContentListener(*m_pMozBrowser, m_pWebBrowser->ifMoz() );	
 	m_pWebBrowser->ifMoz()->SetParentURIContentListener(m_pIURIContentListener); 
}

void SignalsManagerWx::addWebProgressListener(
	nsCOMPtr<nsIWebProgressListener>	pIWebProgressListener, 	
	bool 								bAllowCreateDefault  	
)
{
	// Should we disable this listener ?
	if ( !pIWebProgressListener && !bAllowCreateDefault ) {
/*		printf("ssssssssssssssssssssssss\n");
		// bind the progress listener to the browser object
		nsCOMPtr<nsISupportsWeakReference> supportsWeak;
		supportsWeak = do_QueryInterface( m_pIWebProgressListener );
		nsCOMPtr<nsIWeakReference> weakRef;
		supportsWeak->GetWeakReference( getter_AddRefs(weakRef) );
		m_pWebBrowser->ifMoz()->RemoveWebBrowserListener( weakRef, NS_GET_IID(nsIWebProgressListener) );
		*/
		m_pIWebProgressListener = NULL;
		return;	
	}

	// Add listener	
	m_pIWebProgressListener = pIWebProgressListener;
    if ( !m_pIWebProgressListener ) m_pIWebProgressListener = new DefaultProgress(m_pMozBrowser);
	// bind the progress listener to the browser object
	nsCOMPtr<nsISupportsWeakReference> supportsWeak;
	supportsWeak = do_QueryInterface( m_pIWebProgressListener );
	nsCOMPtr<nsIWeakReference> weakRef;
	supportsWeak->GetWeakReference( getter_AddRefs(weakRef) );
	m_pWebBrowser->ifMoz()->AddWebBrowserListener( weakRef, NS_GET_IID(nsIWebProgressListener) );
}



////////////
void SignalsManagerWx::addHttpActivityObserver(
    nsCOMPtr<nsIHttpActivityObserver>	pIHttpActivityObserver,
    bool 								bAllowCreateDefault
)
{
    // Should we disable this listener ?
    if ( !pIHttpActivityObserver && !bAllowCreateDefault ) {
        m_pIHttpActivityObserver = NULL;
        return;
    }
    ////nsresult rv;

     //nsCOMPtr<nsIWebBrowser> pIWebBrowser ( do_CreateInstance ( NS_WEBBROWSER_CONTRACTID, &rv ) );
     //nsCOMPtr<nsIHttpActivityDistributor> pIActivityDistributor = ( do_CreateInstance ( "@mozilla.org/network/http-activity-distributor;1", &rv ) );
             //Xpcom.GetService<nsIHttpActivityDistributor>("@mozilla.org/network/http-activity-distributor;1");
//         activityDistributor = Xpcom.QueryInterface<nsIHttpActivityDistributor>(activityDistributor);
//         httpActivityObserver = new GeckoHttpActivityObserver(activityDistributor);
//         activityDistributor.addObserver(httpActivityObserver);


//    nsCOMPtr<nsIHttpActivityDistributor> pIActivityDistributor = do_QueryInterface( m_pWebBrowser->ifMoz() );
//    if ( pIActivityDistributor ) {
//        printf("ML: AA\n");
//    }

    nsCOMPtr<nsIPrefService> 	pPrefService 	= do_GetService(NS_PREFSERVICE_CONTRACTID);
    if ( pPrefService ) {
    }

    nsCOMPtr<nsIHttpActivityDistributor> 	pIActivityDistributor 	= do_GetService("@mozilla.org/network/http-activity-distributor;1");
    if ( pIActivityDistributor ) {
        m_pIHttpActivityObserver = new DefaultHttpActivityObserver(m_pMozBrowser);

        pIActivityDistributor->AddObserver(m_pIHttpActivityObserver);
    }



//    // Add listener
//    m_pIHttpActivityObserver = pIHttpActivityObserver;
//    if ( !m_pIHttpActivityObserver ) m_pIHttpActivityObserver = new DefaultHttpActivityObserver(*m_pMozBrowser);
//    // bind the progress listener to the browser object
//    nsCOMPtr<nsISupportsWeakReference> supportsWeak;
//    supportsWeak = do_QueryInterface( m_pIWebProgressListener );
//    nsCOMPtr<nsIWeakReference> weakRef;
//    supportsWeak->GetWeakReference( getter_AddRefs(weakRef) );
//    m_pWebBrowser->ifMoz()->AddWebBrowserListener( weakRef, NS_GET_IID(nsIHttpActivityObserver) );
}



//////////////


void SignalsManagerWx::addHttpChannel(
    nsCOMPtr<nsIHttpChannel>	pIHttpChannel,
    bool 						bAllowCreateDefault
)
{
//    // Should we disable this listener ?
//    if ( !pIHttpChannel && !bAllowCreateDefault ) {
//        m_pIHttpChannel = NULL;
//        return;
//    }

//    // Add listener
//    m_pIHttpChannel = pIHttpChannel;
//    if ( !m_pIHttpChannel ) m_pIHttpChannel = new DefaultHttpChannel(*m_pMozBrowser);
//    // bind the progress listener to the browser object
//    nsCOMPtr<nsISupportsWeakReference> supportsWeak;
//    supportsWeak = do_QueryInterface( m_pIHttpChannel );
//    nsCOMPtr<nsIWeakReference> weakRef;
//    supportsWeak->GetWeakReference( getter_AddRefs(weakRef) );
//    vv->ifMoz()->AddWebBrowserListener( weakRef, NS_GET_IID(nsIWebProgressListener) );
}


