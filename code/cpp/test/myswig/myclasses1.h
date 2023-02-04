#ifndef _MY_CLASSES1_H_
#define _MY_CLASSES1_H_


class Vector {
public:
	double x,y,z;
	Vector( double  iX, double iY, double iZ );
	~Vector();
	double	len2();
//		void	print() {}
};


void 	list_functions();
void	startWx();


#endif //_MY_CLASSES1_H_


