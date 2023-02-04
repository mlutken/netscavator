#ifndef _WEBBROWSE_DOM_NODE_END_TAG_H_
#define _WEBBROWSE_DOM_NODE_END_TAG_H_

#include <dom/DOMNode.h>



/**
Special DOMNode used by crawler code only. Used for inserting 
endtags in the document like </DIV> </A> etc.
*/
class DOMNodeEndTag : public DOMNode {
	public:															
		DOMNodeEndTag ( std::string sStringData ) 							
		 :	DOMNode(0) 
		{
			forceStringData( sStringData );
			forceNodeType( DOMNode::NODE_END_TAG ); 
		}							
	typedef boost::shared_ptr<DOMNodeEndTag>	Ptr;						

private:					
	
public: 
};



#endif /* _WEBBROWSE_DOM_NODE_END_TAG_H_ */
