#include "DomNavigator.h"

#include <string>
#include <stdio.h>
#include <boost/algorithm/string.hpp>
#include <cpaf_libs/utils/cpaf_stl_utils.h>
#include <cpaf_libs/utils/cpaf_string_utils.hpp>
#include "NavigateStateBase.h"
#include "AutoInputState.h"
#include "DomPosClickState.h"
#include "DomClickNextState.h"
#include "DropDownSelectState.h"
#include "InputOptionsState.h"
#include "UrlLoadState.h"
#include "JavascriptExecuteState.h"

using namespace boost::algorithm;

namespace crawl {


    // ------------------------------------
    // --- Static member initialization ---
    // ------------------------------------


    // ------------------------------------
    // --- Constructor / Init Functions ---
    // ------------------------------------
    DomNavigator::DomNavigator(const ScriptMiner* pScriptMiner)
        : m_pCurNavAction()
        , m_iCurNavActionPos(-1)
        , m_sCurNavActionName("")
        , m_bForceDownloadResources(false)
        , m_pScriptMiner(pScriptMiner)
    {
        reset();
    }

    void DomNavigator::reset()
    {
        m_pCurNavAction             = boost::shared_ptr<NavigateStateBase>();
        m_iCurNavActionPos          = -1;
        m_sCurNavActionName         = "";

        m_navActionsOrder.clear();
        m_navActionsLookUp.clear();
        m_navAttributeNamesLookUp.clear();
        m_bForceDownloadResources   = false;
        start();
    }


    // ------------------------------------------
    // --- PUBLIC: Navigator Create functions ---
    // ------------------------------------------
    void DomNavigator::javascriptExecuteCreate(
          const std::string& sNavActionName
        )
    {
        boost::shared_ptr<NavigateStateBase> pNSB = boost::shared_ptr<NavigateStateBase>( new JavascriptExecuteState() );
        pNSB->setScriptMiner(m_pScriptMiner);
        actionAdd( sNavActionName, pNSB );
    }

    void DomNavigator::urlLoadCreate(
          const std::string& sNavActionName
        , const std::string& sBaseUrl
        )
    {
        boost::shared_ptr<NavigateStateBase> pNSB = boost::shared_ptr<NavigateStateBase>(
                new UrlLoadState(sBaseUrl)
                );
        pNSB->setScriptMiner(m_pScriptMiner);
        actionAdd( sNavActionName, pNSB );
    }

    void DomNavigator::inputOptionsCreate(
          const std::string& sNavActionName
        )
    {
        boost::shared_ptr<NavigateStateBase> pNSB = boost::shared_ptr<NavigateStateBase>(new InputOptionsState );
        pNSB->setScriptMiner(m_pScriptMiner);
        actionAdd( sNavActionName, pNSB );
    }


    void DomNavigator::dropDownSelectCreate( const std::string& sNavActionName )
    {
        boost::shared_ptr<NavigateStateBase> pNSB = boost::shared_ptr<NavigateStateBase>( new DropDownSelectState );
        pNSB->setScriptMiner(m_pScriptMiner);
        actionAdd( sNavActionName, pNSB );
    }


    void DomNavigator::domPosClickCreate( const std::string& sNavActionName, const std::string& sFindNextDomPosSequence )
    {
        boost::shared_ptr<NavigateStateBase> pNSB = boost::shared_ptr<NavigateStateBase>( new DomPosClickState(sFindNextDomPosSequence) );
        pNSB->setScriptMiner(m_pScriptMiner);
        actionAdd( sNavActionName, pNSB );
    }

    void DomNavigator::domClickNextCreate(const std::string& sNavActionName, const std::string& sFindNextDomPosSequence)
    {
        auto pNSB = boost::shared_ptr<NavigateStateBase>( new DomClickNextState(sFindNextDomPosSequence) );
        pNSB->setScriptMiner(m_pScriptMiner);
        actionAdd( sNavActionName, pNSB );
    }


    void DomNavigator::autoInputCreate( const std::string& sNavActionName, const std::string& sCharsList, int iMinLength, int iMaxLength )
    {
        boost::shared_ptr<NavigateStateBase> pNSB = boost::shared_ptr<NavigateStateBase>(
                new AutoInputState(sCharsList, iMinLength, iMaxLength) );
        pNSB->setScriptMiner(m_pScriptMiner);
        actionAdd( sNavActionName, pNSB );
    }

    void DomNavigator::attributeNamesCreate(const std::vector<std::string>& attributeNames)
    {
        m_pCurNavAction->attributeNamesCreate(attributeNames);
        for (const auto& attributeName: attributeNames)
            m_navAttributeNamesLookUp[attributeName] = m_sCurNavActionName;
    }

    void DomNavigator::attributeNamesCreate (
          const std::string& sAttrNames
        , const std::string& sDelimiter
        )
    {
        cpaf::StringVecT attributeNamesVec;
        cpaf::splitv_trim (attributeNamesVec, sAttrNames, sDelimiter);
        attributeNamesCreate(attributeNamesVec);
    }


    // ------------------------------------------
    // --- PUBLIC: Runtime settings functions ---
    // ------------------------------------------
    void  DomNavigator::forceDownloadResources  ( bool bForceDownload )
    {
        m_bForceDownloadResources = bForceDownload;
    }

    /** Set begin state using string state. The state string can be either indices, whic
        is assumed to be the case if all elemwnts can be converted to integers. Otherwise
        we assume it's a state string using state names. The elements are assumed to be
        comma separated, */
    void DomNavigator::currentStateIndicesStateSet ( const std::string& sState )
    {
        cpaf::IntVecT state = cpaf::split_int( sState, ",", -1);
        ///bool allIndices = true;
        for ( cpaf::IntVecT::const_iterator it = state.begin(); it != state.end(); ++it ) {
            if ( -1 == *it ) {
                ///allIndices = false;
                break;
            }
        }

        currentStateIndicesVecSet( state );
    }

    void DomNavigator::currentStateIndicesStringSet ( const std::string& sState )
    {
        cpaf::IntVecT state = cpaf::split_int( sState, ",");
        currentStateIndicesVecSet( state );
    }

    std::string DomNavigator::currentStateIndicesStringGet  () const
    {
        cpaf::IntVecT state = currentStateIndicesVecGet ();
        return cpaf::join( state, "," );
    }

    void DomNavigator::currentStateIndicesVecSet ( const cpaf::IntVecT& state )
    {
        for ( unsigned int i = 0; i < m_navActionsOrder.size(); ++i ) {
            if ( i < state.size() )    m_navActionsOrder[i]->currentOptionIndexSet( state[i] );
        }
    }

    cpaf::IntVecT DomNavigator::currentStateIndicesVecGet () const
    {
        cpaf::IntVecT state;
        for ( unsigned int i = 0; i < m_navActionsOrder.size(); ++i ) {
            state.push_back( m_navActionsOrder[i]->currentOptionIndex() );
        }
        return state;
    }

    void DomNavigator::currentStateSet ( const std::string& sState, const std::string& sDelimiter )
    {
        cpaf::StringVecT state = cpaf::splitv( sState, sDelimiter );
        for ( unsigned int i = 0; i < m_navActionsOrder.size(); ++i ) {
            if ( i < state.size() )    m_navActionsOrder[i]->currentOptionSet( trim_copy(state[i]) );
        }
    }

    void DomNavigator::currentStateSet ( const std::string& sState )
    {
        currentStateSet(sState, ",");
    }

    void DomNavigator::endStateSet ( const std::string& sState, const std::string& sDelimiter )
    {
        cpaf::StringVecT state = cpaf::splitv( sState, sDelimiter );
        for ( unsigned int i = 0; i < m_navActionsOrder.size(); ++i ) {
            if ( i < state.size() )    m_navActionsOrder[i]->endOptionSet( trim_copy(state[i]) );
        }
    }

    void DomNavigator::endStateSet ( const std::string& sState )
    {
        endStateSet(sState, ",");
    }

    // -------------------------------------
    // --- PUBLIC: Add Options functions ---
    // -------------------------------------
    void DomNavigator::optionResourceAdd   (
          const std::string& sResourcePath
        , const std::string& sScriptFilterFunction
        , bool bForceDownload  )
    {
        m_pCurNavAction->optionResourceAdd( sResourcePath, sScriptFilterFunction, bForceDownload );
    }


    void DomNavigator::optionAdd( int iCount, const std::string& sValue, const std::string& sSearchFor  )
    {
        m_pCurNavAction->optionAdd( iCount, sValue, sSearchFor );
    }


    void DomNavigator::optionAdd( int iCount, const std::string& sValue )
    {
        optionAdd( iCount, sValue, sValue );
    }


    void DomNavigator::optionAdd( const std::string& sValue, const std::string& sSearchFor )
    {
        optionAdd( NavigateStateBase::UseDefaultCountParameter, sValue, sSearchFor );
    }


    void DomNavigator::optionAdd( const std::string& sValue )
    {
        optionAdd( NavigateStateBase::UseDefaultCountParameter, sValue, sValue );
    }


    void DomNavigator::optionAdd( int iCount )
    {
        optionAdd( iCount, "", "" );
    }

    void DomNavigator::optionAdd( int iCount, const std::string& sValue, const std::string& sSearchFor,
                                  int /*attrStart*/, const std::string& sAttributes, const std::string& sDelimiter )
    {
        optionAdd( iCount, sValue, sSearchFor );
        cpaf::StringVecT attributesVec;
        cpaf::splitv_trim ( attributesVec, sAttributes, sDelimiter );
        attributesAdd(attributesVec);
//        std::string attr1 = attributesVec.size() > 0 ? attributesVec[0] : std::string("");
//        std::string attr2 = attributesVec.size() > 1 ? attributesVec[1] : std::string("");
//        std::string attr3 = attributesVec.size() > 2 ? attributesVec[2] : std::string("");
//        std::string attr4 = attributesVec.size() > 3 ? attributesVec[3] : std::string("");
//        attributesAdd(attr1, attr2, attr3, attr4 );
    }

    void DomNavigator::optionAdd( int iCount, const std::string& sValue,
                                  int attrStart, const std::string& sAttributes, const std::string& sDelimiter )
    {
        optionAdd( iCount, sValue, sValue, attrStart, sAttributes, sDelimiter );
    }


    void DomNavigator::optionAdd( const std::string& sValue, const std::string& sSearchFor,
                                  int attrStart, const std::string& sAttributes, const std::string& sDelimiter )
    {
        optionAdd( NavigateStateBase::UseDefaultCountParameter, sValue, sSearchFor, attrStart, sAttributes, sDelimiter );
    }


    void DomNavigator::optionAdd( const std::string& sValue,
                                  int attrStart, const std::string& sAttributes, const std::string& sDelimiter )
    {
        optionAdd( NavigateStateBase::UseDefaultCountParameter, sValue, sValue, attrStart, sAttributes, sDelimiter );
    }


    void DomNavigator::optionAdd( int iCount,
                                  int attrStart, const std::string& sAttributes, const std::string& sDelimiter )
    {
        optionAdd( iCount, "", "", attrStart, sAttributes, sDelimiter );
    }

    void DomNavigator::attributesAdd(const std::vector<std::string>& attributeValues)
    {
        m_pCurNavAction->attributesAdd(attributeValues);
    }


//    void DomNavigator::attributesAdd( const std::string& sAttrValue1, const std::string& sAttrValue2,
//                                      const std::string& sAttrValue3, const std::string& sAttrValue4  )
//    {
//        m_pCurNavAction->attributesAdd(sAttrValue1, sAttrValue2, sAttrValue3, sAttrValue4);
//    }

//    void DomNavigator::attributesAdd( const std::string& sAttrValue1, const std::string& sAttrValue2,
//                                      const std::string& sAttrValue3  )
//    {
//        m_pCurNavAction->attributesAdd(sAttrValue1, sAttrValue2, sAttrValue3, "");
//    }

//    void DomNavigator::attributesAdd( const std::string& sAttrValue1, const std::string& sAttrValue2  )
//    {
//        m_pCurNavAction->attributesAdd(sAttrValue1, sAttrValue2, "", "");
//    }

//    void DomNavigator::attributesAdd( const std::string& sAttrValue1  )
//    {
//        m_pCurNavAction->attributesAdd(sAttrValue1, "", "", "");
//    }




    // ---------------------------------
    // --- PUBLIC: Runtime functions ---
    // ---------------------------------
    std::string DomNavigator::domTextValueGet(
            const std::string& sNavActionName
            ) const
    {
        const boost::shared_ptr<NavigateStateBase> pNSB = actionPtrGet(sNavActionName);
        if ( pNSB ) return pNSB->currentDomTextValue();
        return "";
    }

    std::string DomNavigator::domValueGet(
            const std::string& sNavActionName
            ) const
    {
        const boost::shared_ptr<NavigateStateBase> pNSB = actionPtrGet(sNavActionName);
        if ( pNSB ) return pNSB->currentDomValue();
        return "";
    }


    std::string DomNavigator::valueGet(
            const std::string& sNavActionName
            ) const
    {
        const boost::shared_ptr<NavigateStateBase> pNSB = actionPtrGet(sNavActionName);
        if ( pNSB ) return pNSB->currentOption();
        return "";
    }


    std::string DomNavigator::searchForGet(
            const std::string& sNavActionName
            ) const
    {
        const boost::shared_ptr<NavigateStateBase> pNSB = actionPtrGet(sNavActionName);
        if ( pNSB ) return pNSB->currentSearchFor();
        return "";
    }

    int DomNavigator::countGet(
            const std::string& sNavActionName
            ) const
    {
        const boost::shared_ptr<NavigateStateBase> pNSB = actionPtrGet(sNavActionName);
        if ( pNSB ) return pNSB->currentCount();
        return NavigateStateBase::UseDefaultCountParameter;
    }

    boost::int64_t DomNavigator::optionIndexGet (
            const std::string& sNavActionName
            ) const
    {
        const boost::shared_ptr<NavigateStateBase> pNSB = actionPtrGet(sNavActionName);
        if ( pNSB ) return pNSB->currentOptionIndex();
        return NavigateStateBase::InvalidOptionIndexE;
    }

    boost::int64_t DomNavigator::stateIndexGet () const
    {
        if ( m_navActionsOrder.size() == 0 ) return 0;

        boost::int64_t res = 0;
        for ( size_t i = 0; i < m_navActionsOrder.size()-1; i++ ) {
            boost::int64_t weight = 1;
            for ( size_t n = i+1; n < m_navActionsOrder.size(); n++ ) {
                weight *= m_navActionsOrder[n]->numOptions();
            }
            res += m_navActionsOrder[i]->currentOptionIndex() * weight;
        }
        res += m_navActionsOrder[m_navActionsOrder.size()-1]->currentOptionIndex();
        return res;
    }

    boost::int64_t DomNavigator::lastStateIndexGet () const
    {
        return numStatesGet() -1;
    }

    boost::int64_t DomNavigator::numStatesGet () const
    {
        if ( m_navActionsOrder.size() == 0 ) return 0;
        boost::int64_t res = 1;
        for(boost::shared_ptr<NavigateStateBase> pNSB : m_navActionsOrder ) {
            res *= pNSB->numOptions();
        }
        return res;
    }


    std::string DomNavigator::attributeGet(
              const std::string& sNavActionName
            , const std::string& sAttrName
            ) const
    {
        const boost::shared_ptr<NavigateStateBase> pNSB = actionPtrGet(sNavActionName);
        if ( pNSB ) return pNSB->attributeGet(sAttrName);
        return "";
    }

    std::string DomNavigator::attributeGet(
            const std::string& sAttrName
            ) const
    {
        std::string sNavActionName = cpaf::map_find( m_navAttributeNamesLookUp, std::string(""), sAttrName );
        return attributeGet( sNavActionName, sAttrName );
    }


    bool DomNavigator::nextState ()
    {
        if ( navigationDone() ) return false;
        doNextState();
        return true;
    }


    std::string DomNavigator::stateString() const
    {
        std::string s;
        int i = 0;
        for(boost::shared_ptr<NavigateStateBase> pNSB : m_navActionsOrder ) {
            if ( i++ > 0 ) s += ",";
            s += pNSB->currentOption();
        }
        return s;
    }

    void DomNavigator::start()
    {
        for(boost::shared_ptr<NavigateStateBase> pNSB : m_navActionsOrder ) {
            pNSB->start();
        }
    }

    bool DomNavigator::navigationDone() const
    {
        bool allAtEnd = true;
        for( boost::shared_ptr<NavigateStateBase> pNSB: m_navActionsOrder ) {
            pNSB->allMoreSignificantStatesAtEnd(allAtEnd);
            allAtEnd = allAtEnd && pNSB->atEndOption() ;
            if ( !allAtEnd ) break;
        }
        return allAtEnd;
    }

    void DomNavigator::autoInputIncreaseLength ( bool bDoIncreaseLength )
    {
        for( boost::shared_ptr<NavigateStateBase> pNSB: m_navActionsOrder ) {
            pNSB->autoInputIncreaseLength (bDoIncreaseLength) ;
        }
    }

    bool DomNavigator::hasNavAction (
        const std::string& sNavActionName
        ) const
    {
        const boost::shared_ptr<NavigateStateBase> pAction = actionPtrGet( sNavActionName );
        if ( ! pAction ) return false;
        return true;
    }

    bool DomNavigator::hasNavActionAttribute(
        const std::string& sNavAttrName
        ) const
    {
        return m_navAttributeNamesLookUp.find( sNavAttrName ) != m_navAttributeNamesLookUp.end();
    }


    boost::shared_ptr<NavigateStateBase>
    DomNavigator::actionPtrGet ( const std::string& sNavActionName )
    {
        return actionPtrGet( actionPosGet(sNavActionName) );
    }

    const boost::shared_ptr<NavigateStateBase>
    DomNavigator::actionPtrGet ( const std::string& sNavActionName ) const
    {
        return actionPtrGet( actionPosGet(sNavActionName) );
    }

    // ---------------------------------
    // --- PRIVATE: Helper functions ---
    // ---------------------------------
    void DomNavigator::doNextState ()
    {
        if ( m_navActionsOrder.empty() )  return;
        NavActionsVecT::reverse_iterator itAction = m_navActionsOrder.rbegin();
        bool advanceToNextAction = (*itAction)->atEndOption();
        (*itAction)->nextOption();
        while ( advanceToNextAction ) {
            ++itAction;
            advanceToNextAction = itAction != m_navActionsOrder.rend() && (*itAction)->atEndOption();
            if ( itAction != m_navActionsOrder.rend() ) (*itAction)->nextOption();
        }
    }


    void DomNavigator::actionAdd (
              const std::string& sNavActionName
            , boost::shared_ptr<NavigateStateBase> pNavAction
            )
    {
        m_sCurNavActionName = sNavActionName;
        ++m_iCurNavActionPos;
        m_pCurNavAction = pNavAction;
        m_navActionsOrder.push_back(pNavAction);
        m_navActionsLookUp[sNavActionName] = m_iCurNavActionPos;
    }


    boost::shared_ptr<NavigateStateBase>
            DomNavigator::actionPtrGet ( int iPos )
    {
        if ( 0 <= iPos && iPos <= m_iCurNavActionPos )  return m_navActionsOrder[static_cast<size_t>(iPos)];
        else                                            return boost::shared_ptr<NavigateStateBase>();
    }

    const boost::shared_ptr<NavigateStateBase>
            DomNavigator::actionPtrGet ( int iPos ) const
    {
        if ( 0 <= iPos && iPos <= m_iCurNavActionPos )  return m_navActionsOrder[static_cast<size_t>(iPos)];
        else                                            return boost::shared_ptr<NavigateStateBase>();
    }


    int DomNavigator::actionPosGet (
            const std::string& sNavActionName
            ) const
    {
        return cpaf::map_find(m_navActionsLookUp, NavigateStateBase::InvalidOptionIndexE, sNavActionName );
    }


} // END namespace crawl

