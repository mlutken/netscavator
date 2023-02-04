#ifndef _CRAWL_INPUT_OPTIONS_STATE_H_
#define _CRAWL_INPUT_OPTIONS_STATE_H_

#include "NavigateStateBase.h"
#include "StringSequenceState.h"

namespace crawl {

class InputOptionsState : public StringSequenceState
{
public:
    LOKI_DEFINE_VISITABLE()
    InputOptionsState();
private:	
    virtual bool    do_needValidDomPosToExecute() const override { return true; }
    virtual int     do_indexToCount         ( boost::int64_t iOptionIndex	)   const;
    virtual void    do_addResourceLine      ( const std::string& sLine );
};


} //END namespace crawl


#endif //_CRAWL_INPUT_OPTIONS_STATE_H_

