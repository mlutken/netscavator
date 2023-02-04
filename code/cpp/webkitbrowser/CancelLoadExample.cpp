#include <QApplication>
#include <QUrl>

//FIXME OLD QWebView #include <QtWebKit/QWebPage>
//FIXME OLD QWebView #include <QtWebKit/QWebFrame>

#include <QtNetwork/QNetworkAccessManager>
#include <QtNetwork/QNetworkRequest>
#include <QtNetwork/QNetworkReply>
#include <QDebug>

#if 0

static const auto webChannelInitialize = QStringLiteral (R"<<<(
            new QWebChannel(qt.webChannelTransport, function(channel)
            {
                window.webChannelBridge = channel.objects.webChannelBridge;
                webChannelBridge.browserToCpp('Hello from web page');
                //PrintLog(" done, now theQtObj=" + theQtObj.toString());
            });
            window.webChannelBridge.browserToCpp('Test call from web page again!');
    )<<<");

m_javascriptInject = "";
//    m_javascriptInject.append(crawl::readResourceFile(":/jquery.min.js"));
//    m_javascriptInject.append("\nvar qt = { 'jQuery': jQuery.noConflict(true) };");
m_javascriptInject.append(crawl::readResourceFile(":/qtwebchannel/qwebchannel.js"));
//    m_javascriptInject.append(webChannelInitialize);
m_javascriptInject.append(QStringLiteral( R"<<<(
        new QWebChannel(qt.webChannelTransport, function(channel)
        {
            window.webChannelBridge = channel.objects.webChannelBridge;
            webChannelBridge.browserToCpp('Hello from web page');
            //PrintLog(" done, now theQtObj=" + theQtObj.toString());
        });
        window.webChannelBridge.browserToCpp('Test call from web page again!');
)<<<" )) ;


#endif


class NAM : public QNetworkAccessManager {

    Q_OBJECT

protected:

    virtual QNetworkReply * createRequest(Operation op,
                                          const QNetworkRequest & req,
                                          QIODevice * outgoingData = 0) {

        if (req.url().path().endsWith("css")) {
            qDebug() << "skipping " << req.url();
            return QNetworkAccessManager::createRequest(QNetworkAccessManager::GetOperation,
                                                        QNetworkRequest(QUrl()));
        } else {
            return QNetworkAccessManager::createRequest(op, req, outgoingData);
        }
    }
};


int main(int argc, char *argv[])
{
    QApplication app(argc, argv);
    QWebPage page;
    NAM nam;

    page.setNetworkAccessManager(&nam);
    page.mainFrame()->load(QUrl("http://google.com"));

    app.exec();
}

#include "main.moc"
