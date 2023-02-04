#include "BoxObjectIF.h"

namespace crawl {

    BoxObjectIF::BoxObjectIF(
            boost::shared_ptr<DomNodeIF> pOwningNode
            , boost::int32_t x
            , boost::int32_t y
            , boost::int32_t w
            , boost::int32_t h
            , boost::int32_t scrX
            , boost::int32_t scrY
            )
                : m_pOwningNode(pOwningNode)
                , m_iX(x)
                , m_iY(y)
                , m_iW(w)
                , m_iH(h)
                , m_iScreenX(scrX)
                , m_iScreenY(scrY)
    {
    }


} // END namespace crawl


