#include "SimpleCreatorFactory.h"
#include <SimpleBrowser.h>
#include <CreatorSimpleWebViewUi.h>

SimpleCreatorFactory::SimpleCreatorFactory(const boost::shared_ptr<crawl::Configuration>& configuration)
    : crawl::NetscavatorFactoryIF(configuration)
{
}

crawl::BrowserViewIF* SimpleCreatorFactory::do_createBrowserView(QObject* parent) const
{
    return new crawl::CreatorSimpleWebViewUi(configuration(), parent);
}

crawl::WebBrowserIF* SimpleCreatorFactory::do_createBrowser(crawl::BrowserViewIF* browserView) const
{
    return new crawl::SimpleBrowser(browserView, configuration());
}
