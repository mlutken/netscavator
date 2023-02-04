#include <QApplication>
#include <QWidget>
#include <applicationutils/QtHttpDownloader.h>
#include <iostream>
#include <utils/StringFinder.h>
#include <locale/default_locales.h>

using namespace std;
using namespace crawl;

crawl::QtHttpDownloader manager;

void completeCallback(QNetworkReply* reply, const QUrl& url, bool ok)
{
    cout << "Download completed[" << ok << "]: " << url.toString().toUtf8().data() << endl;
    const QString filename = QtHttpDownloader::saveFileName(url);

    if (QtHttpDownloader::saveToDisk(filename, reply)) {
        cout << "Download of " << qPrintable(url.toString()) << " succeeded (saved to " <<
                qPrintable(filename) << ")" << endl;
    }
    QCoreApplication::instance()->quit();
}

void completeByteArrayCallback(const QByteArray& data, const QUrl& url, bool ok)
{
    cout << "QByteArray Download completed[" << ok << "]: " << url.toString().toUtf8().data() << endl;
    //const QString filename = QtHttpDownloader::saveFileName(url);

    cout << "DATA\n" << qPrintable(data) << endl;
    QCoreApplication::instance()->quit();
}

void testDownload1()
{
    cout << "testDownload1()" << endl;
//    manager.download(QUrl("https://www.veromoda.com/dk/da/sitemap_index.xml"), completeCallback);
    const QUrl url("https://www.veromoda.com/on/demandware.static/-/Library-Sites-bestseller-content-library/da_DK/dwa1e426d2/affiliatefeeds/product-sitemap/Sitemap_vm_17_BSE-DK.xml.gz");
//    const QUrl url("https://www.veromoda.com/dk/da/sitemap_index.xml");

    manager.downloadToByteArray(url, completeByteArrayCallback);

}

int testDownloader(int argc, char** argv)
{
    QCoreApplication app(argc, argv);
    manager.setCompleteCallback(completeCallback);

//    QTimer::singleShot(0, &manager, &QtHttpDownloader::main);
    QTimer::singleShot(0, testDownload1);
//    QTimer::singleShot(0, &manager, &QtHttpDownloader::mainTester);
    return app.exec();

}

int testStringFinder(int , char** )
{
    cerr << "Testing StringFinder\n";
    string s = "<OL><LI> Startside </LI> <LI> Dele </LI> <LI> Sadler </LI> <LI> Sadelovertræk </LI> <LI> Cube RFR Trekking/City, black </LI> </OL>";
    StringFinder sf(s);
    cerr << "TEXT: " << s << "\n";
    cerr << "findBetween(0, \"<LI>\", \"</LI>\"): " <<  sf.findBetween(0,"<LI>", "</LI>") << "\n";
    cerr << "findBetween(1, \"<LI>\", \"</LI>\"): " <<  sf.findBetween(1,"<LI>", "</LI>") << "\n";
    cerr << "findBetween(2, \"<LI>\", \"</LI>\"): " <<  sf.findBetween(2,"<LI>", "</LI>") << "\n";
    cerr << "findBetween(3, \"<LI>\", \"</LI>\"): " <<  sf.findBetween(3,"<LI>", "</LI>") << "\n";
    cerr << "findBetween(4, \"<LI>\", \"</LI>\"): " <<  sf.findBetween(4,"<LI>", "</LI>") << "\n";
    cerr << "findBetween(5, \"<LI>\", \"</LI>\"): " <<  sf.findBetween(5,"<LI>", "</LI>") << "\n";
    cerr << "findBetween(6, \"<LI>\", \"</LI>\"): " <<  sf.findBetween(6,"<LI>", "</LI>") << "\n";

    cerr << "\n";
    cerr << "findBetween(-1, \"<LI>\", \"</LI>\"): " <<  sf.findBetween(-1,"<LI>", "</LI>") << "\n";
    cerr << "findBetween(-2, \"<LI>\", \"</LI>\"): " <<  sf.findBetween(-2,"<LI>", "</LI>") << "\n";
    cerr << "findBetween(-3, \"<LI>\", \"</LI>\"): " <<  sf.findBetween(-3,"<LI>", "</LI>") << "\n";
    cerr << "findBetween(-4, \"<LI>\", \"</LI>\"): " <<  sf.findBetween(-4,"<LI>", "</LI>") << "\n";
    cerr << "findBetween(-5, \"<LI>\", \"</LI>\"): " <<  sf.findBetween(-5,"<LI>", "</LI>") << "\n";
    cerr << "findBetween(-6, \"<LI>\", \"</LI>\"): " <<  sf.findBetween(-6,"<LI>", "</LI>") << "\n";

    cerr << findLocale("sek");
//    cerr << "3Letter cc: " << countryCodeFrom3LetterCC("dnk") << "\n";

    return 0;
}

int main(int argc, char** argv)
{

    return testStringFinder(argc, argv);
//    return testDownloader(argc, argv);

}





//int main(int argc, char *argv[])
//{
//	QApplication app(argc, argv);

//    QWidget w;
//    w.resize(1024,800);
//    w.show();
//	return app.exec();
//}

