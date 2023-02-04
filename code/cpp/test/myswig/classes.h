#ifndef _CLASSES_H_
#define _CLASSES_H_


class Vector {
public:
	double x,y,z;
	Vector( double  iX, double iY, double iZ );
	~Vector();
	double	len2();
	double	len();
	double	magnitude();
//		void	print() {}
};

Vector getVec( double iX, double iY, double iZ );
Vector* getVecPtr( double iX, double iY, double iZ );

#endif //_CLASSES_H_


