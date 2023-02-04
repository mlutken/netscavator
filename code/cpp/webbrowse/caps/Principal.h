#ifndef _WEBBROWSE_PRINCIPAL_H_
#define _WEBBROWSE_PRINCIPAL_H_

#include <boost/shared_ptr.hpp>	

#include <caps/nsIPrincipal.h>

#include <utils/mozilla_if_macros.h>


//class Principal : /*public nsISerializable */ {
class Principal : public MozBase<nsIPrincipal> {
	MOZ_CONSTRUCT(Principal);
public: 


	/**
	* Values of capabilities for each principal. Order is
	* significant: if an operation is performed on a set
	* of capabilities, the minimum is computed.
	*/
	enum { ENABLE_DENIED 				= nsIPrincipal::ENABLE_DENIED 				};
	enum { ENABLE_UNKNOWN 				= nsIPrincipal::ENABLE_UNKNOWN 				};
	enum { ENABLE_WITH_USER_PERMISSION	= nsIPrincipal::ENABLE_WITH_USER_PERMISSION	};
	enum { ENABLE_GRANTED 				= nsIPrincipal::ENABLE_GRANTED 				};
	
	/**
		* Returns the security preferences associated with this principal.
		* prefBranch will be set to the pref branch to which these preferences
		* pertain.  id is a pseudo-unique identifier, pertaining to either the
		* fingerprint or the origin.  subjectName is a name that identifies the
		* entity this principal represents (may be empty).  grantedList and
		* deniedList are space-separated lists of capabilities which were
		* explicitly granted or denied by a pref.  isTrusted is a boolean that
		* indicates whether this is a codebaseTrusted certificate.
		*/
	/* [noscript] void getPreferences (out string prefBranch, out string id, out string subjectName, out string grantedList, out string deniedList, out boolean isTrusted); */
//	GetPreferences(char **prefBranch, char **id, char **subjectName, char **grantedList, char **deniedList, PRBool *isTrusted) = 0;
	
	/**
		* Returns whether the other principal is equivalent to this principal.
		* Principals are considered equal if they are the same principal,
		* they have the same origin, or have the same certificate fingerprint ID
		*/
	/* boolean equals (in nsIPrincipal other); */
//	Equals(nsIPrincipal *other, PRBool *_retval) = 0;
	
	/**
		* Returns a hash value for the principal.
		*/
	/* [noscript] readonly attribute unsigned long hashValue; */
//	GetHashValue(PRUint32 *aHashValue) = 0;
	
	/**
		* Returns the JS equivalent of the principal.
		* @see JSPrincipals.h
		*/
	/* [noscript] JSPrincipals getJSPrincipals (in JSContext cx); */
//	GetJSPrincipals(JSContext * cx, JSPrincipals * *_retval) = 0;
	
	/**
		* The domain security policy of the principal.
		*/
	/* [noscript] attribute voidPtr securityPolicy; */
// 	GetSecurityPolicy(void * *aSecurityPolicy) = 0;
// 	SetSecurityPolicy(void * aSecurityPolicy) = 0;
	
	/* [noscript] short canEnableCapability (in string capability); */
//	CanEnableCapability(const char *capability, PRInt16 *_retval) = 0;
	
	/* [noscript] void setCanEnableCapability (in string capability, in short canEnable); */
//	SetCanEnableCapability(const char *capability, PRInt16 canEnable) = 0;
	
	/* [noscript] boolean isCapabilityEnabled (in string capability, in voidPtr annotation); */
//	IsCapabilityEnabled(const char *capability, void * annotation, PRBool *_retval) = 0;
	
	/* [noscript] void enableCapability (in string capability, inout voidPtr annotation); */
//	EnableCapability(const char *capability, void * *annotation) = 0;
	
	/* [noscript] void revertCapability (in string capability, inout voidPtr annotation); */
//	RevertCapability(const char *capability, void * *annotation) = 0;
	
	/* [noscript] void disableCapability (in string capability, inout voidPtr annotation); */
//	DisableCapability(const char *capability, void * *annotation) = 0;
	
	/**
	* The codebase URI to which this principal pertains.  This is
	* generally the document URI.
	*/
	/* [noscript] readonly attribute nsIURI URI; */
//	GetURI(nsIURI * *aURI) = 0;
	
	/**
	* The domain URI to which this principal pertains.
	* This is congruent with HTMLDocument.domain, and may be null.
	* Setting this has no effect on the URI.
	*/
	/* [noscript] attribute nsIURI domain; */
//	GetDomain(nsIURI * *aDomain) = 0;
//	SetDomain(nsIURI * aDomain) = 0;
	
	/**
	* The origin of this principal's codebase URI.
	* An origin is defined as: scheme + host + port.
	*/
	/* [noscript] readonly attribute string origin; */
//	GetOrigin(char * *aOrigin) = 0;
	
	/**
	* Whether this principal is associated with a certificate.
	*/
	/* readonly attribute boolean hasCertificate; */
//	NS_SCRIPTABLE GetHasCertificate(PRBool *aHasCertificate) = 0;
	
	/**
	* The fingerprint ID of this principal's certificate.
	* Throws if there is no certificate associated with this principal.
	*/
	/* readonly attribute AUTF8String fingerprint; */
//	NS_SCRIPTABLE GetFingerprint(nsACString & aFingerprint) = 0;
	
	/**
	* The pretty name for the certificate.  This sort of (but not really)
	* identifies the subject of the certificate (the entity that stands behind
	* the certificate).  Note that this may be empty; prefer to get the
	* certificate itself and get this information from it, since that may
	* provide more information.
	*
	* Throws if there is no certificate associated with this principal.
	*/
	/* readonly attribute AUTF8String prettyName; */
//	NS_SCRIPTABLE GetPrettyName(nsACString & aPrettyName) = 0;
	
	/**
	* Returns whether the other principal is equal to or weaker than this
	* principal.  Principals are equal if they are the same object, they
	* have the same origin, or they have the same certificate ID.
	*
	* Thus a principal always subsumes itself.
	*
	* The system principal subsumes itself and all other principals.
	*
	* A null principal (corresponding to an unknown, hence assumed minimally
	* privileged, security context) is not equal to any other principal
	* (including other null principals), and therefore does not subsume
	* anything but itself.
	*
	* Both codebase and certificate principals are subsumed by the system
	* principal, but no codebase or certificate principal yet subsumes any
	* other codebase or certificate principal.  This may change in a future
	* release; note that nsIPrincipal is unfrozen, not slated to be frozen.
	*
	* XXXbz except see bug 147145!
	*
	* Note for the future: Perhaps we should consider a certificate principal
	* for a given URI subsuming a codebase principal for the same URI?  Not
	* sure what the immediate benefit would be, but I think the setup could
	* make some code (e.g. MaybeDowngradeToCodebase) clearer.
	*/
	/* [noscript] boolean subsumes (in nsIPrincipal other); */
//	Subsumes(nsIPrincipal *other, PRBool *_retval) = 0;
	
	/**
	* Checks whether this principal is allowed to load the network resource
	* located at the given URI under the same-origin policy. This means that
	* codebase principals are only allowed to load resources from the same
	* domain, the system principal is allowed to load anything, and null
	* principals are not allowed to load anything.
	*
	* If the load is allowed this function does nothing. If the load is not
	* allowed the function throws NS_ERROR_DOM_BAD_URI.
	*
	* NOTE: Other policies might override this, such as the Access-Control
	*       specification.
	* NOTE: The 'domain' attribute has no effect on the behaviour of this
	*       function.
	*
	*
	* @param uri    The URI about to be loaded.
	* @param report If true, will report a warning to the console service
	*               if the load is not allowed.
	* @throws NS_ERROR_DOM_BAD_URI if the load is not allowed.
	*/
	/* [noscript] void checkMayLoad (in nsIURI uri, in boolean report); */
//	CheckMayLoad(nsIURI *uri, PRBool report) = 0;
	
	/**
	* The subject name for the certificate.  This actually identifies the
	* subject of the certificate.  This may well not be a string that would
	* mean much to a typical user on its own (e.g. it may have a number of
	* different names all concatenated together with some information on what
	* they mean in between). 
	*
	* Throws if there is no certificate associated with this principal.
	*/
	/* readonly attribute AUTF8String subjectName; */
//	GetSubjectName(nsACString & aSubjectName) = 0;
	
	/**
	* The certificate associated with this principal, if any.  If there isn't
	* one, this will return null.  Getting this attribute never throws.
	*/
	/* readonly attribute nsISupports certificate; */
//	GetCertificate(nsISupports * *aCertificate) = 0;

	// ------------------------------------------------
	// --- Methods beyond W3C/Mozilla specification ---	
	// ------------------------------------------------

};


#endif /* _WEBBROWSE_PRINCIPAL_H_ */
