#include "BasePageWxIF.h"


boost::shared_ptr<BasePageCtrl>		
BasePageWxIF::basePageCtrlGet	() const	
{ 
	return m_pBasePageCtrl;	
}

void		
BasePageWxIF::basePageCtrlSet ( boost::shared_ptr<BasePageCtrl> pBasePageCtrl) 
{ 
	m_pBasePageCtrl = pBasePageCtrl;	
}

