
#include <iostream>
#include <boost/assign/list_of.hpp> 

#include "string_compare_functions.h"

#include <cpaf_libs/utils/cpaf_string_utils.hpp>

namespace crawl {

namespace string_compare {

const StringCompFunAliasMapT G_StringCompareLookUp::AliasMap = boost::assign::map_list_of
	("am",alwaysMatch)("alwaysMatch",alwaysMatch)
	("nm",neverMatch)("neverMatch",neverMatch)
	// --- Normal functions ---
	("eq",equals)("equals",equals)
	("ieq",iequals)("iequals",iequals)
	("con",contains)("contains",contains)
	("icon",icontains)("icontains",icontains)
	("sw",startsWith)("startsWith",startsWith)
	("isw",istartsWith)("istartsWith",istartsWith)
	("ew",endsWith)("endsWith",endsWith)
	("iew",iendsWith)("iendsWith",iendsWith)
	("lt",lessThan)("lessThan",lessThan)
	("ilt",ilessThan)("ilessThan",ilessThan)
	("gt",greaterThan)("greaterThan",greaterThan)
	("igt",igreaterThan)("igreaterThan",igreaterThan)
	("re",regexSearch)("regexSearch",regexSearch)
	// --- Negated functions ---
	("neq",nequals)("nequals",nequals)
	("nieq",niequals)("niequals",niequals)
	("ncon",ncontains)("ncontains",ncontains)
	("nicon",nicontains)("nicontains",nicontains)
	("nsw",nstartsWith)("nstartsWith",nstartsWith)
	("nisw",nistartsWith)("nistartsWith",nistartsWith)
	("new",nendsWith)("nendsWith",nendsWith)
	("niew",niendsWith)("niendsWith",niendsWith)
	("nlt",nlessThan)("nlessThan",nlessThan)
	("nilt",nilessThan)("nilessThan",nilessThan)
	("ngt",ngreaterThan)("ngreaterThan",ngreaterThan)
	("nigt",nigreaterThan)("nigreaterThan",nigreaterThan)
	("nre",nregexSearch)("nregexSearch",nregexSearch)
	;


const StringCompFunHandleMapT G_StringCompareLookUp::HandleMap = boost::assign::map_list_of
	(alwaysMatchE,alwaysMatch)
	(neverMatchE,neverMatch)
	(equalsE,equals)
	(iequalsE,iequals)
	(containsE,contains)
	(icontainsE,icontains)
	(startsWithE,startsWith)
	(istartsWithE,istartsWith)
	(endsWithE,endsWith)
	(iendsWithE,iendsWith)
	(lessThanE,lessThan)
	(ilessThanE,ilessThan)
	(greaterThanE,greaterThan)
	(igreaterThanE,igreaterThan)
	(regexSearchE,regexSearch)
	(nequalsE,nequals)
	(niequalsE,niequals)
	(ncontainsE,ncontains)
	(nicontainsE,nicontains)
	(nstartsWithE,nstartsWith)
	(nistartsWithE,nistartsWith)
	(nendsWithE,nendsWith)
	(niendsWithE,niendsWith)
	(nlessThanE,nlessThan)
	(nilessThanE,nilessThan)
	(ngreaterThanE,ngreaterThan)
	(nigreaterThanE,nigreaterThan)
	(nregexSearchE,nregexSearch)
	;


StringCompareFunT  G_StringCompareLookUp::fromAlias	( const std::string& sFunAlias )
{
	StringCompareFunT compareFun = contains;
	StringCompFunAliasMapT::const_iterator itComp = G_StringCompareLookUp::AliasMap.find( sFunAlias );
	if ( itComp != G_StringCompareLookUp::AliasMap.end() ) 	compareFun = itComp->second;
	return compareFun;
}

StringCompareFunT G_StringCompareLookUp::fromHandle	( int iFunHandle )
{
	StringCompareFunT compareFun = contains;
	StringCompFunHandleMapT::const_iterator itComp = G_StringCompareLookUp::HandleMap.find( iFunHandle );
	if ( itComp != G_StringCompareLookUp::HandleMap.end() ) 	compareFun = itComp->second;
	return compareFun;
}


} //END namespace string_compare
} // END namespace crawl

