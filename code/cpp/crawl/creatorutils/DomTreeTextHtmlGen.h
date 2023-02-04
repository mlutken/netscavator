#pragma once

#include <DomNodeIF.h>
#include <LinearDomIF.h>

namespace crawl {

class DomTreeTextHtmlGen
{
public:
    typedef LinearDomIF::size_type	size_type;

    DomTreeTextHtmlGen	();

    void 			textRtfGet			( std::string& sTextRtf, const boost::shared_ptr<LinearDomIF> pLinearDom );
    void 			textHtmlGet			( std::string& sTextHtml, const boost::shared_ptr<LinearDomIF> pLinearDom );



private:
    // --- PRIVATE: Functions ---
    bool 			breakAfter          ( boost::shared_ptr<crawl::DomNodeIF> pNode ) const;
    bool 			breakBefore         ( boost::shared_ptr<crawl::DomNodeIF> pNode ) const;

    std::string 	getNodeClass 		( boost::shared_ptr<crawl::DomNodeIF> pNode ) const;
    std::string     getNodeColor        ( boost::shared_ptr<crawl::DomNodeIF> pNode ) const;
    void 			appendNodeRtf		( std::string& sTextHtml, boost::shared_ptr<crawl::DomNodeIF> pNode, size_type iPos );
    void 			appendNodeHtml		( std::string& sTextHtml, boost::shared_ptr<crawl::DomNodeIF> pNode, size_type iPos );

    void 			appendHtmlHeader	( std::string& sTextHtml );
    void 			appendHtmlFooter	( std::string& sTextHtml );
    // --- PRIVATE: Data ---

    boost::shared_ptr<LinearDomIF>      m_pLinearDom;
    std::string                         m_sTextHtml;
    int									m_iIndentLvl;
    bool                                m_bPreviousIsBreak;
};

} //END namespace crawl


