#include <memory>
#include <QApplication>
#include <QFont>
#include <QGridLayout>
#include <QPushButton>
#include <QWidget>
//FIXME OLD QWebView #include <QtWebKit/QtWebKit>
#include <QSplitter>
#include <QLineEdit>
#include <SignalsManager.h>
//#include <creatorutils/DomTreeTextHtmlGen.h>
#include <url/Url.h>
#include <Configuration.h>
#include <Globals.h>
#include <GuiGlobals.h>
#include <WebkitCreatorFactory.h>
#include <SimpleCreatorFactory.h>
#include <CrawlerMainWindowUi.h>
#include <CreatorMainWindowUi.h>
#include <php_embedding/php_embedding_callbacks.h>

using namespace crawl;

std::unique_ptr<crawl::NetscavatorFactoryIF> createNetcavatorFactory(
        const boost::shared_ptr<crawl::Configuration>& c)
{
    const auto browser = c->valueStrGet("browser");
    if (browser == "webkit") {
        return std::make_unique<WebkitCreatorFactory>(c);
    }
    else if (browser == "simple") {
        return std::make_unique<SimpleCreatorFactory>(c);
    }

    return std::unique_ptr<crawl::NetscavatorFactoryIF>();
}



#ifdef WINDOWS
#include <windows.h>
#include <stdio.h>
#include <fcntl.h>
#include <io.h>
#include <iostream>
#include <fstream>


void setStdOutToNewConsole()
{
    // allocate a console for this app
    AllocConsole();

    // redirect unbuffered STDOUT to the console
    HANDLE consoleHandle = GetStdHandle(STD_OUTPUT_HANDLE);
    int fileDescriptor = _open_osfhandle((intptr_t)consoleHandle, _O_TEXT);
    FILE *fp = _fdopen( fileDescriptor, "w" );
    *stdout = *fp;
    setvbuf( stdout, NULL, _IONBF, 0 );

    // give the console window a nicer title
    SetConsoleTitle("Std Output");

    // give the console window a bigger buffer size
    CONSOLE_SCREEN_BUFFER_INFO csbi;
    if ( GetConsoleScreenBufferInfo(consoleHandle, &csbi) )
    {
        COORD bufferSize;
        bufferSize.X = csbi.dwSize.X;
        bufferSize.Y = 9999;
        SetConsoleScreenBufferSize(consoleHandle, bufferSize);
    }
}
#endif

int main(int argc, char *argv[])
{
#ifdef WINDOWS
//	setStdOutToNewConsole();
#endif

    boost::shared_ptr<crawl::Configuration> c = crawl::g()->configuration();
    g_phpEmbedCallbacks::Instance().logToStdOut = true;

    if ( !c->parseCommandLine( "creator", argc, argv ) ) {
        exit(0);
    }
    c->printSettings();

    auto netscavatorFactoryPtr = createNetcavatorFactory(c);

    QCoreApplication::setOrganizationName("Nitram");
    QCoreApplication::setOrganizationDomain("netscavator.com");
    QCoreApplication::setApplicationName("Sleipner Creator");
    QApplication app(argc, argv);
    QLocale::setDefault(QLocale(QLocale::English, QLocale::UnitedStates));

    CreatorMainWindowUi window(netscavatorFactoryPtr.get());
    window.init();
    window.loadPhpScript(QString::fromUtf8(c->valueStrGet("script-path").c_str()));
    window.runCrawlerRobot(c->runMode());
    window.show();

    return app.exec();
}


