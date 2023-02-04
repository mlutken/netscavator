#ifndef WEBKITCREATORFACTORY_H
#define WEBKITCREATORFACTORY_H

#include <NetscavatorFactoryIF.h>

class WebkitCreatorFactory : public crawl::NetscavatorFactoryIF
{
public:
    explicit WebkitCreatorFactory(const boost::shared_ptr<crawl::Configuration>& configuration);
private:
    crawl::BrowserViewIF*   do_createBrowserView(QObject* parent) const override;
    crawl::WebBrowserIF*    do_createBrowser    (crawl::BrowserViewIF* browserView) const override;
};

#endif // WEBKITCREATORFACTORY_H
