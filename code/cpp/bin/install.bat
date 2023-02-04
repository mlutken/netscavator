@echo off
SET SAVE_DIR_VERIQUIN_CPP_INSTALL=%CD%

set INPUT-VERIQUIN-CPP-ENVIRONMENT-VARS=y

SET /P INPUT-VERIQUIN-CPP-ENVIRONMENT-VARS=(2)  Install VERIQUIN_CPP environment variables [Y]/N : 

echo .
echo You chose:
echo VERIQUIN-CPP-ENVIRONMENT-VARS : %INPUT-VERIQUIN-CPP-ENVIRONMENT-VARS%
echo .
 
REM echo (1)  Running install in cpaf directory ...
REM cd ..\..\..\..\cpaf\bin\windows
REM call install.bat
REM chdir /d %SAVE_DIR_VERIQUIN_CPP_INSTALL%


IF "%INPUT-VERIQUIN-CPP-ENVIRONMENT-VARS%" == "n"  GOTO END-VERIQUIN_CPP
echo (2)  Setting up VERIQUIN_CPP environment vars ...
echo Setting VERIQUIN_CPP_DIR, VERIQUIN_CPP_DIR_BACKSLASH 
echo and VERIQUIN_CODE_DIR, VERIQUIN_CODE_DIR_BACKSLASH ...

cd ..
SET VERIQUIN_CPP_DIR_BACKSLASH=%CD%
echo %CD%> path.txt
for /f "delims=" %%i in ('%SAVE_DIR_VERIQUIN_CPP_INSTALL%\sed.exe "s/\\/\//g" path.txt') do set VERIQUIN_CPP_DIR=%%i
del path.txt

cd ..
SET VERIQUIN_CODE_DIR_BACKSLASH=%CD%
echo %CD%> path.txt
for /f "delims=" %%i in ('%SAVE_DIR_VERIQUIN_CPP_INSTALL%\sed.exe "s/\\/\//g" path.txt') do set VERIQUIN_CODE_DIR=%%i
del path.txt
REM SET PATH=%VERIQUIN_CPP_DIR_BACKSLASH%\3rdparty\php\windows\bin;%VERIQUIN_CPP_DIR_BACKSLASH%\bin;%VERIQUIN_CODE_DIR_BACKSLASH%\bin;%VERIQUIN_CODE_DIR_BACKSLASH%\bin\windows;%PATH%
REM SET PATH=%VERIQUIN_CPP_DIR_BACKSLASH%\3rdparty\php\windows\bin;%VERIQUIN_CPP_DIR_BACKSLASH%\bin;%PATH%
SET PATH=%VERIQUIN_CPP_DIR_BACKSLASH%\bin;%PATH%

chdir /d %SAVE_DIR_VERIQUIN_CPP_INSTALL%

echo VERIQUIN_CPP_DIR            : %VERIQUIN_CPP_DIR%
echo VERIQUIN_CPP_DIR_BACKSLASH  : %VERIQUIN_CPP_DIR_BACKSLASH%
echo VERIQUIN_CODE_DIR           : %VERIQUIN_CODE_DIR%
echo VERIQUIN_CODE_DIR_BACKSLASH : %VERIQUIN_CODE_DIR_BACKSLASH%
call setenv -u VERIQUIN_CPP_DIR "%VERIQUIN_CPP_DIR%"
call setenv -u VERIQUIN_CPP_DIR_BACKSLASH "%VERIQUIN_CPP_DIR_BACKSLASH%"
call setenv -u VERIQUIN_CODE_DIR "%VERIQUIN_CODE_DIR%"
call setenv -u VERIQUIN_CODE_DIR_BACKSLASH "%VERIQUIN_CODE_DIR_BACKSLASH%"
call setenv -u PATH "%PATH%"
echo PATH: %PATH%
echo .


:END-VERIQUIN_CPP
echo Done!

chdir /d %SAVE_DIR_VERIQUIN_CPP_INSTALL%

REM C:\Program Files\CMake 2.4\bin;C:\Program Files\gs\gs8.54\bin;C:\Program Files\MiKTeX 2.5\miktex\bin;C:\WINDOWS\system32;C:\WINDOWS;C:\WINDOWS\System32\Wbem;C:\Program Files\GNU\WinCvs 1.3\CVSNT;C:\Python24;C:\Program Files\doxygen\bin;C:\Program Files\doxygen1.3.3\bin;C:\Program Files\Microsoft SQL Server\90\Tools\Binn\VSShell\Common7\IDE\;C:\Program Files\Microsoft Visual Studio 8\Common7\IDE\PrivateAssemblies\;C:\Program Files\Common Files\Roxio Shared\DLLShared;


