#if WEBBROWSE_ENABLE_GTK
#include <stdio.h>
#include "MozBrowserGtk.h"


MozBrowserGtk::MozBrowserGtk ()	:	
	MozBrowser ()
{
	printf("MozBrowserGtk::CONSTRUCTOR this: %p\n", this );
}

MozBrowserGtk::MozBrowserGtk (boost::shared_ptr<WebBrowser> pWebBrowser )	:	
	MozBrowser( pWebBrowser )
{
	printf("MozBrowserGtk::CONSTRUCTOR(pWebBrowser) this: %p\n", this );
}

void MozBrowserGtk::show()
{
}

void MozBrowserGtk::hide()
{
}

#endif //#if WEBBROWSE_ENABLE_GTK


