#ifndef _MOZ_BROWSER_WX_H_
#define _MOZ_BROWSER_WX_H_

//#if WEBBROWSE_ENABLE_WX
#include <hacks/wx_h_include_hack.h>


////#include <nsIDOMUIListener.h>
////#include <nsIDOMKeyListener.h>
////#include <nsIDOMMouseListener.h>
#include <nsIURIContentListener.h>
////#include <nsPIDOMEventTarget.h>
#include <nsPIDOMWindow.h>
#include <nsIWebProgressListener.h>
#include <nsIContextMenuListener.h>
#include <nsIHttpActivityObserver.h>
#include <nsIHttpChannel.h>

#include <WebBrowserIF.h>
#include <docshell/WebNavigation.h>
#include "webbrwsr/WebBrowser.h"
#include "mozbrowser/DefaultContentListener.h"
#include "mozbrowser/DefaultEventListener.h"
#include "mozbrowser/DefaultProgress.h"
#include <mozbrowser/DefaultHttpChannel.h>
#include <mozbrowser/DefaultHttpActivityObserver.h>
#include "utils/webbrowse_embedding_utils.h"


class nsIWebBrowserFocus;
class WebBrowserFind;
//class nsIDOMWindow;
class DOMWindow;
class MozWxTimer;
class SignalsManagerWx;


/** Toplevel (WxWidgets) browser class. */
class MozBrowserWx : public crawl::WebBrowserIF {
    friend class CreatorBrowserControlWx;
    friend class CreatorMainFrameWx;
protected:
////    virtual void		initCommonDefaultsDerived ();
public:
	typedef boost::shared_ptr<MozBrowserWx> 	Ptr;		///< Pointer to a MozBrowserWx
	

	MozBrowserWx ( );
	MozBrowserWx ( wxWindow* pGuiWx );
    virtual 	~MozBrowserWx ();


//    /// Get signals manager pointer.
//    virtual boost::shared_ptr<SignalsManager>
//    signalsManager()	const;

    nsCOMPtr<nsIWebBrowserFocus>
    webBrowserFocus()	const;

    virtual boost::shared_ptr<DOMWindow>
    getContentDOMWindow() const;

    virtual nsCOMPtr<nsIDOMWindow>
    getIContentDOMWindow() const;


protected:
    virtual boost::shared_ptr<WebBrowser>
    webBrowser                              () const    { return m_pWebBrowser; }

private:
    boost::shared_ptr<WebBrowserFind>
    webBrowserFind()	const;

    // -------------------------------
    // --- PRIVATE: Init functions ---
    // -------------------------------
    virtual void            do_initDerived();

    // --------------------------------
    // --- PRIVATE: Get interfaces functions ---
    // --------------------------------
    virtual boost::shared_ptr<crawl::LinearDomIF>   do_createLinearDom  ();
    virtual boost::shared_ptr<SignalsManager>       do_signalsManager   ()	const;

    // ------------------------------
    // --- PRIVATE: Url functions ---
    // ------------------------------
    virtual std::string 	do_currentUriGet        () const ;
    virtual bool            do_loadUri              ( const std::string& sUri );
//        virtual std::string     do_currentLoadingUrl() const = 0;
    virtual bool            do_goBack() const;
    virtual bool            do_cancelUriLoadRequest  ( void* requestID, const std::string& sUri );

    // ------------------------------
    // --- PRIVATE: Dom functions ---
    // ------------------------------
    virtual boost::shared_ptr<crawl::DomNodeIF>    do_getElementById ( const std::string& sID ) const;

    // ----------------------------
    // --- PRIVATE: Pagestatus functions ---
    // ----------------------------
//        virtual bool            do_pageLoading		() const = 0;
//        virtual bool            do_domValid			() const 	{	return !pageLoading(); 	}

    // -------------------------------------
    // --- PRIVATE: Javascript functions ---
    // -------------------------------------
    virtual bool        do_javaScriptExecuteRetVal  (   const std::string& sScript, std::string& sScriptReturnValue );


    // -------------------------------
    // --- Configuration functions ---
    // -------------------------------
    virtual void		do_loadImages				( bool bLoadImages );
    virtual void		do_loadStyleSheets			( bool bLoadStyleSheets );

    // ---------------------------------
    // --- PRIVATE: Window functions ---
    // ---------------------------------
    virtual void        do_refresh			();
    virtual void        do_show				();
    virtual void        do_hide				();
    virtual void        do_sizeGet			( int& x, int& y ) const;
    virtual void        do_sizeSet			( int x, int y 	);
    virtual void        do_close 			( bool bForce );
    virtual void        do_focusActivate    ();
    virtual void        do_focusDeactivate  ();
    virtual void		do_sendKeepActive   ();
    virtual void        do_scrollTo         ( boost::int32_t xScroll, boost::int32_t yScroll );
    virtual void        do_scrollByLines    ( boost::int32_t iNumLines );


    // -------------------------------
    // --- PRIVATE: Edit functions ---
    // -------------------------------
    virtual std::string	do_selectionGet		() const;
    virtual void        do_searchStringSet  ( const std::string& sSearchFor );
    virtual bool        do_findNext         ();
    virtual void        do_findEntireWord   ( bool val );
    virtual void        do_findMatchCase    ( bool val );

    // --------------------------------
    // --- PRIVATE: Timer functions ---
    // --------------------------------
    virtual void		do_continuousTimerStart ( int iMilisecs );
    virtual void		do_oneShotTimerStart	( int iMilisecs );
    virtual void		do_continuousTimerStop	();
    virtual void		do_oneShotTimerStop     ();

    // -------------------------------
    // --- PRIVATE: Misc functions ---
    // -------------------------------
    virtual std::string	do_typeNameGet		() const;
    virtual	wxWindow*	do_guiWx            () const;

    // ---------------------------------------
    // --- PRVATE: Mozilla event functions ---
    // ---------------------------------------
    void    initEventListneners();


    boost::shared_ptr<WebBrowser>			m_pWebBrowser;
    boost::shared_ptr<SignalsManagerWx>		m_pSignalsManagerWx;
    boost::shared_ptr<WebNavigation>		m_pNavigation;
    boost::shared_ptr<WebBrowserFind>		m_pWebBrowserFind;
    nsCOMPtr<nsIWebBrowserChrome>  			m_pChrome;
    nsCOMPtr<nsIWebBrowserFocus>			m_pIWebBrowserFocus;


	wxWindow*		m_pGuiWx;
	MozWxTimer*		m_pContinuousTimer;
	MozWxTimer*		m_pOneShotTimer;
	MozWxTimer*		m_pInitTimer;
	int				m_iKeepAxtiveX;
	int				m_iKeepAxtiveY;

    // -------------------------------------
    // --- PRVATE: Mozilla specific data ---
    // -------------------------------------
    nsCOMPtr<nsPIDOMEventTarget>		m_pIDOMEventTarget;


};


//#endif //#if WEBBROWSE_ENABLE_WX


#endif // _MOZ_BROWSER_WX_H_



