#ifndef _CREATOR_FIND_TOOLBAR_WX_H_
#define _CREATOR_FIND_TOOLBAR_WX_H_

#include <hacks/wx_h_include_hack.h>
#include <wx/wxprec.h>

class CreatorMainFrameWx;

class FindToolBarWx : public wxPanel
{
    enum
    {
        ID_TxtFind = wxID_HIGHEST+1,
        ID_BtnFind
    };

public:

    FindToolBarWx( CreatorMainFrameWx* pCreatorMainFrameWx );

private:
	void		onClicked_BtnFind(wxCommandEvent& event);


private:
	
	wxTextCtrl* 					m_pTxtFind;
	wxButton* 						m_pBtnFind;
	CreatorMainFrameWx*				m_pCreatorMainFrameWx;	
	DECLARE_EVENT_TABLE()
};




#endif // _CREATOR_FIND_TOOLBAR_WX_H_

