#include "scriptcrawl_module_cpp.h"

#include <stdio.h>
#include <iostream>
#include <string>

using namespace std;

void dbgSimpleTestFunction()
{
    cout << "dbgSimpleTestFunction()" << endl;
}

void dbgIntParam(int i)
{
    printf("dbgIntParam('%d')\n", i );
}


void dbgCurrentMinerSetPointer(const std::string& sMinerPointer)
{
    std::string s = "Halloo";
    printf("dbgCurrentMinerSetPointer('%s')\n", sMinerPointer.c_str() );

}



void runMiners( )
{
    printf("runMiners\n");
//    char*  szArgv[2] = { "", "" };
//    int iArgc = 1;
//    wxEntry( iArgc, &szArgv[0] );
}
