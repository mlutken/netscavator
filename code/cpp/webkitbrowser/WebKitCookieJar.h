#ifndef WEBKIT_COOKIE_JAR_H
#define WEBKIT_COOKIE_JAR_H

#include <QFile>
#include <QNetworkCookie>
#include <QNetworkCookieJar>
#include <QTimer>

class WebKitCookieJar final : public QNetworkCookieJar {
    Q_OBJECT

public:
    WebKitCookieJar(QObject* parent = 0);
    virtual ~WebKitCookieJar();

    bool setCookiesFromUrl(const QList<QNetworkCookie>&, const QUrl&) final;

    void setDiskStorageEnabled(bool);

public Q_SLOTS:
    void scheduleSaveToDisk();
    void loadFromDisk();
    void reset();

private Q_SLOTS:
    void saveToDisk();

private:
    void extractRawCookies();

    QList<QByteArray> m_rawCookies;
    bool m_storageEnabled;
    QFile m_file;
    QTimer m_timer;
};

#endif // WEBKIT_COOKIE_JAR_H

