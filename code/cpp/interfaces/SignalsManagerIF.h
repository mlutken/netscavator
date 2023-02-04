#ifndef _CRAWL_SIGNALS_MANAGER_IF_H_
#define _CRAWL_SIGNALS_MANAGER_IF_H_


#include <iostream>
#include <string>
#include <boost/cstdint.hpp>
#include <boost/shared_ptr.hpp>	
#include <boost/signals2/signal.hpp>
//#include <boost/signals.hpp>
#include <boost/bind.hpp>



namespace bs2 = boost::signals2;
namespace bs = boost;
//namespace bss = boost::signals;

namespace crawl {

    class DomNodeIF;
    class WebBrowserIF;
    class DomMouseEventIF;
    class DomKeyEventIF;


/** Signals manager class. */
class SignalsManagerIF {
public:
//	// ----------------
//	// --- Typedefs ---
//	// ----------------
//    typedef boost::signals2::connection			ConnectionT;

//	// -------------------------------
//	// --- PUBLIC: Signal Typedefs ---
//	// -------------------------------
//    typedef boost::signals2::signal<void (void)>                                                    TimerSignalT;
//    typedef boost::signals2::signal<bool (WebBrowserIF*)>                                           CloseSignalT;
//    typedef boost::signals2::signal<void (WebBrowserIF*, boost::int32_t, const std::string&)>       NetProgressSignalT;
//    typedef boost::signals2::signal<bool (WebBrowserIF*, const std::string&)>                       LoadUrlSignalT;
//    typedef boost::signals2::signal<void (WebBrowserIF*, const std::string&)>                       PageLoadedSignalT;
//    typedef boost::signals2::signal<void (WebBrowserIF*, boost::shared_ptr<DomMouseEventIF>)>		MouseEventSignalT;
//    typedef boost::signals2::signal<void (WebBrowserIF*, boost::shared_ptr<DomKeyEventIF>)>         KeyEventSignalT;
//    typedef boost::signals2::signal<void (WebBrowserIF*, boost::shared_ptr<DomMouseEventIF>, boost::shared_ptr<DomNodeIF>)>		ContextMouseEventSignalT;
	
	
	// ------------------------------------
	// --- Constructor / Init Functions ---
	// ------------------------------------
    SignalsManagerIF();
    virtual ~SignalsManagerIF();



//	// -------------------------------
//	// --- CONNECT: Misc Functions ---
//	// -------------------------------



//    ConnectionT     connectOnClose          ( const CloseSignalT::slot_type& slot );

//    // -------------------------------------------
//    // --- CONNECT: Progress/LoadUrl Functions ---
//    // -------------------------------------------
//    ConnectionT     connectOnNetProgress    ( const NetProgressSignalT::slot_type& slot );
//    ConnectionT     connectOnNetStart       ( const LoadUrlSignalT::slot_type& slot     );
//    ConnectionT     connectOnLoadUri        ( const LoadUrlSignalT::slot_type& slot     );
//    ConnectionT     connectPageLoaded       ( const PageLoadedSignalT::slot_type& slot  );
	
//	// ---------------------------
//	// --- CONNECT: Key Events ---
//	// ---------------------------
																
//    ConnectionT     connectKeyDown          ( const KeyEventSignalT::slot_type& slot );
//    ConnectionT     connectKeyUp            ( const KeyEventSignalT::slot_type& slot );
//    ConnectionT     connectKeyPress         ( const KeyEventSignalT::slot_type& slot );

//	// -----------------------------
//	// --- CONNECT: Mouse Events ---
//	// -----------------------------
//    ConnectionT     connectMouseDown        ( const MouseEventSignalT::slot_type& slot );
//    ConnectionT     connectMouseUp          ( const MouseEventSignalT::slot_type& slot );
//    ConnectionT     connectMouseClick       ( const MouseEventSignalT::slot_type& slot );
//    ConnectionT     connectMouseDblClick    ( const MouseEventSignalT::slot_type& slot );
//    ConnectionT     connectMouseOver        ( const MouseEventSignalT::slot_type& slot );
//    ConnectionT     connectMouseOut         ( const MouseEventSignalT::slot_type& slot );
//	// --------------------------
//	// --- CONNECT: UI Events ---
//	// --------------------------
////	/// Connect to activate event signal.
////	ConnectionT     connectActivate( const UIEventSignalT::slot_type& slot );
////															{	return	m_ActivateSig.connect(slot);	}
////	/// Connect to focus in event signal.
////	ConnectionT     connectFocusIn( const UIEventSignalT::slot_type& slot );
////															{	return	m_FocusInSig.connect(slot);	}
////	/// Connect to focus out signal.
////	ConnectionT     connectFocusOut( const UIEventSignalT::slot_type& slot );
////															{	return	m_FocusOutSig.connect(slot);	}
//    ConnectionT     connectContextMouseEvent( const ContextMouseEventSignalT::slot_type& slot );
	
//	// -----------------------------
//	// --- CONNECT: Timer Events ---
//	// -----------------------------
//    ConnectionT     connectContinuousTimer  ( const TimerSignalT::slot_type& slot );
//    ConnectionT     connectOneShotTimer     ( const TimerSignalT::slot_type& slot );
	
//	// ----------------------------
//	// --- CALL: Misc Functions ---
//	// ----------------------------
//    bool        signalOnClose	( WebBrowserIF* pBrowser );

//    // ----------------------------------------
//    // --- CALL: Progress/LoadUrl Functions ---
//    // ----------------------------------------
//    void    signalOnNetProgress ( WebBrowserIF* pBrowser, boost::uint32_t progress, const std::string& sUrl );
//    void    signalOnNetStart	( WebBrowserIF* pBrowser, const std::string& sUrl );
//    bool    signalOnLoadUri     ( WebBrowserIF* pBrowser, const std::string& sUrl );
//    void    signalPageLoaded    ( WebBrowserIF* pBrowser, const std::string& sUrl );
															
//	// --------------------------
//	// --- CALL: Key Events ---
//	// --------------------------
//    void    signalKeyDown       ( WebBrowserIF* pBrowser, boost::shared_ptr<DomKeyEventIF> pKeyEvent );
//    void    signalKeyUp         ( WebBrowserIF* pBrowser, boost::shared_ptr<DomKeyEventIF> pKeyEvent );
//    void    signalKeyPress      ( WebBrowserIF* pBrowser, boost::shared_ptr<DomKeyEventIF> pKeyEvent );

//	// --------------------------
//	// --- CALL: Mouse Events ---
//	// --------------------------
//    void    signalMouseDown     ( WebBrowserIF* pBrowser, boost::shared_ptr<DomMouseEventIF> pMouseEvent );
//    void    signalMouseUp       ( WebBrowserIF* pBrowser, boost::shared_ptr<DomMouseEventIF> pMouseEvent );
//    void    signalMouseClick    ( WebBrowserIF* pBrowser, boost::shared_ptr<DomMouseEventIF> pMouseEvent );
//    void    signalMouseDblClick ( WebBrowserIF* pBrowser, boost::shared_ptr<DomMouseEventIF> pMouseEvent );
//    void    signalMouseOver     ( WebBrowserIF* pBrowser, boost::shared_ptr<DomMouseEventIF> pMouseEvent );
//    void    signalMouseOut      ( WebBrowserIF* pBrowser, boost::shared_ptr<DomMouseEventIF> pMouseEvent );

//	// -----------------------
//	// --- CALL: UI Events ---
//	// -----------------------
////	/// Signal activate event
////	void
////    signalActivate( 	WebBrowserIF* pBrowser, 		///< MozBrowser to relay to slots.
////						boost::shared_ptr<DOMUIEvent>	pUIEvent	)		///< Pointer DOM UI to event.
////															{	m_ActivateSig(pBrowser,pUIEvent);}
////	/// Signal focus in event
////	void
////    signalFocusIn( 	WebBrowserIF* pBrowser, 		///< MozBrowser to relay to slots.
////						boost::shared_ptr<DOMUIEvent>	pUIEvent	)		///< Pointer DOM UI to event.
////															{	m_FocusInSig(pBrowser,pUIEvent);}
////	/// Signal focus out event
////	void
////    signalFocusOut( 	WebBrowserIF* pBrowser, 		///< MozBrowser to relay to slots.
////						boost::shared_ptr<DOMUIEvent>	pUIEvent	)		///< Pointer DOM UI to event.
////															{	m_FocusOutSig(pBrowser,pUIEvent);}

//    void    signalContextMouseEvent( WebBrowserIF* pBrowser, boost::shared_ptr<DomMouseEventIF> pMouseEvent, boost::shared_ptr<DomNodeIF>	pDomNode );
//	// --------------------------
//	// --- CALL: Timer Events ---
//	// --------------------------
//    void    signalContinuousTimer   ();
//    void    signalOneShotTimer		();
	
	
//private:

//    CloseSignalT						m_onCloseSig;
//    LoadUrlSignalT                      m_onNetStartSig;
//    NetProgressSignalT                  m_onNetProgressSig;
//    LoadUrlSignalT                      m_onLoadUriSig;
//    PageLoadedSignalT                   m_pageLoadedSig;
//    KeyEventSignalT						m_keyDownSig;
//    KeyEventSignalT						m_keyUpSig;
//    KeyEventSignalT						m_keyPressSig;
//    MouseEventSignalT					m_mouseDownSig;
//    MouseEventSignalT					m_mouseUpSig;
//    MouseEventSignalT					m_mouseClickSig;
//    MouseEventSignalT					m_mouseDblClickSig;
//    MouseEventSignalT					m_mouseOverSig;
//    MouseEventSignalT					m_mouseOutSig;
////	UIEventSignalT						m_ActivateSig;
////	UIEventSignalT						m_FocusInSig;
////	UIEventSignalT						m_FocusOutSig;
//    ContextMouseEventSignalT			m_contextMouseEventSig;
//    TimerSignalT						m_continuousTimerSig;
//    TimerSignalT						m_oneShotTimerSig;

};

} //END namespace crawl

#endif // _CRAWL_SIGNALS_MANAGER_IF_H_




