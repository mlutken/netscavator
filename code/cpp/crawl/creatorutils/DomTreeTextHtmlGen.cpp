#include "DomTreeTextHtmlGen.h"
#include <stdio.h>
#include <set>
#include <boost/algorithm/string.hpp>
#include <boost/assign/list_of.hpp>
#include <cpaf_libs/utils/cpaf_string_utils.hpp>

using namespace std;
using namespace boost::assign; // bring 'list_of()' into scope

namespace crawl {


DomTreeTextHtmlGen::DomTreeTextHtmlGen()
    : m_bPreviousIsBreak(false)
{
}






void DomTreeTextHtmlGen::textHtmlGet( std::string& sTextHtml, const boost::shared_ptr<LinearDomIF> pLinearDom )
{
    m_pLinearDom = pLinearDom;
    sTextHtml.clear();

    appendHtmlHeader( sTextHtml );

    m_iIndentLvl = 0;

    size_type iPos = 0;
    LinearDomIF::const_iterator it      = m_pLinearDom->begin();
    LinearDomIF::const_iterator itEND   = m_pLinearDom->end();
    size_t i = 0;
    for ( ; it != itEND; ++it ) {
        i++;
        appendNodeHtml( sTextHtml, it->node(), ++iPos );
    }
    appendHtmlFooter( sTextHtml );
}


void DomTreeTextHtmlGen::textRtfGet( std::string& sTextRtf, const boost::shared_ptr<LinearDomIF> pLinearDom )
{
    m_pLinearDom = pLinearDom;
    sTextRtf.clear();

    appendHtmlHeader( sTextRtf );

    m_iIndentLvl = 0;

    size_type iPos = 0;
    LinearDomIF::const_iterator it      = m_pLinearDom->begin();
    LinearDomIF::const_iterator itEND   = m_pLinearDom->end();
    size_t i = 0;
    for ( ; it != itEND; ++it ) {
        i++;
        appendNodeRtf( sTextRtf, it->node(), ++iPos );
    }
    appendHtmlFooter( sTextRtf );
}



// --------------------------
// --- PRIVATE: Functions ---
// --------------------------

bool DomTreeTextHtmlGen::breakAfter ( boost::shared_ptr<crawl::DomNodeIF> pNode ) const
{
    static const set<std::string> exceptELEM = list_of("A")
            ("B")("I")("U")
            ("LI")
            ("TITLE")
            ;

    static const set<std::string> exceptEND_TAG = list_of("/A")
            ("/B")("/I")("/U")
            ;

    const std::string sNodeVal = pNode->stringDataUTF8();
    bool insertBreak = false;
    if ( DomNodeTypes::ELEMENT == pNode->nodeType() ) {
        insertBreak = true;
        if ( exceptELEM.find( sNodeVal ) != exceptELEM.end() ) {
            insertBreak = false;
        }
    }
    else if ( DomNodeTypes::ELEMENT_END_TAG == pNode->nodeType() ) {
        insertBreak = true;
        if ( exceptEND_TAG.find( sNodeVal ) != exceptEND_TAG.end() ) {
            insertBreak = false;
        }
    }
    return insertBreak;
}


bool DomTreeTextHtmlGen::breakBefore ( boost::shared_ptr<crawl::DomNodeIF> pNode ) const
{
    static const set<std::string> exceptELEM = list_of("A")
            ("B")("I")("U")
            ("LI")
            ("TITLE")
            ;

    static const set<std::string> exceptEND_TAG = list_of("/A")
            ("/B")("/I")("/U")
            ("/TITLE")("/LI")
            ;

    const std::string sNodeVal = pNode->stringDataUTF8();
    bool insertBreak = false;
    if ( DomNodeTypes::ELEMENT == pNode->nodeType() ) {
        insertBreak = true;
        if ( exceptELEM.find( sNodeVal ) != exceptELEM.end() ) {
            insertBreak = false;
        }
    }
    else if ( DomNodeTypes::ELEMENT_END_TAG == pNode->nodeType() ) {
        insertBreak = true;
        if ( exceptEND_TAG.find( sNodeVal ) != exceptEND_TAG.end() ) {
            insertBreak = false;
        }
    }
    return insertBreak;
}

std::string DomTreeTextHtmlGen::getNodeClass ( boost::shared_ptr<crawl::DomNodeIF> pNode ) const
{
    std::string sClass;
    switch ( pNode->nodeType() ) {
    case crawl::DomNodeTypes::ELEMENT :
    case crawl::DomNodeTypes::ELEMENT_END_TAG:
    case crawl::DomNodeTypes::DOCUMENT :
        sClass = "ClassELEMENT ClassALIGN_LEFT";
        break;
    case crawl::DomNodeTypes::TEXT :
        sClass = "ClassTEXT ClassALIGN_LEFT";
        break;
    case crawl::DomNodeTypes::ATTRIBUTE :
        sClass = "ClassATTRIBUTE ClassALIGN_LEFT";
        break;
    case crawl::DomNodeTypes::ATTRIBUTE_VALUE :
        sClass = "ClassATTRIBUTE_VALUE ClassALIGN_LEFT";
        break;
    case crawl::DomNodeTypes::COMMENT :
        sClass = "ClassCOMMENT ClassALIGN_LEFT";
        break;
    default:
        sClass = "ClassDEFAULT ClassALIGN_LEFT";
    }
    return sClass;
}

//    sTextHtml += "<style type='text/css'>\n.different-text-color { color: Cyan; }\n</style>";
//    sTextHtml += "<style type='text/css'>\n.ClassActive { background-color: PowderBlue; }\n</style>";
//    sTextHtml += "<style type='text/css'>\n.ClassELEMENT { color: DarkBlue; }\n</style>";
//    sTextHtml += "<style type='text/css'>\n.ClassATTRIBUTE { color: DarkGreen ; }\n</style>";
//    sTextHtml += "<style type='text/css'>\n.ClassATTRIBUTE_VALUE { color: LimeGreen; }\n</style>";
//    sTextHtml += "<style type='text/css'>\n.ClassCOMMENT { color: Magenta; }\n</style>";
//    sTextHtml += "<style type='text/css'>\n.ClassDEFAULT { color: Darkorange; }\n</style>";
//    sTextHtml += "<style type='text/css'>\n.ClassINDENTION { }\n</style>";
//    sTextHtml += "<style type='text/css'>\n.ClassALIGN_LEFT { text-align: left; float:left;}\n</style>";

std::string DomTreeTextHtmlGen::getNodeColor ( boost::shared_ptr<crawl::DomNodeIF> pNode ) const
{
    std::string sClass;
    switch ( pNode->nodeType() ) {
    case crawl::DomNodeTypes::ELEMENT :
    case crawl::DomNodeTypes::ELEMENT_END_TAG:
    case crawl::DomNodeTypes::DOCUMENT :
        sClass = "darkblue";
        break;
    case crawl::DomNodeTypes::TEXT :
        sClass = "black";
        break;
    case crawl::DomNodeTypes::ATTRIBUTE :
        sClass = "darkgreen";
        break;
    case crawl::DomNodeTypes::ATTRIBUTE_VALUE :
        sClass = "limegreen";
        break;
    default:
        sClass = "darkorange";
    }
    return sClass;
}


void DomTreeTextHtmlGen::appendNodeRtf		(
        std::string& sTextRtf,
        boost::shared_ptr<crawl::DomNodeIF> pNode, 						///< Node (pointer) to print.
        size_type /*iPos*/
        )
{
    using namespace std;
    std::string sNodeVal = pNode->stringDataUTF8();
//    boost::algorithm::replace_all( sNodeVal, "<", "&lt;");
//    boost::algorithm::replace_all( sNodeVal, ">", "&gt;");
//    boost::algorithm::replace_all( sNodeVal, std::string("\302\240"), std::string("&amp;nbsp;") );
    sTextRtf += sNodeVal + ", ";
}



void DomTreeTextHtmlGen::appendNodeHtml		(
        std::string& sTextHtml,
        boost::shared_ptr<crawl::DomNodeIF> pNode, 						///< Node (pointer) to print.
        size_type iPos
        )
{
    using namespace std;
    std::string sNodeVal = pNode->stringDataUTF8();
    if ( sNodeVal == "" || sNodeVal == " " ) {
        printf("WARNING: nodeType: %d nodeName: '%s'  '%s'\n", pNode->nodeType(), pNode->nodeName().c_str(), sNodeVal.c_str());
    }
    boost::algorithm::replace_all( sNodeVal, "<", "&lt;");
    boost::algorithm::replace_all( sNodeVal, ">", "&gt;");
    boost::algorithm::replace_all( sNodeVal, std::string("\302\240"), std::string("&amp;nbsp;") );
    std::string sClass = getNodeClass( pNode );
    std::string sColor = getNodeColor( pNode );

    //bool bInsertBreak = false;    // TODO: Why is this not used?

    if ( pNode->nodeType() == crawl::DomNodeTypes::ELEMENT && pNode->hasChildNodes() )
    {
        if ( sNodeVal != "A" && sNodeVal != "B" ) {
            //bInsertBreak = true;
        }
    }

    if ( pNode->nodeType() == crawl::DomNodeTypes::ELEMENT_END_TAG ) {
        if ( sNodeVal != "/A" && sNodeVal != "/B"  && sNodeVal != "/LI" ) {
            //bInsertBreak = true;
        }
    }

    const bool bBreakBefore = breakBefore( pNode );
    if ( !m_bPreviousIsBreak && bBreakBefore )
    {
//        sTextHtml += "<br />\n";
    }
//    const bool bNewLine = m_bPreviousIsBreak || bBreakBefore;
//    if ( bNewLine && pNode->depthLevelGet()) {
//        sTextHtml += "<div class='ClassINDENTION ClassALIGN_LEFT' >";
//        for ( int i = pNode->depthLevelGet(); i > 0; --i ) {
//            sTextHtml += "&nbsp;" ;
//        }
//        sTextHtml += "</div>";
//    }
    std::string sID = "";
    if ( DomNodeTypes::ELEMENT == pNode->nodeType() ) {
  //      sID +=  " id='" + std::to_string(iPos) + "'";
    }
    sTextHtml += "<div" + sID + " name='" + std::to_string(iPos) + "' class='" + sClass + "' >" + sNodeVal + ", </div>" ;
//    sTextHtml += "<div id='" + std::to_string(iPos) + "' style='color:" + sColor + "' >" + sNodeVal + ", </div>" ;
//      sTextHtml += "<div style='text-align:left;float:left;color:" + sColor + "' >" + sNodeVal + ", </div>" ;
//    sTextHtml += "<div>" + sNodeVal + ", </div>" ;

    m_bPreviousIsBreak = false;
    if ( breakAfter( pNode ) )
    {
//        sTextHtml += "<br />\n";
        m_bPreviousIsBreak = true;
    }
}


void DomTreeTextHtmlGen::appendHtmlHeader	( std::string& sTextHtml )
{
    sTextHtml += "<html xmlns='http://www.w3.org/1999/xhtml'>\n";
    sTextHtml += "<head>\n\t<meta http-equiv='content-type' content='text/html; charset=utf-8'/>\n";
    sTextHtml += "<style type='text/css'>\n.different-text-color { color: Cyan; }\n</style>";
    sTextHtml += "<style type='text/css'>\n.ClassActive { background-color: PowderBlue; }\n</style>";
    sTextHtml += "<style type='text/css'>\n.ClassELEMENT { color: DarkBlue; }\n</style>";
    sTextHtml += "<style type='text/css'>\n.ClassATTRIBUTE { color: DarkGreen ; }\n</style>";
    sTextHtml += "<style type='text/css'>\n.ClassATTRIBUTE_VALUE { color: LimeGreen; }\n</style>";
    sTextHtml += "<style type='text/css'>\n.ClassCOMMENT { color: Magenta; }\n</style>";
    sTextHtml += "<style type='text/css'>\n.ClassDEFAULT { color: Darkorange; }\n</style>";
    sTextHtml += "<style type='text/css'>\n.ClassINDENTION { }\n</style>";
    sTextHtml += "<style type='text/css'>\n.ClassALIGN_LEFT { text-align: left; float:left;}\n</style>";
    sTextHtml += "</head>\n<body>\n";
}

void DomTreeTextHtmlGen::appendHtmlFooter	( std::string& sTextHtml )
{
    sTextHtml += "\n</body>\n</html>\n";
}


} //END namespace crawl
