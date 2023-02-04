#pragma once
#include <loki/Visitor.h>
#include <DomNodeIF.h>
#include <ScriptMinerIF.h>

namespace crawl {
    class NavigateStateBase;
    class AutoInputState;
    class DropDownSelectState;
    class DomPosClickState;
    class InputOptionsState;
    class UrlLoadState;
    class JavascriptExecuteState;
}

namespace crawl {

/**
For implementing a cliclAll options for navigate actions.
Currently only makes sense and thus implemented for, DomPosClickState. */
class NavigatorActionsClickAllExecutor :
      public Loki::BaseVisitor
    , public Loki::Visitor<crawl::AutoInputState>
    , public Loki::Visitor<crawl::DropDownSelectState>
    , public Loki::Visitor<crawl::DomPosClickState>
    , public Loki::Visitor<crawl::InputOptionsState>
    , public Loki::Visitor<crawl::UrlLoadState>
    , public Loki::Visitor<crawl::JavascriptExecuteState>
{
public:
    NavigatorActionsClickAllExecutor() ;
    bool            doAction    (crawl::ScriptMinerIF* pMiner
                                  , boost::shared_ptr<crawl::NavigateStateBase> pNSB
                                  );

    virtual void    Visit       ( crawl::AutoInputState& nsb );
    virtual void    Visit       ( crawl::DropDownSelectState& nsb );
    virtual void    Visit       ( crawl::DomPosClickState& nsb );
    virtual void    Visit       ( crawl::InputOptionsState& nsb );
    virtual void    Visit       ( crawl::UrlLoadState& nsb );
    virtual void    Visit       ( crawl::JavascriptExecuteState& nsb );

private:
    crawl::ScriptMinerIF*                           m_pMiner;
    boost::shared_ptr<crawl::NavigateStateBase>     m_pNSB;
//    boost::shared_ptr<crawl::DomNodeIF>             m_pNode;
    bool                                            m_bReturnVal;
};

} // END namespace crawl


