#include <stdio.h>
#include <boost/thread.hpp>
#include <boost/algorithm/string.hpp>

#include <nsIChannel.h>
#include <nsISocketTransport.h>
#include <nsIDOMWindow.h>
#include <nsNetError.h>

#include <nsIURI.h>
#include <WebBrowserIF.h>
#include "DefaultHttpActivityObserver.h"




namespace b = boost;

DefaultHttpActivityObserver::DefaultHttpActivityObserver (
    crawl::WebBrowserIF* pMozBrowser
)	:
    m_pMozBrowser( pMozBrowser )
{
    ResetCounters();
}

DefaultHttpActivityObserver::~DefaultHttpActivityObserver()
{
}

void DefaultHttpActivityObserver::ResetCounters()
{
    m_iCount_REQUEST_HEADER        = 0;
    m_iCount_REQUEST_BODY_SENT     = 0;
    m_iCount_RESPONSE_START        = 0;
    m_iCount_RESPONSE_HEADER       = 0;
    m_iCount_RESPONSE_COMPLETE     = 0;
    m_iCount_TRANSACTION_CLOSE     = 0;

    m_iCount_RESOLVING              = 0;
    m_iCount_CONNECTING_TO          = 0;
    m_iCount_CONNECTED_TO           = 0;
    m_iCount_SENDING_TO             = 0;
    m_iCount_WAITING_FOR            = 0;
    m_iCount_RECEIVING_FROM         = 0;
    m_iCount_ACTIVITY_ANY           = 0;
}


NS_IMPL_ISUPPORTS2 ( DefaultHttpActivityObserver,
                     nsIHttpActivityObserver,
                     nsISupportsWeakReference )


/* void observeActivity (in nsISupports aHttpChannel, in PRUint32 aActivityType, in PRUint32 aActivitySubtype, in PRTime aTimestamp, in PRUint64 aExtraSizeData, in ACString aExtraStringData); */
NS_IMETHODIMP DefaultHttpActivityObserver::ObserveActivity(
      nsISupports *aHttpChannel
    , PRUint32 aActivityType
    , PRUint32 aActivitySubtype
    , PRTime aTimestamp
    , PRUint64 aExtraSizeData
    , const nsACString & aExtraStringData )
{
    ++m_iCount_ACTIVITY_ANY;
    m_pMozBrowser->activityCounterSet(m_iCount_ACTIVITY_ANY);

    std::stringstream idStream;
    idStream << boost::this_thread::get_id();
    //printf("ML: Activity any: %d,  thread_id: '%s'\n", m_iCount_ACTIVITY_ANY, idStream.str().c_str() );

    if ( ACTIVITY_TYPE_HTTP_TRANSACTION == aActivityType ) {
        switch (aActivitySubtype) {
        case ACTIVITY_SUBTYPE_REQUEST_HEADER    : m_iCount_REQUEST_HEADER++    ; break;
        case ACTIVITY_SUBTYPE_REQUEST_BODY_SENT : m_iCount_REQUEST_BODY_SENT++ ; break;
        case ACTIVITY_SUBTYPE_RESPONSE_START    : m_iCount_RESPONSE_START++    ; break;
        case ACTIVITY_SUBTYPE_RESPONSE_HEADER   : m_iCount_RESPONSE_HEADER++   ; break;
        case ACTIVITY_SUBTYPE_RESPONSE_COMPLETE : m_iCount_RESPONSE_COMPLETE++ ; break;
        case ACTIVITY_SUBTYPE_TRANSACTION_CLOSE : m_iCount_TRANSACTION_CLOSE++ ; break;
//        default:

           // printf("ML: Error aActivitySubtype\n");
        }
        //printf("ML: DefaultHttpActivityObserver::ObserveActivity %d , %X \n", aActivitySubtype, aActivitySubtype  );
//        printf("ML: %d, %d, %d, %d, %d, %d  : %d"       , m_iCount_REQUEST_HEADER
//                          b                              , m_iCount_REQUEST_BODY_SENT
//                                                        , m_iCount_RESPONSE_START
//                                                        , m_iCount_RESPONSE_HEADER
//                                                        , m_iCount_RESPONSE_COMPLETE
//                                                        , m_iCount_TRANSACTION_CLOSE
//                                                        , m_iCount_REQUEST_HEADER - m_iCount_TRANSACTION_CLOSE
//                                                        );
    }
    else {
        //printf("ML: DefaultHttpActivityObserver::ObserveActivity %d , %d", aActivityType, (unsigned int)aActivitySubtype );
        switch (aActivitySubtype) {
        case nsISocketTransport::STATUS_RESOLVING       : m_iCount_RESOLVING++      ; break;
        case nsISocketTransport::STATUS_CONNECTING_TO   : m_iCount_CONNECTING_TO++  ; break;
        case nsISocketTransport::STATUS_CONNECTED_TO    : m_iCount_CONNECTED_TO++   ; break;
        case nsISocketTransport::STATUS_SENDING_TO      : m_iCount_SENDING_TO++     ; break;
        case nsISocketTransport::STATUS_WAITING_FOR     : m_iCount_WAITING_FOR++    ; break;
        case nsISocketTransport::STATUS_RECEIVING_FROM  : m_iCount_RECEIVING_FROM++ ; break;
        }

//        printf("ML: SOCKET %d, %d, %d, %d, %d, %d  : %d" , m_iCount_RESOLVING
//                                                        , m_iCount_CONNECTING_TO
//                                                        , m_iCount_CONNECTED_TO
//                                                        , m_iCount_SENDING_TO
//                                                        , m_iCount_WAITING_FOR
//                                                        , m_iCount_RECEIVING_FROM
//                                                        , m_iCount_SENDING_TO - m_iCount_RECEIVING_FROM
//                                                        );



    }

    //std::cout << std::endl;

    return NS_ERROR_NOT_IMPLEMENTED;
}

/* readonly attribute boolean isActive; */
NS_IMETHODIMP DefaultHttpActivityObserver::GetIsActive(PRBool *aIsActive)
{
    //printf("ML: DefaultHttpActivityObserver::GetIsActive \n");
    *aIsActive = PR_TRUE;
    return NS_OK;
}
