#ifndef _WEBBROWSE_DOM_CHARACTER_DATA_H_
#define _WEBBROWSE_DOM_CHARACTER_DATA_H_


////#include <dom/nsIDOMCharacterData.h>
#include <nsIDOMCharacterData.h>

#include <dom/DOMNode.h>

/**
The nsIDOMCharacterData interface extends nsIDOMNode with a set of 
attributes and methods for accessing character data in the DOM.
 
For more information on this interface please see 
http://www.w3.org/TR/DOM-Level-2-Core/

@status FROZEN
*/
class DOMCharacterData : public DOMNode {
	MOZ_CONSTRUCT(DOMCharacterData,DOMNode);
public: 
	///  Get data
	std::string 				
	data() const 
											{	MOZ_IF_RETURN_STRING(GetData); }
	///  Set data
	void 				
	data( const std::string& sData )		///< String data 
											{	MOZ_IF_SET_VOID_STRING(SetData,sData);	}
  	///  Get length 
	boost::uint32_t 				
	length() const 
											{	MOZ_IF_RETURN_UINT32(GetLength); }
  	
  	/// Get sub-string. \todo raises (DOMException)
	std::string 				
	substringData( 	boost::uint32_t		iOffset,	///< Offset position 
					boost::uint32_t 	iCount )	///< Number of characters to return
	{	
		nsString result;																
		ifMoz()->SubstringData( static_cast<PRUint32>(iOffset), static_cast<PRUint32>(iCount), result );	
		return toStdStringUTF8( result );													
	}
  	
  	/// Append string data. \todo raises (DOMException)
	void 				
	appendData( const std::string& sString )	///< String data to append
											{	MOZ_IF_SET_VOID_STRING(AppendData,sString);	}
  	
  	/// Insert string data at offset. \todo raises (DOMException)
	void 				
	insertData( boost::uint32_t		iOffset,	///< Offset position to insert string at.
				const std::string& 	sString )	///< String data to append
											{	ifMoz()->InsertData( static_cast<PRUint32>(iOffset), toAStringUTF16( sString ) );	}
  	
  	/// Remove count characters beginning at offset. \todo raises (DOMException)
	void 				
	deleteData( boost::uint32_t		iOffset,	///< Offset position where remove 'starts'.
				boost::uint32_t 	iCount )	///< Number of characters to remove
											{	ifMoz()->DeleteData( static_cast<PRUint32>(iOffset), static_cast<PRUint32>(iCount) );	}

  	/// Replace characters beginning at offset. \todo raises (DOMException)
	void 				
	replaceData(boost::uint32_t		iOffset,	///< Offset position where replace 'starts'.
				boost::uint32_t 	iCount,		///< \todo ? TODO:
				const std::string& 	sString )	///< String data to insert
											{	ifMoz()->ReplaceData( static_cast<PRUint32>(iOffset), static_cast<PRUint32>(iCount), toAStringUTF16( sString ) );	}
};
#endif /* _WEBBROWSE_DOM_CHARACTER_DATA_H_ */

