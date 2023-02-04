#include "AutoInputState.h"
#include <stdio.h>
#include <iostream>
#include <cmath>
#include <algorithm>
#include <boost/algorithm/string.hpp>
#include <cpaf_libs/utils/cpaf_string_utils.hpp>
#include <cpaf_libs/utils/cpaf_stl_utils.h>

using namespace std;

namespace crawl {

    // ------------------------------------
    // --- Static member initialization ---
    // ------------------------------------


    // ------------------------------------
    // --- Constructor / Init Functions ---
    // ------------------------------------
    AutoInputState::AutoInputState  (
          const std::string& sCharsList
        , int iMinLength
        , int iMaxLength
        )   : m_iMinLevel(iMinLength > 0 ? iMinLength -1 : 1)
            , m_iMaxLevel(iMaxLength > 0 ? iMaxLength -1 : 1)
            , m_iCurLevel(m_iMinLevel)
            , m_bAtEndOption(false)
            , m_state(static_cast<size_t>(m_iMaxLevel)+1u,0)
            , m_stateFirst(static_cast<size_t>(m_iMaxLevel)+1u,0)
            , m_stateLast(static_cast<size_t>(m_iMaxLevel)+1u,0)
            , m_stateBegin(static_cast<size_t>(m_iMaxLevel)+1u,0)
            , m_stateEnd(static_cast<size_t>(m_iMaxLevel)+1u,0)
    {
        cpaf::splitv( m_chars, std::string("#,") + sCharsList + ",$", "," );
        createCharsLookUp();
        fill_n ( m_stateFirst.begin(), m_iMinLevel+1, 1 );                       // Default start state eg. (1,1,0...)
        fill_n ( m_stateLast.begin(), m_iMinLevel+1, m_chars.size()-1 );    // Last state eg. (25,25,0...)
        m_state     = m_stateFirst;
        m_stateEnd  = m_stateLast;
    }

    // --------------------------------------------------
    // --- PRIVATE: Abstract interface (do) functions ---
    // --------------------------------------------------
    void AutoInputState::do_currentOptionIndexSet(boost::int64_t /*iIndex*/ )
    {
        printf("TODO: Implement AutoInputState::do_setCurrentOptionIndex\n");
    }

    boost::int64_t AutoInputState::do_currentOptionIndexGet() const
    {
        return stateToOptionIndex(m_state);
    }

    boost::int64_t AutoInputState::do_endOptionIndexGet   () const
    {
        printf("TODO: Implement AutoInputState::do_getEndOptionIndex\n");
        return 0;
    }

    void AutoInputState::do_endOptionIndexSet ( boost::int64_t /*iIndex*/ )
    {
        printf("TODO: Implement AutoInputState::do_endOptionIndexSet\n");
    }

    boost::int64_t AutoInputState::do_lastOptionIndexGet   () const
    {
        return stateToOptionIndex(m_stateLast);
    }

    std::string AutoInputState::do_indexToOption  (
            boost::int64_t iOptionIndex
            ) const
    {
        IntVecT state = optionIndexToState(iOptionIndex);
        return stateToOption( state, "" );
    }

    std::string AutoInputState::do_indexToSearchVal (
            boost::int64_t /*iOptionIndex*/
            ) const
    {
        return "";
    }

    int AutoInputState::do_indexToCount (
            boost::int64_t /*iOptionIndex*/
            ) const
    {
        return 0;
    }


    void AutoInputState::do_nextOption()
    {
        doNextState(autoInputIncreaseLength());
    }

    std::string  AutoInputState::do_optionAdd (
              int /*iCount*/
            , const std::string& /*sValue*/
            , const std::string& /*sSearchFor*/
            )
    {
        return "";
        // Empty implementation by design.
    }

    void AutoInputState::do_start()
    {
//        boost::int64_t iFirst = firstOptionIndex();
//        boost::int64_t iBegin = beginOptionIndex();
//        if ( iBegin < iFirst ) iBegin = iFirst;

        boost::int64_t iBegin = firstOptionIndex();
        m_bAtEndOption = false;

        m_state = optionIndexToState(iBegin);

        // If no end option is set use default (m_stateLast)
        if ( endOption() == "" ) {
            std::string sEndOption = stateToOption(m_stateLast, " ");
            endOptionSet(sEndOption);
        }
        printf ("endOption()        : %s\n" , endOption().c_str() );
        printf ("endOptionIndex()   : %d\n", static_cast<int>(endOptionIndex()) );
    }

    void AutoInputState::do_addResourceLine ( const std::string& /*sLine*/ )
    {
    }


    /** Compute index for option based on the option value. */
    boost::int64_t AutoInputState::hlp_optionToIndex (
        const std::string& sOption
     ) const
    {
        IntVecT state = optionToState( sOption, "");
        return stateToOptionIndex(state);
    }

    boost::int64_t AutoInputState::hlp_firstOptionIndex () const
    {
        return stateToOptionIndex(m_stateFirst);
    }

    bool AutoInputState::hlp_atEndOption() const
    {
        return m_bAtEndOption;
    }

    // ---------------------------------
    // --- PRIVATE: Helper functions ---
    // ---------------------------------

    bool AutoInputState::atLastRealState () const
    {
        bool atLast = true;
        for ( int i = 0; i <= m_iCurLevel; ++i) {
            atLast = atLast && atLastCharOfLvl(i);
        }
        return atLast;
    }


    bool AutoInputState::atLastCharOfLvl ( int iLvl ) const
    {
        return m_state[static_cast<size_t>(iLvl)] == static_cast<int>(m_chars.size())-2;
    }

    bool AutoInputState::doNextStateLvl( int iLvl )
    {
        if ( iLvl < 0 ) return false;
        bool lvlRestarted = atLastCharOfLvl( iLvl );
        const size_t uLvl = static_cast<size_t>(iLvl);
        const int chars_size = static_cast<int>(m_chars.size());
        m_state[uLvl] = (m_state[uLvl] +1) % chars_size;

        // Skip first and last chars which are not "real" states
        while ( m_state[uLvl] == (chars_size -1) || (m_state[uLvl] == 0) ) {
            m_state[uLvl] = (m_state[uLvl] +1) % chars_size;
        }
        return lvlRestarted;
    }

    void AutoInputState::doNextState( bool bGoLvlUp )
    {
        if ( m_chars.empty() )  return;

        if ( m_bAtEndOption ) {
            m_bAtEndOption = false;
            ////do_start();
            m_state     = m_stateFirst;
            return;
        }

        // --- Check if need to go one level up (increase string length by 1 ) ---
        int lvl = m_iCurLevel;
        bGoLvlUp = bGoLvlUp && (lvl < m_iMaxLevel);

        if ( bGoLvlUp ) {
            ++m_iCurLevel;
            lvl = m_iCurLevel;
            autoInputIncreaseLength(false);
         //   m_state[m_iCurLevel] = 1;
         //   return;
        }

        // --- Do normal nextState with "ripple carry" to lower level if end of current reached ---

        // Advance m_iCurLevel by one allways
        bool goLvlDown = doNextStateLvl( lvl );
        while ( goLvlDown ) {
            --lvl;
            goLvlDown = doNextStateLvl( lvl );
        }

        if ( !bGoLvlUp ) {
            bool atLast = atLastRealState();
            bool atEnd = allMoreSignificantStatesAtEnd() && currentOptionIndex() >= endOptionIndex();
            if ( atLast || atEnd ) {
                m_bAtEndOption = true;
            }
        }


        // --- See if we possibly can go one ore more levels down ---
        //     This is possible only if cur lvl is above m_iMinLevel and we have
        //     traversed all states in that level so it's value is now one again.
        //     But only lvl = m_iCurLeveldo this check if we not just increased the level (bGoLvlUp)
        if ( !bGoLvlUp ) {
            const size_t minLevel = static_cast<size_t>(m_iMinLevel);
            size_t curLevel = static_cast<size_t>(m_iCurLevel);

            while ( curLevel > minLevel && m_state[curLevel] == 1 ) {
                m_state[curLevel] = 0;
                --curLevel;
                m_iCurLevel = static_cast<int>(curLevel);
            }
        }
    }


    void AutoInputState::createCharsLookUp()
    {
        for ( size_t i = 0; i < m_chars.size(); ++i ) {
            m_charToIntMap[ m_chars[i] ] = i;
        }
    }

    int AutoInputState::charToInt(const std::string& sChar, int iNotFoundVal ) const
    {
        return cpaf::map_find(m_charToIntMap, iNotFoundVal, sChar);
    }

    std::string AutoInputState::intToChar(int iCharInt ) const
    {
        if ( 0 <= iCharInt && iCharInt < static_cast<int>(m_chars.size()) )	return m_chars[static_cast<size_t>(iCharInt)];
        else																return "";
    }

    boost::int64_t AutoInputState::stateToOptionIndex  (
            const IntVecT& state
            ) const
    {

        const auto base = m_chars.size();
        const size_t maxLevel = static_cast<size_t>(m_iMaxLevel);
        int iOptionIndex = 0;
        for ( size_t i = 0; i <= maxLevel; ++i ) {
            int weight = static_cast<int>(pow( static_cast<float>(base), maxLevel - i));
            iOptionIndex += state[i]*weight;
        }

        IntVecT compState = optionIndexToState(iOptionIndex);
        if ( compState != state ) {
            printf ("<>: %s" , cpaf::container_to_string(state).c_str() );
        }

        return iOptionIndex;
    }


    AutoInputState::IntVecT AutoInputState::optionIndexToState  (
               boost::int64_t iOptionIndex
            ) const
    {
        const auto base = m_chars.size();
        const size_t maxLevel = static_cast<size_t>(m_iMaxLevel);
        const size_t vecSize = maxLevel+1;
        IntVecT state(vecSize, 0);
        for ( size_t i = 0; i < maxLevel; ++i ) {
            int64_t weight = static_cast<int64_t>(pow( static_cast<float>(base),  maxLevel - i ));
            int val = static_cast<int>(iOptionIndex / weight);
            state[i] = val;
            iOptionIndex -= state[i]*weight;
        }
        state[maxLevel] = static_cast<int>(iOptionIndex);

        //printf("optionIndexToState: size: %d\n", (int)state.size() );
        return state;
    }

    /** Compute state vector for option value. */
    AutoInputState::IntVecT AutoInputState::optionToState (
              const std::string& sOption
            , std::string sSplitChar
            ) const
    {
        std::string opt = boost::trim_copy(sOption);
        const size_t maxLevel = static_cast<size_t>(m_iMaxLevel);
        IntVecT state(maxLevel+1,0);
        if ( sSplitChar == "" ) {
            if      ( boost::algorithm::contains( opt, "," ) )   sSplitChar = ",";
            else if ( boost::algorithm::contains( opt, " " ) )   sSplitChar = " ";
            else if ( boost::algorithm::contains( opt, ";" ) )   sSplitChar = ";";
        }
        cpaf::StringVecT strVec = cpaf::splitv_trim(opt, sSplitChar );
        for ( int i = m_iMaxLevel; 0 <= i; --i ) {
            if ( i < static_cast<int>(strVec.size())) {
                state[static_cast<size_t>(i)] = charToInt( strVec[static_cast<size_t>(i)], 0 );
            }
        }
        return state;
    }

    std::string AutoInputState::stateToOption (
              const IntVecT& state
            , const std::string& sJoinChar
            ) const
    {
        cpaf::StringVecT strVec;
        for ( size_t i = 0; i < state.size(); ++i ) {
            if (state[i] != 0) strVec.push_back( intToChar(state[i]) );
        }
        return boost::join(strVec, sJoinChar );
    }


    // ------------
    // --- OUT: ---
    // ------------

    bool AutoInputState::doLvlUp()
    {
        if ( m_iCurLevel < m_iMaxLevel ) {
            ++m_iCurLevel;
            return true;
        }
        else	return false;
    }

    bool AutoInputState::doLvlDown()
    {
        int iLvl = m_iCurLevel;
        iLvl--;
        if ( iLvl >= 0 ) {
            m_iCurLevel = iLvl;
            const size_t uLvl = static_cast<size_t>(iLvl);
            m_state[uLvl] = (m_state[uLvl] +1) % static_cast<int>(m_chars.size());
            if ( atLastCharOfLvl(iLvl) ) {
                return this->doLvlDown();
            }
            else return true;
        }
        else	return false;
    }



} // END namespace crawl

