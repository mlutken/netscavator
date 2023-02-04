#ifndef WEBKIT_WEBVIEW_H
#define WEBKIT_WEBVIEW_H

#include <QWidget>
#include <QtWebEngineWidgets>
//FIXME OLD QWebView #include <QWebView>
//FIXME OLD QWebView #include <QWebElement>
//FIXME OLD QWebView #include <QtWebKit/QtWebKit>
//FIXME OLD QWebView #include <QtWebKitWidgets/QWebView>
#include <LinearDomIF.h>
#include <BrowserViewIF.h>

class GuiGlobals;
class QProgressBar;

class WebkitWebView : public QWebEngineView
{
    Q_OBJECT
public:
    explicit WebkitWebView(QWidget *parent = nullptr);
    ~WebkitWebView() override;
//FIXME OLD QWebView     QWebElement     selectedElement () const;

signals:
    void    elementSelectedSig  ( WebkitWebView* pWebView );
    void    pageLoadedSig       ( WebkitWebView* pWebView, bool ok );

public slots:

protected:
    void    mousePressEvent         ( QMouseEvent* event ) override;
    void    wheelEvent              ( QWheelEvent* event ) override;
    void    keyPressEvent           ( QKeyEvent * event ) override;


private slots:
    void    loadFinishedSlot ( bool ok );


private:
//FIXME OLD QWebView     QWebElement     m_selectedElement;
    bool            m_bPageIsLoading;
    GuiGlobals*     m_guiGlobals;
    QProgressBar*   m_pageLoadProgressBar;
};

#endif // WEBKIT_WEBVIEW_H
