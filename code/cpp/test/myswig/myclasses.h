#ifndef _MY_CLASSES_H_
#define _MY_CLASSES_H_

#define USE_WX_EXAMPLE

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

void	callCallback( const char* szCallBack );
void 	list_functions();
void 	list_classes();
void	startWx();


#endif //_MY_CLASSES_H_


