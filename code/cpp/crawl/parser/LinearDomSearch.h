#pragma once

#include <LinearDomIF.h>
#include "linear_dom_algorithms.h"
#include <stack>

namespace crawl {

/** Search class 'incapsulation' of a linear DOM document.
@author Martin Lütken */
class LinearDomSearch {
public:
    typedef boost::shared_ptr<LinearDomSearch>		Ptr;
    typedef LinearDomIF::size_type                  size_type;

    // -------------------------------------------------
    // --- CONSTRUCTOR / INIT and DESTRUCTOR methods ---
    // -------------------------------------------------
    LinearDomSearch( LinearDomIF const& linearDom, crawl::RunModeE rm );

    void            debugMode               (bool bDebugMode )	{ m_bDebugMode = bDebugMode;	}
    bool            debugMode               () const            { return m_bDebugMode;			}

    void            debugPrintCurrentNode   ( int iNodesBefore, int iNodesAfter, bool bPrintNodeTypes = false ) const;
    std::string     debugGetCurrentNode     ( int iNodesBefore, int iNodesAfter, bool bPrintNodeTypes = false ) const;

    // ----------------------
    // --- Search methods ---
    // ----------------------
    void        newSearch           ();
    void        setCurrentPosToEnd  ();
    size_type   next                (std::string const& sSearchFor, StringCompareFunT const& compareFun, int iCount ,
                                     int iNodeTypes, bool bUpdateCurrentNode	);

    size_type   next                (DomSeq const& seq, int iCount , int iNodeTypes, bool bUpdateCurrentNode,
                                     const PtrStrVecT pArgs );
    size_type   step                (int iCount , int iNodeTypes );
    size_type   findFromTreeNode    (TreeNode* pNativeNode, bool bUpdateCurrentNode  );

    LinearDomIF::const_iterator     seekNearest             (std::string const& sPattern, StringCompareFunT const& compareFun,
                                                             ENearestDir searchDir, int iCount = 1,
                                                             int iNodeTypes = DomNodeTypes::ALL_NODE_TYPES );
    LinearDomIF::const_iterator     seekNearestElement      (std::string const& sElemType, ENearestDir searchDir,
                                                             int iCount = 1 );
    std::vector<size_type>          childPositions          (const size_type pos, const std::string& tagName) const;

    std::vector<size_type>          locatedPositions        () const    { return m_locatedPositions; }
    void                            locatedPositionsClear   ()          { m_locatedPositions.clear(); }



    // ----------------------
    // --- Access methods ---
    // ----------------------
    LinearDomIF::const_iterator     itCurElem       () const   { return m_itCurElem;		}
    const LinearDomNode&            curElem         () const   { return *m_itCurElem;  }
    boost::shared_ptr<DomNodeIF>    curElemPtr      () const;
    void                            iteratorPush    ()          { m_IterratorStack.push_back ( m_itCurElem ) ;	}
    size_type                       iteratorPop     ();
    size_type                       domSize         () const    { return m_linearDom.end() - m_linearDom.begin(); }
    size_type                       domEndPos       () const    { return m_linearDom.end() - m_linearDom.begin() +1;	}
    size_type                       iteratorPos     () const    { return iteratorToPos (m_itCurElem);					}

    size_type                       iteratorPos     ( size_type iNewPos );
    size_type                       setStartPos     (size_type iStartPos );
    size_type                       getStartPos     () const;
    void                            clearStartPos   ();

    size_type                       setStopPos      ( size_type iStopPos );
    size_type                       getStopPos      () const;
    void                            clearStopPos    ();
    void                            rangePush       ( size_type iStartPos, size_type iStopPos );
    void                            rangePop        ();


    LinearDomIF::const_iterator     posToIterator   ( size_type iDomPos ) const;
    size_type                       iteratorToPos   ( LinearDomIF::const_iterator it ) const;

    LinearDomIF::const_iterator     begin           () const	{	return m_linearDom.begin();	}
    LinearDomIF::const_iterator		end             () 	const	{	return m_linearDom.end();	}

    // --------------------
    // --- Info methods ---
    // --------------------
    bool                            atDomEnd        ()const     { return m_itCurElem >= m_linearDom.end() ;	}
    LinearDomIF const&              linearDom       () const    { return m_linearDom; 	}

private:
    // ---------------------------------
    // --- PRIVATE: Helper functions ---
    // ---------------------------------
    typedef std::pair<LinearDomIF::const_iterator,LinearDomIF::const_iterator>	NodeIteratorPairT;	///< Begin/End pair.
    typedef std::vector<LinearDomIF::const_iterator>	NodeIteratorStackT;	///< Container used for storing xx.

    struct Range { size_type start_pos; size_type stop_pos; };
    using RangeStack = std::stack<Range>;	///< Container used for storing dom start stop position pairs.

    NodeIteratorPairT	getBeginEndIterators( int iCount, bool& bOkToSearch );
    size_type           nextUpdateAndReturn( LinearDomIF::const_iterator it, bool bUpdateCurrentNode ) ;

    LinearDomIF::const_iterator
    itStart() const						{	return m_itStart;	}

    LinearDomIF::const_iterator
    itStop() const						{	return m_itStop;	}

    void                locatedPositionAdd      (size_type pos) const;
    void                locatedPositionsAdd     (const std::vector<LinearDomSearch::size_type>& positions) const;

    // ----------------------------
    // --- PRIVATE: Member data ---
    // ----------------------------
    LinearDomIF const&              m_linearDom;
    LinearDomIF::const_iterator     m_itCurElem;
    LinearDomIF::const_iterator 	m_itStart;
    LinearDomIF::const_iterator 	m_itStop;
    bool							m_bDebugMode;
    NodeIteratorStackT				m_IterratorStack;
    RangeStack                      m_rangeStack;
    mutable std::vector<size_type>  m_locatedPositions;
    crawl::RunModeE                 m_runMode;

};

} // END namespace crawl
