IF ( NOT CBS_BUILD )
    set (library_name crawl)
    add_library(${library_name} STATIC "")

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
        # crawl/applicationutils
        ${CMAKE_CURRENT_LIST_DIR}/applicationutils/CrawlerCommandQueue.h
        ${CMAKE_CURRENT_LIST_DIR}/applicationutils/qt_compression.h
        ${CMAKE_CURRENT_LIST_DIR}/applicationutils/QtHttpDownloader.h
        # interfaces/containers
        ${CMAKE_CURRENT_LIST_DIR}/containers/DomActionMgr.h
        ${CMAKE_CURRENT_LIST_DIR}/containers/DomSearchMgr.h
        ${CMAKE_CURRENT_LIST_DIR}/containers/LookForWordMgr.h
        ${CMAKE_CURRENT_LIST_DIR}/containers/ModifierMgr.h
        ${CMAKE_CURRENT_LIST_DIR}/containers/NetworkActivityLogger.h
        ${CMAKE_CURRENT_LIST_DIR}/containers/SettingsMgr.h
        ${CMAKE_CURRENT_LIST_DIR}/containers/UrlQueue.h
        ${CMAKE_CURRENT_LIST_DIR}/containers/WordMonitor.h
        # crawl/creatorutils
#        ${CMAKE_CURRENT_LIST_DIR}/creatorutils/DomTreeTextHtmlGen.h
        # crawl/locale
        ${CMAKE_CURRENT_LIST_DIR}/locale/default_locales.h
        # crawl/navigator
        ${CMAKE_CURRENT_LIST_DIR}/navigator/AutoInputLocales.h
        ${CMAKE_CURRENT_LIST_DIR}/navigator/AutoInputState.h
        ${CMAKE_CURRENT_LIST_DIR}/navigator/DomClickNextState.h
        ${CMAKE_CURRENT_LIST_DIR}/navigator/DomNavigator.h
        ${CMAKE_CURRENT_LIST_DIR}/navigator/DomPosClickState.h
        ${CMAKE_CURRENT_LIST_DIR}/navigator/DropDownSelectState.h
        ${CMAKE_CURRENT_LIST_DIR}/navigator/InputOptionsState.h
        ${CMAKE_CURRENT_LIST_DIR}/navigator/JavascriptExecuteState.h
        ${CMAKE_CURRENT_LIST_DIR}/navigator/NavigateStateBase.h
        ${CMAKE_CURRENT_LIST_DIR}/navigator/NavigatorActionsClickAllExecutor.h
        ${CMAKE_CURRENT_LIST_DIR}/navigator/NavigatorActionsExecutor.h
        ${CMAKE_CURRENT_LIST_DIR}/navigator/SiteMapGetter.h
        ${CMAKE_CURRENT_LIST_DIR}/navigator/StateMachineMgr.h
        ${CMAKE_CURRENT_LIST_DIR}/navigator/StringSequenceState.h
        ${CMAKE_CURRENT_LIST_DIR}/navigator/UrlLoadState.h
        # crawl/parser
        ${CMAKE_CURRENT_LIST_DIR}/parser/DataWriterJson.h
        ${CMAKE_CURRENT_LIST_DIR}/parser/DataWriterXml.h
        ${CMAKE_CURRENT_LIST_DIR}/parser/DomActionAbstraction.h
        ${CMAKE_CURRENT_LIST_DIR}/parser/DomSeq.h
        ${CMAKE_CURRENT_LIST_DIR}/parser/linear_dom_algorithms.h
        ${CMAKE_CURRENT_LIST_DIR}/parser/LinearDomSearch.h
        ${CMAKE_CURRENT_LIST_DIR}/parser/LinksGetter.h
        ${CMAKE_CURRENT_LIST_DIR}/parser/LookForWordDomFinder.h
        ${CMAKE_CURRENT_LIST_DIR}/parser/StringSearch.h
        # crawl/scripting
        ${CMAKE_CURRENT_LIST_DIR}/scripting/ScriptExecutor.h
        # crawl/
        ${CMAKE_CURRENT_LIST_DIR}/Crawler.h
        ${CMAKE_CURRENT_LIST_DIR}/KeepActiveThread.h
        ${CMAKE_CURRENT_LIST_DIR}/MinerWorker.h
        ${CMAKE_CURRENT_LIST_DIR}/ScriptMiner.h

        PRIVATE
        # crawl/applicationutils
        ${CMAKE_CURRENT_LIST_DIR}/applicationutils/CrawlerCommandQueue.cpp
        ${CMAKE_CURRENT_LIST_DIR}/applicationutils/qt_compression.cpp
        ${CMAKE_CURRENT_LIST_DIR}/applicationutils/QtHttpDownloader.cpp
        # interfaces/containers
        ${CMAKE_CURRENT_LIST_DIR}/containers/DomActionMgr.cpp
        ${CMAKE_CURRENT_LIST_DIR}/containers/DomSearchMgr.cpp
        ${CMAKE_CURRENT_LIST_DIR}/containers/LookForWordMgr.cpp
        ${CMAKE_CURRENT_LIST_DIR}/containers/ModifierMgr.cpp
        ${CMAKE_CURRENT_LIST_DIR}/containers/NetworkActivityLogger.cpp
        ${CMAKE_CURRENT_LIST_DIR}/containers/SettingsMgr.cpp
        ${CMAKE_CURRENT_LIST_DIR}/containers/UrlQueue.cpp
        ${CMAKE_CURRENT_LIST_DIR}/containers/WordMonitor.cpp
        # crawl/creatorutils
#        ${CMAKE_CURRENT_LIST_DIR}/creatorutils/DomTreeTextHtmlGen.cpp
        # crawl/locale
        ${CMAKE_CURRENT_LIST_DIR}/locale/default_locales.cpp
        # crawl/navigator
        ${CMAKE_CURRENT_LIST_DIR}/navigator/AutoInputLocales.cpp
        ${CMAKE_CURRENT_LIST_DIR}/navigator/AutoInputState.cpp
        ${CMAKE_CURRENT_LIST_DIR}/navigator/DomClickNextState.cpp
        ${CMAKE_CURRENT_LIST_DIR}/navigator/DomNavigator.cpp
        ${CMAKE_CURRENT_LIST_DIR}/navigator/DomPosClickState.cpp
        ${CMAKE_CURRENT_LIST_DIR}/navigator/DropDownSelectState.cpp
        ${CMAKE_CURRENT_LIST_DIR}/navigator/InputOptionsState.cpp
        ${CMAKE_CURRENT_LIST_DIR}/navigator/JavascriptExecuteState.cpp
        ${CMAKE_CURRENT_LIST_DIR}/navigator/NavigateStateBase.cpp
        ${CMAKE_CURRENT_LIST_DIR}/navigator/NavigatorActionsClickAllExecutor.cpp
        ${CMAKE_CURRENT_LIST_DIR}/navigator/NavigatorActionsExecutor.cpp
        ${CMAKE_CURRENT_LIST_DIR}/navigator/SiteMapGetter.cpp
        ${CMAKE_CURRENT_LIST_DIR}/navigator/StateMachineMgr.cpp
        ${CMAKE_CURRENT_LIST_DIR}/navigator/StringSequenceState.cpp
        ${CMAKE_CURRENT_LIST_DIR}/navigator/UrlLoadState.cpp
        # crawl/parser
        ${CMAKE_CURRENT_LIST_DIR}/parser/DataWriterJson.cpp
        ${CMAKE_CURRENT_LIST_DIR}/parser/DataWriterXml.cpp
        ${CMAKE_CURRENT_LIST_DIR}/parser/DomActionAbstraction.cpp
        ${CMAKE_CURRENT_LIST_DIR}/parser/DomSeq.cpp
        ${CMAKE_CURRENT_LIST_DIR}/parser/linear_dom_algorithms.cpp
        ${CMAKE_CURRENT_LIST_DIR}/parser/LinearDomSearch.cpp
        ${CMAKE_CURRENT_LIST_DIR}/parser/LinksGetter.cpp
        ${CMAKE_CURRENT_LIST_DIR}/parser/LookForWordDomFinder.cpp
        ${CMAKE_CURRENT_LIST_DIR}/parser/StringSearch.cpp
        # crawl/scripting
        ${CMAKE_CURRENT_LIST_DIR}/scripting/ScriptExecutor.cpp
        # crawl/
        ${CMAKE_CURRENT_LIST_DIR}/Crawler.cpp
        ${CMAKE_CURRENT_LIST_DIR}/KeepActiveThread.cpp
        ${CMAKE_CURRENT_LIST_DIR}/MinerWorker.cpp
        ${CMAKE_CURRENT_LIST_DIR}/ScriptMiner.cpp

    )

    # --------------------------
    # --- Build instructions ---
    # --------------------------
    get_filename_component(PARENT_DIR ${CMAKE_CURRENT_SOURCE_DIR} DIRECTORY)
    target_link_libraries(${library_name} "webkitbrowser;scriptfunctions_php;script_embedding;interfaces;cpaf_concurrent;" )
    target_link_libraries(${library_name} "cpaf_net;cpaf_math;cpaf_time;json;utf8" )

#    target_link_libraries(${library_name} "cpaf_compression;cpaf_utils;cpaf_system;cpaf_filesystem;loki")

    set_target_properties(${library_name} PROPERTIES LINKER_LANGUAGE CXX)
    target_include_directories(${library_name} PUBLIC ${Qt5Network_INCLUDE_DIRS}
                                ${LOHMAN_JSON_INCLUDE_DIRS}
                                ${PARENT_DIR}
                                ${CMAKE_CURRENT_SOURCE_DIR})
    target_compile_options(${library_name} PRIVATE ${STANDARD_COMPILE_FLAGS})

    add_subdirectories_standard()

ELSE ()
    project ( crawl )
    INCLUDE ( $ENV{CBS_ROOT_DIR}/cbs_common_rules.cbs )
    BUILD_LIBRARY ( crawl )
ENDIF ()


