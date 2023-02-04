#ifndef CRAWL_SIMPLE_NETWORK_ACCESS_MANAGER_H
#define CRAWL_SIMPLE_NETWORK_ACCESS_MANAGER_H

#include <boost/shared_ptr.hpp>
#include <boost/function.hpp>
#include <boost/date_time/posix_time/posix_time_types.hpp>
#include <QtNetwork>

class SignalsManager;

// bool Crawler::okToLoadUrl (std::string const& sUrl)

namespace crawl {


// QNetworkReply::ContentNotFoundError

class SimpleNetworkAccessManager : public QNetworkAccessManager
{
    Q_OBJECT

public:
    typedef boost::function< bool ( std::string const& ) >	OkToLoadUrlFunT;


//    SimpleNetworkAccessManager(QNetworkAccessManager *manager, const OkToLoadUrlFunT& okToLoadUrlFun, QObject *parent);
    SimpleNetworkAccessManager(
              QNetworkAccessManager* manager
            , boost::shared_ptr<SignalsManager> pSignalsManager
            , bool doLoadImages
            , bool doLoadStyleSheets
            , QObject* parent
            );

    void    doLoadImages					( bool doLoad );
    bool    doLoadImagesGet					() const;

    void    doLoadStyleSheets				( bool doLoad );
    bool    doLoadStyleSheetsGet			() const;
    bool	checkPotentialAjaxLoadCompleted	( const boost::posix_time::time_duration& deltaTime ) const;
    void	resetPageRequestCounters		();
    int     outstandingPageRequests         () const;

    virtual QNetworkReply* createRequest ( QNetworkAccessManager::Operation operation, const QNetworkRequest &request, QIODevice *device);

    QNetworkReply* lastNetworkReply() const;

private slots:
//    void     onRequestCompleted() ;
    void     onFinished(QNetworkReply* reply) ;

private:


    boost::shared_ptr<SignalsManager>   m_pSignalsManager;
    OkToLoadUrlFunT                     m_okLoadUrlFun;
    bool                                m_doLoadImages;
    bool                                m_doLoadStyleSheets;
    int                                 m_iRequestStartCount;
    int                                 m_iRequestFinishedCount;
    int                                 m_iRequestStartCountTotal;
    int                                 m_iRequestFinishedCountTotal;
    boost::posix_time::ptime			m_timeLastRequestFinished;
    QNetworkReply*                      m_lastNetworkReply;
    bool                                m_showNetworkActivity = false;
};

} // END namespace crawl

#endif // CRAWL_SIMPLE_NETWORK_ACCESS_MANAGER_H
