
#include "SignalsManagerIF.h"
#include <stdio.h>
#include <iostream> 
#include <sstream>


using namespace std;
namespace b = boost;

namespace crawl {


    // ------------------------------------
    // --- Constructor / Init Functions ---
    // ------------------------------------

    SignalsManagerIF::SignalsManagerIF()
    {

    }

    SignalsManagerIF::~SignalsManagerIF()
    {

    }


    // -------------------------------
    // --- CONNECT: Misc Functions ---
    // -------------------------------



//    /// Connect to close signal.
//    SignalsManagerIF::ConnectionT SignalsManagerIF::connectOnClose(
//            const CloseSignalT::slot_type& slot )	///< Function object to be called
//    {
//        return	m_onCloseSig.connect(slot);
//    }

//    // -------------------------------------------
//    // --- CONNECT: Progress/LoadUrl Functions ---
//    // -------------------------------------------
//    /// Connect to 'Net Progress' signal.
//    SignalsManagerIF::ConnectionT SignalsManagerIF::connectOnNetProgress(
//            const NetProgressSignalT::slot_type& slot )	///< Function object to be called
//    {
//        return	m_onNetProgressSig.connect(slot);
//    }


//    /// Connect to 'Net Start' signal
//    SignalsManagerIF::ConnectionT SignalsManagerIF::connectOnNetStart(
//            const LoadUrlSignalT::slot_type& slot )	///< Function object to be called
//    {
//        return	m_onNetStartSig.connect(slot);
//    }

//    /// Connect to 'Load Uri' signal.
//    SignalsManagerIF::ConnectionT SignalsManagerIF::connectOnLoadUri(
//            const LoadUrlSignalT::slot_type& slot )	///< Function object to be called
//    {
//        return	m_onLoadUriSig.connect(slot);
//    }

//    /// Connect to page loaded signal.
//    SignalsManagerIF::ConnectionT SignalsManagerIF::connectPageLoaded(
//            const PageLoadedSignalT::slot_type& slot )	///< Function object to be called
//    {
//        return	m_pageLoadedSig.connect(slot);
//    }

//    // ---------------------------
//    // --- CONNECT: Key Events ---
//    // ---------------------------

//    /// Connect to key down signal.
//    SignalsManagerIF::ConnectionT SignalsManagerIF::connectKeyDown(
//            const KeyEventSignalT::slot_type& slot )	///< Function object to be called
//    {
//        return	m_keyDownSig.connect(slot);
//    }

//    /// Connect to key up signal.
//    SignalsManagerIF::ConnectionT SignalsManagerIF::connectKeyUp(
//            const KeyEventSignalT::slot_type& slot )	///< Function object to be called
//    {
//        return	m_keyUpSig.connect(slot);
//    }

//    /// Connect to key press signal.
//    SignalsManagerIF::ConnectionT SignalsManagerIF::connectKeyPress(
//            const KeyEventSignalT::slot_type& slot )	///< Function object to be called
//    {
//        return	m_keyPressSig.connect(slot);
//    }

//    // -----------------------------
//    // --- CONNECT: Mouse Events ---
//    // -----------------------------

//    /// Connect to mouse event signal.
//    SignalsManagerIF::ConnectionT SignalsManagerIF::connectMouseDown(
//            const MouseEventSignalT::slot_type& slot )	///< Function object to be called
//    {
//        return	m_mouseDownSig.connect(slot);
//    }

//    /// Connect to mouse event signal.
//    SignalsManagerIF::ConnectionT SignalsManagerIF::connectMouseUp(
//            const MouseEventSignalT::slot_type& slot )	///< Function object to be called
//    {
//        return	m_mouseUpSig.connect(slot);
//    }

//    /// Connect to mouse click signal.
//    SignalsManagerIF::ConnectionT SignalsManagerIF::connectMouseClick(
//            const MouseEventSignalT::slot_type& slot )	///< Function object to be called
//    {
//        return	m_mouseClickSig.connect(slot);
//    }

//    /// Connect to mouse event signal.
//    SignalsManagerIF::ConnectionT SignalsManagerIF::connectMouseDblClick(
//            const MouseEventSignalT::slot_type& slot )	///< Function object to be called
//    {
//        return	m_mouseDblClickSig.connect(slot);
//    }

//    /// Connect to mouse event signal.
//    SignalsManagerIF::ConnectionT SignalsManagerIF::connectMouseOver(
//            const MouseEventSignalT::slot_type& slot )	///< Function object to be called
//    {
//        return	m_mouseOverSig.connect(slot);
//    }

//    /// Connect to mouse event signal.
//    SignalsManagerIF::ConnectionT SignalsManagerIF::connectMouseOut( const MouseEventSignalT::slot_type& slot )	///< Function object to be called
//    {
//        return	m_mouseOutSig.connect(slot);
//    }

//    // --------------------------
//    // --- CONNECT: UI Events ---
//    // --------------------------
//    //	/// Connect to activate event signal.
//    //	ConnectionT
//    //	connectActivate( const UIEventSignalT::slot_type& slot )	///< Function object to be called
//    //															{	return	m_ActivateSig.connect(slot);	}
//    //	/// Connect to focus in event signal.
//    //	ConnectionT
//    //	connectFocusIn( const UIEventSignalT::slot_type& slot )	///< Function object to be called
//    //															{	return	m_FocusInSig.connect(slot);	}
//    //	/// Connect to focus out signal.
//    //	ConnectionT
//    //	connectFocusOut( const UIEventSignalT::slot_type& slot )	///< Function object to be called
//    //															{	return	m_FocusOutSig.connect(slot);	}

//    /// Connect to context menu signal.
//    SignalsManagerIF::ConnectionT SignalsManagerIF::connectContextMouseEvent(
//            const ContextMouseEventSignalT::slot_type& slot )	///< Function object to be called
//    {
//        return	m_contextMouseEventSig.connect(slot);
//    }


//    // -----------------------------
//    // --- CONNECT: Timer Events ---
//    // -----------------------------
//    /// Connect to activate timer event signal.
//    SignalsManagerIF::ConnectionT SignalsManagerIF::connectContinuousTimer(
//            const TimerSignalT::slot_type& slot )	///< Function object to be called
//    {
//        return	m_continuousTimerSig.connect(slot);
//    }

//    /// Connect to activate timer event signal.
//    SignalsManagerIF::ConnectionT SignalsManagerIF::connectOneShotTimer(
//            const TimerSignalT::slot_type& slot )	///< Function object to be called
//    {
//        return	m_oneShotTimerSig.connect(slot);
//    }




//    // ----------------------------
//    // --- CALL: Misc Functions ---
//    // ----------------------------

//    /// Signal close event
//    bool SignalsManagerIF::signalOnClose(
//            WebBrowserIF* pBrowser )            ///< MozBrowser to relay to slots.
//    {
//        if ( !m_onCloseSig.empty() ) 	return m_onCloseSig(pBrowser);
//        else							return true;
//    }

//    // ----------------------------------------
//    // --- CALL: Progress/LoadUrl Functions ---
//    // ----------------------------------------

//    /// Signal net progress event
//    void SignalsManagerIF::signalOnNetProgress(
//            WebBrowserIF*           pBrowser    ///< MozBrowser to relay to slots.
//            , boost::uint32_t       progress    ///< Fraction loaded so far if positive ( 0.0 - 1.0 )
//            , const std::string&    sUrl )      ///< Url about being loaded
//    {
//        if ( !m_onNetProgressSig.empty() )	m_onNetProgressSig(pBrowser, progress, sUrl);
//    }


//    /// Signal 'Net Start' event
//    void SignalsManagerIF::signalOnNetStart	(
//            WebBrowserIF*           pBrowser 	///< MozBrowser to relay to slots.
//            , const std::string&	sUrl	)	///< Url about to be loaded
//    {
//        if ( !m_onNetStartSig.empty() )	m_onNetStartSig(pBrowser,sUrl);
//    }


//    /// Signal on load url event
//    bool SignalsManagerIF::signalOnLoadUri	(
//            WebBrowserIF*           pBrowser    ///< MozBrowser to relay to slots.
//            , const std::string&	sUrl        ///< Url about to be loaded
//            )
//    {
//        //std::stringstream idStream;
//        //idStream << boost::this_thread::get_id();
//        //printf( "\nML: SignalsManager::signalOnLoadUri thread_id: '%s'\n" , idStream.str().c_str() );
//        printf( "ML: SignalsManager::signalOnLoadUri url: '%s'\n" , sUrl.c_str() );
//        bool bAbortLoad = false ;
//        if ( !m_onLoadUriSig.empty() ) {
//            boost::optional<bool> op = m_onLoadUriSig(pBrowser,sUrl);
//            bAbortLoad = *op;
//        }
//        return bAbortLoad;
//    }


//    /// Signal page loaded event
//    void SignalsManagerIF::signalPageLoaded(
//            WebBrowserIF*           pBrowser    ///< MozBrowser to relay to slots.
//            , const std::string&	sUrl )		///< MozBrowser to relay to slots.
//    {
//        m_pageLoadedSig(pBrowser, sUrl);
//    }


//    // --------------------------
//    // --- CALL: Key Events ---
//    // --------------------------

//    /// Signal key down event
//    void SignalsManagerIF::signalKeyDown(
//            WebBrowserIF*                       pBrowser  		///< MozBrowser to relay to slots.
//            , boost::shared_ptr<DomKeyEventIF> 	pKeyEvent	)	///< Pointer to key event

//    {
//        m_keyDownSig(pBrowser, pKeyEvent);
//    }

//    /// Signal key up event
//    void SignalsManagerIF::signalKeyUp(
//            WebBrowserIF*                       pBrowser 		///< MozBrowser to relay to slots.
//            , boost::shared_ptr<DomKeyEventIF> 	pKeyEvent	)	///< Pointer to key event
//    {
//        m_keyUpSig(pBrowser, pKeyEvent);
//    }

//    /// Signal key press event
//    void SignalsManagerIF::signalKeyPress(
//            WebBrowserIF*                       pBrowser   		///< MozBrowser to relay to slots.
//            , boost::shared_ptr<DomKeyEventIF> 	pKeyEvent	)	///< Pointer to key event
//    {
//        m_keyPressSig(pBrowser, pKeyEvent);
//    }

//    // --------------------------
//    // --- CALL: Mouse Events ---
//    // --------------------------

//    /// Signal mouse down event
//    void SignalsManagerIF::signalMouseDown(
//            WebBrowserIF*                           pBrowser 		///< MozBrowser to relay to slots.
//            , boost::shared_ptr<DomMouseEventIF>	pMouseEvent	)	///< Pointer to mouse event.
//    {
//        m_mouseDownSig(pBrowser,pMouseEvent);
//    }

//    /// Signal mouse up event
//    void SignalsManagerIF::signalMouseUp(
//            WebBrowserIF*                           pBrowser        ///< MozBrowser to relay to slots.
//            , boost::shared_ptr<DomMouseEventIF>	pMouseEvent	)	///< Pointer to mouse event.
//    {
//        m_mouseUpSig(pBrowser,pMouseEvent);
//    }

//    /// Signal mouse click event
//    void SignalsManagerIF::signalMouseClick(
//            WebBrowserIF*                           pBrowser 		///< MozBrowser to relay to slots.
//            , boost::shared_ptr<DomMouseEventIF>	pMouseEvent	)	///< Pointer to mouse event.
//    {
//        m_mouseClickSig(pBrowser,pMouseEvent);
//    }

//    /// Signal mouse double click event
//    void SignalsManagerIF::signalMouseDblClick(
//            WebBrowserIF*                           pBrowser 		///< MozBrowser to relay to slots.
//            , boost::shared_ptr<DomMouseEventIF>	pMouseEvent	)	///< Pointer to mouse event.
//    {
//        m_mouseDblClickSig(pBrowser,pMouseEvent);
//    }

//    /// Signal mouse over event
//    void SignalsManagerIF::signalMouseOver(
//            WebBrowserIF*                           pBrowser 		///< MozBrowser to relay to slots.
//            , boost::shared_ptr<DomMouseEventIF>	pMouseEvent	)	///< Pointer to mouse event.
//    {
//        m_mouseOverSig(pBrowser,pMouseEvent);
//    }

//    /// Signal mouse out event
//    void SignalsManagerIF::signalMouseOut(
//            WebBrowserIF*                           pBrowser 		///< MozBrowser to relay to slots.
//            , boost::shared_ptr<DomMouseEventIF>	pMouseEvent	)	///< Pointer to mouse event.
//    {
//        m_mouseOutSig(pBrowser,pMouseEvent);
//    }

//    // -----------------------
//    // --- CALL: UI Events ---
//    // -----------------------

//    /// Signal context mouse event
//    void SignalsManagerIF::signalContextMouseEvent(
//            WebBrowserIF*                           pBrowser        ///< MozBrowser to relay to slots
//            , boost::shared_ptr<DomMouseEventIF>	pMouseEvent     ///< DOM event.
//            , boost::shared_ptr<DomNodeIF>          pDomNode	)   ///< DOM node of event
//    {
//        m_contextMouseEventSig(pBrowser, pMouseEvent, pDomNode);
//    }

//    // --------------------------
//    // --- CALL: Timer Events ---
//    // --------------------------
//    /// Signal timer event
//    void SignalsManagerIF::signalContinuousTimer 	()
//    {
//        m_continuousTimerSig();
//    }

//    /// Signal timer event
//    void SignalsManagerIF::signalOneShotTimer		()
//    {
//        m_oneShotTimerSig();
//    }





} //END namespace crawl
