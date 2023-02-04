
#include <iostream>
#include <limits>
#include <boost/format.hpp>
#include <boost/integer_traits.hpp>
#include <DomNodeIF.h>
#include "linear_dom_algorithms.h"

namespace crawl {


    inline bool compareNode(
            LinearDomIF::const_iterator itNode              ///< Dom node to compare
            , std::string const& sPattern                   ///< String pattern to compare against
            , StringCompareFunT const& compareFun           ///< Compare function
            , int iNodeTypes                                ///< Allowed node types to compare see DomNodeIF::Type
            )
    {
        const std::string& stringDataUTF8 = itNode->stringData();
        const boost::shared_ptr<DomNodeIF> pDomNode = itNode->node();
        if ( (static_cast<uint32_t>(iNodeTypes) & pDomNode->nodeType()) == 0 )	return false;
        if 		( sPattern == "?"	)	return true;		// Globbing type match any node
        else if ( sPattern == "\\?" ) 	return compareFun( stringDataUTF8, "?" );		// Escaping '?'
        return compareFun( stringDataUTF8, sPattern );
    }


    static LinearDomIF::const_iterator
            findPredStopAtHelper(
                    LinearDomIF::const_iterator itBegin
                    , LinearDomIF::const_iterator const& itEnd
                    , DomSeq::StringComparePairVecT::const_iterator itSeqBeg
                    , DomSeq::StringComparePairVecT::const_iterator itSeqEnd
                    , int iCount
                    , int iNodeTypes
                    , LinearDomIF::const_iterator const& itStop
                    , const PtrStrVecT pArgs
                    )
    {
        auto iSeqSize = itSeqEnd - itSeqBeg;

        LinearDomIF::const_iterator itSave;
        if (iSeqSize < 1 )	return itEnd;
        // Search forward
        if ( iCount > 0 ) {
            while ( itBegin < itEnd && itBegin < itStop)
            {
                itBegin = findPredStopAt( itBegin, itEnd, itSeqBeg->pattern(pArgs), itSeqBeg->compareFun, 1, iNodeTypes, itStop )	;
                itSave = itBegin < itEnd ? itBegin +1 : itEnd;
                if ( itEnd - itBegin >= iSeqSize )
                {
                    DomSeq::const_iterator itSeq = itSeqBeg;
                    bool bSeqOk = true;
                    for ( ; itSeq != itSeqEnd; ++itSeq, ++itBegin )
                    {
                        // Normal sequence compare string
                        if ( !compareNode( itBegin, (*itSeq).pattern(pArgs), (*itSeq).compareFun, iNodeTypes ) ) {
                            bSeqOk = false;
                            break;
                        }
                        if ( itBegin == itStop ) return itEnd;	// Terminate search
                    }
                    if ( bSeqOk && ( --iCount == 0) )	return --itBegin; 	// in case we found a match we have gotten one too far!
                }
                itBegin = itSave;
            }
        }
        // Search backward
        else if ( iCount < 0 ) {
            LinearDomIF::const_iterator itEndPos = itEnd;
            while ( itBegin < itEndPos )
            {
                LinearDomIF::const_iterator it = findPredStopAt( itBegin, itEndPos, (itSeqEnd-1)->pattern(pArgs), (itSeqEnd-1)->compareFun, -1, iNodeTypes, itStop )	;
                if ( it == itEndPos )	return itEnd;
                itEndPos = it;
                itSave = itEndPos > itBegin ? itEndPos -1 : itBegin;

                if ( itEndPos - itBegin >= iSeqSize )
                {
                    DomSeq::const_iterator itSeq = itSeqEnd;
                    bool bSeqOk = true;
                    for ( ; itSeq > itSeqBeg; --itEndPos ) {
                        --itSeq;
                        // Normal sequence compare string
                        if ( !compareNode( itEndPos, (*itSeq).pattern(pArgs), (*itSeq).compareFun, iNodeTypes ) ) {
                            bSeqOk = false;
                            break;
                        }
                        if ( itEndPos == itStop ) return itEnd;	// Terminate search
                    }
                    if ( bSeqOk && ( ++iCount == 0) )	return ++itEndPos; 	// in case we found a match we have gotten one too far!
                }
                itEndPos = itSave;
            }
        }
        return itEnd;
    }


    LinearDomIF::const_iterator
            findPredStopAt(LinearDomIF::const_iterator const& itBegin, 	///< Beginning of interval
                    LinearDomIF::const_iterator const& itEnd,       ///< End of interval
                    std::string const& sPattern,					///< String pattern to compare against
                    StringCompareFunT const& compareFun,			///< Compare function
                    int iCount,										///< Number of intances to match (node intances that matches)
                    int iNodeTypes,                                 ///< Restrict to node types.
                    LinearDomIF::const_iterator const& itStop       ///< Stop at this iterator.
                    )
    {
        // Search forward
        if ( iCount > 0 ) {
            LinearDomIF::const_iterator it = itBegin;
            for ( ; it != itEnd && it != itStop; ++it	) {
                if ( (static_cast<uint32_t>(iNodeTypes) & it->node()->nodeType()) == 0 )	continue;
                if ( compareFun( it->stringData(), sPattern ) )	{
                    if ( --iCount == 0 )
                        return it;
                }
            }
        }
        // Search backward
        else if ( iCount < 0 ) {
            LinearDomIF::const_iterator it = itEnd;

            for ( ; it > itBegin; ) {
                --it;
                if ( it == itStop ) return itEnd;	// Terminate search
                if ( (static_cast<uint32_t>(iNodeTypes) & it->node()->nodeType()) == 0 )	continue;
                if ( compareFun( it->stringData() , sPattern ) )	{
                    if ( ++iCount == 0 ) return it;
                }
            }
        }
        return itEnd;
    }





    LinearDomIF::const_iterator
            findPredStopAt(LinearDomIF::const_iterator itBegin
                    , LinearDomIF::const_iterator const& itEnd
                    , DomSeq const& seq
                    , int iCount
                    , int iNodeTypes
                    , const LinearDomIF::const_iterator& itStop
                    , const PtrStrVecT pArgs
                    )
    {
        if ( seq.subSequences().empty() ) return itEnd;
        LinearDomIF::const_iterator itFoundPos;
        //    printf("ML: findPredStopAt('%s')  subranges count: %d\n", seq.sequenceGet().c_str(), (int)seq.subSequences().size() );
        //    DomSeq::SubSequenceVecT::const_iterator itSubSeqs = seq.subSequences().begin();
        //    for (   ; itSubSeqs != seq.subSequences().end();  ++itSubSeqs ){
        //        DomSeq::StringComparePairVecT::const_iterator itSeqBeg = itSubSeqs->first;
        //        DomSeq::StringComparePairVecT::const_iterator itSeqEnd = itSubSeqs->second;
        //        DomSeq::StringComparePairVecT::const_iterator itSeq = itSubSeqs->first;
        //        std::cout << "ML: sub sequence: ";
        //        for ( ; itSeq != itSeqEnd; ++itSeq ) {
        //            std::cout << itSeq->pattern() << ", ";
        //        }
        //        std::cout << std::endl;
        //    }


        DomSeq::SubSequenceVecT::const_iterator itSubSeqs = seq.subSequences().begin();
        DomSeq::StringComparePairVecT::const_iterator itSeqBeg = itSubSeqs->first;
        DomSeq::StringComparePairVecT::const_iterator itSeqEnd = itSubSeqs->second;

        itFoundPos = findPredStopAtHelper(itBegin, itEnd, itSeqBeg, itSeqEnd, iCount, iNodeTypes, itStop, pArgs );

        ++itSubSeqs;
        while ( (itFoundPos != itEnd) && (itSubSeqs != seq.subSequences().end() ) ) {
            itSeqBeg = itSubSeqs->first;
            itSeqEnd = itSubSeqs->second;
            int iDir = iCount < 0 ? -1 : 1;
            itFoundPos = findPredStopAtHelper(itFoundPos, itEnd, itSeqBeg, itSeqEnd, iDir, iNodeTypes, itStop, pArgs );
            ++itSubSeqs;
        }

        return itFoundPos;
    }


    /** Find node near a given node. */
    LinearDomIF::const_iterator
            findNearest		(	LinearDomIF::const_iterator const& itBegin, 		///< [in] Beginning of interval
                                LinearDomIF::const_iterator const& itEnd, 		///< [in] End of interval
                                LinearDomIF::const_iterator const& itSearchFrom, 	///< [in] Start search from here
                                std::string const& sPattern, 							///< [in] String pattern to compare against
                                StringCompareFunT const& compareFun, 					///< [in] Compare function
                                ENearestDir searchDir,									///< [in] Search direction ( max NEAREST_BOTH i.e. don't use NEAREST_PARENT or NEAREST_AUTO here )
                                int iCount,												///< [in] Number of intances to match (node intances that matches)
                                int iNodeTypes)											///< [in] Node types to search see DomNodeIF::Type
    {
        if ( iCount < 1 )	return itEnd;
        LinearDomIF::const_iterator itFindForward;
        LinearDomIF::const_iterator itFindBackward;
        int iForwardDist	= std::numeric_limits<int>::max();
        int iBackwardDist	= std::numeric_limits<int>::max();

        if ( searchDir == NEAREST_THIS_NODE )	{
            return itSearchFrom;	// No search actually requested
        }

        if ( searchDir & NEAREST_FORWARD ) {
            itFindForward 	= findPredStopAt ( 	itSearchFrom, itEnd, sPattern, compareFun, iCount, iNodeTypes, itEnd );
            if ( itFindForward != itEnd ) 	iForwardDist	= itFindForward - itSearchFrom;
        }

        if ( searchDir & NEAREST_BACKWARD ) {
            LinearDomIF::const_iterator	itBkwdEnd   = itSearchFrom;
            if ( itBkwdEnd < itEnd )	++itBkwdEnd;	// Increment by one since when searchin backwards end of range is not considered, but we want forward and backward to be "equal in distance" so to speak.
            itFindBackward = findPredStopAt ( itBegin, itBkwdEnd, sPattern, compareFun, -iCount, iNodeTypes, itBkwdEnd );
            if ( itFindBackward != itBkwdEnd ) 	iBackwardDist = itSearchFrom - itFindBackward;
        }

        if ( 	iBackwardDist	== std::numeric_limits<int>::max() &&
                iForwardDist 	== std::numeric_limits<int>::max() 		)	return itEnd;

        if 		( iBackwardDist <= iForwardDist )	return itFindBackward 	;
        else 										return itFindForward	;
    }


    // -----------------------
    // --- Debug functions ---
    // -----------------------

    void debugPrint (
                    LinearDomIF::const_iterator const& /*itBegin*/, ///< Beginning of interval
                    LinearDomIF::const_iterator const& /*itEnd*/, 	///< End of interval
                    bool /*bTrimBlanks*/,
                    bool /*bPrintNodeTypes*/ )						///< Should we print node types as well
    {

        printf("TODO: Implement dom debugPrint with printf\n");
        //	for ( LinearDomIF::const_iterator it = itBegin; it != itEnd; ++it	) {
        //		LinearDomIF::printNode( *it, std::cout, bTrimBlanks, bPrintNodeTypes );
        //	}
        //	std::cout << std::endl;
    }

    std::string getDebugPrintString(
                    LinearDomIF::const_iterator const& itBegin, 	///< Beginning of interval
                    LinearDomIF::const_iterator const& itEnd, 	///< End of interval
                    bool bTrimBlanks,
                    bool bPrintNodeTypes )								///< Should we print node types as well
    {
        std::string s("");
        for ( LinearDomIF::const_iterator it = itBegin; it != itEnd; ++it	) {
            s += LinearDomIF::nodeToString	( it->node(), bTrimBlanks, bPrintNodeTypes );
        }
        return s;
    }

} // END namespace crawl
