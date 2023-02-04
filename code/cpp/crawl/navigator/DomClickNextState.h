#ifndef _CRAWL_DOM_CLICK_NEXT_STATE_H_
#define _CRAWL_DOM_CLICK_NEXT_STATE_H_

#include "NavigateStateBase.h"
#include "StringSequenceState.h"

namespace crawl {

class ScriptMinerIF;


class DomClickNextState : public StringSequenceState
{
public:
    friend class NavigatorActionsClickAllExecutor;
    LOKI_DEFINE_VISITABLE()

    DomClickNextState( const std::string& sFindNextDomPosSequence);
    const std::string&      findNextDomPosSequence () const { return m_sFindNextDomPosSequence; }


    void initialize(ScriptMinerIF* miner);

    bool isInitialized() const;
    void setIsInitialized(bool isInitialized);

private:
    virtual bool    do_needValidDomPosToExecute() const override { return true; }
    virtual void    do_start ();


    // --- PRIVATE: Members ---
    bool            m_isInitialized = false;
    bool            m_atEndOption = false;
    std::string     m_sFindNextDomPosSequence;
};


} //END namespace crawl


#endif //_CRAWL_DOM_CLICK_NEXT_STATE_H_

