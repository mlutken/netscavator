#pragma once

#include <map>
#include <vector>
#include <set>
#include <string>
#include <optional>
#include <boost/shared_ptr.hpp>
#include <boost/range/iterator_range.hpp>

#include <parser/DomSeq.h>


namespace crawl {


/**
XXX Brief description XXX.
XXX Detailed description here ... XXX
\author Veriquin */
class DomSearchMgr
{
public:
    struct DomSeqSort {
        bool operator() (const boost::shared_ptr<DomSeq>& a, const boost::shared_ptr<DomSeq>& b) const {
            return a->choicesSortOrder() < b->choicesSortOrder();
        }
    };

    // ----------------
    // --- Typedefs ---
    // ----------------
    using DomSeqVecT        = std::vector<boost::shared_ptr<DomSeq>>;
    using DomSeqVecRangeT   = boost::iterator_range<DomSeqVecT::const_iterator>;
    using DomSeqMapT        = std::map<std::string, boost::shared_ptr<DomSeq>>;
    using value_type        = std::pair<std::string, boost::shared_ptr<DomSeq>>;
    using DomSeqChoicesMapT = std::map<std::string, DomSeqVecT>;

    // ------------------------------------
    // --- Constructor / Init Functions ---
    // ------------------------------------
    DomSearchMgr();
    void prepareForRun();
    void clear();

    // -------------------------
    // --- DomSeq Functions ---
    // -------------------------
    void						domSeqAdd			( const std::string& sName, boost::shared_ptr<DomSeq> pDomSeq );
    boost::shared_ptr<DomSeq>	domSeqGet			( const std::string& sName ) const;
    DomSeqVecRangeT				domSeqChoicesGet	( const std::string& sName ) const;
    bool						domSeqChoicesExists	( const std::string& sName ) const;
	bool						domSequenceExists	( const std::string& sName ) const;
    size_t                      size                () const;
    DomSeqVecT*                 domSeqChoices       (const std::string& name);
    const DomSeqChoicesMapT&    domSeqChoicesMap    () const { return m_domSeqChoicesMap; }

    /** Get sequence at index.
     *  Get the dom sequence at index. They are ordered alphabetically
     * in the underlying map. It's for use in the DesignView in the Creator
     * which uses a Qt TableView and need a vector like interfacve to
     * the list of dom sequences.
        \note Only intended for use in Creator, since it's slow.
        */
    value_type                  at                  (size_t index) const;

private:
    std::optional<DomSeqVecT::iterator>
                                findDomSeqChoice    (const std::string& name, uint32_t choicesSortOrder);

    // -------------------
    // --- Member Data ---
    // -------------------
    DomSeqMapT                  m_domSequences;
    DomSeqChoicesMapT           m_domSeqChoicesMap;
};


} // END namespace crawl

