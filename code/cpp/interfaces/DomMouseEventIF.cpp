#include "DomMouseEventIF.h"

namespace crawl {

    DomMouseEventIF::DomMouseEventIF(
            boost::uint32_t btn
            , boost::int32_t scrX
            , boost::int32_t scrY
            , boost::int32_t clntX
            , boost::int32_t clntY
            )
                : DomEventIF()
                , m_button(btn)
                , m_screenX(scrX)
                , m_screenY(scrY)
                , m_clientX(clntX)
                , m_clientY(clntY)
                , m_altKey(false)
                , m_ctrlKey(false)
                , m_shiftKey(false)
                , m_metaKey(false)
    {
    }

    DomMouseEventIF::DomMouseEventIF(
            boost::uint32_t btn
            , boost::int32_t scrX
            , boost::int32_t scrY
            , boost::int32_t clntX
            , boost::int32_t clntY
            , bool alt
            , bool ctrl
            , bool shift
            , bool meta
            )
                : DomEventIF()
                , m_button(btn)
                , m_screenX(scrX)
                , m_screenY(scrY)
                , m_clientX(clntX)
                , m_clientY(clntY)
                , m_altKey(alt)
                , m_ctrlKey(ctrl)
                , m_shiftKey(shift)
                , m_metaKey(meta)
    {
    }


} // END namespace crawl


