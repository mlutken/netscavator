set (target_name netcreator)
add_executable(${target_name} "")

configure_file ( ${CMAKE_CURRENT_LIST_DIR}/${target_name}.cfg.in ${CBS_SHARED_LIBRARY_PATH_PREBUILD}/${target_name}.cfg     )
configure_file ( ${CMAKE_CURRENT_LIST_DIR}/${target_name}.cfg.in ${CMAKE_CURRENT_BINARY_DIR}/${target_name}.cfg             )

find_package(Qt${QT_VER} REQUIRED
    Core
    Gui
    Widgets
)

# --------------------
# --- Source files ---
# --------------------
target_sources(${target_name}
    PRIVATE
    ${CMAKE_CURRENT_LIST_DIR}/${target_name}.cpp
    ${CMAKE_CURRENT_LIST_DIR}/../crawler.qrc
)

# --------------------------
# --- Build instructions ---
# --------------------------
get_filename_component(PARENT_DIR ${CMAKE_CURRENT_SOURCE_DIR} DIRECTORY)
target_link_libraries(${target_name} "gui;webkitbrowser;simplebrowser;crawl;scriptfunctions_php;script_embedding")

set_target_properties(${target_name} PROPERTIES LINKER_LANGUAGE CXX)
target_include_directories(${target_name} PRIVATE ${CMAKE_CURRENT_SOURCE_DIR})

target_compile_options(${target_name} PRIVATE ${STANDARD_COMPILE_FLAGS})
set_property(SOURCE ${CMAKE_CURRENT_LIST_DIR}/${target_name}.cpp PROPERTY SKIP_AUTOGEN ON) # Prevent warnings from CMAKE_AUTOMOC

add_subdirectories_standard()


