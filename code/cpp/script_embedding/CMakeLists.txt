IF ( NOT CBS_BUILD )
    set (library_name script_embedding)
    add_library(${library_name} STATIC "")

    # ------------------------
    # --- Find dependecies ---
    # ------------------------
    find_package(Qt${QT_VER} REQUIRED
        Core
        Widgets
    )
    find_package(Boost ${BOOST_MIN_VERSION} REQUIRED)

    # --------------------
    # --- Source files ---
    # --------------------
    target_sources(${library_name}
        PUBLIC
        ${CMAKE_CURRENT_LIST_DIR}/php_embedding/php_embedding_utils.h
        ${CMAKE_CURRENT_LIST_DIR}/php_embedding/php_embedding_callbacks.h

        PRIVATE
        ${CMAKE_CURRENT_LIST_DIR}/php_embedding/php_embedding_utils.cpp
        ${CMAKE_CURRENT_LIST_DIR}/php_embedding/php_embedding_callbacks.cpp
    )

    # --------------------------
    # --- Build instructions ---
    # --------------------------
    get_filename_component(PARENT_DIR ${CMAKE_CURRENT_SOURCE_DIR} DIRECTORY)
    target_link_libraries(${library_name} "php-sleipner5;Qt${QT_VER}::Widgets;Qt${QT_VER}::Core" )
    target_link_libraries(${library_name} "cpaf_compression;cpaf_utils;cpaf_system;cpaf_filesystem;loki")

    set_target_properties(${library_name} PROPERTIES LINKER_LANGUAGE CXX)
    target_include_directories(${library_name} PRIVATE ${Boost_INCLUDE_DIRS} ${Qt5Core_INCLUDE_DIRS} ${CUSTOM_PHP_INCLUDES})
    #     target_include_directories(${library_name} PUBLIC ${Boost_INCLUDE_DIRS} ${Qt5Core_INCLUDE_DIRS} ${PARENT_DIR} ${CUSTOM_PHP_INCLUDES} ${CMAKE_CURRENT_SOURCE_DIR})
    target_include_directories(${library_name} PUBLIC ${PARENT_DIR} ${CMAKE_CURRENT_LIST_DIR})
    target_compile_options(${library_name} PRIVATE ${COMMON_COMPILE_FLAGS}) # We do not want -Wall etc. here, since the PHP includes creates troubles

    target_compile_definitions(${library_name} PRIVATE PHP_HARDCODED_INI_FILE_PATH="${PHP_HARDCODED_INI_FILE_PATH}" )

    add_subdirectories_standard()

ELSE ()
    project ( script_embedding )
    include ( $ENV{CBS_ROOT_DIR}/cbs_common_rules.cbs )
    BUILD_LIBRARY ( script_embedding ) 
ENDIF ()


