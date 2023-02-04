#ifndef __WX_MOZILLA_HTML_COMPATH__
#define __WX_MOZILLA_HTML_COMPAT_H__
/*
 * wxMozilla wxHtmlWindow Wrapper Class
 *
 * Developers:
 *  Jeremiah Cornelius McCarthy <jeremiah@whoop-ass.ca>
 *  Kevin Ollivier <kevino@tulane.edu>
 *  Dave Fancella <david.fancella@attbi.com>
*
 */

/*
#if defined(__WXGTK__)
#include <gtk/gtk.h>
#include <gdk/gdk.h>
#endif
*/
/* wxwindow includes */
#include "wx/defs.h"
#include "wx/window.h"

/* mozilla includes */
#include "nsIWebNavigation.h"
#include "nsStringAPI.h"
#include "nsCOMPtr.h"
#include "nsIEventQueueService.h"
#include "nsIPref.h"
#include "nsISupports.h"
#include "nsIBaseWindow.h"
#include "nsIWebBrowser.h"
#include "nsIWebBrowserChrome.h"
#include "nsIEmbeddingSiteWindow.h"
#include "nsEmbedAPI.h"
#include "nsIWindowCreator.h"
#include "nsCWebBrowser.h"
#include "nsIWebProgressListener.h"
#include "nsIInterfaceRequestor.h"
#include "nsIWebBrowserSetup.h"
#include "nsIDocShellTreeItem.h"
#include "nsIWebBrowserChromeFocus.h"
#include "nsIInterfaceRequestor.h"
#include "nsReadableUtils.h"



extern const char *wxMozillaBrowserNameStr;

/**
 * wxWindows Mozilla browser component
 */
class wxHtmlWindow
{
	private:
		DECLARE_DYNAMIC_CLASS ( wxMozillaBrowserImpl )

	protected:
		class wxMozillaBrowserChrome *Chrome;

		nsCOMPtr<nsIBaseWindow> mBaseWindow;
		nsCOMPtr<nsIWebBrowser> mWebBrowser;
		nsCOMPtr<nsIWebNavigation> mWebNav;
		nsString mURI;

	public:
		wxHtmlWindow();
		inline wxHtmlWindow ( wxWindow *parent, wxWindowID id,
		                      const wxPoint &pos = wxDefaultPosition,
		                      const wxSize &size = wxDefaultSize,
		                      long style = 0,
		                      const wxString &name = wxMozillaWindowImplNameStr )
		{
			Create ( parent, id, pos, size, style, name );
		}
		virtual ~wxHtmlWindow();

		bool Create ( wxWindow *parent, wxWindowID id,
		              const wxPoint &pos = wxDefaultPosition,
		              const wxSize &size = wxDefaultSize,
		              long style = 0,
		              const wxString &name = wxMozillaWindowImplNameStr );

		void AddFilter ( wxHtmlFilter *filter );
		bool AppendToPage ( const wxString &source );
		const wxHtmlContainerCell *GetInternalRepresention();
		wxString GetOpenedAnchor();
		wxString GetOpenedPage();
		wxString GetOpenedPageTitle();
		const wxFrame GetRelatedFrame();
		bool HistoryBack();
		bool HistoryCanBack();
		bool HistoryCanForward();
		bool HistoryClear();
		bool HistoryForward();
		bool LoadPage ( const wxString &location );
		void OnCellClicked ( wxHtmlCell *cell, wxCoord x, wxCoord y, const wxMouseEvent &event );
		void OnCellMouseHover ( wxHtmlCell *cell, wxCoord x, wxCoord y );
		void OnLinkClicked ( const wxHtmlLinkInfo &link );
		wxHtmlOpeningStatus OnOpeningURL ( wxHtmlURLType type, const wxString &url, wxString *redirect );
		void OnSetTitle ( const wxString &title );
		void ReadCustomization ( wxConfigBase *cfg, wxString path = wxEmptyString );
		void SetBorders ( int b );
		void SetFonts ( wxString normal_face, wxString fixed_face, const int *sizes );
		bool SetPage ( const wxString &source );
		void SetRelatedFrame ( wxFrame *frame, const wxString &format );
		void SetRelatedStatusBar ( int bar );
		void WriteCustomization ( wxConfigBase *cfg, wxString path = wxEmptyString );
};

#endif
