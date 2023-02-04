#ifndef _STRING_FINDER_H_
#define _STRING_FINDER_H_

#include <string>
#include <functional>
#include <boost/algorithm/string.hpp>

namespace crawl {


/** String finder class which is meant to take over the misplaced implementation of the same
    functions found in StringSearch class.
    \todo Copy/implement rest of needed functions from StringSearch
*/
class StringFinder
{
public:
    enum 	EMatchPos { MATCH_FIRST = 0, MATCH_LAST = 1	};
    // ----------------
    // --- Typedefs ---
    // ----------------
    typedef boost::iterator_range<std::string::iterator>		StringRangeT;
    typedef boost::find_iterator<std::string::iterator> 		StringFindIteratorT;

    typedef boost::iterator_range<std::string::const_iterator>	StringRangeConstT;
    typedef boost::find_iterator<std::string::const_iterator> 	StringFindConstIteratorT;

    // -----------------------------------
    // --- Constructors/init functions ---
    // -----------------------------------

    explicit StringFinder ( const std::string& sSearchIn );

    void                newSearch               ();
    void                nextSearch              ();
    const std::string   currentValue            () const;
    const std::string   currentValueRaw         () const;

    // --- Finder 'from start' functions ---
    bool                findBegin               ( int iCount, const std::string& sPattern, EMatchPos setBeginToPos = MATCH_LAST );
    bool                findEnd                 ( int iCount, const std::string& sPattern, EMatchPos setEndToPos   = MATCH_FIRST );
    bool                findBegin               ( const std::string& sPattern, EMatchPos setBeginToPos = MATCH_LAST );
    bool                findEnd                 ( const std::string& sPattern, EMatchPos setEndToPos   = MATCH_FIRST );

    // --- Finder 'next' functions ---
    bool                findBeginNext           ( int iCount, const std::string& sPattern, EMatchPos setBeginToPos = MATCH_LAST );
    bool                findEndNext             ( int iCount, const std::string& sPattern, EMatchPos setEndToPos   = MATCH_FIRST );
    bool                findBeginNext           ( const std::string& sPattern, EMatchPos setBeginToPos = MATCH_LAST );
    bool                findEndNext             ( const std::string& sPattern, EMatchPos setEndToPos   = MATCH_FIRST );

    std::vector<std::string_view> findBetweenAll( const std::string& sBegin, const std::string& sEnd );
    std::string   findBetween                   ( const std::string& sBegin, const std::string& sEnd );
    std::string   findBetween                   ( int iCount, const std::string& sBegin, const std::string& sEnd );

    bool ignoreCase                             () const;
    void ignoreCaseSet                          (bool ignoreCase);

    std::string searchIn                        () const;
private:
    StringFindConstIteratorT    getFinderIterator (const std::string& sPattern) const;
    void                        setCurrentValueToEmptyString ();

    std::string 							m_searchIn;
    mutable std::string::const_iterator		m_itSubStrBegin;
    mutable std::string::const_iterator		m_itSubStrEnd;
    bool m_ignoreCase = false;

};

} // END namespace crawl

#endif // _STRING_FINDER_H_
