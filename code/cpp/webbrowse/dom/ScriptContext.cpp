#include "ScriptContext.h" 
 
////#include <js/jspubtd.h>
#include <jspubtd.h>

#include <utils/string_conversion.h>
 
// ------------------------------------------------
// --- Methods beyond W3C/Mozilla specification ---	
// ------------------------------------------------

/** 
Compile and execute a script (simple).
\return True if the result is NOT undefined. I.e. script execution probably went OK. False
		in case the result is undefined. */
bool ScriptContext::evaluateString(	
	const std::string& sScript, 		///< [in]	String with script to execute
	std::string& sScriptReturnValue ) 	///< [out]	Return value of script (if any)
{
	nsIPrincipal* thePrincipal = nsnull;
	nsString script= toAStringUTF16( sScript );
	PRBool bUndefined;
	nsString sReturnValue;
	nsresult rv = ifMoz()->EvaluateString( 
		script,
//		NS_LITERAL_STRING("bob();"),
		nsnull,	thePrincipal, "", 1, 
		JSVERSION_DEFAULT, 
//		JSVERSION_1_8,
		&sReturnValue, &bUndefined );
				
	sScriptReturnValue 	= toStdStringUTF8( sReturnValue );		
	return !static_cast<bool>(bUndefined != 0);
}

//	bool& bIsUndefined )				///< [out] True if the result of executing the script is the undefined value.


