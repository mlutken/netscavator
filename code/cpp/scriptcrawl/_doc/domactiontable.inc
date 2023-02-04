!!Dom built-in actions overview 
|click| Do simple (left) click on current element
|mouseEvent| Send named mouseevent to current element. See below table for events
|loadUrl| Load the url specified in \a sParam1
|inputValue| Input the value specified in \a sParam1 into current INPUT element
|formSubmit| Assuming current dom element is a FORM, do a submit.
|formReset| Assuming current dom element is a FORM, do a reset of the form
|selectIndex| Assuming current dom element is a SELECT, do select index specifie in \a sParam1
|selectOption| Assuming current dom element is an OPTION, do select this option

!Dom event names
Events
    Covers all event types.
HTMLEvents
    Covers 'abort', 'blur', 'change', 'error', 'focus', 'load', 'reset', 'resize', 
    'scroll', 'select', 'submit', and 'unload'.
UIEvents
    Covers 'DOMActivate', 'DOMFocusIn', 'DOMFocusOut', 
    and (since they do not have their own key events module in DOM 2) it also covers 'keydown', 
    'keypress', and 'keyup'. 
    Also indirectly covers MouseEvents.
MouseEvents
    Covers 'click', 'mousedown', 'mousemove', 'mouseout', 'mouseover', and 'mouseup'.
MutationEvents
    Covers 'DOMAttrModified', 'DOMNodeInserted', 'DOMNodeRemoved', 'DOMCharacterDataModified', 
    'DOMNodeInsertedIntoDocument', 'DOMNodeRemovedFromDocument', and 'DOMSubtreeModified'.
