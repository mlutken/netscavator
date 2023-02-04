
#include <iostream> // Debug only 
#include <string>
#include <set>

#include <boost/algorithm/string.hpp>
#include <boost/algorithm/string/replace.hpp>
#include <boost/format.hpp>

#include <filesystem/cpaf_file_directory_functions.h>

#include "url_string_functions.h"
#include "Url.h"

// --- Test Url class ---
//#include "_test/test_url.cpp"
//static	TestUrlClass testUrlClass;

using namespace std;
using namespace boost;


namespace crawl { 
 
// ------------------------------------
// --- Static member initialization ---
// ------------------------------------

// ------------------------------------
// --- Constructor / Init Functions ---
// ------------------------------------

Url::Url(
	const std::string& sUrl			///< 
) : m_sRawUrl       ( sUrl  )
  , m_bIsFile       ( false )
  ,	m_bUseParsed    ( true  )
{
    assign ( sUrl, false );
}


Url::Url(
	const std::string& sUrl,			///< 
    bool bAssumeRelativeLink			///<
) : m_sRawUrl       ( sUrl  )
  , m_bIsFile       ( false )
  , m_bUseParsed    ( true  )
{
    assign ( sUrl, bAssumeRelativeLink );
}


Url::Url(
    const Url& url
)
    : m_sRawUrl     ( url.m_sRawUrl     )
    , m_sProtocol	( url.m_sProtocol   )
    , m_Domain		( url.m_Domain      )
    , m_subDir      ( url.m_subDir      )
    , m_sLeaf       ( url.m_sLeaf       )
    , m_bIsFile		( url.m_bIsFile     )
{
}


std::string Url::domain() const
{
    return domainCompose();
}
// ---------------------
// --- Set Functions ---
// ---------------------

/** Set protocol */
void Url::protocolSet ( const std::string& sProtocol )
{
	if ( is_valid_protocol( sProtocol ) )	m_sProtocol = sProtocol;
	else	{
        if ( sProtocol != "" ) printf( "ERROR : Url::protocol INVALID protocol:\n" );
		m_sProtocol = "";
	}
}

/** Set domain/site */
void Url::domainSet ( const std::string& sDomain)
{
	split_domain( sDomain, m_Domain);
}

void Url::subdirSet ( const std::string& subdir )		///< [in] Subdir to assign.
{
    subdirSet( boost::filesystem::path(subdir) );
}

void Url::subdirSet ( const boost::filesystem::path& subdir )		///< [in] Subdir to assign.
{
    m_subDir = subdir;
}



// ---------------------
// --- Get Functions ---
// ---------------------

std::string	Url::string() const
{
    if ( m_bUseParsed )	{
        return parsedString();
    }
    else {
        return rawStringWithProtocol();
    }
}

std::string Url::rawStringWithProtocol()  const
{
    std::string::size_type i = 0;
    std::string sProto = parse_protocol(m_sRawUrl, i);
    if ( sProto == "" )  {
        sProto =  m_bIsFile ? "file://" : "http://";
    }
    else sProto = "";
    std::string sUrl = sProto + rawString();
    return sUrl;
}


/** Get URL as string. */
std::string	Url::parsedString() const
{ 
	std::string s;
    if ( hasProtocol()	)	s.append( protocolCompose()		);
    if ( hasDomain()	)	s.append( domainCompose()		);
    if ( hasSubdir()	)	s.append( subdirCompose()		);
    if ( hasLeaf()     )	s.append( leafCompose()         );
    return s;
}

std::string	Url::protocolCompose() const
{
    return protocol() + "://";
}


/// Get domain as a string
std::string	Url::domainCompose() const
{ 
	std::string sDomain;
	for ( string_vec_t::const_reverse_iterator it = m_Domain.rbegin(); it != m_Domain.rend(); ++it ) {
		sDomain.append(*it);
		if ( it < m_Domain.rend() -1) sDomain.append(1, '.');
	}
	return sDomain; 
}

std::string	Url::subdirCompose() const
{
    if ( m_subDir.empty() ) return "/";
    else                    return m_subDir.string();
}


std::string	Url::leafCompose() const
{
    return m_sLeaf;
}



std::string	Url::topDomain() const
{
	if ( m_Domain.size() > 0 )	return m_Domain.front();
	else						return ""; 
}

std::string	Url::secondLevelDomain() const
{
	if ( m_Domain.size() > 1 )	return *(m_Domain.begin() +1);
	else						return ""; 
}

std::string	Url::subDomains() const
{
	using namespace std;
	if ( m_Domain.size() >= 3 )	{
		std::string sDomain;
		for ( string::size_type i = m_Domain.size() -1; i >= 2; --i ) {
			sDomain.append( m_Domain[i] );
			if ( i > 2 ) sDomain.append(1, '.');
		}
		return sDomain; 
	}	
	else						return ""; 
} 

/** Site domain (name) like 'lego.com'. Sitename is the second + top level domains 
concatenated. */
std::string Url::siteDomain() const
{
    std::string s( topDomain() );
    if ( !secondLevelDomain().empty() )	{
        s = secondLevelDomain() + "." + s;
	}
	return s;
}


// ----------------------------------
// --- Convenience Info Functions ---
// ----------------------------------


bool Url::isJavaScript() const
{ 
	bool bIsJavaScript = false;
	std::string s = string();
	if ( s.find( ".jsp" )	!= std::string::npos )	bIsJavaScript = true;
	if ( s.find( ".js" )	!= std::string::npos )	bIsJavaScript = true;
	return bIsJavaScript;
}

bool Url::isJavaScriptFunctionCall() const
{
	std::string s = string();
	return s.find( ')' ) != std::string::npos;			
}


/** Link is a link to a named section. 
Html href looking like this will cause thjis function to return true:
\code
<a href="http://www.w3schools.com/html_links.asp#tips">
\endcode
*/
bool Url::isSectionLink() const
{
	std::string s = string();
	return s.find( '#' ) != std::string::npos;			
} 


/** Link is a "local" link to a named section. 
Html href looking like this will cause this function to return true:
\code
<a href="#tips">Jump to the Useful Tips Section</a>
\endcode
*/
bool Url::isLocalSectionLink() const
{
	std::string s = string();
    return boost::contains( string(), "#" );
//	return s[0] == '#' ;
} 

/** */
bool Url::isMailAddress()	const
{
	return boost::contains( string(), "mailto" );
}


// ----------------------
// --- Misc Functions ---
// ----------------------


Url& Url::operator=	(
    const Url& url
)
{
    m_sRawUrl		= url.m_sRawUrl;
    m_sProtocol		= url.m_sProtocol;
    m_Domain		= url.m_Domain;
    m_subDir        = url.m_subDir;
    m_sLeaf         = url.m_sLeaf;
    m_bIsFile		= url.m_bIsFile;
    return *this;
}

/**
Typically used to add the protocol ('http://')
  */
Url& Url::makeDefaultProtocol ()
{
    if ( !hasProtocol() ) {
        std::string sProto =  m_bIsFile ? "file" : "http";
        protocolSet(sProto);
    }
    return *this;
}




// -------------------------
// --- Private Functions ---
// -------------------------

/** */
void Url::assign ( 
      const std::string& sUrl			///< [in]
    , bool bAssumeRelativeLink
)
{
	using namespace std;
    using boost::format;
	namespace fs = boost::filesystem;

    m_sRawUrl               = sUrl;
    m_sProtocol             = "";
    m_Domain                = string_vec_t();
    m_subDir                = boost::filesystem::path();
    m_sLeaf                 = "";
    m_bIsFile               = false;

	if ( sUrl.empty() ) return;
	
	////std::cout << boost::format ("Url::assign(%1%)\n") % sUrl;
	
	bool bMoreToParse;
	std::string sDomain;
	 
	string::size_type iCurPos = 0;
	m_sProtocol		= parse_protocol(sUrl, iCurPos);
	bMoreToParse	= parse_advance( sUrl, m_sProtocol, iCurPos );
	
    bool bDoParseDomainAndSubdir = hasProtocol() || !bAssumeRelativeLink;

    if ( bDoParseDomainAndSubdir && bMoreToParse ) {
        sDomain	= parse_domain(sUrl, iCurPos);
        bMoreToParse	= parse_advance( sUrl, sDomain, iCurPos );
    }

    if ( bDoParseDomainAndSubdir && bMoreToParse ) {
        m_subDir = fs::path(parse_subdir(sUrl, iCurPos));
        bMoreToParse	= parse_advance( sUrl, m_subDir.string(), iCurPos );
    }

    if (bMoreToParse) {
        m_sLeaf = parse_leaf(sUrl, iCurPos);
    }


////	//printf("bMoreToParse: %d\n", bMoreToParse );
////	if (bMoreToParse) sParameters	= parse_parameters(sUrl, iCurPos);
////	bMoreToParse	= parse_advance( sUrl, sParameters, iCurPos );
////	if (bMoreToParse) m_sHash		= parse_hash(sUrl, iCurPos);
	
	
	// Split domain and parameters into parts
	split_domain( sDomain, m_Domain);
    //	split_parameters( sParameters, m_Parameters );
    m_bIsFile = false;
    if ( m_sProtocol == "file"
      //   ||  (sDomain == "" && ( m_Path.leaf() == "/" || m_Path.leaf() == "." || m_Path.leaf() == ".." ) )
        )
    {
        m_bIsFile = true;
    }
//    if ( !has_protocol() ) {
//        std::string sProto =  m_bIsFile ? "file" : "http";
//        protocolSet(sProto);
//    }
}




// ----------------------
// --- Friend Functions ---
// ----------------------


/** Equal comparision.
\return True if URLs are equal. */
bool operator==	(const Url& lhs, const Url& rhs)
{
	return	( lhs.m_sProtocol	== rhs.m_sProtocol	) &&
			( lhs.m_Domain		== rhs.m_Domain		) &&
            ( lhs.m_subDir		== rhs.m_subDir		) &&
            ( lhs.m_sLeaf       == rhs.m_sLeaf      ) &&
			( lhs.m_bIsFile		== rhs.m_bIsFile	);		
}

// ----------------------
// --- Free Functions ---
// ----------------------

/**
Typically used to add
domain and subdir parts to an url that only has the filename/leaf part with parametets ect. I.e.
making a relative link on a page complete/absolute.
\example
\endexample
*/
Url linkComplete  ( const Url& owningPageUrl, const std::string& link )
{
    using namespace boost::algorithm;
    Url u(link);
    if ( !u.hasProtocol() ) {
        string s = owningPageUrl.protocolCompose();
        s.append( owningPageUrl.domainCompose() );
        if ( !boost::algorithm::starts_with(link, "/") ) {
            s.append(owningPageUrl.subdirCompose() );
        }
        if ( starts_with(link,  "#") ) {
            string::size_type iPos = s.find('#');
            if ( iPos != string::npos ) {
                s = s.substr(0, iPos );
                printf("s: %s\n", s.c_str());
            }
        }

        s.append( link );
        ////printf("ML: linkComplete: %s\n", s.c_str() );
        u = Url(s);
    }
    return u;
}


std::string linkComplete  ( const std::string& owningPageUrl, const std::string& link )
{
    return linkComplete( Url(owningPageUrl), link ).string();
}

std::string ensureProtocol( const std::string& url )
{
    Url u(url);
    u.makeDefaultProtocol();
    return u.string();
}


/** '<<' operator, Write Url to stream. 
	\return Reference to (modified) ostream. */
std::ostream&	operator <<(std::ostream& os,		///< [out] Output stream to write to.
							const Url& Url)			///< [in] Url to write.
{
	os << Url.string();
	return os;
}


} // END namespace crawl


// --- OLD Stuff ---
///// Get paramters as a string
//std::string	Url::parameters_as_string() const
//{
//	std::string sParameters("");
//	if ( m_Parameters.size() > 0 ) sParameters.append(1, '?');
//	for ( parameter_vec_t::const_iterator it = m_Parameters.begin(); it != m_Parameters.end(); ++it ) {
//		sParameters.append(it->string());
//		if ( it < m_Parameters.end() -1) sParameters.append(1, '&');
//	}
//	return sParameters;
//}
///** Set parameters */
//void Url::parameters ( const std::string& sParameters )
//{
//	split_parameters( sParameters, m_Parameters );
//}
