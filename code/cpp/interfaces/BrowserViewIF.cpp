#include "BrowserViewIF.h"
#include <stdio.h>
#include <iostream>

using namespace crawl;

BrowserViewIF::BrowserViewIF(const boost::shared_ptr<Configuration>& configuration,
                             QObject* parent)
  : QObject(parent),
    m_configuration(configuration)
{
}

boost::shared_ptr<Configuration> BrowserViewIF::configuration() const
{
    return m_configuration;
}

void BrowserViewIF::configurationSet(const boost::shared_ptr<Configuration>& configuration)
{
    m_configuration = configuration;
}

void BrowserViewIF::emitDomPosSelectedSig(const QString& xpath, const QString& innerText)
{
    emit domPosSelectedSig(xpath, innerText);
}

void BrowserViewIF::emitLinkClicked(const QUrl& url)
{
    emit linkClicked(this, url);
}

void BrowserViewIF::emitBrowserViewPageLoaded(bool ok)
{
    emit browserViewPageLoadedSignal(this, ok);
}

WebBrowserIF* BrowserViewIF::owningBrowser() const
{
    return m_owningBrowser;
}

void BrowserViewIF::owningBrowserSet(WebBrowserIF* owningBrowser)
{
    m_owningBrowser = owningBrowser;
}
