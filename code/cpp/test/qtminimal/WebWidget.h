#ifndef _WEB_WIDGET_H_
#define _WEB_WIDGET_H_

#include <QFont>
#include <QGridLayout>
#include <QPushButton>
#include <QWidget>
#include <QtWebKit>
#include <QSplitter>
#include <QLineEdit>

class ScriptMiner;

class WebWidget : public QWidget
{
    Q_OBJECT

public:
    WebWidget(QWidget *parent = 0);
    ~WebWidget();



public slots:


private:
    // --- DATA ---
    QWebView*             m_pWebViewBrowser;
};


#endif //_WEB_WIDGET_H_


