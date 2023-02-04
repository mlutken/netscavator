#include "WebKitCookieJar.h"

#include <QStandardPaths>
#include <QDir>
#include <QTextStream>

WebKitCookieJar::WebKitCookieJar(QObject* parent)
    : QNetworkCookieJar(parent)
    , m_storageEnabled(false)
{
    // We use a timer for the real disk write to avoid multiple IO
    // syscalls in sequence (when loading pages which set multiple cookies).
    m_timer.setInterval(10000);
    m_timer.setSingleShot(true);
    connect(&m_timer, SIGNAL(timeout()), this, SLOT(saveToDisk()));

#ifndef QT_NO_DESKTOPSERVICES
    QString path = QStandardPaths::writableLocation(QStandardPaths::CacheLocation);
#else
    QString path = QDir::homePath() + "/.QtTestBrowser";
#endif

    QDir().mkpath(path);
    m_file.setFileName(path + "/cookieJar");
}

WebKitCookieJar::~WebKitCookieJar()
{
    if (m_storageEnabled) {
        extractRawCookies();
        saveToDisk();
    }
}

bool WebKitCookieJar::setCookiesFromUrl(const QList<QNetworkCookie>& cookieList, const QUrl& url)
{
    bool status = QNetworkCookieJar::setCookiesFromUrl(cookieList, url);
    if (status && m_storageEnabled)
        scheduleSaveToDisk();
    return status;
}

void WebKitCookieJar::setDiskStorageEnabled(bool enabled)
{
    m_storageEnabled = enabled;

    if (enabled && allCookies().isEmpty())
        loadFromDisk();

    // When disabling, save current cookies.
    if (!enabled && !allCookies().isEmpty())
        scheduleSaveToDisk();
}

void WebKitCookieJar::scheduleSaveToDisk()
{
    // We extract the raw cookies here because the user may
    // enable/disable/clear cookies while the timer is running.
    extractRawCookies();
    m_timer.start();
}

void WebKitCookieJar::extractRawCookies()
{
    QList<QNetworkCookie> cookies = allCookies();
    m_rawCookies.clear();

    foreach (const QNetworkCookie &cookie, cookies) {
        if (!cookie.isSessionCookie())
            m_rawCookies.append(cookie.toRawForm());
    }
}

void WebKitCookieJar::saveToDisk()
{
    m_timer.stop();

    if (m_file.open(QIODevice::WriteOnly | QIODevice::Text)) {
        QTextStream out(&m_file);
        foreach (const QByteArray &cookie, m_rawCookies)
            out << cookie + "\n";
        m_file.close();
    } else
        qWarning("IO error handling cookiejar file");
}

void WebKitCookieJar::loadFromDisk()
{
    if (!m_file.exists())
        return;

    QList<QNetworkCookie> cookies;

    if (m_file.open(QIODevice::ReadOnly | QIODevice::Text)) {
        QTextStream in(&m_file);
        while (!in.atEnd())
            cookies.append(QNetworkCookie::parseCookies(in.readLine().toUtf8()));
        m_file.close();
    } else
        qWarning("IO error handling cookiejar file");

    setAllCookies(cookies);
}

void WebKitCookieJar::reset()
{
    setAllCookies(QList<QNetworkCookie>());
    if (m_storageEnabled)
        scheduleSaveToDisk();
}
