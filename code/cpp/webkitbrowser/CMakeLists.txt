set (library_name webkitbrowser)
add_library(${library_name} STATIC "")

# ------------------------
# --- Find dependecies ---
# ------------------------
find_package(Qt${QT_VER} REQUIRED
    Core
    Test
    Widgets
    Network
)
find_package(Boost ${BOOST_MIN_VERSION} REQUIRED)

# --------------------
# --- Source files ---
# --------------------
target_sources(${library_name}
    PUBLIC
    ${CMAKE_CURRENT_LIST_DIR}/WebChannelBridge.h
    ${CMAKE_CURRENT_LIST_DIR}/WebKitBrowserQt.h
    ${CMAKE_CURRENT_LIST_DIR}/WebKitCookieJar.h
    ${CMAKE_CURRENT_LIST_DIR}/WebKitDomNodeQt.h
    ${CMAKE_CURRENT_LIST_DIR}/WebKitDomDocumentLinearQt.h
    ${CMAKE_CURRENT_LIST_DIR}/WebkitNetworkAccessManagerQt.h

    PRIVATE
    ${CMAKE_CURRENT_LIST_DIR}/WebChannelBridge.cpp
    ${CMAKE_CURRENT_LIST_DIR}/WebKitBrowserQt.cpp
    ${CMAKE_CURRENT_LIST_DIR}/WebKitCookieJar.cpp
    ${CMAKE_CURRENT_LIST_DIR}/WebKitDomNodeQt.cpp
    ${CMAKE_CURRENT_LIST_DIR}/WebKitDomDocumentLinearQt.cpp
    ${CMAKE_CURRENT_LIST_DIR}/WebkitNetworkAccessManagerQt.cpp
)

# 	ADDX_LINK_DIR       ( ${QT_WEBKIT_LIB_DIR}  			)
#   	ADDX_LINK_DIR       ( ${QT_LIB_DIR}                     )
#     ADDX_INCLUDE_DIR    ( ${QT_WEBKIT_HDR_DIR} 				)
#     ADDX_INCLUDE_DIR    ( ${QT_WEBKIT_HDR_DIR}/QtWebKit            )
#     ADDX_INCLUDE_DIR    ( ${QT_WEBKIT_HDR_DIR}/QtWebKitWidgets     )

# --------------------------
# --- Build instructions ---
# --------------------------
get_filename_component(PARENT_DIR ${CMAKE_CURRENT_SOURCE_DIR} DIRECTORY)


target_link_libraries(${library_name}
    Qt${QT_VER}::WebEngineWidgets
    Qt${QT_VER}::Network
    Qt${QT_VER}::Widgets
    Qt${QT_VER}::Test
    Qt${QT_VER}::Core
    simplebrowser
    cpaf_compression
    cpaf_utils
    cpaf_system
    cpaf_filesystem
    cpaf_crypto
    loki
    json
    interfaces
)

#target_link_libraries(${library_name} "cpaf_compression;cpaf_utils;cpaf_system;cpaf_filesystem;loki")
#target_link_libraries(${library_name} "json;interfaces")

set_target_properties(${library_name} PROPERTIES LINKER_LANGUAGE CXX)
target_include_directories(${library_name} PUBLIC
                        ${QT_WEBKIT_INCLUDES}
                        ${Boost_INCLUDE_DIRS}
                        ${Qt5Core_INCLUDE_DIRS}
                        ${CUSTOM_PHP_INCLUDES})
#     target_include_directories(${library_name} PUBLIC ${Boost_INCLUDE_DIRS} ${Qt5Core_INCLUDE_DIRS} ${PARENT_DIR} ${CUSTOM_PHP_INCLUDES} ${CMAKE_CURRENT_SOURCE_DIR})
target_include_directories(${library_name} PUBLIC ${PARENT_DIR} ${CMAKE_CURRENT_LIST_DIR})

target_compile_definitions(${library_name} PRIVATE PHP_HARDCODED_INI_FILE_PATH="${PHP_HARDCODED_INI_FILE_PATH}" )
target_compile_options(${library_name} PRIVATE ${COMMON_COMPILE_FLAGS})

add_subdirectories_standard()


