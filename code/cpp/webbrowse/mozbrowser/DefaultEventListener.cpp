#include <stdio.h>

#include <nsCOMPtr.h>
#include <nsIDOMMouseEvent.h>
#include <nsIWebBrowserFocus.h>

#include <dom/DOMMouseEvent.h>
#include <dom/DOMKeyEvent.h>
#include <necko/URL.h>

#include <SignalsManager.h>
#include <WebBrowserIF.h>
#include <DomMouseEventIF.h>
#include <DomKeyEventIF.h>
#include <DomEventIF.h>
#include "DefaultEventListener.h"


// -----------------------------
// --- DefaultDOMKeyListener ---
// -----------------------------


DefaultDOMKeyListener::DefaultDOMKeyListener( 
	crawl::WebBrowserIF& mozBrowser 
)	:
	 m_mozBrowser( mozBrowser )
{
//// 	printf("DefaultDOMKeyListener::CONSTRUCTOR\n");
}

DefaultDOMKeyListener::~DefaultDOMKeyListener()
{
}

NS_IMPL_ADDREF 	( DefaultDOMKeyListener )
NS_IMPL_RELEASE ( DefaultDOMKeyListener )

NS_INTERFACE_MAP_BEGIN ( DefaultDOMKeyListener )
NS_INTERFACE_MAP_ENTRY_AMBIGUOUS ( nsISupports, nsIDOMKeyListener )
NS_INTERFACE_MAP_ENTRY_AMBIGUOUS ( nsIDOMEventListener, nsIDOMKeyListener )
NS_INTERFACE_MAP_ENTRY ( nsIDOMKeyListener )
NS_INTERFACE_MAP_END


NS_IMETHODIMP
DefaultDOMKeyListener::HandleEvent ( nsIDOMEvent* aDOMEvent )
{
// 	printf("DefaultDOMKeyListener::HandleEvent\n");
	return NS_OK;
}

NS_IMETHODIMP
DefaultDOMKeyListener::KeyDown ( nsIDOMEvent* aDOMEvent )
{
// 	printf("DefaultDOMKeyListener::KeyDown\n");
 	
 	////////////
//  	std::string sSel = m_mozBrowser.selectionGet();
//  	printf("Selection: %s\n", sSel.c_str() );
 	//////////
 	 
 	
	nsCOMPtr <nsIDOMKeyEvent> keyEvent;
	keyEvent = do_QueryInterface ( aDOMEvent );
	if ( !keyEvent ) return NS_OK;
////    boost::shared_ptr<DOMKeyEvent> pKeyEvent(new DOMKeyEvent(keyEvent) );
    boost::shared_ptr<DOMKeyEvent> e(new DOMKeyEvent(keyEvent) );
    boost::shared_ptr<crawl::DomKeyEventIF> pKeyEvent(
            new crawl::DomKeyEventIF( e->charCode()
                                      , e->keyCode()
                                      , e->altKey()
                                      , e->ctrlKey()
                                      , e->shiftKey()
                                      , e->metaKey()
                                      ));
    m_mozBrowser.signalsManager()->signalKeyDown( m_mozBrowser, pKeyEvent );
	
	// Stop propergation of event
// 	aDOMEvent->StopPropagation();
// 	aDOMEvent->PreventDefault();
	return NS_OK;
}

NS_IMETHODIMP
DefaultDOMKeyListener::KeyUp ( nsIDOMEvent* aDOMEvent )
{
// 	printf("DefaultDOMKeyListener::KeyUp\n");
	nsCOMPtr <nsIDOMKeyEvent> keyEvent;
	keyEvent = do_QueryInterface ( aDOMEvent );
	if ( !keyEvent ) return NS_OK;
////	boost::shared_ptr<DOMKeyEvent> pKeyEvent(new DOMKeyEvent(keyEvent) );
    boost::shared_ptr<DOMKeyEvent> e(new DOMKeyEvent(keyEvent) );
    boost::shared_ptr<crawl::DomKeyEventIF> pKeyEvent(
            new crawl::DomKeyEventIF( e->charCode()
                                      , e->keyCode()
                                      , e->altKey()
                                      , e->ctrlKey()
                                      , e->shiftKey()
                                      , e->metaKey()
                                      ));
	m_mozBrowser.signalsManager()->signalKeyUp( m_mozBrowser, pKeyEvent );
	
	// Stop propergation of event
// 	aDOMEvent->StopPropagation();
// 	aDOMEvent->PreventDefault();
	return NS_OK;
}

NS_IMETHODIMP
DefaultDOMKeyListener::KeyPress ( nsIDOMEvent* aDOMEvent )
{
	nsCOMPtr <nsIDOMKeyEvent> keyEvent;
	keyEvent = do_QueryInterface ( aDOMEvent );
	if ( !keyEvent ) return NS_OK;
////	boost::shared_ptr<DOMKeyEvent> pKeyEvent(new DOMKeyEvent(keyEvent) );
    boost::shared_ptr<DOMKeyEvent> e(new DOMKeyEvent(keyEvent) );
    boost::shared_ptr<crawl::DomKeyEventIF> pKeyEvent(
            new crawl::DomKeyEventIF( e->charCode()
                                      , e->keyCode()
                                      , e->altKey()
                                      , e->ctrlKey()
                                      , e->shiftKey()
                                      , e->metaKey()
                                      ));
    m_mozBrowser.signalsManager()->signalKeyPress( m_mozBrowser, pKeyEvent );


    //  	printf("DefaultDOMKeyListener::KeyPress\n");

	// Stop propergation of event
// 	aDOMEvent->StopPropagation();
// 	aDOMEvent->PreventDefault();
	return NS_OK;
}


// -------------------------------
// --- DefaultDOMMouseListener ---
// -------------------------------

DefaultDOMMouseListener::DefaultDOMMouseListener (  
	crawl::WebBrowserIF& mozBrowser 
)	:
	 m_mozBrowser( mozBrowser )
{
}

DefaultDOMMouseListener::~DefaultDOMMouseListener()
{
}

NS_IMPL_ADDREF ( DefaultDOMMouseListener )
NS_IMPL_RELEASE ( DefaultDOMMouseListener )
NS_INTERFACE_MAP_BEGIN ( DefaultDOMMouseListener )
NS_INTERFACE_MAP_ENTRY ( nsIDOMMouseListener )
NS_INTERFACE_MAP_END


NS_IMETHODIMP
DefaultDOMMouseListener::HandleEvent ( nsIDOMEvent* aDOMEvent )
{
	return NS_OK;
}



NS_IMETHODIMP
DefaultDOMMouseListener::MouseDown ( nsIDOMEvent* aDOMEvent )
{
    //printf("\nDefaultDOMMouseListener::MouseDown\n");
    m_mozBrowser.focusActivate();  // TODO: Is it a good idea to allways do this Activate?
	nsCOMPtr <nsIDOMMouseEvent> mouseEvent;
	mouseEvent = do_QueryInterface ( aDOMEvent );
	if ( !mouseEvent )	return NS_OK;
    boost::shared_ptr<DOMMouseEvent> e(new DOMMouseEvent(mouseEvent) );
    boost::shared_ptr<crawl::DomMouseEventIF> pMouseEvent(
            new crawl::DomMouseEventIF( e->button(), e->screenX(), e->screenY()
                                        ,   e->clientX(), e->clientY()
                                        ,   e->altKey(), e->ctrlKey(), e->shiftKey(), e->metaKey()) );

    m_mozBrowser.signalsManager()->signalMouseDown( m_mozBrowser, pMouseEvent );
	
	// Stop propergation of event
    // 	aDOMEvent->StopPropagation();
    // 	aDOMEvent->PreventDefault();
	return NS_OK;
}

NS_IMETHODIMP
DefaultDOMMouseListener::MouseUp ( nsIDOMEvent* aDOMEvent )
{
// 	printf("DefaultDOMMouseListener::MouseUp\n");
	nsCOMPtr <nsIDOMMouseEvent> mouseEvent;
	mouseEvent = do_QueryInterface ( aDOMEvent );
	if ( !mouseEvent )	return NS_OK;
    boost::shared_ptr<DOMMouseEvent> e(new DOMMouseEvent(mouseEvent) );
    boost::shared_ptr<crawl::DomMouseEventIF> pMouseEvent(
            new crawl::DomMouseEventIF( e->button(), e->screenX(), e->screenY()
                                        ,   e->clientX(), e->clientY()
                                        ,   e->altKey(), e->ctrlKey(), e->shiftKey(), e->metaKey()) );
    m_mozBrowser.signalsManager()->signalMouseUp( m_mozBrowser, pMouseEvent );
	
	// Stop propergation of event
	aDOMEvent->StopPropagation();
	aDOMEvent->PreventDefault();
	return NS_OK;
}

NS_IMETHODIMP
DefaultDOMMouseListener::MouseClick ( nsIDOMEvent* aDOMEvent )
{
// 	printf("DefaultDOMMouseListener::MouseClick\n");
	nsCOMPtr <nsIDOMMouseEvent> mouseEvent;
	mouseEvent = do_QueryInterface ( aDOMEvent );
	if ( !mouseEvent ) 	return NS_OK;
    boost::shared_ptr<DOMMouseEvent> e(new DOMMouseEvent(mouseEvent) );
    boost::shared_ptr<crawl::DomMouseEventIF> pMouseEvent(
            new crawl::DomMouseEventIF( e->button(), e->screenX(), e->screenY()
                                        ,   e->clientX(), e->clientY()
                                        ,   e->altKey(), e->ctrlKey(), e->shiftKey(), e->metaKey()) );
    m_mozBrowser.signalsManager()->signalMouseClick( m_mozBrowser, pMouseEvent );
	
	// Stop propergation of event
// 	aDOMEvent->StopPropagation();
// 	aDOMEvent->PreventDefault();
	return NS_OK;
}

NS_IMETHODIMP
DefaultDOMMouseListener::MouseDblClick ( nsIDOMEvent* aDOMEvent )
{
//	printf("DefaultDOMMouseListener::MouseDblClick\n");
	nsCOMPtr <nsIDOMMouseEvent> mouseEvent;
	mouseEvent = do_QueryInterface ( aDOMEvent );
	if ( !mouseEvent ) return NS_OK;
    boost::shared_ptr<DOMMouseEvent> e(new DOMMouseEvent(mouseEvent) );
    boost::shared_ptr<crawl::DomMouseEventIF> pMouseEvent(
            new crawl::DomMouseEventIF( e->button(), e->screenX(), e->screenY()
                                        ,   e->clientX(), e->clientY()
                                        ,   e->altKey(), e->ctrlKey(), e->shiftKey(), e->metaKey()) );
    m_mozBrowser.signalsManager()->signalMouseDblClick( m_mozBrowser, pMouseEvent );
	
	// Stop propergation of event
// 	aDOMEvent->StopPropagation();
// 	aDOMEvent->PreventDefault();
	return NS_OK;
}

NS_IMETHODIMP
DefaultDOMMouseListener::MouseOver ( nsIDOMEvent* aDOMEvent )
{
//	printf("DefaultDOMMouseListener::MouseOver\n");
	nsCOMPtr <nsIDOMMouseEvent> mouseEvent;
	mouseEvent = do_QueryInterface ( aDOMEvent );
	if ( !mouseEvent ) return NS_OK;
    boost::shared_ptr<DOMMouseEvent> e(new DOMMouseEvent(mouseEvent) );
    boost::shared_ptr<crawl::DomMouseEventIF> pMouseEvent(
            new crawl::DomMouseEventIF( e->button(), e->screenX(), e->screenY()
                                        ,   e->clientX(), e->clientY()
                                        ,   e->altKey(), e->ctrlKey(), e->shiftKey(), e->metaKey()) );
    m_mozBrowser.signalsManager()->signalMouseOver( m_mozBrowser, pMouseEvent );
	
	// Stop propergation of event
// 	aDOMEvent->StopPropagation();
// 	aDOMEvent->PreventDefault();
	return NS_OK;
}

NS_IMETHODIMP
DefaultDOMMouseListener::MouseOut ( nsIDOMEvent* aDOMEvent )
{
//	printf("DefaultDOMMouseListener::MouseOut\n");
	nsCOMPtr <nsIDOMMouseEvent> mouseEvent;
	mouseEvent = do_QueryInterface ( aDOMEvent );
	if ( !mouseEvent ) return NS_OK;
    boost::shared_ptr<DOMMouseEvent> e(new DOMMouseEvent(mouseEvent) );
    boost::shared_ptr<crawl::DomMouseEventIF> pMouseEvent(
            new crawl::DomMouseEventIF( e->button(), e->screenX(), e->screenY()
                                        ,   e->clientX(), e->clientY()
                                        ,   e->altKey(), e->ctrlKey(), e->shiftKey(), e->metaKey()) );
    m_mozBrowser.signalsManager()->signalMouseOut( m_mozBrowser, pMouseEvent );
	
	// Stop propergation of event
// 	aDOMEvent->StopPropagation();
// 	aDOMEvent->PreventDefault();
	return NS_OK;
}

// ----------------------------
// --- DefaultDOMUIListener ---
// ----------------------------

DefaultDOMUIListener::DefaultDOMUIListener ( 
	crawl::WebBrowserIF& mozBrowser 
)	:
	 m_mozBrowser( mozBrowser )
{
}

DefaultDOMUIListener::~DefaultDOMUIListener()
{
}

NS_IMPL_ADDREF ( DefaultDOMUIListener )
NS_IMPL_RELEASE ( DefaultDOMUIListener )
NS_INTERFACE_MAP_BEGIN ( DefaultDOMUIListener )
NS_INTERFACE_MAP_ENTRY ( nsIDOMUIListener )
NS_INTERFACE_MAP_END


NS_IMETHODIMP
DefaultDOMUIListener::HandleEvent ( nsIDOMEvent* aDOMEvent )
{
	return NS_OK;
}


NS_IMETHODIMP
DefaultDOMUIListener::Activate ( nsIDOMEvent* aDOMEvent )
{
// // 	printf("DefaultDOMUIListener::Activate\n");
	nsCOMPtr <nsIDOMUIEvent> uiEvent = do_QueryInterface ( aDOMEvent );
	if ( !uiEvent ) return NS_OK;
//	boost::shared_ptr<DOMUIEvent> e(new DOMMouseEvent(uiEvent) );
    boost::shared_ptr<crawl::DomEventIF> pUIEvent(new crawl::DomEventIF() );
    m_mozBrowser.signalsManager()->signalActivate( m_mozBrowser, pUIEvent );
	
	//g_signal_emit ( G_OBJECT ( mOwner->mOwningWidget ),moz_embed_signals[DOM_ACTIVATE], 0,( void * ) uiEvent, &bReturnVal );
// 	aDOMEvent->StopPropagation();
// 	aDOMEvent->PreventDefault();
	return NS_OK;
}

NS_IMETHODIMP
DefaultDOMUIListener::FocusIn ( nsIDOMEvent* aDOMEvent )
{
// // 	printf("DefaultDOMUIListener::FocusIn\n");
	nsCOMPtr <nsIDOMUIEvent> uiEvent = do_QueryInterface ( aDOMEvent );
	if ( !uiEvent ) return NS_OK;
    //	boost::shared_ptr<DOMUIEvent> e(new DOMMouseEvent(uiEvent) );
    boost::shared_ptr<crawl::DomEventIF> pUIEvent(new crawl::DomEventIF() );
    m_mozBrowser.signalsManager()->signalFocusIn( m_mozBrowser, pUIEvent );
	
	//g_signal_emit ( G_OBJECT ( mOwner->mOwningWidget ),moz_embed_signals[DOM_FOCUS_IN], 0,( void * ) uiEvent, &bReturnVal );
// 	aDOMEvent->StopPropagation();
// 	aDOMEvent->PreventDefault();
	return NS_OK;
}

NS_IMETHODIMP
DefaultDOMUIListener::FocusOut ( nsIDOMEvent* aDOMEvent )
{
// // 	printf("DefaultDOMUIListener::FocusOut\n");
	nsCOMPtr <nsIDOMUIEvent> uiEvent = do_QueryInterface ( aDOMEvent );
	if ( !uiEvent ) return NS_OK;
    //	boost::shared_ptr<DOMUIEvent> e(new DOMMouseEvent(uiEvent) );
    boost::shared_ptr<crawl::DomEventIF> pUIEvent(new crawl::DomEventIF() );
    m_mozBrowser.signalsManager()->signalFocusOut( m_mozBrowser, pUIEvent );
	
	//g_signal_emit ( G_OBJECT ( mOwner->mOwningWidget ),moz_embed_signals[DOM_FOCUS_OUT], 0,( void * ) uiEvent, &bReturnVal );
// 	aDOMEvent->StopPropagation();
// 	aDOMEvent->PreventDefault();
	return NS_OK;
}


