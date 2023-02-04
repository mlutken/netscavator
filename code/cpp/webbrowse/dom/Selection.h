#ifndef _WEBBROWSE_SELECTION_H_
#define _WEBBROWSE_SELECTION_H_

#include <nsISelection.h>

#include <utils/mozilla_if_macros.h>
#include <utils/mozilla_utils.h>

class Selection;
typedef boost::shared_ptr<Selection>		SelectionPtr;			///< Pointer to a Selection

class DOMNode;
class DOMRange;	

/**
 * Interface for manipulating and querying the current selected range
 * of nodes within the document.
 *
 * @status FROZEN
 * @version 1.0
 */
class Selection : public Supports {
	MOZ_CONSTRUCT(Selection,Supports);
public: 
	
	virtual ~Selection() {}
	/**
		* Returns the node in which the selection begins.
		*/
	boost::shared_ptr<DOMNode>
	anchorNode() const;
	
	/**
		* The offset within the (text) node where the selection begins.
		*/
	boost::int32_t
	anchorOffset () const
										{	MOZ_IF_RETURN_INT32(GetAnchorOffset);	}
	
	/**
		* Returns the node in which the selection ends.
		*/
	boost::shared_ptr<DOMNode>
	focusNode() const;
	
	/**
		* The offset within the (text) node where the selection ends.
		*/
	boost::int32_t
	focusOffset () const
										{	MOZ_IF_RETURN_INT32(GetFocusOffset);	}
	
	/**
		* Indicates if the selection is collapsed or not.
		*/
	bool  				
	isCollapsed() const 
										{	MOZ_IF_RETURN_BOOL(GetIsCollapsed); }
	
	/**
		* Returns the number of ranges in the selection.
		*/
	boost::int32_t
	rangeCount () const
										{	MOZ_IF_RETURN_INT32(GetRangeCount);	}
	
	/**
		* Returns the range at the specified index.
		*/
 	boost::shared_ptr<DOMRange>
 	getRangeAt( boost::int32_t index ) const;
	
	/**
		* Collapses the selection to a single point, at the specified offset
		* in the given DOM node. When the selection is collapsed, and the content
		* is focused and editable, the caret will blink there.
		* @param parentNode      The given dom node where the selection will be set
		* @param offset          Where in given dom node to place the selection (the offset into the given node)
		*/
	void 
	collapse( boost::shared_ptr<DOMNode> parentNode, boost::int32_t offset );
	
	/**
		* Extends the selection by moving the selection end to the specified node and offset,
		* preserving the selection begin position. The new selection end result will always
		* be from the anchorNode to the new focusNode, regardless of direction.
		* @param parentNode      The node where the selection will be extended to
		* @param offset          Where in node to place the offset in the new selection end
		*/
	void 
	extend( boost::shared_ptr<DOMNode> parentNode, boost::int32_t offset );
	
	/**
		* Collapses the whole selection to a single point at the start
		* of the current selection (irrespective of direction).  If content
		* is focused and editable, the caret will blink there.
		*/
	void collapseToStart () {	ifMoz()->CollapseToStart();	}
	
	/**
		* Collapses the whole selection to a single point at the end
		* of the current selection (irrespective of direction).  If content
		* is focused and editable, the caret will blink there.
		*/
	void collapseToEnd () {	ifMoz()->CollapseToEnd();	}
	
	/**
		* Indicates whether the node is part of the selection. If partlyContained 
		* is set to PR_TRUE, the function returns true when some part of the node 
		* is part of the selection. If partlyContained is set to PR_FALSE, the
		* function only returns true when the entire node is part of the selection.
		*/
	bool	
	containsNode ( boost::shared_ptr<DOMNode> node, bool partlyContained ); 
	
	/**
		* Adds all children of the specified node to the selection.
		* @param parentNode  the parent of the children to be added to the selection.
		*/
	void	selectAllChildren ( boost::shared_ptr<DOMNode> parentNode );
	 	
	/**
		* Adds a range to the current selection.
		*/
	void addRange ( boost::shared_ptr<DOMRange> range );	
	
	/**
		* Removes a range from the current selection.
		*/
	void removeRange ( boost::shared_ptr<DOMRange> range );	
	
	/**
		* Removes all ranges from the current selection.
		*/
	void removeAllRanges ()
								{	ifMoz()->RemoveAllRanges();	}
	/**
		* Deletes this selection from document the nodes belong to.
		*/
	void deleteFromDocument ()
								{	ifMoz()->DeleteFromDocument();	}
	
	/**
		* Modifies the cursor Bidi level after a change in keyboard direction
		* @param langRTL is PR_TRUE if the new language is right-to-left or
		*                PR_FALSE if the new language is left-to-right.
		*/
	void selectionLanguageChange ( bool langRTL)
										{	ifMoz()->SelectionLanguageChange( static_cast<PRBool>(langRTL) ); }
	/**
		* Returns the whole selection into a plain text string.
		*/
	std::string toString () const;
	
};


#endif /* _WEBBROWSE_SELECTION_H_ */

