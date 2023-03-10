#ifndef __SPECIALTHING_IMPL_H__
#define __SPECIALTHING_IMPL_H__

#include "ISpecialThing.h"
#include "nsStringAPI.h"
#include <nsCOMPtr.h>
#include <nsIDOMEventListener.h>
#include <nsIDOMWindow.h>
#include <nsIHttpActivityObserver.h>


#define SPECIALTHING_CONTRACTID "@starkravingfinkle.org/specialthing;1"
#define SPECIALTHING_CLASSNAME "SpecialThing"
#define SPECIALTHING_CID { 0x245626, 0x5cc1, 0x11db, { 0x96, 0x73, 0x0, 0xe0, 0x81, 0x61, 0x16, 0x5f } }


class CSpecialThing :
            public ISpecialThing
        ,   public nsIDOMEventListener
{
public:
    NS_DECL_ISUPPORTS
    NS_DECL_ISPECIALTHING
    NS_DECL_NSIDOMEVENTLISTENER

    CSpecialThing();

    void            getBrowserQuestionForForum();
    void            getBrowserAnswerFromForum();

    void 			addHttpActivityObserver ( nsCOMPtr<nsIHttpActivityObserver>	pIHttpActivityObserver, bool bAllowCreateDefault = true );


private:
    ~CSpecialThing();
    bool                        m_bInitialized;
    nsCOMPtr<nsIDOMWindow>      m_pDomWinBrowser;
    nsCOMPtr<nsIDOMWindow>      m_pDomWinHtml;

protected:
    /* additional members */
    nsString mName;
    nsCOMPtr<nsIHttpActivityObserver>   m_pIHttpActivityObserver;

};

#endif
