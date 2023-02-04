#ifndef _WEBBROWSE_WEB_BROWSER_FIND_H_
#define _WEBBROWSE_WEB_BROWSER_FIND_H_

#include <nsIWebBrowserFind.h>
#include <boost/shared_ptr.hpp>	

#include <utils/mozilla_if_macros.h>
#include <utils/mozilla_utils.h>

class WebBrowserFind;
typedef boost::shared_ptr<WebBrowserFind>		WebBrowserFindPtr;			///< Pointer to a WebBrowserFind


/**
 * nsIWebBrowserFind
 *
 * Searches for text in a web browser.
 *
 * Get one by doing a GetInterface on an nsIWebBrowser.
 *
 * By default, the implementation will search the focussed frame, or
 * if there is no focussed frame, the web browser content area. It
 * does not by default search subframes or iframes. To change this
 * behaviour, and to explicitly set the frame to search, 
 * QueryInterface to nsIWebBrowserFindInFrames.
 *
 * @status FROZEN
 */
class WebBrowserFind : public Supports {
	MOZ_CONSTRUCT(WebBrowserFind,Supports);
public: 

	/**
		* findNext
		*
		* Finds, highlights, and scrolls into view the next occurrence of the
		* search string, using the current search settings. Fails if the
		* search string is empty.
		*
		* @return  Whether an occurrence was found
		*/
	bool 				
	findNext() const 
											{	MOZ_IF_RETURN_BOOL(FindNext); }
	
	
	/**
		* searchString
		*
		* The string to search for. This must be non-empty to search.
		*/
	/* attribute wstring searchString; */
// 	NS_SCRIPTABLE NS_IMETHOD GetSearchString(PRUnichar * *aSearchString) = 0;
// 	NS_SCRIPTABLE NS_IMETHOD SetSearchString(const PRUnichar * aSearchString) = 0;
	
  	///  Get search string 
	std::string 				
	searchString() const ;
	
	void 				
	searchString( const std::string& sSearchString ); 
	
	/**
		* findBackwards
		*
		* Whether to find backwards (towards the beginning of the document).
		* Default is false (search forward).
		*/
	/* attribute boolean findBackwards; */
// 	NS_SCRIPTABLE NS_IMETHOD GetFindBackwards(PRBool *aFindBackwards) = 0;
// 	NS_SCRIPTABLE NS_IMETHOD SetFindBackwards(PRBool aFindBackwards) = 0;
	
	/// Get findBackwards.
	/// Whether to find backwards (towards the beginning of the document).
	/// Default is false (search forward).
	bool 				
	findBackwards() const 
											{	MOZ_IF_RETURN_BOOL(GetFindBackwards); }
	
	/// Set findBackwards.
	/// Whether to find backwards (towards the beginning of the document).
	/// Default is false (search forward).
	void 				
	findBackwards( bool bFindBackwards )  
											{	MOZ_IF_SET_VOID_BOOL(SetFindBackwards, bFindBackwards); }
	
	/**
		* wrapFind
		*
		* Whether the search wraps around to the start (or end) of the document
		* if no match was found between the current position and the end (or
		* beginning). Works correctly when searching backwards. Default is
		* false.
		*/
	/* attribute boolean wrapFind; */
// 	NS_SCRIPTABLE NS_IMETHOD GetWrapFind(PRBool *aWrapFind) = 0;
// 	NS_SCRIPTABLE NS_IMETHOD SetWrapFind(PRBool aWrapFind) = 0;
	/**
		Get wrapFind.
		Whether the search wraps around to the start (or end) of the document
		if no match was found between the current position and the end (or
		beginning). Works correctly when searching backwards. Default is
		false. */
	bool 				
	wrapFind() const 
											{	MOZ_IF_RETURN_BOOL(GetWrapFind); }
	
	/**
		Set wrapFind.
		Whether the search wraps around to the start (or end) of the document
		if no match was found between the current position and the end (or
		beginning). Works correctly when searching backwards. Default is
		false. */
	void 				
	wrapFind( bool bWrapFind )  
											{	MOZ_IF_SET_VOID_BOOL(SetWrapFind, bWrapFind); }

	
	/**	
		Get entireWord.
		Whether to match entire words only. Default is false. */
	bool 				
	entireWord() const 
											{	MOZ_IF_RETURN_BOOL(GetEntireWord); }
	/**	
		Set entireWord.
		Whether to match entire words only. Default is false. */
	void 				
	entireWord( bool bEntireWord )  
											{	MOZ_IF_SET_VOID_BOOL(SetEntireWord, bEntireWord); }
	
	
	/** 
		Get matchCase.
		Whether to match case (case sensitive) when searching. Default is false. */
	bool 				
	matchCase() const 
											{	MOZ_IF_RETURN_BOOL(GetMatchCase); }
	/** 
		Set matchCase.
		Whether to match case (case sensitive) when searching. Default is false. */
	void 				
	matchCase( bool bMatchCase )  
											{	MOZ_IF_SET_VOID_BOOL(SetMatchCase, bMatchCase); }
	
	/**
		Get searchFrames.
		Whether to search through all frames in the content area. Default is true.
		Note that you can control whether the search propagates into child or
		parent frames explicitly using nsIWebBrowserFindInFrames, but if one,
		but not both, of searchSubframes and searchParentFrames are set, this
		returns false. */
	bool 				
	searchFrames() const 
											{	MOZ_IF_RETURN_BOOL(GetSearchFrames); }
	/**
		Set searchFrames.
		Whether to search through all frames in the content area. Default is true.
		Note that you can control whether the search propagates into child or
		parent frames explicitly using nsIWebBrowserFindInFrames, but if one,
		but not both, of searchSubframes and searchParentFrames are set, this
		returns false. */
	void 				
	searchFrames( bool bSearchFrames )  
											{	MOZ_IF_SET_VOID_BOOL(SetSearchFrames, bSearchFrames ); }

};

#if 0
/**
 * nsIWebBrowserFindInFrames
 *
 * Controls how find behaves when multiple frames or iframes are present.
 *
 * Get by doing a QueryInterface from nsIWebBrowserFind.
 *
 * @status FROZEN
 */
class NS_NO_VTABLE NS_SCRIPTABLE nsIWebBrowserFindInFrames : public nsISupports {
 public: 

  NS_DECLARE_STATIC_IID_ACCESSOR(NS_IWEBBROWSERFINDINFRAMES_IID)

  /**
     * currentSearchFrame
     *
     * Frame at which to start the search. Once the search is done, this will
     * be set to be the last frame searched, whether or not a result was found.
     * Has to be equal to or contained within the rootSearchFrame.
     */
  /* attribute nsIDOMWindow currentSearchFrame; */
  NS_SCRIPTABLE NS_IMETHOD GetCurrentSearchFrame(nsIDOMWindow * *aCurrentSearchFrame) = 0;
  NS_SCRIPTABLE NS_IMETHOD SetCurrentSearchFrame(nsIDOMWindow * aCurrentSearchFrame) = 0;

  /**
     * rootSearchFrame
     *
     * Frame within which to confine the search (normally the content area frame).
     * Set this to only search a subtree of the frame hierarchy.
     */
  /* attribute nsIDOMWindow rootSearchFrame; */
  NS_SCRIPTABLE NS_IMETHOD GetRootSearchFrame(nsIDOMWindow * *aRootSearchFrame) = 0;
  NS_SCRIPTABLE NS_IMETHOD SetRootSearchFrame(nsIDOMWindow * aRootSearchFrame) = 0;

  /**
     * searchSubframes
     *
     * Whether to recurse down into subframes while searching. Default is true.
     *
     * Setting nsIWebBrowserfind.searchFrames to true sets this to true.
     */
  /* attribute boolean searchSubframes; */
  NS_SCRIPTABLE NS_IMETHOD GetSearchSubframes(PRBool *aSearchSubframes) = 0;
  NS_SCRIPTABLE NS_IMETHOD SetSearchSubframes(PRBool aSearchSubframes) = 0;

  /**
     * searchParentFrames
     *
     * Whether to allow the search to propagate out of the currentSearchFrame into its
     * parent frame(s). Search is always confined within the rootSearchFrame. Default
     * is true.
     *
     * Setting nsIWebBrowserfind.searchFrames to true sets this to true.
     */
  /* attribute boolean searchParentFrames; */
  NS_SCRIPTABLE NS_IMETHOD GetSearchParentFrames(PRBool *aSearchParentFrames) = 0;
  NS_SCRIPTABLE NS_IMETHOD SetSearchParentFrames(PRBool aSearchParentFrames) = 0;

};

#endif


#endif /* _WEBBROWSE_WEB_BROWSER_FIND_H_ */

