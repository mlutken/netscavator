
#include <math.h>
#include <iostream>

#include "classes.h"
 
Vector::Vector( double  iX, double iY, double iZ )
	: x(iX), y(iY), z(iZ)
{
	std::cout << "Vector CONSTRUCTOR: " << x << ", " << y << ", " << z << std::endl;
}

Vector::~Vector()
{
	std::cout << "Vector DESTRUCTOR" << std::endl;
}
 
double
Vector::len2() 
{ 
	return x*x + y*y + z*z; 
}

double
Vector::len() 
{ 
	return sqrt(x*x + y*y + z*z); 
}

double
Vector::magnitude() 
{ 
	return sqrt(x*x + y*y + z*z); 
}


Vector getVec( double iX, double iY, double iZ )
{
	return Vector( iX, iY, iZ );
}

Vector* getVecPtr( double iX, double iY, double iZ )
{
	return new Vector ( iX, iY, iZ );
}
