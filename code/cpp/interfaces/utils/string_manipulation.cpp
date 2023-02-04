#include "string_manipulation.h"

#include <iostream>
#include <boost/assign/list_of.hpp> 
#include <cpaf_libs/utils/cpaf_string_utils.hpp>
////#include "scriptcrawl_private.h"

using namespace crawl;

using boost::any_cast;

// ------------------------------
// --- STATIC: Initialization ---
// ------------------------------

const StringManipAnyAliasMapT G_StringManipLookUp::AnyAliasMap = boost::assign::map_list_of
    ("trimDefault",			boost::shared_ptr<StrModifierAbstraction>( new StringManipStr_Str(trimDefault_fnc)						)	)
    ("raw",					boost::shared_ptr<StrModifierAbstraction>( new StringManipStr_Str(raw_fnc)								)	)
    ("toUpper",				boost::shared_ptr<StrModifierAbstraction>( new StringManipStr_Str(toUpper_fnc)							)	)
    ("toLower",				boost::shared_ptr<StrModifierAbstraction>( new StringManipStr_Str(toLower_fnc)							)	)
    ("trimEnds",			boost::shared_ptr<StrModifierAbstraction>( new StringManipStr_Str(trimEnds_fnc)							)	)
    ("trimLeft",			boost::shared_ptr<StrModifierAbstraction>( new StringManipStr_Str(trimLeft_fnc)							)	)
    ("trimRight",			boost::shared_ptr<StrModifierAbstraction>( new StringManipStr_Str(trimRight_fnc)						)	)
    ("trimYear",			boost::shared_ptr<StrModifierAbstraction>( new StringManipStr_Str(trimYear_fnc)							)	)
    ("trimInteger",			boost::shared_ptr<StrModifierAbstraction>( new StringManipStr_Str(trimInteger_fnc)						)	)
    ("trimNumber",			boost::shared_ptr<StrModifierAbstraction>( new StringManipStr_Str(trimNumber_fnc)						)	)

    ("trimCharsEnds",		boost::shared_ptr<StrModifierAbstraction>( new StringManipStr_StrStr(trimCharsEnds_fnc)					)	)
    ("trimCharsLeft",		boost::shared_ptr<StrModifierAbstraction>( new StringManipStr_StrStr(trimCharsLeft_fnc)					)	)
    ("trimCharsRight",		boost::shared_ptr<StrModifierAbstraction>( new StringManipStr_StrStr(trimCharsRight_fnc)				)	)
    ("trimRegex",			boost::shared_ptr<StrModifierAbstraction>( new StringManipStr_StrStr(trimRegex_fnc)						)	)
    ("itrimRegex",			boost::shared_ptr<StrModifierAbstraction>( new StringManipStr_StrStr(itrimRegex_fnc)					)	)
    ("append",				boost::shared_ptr<StrModifierAbstraction>( new StringManipStr_StrStr(append_fnc)						)	)
    ("prepend",				boost::shared_ptr<StrModifierAbstraction>( new StringManipStr_StrStr(prepend_fnc)						)	)
    ("eraseFirst",			boost::shared_ptr<StrModifierAbstraction>( new StringManipStr_StrStr(eraseFirst_fnc)					)	)
    ("ieraseFirst",			boost::shared_ptr<StrModifierAbstraction>( new StringManipStr_StrStr(ieraseFirst_fnc)					)	)
    ("eraseLast",			boost::shared_ptr<StrModifierAbstraction>( new StringManipStr_StrStr(eraseLast_fnc)						)	)
    ("ieraseLast",			boost::shared_ptr<StrModifierAbstraction>( new StringManipStr_StrStr(ieraseLast_fnc)					)	)
    ("eraseAll",			boost::shared_ptr<StrModifierAbstraction>( new StringManipStr_StrStr(eraseAll_fnc)						)	)
    ("ieraseAll",			boost::shared_ptr<StrModifierAbstraction>( new StringManipStr_StrStr(ieraseAll_fnc)						)	)
    ("eraseRegex",			boost::shared_ptr<StrModifierAbstraction>( new StringManipStr_StrStr(eraseRegex_fnc)					)	)
    ("eraseAllRegex",		boost::shared_ptr<StrModifierAbstraction>( new StringManipStr_StrStr(eraseAllRegex_fnc)					)	)

    ("trimBetween",         boost::shared_ptr<StrModifierAbstraction>( new StringManipStr_StrStrStr(trimBetween_fnc)                )	)
    ("trimBetweenCount",    boost::shared_ptr<StrModifierAbstraction>( new StringManipStr_StrStrStrStr(trimBetweenCount_fnc)        )	)
    ("trimIntegerCustom",	boost::shared_ptr<StrModifierAbstraction>( new StringManipStr_StrStrStr(trimIntegerCustom_fnc)			)	)
    ("trimNumberCustom",	boost::shared_ptr<StrModifierAbstraction>( new StringManipStr_StrStrStr(trimNumberCustom_fnc)			)	)
    ("replaceFirst",		boost::shared_ptr<StrModifierAbstraction>( new StringManipStr_StrStrStr(replaceFirst_fnc)				)	)
    ("ireplaceFirst",		boost::shared_ptr<StrModifierAbstraction>( new StringManipStr_StrStrStr(ireplaceFirst_fnc)				)	)
    ("replaceLast",			boost::shared_ptr<StrModifierAbstraction>( new StringManipStr_StrStrStr(replaceLast_fnc)				)	)
    ("ireplaceLast",		boost::shared_ptr<StrModifierAbstraction>( new StringManipStr_StrStrStr(ireplaceLast_fnc)				)	)
    ("replaceAll",			boost::shared_ptr<StrModifierAbstraction>( new StringManipStr_StrStrStr(replaceAll_fnc)					)	)
    ("ireplaceAll",			boost::shared_ptr<StrModifierAbstraction>( new StringManipStr_StrStrStr(ireplaceAll_fnc)				)	)
    ("replaceRegex",		boost::shared_ptr<StrModifierAbstraction>( new StringManipStr_StrStrStr(replaceRegex_fnc)				)	)
    ("replaceAllRegex",		boost::shared_ptr<StrModifierAbstraction>( new StringManipStr_StrStrStr(replaceAllRegex_fnc)			)	)

    ("eraseNth",			boost::shared_ptr<StrModifierAbstraction>( new StringManipStr_StrStrStr(eraseNthStrIndex_fnc)			)	)
    ("ieraseNth",			boost::shared_ptr<StrModifierAbstraction>( new StringManipStr_StrStrStr(ieraseNthStrIndex_fnc)			)	)

    ("replaceNth",			boost::shared_ptr<StrModifierAbstraction>( new StringManipStr_StrStrStrStr(replaceNthStrIndex_fnc)		)	)
    ("ireplaceNth",			boost::shared_ptr<StrModifierAbstraction>( new StringManipStr_StrStrStrStr(ireplaceNthStrIndex_fnc)		)	)
;



boost::shared_ptr<crawl::StrModifierAbstraction>	G_StringManipLookUp::fromAliasAny	( const std::string& sFunAlias )
{
	StringManipAnyAliasMapT::const_iterator itManip = G_StringManipLookUp::AnyAliasMap.find( sFunAlias );
	if ( itManip != G_StringManipLookUp::AnyAliasMap.end() ) 	return itManip->second;
	
    return boost::shared_ptr<crawl::StrModifierAbstraction>();
}




// ------------------------------------------
// --- String manipulation functions ---
// ------------------------------------------

namespace crawl {



} // END namespace crawl

