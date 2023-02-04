#ifndef _INTERFACES_BROWSER_IF_H_
#define _INTERFACES_BROWSER_IF_H_

#include <string>
#include <vector>
#include <boost/shared_ptr.hpp>

namespace crawl {

class LinearDomIF;



class BrowserIF  {
public: 
	// ------------------------------------------------
    // ---  ---
	// ------------------------------------------------
    virtual ~BrowserIF() {};

	
    boost::shared_ptr<LinearDomIF>           createLinearDom() const
    { return do_createLinearDom(); }
	

private:
    virtual boost::shared_ptr<LinearDomIF>   do_createLinearDom() const
    { return boost::shared_ptr<LinearDomIF>(); }

	
};


} // END namespace crawl

#endif /* _INTERFACES_BROWSER_IF_H_ */
