#ifndef _WEBBROWSE_DEFAULT_PROGRESS_H_
#define _WEBBROWSE_DEFAULT_PROGRESS_H_

#include <nsIWebProgressListener.h>
#include <nsWeakReference.h>

class MozBrowserWx;

class DefaultProgress : public nsIWebProgressListener,
			public nsSupportsWeakReference
{
public:
    DefaultProgress( MozBrowserWx* pMozBrowser );
	virtual ~DefaultProgress();

	NS_DECL_ISUPPORTS
	NS_DECL_NSIWEBPROGRESSLISTENER

private:
	static void requestToURIString ( nsIRequest *aRequest, nsACString &aString );
	
	// --- Data ---
    MozBrowserWx* 						m_pMozBrowser;
};

#endif // _WEBBROWSE_DEFAULT_PROGRESS_H_
