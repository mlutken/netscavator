#ifndef _DOM_WINDOW_H_
#define _DOM_WINDOW_H_

#include <boost/shared_ptr.hpp>	

#include <nsCOMPtr.h>
#include <nsIDOMWindow.h>
#include <utils/mozilla_if_macros.h>
#include <utils/mozilla_utils.h>
#include "DOMDocument.h"

class DOMWindowCollection;
class DOMBarProp;
class ScriptContext;
class Selection;
class DOMWindow;
typedef boost::shared_ptr<DOMWindow>		DOMWindowPtr;			///< Pointer to a DOMWindow

  /**
 * The nsIDOMWindow interface is the primary interface for a DOM
 * window object. It represents a single window object that may
 * contain child windows if the document in the window contains a
 * HTML frameset document or if the document contains iframe elements.
 *
 * This interface is not officially defined by any standard bodies, it
 * originates from the defacto DOM Level 0 standard.
 *
 * @status FROZEN
 */
class DOMWindow : public Supports {
	MOZ_CONSTRUCT(DOMWindow,Supports);
public: 
	/// Accessor for the document in this window.
	boost::shared_ptr<DOMDocument>	
	document() 
											{	MOZ_IF_RETURN_MOZ(GetDocument,DOMDocument);	}
 
	/** Access for this window's parent (readonly).
	Accessor for this window's parent window, or the window itself if
	there is no parent, or if the parent is of different type
	(i.e. this does not cross chrome-content boundaries). */
	boost::shared_ptr<DOMWindow>	
	parent() 
											{	MOZ_IF_RETURN_MOZ(GetParent,DOMWindow);	}

	/** Access for this window's root (readonly).
	Accessor for the root of this hierarchy of windows. This root may
	be the window itself if there is no parent, or if the parent is
	of different type (i.e. this does not cross chrome-content
	boundaries). */
	boost::shared_ptr<DOMWindow>	
	top() 
											{	MOZ_IF_RETURN_MOZ(GetTop,DOMWindow);	}

	boost::shared_ptr<DOMBarProp>	
	scrollbars() const;

	boost::shared_ptr<DOMWindowCollection>	
	frames() const;

	/// Set the name of this window. 
	std::string			name() const 
															{MOZ_IF_RETURN_STRING(GetName);}
	/// Get the name of this window. 
	void				name( const std::string& sValue )  	///< Name to assign
															{MOZ_IF_SET_VOID_STRING(SetName,sValue);}

	/** Get text zoom value.
	Set/Get the document scale factor as a multiplier on the default
	size. When setting this attribute, a NS_ERROR_NOT_IMPLEMENTED
	error may be returned by implementations not supporting
	zoom. Implementations not supporting zoom should return 1.0 all
	the time for the Get operation. 1.0 is equals normal size,
	i.e. no zoom. */
	float
	textZoom() const
															{	MOZ_IF_RETURN_FLOAT(GetTextZoom);	}
	/// Set text zoom value.
	void
	textZoom( float fTextZoom )								///< Zoom value
															{	MOZ_IF_SET_VOID_FLOAT(SetTextZoom,fTextZoom);	}

	///	Get current x scroll position in pixels (readonly).
	boost::int32_t
	scrollX() const
															{	MOZ_IF_RETURN_INT32(GetScrollX);	}

	///	Get current y scroll position in pixels (readonly).
	boost::int32_t
	scrollY() const
															{	MOZ_IF_RETURN_INT32(GetScrollY);	}

	/// Method for scrolling this window to an absolute pixel offset.
	void 
	scrollTo ( boost::int32_t xScroll, boost::int32_t yScroll )
															{	MOZ_IF_SET_VOID_INT32_INT32(ScrollTo, xScroll, yScroll);	}

	/// Method for scrolling this window to a pixel offset relative to
	/// the current scroll position.
	void 
	scrollBy ( boost::int32_t xScrollDif, boost::int32_t yScrollDif )
															{	MOZ_IF_SET_VOID_INT32_INT32(ScrollTo, xScrollDif, yScrollDif);	}

	/// Method for accessing this window's selection object.
	boost::shared_ptr<Selection>	
	getSelection() const;

	///  Scroll this window by a number of lines.
	void
	scrollByLines( boost::int32_t iNumLines )					///< Number of lines to scroll
															{	MOZ_IF_SET_VOID_INT32(ScrollByLines,iNumLines);	}
	
	/// Scroll this window by a number of pages.
	void
	scrollByPages( boost::int32_t iNumPages )					///< Number of pages to scroll
															{	MOZ_IF_SET_VOID_INT32(ScrollByPages,iNumPages);	}
	/// Size this window to the content in the window.
	void 
	sizeToContent()
															{	ifMoz()->SizeToContent();	}
	
	// ------------------------------------------------
	// --- Methods beyond W3C/Mozilla specification ---	
	// ------------------------------------------------
	
	/// Get windows (java)script context.
	boost::shared_ptr<ScriptContext>	
	getScriptContext();
};


#endif /* _DOM_WINDOW_H_ */


