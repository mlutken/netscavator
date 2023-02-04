#ifndef INTERFACES_BOX_OBJECT_IF_H
#define INTERFACES_BOX_OBJECT_IF_H

#include <string>
#include <vector>
#include <boost/shared_ptr.hpp>
#include <boost/cstdint.hpp>


namespace crawl {
    class DomNodeIF;

    class BoxObjectIF {
    public:

        BoxObjectIF(
                boost::shared_ptr<DomNodeIF> pOwningNode
                , boost::int32_t x
                , boost::int32_t y
                , boost::int32_t w
                , boost::int32_t h
                , boost::int32_t scrX
                , boost::int32_t scrY
                );

        boost::int32_t    x         () const { return m_iX; }
        boost::int32_t    y         () const { return m_iY; }
        boost::int32_t    w         () const { return m_iW; }
        boost::int32_t    h         () const { return m_iH; }
        boost::int32_t    screenX   () const { return m_iScreenX; }
        boost::int32_t    screenY   () const { return m_iScreenY; }
    private:
        boost::shared_ptr<DomNodeIF>      m_pOwningNode;
        boost::int32_t    m_iX;
        boost::int32_t    m_iY;
        boost::int32_t    m_iW;
        boost::int32_t    m_iH;
        boost::int32_t    m_iScreenX;
        boost::int32_t    m_iScreenY;
    };

} // END namespace crawl


#endif /* INTERFACES_BOX_OBJECT_IF_H */
