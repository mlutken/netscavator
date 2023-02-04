#ifndef _CREATOR_DOM_TREE_TEXT_CTRL_H_
#define _CREATOR_DOM_TREE_TEXT_CTRL_H_

#include <SignalsManager.h>
#include <ScriptMiner.h>
#include <base/BasePageCtrl.h>
#include <DomNodeIF.h>
#include <DomKeyEventIF.h>
#include <DomMouseEventIF.h>

class CreatorMainFrameWx;


namespace crawl {
    class DomKeyEventIF;
}

class DomTreeTextCtrl  : public BasePageCtrl
{
public:
	typedef crawl::LinearDomSearch::size_type	size_type;

    DomTreeTextCtrl	( CreatorMainFrameWx* pCreatorMainFrameWx );
	
	void 								textHtmlGet			( std::string& sTextHtml );
	
	virtual void						searchStringSet 	( std::string sSearchFor );
	virtual bool						findNext 			( );
	virtual void						focusActivate		();
	virtual void						focusDeactivate		();
	
    boost::shared_ptr<crawl::DomNodeIF>	containerNodeFromIndex 	( size_type iPos ) const;
	void								activePositionSet 		( size_type iPos );
	size_type							activePositionGet 		( )	const 				{ return m_iPosActive;	};
	void								scrollWindowToPos 		( size_type iPos, boost::int32_t iOffsetLines = 0 );
			

private:
	// --- PRIVATE: Functions ---	
// 	void			onClicked_BtnLoadUrl(wxCommandEvent& event);
    void 			slotKeyDown	( crawl::WebBrowserIF& mozBrowser, boost::shared_ptr<crawl::DomKeyEventIF> pDOMKeyEvent );
    void 			slotKeyPress( crawl::WebBrowserIF& mozBrowser, boost::shared_ptr<crawl::DomKeyEventIF> pDOMKeyEvent );
	
    std::string 	getNodeStyle 		( boost::shared_ptr<crawl::DomNodeIF> pNode ) const ;
    void 			appendNodeText		( std::string& sTextHtml, boost::shared_ptr<crawl::DomNodeIF> pNode, size_type	iPos );
	
	void 			appendHtmlHeader	( std::string& sTextHtml );	
	void 			appendHtmlFooter	( std::string& sTextHtml );	
	// --- PRIVATE: Data ---	
	
	SignalsManager::ConnectionT			m_connectionKeyDown;
	SignalsManager::ConnectionT			m_connectionKeyPress;
	CreatorMainFrameWx* 				m_pCreatorMainFrameWx;
    boost::shared_ptr<crawl::Crawler>	m_pCrawler;
    boost::shared_ptr<crawl::WebBrowserIF>		m_pMozDomTreeText;
	int									m_iIndentLvl;	
	size_type							m_iPosActive;
// 	DECLARE_EVENT_TABLE()
};




#endif // _CREATOR_DOM_TREE_TEXT_CTRL_H_

