#include "launcherapplication.h"

#include <QWebSettings>
#include <QFile>
#include <QFileInfo>
#include <QFontDatabase>
#include <QRegExp>
#include <QGraphicsView>

#include "urlloader.h"
#include "utils.h"


void LauncherApplication::applyDefaultSettings()
{
    QWebSettings::setMaximumPagesInCache(4);

    QWebSettings::setObjectCacheCapacities((16*1024*1024) / 8, (16*1024*1024) / 8, 16*1024*1024);

    QWebSettings::globalSettings()->setAttribute(QWebSettings::PluginsEnabled, true);
    QWebSettings::globalSettings()->setAttribute(QWebSettings::DeveloperExtrasEnabled, true);
    QWebSettings::enablePersistentStorage();
}

LauncherApplication::LauncherApplication(int& argc, char** argv)
    : QApplication(argc, argv)
    , m_isRobotized(false)
    , m_robotTimeoutSeconds(0)
    , m_robotExtraTimeSeconds(0)
{
    // To allow QWebInspector's configuration persistence
    setOrganizationName("QtProject");
    setApplicationName("QtTestBrowser");
    setApplicationVersion("0.1");

    applyDefaultSettings();

    handleUserOptions();
}

void LauncherApplication::handleUserOptions()
{
    QStringList args = arguments();
    QFileInfo program(args.at(0));
    QString programName("QtTestBrowser");
    if (program.exists())
        programName = program.baseName();

    QList<QString> updateModes(enumToKeys(QGraphicsView::staticMetaObject,
            "ViewportUpdateMode", "ViewportUpdate"));

    if (args.contains("-help")) {
        qDebug() << "Usage:" << programName.toLatin1().data()
             << "[-graphicsbased]"
             << "[-no-compositing]"
#if defined(QT_CONFIGURED_WITH_OPENGL)
             << "[-gl-viewport]"
#endif
             << "[-opengl-viewport]"
             << "[-webgl]"
             << QString("[-viewport-update-mode %1]").arg(formatKeys(updateModes)).toLatin1().data()
#if !defined(QT_NO_NETWORKDISKCACHE) && !defined(QT_NO_DESKTOPSERVICES)
             << "[-disk-cache]"
#endif
             << "[-cache-webview]"
             << "[-maximize]"
             << "[-show-fps]"
             << "[-r list]"
             << "[-robot-timeout seconds]"
             << "[-robot-extra-time seconds]"
             << "[-inspector-url location]"
             << "[-tiled-backing-store]"
             << "[-resizes-to-contents]"
             << "[-local-storage-enabled]"
             << "[-no-disk-cookies]"
             << "[-offline-storage-database-enabled]"
             << "[-offline-web-application-cache-enabled]"
             << "[-set-offline-storage-default-quota maxSize]"
//#if HAVE(QTTESTSUPPORT)
//             << "[-use-test-fonts]"
//#endif
             << "[-print-loaded-urls]"
             << "URLs";
        appQuit(0);
    }

    const bool defaultForAnimations = args.contains("-default-animations");
    if (args.contains("-graphicsbased") || defaultForAnimations)
        m_windowOptions.useGraphicsView = true;

    if (args.contains("-no-compositing")) {
        m_windowOptions.useCompositing = false;
    }

    if (args.contains("-show-fps")) {
        requiresGraphicsView("-show-fps");
        m_windowOptions.showFrameRate = true;
    }

    if (args.contains("-disk-cache")) {
#if !defined(QT_NO_NETWORKDISKCACHE) && !defined(QT_NO_DESKTOPSERVICES)
        m_windowOptions.useDiskCache = true;
#else
    appQuit(1, "-disk-cache only works if QNetworkDiskCache and QDesktopServices is enabled in your Qt build.");
#endif
    }

    if (args.contains("-cache-webview") || defaultForAnimations) {
        requiresGraphicsView("-cache-webview");
        m_windowOptions.cacheWebView = true;
    }

    if (args.contains("-tiled-backing-store")) {
        requiresGraphicsView("-tiled-backing-store");
        m_windowOptions.useTiledBackingStore = true;
    }

    if (args.contains("-resizes-to-contents")) {
        requiresGraphicsView("-resizes-to-contents");
        m_windowOptions.resizesToContents = true;
    }

    if (args.contains("-local-storage-enabled"))
        m_windowOptions.useLocalStorage = true;

    if (args.contains("-no-disk-cookies"))
        m_windowOptions.useDiskCookies = false;

    if (args.contains("-maximize"))
        m_windowOptions.startMaximized = true;

    if (args.contains("-offline-storage-database-enabled"))
        m_windowOptions.useOfflineStorageDatabase = true;

    if (args.contains("-offline-web-application-cache-enabled"))
        m_windowOptions.useOfflineWebApplicationCache = true;

    int setOfflineStorageDefaultQuotaIndex = args.indexOf("-set-offline-storage-default-quota");
    if (setOfflineStorageDefaultQuotaIndex != -1) {
        unsigned int maxSize = takeOptionValue(&args, setOfflineStorageDefaultQuotaIndex).toUInt();
        m_windowOptions.offlineStorageDefaultQuotaSize = maxSize;
    }

    if (defaultForAnimations)
        m_windowOptions.viewportUpdateMode = QGraphicsView::BoundingRectViewportUpdate;

    QString arg1("-viewport-update-mode");
    int modeIndex = args.indexOf(arg1);
    if (modeIndex != -1) {
        requiresGraphicsView(arg1);

        QString mode = takeOptionValue(&args, modeIndex);
        if (mode.isEmpty())
            appQuit(1, QString("%1 needs a value of one of [%2]").arg(arg1).arg(formatKeys(updateModes)));
        int idx = updateModes.indexOf(mode);
        if (idx == -1)
            appQuit(1, QString("%1 value has to be one of [%2]").arg(arg1).arg(formatKeys(updateModes)));

        m_windowOptions.viewportUpdateMode = static_cast<QGraphicsView::ViewportUpdateMode>(idx);
    }
#ifdef QT_CONFIGURED_WITH_OPENGL
    if (args.contains("-gl-viewport") || defaultForAnimations) {
        requiresGraphicsView("-gl-viewport");
        windowOptions.useQGLWidgetViewport = true;
    }

#endif
    if (args.contains("-webgl")) {
        m_windowOptions.useWebGL = true;
    }

    if (args.contains("-opengl-viewport")) {
        requiresGraphicsView("-opengl-viewport");
        m_windowOptions.useQOpenGLWidgetViewport = true;
    }


//#if HAVE(QTTESTSUPPORT)
//    if (args.contains("-use-test-fonts"))
//        WebKit::QtTestSupport::initializeTestFonts();
//#endif

    if (args.contains("-print-loaded-urls"))
        m_windowOptions.printLoadedUrls = true;

    QString inspectorUrlArg("-inspector-url");
    int inspectorUrlIndex = args.indexOf(inspectorUrlArg);
    if (inspectorUrlIndex != -1)
       m_windowOptions.inspectorUrl = takeOptionValue(&args, inspectorUrlIndex);

    QString remoteInspectorPortArg("-remote-inspector-port");
    int remoteInspectorPortIndex = args.indexOf(remoteInspectorPortArg);
    if (remoteInspectorPortIndex != -1)
        m_windowOptions.remoteInspectorPort = takeOptionValue(&args, remoteInspectorPortIndex).toInt();

    int robotIndex = args.indexOf("-r");
    if (robotIndex != -1) {
        QString listFile = takeOptionValue(&args, robotIndex);
        if (listFile.isEmpty())
            appQuit(1, "-r needs a list file to start in robotized mode");
        if (!QFile::exists(listFile))
            appQuit(1, "The list file supplied to -r does not exist.");

        m_isRobotized = true;
        m_urls = QStringList(listFile);
    } else {
        int lastArg = args.lastIndexOf(QRegExp("^-.*"));
        m_urls = (lastArg != -1) ? args.mid(++lastArg) : args.mid(1);
    }

    int robotTimeoutIndex = args.indexOf("-robot-timeout");
    if (robotTimeoutIndex != -1)
        m_robotTimeoutSeconds = takeOptionValue(&args, robotTimeoutIndex).toInt();

    int robotExtraTimeIndex = args.indexOf("-robot-extra-time");
    if (robotExtraTimeIndex != -1)
        m_robotExtraTimeSeconds = takeOptionValue(&args, robotExtraTimeIndex).toInt();
}


void LauncherApplication::requiresGraphicsView(const QString& option)
{
    if (m_windowOptions.useGraphicsView)
        return;
    appQuit(1, QString("%1 only works in combination with the -graphicsbased option").arg(option));
}

