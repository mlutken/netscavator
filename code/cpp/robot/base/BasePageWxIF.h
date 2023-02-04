#ifndef _CREATOR_BASE_PAGE_WX_IF_H_
#define _CREATOR_BASE_PAGE_WX_IF_H_

#include <boost/shared_ptr.hpp>


class BasePageCtrl;

class BasePageWxIF  
{
public:
	virtual ~BasePageWxIF() {};  
	
	boost::shared_ptr<BasePageCtrl>		
	basePageCtrlGet	() const;
	
	void		
	basePageCtrlSet	( boost::shared_ptr<BasePageCtrl> pBasePageCtrl) ;
			

private:
	// --- PRIVATE: Data ---	
	boost::shared_ptr<BasePageCtrl>		m_pBasePageCtrl;
};




#endif // _CREATOR_BASE_PAGE_WX_IF_H_

