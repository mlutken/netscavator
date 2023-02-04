#ifndef _WEBBROWSE_STRING_CONVERSION_H_
#define _WEBBROWSE_STRING_CONVERSION_H_


#include <string>
#include <utils/mozilla_strings.h>



/** Convert a Mozilla UTF16 string (nsEmbedString) to a std::string in UTF8 */
inline std::string 
toStdStringUTF8 (const nsString& aString )		///< Mozilla UTF16 string to convert
//toStdStringUTF8 (const nsEmbedString& aString )		///< Mozilla UTF16 string to convert
{
	return NS_ConvertUTF16toUTF8(aString).get();	
}

// // /** Convert a Mozilla UTF16 string (nsCAutoString) to a std::string in UTF8 */
// // inline std::string 
// // toStdStringUTF8 (const nsCAutoString& aString )		///< Mozilla UTF16 string to convert
// // {
// // 	return NS_ConvertUTF16toUTF8(aString).get();	
// // }



/** Convert a std::string in UTF8 to Mozilla UTF16 string */
//inline nsEmbedString 
inline nsString 
toAStringUTF16 (const std::string& sString )		///< UTF8 std::string to convert
{
	return NS_ConvertUTF8toUTF16( sString.c_str() );
}




// ------------------------------------------------------
// --- For later when/if we implement wstring support ---
// ------------------------------------------------------

// /** Convert a Mozilla UTF16 string to a std::wstring in UTF16 
// \warning Not working yet!
// \todo Fix the toStdWStringUTF16 function.*/
// inline std::wstring 
// toStdWStringUTF16 (const nsEmbedString& aString )		///< Mozilla UTF16 string to convert
// {
// 	return (wchar_t*)aString.get();	
// }

#endif //_WEBBROWSE_STRING_CONVERSION_H_
