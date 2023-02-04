#include "LinksGetter.h"

#include <iostream> 
#include <boost/format.hpp> 
#include <boost/lambda/lambda.hpp>

namespace b	= boost;


namespace crawl { 

     



// ------------------------------------
// --- Constructor / Init Functions ---
// ------------------------------------
	

LinksGetter::LinksGetter ( 	
    boost::shared_ptr<LinearDomIF> pLinearDom
    , const Url& siteUrl
) :
    m_pLinearDom(pLinearDom),
	m_siteUrl(siteUrl),
    m_fnUrlsMatch(string_compare::alwaysTrue),
    m_sUrlsMatchString(""),
    m_bFullPathLinks (true)
{
}                                                                               


/** Find/calculate all links in current document. */ 
void
LinksGetter::calculateLinks(
	bool bFullPathLinks			///< Full paths to local Urls i.e. with 'http://sitename.xxx' in front
) 
{	
	m_bFullPathLinks 	= bFullPathLinks;
	m_sUrlsMatchString 	= "";
	m_fnUrlsMatch 		= string_compare::alwaysTrue;
	recalculateLinks() ;
}

/** Find/calculate all links in current document. */ 
void
LinksGetter::calculateLinks(
	bool bFullPathLinks,					///< Full paths to local Urls i.e. with 'http://sitename.xxx' in front
	std::string const& sUrlsMatchString, 	///< String to match agains using fnUrlsMatch
	StringCompareFunT const& fnUrlsMatch	///< String compare function to use.
) 
{	
	m_bFullPathLinks 	= bFullPathLinks;
	m_sUrlsMatchString 	= sUrlsMatchString;
	m_fnUrlsMatch 		= fnUrlsMatch;
	recalculateLinks() ;
}



// -----------------------
// --- Debug Functions ---
// -----------------------
void LinksGetter::printLinks() const 
{
	using namespace std;
    printf( "\nLOCAL Links      : %s\n" , m_siteUrl.string().c_str() );
    printf( "\nLOCAL Links size : %d" , (int)linksLocal().size() );
    printf("TODO: Implement priting of links !!!\n");
    //std::for_each( linksLocal().begin(), linksLocal().end(), std::cout << boost::lambda::_1 << '\n' );
    printf( "\n" );
    printf( "\nEXTERNAL Links      : %s\n" , m_siteUrl.string().c_str() );
    printf( "\nEXTERNAL Links size : %d\n" , (int)linksExternal().size() );
    //std::for_each( linksExternal().begin(), linksExternal().end(), std::cout << boost::lambda::_1 << '\n' );
    printf( "\n" );
}

// -------------------------
// --- Private Functions ---
// -------------------------

void LinksGetter::recalculateLinks() 
{
	m_Links.clear();
	m_LinksLocal.clear();
	m_LinksExternal.clear();
////    parseLinks_OLD();
    parseLinks();
}


void LinksGetter::parseLinks()
{
    LinearDomIF::const_iterator it      = m_pLinearDom->begin();
    LinearDomIF::const_iterator itEND   = m_pLinearDom->end();
    for ( ; it != itEND; ++it )
    {
        if ( it->stringData() == "href" )
        {
            ++it;
            if ( it != itEND  )
            {
                Url url( it->stringData(), false );
                if ( url.isMailAddress() ) {
                    continue;
                }

                if ( m_bFullPathLinks )	{
                    if ( !url.hasDomain() ) {
                        url.domainSet( m_siteUrl.domainVec() );
                        url.protocolSet( m_siteUrl.protocol() );
                    }
                    if ( !url.hasProtocol() )	{
                        url.protocolSet( "http" );
                    }
                }

                if ( 	!url.isJavaScriptFunctionCall() && !url.isJavaScript() &&
                        !url.isSectionLink() )
                {
                    if ( !url.empty() ) {
                        add_if ( m_Links, url, m_sUrlsMatchString, m_fnUrlsMatch );

                        if ( url.hasDomain() ) {
                            if ( m_siteUrl.siteDomain() == url.siteDomain() ) {
                                add_if ( m_LinksLocal, url, m_sUrlsMatchString, m_fnUrlsMatch );
                            }
                            else {
                                add_if ( m_LinksExternal, url, m_sUrlsMatchString, m_fnUrlsMatch );
                            }
                        }
                        else add_if ( m_LinksLocal, url, m_sUrlsMatchString, m_fnUrlsMatch );
                    }
                }
            }
        }

    }
}

/** 
Get all links from document. Currently we only get plain links i.e. not javascript etc.
*/
//void LinksGetter::parseLinks_OLD()
//{
//	using namespace std;
	
//	boost::shared_ptr<DOMHTMLDocument> pHTMLDoc( doQueryInterface<DOMHTMLDocument>(m_pDOMDoc) );
	
//	if ( !pHTMLDoc->valid() )	return;
	
//	DOMHTMLCollection::iterator 	pIt;
//	DOMHTMLCollection::Ptr 			pNodes 		= pHTMLDoc->links();
	
//	for ( pIt = pNodes->begin(); pIt != pNodes->end(); ++pIt ) {
//		boost::shared_ptr<DOMHTMLElement> pElem( doQueryInterface<DOMHTMLElement>(*pIt) );
//		if ( !pElem->valid() ) continue;
	
//        Url Url( pElem->getAttribute("href"), false, true );
//		if ( Url.is_mail_address() ) {
//			continue;
//		}
		
//		if ( m_bFullPathLinks )	{
//			if ( !Url.has_domain() ) {
//				Url.domain( m_siteUrl.domain() );
//				Url.protocol( m_siteUrl.protocol() );
//			}
//			if ( !Url.has_protocol() )	{
//				Url.protocol( "http" );
//			}
//		}
		
//		if ( 	!Url.is_java_script_function_call() && !Url.is_java_script() &&
//				!Url.is_section_link() )
//		{
//			if ( !Url.empty() ) {
//				add_if ( m_Links, Url, m_sUrlsMatchString, m_fnUrlsMatch );
				
//				if ( Url.has_domain() ) {
//				  	if ( m_siteUrl.site_domain() == Url.site_domain() ) {
//						add_if ( m_LinksLocal, Url, m_sUrlsMatchString, m_fnUrlsMatch );
//					}
//					else {
//						add_if ( m_LinksExternal, Url, m_sUrlsMatchString, m_fnUrlsMatch );
//					}
//				}
//				else add_if ( m_LinksLocal, Url, m_sUrlsMatchString, m_fnUrlsMatch );
//			}
//		}
//	}
//}


// ----------------------
// --- Free Functions ---
// ----------------------

void 
add_if ( 
	UrlVecT& vecTo, 
	Url const& url, 
	std::string const& sUrlsMatchString, 
	StringCompareFunT const& fnUrlsMatch 
) 
{
	if ( fnUrlsMatch( url.parsedString(), sUrlsMatchString ) ) {
		vecTo.push_back ( url );
	}
}


void 
copy_if ( 
	UrlVecT& vecTo, 
	UrlVecT const& vecFrom, 
	std::string const& sUrlsMatchString, 
	StringCompareFunT const& fnUrlsMatch 
) 
{
	for ( UrlVecT::const_iterator it = vecFrom.begin(); it != vecFrom.end(); ++it ) {
        if ( fnUrlsMatch( it->parsedString(), sUrlsMatchString ) ) {
			vecTo.push_back ( *it );
		}
	}
}



} // END namespace crawl

