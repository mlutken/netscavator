#ifndef _WEBBROWSE_SIGNALS_MANAGER_WX_H_
#define _WEBBROWSE_SIGNALS_MANAGER_WX_H_

#include "SignalsManager.h"
#include <webbrwsr/WebBrowser.h>
#include <nsIDOMUIListener.h>
#include <nsIDOMKeyListener.h>
#include <nsIDOMMouseListener.h>
#include <nsIURIContentListener.h>
//#include <nsPIDOMEventTarget.h>
#include <nsPIDOMWindow.h>
#include <nsIWebProgressListener.h>
#include <nsIContextMenuListener.h>
#include <nsIHttpActivityObserver.h>
#include <nsIHttpChannel.h>
#include <MozBrowserWx.h>

/** Signals manager class for use in wx (embedded mode). */
class SignalsManagerWx : public SignalsManager {
public:
	// ----------------
	// --- Typedefs ---
	// ----------------
	
	// ------------------------------------
	// --- Constructor / Init Functions ---
	// ------------------------------------
    SignalsManagerWx();
    virtual ~SignalsManagerWx();

    virtual void	init( MozBrowserWx* pMozBrowser, boost::shared_ptr<WebBrowser> pWebBrowser );

    // ------------------------------
    // --- Add listener Functions ---
    // ------------------------------
    void	addContextMenuListener  ( nsCOMPtr<nsIContextMenuListener>	pIContextMenuListener, 	bool bAllowCreateDefault );
    void	addDOMKeyListener       ( nsCOMPtr<nsIDOMKeyListener>		pIDOMKeyListener, 		bool bAllowCreateDefault 	= true 	);
    void	addDOMMouseListener     ( nsCOMPtr<nsIDOMMouseListener>		pIDOMMouseListener, 	bool bAllowCreateDefault 	= true 	);
    void	addDOMUIListener        ( nsCOMPtr<nsIDOMUIListener>		pIDOMUIListener, 		bool bAllowCreateDefault 	= true 	);
    void	addURIContentListener   ( nsCOMPtr<nsIURIContentListener>	pIURIContentListener, 	bool bAllowCreateDefault 	= true 	);
    void	addWebProgressListener  ( nsCOMPtr<nsIWebProgressListener>	pIWebProgressListener, 	bool bAllowCreateDefault 	= true 	);
    void	addHttpActivityObserver ( nsCOMPtr<nsIHttpActivityObserver>	pIHttpActivityObserver, bool bAllowCreateDefault 	= true 	);
    void	addHttpChannel          ( nsCOMPtr<nsIHttpChannel>          pIHttpChannel        , 	bool bAllowCreateDefault 	= true 	);


	
private:
    MozBrowserWx*						m_pMozBrowser;
    boost::shared_ptr<WebBrowser>		m_pWebBrowser;
    nsCOMPtr<nsPIDOMEventTarget>		m_pIDOMEventTarget;


    // --- Mozilla event listners ---
    nsCOMPtr<nsIDOMKeyListener> 		m_pIDOMKeyListener;
    nsCOMPtr<nsIDOMMouseListener>		m_pIDOMMouseListener;
    nsCOMPtr<nsIDOMUIListener>			m_pIDOMUIListener;
    nsCOMPtr<nsIURIContentListener> 	m_pIURIContentListener;
    nsCOMPtr<nsIWebProgressListener> 	m_pIWebProgressListener;
    nsCOMPtr<nsIHttpActivityObserver>   m_pIHttpActivityObserver;
    nsCOMPtr<nsIHttpChannel>            m_pIHttpChannel;
    nsCOMPtr<nsIContextMenuListener>	m_pIContextMenuListener;

};


#endif // _WEBBROWSE_SIGNALS_MANAGER_WX_H_




