
find_package(Qt${QT_VER} REQUIRED
    Core
    Network
    WebEngineCore
    WebEngineWidgets
    Gui
    Widgets
)

set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTORCC ON)


CONFIGURE_FILE ( ${QT_RESOURCES_PATH}/qtwebengine_devtools_resources.pak ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/qtwebengine_devtools_resources.pak COPYONLY )
CONFIGURE_FILE ( ${QT_RESOURCES_PATH}/qtwebengine_resources_100p.pak ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/qtwebengine_resources_100p.pak COPYONLY )
CONFIGURE_FILE ( ${QT_RESOURCES_PATH}/qtwebengine_resources_200p.pak ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/qtwebengine_resources_200p.pak COPYONLY )
CONFIGURE_FILE ( ${QT_RESOURCES_PATH}/qtwebengine_resources.pak ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/qtwebengine_resources.pak COPYONLY )

#cmake --help-policy CMP0005
set ( CBS_ROOT_DIR ${CMAKE_CURRENT_LIST_DIR}/../../cpaf/cbs )
message ( "CBS_ROOT_DIR: ${CBS_ROOT_DIR}" )
set  ( PHP_VERSION      "${CRAWLER_PHP_VERSION}" )
#     set  ( QT_VERSION       "5.5.0" )
set  ( WEBKIT_VERSION   "git" )  # 2017-04-05, 2017-05-26, 2018-01-06
set  ( HTMLCXX_VERSION  "0.87" )

set ( CPAF_ROOT_DIR "../../../cpaf" )

set ( CBS_SHARED_LIBRARY_PATH_PREBUILD ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}    ) # For configuring files like netscavator.cfg.in: TODO: Change .in files to use different var than CBS_SHARED_LIBRARY_PATH_PREBUILD
set ( RESOURCE_DIR  ${CMAKE_CURRENT_LIST_DIR}/data                          )

if ( ${CMAKE_BUILD_TYPE} STREQUAL "Debug"  )
    set ( CUSTOM_PHP_BASE_DIR       ${BASE_3RD_PARTY_DIR}/php-${PHP_VERSION}/linux_64_debug )
    set ( QT_WEBKIT_LIB_DIR         ${BASE_3RD_PARTY_DIR}/qtlibs/linux_64_release/lib/x86_64-linux-gnu   )
    set ( QT_WEBKIT_HDR_DIR         ${BASE_3RD_PARTY_DIR}/qtlibs/linux_64_release/include                )
else ()
    set ( CUSTOM_PHP_BASE_DIR       ${BASE_3RD_PARTY_DIR}/php-${PHP_VERSION}/linux_64_release )
    set ( QT_WEBKIT_LIB_DIR         ${BASE_3RD_PARTY_DIR}/qtlibs/linux_64_release/lib/x86_64-linux-gnu   )
    set ( QT_WEBKIT_HDR_DIR         ${BASE_3RD_PARTY_DIR}/qtlibs/linux_64_release/include                )
endif ()

# --- Set define for hardcoded php.ini file path. Mostly used for debugging/testing purposes ---
set ( PHP_HARDCODED_INI_FILE_PATH   "${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/php.ini" )

# ------------------------------------------
# --- DEVELOP PHP (crawler PHP) ini file ---
# ------------------------------------------
set ( WEBMINER_PHP_INCLUDE_PATH     "${CMAKE_CURRENT_LIST_DIR}/scriptcrawl/cpp_crawl:${CMAKE_CURRENT_LIST_DIR}/data/php/miner_utils:${CMAKE_CURRENT_LIST_DIR}/data/php/miner_templates:${CMAKE_RUNTIME_OUTPUT_DIRECTORY}" )
set ( WEBMINER_PHP_EXTENSION_DIR    "${CMAKE_RUNTIME_OUTPUT_DIRECTORY}" )
configure_file (${CMAKE_CURRENT_LIST_DIR}/scriptcrawl/cpp_crawl/php.ini.in ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/php.ini )

# ------------------------------------------
# --- INSTALL PHP (crawler PHP) ini file ---
# ------------------------------------------
set ( WEBMINER_PHP_INCLUDE_PATH     "${CMAKE_INSTALL_PREFIX}/share/netscavator:${CMAKE_INSTALL_PREFIX}/lib" )
set ( WEBMINER_PHP_EXTENSION_DIR    "${CMAKE_INSTALL_PREFIX}/lib" )
configure_file (${CMAKE_CURRENT_LIST_DIR}/scriptcrawl/cpp_crawl/php.ini.in ${CMAKE_BINARY_DIR}/php.ini )

set  ( swig_EXECUTABLE   ${CMAKE_CURRENT_SOURCE_DIR}/../3rdparty/swig-3.0.12/linux_64/bin/swig )

# ---------------------------------------
# --- Custom PHP Includes and defines ---
# ---------------------------------------
set (CUSTOM_PHP_INCLUDES "${CUSTOM_PHP_BASE_DIR}/include/php;${CUSTOM_PHP_BASE_DIR}/include/php/Zend;${CUSTOM_PHP_BASE_DIR}/include/php/TSRM;${CUSTOM_PHP_BASE_DIR}/include/php/main")
set (CUSTOM_PHP_LIBRARIES "")
add_library(php-sleipner5 SHARED IMPORTED)
set_target_properties(php-sleipner5 PROPERTIES IMPORTED_LOCATION "${CUSTOM_PHP_BASE_DIR}/lib/libphp-sleipner5.so")

# -----------------------------------
# --- Webkit Includes and defines ---
# -----------------------------------
#set (QT_WEBKIT_INCLUDES "${QT_WEBKIT_HDR_DIR};${QT_WEBKIT_HDR_DIR}/QtWebKit;${QT_WEBKIT_HDR_DIR}/QtWebKitWidgets")
set (QT_WEBKIT_INCLUDES "${QT_WEBKIT_HDR_DIR}")
set (QT_WEBKIT_LINK_DIRS "${QT_WEBKIT_LIB_DIR}")
set (QT_WEBKIT_LIBRARIES "")

add_library(qscintilla2 STATIC IMPORTED)
set_target_properties(qscintilla2 PROPERTIES IMPORTED_LOCATION "${QT_WEBKIT_LIB_DIR}/libqscintilla2.a")
add_library(Qt5WebKit SHARED IMPORTED)

set (LOHMAN_JSON_INCLUDE_DIRS ${BASE_3RD_PARTY_DIR}/json )
message ("CMAKE_BUILD_TYPE: '${CMAKE_BUILD_TYPE}'")

message ("BASE_3RD_PARTY_DIR            : '${BASE_3RD_PARTY_DIR}'")
message ("QT_WEBKIT_LIB_DIR             : '${QT_WEBKIT_LIB_DIR}'")

message ("CUSTOM_PHP_BASE_DIR           : '${CUSTOM_PHP_BASE_DIR}'")
message ("PHP_HARDCODED_INI_FILE_PATH   : '${PHP_HARDCODED_INI_FILE_PATH}'")
#message ("CUSTOM_PHP_INCLUDES: '${CUSTOM_PHP_INCLUDES}'")

message ("SYSTEM_PHP_BASE_INCLUDE_DIR   : '${SYSTEM_PHP_BASE_INCLUDE_DIR}'")
#message ("SYSTEM_PHP_INCLUDES           : '${SYSTEM_PHP_INCLUDES}'")

add_subdirectory ( htmlparser                           )
add_subdirectory ( common_utils                         )
add_subdirectory ( script_embedding                     )
add_subdirectory ( interfaces                           )
add_subdirectory ( simplebrowser                        )
add_subdirectory ( webkitbrowser                        )
add_subdirectory ( scriptfunctions/scriptfunctions_php  )
add_subdirectory ( crawl                                )
add_subdirectory ( scriptcrawl                          )
add_subdirectory ( gui                                  )
add_subdirectory ( netscavator                          )
add_subdirectory ( netcreator                           )
add_subdirectory ( test/qtminimal                       )
#     add_subdirectory ( test                                 )
