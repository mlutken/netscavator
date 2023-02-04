#include "DomActionAbstraction.h"

#include <boost/algorithm/string.hpp>
#include <boost/assign/list_of.hpp> 
#include <cpaf_libs/utils/cpaf_string_utils.hpp>

#include <ScriptMinerIF.h>
#include <DomNodeIF.h>
#include <interfaces_utils.h>

namespace crawl {


// -------------------------
// --- NodeClickLoadHref ---
// -------------------------

/**
Action abstraction implementation to click a dom node.
\return true if operation was successfull .
*/
bool NodeClickLoadHref::doActionBool	(
        ScriptMinerIF*                    pCrawler		///< [in] pointer to crawler that holds node in question
        ,const std::string&                             ///< [in] Bool string. Ie. if \a sDoLoadHref is the string "false" or the string "0" we will only try to click the node. Otherwise in case the node is actually a link (<A href='LinkToSomeWhere.html' ... >...</A> We also load the URL directly
        ,const std::string&								///< Unused
        )
{
    return pCrawler->nodeClickLoadHref( NEAREST_AUTO );
}


// -----------------
// --- NodeClick ---
// -----------------

/**
Action abstraction implementation to click a dom node.
\return true if operation was successfull .
*/
bool NodeClick::doActionBool	(
        ScriptMinerIF*                       pCrawler	///< [in] pointer to crawler that holds node in question
        ,const std::string&                             ///< [in] Bool string. Ie. if \a sDoLoadHref is the string "false" or the string "0" we will only try to click the node. Otherwise in case the node is actually a link (<A href='LinkToSomeWhere.html' ... >...</A> We also load the URL directly
        ,const std::string&								///< Unused
        )
{
    return pCrawler->nodeClick( NEAREST_AUTO );
}

bool NodeClickWait::doActionBool(ScriptMinerIF* pCrawler, const std::string& sTimeoutInMs, const std::string& /*sParam2*/)
{
    return pCrawler->nodeClickWait(NEAREST_AUTO, cpaf::to_int(sTimeoutInMs));
}


// ------------------
// --- MouseEvent ---
// ------------------

/** Action abstraction implementation to send mouse event(s) dom node.
There are five DOM 2 event modules, and they map directly to the names of the DOM features;
Events
    Covers all event types.
HTMLEvents
    Covers 'abort', 'blur', 'change', 'error', 'focus', 'load', 'reset', 'resize',
    'scroll', 'select', 'submit', and 'unload'.
UIEvents
    Covers 'DOMActivate', 'DOMFocusIn', 'DOMFocusOut',
    and (since they do not have their own key events module in DOM 2) it also covers 'keydown',
    'keypress', and 'keyup'.
    Also indirectly covers MouseEvents.
MouseEvents
    Covers 'click', 'mousedown', 'mousemove', 'mouseout', 'mouseover', and 'mouseup'.
MutationEvents
    Covers 'DOMAttrModified', 'DomNodeIFInserted', 'DomNodeIFRemoved', 'DOMCharacterDataModified',
    'DomNodeIFInsertedIntoDocument', 'DomNodeIFRemovedFromDocument', and 'DOMSubtreeModified'.
\return true if operation was successfull .
*/
bool MouseEvent::doActionBool	(
        ScriptMinerIF*                  pCrawler        ///< [in] pointer to crawler that holds node in question
        ,const std::string&				sEvent			///< [in] Event names ( comma separated ) to dispatch
        ,const std::string&				sButton			///< [in] Button ( 'left', 'middle', 'right' )
        )
{
    int iButton	= 0;	// Button ( left=0, middle/wheel=1, right=2 )
    if 		( sButton == "middle" 	)	iButton = 1;
    else if	( sButton == "right"	)	iButton = 2;

    return pCrawler->nodeMouseEvent( sEvent, iButton, NEAREST_AUTO );
}

// ------------------------------
// --- NodeJavaScriptEvaluate ---
// ------------------------------

bool NodeJavaScriptEvaluate::doActionBool	(
        ScriptMinerIF*                  pCrawler        ///< [in] pointer to crawler that holds node in question
        ,const std::string&				sJavaScript		///< [in] Javascript string to evaluate at current element
        ,const std::string&                             ///< [in]
        )
{
    return pCrawler->nodeJavaScriptEvaluate( sJavaScript, NEAREST_AUTO );
}

// ---------------
// --- LoadUrl ---
// ---------------

/** Action abstraction implementation to load URL into browser.
\return true if operation was successfull .
*/
bool LoadUrl::doActionBool	(
        ScriptMinerIF*                  pCrawler		///< [in] pointer to crawler that holds node in question
        ,const std::string&				sUrl			///< [in] URL to load
        ,const std::string&								///< Unused
        )
{
    return pCrawler->urlLoad(sUrl);
}

bool LoadUrlWait::doActionBool(ScriptMinerIF* pCrawler,
       const std::string& sTimeoutInMs,
       const std::string& )
{
    return pCrawler->nodeClickWait(NEAREST_AUTO, cpaf::to_int(sTimeoutInMs));
}

// ------------------
// --- InputValue ---
// ------------------

/** Action abstraction implementation to input value into html input field/element.
\return true if operation was successfull .
*/
bool InputValue::doActionBool	(
        ScriptMinerIF*                  pCrawler        ///< [in] pointer to crawler that holds node in question
        ,const std::string&				sValue			///< [in] Value to input in the field at \a pNode
        ,const std::string&								///< Unused
        )
{
    return pCrawler->inputSet( sValue );
}


// ------------------
// --- FormSubmit ---
// ------------------

/** Action abstraction implementation to submit a form.
\return true if operation was successfull .
*/
bool FormSubmit::doActionBool	(
        ScriptMinerIF*          pCrawler                ///< [in] pointer to crawler that holds node in question
        ,const std::string&								///< Unused
        ,const std::string&								///< Unused
        )
{
    return pCrawler->formSubmit();
}


// -----------------
// --- FormReset ---
// -----------------

/** Action abstraction implementation to reset a form
\return true if operation was successfull .
*/
bool FormReset::doActionBool	(
        ScriptMinerIF*                  pCrawler        ///< [in] pointer to crawler that holds node in question
        ,const std::string&								///< Unused
        ,const std::string&								///< Unused
        )
{
    return pCrawler->formReset();
}


// -------------------
// --- SelectIndex ---
// -------------------

/** Action abstraction implementation to choose a specified index in a select element.
\return true if operation was successfull .
*/
bool SelectIndex::doActionBool	(
        ScriptMinerIF*                  pCrawler        ///< [in] pointer to crawler that holds node in question
        ,const std::string&				sIndex			///< [in] String (is converted to integer) designating the index of the select to be selected.
        ,const std::string&								///< Unused
        )
{
    int iIndex;
    try                                     { iIndex = cpaf::to_int( sIndex ) ;	}
    catch (const cpaf::bad_conversion& ) 	{ iIndex = 0;	}

    return pCrawler->selectIndex(iIndex);
}

/** Action abstraction implementation to choose a specified index in a select element.
\return true if operation was successfull .
*/
bool SelectIndexWait::doActionBool	(
        ScriptMinerIF*                  pCrawler        ///< [in] pointer to crawler that holds node in question
        ,const std::string&				sIndex			///< [in] String (is converted to integer) designating the index of the select to be selected.
        ,const std::string&				sTimeoutInMs	///< Timeout in milliseconds
        )
{
    int iIndex;
    try                                     { iIndex = cpaf::to_int( sIndex ) ;	}
    catch (const cpaf::bad_conversion&) 	{ iIndex = 0;	}

    return pCrawler->selectIndexWait(iIndex, cpaf::to_int(sTimeoutInMs));
}

// --------------------
// --- SelectOption ---
// --------------------

/** Action abstraction implementation to choose the \a pNode OPTION in a select element.
The \a pNode should be an HTML OPTION element which belongs to a HTML SELECT element. The owning 
SELECT element will be set to the OPTION element specified.
\return true if operation was successfull .
*/
bool SelectOption::doActionBool	(
        ScriptMinerIF*              pCrawler        ///< [in] pointer to crawler that holds node in question
        ,const std::string&                         ///< [in] Unused ? TODO: String (is converted to integer) designating the index of the select to be selected.
        ,const std::string&							///< Unused
        )
{
    return pCrawler->selectOption();
}



// ------------------------------
// --- STATIC: Initialization ---
// ------------------------------

const G_DomActionAbstractionLookUp::MapT G_DomActionAbstractionLookUp::AliasMap = boost::assign::map_list_of
        ("click",                   boost::shared_ptr<DomActionAbstraction>( new NodeClick()		)	)
        ("nodeClick",               boost::shared_ptr<DomActionAbstraction>( new NodeClick()		)	)
        ("clickWait",               boost::shared_ptr<DomActionAbstraction>( new NodeClickWait()	)	)
        ("nodeClickLoadHref",       boost::shared_ptr<DomActionAbstraction>( new NodeClickLoadHref())	)
        ("mouseEvent",              boost::shared_ptr<DomActionAbstraction>( new MouseEvent()		)	)
        ("nodeJavaScriptEvaluate",	boost::shared_ptr<DomActionAbstraction>( new NodeJavaScriptEvaluate())	)
        ("loadUrl",                 boost::shared_ptr<DomActionAbstraction>( new LoadUrl()			)	)
        ("urlLoad",                 boost::shared_ptr<DomActionAbstraction>( new LoadUrl()			)	)
        ("urlLoadWait",             boost::shared_ptr<DomActionAbstraction>( new LoadUrlWait()      )	)
        ("inputValue",              boost::shared_ptr<DomActionAbstraction>( new InputValue()		)	)
        ("inputSet",                boost::shared_ptr<DomActionAbstraction>( new InputValue()		)	)
        ("formSubmit",              boost::shared_ptr<DomActionAbstraction>( new FormSubmit()		)	)
        ("formReset",               boost::shared_ptr<DomActionAbstraction>( new FormReset()		)	)
        ("selectIndex",             boost::shared_ptr<DomActionAbstraction>( new SelectIndex()		)	)
        ("selectIndexWait",         boost::shared_ptr<DomActionAbstraction>( new SelectIndexWait()  )	)
        ("selectOption",            boost::shared_ptr<DomActionAbstraction>( new SelectOption()		)	)
        ;


boost::shared_ptr<DomActionAbstraction>	G_DomActionAbstractionLookUp::fromAlias	( const std::string& sFunAlias )
{
    G_DomActionAbstractionLookUp::MapT::const_iterator itManip = G_DomActionAbstractionLookUp::AliasMap.find( sFunAlias );
    if ( itManip != G_DomActionAbstractionLookUp::AliasMap.end() ) 	return itManip->second;

    return boost::shared_ptr<DomActionAbstraction>();
}



} //namespace crawl


