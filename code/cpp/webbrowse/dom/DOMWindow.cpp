#include "DOMWindow.h"

#include <stdio.h>
#include <nsIScriptGlobalObjectOwner.h>
#include <nsIInterfaceRequestorUtils.h>
#include <nsIScriptContext.h>
#include <nsIScriptGlobalObject.h>

#include <dom/ScriptContext.h>
#include "DOMBarProp.h"
#include "DOMWindowCollection.h"
#include "Selection.h"

// ------------------------------------------------
// --- Methods beyond W3C/Mozilla specification ---	
// ------------------------------------------------

boost::shared_ptr<ScriptContext>	
DOMWindow::getScriptContext()
{
	nsCOMPtr<nsIScriptGlobalObject> pIScriptGlobalObject( do_GetInterface(this->ifMoz()) );	// VIRKER	
	nsCOMPtr<nsIScriptContext> pIScriptContext ( pIScriptGlobalObject->GetContext() );	// VIRKER ogs�. Ser det ud til!
	if ( ! pIScriptContext )
	{
		printf("ERROR DOMWindow::getScriptContext\n");
		//return boost::shared_ptr<ScriptContext>( new ScriptContext(0));
	}
	
	return boost::shared_ptr<ScriptContext>( new ScriptContext(pIScriptContext));
}


/** Access for this window's scrollbars (readonly).
Accessor for the object that controls whether or not scrollbars
are shown in this window. */
boost::shared_ptr<DOMBarProp>	
DOMWindow::scrollbars() const
{	
	MOZ_IF_RETURN_MOZ(GetScrollbars,DOMBarProp);	
}


/** Accessor for the child windows in this window. */
/* [noscript] readonly attribute nsIDOMWindowCollection frames; */
//GetFrames(nsIDOMWindowCollection * *aFrames) = 0;
boost::shared_ptr<DOMWindowCollection>	
DOMWindow::frames() const
{
	MOZ_IF_RETURN_MOZ(GetFrames,DOMWindowCollection);	
}


/// Method for accessing this window's selection object.
/* nsISelection getSelection (); */
//    GetSelection(nsISelection **_retval) = 0;
boost::shared_ptr<Selection>	
DOMWindow::getSelection() const
{
	MOZ_IF_RETURN_MOZ(GetSelection,Selection);	
}
