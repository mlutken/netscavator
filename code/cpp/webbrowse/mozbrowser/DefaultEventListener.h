#ifndef _WEBBROWSE_DEFAULT_EVENT_LISTENER_H_
#define _WEBBROWSE_DEFAULT_EVENT_LISTENER_H_

#include <nsIDOMKeyListener.h>
#include <nsIDOMMouseListener.h>
#include <nsIDOMUIListener.h>
#include <nsINativeKeyBindings.h>

class SignalsManager;

namespace crawl {
    class WebBrowserIF;
}

// -----------------------------
// --- DefaultDOMKeyListener ---
// -----------------------------

class DefaultDOMKeyListener : public nsIDOMKeyListener
{
public:
	DefaultDOMKeyListener( crawl::WebBrowserIF& mozBrowser );
	virtual ~DefaultDOMKeyListener();

	NS_DECL_ISUPPORTS

	// nsIDOMEventListener
	NS_IMETHOD HandleEvent ( nsIDOMEvent* aEvent );

	// nsIDOMKeyListener
	NS_IMETHOD KeyDown ( nsIDOMEvent* aDOMEvent );
	NS_IMETHOD KeyUp ( nsIDOMEvent* aDOMEvent );
	NS_IMETHOD KeyPress ( nsIDOMEvent* aDOMEvent );
private:
	crawl::WebBrowserIF& 			m_mozBrowser; 
};

// -------------------------------
// --- DefaultDOMMouseListener ---
// -------------------------------

class DefaultDOMMouseListener : public nsIDOMMouseListener
{
public:
	DefaultDOMMouseListener( crawl::WebBrowserIF& mozBrowser );
	virtual ~DefaultDOMMouseListener();
	NS_DECL_ISUPPORTS

	// nsIDOMEventListener
	NS_IMETHOD HandleEvent ( nsIDOMEvent* aEvent );

	// nsIDOMMouseListener
	NS_IMETHOD MouseDown ( nsIDOMEvent* aDOMEvent );
	NS_IMETHOD MouseUp ( nsIDOMEvent* aDOMEvent );
	NS_IMETHOD MouseClick ( nsIDOMEvent* aDOMEvent );
	NS_IMETHOD MouseDblClick ( nsIDOMEvent* aDOMEvent );
	NS_IMETHOD MouseOver ( nsIDOMEvent* aDOMEvent );
	NS_IMETHOD MouseOut ( nsIDOMEvent* aDOMEvent );
private:
	crawl::WebBrowserIF& 			m_mozBrowser; 
};

// ----------------------------
// --- DefaultDOMUIListener ---
// ----------------------------

class DefaultDOMUIListener : public nsIDOMUIListener
{
public:

	DefaultDOMUIListener( crawl::WebBrowserIF& mozBrowser );
	virtual ~DefaultDOMUIListener();

	NS_DECL_ISUPPORTS

	// nsIDOMEventListener
	NS_IMETHOD HandleEvent ( nsIDOMEvent* aEvent );

	// nsIDOMUIListener
	NS_IMETHOD Activate ( nsIDOMEvent* aDOMEvent );
	NS_IMETHOD FocusIn ( nsIDOMEvent* aDOMEvent );
	NS_IMETHOD FocusOut ( nsIDOMEvent* aDOMEvent );
private:
	crawl::WebBrowserIF& 			m_mozBrowser; 
};


// -----------------------------
// --- TestDOMKeyListener ---
// -----------------------------
/*
class TestDOMKeyListener : public nsIDOMKeyListener
{
public:
	TestDOMKeyListener();
	virtual ~TestDOMKeyListener();

	NS_DECL_ISUPPORTS

	// nsIDOMEventListener
	NS_IMETHOD HandleEvent ( nsIDOMEvent* aEvent );

	// nsIDOMKeyListener
	NS_IMETHOD KeyDown ( nsIDOMEvent* aDOMEvent );
	NS_IMETHOD KeyUp ( nsIDOMEvent* aDOMEvent );
	NS_IMETHOD KeyPress ( nsIDOMEvent* aDOMEvent );
private:
};

*/

#endif // _WEBBROWSE_DEFAULT_EVENT_LISTENER_H_

