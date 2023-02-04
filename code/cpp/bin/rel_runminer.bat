@echo off
SET SAVE_DIR_RUN_MINER=%CD%
:::: %VERIQUIN_CPP_DIR_BACKSLASH%\3rdparty\php\windows\bin\php.exe -c %VERIQUIN_CPP_DIR_BACKSLASH%\build_cbs\libs\shared\Release -f %1 %2 %3 %4 %5 %6 %7 %8 %9
%VERIQUIN_CPP_DIR_BACKSLASH%\3rdparty\php-5.3.2\win_vc9_release\bin\php.exe -c %VERIQUIN_CPP_DIR_BACKSLASH%\build_cbs\libs\shared\Release -f  %1 %2 %3 %4 %5 %6 %7 %8 %9

chdir /d %SAVE_DIR_RUN_MINER%

