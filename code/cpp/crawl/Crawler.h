#pragma once

//#include <hacks/wx_h_include_hack.h>
//#include <hacks/wx_h_php_undef_hack.h>
#include <ostream>	
#include <boost/shared_ptr.hpp>	
#include <boost/signals2/signal.hpp>
#include <boost/format.hpp>

#include <WebBrowserIF.h>
#include <parser/LinearDomSearch.h>
#include <parser/StringSearch.h>
#include <url/Url.h>
#include <containers/UrlQueue.h>
#include <containers/WordMonitor.h>
#include <utils/string_algorithms.h>
#include <parser/LinksGetter.h>
#include <ScriptMinerIF.h>
#include <LinearDomIF.h>
#include <WebBrowserIF.h>
#include <DataWriterIF.h>

namespace bs2 = boost::signals2;
namespace bs = boost;


namespace crawl { 

class DomActionMgr;
class DomSearchMgr;
class ModifierMgr;
class SettingsMgr;
class ScriptingClassIF;
class Configuration;
class DomMouseEventIF;
class DomKeyEventIF;
class NetworkActivityLogger;

class Crawler : public ScriptMinerIF
{
public:
	// ----------------
	// --- Typedefs ---
	// ----------------
    typedef boost::signals2::connection						ConnectionT;
    //typedef bs2::signal<void (void)>                         ScanningDoneT;
	typedef boost::function< bool ( std::string const& ) >	UrlCompareFunctorT;
	typedef std::vector<UrlCompareFunctorT>					UrlCompareVecT;
	
    Crawler( boost::shared_ptr<crawl::WebBrowserIF> pMozBrowser
             , Url const& siteUrl
             , const DataWriterIF::DataWriterVecT& dataWriters
             , boost::shared_ptr<crawl::ScriptingClassIF> pScriptClass
             , boost::shared_ptr<Configuration> pConfig
             );

    virtual ~Crawler();
    void        assignWebBrowser        ( boost::shared_ptr<crawl::WebBrowserIF> pMozBrowser );

    void        reset                   ();
    void        init                    ();
    void		clearForReloadScript    () override;

    void        outputNameSet           ( const std::string sBaseOutputName );
    void        dataBaseOutputStreamClose   ();
    void        restart                     ( const std::string sBaseOutputName = "" );

	void		refresh					()									{ m_pMozBrowser->refresh();			}
	void		show					()									{ m_pMozBrowser->show();			}
	void		hide					()									{ m_pMozBrowser->hide();			}
    bool		loadURI					(  std::string const& sURI )		{ return m_pMozBrowser->loadUri(sURI); 	}

//     --------------------
//     --- PUBLIC: Info ---
//     --------------------

	// -------------------------------
	// --- Configuration functions ---
	// -------------------------------
	void		loadImages				( bool bLoadImages );
	void 		configAddIncludeUrl		( const std::string sPattern, StringCompareFunT fnCompare )	;
	void 		configAddExcludeUrl		( const std::string sPattern, StringCompareFunT fnCompare )	;
	
	
	// ------------------------
	// --- Helper functions ---
	// ------------------------
    bool		checkUrlInclude			( std::string const& sUrl   )	const	;
    bool		checkUrlExclude			( std::string const& sUrl   )	const	;
    bool        okToLoadUrl             ( std::string const& sUrl   )   const   ;

	
	// ---------------------------------------
	// --- Simple set/get inline functions ---
	// ---------------------------------------
//	void							configInsertEndTagNodes	( bool bInsertEndTagNodes) 	{ m_bInsertEndTagNodes = bInsertEndTagNodes;	}
//	void							configSkipEmptyNodes	( bool bSkipEmptyNodes) 	{ m_bSkipEmptyNodes = bSkipEmptyNodes;					}
//	void							configTrimBlanks		( bool bTrimBlanks) 		{ m_bTrimBlanks = bTrimBlanks;					}


// 	ConnectionT			
// 	connectOnScanningDone( const ScanningDoneT::slot_type& slot )	///< Function object to be called	
// 															{	return	m_OnScanningDone.connect(slot);		}

    void        domNodeToCurrentValue   ();
    void        buildLinearDom          ();

	
    boost::shared_ptr<crawl::WebBrowserIF>
    webBrowser() override				{	return m_pMozBrowser;		}
    const boost::shared_ptr<crawl::WebBrowserIF>
    webBrowser() const override			{	return m_pMozBrowser;		}

    boost::shared_ptr<LinearDomIF>
    linearDom()	override				{	return m_pLinearDom;		}
    const boost::shared_ptr<LinearDomIF>
    linearDom() const override			{	return m_pLinearDom;		}

    boost::shared_ptr<LinearDomSearch>
    linearDomSearch() override				{	return m_pLinearDomSearch;	}
    const boost::shared_ptr<LinearDomSearch>
    linearDomSearch() const	override		{	return m_pLinearDomSearch;	}

    boost::shared_ptr<LinksGetter>
    linksGetter()					{	return m_pLinksGetter;		}
    const boost::shared_ptr<LinksGetter>
    linksGetter() const				{	return m_pLinksGetter;		}

    boost::shared_ptr<DomActionMgr>
    domActionMgr()					{	return m_pDomActionMgr;		}
    const boost::shared_ptr<DomActionMgr>
    domActionMgr() const			{	return m_pDomActionMgr;		}

    boost::shared_ptr<DomSearchMgr>
    domSearchMgr() override			{	return m_pDomSearchMgr;		}
    const boost::shared_ptr<DomSearchMgr>
    domSearchMgr() const override	{	return m_pDomSearchMgr;		}

    boost::shared_ptr<ModifierMgr>
    modifierMgr()					{	return m_pModifierMgr;		}
    const boost::shared_ptr<ModifierMgr>
    modifierMgr() const				{	return m_pModifierMgr;		}

    boost::shared_ptr<SettingsMgr>
    settingsMgr()					{	return m_pSettingsMgr;		}
    const boost::shared_ptr<SettingsMgr>
    settingsMgr() const				{	return m_pSettingsMgr;		}

    StringSearch&       stringSearch()                              {	return m_stringSearch;		}
    const StringSearch& stringSearch() const                        {	return m_stringSearch;		}

    UrlQueue&           urlQueue    ()       override               { return m_urlQueue;			}
    const UrlQueue&     urlQueue    () const override               { return m_urlQueue;			}

    const Url&          siteUrlObj   () const                       {	return m_siteUrl;	}
    void                siteUrlObjSet( const Url& url)              {	m_siteUrl = url;	}

    std::string			siteUrl      () const;
    void				siteUrlSet   ( const std::string& sUrl)     {	m_siteUrl = Url(sUrl);      }

    const Url
    currentUrlObj() const			{	return Url( currentUrl() );		}

    const std::string
    currentUrl() const				{	return webBrowser()->currentUri();}

	bool
	progressOutput() const			{	return m_bProgressOutput;	}
	
	void 
	progressOutput					( bool bEnable )				{	m_bProgressOutput = bEnable;	}
	
	bool
	debugOutput() const				{	return m_bDebugOutput;		}
	
	void 
	debugOutput						( bool bEnable )				{	m_bDebugOutput = bEnable;		}
	
	void	
	createProgressOut				( const std::string& sName );
	
	void	
	writeProgress					( const std::string& sMsg, bool bAppendEndl = true );
	
	void	
	writeProgress					( const boost::format& msg, bool bAppendEndl = true );
	
    boost::shared_ptr<NetworkActivityLogger>    networkActivityLogger() const;
    void                                        networkActivityLoggerSet(const boost::shared_ptr<NetworkActivityLogger>& networkActivityLogger);

private:
    // --------------------------
    // --- PRIVATE: Functions ---
    // --------------------------
    bool            slotNetProgress     ( void* aRequest, boost::uint32_t aStateFlags, const std::string& sUri );
    bool			slotLoadUri         ( crawl::WebBrowserIF& webBrowser, const std::string& sUri);
    void			slotPageLoaded      ( crawl::WebBrowserIF& webBrowser );
    void            slotMouseDown       ( crawl::WebBrowserIF&, boost::shared_ptr<crawl::DomMouseEventIF> );
    void            connectSignals      ();
    void            disconnectSignals   ();

		
	// -------------------
	// --- Member Data ---
	// -------------------
    boost::shared_ptr<crawl::WebBrowserIF>      m_pMozBrowser;
    StringSearch                                m_stringSearch;
    Url                                         m_siteUrl;
    UrlQueue                                    m_urlQueue;
    WordMonitor                                 m_wordMonitor;
    boost::shared_ptr<NetworkActivityLogger>    m_networkActivityLogger;
    bool                                        m_bProgressOutput;
    bool                                        m_bDebugOutput;

	Url		 								m_currentUrl;
    boost::shared_ptr<LinearDomIF>          m_pLinearDom;
	boost::shared_ptr<LinearDomSearch>		m_pLinearDomSearch;
	boost::shared_ptr<LinksGetter>			m_pLinksGetter;
	boost::shared_ptr<DomActionMgr>			m_pDomActionMgr;
	boost::shared_ptr<DomSearchMgr>			m_pDomSearchMgr;
	boost::shared_ptr<ModifierMgr>			m_pModifierMgr;
	boost::shared_ptr<SettingsMgr>			m_pSettingsMgr;
	
    ////ScanningDoneT							m_OnScanningDone;
	
	UrlCompareVecT							m_includeUrlFunctors;
	UrlCompareVecT							m_excludeUrlFunctors;
	
    ConnectionT                             m_connectionNetProgress;
    ConnectionT								m_connectionPageLoaded;
	ConnectionT								m_connectionLoadUri;
    ConnectionT                             m_connectionMouseDown;
protected:
    boost::uint64_t                         m_iCountActivityAny;

};

} // END namespace crawl



