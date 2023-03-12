set (library_name cpp_crawl)
add_library(${library_name} MODULE "")


# ------------------------
# --- Find dependecies ---
# ------------------------
find_package(Qt${QT_VER} REQUIRED
    Core
    Widgets
)
find_package(Boost ${BOOST_MIN_VERSION} REQUIRED)

set (SCRIPTCRAWL_WRAP_CPP_PATH ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/scriptcrawl_wrap.cpp )


ADD_CUSTOM_COMMAND(
    OUTPUT 				${SCRIPTCRAWL_WRAP_CPP_PATH}
    SOURCE				${scriptcrawl_dir}/scriptcrawl.i
    COMMAND 			${swig_EXECUTABLE} -c++ -php5 -outdir ${CMAKE_RUNTIME_OUTPUT_DIRECTORY} -module ${library_name} -o ${SCRIPTCRAWL_WRAP_CPP_PATH} ${scriptcrawl_dir}/scriptcrawl.i
    WORKING_DIRECTORY	${CMAKE_RUNTIME_OUTPUT_DIRECTORY}
    DEPENDS				${scriptcrawl_dir}/scriptcrawl.i
)

# --------------------
# --- Source files ---
# --------------------
target_sources(${library_name}
    PUBLIC
    ${scriptcrawl_dir}/scriptcrawl.h
    ${scriptcrawl_dir}/scriptcrawl_private.h
    ${CMAKE_CURRENT_LIST_DIR}/scriptcrawl_module_cpp.h

    PRIVATE
    ${scriptcrawl_dir}/scriptcrawl.cpp
    ${scriptcrawl_dir}/scriptcrawl_private.cpp
    ${CMAKE_CURRENT_LIST_DIR}/scriptcrawl_module_cpp.cpp
    ${SCRIPTCRAWL_WRAP_CPP_PATH}
)

set_property(SOURCE ${SCRIPTCRAWL_WRAP_CPP_PATH} PROPERTY SKIP_AUTOGEN ON) # Prevent warnings from CMAKE_AUTOMOC

# --------------------------
# --- Build instructions ---
# --------------------------
get_filename_component(PARENT_DIR ${CMAKE_CURRENT_SOURCE_DIR} DIRECTORY)
target_link_libraries(${library_name} PUBLIC "${CUSTOM_PHP_BASE_DIR}/lib/libphp-sleipner5.so")
target_link_libraries(${library_name} PUBLIC "crawl;interfaces")
target_link_libraries(${library_name} PUBLIC "cpaf_net;loki")

set_target_properties(${library_name} PROPERTIES PREFIX "") # Prevent the default 'lib' prefix
set_target_properties(${library_name} PROPERTIES LINKER_LANGUAGE CXX)
target_include_directories(${library_name} PUBLIC ${Boost_INCLUDE_DIRS} ${Qt5Core_INCLUDE_DIRS} ${PARENT_DIR} ${CMAKE_CURRENT_SOURCE_DIR})
target_compile_options(${library_name} PRIVATE ${COMMON_COMPILE_FLAGS})

target_compile_definitions(${library_name} PUBLIC ZTS=1 )

if ( ${CMAKE_BUILD_TYPE} STREQUAL "Debug"  )
    target_compile_definitions(${library_name} PUBLIC ZEND_DEBUG=1 )
else ()
    target_compile_definitions(${library_name} PUBLIC ZEND_DEBUG=0 )
endif ()

add_custom_command(TARGET ${library_name} POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy
        ${CMAKE_BINARY_DIR}/lib/${library_name}${CMAKE_SHARED_LIBRARY_SUFFIX}
        ${CMAKE_BINARY_DIR}/bin/
)

add_subdirectories_standard()
