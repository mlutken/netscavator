IF ( NOT CBS_BUILD )
    set (library_name commmon_utils)
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

        PRIVATE
    )

    # --------------------------
    # --- Build instructions ---
    # --------------------------
    get_filename_component(PARENT_DIR ${CMAKE_CURRENT_SOURCE_DIR} DIRECTORY)
    target_link_libraries(${library_name} "Qt${QT_VER}::Widgets;Qt${QT_VER}::Core" )
    target_link_libraries(${library_name} "cpaf_compression;cpaf_utils;cpaf_system;cpaf_filesystem;loki")

    set_target_properties(${library_name} PROPERTIES LINKER_LANGUAGE CXX)
    target_include_directories(${library_name} PUBLIC ${Boost_INCLUDE_DIRS} ${Qt5Core_INCLUDE_DIRS} ${PARENT_DIR} ${CMAKE_CURRENT_SOURCE_DIR})

    add_subdirectories_standard()

ELSE ()
    project ( commmon_utils )
    include ( ${CBS_ROOT_DIR}/cbs_common_rules.cbs )
    BUILD_LIBRARY ( commmon_utils ) 
ENDIF ()


