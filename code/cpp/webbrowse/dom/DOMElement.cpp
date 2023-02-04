
#include "DOMElement.h"


#include <boost/algorithm/string.hpp>
#include <cpaf_string_utils.hpp>
#include <utils/webbrowse_string_utils.h>


/// Add class 
void DOMElement::addClass( const std::string& sClassName )
{
	setClass( getClass() + " " + sClassName );
}

/// Remove class 
void DOMElement::removeClass( const std::string& sClassName )
{
	std::string sClass = boost::algorithm::erase_all_copy( getClass(), sClassName );
	setClass( boost::algorithm::trim_copy( sClass ) );
}
