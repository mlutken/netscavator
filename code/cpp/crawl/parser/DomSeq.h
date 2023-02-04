#pragma once

#include <vector>
#include <utils/string_algorithms.h>
#include <boost/range.hpp>
#include <utils/string_compare_functions.h>
#include <interfaces/DomNodeIF.h>

namespace crawl {

typedef boost::shared_ptr<std::vector<std::string> >    PtrStrVecT;

/**
Sequence of pairs of (dom nodes, compare functions) for use in searching
a linear dom.
\author Martin Lütken */
class DomSeq
{
public:
    // ----------------
    // --- Typedefs ---
    // ----------------
    struct StringComparePairT
    {
    private:
        std::string         sPattern;
    public:
        StringCompareFunT   compareFun;
        int                 iSubstArgumentPos;
        StringComparePairT ( const std::string& sPattrn, const StringCompareFunT& compFun, int iSubstArgPos )
            : sPattern(sPattrn), compareFun(compFun), iSubstArgumentPos(iSubstArgPos) {}
        const std::string&  pattern() const { return sPattern; }
        const std::string&  pattern( const PtrStrVecT pArgs ) const
        {
            if ( (iSubstArgumentPos == 0) || !pArgs )   return sPattern;
            if ( (iSubstArgumentPos > 0) && ( iSubstArgumentPos <= static_cast<int>(pArgs->size()) ) ) {
                return (*pArgs)[ static_cast<size_t>(iSubstArgumentPos-1)];
            }
            return sPattern;
        }
    };

    typedef std::vector<StringComparePairT>				StringComparePairVecT;
    typedef StringComparePairVecT::const_iterator		const_iterator;

    typedef std::pair <StringComparePairVecT::const_iterator, StringComparePairVecT::const_iterator >   SubSequenceT;
    typedef std::vector<SubSequenceT>                   SubSequenceVecT;

    typedef StringComparePairT							value_type;
    typedef StringComparePairVecT::size_type			size_type;

    // --------------------
    // --- Constructors ---
    // --------------------
    DomSeq	();
    DomSeq	(	int iCount, const std::string& sPattern, const std::string& sCompareFun, int iPostMatchSteps, int iNodeTypes, const std::string& sCommaChar );

    // --------------------------------
    // --- PUBLIC: Member functions ---
    // --------------------------------

    int					count                   () const 		{ return m_iCount;	}
    const std::string&  sequenceGet             () const        { return m_sSequence;       }
    const std::string&  defaultCompareFunNameGet() const        { return m_sDefaultCompareFun; }
    int					postMatchSteps          () const;
    int					postMatchStepsNodeTypes	() const;
    DomNodeTypes::node_type_type   nodeTypes               () const 		{ return m_iNodeTypes & DomNodeTypes::ALL_NODE_TYPES;	}

    const std::string&  name                    () const            { return m_name; }
    void                nameSet                 (std::string name)  { m_name = std::move(name); }

    uint32_t            choicesSortOrder        () const { return m_iChoicesSortOrder; }
    void                choicesSortOrderSet     (uint32_t sortOrder) { m_iChoicesSortOrder = sortOrder; }

    void				add     ( const std::string& sPattern )	;
    void				add     ( const std::string& sPattern, const std::string& sCompareFun );

    size_type			size	() 	const	{	return m_comparePairs.size();		}
    size_type			getSize	() 	const	{	return m_comparePairs.size();		}

    const_iterator		begin	() 	const	{	return m_comparePairs.begin();		}
    const_iterator		end		() 	const	{	return m_comparePairs.end();		}

    value_type const&	front	() 	const	{	return *m_comparePairs.begin();		}
    value_type const&	back	() 	const	{	return *(m_comparePairs.end()-1);	}
    bool                empty   () const    {   return 0 == subSequences().size();  }

    const SubSequenceVecT&      subSequences    () const { return m_subSequences; }

private:
    // --- PRIVATE: Member functions ---
    void 	parseSequence       ( const std::string& sSequence );
    void    postMatchStepsSet   (int iPostMatchSteps);

    // --- PRIVATE: Member data ---
    int                         m_iCount;          ///< To 'override' the iCount parameter to domFind functions
    std::string                 m_sSequence;
    std::string                 m_name;
    StringComparePairVecT		m_comparePairs;
    SubSequenceVecT             m_subSequences;         ///< The full sequence split at every '*'
    std::string                 m_sDefaultCompareFun;
    StringCompareFunT			m_defaultCompareFun;
    std::string					m_sCommaChar;
    uint32_t					m_iPostMatchSteps = 0;
    int32_t                     m_iPostMatchStepsSignFac = 1;
    uint32_t                    m_iChoicesSortOrder = 0;
    DomNodeTypes::node_type_type	m_iNodeTypes = crawl::DomNodeTypes::ALL_NODE_TYPES;
};

} // END namespace crawl


