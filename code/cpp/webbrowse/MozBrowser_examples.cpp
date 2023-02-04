
// Adding STL like interfaces to the Mozilla DOM Part X


 
#include <iostream>
#include <boost/format.hpp> 

// // #include <dom/nsIScriptGlobalObjectOwner.h>
// // #include <xpcom/nsIInterfaceRequestorUtils.h>
// // #include <dom/nsIScriptContext.h>
// // #include <dom/nsIScriptGlobalObject.h>
// // #include <js/jspubtd.h>
// // #include <dom/nsIDOMHTMLFormElement.h>
// // #include <dom/nsIDOMHTMLCollection.h>

#include <nsIScriptGlobalObjectOwner.h>
#include <nsIInterfaceRequestorUtils.h>
#include <nsIScriptContext.h>
#include <nsIScriptGlobalObject.h>
#include <jspubtd.h>
#include <nsIDOMHTMLFormElement.h>
#include <nsIDOMHTMLCollection.h>

#include "MozBrowser.h"
#include "dom/DOMDocument.h"
#include "dom/DOMHTMLDocument.h"
#include "dom/DOMNodeList.h"
#include "dom/DOMNamedNodeMap.h"
#include "dom/DOMWindow.h"
#include "dom/DOMNodeList.h"
#include "dom/DOMNode.h"
#include "dom/DOMElement.h"
#include "dom/DOMHTMLElement.h"
#include "dom/DOMHTMLLinkElement.h"
#include "dom/DOMHTMLAnchorElement.h"
#include "dom/DOMHTMLButtonElement.h"
#include "dom/DOMHTMLFormElement.h"
#include "dom/DOMHTMLImageElement.h"
#include "dom/DOMHTMLMapElement.h"
#include "dom/DOMHTMLOptionElement.h"
#include "dom/DOMHTMLParamElement.h"
#include "dom/DOMHTMLScriptElement.h"
#include "dom/DOMHTMLSelectElement.h"
#include "dom/DOMHTMLInputElement.h"
#include "dom/DOMProcessingInstruction.h"
#include "dom/DOMEntityReference.h"
#include "dom/DOMDOMImplementation.h"
#include "dom/DOMDocumentType.h"
#include "dom/DOMDocumentFragment.h"
#include "dom/DOMComment.h"
#include "dom/DOMText.h"
#include "dom/DOMCharacterData.h"
#include "dom/DOMCDATASection.h"
#include "dom/DOMHTMLCollection.h"


#include "dom/ScriptContext.h"
#include "docshell/WebNavigation.h"

#include "utils/mozilla_utils.h"



using namespace std;
namespace b = boost;

static bool ex_WantToRecurseNode( DOMNode::Ptr pNode ) 
{
	return 	!( 	pNode->nodeType() 	== DOMNode::ATTRIBUTE ||
				pNode->nodeType() 	== DOMNode::TEXT 			);
}

static bool ex_PrintNode( DOMNode::Ptr pNode ) 
{
	if ( 		pNode->nodeType() 	== DOMNode::ATTRIBUTE ) {
 		cout << pNode->nodeName() << "=\"" << pNode->nodeValue() << "\" " ;	 
	}
	else if ( 	pNode->nodeType() 	== DOMNode::TEXT ) {
 		cout << ">" << pNode->nodeValue() << "< " ;	 
	}
	else if ( 	pNode->nodeType() 	== DOMNode::COMMENT ) {
 		cout << "<!-- " << pNode->nodeValue() << " --> " ;	 
	}
	else {
 		cout << "<" << pNode->nodeName() << " " ;	 
	}
	
//				pNode->nodeType() 	== DOMNode::TEXT 			);
}

static void ex_RecurseDOM( DOMNode::Ptr pNode )
{
	ex_PrintNode ( pNode );
//	if ( 1 ) { 
// 	if ( pNode->nodeValue() != "\n" ) { 
// 		cout << b::format("C(%d): NodeName: %s, '%s'") % pNode->nodeType() % pNode->nodeName() % pNode->nodeValue() << endl ;	 
// 	}
// 	if ( !ex_WantToRecurseNode( pNode ) ) return;
//	if ( pNode->nodeValue() == "\n" ) cout << "NEWLINE" << endl;
	
	
	if ( pNode->hasAttributes() && ex_WantToRecurseNode( pNode) ) {
		DOMNamedNodeMap::Ptr 			pNodes 	= pNode->attributes();
		DOMNamedNodeMap::iterator 		pIt;
		
		// For some reason the DOMNamedNodeMap seems to order the attributes in reverse!
		for ( pIt = pNodes->end(); pIt > pNodes->begin();  ) {
			--pIt;
			ex_RecurseDOM ( *pIt );
		}
		
	}
	if ( pNode->hasChildNodes() && ex_WantToRecurseNode( pNode) ) {
		DOMNodeList::Ptr 			pNodes 	= pNode->childNodes();
		DOMNodeList::iterator 		pIt;
		
		for ( pIt = pNodes->begin(); pIt != pNodes->end(); ++pIt ) {
			ex_RecurseDOM ( *pIt );
		}
	
	}
}

void ex_AllElements (MozBrowserPtr pMozBrowser )
{
	DOMWindowPtr 			pDOMWindow 	= pMozBrowser->webBrowser()->contentDOMWindow();
	DOMNodeListPtr 			pNodes 		= pDOMWindow->document()->getElementsByTagName( "*" );
//	DOMNodeListPtr 			pNodes 		= pDOMWindow->document()->childNodes();
	DOMNodeList::iterator 	pIt;
	
	
//	ex_RecurseDOM ( pDOMWindow->document() ); 
	return;
	
	cout << "Number of nodes: " << pNodes->size() << endl;
	for ( pIt = pNodes->begin(); pIt != pNodes->end(); ++pIt ) {
//		cout << b::format("Node Name, Value: %s, %s") % (*pIt)->nodeName() % (*pIt)->nodeValue() << endl ;	 
		
		boost::shared_ptr<DOMHTMLElement> pElem( doQueryInterface<DOMHTMLElement>(*pIt) );
		if ( !pElem->valid() ) return;
		
//		cout << b::format("1: NodeName: %s, %d") % (*pIt)->nodeName() % (*pIt)->nodeType() << endl ;	 
		cout << b::format("A(%d): title(): %s, '%s'") % (*pIt)->nodeType() % pElem->title() % pElem->prefix() << endl ;	 
//		cout << b::format("A(%d)") % (*pIt)->nodeType() << endl ;	 
				
				
			
// 		DOMNamedNodeMapPtr 			pNodes1 	= (*pIt)->attributes();	// Attribute nodes	
// 		DOMNamedNodeMap::iterator 	pIt1;								
		DOMNodeListPtr 				pNodes1 	= (*pIt)->childNodes();
		DOMNodeList::iterator 		pIt1;
		
		for ( pIt1 = pNodes1->begin(); pIt1 != pNodes1->end(); ++pIt1 ) {
//			if ( (*pIt1)->nodeName() == "href" )	cout << b::format("href=%s") % (*pIt1)->nodeValue() << endl ;
			cout << b::format("B(%d): NodeName: %s, '%s'") % (*pIt1)->nodeType() % (*pIt1)->nodeName() % (*pIt1)->nodeValue() << endl ;	 
		}
	}
}

void ex_HomeSearch ( MozBrowserPtr pMozBrowser )
{
//	return ;
	DOMWindowPtr 			pDOMWindow 	= pMozBrowser->webBrowser()->contentDOMWindow();
	boost::shared_ptr<DOMHTMLDocument> pHTMLDoc( doQueryInterface<DOMHTMLDocument>(pDOMWindow->document()) );
	
	if ( !pHTMLDoc->valid() )	return;
	
	DOMNode::Ptr 			pNode 		= pHTMLDoc->forms()->namedItem("homesearchform");
	DOMHTMLFormElement::Ptr pForm ( doQueryInterface<DOMHTMLFormElement>(pNode) ) ;
	if ( !pForm->valid() )	return;
	
	cout << b::format("pNode: %s") % pForm->name() << endl ;	 
	
// 	ScriptContext::Ptr 		pScriptContext 	= pMozBrowser->webBrowser()->contentDOMWindow()->getScriptContext();
// 	std::string sReturnVal;
// 	bool bOk= pScriptContext->evaluateString( "javascript:setPage(1);", sReturnVal);
// 	pForm->submit();
	
	int bFoundSearchBtn = 0;
	DOMHTMLCollection::iterator 	pIt;
	for ( pIt = pForm->elements()->begin(); pIt != pForm->elements()->end(); ++pIt ) {
		//cout << b::format( "MM: '%s'") % (*pIt)->nodeType() << endl;
		
		boost::shared_ptr<DOMCharacterData> pText( doQueryInterface<DOMCharacterData>(*pIt) );
		if ( pText->valid() ) {
			cout << b::format( "TT: '%s'") % pText->data() << endl;
		}
//		continue;
		
		boost::shared_ptr<DOMHTMLInputElement> pElem( doQueryInterface<DOMHTMLInputElement>(*pIt) );
		if ( !pElem->valid() ) continue;
		
		std::string sValue = pElem->getAttribute("onclick");
		cout << b::format( "A: '%s'") % pElem->value() << endl;
		
		if ( pElem->getAttribute("onclick") == "doSearch();"  ) {
			bFoundSearchBtn++;
			
			if ( bFoundSearchBtn == 2 ) {
				pElem->click();
				cout << b::format( "BB: SearchButton: %s") % pElem->getAttribute("onclick") << endl;
			}
		}
// 		if ( pElem->getAttribute("value") == "V1,V2" ) {
// 			cout << b::format( "CC:Villa: %s") % pElem->getAttribute("value") << endl;
// 			pElem->click();
// 		}
// 		
// 		if ( pElem->getAttribute("value") == "AA" ) {
// 			cout << b::format( "DD:Andel: %s") % pElem->getAttribute("value") << endl;
// 			pElem->click();
// 		}
// 		
// 		if ( pElem->getAttribute("name") == "maxPrice" ) {
// 			cout << b::format( "EE:maxPrice: %s") % pElem->getAttribute("name") << endl;
// 			pElem->value("3000000");
// 		}
	}
}

void ex_DomTest ( MozBrowserPtr pMozBrowser )
{
//	return ;
	cout << endl << "*** ex_DomTest *** " << endl << endl ;
	DOMWindowPtr 			pDOMWindow 	= pMozBrowser->webBrowser()->contentDOMWindow();
	boost::shared_ptr<DOMHTMLDocument> pHTMLDoc( doQueryInterface<DOMHTMLDocument>(pDOMWindow->document()) );
	
	if ( !pHTMLDoc->valid() )	return;
	
	DOMNode::Ptr 			pNode 		= pHTMLDoc->forms()->namedItem("testform");
	DOMHTMLFormElement::Ptr pForm ( doQueryInterface<DOMHTMLFormElement>(pNode) ) ;
	if ( !pForm->valid() )	return;
	
	cout << b::format("pNode: %s") % pForm->name() << endl ;	 
	
	int bFoundSearchBtn = 0;
	DOMHTMLCollection::iterator 	pIt;
	for ( pIt = pForm->elements()->begin(); pIt != pForm->elements()->end(); ++pIt ) {
		
		boost::shared_ptr<DOMCharacterData> pText( doQueryInterface<DOMCharacterData>(*pIt) );
		if ( pText->valid() ) {
			cout << b::format( "TT: '%s'") % pText->data() << endl;
		}
		
		boost::shared_ptr<DOMHTMLInputElement> pElem( doQueryInterface<DOMHTMLInputElement>(*pIt) );
		if ( !pElem->valid() ) continue;
		
		std::string sValue = pElem->getAttribute("onclick");
		cout << b::format( "A: '%s'") % pElem->value() << endl;
		
		if ( pElem->getAttribute("onclick") == "replaceSpan();"  ) {
			bFoundSearchBtn++;
			
			if ( bFoundSearchBtn == 1 ) {
				pElem->click();
				cout << b::format( "BB: SearchButton: %s") % pElem->getAttribute("onclick") << endl;
			}
		}
	}
}


void ex_Click (MozBrowserPtr pMozBrowser )
{
	DOMWindowPtr 			pDOMWindow 	= pMozBrowser->webBrowser()->contentDOMWindow();
	boost::shared_ptr<DOMHTMLDocument> pHTMLDoc( doQueryInterface<DOMHTMLDocument>(pDOMWindow->document()) );
	
	if ( !pHTMLDoc->valid() )	return;
	
	DOMNode::Ptr 			pNode 		= pHTMLDoc->forms()->namedItem("navigation");
	DOMHTMLFormElement::Ptr pForm ( doQueryInterface<DOMHTMLFormElement>(pNode) ) ;
	if ( !pForm->valid() )	return;
	
	cout << b::format("pNode: %s") % pForm->name() << endl ;	 
	
// 	ScriptContext::Ptr 		pScriptContext 	= pMozBrowser->webBrowser()->contentDOMWindow()->getScriptContext();
// 	std::string sReturnVal;
// 	bool bOk= pScriptContext->evaluateString( "javascript:setPage(1);", sReturnVal);
// 	pForm->submit();
	
	DOMHTMLCollection::iterator 	pIt;
	for ( pIt = pForm->elements()->begin(); pIt != pForm->elements()->end(); ++pIt ) {
		boost::shared_ptr<DOMHTMLInputElement> pElem( doQueryInterface<DOMHTMLInputElement>(*pIt) );
		if ( !pElem->valid() ) continue;
		//cout << b::format( "getAttribute('name'): %s") % pElem->getAttribute("name") << endl;
		
		if ( pElem->getAttribute("class") == "linkLook boldBlackFont rightArrow" ) {
			cout << b::format( "getAttribute('class'): %s") % pElem->getAttribute("class") << endl;
			pElem->click();
		}
		
	}
}


void ex_Links (MozBrowserPtr pMozBrowser )
{
	DOMWindowPtr 			pDOMWindow 	= pMozBrowser->webBrowser()->contentDOMWindow();
	
	boost::shared_ptr<DOMHTMLDocument> pHTMLDoc( doQueryInterface<DOMHTMLDocument>(pDOMWindow->document()) );
	
	if ( !pHTMLDoc->valid() )	return;
	
	DOMHTMLCollection::iterator 	pIt;
	DOMHTMLCollection::Ptr 			pNodes 		= pHTMLDoc->links();
	
	cout << b::format("Url: %s") % pHTMLDoc->url() << endl ;	 
	cout << "Links: " << pNodes->size() << endl;
	for ( pIt = pNodes->begin(); pIt != pNodes->end(); ++pIt ) {
		boost::shared_ptr<DOMHTMLElement> pElem( doQueryInterface<DOMHTMLElement>(*pIt) );
		if ( !pElem->valid() ) continue;
		cout << b::format( "getAttribute('href'): %s") % pElem->getAttribute("href") << endl;
	}
}



void ex_HTMLElements ( MozBrowserPtr pMozBrowser )
{
	static int iCount = 0;
	DOMWindowPtr 			pDOMWindow 	= pMozBrowser->webBrowser()->contentDOMWindow();
	DOMNodeListPtr 			pNodes 		= pDOMWindow->document()->getElementsByTagName( "*" );
	DOMNodeList::iterator 	pIt;
	
	cout << "Number of nodes: " << pNodes->size() << endl;
	for ( pIt = pNodes->begin(); pIt != pNodes->end(); ++pIt ) {
//		cout << b::format("nodeName, Value: %s, %s") % (*pIt)->nodeName() % (*pIt)->nodeValue() << endl ;	 
				
				
		boost::shared_ptr<DOMHTMLElement> pElem( doQueryInterface<DOMHTMLElement>(*pIt) );
		if ( pElem->valid() )
		{
	//		cout << b::format("HTMLElement: nodeName, id: %s %s") % pElem->nodeName() % pElem->id() << endl ;	 
			//cout << "DOMElement.tagName             : " << pElem->tagName() 				<< endl;
			//cout << "DOMElement.getAttribute.value  : " << pElem->getAttribute("value") 	<< endl;
			
			boost::shared_ptr<DOMHTMLFormElement> pForm( doQueryInterface<DOMHTMLFormElement>(*pIt) );
			if ( pForm->valid() ){
				cout << b::format("Form: (nodeName, name): (%s, %s)") % pForm->nodeName() % pForm->name() << endl ;	 
				
			}
			
			if ( iCount == 2 ) {
				if ( pElem->hasAttribute("value")) {
					cout << "Changing attribute value" << endl;
					pElem->setAttribute("value", "http://www.doxys.dk");	
				}
			}
		}
	}
	iCount++;
}

void ex_Elements (MozBrowserPtr pMozBrowser )
{
	static int iCount = 0;
	DOMWindowPtr 			pDOMWindow 	= pMozBrowser->webBrowser()->contentDOMWindow();
	DOMNodeListPtr 			pNodes 		= pDOMWindow->document()->getElementsByTagName( "*" );
	DOMNodeList::iterator 	pIt;
	
	cout << "Number of nodes: " << pNodes->size() << endl;
	for ( pIt = pNodes->begin(); pIt != pNodes->end(); ++pIt ) {
//		cout << b::format("Node Name, Value: %s, %s") % (*pIt)->nodeName() % (*pIt)->nodeValue() << endl ;	 
				
				
// 		boost::shared_ptr<DOMNodeList> pFail( doQueryInterface<DOMNodeList>(*pIt) );
// 		if ( pFail->valid() )
// 		{
// 			cout << "NOT failed !!" << endl;
// 		}
// 		else cout << "FAILED (as this should)" << endl; 
				
		boost::shared_ptr<DOMElement> pElem( doQueryInterface<DOMElement>(*pIt) );
		if ( pElem->valid() )
		{
			//cout << "DOMElement.tagName             : " << pElem->tagName() 				<< endl;
			//cout << "DOMElement.getAttribute.value  : " << pElem->getAttribute("value") 	<< endl;
			if ( iCount == 2 ) {
				if ( pElem->hasAttribute("value")) {
					cout << "Changing attribute value" << endl;
					pElem->setAttribute("value", "http://www.doxys.dk");	
				}
			}
		}
	}
	iCount++;
}



void ex_Javascript (MozBrowserPtr pMozBrowser )
{
	cout << "Javascript example !!" << endl;
	WebBrowserPtr 			pWebBrowser 	= pMozBrowser->webBrowser();
	ScriptContextPtr 		pScriptContext 	= pWebBrowser->contentDOMWindow()->getScriptContext();
	
	std::string sReturnVal;
//	bool bOk= pScriptContext->evaluateString( "bob();", sReturnVal );
//	bool bOk= pScriptContext->evaluateString( "marley('http://www.google.dk');", sReturnVal );
//	bool bOk= pScriptContext->evaluateString( "martin('http://www.w3c.org');", sReturnVal );
//	bool bOk= pScriptContext->evaluateString( "lutken('');", sReturnVal );
	
//	bool bOk= pScriptContext->evaluateString( "link('_dir','testcode1/geoms/geoms0',this);", sReturnVal );	// For http://www.doxys.dk
	
//	bool bOk= pScriptContext->evaluateString( "javascript:doSearch();", sReturnVal );	// For http://www.home.dk
//	bool bOk= pScriptContext->evaluateString( "javascript:gotocase('208-8074');", sReturnVal);
	bool bOk= pScriptContext->evaluateString( "Javascript:checkAndSubmit();", sReturnVal);
	

	cout << "RETURN VALUE: " << sReturnVal << endl;
	cout << "bOk: " << bOk << endl;
}


void ex_WebNavigation (MozBrowserPtr pMozBrowser )
{
	WebBrowserPtr 			pWebBrowser 	= pMozBrowser->webBrowser();
	boost::shared_ptr<WebNavigation> pWebNav = doQueryInterface<WebNavigation>( pMozBrowser->webBrowser() );
	if ( pWebNav->valid() )
	{
		cout << "WebNavigation found !!" << endl;
// 		pWebNav->loadURI( "http://www.home.dk" );
// 		pWebNav->loadURI("javascript:__doPostBack('ctl00$Content$Find','')");
		cout << "Current URI: " << pWebNav->currentURIAsString() << endl;
		
		cout << endl;
		cout << "--------------------------------" 	<< endl;
		cout << "--- Current URI Page source: --- "	<< endl;
		cout << "--------------------------------"	<< endl;
		cout << pWebNav->currentURIPageSourceWget()	<< endl;
		cout << "--------------------------------"	<< endl;
		
	}
}



void ex_DOM (MozBrowserPtr pMozBrowser )
{
	DOMWindowPtr 			pDOMWindow 	= pMozBrowser->webBrowser()->contentDOMWindow();
	DOMNodeListPtr 			pNodes 		= pDOMWindow->document()->getElementsByTagName( "*" );
//	DOMNodeListPtr 			pNodes 		= pDOMWindow->document()->childNodes();
	DOMNodeList::iterator 	pIt;
	
	cout << "Number of nodes: " << pNodes->size() << endl;
	for ( pIt = pNodes->begin(); pIt != pNodes->end(); ++pIt ) {
//		cout << b::format("Node Name, Value: %s, %s") % (*pIt)->nodeName() % (*pIt)->nodeValue() << endl ;	 
		
		boost::shared_ptr<DOMHTMLElement> pElem( doQueryInterface<DOMHTMLElement>(*pIt) );
		if ( !pElem->valid() ) return;
		
//		cout << b::format("1: NodeName: %s, %d") % (*pIt)->nodeName() % (*pIt)->nodeType() << endl ;	 
		cout << b::format("A(%d): title(): %s, '%s'") % (*pIt)->nodeType() % pElem->title() % pElem->prefix() << endl ;	 
//		cout << b::format("A(%d)") % (*pIt)->nodeType() << endl ;	 
				
				
			
// 		DOMNamedNodeMapPtr 			pNodes1 	= (*pIt)->attributes();	// Attribute nodes	
// 		DOMNamedNodeMap::iterator 	pIt1;								
		DOMNodeListPtr 				pNodes1 	= (*pIt)->childNodes();
		DOMNodeList::iterator 		pIt1;
		
		for ( pIt1 = pNodes1->begin(); pIt1 != pNodes1->end(); ++pIt1 ) {
//			if ( (*pIt1)->nodeName() == "href" )	cout << b::format("href=%s") % (*pIt1)->nodeValue() << endl ;
			
			cout << b::format("B(%d): NodeName: %s, '%s'") % (*pIt1)->nodeType() % (*pIt1)->nodeName() % (*pIt1)->nodeValue() << endl ;	 
		}
	}
}


static void
ex_DOMWindow_Name( boost::shared_ptr<DOMWindow> pDOMWindow )
{
	cout << "Example: nsIDOMWindow Name 1" << endl;
	if ( pDOMWindow->name().empty() ) {
		cout << "EMPTY 1" << endl;
		pDOMWindow->name( "DOM name with std::string" );
	}
	else {
		cout << b::format("DOM Window Name 1: %s\n") % pDOMWindow->name();
	}
}

// void ex_DOMNodeVec ( MozBrowserPtr pMozBrowser )
// {
// 	DOMWindowPtr 					pDOMWindow 	= pMozBrowser->webBrowser()->contentDOMWindow();
// 	std::vector<DOMNode> 			nodes 		= pDOMWindow->document()->getElementsByTagNameCopy( "a" );
// 	std::vector<DOMNode>::iterator 	it;
// 	
// 	cout << "Number of nodes: " << nodes.size() << endl;
// 	for ( it = nodes.begin(); it != nodes.end(); ++it ) {
// 		cout << b::format("Node Name, Value: %s, %s") % it->nodeName() % it->nodeValue() << endl ;	 
// 	}
// 
// }


// --------------------------------
// --------------------------------
// --------------------------------

//#include "nsEmbedString.h>
// // #include <dom/nsIDOMNodeList.h>
// // #include <dom/nsIDOMElement.h>
// // #include <dom/nsIDOMNode.h>
// // #include <dom/nsIDOMNamedNodeMap.h>

#include <nsIDOMNodeList.h>
#include <nsIDOMElement.h>
#include <nsIDOMNode.h>
#include <nsIDOMNamedNodeMap.h>

static void 
ex_nsIDOMDocument_Intro ( nsIDOMDocument* domDoc )
{
	nsresult res;
	printf("Get Document \n");
	nsCOMPtr<nsIDOMNodeList> nodelist;
//	res = domDoc->GetElementsByTagName(NS_LITERAL_STRING("*"),getter_AddRefs(nodelist));	// All elements
	res = domDoc->GetElementsByTagName(NS_LITERAL_STRING("a"),getter_AddRefs(nodelist));	// a elements
	
	PRUint32 index;
	PRUint32 length;
 	res = nodelist->GetLength(&length);
 	printf("Get nodelist num[%d] res[%d]\n",length,res);
 	for(index=0;index<length;index++)
 	{
 		nsCOMPtr<nsIDOMNode> node;
		res=nodelist->Item(index,getter_AddRefs(node));
		
		nsEmbedString sNodeName, sNodeValue;
		node->GetNodeName(sNodeName);
		node->GetNodeValue(sNodeValue);
		printf("Node(name, value): ( %s , %s )\n", NS_ConvertUTF16toUTF8(sNodeName).get(), NS_ConvertUTF16toUTF8(sNodeValue).get());
		PRUint32 iAttribIndex;
		PRUint32 iAttribLength;
		nsCOMPtr<nsIDOMNamedNodeMap> nodeAttribs;
		res = node->GetAttributes( getter_AddRefs(nodeAttribs) );	
		
		nodeAttribs->GetLength ( &iAttribLength ); 
		for ( iAttribIndex=0 ; iAttribIndex < iAttribLength; iAttribIndex++ )
		{
			nsCOMPtr<nsIDOMNode> attribNode;
			res = nodeAttribs->Item( iAttribIndex, getter_AddRefs( attribNode ));
			nsEmbedString s1, s2;
			attribNode->GetNodeName(s1);
			attribNode->GetNodeValue(s2);
			printf("attribNode(name, value): ( %s , %s )\n", NS_ConvertUTF16toUTF8(s1).get(), NS_ConvertUTF16toUTF8(s2).get());
		}		
 	}

}

void ex_javascript1(nsIWebBrowser*  pIWebBrowser )
{
	nsCOMPtr<nsIScriptGlobalObjectOwner> theGlobalObjectOwner(do_GetInterface(pIWebBrowser));
	nsCOMPtr<nsIDOMWindow> pIDOMWindow;
	pIWebBrowser->GetContentDOMWindow ( getter_AddRefs ( pIDOMWindow ) );
	
	if (theGlobalObjectOwner) {
		//JSFunction* jsf;
//		nsIScriptGlobalObject* pIScriptGlobalObject = theGlobalObjectOwner->GetScriptGlobalObject();
//		nsCOMPtr<nsIScriptGlobalObject> pIScriptGlobalObject( do_QueryInterface(pIDOMWindow) );	// VIRKER	
		nsCOMPtr<nsIScriptGlobalObject> pIScriptGlobalObject( do_GetInterface(pIDOMWindow) );	// VIRKER	
		
//		nsCOMPtr<nsIScriptContext> pIScriptContext ( do_QueryInterface(pIScriptGlobalObject) );	// VIRKER IKKE. Ser det ud til!
//		nsIScriptContext* pIScriptContext = pIScriptGlobalObject->GetContext();	// VIRKER
//		nsCOMPtr<nsIScriptContext> pIScriptContext ( pIScriptGlobalObject->GetContext() );	// VIRKER ogs�. Ser det ud til!
		nsCOMPtr<nsIScriptContext> pIScriptContext1 ( pIScriptGlobalObject->GetContext() );	// VIRKER ogs�. Ser det ud til!
		
		nsCOMPtr<nsIScriptContext> pIScriptContext ( pIScriptContext1 );	// VIRKER ogs�. Ser det ud til!
        
        if ( ! pIScriptContext )
        {
        	printf("HHHHHHHHHHHHH\n");
        	return;
        }
        
//        static int iCount = 0;
//        if ( iCount++ == 0 ) return;
        
		nsIPrincipal *thePrincipal = nsnull;
		PRBool IsUndefined;
		nsEmbedString theReturnValue;
		nsresult rv = pIScriptContext->EvaluateString( 
//				NS_LITERAL_STRING("javascript:validatePostnr('4700');"),	// works on www.home.dk (main page)
//				NS_LITERAL_STRING("javaScript:selectAll();"),
//				NS_LITERAL_STRING("javascript:changePage();"),
//				NS_LITERAL_STRING("javascript:doSearch();"),
				NS_LITERAL_STRING("javascript:__doPostBack('ctl00$Content$NewSearch','')"),
				nsnull,
				thePrincipal, 
				"", 
				1, 
				JSVERSION_LATEST, 
				&theReturnValue,
				&IsUndefined );
				
		printf("AAAAAAAAA: IsUndefined   : %d\n", IsUndefined);
		printf("AAAAAAAAA: theReturnValue: %s\n", NS_ConvertUTF16toUTF8(theReturnValue).get());
				
	}
}




