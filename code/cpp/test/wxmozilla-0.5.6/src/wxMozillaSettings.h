#ifndef __WX_MOZILLA_SETTINGS_H__
#define __WX_MOZILLA_SETTINGS_H__

/* wxwindow includes */
#include "wx/defs.h"
#include "wx/string.h"

class wxMozillaSettingsData;
class wxMozillaBrowser;
class nsIPrefBranch;

class wxMozillaSettings
{
	public:
		static bool SetProfilePath ( const wxString &path );
		static wxString GetProfilePath() { return ms_profilePath; }

		static void SetMozillaPath ( const wxString &path );
		static wxString GetMozillaPath() { return ms_mozillaPath; }

		static void SetBoolPref ( const wxString& name, bool value );
		static bool GetBoolPref ( const wxString& name );
		static void SetStrPref ( const wxString& name, const wxString& value );
		static wxString GetStrPref ( const wxString& name );
		static void SetIntPref ( const wxString& name, int value );
		static int GetIntPref ( const wxString& name );

		static void SavePrefs();

	private:
		static nsIPrefBranch *GetPrefBranch();
		static void CleanUp();

		friend void wxMozillaShutdown();

		static wxMozillaSettingsData *ms_data;
		static wxString ms_profilePath, ms_mozillaPath;
};

#endif
