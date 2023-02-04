#ifndef _CRAWL_NETWORK_ACTIVITY_LOGGER_H_
#define _CRAWL_NETWORK_ACTIVITY_LOGGER_H_

#include <deque>
#include <QString>
#include <dom_constants.h>

namespace crawl {

/** 

*/
class NetworkActivityLogger
{
public:

    // ----------------
    // --- Typedefs ---
    // ----------------
    struct Entry
    {
        Entry() = default;
        Entry(const QString& url, NetworkOperationType networkOpType) : m_url(url), m_networkOpType(networkOpType) {}
        QString                 m_url;
        NetworkOperationType    m_networkOpType;

    };

    // ------------------------------------
    // --- Constructor / Init Functions ---
    // ------------------------------------
    NetworkActivityLogger();
	
    // ----------------------------
    // --- Inline Get Functions ---
    // ----------------------------
    size_t					size            () const   { return m_logDeque.size(); }

    // ----------------------------------
    // --- Convenience Info Functions ---
    // ----------------------------------
    bool					empty           () const    {return m_logDeque.empty();	}
	
    // -------------------------
    // --- Element Functions ---
    // -------------------------
    int                     locate          (const QString& url) const;
    int                     updateEntry     (const QString& url, NetworkOperationType networkOpType);
    void					pushFront       (const Entry& entry);
    void					pushFront       (const QString& url, NetworkOperationType networkOpType);

    const Entry&            front           () const;
    const Entry&            operator[]      (size_t index) const;
    Entry&                  operator[]      (size_t index);

    void					reset           ();
    void					clearQueue      ();

    size_t maxLogSize() const;
    void maxLogSizeSet(const size_t& maxLogSize);

private:
    typedef	std::deque<Entry>			EntryDeqT;
    // -------------------------
    // --- Private Functions ---
    // -------------------------
    // -------------------
    // --- Member Data ---
    // -------------------
    size_t                  m_maxLogSize = 10000;
    EntryDeqT				m_logDeque;

};


} // END namespace crawl

#endif //_CRAWL_NETWORK_ACTIVITY_LOGGER_H_
