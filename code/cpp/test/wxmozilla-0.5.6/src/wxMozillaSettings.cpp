
#include <wx/wxprec.h>
#include <wx/filename.h>

#include "wxMozillaSettings.h"
#include "wxMozillaBrowser.h"

#include "nsStringAPI.h"
#include "nsCOMPtr.h"
#include "nsProfileDirServiceProvider.h"
#include "nsIPrefService.h"
#include "nsIPrefBranch.h"

class wxMozillaSettingsData
{
	public:
		~wxMozillaSettingsData();

#ifndef __WXMAC__
//There seems to be some extra library needed on OS X - until then skip OS X.
		nsCOMPtr<nsProfileDirServiceProvider> m_profileDirServiceProvider;
#endif
		nsCOMPtr<nsIPrefService> m_prefService;
		nsCOMPtr<nsIPrefBranch> m_prefBranch;
};

wxMozillaSettingsData::~wxMozillaSettingsData()
{
#ifndef __WXMAC__
	if ( m_profileDirServiceProvider )
	{
		m_profileDirServiceProvider->Shutdown();
		m_profileDirServiceProvider = nsnull;
	}
#endif
}


wxString wxMozillaSettings::ms_profilePath;
wxString wxMozillaSettings::ms_mozillaPath;
wxMozillaSettingsData *wxMozillaSettings::ms_data = NULL;


/**
 * Sets the path to Mozilla runtime directory. Must be called before
 * first instance of wxMozillaBrowser is created. By default, current directory
 * is used on Windows and the directory where Mozilla was during compilation
 * on Unix.
 *
 * @param path
 * 	Path to Mozilla runtime
 */
void wxMozillaSettings::SetMozillaPath ( const wxString &path )
{
	wxASSERT_MSG ( !wxMozillaBrowser::IsEmbeddingInitialized(),
	               _T ( "You must call SetMozillaPath before creating wxMozillaBrowser instance!" ) );

	wxFileName fn ( path );
	fn.MakeAbsolute();
	ms_mozillaPath = fn.GetFullPath();
}


/**
 * Sets the profile path for the browser. Profile path is directory where
 * Mozilla stores its settings. You should call this function as soon as
 * possible and set the path to directory specific to your application.
 * If you don't call the function, settings are discarded when the application
 * exits.
 *
 * @param path
 * 	Path in which to store profile information
 *
 * @return
 * 	true on success, false on failure.
 */
bool wxMozillaSettings::SetProfilePath ( const wxString &path )
{
	printf("ML: Error: wxMozillaSettings::SetProfilePath needs implementation\n");	
#if 0
//TODO: figure out what needs added on OS X to get this to compile!
#ifndef __WXMAC__
	wxFileName fn ( path );
	fn.MakeAbsolute();
	ms_profilePath = fn.GetFullPath();

	// If Mozilla wasn't loaded yet, postpone setting profile path:
	if ( !wxMozillaBrowser::IsEmbeddingInitialized() )
		return TRUE;

	if ( ms_data == NULL )
		ms_data = new wxMozillaSettingsData();

	nsresult rv;
	nsCOMPtr<nsILocalFile> dir;
	NS_NewNativeLocalFile ( nsDependentCString ( ms_profilePath.mb_str ( wxConvFile ) ),
	                        PR_TRUE,
	                        getter_AddRefs ( dir ) );
	if ( !dir )
		return FALSE;
	if ( !ms_data->m_profileDirServiceProvider )
	{
		NS_NewProfileDirServiceProvider ( PR_TRUE,
		                                  getter_AddRefs ( ms_data->m_profileDirServiceProvider ) );
		if ( !ms_data->m_profileDirServiceProvider )
			return FALSE;
		rv = ms_data->m_profileDirServiceProvider->Register();
		if ( NS_FAILED ( rv ) )
			return FALSE;
	}
	rv = ms_data->m_profileDirServiceProvider->SetProfileDir ( dir );
	if ( NS_FAILED ( rv ) )
		return FALSE;
	return TRUE;
#endif
#endif
}

static NS_DEFINE_CID ( kPrefServiceCID, NS_PREFSERVICE_CID );

/// Return nsIPrefBranch object and create it if we don't have it yet
nsIPrefBranch *wxMozillaSettings::GetPrefBranch()
{
	if ( !wxMozillaBrowser::EnsureEmbedding() )
		return NULL;

	if ( ms_data == NULL )
		ms_data = new wxMozillaSettingsData();
	if ( !ms_data->m_prefBranch )
	{
		ms_data->m_prefService = do_GetService ( kPrefServiceCID );
		ms_data->m_prefBranch = do_QueryInterface ( ms_data->m_prefService );
		// read default prefs files (prefs.js, user.js):
		ms_data->m_prefService->ReadUserPrefs ( nsnull );
	}
	wxASSERT_MSG ( ms_data->m_prefBranch, _T ( "failed to get nsIPrefBranch" ) );
	return ms_data->m_prefBranch;
}

#ifdef __WXDEBUG__
#define CHECK_PREF_TYPE(pref, name, type, msg) \
        PRInt32 ptype; \
        pref->GetPrefType(name.ToAscii(), &ptype); \
        wxASSERT_MSG( ptype == nsIPrefBranch::type, msg );
#else
#define CHECK_PREF_TYPE(pref, name, type, msg)
#endif

void wxMozillaSettings::SetBoolPref ( const wxString& name, bool value )
{
	nsIPrefBranch *p = GetPrefBranch();
	CHECK_PREF_TYPE ( p, name, PREF_BOOL, _T ( "preference not bool" ) )
	p->SetBoolPref ( name.ToAscii(), value );
}

void wxMozillaSettings::SetStrPref ( const wxString& name, const wxString& value )
{
	nsIPrefBranch *p = GetPrefBranch();
	CHECK_PREF_TYPE ( p, name, PREF_STRING, _T ( "preference not string" ) )
	p->SetCharPref ( name.ToAscii(), value.ToAscii() );
}

void wxMozillaSettings::SetIntPref ( const wxString& name, int value )
{
	nsIPrefBranch *p = GetPrefBranch();
	CHECK_PREF_TYPE ( p, name, PREF_INT, _T ( "preference not integer" ) )
	p->SetIntPref ( name.ToAscii(), value );
}

bool wxMozillaSettings::GetBoolPref ( const wxString& name )
{
	nsIPrefBranch *p = GetPrefBranch();
	CHECK_PREF_TYPE ( p, name, PREF_BOOL, _T ( "preference not bool" ) )
	PRBool val;
	p->GetBoolPref ( name.ToAscii(), &val );
	return val;
}

wxString wxMozillaSettings::GetStrPref ( const wxString& name )
{
	nsIPrefBranch *p = GetPrefBranch();
	CHECK_PREF_TYPE ( p, name, PREF_STRING, _T ( "preference not string" ) )
	char *val;
	p->GetCharPref ( name.ToAscii(), &val );
	return wxString::FromAscii ( val );
}

int wxMozillaSettings::GetIntPref ( const wxString& name )
{
	nsIPrefBranch *p = GetPrefBranch();
	CHECK_PREF_TYPE ( p, name, PREF_INT, _T ( "preference not integer" ) )
	int val;
	p->GetIntPref ( name.ToAscii(), &val );
	return val;
}

void wxMozillaSettings::SavePrefs()
{
	if ( ms_data && ms_data->m_prefService )
	{
		ms_data->m_prefService->SavePrefFile ( nsnull );
	}
}

void wxMozillaSettings::CleanUp()
{
	delete wxMozillaSettings::ms_data;
	wxMozillaSettings::ms_data = NULL;
}
