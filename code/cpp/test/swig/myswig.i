
/* File : myswig.i */
%module myswig

%{
/* Put headers and other declarations here */
extern double Swig_variable;
extern int    Swig_fact(int);
extern int    Swig_div(int n, int m);
%}
extern double Swig_variable;
extern int    Swig_fact(int);
extern int    Swig_div(int n, int m);

