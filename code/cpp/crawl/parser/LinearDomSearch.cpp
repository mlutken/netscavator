

#include <iostream>
#include <boost/format.hpp>
#include <math/base/utils.hpp>
////#include "DomDocumentLinear.h"
#include "LinearDomSearch.h"
#include <DomNodeIF.h>

namespace crawl {



// -------------------------------------------------
// --- CONSTRUCTOR / INIT and DESTRUCTOR methods ---
// -------------------------------------------------
LinearDomSearch::LinearDomSearch(LinearDomIF const& linearDom
, RunModeE rm) :	m_linearDom     ( linearDom ),
    m_itCurElem     ( m_linearDom.begin() ),
    m_itStart       ( m_linearDom.begin() ),
    m_itStop        ( m_linearDom.end() ),
    m_bDebugMode    ( false ),
    m_runMode       (rm)
{
}


void
LinearDomSearch::debugPrintCurrentNode(
    int iNodesBefore, 				///< [in] Number of nodes to print before the current node (positive number always)
    int iNodesAfter, 				///< [in] Number of nodes to print after the current node (positive number always)
    bool bPrintNodeTypes 			///< [in] Print the node types also
) const
{
    iNodesBefore = abs(iNodesBefore);
    iNodesAfter = abs(iNodesAfter);
    LinearDomIF::const_iterator itBegin = m_itCurElem - iNodesBefore;
    LinearDomIF::const_iterator itEnd = m_itCurElem + iNodesAfter;
    if ( itBegin < m_linearDom.begin() )	itBegin = m_linearDom.begin();
    if ( itEnd > m_linearDom.end() )		itEnd = m_linearDom.end();
    debugPrint ( itBegin, itEnd, bPrintNodeTypes );
}

std::string
LinearDomSearch::debugGetCurrentNode(
    int iNodesBefore, 				///< [in] Number of nodes to print before the current node (positive number always)
    int iNodesAfter, 				///< [in] Number of nodes to print after the current node (positive number always)
    bool bPrintNodeTypes 			///< [in] Print the node types also
) const
{
    iNodesBefore = abs(iNodesBefore);
    iNodesAfter = abs(iNodesAfter);
    LinearDomIF::const_iterator itBegin = m_itCurElem - iNodesBefore;
    LinearDomIF::const_iterator itEnd = m_itCurElem + iNodesAfter;
    if ( itBegin < m_linearDom.begin() )	itBegin = m_linearDom.begin();
    if ( itEnd > m_linearDom.end() )		itEnd = m_linearDom.end();
    return getDebugPrintString ( itBegin, itEnd, bPrintNodeTypes );
}

// ----------------------
// --- Search methods ---
// ----------------------

void LinearDomSearch::newSearch ()
{
    m_itCurElem = itStart();
}


/** */
LinearDomSearch::size_type
LinearDomSearch::next	(
    std::string const& sSearchFor, 			///<
    StringCompareFunT const& compareFun, 	///<
    int iCount,								///<
    int iNodeTypes,							///<
    bool bUpdateCurrentNode
)
{
    bool bOkToSearch 			= false;
    NodeIteratorPairT interVal 	= getBeginEndIterators( iCount, bOkToSearch );
    LinearDomIF::const_iterator it = m_linearDom.end();
    if ( bOkToSearch ) 	{
        it = findPredStopAt ( interVal.first, interVal.second, sSearchFor, compareFun, iCount, iNodeTypes, itStop() );
    }
    return nextUpdateAndReturn( it, bUpdateCurrentNode );
}


LinearDomSearch::size_type
LinearDomSearch::next	(
      DomSeq const& seq
    , int iCount
    , int iNodeTypes							///<
    , bool bUpdateCurrentNode
    , const PtrStrVecT pArgs
)
{
    using namespace std;
    iNodeTypes = iNodeTypes & seq.nodeTypes();  // Set nodetypes by bitwise AND of the directly requested and those from the sequence
    if (seq.count() != 0) iCount = seq.count();

    LinearDomIF::const_iterator itCurElemSave = m_itCurElem;
    bool bOkToSearch 			= false;
    NodeIteratorPairT interVal 	= getBeginEndIterators( iCount, bOkToSearch );
    LinearDomIF::const_iterator it = m_linearDom.end();

    if ( bOkToSearch ) 	{
        it = findPredStopAt ( interVal.first, interVal.second, seq, iCount, iNodeTypes, itStop(), pArgs );
    }
    size_type iPos = nextUpdateAndReturn( it, bUpdateCurrentNode );
    if ( iPos && seq.postMatchSteps() ) {
        // Check if post match steps should be restricted to another subset of node types than the original dom searcg matching...
        int postMatchStepsNodeTypes = seq.postMatchStepsNodeTypes();
        if (postMatchStepsNodeTypes)
            iNodeTypes = postMatchStepsNodeTypes;
        iPos = step( seq.postMatchSteps(), iNodeTypes );
        if ( !iPos ) m_itCurElem = itCurElemSave;
    }
    return iPos;
}



LinearDomSearch::size_type
LinearDomSearch::step (
    int iCount,
    int iNodeTypes
)
{
    if ( m_itCurElem >= m_linearDom.end() )	return false;

    if ( iCount > 0 ) {
        while ( iCount > 0 && ( ++m_itCurElem < m_linearDom.end() ) ) {
            if ( m_itCurElem->node()->nodeType() & static_cast<uint32_t>(iNodeTypes) )	--iCount;
        }
        return m_itCurElem < m_linearDom.end() ? iteratorPos() : 0;
    }
    else {
        bool bFound = false;
        while ( !bFound && ( m_itCurElem > m_linearDom.begin() ) ) {
            --m_itCurElem;
            if ( m_itCurElem->node()->nodeType() & static_cast<uint32_t>(iNodeTypes) )	{
                if ( ++iCount == 0 )	bFound = true;
            }
        }
        return bFound ? iteratorPos() : 0;
    }
}

LinearDomSearch::size_type
LinearDomSearch::findFromTreeNode (
        TreeNode* pNativeNode
        , bool bUpdateCurrentNode  )
{
    LinearDomIF::const_iterator it = m_linearDom.findFromTreeNode(pNativeNode);
    return nextUpdateAndReturn( it, bUpdateCurrentNode );
}

LinearDomIF::const_iterator
LinearDomSearch::seekNearest		(
    std::string const& sPattern, 							///< [in] String pattern to compare against
    StringCompareFunT const& compareFun, 					///< [in] Compare function
    ENearestDir searchDir,									///< [in] Search direction
    int iCount,												///< [in] Number of intances to match (node intances that matches)
    int iNodeTypes)											///< [in] Node types to search see DOMNode::Type
{
    return findNearest ( m_linearDom.begin(), m_linearDom.end(), m_itCurElem, sPattern, compareFun, searchDir, iCount, iNodeTypes );
}


LinearDomIF::const_iterator
LinearDomSearch::seekNearestElement	(
    std::string const& sElemType, 	///< [in] Element type name (e.g. INPUT ) to search for. If this string is empty all element types are matched against.
    ENearestDir searchDir, 			///< [in] Search direction
    int iCount )					///< [in] Number of intances to match (node intances that matches)
{
    if  ( sElemType.empty() )	return seekNearest( "", 		string_compare::alwaysTrue, searchDir, iCount, DomNodeTypes::ELEMENT ) ;
    else 						return seekNearest( sElemType, 	string_compare::equals, 	searchDir, iCount, DomNodeTypes::ELEMENT ) ;
}

std::vector<LinearDomSearch::size_type> LinearDomSearch::childPositions(const size_type pos, const std::string& tagName) const
{
    auto positions = m_linearDom.childPositions(pos, tagName);
    locatedPositionsAdd(positions);
    return positions;
}


// ----------------------
// --- Access methods ---
// ----------------------

boost::shared_ptr<DomNodeIF>
LinearDomSearch::curElemPtr() const
{
    if ( m_itCurElem >= m_linearDom.end() ) {
        if ( m_bDebugMode ) printf( "ERROR: End of dom (LinearDomSearch::curElemPtr())\n" );
        return boost::shared_ptr<DomNodeIF>();	// Return 'NULL' pointer !!!
    }
    return m_itCurElem->node();
}

LinearDomSearch::size_type
LinearDomSearch::iteratorPop()
{
    if (m_IterratorStack.size() > 0 ) {
        m_itCurElem = m_IterratorStack.back();
        m_IterratorStack.pop_back();
        return iteratorPos();
    }
    return 0;
}



/// Set current dom iterator from dom node position
///  \note In case of iNewDomPos == 0, we don't change current domPos
LinearDomSearch::size_type
LinearDomSearch::iteratorPos( LinearDomSearch::size_type iNewDomPos )
{
    LinearDomIF::const_iterator itNew = m_linearDom.begin() -1 + static_cast<ptrdiff_t>(iNewDomPos);
    cpaf::math::clamp(itNew, m_itStart, m_itStop);
    if ( m_linearDom.begin() <= itNew && itNew < m_linearDom.end() ) {
        m_itCurElem = itNew;

        return iteratorPos();
    }
    return 0;
}

/// Set current dom start at position
///  \note In case of iStartPos == 0, we set current start pos to start of dom
/// \return New startPos or zero if input startpos was zero.
LinearDomSearch::size_type
LinearDomSearch::setStartPos( size_type iStartPos )
{
    using namespace std;

    // NOTE: domStartPos should be beginDomPos when iStartPos is zero.
    if ( iStartPos == 0 ) {
        m_itStart = m_linearDom.begin();
        return 0;
    }
    else {
        m_itStart = posToIterator( iStartPos );
        if (m_itStart > m_itCurElem)
            m_itCurElem = m_itStart;

        return iteratorToPos ( m_itStart );
    }
}


LinearDomSearch::size_type
LinearDomSearch::getStartPos() const
{
    return iteratorToPos ( m_itStart );
}

void
LinearDomSearch::clearStartPos()
{
    m_itStart = m_linearDom.begin();
}


/// Set current dom stop at position
///  \note In case of iStopPos == 0, we set current stop pos to end of dom
/// \return New stopPos or zero if input stoppos was zero.
LinearDomSearch::size_type
LinearDomSearch::setStopPos( size_type iStopPos )
{
    // NOTE: domStopPos should be endDomPos when iStopPos is zero.
    if ( iStopPos == 0 ) {
        m_itStop = m_linearDom.end();
        return 0;
    }
    else {
        m_itStop = posToIterator( iStopPos );
        return iteratorToPos ( m_itStop );
    }
}

LinearDomSearch::size_type
LinearDomSearch::getStopPos() const
{
    return iteratorToPos ( m_itStop );
}

void
LinearDomSearch::clearStopPos()
{
    m_itStop = m_linearDom.end();
}

void LinearDomSearch::rangePush(size_type iStartPos, size_type iStopPos)
{
    m_rangeStack.push({getStartPos(), getStopPos()});
    setStartPos(iStartPos);
    setStopPos(iStopPos);
}

void LinearDomSearch::rangePop()
{
    const auto& range = m_rangeStack.top();
    setStartPos(range.start_pos);
    setStopPos(range.stop_pos);
    m_rangeStack.pop();
}



/// Get iterator from dom node position
LinearDomIF::const_iterator
LinearDomSearch::posToIterator( size_type iDomPos ) const
{
    return m_linearDom.posToIterator( iDomPos );
}

LinearDomIF::size_type
LinearDomSearch::iteratorToPos( LinearDomIF::const_iterator it ) const
{
    return m_linearDom.iteratorToPos(it);
}


// --------------------
// --- Info methods ---
// --------------------


// ---------------------------------
// --- PRIVATE: Helper functions ---
// ---------------------------------

LinearDomSearch::NodeIteratorPairT	LinearDomSearch::getBeginEndIterators( int iCount, bool& bOkToSearch )
{
    if (m_itStart > m_itCurElem)
        m_itCurElem = m_itStart;
    bOkToSearch = false;
    NodeIteratorPairT interVal ( m_linearDom.begin(), m_linearDom.end() );
    if ( iCount > 0 ) {
        if ( m_itCurElem == m_linearDom.begin()  ) {
            bOkToSearch = true;
        }
        else if ( m_itCurElem +1 < m_linearDom.end() ) {
            bOkToSearch = true;
            interVal.first = m_itCurElem +1;
        }
    }
    else {
        bOkToSearch = true;
        interVal.second = m_itCurElem;
    }
    return interVal;
}


/// Updates ( if requested ) the current node pointer and returns the position found
LinearDomIF::size_type
LinearDomSearch::nextUpdateAndReturn( LinearDomIF::const_iterator it, bool bUpdateCurrentNode )
{
    size_type pos = 0;
    if ( it != m_linearDom.end() ) {
        if ( bUpdateCurrentNode ) m_itCurElem = it;
        pos = iteratorToPos(it);
    }
    if ( bUpdateCurrentNode ) m_itCurElem = it; // TODO: Observe if it's ok to update also when not found. Seems ok.
    locatedPositionAdd(pos);
    return pos;
}

void LinearDomSearch::locatedPositionAdd(size_type pos) const
{
    if (runModeCreator(m_runMode)) {
        m_locatedPositions.push_back(pos);
    }
}

void LinearDomSearch::locatedPositionsAdd(const std::vector<size_type>& positions) const
{
    if (runModeCreator(m_runMode)) {
        std::copy(positions.begin(), positions.end(),  std::back_inserter(m_locatedPositions));
    }
}

} // END namespace crawl
