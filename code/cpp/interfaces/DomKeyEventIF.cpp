#include "DomKeyEventIF.h"

namespace crawl {

    DomKeyEventIF::DomKeyEventIF(
            boost::uint32_t chCode
            , boost::uint32_t kCode
            )
                : DomEventIF()
                , m_charCode(chCode)
                , m_keyCode(kCode)
                , m_altKey(false)
                , m_ctrlKey(false)
                , m_shiftKey(false)
                , m_metaKey(false)
    {
    }

    DomKeyEventIF::DomKeyEventIF(
            boost::uint32_t chCode
            , boost::uint32_t kCode
            , bool alt
            , bool ctrl
            , bool shift
            , bool meta
            )
                : DomEventIF()
                , m_charCode(chCode)
                , m_keyCode(kCode)
                , m_altKey(alt)
                , m_ctrlKey(ctrl)
                , m_shiftKey(shift)
                , m_metaKey(meta)
    {
    }


} // END namespace crawl


