#include "NavigatorActionsExecutor.h"
#include <ScriptMinerIF.h>

#include <navigator/AutoInputState.h>
#include <navigator/DomPosClickState.h>
#include <navigator/DomClickNextState.h>
#include <navigator/DropDownSelectState.h>
#include <navigator/InputOptionsState.h>
#include <navigator/UrlLoadState.h>
#include <navigator/JavascriptExecuteState.h>


using namespace std;
using namespace crawl;

NavigatorActionsExecutor::NavigatorActionsExecutor()
{
} 

/** Gets the valid options for the given Definition. */
bool NavigatorActionsExecutor::doAction(crawl::ScriptMinerIF* pMiner
    , boost::shared_ptr<crawl::NavigateStateBase> pNSB
    )
{
    m_pMiner    = pMiner;
    m_pNSB      = pNSB;
//    m_pNode     = pNode;
    if ( !m_pNSB ) return false;

    m_bReturnVal = false;
    m_pNSB->Accept(*this);
    return m_bReturnVal;
}



void NavigatorActionsExecutor::Visit ( crawl::AutoInputState& /*nsb*/ )
{
//    if ( !m_pNode) return;
//    m_bReturnVal = m_pNode->inputSet( nsb.currentOption() );
}

void NavigatorActionsExecutor::Visit ( crawl::DropDownSelectState& /*nsb*/ )
{
//    if ( !m_pNode) return;
//    const DropDownSelectState::OptionT* pOptionData = nsb.getOptionData();
//    if ( pOptionData ) {
//        //printf("ML: NavigatorActionsExecutor DropDownSelectState: %d\n", pOptionData->iSelectIndex );
//        m_pNode->selectIndex( pOptionData->iCount );
//        boost::shared_ptr<DomNodeIF> pOptionNode = m_pNode->selectOptionNodeGet(pOptionData->iCount);

//        // OLD: Mozilla specific code. Should be fixed in the MozDomNode.cpp file to use the 'else' version
//        if ( pOptionNode ) {
//            nsb.currentDomValue("TODO: DEBUG ONLY currentDomValue");
//            nsb.currentDomTextValue( pOptionNode->optionTextGet() );
//        }
//        else {
//            nsb.currentDomValue( m_pNode->selectValueGet() );
//            nsb.currentDomTextValue( m_pNode->selectTextGet() );
//        }
//     }
}

//void NavigatorActionsExecutor::Visit ( crawl::DropDownSelectState& nsb )
//{
// if ( !m_pNode) return;
//    const DropDownSelectState::OptionT* pOptionData = nsb.getOptionData();
//    if ( pOptionData ) {
//        boost::shared_ptr<DOMHTMLOptionElement> pOptionNode;
//        m_bReturnVal = crawl::selectSelect( pOptionNode, m_pNode->DOMNodePtr(), pOptionData->iSelectIndex );
//        DOMHTMLSelectElement::Ptr pSelect= doQueryInterface<DOMHTMLSelectElement>(m_pNode->DOMNodePtr());
//        if ( pSelect ) {
//            nsb.currentDomValue( pSelect->value() );
//        }
//        else nsb.currentDomValue( "" );

//        if ( pOptionNode ) {
//            nsb.currentDomTextValue( pOptionNode->text() );
//        }
//        else nsb.currentDomTextValue( "" );

//     }
//}

void NavigatorActionsExecutor::Visit ( crawl::DomPosClickState& nsb )
{
    const DomPosClickState::OptionT* pOptionData = nsb.getOptionData();
    if ( !pOptionData ) return;
    m_bReturnVal = true;
    int iPosSave = m_pMiner->domPos();
    if ( ! m_pMiner->domSeqFindNextParams( pOptionData->iCount, nsb.findNextDomPosSequence(), pOptionData->sSearchFor)) {
        m_bReturnVal = m_pMiner->domFindNext( pOptionData->iCount, pOptionData->sSearchFor);
    }
    if ( m_bReturnVal ) m_bReturnVal = m_pMiner->nodeClick();
    m_pMiner->domPosSet( iPosSave );
}

void NavigatorActionsExecutor::Visit(DomClickNextState& nsb)
{
//    if ( !m_pNode) return;
    if (!nsb.isInitialized()) {
        nsb.initialize(m_pMiner);
    }
    const DomPosClickState::OptionT* pOptionData = nsb.getOptionData();
    if ( !pOptionData ) return;
    m_bReturnVal = false;
    int iPosSave = m_pMiner->domPos();
    if ( pOptionData->iCount ) {
        m_pMiner->domPosSet(pOptionData->iCount);
        m_bReturnVal = m_pMiner->nodeClick();
    }
    m_pMiner->domPosSet( iPosSave );
}

void NavigatorActionsExecutor::Visit ( crawl::InputOptionsState& /*nsb*/ )
{
//    if ( !m_pNode) return;
//    m_bReturnVal = m_pNode->inputSet( nsb.currentOption() );
}

void NavigatorActionsExecutor::Visit ( crawl::UrlLoadState& nsb )
{
    std::string sUrl = nsb.baseUlrGet() + nsb.currentSearchFor();
    m_bReturnVal = m_pMiner->urlLoad( sUrl );
}

void NavigatorActionsExecutor::Visit ( crawl::JavascriptExecuteState& nsb )
{
    m_bReturnVal = m_pMiner->javaScriptExecute( nsb.currentSearchFor() );
}
