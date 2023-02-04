#ifndef _CREATOR_BROWSER_WINDOW_CTRL_H_
#define _CREATOR_BROWSER_WINDOW_CTRL_H_

#include <DomKeyEventIF.h>
#include <DomMouseEventIF.h>
#include <SignalsManager.h>
#include <ScriptMiner.h>
#include <base/BasePageCtrl.h>


class CreatorMainFrameWx;

class BrowserWindowCtrl : public BasePageCtrl  
{
public:

    BrowserWindowCtrl	( CreatorMainFrameWx* pCreatorMainFrameWx );
	
	virtual void			searchStringSet 	( std::string sSearchFor );
    virtual bool			findNext 			();
	virtual void			focusActivate		();
	virtual void			focusDeactivate		();

private:
	// --- PRIVATE: Functions ---	
    void 		slotKeyDown	( crawl::WebBrowserIF& mozBrowser, boost::shared_ptr<crawl::DomKeyEventIF> pDOMKeyEvent );
    void 		slotKeyPress( crawl::WebBrowserIF& mozBrowser, boost::shared_ptr<crawl::DomKeyEventIF> pDOMKeyEvent );
    void		slotContextMenu( boost::uint32_t iContextFlags
                                 , boost::shared_ptr<crawl::DomEventIF> pDOMEvent
                                 , boost::shared_ptr<crawl::DomNodeIF> pDomNode  );
    void 		slotPageLoaded( crawl::WebBrowserIF& mozBrowser );

	// --- PRIVATE: Data ---	
	
    SignalsManager::ConnectionT             m_connectionKeyDown;
    SignalsManager::ConnectionT             m_connectionKeyPress;
    SignalsManager::ConnectionT             m_connectionContextMenu;
    CreatorMainFrameWx*                     m_pCreatorMainFrameWx;
    boost::shared_ptr<ScriptMiner>          m_pMiner;
    boost::shared_ptr<crawl::WebBrowserIF>	m_pMozDomTreeText;
};




#endif // _CREATOR_BROWSER_WINDOW_CTRL_H_

