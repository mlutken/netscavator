
/* File : myclass.i */
%module myclass

%{
#include "myclass.h"
%}

class Vector {
public:
        double x,y,z;
        Vector();
        ~Vector();
        double magnitude2();
};

void	callCallback( const char* szCallBack );
void	callMemberCallback( void* pClassObj,  const char* szCallBack );



