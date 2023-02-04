#ifndef SIMPLE_WEBVIEW_H
#define SIMPLE_WEBVIEW_H

#include <QUrl>
#include <QWidget>
#include <LinearDomIF.h>
#include <BrowserViewIF.h>

//class GuiGlobals;
class QTextBrowser;
class QTextEdit;
namespace crawl {

class SimpleWebView : public QWidget
{
    Q_OBJECT
public:
    explicit SimpleWebView(const boost::shared_ptr<crawl::Configuration>& configuration,
            crawl::BrowserViewIF* browserView,
            QWidget *parent = nullptr);
    ~SimpleWebView() override;

    QString         viewMode        () const;
    void            htmlSet         (const QString& html);

    QString         title           () const;
    void            setZoomFactor   (float fac);
    void            forward         ();
    void            back            ();

signals:
    void    elementSelectedSig  ( SimpleWebView* pWebView );

private slots:
    void    linkedClickedSlot   (const QUrl& url);
    void    sourceChangedSlot   (const QUrl &src);

private:
    void                    initWithTextEdit    ();
    void                    initWithTextBrowser ();

    boost::shared_ptr<Configuration> m_configuration;
    crawl::BrowserViewIF*            m_owningBrowserView = nullptr;
    QTextBrowser*                    m_textBrowser = nullptr; // Depends on configuration
    QTextEdit*                       m_webView;
};

} // END namespace crawl

#endif // SIMPLE_WEBVIEW_H
