#include "DropDownSelectState.h"
#include <cpaf_libs/utils/cpaf_string_utils.hpp>
#include <stdio.h>

using namespace boost;

namespace crawl {


// ------------------------------------
// --- Constructor / Init Functions ---
// ------------------------------------
DropDownSelectState::DropDownSelectState()
{

}

std::string DropDownSelectState::do_optionAdd (
          int iCount
        , const std::string& sValue
        , const std::string& sSearchFor
        )
{
    std::string value = sValue;
    std::string searchFor = sSearchFor;
    if ( iCount == NavigateStateBase::UseDefaultCountParameter ) iCount = addOptionPosCounter() +1;
    if ( value == "" )      value = std::to_string( iCount );
    if ( searchFor == "" )  searchFor = value;

    m_options.push_back(OptionT(iCount, value, searchFor));
    return value;
}

} // END namespace crawl

