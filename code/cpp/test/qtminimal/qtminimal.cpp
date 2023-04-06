
//https://code.qt.io/cgit/qt/qtwebengine.git/tree/examples/webenginewidgets/minimal?h=5.15.2

#include <iostream>
#include <QApplication>
#include <QUrl>
#include <QPushButton>
#include <QWebEngineView>
#include <QLibraryInfo>


//https://doc.qt.io/qt-6/qtwebengine-deploying.html

using namespace std;

QUrl commandLineUrlArgument()
{
    const QStringList args = QCoreApplication::arguments();
    for (const QString &arg : args.mid(1)) {
        if (!arg.startsWith(QLatin1Char('-')))
            return QUrl::fromUserInput(arg);
    }
    return QUrl(QStringLiteral("https://cykelshoppen.dk/"));
}

int main(int argc, char *argv[])
{
//    QCoreApplication::setOrganizationName("QtExamples");
//    QCoreApplication::setAttribute(Qt::AA_EnableHighDpiScaling);

//QCoreApplication::applicationDirPath() + QDir::separator() + "qt.conf"
    QApplication app(argc, argv);

    cerr << "QCoreApplication::applicatkionDirPath(): '" << QCoreApplication::applicationDirPath().toUtf8().constData() << "'\n";
    cerr << "QLibraryInfo::PrefixPath: '" << QLibraryInfo::location(QLibraryInfo::PrefixPath).toUtf8().constData() << "'\n";
    cerr << "QLibraryInfo::DocumentationPath: '" << QLibraryInfo::location(QLibraryInfo::DocumentationPath).toUtf8().constData() << "'\n";
    cerr << "QLibraryInfo::HeadersPath: '" << QLibraryInfo::location(QLibraryInfo::HeadersPath).toUtf8().constData() << "'\n";
    cerr << "QLibraryInfo::LibrariesPath: '" << QLibraryInfo::location(QLibraryInfo::LibrariesPath).toUtf8().constData() << "'\n";
    cerr << "QLibraryInfo::LibraryExecutablesPath: '" << QLibraryInfo::location(QLibraryInfo::LibraryExecutablesPath).toUtf8().constData() << "'\n";
    cerr << "QLibraryInfo::BinariesPath: '" << QLibraryInfo::location(QLibraryInfo::BinariesPath).toUtf8().constData() << "'\n";
    cerr << "QLibraryInfo::PluginsPath: '" << QLibraryInfo::location(QLibraryInfo::PluginsPath).toUtf8().constData() << "'\n";
    cerr << "QLibraryInfo::QmlImportsPath: '" << QLibraryInfo::location(QLibraryInfo::QmlImportsPath).toUtf8().constData() << "'\n";
    cerr << "QLibraryInfo::Qml2ImportsPath: '" << QLibraryInfo::location(QLibraryInfo::Qml2ImportsPath).toUtf8().constData() << "'\n";
    cerr << "QLibraryInfo::ArchDataPath: '" << QLibraryInfo::location(QLibraryInfo::ArchDataPath).toUtf8().constData() << "'\n";
    cerr << "QLibraryInfo::DataPath: '" << QLibraryInfo::location(QLibraryInfo::DataPath).toUtf8().constData() << "'\n";
    cerr << "QLibraryInfo::TranslationsPath: '" << QLibraryInfo::location(QLibraryInfo::TranslationsPath).toUtf8().constData() << "'\n";
    cerr << "QLibraryInfo::ExamplesPath: '" << QLibraryInfo::location(QLibraryInfo::ExamplesPath).toUtf8().constData() << "'\n";
    cerr << "QLibraryInfo::TestsPath: '" << QLibraryInfo::location(QLibraryInfo::TestsPath).toUtf8().constData() << "'\n";
    cerr << "QLibraryInfo::SettingsPath: '" << QLibraryInfo::location(QLibraryInfo::SettingsPath).toUtf8().constData() << "'\n";

    QWebEngineView* view = new QWebEngineView();


//    QPushButton button ("Hello world!");
//    button.show();

    view->setUrl(commandLineUrlArgument());
    view->resize(1024, 750);
    view->show();

    return app.exec();
}

/*
assistant-qt6 - Qt 6 Assistant
designer-qt6 - Qt 6 Designer
libkf5bluezqt6 - Qt wrapper for bluez
libkf5modemmanagerqt6 - Qt wrapper library for ModemManager
libkf5networkmanagerqt6 - Qt wrapper for NetworkManager - library
libqcoro6core0 - C++20 coroutines for Qt6 - Core
libqcoro6dbus0 - C++20 coroutines for Qt6 - DBus
libqcoro6network0 - C++20 coroutines for Qt6 - Network
libqt63danimation6 - Qt 6 3D Animation library
libqt63dcore6 - Qt 6 3D Core library
libqt63dextras6 - Qt 6 3D extras library
libqt63dinput6 - Qt 6 3D Input library
libqt63dlogic6 - Qt 6 3D Logic library
libqt63dquick6 - Qt 6 3D Quick library
libqt63dquickanimation6 - Qt 6 3D Quick Animation library
libqt63dquickextras6 - Qt 6 3D Quick extras library
libqt63dquickinput6 - Qt 6 3D Quick Input library
libqt63dquickrender6 - Qt 6 3D Quick Renderer library
libqt63dquickscene2d6 - Qt 6 3D Quick Scene 2D library
libqt63drender6 - Qt 6 3D Renderer library
libqt6bluetooth6 - Qt 6 Connectivity Bluetooth library
libqt6bluetooth6-bin - Qt 6 Connectivity Bluetooth module helper binaries
libqt6bodymovin6 - Qt 6 Lottie Bodymovin library
libqt6bodymovin6-dev - Qt 6 Lottie - development files
libqt6charts6 - Qt 6 charts library
libqt6charts6-dev - Qt 6 charts - development files
libqt6chartsqml6 - Qt 6 charts QML library
libqt6concurrent6 - Qt 6 concurrent module
libqt6core5compat6 - Qt 6 Qt5Compat library
libqt6core5compat6-dev - Qt 6 Qt5Compat - development files
libqt6core6 - Qt 6 core module
libqt6datavisualization6 - Qt 6 Data Visualization library
libqt6datavisualization6-dev - Qt 6 Data Visualization - development files
libqt6dbus6 - Qt 6 D-Bus module
libqt6designer6 - Qt 6 Designer library
libqt6designercomponents6 - Qt 6 Designer Components library
libqt6gui6 - Qt 6 GUI module
libqt6help6 - Qt 6 Help library
libqt6hunspellinputmethod6 - Qt 6 Hunspell Input Method helper library
libqt6keychain1 - Qt API to store passwords (QT6 version)
libqt6labsanimation6 - Qt 6 Labs Animation library
libqt6labsfolderlistmodel6 - Qt 6 Labs FolderListModel library
libqt6labsqmlmodels6 - Qt 6 Labs QML Models library
libqt6labssettings6 - Qt 6 Labs Settings library
libqt6labssharedimage6 - Qt 6 Labs Shared Image library
libqt6labswavefrontmesh6 - Qt 6 Labs WavefrontMesh library
libqt6multimedia6 - Qt 6 Multimedia library
libqt6multimediaquick6 - Qt 6 Multimedia Quick library
libqt6multimediawidgets6 - Qt 6 Multimedia Widgets library
libqt6network6 - Qt 6 network module
libqt6networkauth6 - Qt 6 QtNetworkAuth library
libqt6networkauth6-dev - Qt 6 QtNetworkAuth - development files
libqt6nfc6 - Qt 6 Connectivity NFC library
libqt6opengl6 - Qt 6 OpenGL module
libqt6opengl6-dev - Qt 6 OpenGL library development files
libqt6openglwidgets6 - Qt 6 OpenGL widgets module
libqt6pdf6 - Qt 6 PDF library
libqt6pdfquick6 - Qt 6 PDF Quick library
libqt6pdfwidgets6 - Qt 6 PDF Widgets library
libqt6positioning6 - Qt 6 Positioning library
libqt6positioning6-plugins - Qt 6 Positioning module - position plugins
libqt6positioningquick6 - Qt 6 Positioning library - Qt Quick library
libqt6printsupport6 - Qt 6 print support module
libqt6qml6 - Qt 6 QML module
libqt6qmlcore6 - Qt 6 QML Core library
libqt6qmllocalstorage6 - Qt 6 QML Local Storage library
libqt6qmlmodels6 - Qt 6 QML Models library
libqt6qmlworkerscript6 - Qt 6 QML WorkerScript library
libqt6qmlxmllistmodel6 - Qt 6 QML XmlListModel library
libqt6quick3d6 - Qt 6 Quick 3D library
libqt6quick3dassetimport6 - Qt 6 Quick 3D Asset Import library
libqt6quick3dassetutils6 - Qt 6 Quick 3D Asset Utils library
libqt6quick3deffects6 - Qt 6 Quick 3D Effects library
libqt6quick3dhelpers6 - Qt 6 Quick 3D Helpers library
libqt6quick3diblbaker6 - Qt 6 Quick 3D IblBaker library
libqt6quick3dparticles6 - Qt 6 Quick 3D Particles library
libqt6quick3druntimerender6 - Qt 6 Quick 3D Runtime Renderer library
libqt6quick3dutils6 - Qt 6 Quick 3D Utils library
libqt6quick6 - Qt 6 Quick library
libqt6quickcontrols2-6 - Qt 6 Quick Controls 2 library
libqt6quickcontrols2impl6 - Qt 6 Quick Controls 2 Impl library
libqt6quickdialogs2-6 - Qt 6 Quick Dialogs 2 library
libqt6quickdialogs2quickimpl6 - Qt 6 Quick Dialogs 2 Quick Impl library
libqt6quickdialogs2utils6 - Qt 6 Quick Dialogs 2 Utils library
libqt6quicklayouts6 - Qt 6 Quick Layouts library
libqt6quickparticles6 - Qt 6 Quick particles library
libqt6quickshapes6 - Qt 6 Quick Shapes library
libqt6quicktemplates2-6 - Qt 6 Quick Templates 2 library
libqt6quicktest6 - Qt 6 Quick Test library
libqt6quicktimeline6 - Qt 6 Quick Timeline library
libqt6quicktimeline6-dev - Qt 6 Quick Timeline - development files
libqt6quickwidgets6 - Qt 6 Quick Widgets library
libqt6remoteobjects6 - Qt 6 Remote Objects library
libqt6remoteobjects6-bin - Qt 6 Remote Objects - the Replica Compiler (repc)
libqt6remoteobjectsqml6 - Qt 6 Remote Objects QML library
libqt6scxml6 - Qt 6 SCXML library
libqt6scxml6-bin - Qt 6 SCXML helper binaries
libqt6scxmlqml6 - Qt 6 SCXML QML library
libqt6sensors6 - Qt 6 Sensors library
libqt6sensors6-dev - Qt 6 Sensors - development files
libqt6sensorsquick6 - Qt 6 Sensors Quick library
libqt6serialbus6 - Qt 6 Serial Bus library
libqt6serialbus6-bin - Qt 6 Serial Bus helper binaries
libqt6serialbus6-dev - Qt 6 Serial Bus development files
libqt6serialbus6-plugins - Qt 6 Serial Bus plugins
libqt6serialport6 - Qt 6 serial port support library
libqt6serialport6-dev - Qt 6 serial port development files
libqt6shadertools6 - Qt 6 shader tools module
libqt6shadertools6-dev - Qt 6 shader tools module - development files
libqt6sql6 - Qt 6 SQL module
libqt6sql6-ibase - Qt 6 Firebird database driver
libqt6sql6-mysql - Qt 6 MySQL database driver
libqt6sql6-odbc - Qt 6 ODBC database driver
libqt6sql6-psql - Qt 6 PostgreSQL database driver
libqt6sql6-sqlite - Qt 6 SQLite 3 database driver
libqt6statemachine6 - Qt 6 State Machine library
libqt6statemachineqml6 - Qt 6 State Machine QML library
libqt6svg6 - Qt 6 SVG library
libqt6svg6-dev - Qt 6 SVG - development files
libqt6svgwidgets6 - Qt 6 SVG Widgets library
libqt6test6 - Qt 6 test module
libqt6uitools6 - Qt 6 UI tools library
libqt6virtualkeyboard6 - Qt 6 Virtual Keyboard library
libqt6virtualkeyboard6-dev - Qt 6 Virtual Keyboard - development files
libqt6waylandclient6 - Qt 6 Wayland Client library
libqt6waylandcompositor6 - Qt 6 Wayland Compositor library
libqt6waylandeglclienthwintegration6 - Qt 6 Wayland WaylandEglClientHwIntegration library
libqt6waylandeglcompositorhwintegration6 - Qt 6 Wayland WaylandEglCompositorHwIntegration library
libqt6webchannel6 - Qt 6 WebChannel library
libqt6webchannel6-dev - Qt 6 WebChannel library - development files
libqt6webengine6-data - Qt 6 Web content engine library - data
libqt6webenginecore6 - Qt 6 WebEngine Core library
libqt6webenginecore6-bin - Qt 6 WebEngine Core binaries
libqt6webenginequick6 - Qt 6 WebEngine Quick library
libqt6webenginequickdelegatesqml6 - Qt 6 WebEngine Quick Delegates QML library
libqt6webenginewidgets6 - Qt 6 WebEngine Widgets library
libqt6websockets6 - Qt 6 WebSockets library
libqt6websockets6-dev - Qt 6 WebSockets library - development files
libqt6webview6 - Qt 6 WebView library
libqt6webviewquick6 - Qt 6 WebView Quick library
libqt6widgets6 - Qt 6 widgets module
libqt6wlshellintegration6 - Qt 6 Wayland ShellIntegration library
libqt6xml6 - Qt 6 XML module
linguist-qt6 - Qt 6 Linguist
python3-pyqt6.sip - runtime module for Python extensions using SIP
qcoro-qt6-dev - C++20 coroutines for Qt6 - development
qml-qt6 - Qt 6 QML viewer
qmlscene-qt6 - Qt 6 QML scene viewer
qt6-3d-assimpsceneimport-plugin - Qt 6 3D GL Assimp Scene Import plugin
qt6-3d-defaultgeometryloader-plugin - Qt 3D default geometry loader plugin
qt6-3d-dev - Qt 6 3D - development files
qt6-3d-gltfsceneio-plugin - Qt 6 3D GL Transmission Format Scene IO plugin
qt6-3d-scene2d-plugin - Qt 6 3D Scene 2D plugin
qt6-base-dev - Qt 6 base development files
qt6-base-dev-tools - Qt 6 base development programs
qt6-base-private-dev - Qt 6 base private development files
qt6-connectivity-dev - Qt 6 Connectivity - development files
qt6-declarative-dev - Qt 6 declarative development files
qt6-declarative-dev-tools - Qt 6 declarative development programs
qt6-declarative-private-dev - Qt 6 declarative private development files
qt6-documentation-tools - Qt 6 documentation tools
qt6-gtk-platformtheme - Qt 6 GTK+ 3 platform theme
qt6-image-formats-plugin-pdf - Qt 6 PDF image format plugin
qt6-image-formats-plugins - Qt 6 Image Formats plugins
qt6-l10n-tools - Qt 6 translation tools
qt6-multimedia-dev - Qt 6 Multimedia - development files
qt6-pdf-dev - Qt 6 PDF library - development files
qt6-positioning-dev - Qt 6 Positioning - development files
qt6-qmltooling-plugins - Qt 6 qmltooling plugins
qt6-qpa-plugins - Qt 6 EGL plugins
qt6-quick3d-assetimporters-plugin - Qt 6 Quick 3D Assimp Import plugin
qt6-quick3d-dev - Qt 6 Quick 3D - development files
qt6-quick3d-dev-tools - Qt 6 Quick 3D development programs
qt6-remoteobjects-dev - Qt 6 Remote Objects - development files
qt6-scxml-dev - Qt 6 SCXML - development files
qt6-shader-baker - Qt 6 shader baker
qt6-tools-dev - Qt 6 Tools - development files
qt6-tools-dev-tools - Qt 6 development tools
qt6-tools-private-dev - Qt 6 Tools - private development files
qt6-translations-l10n - translations for Qt 6
qt6-virtualkeyboard-plugin - Qt 6 Virtual Keyboard
qt6-wayland - Qt 6 Wayland platform plugin
qt6-wayland-dev - Qt 6 Wayland - development files
qt6-wayland-dev-tools - Qt 6 Wayland developer tools
qt6-webengine-dev - Qt 6 WebEngine library - development files
qt6-webengine-dev-tools - Qt 6 WebEngine development programs
qt6-webengine-private-dev - Qt 6 WebEngine library - private development files
qt6-webview-dev - Qt 6 WebView - development files
qt6-webview-plugins - Qt 6 WebView plugins
qt6-xdgdesktopportal-platformtheme - Qt 6 XDG Desktop Portal platform theme
qtkeychain-qt6-dev - Development files for qtkeychain (QT6 version)

*/
