IF ( NOT CBS_BUILD )
    set (library_name scriptfunctions_php)
    add_library(${library_name} STATIC "")

    message ("PHP_BASE_INCLUDE_DIR: ${PHP_BASE_INCLUDE_DIR}")
    
    # ------------------------
    # --- Find dependecies ---
    # ------------------------
    # See: https://doc.qt.io/qt-5/cmake-manual.html
    find_package(Qt${QT_VER} REQUIRED
        Network
    )
    find_package(Boost ${BOOST_MIN_VERSION} REQUIRED)

    # --------------------
    # --- Source files ---
    # --------------------

    target_sources(${library_name}
        PUBLIC
        ${CMAKE_CURRENT_LIST_DIR}/PhpScriptingClass.h
        ${CMAKE_CURRENT_LIST_DIR}/scriptcrawl_private_php.h

        PRIVATE
        ${CMAKE_CURRENT_LIST_DIR}/PhpScriptingClass.cpp
        ${CMAKE_CURRENT_LIST_DIR}/scriptcrawl_private_php.cpp
    )

    # --------------------------
    # --- Build instructions ---
    # --------------------------
    get_filename_component(PARENT_DIR ${CMAKE_CURRENT_SOURCE_DIR} DIRECTORY)
    target_link_libraries(${library_name} "script_embedding;interfaces;cpaf_concurrent;cpaf_net;cpaf_math;utf8" )

#    target_link_libraries(${library_name} "cpaf_compression;cpaf_utils;cpaf_system;cpaf_filesystem;loki")

    set_target_properties(${library_name} PROPERTIES LINKER_LANGUAGE CXX)
    
#     target_include_directories(${library_name} PUBLIC ${Boost_INCLUDE_DIRS} ${Qt5Core_INCLUDE_DIRS} ${PARENT_DIR} ${CUSTOM_PHP_INCLUDES} ${CMAKE_CURRENT_SOURCE_DIR})
    target_include_directories(${library_name} PUBLIC ${Boost_INCLUDE_DIRS} ${CUSTOM_PHP_INCLUDES} ${PARENT_DIR} ${CMAKE_CURRENT_SOURCE_DIR})
    target_compile_options(${library_name} PRIVATE ${COMMON_COMPILE_FLAGS}) # We do not want -Wall etc. here, since the PHP includes creates troubles
    target_compile_definitions(${library_name} PRIVATE PHP_HARDCODED_INI_FILE_PATH="${PHP_HARDCODED_INI_FILE_PATH}" )

    
#     ADDX_INCLUDE_DIR ( ${CMAKE_CURRENT_SOURCE_DIR} )
#     ADDX_INCLUDE_DIR ( ${PHP_BASE_INCLUDE_DIR}			)
#     ADDX_INCLUDE_DIR ( ${PHP_BASE_INCLUDE_DIR}/Zend 	)
#     ADDX_INCLUDE_DIR ( ${PHP_BASE_INCLUDE_DIR}/TSRM 	)
#     ADDX_INCLUDE_DIR ( ${PHP_BASE_INCLUDE_DIR}/main		)
#     ADDX_INCLUDE_DIR ( ${veriquin_cpp_SOURCE_DIR}		)


    IF ( WINDOWS )
#         ADDX_LINK_DIR 		( ${PHP_BASE_DIR}/bin	)
#         ADDX_LINK_LIBRARY 	( php5ts_debug				CBS_DEBUG	)
#         ADDX_LINK_LIBRARY 	( php5ts					CBS_RELEASE	)
#         ADD_DEFINE ( _USE_32BIT_TIME_T				1		WINDOWS						)
#         ADD_DEFINE ( ZEND_WIN32						1		WINDOWS						)
#         ADD_DEFINE ( PHP_WIN32						1		WINDOWS						)
#         ADD_DEFINE ( ZEND_WIN32_FORCE_INLINE		1		WINDOWS						)
#         ADD_DEFINE ( WIN32							1		WIN32						)
#         ADD_DEFINE ( __WIN32__						1		WIN32						)
    ENDIF ()
                             
                                
    add_subdirectories_standard()

ELSE ()
    project ( scriptfunctions_php )
    INCLUDE ( $ENV{CBS_ROOT_DIR}/cbs_common_rules.cbs )
    BUILD_LIBRARY ( scriptfunctions_php )
ENDIF ()


