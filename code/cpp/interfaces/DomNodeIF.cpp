#include "DomNodeIF.h"
#include "BoxObjectIF.h"
#include "WebBrowserIF.h"
#include <boost/algorithm/string.hpp>

namespace crawl {


//    bool DomNodeIF::mouseEvent (
//            std::string const& 			sEventNames	///< [in] Event names ( comma separated ) to dispatch
//            , boost::int32_t 			iDetail		///< [in] Detail argument from W3C DOM spec.
//            , boost::uint32_t 			iButton		///< [in] Button ( left=0, middle/wheel=1, right=2 )
//            ) const
//    {
//        return do_mouseEvent(sEventNames, iDetail, iButton);
//    }


    // ------------------------------------
    // --- PUBLIC: Structural functions ---
    // ------------------------------------
    boost::shared_ptr<LinearDomIF> DomNodeIF::ownerLinearDom      () const
    {
        return m_pOwnerBrowser->currentLinearDom();
    }

    boost::shared_ptr<DomNodeIF> DomNodeIF::parentNode(int iLevelsUp) const
    {
        if ( iLevelsUp < 1 ) iLevelsUp = 1;
        boost::shared_ptr<DomNodeIF> parent = immediateParentNode();
        if (iLevelsUp == 1)
            return parent;

        --iLevelsUp;
        while ( (iLevelsUp > 0) && parent )	{
            parent = parent->immediateParentNode();
            --iLevelsUp;
        }
        if ( iLevelsUp == 0 )
            return parent;

        return boost::shared_ptr<DomNodeIF>();
    }

    // -----------------------------------
    // --- PUBLIC: Attribute functions ---
    // -----------------------------------
//    std::string DomNodeIF::classGet () const
//    {
//        return attributeGet("class");
//    }

//    void DomNodeIF::classSet ( const std::string& sClassName )
//    {
//        attributeSet("class", sClassName );
//    }


//    /// Add class
//    void DomNodeIF::classAdd( const std::string& sClassName )
//    {
//        classSet( classGet() + " " + sClassName );
//    }

//    /// Remove class
//    void DomNodeIF::classRemove( const std::string& sClassName )
//    {
//        std::string sClass = boost::algorithm::erase_all_copy( classGet(), sClassName );
//        classSet( boost::algorithm::trim_copy( sClass ) );
//    }

    std::string DomNodeIF::stringDataUTF8() const
    {
        if (m_stringDataUTF8Cached == "")
            m_stringDataUTF8Cached = do_stringDataUTF8Get();
        return m_stringDataUTF8Cached;
    }

    // -----------------------------
    // --- PUBLIC: Node actions ---
    // -----------------------------

//    bool DomNodeIF::inputSet ( const std::string& sValue ) const
//    {
//        std::string sVal = boost::algorithm::replace_all_copy(sValue, "'", "\\'");
//        return do_inputSet(sVal );
//    }

//    std::string DomNodeIF::innerHtml() const
//    {
//        return do_innerHtml();
//    }

//    bool DomNodeIF::innerHtmlSet(const std::string &sValue) const
//    {
//        return do_innerHtmlSet( sValue );
//    }

//    std::string DomNodeIF::innerText() const
//    {
//        return do_innerText();
//    }

//    bool DomNodeIF::innerTextSet(const std::string &sValue) const
//    {
//        return do_innerTextSet( sValue );
//    }

    boost::shared_ptr<DomNodeIF> DomNodeIF::immediateParentNode() const
    {
        if (!m_immediateParentNode) {
            m_immediateParentNode = do_immediateParentNodeNative();
        }
        return m_immediateParentNode;
    }
    
    void DomNodeIF::setStringDataUTF8Cached(const std::string& stringDataUTF8Cached)
    {
        m_stringDataUTF8Cached = stringDataUTF8Cached;
    }

} // END namespace crawl

