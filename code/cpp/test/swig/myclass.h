#ifndef _MY_CLASS_H_
#define _MY_CLASS_H_


class Vector {
public:
        double x,y,z;
        Vector();
        ~Vector();
		double	magnitude2();
//		void	print() {}
};

void	callCallback( const char* szCallBack );
void	callMemberCallback( void* pClassObj,  const char* szCallBack );


#endif //_MY_CLASS_H_


