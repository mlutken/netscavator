#include "WebkitCreatorFactory.h"
#include <WebKitBrowserQt.h>
#include <CreatorWebkitWebViewUi.h>

WebkitCreatorFactory::WebkitCreatorFactory(
        const boost::shared_ptr<crawl::Configuration>& configuration)
    : crawl::NetscavatorFactoryIF(configuration)
{
}

crawl::BrowserViewIF* WebkitCreatorFactory::do_createBrowserView(QObject* parent) const
{
    return new CreatorWebkitWebViewUi(configuration(), parent);
}

crawl::WebBrowserIF* WebkitCreatorFactory::do_createBrowser(crawl::BrowserViewIF* browserView) const
{
    return new crawl::WebKitBrowserQt(browserView, configuration());
}

