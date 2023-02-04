#ifndef _WEBBROWSE_MOZILLA_UTILS_H_
#define _WEBBROWSE_MOZILLA_UTILS_H_

#include <vector>				// For the random_access_iterator_tag. TODO: Could we include another file to get that instead?
#include <boost/shared_ptr.hpp>	
#include <boost/cstdint.hpp>

// // #include <xpcom/nsCOMPtr.h>

#include <nsCOMPtr.h>

template <class MOZ_WRAPPER_TO, class MOZ_WRAPPER_ASK>
boost::shared_ptr<MOZ_WRAPPER_TO>
doQueryInterface( boost::shared_ptr<MOZ_WRAPPER_ASK> pMoz )
{
	nsCOMPtr<typename MOZ_WRAPPER_TO::nsInterfaceT> pIMoz = do_QueryInterface( pMoz->ifMoz() );
	return boost::shared_ptr<MOZ_WRAPPER_TO>(new MOZ_WRAPPER_TO(pIMoz));
}

//   nsCOMPtr<nsIAccessible> accessible(do_QueryInterface(accessNode));
//   nsIAccessible *accPtr;
//   NS_IF_ADDREF(accPtr = accessible);
//   return accPtr;

class Supports
{
public:
	Supports ( nsISupports* pISupports ) :			
		m_pISupports(pISupports)	{}														

	bool			valid() const					
	{	return static_cast<bool>(m_pISupports.get() != 0);	}						
												
protected:
	/// Return mutable raw nsISupports*, NON add refed.
	nsISupports*	ifISupportsNAR()
	{ 	return m_pISupports;	} 								
	
	/// Return raw nsISupports*, NON add refed const.														
	nsISupports*	ifISupportsNAR() const
	{ 	return m_pISupports;	} 								
															
	/// Return nsCOMPtr<nsISupports>.
	nsCOMPtr<nsISupports>	ifISupportsCOMPtr()
	{ 	return m_pISupports;	} 								
	
	/// Return nsCOMPtr<nsISupports>.const.														
	nsCOMPtr<nsISupports>	ifISupportsCOMPtr() const
	{ 	return m_pISupports;	} 								
															
private:													
	nsCOMPtr<nsISupports>	m_pISupports;
};




/// Nested IteratorItemIndex class.
template <class CONTAINER_MOZ, class VALUE_TYPE>
class IteratorItemIndex
{
public:
	// --- Typedefs PUBLIC ---
	typedef typename CONTAINER_MOZ::nsInterfaceT		nsContainerInterfaceT;
	typedef typename VALUE_TYPE::nsInterfaceT			nsValueTypeInterfaceT;
	
	typedef typename std::random_access_iterator_tag	iterator_category;	///< Iterator category. Certain algorithms need certain kinds of IteratorItemIndexs.
	typedef typename boost::shared_ptr<VALUE_TYPE>		value_type;			///< The type of object, T, pointed to by the IteratorItemIndex.
	typedef value_type &								reference;
	typedef value_type *								pointer;
	typedef boost::int32_t								difference_type;

	// --- Constructors PUBLIC ---
	/// Default constructor. Initialize node pointer to 0.
	IteratorItemIndex() : m_pIMozImpl(0), m_iIndex(0) { }
	
	/// Construct from MOzilla interface pointer and a given index value
	IteratorItemIndex( nsContainerInterfaceT* pIMozImpl, boost::uint32_t iStartIndex = 0 )		///< [in] Pointer to node list.
		: m_pIMozImpl(pIMozImpl), m_iIndex(iStartIndex) { }

	/// Copy contructor
	IteratorItemIndex(const IteratorItemIndex& it)							///< [in] Iterator to construct from.
		: m_pIMozImpl(it.m_pIMozImpl), m_iIndex(it.m_iIndex) { }
	
	// --- Operator overloads PUBLIC ---

	/// Acces operator '*' de-reference
	/// \todo Perhaps this should somehow return a reference to a member instead of 'by value'.
	value_type			operator*() const 
	{
//		printf("SSSSSSSSSSSSSSSSSSSSSSSSSSSS\n");
		nsCOMPtr<nsValueTypeInterfaceT> pIValue;
		m_pIMozImpl->Item( m_iIndex, getter_AddRefs(pIValue) );
		return boost::shared_ptr<VALUE_TYPE>(new VALUE_TYPE(pIValue) );
	}

	// /// Acces operator '->'. 
	//pointer				operator->() const 
	//{	// Delegate to operator '*'
	//	return (&**this);	// Return pointer to class object TODO: Get warning for taking address of temporary.
	//}


	/// += operator. Note we return by REFERENCE here. 
	IteratorItemIndex&			operator+=(difference_type iRhs)
	{
		m_iIndex += iRhs;	
		return *this;	
	}

	/// + operator. Note we return by REFERENCE here.
	IteratorItemIndex&			operator+(difference_type iRhs)
	{
		m_iIndex = m_iIndex + iRhs;	
		return *this;	
	}

	/// += operator. Note we return by REFERENCE here. 
	IteratorItemIndex&			operator-=(difference_type iRhs)
	{
		m_iIndex -= iRhs;	
		return *this;	
	}

	/// + operator. Note we return by REFERENCE here. 
	IteratorItemIndex&			operator-(difference_type iRhs)
	{
		m_iIndex = m_iIndex - iRhs;	
		return *this;	
	}

	/// Postfix increment operator. 
	const IteratorItemIndex		operator++(int)
	{
		IteratorItemIndex itTemp(*this);		// Make copy of original
		m_iIndex++;	
		return itTemp;				// Return copy of original
	}

	/// Prefix increment operator. Note we return by REFERENCE here.
	IteratorItemIndex&			operator++()
	{
		m_iIndex++;	
		return *this;	
	}

	/// Postfix decrement operator. 
	const IteratorItemIndex		operator--(int)
	{
		IteratorItemIndex itTemp(*this);		// Make copy of original
		m_iIndex--;	
		return itTemp;				// Return copy of original
	}

	/// Prefix decrement operator. Note we return by REFERENCE here. 
	IteratorItemIndex&			operator--()
	{
		m_iIndex--;	
		return *this;	
	}

	/// Compare IteratorItemIndexs for equality
	bool				operator==(	const IteratorItemIndex& itR )	const ///< [in] Right operand.    
	{	return (this->m_pIMozImpl == itR.m_pIMozImpl) && (this->m_iIndex == itR.m_iIndex) ;	}
	
	/// Compare IteratorItemIndexs for in-equality
	bool 				operator!=(	const IteratorItemIndex& itR ) 	const
	{   return (!(*this == itR));	}

	/// Operator < (less than) 
	bool				operator<(	const IteratorItemIndex& itR )	const ///< [in] Right operand.    
	{	return (this->m_iIndex < itR.m_iIndex) ;	}
	
	/// Operator <= (less than or equal ) 
	bool				operator<=(	const IteratorItemIndex& itR )	const ///< [in] Right operand.    
	{	return (this->m_iIndex <= itR.m_iIndex) ;	}

	/// Operator > (greater than) 
	bool				operator>(	const IteratorItemIndex& itR )	const ///< [in] Right operand.    
	{	return (this->m_iIndex > itR.m_iIndex) ;	}
	
	/// Operator >= (greater than or equal) 
	bool				operator>=(	const IteratorItemIndex& itR )	const ///< [in] Right operand.    
	{	return (this->m_iIndex >= itR.m_iIndex) ;	}
	
private:
	nsCOMPtr<nsContainerInterfaceT>	m_pIMozImpl;	///< Pointer to nsIxx type of contaner class 
	boost::uint32_t					m_iIndex;		///< Index 
};



#endif //_WEBBROWSE_MOZILLA_UTILS_H_

// template <class MOZ_IF>
// class MozBase : public Supports
// {
// public:
// 	typedef MOZ_IF		nsInterfaceT;
// 															
// /*	MozBase ( nsCOMPtr<nsInterfaceT> pIMozImpl ) :			
// 		m_pIMozImpl(pIMozImpl)								
// 	{}														*/
// //	MozBase ( nsInterfaceT* pIMozImpl ) :			
// 	MozBase ( nsISupports* pIMozImpl ) :			
// 		Supports(pIMozImpl)
// //		m_pIMozImpl(pIMozImpl)								
// 	{}														
// 															
// //	nsCOMPtr<nsInterfaceT>	ifMoz()  						
// //	already_AddRefed<nsInterfaceT>	ifMoz()  						
// // 	nsInterfaceT*	ifMoz()  						
// // 	{ 	return m_pIMozImpl;	} 								
// 															
// //	already_AddRefed<nsInterfaceT>	ifMoz()  const
// //	nsCOMPtr<nsInterfaceT>	ifMoz() const
// // 	nsInterfaceT*	ifMoz() const
// // 	{ 	return m_pIMozImpl;	} 								
// 															
// 															
// 															
// 	nsInterfaceT*	ifMoz()  						
// 	{ 	return static_cast<nsInterfaceT*>( ifISupportsNAF() );	} 								
// 															
// 	nsInterfaceT*	ifMoz() const
// 	{ 	return static_cast<nsInterfaceT*>( ifISupportsNAF() );	} 								
// 															
// 															
// /*	bool					valid() const					
// 	{	return m_pIMozImpl != 0;	}						*/
// 															
// private:													
// //	nsCOMPtr<nsInterfaceT>	m_pIMozImpl;
// 
// };

