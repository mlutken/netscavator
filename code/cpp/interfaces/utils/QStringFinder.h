#ifndef Q_STRING_FINDER_H_
#define Q_STRING_FINDER_H_

#include <QString>

namespace crawl {


/** String finder class which is meant to take over the misplaced implementation of the same
    functions found in StringSearch class.
    \todo Copy/implement rest of needed functions from StringSearch
*/
class QStringFinder
{
public:
    enum 	EMatchPos { MATCH_FIRST = 0, MATCH_LAST = 1	};
    // ----------------
    // --- Typedefs ---
    // ----------------

    // -----------------------------------
    // --- Constructors/init functions ---
    // -----------------------------------

    explicit QStringFinder ( const char* searchIn );
    explicit QStringFinder (const QString& searchIn );

    void                newSearch               ();
    void                nextSearch              ();
    const QString       currentValue            () const;
    const QString       currentValueRaw         () const;

    // --- Finder 'from start' functions ---
//  bool                findBegin               (int iCount, const QString& pattern, EMatchPos setBeginToPos = MATCH_LAST);
//  bool                findEnd                 (int iCount, const QString& pattern, EMatchPos setEndToPos   = MATCH_FIRST);
    bool                findBegin               (const QString& pattern, EMatchPos setBeginToPos = MATCH_LAST);
    bool                findEnd                 (const QString& pattern, EMatchPos setEndToPos   = MATCH_FIRST);

    // --- Finder 'next' functions ---
//  bool                findBeginNext           (int iCount, const QString& pattern, EMatchPos setBeginToPos = MATCH_LAST);
//  bool                findEndNext             (int iCount, const QString& pattern, EMatchPos setEndToPos   = MATCH_FIRST);
    bool                findBeginNext           (const QString& pattern, EMatchPos setBeginToPos = MATCH_LAST);
    bool                findEndNext             (const QString& pattern, EMatchPos setEndToPos   = MATCH_FIRST);

    const QString       findBetween             (const QString& beginPattern, const QString& endPattern);
    bool                ignoreCase              () const;
    void                ignoreCaseSet           (bool ignoreCase);

    const QString&      searchIn                () const;

    int                 rangeBegin              () const;
    void                rangeBeginSet           (int rangeBegin);

    int                 rangeEnd                () const;
    void                rangeEndSet             (int rangeEnd);
    int                 size                    () const { return m_searchIn.size(); }

private:
    QString             m_searchIn;
    mutable int         m_rangeBegin;
    mutable int         m_rangeEnd;
    bool                m_ignoreCase = false;
};

} // END namespace crawl

#endif // Q_STRING_FINDER_H_
