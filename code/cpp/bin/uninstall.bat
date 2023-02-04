@echo off
SET SAVE_DIR_VERIQUIN_CPP_UNINSTALL=%CD%

set INPUT-VERIQUIN-CPP-ENVIRONMENT-VARS=y

SET /P INPUT-VERIQUIN-CPP-ENVIRONMENT-VARS=(2)  UnInstall VERIQUIN_CPP environment variables [Y]/N : 

echo .
echo You chose:
echo VERIQUIN-CPP-ENVIRONMENT-VARS : %INPUT-VERIQUIN-CPP-ENVIRONMENT-VARS%
echo .

IF "%INPUT-VERIQUIN-CPP-ENVIRONMENT-VARS%" == "n"  GOTO UNINSTALL-CPAF
echo (2)  Uninstalling VERIQUIN_CPP environment vars ...
echo Removing VERIQUIN_CPP_DIR, VERIQUIN_CPP_DIR_BACKSLASH 
echo and VERIQUIN_CODE_DIR, VERIQUIN_CODE_DIR_BACKSLASH ...

call setenv -u VERIQUIN_CPP_DIR -delete
call setenv -u VERIQUIN_CPP_DIR_BACKSLASH -delete
call setenv -u VERIQUIN_CODE_DIR -delete
call setenv -u VERIQUIN_CODE_DIR_BACKSLASH -delete

chdir /d %SAVE_DIR_VERIQUIN_CPP_UNINSTALL%

:UNINSTALL-CPAF
echo (1)  Running un-install in cpaf directory ...
cd ..\..\..\cpaf\bin\windows
call uninstall.bat
chdir /d %SAVE_DIR_VERIQUIN_CPP_UNINSTALL%


echo Done!





