#ifndef _CRAWL_LINKS_GETTER_H_
#define _CRAWL_LINKS_GETTER_H_

#include <url/Url.h>
#include <utils/string_compare_functions.h>
#include <utils/string_algorithms.h>
#include <LinearDomIF.h>

namespace crawl { 



/** 
Mozilla html document parser implementation. 
\author Veriquin */
class LinksGetter 
{
public:

    // ----------------
    // --- Typedefs ---
    // ----------------
	typedef boost::shared_ptr<LinksGetter>		Ptr;	

    // ------------------------------------
    // --- Constructor / Init Functions ---
    // ------------------------------------
	
    LinksGetter( boost::shared_ptr<LinearDomIF> pLinearDom, const Url& siteUrl = Url("") );

	void			calculateLinks( bool bFullPathLinks	);
	void			calculateLinks( bool bFullPathLinks, std::string const& sUrlsMatchString, 
									StringCompareFunT const& fnUrlsMatch );
	

    // ---------------------
    // --- Get Functions ---
    // ---------------------
	const UrlVecT&	links() 								const
								{	return m_Links; 		}
	const UrlVecT&	linksLocal() 							const
								{	return m_LinksLocal; }
	
	const UrlVecT&	linksExternal() 						const
								{	return m_LinksExternal; }

    // ----------------------------------
    // --- Convenience Info Functions ---
    // ----------------------------------
	Url				siteUrl() 								const		
								{	return m_siteUrl;		}

    // ----------------------
    // --- Misc Functions ---
    // ----------------------
	
    // ----------------------
    // --- Friend Functions ---
    // ----------------------
	
    // -----------------------
    // --- Debug Functions ---
    // -----------------------
	void 					printLinks() const;

protected:

private:
    // -------------------------
    // --- Private Functions ---
    // -------------------------
	void 					recalculateLinks();
    void 					parseLinks();


    // -------------------
    // --- Member Data ---
    // -------------------
    boost::shared_ptr<LinearDomIF>          m_pLinearDom;
    Url						m_siteUrl;
    StringCompareFunT		m_fnUrlsMatch;
	std::string				m_sUrlsMatchString;
	bool					m_bFullPathLinks;
	std::string				m_sPageData;
	UrlVecT					m_Links;
	UrlVecT					m_LinksLocal;
	UrlVecT					m_LinksExternal;
};

// ----------------------
// --- Free Functions ---
// ----------------------


void 
add_if ( UrlVecT& vecTo, Url const& url, std::string const& sUrlsMatchString, StringCompareFunT const& fnUrlsMatch ) ;

void 
copy_if ( UrlVecT& vecTo, UrlVecT const& vecFrom, std::string const& sUrlsMatchString, StringCompareFunT const& fnUrlsMatch ) ;
 





} // END namespace crawl


#endif //_CRAWL_LINKS_GETTER_H_


