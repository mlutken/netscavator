#include "webbrowse_string_utils.h"

#include <boost/algorithm/string.hpp>

std::string 
trimBlanksCopy	( const std::string& sInput )
{
	std::string sRet = boost::algorithm::trim_copy( sInput );
	return sRet;
}

