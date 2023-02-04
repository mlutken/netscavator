#IF ( NOT CBS_BUILD )
    set ( scriptcrawl_dir ${CMAKE_CURRENT_LIST_DIR} )
    add_subdirectory ( cpp_crawl )
#ELSE ()
#    project ( scriptcrawl )
#    INCLUDE ( $ENV{CBS_ROOT_DIR}/cbs_common_rules.cbs )
#    BUILD_PROJECT ( scriptcrawl )
#ENDIF ()



