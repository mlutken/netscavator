#include "WebkitNetworkAccessManagerQt.h"
#include <iostream>
#include <Globals.h>
#include <Configuration.h>
#include <SignalsManager.h>
#include <boost/algorithm/string.hpp>
#include <boost/date_time/posix_time/posix_time.hpp>

#include <dom_constants.h>

using namespace std;

namespace crawl {

WebkitNetworkAccessManagerQt::WebkitNetworkAccessManagerQt(
        QNetworkAccessManager* manager
        , boost::shared_ptr<SignalsManager> pSignalsManager
        , bool doLoadImages
        , bool doLoadStyleSheets
        , QObject *parent
        )
    : QNetworkAccessManager(parent)
    , m_pSignalsManager(pSignalsManager)
    , m_doLoadImages(doLoadImages)
    , m_doLoadStyleSheets(doLoadStyleSheets)
    , m_iRequestStartCount(0)
    , m_iRequestFinishedCount(0)
    , m_iRequestStartCountTotal(0)
    , m_iRequestFinishedCountTotal(0)
    , m_lastNetworkReply(0)
{
    setCache(manager->cache());
    setCookieJar(manager->cookieJar());
    setProxy(manager->proxy());
    setProxyFactory(manager->proxyFactory());
    connect(this, SIGNAL(finished(QNetworkReply*)),this, SLOT(onFinished(QNetworkReply*)));
    m_showNetworkActivity = globalConfig()->valueBoolGet("show-network-activity");
}


void WebkitNetworkAccessManagerQt::doLoadImages  ( bool doLoad )
{
    m_doLoadImages = doLoad;
}

bool WebkitNetworkAccessManagerQt::doLoadImagesGet  ( ) const
{
    return m_doLoadImages;
}


void WebkitNetworkAccessManagerQt::doLoadStyleSheets  ( bool doLoad )
{
    m_doLoadStyleSheets = doLoad;
}

bool WebkitNetworkAccessManagerQt::doLoadStyleSheetsGet  ( ) const
{
    return m_doLoadStyleSheets;
}


bool WebkitNetworkAccessManagerQt::checkPotentialAjaxLoadCompleted( const boost::posix_time::time_duration& deltaTime ) const
{
    if ( (m_iRequestStartCount > 0) && (m_iRequestStartCount <= m_iRequestFinishedCount) ) {
        const bool ajaxCompleted = (boost::posix_time::microsec_clock::universal_time() - m_timeLastRequestFinished) > deltaTime;
        if (m_showNetworkActivity) {
            cerr << "Network ajaxCompleted: " << ajaxCompleted
                 << " , deltaTime: '" << deltaTime << "'"
                 << endl;
        }
        return ajaxCompleted;
    }
    return false;
}

void WebkitNetworkAccessManagerQt::resetPageRequestCounters	()
{
    m_iRequestStartCount	= 0;
    m_iRequestFinishedCount	= 0;
}

/** Get number of not (yet) completed page requests. */
int WebkitNetworkAccessManagerQt::outstandingPageRequests() const
{
    int diff = m_iRequestStartCount - m_iRequestFinishedCount;
    return diff > 0 ? diff : 0;
}


QNetworkReply* WebkitNetworkAccessManagerQt::createRequest(
    QNetworkAccessManager::Operation operation, const QNetworkRequest& request,
    QIODevice* device)
{
    // GetOperation
    bool okToLoad = true;
    const std::string url(request.url().toEncoded().data());
    if ( !m_doLoadImages ) {
        if (    boost::algorithm::contains(url, ".png") ||
                boost::algorithm::contains(url, ".gif") ||
                boost::algorithm::contains(url, ".jpg")

             )
        {
            okToLoad = false;
        }
    }
    if ( !m_doLoadStyleSheets ) {
        if ( boost::algorithm::contains(url, ".css") ) okToLoad = false;
    }

    bool ok = m_pSignalsManager->signalOnNetProgress(NULL, NetworkOperationType::NetworkRequestStart, url );
    if ( !ok) {
        okToLoad = false;
    }

    if ( okToLoad ) {
        m_iRequestStartCount++;
        m_iRequestStartCountTotal++;
        if (m_showNetworkActivity) {
            cout << "Network request started: " << m_iRequestStartCount
                 << " , url: '" << url << "'"
                 << endl;
        }
        QNetworkReply* pNetworkReply = QNetworkAccessManager::createRequest(operation, request, device);
//        connect(pNetworkReply, SIGNAL(finished()),this, SLOT(onRequestCompleted()));
        return pNetworkReply;
    }
    else {
        m_pSignalsManager->signalOnNetProgress(NULL, NetworkOperationType::NetworkRequestCancelled, url );
        return QNetworkAccessManager::createRequest(operation, QNetworkRequest( QUrl() ), device);
    }
}

//void WebkitNetworkAccessManagerQt::onRequestCompleted()
//{
//    m_iRequestFinishedCount++;
//    m_iRequestFinishedCountTotal++;
//    m_timeLastRequestFinished = boost::posix_time::microsec_clock::universal_time();


//    if ( m_iRequestStartCount <= m_iRequestFinishedCount) {
//        cout << "DBG, Network request completed. Started, Finished => "
//             << m_iRequestStartCount << " , " << m_iRequestFinishedCount
//             << "    m_timeLastRequestFinished: " << boost::posix_time::to_iso_extended_string(m_timeLastRequestFinished)
//             << endl;
//    }
//}

void WebkitNetworkAccessManagerQt::onFinished(QNetworkReply* reply)
{
    m_iRequestFinishedCount++;
    m_iRequestFinishedCountTotal++;
    m_timeLastRequestFinished = boost::posix_time::microsec_clock::universal_time();
    m_lastNetworkReply = reply;

    const std::string url(reply->url().toEncoded().data());

    if (m_showNetworkActivity) {
        cout << "Network request finished: " << m_iRequestFinishedCount
             << " , url: '" << url << "'"
             << endl;
    }
    m_pSignalsManager->signalOnNetProgress(NULL, NetworkOperationType::NetworkRequestComplete, url);

}

int WebkitNetworkAccessManagerQt::requestFinishedCount() const
{
    return m_iRequestFinishedCount;
}

int WebkitNetworkAccessManagerQt::requestStartCount() const
{
    return m_iRequestStartCount;
}

QNetworkReply* WebkitNetworkAccessManagerQt::lastNetworkReply() const
{
    return m_lastNetworkReply;
}



} // END namespace crawl

// ----------------------------------------------------
// ----------------------------------------------------

//        //const Qt::CaseSensitivity = Qt::CaseInsensitive;
//        const Qt::CaseSensitivity = Qt::CaseSensitive;
//        const QString url = request.url().toEncoded();
//        if (
//                url.endsWith( ".png", Qt::CaseInsensitive ) ||
//                url.endsWith( ".gif", Qt::CaseInsensitive ) ||
//                url.endsWith( ".jpg", Qt::CaseInsensitive )
//            )
//        {
//            okToLoad = false;
//        }

