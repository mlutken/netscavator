#ifndef _CREATOR_NOTEBOOK_CTRL_H_
#define _CREATOR_NOTEBOOK_CTRL_H_

#include <hacks/wx_h_include_hack.h>
#include <wx/bitmap.h>
#include <boost/shared_ptr.hpp>
#include <base/BasePageCtrl.h>


class CreatorMainFrameWx;
class wxAuiNotebook;
class wxAuiNotebookEvent;
class wxWindow;
class wxString;
class BasePageCtrl;
class BasePageWxIF;

class NotebookCtrl
{
public:
    NotebookCtrl	( CreatorMainFrameWx* pCreatorMainFrameWx, wxAuiNotebook* pNotebook );
	
    int									activePageGet 		( )	const;
    wxWindow* 							pageGet				( int iPage ) const;
    boost::shared_ptr<BasePageCtrl> 	basePageCtrlGet		( int iPage ) const;
	 
	 
    bool 				addPage( wxWindow* page, const wxString& caption, bool select = false, const wxBitmap& bitmap = wxNullBitmap );
			
    void 				notebookPageChangeSlot	( wxAuiNotebookEvent& evt );

private:
    // --- PRIVATE: Functions ---
    // --- PRIVATE: Data ---
    CreatorMainFrameWx* 				m_pCreatorMainFrameWx;
    wxAuiNotebook* 						m_pNotebook;
    int									m_iActivePage;
    wxWindow*							m_pActivePageWindow;
};




#endif // _CREATOR_NOTEBOOK_CTRL_H_

