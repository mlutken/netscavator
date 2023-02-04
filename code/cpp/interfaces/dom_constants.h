#ifndef _INTERFACES_DOM_CONSTANTS_H_
#define _INTERFACES_DOM_CONSTANTS_H_

#include <QEvent>

namespace crawl {



enum 	EMatchPos { MATCH_FIRST = 0, MATCH_LAST = 1	};


/// Enum for designating search direction in function findNearest().
enum ENearestDir	{	NEAREST_FORWARD 	= 1 << 0,			///< Search only forwards
						NEAREST_BACKWARD 	= 1 << 1, 			///< Search only backwards
						NEAREST_BOTH 		= 0x3, 				///< Search in both directions 
						NEAREST_THIS_NODE	= NEAREST_BOTH +1,	///< No seach at all. Expect node to be the current
						NEAREST_PARENT		= NEAREST_BOTH +2,	///< Find a parent node that matches (note:semi working currently)
						NEAREST_AUTO		= NEAREST_BOTH +3	///< Automatic search mode.
					};


enum EUrlLinkType {
      LINK_TYPE_LOCAL       = 1 << 0
    , LINK_TYPE_EXTERNAL    = 1 << 1
    , LINK_TYPE_ALL         = 3
    };


const int MOUSE_CLICK_EVENT = QEvent::MaxUser -1;

enum NetworkOperationType { NetworkRequestStart, NetworkRequestComplete, NetworkRequestCancelled, NetworkRequestFailed };

} // END namespace crawl


 



#endif //_INTERFACES_DOM_CONSTANTS_H_
