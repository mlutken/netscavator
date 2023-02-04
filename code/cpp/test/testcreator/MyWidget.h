#ifndef _MY_WIDGET_H
#define _MY_WIDGET_H

#include <QGridLayout>
#include <QPushButton>
#include <QWidget>
#include <QSplitter>
#include <QLineEdit>
#include <QTextEdit>
#include <SignalsManager.h>
#include <WebKitDomDocumentLinearQt.h>
#include <WebKitBrowserQt.h>
#include <OutputViewUi.h>
//#include <creatorutils/DomTreeTextHtmlGen.h>
#include "CreatorWebView.h"
#include <CreatorWebViewUi.h>
#include <CreatorTextDomTreeView.h>

#include "lcdrange.h"

namespace crawl {
    class DataWriterXml;
    class OutputViewCtrl;
}

class ScriptMiner;
struct PhpEmbedConfig;

class MyWidget : public QWidget
{
    Q_OBJECT

public:
    MyWidget( QWidget *parent = 0);
    ~MyWidget();
    void    pageLoadedSlot( crawl::WebBrowserIF& browser );

    boost::shared_ptr<crawl::WebBrowserIF>  browser ()   { return m_pBrowser; }
    boost::shared_ptr<ScriptMiner>          miner   ()   { return m_pMiner; }


public slots:
    void        loadUrlSlot             ();
    void        executePhpSlot          ();
    void        webElementSelectedSlot  (CreatorWebViewUi* pWebView);


private:
    // --- DATA ---
    CreatorWebView*                             m_pWebViewBrowser;
    CreatorTextDomTreeView*                     m_pDomTreeText;
    QTextEdit*                                  m_pScriptTextEdit;
    OutputViewUi*                               m_pDataOutView;
//    crawl::OutputViewCtrl                       m_pDataOutEdit;

    QLineEdit*                                  m_pUrlEdit;
    boost::shared_ptr<crawl::DataWriterXml>     m_pXmlOut;
    boost::shared_ptr<crawl::OutputViewCtrl>    m_pOutputViewCtrl;
    boost::shared_ptr<crawl::WebKitBrowserQt>   m_pBrowser;
    boost::shared_ptr<crawl::LinearDomIF>       m_pLinearDom;
    boost::shared_ptr<ScriptMiner>              m_pMiner;

};


#endif //_MY_WIDGET_H


