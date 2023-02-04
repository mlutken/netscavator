#include "SimpleNetworkAccessManager.h"
#include <iostream>
#include <Globals.h>
#include <Configuration.h>
#include <SignalsManager.h>
#include <boost/algorithm/string.hpp>
#include <boost/date_time/posix_time/posix_time.hpp>
#include <utility>
#include <utility>

#include <dom_constants.h>

using namespace std;

namespace crawl {

SimpleNetworkAccessManager::SimpleNetworkAccessManager(
        QNetworkAccessManager* manager
        , boost::shared_ptr<SignalsManager> pSignalsManager
        , bool doLoadImages
        , bool doLoadStyleSheets
        , QObject *parent
        )
    : QNetworkAccessManager(parent)
    , m_pSignalsManager(std::move(std::move(pSignalsManager)))
    , m_doLoadImages(doLoadImages)
    , m_doLoadStyleSheets(doLoadStyleSheets)
    , m_iRequestStartCount(0)
    , m_iRequestFinishedCount(0)
    , m_iRequestStartCountTotal(0)
    , m_iRequestFinishedCountTotal(0)
    , m_lastNetworkReply(nullptr)
{
    setCache(manager->cache());
    setCookieJar(manager->cookieJar());
    setProxy(manager->proxy());
    setProxyFactory(manager->proxyFactory());
    connect(this, SIGNAL(finished(QNetworkReply*)),this, SLOT(onFinished(QNetworkReply*)));
    m_showNetworkActivity = globalConfig()->valueBoolGet("show-network-activity");
}


void SimpleNetworkAccessManager::doLoadImages  ( bool doLoad )
{
    m_doLoadImages = doLoad;
}

bool SimpleNetworkAccessManager::doLoadImagesGet  ( ) const
{
    return m_doLoadImages;
}


void SimpleNetworkAccessManager::doLoadStyleSheets  ( bool doLoad )
{
    m_doLoadStyleSheets = doLoad;
}

bool SimpleNetworkAccessManager::doLoadStyleSheetsGet  ( ) const
{
    return m_doLoadStyleSheets;
}


bool SimpleNetworkAccessManager::checkPotentialAjaxLoadCompleted( const boost::posix_time::time_duration& deltaTime ) const
{
    if ( (m_iRequestStartCount > 0) && (m_iRequestStartCount <= m_iRequestFinishedCount) ) {
        const bool ajaxCompleted = (boost::posix_time::microsec_clock::universal_time() - m_timeLastRequestFinished) > deltaTime;
        if (m_showNetworkActivity) {
            cout << "Network ajaxCompleted: " << ajaxCompleted
                 << " , deltaTime: '" << deltaTime << "'"
                 << endl;
        }
        return ajaxCompleted;
    }
    return false;
}

void SimpleNetworkAccessManager::resetPageRequestCounters	()
{
    m_iRequestStartCount	= 0;
    m_iRequestFinishedCount	= 0;
}

/** Get number of not (yet) completed page requests. */
int SimpleNetworkAccessManager::outstandingPageRequests() const
{
    int diff = m_iRequestStartCount - m_iRequestFinishedCount;
    return diff > 0 ? diff : 0;
}


QNetworkReply* SimpleNetworkAccessManager::createRequest(
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

    bool ok = m_pSignalsManager->signalOnNetProgress(nullptr, NetworkOperationType::NetworkRequestStart, url );
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
    
        m_pSignalsManager->signalOnNetProgress(nullptr, NetworkOperationType::NetworkRequestCancelled, url );
        return QNetworkAccessManager::createRequest(operation, QNetworkRequest( QUrl() ), device);
    
}

//void SimpleNetworkAccessManager::onRequestCompleted()
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

void SimpleNetworkAccessManager::onFinished(QNetworkReply* reply)
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
    m_pSignalsManager->signalOnNetProgress(nullptr, NetworkOperationType::NetworkRequestComplete, url);

}

QNetworkReply* SimpleNetworkAccessManager::lastNetworkReply() const
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

