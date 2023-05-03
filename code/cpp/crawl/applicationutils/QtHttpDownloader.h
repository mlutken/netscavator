#ifndef CRAWL_QTHTTPDOWNLOADER_H
#define CRAWL_QTHTTPDOWNLOADER_H

#include <QtCore>
#include <QtNetwork>
#include <cstdio>
#include <functional>


class QSslError;



namespace crawl {


/**
  HTTP downloader with automatic support for redirect.
  Only one file is supported currently.
 */
class QtHttpDownloader : public QObject {
    Q_OBJECT

public:
    using CompleteCallbackT = std::function< void (QNetworkReply*, const QUrl&, bool ok)> ;
    using CompleteByteArrayCallbackT = std::function< void (const QByteArray&, const QUrl&, bool ok)>;
    using CompleteByteArrayCallbackMoveT = std::function< void (QByteArray&&, const QUrl&, bool ok)>;

    static bool isGzCompressed  (const QString& filename);
    static QString saveFileName (const QUrl& url);
    static QString baseName     (const QUrl& url);
    static bool saveToDisk      (const QString& filename, QIODevice* data);

    QtHttpDownloader            ();
    ~QtHttpDownloader           () override;
    void download               (const QUrl& url);
    void download               (const QUrl& url, const CompleteCallbackT& completeCallback);
    void downloadToByteArray    (const QUrl& url, const CompleteByteArrayCallbackT& completeCallback);
    void downloadToByteArrayMove(const QUrl& url, const CompleteByteArrayCallbackMoveT& completeCallback);
    void setCompleteCallback    (const CompleteCallbackT& completeCallback);


signals:
    void complete               (QNetworkReply*, const QUrl&);
    void failed                 (QNetworkReply*, const QUrl&);

public slots:
    void mainTester();

private slots:
    void downloadFinished       (QNetworkReply* reply);
    void sslErrors              (const QList<QSslError>& errors);

private:
    void handleComplete         (QNetworkReply* reply);
    void doDownload             (const QUrl& url);
    bool handleHttpRedirect     (QNetworkReply* reply);
    bool isHttpRedirect         (QNetworkReply* reply) const;

    QUrl                        m_originalUrl;
    QNetworkAccessManager       m_manager;
    QVector<QNetworkReply *>    m_currentDownloads;
    CompleteCallbackT           m_completeCallback;
    CompleteByteArrayCallbackT  m_completeByteArrayCallback;
    CompleteByteArrayCallbackMoveT  m_completeByteArrayCallbackMove;
    QByteArray                  m_replyData;
    uint32_t                    m_maxAllowedRedirects   = 10;
    uint32_t                    m_redirectCounter       = 0;
};

} // namespace crawl

#endif // CRAWL_QTHTTPDOWNLOADER_H
