#include "NetworkActivityLogger.h"

#include <iostream> 
 
using namespace std;

namespace crawl {

// ------------------------------------
// --- Static member initialization ---
// ------------------------------------


// ------------------------------------
// --- Constructor / Init Functions ---
// ------------------------------------
NetworkActivityLogger::NetworkActivityLogger()
{
}

// ----------------------------------
// --- Convenience Info Functions ---
// ----------------------------------




// -------------------------
// --- Element Functions ---
// -------------------------

/** Return index of url, -1 if not found.
\return The index of the entry located or -1 if entry (url) was not found. */
int NetworkActivityLogger::locate(const QString& url) const
{
    size_t n = 0;
    const size_t SIZE = m_logDeque.size();
    for ( ; n < SIZE; ++n) {
        if (url == m_logDeque[n].m_url)
            break;
    }
    return n < SIZE ? static_cast<int>(n) : -1;
}

/** Locates the given entry (by url) and updates its NetworkOperationType.
\return The index of the entry update or -1 if entry (url) was not found. */
int NetworkActivityLogger::updateEntry(const QString& url, NetworkOperationType networkOpType)
{
    const int n = locate(url);
    if (n != -1)
        m_logDeque[static_cast<size_t>(n)].m_networkOpType = networkOpType;
    return n;
}

void NetworkActivityLogger::pushFront(const NetworkActivityLogger::Entry& entry)
{
    m_logDeque.push_front(entry);
    if (m_logDeque.size() > m_maxLogSize)
        m_logDeque.pop_back();
}

void NetworkActivityLogger::pushFront(const QString& url, NetworkOperationType networkOpType)
{
    m_logDeque.push_front(Entry(url, networkOpType));
}


const NetworkActivityLogger::Entry& NetworkActivityLogger::front()	const
{ 
    return m_logDeque.front();
}

const NetworkActivityLogger::Entry& NetworkActivityLogger::operator[](size_t index) const
{
    return m_logDeque[index];
}

NetworkActivityLogger::Entry& NetworkActivityLogger::operator[](size_t index)
{
    return m_logDeque[index];
}


void NetworkActivityLogger::reset()
{
    clearQueue();
}

void NetworkActivityLogger::clearQueue  ()
{
    m_logDeque.clear();
}

size_t NetworkActivityLogger::maxLogSize() const
{
    return m_maxLogSize;
}

void NetworkActivityLogger::maxLogSizeSet(const size_t& maxLogSize)
{
    m_maxLogSize = maxLogSize;
}




// ----------------------
// --- Free Functions ---
// ----------------------



} // END namespace crawl


