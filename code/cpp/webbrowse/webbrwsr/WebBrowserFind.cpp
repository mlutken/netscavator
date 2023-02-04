
#include "WebBrowserFind.h"
///  Get search string 
std::string 				
WebBrowserFind::searchString() const
{	
 	MOZ_IF_RETURN_STRING_PRUnichar(GetSearchString); 
}
  	
///  Set search string
void 				
WebBrowserFind::searchString( const std::string& sSearchString )		///< String value 
{	
	nsString nsValue = toAStringUTF16 ( sSearchString )	;
	const PRUnichar* szSearchFor = nsValue.get();
 	ifMoz()->SetSearchString( szSearchFor );	
}
