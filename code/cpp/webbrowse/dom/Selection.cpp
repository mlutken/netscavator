#include "Selection.h"

#include "DOMNode.h"
#include "DOMRange.h"

boost::shared_ptr<DOMNode>
Selection::anchorNode() const
{
	MOZ_IF_RETURN_MOZ(GetAnchorNode,DOMNode);	
}

boost::shared_ptr<DOMNode>
Selection::focusNode() const
{
	MOZ_IF_RETURN_MOZ(GetFocusNode,DOMNode);	
}



/**
	* Returns the range at the specified index.
	*/
/* nsIDOMRange getRangeAt (in long index); */
// 	NS_SCRIPTABLE NS_IMETHOD GetRangeAt(PRInt32 index, nsIDOMRange **_retval NS_OUTPARAM) = 0;
boost::shared_ptr<DOMRange>
Selection::getRangeAt( boost::int32_t index ) const
{
	MOZ_IF_RETURN_MOZ_INT32(GetRangeAt,DOMRange,index);
}



void 
Selection::collapse( boost::shared_ptr<DOMNode> parentNode, boost::int32_t offset )
{ 	
	ifMoz()->Collapse( parentNode->ifMoz(), static_cast<PRInt32>(offset) );	
}

void 
Selection::extend( boost::shared_ptr<DOMNode> parentNode, boost::int32_t offset )
{ 	
	ifMoz()->Extend( parentNode->ifMoz(), static_cast<PRInt32>(offset) );	
}

bool	
Selection::containsNode ( boost::shared_ptr<DOMNode> node, bool partlyContained )
{
	MOZ_IF_RETURN_BOOL_MOZ_BOOL(ContainsNode,node,partlyContained);
}

void Selection::selectAllChildren ( boost::shared_ptr<DOMNode> parentNode )
{
	MOZ_IF_SET_VOID_MOZ(SelectAllChildren,parentNode);
	////ifMoz()->SelectAllChildren( parentNode->ifMoz() );
}

void Selection::addRange ( boost::shared_ptr<DOMRange> range )
{
	MOZ_IF_SET_VOID_MOZ(AddRange,range);
}

void Selection::removeRange ( boost::shared_ptr<DOMRange> range )
{
	MOZ_IF_SET_VOID_MOZ(RemoveRange,range);
}

std::string Selection::toString () const
{
 	PRUnichar* szSelection;
 	ifMoz()->ToString( &szSelection);
 	nsEmbedString sSelection(szSelection);
 	std::string sSel = toStdStringUTF8( sSelection );
	return sSel;
}


