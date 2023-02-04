#include <stdio.h>
#include <string>
#include <nsIURI.h>
#include <nsServiceManagerUtils.h>
#include <nsIWebNavigationInfo.h>
////#include <nsITimer.h>
#include <nsDocShellCID.h>
////#include <nsComponentManagerUtils.h>
#include <utils/string_conversion.h>
#include <WebBrowserIF.h>
#include <SignalsManager.h>
#include "DefaultContentListener.h"



DefaultURIContentListener::DefaultURIContentListener ( 
	crawl::WebBrowserIF& mozBrowser,
	nsCOMPtr<nsIWebBrowser> pIWebBrowser
)	:
	m_mozBrowser( mozBrowser ),
	m_pNavigation ( do_QueryInterface ( pIWebBrowser ) )
{
}

DefaultURIContentListener::~DefaultURIContentListener()
{
}

NS_IMPL_ISUPPORTS2 ( DefaultURIContentListener,
                     nsIURIContentListener,
                     nsISupportsWeakReference )


NS_IMETHODIMP
DefaultURIContentListener::OnStartURIOpen (
    nsIURI     *aURI,
    PRBool     *aAbortOpen
)
{
	nsresult rv;

	nsCAutoString specString;
	rv = aURI->GetSpec ( specString );
	if ( NS_FAILED ( rv ) ) return rv;
	
	std::string sURI ( specString.get() );
	*aAbortOpen = PR_FALSE;
	
	// Timer code
// 	nsCOMPtr<nsITimer> m_timer = do_CreateInstance("@mozilla.org/timer;1", &rv);
// 	if (NS_FAILED(rv))
// 	{
// 		return rv;
// 	}
    bool bAbortOpen = m_mozBrowser.signalsManager()->signalOnLoadUri( m_mozBrowser, sURI );
    if ( bAbortOpen ) {
        *aAbortOpen = PR_TRUE;
    }
    return NS_OK;
}

NS_IMETHODIMP
DefaultURIContentListener::DoContent (
    const char         *aContentType,
    PRBool             aIsContentPreferred,
    nsIRequest         *aRequest,
    nsIStreamListener **aContentHandler,
    PRBool             *aAbortProcess
)
{
	return NS_ERROR_NOT_IMPLEMENTED;
}

NS_IMETHODIMP
DefaultURIContentListener::IsPreferred (
    const char        *aContentType,
    char             **aDesiredContentType,
    PRBool            *aCanHandleContent
)
{
	return CanHandleContent ( aContentType, PR_TRUE, aDesiredContentType, aCanHandleContent );
}

NS_IMETHODIMP
DefaultURIContentListener::CanHandleContent (
    const char        *aContentType,
    PRBool           aIsContentPreferred,
    char             **aDesiredContentType,
    PRBool            *_retval
)
{
	*_retval = PR_FALSE;
	*aDesiredContentType = NULL;

	if ( aContentType )
	{
		nsCOMPtr<nsIWebNavigationInfo> webNavInfo ( do_GetService ( NS_WEBNAVIGATION_INFO_CONTRACTID ) );
		if ( webNavInfo )
		{
			PRUint32 canHandle;
			nsresult rv = 
				webNavInfo->IsTypeSupported( nsDependentCString(aContentType),
				m_pNavigation ? m_pNavigation.get() : NULL,	&canHandle );
			NS_ENSURE_SUCCESS(rv, rv);
			*_retval = (canHandle != nsIWebNavigationInfo::UNSUPPORTED);
		}
	}
	return NS_OK;
}

NS_IMETHODIMP
DefaultURIContentListener::GetLoadCookie (
    nsISupports **aLoadCookie
)
{
	return NS_ERROR_NOT_IMPLEMENTED;
}

NS_IMETHODIMP
DefaultURIContentListener::SetLoadCookie (
    nsISupports *aLoadCookie
)
{
	return NS_ERROR_NOT_IMPLEMENTED;
}

NS_IMETHODIMP
DefaultURIContentListener::GetParentContentListener (
    nsIURIContentListener **aParent
)
{
	return NS_ERROR_NOT_IMPLEMENTED;
}

NS_IMETHODIMP
DefaultURIContentListener::SetParentContentListener (
    nsIURIContentListener *aParent
)
{
	return NS_ERROR_NOT_IMPLEMENTED;
}

