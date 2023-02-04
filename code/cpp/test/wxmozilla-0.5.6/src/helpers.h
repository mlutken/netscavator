/*
 * wxWindows Mozilla Browser Component
 *
 * Developers:
 *  Jeremiah Cornelius McCarthy <jeremiah@whoop-ass.ca>
 *  Kevin Ollivier <kevino@tulane.edu>
 *  Dave Fancella <david.fancella@attbi.com>
 */

// Note: this is private header, to be included only by wxMozilla
//       implementation!

#ifndef __HELPERS_H__
#define __HELPERS_H__

#include <wx/string.h>
#include <mozilla-config.h>
#include <nsIURI.h>
#include <nsIID.h>

#include "wxMozillaComponents.h"
// ----------------------------------------------------------------------
// String conversion
// ----------------------------------------------------------------------

// Conversion functions to convert between Mozilla strings and wxString
//
// (there are two problems involved:
//    - Mozilla uses UCS-2, not wchar_t, we have to convert between them
//    - Mozilla doesn't use locale to convert between UCS-2 and 8bit string)

nsString wxString_to_nsString ( const wxString& s, wxMBConv& conv );
wxString nsString_to_wxString ( const nsString& s, wxMBConv& conv );

// ----------------------------
// URI conversion
// ----------------------------

/**
 * Convert a wxMozilla-style URI to a Mozilla-style URI
 *
 * @from the wxMozilla-style URI.
 * @return the equivalent Mozilla-style URI, as a nsIURI. It belongs to the caller.
 *
 * @author David Teller <Yoric@users.sourceforge.net>
 */
nsIURI* wxString_to_nsURI ( wxString from );
/**
 * Convert a Mozilla-style URI to a wxMozilla-style URI
 *
 * @from the Mozilla-style URI. It may be null.
 * @return the equivalent wxMozilla-style URI, as a wxString
 *
 * @author David Teller <Yoric@users.sourceforge.net>
 */
wxString nsURI_to_wxString ( nsIURI* from );

// ----------------------------------
// Unique Identifiers conversion
// ----------------------------------

/**
 * Converts a wxWindows-style unique identifier to a mozilla-style unique identifier
 */
nsID wxUId_to_nsID ( const wxUId& aID );

#endif
