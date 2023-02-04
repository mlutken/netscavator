#pragma once

#include <string>
#include <vector>
#include <limits>
#include <boost/shared_ptr.hpp>
#include <boost/enable_shared_from_this.hpp>
#include <boost/function.hpp>
#include <QString>

#include <html/ParserDom.h>
#include <DomNodeIF.h>

namespace crawl {
class XPath;

class WebBrowserIF;

class LinearDomNode  {
public:
    static constexpr int no_owner_pos = std::numeric_limits<int>::max();
    explicit LinearDomNode( boost::shared_ptr<DomNodeIF> pNode );
    LinearDomNode(TreeNode* treeNode, boost::shared_ptr<DomNodeIF> node, const std::string& string_data, int parent_pos,
                  int depth_level, int32_t node_type);
    LinearDomNode(TreeNode* treeNode, boost::shared_ptr<DomNodeIF> node, const QString& string_data, int parent_pos,
                  int depth_level, int32_t node_type);

    TreeNode*                       treeNode        () const { return m_treeNode; }
    const TreeNode*                 treeNodeConst   () const { return m_treeNode; }
    void                            qstringDataSet  (const QString& string_data) { m_string_data = string_data.toUtf8().constData();}
    QString                         qstringData     () const { return QString::fromUtf8(m_string_data.c_str());}
    const std::string&              stringData      () const { return m_string_data; }
    int32_t                         nodeType        () const { return m_node_type; }
    boost::shared_ptr<DomNodeIF>    node            () const;
    std::vector<int>                childPositions  () const;
    XPath                           xpath           () const;

    int    parentPos        () const                { return m_parent_pos; }
    void   parentPosSet     (int owner_pos)         { m_parent_pos = owner_pos;}
    int    depthLevel       () const                { return m_depth_level; }
    void   depthLevelSet    (int depth_level)       { m_depth_level = depth_level;}
    int    thisPos          () const                { return m_this_pos; }
    void   thisPosSet       (int this_pos)          { m_this_pos = this_pos;}
    bool   hasOwner         () const                { return m_parent_pos != no_owner_pos; }

private:
    TreeNode*                       m_treeNode;
    boost::shared_ptr<DomNodeIF>    m_node;
    std::string                     m_string_data;
    int                             m_parent_pos;
    int                             m_depth_level;
    int32_t                         m_node_type;
    int                             m_this_pos;
    bool                            m_children_initialized = false;
    //QString                         m_string_data;
};

class LinearDomIF : public boost::enable_shared_from_this<LinearDomIF> {
public:
    typedef boost::function< void (boost::shared_ptr<DomNodeIF>, std::ostream&, bool, bool ) >		PrintNodeFunT;	///< Prototype for node print function

    typedef std::vector<LinearDomNode>				NodeContainerT;     ///< Container used for storing the (node pointers of) the "linearised" document.
    typedef NodeContainerT::iterator				iterator;
    typedef NodeContainerT::const_iterator			const_iterator;
    typedef NodeContainerT::reverse_iterator		reverse_iterator;
    typedef NodeContainerT::const_reverse_iterator	const_reverse_iterator;
    using size_type = int;

    // -------------------------------------------------
    // --- CONSTRUCTOR / INIT and DESTRUCTOR methods ---
    // -------------------------------------------------
    LinearDomIF(boost::shared_ptr<WebBrowserIF> pBrowser);
    virtual ~LinearDomIF() {}

    // -----------------------
    // --- Browser methods ---
    // -----------------------
    void                            browserSet  ( boost::shared_ptr<WebBrowserIF> pBrowser )    { m_pBrowser = pBrowser; }
    boost::shared_ptr<WebBrowserIF> browser     () const    { return m_pBrowser; }


    // -------------------
    // --- STL methods ---
    // -------------------
    iterator 				begin   () 			{	return m_LinearNodes.begin();	}
    const_iterator 			begin   () 	const 	{	return m_LinearNodes.begin();	}
    const_iterator 			cbegin  () 	const 	{	return m_LinearNodes.cbegin();	}
    iterator 				end     () 			{	return m_LinearNodes.end()	;	}
    const_iterator 			end     () 	const 	{	return m_LinearNodes.end()	;	}
    const_iterator 			cend    () 	const 	{	return m_LinearNodes.cend()	;	}

    reverse_iterator 		rbegin  () 			{	return m_LinearNodes.rbegin();	}
    const_reverse_iterator 	rbegin  () 	const 	{	return m_LinearNodes.rbegin();	}
    reverse_iterator 		rend    () 			{	return m_LinearNodes.rend()	;	}
    const_reverse_iterator 	rend    () 	const 	{	return m_LinearNodes.rend()	;	}

    // --------------------
    // --- Node methods ---
    // --------------------
    TreeNode*               treeNode            (size_type pos) const;
    TreeNode*               treeNode            (const_iterator it) const;
    size_type               parentPos           (size_type pos,  int levels_up) const;
    size_type               ownerPos            (size_type pos,  int levels_up) const;
    size_type               endTagPos           (size_type parentPos) const;
    size_type               thisElementPos      (size_type pos) const;
    std::vector<size_type>  childPositions      (const size_type pos, const std::string& tagName) const;
    std::vector<size_type>  childPositionsAll   (const size_type pos) const;
    std::string             attribute           (const size_type pos, const std::string& key, const std::string& default_val = "") const;
    std::string             toXPathStringList   (const std::vector<int>& domPositions) const;
    XPath                   toXPath             (const size_type pos) const;
    XPath                   toXPath             (const_iterator it) const;

    // --------------------
    // --- Misc methods ---
    // --------------------
    void                    pushBackNode        ( const LinearDomNode& node );
    void                    clearNodes          ();

    const_iterator          findFromTreeNode    (const TreeNode* treeNode ) const               { return do_findFromTreeNode(treeNode);  }
    const_iterator          findFromXPath       (const XPath& xpath) const                      { return do_findFromXPath(xpath);             }
    TreeNode*               rootNode            ()         { return do_rootNode();      }
    const TreeNode*         rootNode            () const   { return do_rootNode();      }
    DomTree*                domTree             () const   { return do_domTree();       }

    const_iterator          posToIterator       ( size_type iDomPos ) const;
    size_type               iteratorToPos       ( const_iterator it ) const;
    size_type               treeNodeToPos       (const TreeNode* treeNode ) const;
    std::vector<size_type>  treeNodesToPositions(std::vector<TreeNode*> treeNodes) const;
    std::vector<size_type>  treeNodesToPositions(std::vector<const TreeNode*> treeNodes) const;

    void                    print               ( std::ostream& os, bool bPrintNodeTypes  ) const ;
    void                    assignPrintNodeFun  ( PrintNodeFunT const& printNodeFun )      {	m_PrintNodeFun	= printNodeFun;	}
    const LinearDomNode&    operator[]          (size_type domPos) const;
    LinearDomNode&          operator[]          (size_type domPos);

    // -------------------------------------
    // --- Simple inline get/set methods ---
    // -------------------------------------
    size_type           size            () 	const                   {	return static_cast<size_type>(m_LinearNodes.size()); }
    constexpr size_type	firstDomPos     () 	const                   {	return 1;                               }
    size_type           lastDomPos      () 	const                   {	return static_cast<size_type>(size());  }
    bool                posValid        (int pos) const             {	return pos > 0 && pos <= lastDomPos();  }

    bool                printNodeTypes  () 	const                   {	return m_bPrintNodeTypes;				}
    void                printNodeTypes  ( bool bPrintNodeTypes )    {	m_bPrintNodeTypes = bPrintNodeTypes;	}

    // ----------------------
    // --- Static methods ---
    // ----------------------
    static 	std::string		nodeToString( boost::shared_ptr<DomNodeIF> pNode, 					bool bTrimBlanks,  bool bPrintNodeType	) ;
    static	void			printNode	( boost::shared_ptr<DomNodeIF> pNode, std::ostream& os, bool bTrimBlanks,  bool bPrintNodeType	) ;


    void    dbgPrintLinearDom   () const;

private:
     using internal_size_type = NodeContainerT::size_type;

    void                    setDataForLastAddedLinearDomNode   ();
    // -----------------------------------------
    // --- PRIVATE: Implementation functions ---
    // -----------------------------------------
//    virtual const_iterator  do_findFromRawPointer   (boost::shared_ptr<DomNodeIF> pDomNode ) const  = 0;
    virtual const_iterator  do_findFromTreeNode     (const TreeNode* pNativeNode) const;
    virtual const_iterator  do_findFromXPath        (const XPath& xpath) const;
    virtual TreeNode*       do_rootNode             ()                  = 0;
    virtual const TreeNode* do_rootNode             () const            = 0;
    virtual DomTree*        do_domTree              () const            = 0;

    // ----------------------------
    // --- PRIVATE: Member data ---
    // ----------------------------
    NodeContainerT                      m_LinearNodes;
    boost::shared_ptr<WebBrowserIF>     m_pBrowser;
    PrintNodeFunT                       m_PrintNodeFun;
    bool                                m_bPrintNodeTypes;          ///< If true we also print node types in front of all nodes.
};


/** '<<' operator, Write LinearDomIF to stream.
\return Reference to (modified) ostream. */
inline std::ostream&
        operator << (	std::ostream& os,				///< [out] Output stream to write to.
                        LinearDomIF const&	domLinenar)	///< [in] DomDocumentLinear to write.
{
    domLinenar.print( os, domLinenar.printNodeTypes() );
    return os;
}

} // END namespace crawl
