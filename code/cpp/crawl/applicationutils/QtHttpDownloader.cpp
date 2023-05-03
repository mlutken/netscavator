#include <iostream>
#include <QFileInfo>
#include "qt_compression.h"
#include "QtHttpDownloader.h"


using namespace std;

namespace crawl {


bool QtHttpDownloader::isGzCompressed(const QString& filename)
{
    return QFileInfo(filename).suffix() == "gz";
}

QString QtHttpDownloader::saveFileName(const QUrl &url)
{
    QString path = url.path();
    QString basename = QFileInfo(path).fileName();

    if (basename.isEmpty())
        basename = "download";

    if (QFile::exists(basename)) {
        // already exists, don't overwrite
        int i = 0;
        basename += '.';
        while (QFile::exists(basename + QString::number(i)))
            ++i;

        basename += QString::number(i);
    }

    return basename;
}

QString QtHttpDownloader::baseName(const QUrl& url)
{
    QString path = url.path();
    return QFileInfo(path).fileName();
}

bool QtHttpDownloader::saveToDisk(const QString& filename, QIODevice* data)
{
    QFile file(filename);
    if (!file.open(QIODevice::WriteOnly)) {
        fprintf(stderr, "Could not open %s for writing: %s\n",
                qPrintable(filename),
                qPrintable(file.errorString()));
        return false;
    }

    file.write(data->readAll());
    file.close();

    return true;
}


QtHttpDownloader::QtHttpDownloader()
{
    connect(&m_manager, &QNetworkAccessManager::finished, this, &QtHttpDownloader::downloadFinished);
}

QtHttpDownloader::~QtHttpDownloader()
{
    // Cleanup in case exeptions are thrown in callbacks
    for ( auto reply : m_currentDownloads) {
        reply->deleteLater();
    }
}

void QtHttpDownloader::download(const QUrl& url)
{
    m_originalUrl = url;
    m_redirectCounter = 0;
    doDownload(url);
}

void QtHttpDownloader::download(const QUrl& url, const QtHttpDownloader::CompleteCallbackT& completeCallback)
{
    m_originalUrl = url;
    m_completeByteArrayCallbackMove = CompleteByteArrayCallbackMoveT();
    m_completeByteArrayCallback = CompleteByteArrayCallbackT();
    m_completeCallback = completeCallback;
    m_redirectCounter = 0;
    doDownload(url);
}

void QtHttpDownloader::downloadToByteArray(const QUrl& url, const QtHttpDownloader::CompleteByteArrayCallbackT& completeCallback)
{
    m_originalUrl = url;
    m_completeByteArrayCallbackMove = CompleteByteArrayCallbackMoveT();
    m_completeByteArrayCallback = completeCallback;
    m_completeCallback = CompleteCallbackT();
    m_redirectCounter = 0;
    doDownload(url);
}

void QtHttpDownloader::downloadToByteArrayMove(const QUrl& url, const QtHttpDownloader::CompleteByteArrayCallbackMoveT& completeCallback)
{
    m_originalUrl = url;
    m_completeByteArrayCallbackMove = completeCallback;
    m_completeByteArrayCallback = CompleteByteArrayCallbackT();
    m_completeCallback = CompleteCallbackT();
    m_redirectCounter = 0;
    doDownload(url);
}

void QtHttpDownloader::setCompleteCallback(const CompleteCallbackT& completeCallback)
{
    m_completeCallback = completeCallback;
}



void QtHttpDownloader::mainTester()
{
    QStringList args = QCoreApplication::instance()->arguments();
    args.takeFirst();           // skip the first argument, which is the program's name
    if (args.isEmpty()) {
        printf("Qt Download example - downloads all URLs in parallel\n"
               "Usage: download url1 [url2... urlN]\n"
               "\n"
               "Downloads the URLs passed in the command-line to the local directory\n"
               "If the target file already exists, a .0, .1, .2, etc. is appended to\n"
               "differentiate.\n");
        QCoreApplication::instance()->quit();
        return;
    }

    for (const QString &arg : qAsConst(args)) {
        QUrl url = QUrl::fromEncoded(arg.toLocal8Bit());
        doDownload(url);
    }
}

void QtHttpDownloader::downloadFinished(QNetworkReply* reply)
{
    const QUrl url = reply->url();
    if (reply->error()) {
        emit failed(reply, url);
        fprintf(stderr, "Download of %s failed: %s\n",
                url.toEncoded().constData(),
                qPrintable(reply->errorString()));
        handleComplete(reply);
    }
    else {
        if (handleHttpRedirect(reply)) {
            fputs("Request was redirected.\n", stderr);
        } else {
            if (m_redirectCounter > m_maxAllowedRedirects) {
                emit failed(reply, url);
                fprintf(stderr, "Download of %s failed (too many redirects): %s\n",
                        url.toEncoded().constData(),
                        qPrintable(reply->errorString()));
                handleComplete(reply);
            }
            else {
                handleComplete(reply);
            }
        }
    }
    m_currentDownloads.removeAll(reply);
    reply->deleteLater();
}

void QtHttpDownloader::sslErrors(const QList<QSslError> &sslErrors)
{
#if QT_CONFIG(ssl)
    for (const QSslError &error : sslErrors)
        fprintf(stderr, "SSL error: %s\n", qPrintable(error.errorString()));
#else
    Q_UNUSED(sslErrors);
#endif
}

void QtHttpDownloader::handleComplete(QNetworkReply* reply)
{
    const QUrl url = reply->url();
    emit complete(reply, url);
    if (m_completeByteArrayCallbackMove) {
        if (isGzCompressed(baseName(url))) {
            m_replyData = crawl::gUncompress(reply->readAll());
        }
        else {
            m_replyData = reply->readAll();
        }
        m_completeByteArrayCallbackMove(std::move(m_replyData), url, true);
    }
    else if (m_completeByteArrayCallback) {
        if (isGzCompressed(baseName(url))) {
            m_replyData = crawl::gUncompress(reply->readAll());
        }
        else {
            m_replyData = reply->readAll();
        }
        m_completeByteArrayCallback(m_replyData, url, true);
    }
    else if (m_completeCallback) {
        m_completeCallback(reply, url, true);
    }
}

void QtHttpDownloader::doDownload(const QUrl &url)
{
    QNetworkRequest request(url);
    request.setAttribute(QNetworkRequest::RedirectPolicyAttribute, QNetworkRequest::ManualRedirectPolicy);
    QNetworkReply *reply = m_manager.get(request);

#if QT_CONFIG(ssl)
    connect(reply, SIGNAL(sslErrors(QList<QSslError>)),
            SLOT(sslErrors(QList<QSslError>)));
#endif

    m_currentDownloads.append(reply);
}

bool QtHttpDownloader::handleHttpRedirect(QNetworkReply* reply)
{
    if (isHttpRedirect(reply)) {
        ++m_redirectCounter;
        if (m_redirectCounter > m_maxAllowedRedirects) {
            return false;
        }
        QUrl redirectUrl = reply->attribute(QNetworkRequest::RedirectionTargetAttribute).toUrl();
        redirectUrl = m_originalUrl.resolved(redirectUrl); // In case redirect url is relative or has no scheme or authority
        cout << "Note: Redirecting to URL [" << m_redirectCounter << " times redirected] : '" << redirectUrl.toString().toLocal8Bit().data() << "'" << endl;
        doDownload(redirectUrl);
        return true;
    }

    return false;
}

bool QtHttpDownloader::isHttpRedirect(QNetworkReply *reply) const
{
    int statusCode = reply->attribute(QNetworkRequest::HttpStatusCodeAttribute).toInt();
    return statusCode == 301 || statusCode == 302 || statusCode == 303
            || statusCode == 305 || statusCode == 307 || statusCode == 308;
}



} // namespace crawl

