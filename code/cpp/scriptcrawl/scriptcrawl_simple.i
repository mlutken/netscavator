
/* File : scripting.i */
%module scripting

%{
#include "scriptcrawl.h"
#include <string>
#include <vector>
#include <utils/string_compare_functions.h>
%}

%include "std_string.i"
%include "typemaps.i"


void        dbgSimpleTestFunction();
void        dbgIntParam(int i);
void        dbgCurrentMinerSetPointer(const std::string& sMinerPointer);

