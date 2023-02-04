#ifndef _SCRIPTCRAWL_STRING_MANIPULATION_H_
#define _SCRIPTCRAWL_STRING_MANIPULATION_H_

#include <boost/any.hpp>
#include <utils/string_algorithms.h>
#include <utils/string_base.h>
#include <Configuration.h>



// -------------------------------------------------------------
// --- Map types for looking up string manipulation funcions ---
// -------------------------------------------------------------
typedef std::map< std::string, boost::shared_ptr<crawl::StrModifierAbstraction> > 	StringManipAnyAliasMapT;


/** 
Static class for looking up string manipulation functions based on string 
names and integer 'handles'. */
struct G_StringManipLookUp {
	static const StringManipAnyAliasMapT 						AnyAliasMap;
    static  boost::shared_ptr<crawl::StrModifierAbstraction>	fromAliasAny			( const std::string& sFunAlias );

};






// -------------------------------------
// --- String manipulation functions ---
// -------------------------------------
// NOTE: These needs to be here and not in crawl/utils/string_algorthms.h/cpp 
//		 since they rely on miner specific settings like locale related such as 
//		 which character that represent a comma and which represents 1000s separator

namespace crawl {
//    std::string		trimInteger_fnc			( const boost::shared_ptr<Configuration> pConfig, const std::string& sInput		)								;
//    std::string		trimNumber_fnc			( const boost::shared_ptr<Configuration> pConfig, const std::string& sInput		)								;

//    std::string		eraseNthStrIndex_fnc	( const boost::shared_ptr<Configuration> pConfig, const std::string& sInput, const std::string& sSearchFor,	const std::string& sNth 	)	;
//    std::string		ieraseNthStrIndex_fnc	( const boost::shared_ptr<Configuration> pConfig, const std::string& sInput, const std::string& sSearchFor,	const std::string& sNth 	)	;

//    std::string		replaceNthStrIndex_fnc	( const boost::shared_ptr<Configuration> pConfig, const std::string& sInput, const std::string& sSearchFor,	const std::string& sReplaceWith ,const std::string& sNth	)	;
//    std::string		ireplaceNthStrIndex_fnc	( const boost::shared_ptr<Configuration> pConfig, const std::string& sInput, const std::string& sSearchFor,	const std::string& sReplaceWith, const std::string& sNth	)	;

} // END namespace crawl



#endif //_SCRIPTCRAWL_STRING_MANIPULATION_H_

