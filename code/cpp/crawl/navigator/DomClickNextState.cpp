#include "DomClickNextState.h"
#include <cpaf_libs/utils/cpaf_string_utils.hpp>
#include <ScriptMinerIF.h>


using namespace std;

namespace crawl {

// ------------------------------------
// --- Constructor / Init Functions ---
// ------------------------------------
DomClickNextState::DomClickNextState(const std::string& sFindNextDomPosSequence)
    : m_sFindNextDomPosSequence(sFindNextDomPosSequence)
{
}

void DomClickNextState::initialize(ScriptMinerIF* miner)
{
////    StrVecT attrNames = attributeNames();
    int posSave = miner->domPos();
    miner->domNewSearch();
    while ( miner->domFindNext( m_sFindNextDomPosSequence ) ) {
        int domPosValue = miner->domPos();
        string value = std::to_string(domPosValue);
        optionAdd  ( domPosValue, value, value );

// TODO: Consider how to possibly support this in a good way.
//        void        attributesAdd           ( const std::string& sAttrValue1, const std::string& sAttrValue2,
//                                              const std::string& sAttrValue3, const std::string& sAttrValue4  );


    }
    miner->domPosSet( posSave );

}

bool DomClickNextState::isInitialized() const
{
    return m_isInitialized;
}

void DomClickNextState::setIsInitialized(bool isInitialized)
{
    m_isInitialized = isInitialized;
}

void DomClickNextState::do_start()
{
    currentOptionIndexSet( FirstOptionIndexE );
    m_isInitialized = false;
}


} // END namespace crawl

