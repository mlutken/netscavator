
#include "WebWidget.h"
using namespace std;



WebWidget::WebWidget(QWidget *parent)
    : QWidget(parent)
{
    QVBoxLayout* layout = new QVBoxLayout;

    m_pWebViewBrowser = new QWebView(parent);
    m_pWebViewBrowser->load( QUrl("http://www.google.dk") );
    m_pWebViewBrowser->show();

    layout->addWidget(m_pWebViewBrowser);
    setLayout(layout);

}

WebWidget::~WebWidget()
{
}

