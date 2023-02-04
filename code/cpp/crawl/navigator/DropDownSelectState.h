#ifndef _CRAWL_DROP_DOWN_SELECT_STATE_H_
#define _CRAWL_DROP_DOWN_SELECT_STATE_H_

#include "NavigateStateBase.h"
#include "StringSequenceState.h"

namespace crawl {

class DropDownSelectState : public StringSequenceState
{
public:
    LOKI_DEFINE_VISITABLE()

    // --------------------------------------------
    // --- PUBLIC: Constructor / Init Functions ---
    // --------------------------------------------
    DropDownSelectState();

private:	
    virtual bool            do_needValidDomPosToExecute() const override { return true; }
    virtual std::string     do_optionAdd            ( int iCount, const std::string& sValue,
                                                      const std::string& sSearchFor );
};


} //END namespace crawl


#endif //_CRAWL_DROP_DOWN_SELECT_STATE_H_

