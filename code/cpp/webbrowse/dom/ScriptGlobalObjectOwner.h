#ifndef _WEBBROWSE_SCRIPT_GLOBAL_OBJECT_OWNER_H_
#define _WEBBROWSE_SCRIPT_GLOBAL_OBJECT_OWNER_H_

#include <boost/shared_ptr.hpp>	

#include <dom/nsIScriptGlobalObjectOwner.h>

#include <utils/mozilla_if_macros.h>
#include <utils/mozilla_utils.h>

/**
 * Implemented by any object capable of supplying a nsIScriptGlobalObject.
 * The implentor may create the script global object on demand. */
class ScriptGlobalObjectOwner : public MozBase<nsIScriptGlobalObjectOwner> {
	MOZ_CONSTRUCT(ScriptGlobalObjectOwner);
public:

	
	/// Returns the script global object
//	virtual nsIScriptGlobalObject* GetScriptGlobalObject() = 0; //TODO: Should perhaps not be virtual in our "wrapping"
	
	// ------------------------------------------------
	// --- Methods beyond W3C/Mozilla specification ---	
	// ------------------------------------------------

};


#endif /* _WEBBROWSE_SCRIPT_GLOBAL_OBJECT_OWNER_H_ */

