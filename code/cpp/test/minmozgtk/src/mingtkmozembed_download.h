/* ***** BEGIN LICENSE BLOCK *****
 * Version: MPL 1.1/GPL 2.0/LGPL 2.1
 *
 * The contents of this file are subject to the Mozilla Public License Version
 * 1.1 (the "License"); you may not use this file except in compliance with
 * the License. You may obtain a copy of the License at
 * http://www.mozilla.org/MPL/
 *
 * Software distributed under the License is distributed on an "AS IS" basis,
 * WITHOUT WARRANTY OF ANY KIND, either express or implied. See the License
 * for the specific language governing rights and limitations under the
 * License.
 *
 * The Original Code is mozilla.org code.
 *
 * The Initial Developer of the Original Code is
 * Christopher Blizzard.
 * Portions created by the Initial Developer are Copyright (C) 2001
 * the Initial Developer. All Rights Reserved.
 *
 * Contributor(s):
 *   Christopher Blizzard <blizzard@mozilla.org>
 *   Ramiro Estrugo <ramiro@eazel.com>
 *
 * Alternatively, the contents of this file may be used under the terms of
 * either the GNU General Public License Version 2 or later (the "GPL"), or
 * the GNU Lesser General Public License Version 2.1 or later (the "LGPL"),
 * in which case the provisions of the GPL or the LGPL are applicable instead
 * of those above. If you wish to allow use of your version of this file only
 * under the terms of either the GPL or the LGPL, and not to allow others to
 * use your version of this file under the terms of the MPL, indicate your
 * decision by deleting the provisions above and replace them with the notice
 * and other provisions required by the GPL or the LGPL. If you do not delete
 * the provisions above, a recipient may use your version of this file under
 * the terms of any one of the MPL, the GPL or the LGPL.
 *
 * ***** END LICENSE BLOCK ***** */

#ifndef mingtkmozembed_download_h
#define mingtkmozembed_download_h
#ifdef __cplusplus
extern "C" {
#endif /* __cplusplus */
#include <stddef.h>
#include <gtk/gtk.h>
#ifdef MOZILLA_CLIENT
#include "nscore.h"
#else // MOZILLA_CLIENT
#ifndef nscore_h__
/* Because this header may be included from files which not part of the mozilla
   build system, define macros from nscore.h */
#if (__GNUC__ >= 4) || (__GNUC__ == 3 && __GNUC_MINOR__ >= 3)
#define NS_HIDDEN __attribute__((visibility("hidden")))
#else
#define NS_HIDDEN
#endif
#define NS_FROZENCALL
#define NS_EXPORT_(type) type
#define NS_IMPORT_(type) type
#endif // nscore_h__
#endif // MOZILLA_CLIENT
#ifdef XPCOM_GLUE
#define MINGTKMOZEMBED_API(type, name, params) \
  typedef type (NS_FROZENCALL * name##Type) params; \
  extern name##Type name NS_HIDDEN;
#else // XPCOM_GLUE
#ifdef _IMPL_MINGTKMOZEMBED
#define GTKMOZEMBED_API(type, name, params) NS_EXPORT_(type) name params;
#else
#define GTKMOZEMBED_API(type,name, params) NS_IMPORT_(type) name params;
#endif
#endif // XPCOM_GLUE

#define MINGTK_TYPE_MOZ_EMBED_DOWNLOAD             (gtk_moz_embed_download_get_type())
#define MINGTK_MOZ_EMBED_DOWNLOAD(obj)             GTK_CHECK_CAST((obj), MINGTK_TYPE_MOZ_EMBED_DOWNLOAD, MinGtkMozEmbedDownload)
#define MINGTK_MOZ_EMBED_DOWNLOAD_CLASS(klass)     GTK_CHECK_CLASS_CAST((klass), MINGTK_TYPE_MOZ_EMBED_DOWNLOAD, MinGtkMozEmbedDownloadClass)
#define MINGTK_IS_MOZ_EMBED_DOWNLOAD(obj)          GTK_CHECK_TYPE((obj), MINGTK_TYPE_MOZ_EMBED_DOWNLOAD)
#define MINGTK_IS_MOZ_EMBED_DOWNLOAD_CLASS(klass)  GTK_CHECK_CLASS_TYPE((klass), MINGTK_TYPE_MOZ_EMBED_DOWNLOAD)

typedef struct _MinGtkMozEmbedDownload      MinGtkMozEmbedDownload;
typedef struct _MinGtkMozEmbedDownloadClass MinGtkMozEmbedDownloadClass;

struct _MinGtkMozEmbedDownload
{
  GtkObject  object;
  void *data;
};

struct _MinGtkMozEmbedDownloadClass
{
  GtkObjectClass parent_class;
  void (*started) (MinGtkMozEmbedDownload* item, gchar **file_name_with_path);
  void (*completed) (MinGtkMozEmbedDownload* item);
  void (*error) (MinGtkMozEmbedDownload* item);
  void (*aborted) (MinGtkMozEmbedDownload* item);
  void (*progress) (MinGtkMozEmbedDownload* item, gulong downloaded_bytes, gulong total_bytes, gdouble kbps);
};

typedef enum
{
  MINGTK_MOZ_EMBED_DOWNLOAD_RESUME,
  MINGTK_MOZ_EMBED_DOWNLOAD_CANCEL,
  MINGTK_MOZ_EMBED_DOWNLOAD_PAUSE,
  MINGTK_MOZ_EMBED_DOWNLOAD_RELOAD,
  MINGTK_MOZ_EMBED_DOWNLOAD_STORE,
  MINGTK_MOZ_EMBED_DOWNLOAD_RESTORE
} MinGtkMozEmbedDownloadActions;

GTKMOZEMBED_API(GtkType,      gtk_moz_embed_download_get_type,           (void))
GTKMOZEMBED_API(GtkObject *,  gtk_moz_embed_download_new,                (void))
GTKMOZEMBED_API(GtkObject *,  gtk_moz_embed_download_get_latest_object,  (void))
GTKMOZEMBED_API(void,         gtk_moz_embed_download_do_command,         (MinGtkMozEmbedDownload *item, guint command))
GTKMOZEMBED_API(void,         gtk_moz_embed_download_do_command,         (MinGtkMozEmbedDownload *item, guint command))
GTKMOZEMBED_API(void,         gtk_moz_embed_download_do_command,         (MinGtkMozEmbedDownload *item, guint command))
GTKMOZEMBED_API(void,         gtk_moz_embed_download_do_command,         (MinGtkMozEmbedDownload *item, guint command))
GTKMOZEMBED_API(gchar*,       gtk_moz_embed_download_get_file_name,      (MinGtkMozEmbedDownload *item))
GTKMOZEMBED_API(gchar*,       gtk_moz_embed_download_get_url,            (MinGtkMozEmbedDownload *item))
GTKMOZEMBED_API(glong,        gtk_moz_embed_download_get_progress,       (MinGtkMozEmbedDownload *item))
GTKMOZEMBED_API(glong,        gtk_moz_embed_download_get_file_size,      (MinGtkMozEmbedDownload *item))
#ifdef __cplusplus
}
#endif /* __cplusplus */
#endif /* mingtkmozembed_download_h */
