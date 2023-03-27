IF ( NOT CBS_BUILD )
    set (library_name gui)
    add_library(${library_name} STATIC "")

    # ------------------------
    # --- Find dependecies ---
    # ------------------------
    # See: https://doc.qt.io/qt-5/cmake-manual.html
    find_package(Qt${QT_VER} REQUIRED
        Core
        Gui
        Widgets
    )

    find_package(Boost ${BOOST_MIN_VERSION} REQUIRED)

    # --------------------
    # --- Source files ---
    # --------------------
    target_sources(${library_name}
        PUBLIC
        ${CMAKE_CURRENT_LIST_DIR}/BrowserWidgetUi.h
        ${CMAKE_CURRENT_LIST_DIR}/CrawlerMainWindowUi.h
        ${CMAKE_CURRENT_LIST_DIR}/CrawlerSimple.h
        ${CMAKE_CURRENT_LIST_DIR}/CreatorDomTableView.h
        ${CMAKE_CURRENT_LIST_DIR}/CreatorLinearDomTableModel.h
        ${CMAKE_CURRENT_LIST_DIR}/CreatorMainWindowUi.h
        ${CMAKE_CURRENT_LIST_DIR}/CreatorMainWidgetUi.h
        ${CMAKE_CURRENT_LIST_DIR}/CreatorTextDomTreeView.h
        ${CMAKE_CURRENT_LIST_DIR}/CreatorWebkitWebViewUi.h
        ${CMAKE_CURRENT_LIST_DIR}/DesignWidgetUi.h
        ${CMAKE_CURRENT_LIST_DIR}/DomSeqWidget.h
        ${CMAKE_CURRENT_LIST_DIR}/DomSequencesTreeModel.h
        ${CMAKE_CURRENT_LIST_DIR}/DomSequencesTreeViewUi.h
        ${CMAKE_CURRENT_LIST_DIR}/DomTreeModel.h
        ${CMAKE_CURRENT_LIST_DIR}/DomTreeView.h
        ${CMAKE_CURRENT_LIST_DIR}/DebugToolBarUI.h
        ${CMAKE_CURRENT_LIST_DIR}/editor_utils.h
        ${CMAKE_CURRENT_LIST_DIR}/EditorViewUi.h
        ${CMAKE_CURRENT_LIST_DIR}/EditorWidgetUi.h
        ${CMAKE_CURRENT_LIST_DIR}/gui_utils.h
        ${CMAKE_CURRENT_LIST_DIR}/GuiActionsMgr.h
        ${CMAKE_CURRENT_LIST_DIR}/GuiGlobals.h
        ${CMAKE_CURRENT_LIST_DIR}/HelpWidgetUi.h
        ${CMAKE_CURRENT_LIST_DIR}/HtmlSourceWidgetUi.h
        ${CMAKE_CURRENT_LIST_DIR}/LeftPanelUi.h
        ${CMAKE_CURRENT_LIST_DIR}/MainToolBarUI.h
        ${CMAKE_CURRENT_LIST_DIR}/MinerCtrl.h
        ${CMAKE_CURRENT_LIST_DIR}/OutputViewUi.h
        ${CMAKE_CURRENT_LIST_DIR}/OutputViewCtrl.h
        ${CMAKE_CURRENT_LIST_DIR}/PhpQuickUi.h
        ${CMAKE_CURRENT_LIST_DIR}/ProjectsViewUi.h
        ${CMAKE_CURRENT_LIST_DIR}/ProjectTableModel.h
        ${CMAKE_CURRENT_LIST_DIR}/ScriptCtrl.h
        ${CMAKE_CURRENT_LIST_DIR}/UrlInputUi.h
        ${CMAKE_CURRENT_LIST_DIR}/UrlQueueTableModel.h
        ${CMAKE_CURRENT_LIST_DIR}/WebkitWebView.h
        ${CMAKE_CURRENT_LIST_DIR}/WelcomeWidgetUi.h
        ${CMAKE_CURRENT_LIST_DIR}/WebkitCreatorFactory.h
        ${CMAKE_CURRENT_LIST_DIR}/SimpleCreatorFactory.h
        ${CMAKE_CURRENT_LIST_DIR}/SimpleCrawlerFactory.h

        # Debugging files
        ${CMAKE_CURRENT_LIST_DIR}/treeitem.h
        ${CMAKE_CURRENT_LIST_DIR}/treemodel.h
        PRIVATE
        ${CMAKE_CURRENT_LIST_DIR}/BrowserWidgetUi.cpp
        ${CMAKE_CURRENT_LIST_DIR}/CrawlerMainWindowUi.cpp
        ${CMAKE_CURRENT_LIST_DIR}/CrawlerSimple.cpp
        ${CMAKE_CURRENT_LIST_DIR}/CreatorDomTableView.cpp
        ${CMAKE_CURRENT_LIST_DIR}/CreatorLinearDomTableModel.cpp
        ${CMAKE_CURRENT_LIST_DIR}/CreatorMainWindowUi.cpp
        ${CMAKE_CURRENT_LIST_DIR}/CreatorMainWidgetUi.cpp
        ${CMAKE_CURRENT_LIST_DIR}/CreatorTextDomTreeView.cpp
        ${CMAKE_CURRENT_LIST_DIR}/CreatorWebkitWebViewUi.cpp
        ${CMAKE_CURRENT_LIST_DIR}/DesignWidgetUi.cpp
        ${CMAKE_CURRENT_LIST_DIR}/DomSeqWidget.cpp
        ${CMAKE_CURRENT_LIST_DIR}/DomSequencesTreeModel.cpp
        ${CMAKE_CURRENT_LIST_DIR}/DomSequencesTreeViewUi.cpp
        ${CMAKE_CURRENT_LIST_DIR}/DomTreeModel.cpp
        ${CMAKE_CURRENT_LIST_DIR}/DomTreeView.cpp
        ${CMAKE_CURRENT_LIST_DIR}/DebugToolBarUI.cpp
        ${CMAKE_CURRENT_LIST_DIR}/editor_utils.cpp
        ${CMAKE_CURRENT_LIST_DIR}/EditorViewUi.cpp
        ${CMAKE_CURRENT_LIST_DIR}/EditorWidgetUi.cpp
        ${CMAKE_CURRENT_LIST_DIR}/gui_utils.cpp
        ${CMAKE_CURRENT_LIST_DIR}/GuiActionsMgr.cpp
        ${CMAKE_CURRENT_LIST_DIR}/GuiGlobals.cpp
        ${CMAKE_CURRENT_LIST_DIR}/HelpWidgetUi.cpp
        ${CMAKE_CURRENT_LIST_DIR}/HtmlSourceWidgetUi.cpp
        ${CMAKE_CURRENT_LIST_DIR}/LeftPanelUi.cpp
        ${CMAKE_CURRENT_LIST_DIR}/MainToolBarUI.cpp
        ${CMAKE_CURRENT_LIST_DIR}/MinerCtrl.cpp
        ${CMAKE_CURRENT_LIST_DIR}/OutputViewUi.cpp
        ${CMAKE_CURRENT_LIST_DIR}/OutputViewCtrl.cpp
        ${CMAKE_CURRENT_LIST_DIR}/PhpQuickUi.cpp
        ${CMAKE_CURRENT_LIST_DIR}/ProjectsViewUi.cpp
        ${CMAKE_CURRENT_LIST_DIR}/ProjectTableModel.cpp
        ${CMAKE_CURRENT_LIST_DIR}/ScriptCtrl.cpp
        ${CMAKE_CURRENT_LIST_DIR}/UrlInputUi.cpp
        ${CMAKE_CURRENT_LIST_DIR}/UrlQueueTableModel.cpp
        ${CMAKE_CURRENT_LIST_DIR}/WebkitWebView.cpp
        ${CMAKE_CURRENT_LIST_DIR}/WelcomeWidgetUi.cpp
        ${CMAKE_CURRENT_LIST_DIR}/WebkitCreatorFactory.cpp
        ${CMAKE_CURRENT_LIST_DIR}/SimpleCreatorFactory.cpp
        ${CMAKE_CURRENT_LIST_DIR}/SimpleCrawlerFactory.cpp
        # Debugging files
        ${CMAKE_CURRENT_LIST_DIR}/treeitem.cpp
        ${CMAKE_CURRENT_LIST_DIR}/treemodel.cpp
    )

    # --------------------------
    # --- Build instructions ---
    # --------------------------
    get_filename_component(PARENT_DIR ${CMAKE_CURRENT_SOURCE_DIR} DIRECTORY)
    target_link_libraries(${library_name} "webkitbrowser;simplebrowser;qscintilla2;script_embedding;scriptfunctions_php;interfaces")
    target_link_libraries(${library_name} "cpaf_unicode")

    set_target_properties(${library_name} PROPERTIES LINKER_LANGUAGE CXX)
    target_include_directories(${library_name} PUBLIC ${Boost_INCLUDE_DIRS} ${Qt5Core_INCLUDE_DIRS} ${PARENT_DIR} ${CMAKE_CURRENT_SOURCE_DIR})

    add_subdirectories_standard()

ELSE ()
    project ( gui )
    include ( $ENV{CBS_ROOT_DIR}/cbs_common_rules.cbs )
    BUILD_LIBRARY ( gui )
ENDIF ()





