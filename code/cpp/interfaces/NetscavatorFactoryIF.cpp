#include "NetscavatorFactoryIF.h"

namespace crawl {

NetscavatorFactoryIF::NetscavatorFactoryIF(const boost::shared_ptr<Configuration>& configuration)
    : m_configuration(configuration)
{
}

BrowserViewIF* NetscavatorFactoryIF::createBrowserView(QObject* parent) const
{
    return do_createBrowserView(parent);
}

WebBrowserIF* NetscavatorFactoryIF::createBrowser(BrowserViewIF* browserView) const
{
    WebBrowserIF* webBrowser = do_createBrowser(browserView);

    return webBrowser;
}

boost::shared_ptr<Configuration> NetscavatorFactoryIF::configuration() const
{
    return m_configuration;
}

void NetscavatorFactoryIF::configurationSet(const boost::shared_ptr<Configuration>& configuration)
{
    m_configuration = configuration;
}


} // namespace crawl
