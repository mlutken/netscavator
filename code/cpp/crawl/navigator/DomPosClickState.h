#ifndef _CRAWL_DOM_POS_CLICK_STATE_H_
#define _CRAWL_DOM_POS_CLICK_STATE_H_

#include "NavigateStateBase.h"
#include "StringSequenceState.h"

namespace crawl {

class DomPosClickState : public StringSequenceState
{
public:
    friend class NavigatorActionsClickAllExecutor;
    LOKI_DEFINE_VISITABLE()

    DomPosClickState(const std::string& sFindNextDomPosSequence);
    const std::string&      findNextDomPosSequence () const { return m_sFindNextDomPosSequence; }


private:
    virtual bool    do_needValidDomPosToExecute() const override { return false; }
    // --- PRIVATE: Members ---
    std::string     m_sFindNextDomPosSequence;
};


} //END namespace crawl


#endif //_CRAWL_DOM_POS_CLICK_STATE_H_

