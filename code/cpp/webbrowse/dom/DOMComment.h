#ifndef _WEBBROWSE_DOM_COMMENT_H_
#define _WEBBROWSE_DOM_COMMENT_H_


//#include <dom/nsIDOMComment.h>
#include <nsIDOMComment.h>

#include <dom/DOMCharacterData.h>

class DOMComment : public DOMCharacterData {
	MOZ_CONSTRUCT(DOMComment,DOMCharacterData);
public: 
};

#endif /* _WEBBROWSE_DOM_COMMENT_H_ */

