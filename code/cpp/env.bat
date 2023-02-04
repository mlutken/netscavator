@echo off
SET SAVE_DIR_VERIQUIN_CPP=%CD%

REM Set cpaf environment
cd ..\..\cpaf
call env.bat
chdir /d %SAVE_DIR_VERIQUIN_CPP%

REM Set Veriquin code environment
cd ..
call env.bat
chdir /d %SAVE_DIR_VERIQUIN_CPP%

REM Set Veriquin cpp environment
SET VERIQUIN_CPP_DIR_BACKSLASH=%CD%
echo %CD%> path.txt
for /f "delims=" %%i in ('sed "s/\\/\//g" path.txt') do set VERIQUIN_CPP_DIR=%%i
del path.txt
SET PATH=%VERIQUIN_CPP_DIR_BACKSLASH%\bin;%PATH%

echo VERIQUIN_CPP_DIR           : "%VERIQUIN_CPP_DIR%"
echo VERIQUIN_CPP_DIR_BACKSLASH : "%VERIQUIN_CPP_DIR_BACKSLASH%"

chdir /d %SAVE_DIR_VERIQUIN_CPP%
