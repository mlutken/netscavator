#ifndef _WEBBROWSE_URL_H_
#define _WEBBROWSE_URL_H_

#include <nsIURL.h>
#include "URI.h"

/**
The nsIURL interface provides convenience methods that further
break down the path portion of URI:
\code
http://host/directory/fileBaseName.fileExtension?query
http://host/directory/fileBaseName.fileExtension#ref
http://host/directory/fileBaseName.fileExtension;param
           \          \                       /
            \          -----------------------
             \                   |          /
              \               fileName     /
               ----------------------------
                           |
                       filePath
\endcode
@status FROZEN */
class URL : public URI {
	MOZ_CONSTRUCT(URL,URI);
public: 


  	/*************************************************************************
     * The URL path is broken down into the following principal components:
     */
	/**
	Returns a path including the directory and file portions of a
	URL.  For example, the filePath of "http://host/foo/bar.html#baz"
	is "/foo/bar.html".
	Some characters may be escaped. */
	std::string 				
	filePath () const 
											{	MOZ_IF_RETURN_CSTRING(GetFilePath); 			}
  	///  Set filePath.
	void 				
	filePath ( const std::string& sFilePath )		///< String value 
											{	MOZ_IF_SET_VOID_CSTRING(SetFilePath,sFilePath);	}



	/// Returns the parameters specified after the ; in the URL. 
	/// Some characters may be escaped. 
	std::string 				
	param () const 
											{	MOZ_IF_RETURN_CSTRING(GetParam); 			}
  	///  Set param.
	void 				
	param ( const std::string& sParam )		///< String value 
											{	MOZ_IF_SET_VOID_CSTRING(SetParam,sParam);	}
	
	/**
	Returns the query portion (the part after the "?") of the URL.
	If there isn't one, an empty string is returned.
	Some characters may be escaped. */
	std::string 				
	query () const 
											{	MOZ_IF_RETURN_CSTRING(GetQuery); 			}
  	///  Set query.
	void 				
	query ( const std::string& sQuery )		///< String value 
											{	MOZ_IF_SET_VOID_CSTRING(SetQuery,sQuery);	}
	
	/**
	Returns the reference portion (the part after the "#") of the URL.
	If there isn't one, an empty string is returned.
	Some characters may be escaped. */
	std::string 				
	ref () const 
											{	MOZ_IF_RETURN_CSTRING(GetRef); 			}
  	///  Set ref.
	void 				
	ref ( const std::string& sRef )		///< String value 
											{	MOZ_IF_SET_VOID_CSTRING(SetRef,sRef);	}
	
	/*************************************************************************
		* The URL filepath is broken down into the following sub-components:
		*/
	/**
	Returns the directory portion of a URL.  If the URL denotes a path to a
	directory and not a file, e.g. http://host/foo/bar/, then the Directory
	attribute accesses the complete /foo/bar/ portion, and the FileName is
	the empty string. If the trailing slash is omitted, then the Directory
	is /foo/ and the file is bar (i.e. this is a syntactic, not a semantic
	breakdown of the Path).  And hence don't rely on this for something to
	be a definitely be a file. But you can get just the leading directory
	portion for sure.
	Some characters may be escaped. */
	std::string 				
	directory () const 
											{	MOZ_IF_RETURN_CSTRING(GetDirectory); 			}
  	///  Set directory.
	void 				
	directory ( const std::string& sDirectory )		///< String value 
											{	MOZ_IF_SET_VOID_CSTRING(SetDirectory,sDirectory);	}
	
	/**
	Returns the file name portion of a URL.  If the URL denotes a path to a
	directory and not a file, e.g. http://host/foo/bar/, then the Directory
	attribute accesses the complete /foo/bar/ portion, and the FileName is
	the empty string. Note that this is purely based on searching for the
	last trailing slash. And hence don't rely on this to be a definite file. 
	Some characters may be escaped. */
	std::string 				
	fileName () const 
											{	MOZ_IF_RETURN_CSTRING(GetFileName); 			}
  	///  Set fileName.
	void 				
	fileName ( const std::string& sFileName )		///< String value 
											{	MOZ_IF_SET_VOID_CSTRING(SetFileName,sFileName);	}
	
	/*************************************************************************
		* The URL filename is broken down even further:
		*/
	/// Returns the file basename portion of a filename in a url.
	/// Some characters may be escaped.
	std::string 				
	fileBaseName () const 
											{	MOZ_IF_RETURN_CSTRING(GetFileBaseName); 			}
  	///  Set fileBaseName.
	void 				
	fileBaseName ( const std::string& sFileBaseName )		///< String value 
											{	MOZ_IF_SET_VOID_CSTRING(SetFileBaseName,sFileBaseName);	}
	
	/**
	Returns the file extension portion of a filename in a url.  If a file
	extension does not exist, the empty string is returned.
	Some characters may be escaped. */
	std::string 				
	fileExtension () const 
											{	MOZ_IF_RETURN_CSTRING(GetFileExtension); 			}
  	///  Set fileExtension.
	void 				
	fileExtension ( const std::string& sFileExtension )		///< String value 
											{	MOZ_IF_SET_VOID_CSTRING(SetFileExtension,sFileExtension);	}
	
	/**
	This method takes a uri and compares the two.  The common uri portion
	is returned as a string.  The minimum common uri portion is the 
	protocol, and any of these if present:  login, password, host and port
	If no commonality is found, "" is returned.  If they are identical, the
	whole path with file/ref/etc. is returned.  For file uris, it is
	expected that the common spec would be at least "file:///" since '/' is
	a shared common root.
	
	!Examples:
	   this.spec               aURIToCompare.spec        result
	1) http://mozilla.org/     http://www.mozilla.org/   ""
	2) http://foo.com/bar/     ftp://foo.com/bar/        ""
	3) http://foo.com:8080/    http://foo.com/bar/       ""
	4) ftp://user@foo.com/     ftp://user:pw@foo.com/    ""
	5) ftp://foo.com/bar/      ftp://foo.com/bar         ftp://foo.com/
	6) ftp://foo.com/bar/      ftp://foo.com/bar/b.html  ftp://foo.com/bar/
	7) http://foo.com/a.htm#i  http://foo.com/b.htm      http://foo.com/
	8) ftp://foo.com/c.htm#i   ftp://foo.com/c.htm       ftp://foo.com/c.htm
	9) file:///a/b/c.html      file:///d/e/c.html        file:///  */
	std::string 
	getCommonBaseSpec ( URI* pURIToCompare )
	{
		nsCString sResult;															\
		ifMoz()->GetCommonBaseSpec( pURIToCompare->ifMoz(), sResult );
		return sResult.get();
	}
	
	/**
	This method takes a uri and returns a substring of this if it can be
	made relative to the uri passed in.  If no commonality is found, the
	entire uri spec is returned.  If they are identical, "" is returned.
	Filename, query, etc are always returned except when uris are identical. */
	std::string 
	getRelativeSpec ( URI* pURIToCompare )
	{
		nsCString sResult;															\
		ifMoz()->GetRelativeSpec( pURIToCompare->ifMoz(), sResult );
		return sResult.get();
	}
	
	
	// ------------------------------------------------
	// --- Methods beyond W3C/Mozilla specification ---	
	// ------------------------------------------------

};


#endif /* _WEBBROWSE_URL_H_ */
