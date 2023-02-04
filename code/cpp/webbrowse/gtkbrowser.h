
#ifndef _GTK_BROWSER_H_
#define _GTK_BROWSER_H_

#ifdef _WINDOWS
#define PATH_MAX	2048
#endif

// ------------------------
// --- Advanced example ---
// ------------------------
#include <gtkmozembed.h>

#include <gtk/gtk.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#include <nsIDOMKeyEvent.h>
#include <nsIDOMMouseEvent.h>
#include <nsIDOMUIEvent.h>
#include <nsCOMPtr.h>
#include <nsIDOMWindow.h>
#include <nsIDOMDocument.h>
#include <nsIDOMDOMImplementation.h>
#include <nsXPCOMGlue.h>
#include <nsIWebNavigation.h>


#include "MozBrowser.h"

#include <boost/shared_ptr.hpp>	

//#include "gtkmozembed_glue.cpp"

typedef struct _TestGtkBrowser
{
	GtkWidget  *topLevelWindow;
	GtkWidget  *topLevelVBox;
	GtkWidget  *menuBar;
	GtkWidget  *fileMenuItem;
	GtkWidget  *fileMenu;
	GtkWidget  *fileOpenNewBrowser;
	GtkWidget  *fileStream;
	GtkWidget  *fileClose;
	GtkWidget  *fileQuit;
	GtkWidget  *toolbarHBox;
	GtkWidget  *toolbar;
	GtkWidget  *backButton;
	GtkWidget  *stopButton;
	GtkWidget  *forwardButton;
	GtkWidget  *reloadButton;
	GtkWidget  *urlEntry;
	GtkWidget  *mozEmbed;
	GtkWidget  *progressAreaHBox;
	GtkWidget  *progressBar;
	GtkWidget  *statusAlign;
	GtkWidget  *statusBar;
	const char *statusMessage;
	int         loadPercent;
	int         bytesLoaded;
	int         maxBytesLoaded;
	char       *tempMessage;
	gboolean menuBarOn;
	gboolean toolBarOn;
	gboolean locationBarOn;
	gboolean statusBarOn;
	
	boost::shared_ptr<MozBrowser> m_pMozBrowser;
}
TestGtkBrowser;





TestGtkBrowser *new_gtk_browser ( guint32 chromeMask );
void            set_browser_visibility ( TestGtkBrowser *browser, gboolean visibility );


// callbacks from the UI
void	back_clicked_cb ( GtkButton   *button, TestGtkBrowser *browser );
void	stop_clicked_cb ( GtkButton   *button, TestGtkBrowser *browser );
void	forward_clicked_cb ( GtkButton   *button, TestGtkBrowser *browser );
void	reload_clicked_cb ( GtkButton   *button,  TestGtkBrowser *browser );
void     url_activate_cb ( GtkEditable *widget,
                                  TestGtkBrowser *browser );
void     menu_open_new_cb ( GtkMenuItem *menuitem,
                                   TestGtkBrowser *browser );
void     menu_stream_cb ( GtkMenuItem *menuitem,
                                 TestGtkBrowser *browser );
void     menu_close_cb ( GtkMenuItem *menuitem,
                                TestGtkBrowser *browser );
void     menu_quit_cb ( GtkMenuItem *menuitem,
                               TestGtkBrowser *browser );
gboolean delete_cb ( GtkWidget *widget, GdkEventAny *event,
                            TestGtkBrowser *browser );
void     destroy_cb ( GtkWidget *widget,
                             TestGtkBrowser *browser );

// callbacks from the widget
void location_changed_cb ( GtkMozEmbed *embed, TestGtkBrowser *browser );
void title_changed_cb ( GtkMozEmbed *embed, TestGtkBrowser *browser );
void load_started_cb ( GtkMozEmbed *embed, TestGtkBrowser *browser );
void load_finished_cb ( GtkMozEmbed *embed, TestGtkBrowser *browser );
void net_state_change_cb ( GtkMozEmbed *embed, gint flags,
                                  guint status, TestGtkBrowser *browser );
void net_state_change_all_cb ( GtkMozEmbed *embed, const char *uri,
                                      gint flags, guint status,
                                      TestGtkBrowser *browser );
void progress_change_cb ( GtkMozEmbed *embed, gint cur, gint max,
                                 TestGtkBrowser *browser );
void progress_change_all_cb ( GtkMozEmbed *embed, const char *uri,
                                     gint cur, gint max,
                                     TestGtkBrowser *browser );
void link_message_cb ( GtkMozEmbed *embed, TestGtkBrowser *browser );
void js_status_cb ( GtkMozEmbed *embed, TestGtkBrowser *browser );
void new_window_cb ( GtkMozEmbed *embed,
                            GtkMozEmbed **retval, guint chromemask,
                            TestGtkBrowser *browser );
void visibility_cb ( GtkMozEmbed *embed,
                            gboolean visibility,
                            TestGtkBrowser *browser );
void destroy_brsr_cb ( GtkMozEmbed *embed, TestGtkBrowser *browser );
gint open_uri_cb ( GtkMozEmbed *embed, const char *uri,
                          TestGtkBrowser *browser );
void size_to_cb ( GtkMozEmbed *embed, gint width,
                         gint height, TestGtkBrowser *browser );
gint dom_key_down_cb ( GtkMozEmbed *embed, nsIDOMKeyEvent *event,
                              TestGtkBrowser *browser );
gint dom_key_press_cb ( GtkMozEmbed *embed, nsIDOMKeyEvent *event,
                               TestGtkBrowser *browser );
gint dom_key_up_cb ( GtkMozEmbed *embed, nsIDOMKeyEvent *event,
                            TestGtkBrowser *browser );
gint dom_mouse_down_cb ( GtkMozEmbed *embed, nsIDOMMouseEvent *event,
                                TestGtkBrowser *browser );
gint dom_mouse_up_cb ( GtkMozEmbed *embed, nsIDOMMouseEvent *event,
                              TestGtkBrowser *browser );
gint dom_mouse_click_cb ( GtkMozEmbed *embed, nsIDOMMouseEvent *event,
                                 TestGtkBrowser *browser );
gint dom_mouse_dbl_click_cb ( GtkMozEmbed *embed,
                                     nsIDOMMouseEvent *event,
                                     TestGtkBrowser *browser );
gint dom_mouse_over_cb ( GtkMozEmbed *embed, nsIDOMMouseEvent *event,
                                TestGtkBrowser *browser );
gint dom_mouse_out_cb ( GtkMozEmbed *embed, nsIDOMMouseEvent *event,
                               TestGtkBrowser *browser );
gint dom_activate_cb ( GtkMozEmbed *embed, nsIDOMUIEvent *event,
                              TestGtkBrowser *browser );
gint dom_focus_in_cb ( GtkMozEmbed *embed, nsIDOMUIEvent *event,
                              TestGtkBrowser *browser );
gint dom_focus_out_cb ( GtkMozEmbed *embed, nsIDOMUIEvent *event,
                               TestGtkBrowser *browser );

// callbacks from the singleton object
void new_window_orphan_cb ( GtkMozEmbedSingle *embed,
                                   GtkMozEmbed **retval, guint chromemask,
                                   gpointer data );

// some utility functions
void update_status_bar_text ( TestGtkBrowser *browser );
void update_temp_message ( TestGtkBrowser *browser,
                                  const char *message );
void update_nav_buttons ( TestGtkBrowser *browser );



#endif //_GTK_BROWSER_H_ 
