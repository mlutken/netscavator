#include "UrlQueue.h"

#include <stdio.h>
#include <algorithm>
#include <iostream> 

#include <boost/format.hpp> 
#include <boost/lambda/lambda.hpp>
#include <boost/lambda/bind.hpp>
#include <boost/bind.hpp>


#include <cpaf_compression_functions.h>
#include <Configuration.h>
#include <utils/string_algorithms.h>

using namespace std;

namespace crawl {

// ------------------------------------
// --- Static member initialization ---
// ------------------------------------


// ------------------------------------
// --- Constructor / Init Functions ---
// ------------------------------------
UrlQueue::UrlQueue( bool bUnique, ScriptMinerIF* pMiner )
    :	m_bUnique   ( bUnique   )
    ,   m_pMiner    ( pMiner    )
    ,   m_emptyUrl  ( ""        )
{
    writeQueueToFile();
}


// ----------------------------------
// --- Convenience Info Functions ---
// ----------------------------------
bool UrlQueue::inQueue (
    const std::string& sUrl
    ) const
{
    return std::find( m_urlQueue.begin(), m_urlQueue.end(), sUrl) != m_urlQueue.end();
}

bool UrlQueue::alreadyProcessed (
    const std::string& sUrl
    ) const
{
    return m_processedUrls.find ( sUrl ) != m_processedUrls.end();
}

// -------------------------
// --- Element Functions ---
// -------------------------

void UrlQueue::popFront()						
{ 
	m_processedUrls.insert( front().string() );
	m_urlQueue.pop_front(); 
	while ( m_bUnique && !m_urlQueue.empty() && frontProcessed() ) {
		m_urlQueue.pop_front(); 
	}
    writeQueueToFile();
}


void UrlQueue::pushBack( const std::string& sUrl, bool bForceUnique, bool updateQueueFile )
{
	bool bAddUrl = true;
    if ( sUrl == "" ) bAddUrl = false;
	if ( m_bUnique || bForceUnique ) 
	{
		// If queue is unique we only add Urls that are not already processed or not just added.
        bool bAlreadyProcessed 	= alreadyProcessed ( sUrl );    // Already processed ?
        bool bInQueue           = inQueue( sUrl );              // Already in queue ?
        if ( bAlreadyProcessed || bInQueue )	bAddUrl = false;
	}
    if ( bAddUrl ) {
        m_urlQueue.push_back ( sUrl );
        if (updateQueueFile) {
            writeQueueToFile();
        }
    }
}

void UrlQueue::pushFront( const std::string& sUrl, bool bForceUnique )
{
	bool bAddUrl = true;
    if ( sUrl == "" ) bAddUrl = false;
    if ( m_bUnique || bForceUnique )
	{
		// If queue is unique we only add Urls that are not already processed or not just added.
        bool bAlreadyProcessed 	= alreadyProcessed ( sUrl );    // Already processed ?
        bool bInQueue           = inQueue( sUrl );              // Already in queue ?
        if ( bAlreadyProcessed || bInQueue )	bAddUrl = false;
	}
    if ( bAddUrl ) {
        m_urlQueue.push_front ( sUrl );
        writeQueueToFile();
    }
}


void UrlQueue::pushBackUrl( const Url& url, bool bForceUnique, bool updateQueueFile )
{
    pushBack( url.string(), bForceUnique, updateQueueFile);
}
 
void UrlQueue::append( const UrlVecT& Urls, bool bForceUnique  )
{
	using namespace boost::lambda;
    const bool updateQueueFile = false;
    std::for_each( Urls.begin(), Urls.end(), boost::bind(&UrlQueue::pushBackUrl, this, boost::lambda::_1, bForceUnique, updateQueueFile ) );
    writeQueueToFile();
}

void UrlQueue::append ( const string_vec_t& urls, bool bForceUnique  )
{
    const bool updateQueueFile = false;
    for( const string& s: urls ) {
        auto url = trimDefault_fun(s);
        if (!url.empty())
            pushBackUrl( Url(url), bForceUnique, updateQueueFile );
    }
    writeQueueToFile();
}

void UrlQueue::assign ( const string_vec_t& urls, bool bForceUnique )
{
    clearQueue();
    append( urls, bForceUnique );
    writeQueueToFile();
}



const Url& UrlQueue::front()	const 
{ 
	if ( empty() )	
	{ 
		return m_emptyUrl;
	}
	
	return m_urlQueue.front(); 
}


void UrlQueue::reset(bool bUnique )
{
    m_bUnique = bUnique;
    clearQueue();
    clearProcessed();
}

void UrlQueue::clearQueue  ()
{
    m_urlQueue.clear();
    writeQueueToFile();
}

// ----------------------
// --- Misc Functions ---
// ----------------------
void UrlQueue::writeQueueToFile () const
{
    if (m_write_url_queue_to_disk_counter++ % m_write_url_queue_to_disk_modulus != 0) {
        return;
    }

    if ( !m_pMiner )    return;
    const string sFile = m_pMiner->config()->urlQueueContinueFile();
    vector<string> v;
    UrlDeqT::const_iterator          it      = m_urlQueue.begin();
    const UrlDeqT::const_iterator    itEND   = m_urlQueue.end();
    for ( ; it != itEND; ++it ) {
        v.push_back( it->string() );
    }

    cpaf::compression::gz_writelines( sFile, v );
}


// -----------------------
// --- Debug Functions ---
// -----------------------
void UrlQueue::debugPrintQueue() const
{
    printf("\nURLs in queue: TODO: Implement this!!!\n" );
//	std::for_each( m_urlQueue.begin(), m_urlQueue.end(), std::cout << boost::lambda::_1 << '\n' );
    printf("\n");
}


// -------------------------
// --- Private Functions ---
// -------------------------
bool UrlQueue::frontProcessed() const
{
	return m_processedUrls.find ( front().string() ) != m_processedUrls.end();
}




// ----------------------
// --- Free Functions ---
// ----------------------



} // END namespace crawl


