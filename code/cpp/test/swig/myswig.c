/* File : myswig.c */

double  Swig_variable   = 5.0;

/* Compute factorial of n */
int Swig_fact ( int n )
{
	if ( n <= 1 ) return 1;
	else return n*Swig_fact ( n-1 );
}

/* Compute n mod m */
int Swig_div ( int n, int m )
{
	return ( n / m );
}

