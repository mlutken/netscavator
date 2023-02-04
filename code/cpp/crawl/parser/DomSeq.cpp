
#include "DomSeq.h"
#include <map>
#include <boost/assign/list_of.hpp>
#include <cpaf_libs/utils/cpaf_string_utils.hpp>

using crawl::string_compare::G_StringCompareLookUp;
using namespace std;

namespace crawl {
using namespace string_compare;




DomSeq::DomSeq	(
    )
    : m_iCount (0)
    , m_sSequence("")
    , m_defaultCompareFun( string_compare::contains )
    , m_sCommaChar(",")
    , m_iPostMatchSteps( 0 )
{
}

DomSeq::DomSeq	(int                       iCount
    , const std::string& 		sPattern
    , const std::string&		sCompareFun
    , int 						iPostMatchSteps
    , int                       iNodeTypes
    , const std::string&		sCommaChar
    )
    : m_iCount(iCount)
    , m_sSequence(sPattern)
    , m_sDefaultCompareFun(sCompareFun)
    , m_defaultCompareFun(  G_StringCompareLookUp::fromAlias( sCompareFun )  )
    , m_sCommaChar(sCommaChar)
    , m_iNodeTypes(iNodeTypes)
{
    postMatchStepsSet(iPostMatchSteps);
    parseSequence( sPattern );
}

// TODO: This needs to be done en a better way!
int DomSeq::postMatchSteps() const
{
    return static_cast<int>((m_iPostMatchSteps & DomNodeTypes::REMOVE_NODE_TYPES)) * m_iPostMatchStepsSignFac;
}

// TODO: This needs to be done en a better way!
int DomSeq::postMatchStepsNodeTypes() const
{
    return static_cast<int>(m_iPostMatchSteps) & DomNodeTypes::ALL_NODE_TYPES;
}

void DomSeq::add	(
        const std::string& sPattern )
{
    m_comparePairs.push_back( StringComparePairT(sPattern, m_defaultCompareFun, 0 ) );
}


void DomSeq::add	(
     const std::string& 	sPattern
    ,const std::string&		sCompareFun
)
{
    m_comparePairs.push_back( StringComparePairT(sPattern, G_StringCompareLookUp::fromAlias(sCompareFun), 0 ) );
}

// ---------------------------------
// --- PRIVATE: Member functions ---
// ---------------------------------

void DomSeq::parseSequence ( const std::string& sSequence )
{
    using namespace cpaf;
    if ( sSequence == "" ) {
        m_comparePairs.clear();
        m_subSequences.clear();
        return;
    }

    StringVecT sv1;
    boost::split( sv1, sSequence, boost::is_any_of( m_sCommaChar ) );
    StringVecT::iterator it1 = sv1.begin();

    for ( ; it1 != sv1.end(); ++it1 ){
        std::string sPattern = boost::trim_copy( *it1 );
        StringCompareFunT compareFun = m_defaultCompareFun;
        int iSubstArgPos = 0;

        if ( startsWith ( sPattern, "\\#" ) ) {	boost::erase_first( sPattern, "\\" ); }		// Escaping '#' in case user really needs a pattern starting with '#'
        else if ( startsWith ( sPattern, "#" ) ) {
            size_t iEnd; // iBeg not used ??
            iEnd = sPattern.find_first_of(":");
            if ( iEnd != std::string::npos ) {
                std::string sCompareFun = boost::trim_copy( sPattern.substr(1, iEnd -1 ) );
                StringCompFunAliasMapT::const_iterator itComp = G_StringCompareLookUp::AliasMap.find( sCompareFun );
                if ( itComp != G_StringCompareLookUp::AliasMap.end() ) 	compareFun = itComp->second;

                if ( (iEnd +1) < sPattern.length() ) {
                    std::string sPatNew = sPattern.substr( iEnd +1);
                    sPattern = boost::trim_copy(sPatNew);
                    if ( startsWith ( sPattern, "\\#" ) ) {
                        printf("ML: Check to see if we ever hit this \n");
                        boost::erase_first( sPattern, "\\" );	// We need to test again in case pattern really needs to contain a '#'. Because here a starting '#' would be followed by a number, like '#1' for substituting params to domFindXXX
                    }
                }
            }
        }
        if ( startsWith(sPattern, "#" ) ) {
            string::iterator itArg = sPattern.begin() +1;
            iSubstArgPos = static_cast<int>( parse_long(itArg, sPattern.end()) );
            if ( iSubstArgPos < 1 || iSubstArgPos > 9  ) {
                iSubstArgPos = 0;
            }
        }

        m_comparePairs.push_back( StringComparePairT(sPattern, compareFun, iSubstArgPos) );
    }

    // --- Create subsequences by splitting at all '*' ---
    m_subSequences.clear();
    StringComparePairVecT::const_iterator itEND = m_comparePairs.end();
    StringComparePairVecT::const_iterator it    = m_comparePairs.begin();



    while ( it < itEND && it->pattern() == "*" ) ++it;    // Skip any preceeding *'s

    StringComparePairVecT::const_iterator itBeg = it;
    while ( it < m_comparePairs.end() )
    {
        if ( it->pattern() == "*" ) {
            m_subSequences.push_back( make_pair(itBeg, it) );
            while ( it < itEND && it->pattern() == "*" ) ++it;    // Skip also if consequtive *'s
            itBeg = it;
        }
        else {
            ++it;
        }
    }
    // Add last sub range ( or first and only in case no *'s was found )
    m_subSequences.push_back( make_pair(itBeg, it) );

}

void DomSeq::postMatchStepsSet(int iPostMatchSteps)
{
    m_iPostMatchSteps = static_cast<uint32_t>(std::abs(iPostMatchSteps));
    m_iPostMatchStepsSignFac = iPostMatchSteps < 0 ? -1 : 1;
}

} // END namespace crawl


