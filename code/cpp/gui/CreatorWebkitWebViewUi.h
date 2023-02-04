#pragma once

//FIXME OLD QWebView #include <QWebView>
//FIXME OLD QWebView #include <QWebElement>
#include <LinearDomIF.h>
#include <BrowserViewIF.h>

class GuiGlobals;
class QProgressBar;
class WebkitWebView;

class CreatorWebkitWebViewUi : public crawl::BrowserViewIF
{
    Q_OBJECT
public:
    explicit CreatorWebkitWebViewUi(const boost::shared_ptr<crawl::Configuration>& configuration,
                                    QObject* parent = nullptr);
    ~CreatorWebkitWebViewUi() override;
    /// TODO: Get rid of this function and use selectedElement(/NativePtr) instead
//FIXME OLD QWebView     QWebElement     selectedElement () const { return m_selectedElement; }

public slots:

private slots:
    void    loadFinishedSlot    ( bool ok );
    void    elementSelectedSlot ( WebkitWebView* pWebView );
    void    domPosSelectedSlot  (const QString& xpath, const QString& innerText);

private:
    virtual void*           do_nativeViewPtr() override;
    virtual QWidget*        do_widgetPtr    () override;

    virtual QString         do_title        () override;
    virtual void            do_forward      () override;
    virtual void            do_back         () override;
    virtual QUrl            do_url          () const override;
    void                    do_setUrl       (const QUrl& url) override;
    virtual crawl::XPath                        do_selectedElementXPath () override;
    virtual boost::shared_ptr<crawl::DomNodeIF> do_selectedElement          () const override;

    WebkitWebView*  m_webkitWebView = nullptr;
    GuiGlobals*     m_guiGlobals;
};

