set (target_name qtminimal)
add_executable(${target_name} "")


find_package(Qt${QT_VER} REQUIRED
    Core
    Network
    WebEngineWidgets
    Gui
    Widgets
)

# --------------------
# --- Source files ---
# --------------------
target_sources(${target_name}
    PRIVATE
    ${CMAKE_CURRENT_LIST_DIR}/${target_name}.cpp
)

# --------------------------
# --- Build instructions ---
# --------------------------
#target_link_libraries(${target_name} "Qt6::WebView;Qt6::Network;Qt6::Widgets;Qt6::Core" )
#target_link_libraries(${target_name} "Qt${QT_VER}::WebEngineWidgets;Qt${QT_VER}::Widgets;Qt${QT_VER}::Core" )

target_link_libraries(${target_name}
    Qt${QT_VER}::WebEngineWidgets
    Qt${QT_VER}::Widgets
    Qt${QT_VER}::Network
    Qt${QT_VER}::Core
)

set_target_properties(${target_name} PROPERTIES LINKER_LANGUAGE CXX)
target_include_directories(${target_name} PRIVATE ${CMAKE_CURRENT_SOURCE_DIR})

target_compile_options(${target_name} PRIVATE ${STANDARD_COMPILE_FLAGS})

#add_custom_command(TARGET ${target_name} PRE_BUILD
#                   COMMAND ${CMAKE_COMMAND} -E copy_directory
#                       ${QT_RESOURCES_PATH}/ $<TARGET_FILE_DIR:${target_name}>)


## set_property(SOURCE ${CMAKE_CURRENT_LIST_DIR}/${target_name}.cpp PROPERTY SKIP_AUTOGEN ON) # Prevent warnings from CMAKE_AUTOMOC


