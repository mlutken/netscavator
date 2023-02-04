#ifndef _WEBBROWSE_SIGNALS_MANAGER_H_
#define _WEBBROWSE_SIGNALS_MANAGER_H_

#include <QPointer>
#include <QObject>

#include <iostream>

#include <boost/cstdint.hpp>
#include <boost/shared_ptr.hpp>	
#include <boost/signals2/signal.hpp>
#include <boost/bind.hpp>


namespace crawl {
    class WebBrowserIF;
    class DomNodeIF;
    class DomEventIF;
    class DomKeyEventIF;
    class DomMouseEventIF;
    class MinerWorkerIF;
}


// combiner which returns the logical AND of all slot return values
template<typename T>
struct and_combiner
{
  typedef T result_type;

  template<typename InputIterator>
  T operator()(InputIterator first, InputIterator last) const
  {
    // If there are no slots to call, just return the
    // default-constructed value
    if(first == last ) return T(static_cast<T>(1));
    T val = *first++;
    while (first != last) {
      val = val && *first;
      ++first;
    }
    return val;
  }
};


namespace bs2 = boost::signals2;
namespace bs = boost;

/** Signals manager class. */
class SignalsManager : public QObject {
    Q_OBJECT
public:
    // ----------------
    // --- Typedefs ---
    // ----------------
    typedef boost::signals2::connection			ConnectionT;

    // -------------------------------
    // --- PUBLIC: Signal Typedefs ---
    // -------------------------------
    typedef boost::signals2::signal<void (void)>                                                            VoidVoidSignalT;
    typedef boost::signals2::signal<void (std::string)>                                                     VoidStringSignalT;
    typedef VoidVoidSignalT                                                                                 TimerSignalT;
    typedef boost::signals2::signal<bool (void)>                                                            CloseSignalT;
    typedef boost::signals2::signal<bool (void*, boost::uint32_t, const std::string&), and_combiner<bool> > NetProgressSignalT;
    typedef boost::signals2::signal<void (crawl::WebBrowserIF&)>                                            SimpleSignalT;
    typedef SimpleSignalT                                                                                   PageLoadedSignalT;
    typedef boost::signals2::signal<void (crawl::WebBrowserIF&, const std::string&)>                        VoidMozStringSignalT;
    typedef boost::signals2::signal<bool (crawl::WebBrowserIF&, const std::string&)>                        BoolMozStringSignalT;
    typedef boost::signals2::signal<void (crawl::WebBrowserIF&, boost::shared_ptr<crawl::DomMouseEventIF>)>	MouseEventSignalT;
    typedef boost::signals2::signal<void (crawl::WebBrowserIF&, boost::shared_ptr<crawl::DomKeyEventIF>)>   KeyEventSignalT;
    typedef boost::signals2::signal<void (crawl::WebBrowserIF&, boost::shared_ptr<crawl::DomEventIF>)>      UIEventSignalT;
    typedef boost::signals2::signal<void (boost::uint32_t, boost::shared_ptr<crawl::DomEventIF>, boost::shared_ptr<crawl::DomNodeIF>)>		ContextMenuSignalT;
	
	
    // ------------------------------------
    // --- Constructor / Init Functions ---
    // ------------------------------------
    SignalsManager();
    virtual ~SignalsManager();

    QPointer<crawl::MinerWorkerIF> minerWorker() const;
    void minerWorkerSet(const QPointer<crawl::MinerWorkerIF>& minerWorker);

    // -------------------------------
    // --- CONNECT: Misc Functions ---
    // -------------------------------
    ConnectionT     connectOnNetProgress    ( const NetProgressSignalT::slot_type& slot     );
    ConnectionT     connectOnNetStart       ( const VoidMozStringSignalT::slot_type& slot   );
    ConnectionT     connectOnLoadUri        ( const BoolMozStringSignalT::slot_type& slot   );
    ConnectionT     connectOnMiningDone     ( const VoidVoidSignalT::slot_type& slot        );
    ConnectionT     connectOnClose          ( const CloseSignalT::slot_type& slot           );
    ConnectionT     connectOnMatchHandler   ( const VoidVoidSignalT::slot_type& slot        );

    // -----------------------------------
    // --- CONNECT: Progress Functions ---
    // -----------------------------------
    ConnectionT		connectPageLoaded       ( const PageLoadedSignalT::slot_type& slot );
    ConnectionT		connectDomChanged       ( const PageLoadedSignalT::slot_type& slot );

    // ---------------------------
    // --- CONNECT: Key Events ---
    // ---------------------------
    ConnectionT     connectKeyDown          ( const KeyEventSignalT::slot_type& slot );
    ConnectionT     connectKeyUp            ( const KeyEventSignalT::slot_type& slot );
    ConnectionT     connectKeyPress         ( const KeyEventSignalT::slot_type& slot );

    // -----------------------------
    // --- CONNECT: Mouse Events ---
    // -----------------------------
    ConnectionT     connectMouseDown        ( const MouseEventSignalT::slot_type& slot );
    ConnectionT     connectMouseUp          ( const MouseEventSignalT::slot_type& slot );
    ConnectionT		connectMouseClick       ( const MouseEventSignalT::slot_type& slot );
    ConnectionT     connectMouseDblClick    ( const MouseEventSignalT::slot_type& slot );
    ConnectionT		connectMouseOver        ( const MouseEventSignalT::slot_type& slot );
    ConnectionT		connectMouseOut         ( const MouseEventSignalT::slot_type& slot );

    // --------------------------
    // --- CONNECT: UI Events ---
    // --------------------------
    ConnectionT		connectActivate         ( const UIEventSignalT::slot_type& slot );
    ConnectionT     connectFocusIn          ( const UIEventSignalT::slot_type& slot );
    ConnectionT		connectFocusOut         ( const UIEventSignalT::slot_type& slot );
    ConnectionT     connectContextMenu      ( const ContextMenuSignalT::slot_type& slot );
	
	
    // -----------------------------
    // --- CONNECT: Timer Events ---
    // -----------------------------
    ConnectionT		connectContinuousTimer  ( const TimerSignalT::slot_type& slot );
    ConnectionT		connectContinuousTimer2 ( const TimerSignalT::slot_type& slot );
    ConnectionT     connectOneShotTimer     ( const TimerSignalT::slot_type& slot );
	
    // ----------------------------
    // --- CALL: Misc Functions ---
    // ----------------------------
    bool    signalOnNetProgress ( void* aRequest, boost::uint32_t aStateFlags, const std::string& sUri );
    void    signalOnNetStart	( crawl::WebBrowserIF& mozBrowser, const std::string& sUri );
    bool    signalOnLoadUri     ( crawl::WebBrowserIF& mozBrowser, const std::string& sUri );

    void    signalOnMiningDone  (); // This slot can be called from mining worker thread, uses internal QT signal/slot to avoid cross thread problems
    bool    signalOnClose       ();
    void    signalOnMatch       ();

public:
    // --------------------------------
    // --- CALL: Progress Functions ---
    // --------------------------------
    void    signalPageLoaded    ( crawl::WebBrowserIF& mozBrowser );
    void    signalDomChanged    ( crawl::WebBrowserIF& mozBrowser );

    // --------------------------
    // --- CALL: Key Events ---
    // --------------------------
    void    signalKeyDown       ( crawl::WebBrowserIF& mozBrowser, boost::shared_ptr<crawl::DomKeyEventIF> pKeyEvent );
    void    signalKeyUp         ( crawl::WebBrowserIF& mozBrowser, boost::shared_ptr<crawl::DomKeyEventIF> pKeyEvent );
    void    signalKeyPress      ( crawl::WebBrowserIF& mozBrowser, boost::shared_ptr<crawl::DomKeyEventIF> pKeyEvent );

    // --------------------------
    // --- CALL: Mouse Events ---
    // --------------------------
    void    signalMouseDown     ( crawl::WebBrowserIF& mozBrowser, boost::shared_ptr<crawl::DomMouseEventIF>	pMouseEvent	);
    void    signalMouseUp       ( crawl::WebBrowserIF& mozBrowser, boost::shared_ptr<crawl::DomMouseEventIF>	pMouseEvent	);
    void    signalMouseClick    ( crawl::WebBrowserIF& mozBrowser, boost::shared_ptr<crawl::DomMouseEventIF>	pMouseEvent	);
    void    signalMouseDblClick ( crawl::WebBrowserIF& mozBrowser, boost::shared_ptr<crawl::DomMouseEventIF>	pMouseEvent	);
    void    signalMouseOver     ( crawl::WebBrowserIF& mozBrowser, boost::shared_ptr<crawl::DomMouseEventIF>	pMouseEvent	);
    void    signalMouseOut      ( crawl::WebBrowserIF& mozBrowser, boost::shared_ptr<crawl::DomMouseEventIF>	pMouseEvent	);

    // -----------------------
    // --- CALL: UI Events ---
    // -----------------------
    void    signalActivate      ( crawl::WebBrowserIF& mozBrowser, boost::shared_ptr<crawl::DomEventIF>	pUIEvent	);
    void    signalFocusIn       ( crawl::WebBrowserIF& mozBrowser, boost::shared_ptr<crawl::DomEventIF>	pUIEvent	);
    void    signalFocusOut      ( crawl::WebBrowserIF& mozBrowser, boost::shared_ptr<crawl::DomEventIF>	pUIEvent	);
    void    signalContextMenu   ( boost::uint32_t iContextFlags, boost::shared_ptr<crawl::DomEventIF> pDOMEvent, boost::shared_ptr<crawl::DomNodeIF> pDOMNode	);
    // --------------------------
    // --- CALL: Timer Events ---
    // --------------------------
    void    signalContinuousTimer 	();
    void    signalContinuousTimer2 	();
    void    signalOneShotTimer		();

signals:
    void    doCallMiningDoneSignal  ();
private slots:
    void    doCallMiningDoneSlot    ();

	
private:

    VoidVoidSignalT                     m_OnMiningDoneSig;
    CloseSignalT						m_OnCloseSig;
    VoidVoidSignalT                     m_OnMatchSig;
    VoidMozStringSignalT				m_OnNetStartSig;
    NetProgressSignalT                  m_OnNetProgressSig;
    BoolMozStringSignalT				m_OnLoadUriSig;
    PageLoadedSignalT					m_PageLoadedSig;
    PageLoadedSignalT					m_DomChangedSig;
    KeyEventSignalT						m_KeyDownSig;
    KeyEventSignalT						m_KeyUpSig;
    KeyEventSignalT						m_KeyPressSig;
    MouseEventSignalT					m_MouseDownSig;
    MouseEventSignalT					m_MouseUpSig;
    MouseEventSignalT					m_MouseClickSig;
    MouseEventSignalT					m_MouseDblClickSig;
    MouseEventSignalT					m_MouseOverSig;
    MouseEventSignalT					m_MouseOutSig;
    UIEventSignalT						m_ActivateSig;
    UIEventSignalT						m_FocusInSig;
    UIEventSignalT						m_FocusOutSig;
    ContextMenuSignalT					m_ContextMenuSig;
    TimerSignalT						m_ContinuousTimerSig;
    TimerSignalT						m_ContinuousTimer2Sig;
    TimerSignalT						m_OneShotTimerSig;
    QPointer<crawl::MinerWorkerIF>      m_minerWorker;

};


#endif // _WEBBROWSE_SIGNALS_MANAGER_H_




