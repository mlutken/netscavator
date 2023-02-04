#ifndef _WEBBROWSE_URI_H_
#define _WEBBROWSE_URI_H_


#include <nsIURI.h>

#include <utils/mozilla_if_macros.h>
#include <utils/mozilla_utils.h>


/**
URI - interface for an uniform resource identifier w/ i18n support.
 
AUTF8String attributes may contain unescaped UTF-8 characters.
Consumers should be careful to escape the UTF-8 strings as necessary, but
should always try to "display" the UTF-8 version as provided by this
interface.
 
AUTF8String attributes may also contain escaped characters.
  
Unescaping URI segments is unadvised unless there is intimate
knowledge of the underlying charset or there is no plan to display (or
otherwise enforce a charset on) the resulting URI substring.
 
! About URIs
URIs are essentially structured names for things -- anything. This interface
provides accessors to set and query the most basic components of an URI.
Subclasses, including nsIURL, impose greater structure on the URI.

This interface follows Tim Berners-Lee's URI spec (RFC2396) [1], where the
basic URI components are defined as such:
\code 
     ftp://username:password@hostname:portnumber/pathname
     \ /   \               / \      / \        /\       /
      -     ---------------   ------   --------  -------
      |            |             |        |         |
      |            |             |        |        Path
      |            |             |       Port         
      |            |            Host      /
      |         UserPass                 /
    Scheme                              /
      \                                /
       --------------------------------
                      |
                   PrePath
\endcode

The definition of the URI components has been extended to allow for
internationalized domain names [2] and the more generic IRI structure [3].

[1] http://www.ietf.org/rfc/rfc2396.txt
[2] http://www.ietf.org/internet-drafts/draft-ietf-idn-idna-06.txt
[3] http://www.ietf.org/internet-drafts/draft-masinter-url-i18n-08.txt
@status FROZEN */
class URI : public Supports {
	MOZ_CONSTRUCT(URI,Supports);
public: 
	
	/************************************************************************
		* The URI is broken down into the following principal components:
		*/
	/**
	Returns a string representation of the URI. Setting the spec causes
	the new spec to be parsed, initializing the URI.
	Some characters may be escaped. */
	std::string 				
	spec () const 
											{	MOZ_IF_RETURN_CSTRING(GetSpec); 			}
  	///  Set URI string representation (spec).
	void 				
	spec ( const std::string& sSpec )		///< String value 
											{	MOZ_IF_SET_VOID_CSTRING(SetSpec,sSpec);		}
	
	/**
	The prePath (eg. scheme://user:password@host:port) returns the string
	before the path.  This is useful for authentication or managing sessions.
	Some characters may be escaped. */
	std::string 				
	prePath () const 
											{	MOZ_IF_RETURN_CSTRING(GetPrePath); 			}
	
	/// The Scheme is the protocol to which this URI refers.  The scheme is
	/// restricted to the US-ASCII charset per RFC2396. 
	std::string 				
	scheme () const 
											{	MOZ_IF_RETURN_CSTRING(GetScheme); 			}
  	///  Set scheme.
	void 				
	scheme ( const std::string& sScheme )		///< String value 
											{	MOZ_IF_SET_VOID_CSTRING(SetScheme,sScheme);	}
	
	/// The username:password (or username only if value doesn't contain a ':')
	/// Some characters may be escaped. 
	std::string 				
	userPass () const 
											{	MOZ_IF_RETURN_CSTRING(GetUserPass); 			}
  	///  Set username:password (or username only if value doesn't contain a ':').
	void 				
	userPass ( const std::string& sUserPass )		///< String value 
											{	MOZ_IF_SET_VOID_CSTRING(SetUserPass,sUserPass);	}
	
	/// The optional username , assuming the preHost consists of username:password.
	/// Some characters may be escaped. 
	std::string 				
	username () const 
											{	MOZ_IF_RETURN_CSTRING(GetUsername); 			}
  	///  Set username.
	void 				
	username ( const std::string& sUserName )		///< String value 
											{	MOZ_IF_SET_VOID_CSTRING(SetUsername,sUserName);	}
	
	/// The optional password, assuming the preHost consists of username:password.
	/// Some characters may be escaped. 
	std::string 				
	password () const 
											{	MOZ_IF_RETURN_CSTRING(GetPassword); 			}
  	///  Set password.
	void 				
	password ( const std::string& sPassword )		///< String value 
											{	MOZ_IF_SET_VOID_CSTRING(SetPassword,sPassword);	}
	
	/// The host:port (or simply the host, if port == -1).
	/// Characters are NOT escaped. 
	std::string 				
	hostPort () const 
											{	MOZ_IF_RETURN_CSTRING(GetHostPort); 			}
  	///  Set hostPort.
	void 				
	hostPort ( const std::string& sHostPort )		///< String value 
											{	MOZ_IF_SET_VOID_CSTRING(SetHostPort,sHostPort);	}
	
	/**
	The host is the internet domain name to which this URI refers.  It could
	be an IPv4 (or IPv6) address literal.  If supported, it could be a
	non-ASCII internationalized domain name.
	Characters are NOT escaped. */
	std::string 				
	host () const 
											{	MOZ_IF_RETURN_CSTRING(GetHost); 			}
  	///  Set host.
	void 				
	host ( const std::string& sHost )		///< String value 
											{	MOZ_IF_SET_VOID_CSTRING(SetHost,sHost);		}
	
	/// Get port. A port value of -1 corresponds to the protocol's default port (eg. -1
	/// implies port 80 for http URIs).
	boost::int32_t 
	port () const
											{	MOZ_IF_RETURN_INT32(GetPort); 				}
	
	/// Set port. A port value of -1 corresponds to the protocol's default port (eg. -1
	/// implies port 80 for http URIs).
//	void 				
//	port( const boost::int32_t iPort )		///< Port number 
//											{	MOZ_IF_SET_VOID_INT32(SetPort,iPort);	}
	
	/**
	The path, typically including at least a leading '/' (but may also be
	empty, depending on the protocol).
	Some characters may be escaped */
	std::string 				
	path () const 
											{	MOZ_IF_RETURN_CSTRING(GetPath); 			}
  	///  Set path.
	void 				
	path ( const std::string& sPath )		///< String value 
											{	MOZ_IF_SET_VOID_CSTRING(SetPath,sPath);		}
	
	/************************************************************************
		* An URI supports the following methods:
		*/
	/**
	URI equivalence test (not a strict string comparison).
	eg. http://foo.com:80/ == http://foo.com/ */
	bool 
//	equals ( boost::shared_ptr<URI> pLhsURI )
	equals ( URI* pLhsURI )
	{
		PRBool bRetVal;
		ifMoz()->Equals( pLhsURI->ifMoz(), &bRetVal );
		return static_cast<bool>(bRetVal != 0);
	}
	
	/**
	* An optimization to do scheme checks without requiring the users of nsIURI
	* to GetScheme, thereby saving extra allocating and freeing. Returns true if
	* the schemes match (case ignored). */
	bool 
	schemeIs ( std::string const& sScheme ) const
	{
		PRBool bRetVal;
		ifMoz()->SchemeIs( sScheme.c_str(), &bRetVal );
		return static_cast<bool>(bRetVal != 0);
	}
	
	/**
	* Clones the current URI.  For some protocols, this is more than just an
	* optimization.  For example, under MacOS, the spec of a file URL does not
	* necessarily uniquely identify a file since two volumes could share the
	* same name. */
	boost::shared_ptr<URI>
	clone () const 
											{	MOZ_IF_RETURN_MOZ(Clone,URI);	}
	/**
	This method resolves a relative string into an absolute URI string,
	using this URI as the base. 
	\note Some implementations may have no concept of a relative URI. */
	std::string 
	resolve ( std::string const& sRelativePath 	///< [in] Relative path to resolve to absolute path.
											) const
											{	MOZ_IF_RETURN_CSTRING_CSTRING(Resolve,sRelativePath);	}
											
	/************************************************************************
		* Additional attributes:
		*/
	/**
	The URI spec with an ASCII compatible encoding.  Host portion follows
	the IDNA draft spec.  Other parts are URL-escaped per the rules of
	RFC2396.  The result is strictly ASCII. */
	std::string 				
	asciiSpec () const 
											{	MOZ_IF_RETURN_CSTRING(GetAsciiSpec); 			}
	
	/**
	The URI host with an ASCII compatible encoding.  Follows the IDNA
	draft spec for converting internationalized domain names (UTF-8) to
	ASCII for compatibility with existing internet infrasture. */
	std::string 				
	asciiHost () const 
											{	MOZ_IF_RETURN_CSTRING(GetAsciiHost); 			}
	
	/**
	The charset of the document from which this URI originated.  An empty
	value implies UTF-8.
	
	If this value is something other than UTF-8 then the URI components
	(e.g., spec, prePath, username, etc.) will all be fully URL-escaped.
	Otherwise, the URI components may contain unescaped multibyte UTF-8
	characters. */
	std::string 				
	originCharset () const 
											{	MOZ_IF_RETURN_CSTRING(GetOriginCharset); 	}

	// ------------------------------------------------
	// --- Methods beyond W3C/Mozilla specification ---	
	// ------------------------------------------------

};

#endif /* _WEBBROWSE_URI_H_ */

