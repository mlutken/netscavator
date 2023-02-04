
#include <stdio.h> 
#include <iostream> 
#include <sstream>
#include <boost/optional.hpp>
#include <QCoreApplication>

#include <MinerWorkerIF.h>

#include "SignalsManager.h"
#include <DomKeyEventIF.h>
#include <DomMouseEventIF.h>
#include <DomNodeIF.h>
#include <WebBrowserIF.h>

using namespace std;
using namespace crawl;
namespace b = boost;

// ------------------------------------
// --- Constructor / Init Functions ---
// ------------------------------------

SignalsManager::SignalsManager()
{
    connect(this, SIGNAL(doCallMiningDoneSignal() ), this, SLOT(doCallMiningDoneSlot()));

}

SignalsManager::~SignalsManager()
{

}

QPointer<MinerWorkerIF> SignalsManager::minerWorker() const
{
    return m_minerWorker;
}

void SignalsManager::minerWorkerSet(const QPointer<MinerWorkerIF> &minerWorker)
{
    m_minerWorker = minerWorker;
}


// -------------------------------
// --- CONNECT: Misc Functions ---
// -------------------------------

/// Connect to 'Net Progress' signal.
SignalsManager::ConnectionT
        SignalsManager::connectOnNetProgress( const NetProgressSignalT::slot_type& slot )	///< Function object to be called
{
    return	m_OnNetProgressSig.connect(slot);
}


/// Connect to 'Net Start' signal
SignalsManager::ConnectionT
        SignalsManager::connectOnNetStart( const VoidMozStringSignalT::slot_type& slot )	///< Function object to be called
{
    return	m_OnNetStartSig.connect(slot);
}

/// Connect to 'Load Uri' signal.
SignalsManager::ConnectionT
        SignalsManager::connectOnLoadUri( const BoolMozStringSignalT::slot_type& slot )	///< Function object to be called
{
    return	m_OnLoadUriSig.connect(slot);
}

/// Connect to on mining done signal.
SignalsManager::ConnectionT
        SignalsManager::connectOnMiningDone( const VoidVoidSignalT::slot_type& slot )	///< Function object to be called
{
    return	m_OnMiningDoneSig.connect(slot);
}


/// Connect to close signal.
SignalsManager::ConnectionT
        SignalsManager::connectOnClose( const CloseSignalT::slot_type& slot )	///< Function object to be called
{
    return	m_OnCloseSig.connect(slot);
}

/// Connect to new match handler signal.
SignalsManager::ConnectionT
        SignalsManager::connectOnMatchHandler( const VoidVoidSignalT::slot_type& slot )	///< Function object to be called
{
    return	m_OnMatchSig.connect(slot);
}

// -----------------------------------
// --- CONNECT: Progress Functions ---
// -----------------------------------
/// Connect to page loaded signal.
SignalsManager::ConnectionT
        SignalsManager::connectPageLoaded( const PageLoadedSignalT::slot_type& slot )	///< Function object to be called
{
    return	m_PageLoadedSig.connect(slot);
}

/// Connect to page loaded signal.
SignalsManager::ConnectionT
        SignalsManager::connectDomChanged( const PageLoadedSignalT::slot_type& slot )	///< Function object to be called
{
    return	m_DomChangedSig.connect(slot);
}

// ---------------------------
// --- CONNECT: Key Events ---
// ---------------------------

/// Connect to key down signal.
SignalsManager::ConnectionT
        SignalsManager::connectKeyDown( const KeyEventSignalT::slot_type& slot )	///< Function object to be called
{
    return	m_KeyDownSig.connect(slot);
}

/// Connect to key up signal.
SignalsManager::ConnectionT
        SignalsManager::connectKeyUp( const KeyEventSignalT::slot_type& slot )	///< Function object to be called
{
    return	m_KeyUpSig.connect(slot);
}

/// Connect to key press signal.
SignalsManager::ConnectionT
        SignalsManager::connectKeyPress( const KeyEventSignalT::slot_type& slot )	///< Function object to be called
{
    return	m_KeyPressSig.connect(slot);
}

// -----------------------------
// --- CONNECT: Mouse Events ---
// -----------------------------

/// Connect to mouse event signal.
SignalsManager::ConnectionT
        SignalsManager::connectMouseDown( const MouseEventSignalT::slot_type& slot )	///< Function object to be called
{
    return	m_MouseDownSig.connect(slot);
}

/// Connect to mouse event signal.
SignalsManager::ConnectionT
        SignalsManager::connectMouseUp( const MouseEventSignalT::slot_type& slot )	///< Function object to be called
{
    return	m_MouseUpSig.connect(slot);
}

/// Connect to mouse click signal.
SignalsManager::ConnectionT
        SignalsManager::connectMouseClick( const MouseEventSignalT::slot_type& slot )	///< Function object to be called
{
    return	m_MouseClickSig.connect(slot);
}

/// Connect to mouse event signal.
SignalsManager::ConnectionT
        SignalsManager::connectMouseDblClick( const MouseEventSignalT::slot_type& slot )	///< Function object to be called
{
    return	m_MouseDblClickSig.connect(slot);
}

/// Connect to mouse event signal.
SignalsManager::ConnectionT
        SignalsManager::connectMouseOver( const MouseEventSignalT::slot_type& slot )	///< Function object to be called
{
    return	m_MouseOverSig.connect(slot);
}

/// Connect to mouse event signal.
SignalsManager::ConnectionT
        SignalsManager::connectMouseOut( const MouseEventSignalT::slot_type& slot )	///< Function object to be called
{
    return	m_MouseOutSig.connect(slot);
}

// --------------------------
// --- CONNECT: UI Events ---
// --------------------------
/// Connect to activate event signal.
SignalsManager::ConnectionT
        SignalsManager::connectActivate( const UIEventSignalT::slot_type& slot )	///< Function object to be called
{
    return	m_ActivateSig.connect(slot);
}

/// Connect to focus in event signal.
SignalsManager::ConnectionT
        SignalsManager::connectFocusIn( const UIEventSignalT::slot_type& slot )	///< Function object to be called
{
    return	m_FocusInSig.connect(slot);
}

/// Connect to focus out signal.
SignalsManager::ConnectionT
        SignalsManager::connectFocusOut( const UIEventSignalT::slot_type& slot )	///< Function object to be called
{
    return	m_FocusOutSig.connect(slot);
}

/// Connect to context menu signal.
SignalsManager::ConnectionT
        SignalsManager::connectContextMenu( const ContextMenuSignalT::slot_type& slot )	///< Function object to be called
{
    return	m_ContextMenuSig.connect(slot);
}


// -----------------------------
// --- CONNECT: Timer Events ---
// -----------------------------
/// Connect to activate timer event signal.
SignalsManager::ConnectionT
        SignalsManager::connectContinuousTimer( const TimerSignalT::slot_type& slot )	///< Function object to be called
{
    return	m_ContinuousTimerSig.connect(slot);
}

/// Connect to activate timer2 event signal.
SignalsManager::ConnectionT
        SignalsManager::connectContinuousTimer2( const TimerSignalT::slot_type& slot )	///< Function object to be called
{
    return	m_ContinuousTimer2Sig.connect(slot);
}

/// Connect to activate timer event signal.
SignalsManager::ConnectionT
        SignalsManager::connectOneShotTimer( const TimerSignalT::slot_type& slot )	///< Function object to be called
{
    return	m_OneShotTimerSig.connect(slot);
}



// ----------------------------
// --- CALL: Misc Functions ---
// ----------------------------
/// Signal net progress event
bool SignalsManager::signalOnNetProgress(
        void* aRequest
        , boost::uint32_t aStateFlags
        , const std::string& sUri )
{
    bool ok = true;
    if ( !m_OnNetProgressSig.empty() )	{
        boost::optional<bool> op = m_OnNetProgressSig(aRequest, aStateFlags, sUri);
        if ( !op.get() ) {
            ok = false;
        }
    }
    return ok;
}


/// Signal 'Net Start' event
void SignalsManager::signalOnNetStart	(
        crawl::WebBrowserIF& 	mozBrowser, 	///< crawl::WebBrowserIF to relay to slots.
        const std::string&		sUri        	///< Uri about to be loaded
        )
{
    if ( !m_OnNetStartSig.empty() )	m_OnNetStartSig(mozBrowser,sUri);
}

/// Signal load uri event
bool SignalsManager::signalOnLoadUri	(
                crawl::WebBrowserIF& mozBrowser     ///< crawl::WebBrowserIF to relay to slots.
                , const std::string&		sUri    ///< Uri about to be loaded
                )
{
    bool bAbortLoad = false ;
    if ( !m_OnLoadUriSig.empty() ) {
        boost::optional<bool> op = m_OnLoadUriSig(mozBrowser,sUri);
        bAbortLoad = *op;
    }
    return bAbortLoad;
}

/// Signal mining done event
void SignalsManager::signalOnMiningDone()
{
    emit doCallMiningDoneSignal();
}


/// Signal close event
bool SignalsManager::signalOnClose	( )
{
    if ( !m_OnCloseSig.empty() ) {
        m_OnCloseSig(); // OLD: return m_OnCloseSig();
        return true;
    }
    else
        return true;
}

/// Signal handler matched event
void SignalsManager::signalOnMatch()
{
    m_OnMatchSig();
}


// --------------------------------
// --- CALL: Progress Functions ---
// --------------------------------
/// Signal page loaded event
void SignalsManager::signalPageLoaded( crawl::WebBrowserIF& mozBrowser )				///< crawl::WebBrowserIF to relay to slots.
{
    using namespace std;
    m_PageLoadedSig(mozBrowser);
}

/// Signal dom changed event
void SignalsManager::signalDomChanged( crawl::WebBrowserIF& mozBrowser )				///< crawl::WebBrowserIF to relay to slots.
{
    m_DomChangedSig(mozBrowser);
}

// --------------------------
// --- CALL: Key Events ---
// --------------------------

/// Signal key down event
void SignalsManager::signalKeyDown(
        crawl::WebBrowserIF& mozBrowser, 						///< crawl::WebBrowserIF to relay to slots.
        boost::shared_ptr<crawl::DomKeyEventIF> 	pKeyEvent	)	///< Pointer to key event
{
    m_KeyDownSig(mozBrowser, pKeyEvent);
}

/// Signal key up event
void SignalsManager::signalKeyUp(
        crawl::WebBrowserIF& mozBrowser, 						///< crawl::WebBrowserIF to relay to slots.
        boost::shared_ptr<crawl::DomKeyEventIF> 	pKeyEvent	)	///< Pointer to key event
{
    m_KeyUpSig(mozBrowser, pKeyEvent);
}

/// Signal key press event
void SignalsManager::signalKeyPress(
        crawl::WebBrowserIF& mozBrowser, 						///< crawl::WebBrowserIF to relay to slots.
        boost::shared_ptr<crawl::DomKeyEventIF> 	pKeyEvent	)	///< Pointer to key event
{
    m_KeyPressSig(mozBrowser, pKeyEvent);
}

// --------------------------
// --- CALL: Mouse Events ---
// --------------------------
/// Signal mouse down event
void SignalsManager::signalMouseDown(
        crawl::WebBrowserIF&                                 mozBrowser, 		///< crawl::WebBrowserIF to relay to slots.
        boost::shared_ptr<crawl::DomMouseEventIF>	pMouseEvent	)		///< Pointer to mouse event.
{
    m_MouseDownSig(mozBrowser,pMouseEvent);
}

/// Signal mouse up event
void SignalsManager::signalMouseUp(
        crawl::WebBrowserIF& mozBrowser, 		///< crawl::WebBrowserIF to relay to slots.
        boost::shared_ptr<crawl::DomMouseEventIF>	pMouseEvent	)		///< Pointer to mouse event.
{
    m_MouseUpSig(mozBrowser,pMouseEvent);
}

/// Signal mouse click event
void SignalsManager::signalMouseClick(
        crawl::WebBrowserIF&                                 mozBrowser, 		///< crawl::WebBrowserIF to relay to slots.
        boost::shared_ptr<crawl::DomMouseEventIF>	pMouseEvent	)		///< Pointer to mouse event.
{
    m_MouseClickSig(mozBrowser,pMouseEvent);
}

/// Signal mouse double click event
void SignalsManager::signalMouseDblClick(
        crawl::WebBrowserIF&                                 mozBrowser, 		///< crawl::WebBrowserIF to relay to slots.
        boost::shared_ptr<crawl::DomMouseEventIF>	pMouseEvent	)		///< Pointer to mouse event.
{
    m_MouseDblClickSig(mozBrowser,pMouseEvent);
}

/// Signal mouse over event
void SignalsManager::signalMouseOver(
        crawl::WebBrowserIF&                                 mozBrowser, 		///< crawl::WebBrowserIF to relay to slots.
        boost::shared_ptr<crawl::DomMouseEventIF>	pMouseEvent	)		///< Pointer to mouse event.
{
    m_MouseOverSig(mozBrowser,pMouseEvent);
}

/// Signal mouse out event
void SignalsManager::signalMouseOut(
        crawl::WebBrowserIF&                                 mozBrowser, 		///< crawl::WebBrowserIF to relay to slots.
        boost::shared_ptr<crawl::DomMouseEventIF>	pMouseEvent	)		///< Pointer to mouse event.
{
    m_MouseOutSig(mozBrowser,pMouseEvent);
}

// -----------------------
// --- CALL: UI Events ---
// -----------------------
/// Signal activate event
void SignalsManager::signalActivate(
        crawl::WebBrowserIF&                             mozBrowser, 		///< crawl::WebBrowserIF to relay to slots.
        boost::shared_ptr<crawl::DomEventIF>	pUIEvent	)		///< Pointer DOM UI to event.
{
    m_ActivateSig(mozBrowser,pUIEvent);
}

/// Signal focus in event
void SignalsManager::signalFocusIn(
        crawl::WebBrowserIF&                             mozBrowser, 		///< crawl::WebBrowserIF to relay to slots.
        boost::shared_ptr<crawl::DomEventIF>	pUIEvent	)		///< Pointer DOM UI to event.
{
    m_FocusInSig(mozBrowser,pUIEvent);
}

/// Signal focus out event
void SignalsManager::signalFocusOut(
        crawl::WebBrowserIF&                             mozBrowser, 		///< crawl::WebBrowserIF to relay to slots.
        boost::shared_ptr<crawl::DomEventIF>	pUIEvent	)		///< Pointer DOM UI to event.
{
    m_FocusOutSig(mozBrowser,pUIEvent);
}

/// Signal context menu event
void SignalsManager::signalContextMenu(
        boost::uint32_t                         iContextFlags, 	///< Flags see nsIContextMenuListener
        boost::shared_ptr<crawl::DomEventIF>	pDOMEvent,		///< DOM event.
        boost::shared_ptr<crawl::DomNodeIF>     pDOMNode	)	///< DOM node of event
{
    m_ContextMenuSig(iContextFlags, pDOMEvent, pDOMNode);
}

// --------------------------
// --- CALL: Timer Events ---
// --------------------------
/// Signal timer event
void SignalsManager::signalContinuousTimer 	()
{
    m_ContinuousTimerSig();
}

/// Signal timer event
void SignalsManager::signalContinuousTimer2 	()
{
    m_ContinuousTimer2Sig();
}

/// Signal timer event
void SignalsManager::signalOneShotTimer		()
{
    m_OneShotTimerSig();
}

void SignalsManager::doCallMiningDoneSlot()
{
    m_OnMiningDoneSig();
}


