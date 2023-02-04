/*
 * DO NOT EDIT.  THIS FILE IS GENERATED FROM ./ISpecialThing.idl
 */

#ifndef __gen_ISpecialThing_h__
#define __gen_ISpecialThing_h__


#ifndef __gen_nsISupports_h__
#include "nsISupports.h"
#endif

/* For IDL files that don't want to include root IDL files. */
#ifndef NS_NO_VTABLE
#define NS_NO_VTABLE
#endif

/* starting interface:    ISpecialThing */
#define ISPECIALTHING_IID_STR "263ed1ba-5cc1-11db-9673-00e08161165f"

#define ISPECIALTHING_IID \
  {0x263ed1ba, 0x5cc1, 0x11db, \
    { 0x96, 0x73, 0x00, 0xe0, 0x81, 0x61, 0x16, 0x5f }}

class NS_NO_VTABLE NS_SCRIPTABLE ISpecialThing : public nsISupports {
 public: 

  NS_DECLARE_STATIC_IID_ACCESSOR(ISPECIALTHING_IID)

  /* attribute AString name; */
  NS_SCRIPTABLE NS_IMETHOD GetName(nsAString & aName) = 0;
  NS_SCRIPTABLE NS_IMETHOD SetName(const nsAString & aName) = 0;

  /* void init (in AString xulWindow, in AString browserId); */
  NS_SCRIPTABLE NS_IMETHOD Init(const nsAString & xulWindow, const nsAString & browserId) = 0;

  /* long add (in long a, in long b); */
  NS_SCRIPTABLE NS_IMETHOD Add(PRInt32 a, PRInt32 b, PRInt32 *_retval NS_OUTPARAM) = 0;

  /* void dbgPrint (in AString str); */
  NS_SCRIPTABLE NS_IMETHOD DbgPrint(const nsAString & str) = 0;

};

  NS_DEFINE_STATIC_IID_ACCESSOR(ISpecialThing, ISPECIALTHING_IID)

/* Use this macro when declaring classes that implement this interface. */
#define NS_DECL_ISPECIALTHING \
  NS_SCRIPTABLE NS_IMETHOD GetName(nsAString & aName); \
  NS_SCRIPTABLE NS_IMETHOD SetName(const nsAString & aName); \
  NS_SCRIPTABLE NS_IMETHOD Init(const nsAString & xulWindow, const nsAString & browserId); \
  NS_SCRIPTABLE NS_IMETHOD Add(PRInt32 a, PRInt32 b, PRInt32 *_retval NS_OUTPARAM); \
  NS_SCRIPTABLE NS_IMETHOD DbgPrint(const nsAString & str); 

/* Use this macro to declare functions that forward the behavior of this interface to another object. */
#define NS_FORWARD_ISPECIALTHING(_to) \
  NS_SCRIPTABLE NS_IMETHOD GetName(nsAString & aName) { return _to GetName(aName); } \
  NS_SCRIPTABLE NS_IMETHOD SetName(const nsAString & aName) { return _to SetName(aName); } \
  NS_SCRIPTABLE NS_IMETHOD Init(const nsAString & xulWindow, const nsAString & browserId) { return _to Init(xulWindow, browserId); } \
  NS_SCRIPTABLE NS_IMETHOD Add(PRInt32 a, PRInt32 b, PRInt32 *_retval NS_OUTPARAM) { return _to Add(a, b, _retval); } \
  NS_SCRIPTABLE NS_IMETHOD DbgPrint(const nsAString & str) { return _to DbgPrint(str); } 

/* Use this macro to declare functions that forward the behavior of this interface to another object in a safe way. */
#define NS_FORWARD_SAFE_ISPECIALTHING(_to) \
  NS_SCRIPTABLE NS_IMETHOD GetName(nsAString & aName) { return !_to ? NS_ERROR_NULL_POINTER : _to->GetName(aName); } \
  NS_SCRIPTABLE NS_IMETHOD SetName(const nsAString & aName) { return !_to ? NS_ERROR_NULL_POINTER : _to->SetName(aName); } \
  NS_SCRIPTABLE NS_IMETHOD Init(const nsAString & xulWindow, const nsAString & browserId) { return !_to ? NS_ERROR_NULL_POINTER : _to->Init(xulWindow, browserId); } \
  NS_SCRIPTABLE NS_IMETHOD Add(PRInt32 a, PRInt32 b, PRInt32 *_retval NS_OUTPARAM) { return !_to ? NS_ERROR_NULL_POINTER : _to->Add(a, b, _retval); } \
  NS_SCRIPTABLE NS_IMETHOD DbgPrint(const nsAString & str) { return !_to ? NS_ERROR_NULL_POINTER : _to->DbgPrint(str); } 

#if 0
/* Use the code below as a template for the implementation class for this interface. */

/* Header file */
class _MYCLASS_ : public ISpecialThing
{
public:
  NS_DECL_ISUPPORTS
  NS_DECL_ISPECIALTHING

  _MYCLASS_();

private:
  ~_MYCLASS_();

protected:
  /* additional members */
};

/* Implementation file */
NS_IMPL_ISUPPORTS1(_MYCLASS_, ISpecialThing)

_MYCLASS_::_MYCLASS_()
{
  /* member initializers and constructor code */
}

_MYCLASS_::~_MYCLASS_()
{
  /* destructor code */
}

/* attribute AString name; */
NS_IMETHODIMP _MYCLASS_::GetName(nsAString & aName)
{
    return NS_ERROR_NOT_IMPLEMENTED;
}
NS_IMETHODIMP _MYCLASS_::SetName(const nsAString & aName)
{
    return NS_ERROR_NOT_IMPLEMENTED;
}

/* void init (in AString xulWindow, in AString browserId); */
NS_IMETHODIMP _MYCLASS_::Init(const nsAString & xulWindow, const nsAString & browserId)
{
    return NS_ERROR_NOT_IMPLEMENTED;
}

/* long add (in long a, in long b); */
NS_IMETHODIMP _MYCLASS_::Add(PRInt32 a, PRInt32 b, PRInt32 *_retval NS_OUTPARAM)
{
    return NS_ERROR_NOT_IMPLEMENTED;
}

/* void dbgPrint (in AString str); */
NS_IMETHODIMP _MYCLASS_::DbgPrint(const nsAString & str)
{
    return NS_ERROR_NOT_IMPLEMENTED;
}

/* End of implementation class template. */
#endif


#endif /* __gen_ISpecialThing_h__ */
