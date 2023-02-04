#ifndef _MOZ_BROWSER_QT_H_
#define _MOZ_BROWSER_QT_H_

#if WEBBROWSE_ENABLE_QT
//#include <hacks/qt_h_include_hack.h>
class QWidget;

#include "MozBrowser.h"


/** Toplevel (QtWidgets) browser class. */
class MozBrowserQt : public MozBrowser {
public:
	typedef boost::shared_ptr<MozBrowserQt> 	Ptr;		///< Pointer to a MozBrowserQt
	

	MozBrowserQt ( );
	MozBrowserQt ( boost::shared_ptr<WebBrowser> pWebBrowser );
	MozBrowserQt ( QWidget* pGuiQt );
	MozBrowserQt ( boost::shared_ptr<WebBrowser> pWebBrowser, QWidget* pGuiQt );
	~MozBrowserQt ( );
	
	virtual std::string	typeName() const { return "MozBrowserQt"; } ;	 
	virtual void		refresh				()						;	 
	virtual void		show				()						;	 
	virtual void		hide				()						;	 
 	virtual void		sizeGet				(int& x, int& y	) const ;	 
 	virtual void		sizeSet				(int x, int y 	) 		;	 
 	virtual void		sendKeepActive 		()						;	 
 	virtual void		close 				(bool bForce) 			;	 
	virtual void		continuousTimerStart( int iMilisecs )		; 	 
	virtual void		oneShotTimerStart	( int iMilisecs )		; 	 
	virtual void		continuousTimerStop	( )						; 	 
	virtual void		oneShotTimerStop	( )						; 	 
	
	QWidget*				
	guiQt()	const							{	return m_pGuiQt;	}

private:
	QWidget*		m_pGuiQt;
	int				m_iKeepAxtiveX;
	int				m_iKeepAxtiveY;
};


#endif //#if WEBBROWSE_ENABLE_QT


#endif // _MOZ_BROWSER_QT_H_



