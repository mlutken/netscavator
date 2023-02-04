#include "CreatorMainWidgetUi.h"
#include "LeftPanelUi.h"

#include <QStackedLayout>
#include <QTextEdit>
#include <gui/WelcomeWidgetUi.h>
#include <gui/BrowserWidgetUi.h>
#include <gui/EditorWidgetUi.h>
#include <gui/DesignWidgetUi.h>
#include <gui/HtmlSourceWidgetUi.h>
#include <gui/HelpWidgetUi.h>


CreatorMainWidgetUi::CreatorMainWidgetUi(crawl::NetscavatorFactoryIF* netscavatorFactory,
                                         UrlQueueTableModel* urlQueueTableModel,
                                         DomSequencesTreeModel* domSequencesTreeModel,
                                         QWidget *parent)
    : QWidget(parent),
    m_netscavatorFactory  (netscavatorFactory)
{
    m_pWelcome      = new WelcomeWidgetUi   (this);
    m_pBrowser      = new BrowserWidgetUi   (netscavatorFactory, this);
    m_pEditor       = new EditorWidgetUi    (this);
    m_pDesign       = new DesignWidgetUi    (urlQueueTableModel, domSequencesTreeModel, this);
    m_pHtmlSource   = new HtmlSourceWidgetUi(this);
    m_pHelp         = new HelpWidgetUi      (this);

    //m_pCreatorWebView = new CreatorWebViewUi(this);
    //m_pCreatorWebView->setUrl( QUrl("http://sleipnerexamples.com.localhost/") );
    m_pStackedLayout = new QStackedLayout;
    m_pStackedLayout->addWidget(m_pWelcome);
    m_pStackedLayout->addWidget(m_pBrowser);
    m_pStackedLayout->addWidget(m_pEditor);
    m_pStackedLayout->addWidget(m_pDesign);
    m_pStackedLayout->addWidget(m_pHtmlSource);
    m_pStackedLayout->addWidget(m_pHelp);
    setLayout(m_pStackedLayout);
}

void CreatorMainWidgetUi::netscavatorFactorySet(crawl::NetscavatorFactoryIF* netscavatorFactory)
{
    m_netscavatorFactory = netscavatorFactory;
    if (m_pBrowser) m_pBrowser->netscavatorFactorySet(netscavatorFactory);
}

void CreatorMainWidgetUi::urlQueueTableModelSet(UrlQueueTableModel* model)
{
    m_pDesign->urlQueueTableModelSet(model);
}

void CreatorMainWidgetUi::domSequencesTreeModelSet(DomSequencesTreeModel* model)
{
    m_pDesign->domSequencesTreeModelSet(model);
}

// ---------------------
// --- PUBLIC slots: ---
// ---------------------

void CreatorMainWidgetUi::setMainViewSlot ( int view )
{
    switch (view) {
    case 1:     showWidgetSlot(0); break;
    case 2:     showWidgetSlot(1); break;
    case 3:     showWidgetSlot(2); break;
    case 4:     showWidgetSlot(3); break;
    case 5:     showWidgetSlot(4); break;
    case 6:     showWidgetSlot(5); break;
    default:    showWidgetSlot(0);
    }
}

void  CreatorMainWidgetUi::showWidgetSlot ( int index )
{
    m_pStackedLayout->setCurrentIndex(index);
}

void CreatorMainWidgetUi::showWidgetWelcomeSlot()
{
    showWidgetSlot(0);
}

void CreatorMainWidgetUi::showWidgetBrowserSlot  ()
{
    showWidgetSlot(1);
}

void CreatorMainWidgetUi::showWidgetEditorSlot   ()
{
    showWidgetSlot(2);
}

void CreatorMainWidgetUi::showWidgetDesignSlot   ()
{
    showWidgetSlot(3);
}

void CreatorMainWidgetUi::showWidgetHtmlSourceSlot()
{
    showWidgetSlot(4);
}

void CreatorMainWidgetUi::showWidgetHelpSlot     ()
{
    showWidgetSlot(5);
}

