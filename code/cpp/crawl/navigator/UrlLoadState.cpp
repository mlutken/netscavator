#include "UrlLoadState.h"
#include <cpaf_libs/utils/cpaf_string_utils.hpp>

using namespace boost;

namespace crawl {

UrlLoadState::UrlLoadState(const std::string& sBaseUrl)
    : m_sBaseUrl(sBaseUrl)
{
}

int	UrlLoadState::do_indexToCount ( boost::int64_t /*iOptionIndex*/	) const
{
    return 0;
}


} // END namespace crawl

