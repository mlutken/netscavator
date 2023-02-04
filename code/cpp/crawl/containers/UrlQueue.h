#ifndef _CRAWL_URL_QUEUE_H_
#define _CRAWL_URL_QUEUE_H_

#include <deque>
#include <set>
#include <string>
#include <boost/shared_ptr.hpp>

#include <url/url_functions.h>
#include <ScriptMinerIF.h>


namespace crawl {

/** 

XXX Brief description XXX.
XXX Detailed description here ... XXX
\author Veriquin */
class UrlQueue 
{
public:

    // ----------------
    // --- Typedefs ---
    // ----------------
    // ------------------------------------
    // --- Constructor / Init Functions ---
    // ------------------------------------
    UrlQueue( bool bUnique,  ScriptMinerIF* pMiner );
	
    // ----------------------------
    // --- Inline Get Functions ---
    // ----------------------------
    size_t					size            () const   { return m_urlQueue.size(); 		}
    size_t					sizeProcessed   () const   { return m_processedUrls.size(); 	}

    // ----------------------------------
    // --- Convenience Info Functions ---
    // ----------------------------------
    bool					empty               () const    {	return size() == 0;				}
    bool                    inQueue             ( const std::string& sUrl ) const;
    bool                    alreadyProcessed    ( const std::string& sUrl ) const;

	
    // -------------------------
    // --- Element Functions ---
    // -------------------------
    void					popFront        ();
    void					pushBack        ( const std::string& sUrl, bool bForceUnique, bool updateQueueFile );
    void					pushFront       ( const std::string& sUrl, bool bForceUnique = false );
    void					pushBackUrl     ( const Url& url, bool bForceUnique, bool updateQueueFile );
    void					append          ( const UrlVecT& Urls, bool bForceUnique = false );
    void					append          ( const string_vec_t& urls, bool bForceUnique = false );
    void					assign          ( const string_vec_t& urls, bool bForceUnique = false );

    const Url&				front           () const;
    const Url&				at              (size_t index) const { return m_urlQueue.at(index); }

    void					reset           ( bool bUnique );
    void					clearQueue      ();

    void					clearProcessed  () { m_processedUrls.clear(); 	}
	
    // ----------------------
    // --- Misc Functions ---
    // ----------------------
    void					writeQueueToFile () const ;

    // -----------------------
    // --- Debug Functions ---
    // -----------------------
    void					debugPrintQueue () const;


private:
	typedef	std::deque<Url>				UrlDeqT;
	typedef	std::set<std::string>		UrlStringSetT;
    // -------------------------
    // --- Private Functions ---
    // -------------------------
    bool					frontProcessed      () const ;


    // -------------------
    // --- Member Data ---
    // -------------------
    bool					m_bUnique;			///< true if only one of each URL is allowed in the queue
    ScriptMinerIF*          m_pMiner;
    UrlDeqT					m_urlQueue;
	UrlStringSetT			m_processedUrls;
	Url						m_emptyUrl;
    mutable unsigned        m_write_url_queue_to_disk_counter = 0;
    unsigned                m_write_url_queue_to_disk_modulus = 10;
};


} // END namespace crawl

#endif //_CRAWL_URL_QUEUE_H_

