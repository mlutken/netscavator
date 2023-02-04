#ifndef _MY_COMPONENT_H_
#define _MY_COMPONENT_H_

#include "IMyComponent.h"

#define MY_COMPONENT_CONTRACTID "@mydomain.com/XPCOMSample/MyComponent;1"
#define MY_COMPONENT_CLASSNAME "A Simple XPCOM Sample"
#define MY_COMPONENT_CID  { 0x597a60b0, 0x5272, 0x4284, { 0x90, 0xf6, 0xe9, 0x6c, 0x24, 0x2d, 0x74, 0x6 } }

/* Header file */
class MyComponent : public IMyComponent
{
public:
  NS_DECL_ISUPPORTS
  NS_DECL_IMYCOMPONENT

  MyComponent();
  virtual ~MyComponent();
  /* additional members */
};


#endif //_MY_COMPONENT_H_
