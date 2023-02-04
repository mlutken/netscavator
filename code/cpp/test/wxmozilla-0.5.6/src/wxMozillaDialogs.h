#ifndef __WX_MOZILLA_PROMPTS_H__
#define __WX_MOZILLA_PROMPTS_H__
/*
 * wxMozilla
 *
 * Developers:
 *  Jeremiah Cornelius McCarthy <jeremiah@whoop-ass.ca>
 *  Kevin Ollivier <kevino@tulane.edu>
 *  Dave Fancella <david.fancella@attbi.com>
 */

/* Overrides the Mozilla XUL-based dialogs */
#include "nsError.h"

class nsIFactory;

extern nsresult NS_NewPromptServiceFactory ( nsIFactory** aFactory );

#endif