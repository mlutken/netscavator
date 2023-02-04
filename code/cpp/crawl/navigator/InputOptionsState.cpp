#include "InputOptionsState.h"
#include <cpaf_libs/utils/cpaf_string_utils.hpp>

using namespace boost;

namespace crawl {
InputOptionsState::InputOptionsState()
{
}

int	InputOptionsState::do_indexToCount ( boost::int64_t /*iOptionIndex*/	) const
{
    return 0;
}

void InputOptionsState::do_addResourceLine ( const std::string& sLine )
{
    //printf("ML: InputOptionsState::do_addResourceLine: '%s'\n", sLine.c_str() );
    optionAdd( NavigateStateBase::UseDefaultCountParameter, sLine, sLine );
}


} // END namespace crawl

