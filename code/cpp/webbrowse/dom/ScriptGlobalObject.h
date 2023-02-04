#ifndef _WEBBROWSE_SCRIPT_GLOBAL_OBJECT_H_
#define _WEBBROWSE_SCRIPT_GLOBAL_OBJECT_H_

#include <boost/shared_ptr.hpp>	

#include <dom/nsIScriptGlobalObject.h>

#include <utils/mozilla_if_macros.h>
#include <utils/mozilla_utils.h>

 
/**
+  * The global object which keeps a script context for each supported script
+  * language. This often used to store per-window global state.
 */

class ScriptGlobalObject : public MozBase<nsIScriptGlobalObject> {
	MOZ_CONSTRUCT(ScriptGlobalObject);
public:

	/**
	* Ensure that the script global object is initialized for working with the
	* specified script language ID.  This will set up the nsIScriptContext
	* and 'script global' for that language, allowing these to be fetched
	* and manipulated.
	* @return NS_OK if successful; error conditions include that the language
	* has not been registered, as well as 'normal' errors, such as
	* out-of-memory
	*/
//	virtual nsresult EnsureScriptEnvironment(PRUint32 aLangID) = 0;
	
	/**
	* Get a script context (WITHOUT added reference) for the specified language.
	*/
//	virtual nsIScriptContext *GetScriptContext(PRUint32 lang) = 0;
	
	/**
	* Get the opaque "global" object for the specified lang.
	*/
//	virtual void *GetScriptGlobal(PRUint32 lang) = 0;
	
	// Set/GetContext deprecated methods - use GetScriptContext/Global
// 	virtual JSObject *GetGlobalJSObject() {
// 		return (JSObject *)GetScriptGlobal(nsIProgrammingLanguage::JAVASCRIPT);
// 	}
	
//	virtual nsIScriptContext *GetContext() 
// 	{
// 		return GetScriptContext(nsIProgrammingLanguage::JAVASCRIPT);
// 	}
	
	/**
	* Set a new language context for this global.  The native global for the
	* context is created by the context's GetNativeGlobal() method.
	*/
	
//	virtual nsresult SetScriptContext(PRUint32 lang, nsIScriptContext *aContext) = 0;
	
	/**
	* Called when the global script for a language is finalized, typically as
	* part of its GC process.  By the time this call is made, the
	* nsIScriptContext for the language has probably already been removed.
	* After this call, the passed object is dead - which should generally be the
	* same object the global is using for a global for that language.
	*/
	
//	virtual void OnFinalize(PRUint32 aLangID, void *aScriptGlobal) = 0;
	
	/**
	* Called to enable/disable scripts.
	*/
//	virtual void SetScriptsEnabled(PRBool aEnabled, PRBool aFireTimeouts) = 0;
	
	/** Set a new arguments object for this window. This will be set on
	* the window right away (if there's an existing document) and it
	* will also be installed on the window when the next document is
	* loaded.  Each language impl is responsible for converting to
	* an array of args as appropriate for that language.
	*/
//	virtual nsresult SetNewArguments(nsIArray *aArguments) = 0;
	
	/** Handle a script error.  Generally called by a script context.
	*/
// 	virtual nsresult HandleScriptError(nsScriptErrorEvent *aErrorEvent, nsEventStatus *aEventStatus) 
// 	{
// 		return NS_HandleScriptError(this, aErrorEvent, aEventStatus);
// 	}


	// ------------------------------------------------
	// --- Methods beyond W3C/Mozilla specification ---	
	// ------------------------------------------------


};


#endif /*_WEBBROWSE_SCRIPT_GLOBAL_OBJECT_H_ */


