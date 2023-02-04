#ifndef CREATOR_SIMPLE_WEBVIEW_UI_H
#define CREATOR_SIMPLE_WEBVIEW_UI_H

#include <LinearDomIF.h>
#include <BrowserViewIF.h>

class GuiGlobals;
class QProgressBar;

namespace crawl {
class SimpleWebView;

class CreatorSimpleWebViewUi : public crawl::BrowserViewIF
{
    Q_OBJECT
public:
    explicit CreatorSimpleWebViewUi(const boost::shared_ptr<Configuration>& configuration,
                                    QObject* parent = nullptr);
    ~CreatorSimpleWebViewUi() override;

public slots:

private slots:
    void    elementSelectedSlot ( crawl::SimpleWebView* pWebView );

private:
    virtual void*       do_nativeViewPtr() override;
    virtual QWidget*    do_widgetPtr    () override;

    virtual QString     do_title        () override;
    virtual void        do_forward      () override;
    virtual void        do_back         () override;
    virtual QUrl        do_url          () const override;
    void                do_setUrl       (const QUrl& url) override;
    virtual XPath                               do_selectedElementXPath () override;
    virtual boost::shared_ptr<crawl::DomNodeIF> do_selectedElement          () const override;

    SimpleWebView*  m_simpleWebView = nullptr;
//    GuiGlobals*     m_guiGlobals;

};

} // END namespace crawl

#endif // CREATOR_SIMPLE_WEBVIEW_UI_H
