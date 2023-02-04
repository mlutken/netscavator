/*
 * wxWindows Mozilla Dialogs Component
 *
 * Developers:
 *  Jeremiah Cornelius McCarthy <jeremiah@whoop-ass.ca>
 *  Kevin Ollivier <kevino@tulane.edu>
 *  Dave Fancella <david.fancella@attbi.com>
 */
#include "wx/wxprec.h"

#ifndef WX_PRECOMP
#include "wx/wx.h"
#endif

#include "wxMozillaDialogs.h"
#include "cstmdlg.h"
#include "wxMozilla.h"
#include "wxMozillaBrowser.h"
#include "wxMozillaBrowserChrome.h"
#include "helpers.h"

#include "nsCOMPtr.h"

#include "nsIPromptService.h"
#include "nsIFactory.h"
#include "nsIDOMWindow.h"
#include "nsIWindowWatcher.h"
////#include "nsReadableUtils.h"
#include "nsServiceManagerUtils.h"

/* nsIPromptService implementation -
	this overriddes the default XUL dialogs with native wxWindows ones!

	Sites for testing prompts:
	Alert - just type in a bad web address or http://www.htmlite.com/JS002.php
	Prompt - http://www.htmlite.com/JS007.php
	Confirm - http://www.htmlite.com/JS006.php

*/

class wxMozillaDialogs: public nsIPromptService
{
	public:
		wxMozillaDialogs();
		virtual ~wxMozillaDialogs();

		NS_DECL_ISUPPORTS
		NS_DECL_NSIPROMPTSERVICE

	private:
		nsCOMPtr<nsIWindowWatcher> mWWatch;
		wxMozillaBrowser* BrowserForDOMWindow ( nsIDOMWindow *aWindow );
};
//*****************************************************************************

NS_IMPL_ISUPPORTS1 ( wxMozillaDialogs, nsIPromptService )

wxMozillaDialogs::wxMozillaDialogs() :
		mWWatch ( do_GetService ( NS_WINDOWWATCHER_CONTRACTID ) )
{
}

wxMozillaDialogs::~wxMozillaDialogs()
{
}

wxMozillaBrowser* wxMozillaDialogs::BrowserForDOMWindow ( nsIDOMWindow *aWindow )
{
	nsCOMPtr<nsIWebBrowserChrome> chrome;
	wxMozillaBrowser* Moz = NULL;

	if ( mWWatch )
	{
		nsCOMPtr<nsIDOMWindow> fosterParent;
		if ( !aWindow ) // it will be a dependent window. try to find a foster parent.
		{
			mWWatch->GetActiveWindow ( getter_AddRefs ( fosterParent ) );
			aWindow = fosterParent;
		}
		mWWatch->GetChromeForWindow ( aWindow, getter_AddRefs ( chrome ) );
	}

	if ( chrome )
	{
		nsCOMPtr<nsIEmbeddingSiteWindow> site ( do_QueryInterface ( chrome ) );
		if ( site )
		{
			site->GetSiteWindow ( reinterpret_cast<void **> ( &Moz ) );
		}
	}

	return Moz;
}

NS_IMETHODIMP wxMozillaDialogs::Alert ( nsIDOMWindow *parent, const PRUnichar *dialogTitle, const PRUnichar *text )
{
	wxString title = wxEmptyString;
	wxString message = wxEmptyString;

	if ( dialogTitle )
		title = nsString_to_wxString ( nsString ( dialogTitle ), wxConvLocal );

	if ( text )
		message = nsString_to_wxString ( nsString ( text ), wxConvLocal );

	wxMozillaBrowser* Moz = BrowserForDOMWindow ( parent );
	if ( Moz )
		wxMessageDialog ( Moz->GetParent(), message, title, wxOK ).ShowModal();

	return NS_OK;
}

//this one is a message dialog with a checkbox in it - does wxWin have this?
NS_IMETHODIMP wxMozillaDialogs::AlertCheck ( nsIDOMWindow *parent, const PRUnichar *dialogTitle, const PRUnichar *text, const PRUnichar *checkMsg, PRBool *checkValue )
{

	wxString title = wxEmptyString;
	wxString message = wxEmptyString;
	wxString checkText = wxEmptyString;

	if ( dialogTitle )
		title = nsString_to_wxString ( nsString ( dialogTitle ), wxConvLocal );

	if ( text )
		message = nsString_to_wxString ( nsString ( text ), wxConvLocal );

	if ( checkMsg )
		checkText = nsString_to_wxString ( nsString ( checkMsg ), wxConvLocal );

	wxMozillaBrowser* Moz = BrowserForDOMWindow ( parent );
	if ( Moz )
	{
		wxCustomDialog mydialog ( Moz->GetParent(), message, title, _ ( "OK" ), wxEmptyString, wxEmptyString, checkText );
		mydialog.ShowModal();
		if ( mydialog.IsChecked() )
			*checkValue = PR_TRUE;
		else
			*checkValue = PR_FALSE;
	}

	return NS_OK;
}

//OK or Cancel dialog - returns PR_TRUE or PR_FALSE to Mozilla
NS_IMETHODIMP wxMozillaDialogs::Confirm ( nsIDOMWindow *parent, const PRUnichar *dialogTitle, const PRUnichar *text, PRBool *_retval )
{

	wxString title = wxEmptyString;
	wxString message = wxEmptyString;

	if ( dialogTitle )
		title = nsString_to_wxString ( nsString ( dialogTitle ), wxConvLocal );

	if ( text )
		message = nsString_to_wxString ( nsString ( text ), wxConvLocal );

	wxMozillaBrowser* Moz = BrowserForDOMWindow ( parent );
	if ( Moz )
	{
		int result;
		result = wxMessageDialog ( Moz->GetParent(), message, title, wxOK | wxCANCEL ).ShowModal();
		if ( result == wxID_OK )
			*_retval = PR_TRUE;
		else
			*_retval = PR_FALSE;
	}

	return NS_OK;
}

/* same as confirm, but with checkbox */
NS_IMETHODIMP wxMozillaDialogs::ConfirmCheck ( nsIDOMWindow *parent, const PRUnichar *dialogTitle, const PRUnichar *text, const PRUnichar *checkMsg, PRBool *checkValue, PRBool *_retval )
{
	wxString title = wxEmptyString;
	wxString message = wxEmptyString;
	wxString checkText = wxEmptyString;

	if ( dialogTitle )
		title = nsString_to_wxString ( nsString ( dialogTitle ), wxConvLocal );

	if ( text )
		message = nsString_to_wxString ( nsString ( text ), wxConvLocal );

	if ( checkMsg )
		checkText = nsString_to_wxString ( nsString ( checkMsg ), wxConvLocal );

	wxMozillaBrowser* Moz = BrowserForDOMWindow ( parent );
	if ( Moz )
	{
		int result;
		wxCustomDialog mydialog ( Moz->GetParent(), message, title, _ ( "OK" ), _ ( "Cancel" ), wxEmptyString, checkText );
		result = mydialog.ShowModal();
		if ( result == 1 )
		{
			*_retval = PR_TRUE;
			if ( mydialog.IsChecked() )
				*checkValue = PR_TRUE;
			else
				*checkValue = PR_FALSE;
		}
		else
			*_retval = PR_FALSE;
	}

	return NS_OK;
}

/* confirm with up to 3 buttons, which can have situation-defined values*/
NS_IMETHODIMP wxMozillaDialogs::ConfirmEx ( nsIDOMWindow *parent, const PRUnichar *dialogTitle, const PRUnichar *text, PRUint32 buttonFlags, const PRUnichar *button0Title, const PRUnichar *button1Title, const PRUnichar *button2Title, const PRUnichar *checkMsg, PRBool *checkValue, PRInt32 *_retval )
{
	wxString title = wxEmptyString;
	wxString message = wxEmptyString;
	wxString checkText = wxEmptyString;
	wxArrayString btnStrings;

	//this nasty bit-shifting loop is used to set the button titles...
	for ( int i = 0; i < 3; i++ )
	{
		PRUint32 titleId = buttonFlags & 255;
		switch ( titleId )
		{
			case nsIPromptService::BUTTON_TITLE_OK:
			{
				btnStrings.Add ( _ ( "OK" ) );
				break;
			}
			case nsIPromptService::BUTTON_TITLE_CANCEL:
			{
				btnStrings.Add ( _ ( "Cancel" ) );
				break;
			}
			case nsIPromptService::BUTTON_TITLE_YES:
			{
				btnStrings.Add ( _ ( "Yes" ) );
				break;
			}
			case nsIPromptService::BUTTON_TITLE_NO:
			{
				btnStrings.Add ( _ ( "No" ) );
				break;
			}
			case nsIPromptService::BUTTON_TITLE_SAVE:
			{
				btnStrings.Add ( _ ( "Save" ) );
				break;
			}
			case nsIPromptService::BUTTON_TITLE_DONT_SAVE:
			{
				btnStrings.Add ( _ ( "Don't Save" ) );
				break;
			}
			case nsIPromptService::BUTTON_TITLE_REVERT:
			{
				btnStrings.Add ( _ ( "Revert" ) );
				break;
			}
			case nsIPromptService::BUTTON_TITLE_IS_STRING:
			{
				const PRUnichar *btnTitle =
				    ( i == 0 ) ? button0Title :
				    ( i == 1 ) ? button1Title : button2Title;
				if ( btnTitle )
				{
					btnStrings.Add ( nsString_to_wxString ( nsString ( btnTitle ), wxConvLocal ) );
				}
				break;
			}
			default:
				// ANYTHING ELSE GETS IGNORED - but make sure we have a total of 3 strings
				btnStrings.Add ( wxEmptyString );
				break;
		}
		buttonFlags >>= 8;
	}

	if ( dialogTitle )
		title = nsString_to_wxString ( nsString ( dialogTitle ), wxConvLocal );

	if ( text )
		message = nsString_to_wxString ( nsString ( text ), wxConvLocal );

	if ( checkMsg )
		checkText = nsString_to_wxString ( nsString ( checkMsg ), wxConvLocal );

	wxMozillaBrowser* Moz = BrowserForDOMWindow ( parent );
	if ( Moz )
	{
		int result;
		wxCustomDialog mydialog ( Moz->GetParent(), message, title, btnStrings[0], btnStrings[1], btnStrings[2], checkText );
		result = mydialog.ShowModal();
		if ( mydialog.IsChecked() )
			*checkValue = PR_TRUE;
		else
			*checkValue = PR_FALSE;

		*_retval = result - 1; //Moz wants 0-2 return codes
		//TODO: add support for checkboxes, for now just leave the value as it was
	}

	return NS_OK;
}

NS_IMETHODIMP wxMozillaDialogs::Prompt ( nsIDOMWindow *parent, const PRUnichar *dialogTitle, const PRUnichar *text, PRUnichar **value, const PRUnichar *checkMsg, PRBool *checkValue, PRBool *_retval )
{

	wxString title = wxEmptyString;
	wxString message = wxEmptyString;
	wxString defValue = wxEmptyString;
	int dlgResult;

	if ( dialogTitle )
		title = nsString_to_wxString ( nsString ( dialogTitle ), wxConvLocal );

	if ( text )
		message = nsString_to_wxString ( nsString ( text ), wxConvLocal );

	if ( *value )
	{
		defValue = nsString_to_wxString ( nsString ( *value ), wxConvLocal );
	}

	wxMozillaBrowser* Moz = BrowserForDOMWindow ( parent );
	if ( Moz )
	{
		wxTextEntryDialog mydialog ( Moz, message, title, defValue );
		dlgResult = mydialog.ShowModal();
		if ( dlgResult == wxID_OK )
		{
			*_retval = PR_TRUE;
			*value = ToNewUnicode ( wxString_to_nsString ( mydialog.GetValue(), wxConvLocal ) );

		}
		else
		{
			*_retval = PR_FALSE;
		}
	}
	else
	{
		*_retval = PR_FALSE;
	}
	return NS_OK;
}

NS_IMETHODIMP wxMozillaDialogs::PromptUsernameAndPassword ( nsIDOMWindow *parent, const PRUnichar *dialogTitle, const PRUnichar *text, PRUnichar **username, PRUnichar **password, const PRUnichar *checkMsg, PRBool *checkValue, PRBool *_retval )
{
	wxString title = wxEmptyString;
	wxString message = wxEmptyString;
	wxString defUser = wxEmptyString;
	wxString defPass = wxEmptyString;
	wxString chkMessage = wxEmptyString;

	int dlgResult;

	if ( dialogTitle )
		title = nsString_to_wxString ( nsString ( dialogTitle ), wxConvLocal );

	if ( text )
		message = nsString_to_wxString ( nsString ( text ), wxConvLocal );

	if ( *username )
	{
		defUser = nsString_to_wxString ( nsString ( *username ), wxConvLocal );
	}

	if ( *password )
	{
		defPass = nsString_to_wxString ( nsString ( *password ), wxConvLocal );
	}

	if ( *checkMsg )
	{
		chkMessage = nsString_to_wxString ( nsString ( checkMsg ), wxConvLocal );
	}

	wxMozillaBrowser* Moz = BrowserForDOMWindow ( parent );
	if ( Moz )
	{
		wxLoginDialog login ( Moz, message, title, defUser, defPass, chkMessage );
		dlgResult = login.ShowModal();
		if ( dlgResult == wxID_OK )
		{
			*username = ToNewUnicode ( wxString_to_nsString ( login.GetUsername(), wxConvLocal ) );
			*password = ToNewUnicode ( wxString_to_nsString ( login.GetPassword(), wxConvLocal ) );
			if ( login.IsChecked() )
				*checkValue = PR_TRUE;
			else
				*checkValue = PR_FALSE;

			*_retval = PR_TRUE;
		}
		else
		{
			*_retval = PR_FALSE;
		}
	}
	else
	{
		*_retval = PR_FALSE;
	}
	//wxMessageBox("PromptUsernameAndPassword called!");
	return NS_OK;
}

NS_IMETHODIMP wxMozillaDialogs::PromptPassword ( nsIDOMWindow *parent, const PRUnichar *dialogTitle, const PRUnichar *text, PRUnichar **password, const PRUnichar *checkMsg, PRBool *checkValue, PRBool *_retval )
{
	wxString title = wxEmptyString;
	wxString message = wxEmptyString;
	wxString defValue = wxEmptyString;
	int dlgResult;

	if ( dialogTitle )
		title = nsString_to_wxString ( nsString ( dialogTitle ), wxConvLocal );

	if ( text )
		message = nsString_to_wxString ( nsString ( text ), wxConvLocal );

	if ( *password )
	{
		defValue = nsString_to_wxString ( nsString ( *password ), wxConvLocal );
	}

	wxMozillaBrowser* Moz = BrowserForDOMWindow ( parent );
	if ( Moz )
	{
		wxTextEntryDialog mydialog ( Moz, message, title, defValue, wxOK|wxCANCEL|wxTE_PASSWORD|wxALIGN_CENTRE );
		dlgResult = mydialog.ShowModal();
		if ( dlgResult == wxID_OK )
		{
			*_retval = PR_TRUE;
			*password = ToNewUnicode ( wxString_to_nsString ( mydialog.GetValue(), wxConvLocal ) );

		}
		else
		{
			*_retval = PR_FALSE;
		}
	}
	else
	{
		*_retval = PR_FALSE;
	}
	return NS_OK;
}

NS_IMETHODIMP wxMozillaDialogs::Select ( nsIDOMWindow *parent, const PRUnichar *dialogTitle, const PRUnichar *text, PRUint32 count, const PRUnichar **selectList, PRInt32 *outSelection, PRBool *_retval )
{

	wxString title = wxEmptyString;
	wxString message = wxEmptyString;
	wxString defValue = wxEmptyString;
	int dlgResult;

	if ( dialogTitle )
		title = nsString_to_wxString ( nsString ( dialogTitle ), wxConvLocal );

	if ( text )
		message = nsString_to_wxString ( nsString ( text ), wxConvLocal );

	wxString* choices = NULL;
	int counter;
	for ( counter = 0; counter < count; counter++ )
	{
		choices[counter] = nsString_to_wxString ( nsString ( selectList[counter] ), wxConvLocal );
	}

	wxMozillaBrowser* Moz = BrowserForDOMWindow ( parent );
	if ( Moz )
	{
		wxSingleChoiceDialog mydialog ( Moz, message, title, ( int ) count, choices );
		dlgResult = mydialog.ShowModal();
		if ( dlgResult == wxID_OK )
		{
			*_retval = PR_TRUE;
			*outSelection = mydialog.GetSelection();
			//KO: hopefully both Mozilla and wxWindows count items the same (i.e. 0 or 1-based)
			//nsIPromptService.h doesn't really say what way it needs to be, so I'm just assuming this
			//is correct for now.

			//I'm not even sure under what situation this dialog would appear! =)
		}
		else
		{
			*_retval = PR_FALSE;
		}
	}
	return NS_OK;
	//return NS_ERROR_NOT_IMPLEMENTED;
}

class CPromptServiceFactory : public nsIFactory
{
	public:
		NS_DECL_ISUPPORTS
		NS_DECL_NSIFACTORY

		CPromptServiceFactory();
		virtual ~CPromptServiceFactory();
};

//*****************************************************************************

NS_IMPL_ISUPPORTS1 ( CPromptServiceFactory, nsIFactory )

CPromptServiceFactory::CPromptServiceFactory()
{
}

CPromptServiceFactory::~CPromptServiceFactory()
{
}

NS_IMETHODIMP CPromptServiceFactory::CreateInstance ( nsISupports *aOuter, const nsIID & aIID, void **aResult )
{
	NS_ENSURE_ARG_POINTER ( aResult );

	*aResult = NULL;
	wxMozillaDialogs *inst = new wxMozillaDialogs;
	if ( !inst )
		return NS_ERROR_OUT_OF_MEMORY;

	nsresult rv = inst->QueryInterface ( aIID, aResult );
	if ( rv != NS_OK )
	{
		// We didn't get the right interface, so clean up
		delete inst;
	}

	return rv;
}

NS_IMETHODIMP CPromptServiceFactory::LockFactory ( PRBool lock )
{
	return NS_OK;
}

//*****************************************************************************

nsresult NS_NewPromptServiceFactory ( nsIFactory** aFactory )
{
	NS_ENSURE_ARG_POINTER ( aFactory );
	*aFactory = nsnull;

	CPromptServiceFactory *result = new CPromptServiceFactory;
	if ( !result )
		return NS_ERROR_OUT_OF_MEMORY;

	NS_ADDREF ( result );
	*aFactory = result;

	return NS_OK;
}