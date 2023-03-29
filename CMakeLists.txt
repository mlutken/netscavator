cmake_minimum_required(VERSION 3.5)
project(netscavator)
SET(QT_CREATOR_SKIP_PACKAGE_MANAGER_SETUP TRUE)
SET(QT_CREATOR_SKIP_CONAN_SETUP TRUE)


enable_testing()
include (${CMAKE_CURRENT_LIST_DIR}/cpaf/tools/cmake/default_vars.cmake)
include (${CMAKE_CURRENT_LIST_DIR}/cpaf/tools/cmake/default_versions.cmake)

list(APPEND CMAKE_MODULE_PATH ${CMAKE_BINARY_DIR})
list(APPEND CMAKE_PREFIX_PATH ${CMAKE_BINARY_DIR})
list(APPEND CMAKE_MODULE_PATH ${CMAKE_CURRENT_LIST_DIR}/cpaf/tools/cmake)

# --- Crawler version ---
set ( NETSCAVATOR_VERSION_MAJOR     6   )
set ( NETSCAVATOR_VERSION_MINOR     7   )
set ( NETSCAVATOR_VERSION_PATCH     3   )
set ( NETSCAVATOR_VERSION_STRING    "${NETSCAVATOR_VERSION_MAJOR}.${NETSCAVATOR_VERSION_MINOR}.${NETSCAVATOR_VERSION_PATCH}"    )
set ( VERSION_DIR                   ${CMAKE_CURRENT_LIST_DIR}/version)

set ( CRAWLER_PHP_VERSION      "5.6.40" )

# --- C++ standard ---
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_C_STANDARD 99)
set(CMAKE_C_STANDARD_REQUIRED ON)

# Luepp platform

if(NOT EXISTS "${CMAKE_BINARY_DIR}/conan.cmake")
  file(COPY_FILE "${CMAKE_CURRENT_LIST_DIR}/3rdparty/conan/conan.cmake" "${CMAKE_BINARY_DIR}/conan.cmake")
  #file(DOWNLOAD "https://raw.githubusercontent.com/conan-io/cmake-conan/0.18.1/conan.cmake"
                #"${CMAKE_BINARY_DIR}/conan.cmake" TLS_VERIFY ON)
endif()


include(${CMAKE_BINARY_DIR}/conan.cmake)

conan_cmake_autodetect(settings)

conan_cmake_install(PATH_OR_REFERENCE ${CMAKE_CURRENT_LIST_DIR}
                    BUILD missing
                    REMOTE conancenter
                    SETTINGS ${settings})


include(${CMAKE_BINARY_DIR}/conanbuildinfo.cmake)
conan_basic_setup()


# CPAF Platform
include (${CMAKE_CURRENT_LIST_DIR}/cpaf/tools/cmake/platform_definitions.cmake)
include (${CMAKE_CURRENT_LIST_DIR}/cpaf/tools/cmake/default_platform_definitions.cmake)
include (${CMAKE_CURRENT_LIST_DIR}/cpaf/tools/cmake/set_platform_compiler_defines.cmake)

#set (QT_MAJOR_VERSION 5 )
set (QT_VER 6 )
set (QT_PREFIX_PATH "/usr" )
set (QT_DATA_PATH "${QT_PREFIX_PATH}/share/qt${QT_VER}" )
set (QT_RESOURCES_PATH "${QT_DATA_PATH}/resources" )

message ("QT_MAJOR_VERSION: '${QT_MAJOR_VERSION}'")

# Set 3rdparty install dir
get_filename_component(PARENT_DIR ${CMAKE_CURRENT_SOURCE_DIR} DIRECTORY)
set (RELEASE_BUILD_DIR ${PARENT_DIR}/_build )

# Set some diretories
set (PROJECT_ROOT_DIR ${CMAKE_CURRENT_SOURCE_DIR} )
set (CPAF_ROOT_DIR ${CMAKE_CURRENT_SOURCE_DIR}/cpaf )


# TODO: Remove the "-Wno-deprecated-declarations" flag again
set (COMMON_COMPILE_FLAGS "-fPIC")
set (QT_COMMON_COMPILE_FLAGS "-fPIC")
set (STANDARD_COMPILE_FLAGS "-Wall;-Wextra;-Wsign-conversion;-Wno-zero-as-null-pointer-constant;-Werror;-fPIC;-Wno-deprecated-declarations")


# --- Include cmake utility files ---
include (${CMAKE_CURRENT_LIST_DIR}/cpaf/tools/cmake/std_utils.cmake)


# --- Add testing before setting general compiler flags ---
#add_subdirectory(testing)


# --- Current user's/developer's 'private' config file ---
set ( USER_CONFIG ${CMAKE_CURRENT_SOURCE_DIR}/user.buildconfig.cmake )
if ( EXISTS ${USER_CONFIG} )
    INCLUDE ( ${USER_CONFIG} )
endif()

find_package(GTest REQUIRED)

# --- Add subdirectories ---
add_subdirectory(cpaf)


add_subdirectory(code)

message ("(sleipner)CMAKE_PROJECT_NAME      : '${CMAKE_PROJECT_NAME}'")
message ("CMAKE_SYSTEM_NAME                 : '${CMAKE_SYSTEM_NAME}'")
message ("CMAKE_BINARY_DIR                  : '${CMAKE_BINARY_DIR}'")
message ("CMAKE_RUNTIME_OUTPUT_DIRECTORY    : '${CMAKE_RUNTIME_OUTPUT_DIRECTORY}'")
message ("CMAKE_LIBRARY_OUTPUT_DIRECTORY    : '${CMAKE_LIBRARY_OUTPUT_DIRECTORY}'")
message ("CMAKE_ARCHIVE_OUTPUT_DIRECTORY    : '${CMAKE_ARCHIVE_OUTPUT_DIRECTORY}'")
message ("CMAKE_COMPILE_PDB_OUTPUT_DIRECTORY: '${CMAKE_COMPILE_PDB_OUTPUT_DIRECTORY}'")
message ("RELEASE_BUILD_DIR                 : '${RELEASE_BUILD_DIR}'")
message ("CPAF_INSTALL_DIR                  : '${CPAF_INSTALL_DIR}'")
message ("CMAKE_INSTALL_PREFIX              : '${CMAKE_INSTALL_PREFIX}'")

# ----------------------
# --- install target ---
# ----------------------

# https://doc.qt.io/qt-6/qtwebengine-deploying.html
set (DATA_PHP_SRC_DIR ${CMAKE_CURRENT_LIST_DIR}/code/cpp/data/php )
set (PHP_SLEIPNER_LIB_SRC_DIR ${CMAKE_CURRENT_LIST_DIR}/code/3rdparty/php-${CRAWLER_PHP_VERSION}/linux_64_release/lib)
configure_file(netcreator.desktop.in ${CMAKE_CURRENT_BINARY_DIR}/netcreator.desktop)
configure_file(netscavator.desktop.in ${CMAKE_CURRENT_BINARY_DIR}/netscavator.desktop)

install (TARGETS netscavator        DESTINATION bin)
install (TARGETS netcreator         DESTINATION bin)
install (TARGETS cpp_crawl          DESTINATION lib)
install (FILES netcreator.png       DESTINATION share/pixmaps/)
install (FILES netscavator.png      DESTINATION share/pixmaps/)

install (FILES ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/cpp_crawl.php  DESTINATION lib/ )
install (FILES ${PHP_SLEIPNER_LIB_SRC_DIR}/libphp-sleipner5.so  DESTINATION lib/ )
install (FILES ${CMAKE_CURRENT_BINARY_DIR}/netcreator.desktop   DESTINATION share/applications/)
install (FILES ${CMAKE_CURRENT_BINARY_DIR}/netscavator.desktop  DESTINATION share/applications/)


install (FILES ${CMAKE_BINARY_DIR}/php.ini DESTINATION share/netscavator/)
install (FILES ${CMAKE_CURRENT_LIST_DIR}/code/cpp/scriptcrawl/cpp_crawl/webminer.php DESTINATION share/netscavator/)
install (FILES ${DATA_PHP_SRC_DIR}/miner_templates/standard_project_item_template.tpl.php DESTINATION share/netscavator/)
install (FILES ${DATA_PHP_SRC_DIR}/miner_utils/CrawlerLog.php DESTINATION share/netscavator/)
install (FILES ${DATA_PHP_SRC_DIR}/miner_utils/parsing_utils.php DESTINATION share/netscavator/)
install (FILES ${DATA_PHP_SRC_DIR}/miner_utils/string_utils.php DESTINATION share/netscavator/)
install (FILES ${DATA_PHP_SRC_DIR}/miner_utils/utils.php DESTINATION share/netscavator/)

# ------------------------
# --- uninstall target ---
# ------------------------
if(NOT TARGET uninstall)
  configure_file(
    "${CMAKE_CURRENT_SOURCE_DIR}/cmake_uninstall.cmake.in"
    "${CMAKE_CURRENT_BINARY_DIR}/cmake_uninstall.cmake"
    IMMEDIATE @ONLY)

  add_custom_target(uninstall
    COMMAND ${CMAKE_COMMAND} -P ${CMAKE_CURRENT_BINARY_DIR}/cmake_uninstall.cmake)
endif()

# -----------
# --- DOC ---
# -----------
# CMD: ./linuxdeploy-x86_64.AppImage --appdir AppDir --output appimage
# - make uninstall: https://gitlab.kitware.com/cmake/community/-/wikis/FAQ#can-i-do-make-uninstall-with-cmake
# - AppImage with CMake: https://www.codeintrinsic.com/create-appimage-with-linuxdeploy-and-cmake/
# - AppImageTool: https://docs.appimage.org/introduction/software-overview.html
# - AppImage repo: https://flathub.org/apps
# - linuxdeploy: https://docs.appimage.org/packaging-guide/from-source/linuxdeploy-user-guide.html#ref-linuxdeploy
# - AppImageTool download: https://github.com/AppImage/AppImageKit/releases/continuous
# https://docs.appimage.org/packaging-guide/from-source/native-binaries.html#bundle-qtquickapp-with-cmake
# - LD_PRELOAD: https://www.baeldung.com/linux/ld_preload-trick-what-is
# - NSS library problems: https://github.com/probonopd/linuxdeployqt/issues/435
# Meta info for desktop apps XML format: https://www.freedesktop.org/software/appstream/docs/chap-Quickstart.html#sect-Quickstart-DesktopApps

#${CMAKE_BINARY_DIR}/php.ini.install
    #if(SNAP)
        #install(FILES sandboxed.png
            #DESTINATION share/pixmaps/)


# Get tarball from Github netscavator: https://api.github.com/repos/mlutken/netscavator/tarball
# Get tarball from Github cpaf: https://api.github.com/repos/mlutken/cpaf/tarball
