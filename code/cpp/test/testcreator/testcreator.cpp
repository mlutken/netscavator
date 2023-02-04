#include <QApplication>
#include <QFont>
#include <QGridLayout>
#include <QPushButton>
#include <QWidget>
#include <QtWebKit>
#include <QSplitter>
#include <QLineEdit>
#include <QWindowsStyle>
#include <SignalsManager.h>
#include <WebKitDomDocumentLinearQt.h>
#include <WebKitBrowserQt.h>
//#include <creatorutils/DomTreeTextHtmlGen.h>
#include <url/Url.h>
#include <Configuration.h>
#include <Globals.h>
#include <GuiGlobals.h>
#include "CreatorMainWidget.h"
#include <CreatorMainWindowUi.h>

#include "tabdialog.h"
#include "lcdrange.h"
#include "MyWidget.h"
#include <coreplugin/manhattanstyle.h>

using namespace crawl;


void printSettings()
{
    boost::shared_ptr<crawl::Configuration> c= crawl::g()->configuration();

    printf("Config url                 : %s\n", c->valueStrGet("url").c_str() );
    printf("Config exe-path            : %s\n", c->valueStrGet("exe-path").c_str() );
    printf("Config exe-dir             : %s\n", c->valueStrGet("exe-dir").c_str() );
    printf("Config exe-name            : %s\n", c->valueStrGet("exe-name").c_str() );
    printf("Config exe-stemname        : %s\n", c->valueStrGet("exe-stemname").c_str() );
    printf("Config cfg-path            : %s\n", c->valueStrGet("cfg-path").c_str() );
    printf("Config xul-dir             : %s\n", c->valueStrGet("xul-dir").c_str() );
    printf("Config run-mode            : %s\n", c->valueStrGet("run-mode").c_str() );
    printf("Config upload-result       : %s\n", c->valueStrGet("upload-result").c_str() );
    printf("Config load-images         : %s\n", c->valueStrGet("load-images").c_str() );
    printf("Config script-path         : %s\n", c->valueStrGet("script-path").c_str() );
    printf("Config script-name         : %s\n", c->valueStrGet("script-name").c_str() );
    printf("Config script-dir          : %s\n", c->valueStrGet("script-dir").c_str() );
    printf("Config php-ini-path        : %s\n", c->valueStrGet("php-ini-path").c_str() );
    printf("Config Script arguments    : %s\n", c->phpArgsStr().c_str() );
    printf("Config Script include dirs : %s\n", c->scriptIncludeDirsIniFileStr().c_str() );
    printf("Config exit-when-done      : %s\n", c->valueStrGet("exit-when-done").c_str() );
    printf("Config win-width           : %d\n", c->valueIntGet("win-width") );
    printf("Config win-height          : %d\n", c->valueIntGet("win-height") );

}


int main(int argc, char *argv[])
{

//    Url u( "http://sleipnerexamples.com.localhost/sites/ExDoSearchActionsAndClickNext/searchlisting1.php?producttype=all" );
//    printf("O: %s\n", u.rawString().c_str() );
//    printf("P: %s\n", u.parsedString().c_str() );
//    printf("Subdir: %s\n", u.subdirPath().string().c_str() );

//    u = Url ( "http://www.imusic.dk/page/search?combined=&artist=&title=&composer=&released=0&releaseDate[mon]=4&releaseDate[year]=2011&label=&releaseCountryId=0&releaseCode=&ean=&genreId=&mediaGroupId=&search=S�g+i+kataloget&_form=searchForm" );
//    printf("O: %s\n", u.rawString().c_str() );
//    printf("P: %s\n", u.parsedString().c_str() );
//    printf("Subdir: %s\n", u.subdirPath().string().c_str() );

//    qDebug() << "Debug out\n";
////    std::string s = "http://www.imusic.dk/?released=0&releaseDate%5Bmon%5D";
//    std::string s = "/?released=0&releaseDate%5Bmon%5D";
//    qDebug() << "s  : " << s.c_str() << "\n";

//    //    QString qs ( QString::fromUtf8(s.c_str()) );
//    QString qs ( s.c_str() );
//    qDebug() << "qs : " << qs << "\n";

////    QUrl qu( qs, QUrl::TolerantMode );
//    QUrl qu( qs, QUrl::StrictMode );
//    qDebug() << "qu : " << qu << "\n";
//    qDebug() << "qus: " << qu.toString() << "\n";
//    qDebug() << "que: " << qu.toEncoded() << "\n";
//    qDebug() << "qud: " << qu.toString().toUtf8().data() << "\n";


////    printf("ML: Temporary exit for testing Url parsing\n");
////    exit(0);



    boost::shared_ptr<crawl::Configuration> c= crawl::g()->configuration();

    if ( !c->parseCommandLine( "creator", argc, argv ) ) {
        exit(0);
    }
    printSettings();

//    QString baseName ("windows");
//    QString baseName = QApplication::style()->objectName();

 //   QApplication::setStyle(new ManhattanStyle(baseName) );

    QCoreApplication::setOrganizationName("Nitram");
    QCoreApplication::setOrganizationDomain("netscavator.com");
    QCoreApplication::setApplicationName("Sleipner Creator");
    QApplication app(argc, argv);


    TabDialog widget( QString::fromUtf8( c->valueStrGet("script-path").c_str() ) );
    widget.show();

    //qApp->setStyleSheet("QTabBar::tab { background: white }");
 //   qApp->setStyleSheet("QTabBar::tab { background: lightgray; color: white; padding: 10px; } QTabBar::tab:selected { background: gray; } QTabWidget::pane { border: 0; } QWidget { background: lightgray; }");

//    CreatorMainWindowUi window;
//    window.init();
//    window.show();

    return app.exec();
}


/*

    Url u( "http://sleipnerexamples.com.localhost/sites/ExDoSearchActionsAndClickNext/searchlisting1.php?producttype=all" );
    printf("O: %s\n", u.rawString().c_str() );
    printf("P: %s\n", u.parsedString().c_str() );
    printf("Subdir: %s\n", u.subdirPath().string().c_str() );

    u = Url ( "http://www.imusic.dk/page/search?combined=&artist=&title=&composer=&released=0&releaseDate[mon]=4&releaseDate[year]=2011&label=&releaseCountryId=0&releaseCode=&ean=&genreId=&mediaGroupId=&search=S�g+i+kataloget&_form=searchForm" );
    printf("O: %s\n", u.rawString().c_str() );
    printf("P: %s\n", u.parsedString().c_str() );
    printf("Subdir: %s\n", u.subdirPath().string().c_str() );

    QUrl qu("http://www.imusic.dk/page/search?combined=&artist=&title=&composer=&released=0&releaseDate%5Bmon%5D=4&releaseDate%5Byear%5D=2011&label=&releaseCountryId=0&releaseCode=&ean=&genreId=&mediaGroupId=&search=S%F8g+i+kataloget&_form=searchForm");

    qDebug() << "Debug out\n";
    qDebug() << qu;

    printf("ML: Temporary exit for testing Url parsing\n");
    exit(0);


    Url u( "http://sleipnerexamples.com.localhost/sites/ExDoSearchActionsAndClickNext/searchlisting1.php?producttype=all" );
    printf("O: %s\n", u.rawString().c_str() );
    printf("P: %s\n", u.parsedString().c_str() );
    printf("Subdir: %s\n", u.subdirPath().string().c_str() );

    u = Url ( "http://sleipnerexamples.com.localhost" );
    printf("O: %s\n", u.rawString().c_str() );
    printf("P: %s\n", u.parsedString().c_str() );
    printf("Subdir: %s\n", u.subdirPath().string().c_str() );

    u = Url ( "http://sleipnerexamples.com.localhost/sites/" );
    printf("O: %s\n", u.rawString().c_str() );
    printf("P: %s\n", u.parsedString().c_str() );
    printf("Subdir: %s\n", u.subdirPath().string().c_str() );

    u = Url ( "sleipnerexamples.com.localhost/sites/" );
    printf("O: %s\n", u.rawString().c_str() );
    printf("P: %s\n", u.parsedString().c_str() );
    printf("Subdir: %s\n", u.subdirPath().string().c_str() );

    u = Url ( "sleipnerexamples.com.localhost" );
    printf("O: %s\n", u.rawString().c_str() );
    printf("P: %s\n", u.parsedString().c_str() );
    printf("Subdir: %s\n", u.subdirPath().string().c_str() );


    u = linkComplete( Url("http://www.mydomain.com"), "index.html" );
    printf("M: %s\n", u.parsedString().c_str() );
    printf("SubdirM: %s\n", u.subdirPath().string().c_str() );

    u = linkComplete( Url("http://en.wikipedia.org/wiki/Robert_Atkins_(nutritionist)"), "Kim_Larsen" );
    printf("M: %s\n", u.parsedString().c_str() );
    printf("SubdirM: %s\n", u.subdirPath().string().c_str() );





//    u.domainSet("www.mydomain.com");
//    printf("M: %s\n", u.parsedString().c_str() );

//    printf("ML: Temporary exit for testing Url parsing\n");
//    exit(0);

  */
