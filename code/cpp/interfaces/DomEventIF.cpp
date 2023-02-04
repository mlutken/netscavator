#include "DomEventIF.h"

namespace crawl {

    DomEventIF::DomEventIF()
                : m_type("")
                , m_canBubble(true)
                , m_cancelable(true)
    {
    }

    DomEventIF::DomEventIF(
            std::string type
            , bool canBubble
            , bool cancelable
            )
                : m_type(type)
                , m_canBubble(canBubble)
                , m_cancelable(cancelable)

    {
    }



} // END namespace crawl


