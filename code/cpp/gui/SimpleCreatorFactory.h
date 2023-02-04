#ifndef SIMPLECREATORFACTORY_H
#define SIMPLECREATORFACTORY_H

#include <NetscavatorFactoryIF.h>

class SimpleCreatorFactory : public crawl::NetscavatorFactoryIF
{
public:
    SimpleCreatorFactory(const boost::shared_ptr<crawl::Configuration>& configuration);
private:
    crawl::BrowserViewIF*   do_createBrowserView(QObject* parent) const override;
    crawl::WebBrowserIF*    do_createBrowser    (crawl::BrowserViewIF* browserView) const override;
};

#endif // SIMPLECREATORFACTORY_H
