#pragma once

#include <LinearDomIF.h>
#include <WebBrowserIF.h>

class DOMDocument;
class DOMNode;

namespace crawl {
class DomNodeIF;
class WebBrowserIF;
class WordMonitor;

/** Linear representation of a DOM document
@author Martin Lütken */
class WebKitDomDocumentLinearQt : public LinearDomIF {
public:

    // -------------------------------------------------
    // --- CONSTRUCTOR / INIT and DESTRUCTOR methods ---
    // -------------------------------------------------
    WebKitDomDocumentLinearQt( boost::shared_ptr<crawl::WebBrowserIF> pBrowser/*, boost::shared_ptr<DOMDocument> pDOMDoc */);
    virtual ~WebKitDomDocumentLinearQt();

    void createWebKitLinearDomFromNodeQt(
            boost::shared_ptr<WebBrowserIF> pBrowser
            );

    void wordMonitorSet(WordMonitor *wordMonitor);

private:

    // ---------------------------------
    // --- PRIVATE: Helper functions ---
    // ---------------------------------
//    virtual const_iterator       do_findFromRawPointer (boost::shared_ptr<DomNodeIF> pDomNode ) const;
//    virtual const_iterator       do_findFromNodeTreePointer (const void* pNativeNode ) const;

    void        indexTokenWords         ( const QString& text );


    //FIXME NEW QWebView
    QString     getText                 () const;
    int         countChildrenWithText   () const;
    QString     getChildrensText        () const;

    void        recurseCreateLinearDom  (int iDepthLevel, int parent_pos);
    void        recurseCreateLinearDomOLD  (int iDepthLevel );

    // ----------------------------
    // --- PRIVATE: Member data ---
    // ----------------------------
    boost::shared_ptr<WebBrowserIF>     m_pBrowser;
    int                                 m_iFrameCounter;
    WordMonitor*                        m_wordMonitor;
};


// ----------------------
// --- Free functions ---
// ----------------------
void createWebKitLinearDomFromNodeQt(
        boost::shared_ptr<WebBrowserIF>                 pBrowser
        , boost::shared_ptr<WebKitDomDocumentLinearQt>  pLinearDom
        );


} // END namespace crawl

