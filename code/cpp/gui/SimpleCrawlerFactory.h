#ifndef SIMPLECRAWLERFACTORY_H
#define SIMPLECRAWLERFACTORY_H

#include <NetscavatorFactoryIF.h>

class SimpleCrawlerFactory : public crawl::NetscavatorFactoryIF
{
public:
    SimpleCrawlerFactory(const boost::shared_ptr<crawl::Configuration>& configuration);
private:
    crawl::BrowserViewIF*   do_createBrowserView(QObject* parent) const override;
    crawl::WebBrowserIF*    do_createBrowser    (crawl::BrowserViewIF* browserView) const override;
};

#endif // SIMPLECRAWLERFACTORY_H
