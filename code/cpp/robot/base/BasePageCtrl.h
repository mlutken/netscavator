#ifndef _CREATOR_BASE_PAGE_CTRL_H_
#define _CREATOR_BASE_PAGE_CTRL_H_

#include <string>

class CreatorMainFrameWx;


class BasePageCtrl  
{
public:
	virtual void			searchStringSet 	( std::string sSearchFor ) 	{};
	virtual bool			findNext 			()							{ return false;	};
	virtual void			focusActivate		()							{};
	virtual void			focusDeactivate		()							{};
			

private:
	// --- PRIVATE: Functions ---	
	// --- PRIVATE: Data ---	
};




#endif // _CREATOR_BASE_PAGE_CTRL_H_

