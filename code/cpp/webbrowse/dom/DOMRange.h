#ifndef _WEBBROWSE_DOM_RANGE_H_
#define _WEBBROWSE_DOM_RANGE_H_

#include <nsIDOMRange.h>

#include <utils/mozilla_if_macros.h>
#include <utils/mozilla_utils.h>

class DOMRange;
typedef boost::shared_ptr<DOMRange>		DOMRangePtr;			///< Pointer to a DOMRange

class DOMNode;
class DOMDocumentFragment;

/**
* The nsIDOMRange interface is an interface to a DOM range object.
*
* For more information on this interface please see
* http://www.w3.org/TR/DOM-Level-2-Traversal-Range/
*
* @status FROZEN
*/
class DOMRange : public Supports {
	MOZ_CONSTRUCT(DOMRange,Supports);
public: 

	/* readonly attribute nsIDOMNode startContainer; */
	//NS_SCRIPTABLE NS_IMETHOD GetStartContainer(nsIDOMNode * *aStartContainer) = 0;
	
	/* readonly attribute long startOffset; */
	//NS_SCRIPTABLE NS_IMETHOD GetStartOffset(PRInt32 *aStartOffset) = 0;
	
	/* readonly attribute nsIDOMNode endContainer; */
	//NS_SCRIPTABLE NS_IMETHOD GetEndContainer(nsIDOMNode * *aEndContainer) = 0;
	
	/* readonly attribute long endOffset; */
	//NS_SCRIPTABLE NS_IMETHOD GetEndOffset(PRInt32 *aEndOffset) = 0;
	
	/* readonly attribute boolean collapsed; */
	//NS_SCRIPTABLE NS_IMETHOD GetCollapsed(PRBool *aCollapsed) = 0;
	
	/* readonly attribute nsIDOMNode commonAncestorContainer; */
	//NS_SCRIPTABLE NS_IMETHOD GetCommonAncestorContainer(nsIDOMNode * *aCommonAncestorContainer) = 0;
	
	/* void setStart (in nsIDOMNode refNode, in long offset)  raises (RangeException, DOMException); */
	//NS_SCRIPTABLE NS_IMETHOD SetStart(nsIDOMNode *refNode, PRInt32 offset) = 0;
	
	/* void setEnd (in nsIDOMNode refNode, in long offset)  raises (RangeException, DOMException); */
	//NS_SCRIPTABLE NS_IMETHOD SetEnd(nsIDOMNode *refNode, PRInt32 offset) = 0;
	
	/* void setStartBefore (in nsIDOMNode refNode)  raises (RangeException, DOMException); */
	//NS_SCRIPTABLE NS_IMETHOD SetStartBefore(nsIDOMNode *refNode) = 0;
	
	/* void setStartAfter (in nsIDOMNode refNode)  raises (RangeException, DOMException); */
	//NS_SCRIPTABLE NS_IMETHOD SetStartAfter(nsIDOMNode *refNode) = 0;
	
	/* void setEndBefore (in nsIDOMNode refNode)  raises (RangeException, DOMException); */
	//NS_SCRIPTABLE NS_IMETHOD SetEndBefore(nsIDOMNode *refNode) = 0;
	
	/* void setEndAfter (in nsIDOMNode refNode)  raises (RangeException, DOMException); */
	//NS_SCRIPTABLE NS_IMETHOD SetEndAfter(nsIDOMNode *refNode) = 0;
	
	/* void collapse (in boolean toStart)  raises (DOMException); */
	//NS_SCRIPTABLE NS_IMETHOD Collapse(PRBool toStart) = 0;
	
	/* void selectNode (in nsIDOMNode refNode)  raises (RangeException, DOMException); */
	//NS_SCRIPTABLE NS_IMETHOD SelectNode(nsIDOMNode *refNode) = 0;
	
	/* void selectNodeContents (in nsIDOMNode refNode)  raises (RangeException, DOMException); */
	//NS_SCRIPTABLE NS_IMETHOD SelectNodeContents(nsIDOMNode *refNode) = 0;
	
	//enum { START_TO_START = 0U };
	
	//enum { START_TO_END = 1U };
	
	//enum { END_TO_END = 2U };
	
	//enum { END_TO_START = 3U };
	
	/* short compareBoundaryPoints (in unsigned short how, in nsIDOMRange sourceRange)  raises (DOMException); */
	//NS_SCRIPTABLE NS_IMETHOD CompareBoundaryPoints(PRUint16 how, nsIDOMRange *sourceRange, PRInt16 *_retval NS_OUTPARAM) = 0;
	
	/* void deleteContents ()  raises (DOMException); */
	//NS_SCRIPTABLE NS_IMETHOD DeleteContents(void) = 0;
	
	/* nsIDOMDocumentFragment extractContents ()  raises (DOMException); */
	//NS_SCRIPTABLE NS_IMETHOD ExtractContents(nsIDOMDocumentFragment **_retval NS_OUTPARAM) = 0;
	
	/* nsIDOMDocumentFragment cloneContents ()  raises (DOMException); */
	//NS_SCRIPTABLE NS_IMETHOD CloneContents(nsIDOMDocumentFragment **_retval NS_OUTPARAM) = 0;
	
	/* void insertNode (in nsIDOMNode newNode)  raises (DOMException, RangeException); */
	//NS_SCRIPTABLE NS_IMETHOD InsertNode(nsIDOMNode *newNode) = 0;
	
	/* void surroundContents (in nsIDOMNode newParent)  raises (DOMException, RangeException); */
	//NS_SCRIPTABLE NS_IMETHOD SurroundContents(nsIDOMNode *newParent) = 0;
	
	/* nsIDOMRange cloneRange ()  raises (DOMException); */
	//NS_SCRIPTABLE NS_IMETHOD CloneRange(nsIDOMRange **_retval NS_OUTPARAM) = 0;
	
	/* DOMString toString ()  raises (DOMException); */
	//NS_SCRIPTABLE NS_IMETHOD ToString(nsAString & _retval NS_OUTPARAM) = 0;
	
	/* void detach ()  raises (DOMException); */
	//NS_SCRIPTABLE NS_IMETHOD Detach(void) = 0;

};

#endif /* _WEBBROWSE_DOM_RANGE_H_ */

