#include "SimpleCrawlerFactory.h"
#include <SimpleBrowser.h>

SimpleCrawlerFactory::SimpleCrawlerFactory(const boost::shared_ptr<crawl::Configuration>& configuration)
    : crawl::NetscavatorFactoryIF(configuration)
{
}

crawl::BrowserViewIF* SimpleCrawlerFactory::do_createBrowserView(QObject* /*parent*/) const
{
    return nullptr;
}

crawl::WebBrowserIF* SimpleCrawlerFactory::do_createBrowser(crawl::BrowserViewIF* browserView) const
{
    return new crawl::SimpleBrowser(browserView, configuration());
}
