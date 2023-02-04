
/* File : classes.i */
%module classes

%{
#include "classes.h"
%}
  
class Vector {
public:
        double x,y,z;
        Vector( double iX, double iY, double iZ );
        ~Vector();
        double len2();
		double	len();
		double	magnitude();
};


Vector getVec( double iX, double iY, double iZ );
Vector* getVecPtr( double iX, double iY, double iZ );


