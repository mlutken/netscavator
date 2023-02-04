#ifndef _MOZ_BROWSER_GTK_H_
#define _MOZ_BROWSER_GTK_H_

#if WEBBROWSE_ENABLE_GTK
#include <gtk/gtk.h>

#include "MozBrowser.h"

/** Toplevel (Gtk) browser class. */
class MozBrowserGtk : public MozBrowser {
public:
	typedef boost::shared_ptr<MozBrowserGtk> 	Ptr;		///< Pointer to a MozBrowserGtk
	

	MozBrowserGtk ( );
	MozBrowserGtk ( boost::shared_ptr<WebBrowser> pWebBrowser );
	
	virtual void		show();	 
	virtual void		hide();	 

//	boost::shared_ptr<wxFrame>				
//	guiGtk()	const							{	return m_pGuiGtk;	}

private:
//	boost::shared_ptr<wxFrame>				m_pGuiGtk;

};


#endif //#if WEBBROWSE_ENABLE_GTK


#endif // _MOZ_BROWSER_GTK_H_



