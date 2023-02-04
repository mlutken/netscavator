#pragma once

#include <boost/shared_ptr.hpp>
#include <QWidget>

class QStackedLayout;

class WelcomeWidgetUi;
class BrowserWidgetUi;
class EditorWidgetUi;
class DesignWidgetUi;
class HtmlSourceWidgetUi;
class HelpWidgetUi;
class UrlQueueTableModel;
class DomSequencesTreeModel;

namespace crawl {
class NetscavatorFactoryIF;
class DomSearchMgr;
}


class CreatorMainWidgetUi : public QWidget
{
    Q_OBJECT
public:
    explicit    CreatorMainWidgetUi    (crawl::NetscavatorFactoryIF* netscavatorFactory,
                                        UrlQueueTableModel* urlQueueTableModel,
                                        DomSequencesTreeModel* domSequencesTreeModel,
                                        QWidget *parent = nullptr);
    void        netscavatorFactorySet  (crawl::NetscavatorFactoryIF* netscavatorFactory);

    void        urlQueueTableModelSet   (UrlQueueTableModel* model);
    void        domSequencesTreeModelSet(DomSequencesTreeModel* model);

    // --- PUBLIC: Gui members ---
    WelcomeWidgetUi*    welcome     () const    { return m_pWelcome;    }
    BrowserWidgetUi*    browserWidgetUi     () const    { return m_pBrowser;    }
    EditorWidgetUi*     editor      () const    { return m_pEditor;     }
    DesignWidgetUi*     design      () const    { return m_pDesign;     }
    HtmlSourceWidgetUi* htmlSource  () const    { return m_pHtmlSource; }
    HelpWidgetUi*       help        () const    { return m_pHelp;       }

//signals:
    
public slots:
    void        setMainViewSlot         ( int view );
    void        showWidgetSlot          ( int index );
    void        showWidgetWelcomeSlot   ();
    void        showWidgetBrowserSlot   ();
    void        showWidgetEditorSlot    ();
    void        showWidgetDesignSlot    ();
    void        showWidgetHtmlSourceSlot();
    void        showWidgetHelpSlot      ();


private:
    // --- PRIVATE: Data ---
    crawl::NetscavatorFactoryIF*    m_netscavatorFactory;   // Owned by the "parent" main function
    QStackedLayout*     m_pStackedLayout;
    WelcomeWidgetUi*    m_pWelcome;
    BrowserWidgetUi*    m_pBrowser;
    EditorWidgetUi*     m_pEditor;
    DesignWidgetUi*     m_pDesign;
    HtmlSourceWidgetUi* m_pHtmlSource;
    HelpWidgetUi*       m_pHelp;
};
