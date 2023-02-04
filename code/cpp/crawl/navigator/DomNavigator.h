#ifndef _CRAWL_DOM_NAVIGATOR_H_
#define _CRAWL_DOM_NAVIGATOR_H_

#include <string>
#include <vector>
#include <map>
#include <boost/shared_ptr.hpp>
#include <boost/cstdint.hpp>
#include <cpaf_libs/utils/cpaf_string_utils.hpp>

class ScriptMiner;

namespace crawl {

    class NavigateStateBase;

    class DomNavigator
    {
    public:
        // ------------------------
        // --- PUBLIC: Typedefs ---
        // ------------------------

        // ------------------------------------
        // --- Constructor / Init Functions ---
        // ------------------------------------
        DomNavigator(const ScriptMiner* pScriptMiner);
        void reset();


        // ------------------------------------------
        // --- PUBLIC: Navigator Create functions ---
        // ------------------------------------------
        void        javascriptExecuteCreate ( const std::string& sNavActionName );
        void        urlLoadCreate           ( const std::string& sNavActionName, const std::string& sBaseUrl );
        void        inputOptionsCreate      ( const std::string& sNavActionName );
        void        dropDownSelectCreate    ( const std::string& sNavActionName );
        void        domPosClickCreate       ( const std::string& sNavActionName,
                                              const std::string& sFindNextDomPosSequence );
        void        domClickNextCreate      ( const std::string& sNavActionName,
                                              const std::string& sFindNextDomPosSequence );
        void        autoInputCreate         ( const std::string& sNavActionName, const std::string& sCharsList,
                                              int iMinLength, int iMaxLength );

        void        attributeNamesCreate    ( const std::vector<std::string>& attributeNames);
        void        attributeNamesCreate    ( const std::string& sAttrNames, const std::string& sDelimiter = "," );

        // ------------------------------------------
        // --- PUBLIC: Runtime settings functions ---
        // ------------------------------------------
        void            forceDownloadResources      ( bool bForceDownload );
        void            currentStateIndicesStateSet ( const std::string& sState );
        void            currentStateIndicesStringSet( const std::string& sState );
        std::string     currentStateIndicesStringGet() const;
        void            currentStateIndicesVecSet   ( const cpaf::IntVecT& state );
        cpaf::IntVecT   currentStateIndicesVecGet   () const;
        void            currentStateSet             ( const std::string& sState, const std::string& sDelimiter );
        void            currentStateSet             ( const std::string& sState );
        void            endStateSet                 ( const std::string& sState, const std::string& sDelimiter );
        void            endStateSet                 ( const std::string& sState );

        // -------------------------------------
        // --- PUBLIC: Add Options functions ---
        // -------------------------------------
        void        optionResourceAdd   ( const std::string& sResourcePath, const std::string& sScriptFilterFunction,  bool bForceDownload  );
        void        optionAdd           ( int iCount, const std::string& sValue, const std::string& sSearchFor  );
        void        optionAdd           ( int iCount, const std::string& sValue );
        void        optionAdd           ( const std::string& sValue, const std::string& sSearchFor );
        void        optionAdd           ( const std::string& sValue );
        void        optionAdd           ( int iCount );

        void        optionAdd           ( int iCount, const std::string& sValue, const std::string& sSearchFor,
                                          int attrStart, const std::string& sAttributes, const std::string& sDelimiter = "," );
        void        optionAdd           ( int iCount, const std::string& sValue,
                                          int attrStart, const std::string& sAttributes, const std::string& sDelimiter = "," );
        void        optionAdd           ( const std::string& sValue, const std::string& sSearchFor,
                                          int attrStart, const std::string& sAttributes, const std::string& sDelimiter = "," );
        void        optionAdd           ( const std::string& sValue,
                                          int attrStart, const std::string& sAttributes, const std::string& sDelimiter = "," );
        void        optionAdd           ( int iCount, int attrStart, const std::string& sAttributes, const std::string& sDelimiter = "," );

        void        attributesAdd       ( const std::vector<std::string>& attributeValues );
//        void        attributesAdd       ( const std::string& sAttrValue1, const std::string& sAttrValue2,
//                                          const std::string& sAttrValue3, const std::string& sAttrValue4  );
//        void        attributesAdd       ( const std::string& sAttrValue1, const std::string& sAttrValue2,
//                                          const std::string& sAttrValue3 );
//        void        attributesAdd       ( const std::string& sAttrValue1, const std::string& sAttrValue2 );
//        void        attributesAdd       ( const std::string& sAttrValue1 );


        // ---------------------------------
        // --- PUBLIC: Runtime functions ---
        // ---------------------------------
        std::string     domTextValueGet     ( const std::string& sNavActionName ) const;
        std::string     domValueGet         ( const std::string& sNavActionName ) const;
        std::string     valueGet            ( const std::string& sNavActionName ) const;
        std::string     searchForGet        ( const std::string& sNavActionName ) const;
        int             countGet            ( const std::string& sNavActionName ) const;
        boost::int64_t  optionIndexGet      ( const std::string& sNavActionName ) const;
        boost::int64_t  stateIndexGet       () const;
        boost::int64_t  numStatesGet        () const;
        boost::int64_t  lastStateIndexGet   () const;

        std::string     attributeGet        ( const std::string& sNavActionName, const std::string& sAttrName ) const;
        std::string     attributeGet        ( const std::string& sAttrName ) const;

        bool            nextState           ();

        std::string     stateString         () const;
        void            start               ();
        bool            navigationDone      () const;

        void            autoInputIncreaseLength ( bool bDoIncreaseLength );
        bool            hasNavAction            ( const std::string& sNavActionName ) const;
        bool            hasNavActionAttribute   ( const std::string& sNavAttrName ) const;

        boost::shared_ptr<NavigateStateBase>
                    actionPtrGet ( const std::string& sNavActionName ) ;
        const boost::shared_ptr<NavigateStateBase>
                    actionPtrGet ( const std::string& sNavActionName ) const;


    private:
        // ---------------------------------currentOptionIndex
        // --- PRIVATE: Helper functions ---
        // ---------------------------------
        void                                        doNextState     ();
        void                                        actionAdd       ( const std::string& sNavActionName, boost::shared_ptr<NavigateStateBase> pNavAction ) ;
        boost::shared_ptr<NavigateStateBase>        actionPtrGet    ( int iPos ) ;
        const boost::shared_ptr<NavigateStateBase>  actionPtrGet    ( int iPos ) const;
        int                                         actionPosGet    ( const std::string& sNavActionName ) const;

        // --- PRIVATE: Typedefs ---
        typedef std::map<std::string, std::string >                  StringStringMapT;
        typedef std::map<std::string, int >                          StringIntMapT;
        typedef std::vector< boost::shared_ptr<NavigateStateBase> >  NavActionsVecT;

        boost::shared_ptr<NavigateStateBase>    m_pCurNavAction;
        int                                     m_iCurNavActionPos;
        std::string                             m_sCurNavActionName;
        NavActionsVecT                          m_navActionsOrder;          // [pos]
        StringIntMapT                           m_navActionsLookUp;         // [ navActionName => pos ]
        StringStringMapT                        m_navAttributeNamesLookUp;  // [navAttrName => navActionName]
        bool                                    m_bForceDownloadResources;  // Set to true to force each of the actions to (re) download any resource files
        const ScriptMiner*                      m_pScriptMiner;

    };



} //END namespace crawl

#endif //_CRAWL_DOM_NAVIGATOR_H_

