//
// C++ Interface: string_conversion
//

#ifndef _WEBBROWSE_MOZILLA_IF_MACROS_H_
#define _WEBBROWSE_MOZILLA_IF_MACROS_H_

#include <boost/shared_ptr.hpp>	
#include <boost/cstdint.hpp>

////#include <xpcom/nsCOMPtr.h>
#include <nsCOMPtr.h>

#include "string_conversion.h"

// ---------------------
// --- Moz Macros ---
// ---------------------
/// GET! Return: Supports derivative class; Input: void. 
#define MOZ_IF_RETURN_MOZ(MozIfFunName,MozBaseClass) 								\
{																					\
	nsCOMPtr<MozBaseClass::nsInterfaceT> pIMozReturn;								\
	ifMoz()->MozIfFunName( getter_AddRefs(pIMozReturn) );							\
	return boost::shared_ptr<MozBaseClass>(new MozBaseClass(pIMozReturn) );			\
}

/// GET! Return: Supports derivative class; Input: string. 
#define MOZ_IF_RETURN_MOZ_STRING(MozIfFunName,MozBaseClass,StrIn1)					\
{																					\
	nsCOMPtr<MozBaseClass::nsInterfaceT> pIMozReturn;								\
	ifMoz()->MozIfFunName( toAStringUTF16(StrIn1), getter_AddRefs(pIMozReturn) );	\
	return boost::shared_ptr<MozBaseClass>(new MozBaseClass(pIMozReturn) );			\
}

/// GET! Return: Supports derivative class; Input: string, string. 
#define MOZ_IF_RETURN_MOZ_STRING_STRING(MozIfFunName,MozBaseClass,StrIn1,StrIn2)							\
{																											\
	nsCOMPtr<MozBaseClass::nsInterfaceT> pIMozReturn;														\
	ifMoz()->MozIfFunName( toAStringUTF16(StrIn1), toAStringUTF16(StrIn2), getter_AddRefs(pIMozReturn) );	\
	return boost::shared_ptr<MozBaseClass>(new MozBaseClass(pIMozReturn) );									\
}

/// GET! Return: Supports derivative class; Input: string, string. 
#define MOZ_IF_RETURN_MOZ_STRING_STRING_STRING(MozIfFunName,MozBaseClass,StrIn1,StrIn2,StrIn3)										\
{																																	\
	nsCOMPtr<MozBaseClass::nsInterfaceT> pIMozReturn;																				\
	ifMoz()->MozIfFunName( toAStringUTF16(StrIn1), toAStringUTF16(StrIn2), toAStringUTF16(StrIn3), getter_AddRefs(pIMozReturn) );	\
	return boost::shared_ptr<MozBaseClass>(new MozBaseClass(pIMozReturn) );															\
}

/// GET! Return: Supports derivative class; Input: Supports derivative class (boost::shared_ptr). 
#define MOZ_IF_RETURN_MOZ_MOZ(MozIfFunName,MozBaseClass,MozIn1)				\
{																			\
	nsCOMPtr<MozBaseClass::nsInterfaceT> pIMozReturn;						\
	ifMoz()->MozIfFunName( MozIn1->ifMoz(), getter_AddRefs(pIMozReturn) );	\
	return boost::shared_ptr<MozBaseClass>(new MozBaseClass(pIMozReturn) );	\
}

/// GET! Return: Supports derivative class; 
/// Input: Supports derivative class (boost::shared_ptr), Supports derivative class (boost::shared_ptr). 
#define MOZ_IF_RETURN_MOZ_MOZ_MOZ(MozIfFunName,MozBaseClass,MozIn1,MozIn2)					\
{																							\
	nsCOMPtr<MozBaseClass::nsInterfaceT> pIMozReturn;										\
	ifMoz()->MozIfFunName( MozIn1->ifMoz(), MozIn2->ifMoz(), getter_AddRefs(pIMozReturn) );	\
	return boost::shared_ptr<MozBaseClass>(new MozBaseClass(pIMozReturn) );					\
}

/// GET! Return: Supports derivative class; Input: int32. 
#define MOZ_IF_RETURN_MOZ_INT32(MozIfFunName,MozBaseClass,IntIn1)							\
{																							\
	nsCOMPtr<MozBaseClass::nsInterfaceT> pIMozReturn;										\
	ifMoz()->MozIfFunName( static_cast<PRInt32>(IntIn1), getter_AddRefs(pIMozReturn) );	\
	return boost::shared_ptr<MozBaseClass>(new MozBaseClass(pIMozReturn) );					\
}

/// GET! Return: Supports derivative class; Input: uint32. 
#define MOZ_IF_RETURN_MOZ_UINT32(MozIfFunName,MozBaseClass,UintIn1)							\
{																							\
	nsCOMPtr<MozBaseClass::nsInterfaceT> pIMozReturn;										\
	ifMoz()->MozIfFunName( static_cast<PRUint32>(UintIn1), getter_AddRefs(pIMozReturn) );	\
	return boost::shared_ptr<MozBaseClass>(new MozBaseClass(pIMozReturn) );					\
}


/// SET! Return: void; Input: Supports derivative class.
#define MOZ_IF_SET_VOID_MOZ(MozIfFunName,MozIn1) 				\
{																\
	ifMoz()->MozIfFunName( MozIn1->ifMoz() );					\
}

/// SET! Return: void; Input: Supports derivative class, Input: Supports derivative class.
#define MOZ_IF_SET_VOID_MOZ_MOZ(MozIfFunName,MozIn1,MozIn2) 		\
{																	\
	ifMoz()->MozIfFunName( MozIn1->ifMoz(), MozIn2->ifMoz() );		\
}

// --------------------------
// --- GET! String Macros ---
// --------------------------

/// GET! Return: string; Input: void.
#define MOZ_IF_RETURN_STRING(MozIfFunName) 						\
{																\
	nsString result;											\
	ifMoz()->MozIfFunName(result);								\
	return toStdStringUTF8( result );							\
}

/// GET! Return: string; Input: void. Moz function returns value to a PRUnichar** 
#define MOZ_IF_RETURN_STRING_PRUnichar(MozIfFunName)			\
{																\
 	PRUnichar* szRes;											\
 	ifMoz()->MozIfFunName( &szRes );							\
 	nsEmbedString nsRes(szRes);									\
 	return toStdStringUTF8( nsRes );							\
}

/// GET! Return: string from a nsACString; Input: void.
#define MOZ_IF_RETURN_CSTRING(MozIfFunName) 					\
{																\
	nsCString result;											\
	ifMoz()->MozIfFunName(result);								\
	return result.get() ;										\
}

/// GET! Return: string; Input: string.
#define MOZ_IF_RETURN_STRING_STRING(MozIfFunName,StrIn1)		\
{																\
	nsString result;										\
	ifMoz()->MozIfFunName( toAStringUTF16(StrIn1), result);		\
	return toStdStringUTF8( result );							\
}

/// GET! Return: string from a nsACString; Input: string (nsACString).
#define MOZ_IF_RETURN_CSTRING_CSTRING(MozIfFunName,StrIn1)							\
{																					\
	nsCString result;															\
	ifMoz()->MozIfFunName( nsCString(StrIn1.c_str(), StrIn1.length()), result);		\
	return result.get();															\
}

/// GET! Return: string; Input: string, string.
#define MOZ_IF_RETURN_STRING_STRING_STRING(MozIfFunName,StrIn1,StrIn2)					\
{																						\
	nsString result;																\
	ifMoz()->MozIfFunName( toAStringUTF16(StrIn1), toAStringUTF16(StrIn2), result);		\
	return toStdStringUTF8( result );													\
}

// --------------------------
// --- SET! Macros ---
// --------------------------

// --- string args only ---

/// SET! Return: void; Input: string.
#define MOZ_IF_SET_VOID_STRING(MozIfFunName,StrIn1) 		\
{															\
	ifMoz()->MozIfFunName(toAStringUTF16( StrIn1 ));		\
}

/// SET! (to nsACString) Return: void; Input: string.
#define MOZ_IF_SET_VOID_CSTRING(MozIfFunName,StrIn1) 						\
{																			\
	ifMoz()->MozIfFunName( nsCString(StrIn1.c_str(), StrIn1.length()) );	\
}

/// SET! Return: void; Input: string, string.
#define MOZ_IF_SET_VOID_STRING_STRING(MozIfFunName,StrIn1,StrIn2) 					\
{																					\
	ifMoz()->MozIfFunName( toAStringUTF16( StrIn1 ), toAStringUTF16( StrIn2 ) );	\
}

/// SET! Return: void; Input: string, string, string.
#define MOZ_IF_SET_VOID_STRING_STRING_STRING(MozIfFunName,StrIn1,StrIn2,StrIn3)									\
{																												\
	ifMoz()->MozIfFunName( toAStringUTF16( StrIn1 ), toAStringUTF16( StrIn2 ), toAStringUTF16( StrIn2 ) );		\
}

// --- int32 ---
#define MOZ_IF_SET_VOID_INT32_INT32(MozIfFunName,ValIn1,ValIn2) 							\
{																							\
	ifMoz()->MozIfFunName( static_cast<PRInt32>(ValIn1), static_cast<PRInt32>(ValIn2));		\
}


// ----------------------
// --- Boolean Macros ---
// ----------------------

/// GET! Return: bool; Input: void.
#define MOZ_IF_RETURN_BOOL(MozIfFunName) 		\
{												\
	PRBool result;								\
	ifMoz()->MozIfFunName(&result);				\
	return static_cast<bool>( result != 0  );	\
}

/// GET! Return: bool; Input: string.
#define MOZ_IF_RETURN_BOOL_STRING(MozIfFunName,StrIn1) 				\
{																	\
	PRBool result;													\
	ifMoz()->MozIfFunName( toAStringUTF16( StrIn1 ), &result);		\
	return static_cast<bool>( result != 0  );						\
}

/// GET! Return: bool; Input: string, string.
#define MOZ_IF_RETURN_BOOL_STRING_STRING(MozIfFunName,StrIn1,StrIn2)							\
{																								\
	PRBool result;																				\
	ifMoz()->MozIfFunName( toAStringUTF16( StrIn1 ), toAStringUTF16( StrIn1 ), &result);		\
	return static_cast<bool>( result != 0 );													\
}

/// GET! Return: bool; Input: moz, bool.
#define MOZ_IF_RETURN_BOOL_MOZ_BOOL(MozIfFunName,MozIn1,BoolIn1)								\
{																								\
	PRBool result;																				\
	ifMoz()->MozIfFunName( MozIn1->ifMoz(), static_cast<PRBool>(BoolIn1), &result);				\
	return static_cast<bool>( result != 0 );													\
}


/// SET! Return: void; Input: bool
#define MOZ_IF_SET_VOID_BOOL(MozIfFunName,Val1) 				\
{																\
	ifMoz()->MozIfFunName( static_cast<PRBool>( Val1 ));		\
}

// -----------------------------
// --- Signed Integer Macros ---
// -----------------------------

#define MOZ_IF_RETURN_INT16(MozIfFunName) 			\
{													\
	PRInt16 result;									\
	ifMoz()->MozIfFunName(&result);					\
	return static_cast<boost::int16_t>( result );	\
}

#define MOZ_IF_SET_VOID_INT16(MozIfFunName,ValIn1) 				\
{																\
	ifMoz()->MozIfFunName( static_cast<PRInt16>( ValIn1 ));		\
}

#define MOZ_IF_RETURN_INT32(MozIfFunName) 			\
{													\
	PRInt32 result;									\
	ifMoz()->MozIfFunName(&result);					\
	return static_cast<boost::int32_t>( result );	\
}

#define MOZ_IF_SET_VOID_INT32(MozIfFunName,ValIn1) 				\
{																\
	ifMoz()->MozIfFunName( static_cast<PRInt32>( ValIn1 ));		\
}

#define MOZ_IF_RETURN_INT64(MozIfFunName) 			\
{													\
	PRInt64 result;									\
	ifMoz()->MozIfFunName(&result);					\
	return static_cast<boost::int64_t>( result );	\
}

#define MOZ_IF_SET_VOID_INT64(MozIfFunName,ValIn1) 				\
{																\
	ifMoz()->MozIfFunName( static_cast<PRInt64>( ValIn1 ));		\
}

// -------------------------------
// --- Unsigned Integer Macros ---
// -------------------------------

#define MOZ_IF_RETURN_UINT16(MozIfFunName) 			\
{													\
	PRUint16 result;								\
	ifMoz()->MozIfFunName(&result);					\
	return static_cast<boost::uint16_t>( result );	\
}

#define MOZ_IF_SET_VOID_UINT16(MozIfFunName,ValIn1)					\
{																	\
	ifMoz()->MozIfFunName( static_cast<PRUint16>( ValIn1 ));		\
}

#define MOZ_IF_RETURN_UINT32(MozIfFunName) 			\
{													\
	PRUint32 result;								\
	ifMoz()->MozIfFunName(&result);					\
	return static_cast<boost::uint32_t>( result );	\
}

#define MOZ_IF_SET_VOID_UINT32(MozIfFunName,ValIn1)					\
{																	\
	ifMoz()->MozIfFunName( static_cast<PRUint32>( ValIn1 ));		\
}

#define MOZ_IF_RETURN_UINT64(MozIfFunName) 			\
{													\
	PRUint64 result;								\
	ifMoz()->MozIfFunName(&result);					\
	return static_cast<boost::uint64_t>( result );	\
}

#define MOZ_IF_SET_VOID_UINT64(MozIfFunName,ValIn1)					\
{																	\
	ifMoz()->MozIfFunName( static_cast<PRUint64>( ValIn1 ));		\
}

// --------------------
// --- Float Macros ---
// --------------------

#define MOZ_IF_RETURN_FLOAT(MozIfFunName) 		\
{												\
	float result;								\
	ifMoz()->MozIfFunName(&result);				\
	return result ;								\
}

#define MOZ_IF_SET_VOID_FLOAT(MozIfFunName,ValIn1)		\
{														\
	ifMoz()->MozIfFunName( ValIn1 );					\
}

// ------------------------------------------
// --- Standard Init Moz Interface Macros ---
// ------------------------------------------
	
	
/// Create standard constructor
/// Use like this: MOZ_CONSTRUCT(DOMNode,Supports) // inside Moz class deriving directly from Supports
/// Or like this: MOZ_CONSTRUCT(DOMElement,DOMNode) // inside Moz class deriving from DOMNode
/// \param ThisClass The name of this class
/// \param ParentClass The name of this class
#define MOZ_CONSTRUCT(ThisClass,ParentClass) 							\
public:																	\
	ThisClass ( nsISupports* pIMozImpl ) 								\
		:	ParentClass(pIMozImpl) {}									\
typedef nsI##ThisClass		nsInterfaceT;								\
typedef boost::shared_ptr<ThisClass>	Ptr;							\
																		\
inline nsInterfaceT*	ifMoz()  										\
{ 	return static_cast<nsInterfaceT*>( ifISupportsNAR() );	} 			\
																		\
inline nsInterfaceT* const	ifMoz() const								\
{ 	return static_cast<nsInterfaceT*>( ifISupportsNAR() );	} 			\
private:					

// --------------------------------
// --- IteratorItemIndex Macros ---
// --------------------------------

/// Creates begin(), end(), front(), back(), at(), size() functions for
/// a standard IteratorItemIndex<> typedef. Use inside iterators containing class
/// e.g. like: MOZ_IF_ITERATOR_ITEM_INDEX_CONTAINER_CLASS_FUNCS(DOMNode,length)
#define MOZ_IF_ITERATOR_ITEM_INDEX_CONTAINER_CLASS_FUNCS(ValueType,GetSizeFun)				\
	iterator						begin()													\
	{	return iterator( ifMoz(), 0 );		}											\
																							\
	iterator						end()													\
	{	return iterator( ifMoz(), size() );	}											\
																							\
	boost::shared_ptr<ValueType>	front()													\
	{	return at(0); }																		\
																							\
	boost::shared_ptr<DOMNode>		back()													\
	{	return at(size() -1); }																\
																							\
	boost::uint32_t					size()	const											\
	{	return GetSizeFun(); }																\
																							\
	boost::shared_ptr<ValueType>	at( boost::uint32_t iIndex ) const						\
	{																						\
		if ( iIndex < size() ) 		return item(iIndex);									\
		else						return boost::shared_ptr<ValueType>(new ValueType(0) );	\
	}


#endif //_WEBBROWSE_MOZILLA_IF_MACROS_H_

