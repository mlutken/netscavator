
/* File : myclasses1.i */
%module myclasses1

%{
#include "myclasses1.h"
%}
  
class Vector {
public:
        double x,y,z;
        Vector( double iX, double iY, double iZ );
        ~Vector();
        double len2();
};

void 	list_functions();
void	startWx();


