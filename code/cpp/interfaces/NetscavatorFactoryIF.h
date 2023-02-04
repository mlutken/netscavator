#ifndef NETSCAVATORFACTORYIF_H
#define NETSCAVATORFACTORYIF_H

#include <memory>
#include <BrowserViewIF.h>
#include <WebBrowserIF.h>

namespace crawl {
class Configuration;

class NetscavatorFactoryIF
{
public:
//    NetscavatorFactoryIF() = default;
    explicit NetscavatorFactoryIF(const boost::shared_ptr<Configuration>& configuration);
    virtual ~NetscavatorFactoryIF() = default;
    crawl::BrowserViewIF*   createBrowserView(QObject* parent) const;
    crawl::WebBrowserIF*    createBrowser    (crawl::BrowserViewIF* browserView) const;

    boost::shared_ptr<Configuration>    configuration() const;
    void                                configurationSet(const boost::shared_ptr<Configuration>& configuration);

private:
    virtual crawl::BrowserViewIF*   do_createBrowserView(QObject* parent) const = 0;
    virtual crawl::WebBrowserIF*    do_createBrowser    (crawl::BrowserViewIF* browserView) const = 0;

    boost::shared_ptr<Configuration>    m_configuration;
};

} // namespace crawl

#endif // NETSCAVATORFACTORYIF_H
