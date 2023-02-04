#include "MyComponent.h"

NS_IMPL_ISUPPORTS1(MyComponent, IMyComponent)

MyComponent::MyComponent()
{
  /* member initializers and constructor code */
}

MyComponent::~MyComponent()
{
  /* destructor code */
}

/* long Add (in long a, in long b); */
NS_IMETHODIMP MyComponent::Add(PRInt32 a, PRInt32 b, PRInt32 *_retval)
{
	*_retval = a + b;
	return NS_OK;
}

