#ifndef _CRAWL_DOM_EVENT_IF_H_
#define _CRAWL_DOM_EVENT_IF_H_


#include <string>
#include <boost/cstdint.hpp>
#include <boost/shared_ptr.hpp>

namespace crawl {


    class DomEventIF
    {
    public:
        DomEventIF();
        DomEventIF( std::string type, bool canBubble, bool cancelable );
        virtual ~DomEventIF() {}

        std::string         type        () const {	return do_type();       }
        bool                canBubble   () const {	return do_canBubble();  }
        bool                cancelable  () const {	return do_cancelable(); }

    private:
        // --- PRIVATE: Virtual Implementation functions ---
        virtual std::string do_type         () const    {	return m_type;      }
        virtual bool        do_canBubble    () const    {	return m_canBubble; }
        virtual bool        do_cancelable   () const    {	return m_cancelable;}

        // --- PRIVATE: Data ---
        std::string             m_type;
        bool                    m_canBubble;
        bool                    m_cancelable;
    };

} // END namespace crawl


#endif //_CRAWL_DOM_EVENT_IF_H_

