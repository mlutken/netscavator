#include "NavigatorActionsClickAllExecutor.h"
#include <navigator/AutoInputState.h>
#include <navigator/DomPosClickState.h>
#include <navigator/DropDownSelectState.h>
#include <navigator/InputOptionsState.h>
#include <navigator/UrlLoadState.h>
#include <navigator/JavascriptExecuteState.h>
#include <navigator/NavigatorActionsExecutor.h>

namespace crawl {

NavigatorActionsClickAllExecutor::NavigatorActionsClickAllExecutor()
{
} 

/** Gets the valid options for the given Definition. */
bool NavigatorActionsClickAllExecutor::doAction(
      crawl::ScriptMinerIF* pMiner
    , boost::shared_ptr<crawl::NavigateStateBase> pNSB
)
{
    m_pMiner    = pMiner;
    m_pNSB      = pNSB;
    if ( !m_pNSB ) return false;

    m_bReturnVal = false;
    m_pNSB->Accept(*this);
    return m_bReturnVal;
}



void NavigatorActionsClickAllExecutor::Visit ( crawl::AutoInputState&  )
{
}

void NavigatorActionsClickAllExecutor::Visit ( crawl::DropDownSelectState&  )
{
}

void NavigatorActionsClickAllExecutor::Visit ( crawl::DomPosClickState& nsb )
{
//    if ( !m_pNode) return;
    boost::int64_t saveOptionIndex = nsb.m_iCurrentOptionIndex;
    for ( boost::int64_t i = nsb.firstOptionIndex(); i <= nsb.lastOptionIndex(); ++i ) {

        nsb.m_iCurrentOptionIndex = i;
        NavigatorActionsExecutor navExe;
        navExe.doAction( m_pMiner, m_pNSB/*, m_pNode */);
    }
    nsb.m_iCurrentOptionIndex = saveOptionIndex;
}

void NavigatorActionsClickAllExecutor::Visit ( crawl::InputOptionsState& )
{
}

void NavigatorActionsClickAllExecutor::Visit ( crawl::UrlLoadState& )
{
}

void NavigatorActionsClickAllExecutor::Visit ( crawl::JavascriptExecuteState& )
{
}

} // END namespace crawl
