#ifndef CRAWL_SITE_MAP_GETTER_H_
#define CRAWL_SITE_MAP_GETTER_H_

#include <string>
#include <vector>
#include <deque>
#include <QString>
#include <applicationutils/QtHttpDownloader.h>

namespace crawl {

/**
 * @brief The SiteMapGetter class
 *
 * @see https://www.sitemaps.org/protocol.html
 *
 */

class SiteMapGetter : public QObject
{
    Q_OBJECT
public:

    using DoneCallbackT         = std::function< void (SiteMapGetter*)>;
    using UrlCompareFunctorT    = std::function< bool ( std::string const& ) >;
    using UrlCompareVecT        = std::vector<UrlCompareFunctorT>;

                    SiteMapGetter();
    explicit        SiteMapGetter(const std::string& site);
    void            clear                               ();
    void            clearLocationUrls                   ();
    void            siteSet                             (const std::string& site);
    void            doneCallbackSet                     (const DoneCallbackT& doneCallback);
    void            siteMapUrlsSet                      (const std::vector<std::string> &siteMapUrls);
    void            siteMapUrlAppend                    (const std::string &siteMapUrl);
    void            addIncludeUrl                       ( const std::string pattern, const std::string& compareFun )	;
    void            addExcludeUrl                       ( const std::string pattern, const std::string& compareFun )	;

    const std::vector<std::string>& locationUrls() const;
    std::vector<std::string>        siteMapUrls () const;

    /** Download all sitemap files from site and store all location/page URLs.
     * Using the site/robots.txt or manually set sitemap URLs.
     * Retrieve the actual links using locationUrls() function.
     *
    */
    void            downloadSiteMap                     ();
signals:
    void            sitemapsDownloaded                  ();

private:
    // --- PRIVATE: Handler functions ---
    void            handleRobotsTxtCb                   (const QByteArray& data, const QUrl& url, bool downloadedOk);

    // --- PRIVATE: Helper functions ---
    std::string     downloadUrl                         (const std::string &url) const;
    void            getRobotsTxt                        ();
    bool            getNextSitemapFile                  ();

    void            parseSiteMapUrlsFromRobotsTxt       ();
    void            getAllLocations                     ();
    void            addLocationsFromXmlSiteMap          (const std::string& siteMapData, const QUrl& sitemapUrl, bool downloadedOk);

    std::string     checkLocationMoved                  (const std::string& pageData) const;
    bool            checkUrlInclude                     (std::string const& url) const;
    bool            checkUrlExclude                     (std::string const& url) const;
    bool            okToAddLocationUrl                  (std::string const& url) const;


    // --- PRIVATE: Members ---
    std::string     m_site;
    std::string     m_robotsTxtUrl;

    std::string     m_robotsTxt;

    std::deque<std::string>     m_siteMapUrls;   // URLs to sitemap (XML) files.
    std::vector<std::string>    m_locationUrls;  // URLs to locations - ie. typical product pages or other content pages on the site
    QtHttpDownloader            m_httpDownloader;
    DoneCallbackT               m_doneCallback;
    UrlCompareVecT				m_includeUrlFunctors;
    UrlCompareVecT				m_excludeUrlFunctors;
};



} //END namespace crawl


#endif //CRAWL_SITE_MAP_GETTER_H_

