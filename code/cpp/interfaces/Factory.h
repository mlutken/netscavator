#ifndef _INTERFACES_FACTORY_H_
#define _INTERFACES_FACTORY_H_

#include <string>
#include <map>
#include <boost/shared_ptr.hpp>
#include <boost/function.hpp>

namespace crawl {
    class ScriptingClassIF;
    class WebBrowserIF;
    class ScriptMinerIF;

    class Factory {
    public:

        // ------------------------
        // --- PUBLIC: Typedefs ---
        // ------------------------
        typedef boost::function< ScriptingClassIF*  ( const std::string& ) >	ScriptingClassCreateFunT;
        typedef boost::function< WebBrowserIF*      ( const std::string& ) >	WebBrowserCreateFunT;
        typedef boost::function< ScriptMinerIF*     ( const std::string& ) >	ScriptMinerCreateFunT;


        // ------------------------------------------
        // --- PUBLIC: Constructor/Init functions ---
        // ------------------------------------------
        Factory();

        // ---------------------------------
        // --- PUBLIC: Creator functions ---
        // ---------------------------------

        // ----------------------------------------
        // --- PUBLIC: Add to factory functions ---
        // ----------------------------------------
        void    addScriptingClass   ( const std::string& sName, ScriptingClassCreateFunT createFun );
        void    addWebBrowser       ( const std::string& sName, WebBrowserCreateFunT createFun );
        void    addScriptMiner      ( const std::string& sName, ScriptMinerCreateFunT createFun );

        //        boost::int32_t    x         () const { return m_iX; }
        //        boost::int32_t    y         () const { return m_iY; }
        //        boost::int32_t    screenX   () const { return m_iScreenX; }
        //        boost::int32_t    screenY   () const { return m_iScreenY; }
    private:
        //        boost::int32_t    m_iX;
        //        boost::int32_t    m_iY;
        //        boost::int32_t    m_iScreenX;
        //        boost::int32_t    m_iScreenY;


    };

} // END namespace crawl


#endif /* _INTERFACES_FACTORY_H_ */
