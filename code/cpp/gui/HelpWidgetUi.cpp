#include "HelpWidgetUi.h"
#include <QLabel>
#include <QAction>

#include <QHBoxLayout>
//#include <QVBoxLayout>
//FIXME OLD QWebView #include <QtWebKitWidgets/QWebView>
#include <QTableWidget>
#include <QHeaderView>
#include <QSplitter>

#include <Globals.h>
#include <Configuration.h>

#include <GuiActionsMgr.h>

HelpWidgetUi::HelpWidgetUi(QWidget *parent) :
    QWidget(parent)
{
    GuiActionsMgr* pAMgr = crawl::g()->guiActionsMgr();
    QSplitter* splitterH = new QSplitter(Qt::Horizontal, this);

    QHBoxLayout* layout = new QHBoxLayout;
//FIXME OLD QWebView     m_pHelpBrowser = new QWebView(this);
//FIXME OLD QWebView     m_pHelpBrowser->setUrl( QUrl("http://netscavator.com/content/manual-introduction") );

    m_pHelpMenuTbl = new QTableWidget(4, 1, this);
    m_pHelpMenuTbl->verticalHeader()->hide();
    m_pHelpMenuTbl->horizontalHeader()->hide();

    QTableWidgetItem* link;
    link = new QTableWidgetItem( tr("Manual") );
    link->setWhatsThis(QString("http://netscavator.com/content/manual-introduction"));
    link->setToolTip(QString("http://netscavator.com/content/manual-introduction"));
    m_pHelpMenuTbl->setItem( 0, 0, link );

    link = new QTableWidgetItem( tr("Reference") );
    link->setWhatsThis(QString("http://netscavator.com/reference/all-function-groups"));
    link->setToolTip(QString("http://netscavator.com/reference/all-function-groups"));
    m_pHelpMenuTbl->setItem( 1, 0, link );
	
    link = new QTableWidgetItem( tr("Examples") );
    link->setWhatsThis(QString("http://netscavator.com/content/examples"));
    link->setToolTip(QString("http://netscavator.com/content/examples"));
    m_pHelpMenuTbl->setItem( 2, 0, link );

    link = new QTableWidgetItem( tr("Suggest feature") );
    link->setWhatsThis(QString("http://netscavator.com/content/feature-request"));
    link->setToolTip(QString("http://netscavator.com/content/feature-request"));
    m_pHelpMenuTbl->setItem( 3, 0, link );

    m_pHelpMenuTbl->setColumnWidth(0, 300);
    m_pHelpMenuTbl->setShowGrid(false);


    //m_pHelpMenuTbl->resizeColumnsToContents();


    splitterH->addWidget(m_pHelpMenuTbl);
//FIXME OLD QWebView     splitterH->addWidget(m_pHelpBrowser);
    layout->addWidget(splitterH);
    setLayout(layout);

    connect( m_pHelpMenuTbl, SIGNAL(itemSelectionChanged()), this, SLOT(itemSelectionChangedSlot()) );

}



void HelpWidgetUi::itemSelectionChangedSlot ()
{
    //QList<QTableWidgetItem *>	selectedItems ()
    QTableWidgetItem* pItem = m_pHelpMenuTbl->currentItem();
    printf("HelpWidgetUi::itemSelectionChangedSlot: %s\n", pItem->whatsThis().toUtf8().data() );
//FIXME OLD QWebView     m_pHelpBrowser->setUrl( QUrl(pItem->whatsThis()) );
}
