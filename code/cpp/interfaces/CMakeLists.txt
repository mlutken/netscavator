IF ( NOT CBS_BUILD )
    set (library_name interfaces)
    add_library(${library_name} STATIC "")

    # ------------------------
    # --- Find dependecies ---
    # ------------------------
    # See: https://doc.qt.io/qt-5/cmake-manual.html
    find_package(Qt${QT_VER} REQUIRED
        Core
        Widgets
    )
    find_package(Boost ${BOOST_MIN_VERSION} REQUIRED)

    # --------------------
    # --- Source files ---
    # --------------------
    CONFIGURE_FILE ( ${VERSION_DIR}/version_info.cpp.in ${CMAKE_CURRENT_BINARY_DIR}/version_info.cpp )

    target_sources(${library_name}
        PUBLIC
        # interfaces/url
        ${CMAKE_CURRENT_LIST_DIR}/url/url_functions.h
        ${CMAKE_CURRENT_LIST_DIR}/url/url_string_functions.h
        ${CMAKE_CURRENT_LIST_DIR}/url/Url.h
        ${CMAKE_CURRENT_LIST_DIR}/url/UrlGetter.h
        # interfaces/utils
        ${CMAKE_CURRENT_LIST_DIR}/utils/CommandLineParser.h
        ${CMAKE_CURRENT_LIST_DIR}/utils/QStringFinder.h
        ${CMAKE_CURRENT_LIST_DIR}/utils/StatusFile.h
        ${CMAKE_CURRENT_LIST_DIR}/utils/string_algorithms.h
        ${CMAKE_CURRENT_LIST_DIR}/utils/string_base.h
        ${CMAKE_CURRENT_LIST_DIR}/utils/string_compare_functions.h
        ${CMAKE_CURRENT_LIST_DIR}/utils/string_manipulation.h
        ${CMAKE_CURRENT_LIST_DIR}/utils/StringFinder.h
        ${CMAKE_CURRENT_LIST_DIR}/utils/utils.h
        # interfaces/
        ${CMAKE_CURRENT_LIST_DIR}/BoxObjectIF.h
        ${CMAKE_CURRENT_LIST_DIR}/BrowserViewIF.h
        ${CMAKE_CURRENT_LIST_DIR}/Configuration.h
        ${CMAKE_CURRENT_LIST_DIR}/DataWriterIF.h
        ${CMAKE_CURRENT_LIST_DIR}/dom_constants.h
        ${CMAKE_CURRENT_LIST_DIR}/DomEventIF.h
        ${CMAKE_CURRENT_LIST_DIR}/DomKeyEventIF.h
        ${CMAKE_CURRENT_LIST_DIR}/DomMouseEventIF.h
        ${CMAKE_CURRENT_LIST_DIR}/DomNodeIF.h
        ${CMAKE_CURRENT_LIST_DIR}/Factory.h
        ${CMAKE_CURRENT_LIST_DIR}/Globals.h
        ${CMAKE_CURRENT_LIST_DIR}/interfaces_types.h
        ${CMAKE_CURRENT_LIST_DIR}/interfaces_utils.h
        ${CMAKE_CURRENT_LIST_DIR}/LinearDomIF.h
        ${CMAKE_CURRENT_LIST_DIR}/MinerWorkerIF.h
        ${CMAKE_CURRENT_LIST_DIR}/NetscavatorFactoryIF.h
        ${CMAKE_CURRENT_LIST_DIR}/QEventWrapper.h
        ${CMAKE_CURRENT_LIST_DIR}/ScriptingClassIF.h
        ${CMAKE_CURRENT_LIST_DIR}/ScriptMinerIF.h
        ${CMAKE_CURRENT_LIST_DIR}/SignalsManager.h
        ${CMAKE_CURRENT_LIST_DIR}/SignalsManagerIF.h
        ${CMAKE_CURRENT_LIST_DIR}/WebBrowserIF.h

        PRIVATE
        # interfaces/url
        ${CMAKE_CURRENT_LIST_DIR}/url/url_functions.cpp
        ${CMAKE_CURRENT_LIST_DIR}/url/url_string_functions.cpp
        ${CMAKE_CURRENT_LIST_DIR}/url/Url.cpp
        ${CMAKE_CURRENT_LIST_DIR}/url/UrlGetter.cpp
        # interfaces/utils
        ${CMAKE_CURRENT_LIST_DIR}/utils/CommandLineParser.cpp
        ${CMAKE_CURRENT_LIST_DIR}/utils/QStringFinder.cpp
        ${CMAKE_CURRENT_LIST_DIR}/utils/StatusFile.cpp
        ${CMAKE_CURRENT_LIST_DIR}/utils/string_algorithms.cpp
        ${CMAKE_CURRENT_LIST_DIR}/utils/string_compare_functions.cpp
        ${CMAKE_CURRENT_LIST_DIR}/utils/string_manipulation.cpp
        ${CMAKE_CURRENT_LIST_DIR}/utils/StringFinder.cpp
        ${CMAKE_CURRENT_LIST_DIR}/utils/utils.cpp
        # interfaces/
        ${CMAKE_CURRENT_LIST_DIR}/BoxObjectIF.cpp
        ${CMAKE_CURRENT_LIST_DIR}/BrowserViewIF.cpp
        ${CMAKE_CURRENT_LIST_DIR}/Configuration.cpp
        ${CMAKE_CURRENT_LIST_DIR}/DataWriterIF.cpp
        ### NOTE: No dom_constants.cpp currently!
        ${CMAKE_CURRENT_LIST_DIR}/DomEventIF.cpp
        ${CMAKE_CURRENT_LIST_DIR}/DomKeyEventIF.cpp
        ${CMAKE_CURRENT_LIST_DIR}/DomMouseEventIF.cpp
        ${CMAKE_CURRENT_LIST_DIR}/DomNodeIF.cpp
        ${CMAKE_CURRENT_LIST_DIR}/Factory.cpp
        ${CMAKE_CURRENT_LIST_DIR}/Globals.cpp
        ${CMAKE_CURRENT_LIST_DIR}/interfaces_types.cpp
        ${CMAKE_CURRENT_LIST_DIR}/interfaces_utils.cpp
        ${CMAKE_CURRENT_LIST_DIR}/LinearDomIF.cpp
        ${CMAKE_CURRENT_LIST_DIR}/MinerWorkerIF.cpp
        ${CMAKE_CURRENT_LIST_DIR}/NetscavatorFactoryIF.cpp
        ${CMAKE_CURRENT_LIST_DIR}/QEventWrapper.cpp
        ${CMAKE_CURRENT_LIST_DIR}/ScriptingClassIF.cpp
        ${CMAKE_CURRENT_LIST_DIR}/ScriptMinerIF.cpp
        ${CMAKE_CURRENT_LIST_DIR}/SignalsManager.cpp
        ${CMAKE_CURRENT_LIST_DIR}/SignalsManagerIF.cpp
        ${CMAKE_CURRENT_BINARY_DIR}/version_info.cpp
        ${CMAKE_CURRENT_LIST_DIR}/WebBrowserIF.cpp
    )

    # --------------------------
    # --- Build instructions ---
    # --------------------------
    get_filename_component(PARENT_DIR ${CMAKE_CURRENT_SOURCE_DIR} DIRECTORY)
    target_link_libraries(${library_name} "Qt${QT_VER}::Widgets;Qt${QT_VER}::Core" )
    target_link_libraries(${library_name} "cpaf_compression;cpaf_filesystem;cpaf_system;cpaf_utils")
    target_link_libraries(${library_name} "boost_program_options;boost_regex;boost_date_time;curl;loki;z")
    target_link_libraries(${library_name} htmlparser)


    set_target_properties(${library_name} PROPERTIES LINKER_LANGUAGE CXX)
    target_include_directories(${library_name} PUBLIC ${Boost_INCLUDE_DIRS} ${Qt5Core_INCLUDE_DIRS} ${PARENT_DIR} ${CMAKE_CURRENT_SOURCE_DIR} ${VERSION_DIR})
    target_compile_options(${library_name} PRIVATE ${STANDARD_COMPILE_FLAGS})

    add_subdirectories_standard()

ELSE ()
    project ( interfaces )
    include ( ${CBS_ROOT_DIR}/cbs_common_rules.cbs )
    BUILD_LIBRARY ( interfaces )
ENDIF ()

