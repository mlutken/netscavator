
#include "MyWidget.h"
#include <fstream>
#include <map>
#include <boost/algorithm/string.hpp>
#include <boost/assign/list_of.hpp>
#include <cpaf_stl_utils.h>
#include <QApplication>
#include <QClipboard>

#include <ScriptMiner.h>
#include <Configuration.h>
#include <Globals.h>
#include <php_embedding/php_embedding_utils.h>
#include <php_embedding/php_embedding_callbacks.h>
#include <scriptcrawl_private_php.h>
#include <url/Url.h>
#include <WebKitDomNodeQt.h>
#include <parser/DataWriterXml.h>
#include <OutputViewCtrl.h>

using namespace crawl;
using namespace std;
using namespace boost;
using namespace boost::assign; // bring 'list_of()' into scope

using namespace crawl;

const int MAX_ARGS = 10;


MyWidget::MyWidget(
      QWidget *parent)
    : QWidget       ( parent        )
{
    boost::shared_ptr<crawl::Configuration> c= crawl::g()->configuration();


    // --- Init php ---
//    startupPhp( c->valueStrGet("php-ini-path").c_str() );
//    executePhpString("require_once 'webminer.php';");

    char** argvPhp;
    int  argcPhp;

    argvPhp = allocateArrayOfStrings(MAX_ARGS, 256);
    c->getScriptArgvArgc( argcPhp, argvPhp );

    shutdownPhp();
    startupPhpScript(c->valueStrGet("php-ini-path").c_str(), argcPhp, argvPhp );
    freeArrayOfStrings( argvPhp, MAX_ARGS );

    executePhpString("require_once 'webminer.php';");

//    executePhpString( "echo 'hej';\n" );
//    executePhpString( "dbgSimpleTestFunction();" );
//    executePhpString( "dbgIntParam(13);" );
//    executePhpString( "dbgSimpleTestFunction();" );



    boost::shared_ptr<crawl::ScriptingClassIF> pScriptingClass = createPhpScriptingClass();

    QPushButton* urlLoadBtn = new QPushButton(tr("Load"));
    urlLoadBtn->setFont(QFont("Times", 12, QFont::Bold));

    QPushButton* executePhpBtn = new QPushButton(tr("Test PHP"));
    urlLoadBtn->setFont(QFont("Times", 10, QFont::Normal));



    QSplitter* toolBarSplitter = new QSplitter(parent);
    QVBoxLayout* layout = new QVBoxLayout;

    m_pScriptTextEdit = new QTextEdit(parent);
    m_pDataOutView = new OutputViewUi(parent);
    m_pUrlEdit = new QLineEdit(parent);
    m_pWebViewBrowser = new CreatorWebView(parent);
    m_pDomTreeText = new CreatorTextDomTreeView(parent);
    m_pBrowser = boost::shared_ptr<WebKitBrowserQt> (new WebKitBrowserQt(m_pWebViewBrowser) );
    m_pBrowser->runModeSet( crawl::rmDesignE );

    std::string sMinerName      = "Crawler";
    std::string sBaseOutputName = "Crawler";

    m_pXmlOut           = boost::shared_ptr<crawl::DataWriterXml> ( new crawl::DataWriterXml(c->outputDirGet(), "") );
    m_pOutputViewCtrl   = boost::shared_ptr<crawl::OutputViewCtrl>( new crawl::OutputViewCtrl(sBaseOutputName, m_pDataOutView)) ;
    StringSearch::DataWriterVecT writers;
    writers.push_back(m_pXmlOut);
    writers.push_back(m_pOutputViewCtrl);

    g_phpEmbedCallbacks::Instance().writeFun = boost::bind(&OutputViewCtrl::phpStdOutputWrite, m_pOutputViewCtrl.get(), _1, _2 );
    g_phpEmbedCallbacks::Instance().logMsgFun = boost::bind(&OutputViewCtrl::phpLogMessage, m_pOutputViewCtrl.get(), _1 );


    m_pMiner = boost::shared_ptr<ScriptMiner>(
                new ScriptMiner(m_pBrowser,sMinerName, sBaseOutputName, crawl::Url(""), writers, pScriptingClass, c )
        );
    m_pMiner->runModeSet( crawl::rmDesignE );
    setMinerPointerRaw(m_pMiner.get());
    g()->minerAdd( m_pMiner, sMinerName );

//    m_pBrowser->loadUri("http://sleipnerexamples.com.localhost/sites/" );
//    m_pBrowser->loadUri("http://sleipnerexamples.com.localhost/sites/TestDomTree/index.html" );
//    m_pBrowser->loadUri("http://sleipnerexamples.com.localhost/sites/ExNavigatorAndSelects/searchlisting.php?clothes_type=dress&fabric_type=wool&page=0");
//    m_pBrowser->loadUri("http://sleipnerexamples.com.localhost/sites/ExNavigatorAndSelects/dosearch.php" );

    m_pBrowser->loadUri( c->valueStrGet("url") );
    m_pWebViewBrowser->show();

    m_pDomTreeText->show();
    QSplitter* splitterBrowserV = new QSplitter(Qt::Vertical, parent);
    QSplitter* splitterScript = new QSplitter(parent);;
    QSplitter* splitterMainH = new QSplitter(parent);
    QSplitter* splitterTextV = new QSplitter(Qt::Vertical, parent);

    toolBarSplitter->addWidget(m_pUrlEdit);
    toolBarSplitter->addWidget(urlLoadBtn);

    m_pUrlEdit->setMinimumHeight(20);
    m_pUrlEdit->setMaximumHeight(30);

    urlLoadBtn->setMinimumSize(120, 20);
    urlLoadBtn->setMaximumSize(150, 30);

    layout->addWidget(toolBarSplitter);
    splitterBrowserV->addWidget(m_pWebViewBrowser);
    splitterScript->addWidget(executePhpBtn);
    splitterScript->addWidget(m_pScriptTextEdit);
    splitterBrowserV->addWidget(splitterScript);
    splitterMainH->addWidget(splitterBrowserV);
    splitterTextV->addWidget(m_pDomTreeText);
    splitterTextV->addWidget(m_pDataOutView);
    splitterMainH->addWidget(splitterTextV);

    layout->addWidget(splitterMainH);
    //layout->addWidget(splitterText);
    setLayout(layout);

    m_pBrowser->signalsManager()->connectPageLoaded ( boost::bind(&MyWidget::pageLoadedSlot, this, _1 ) );

    connect(m_pUrlEdit, SIGNAL(returnPressed()), this, SLOT(loadUrlSlot() ));
    connect(urlLoadBtn, SIGNAL(clicked()), this, SLOT(loadUrlSlot() ));
    connect(executePhpBtn,  SIGNAL(clicked()), this, SLOT( executePhpSlot() ));
    connect(m_pWebViewBrowser,  SIGNAL(elementSelected(CreatorWebViewUi*)), this, SLOT( webElementSelectedSlot(CreatorWebViewUi*) ));


}

MyWidget::~MyWidget()
{
    shutdownPhp();
}

void MyWidget::pageLoadedSlot( crawl::WebBrowserIF& browser )
{
//    qDebug() << m_pWebViewBrowser->url();
//    qDebug() << m_pWebViewBrowser->url().toEncoded();

//    std::string sUrl = browser.currentUri().c_str();
//    printf("ML: '%s'\n", sUrl.c_str() );

    m_pLinearDom = browser.currentLinearDom();

    if ( crawl::rmCrawlerE != m_pMiner->runMode() ) {
        m_pUrlEdit->setText( QString::fromUtf8( browser.currentUri().c_str() ) );
    }

    if ( crawl::rmDesignE == m_pMiner->runMode() || crawl::rmDebugE == m_pMiner->runMode() ) {
        m_pWebViewBrowser->setLinearDom( browser.currentLinearDom() );
        m_pDomTreeText->setFromLinearDom( browser.currentLinearDom() );
        m_pDomTreeText->moveCursor( QTextCursor::Start );
    }
}

void MyWidget::loadUrlSlot()
{
//    QByteArray ba = m_pUrlEdit->text().toAscii();

//    printf("loadUrlSlot: %s\n", ba.data() );
//    QUrl url;
//    //url.setUrl();
//    url.setEncodedUrl(ba, QUrl::StrictMode );
////    url = QUrl(m_pUrlEdit->text(), QUrl::StrictMode ) ;
//    if ( !url.isValid() ) {
//        printf("ML: Url '%s' not valid\n", url.toString().toUtf8().data() );
//    }
//    m_pWebViewBrowser->load( url );
    m_pBrowser->loadUri( m_pUrlEdit->text().toUtf8().data() );
}


void MyWidget::executePhpSlot()
{
    executePhpString( m_pScriptTextEdit->toPlainText().toUtf8().data() );
    if ( m_pMiner->linearDom() ) {
        printf("MyWidget::executePhpSlot domPos: %d\n", m_pMiner->domGetPos() );
        m_pDomTreeText->selectDomPos( m_pMiner->domGetPos() );
        QApplication::clipboard()->setText( QString::fromUtf8(m_pMiner->valueGet().c_str()) );
    }
}

void MyWidget::webElementSelectedSlot  (CreatorWebViewUi* /*pWebView*/)
{
    size_t iSelectedDomPos = 0;
    boost::shared_ptr<crawl::DomNodeIF>  pSelectedNode;
    boost::shared_ptr<LinearDomIF> pLinearDom = m_pMiner->linearDom();
    bool bOk = false;
    if ( pLinearDom ) {
       pSelectedNode = crawl::mkWebKitDomNodeQt(
                    DomNodeTypes::ELEMENT, "", m_pWebViewBrowser->selectedElement(), browser(), -1
                    );
        LinearDomIF::const_iterator it = pLinearDom->findFromRawPointer( pSelectedNode );
        if ( it != pLinearDom->end() ) {
            bOk = true;
            iSelectedDomPos = m_pLinearDom->iteratorToPos(it);
            pSelectedNode = it->node;
            //itSelectedDomPos = it;
            printf("XPos: %d\n", (int)iSelectedDomPos );
            m_pDomTreeText->selectDomPos( iSelectedDomPos );
        }
    }
//    if (!bOk) {
//        pSelectedNode = boost::shared_ptr<crawl::DomNodeIF>();
//        itSelectedDomPos = m_pLinearDom->end();
//        selectedElement = QWebElement();
//        iSelectedDomPos = 0;
//    }


//////
    static const map<string, size_t> adjustPos = map_list_of
            ("A", 2)
            ("LI", 1)
            ("P", 1)
            ("TITLE", 1)
            ;

//    if ( bOk ) {
//        size_t iPos = m_pWebViewBrowser->selectedDomPos();
//        LinearDomIF::const_iterator it = m_pWebViewBrowser->itSelectedDomPos();
//        size_t d = std::map_find( adjustPos, 0, m_pWebViewBrowser->selectedNode()->nodeName());
//        if ( d ) {
//            //        it += d;
//        }
//        if ( it != m_pLinearDom->end() ) {
//            iPos = m_pLinearDom->iteratorToPos(it);
//            printf("Pos: %d, nodeName: %s\n", (int)iPos, m_pWebViewBrowser->selectedNode()->nodeName().c_str() );
//        }
//        m_pDomTreeText->selectDomPos( iPos );
//    }
}
