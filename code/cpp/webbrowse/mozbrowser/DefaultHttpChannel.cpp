#include <stdio.h>
#include <boost/thread.hpp>
#include <boost/algorithm/string.hpp>

#include <nsIChannel.h>
#include <nsIDOMWindow.h>
#include <nsNetError.h>

#include <nsIURI.h>
#include <WebBrowserIF.h>
#include "DefaultHttpChannel.h"





namespace b = boost;


//NS_IMPL_ISUPPORTS1(DefaultHttpChannel, nsIHttpChannel)

NS_IMPL_ISUPPORTS2 ( DefaultHttpChannel,
                     nsIHttpChannel,
                     nsISupportsWeakReference )

DefaultHttpChannel::DefaultHttpChannel (
    crawl::WebBrowserIF& mozBrowser
)	:
    m_mozBrowser( mozBrowser )
{
}

DefaultHttpChannel::~DefaultHttpChannel()
{
}





NS_IMETHODIMP DefaultHttpChannel::GetRequestMethod(nsACString & aRequestMethod)
{
    printf("ML: DefaultHttpChannel\n");
    return NS_ERROR_NOT_IMPLEMENTED;
}

NS_IMETHODIMP DefaultHttpChannel::SetRequestMethod(const nsACString & aRequestMethod)
{
    printf("ML: DefaultHttpChannel\n");
    return NS_ERROR_NOT_IMPLEMENTED;
}

/* attribute nsIURI referrer; */
NS_IMETHODIMP DefaultHttpChannel::GetReferrer(nsIURI **aReferrer)
{
    printf("ML: DefaultHttpChannel\n");
    return NS_ERROR_NOT_IMPLEMENTED;
}

NS_IMETHODIMP DefaultHttpChannel::SetReferrer(nsIURI *aReferrer)
{
    printf("ML: DefaultHttpChannel\n");
    return NS_ERROR_NOT_IMPLEMENTED;
}

/* ACString getRequestHeader (in ACString aHeader); */
NS_IMETHODIMP DefaultHttpChannel::GetRequestHeader(const nsACString & aHeader, nsACString & _retval NS_OUTPARAM)
{
    printf("ML: DefaultHttpChannel\n");
    return NS_ERROR_NOT_IMPLEMENTED;
}

/* void setRequestHeader (in ACString aHeader, in ACString aValue, in boolean aMerge); */
NS_IMETHODIMP DefaultHttpChannel::SetRequestHeader(const nsACString & aHeader, const nsACString & aValue, PRBool aMerge)
{
    printf("ML: DefaultHttpChannel\n");
    return NS_ERROR_NOT_IMPLEMENTED;
}

/* void visitRequestHeaders (in nsIHttpHeaderVisitor aVisitor); */
NS_IMETHODIMP DefaultHttpChannel::VisitRequestHeaders(nsIHttpHeaderVisitor *aVisitor)
{
    printf("ML: DefaultHttpChannel\n");
    return NS_ERROR_NOT_IMPLEMENTED;
}

/* attribute boolean allowPipelining; */
NS_IMETHODIMP DefaultHttpChannel::GetAllowPipelining(PRBool *aAllowPipelining)
{
    printf("ML: DefaultHttpChannel\n");
    return NS_ERROR_NOT_IMPLEMENTED;
}

NS_IMETHODIMP DefaultHttpChannel::SetAllowPipelining(PRBool aAllowPipelining)
{
    printf("ML: DefaultHttpChannel\n");
    return NS_ERROR_NOT_IMPLEMENTED;
}

/* attribute unsigned long redirectionLimit; */
NS_IMETHODIMP DefaultHttpChannel::GetRedirectionLimit(PRUint32 *aRedirectionLimit)
{
    printf("ML: DefaultHttpChannel\n");
    return NS_ERROR_NOT_IMPLEMENTED;
}

NS_IMETHODIMP DefaultHttpChannel::SetRedirectionLimit(PRUint32 aRedirectionLimit)
{
    printf("ML: DefaultHttpChannel\n");
    return NS_ERROR_NOT_IMPLEMENTED;
}

/* readonly attribute unsigned long responseStatus; */
NS_IMETHODIMP DefaultHttpChannel::GetResponseStatus(PRUint32 *aResponseStatus)
{
    return NS_ERROR_NOT_IMPLEMENTED;
}

/* readonly attribute ACString responseStatusText; */
NS_IMETHODIMP DefaultHttpChannel::GetResponseStatusText(nsACString & aResponseStatusText)
{
    return NS_ERROR_NOT_IMPLEMENTED;
}

/* readonly attribute boolean requestSucceeded; */
NS_IMETHODIMP DefaultHttpChannel::GetRequestSucceeded(PRBool *aRequestSucceeded)
{
    return NS_ERROR_NOT_IMPLEMENTED;
}

/* ACString getResponseHeader (in ACString header); */
NS_IMETHODIMP DefaultHttpChannel::GetResponseHeader(const nsACString & header, nsACString & _retval NS_OUTPARAM)
{
    printf("ML: DefaultHttpChannel\n");
    return NS_ERROR_NOT_IMPLEMENTED;
}

/* void setResponseHeader (in ACString header, in ACString value, in boolean merge); */
NS_IMETHODIMP DefaultHttpChannel::SetResponseHeader(const nsACString & header, const nsACString & value, PRBool merge)
{
    printf("ML: DefaultHttpChannel\n");
    return NS_ERROR_NOT_IMPLEMENTED;
}

/* void visitResponseHeaders (in nsIHttpHeaderVisitor aVisitor); */
NS_IMETHODIMP DefaultHttpChannel::VisitResponseHeaders(nsIHttpHeaderVisitor *aVisitor)
{
    printf("ML: DefaultHttpChannel\n");
    return NS_ERROR_NOT_IMPLEMENTED;
}

/* boolean isNoStoreResponse (); */
NS_IMETHODIMP DefaultHttpChannel::IsNoStoreResponse(PRBool *_retval NS_OUTPARAM)
{
    printf("ML: DefaultHttpChannel\n");
    return NS_ERROR_NOT_IMPLEMENTED;
}

/* boolean isNoCacheResponse (); */
NS_IMETHODIMP DefaultHttpChannel::IsNoCacheResponse(PRBool *_retval NS_OUTPARAM)
{
    printf("ML: DefaultHttpChannel\n");
    return NS_ERROR_NOT_IMPLEMENTED;
}

