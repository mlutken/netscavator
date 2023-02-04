#ifndef _URL_GETTER_H_
#define _URL_GETTER_H_
#include <url/Url.h>


class UrlGetter {
public:
    enum {
          LINK_TYPE_LOCAL       = 1 << 0
        , LINK_TYPE_EXTERNAL    = 1 << 1
        , LINK_TYPE_ALL         = 3
        };

    UrlGetter ();
    UrlGetter ( int iLinkType, const std::string& sUrlsMatch="", const std::string& sIdCompFun = "equals" );
    ~UrlGetter();
    int				count					();
    bool			getNext					();
    void			resetCurrent			( int iNewCurrent = 0 );

    bool			currentAtEnd			();
    std::string		current					() const;
    std::string		current_raw				();
    std::string		currentProtocol			();

//    std::string		currentPath				();
//    std::string		currentParameters		();
//    std::string		currentDomain			();
//    std::string		currentTopDomain		();
//    std::string		currentSecondLevelDomain();
//    std::string		currentSubDomains		();
//    std::string		currentSiteDomain		();

private:
    crawl::UrlVecT::size_type	m_iCurrent;
    crawl::UrlVecT				m_Urls;
};

//	UrlGetter( double  iX, double iY, double iZ );

#endif //_URL_GETTER_H_


