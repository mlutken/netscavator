set (library_name htmlparser)
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
target_sources(${library_name}
    PUBLIC
    ${CMAKE_CURRENT_LIST_DIR}/html/CharsetConverter.h
    ${CMAKE_CURRENT_LIST_DIR}/html/Extensions.h
    ${CMAKE_CURRENT_LIST_DIR}/html/Node.h
    ${CMAKE_CURRENT_LIST_DIR}/html/ParserDom.h
    ${CMAKE_CURRENT_LIST_DIR}/html/ParserSax.h
    ${CMAKE_CURRENT_LIST_DIR}/html/Uri.h
    ${CMAKE_CURRENT_LIST_DIR}/html/utils.h
    ${CMAKE_CURRENT_LIST_DIR}/html/XPath.h

    PRIVATE
    ${CMAKE_CURRENT_LIST_DIR}/html/CharsetConverter.cpp
    ${CMAKE_CURRENT_LIST_DIR}/html/Extensions.cpp
    ${CMAKE_CURRENT_LIST_DIR}/html/Node.cpp
    ${CMAKE_CURRENT_LIST_DIR}/html/ParserDom.cpp
    ${CMAKE_CURRENT_LIST_DIR}/html/ParserSax.cpp
    ${CMAKE_CURRENT_LIST_DIR}/html/Uri.cpp
    ${CMAKE_CURRENT_LIST_DIR}/html/utils.cpp
    ${CMAKE_CURRENT_LIST_DIR}/html/XPath.cpp
)

# --------------------------
# --- Build instructions ---
# --------------------------
get_filename_component(PARENT_DIR ${CMAKE_CURRENT_SOURCE_DIR} DIRECTORY)
target_link_libraries(${library_name} "Qt${QT_VER}::Widgets;Qt${QT_VER}::Core" )
target_link_libraries(${library_name}
                    cpaf_compression
                    cpaf_utils
                    cpaf_system
                    cpaf_filesystem
                    cpaf_unicode
                    loki
                    )

set_target_properties(${library_name} PROPERTIES LINKER_LANGUAGE CXX)
target_include_directories(${library_name} PUBLIC ${Boost_INCLUDE_DIRS} ${Qt5Core_INCLUDE_DIRS} ${PARENT_DIR} ${CMAKE_CURRENT_SOURCE_DIR})

add_subdirectories_standard()


