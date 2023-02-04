#ifndef _CRAWL_URL_LOAD_STATE_H_
#define _CRAWL_URL_LOAD_STATE_H_

#include "NavigateStateBase.h"
#include "StringSequenceState.h"

namespace crawl {

class UrlLoadState : public StringSequenceState
{
public:
    LOKI_DEFINE_VISITABLE()

    explicit UrlLoadState(const std::string& sBaseUrl);
    const std::string&  baseUlrGet() const { return m_sBaseUrl; }

private:	
    virtual int     do_indexToCount  ( boost::int64_t iOptionIndex	) const;
    virtual bool    do_needValidDomPosToExecute() const override { return false; }
    // --- PRIVATE: Members ---
    std::string     m_sBaseUrl;
};


} //END namespace crawl


#endif //_CRAWL_URL_LOAD_STATE_H_

