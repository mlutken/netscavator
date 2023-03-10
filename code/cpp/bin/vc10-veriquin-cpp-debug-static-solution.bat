echo off
SET SAVE_DIR_VERIQUIN_CREATE-VS100-DBG=%CD%
call "%VS100COMNTOOLS%"\vsvars32.bat

IF not "%VERIQUIN_CPP_DIR_BACKSLASH%" == ""  GOTO VERIQUIN_CPP_DIR_SET
cd ..
SET VERIQUIN_CPP_DIR_BACKSLASH=%CD%
chdir /d %SAVE_DIR_VERIQUIN_CREATE-VS100-DBG%

:VERIQUIN_CPP_DIR_SET
echo Generating Veriquin CPP code VS100 debug static solution ...
chdir /d %VERIQUIN_CPP_DIR_BACKSLASH%

SET BUILD_DIR=build_cbs\vc10_debug_static
mkdir  %BUILD_DIR%
chdir %BUILD_DIR%
cmake -D CMAKE_BUILD_TYPE:STRING=Debug -D CBS_BUILD=ON -D CBS_LIB_TYPE_TO_BUILD:STRING=STATIC -G "Visual Studio 10" ../..

chdir /d %SAVE_DIR_VERIQUIN_CREATE-VS100-DBG%

