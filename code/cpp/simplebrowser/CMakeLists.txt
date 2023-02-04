set (library_name simplebrowser)
add_library(${library_name} STATIC "")

# ------------------------
# --- Find dependecies ---
# ------------------------
# See: https://doc.qt.io/qt-5/cmake-manual.html
find_package(Qt${QT_VER} REQUIRED
    Core
)

# --------------------
# --- Source files ---
# --------------------
target_sources(${library_name}
    PUBLIC
    ${CMAKE_CURRENT_LIST_DIR}/SimpleBrowser.h
    ${CMAKE_CURRENT_LIST_DIR}/SimpleDomNode.h
    ${CMAKE_CURRENT_LIST_DIR}/SimpleDomDocumentLinear.h
    ${CMAKE_CURRENT_LIST_DIR}/SimpleNetworkAccessManager.h
    ${CMAKE_CURRENT_LIST_DIR}/CreatorSimpleWebViewUi.h
    ${CMAKE_CURRENT_LIST_DIR}/SimpleWebView.h
    PRIVATE
    ${CMAKE_CURRENT_LIST_DIR}/SimpleBrowser.cpp
    ${CMAKE_CURRENT_LIST_DIR}/SimpleDomNode.cpp
    ${CMAKE_CURRENT_LIST_DIR}/SimpleDomDocumentLinear.cpp
    ${CMAKE_CURRENT_LIST_DIR}/SimpleNetworkAccessManager.cpp
    ${CMAKE_CURRENT_LIST_DIR}/CreatorSimpleWebViewUi.cpp
    ${CMAKE_CURRENT_LIST_DIR}/SimpleWebView.cpp
)

# --------------------------
# --- Build instructions ---
# --------------------------
get_filename_component(PARENT_DIR ${CMAKE_CURRENT_SOURCE_DIR} DIRECTORY)
target_link_libraries(${library_name}  Qt${QT_VER}::Core )
target_link_libraries(${library_name} "cpaf_streams;crawl;interfaces;htmlparser;json")

set_target_properties(${library_name} PROPERTIES LINKER_LANGUAGE CXX)
target_include_directories(${library_name} PUBLIC ${Qt5Core_INCLUDE_DIRS} ${CMAKE_CURRENT_SOURCE_DIR})

add_subdirectories_standard()
