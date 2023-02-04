
#include <iostream>
#include <boost/format.hpp>
#include <dom/DOMMouseEvent.h>
#include <dom/DOMKeyEvent.h>

using namespace std;



static void 
testEvents_slotPageLoaded ( 
	MozBrowser& mozBrowser 	///< MozBrowser
)	
{
	cout << boost::format("TTT: testEvents_slotPageLoaded") << endl ;
//	boost::shared_ptr<DOMDocument> 		pDOMDoc = mozBrowser.webBrowser()->contentDOMWindow()->document() ;
//	boost::shared_ptr<WebNavigation> 	pWebNav = doQueryInterface<WebNavigation>( mozBrowser.webBrowser() );
}


static bool 
testEvents_slotLoadUri( 
	MozBrowser& 		mozBrowser, 	///< MozBrowser
	const std::string&	sUri			///< Uri about to be loaded
)	
{
	cout << boost::format("TTT: testEvents_slotLoadUri: %s") % sUri << endl ;
	
//	if ( sUri == "file:///home/ml/code/cpaf/cul/boost/libs/libraries.htm" ) return true;
	
	return false;	 
}

static void 
testEvents_slotMouseClick( 
	MozBrowser& 						mozBrowser, 	///< MozBrowser
	boost::shared_ptr<DOMMouseEvent> 	pMouseEvent		///< Mouse event
)	
{
	cout << boost::format("TTT: testEvents_slotMouseClick") << endl ;
}


static void 
testEvents_slotKeyDown ( 
	MozBrowser& rMozBrowser, 
	boost::shared_ptr<DOMKeyEvent> pKeyEvent 
)
{
	cout << boost::format("TTT: testEvents_slotKeyDown %d") % pKeyEvent->keyCode() << endl ;
}

static void 
testEvents_slotKeyPress ( 
	MozBrowser& rMozBrowser, 
	boost::shared_ptr<DOMKeyEvent> pKeyEvent 
)
{
	cout << boost::format("TTT: testEvents_slotKeyPress %d") % pKeyEvent->charCode() << endl ;
}


static void 
testEvents_connectSlots ( boost::shared_ptr<SignalsManager> pSignalsManager )
{
	pSignalsManager->connectPageLoaded( &testEvents_slotPageLoaded );
	pSignalsManager->connectOnLoadUri( 	&testEvents_slotLoadUri );
	pSignalsManager->connectMouseClick( &testEvents_slotMouseClick );
	pSignalsManager->connectKeyDown( 	&testEvents_slotKeyDown );
	pSignalsManager->connectKeyPress( 	&testEvents_slotKeyPress );

	cout << boost::format("TTT: testEvents_connectSlots") << endl ;
}

