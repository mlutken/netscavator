#ifndef WEBKIT_WEBVIEW_H
#define WEBKIT_WEBVIEW_H

#include <QWidget>
#include <QtWebEngineWidgets>
#include <LinearDomIF.h>
#include <BrowserViewIF.h>

class GuiGlobals;
class QProgressBar;

// https://www.qt.io/blog/qt-webengine-in-qt-6
// https://doc.qt.io/qt-6/qtwebenginewidgets-module.html
// https://stackoverflow.com/questions/57011407/qt-event-propagation-in-qwebengineview

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
