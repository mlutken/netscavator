#include "StringFinder.h"
#include <iostream>

namespace crawl {

StringFinder::StringFinder (const std::string& sSearchIn )
    : m_searchIn       (sSearchIn)
    , m_itSubStrBegin   (m_searchIn.begin())
    , m_itSubStrEnd     (m_searchIn.end())
{
}

void StringFinder::newSearch ()
{
    m_itSubStrBegin	= m_searchIn.begin();
    m_itSubStrEnd	= m_searchIn.end();
}

void StringFinder::nextSearch()
{
    m_itSubStrBegin	= m_itSubStrEnd;
    m_itSubStrEnd = m_searchIn.end();
}


/** Trimmed version of current value */
const std::string StringFinder::currentValue () const
{
    return boost::algorithm::trim_copy(currentValueRaw());
}

const std::string StringFinder::currentValueRaw () const
{
    return std::string(m_itSubStrBegin, m_itSubStrEnd);
}

bool StringFinder::findBegin(int iCount, const std::string& sPattern, StringFinder::EMatchPos setBeginToPos)
{
    newSearch();
    return findBeginNext(iCount, sPattern, setBeginToPos);
}

bool StringFinder::findEnd(int iCount, const std::string& sPattern, StringFinder::EMatchPos setEndToPos)
{
    newSearch();
    return findEndNext(iCount, sPattern, setEndToPos);
}

bool StringFinder::findBegin(const std::string& sPattern, StringFinder::EMatchPos setBeginToPos)
{
    newSearch();
    return findBeginNext(sPattern, setBeginToPos);
}

bool StringFinder::findEnd(const std::string& sPattern, StringFinder::EMatchPos setEndToPos)
{
    newSearch();
    return findEndNext(sPattern, setEndToPos);
}


/** */
bool StringFinder::findBeginNext (
        int iCount, 						///< [in]
        const std::string& 	sPattern, 		///< [in]
        EMatchPos 			setBeginToPos	///< [in] Update 'Begin' marker to first or last position in match.
        )
{
    using namespace boost;
    if (iCount ==0)	return false;
    StringRangeConstT itRangeResult( m_itSubStrBegin,	m_itSubStrBegin );	// Initialize result range to empty
    StringFindConstIteratorT it = getFinderIterator(sPattern);

    if (iCount < 0) { // Search from end of string
        std::vector<StringRangeConstT> v; v.reserve(8);
        for ( ; it!=StringFindConstIteratorT(); ++it) {
            v.push_back(*it);
        }
        const auto intSize = static_cast<int>(v.size());
        const auto pos = intSize - -iCount;
        if (0 <= pos && pos < intSize) {
            itRangeResult = v[static_cast<size_t>(pos)];
            iCount = 0; // Found!
        }
    }
    else { // Normal forward search
        for ( ; it!=StringFindConstIteratorT(); ++it) {
            itRangeResult = *it;
            if ( --iCount == 0 ) break;
        }
    }

    bool bFound = ( iCount == 0 ) && itRangeResult ;			// itRange is convertible to bool. True if a match was found
    if ( bFound ) {
        // Assign 'begin' in case we found a match
        if ( setBeginToPos == MATCH_FIRST ) m_itSubStrBegin = itRangeResult.begin();
        else								m_itSubStrBegin = itRangeResult.end();
    }
    return bFound;		// itRange is convertible to bool. True if a match was found
}


/** */
bool StringFinder::findEndNext (
        int iCount, 						///< [in]
        const std::string& 	sPattern, 		///< [in]
        EMatchPos  			setEndToPos		///< [in] Update 'End' marker to first or last position in match.
        )
{
    using namespace boost;
    if (iCount ==0)	return false;
    StringRangeConstT itRangeResult( m_itSubStrBegin,	m_itSubStrBegin );	// Initialize result range to empty
    StringFindConstIteratorT it = getFinderIterator(sPattern);

    if (iCount < 0) { // Search from end of string
        std::vector<StringRangeConstT> v; v.reserve(8);
        for ( ; it!=StringFindConstIteratorT(); ++it) {
            v.push_back(*it);
        }
        const auto intSize = static_cast<int>(v.size());
        const auto pos = intSize - -iCount;
        if (0 <= pos && pos < intSize) {
            itRangeResult = v[static_cast<size_t>(pos)];
            iCount = 0; // Found!
        }
    }
    else { // Normal forward search
        for ( ; it!=StringFindConstIteratorT(); ++it) {
            itRangeResult = *it;
            if ( --iCount == 0 ) break;
        }
    }

    bool bFound = ( iCount == 0 ) && itRangeResult ;			// itRange is convertible to bool. True if a match was found
    if ( bFound ) {
        // Assign 'end' in case we found a match
        if ( setEndToPos == MATCH_FIRST )	m_itSubStrEnd = itRangeResult.begin();
        else								m_itSubStrEnd = itRangeResult.end();
    }
    return bFound;		// itRange is convertible to bool. True if a match was found
}

/** */
bool StringFinder::findBeginNext (
        const std::string& 	sPattern, 		///< [in]
        EMatchPos 			setBeginToPos	///< [in] Update 'Begin' marker to first or last position in match.
        )
{
    return findBeginNext( 1, sPattern, setBeginToPos );
}


/** */
bool StringFinder::findEndNext (
        const std::string& 	sPattern, 		///< [in]
        EMatchPos  			setEndToPos		///< [in] Update 'End' marker to first or last position in match.
        )
{
    return findEndNext( 1, sPattern, setEndToPos );
}

std::string StringFinder::findBetween ( const std::string& sBegin, const std::string& sEnd )
{
    return findBetween(1, sBegin, sEnd);
}

std::vector<std::string_view> StringFinder::findBetweenAll ( const std::string&, const std::string&)
{
    std::vector<std::string_view> all;

    return all;
}

std::string StringFinder::findBetween(int iCount, const std::string& sBegin, const std::string& sEnd)
{
    newSearch();
    bool foundBegin = true;
    bool foundEnd = true;

    if ( sBegin  != "" )  {
        foundBegin = findBeginNext(iCount, sBegin);
    }
    if (sEnd != "" ) {
        foundEnd = findEndNext(1, sEnd);
    }

    if (!foundBegin || !foundEnd) {
        setCurrentValueToEmptyString();
    }

    return currentValue();
}

bool StringFinder::ignoreCase() const
{
    return m_ignoreCase;
}

void StringFinder::ignoreCaseSet(bool ignoreCase)
{
    m_ignoreCase = ignoreCase;
}

std::string StringFinder::searchIn() const
{
    return m_searchIn;
}

StringFinder::StringFindConstIteratorT StringFinder::getFinderIterator(const std::string& sPattern) const
{
    StringFindConstIteratorT it;
    StringRangeConstT itRangeSearch(m_itSubStrBegin, m_itSubStrEnd);
    if (m_ignoreCase)
        it= make_find_iterator( itRangeSearch, first_finder(sPattern, boost::algorithm::is_iequal()));
    else
        it= make_find_iterator( itRangeSearch, first_finder(sPattern, boost::algorithm::is_equal()));
    return it;
}

void StringFinder::setCurrentValueToEmptyString()
{
    m_itSubStrBegin	= m_searchIn.end();
    m_itSubStrEnd	= m_searchIn.end();
}

} // END namespace crawl
