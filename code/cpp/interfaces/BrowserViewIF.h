#pragma once

#include <QUrl>
#include <QObject>
#include <DomNodeIF.h>
#include <LinearDomIF.h>
#include <htmlparser/html/XPath.h>

class QWidget;

namespace crawl {

class Configuration;

/// Embed for example Chrome browser: QX11EmbedContainer
/// QWidget *QWidget::createWindowContainer(QWindow *window, QWidget *parent = nullptr, Qt::WindowFlags flags = Qt::WindowFlags())
///

class BrowserViewIF : public QObject
{
    Q_OBJECT
public:
    explicit BrowserViewIF(const boost::shared_ptr<Configuration>& configuration,
                           QObject* parent = nullptr);
    ~BrowserViewIF() = default;

    /// TODO: Get rid of this again! We need it in the transition phase!
    void*           nativeViewPtr ()            { return do_nativeViewPtr();    }
    QWidget*        widgetPtr     ()            { return do_widgetPtr();        }

    boost::shared_ptr<Configuration>    configuration() const;
    void                                configurationSet(const boost::shared_ptr<Configuration>& configuration);

    QString         title           ()                  { return do_title();    }
    void            forward         ()                  { do_forward();         }
    void            back            ()                  { do_back();            }
    QUrl            url             () const            { return do_url();      }
    void            setUrl          (const QUrl& url)   { do_setUrl(url);       }
    XPath                               selectedElementXPath    () { return do_selectedElementXPath();  }
    boost::shared_ptr<DomNodeIF>        selectedElement         () const { return do_selectedElement();     }

    void            emitDomPosSelectedSig       (const QString& xpath, const QString& innerText);
    void            emitLinkClicked             (const QUrl& url);
    void            emitBrowserViewPageLoaded   (bool ok);
    WebBrowserIF*   owningBrowser               () const;
    void            owningBrowserSet            (WebBrowserIF* owningBrowser);

signals:
    void            domPosSelectedSig           (const QString& xpath, const QString& innerText);
    void            linkClicked                 (crawl::BrowserViewIF* browserView, const QUrl& url);
    void            elementSelected             (crawl::BrowserViewIF* browserView);
    void            browserViewPageLoadedSignal (crawl::BrowserViewIF* browserView, bool ok);



private:
    virtual void*                           do_nativeViewPtr  ()            = 0;
    virtual QWidget*                        do_widgetPtr()                  = 0;
    virtual QString                         do_title    ()                  = 0;
    virtual void                            do_forward  ()                  = 0;
    virtual void                            do_back     ()                  = 0;
    virtual QUrl                            do_url      () const            = 0;
    virtual void                            do_setUrl   (const QUrl& url)   = 0;
    virtual XPath                           do_selectedElementXPath ()  = 0;
    virtual boost::shared_ptr<DomNodeIF>    do_selectedElement          () const = 0;

    boost::shared_ptr<Configuration>    m_configuration;
    WebBrowserIF*                       m_owningBrowser = nullptr;
};

} // END namespace crawl
