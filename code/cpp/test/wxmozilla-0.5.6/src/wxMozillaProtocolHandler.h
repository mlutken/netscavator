#ifndef __WX_MOZILLA_PROTOCOLS_H__
#define __WX_MOZILLA_PROTOCOLS_H__

/**
 *  This program is free software; you can redistribute it and/or modify
 *  it under the terms of the GNU General Public License as published by
 *  the Free Software Foundation; either version 2 of the License, or
 *  (at your option) any later version.
 *
 *  This program is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *  GNU Library General Public License for more details.
 *
 *  You should have received a copy of the GNU General Public License
 *  along with this program; if not, write to the Free Software
 *  Foundation, Inc., 59 Temple Place - Suite 330, Boston, MA 02111-1307, USA.
 */


/***************************************************************************
                          wxMozillaProtocolHandler.hpp
                             -------------------
    begin                : Jan 2003, 27
    copyright            : (C) 2002-2004 by David Teller
    email                : Yoric@users.sourceforge.net
    project              : OpenBERG (ported to wxMozilla)
 ***************************************************************************/

/***************************************************************************
 *                                                                         *
 *   This program is free software; you can redistribute it and/or modify  *
 *   it under the terms of the GNU General Public License as published by  *
 *   the Free Software Foundation; either version 2 of the License, or     *
 *   (at your option) any later version.                                   *
 *                                                                         *
 ***************************************************************************/

//wxWindows
#include "wx/stream.h"
#include "wx/string.h"
#include "wx/filesys.h"

//wxMozilla
#include "helpers.h"
#include "wxMozillaComponents.h"

/**
 * @file Custom protocol handlers.
 *
 * The interfaces and macros to define custom protocol handlers using
 * wxWindows libraries rather than renderer-specific libraries.
 *
 * We do not add all wxWindows' protocol handlers automatically because this
 * could lead to severe security flaws (for example by using the memory stream
 * reader protocol).
 *
 * @author David Teller
 * @date 12-19-2002
 *
 * @date 03-03-2003 Working
 * @date 02-29-2003 API reworked
 */



/**
 * The mime type for unknown content
 */
static const wxString UNKNOWN_CONTENT_TYPE = wxT ( "unknown/unknown" );
/**
 * The unknown charset type.
 */
static const wxString UNKNOWN_CHARSET      = wxT ( "" );

/**
 * A Channel for a protocol.
 *
 * A Channel is basically <b>one</b> stream plus some meta information (mostly encoding and mime type).
 */
class wxProtocolChannel
{
	public:
		/**
		 * Returns the stream for this channel.
		 *
		 * @return a (possibly null) stream for this channel. It should <b>not</b> be destroyed by the caller.
		 */
		virtual wxInputStream* GetStream() = 0;
		/**
		 * Returns the content type of the last opened stream.
		 *
		 * If the content type is unknown, return UNKNOWN_CONTENT_TYPE ("unknown/unknown")
		 *
		 * @return a non-empty content type as a mime type ("text/html", for example)
		 */
		virtual wxString GetContentType() = 0;
		/**
		 * Returns the charset of the last opened stream.
		 *
		 * @return a (possibly empty) charset
		 */
		virtual wxString GetCharset() = 0;
		/**
		 * Destructor.
		 *
		 * Should clean up the stream as well as any other information.
		 */
		virtual ~wxProtocolChannel() {};
};



/**
 * An abstract class to represent protocol handlers.
 *
 * The implementation of a protocol handler goes through several steps :
 * = subclassing the ProtocolChannel class
 * = subclassing the ProtocolHandler class to create objects of the appropriate ProtocolChannel class
 * = calling Register()
 */
class wxProtocolHandler
{
	public:
		/**
		 * Build an abstract protocol handler.
		 *
		 * @param scheme The scheme for this protocol (eg "html", "ftp", ...)
		 */
		wxProtocolHandler ( const wxString scheme );
		virtual ~wxProtocolHandler();
	public:
		/**
		 * Returns the scheme for this protocol
		 *
		 * @return the scheme for this protocol ("html", "ftp", ...)
		 */
		const wxString GetScheme();
		/**
		 * Returns the default port for connexion.
		 *
		 * @return a positive integer or -1 if this has no meaning
		 */
		virtual int GetDefaultPort();
		/**
		 * Create an appropriate URI for this protocol.
		 *
		 * @param spec the new, possibly empty, possibly relative uri.
		 * @param base the current, possibly empty, absolute uri.
		 */
		virtual const wxString NewURI ( const wxString spec, const wxString base ) = 0;
		/**
		 * Open a channel, for consultation of the protocol.
		 *
		 * Implementations of this method should be thread-safe.
		 *
		 * @param uri The valid uri for this channel.
		 *
		 * @return null if the uri was not valid, a non-null OpenChannel if it was valid.
		 */
		virtual wxProtocolChannel* OpenChannel ( const wxString uri ) = 0;
	public:
		virtual bool IsStd() const;
		virtual bool IsNoRelative() const;
		virtual bool IsNoAuthorityComponent() const;
		virtual bool IsAllowedProxy() const;
		virtual bool IsAllowedProxyHTTP() const;
		virtual bool IsAllowedPort ( int port, const wxString scheme );
	public:
		const wxString mScheme;
};

#if wxUSE_FILESYSTEM
/**
 * A protocol handler based on wxWindows' virtual file systems.
 *
 * Since wxWindows seems to support semi-dynamic addition of
 * protocols, FSProtocolHandler should be instanciated separately
 * for each scheme.
 *
 * @warning Be <b>very</b> careful when using this : carefully chosen
 * @warning nested URIs might represent severe security flaws !
 */
class wxFSProtocolHandler : public wxProtocolHandler
{
	public:
		/**
		 * Instanciate the FS protocol handler for a given scheme.
		 *
		 * This is only an instanciation. Not a registration. You
		 * <b>must</b> call or emulate REGISTER_CUSTOM_PROTOCOL_HANDLER to
		 * register this protocol handler.
		 */
		wxFSProtocolHandler ( const wxString scheme );
		virtual const wxString NewURI ( const wxString spec, const wxString base );
		virtual wxProtocolChannel* OpenChannel ( const wxString uri );

	private:
		/**
		 * An instance of the wxFileSystem shared between protocol handlers.
		 *
		 * @todo YORIC: I have not checked yet whether this is MT-Safe !
		 */
		static wxFileSystem ms_fsys;
};
#endif // wxUSE_FILESYSTEM

/**
 * A callback to create new instances of the protocol handler class.
 *
 * It can answer NULL.
 */

typedef wxProtocolHandler* ( wxProtocolHandlerFactory ) ( const wxString scheme );
/**
 * Registers a class of protocol handlers.
 *
 * @param name A unique name for the protocol handler. Used for hashing and debugging.
 * @param scheme The scheme for which to register the handler.
 * @param factory A callback to create new instances of the protocol handler class.
 *
 * @return true in case of success, false otherwise
 */
bool wxRegisterProtocolHandler ( const wxString name, const wxString scheme, const wxUId id, wxProtocolHandlerFactory factory );

#endif
