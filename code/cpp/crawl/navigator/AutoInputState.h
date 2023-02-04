#ifndef _CRAWL_AUTO_INPUT_STATE_H_
#define _CRAWL_AUTO_INPUT_STATE_H_

#include "NavigateStateBase.h"

namespace crawl {

class AutoInputState : public NavigateStateBase
{
public:
    LOKI_DEFINE_VISITABLE()
    // -----------------
    // --- Constants ---
    // -----------------

    // ------------------------------------
    // --- Constructor / Init Functions ---
    // ------------------------------------
    AutoInputState     ( const std::string& sCharsList, int iMinLength, int iMaxLength );




private:	
    // --- PRIVATE: Typedefs ---
    typedef std::vector<int>            IntVecT;
    typedef std::map<std::string, int>  StrIntMapT;

    // --- PRIVATE: Abstract interface (do) functions ---
    virtual bool            do_needValidDomPosToExecute() const override { return true; }
    virtual void            do_currentOptionIndexSet( boost::int64_t iIndex ) ;
    virtual boost::int64_t  do_currentOptionIndexGet() const;
    virtual void            do_endOptionIndexSet    ( boost::int64_t iIndex );
    virtual boost::int64_t  do_endOptionIndexGet    () const;
    virtual boost::int64_t  do_lastOptionIndexGet   () const;
    virtual std::string     do_indexToOption        ( boost::int64_t iOptionIndex	)   const;
    virtual std::string     do_indexToSearchVal     ( boost::int64_t iOptionIndex	)   const;
    virtual int             do_indexToCount         ( boost::int64_t iOptionIndex	)   const;
    virtual void            do_nextOption			()                                   ;
    virtual std::string     do_optionAdd            ( int iCount, const std::string& sValue,
                                                      const std::string& sSearchFor );
    virtual void            do_start                ();
    virtual void            do_addResourceLine    ( const std::string& sLine );

    // --- PRIVATE: Helper functions ---
    virtual boost::int64_t    hlp_optionToIndex           ( const std::string& sOption	)	const;
    virtual boost::int64_t    hlp_firstOptionIndex        () const;
    virtual bool              hlp_atEndOption             () const;

    bool                atLastRealState     () const;
    bool                atLastCharOfLvl     ( int iLvl ) const;
    void                doNextState         ( bool bGoLvlUp );
    bool                doNextStateLvl      ( int iLvl );
    bool                doLvlUp             ();
    bool                doLvlDown           ();

    void                createCharsLookUp   ();
    int                 charToInt           ( const std::string& sChar, int iNotFoundVal = -1 ) const;
    std::string         intToChar           ( int iCharInt ) const;
    boost::int64_t      stateToOptionIndex  ( const IntVecT& state ) const;
    IntVecT             optionIndexToState  ( boost::int64_t iOptionIndex ) const;
    IntVecT             optionToState       ( const std::string& sOption, std::string sSplitChar="" ) const;
    std::string         stateToOption       ( const IntVecT& state, const std::string& sJoinChar ) const;


    // --- PRIVATE: Members ---
    int                     m_iMinLevel;
    int                     m_iMaxLevel;
    int                     m_iCurLevel;
    bool                    m_bAtEndOption;
    NavigateStateBase::StrVecT   m_chars;
    IntVecT                 m_state;
    IntVecT                 m_stateFirst;
    IntVecT                 m_stateLast;
    IntVecT                 m_stateBegin;
    IntVecT                 m_stateEnd;
    StrIntMapT              m_charToIntMap;

};


} //END namespace crawl


#endif //_CRAWL_AUTO_INPUT_STATE_H_

