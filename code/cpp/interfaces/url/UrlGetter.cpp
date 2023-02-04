


//#include <iostream>
//#include <utils/string_algorithms.h>
//#include <utils/string_compare_functions.h>
#include "UrlGetter.h"

//#include "scriptcrawl.h"
 
//using crawl::string_compare::G_StringCompareLookUp;

UrlGetter::UrlGetter ()
    : m_iCurrent(0)
{
}


UrlGetter::UrlGetter (
      int /*iLinkType*/ 						///< [in] Link type, one of: LINK_TYPE_LOCAL, LINK_TYPE_EXTERNAL, LINK_TYPE_ALL
    , const std::string& /*sUrlsMatch*/ 		///< [in] String to match each url against using the compare operator
    , const std::string& /*sIdCompFun*/ 		///< [in] Url compare operator.
  )
      : m_iCurrent(0)
{
//    TODO: Should be created via a member function in ScriptCrawlIF so we don't need the global curMiner()
//    crawl::StringCompareFunT op = G_StringCompareLookUp::fromAlias( sIdCompFun );
//    if ( sUrlsMatch.empty()	)	curMiner()->linksGetter()->calculateLinks	( true );
//    else						curMiner()->linksGetter()->calculateLinks 	( true, sUrlsMatch, op );
//	if ( iLinkType & LINK_TYPE_LOCAL ) {
//        m_Urls = curMiner()->linksGetter()->linksLocal();
//	}
//	if ( iLinkType & LINK_TYPE_EXTERNAL ) {
//        m_Urls = curMiner()->linksGetter()->linksExternal();
//	}
//	m_iCurrent = 0;
}
 

UrlGetter::~UrlGetter()
{
}
 
// ---------


int
UrlGetter::count()
{
    return static_cast<int>(m_Urls.size());
}

bool
UrlGetter::getNext	()
{
    if ( m_iCurrent < m_Urls.size() )	m_iCurrent++;
    return m_iCurrent < m_Urls.size();
}

void
UrlGetter::resetCurrent( int iNewCurrent )
{
    crawl::UrlVecT::size_type iNew = static_cast<crawl::UrlVecT::size_type>(iNewCurrent);
    if ( iNew >= m_Urls.size() )	iNew = 0;
    m_iCurrent = iNew;
}


bool
UrlGetter::currentAtEnd()
{
    return m_iCurrent >= m_Urls.size();
}

std::string
UrlGetter::current() const
{
//    if ( m_iCurrent < m_Urls.size() )	return m_Urls[m_iCurrent].string();
//    else								return "";
    return "";
}

std::string
UrlGetter::current_raw()
{
    if ( m_iCurrent < m_Urls.size() )	return m_Urls[m_iCurrent].rawString();
    else								return "";
}

std::string
UrlGetter::currentProtocol()
{
    if ( m_iCurrent < m_Urls.size() )	return m_Urls[m_iCurrent].protocol();
    else								return "";
}

// --------

//std::string
//UrlGetter::currentPath()
//{
//    if ( m_iCurrent < m_Urls.size() )	return m_Urls[m_iCurrent].path().string();
//    else								return "";
//}


//std::string
//UrlGetter::currentParameters()
//{
//    if ( m_iCurrent < m_Urls.size() )	return m_Urls[m_iCurrent].parameters_as_string();
//    else								return "";
//}

//std::string
//UrlGetter::currentDomain()
//{
//    if ( m_iCurrent < m_Urls.size() )	return m_Urls[m_iCurrent].domain_as_string();
//    else								return "";
//}


//std::string
//UrlGetter::currentTopDomain()
//{
//    if ( m_iCurrent < m_Urls.size() )	return m_Urls[m_iCurrent].top_domain();
//    else								return "";
//}

//std::string
//UrlGetter::currentSecondLevelDomain()
//{
//    if ( m_iCurrent < m_Urls.size() )	return m_Urls[m_iCurrent].second_level_domain();
//    else								return "";
//}

//std::string
//UrlGetter::currentSubDomains()
//{
//    if ( m_iCurrent < m_Urls.size() )	return m_Urls[m_iCurrent].sub_domains();
//    else								return "";
//}

//std::string
//UrlGetter::currentSiteDomain()
//{
//    if ( m_iCurrent < m_Urls.size() )	return m_Urls[m_iCurrent].site_domain();
//    else								return "";
//}

