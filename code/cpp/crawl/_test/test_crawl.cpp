
#include <iostream>
#include <fstream>
#include <string>
#include <boost/format.hpp> 

#include <dom/DOMHTMLInputElement.h>
#include <dom/DOMHTMLDocument.h>
#include <utils/webbrowse_string_utils.h>

#include <parser/DomDocumentLinear.h>
#include <parser/LinearDomSearch.h>
#include <parser/linear_dom_algorithms.h>
#include <parser/dom_node_convenience.h>
#include <parser/StringSearch.h>


using namespace std;
using namespace crawl;

void
printNodeStringData	( 
	DOMNode::Ptr pNode, 					///< DOMNode (pointer) to print.
	DomDocumentLinear const* pDomLinear, 	///< Owner DomDocumentLinear (pointer) .
	std::ostream& os	) 					///< Stream to print to
{
	using namespace std;
	
	
	string sNodeType("");
	if ( pDomLinear->printNodeTypes() )	sNodeType = "[" + nodeTypeToString ( pNode ) + "]" ;
	
	if ( 		pNode->nodeType() 	== DOMNode::ATTRIBUTE ) {
 		os	 << sNodeType << pNode->stringData() <<  "=" ;	 
	}
	else if ( 	pNode->nodeType() 	== DOMNode::TEXT ) {
 		os << ">" << sNodeType << pNode->stringData() << "< " ;	 
	}
	else if ( 	pNode->nodeType() 	== DOMNode::ATTRIBUTE_VALUE ) {
 		os << ">" << sNodeType << pNode->stringData() << "< " ;	 
	}
	else if ( 	pNode->nodeType() 	== DOMNode::COMMENT ) {
 		os << "<!-- " << sNodeType << pNode->stringData() << " --> " ;	 
	}
	else if ( 	pNode->nodeType() 	== DOMNode::DOCUMENT ) {
 		os << sNodeType << pNode->stringData() << " " ;	 
	}
	else {
 		os << "<" << sNodeType << pNode->stringData() << " " ;	 
	}
}




void test_DomDocumentLinear ( boost::shared_ptr<MozBrowser> pMozBrowser ) 
{
	cout << "test_DomDocumentLinear" << endl;
	DomDocumentLinear linearDom ( pMozBrowser->webBrowser()->contentDOMWindow()->document() ) ;
//	linearDom.assignPrintNodeFun ( printNodeStringData ) ;
	std::string sFileName = std::string( VERIQUIN_CODE_DIR ) + "/cpp/crawl/_test/" ;
	sFileName += "home_sag_108C6332.txt" ;
//	sFileName += "DomDocumentLinear.txt" ;
	
//	ofstream file ( sFileName.c_str() ) ;
//	cout << "SSSSSSSS: " << VERIQUIN_CODE_DIR  << endl ; 
//	linearDom.print ( file );
//	linearDom.print ( std::cout );
//	linearDom.printNodeTypes(true);
	cout << linearDom ;
	
	DomDocumentLinear::const_iterator it;
	it = findPred ( linearDom.begin(), linearDom.end(), "href", crawl::string_compare::equals, 6 );
	if ( it != linearDom.end() ) {
		cout << "FOUND: " << nodeTypeToString(*it) << " " << (*it)->stringData() << endl ;
		if ( ++it != linearDom.end() ) {
			cout << "NEXT " << nodeTypeToString((*it)) << " Node: '" << (*it)->stringData() << "'" << endl ;
		}
	}
	cout << endl ;
	
	//pNode->nodeValue()
	
// 	cout << "DOM Node types test: " << endl ;
// 	cout << boost::format ( "ELEMENT                : %x" ) % static_cast<int>(DOMNode::ELEMENT) 				<< endl ;
// 	cout << boost::format ( "ATTRIBUTE              : %x" ) % static_cast<int>(DOMNode::ATTRIBUTE) 				<< endl ;
// 	cout << boost::format ( "TEXT                   : %x" ) % static_cast<int>(DOMNode::TEXT) 					<< endl ;
// 	cout << boost::format ( "CDATA_SECTION          : %x" ) % static_cast<int>(DOMNode::CDATA_SECTION) 			<< endl ;
// 	cout << boost::format ( "ENTITY_REFERENCE       : %x" ) % static_cast<int>(DOMNode::ENTITY_REFERENCE) 		<< endl ;
// 	cout << boost::format ( "ENTITY                 : %x" ) % static_cast<int>(DOMNode::ENTITY) 				<< endl ;
// 	cout << boost::format ( "PROCESSING_INSTRUCTION : %x" ) % static_cast<int>(DOMNode::PROCESSING_INSTRUCTION) << endl ;
// 	cout << boost::format ( "COMMENT                : %x" ) % static_cast<int>(DOMNode::COMMENT) 				<< endl ;
// 	cout << boost::format ( "DOCUMENT               : %x" ) % static_cast<int>(DOMNode::DOCUMENT) 				<< endl ;
// 	cout << boost::format ( "DOCUMENT_TYPE          : %x" ) % static_cast<int>(DOMNode::DOCUMENT_TYPE) 			<< endl ;
// 	cout << boost::format ( "DOCUMENT_FRAGMENT      : %x" ) % static_cast<int>(DOMNode::DOCUMENT_FRAGMENT) 		<< endl ;
// 	cout << boost::format ( "NOTATION               : %x" ) % static_cast<int>(DOMNode::NOTATION) 				<< endl ;
// 	cout << boost::format ( "ALL_NODE_TYPES         : %x" ) % static_cast<int>(DOMNode::ALL_NODE_TYPES) 		<< endl ;
}



void test_HomeNavigation ( boost::shared_ptr<MozBrowser> pMozBrowser ) 
{
//	return ;
	static int iCount = 0;
	cout << "*** test_HomeNavigation ***: " << ++iCount << endl;
	DomDocumentLinear linearDom ( pMozBrowser->webBrowser()->contentDOMWindow()->document() ) ;
	std::string sFileName = std::string( VERIQUIN_CODE_DIR ) + "/cpp/crawl/_test/" ;
	sFileName += "home_dk.txt" ;
//	cout << linearDom ;
	
	DomDocumentLinear::const_iterator it, itBegin, itEnd;
	itBegin = linearDom.begin();
	itEnd 	= linearDom.end();
	it = findPred ( itBegin, itEnd, "doSearch();", crawl::string_compare::equals, 1 );
	if ( it != itEnd ) {
		cout << "FOUND(1): " << (*it)->stringData() << endl ;
		itEnd = it;
		it = findPred ( itBegin, itEnd, "INPUT", crawl::string_compare::equals, -1 );
		if ( it != itEnd ) {
			cout << "FOUND(2): " << (*it)->stringData() << endl ;
 			DOMHTMLInputElement::Ptr pInput ( doQueryInterface<DOMHTMLInputElement>( *it ) );
 			if ( pInput->valid() ) {
 				pInput->click();
	 			cout << "CLICK: " << pInput->stringData() << endl ;
 			}
		}
	}
	cout << endl ;
}



void test_DomTest ( boost::shared_ptr<MozBrowser> pMozBrowser ) 
{
	static int iCount = 0;
	cout << endl << "*** test_DomTest *** : " << ++iCount << endl;
	DomDocumentLinear linearDom ( pMozBrowser->webBrowser()->contentDOMWindow()->document() ) ;
	std::string sFileName = std::string( VERIQUIN_CODE_DIR ) + "/cpp/crawl/_test/" ;
	sFileName += "DomTest.txt" ;
	cout << linearDom ;
	
	DomDocumentLinear::const_iterator it, itBegin, itEnd;
	itBegin = linearDom.begin();
	itEnd 	= linearDom.end();
	it = findPred ( itBegin, itEnd, "replaceSpan();", crawl::string_compare::equals, 1 );
	if ( it != itEnd ) {
		cout << "FOUND(1): " << (*it)->stringData() << endl ;
		itEnd = it;
		it = findPred ( itBegin, itEnd, "INPUT", crawl::string_compare::equals, -1 );
		if ( it != itEnd ) {
			cout << "FOUND(2): " << (*it)->stringData() << endl ;
 			DOMHTMLInputElement::Ptr pInput ( doQueryInterface<DOMHTMLInputElement>( *it ) );
 			if ( pInput->valid() ) {
				pInput->value("Hejsa");
 				pInput->click();
	 			cout << "CLICK: " << pInput->stringData() << endl ;
 			}
		}
	}
	cout << endl ;
}


void test_DomTestConvenience ( boost::shared_ptr<MozBrowser> pMozBrowser ) 
{
	static int iCount = 0;
	cout << endl << "*** test_DomTestConvenience *** : " << ++iCount << endl;
	DomDocumentLinear linearDom ( pMozBrowser->webBrowser()->contentDOMWindow()->document() ) ;
//	cout << linearDom ;
	
	DomDocumentLinear::const_iterator it, itBegin, itEnd;
	itBegin = linearDom.begin();
	itEnd 	= linearDom.end();
	it = findPred ( itBegin, itEnd, "replaceSpan();", crawl::string_compare::equals, 1 );
	if ( it != itEnd ) {
		itEnd = it;
		it = findINPUT ( itBegin, itEnd, -1 );
		if ( it != itEnd ) {
			inputClick ( *it ) ;
			inputValue ( *it, "Mojn" ) ;
		}
	}
	cout << endl ;
}

void test_LinearDomSearch ( boost::shared_ptr<MozBrowser> pMozBrowser ) 
{
	namespace cmp = crawl::string_compare ;
	static int iCount = 0;
	cout << endl << "*** test_LinearDomSearch *** : " << ++iCount << endl;
	DomDocumentLinear linearDom ( pMozBrowser->webBrowser()->contentDOMWindow()->document() ) ;
	LinearDomSearch ds( linearDom );
//	cout << linearDom ;
	
	//stringData	
	
	ds.find( "quick", 			cmp::contains, 1 	) ;
//	cout << "StringData: " << ds.curElem()->stringData() << endl ;
	StringSearch ss( std::cout, ds.curElemPtr()->stringData() ) ;
	ss.findBegin( "quick" );
	ss.findEnd( "jumps" );
	ss.setValueBeginEnd();
	ss.valueTrim() ;
//	cout << "VALUE: '" << ss.getValue() << "'" << endl ;
	ss.beginTableEntry ( "Cust_pos_ref" ) ;
	ss.outputValue ( "VAL" ) ; 
	ss.endTableEntry ( "Intern comment" ) ;	
	ds.find( "replaceSpan();", 	cmp::equals,  1 	) ;
	ds.next( "INPUT", 			cmp::equals, -1 	) ;
	inputClick ( ds.curElemPtr() 					) ;
	inputValue ( ds.curElemPtr(), "Mojn"			) ;
	
// 	if ( ds.find( "replaceSpan();", crawl::string_compare::equals, 1 ) )
// 	{
// 		if ( ds.next( "INPUT", crawl::string_compare::equals, -1 ) ) {
// 			inputClick ( ds.curElem() ) ;
// 			inputValue ( ds.curElem(), "Mojn" ) ;
// 		}
// 	}
	cout << endl ;
}

