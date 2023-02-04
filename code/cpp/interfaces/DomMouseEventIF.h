#ifndef _CRAWL_DOM_MOUSE_EVENT_IF_H_
#define _CRAWL_DOM_MOUSE_EVENT_IF_H_

#include <boost/cstdint.hpp>
#include <boost/shared_ptr.hpp>
#include "DomEventIF.h"

namespace crawl {

    class DomMouseEventIF : public DomEventIF
    {
    public:

        // --- PUBLIC: Constants ---

        enum { DOM_MOUSE_LEFT   = 1U };

        enum { DOM_MOUSE_MIDDLE = 2U };

        enum { DOM_MOUSE_RIGHT  = 4U };

        DomMouseEventIF(    boost::uint32_t btn, boost::int32_t scrX, boost::int32_t scrY
                        ,   boost::int32_t clntX, boost::int32_t clntY );
        DomMouseEventIF(    boost::uint32_t btn, boost::int32_t scrX, boost::int32_t scrY
                        ,   boost::int32_t clntX, boost::int32_t clntY
                        ,   bool alt, bool ctrl, bool shift, bool meta );
        virtual ~DomMouseEventIF() {}

        boost::uint32_t     button  () const    {	return do_button();     }
        boost::int32_t      screenX () const    {	return do_screenX();    }
        boost::int32_t      screenY () const    {	return do_screenY();    }
        boost::int32_t      clientX () const    {	return do_clientX();    }
        boost::int32_t      clientY () const    {	return do_clientY();    }

        bool                altKey  () const    {	return do_altKey();     }
        bool                ctrlKey () const    {	return do_ctrlKey();    }
        bool                shiftKey() const    {	return do_shiftKey();   }
        bool                metaKey () const    {	return do_metaKey();    }

    private:
        // --- PRIVATE: Virtual Implementation functions ---
        virtual boost::uint32_t     do_button   () const    {	return m_button;     }
        virtual boost::int32_t      do_screenX  () const    {	return m_screenX;    }
        virtual boost::int32_t      do_screenY  () const    {	return m_screenY;    }
        virtual boost::int32_t      do_clientX  () const    {	return m_clientX;    }
        virtual boost::int32_t      do_clientY  () const    {	return m_clientY;    }

        virtual bool                do_altKey   () const    {	return m_altKey;     }
        virtual bool                do_ctrlKey  () const    {	return m_ctrlKey;    }
        virtual bool                do_shiftKey () const    {	return m_shiftKey;   }
        virtual bool                do_metaKey  () const    {	return m_metaKey;    }


        // --- PRIVATE: Data ---
        boost::uint32_t         m_button;
        boost::int32_t          m_screenX;
        boost::int32_t          m_screenY;
        boost::int32_t          m_clientX;
        boost::int32_t          m_clientY;

        bool                    m_altKey;
        bool                    m_ctrlKey;
        bool                    m_shiftKey;
        bool                    m_metaKey;

    };

} // END namespace crawl

#endif // _CRAWL_DOM_MOUSE_EVENT_IF_H_

