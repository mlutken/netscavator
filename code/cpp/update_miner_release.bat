@echo off


set SRC_DIR=%VERIQUIN_CPP_DIR_BACKSLASH%\build_cbs\libs\shared\Release
set SRC_DIR_PHP=%VERIQUIN_CPP_DIR_BACKSLASH%\3rdparty\php-5.3.2\win_vc9_release\bin
set DST_DIR_LIBS=%WEBMINER_ROOT_DIR_BACKSLASH%\webminer\windows\libs
::set DST_DIR_PHP=%WEBMINER_ROOT_DIR_BACKSLASH%\webminer\windows\php

copy /Y %SRC_DIR%\php_crawl.php %DST_DIR_LIBS%
copy /Y %SRC_DIR%\php_php_crawl.dll %DST_DIR_LIBS%
copy /Y %SRC_DIR%\crawler.exe %DST_DIR_LIBS%
copy /Y %SRC_DIR%\minercreator.exe %DST_DIR_LIBS%
copy /Y %SRC_DIR%\php5ts.dll %DST_DIR_LIBS%
copy /Y %SRC_DIR_PHP%\php.exe %DST_DIR_LIBS%

