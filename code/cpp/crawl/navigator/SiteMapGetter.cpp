#include <iostream>
#include <functional>
#include <boost/tokenizer.hpp>
#include <utils/cpaf_string_utils.hpp>
#include <cpaf_libs/filesystem/cpaf_special_dirs.h>
#include <cpaf_libs/filesystem/cpaf_file_directory_functions.h>
#include <net/cpaf_http_convenience.h>
#include <utils/utils.h>
#include <utils/StringFinder.h>
#include <utils/QStringFinder.h>
#include <utils/string_compare_functions.h>
#include "SiteMapGetter.h"

using namespace std;
using namespace boost;

namespace crawl {


SiteMapGetter::SiteMapGetter()
{
}

SiteMapGetter::SiteMapGetter(const std::string& site)
    : m_site(site),
      m_robotsTxtUrl(site + "/robots.txt")
{
}

void SiteMapGetter::clear()
{
    m_siteMapUrls.clear();
    m_includeUrlFunctors.clear();
    m_excludeUrlFunctors.clear();
    clearLocationUrls();
}

void SiteMapGetter::clearLocationUrls()
{
    m_locationUrls.clear();
}

void SiteMapGetter::siteSet(const string& site)
{
    m_site = site;
    m_robotsTxtUrl = site + "/robots.txt";
}

void SiteMapGetter::doneCallbackSet(const DoneCallbackT& doneCallback)
{
    m_doneCallback = doneCallback;
}

void SiteMapGetter::siteMapUrlsSet(const std::vector<string> &siteMapUrls)
{
    m_siteMapUrls.assign(siteMapUrls.begin(), siteMapUrls.end());
}

void SiteMapGetter::siteMapUrlAppend(const string& siteMapUrl)
{
    if ( std::find(m_siteMapUrls.begin(), m_siteMapUrls.end(), siteMapUrl) == m_siteMapUrls.end() ) {
        m_siteMapUrls.push_back(siteMapUrl);
    }
}


/** Add pattern that all URLs }must} match in order to be loaded.
\note If you want to utilize this you must subscribe to the pageLoaded signal
and implement something similar to ScriptMiner::slotLoadUri()
\sa configAddExcludeUrl(), checkUrlInclude() */
void SiteMapGetter::addIncludeUrl (const std::string pattern, 				///< [in] Pattern to compare against URL about to be loaded.
        const std::string& compareFun					///< [in] Funtion to use when comparing.
        )
{
    using namespace std::placeholders;
    using namespace crawl::string_compare;
    // Create and add a functor which compares the designated pattern with some string
    // using the two argument compare function given. Note the functor is a new
    // compare function with the pattern bound so only one parameter is left in the
    // functor - namely the incoming URL we wish to compare against the pattern.
    auto fn = G_StringCompareLookUp::fromAlias(compareFun);
    m_includeUrlFunctors.push_back( std::bind(fn, _1, pattern) );
}


void SiteMapGetter::addExcludeUrl (const std::string pattern, 	///< [in] Pattern to compare against URL about to be loaded.
        const string& compareFun                                ///< [in] Funtion to use when comparing.
        )
{
    using namespace std::placeholders;
    using namespace crawl::string_compare;
    // Create and add a functor which compares the designated pattern with some string
    // using the two argument compare function given. Note the functor is a new
    // compare function with the pattern bound so only one parameter is left in the
    // functor - namely the incoming URL we wish to compare against the pattern.
    auto fn = G_StringCompareLookUp::fromAlias(compareFun);
    m_excludeUrlFunctors.push_back( std::bind(fn, _1, pattern) );
}

const std::vector<string>& SiteMapGetter::locationUrls() const
{
    return m_locationUrls;
}

std::vector<string> SiteMapGetter::siteMapUrls() const
{
    return {m_siteMapUrls.begin(), m_siteMapUrls.end()};
}


void SiteMapGetter::downloadSiteMap()
{
    if (m_siteMapUrls.empty()){
        getRobotsTxt();
    }
    else {
        getAllLocations();
    }
}


// --- PRIVATE: Handler functions ---

void SiteMapGetter::handleRobotsTxtCb(const QByteArray& data, const QUrl& url, bool)
{
    std::cerr << "INFO: Got robots.txt from URL: " << toString(url) << "\n";
    m_robotsTxt = data.constData();
    string newLocation = checkLocationMoved(m_robotsTxt);
    if (!newLocation.empty()) {
        m_robotsTxtUrl = newLocation;
        std::cerr << "INFO: robots.txt was moved to: " << m_robotsTxtUrl <<  " . Fetching again ... \n";
        getRobotsTxt();
        return;
    }
    parseSiteMapUrlsFromRobotsTxt();
    getAllLocations();
}

// --- PRIVATE: Helper functions ---
string SiteMapGetter::downloadUrl(const string &url) const
{
    std::cerr << "INFO: Downloading sitemap file: '" << url << "'\n";
    return cpaf::net::curl_http_download_to_string(url);
}

void SiteMapGetter::getRobotsTxt()
{
    using namespace std::placeholders;
    std::cerr << "INFO: Getting robots.txt: " << m_robotsTxtUrl << "\n";
    auto cb = [this] (const QByteArray& data, const QUrl& url, bool ok) {
        this->handleRobotsTxtCb(data, url, ok);
    };
    m_httpDownloader.downloadToByteArray (toQUrl(m_robotsTxtUrl), cb);
}

bool SiteMapGetter::getNextSitemapFile()
{
    if (m_siteMapUrls.empty()) return false;

    auto cb = [this] (const QByteArray& data, const QUrl& url, bool downloadedOk) {
        this->addLocationsFromXmlSiteMap(data.constData(), url, downloadedOk);
    };
    auto url = toQUrl(m_siteMapUrls.front());
    std::cerr << "INFO: Downloading next sitemap file: " << toString(url.toString()) << "\n";
    m_siteMapUrls.pop_front();
    m_httpDownloader.downloadToByteArray (url, cb);
    return true;
}

void SiteMapGetter::parseSiteMapUrlsFromRobotsTxt()
{
    typedef boost::tokenizer<boost::char_separator<char> > line_tokenizer;
    line_tokenizer tok(m_robotsTxt, boost::char_separator<char>("\n\r"));

    bool site_maps_found = false;
    for (auto it = tok.begin(), end = tok.end();it != end ; ++it) {
        StringFinder sf(*it);   // *it == text line!
        sf.ignoreCaseSet(true);
        if (sf.findBeginNext("sitemap:")) {
            site_maps_found = true;
            m_siteMapUrls.push_back(sf.currentValue());
            std::cout << "INFO: Adding sitemap url from robots.txt: " << sf.currentValue()
                      << " . Total sitemaps found: " << m_siteMapUrls.size()
                      << std::endl;
        }
    }
    if (!site_maps_found) {
        const auto default_sitmap_url = m_site + "/sitemap.xml";
        std::cout << "INFO: Adding DEFAULT sitemap url: " << default_sitmap_url << std::endl;
        m_siteMapUrls.push_back(default_sitmap_url);
    }
}

void SiteMapGetter::getAllLocations()
{
    if (!getNextSitemapFile() ) {
        // Sort and remove duplicates
        std::sort(m_locationUrls.begin(), m_locationUrls.end());
        auto last = std::unique(m_locationUrls.begin(), m_locationUrls.end());
        std::cout << "INFO: Done adding locations from all sitemaps. Removing "
                  << (m_locationUrls.end() - last)
                  << " duplicates from a brutto total of " << m_locationUrls.size()
                  << std::endl;


        m_locationUrls.erase(last, m_locationUrls.end());
        std::cout << "Total location URLs: "  << m_locationUrls.size()
                  << std::endl;

        // Signal we're done!
        emit sitemapsDownloaded();
        if (m_doneCallback) {
            m_doneCallback(this);
        }
    }
}

/** Parse the sitemap XML file specified.
 * All location URLs are appended to m_locationUrls, except those
 * pointing to other sitemap files. Those additional sitemap URLs
 * are added to the m_siteMapUrls queue.
*/
void SiteMapGetter::addLocationsFromXmlSiteMap(const string& siteMapData, const QUrl& sitemapUrl, bool downloadedOk)
{
    QStringFinder sf(toQString(siteMapData));
    sf.ignoreCaseSet(true);

    if (downloadedOk) {
        const auto sitemapFilePath = cpaf::filesystem::special_dirs::temp() / "sitemap.xml";

        cpaf::filesystem::write_file(sitemapFilePath, siteMapData);

        std::cerr << "INFO: Sitemap file '" << toString(sitemapUrl.toString())
                  << "' downloaded ok. Data text size is " << sf.size() << " \"chars\" "
                  << " wrote sitemap to: " << sitemapFilePath.native() << " \"chars\" "
                  << "\n";
    }
    else {
        std::cerr << "ERROR: Sitemap file '" << toString(sitemapUrl.toString()) << "' failed to download.\n";
    }

    const bool isSitemapIndex = sf.searchIn().indexOf(QString("</sitemapindex>"), 0, Qt::CaseInsensitive) != -1;

    bool moreLocations = downloadedOk;
    sf.newSearch();
    size_t locationUrlsAdded = 0;
    while (moreLocations) {
        moreLocations = sf.findBeginNext("<loc>");

        if (moreLocations) {
            moreLocations = sf.findEndNext("</loc>");
            if (moreLocations) {
                const auto& url = toString(sf.currentValue());
                if (isSitemapIndex) {
                    cout << "Is index '" << isSitemapIndex << "' "
                         << " loc: '" << url << "'"
                         << " count: '" << m_locationUrls.size() << "'" << endl;
                    m_siteMapUrls.push_back(url);
                    std::cout << "INFO: Adding sitemap url from '"
                              << toString(sitemapUrl.toString()) << "' "
                              << url << " . Total sitemaps found: " << m_siteMapUrls.size()
                              << std::endl;
                }
                else {
                    if (okToAddLocationUrl(url)) {
                        ++locationUrlsAdded;
                        m_locationUrls.push_back(url);
                    }
                }
                sf.nextSearch();
            }
        }
    }
    std::cout << "INFO: Done adding locations from '" << toString(sitemapUrl.toString())
              << "'  added/total: " << locationUrlsAdded << " / " << m_locationUrls.size()
              << "'  siteMapUrls total: " << m_siteMapUrls.size()
              << std::endl;

    getAllLocations();
}

/** Check if server response was 'page moved'.
If page was moved then return the new URL otherwise return an empty string!
*/
string SiteMapGetter::checkLocationMoved(const string& pageData) const
{
    string newLocation = "";
    StringFinder sf(pageData);   // *it == text line!
    sf.ignoreCaseSet(true);
    if (sf.findBegin("<title>Document Moved</title>") ||
        sf.findBegin("<title>Moved</title>")) {

        sf.findBegin("HREF=\"");
        sf.findEndNext("\"");
        string url = sf.currentValue();
        if (boost::algorithm::istarts_with(url, "http")) {
            newLocation = url;
        }
    }
    return newLocation;
}

/** See if given URL is ok to load according to the include list.
The URL is considered ok, if it matches any of the (pattern,function) pairs.
\sa configAddIncludeUrl(), checkUrlExclude()
\return true if URL is found in a least one of the (pattern,function) pairs, meaning it }should} be loaded. */
bool SiteMapGetter::checkUrlInclude (std::string const& url 		///< [in] In URL to check.
        )	const
{
    if ( m_includeUrlFunctors.empty() ) {
        return true;	// If no patterns all Urls are considered OK.
    }
    for (auto fn : m_includeUrlFunctors) {
        if ( fn(url) ) {
            return true;
        }
    }
    return false;										// No matches - URL is NOT ok to load.
}

/** See if given URL should }not} be loaded according to include list.
If the URL matches any of the (pattern,function) pairs then it should }not}
be loaded and this function returns true.
\sa configAddExcludeUrl(), checkUrlInclude()
\return true if URL is found in a least one of the (pattern,function) pairs, meaning it should }not} be loaded. */
bool SiteMapGetter::checkUrlExclude (std::string const& url 		///< [in] In URL to check.
        )	const
{
    for (auto fn : m_excludeUrlFunctors) {
        if ( fn(url) ) {
            return true;
        }
    }
    return false;					// No matches - URL should NOT be excluded, i.e. it's ok to load.
}


/** Test if URL in question should actually be loaded. */
bool SiteMapGetter::okToAddLocationUrl (std::string const& url ///< [in] In URL to check
        ) const
{
    using namespace std;
    bool okToLoad = true;
    if (!checkUrlInclude (url))	okToLoad = false;
    if (checkUrlExclude  (url))	okToLoad = false;
    return okToLoad;
}

} // END namespace crawl

