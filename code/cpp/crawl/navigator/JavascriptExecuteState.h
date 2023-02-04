#ifndef _CRAWL_JAVASCRIPT_EXECUTE_STATE_H_
#define _CRAWL_JAVASCRIPT_EXECUTE_STATE_H_

#include "NavigateStateBase.h"
#include "StringSequenceState.h"

namespace crawl {

class JavascriptExecuteState : public StringSequenceState
{
public:
    LOKI_DEFINE_VISITABLE()
    explicit JavascriptExecuteState();

private:	
    virtual bool    do_needValidDomPosToExecute() const override { return false; }
    virtual int     do_indexToCount  ( boost::int64_t iOptionIndex	) const;
};

} //END namespace crawl


#endif //_CRAWL_JAVASCRIPT_EXECUTE_STATE_H_

