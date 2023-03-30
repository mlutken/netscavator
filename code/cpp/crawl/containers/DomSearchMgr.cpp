#include "DomSearchMgr.h"

#include <algorithm>
#include <iostream>

#include <boost/format.hpp>
#include <boost/lambda/lambda.hpp>
#include <boost/lambda/bind.hpp>
#include <cpaf_libs/utils/cpaf_string_utils.hpp>


using namespace std;

namespace crawl {


// ------------------------------------
// --- Constructor / Init Functions ---
// ------------------------------------
DomSearchMgr::DomSearchMgr()
{
}

void DomSearchMgr::prepareForRun()
{
    for (auto& pair: m_domSeqChoicesMap) {
        auto& choices = pair.second;
        std::sort(choices.begin(), choices.end(), DomSeqSort());
    }


//    cerr << "FIXMENM DomSearchMgr::prepareForRun()\n";
//    cerr << "Top level sequences count: " << m_domSeqChoicesMap.size() << "\n";
//    for (const auto& pair: m_domSeqChoicesMap) {
//        cerr << pair.first << " : " << pair.second.size() << "\n";
//        if (pair.second.size() == 154) {
//            for (const auto& domSec:  pair.second) {
//                cerr << "[" << domSec->choicesSortOrder() << "]  Name : " << domSec->name() << "\n";

//            }
//        }
//    }

}

void DomSearchMgr::clear()
{
    m_domSequences.clear();
    m_domSeqChoicesMap.clear();
}


// ------------------------
// --- DomSeq Functions ---
// ------------------------
void DomSearchMgr::domSeqAdd( const std::string& sName, boost::shared_ptr<DomSeq> pDomSeq)
{
    static int counter = 0;
    counter++;
    using namespace cpaf;

    // Add full name of domSeq allways. So even when using choice names like 'MyDomSeq#1', 'MyDomSeq#2',
    // where you would normally call it like: outputValueFindNext	( 1, "MyDomSeq?", "MyFieldName", .... ), you can still
    // also just use eg. : outputValueFindNext	( 1, "MyDomSeq#1", "MyFieldName", .... ) and
    // outputValueFindNext	( 1, "MyDomSeq#2", "MyFieldName", .... ).
    StringVecT vec;

    // If name contains a '#' use the part of the name up to the '#' as the actual name and use that
    // as lookup key in the choices map. (Each entry in the choices map has a vector of domSeqs )
    uint32_t domSeqChoiceNumber = 0;  // Sort as first if no number is given. Assume it's 0!
    splitv ( vec, sName, "#" );
    bool hasDomSeqChoiceNumber = false;
    if ( vec.size() >= 1 ) {
        int seqNum = 0;
        if ( vec.size() > 1 ) {
            hasDomSeqChoiceNumber = true;
            seqNum = cpaf::parse_int(vec[1], 0);
            domSeqChoiceNumber = seqNum < 0 ? 0 : static_cast<uint32_t>(seqNum);
        }
        const auto domSeqName = vec[0];
        pDomSeq->nameSet(domSeqName);
        if (!hasDomSeqChoiceNumber) {
            // If no '#' in DomSeq, then delete all choices and insert this new as number 1
            domSeqChoiceNumber = 1;
            m_domSeqChoicesMap[domSeqName].clear();
        }
        pDomSeq->choicesSortOrderSet(domSeqChoiceNumber);
        auto optIt = findDomSeqChoice(domSeqName, domSeqChoiceNumber);
        if (optIt) {
            auto vecIt = *optIt;
            *vecIt = pDomSeq;
        }
        else {
            m_domSeqChoicesMap[domSeqName].push_back(pDomSeq);
        }
    }
    m_domSequences[sName] = pDomSeq;
}

boost::shared_ptr<DomSeq> DomSearchMgr::domSeqGet( const std::string& sName ) const
{
    DomSeqMapT::const_iterator it = m_domSequences.find( sName );
    if ( it != m_domSequences.end() )	{
        return it->second;
    }
    else {

    }
    return boost::shared_ptr<DomSeq>();
}

DomSearchMgr::DomSeqVecRangeT
DomSearchMgr::domSeqChoicesGet( const std::string& sName ) const
{
    DomSeqChoicesMapT::const_iterator it = m_domSeqChoicesMap.find( sName );
    if ( it != m_domSeqChoicesMap.end() )	{
        return DomSearchMgr::DomSeqVecRangeT ( it->second.begin(), it->second.end() );
    }
    else	{
        return DomSearchMgr::DomSeqVecRangeT ();
    }
}

bool
DomSearchMgr::domSeqChoicesExists( const std::string& sName ) const
{
    const auto it = m_domSeqChoicesMap.find(sName);
    const auto found = it != m_domSeqChoicesMap.end();
    return found && !it->second.empty();
}

bool
DomSearchMgr::domSequenceExists( const std::string& sName ) const
{
    return  m_domSequences.find(sName) != m_domSequences.end() ||
            m_domSeqChoicesMap.find(sName) != m_domSeqChoicesMap.end();
}

size_t DomSearchMgr::size() const
{
    return m_domSequences.size();
}

DomSearchMgr::DomSeqVecT* DomSearchMgr::domSeqChoices(const std::string& name)
{
    const auto it = m_domSeqChoicesMap.find(name);
    if (it == m_domSeqChoicesMap.end()) { return nullptr; }
    DomSearchMgr::DomSeqVecT& domChoicesSet = it->second;
    return &domChoicesSet;
}


DomSearchMgr::value_type DomSearchMgr::at(size_t index) const
{
    size_t i = 0;
    for (const auto& pair: m_domSequences) {
//        if (pair.second->choicesSortOrder() == index) {
//            return pair;
//        }
        if (i++ == index) {
            return pair;
        }
    }
    return DomSearchMgr::value_type();
}

std::optional<DomSearchMgr::DomSeqVecT::iterator>
DomSearchMgr::findDomSeqChoice(const std::string& name, uint32_t choicesSortOrder)
{
    auto* choices = domSeqChoices(name);
    if (!choices) { return {}; }
    DomSearchMgr::DomSeqVecT::iterator it = std::find_if(choices->begin(), choices->end(),
                            [=](boost::shared_ptr<DomSeq>& ds){
                                return ds->choicesSortOrder() == choicesSortOrder;
                            }
            );

    if (it == choices->end()) { return {}; }

    return it;
}

} // END namespace crawl


