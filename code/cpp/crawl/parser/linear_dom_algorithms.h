#pragma once

#include <utils/string_algorithms.h>
#include <dom_constants.h>
#include "DomSeq.h"
#include <DomNodeIF.h>
#include <LinearDomIF.h>


namespace crawl {



LinearDomIF::const_iterator
findPredStopAt(  LinearDomIF::const_iterator const& itBegin
               , LinearDomIF::const_iterator const& itEnd
               , std::string const& sPattern
               , StringCompareFunT const& compareFun
               , int iCount
               , int iNodeTypes
               , LinearDomIF::const_iterator const& itStop );


LinearDomIF::const_iterator
findPredStopAt(   LinearDomIF::const_iterator itBegin
                , LinearDomIF::const_iterator const& itEnd
                , DomSeq const& seq
                , int iCount
                , int iNodeTypes
                , LinearDomIF::const_iterator const& itStop
                , const PtrStrVecT pArgs );






LinearDomIF::const_iterator
findNearest		(	LinearDomIF::const_iterator const& itBegin,
                    LinearDomIF::const_iterator const& itEnd,
                    LinearDomIF::const_iterator const& itSearchFrom,
					std::string const& sPattern, StringCompareFunT const& compareFun, 
					ENearestDir searchDir,  int iCount = 1,
                    int iNodeTypes	= DomNodeTypes::ALL_NODE_TYPES );


inline
LinearDomIF::const_iterator
findElement (	
    LinearDomIF::const_iterator const& itBegin,
    LinearDomIF::const_iterator const& itEnd,
	std::string const& sPattern,
	int iCount = 1 
)
{
    return findPredStopAt ( itBegin, itEnd, sPattern, string_compare::equals, iCount, DomNodeTypes::ELEMENT, itEnd ) ;
} 


inline
LinearDomIF::const_iterator
findAttribute (	
    LinearDomIF::const_iterator const& itBegin,
    LinearDomIF::const_iterator const& itEnd,
    std::string const& sPattern,
	int iCount = 1 
)
{
    return findPredStopAt ( itBegin, itEnd, sPattern, string_compare::equals, iCount, DomNodeTypes::ATTRIBUTE, itEnd ) ;
} 

// ---------------------------------------------
// --- Find specific element types functions ---
// ---------------------------------------------
inline
LinearDomIF::const_iterator
findINPUT (	
    LinearDomIF::const_iterator const& itBegin,
    LinearDomIF::const_iterator const& itEnd,
	int iCount = 1 
)
{
    return findPredStopAt ( itBegin, itEnd, "INPUT", string_compare::equals, iCount, DomNodeTypes::ELEMENT, itEnd ) ;
} 

inline
LinearDomIF::const_iterator
findFORM (	
    LinearDomIF::const_iterator const& itBegin,
    LinearDomIF::const_iterator const& itEnd,
	int iCount = 1 
)
{
    return findPredStopAt ( itBegin, itEnd, "FORM", string_compare::equals, iCount, DomNodeTypes::ELEMENT, itEnd ) ;
} 

inline
LinearDomIF::const_iterator
findBUTTON (	
    LinearDomIF::const_iterator const& itBegin,
    LinearDomIF::const_iterator const& itEnd,
	int iCount = 1 
)
{
    return findPredStopAt ( itBegin, itEnd, "BUTTON", string_compare::equals, iCount, DomNodeTypes::ELEMENT, itEnd ) ;
} 


// -----------------------
// --- Debug functions ---
// -----------------------

void debugPrint (
                  LinearDomIF::const_iterator const& itBegin
                , LinearDomIF::const_iterator const& itEnd
                , bool bTrimBlanks
                , bool bPrintNodeTypes = false );

std::string getDebugPrintString (
                  LinearDomIF::const_iterator const& itBegin
                , LinearDomIF::const_iterator const& itEnd
                , bool bTrimBlanks
                , bool bPrintNodeTypes = false );


} // END namespace crawl
