#include "QStringFinder.h"
#include <iostream>

namespace crawl {

QStringFinder::QStringFinder(const char* searchIn)
    : m_searchIn     (QString::fromUtf8(searchIn))
    , m_rangeBegin   (0)
    , m_rangeEnd     (m_searchIn.length())
{

}

QStringFinder::QStringFinder (const QString& searchIn )
    : m_searchIn     (searchIn)
    , m_rangeBegin   (0)
    , m_rangeEnd     (m_searchIn.length())
{
}

void QStringFinder::newSearch ()
{
    m_rangeBegin = 0;
    m_rangeEnd	 = m_searchIn.length();
}

void QStringFinder::nextSearch()
{
    m_rangeBegin = m_rangeEnd;
    m_rangeEnd   = m_searchIn.length();
}


/** Trimmed version of current value */
const QString QStringFinder::currentValue () const
{
    return currentValueRaw().trimmed();
}

const QString QStringFinder::currentValueRaw () const
{
    return m_searchIn.mid(m_rangeBegin, m_rangeEnd - m_rangeBegin);
}

bool QStringFinder::findBegin(const QString& pattern, QStringFinder::EMatchPos setBeginToPos)
{
    newSearch();
    return findBeginNext(pattern, setBeginToPos);
}

bool QStringFinder::findEnd(const QString& pattern, QStringFinder::EMatchPos setEndToPos)
{
    newSearch();
    return findEndNext(pattern, setEndToPos);
}


/** */
bool QStringFinder::findBeginNext (
        const QString& 	pattern, 		///< [in]
        EMatchPos 		setBeginToPos	///< [in] Update 'Begin' marker to first or last position in match.
        )
{
    const Qt::CaseSensitivity cs = m_ignoreCase ? Qt::CaseInsensitive : Qt::CaseSensitive;
    const auto idx = m_searchIn.indexOf(pattern, m_rangeBegin, cs);

    const bool found = idx != -1 && idx < m_rangeEnd;
    if ( found ) {
        // Assign 'begin' in case we found a match
        if ( setBeginToPos == MATCH_FIRST ) m_rangeBegin = idx;
        else								m_rangeBegin = idx + pattern.length();
    }
    return found;
}


/** */
bool QStringFinder::findEndNext (
        const QString& 	pattern, 		///< [in]
        EMatchPos  		setEndToPos		///< [in] Update 'End' marker to first or last position in match.
        )
{
    const Qt::CaseSensitivity cs = m_ignoreCase ? Qt::CaseInsensitive : Qt::CaseSensitive;
    const auto idx = m_searchIn.indexOf(pattern, m_rangeBegin, cs);

    const bool found = idx != -1 && idx < m_rangeEnd;
    if ( found ) {
        // Assign 'end' in case we found a match
        if ( setEndToPos == MATCH_FIRST ) m_rangeEnd = idx;
        else							  m_rangeEnd = idx + pattern.length();
    }
    return found;
}


const QString QStringFinder::findBetween ( const QString& beginPattern, const QString& endPattern )
{
   newSearch();
   if ( beginPattern  != "" ) findBeginNext(beginPattern);
   if ( endPattern    != "" ) findEndNext(endPattern);
   return currentValue();
}

bool QStringFinder::ignoreCase() const
{
    return m_ignoreCase;
}

void QStringFinder::ignoreCaseSet(bool ignoreCase)
{
    m_ignoreCase = ignoreCase;
}

const QString& QStringFinder::searchIn() const
{
    return m_searchIn;
}

int QStringFinder::rangeBegin() const
{
    return m_rangeBegin;
}

void QStringFinder::rangeBeginSet(int rangeBegin)
{
    m_rangeBegin = rangeBegin;
}

int QStringFinder::rangeEnd() const
{
    return m_rangeEnd;
}

void QStringFinder::rangeEndSet(int rangeEnd)
{
    m_rangeEnd = rangeEnd;
}


} // END namespace crawl
